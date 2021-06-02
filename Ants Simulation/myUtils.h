#pragma once

#include <cstdlib>
#include <ctime>
#include <cmath>

int randomi(int a, int b) {
	return rng.rnd() % (b - a + 1) + a;
}

float randomf(float a, float b) {
	static const float number = 1.0f / 1e4f;
	return randomi(0, 10000) * number * (b - a) + a;
}

float crossProd(sf::Vector2f a, sf::Vector2f b) {
	return a.x * b.y - a.y * b.x;
}

float sqr(float x) {
	return x * x;
}

float magnitude_squared(sf::Vector2f a) {
	return a.x * a.x + a.y * a.y;
}

float magnitude(sf::Vector2f a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

void normalize(sf::Vector2f &a) {
	a /= magnitude(a);
}
