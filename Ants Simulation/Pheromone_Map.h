#pragma once

struct Pheromone_Map {
	std::vector<std::vector<std::vector<Pheromone*>>> map;
	uint8_t sizeY, sizeX;
	uint16_t max_number_per_tile;
	float ratioY, ratioX;

	Pheromone_Map() {
		sizeY = (uint8_t)ceil(screenHeight / (2 * ant_sensing_distance));
		sizeX = (uint8_t)ceil(screenWidth / (2 * ant_sensing_distance));
		ratioY = sizeY / screenHeight;
		ratioX = sizeX / screenWidth;

		map = std::vector<std::vector<std::vector<Pheromone*>>>(sizeY + 2, std::vector<std::vector<Pheromone*>>(sizeX + 2));
		Pheromone_Shape.setRadius(pheromone_radius);
	}

	void push(Pheromone *pheromone, uint16_t y, uint16_t x) {
		#if LIMIT_PHEROMONES_NUMBER
			if (map[y][x].size() < max_number_per_tile)
				map[y][x].push_back(pheromone);
		#else
			map[y][x].push_back(pheromone);
		#endif

	}

	void draw() {
		for (auto &row : map)
			for (auto &col : row)
				for (auto *pheromone : col)
					pheromone->draw();
	}

	void update() {
		for (auto &row : map)
			for (auto &col : row)
				for (int i = col.size() - 1; i >= 0; i--)
					if (col[i]->update_life_span() > pheromone_life_span)
						col.erase(col.begin() + i);
	}
};
