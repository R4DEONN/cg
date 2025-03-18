#pragma once

#include <vector>
#include <cstring>

struct Tetromino
{
	int shape[4][4];
	int color;
	int x, y;

	Tetromino() {
		std::memset(shape, 0, sizeof(shape));
		color = 0;
		x = y = 0;
	}
};

class TetrisModel
{
public:
	TetrisModel();

	int score;
	int level;
	int linesToNextLevel;
	bool isPaused;
	bool gameOver;

	std::vector<std::vector<int>> grid;

	void moveLeft();

	void moveRight();

	void rotate();

	void drop();

	void update();

	void restart();

	void togglePause();

	Tetromino current, next;
private:
	bool checkCollision(const Tetromino& t);

	void mergePiece();

	int clearLines();

	void spawnNewPiece();

	void spawnNextPiece();

//	void updateLevel();

	void updateScore(int cleared);
};