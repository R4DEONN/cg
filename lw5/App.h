#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <iostream>
#include <memory>
#include "View.h"
#include "Controller.h"

class App
{
public:
	App(int width, int height, bool fullscreen)
		: m_windowWidth(width), m_windowHeight(height)
	{
		int fakeArgc = 1;
		char* fakeArgv[] = { (char*)"Arcanoid3D" };
		glutInit(&fakeArgc, fakeArgv);

		if (!glfwInit())
		{
			std::cerr << "Ошибка инициализации GLFW!" << std::endl;
			return;
		}
		if (fullscreen)
		{
			m_monitor = glfwGetPrimaryMonitor();
			auto viewMode = glfwGetVideoMode(m_monitor);
			m_windowWidth = viewMode->width;
			m_windowHeight = viewMode->height;
		}

		m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, "3D Maze", m_monitor, nullptr);
		if (!m_window)
		{
			std::cerr << "Ошибка создания окна!" << std::endl;
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, this);
		glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
//		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		InitOpenGL();
		UpdateProjection(m_windowWidth, m_windowHeight);

		m_model = std::make_shared<Model>();
		m_view = std::make_shared<View>(m_model);
		m_controller = std::make_shared<Controller>(m_model, m_view);
	}

	~App()
	{
		if (m_window)
		{
			glfwDestroyWindow(m_window);
			glfwTerminate();
		}
	}

	void Run()
	{
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
	GLFWwindow* m_window = nullptr;
	GLFWmonitor* m_monitor = nullptr;
	std::shared_ptr<Model> m_model;
	std::shared_ptr<View> m_view;
	std::shared_ptr<Controller> m_controller;

	static void InitOpenGL()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		GLfloat lightPos[] = {-10, 50, 50, 1.0f};
		GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 0.3f};
		GLfloat specularLight[] = {1.0f, 1.0f, 1.0f, 1.0f};

		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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
		auto* view = static_cast<App*>(glfwGetWindowUserPointer(window));
		if (view)
		{
			App::UpdateProjection(width, height);
		}
	}

	void Update()
	{
		m_controller->Update();

		m_view->Render();
	}
};
