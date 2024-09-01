#pragma once

#include <SFML/Graphics.hpp>

#define PHEROMONE_FOOD_TYPE 1
#define PHEROMONE_WANDERING_TYPE 2

sf::CircleShape Pheromone_Shape;

struct Pheromone {
  sf::Vector2f pos;
  uint16_t age;

  Pheromone() {
    pos = {0.0f, 0.0f};
    age = 0;
  }

  virtual sf::Vector2f getPos() = 0;
  virtual uint16_t getAge() = 0;
  virtual uint16_t update_life_span() = 0;
  virtual void draw() = 0;
  virtual uint8_t getType() = 0;
};

#include "Pheromone_Food.h"
#include "Pheromone_Map.h"
#include "Pheromone_Wandering.h"
