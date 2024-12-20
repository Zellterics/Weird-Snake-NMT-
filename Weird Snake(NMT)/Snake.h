#pragma once
#include <vector>
#include <random>

class Snake
{
public:
	Snake(std::pair<int, int> startPos, void (Display)(std::vector<int> line), int(rand)(int min, int max)) {

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

		if (head.first <= 0 || head.second <= 0 || head.first >= 23 || head.second >= 23) {
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
		}
		return gameOver;



	}

	void Draw() {
		std::cout << "\033[H";
		for (int y = 0; y < 25; y++) {
			std::vector<int> x_info;
			x_info.resize(25);
			if (head.second == y) {
				x_info[head.first] = 1;
			}
			for (std::pair<int, int> piece : body) {
				if (piece.second == y) {
					x_info[piece.first] = 2;
				}
			}
			if (food.second == y) {
				x_info[food.first] = 3;
			}
			x_info[0] = 4;
			x_info[24] = 4;
			if (y == 0 || y  == 24) {
				for (int i = 0; i < 25; i++) {
					x_info[i] = 4;
				}
			}
			Display(x_info);
		}
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
	void (*Display)(std::vector<int> line);
	int (*rand)(int min, int max);
};