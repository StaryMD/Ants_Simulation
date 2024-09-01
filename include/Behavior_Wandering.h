#pragma once

// Ant is wandering searching for food
#include "Ant.h"
#include "Behavior.h"

struct Behavior_Wandering : Behavior {
	Ant* parent;

	Behavior_Wandering(Ant* _parent) : parent(_parent) {
		parent->timer = 127;
	}

	void update(Pheromone_Map &pheromone_map) {
		int16_t startcellX = (int16_t)(parent->pos.x * pheromone_map.ratioX);
		int16_t startcellY = (int16_t)(parent->pos.y * pheromone_map.ratioY);

		startcellX = std::min(startcellX, (int16_t)(pheromone_map.sizeX - 1));
		startcellY = std::min(startcellY, (int16_t)(pheromone_map.sizeY - 1));
		startcellX = std::max(startcellX, (int16_t)0);
		startcellY = std::max(startcellY, (int16_t)0);

		sf::Vector2f oldest_pheromone_pos;
		uint16_t oldest_pheromone_age = 0;
		for (int16_t i = startcellY + 2; i >= startcellY; i--)
			for (int16_t j = startcellX + 2; j >= startcellX; j--)
				for (Pheromone *pheromone : pheromone_map.map[i][j]) {
					if (pheromone->getType() == PHEROMONE_FOOD_TYPE && parent->is_near_pheromone(pheromone) && pheromone->getAge() > oldest_pheromone_age) {
						oldest_pheromone_age = pheromone->getAge();
						oldest_pheromone_pos = pheromone->getPos();
					}
				}
		
		if (oldest_pheromone_age) {
			sf::Vector2f dir = oldest_pheromone_pos - parent->pos;
			parent->angle = atan2(dir.y, dir.x);
		}
		parent->angle += randomf(-ant_wandering_angle_change, ant_wandering_angle_change);
		parent->pos += sf::Vector2f(
			cos(parent->angle) * antSpeed,
			sin(parent->angle) * antSpeed
		);

		restrict_movement();

		if (parent->can_emanate_pheromone()) {
			uint16_t cellX = (uint16_t)(parent->pos.x * pheromone_map.ratioX);
			uint16_t cellY = (uint16_t)(parent->pos.y * pheromone_map.ratioY);

			if (cellY >= 0 && cellY < pheromone_map.sizeY && cellX >= 0 && cellX < pheromone_map.sizeX)
				pheromone_map.push(new Pheromone_Wandering(parent->pos), cellY + 1, cellX + 1);
		}
	}

	void restrict_movement() {
		if (parent->is_out_of_bounds()) {
			parent->angle += (ant_turn_coeff *= -1.0f) * PI;

			parent->pos.x = std::min(parent->pos.x, screenWidth - 1);
			parent->pos.y = std::min(parent->pos.y, screenHeight - 1);
			parent->pos.x = std::max(0.0f, parent->pos.x);
			parent->pos.y = std::max(0.0f, parent->pos.y);
		}
	}

};
