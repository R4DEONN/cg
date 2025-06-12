#include "Application.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <utility>

Application* Application::m_instance = nullptr;

std::string loadShader(const std::string& path)
{
	std::ifstream file(path);
	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}

Application::Application(int width, int height, std::string title)
	: m_width(width), m_height(height), m_title(std::move(title))
{
	m_instance = this;
}

Application::~Application()
{
	Destroy();
}

void Application::Run()
{
	int argc = 1;
	char* argv[1] = { (char*)"Morphing" };

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(m_width, m_height);
	glutCreateWindow(m_title.c_str());

	glewInit();

	if (!GLEW_ARB_shader_objects)
	{
		std::cerr << "OpenGL ARB shader objects not supported!" << std::endl;
		return;
	}

	Init();

	glutDisplayFunc(DisplayWrapper);
	glutIdleFunc(IdleWrapper);
	glutKeyboardFunc(KeyboardDownWrapper);
	glutKeyboardUpFunc(KeyboardUpWrapper);
	glutPassiveMotionFunc(MousePassiveMotionWrapper);

	glutMainLoop();
}

void Application::Init()
{
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	m_program = CreateProgram("../shaders/vertex.glsl", "../shaders/fragment.glsl");
	glUseProgram(m_program);

	std::vector<float> vertices;
	for (int i = 0; i < m_rows; ++i)
	{
		for (int j = 0; j < m_cols; ++j)
		{
			float u = static_cast<float>(i) / (m_rows - 1);
			float v = static_cast<float>(j) / (m_cols - 1);
			vertices.push_back(u);
			vertices.push_back(v);
		}
	}

	glGenVertexArrays(1, &m_vertexAttributeObject);
	glGenBuffers(1, &m_vertexBufferObject);

	glBindVertexArray(m_vertexAttributeObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Application::Destroy()
{
	glDeleteVertexArrays(1, &m_vertexAttributeObject);
	glDeleteBuffers(1, &m_vertexBufferObject);
	glDeleteObjectARB(m_program);
}

void Application::Display()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_program);

	float currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;
	GLint timeLoc = glGetUniformLocation(m_program, "time");
	glUniform1f(timeLoc, currentTime);

	GLint modelLoc = glGetUniformLocation(m_program, "model");
	GLint viewLoc = glGetUniformLocation(m_program, "view");
	GLint projLoc = glGetUniformLocation(m_program, "projection");

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = m_camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(m_vertexAttributeObject);
	glDrawArrays(GL_POINTS, 0, m_rows * m_cols);
	glBindVertexArray(0);

	glutSwapBuffers();
}

void Application::Idle()
{
	float currentFrame = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;

	if (m_keys['w'] || m_keys['W'])
	{
		m_camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
	}
	if (m_keys['s'] || m_keys['S'])
	{
		m_camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
	}
	if (m_keys['a'] || m_keys['A'])
	{
		m_camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
	}
	if (m_keys['d'] || m_keys['D'])
	{
		m_camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
	}
	if (m_keys[' '])
	{
		m_camera.ProcessKeyboard(CameraMovement::UP, deltaTime);
	}
	if (m_keys[17])
	{
		m_camera.ProcessKeyboard(CameraMovement::DOWN, deltaTime);
	}

	glutPostRedisplay();
}

void Application::KeyboardDown(unsigned char key, int x, int y)
{
	m_keys[key] = true;
}

void Application::KeyboardUp(unsigned char key, int x, int y)
{
	m_keys[key] = false;
}

void Application::MousePassiveMotion(int x, int y)
{
	static int lastX = x, lastY = y;

	float xoffset = x - lastX;
	float yoffset = y - lastY;
	lastX = x;
	lastY = y;

	m_camera.ProcessMouse(xoffset, yoffset);
}

void Application::DisplayWrapper()
{
	if (m_instance) m_instance->Display();
}

void Application::IdleWrapper()
{
	if (m_instance) m_instance->Idle();
}

void Application::KeyboardDownWrapper(unsigned char key, int x, int y)
{
	if (m_instance) m_instance->KeyboardDown(key, x, y);
}

void Application::KeyboardUpWrapper(unsigned char key, int x, int y)
{
	if (m_instance) m_instance->KeyboardUp(key, x, y);
}

void Application::MousePassiveMotionWrapper(int x, int y)
{
	if (m_instance) m_instance->MousePassiveMotion(x, y);
}

GLuint Application::CompileShader(GLenum type, const std::string& source)
{
	GLuint shader = glCreateShaderObjectARB(type);
	const char* src = source.c_str();
	glShaderSourceARB(shader, 1, &src, NULL);

	glCompileShaderARB(shader);

	GLint success;
	glGetObjectParameterivARB(shader, GL_OBJECT_COMPILE_STATUS_ARB, &success);
	if (!success)
	{
		char infoLog[512];
		glGetInfoLogARB(shader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}

GLuint Application::CreateProgram(const std::string& vertexPath, const std::string& fragmentPath)
{
	GLuint program = glCreateProgramObjectARB();

	GLuint vs = CompileShader(GL_VERTEX_SHADER_ARB, loadShader(vertexPath));
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER_ARB, loadShader(fragmentPath));

	glAttachObjectARB(program, vs);
	glAttachObjectARB(program, fs);

	glLinkProgramARB(program);

	GLint success;
	glGetObjectParameterivARB(program, GL_OBJECT_LINK_STATUS_ARB, &success);
	if (!success)
	{
		char infoLog[512];
		glGetInfoLogARB(program, 512, NULL, infoLog);
		std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteObjectARB(vs);
	glDeleteObjectARB(fs);

	return program;
}