#pragma once

#define DEBUG_MODE false
#define SHOW_PHEROMONES true
#define SHOW_WORLD_MAP false
#define LIMIT_PHEROMONES_NUMBER false

const uint16_t FPS = 60;

const float PI = 4.0f * atanf(1);
const float TWO_PI = 2.0f * PI;
const float screenWidth = (float)window.getSize().x;
const float screenHeight = (float)window.getSize().y;
const float invFPS_times_1000 = 1000.0f / FPS;

const float antSpeed = 1.0f;
const float antSize = 5.0f;
const float ant_sensing_distance = 50.0f;
const float ant_wandering_angle_change = 0.4f;
const float nest_radius = 5.0f;
const float food_size_quef = 0.05f;

const float pheromone_radius = 1.0f;
const uint16_t pheromone_life_span = 300;
const float inv_pheromone_life_span = 1.0f / pheromone_life_span;

const uint16_t number_of_ants = 1000;

void fuck() {
	std::cout << "fuck\n";
}
