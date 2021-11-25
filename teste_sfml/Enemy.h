#pragma once
#include <list>
#include "GameObject.h"
#include <iostream>
#include <vector>

class Enemy : public GameObject
{
	std::vector<directions> movement;
	size_t movement_index;
	sf::Clock clock;
public:
	Enemy(sf::Vector2f position, float speed, sf::Vector2f scale, std::string name, int life, std::vector<directions> movement);
	void automatic_move(float time);
};

