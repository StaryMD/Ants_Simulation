#pragma once

#define EMPY_SPACE_TYPE (uint8_t)0
#define FOOD_TYPE (uint8_t)1
#define WALL_TYPE (uint8_t)2
#define ANT_NEST_TYPE (uint8_t)3

struct World_Map {
	struct Map_Cell {
		uint8_t type;
		uint16_t value;
	};

	sf::CircleShape cell_square;
	std::vector<std::vector<Map_Cell>> map;
	uint16_t sizeX, sizeY;
	uint16_t tileSize;

	World_Map(Pheromone_Map &pheromone_map) {
		pheromone_map.max_number_per_tile = tileSize * tileSize;
		sizeX = 0;
		sizeY = 0;
		tileSize = 0;
		cell_square.setPointCount(4);
		cell_square.setOutlineThickness(0);
	}

	void load_map_from_file(const char *fileName, std::vector<Ant_Nest> &ant_nests) {
		FILE* input_file = NULL;
		fopen_s(&input_file, fileName, "rb");

		if (!input_file) {
			perror("Map loading");
			system("pause");
			exit(1);
		}

		fread(&tileSize, 2, 1, input_file);
		cell_square.setRadius(tileSize);
		cell_square.setRotation(45.0f);
		sizeX = (uint16_t)screenWidth / tileSize;
		sizeY = (uint16_t)screenHeight / tileSize;
		map = std::vector<std::vector<Map_Cell>>(sizeY, std::vector<Map_Cell>(sizeX));

		for (uint16_t y = 0; y < sizeY; y++)
			for (uint16_t x = 0; x < sizeX; x++) {
				fread(&map[y][x].type, 1, 1, input_file);

				if (map[y][x].type == ANT_NEST_TYPE)
					ant_nests.push_back(Ant_Nest(sf::Vector2f((float)x * tileSize, (float)y * tileSize)));
			}

		std::cout << "Loaded map: " << map[0].size() << " x " << map.size() << '\n';
		std::cout << "Located " << ant_nests.size() << " ant nests\n";
	}

	void draw() {
		static sf::Color colors[] = {
			sf::Color::Transparent,
			sf::Color::Yellow,
			sf::Color(100, 100, 100),
			sf::Color::Green
		};

		for (uint16_t y = 0; y < sizeY; y++)
			for (uint16_t x = 0; x < sizeX; x++) 
				if (map[y][x].type) {
					cell_square.setPosition((float)(x * tileSize), (float)(y * tileSize));
					cell_square.setFillColor(colors[map[y][x].type]);
					window.draw(cell_square);
				}
	}

};
