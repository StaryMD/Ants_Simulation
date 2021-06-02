#pragma once

uint8_t ant_nest_count = 0;

struct Ant_Nest {
	sf::Vector2f pos;
	uint16_t antsInside;
	uint8_t ID;

	Ant_Nest() {
		pos = { screenWidth / 2, screenHeight / 2 };
		antsInside = 0;
		ID = 0;
	}

	Ant_Nest(sf::Vector2f _pos) : pos(_pos) {
		ID = 0;
		antsInside = 0;
	}

	void draw() {
		sf::CircleShape shape;
		shape.setRadius(nest_radius);
		shape.setPosition(pos);
		shape.setFillColor(sf::Color::Green);
		window.draw(shape);
	}

	bool spawn_ant(std::vector<Ant> &ants) {
		if (antsInside) {
			float randomAngle = randomf(0, TWO_PI);
			ants[current_number_of_ants] = Ant(pos, randomAngle);
			ants[current_number_of_ants].change_Behavior(new Behavior_Wandering(&ants[current_number_of_ants]));
			current_number_of_ants++;
			antsInside--;
			return true;
		}
		return false;
	}

	bool is_near(Ant& ant) {
		return sqr(pos.x - ant.pos.x) + sqr(pos.y - ant.pos.y) <= ant_sensing_distance * ant_sensing_distance;
	}

};