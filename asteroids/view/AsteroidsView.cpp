#define _USE_MATH_DEFINES

#include "AsteroidsView.h"

constexpr int WIDTH = 640;
constexpr int HEIGHT = 480;

AsteroidsView::AsteroidsView(const char* title)
	: CGLApplication(title, WIDTH, HEIGHT),
	  m_controller(WIDTH, HEIGHT)
{
}

void AsteroidsView::OnInit()
{
	glTranslatef(m_width / 2, m_height / 2, 0);

	// Задаем цвет очистки буфера кадра
	glClearColor(0, 0, 0, 1);
}

void AsteroidsView::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_playerView.Render(m_controller.GetModel().GetImmutablePlayerModel(), m_width, m_height);

	auto asteroids = m_controller.GetAsteroids();
	std::for_each(asteroids.begin(), asteroids.end(), [this] (auto asteroid) {
		m_asteroidView.Render(asteroid, m_width, m_height);
	});

	auto bullets = m_controller.GetModel().GetBullets();
	std::for_each(bullets.begin(), bullets.end(), [this] (auto bullet) {
		m_bulletView.Render(bullet, m_width, m_height);
	});
}

void AsteroidsView::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glTranslatef(-m_width / 2, -m_height / 2, 0);
	m_width = width;
	m_height = height;
	glTranslatef(m_width / 2, m_height / 2, 0);
	m_controller.SetBoundingRect(width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
}

void AsteroidsView::OnIdle()
{
	m_controller.OnIdle();
	PostRedisplay();
}

void AsteroidsView::OnKeyboard(unsigned char key, int x, int y)
{
	m_controller.OnKeyboard(key, x, y);
}

void AsteroidsView::OnKeyboardUp(unsigned char key, int x, int y)
{
	m_controller.OnKeyboardUp(key, x, y);
}
