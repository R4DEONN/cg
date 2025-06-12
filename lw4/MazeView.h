#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <iostream>
#include "MazeController.h"
#include "stb_image.h"
#include "Enemy.h"

GLuint LoadTexture(const char* filename)
{
	int width, height, channels;
	unsigned char* image = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);

	if (!image)
	{
		std::cerr << "Error loading: " << filename << std::endl;
		return 0;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	stbi_image_free(image);
	return texture;
}

class MazeView
{
public:
	MazeView(int width, int height)
		: m_windowWidth(width), m_windowHeight(height), m_window(nullptr), m_enemy(0, 0, 10)
	{
	}

	~MazeView()
	{
		if (m_window)
		{
			glfwDestroyWindow(m_window);
			glfwTerminate();
		}
	}

	void Run()
	{
		if (!glfwInit())
		{
			std::cerr << "Ошибка инициализации GLFW!" << std::endl;
			return;
		}

		auto monitor = glfwGetPrimaryMonitor();
		auto viewMode = glfwGetVideoMode(monitor);
		m_windowWidth = viewMode->width;
		m_windowHeight = viewMode->height;
		m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, "3D Maze", monitor, nullptr);
		if (!m_window)
		{
			std::cerr << "Ошибка создания окна!" << std::endl;
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, this);
		glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		InitOpenGL();
		UpdateProjection(m_windowWidth, m_windowHeight);

		wallTexture = LoadTexture("wall_texture.png");
		m_enemyTexture = LoadTexture("malov.png");

		while (!glfwWindowShouldClose(m_window))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Update();

			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
	}

private:
	int m_windowWidth;
	int m_windowHeight;
	GLFWwindow* m_window;
	MazeController m_controller;
	GLuint wallTexture{};
	Enemy m_enemy;
	GLuint m_enemyTexture{};

	void InitOpenGL()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		auto& model = m_controller.GetModel();
		GLfloat lightPos[] = {model.GetCamX(), model.GetCamY(), model.GetCamZ(), 1.0f};
		GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 0.3f};
		GLfloat specularLight[] = {1.0f, 1.0f, 1.0f, 1.0f};

		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
		//TODO: Как задать точечный и направленный источник света

	}

	static void UpdateProjection(int width, int height)
	{
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0f, (double)width / (double)height, 0.1f, 500.0f);
		glMatrixMode(GL_MODELVIEW);
	}

	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		auto* view = static_cast<MazeView*>(glfwGetWindowUserPointer(window));
		if (view)
		{
			MazeView::UpdateProjection(width, height);
		}
	}

	void Update()
	{
		static float lastTime = glfwGetTime();
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		m_enemy.Update(m_controller.GetModel(), deltaTime);

		m_controller.HandleInput(m_window);
		UpdateView();
	}

	void UpdateView()
	{
		auto& model = m_controller.GetModel();
		glLoadIdentity();
		gluLookAt(model.GetCamX(), model.GetCamY(), model.GetCamZ(),
			model.GetCamX() + cos(model.GetAngleY() * M_PI / 180),
			model.GetCamY(),
			model.GetCamZ() + sin(model.GetAngleY() * M_PI / 180),
			0, 1, 0);

		GLfloat lightPos[] = {model.GetCamX(), model.GetCamY() + 5.0f, model.GetCamZ(), 1.0f};
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

		DrawMaze();
		DrawEnemy();
	}

	void DrawEnemy()
	{
		InitMaterialLightness();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_enemyTexture);

		float x = m_enemy.GetX();
		float y = m_enemy.GetY();
		float z = m_enemy.GetZ();
		float size = MazeModel::CELL_SIZE * 0.8f;
		float rotation = m_enemy.GetRotation();

		glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(rotation, 0.0f, 1.0f, 0.0f);

		glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-size/2, -size/2, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(size/2, -size/2, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(size/2, size/2, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-size/2, size/2, 0);

		glEnd();

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		//Windows Media Foundation
	}


	void DrawMaze()
	{
		auto& model = m_controller.GetModel();
		int size = MazeModel::GetMazeSize();
		int cellSize = MazeModel::CELL_SIZE;
		const int(*maze)[16] = model.GetMaze();

		DrawFloor(0, 0, 0, (size - 1) * cellSize);

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (maze[i][j] == 1)
				{
					DrawWall(i * cellSize, 0, j * cellSize, cellSize);
				}
			}
		}

		DrawCeiling(0, cellSize, 0, (size - 1) * cellSize);
	}

	void DrawWall(float x, float y, float z, float size) const
	{
		//TODO: Выделить отрисовку лабиринта в отдельный класс
		InitMaterialLightness();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, wallTexture);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glBegin(GL_QUADS);

		// Передняя стена
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + size, y, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + size, y + size, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + size, z);

		// Задняя стена
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + size, y, z + size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + size, y + size, z + size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + size, z + size);

		// Левая стена
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + size, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + size, z + size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + size);

		// Правая стена
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + size, y, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + size, y + size, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + size, y + size, z + size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + size, y, z + size);

		glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	static void DrawFloor(float x, float y, float z, float size)
	{
		InitMaterialLightness();
		GLfloat floorColor[] = {0.0f, 1.0f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, floorColor);

		glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(x, y, z);
		glVertex3f(x + size, y, z);
		glVertex3f(x + size, y, z + size);
		glVertex3f(x, y, z + size);
		glEnd();
	}

	static void DrawCeiling(float x, float y, float z, float size)
	{
		GLfloat ceilingColor[] = {0.0f, 0.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, ceilingColor);
		GLfloat matAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f};
		GLfloat matSpecular[] = {0.5f, 0.5f, 0.5f, 1.0f};
		GLfloat matShininess[] = {32.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
		glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

		glBegin(GL_QUADS);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(x, y, z);
		glVertex3f(x + size, y, z);
		glVertex3f(x + size, y, z + size);
		glVertex3f(x, y, z + size);
		glEnd();
	}

	static void InitMaterialLightness()
	{
		GLfloat matAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f};
		GLfloat matDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat matSpecular[] = {0.5f, 0.5f, 0.5f, 1.0f};
		GLfloat matShininess[] = {32.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
		glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	}
};
