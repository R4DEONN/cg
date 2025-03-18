#define _USE_MATH_DEFINES

#include "AsteroidsView.h"

constexpr int WIDTH = 640;
constexpr int HEIGHT = 480;

AsteroidsView::AsteroidsView(const char* title)
	: CGLApplication(title, WIDTH, HEIGHT),
	  m_controller()
{
}

void AsteroidsView::OnInit()
{
	glTranslatef(WIDTH / 2, HEIGHT / 2, 0);

	// Задаем цвет очистки буфера кадра
	glClearColor(0, 0, 0, 1);
}

void AsteroidsView::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_playerView.Render(m_controller.GetModel().GetImmutablePlayerModel());
}

void AsteroidsView::OnReshape(int width, int height)
{
	// Настраиваем порт просмотра
	glViewport(0, 0, width, height);

	// Делаем текущей матрицу проецирования и настраиваем ее параметры
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);

	// Делаем текущей матрицей матрицу моделирования-вида
	glMatrixMode(GL_MODELVIEW);
}

void AsteroidsView::OnIdle()
{
	// Обновляем модель (например, перемещаем объекты)
	m_controller.OnIdle();
	// Запрашиваем перерисовку сцены
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
