#pragma once

#include "Pheromone.h"
#include "constants.h"

struct Pheromone_Wandering : Pheromone {
  sf::Vector2f pos;
  uint16_t age;

  Pheromone_Wandering(sf::Vector2f _pos) : pos(_pos) { age = 0; }

  uint16_t update_life_span() { return ++age; }

  sf::Vector2f getPos() { return pos; }

  uint16_t getAge() { return age; }

  void draw() {
    float opacity = 1.0f - age * inv_pheromone_life_span;
    Pheromone_Shape.setPosition(pos);
    Pheromone_Shape.setFillColor(
        sf::Color(0, 0, (uint8_t)255, (uint8_t)(opacity * 255.0f)));
    window.draw(Pheromone_Shape);
  }

  uint8_t getType() { return PHEROMONE_WANDERING_TYPE; }
};
