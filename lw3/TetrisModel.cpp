// TetrisModel.cpp
#include "TetrisModel.h"
#include <algorithm>
#include <random>
#include <array>

// Предопределенные фигуры тетрамино
const std::array<std::array<std::array<int, 4>, 4>, 7> SHAPES[7][4][4] = {
	// I
	{{0,0,0,0},
		{1,1,1,1},
		{0,0,0,0},
		{0,0,0,0}},
	// O
	{{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}},
	// T
	{{0,0,0,0},
		{0,1,0,0},
		{1,1,1,0},
		{0,0,0,0}},
	// S
	{{0,0,0,0},
		{0,1,1,0},
		{1,1,0,0},
		{0,0,0,0}},
	// Z
	{{0,0,0,0},
		{1,1,0,0},
		{0,1,1,0},
		{0,0,0,0}},
	// J
	{{0,0,0,0},
		{1,0,0,0},
		{1,1,1,0},
		{0,0,0,0}},
	// L
	{{0,0,0,0},
		{0,0,1,0},
		{1,1,1,0},
		{0,0,0,0}}
};

const int COLORS[7] = {
	0x00FFFF, // Cyan (I)
	0xFFFF00, // Yellow (O)
	0xFF00FF, // Magenta (T)
	0x00FF00, // Green (S)
	0xFF0000, // Red (Z)
	0x0000FF, // Blue (J)
	0xFFA500  // Orange (L)
};

TetrisModel::TetrisModel() : score(0), level(1), linesToNextLevel(5),
							 isPaused(false), gameOver(false) {
	grid.resize(20, std::vector<int>(10, 0));
	spawnNewPiece();
	spawnNextPiece();
}

void TetrisModel::rotate() {
	// Временная копия для проверки коллизий
	Tetromino temp = current;

	// Поворот матрицы 4x4
	for(int y = 0; y < 4; y++)
		for(int x = 0; x < 4; x++)
			temp.shape[x][3-y] = current.shape[y][x];

	if(!checkCollision(temp))
		current = temp;
}

bool TetrisModel::checkCollision(const Tetromino& t) {
	for(int y = 0; y < 4; y++) {
		for(int x = 0; x < 4; x++) {
			if(t.shape[y][x]) {
				int wx = t.x + x;
				int wy = t.y + y;

				if(wx < 0 || wx >= 10 || wy >= 20) return true;
				if(wy >= 0 && grid[wy][wx]) return true;
			}
		}
	}
	return false;
}

void TetrisModel::update() {
	if(isPaused || gameOver) return;

	Tetromino temp = current;
	temp.y++;

	if(checkCollision(temp)) {
		mergePiece();
		int cleared = clearLines();
		updateScore(cleared);
		spawnNewPiece();
	} else {
		current = temp;
	}
}

void TetrisModel::spawnNextPiece() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 6);

	int type = dist(gen);
	memcpy(next.shape, SHAPES[type], sizeof(int) * 4 * 4);
	next.color = COLORS[dist(gen)];
	next.x = 3;
	next.y = 0;
}

void TetrisModel::spawnNewPiece() {
	current = next;
	current.x = 3; // Центр стакана по X
	current.y = 0; // Верх стакана

	// Проверка на Game Over
	if(checkCollision(current)) {
		gameOver = true;
	}
	spawnNextPiece();
}

void TetrisModel::mergePiece() {
	for(int y = 0; y < 4; y++) {
		for(int x = 0; x < 4; x++) {
			if(current.shape[y][x]) {
				int gy = current.y + y;
				int gx = current.x + x;
				if(gy >= 0 && gy < 20 && gx >= 0 && gx < 10) {
					grid[gy][gx] = current.color;
				}
			}
		}
	}
}

int TetrisModel::clearLines() {
	int linesCleared = 0;
	std::vector<std::vector<int>> newGrid;

	for(int y = 0; y < 20; y++) {
		bool full = true;
		for(int x = 0; x < 10; x++) {
			if(grid[y][x] == 0) {
				full = false;
				break;
			}
		}

		if(!full) {
			newGrid.push_back(grid[y]);
		} else {
			linesCleared++;
		}
	}

	// Добавляем новые пустые строки сверху
	while(newGrid.size() < 20) {
		newGrid.insert(newGrid.begin(), std::vector<int>(10, 0));
	}

	grid = newGrid;
	return linesCleared;
}

void TetrisModel::updateScore(int linesCleared) {
	// Начисление очков за линии
	switch(linesCleared) {
	case 1: score += 10; break;
	case 2: score += 30; break;
	case 3: score += 70; break;
	case 4: score += 150; break;
	}

	// Обновление прогресса уровня
	linesToNextLevel -= linesCleared;

	// Бонус за переход уровня
	if(linesToNextLevel <= 0) {
		// Очки за оставшиеся пустые линии
		int emptyLines = 0;
		for(auto& row : grid) {
			if(std::all_of(row.begin(), row.end(), [](int cell){ return cell == 0; })) {
				emptyLines++;
			}
		}
		score += emptyLines * 10;

		level++;
		linesToNextLevel = level * 5;

		// Очистка стакана
		std::fill(grid.begin(), grid.end(), std::vector<int>(10, 0));
	}
}

void TetrisModel::moveLeft() {
	if(gameOver || isPaused) return;

	Tetromino temp = current;
	temp.x--;
	if(!checkCollision(temp)) {
		current = temp;
	}
}

void TetrisModel::moveRight() {
	if(gameOver || isPaused) return;

	Tetromino temp = current;
	temp.x++;
	if(!checkCollision(temp)) {
		current = temp;
	}
}

void TetrisModel::drop() {
	if(gameOver || isPaused) return;

	while(true) {
		Tetromino temp = current;
		temp.y++;
		if(checkCollision(temp)) break;
		current = temp;
	}
	update(); // Форсируем немедленное обновление
}

void TetrisModel::togglePause() {
	isPaused = !isPaused;
}

void TetrisModel::restart() {
	score = 0;
	level = 1;
	linesToNextLevel = 5;
	gameOver = false;
	isPaused = false;
	std::fill(grid.begin(), grid.end(), std::vector<int>(10, 0));
	spawnNewPiece();
	spawnNextPiece();
}

// Вспомогательная функция для поворота матрицы
void rotateMatrix(int matrix[4][4]) {
	int temp[4][4];
	for(int y = 0; y < 4; y++) {
		for(int x = 0; x < 4; x++) {
			temp[x][3 - y] = matrix[y][x];
		}
	}
	memcpy(matrix, temp, sizeof(temp));
}