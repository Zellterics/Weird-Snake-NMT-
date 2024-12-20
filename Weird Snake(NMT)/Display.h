#pragma once
#include <vector>
#include <iostream>
#include <conio.h>

namespace dsp {
	void DrawLine(std::vector<int> line) {
		std::string textLine;
		for (int key : line) {
			switch (key)
			{
			case 0:
				textLine.push_back(' ');
				textLine.push_back(' ');
				break;
			case 1:
				textLine.push_back(' ');
				textLine.push_back('0');
				break;
			case 2:
				textLine.push_back(' ');
				textLine.push_back('@');
				break;
			case 3:
				textLine.push_back(' ');
				textLine.push_back('&');
				break;
			case 4:
				textLine.push_back(' ');
				textLine.push_back('#');
				break;
			default:
				break;
			}
		}
		std::cout << textLine << std::endl;
	}
	int InputManager(int lastMove) {
		if (_kbhit()) {
			enum Directions {
				Up, Down, Left, Right
			};
			char key;
			while (_kbhit()) {
				key = _getch();
			}
			switch (key) {
			case 'w':
				return Up;
			case 's':
				return Down;
			case 'a':
				return Left;
			case 'd':
				return Right;
			default:
				return lastMove;
			}
		}
		return lastMove;
	}

}