#pragma once

#include "../ball/ball.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include <string>


class Window {
	sf::RenderWindow window;
	sf::Clock deltaClock;

	std::vector<Ball> ball;

	float gravity = 9.807;

	bool open = false;

public:
	Window();
	~Window();

	void Run();
};