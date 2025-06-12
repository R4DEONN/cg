//
// Created by admin on 04.04.2025.
//

#pragma once

#include <vector>

class Model
{
public:
	struct Ball
	{
		float x, y, z;      // Позиция шарика
		float dx, dy, dz;   // Направление движения
		float radius;       // Радиус шарика
	};

	struct Paddle
	{
		float x, y, z;      // Позиция ракетки
		float width, height;// Размеры ракетки
	};

	struct Brick
	{
		float x, y, z;      // Позиция кирпича
		float width, height, depth; // Размеры кирпича
		int health;         // Здоровье кирпича (сколько ударов до разрушения)
	};

	Ball ball;
	Paddle paddle;
	std::vector<Brick> bricks;
	int score = 0;

	Model()
	{
		// Инициализация шарика
		ball = {0.0f, -5.0f, 0.0f, 0.02f, 0.02f, 0.0f, 0.5f};

		// Инициализация ракетки
		paddle = {0.0f, -8.0f, 0.0f, 2.0f, 0.5f};

		// Создание кирпичей
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				bricks.push_back({-4.5f + j * 1.0f, 4.0f - i * 0.5f, -10.0f, 0.9f, 0.4f, 0.2f, 1});
			}
		}
	}

	void UpdateBallPosition()
	{
		ball.x += ball.dx;
		ball.y += ball.dy;
		ball.z += ball.dz;

		// Отскок от стен
		if (ball.x - ball.radius < -5.0f || ball.x + ball.radius > 5.0f)
			ball.dx = -ball.dx;
		if (ball.y + ball.radius > 5.0f)
			ball.dy = -ball.dy;
		if (ball.z - ball.radius < -10.0f || ball.z + ball.radius > 0.0f)
			ball.dz = -ball.dz;
	}

	void CheckCollisions()
	{
		// Проверка столкновений с ракеткой
		if (ball.y - ball.radius <= paddle.y && ball.x >= paddle.x - paddle.width / 2 &&
			ball.x <= paddle.x + paddle.width / 2)
		{
			ball.dy = -ball.dy;
		}

		// Проверка столкновений с кирпичами
		for (auto& brick : bricks)
		{
			if (brick.health > 0 &&
				ball.x >= brick.x - brick.width / 2 && ball.x <= brick.x + brick.width / 2 &&
				ball.y >= brick.y - brick.height / 2 && ball.y <= brick.y + brick.height / 2 &&
				ball.z >= brick.z - brick.depth / 2 && ball.z <= brick.z + brick.depth / 2)
			{
				brick.health--;
				score += 10;
				ball.dy = -ball.dy;
			}
		}
	}
};