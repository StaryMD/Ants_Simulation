#pragma once

#define SEARCHING_FOR_FOOD 0
#define RETURNING_HOME 1
float ant_turn_coeff = 1.0f;
uint16_t current_number_of_ants = 0;

struct Ant {
	sf::Vector2f pos;
	float angle;
	uint8_t offset, timer;
	Behavior *behavior;

	Ant() {
		pos = { 0.0f, 0.0f };
		angle = 0.0f;
		offset = 0;
		timer = 0;
		behavior = new Behavior;
	}

	Ant(sf::Vector2f &_pos, float _angle) : pos(_pos), angle(_angle) {
		offset = randomi(0, 255);
		timer = 0xFF;
		behavior = new Behavior;
	}

	void draw(Pheromone_Map& pheromone_map) {
		#if DEBUG_MODE
			int16_t startcellX = (int16_t)(pos.x * pheromone_map.ratioX);
			int16_t startcellY = (int16_t)(pos.y * pheromone_map.ratioY);

			startcellX = std::min(startcellX, (int16_t)(pheromone_map.sizeX - 1));
			startcellY = std::min(startcellY, (int16_t)(pheromone_map.sizeY - 1));
			startcellX = std::max(startcellX, (int16_t)0);
			startcellY = std::max(startcellY, (int16_t)0);

			const int16_t endcellX = startcellX + 2;
			const int16_t endcellY = startcellY + 2;

			sf::ConvexShape shape;
			shape.setPointCount(4);
			shape.setOutlineColor(sf::Color::White);
			shape.setFillColor(sf::Color::Transparent);
			shape.setOutlineThickness(1);
			shape.setPosition(0, 0);
			sf::Vector2f vertices[] = {
				{ (startcellX - 1) * 2 * ant_sensing_distance, (startcellY - 1) * 2 * ant_sensing_distance },
				{ (startcellX - 1) * 2 * ant_sensing_distance, endcellY * 2 * ant_sensing_distance },
				{ endcellX * 2 * ant_sensing_distance, endcellY * 2 * ant_sensing_distance },
				{ endcellX * 2 * ant_sensing_distance, (startcellY - 1) * 2 * ant_sensing_distance },
			};
			for (int i = 0; i < 4; i++)
				shape.setPoint(i, vertices[i]);

			window.draw(shape);

			sf::CircleShape circle;
			circle.setRadius(ant_sensing_distance);
			circle.setPosition(pos - sf::Vector2f(ant_sensing_distance, ant_sensing_distance));
			circle.setFillColor(sf::Color::Transparent);
			circle.setOutlineColor(sf::Color::Yellow);
			circle.setOutlineThickness(1);
			window.draw(circle);
		#endif

		sf::Vector2f tail = pos + sf::Vector2f(cos(angle - TWO_PI) * antSize, sin(angle - TWO_PI) * antSize);
		sf::Vertex line[] = { pos, tail };
		window.draw(line, 2, sf::Lines);
	}
	
	void update(Pheromone_Map &pheromone_map) {
		behavior->update(pheromone_map);
	}
	
	void change_Behavior(Behavior *new_behavior) {
		delete behavior;
		behavior = new_behavior;
	}

	bool is_near_pheromone(Pheromone *pheromone) {
		static const float ant_sensing_distance_squared = ant_sensing_distance * ant_sensing_distance;
		return magnitude_squared(pos - pheromone->getPos()) < ant_sensing_distance_squared;
	}

	bool is_out_of_bounds() {
		return pos.x < 0 || pos.x > screenWidth || pos.y < 0 || pos.y > screenHeight;
	}

	bool can_emanate_pheromone() {
		return !((frameCount + offset) & timer);
	}
};
