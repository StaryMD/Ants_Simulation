#pragma once

struct Behavior_Sleep : Behavior {
	Ant* parent;

	Behavior_Sleep(Ant* _parent) : parent(_parent) {
	}

	void update(Pheromone_Map& pheromone_map) {
	}

};
