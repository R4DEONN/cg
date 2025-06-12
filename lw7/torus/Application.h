#pragma once

#include "Camera.h"

#include <GL/glew.h>
#include <GL/glut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

class Application {
public:
	Application(int width, int height, std::string  title);
	~Application();

	void Run();

private:
	int m_width;
	int m_height;
	std::string m_title;

	GLuint m_program;
	GLuint m_vertexAttributeObject;
	GLuint m_vertexBufferObject;

	Camera m_camera;
	float m_lastFrame = 0.0f;

	static const int m_rows = 5000;
	static const int m_cols = 5000;

	bool m_keys[256] = { false };

	void Init();
	void Destroy();

	void Display();
	void Idle();
	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void MousePassiveMotion(int x, int y);

	GLuint CreateProgram(const std::string& vertexPath, const std::string& fragmentPath);
	GLuint CompileShader(GLenum type, const std::string& source);

	static void DisplayWrapper();
	static void IdleWrapper();
	static void KeyboardDownWrapper(unsigned char key, int x, int y);
	static void KeyboardUpWrapper(unsigned char key, int x, int y);
	static void MousePassiveMotionWrapper(int x, int y);
	static Application* m_instance;
};