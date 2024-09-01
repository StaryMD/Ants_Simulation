#include <algorithm>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const uint16_t screenWidth = 1920;
const uint16_t screenHeight = 1080;
const uint16_t tileSize = 5;
const int mapY = screenHeight / tileSize;
const int mapX = screenWidth / tileSize;

void fill(uint8_t *map, int x1, int y1, int x2, int y2, uint8_t value) {
	for (int i = y1; i <= y2; i++)
		for (int j = x1; j <= x2; j++)
			*(map + i * mapX + j) = value;
}

int main() {
  FILE *fout = fopen("maps/map1.dat", "wb");
  uint8_t *map = (uint8_t *)calloc(mapX * mapY, 1);
  if (!map)
    return 0;

  fill(map, 10, 10, 100, 100, 1);
  fill(map, 500, 100, 800, 300, 1);
  fill(map, 1100, 700, 1600, 900, 1);

  fwrite(&tileSize, 2, 1, fout);
  fwrite(map, 1, mapX * mapY, fout);

  uint8_t Max = 0;
  for (int i = 0; i < mapX * mapY; i++)
    Max = std::max(Max, *(map + i));
  return 0;
}
