#pragma once
#include "Enemy.h"
#include <list>
#include <vector>

enum class enemyType
{
	ENEMY_A, BOSS
};
class EnemyManager
{
	float enemy_speed;
	sf::Texture enemy_texture;
	sf::Vector2f enemy_scale;
	std::string enemy_suffix;
	sf::Vector2f enemy_origin;
	std::vector<directions> enemy_movement;
	int enemy_life;
	std::list<Enemy> enemies;

	std::vector<directions> get_directions(enemyType enemy_type);
public:
	void print_attributes();
	void set_default_enemy(float enemy_speed, std::string enemy_texture_file, sf::Vector2f enemy_scale, std::string enemy_suffix, int enemy_life, enemyType enemy_type);
	bool manage_enemies(sf::RenderWindow& window, std::list<GameObject> &shots);
	void spawn_enemy(sf::Vector2f enemy_position);
};

