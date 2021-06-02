#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int screenWidth = 1920;
int screenHeight = 1080;
uint16_t tileSize = 5;
uint16_t mapY;
uint16_t mapX;

void fill(uint8_t *map, int x1, int y1, int x2, int y2, uint8_t value) {
	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			*(map + i * mapX + j) = value;
}

int main() {
	srand((unsigned)time(0));
	mapY = screenHeight / tileSize;
	mapX = screenWidth / tileSize;

	FILE* fout = fopen("maps\\map1.dat", "wb");
	if (!fout) return 0;
	uint8_t *map = (uint8_t *) calloc(mapX * mapY, 1);
	if (!map) return 0;

	fill(map, 10, 10, 100, 100, 1);
	fill(map, 125, 130, 150, 200, 2);
	fill(map, 210, 50, 211, 51, 3);

	fwrite(&tileSize, 2, 1, fout);
	fwrite(map, 1, mapX * mapY, fout);

	uint32_t Count = 0;
	for (int i = 0; i < mapX * mapY; i++)
		Count += *(map + i) == 1;

	uint16_t temp;
	while (Count--)
		temp = rand() % 300 + 10,
		fwrite(&temp, 2, 1, fout);
	
	free(map);
	fclose(fout);
	return 0;
}
