#pragma once
#include "GameObject.h"
#include <list>

class EnemyManager
{
	float enemy_speed;
	sf::Texture enemy_texture;
	sf::Vector2f enemy_scale;
	std::string enemy_suffix;
	sf::Vector2f enemy_origin;
	int enemy_life;
	std::list<GameObject> enemies;
public:
	void print_attributes();
	void set_default_enemy(float enemy_speed, std::string enemy_texture_file, sf::Vector2f enemy_scale, std::string enemy_suffix, int enemy_life);
	bool manage_enemies(sf::RenderWindow& window, std::list<GameObject> &shots);
	void spawn_enemy(sf::Vector2f enemy_position);
};

