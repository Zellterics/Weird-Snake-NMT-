#pragma once
#include <vector>
#include <random>

class Snake
{
public:
	Snake(std::pair<int, int> startPos, void (Display)(std::vector<std::vector<int>> map), int(rand)(int min, int max)) {

		if (startPos.second < 1) {startPos.second = 2;}
		if (startPos.second >= 25) { startPos.second = 24; }
		if (startPos.first < 1) {startPos.first = 2;}
		if (startPos.first >= 25) { startPos.first = 24; }
		this->rand = rand;
		this->Display = Display;
		direction = Up;
		head = startPos;
		body.emplace_back(startPos.first, startPos.second - 1);
		gameOver = false;
		food = { rand(2, 22), rand(2, 8) };
	}
	int GetLenght() { return body.size() + 1; };

	bool Update(int (*Move)(int lastInput)) {
		std::pair<int, int> lastPos = head;
		Directions lastDirection = direction;
		direction = (Directions)Move((int)lastDirection);
		switch (direction)
		{
		case Up:
			if (lastDirection == Down) {
				head.second = head.second + 1;
				direction = Down;
			}
			else {
				head.second = head.second - 1;
			}
			break;
		case Down:
			if (lastDirection == Up) {
				head.second = head.second - 1;
				direction = Up;
			}
			else {
				head.second = head.second + 1;
			}
			break;
		case Right:
			if (lastDirection == Left) {
				head.first = head.first - 1;
				direction = Left;
			}
			else {
				head.first = head.first + 1;
			}
			break;
		case Left:
			if (lastDirection == Right) {
				head.first = head.first + 1;
				direction = Right;
			}
			else {
				head.first = head.first - 1;
			}
			break;
		default:
			break;
		}

		for (std::pair<int, int>& piece : body) {
			std::pair<int, int> savePiece = piece;
			piece = lastPos;
			lastPos = savePiece;
			
		}

		if (head.first <= 0 || head.second <= 0 || head.first >= 24 || head.second >= 24) {
			gameOver = true;
		}
		for (std::pair<int, int> piece : body) {
			if (head == piece) {
				gameOver = true;
			}
		}

		if (head == food) {
			body.push_back(lastPos);
			food = { rand(1, 23), rand(1, 23) };
			bool foodOverBody = false;
			for (std::pair<int, int> piece : body) {
				if (food == piece) {
					foodOverBody = true;
				}
			}
			if (!foodOverBody) {
				return gameOver;
			}

			int maxX = std::max_element(body.begin(), body.end(), [](const std::pair<int, int>& x, const std::pair<int, int>& y) {
				return x.first < y.first;
				})->first;
			if (maxX < 23) {
				food = { rand(maxX, 23), rand(1,23) };
				return gameOver;
			}
			int minX = std::min_element(body.begin(), body.end(), [](const std::pair<int, int>& x, const std::pair<int, int>& y) {
				return x.first < y.first;
				})->first;
			if (minX > 1) {
				food = { rand(1, minX), rand(1,23) };
				return gameOver;
			}
			int maxY = std::max_element(body.begin(), body.end(), [](const std::pair<int, int>& x, const std::pair<int, int>& y) {
				return x.first < y.first;
				})->first;
			if (maxY > 1) {
				food = { rand(maxY, 23), rand(1,23) };
				return gameOver;
			}
			int minY = std::min_element(body.begin(), body.end(), [](const std::pair<int, int>& x, const std::pair<int, int>& y) {
				return x.first < y.first;
				})->first;
			if (minY > 1) {
				food = { rand(1, minY), rand(1,23) };
				return gameOver;
			}
			do {
				food = { rand(1, 23), rand(1, 23) };
				bool foodOverBody = false;
				for (std::pair<int, int> piece : body) {
					if (food == piece) {
						foodOverBody = true;
					}
				}
				if (!foodOverBody) {
					return gameOver;
				}
			} while (foodOverBody);
		}
		return gameOver;


	}

	void Draw() {
		std::vector<std::vector<int>> map;
		map.resize(25, std::vector<int>(25, 0));
		for (int y = 0; y < 25; y++) {
			for (int x = 0; x < 25; x++) {
				if (head.second == y && head.first == x) {
					map[y][x] = 1;
				}

				for (std::pair<int, int> piece : body) {
					if (piece.second == y && piece.first == x) {
						map[y][x] = 2;
					}
				}

				if (food.second == y && food.first == x) {
					map[y][x] = 3;
				}

				if (x == 0 || x == 24 || y == 0 || y == 24) {
					map[y][x] = 4;
				}
			}
		}
		Display(map);
	}

	enum Directions {
		Up, Down, Left, Right
	};
	
	bool gameOver;
	Directions direction;
	std::pair<int, int> head;
	std::pair<int, int> food;
private:
	std::vector<std::pair<int, int>> body;
	void (*Display)(std::vector<std::vector<int>> line);
	int (*rand)(int min, int max);
};