#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdio>
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>

sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Ants simulation", sf::Style::Fullscreen);
unsigned frameCount;

#include "RNG.h"
#include "constants.h"
#include "myUtils.h"
#include "Pheromone.h"
#include "Behavior.h"
#include "Ant.h"
#include "Behavior_Wandering.h"
#include "Behavior_Returning.h"
#include "Behavior_Sleep.h"
#include "Ant_Nest.h"
#include "World_Map.h"

int main() {
	std::ios_base::sync_with_stdio(0);
	rng = RNG((uint32_t)time(NULL));

	std::vector<Ant> ants(number_of_ants);

	std::vector<Ant_Nest> ant_nests;
	Pheromone_Map pheromone_map;
	World_Map world_map(pheromone_map);
	world_map.load_map_from_file("maps\\map1.dat", ant_nests);

	{
		uint16_t remaining_ants = number_of_ants % (uint16_t)ant_nests.size();

		for (Ant_Nest &ant_nest : ant_nests) {
			ant_nest.antsInside = number_of_ants / (uint16_t)ant_nests.size() + (remaining_ants > 0);
			ant_nest.ID = ant_nest_count++;
			remaining_ants--;

			while (ant_nest.spawn_ant(ants));
		}
	}

	bool first_loop = true;
	sf::Event event;
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	while (window.isOpen()) {
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> interval = now - start;

		if (interval.count() >= invFPS_times_1000) {
			first_loop = false;
			start = now;
			frameCount++;

			while (window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				}
			}
			window.clear();

			#if SHOW_WORLD_MAP
				world_map.draw();
			#endif
			
			#if SHOW_PHEROMONES
				pheromone_map.draw();
			#endif
			
			//for (Ant_Nest& ant_nest : ant_nests) ant_nest.draw();

			for (Ant &ant : ants)
				ant.draw(pheromone_map);

			window.display();

			for (Ant_Nest &ant_nest : ant_nests)
				ant_nest.spawn_ant(ants);

			for (Ant &ant : ants) ant.update(pheromone_map);

			pheromone_map.update();


			if (frameCount > 1000 && frameCount < 5000 && !(frameCount % 100)) {
				int nr = randomi(0, number_of_ants - 1);

				ants[nr].change_Behavior(new Behavior_Returning(&ants[nr]));
			}
		}
	}
	
	return 0;
}
