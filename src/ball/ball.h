#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>

class Ball {
	sf::CircleShape ball;

	bool isAlive = false;
	bool IsFalling = true;

	double speed = 0.0;
	double dt = 0.01;
	double time = 0.0;
	double e = 0.8;

	int nBounce = 10;

public:
	Ball();
	Ball(int x, int y);
	~Ball();

	void setPosition(float x, float y);

	bool isFalling() { return IsFalling; }
	
	/// This function put gravity on the object
	void fall(float gravity);

	void bounce();


	void Draw(sf::RenderWindow& window) { window.draw(ball); }
};