#pragma once
#include <list>
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	std::string enemy_suffix;
	std::list<GameObject> enemies;
	Enemy(sf::Vector2f position, float speed, std::string texture_file, sf::Vector2f scale, std::string name, sf::Vector2f origin);
	void spawn_enemy(sf::RenderWindow& window);
};

