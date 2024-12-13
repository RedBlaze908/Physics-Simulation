#include "ball.h"

Ball::Ball() {
	ball.setRadius(50.f);
	isAlive = true;
}

Ball::Ball(int x, int y) : Ball() {
	ball.setPosition(sf::Vector2f(x, y));
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 255);
	int r1 = distrib(gen);
	int r2 = distrib(gen);
	int r3 = distrib(gen);
	ball.setFillColor(sf::Color(r1, r2, r3));
}

Ball::~Ball() { isAlive = false; }

void Ball::setPosition(float x, float y) {
	ball.setPosition(sf::Vector2f(x, y));
}

void Ball::fall(float gravity) {
	if (ball.getPosition().y < 622) {
		speed += gravity * dt;
		setPosition(ball.getPosition().x, (ball.getPosition().y + (speed * dt)));
		time += dt;
		IsFalling = true;
	}
	else IsFalling = false;
}

void Ball::bounce() {
	if (nBounce) {
		speed = -speed * e;
		ball.setPosition(sf::Vector2f(ball.getPosition().x, (ball.getPosition().y + (speed * dt))));
		IsFalling = true;
		nBounce--;
	}
}
