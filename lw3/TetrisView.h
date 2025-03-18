// TetrisView.h
#pragma once
#include "TetrisModel.h"
#include <windows.h>
#include <gl/gl.h>
#include <string>

class TetrisView {
public:
	void render(const TetrisModel& model, HDC hdc) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Отрисовка игрового поля
		drawGrid(model.grid);
		drawCurrentTetromino(model.current);

		// Отрисовка информационной панели
		drawInfoPanel(model, hdc);

		// Отрисовка состояния игры
		if(model.gameOver) {
			drawGameOver(hdc);
		}
		if(model.isPaused) {
			drawPause(hdc);
		}
	}

private:
	void setColor(int hexColor) {
		float r = ((hexColor >> 16) & 0xFF) / 255.0f;
		float g = ((hexColor >> 8) & 0xFF) / 255.0f;
		float b = (hexColor & 0xFF) / 255.0f;
		glColor3f(r, g, b);
	}

	void drawGrid(const std::vector<std::vector<int>>& grid) {
		// Отрисовка заполненных клеток
		for(int y = 0; y < 20; y++) {
			for(int x = 0; x < 10; x++) {
				if(grid[y][x] != 0) {
					setColor(grid[y][x]);
					glRectf(x, y, x+1, y+1);
				}
			}
		}

		// Отрисовка сетки
		glColor3f(0.3f, 0.3f, 0.3f);
		glBegin(GL_LINES);
		for(int x = 0; x <= 10; x++) {
			glVertex2f(x, 0);
			glVertex2f(x, 20);
		}
		for(int y = 0; y <= 20; y++) {
			glVertex2f(0, y);
			glVertex2f(10, y);
		}
		glEnd();
	}

	void drawCurrentTetromino(const Tetromino& t) {
		setColor(t.color);
		for(int y = 0; y < 4; y++) {
			for(int x = 0; x < 4; x++) {
				if(t.shape[y][x]) {
					float px = t.x + x;
					float py = t.y + y;
					glRectf(px, py, px+1, py+1);
				}
			}
		}
	}

	void drawInfoPanel(const TetrisModel& model, HDC hdc) {
		// Переключаемся в режим 2D текста
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, 800, 600, 0, -1, 1); // Примерные размеры окна
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		// Настройки текста
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));
		HFONT hFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
			VARIABLE_PITCH, TEXT("Arial"));
		SelectObject(hdc, hFont);

		// Позиционирование текста
		int xPos = 300; // Правая часть окна
		int yPos = 50;

		std::wstring info = L"Score: " + std::to_wstring(model.score) + L"\n"
							+ L"Level: " + std::to_wstring(model.level) + L"\n"
							+ L"Lines to next: " + std::to_wstring(model.linesToNextLevel);

		TextOutW(hdc, xPos, yPos, info.c_str(), info.length());

		// Отрисовка следующей фигуры
		yPos += 150;
		TextOutW(hdc, xPos, yPos, L"Next:", 5);
		drawNextTetromino(model.next, hdc, xPos + 50, yPos + 30);

		// Восстанавливаем матрицы
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);

		DeleteObject(hFont);
	}

	void drawNextTetromino(const Tetromino& t, HDC hdc, int x, int y) {
		// Рисуем миниатюру следующей фигуры
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				if(t.shape[i][j]) {
					RECT rect = {x + j*20, y + i*20, x + (j+1)*20, y + (i+1)*20};
					HBRUSH brush = CreateSolidBrush(RGB(
						(t.color >> 16) & 0xFF,
						(t.color >> 8) & 0xFF,
						t.color & 0xFF
					));
					FillRect(hdc, &rect, brush);
					DeleteObject(brush);
				}
			}
		}
	}

	void drawGameOver(HDC hdc) {
		RECT rect = {100, 250, 400, 350};
		FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));

		SetTextColor(hdc, RGB(255, 0, 0));
		TextOutW(hdc, 150, 280, L"GAME OVER", 8);
		TextOutW(hdc, 120, 310, L"Press R to restart", 17);
	}

	void drawPause(HDC hdc) {
		SetTextColor(hdc, RGB(255, 255, 0));
		TextOutW(hdc, 150, 280, L"PAUSED", 6);
	}
};