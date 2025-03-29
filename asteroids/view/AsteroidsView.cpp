#define _USE_MATH_DEFINES

#include "AsteroidsView.h"
#include "../model/Constants.h"

AsteroidsView::AsteroidsView(const char* title)
	: CGLApplication(title, WIDTH, HEIGHT),
	  m_renderer(WIDTH, HEIGHT)
{
}

void AsteroidsView::OnInit()
{
	glTranslatef(WIDTH / 2, HEIGHT / 2, 0);
	glClearColor(0, 0, 0, 1);
}

void AsteroidsView::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_renderer.Render(m_controller.GetModel());

//	m_playerView.Render(m_controller.GetModel().GetImmutablePlayerModel(), m_width, m_height);
//
//	auto asteroids = m_controller.GetAsteroids();
//	std::for_each(asteroids.begin(), asteroids.end(), [this] (auto asteroid) {
//		m_asteroidView.Render(asteroid, m_width, m_height);
//	});
//
//	auto bullets = m_controller.GetModel().GetBullets();
//	std::for_each(bullets.begin(), bullets.end(), [this] (auto bullet) {
//		m_bulletView.Render(bullet, m_width, m_height);
//	});
}

void AsteroidsView::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glTranslatef(-m_width / 2, -m_height / 2, 0);
	m_renderer.SetBoundingRect(width, height);
	m_controller.GetMutableModel().SetBoundingRect(width, height);
	m_width = static_cast<float>(width);
	m_height = static_cast<float>(height);
	glTranslatef(m_width / 2, m_height / 2, 0);

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
