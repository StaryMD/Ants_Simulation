#pragma once

struct Behavior_Returning : Behavior {
	Ant* parent;

	Behavior_Returning(Ant *_parent) : parent(_parent) {
		parent->timer = 31;
	}

	void update(Pheromone_Map& pheromone_map) {
		parent->pos += {
			cos(parent->angle)* antSpeed,
			sin(parent->angle)* antSpeed
		};
		parent->angle += randomf(-ant_wandering_angle_change, ant_wandering_angle_change);

		if (parent->is_out_of_bounds()) {
			parent->angle += (ant_turn_coeff *= -1.0f) * PI;

			parent->pos.x = std::min(parent->pos.x, screenWidth - 1);
			parent->pos.y = std::min(parent->pos.y, screenHeight - 1);
			parent->pos.x = std::max(0.0f, parent->pos.x);
			parent->pos.y = std::max(0.0f, parent->pos.y);
		}

		if (parent->can_emanate_pheromone()) {
			uint16_t cellX = (uint16_t)(parent->pos.x * pheromone_map.ratioX);
			uint16_t cellY = (uint16_t)(parent->pos.y * pheromone_map.ratioY);

			if (cellY >= 0 && cellY < pheromone_map.sizeY && cellX >= 0 && cellX < pheromone_map.sizeX)
				pheromone_map.push(new Pheromone_Food(parent->pos), cellY + 1, cellX + 1);
		}
	}

};
