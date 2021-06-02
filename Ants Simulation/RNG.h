#pragma once

struct RNG {
	uint32_t nProcGen;

	RNG(uint32_t seed = 0) : nProcGen(seed) {
	}

	uint32_t rnd() {
		nProcGen += 0xe120fc15;
		uint64_t tmp = (uint64_t)nProcGen * 0x4a39b70d;
		uint32_t m1 = (uint32_t)((tmp >> 32) ^ tmp);
		tmp = (uint64_t)m1 * 0x12fad5c9;
		uint32_t m2 = (uint32_t)((tmp >> 32) ^ tmp);
		return m2;
	}

	float rndFloat(float min, float max) {
		static const float number = 1.0f / (float)(0x7FFFFFFF);
		return ((float)rnd() * number ) * (max - min) + min;
	}

	int rndInt(int min, int max) {
		return (rnd() % (max - min)) + min;
	}

} rng;
