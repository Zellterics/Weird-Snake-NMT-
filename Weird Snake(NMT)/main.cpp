#include <iostream>
#include "Snake.h"
#include "Display.h"
#include "handMade.h"
#include <thread>
#include <chrono>


int main() {
	Snake snake({ 20, 19 }, dsp::DrawLine, hm::RandomGenerator);
	bool gameOver = false;
	while (true) {
		gameOver = snake.Update(dsp::InputManager);
		snake.Draw();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		if (gameOver) {
			break;
		}
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	return 0;
}