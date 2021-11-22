#include "Enemy.h"

void Enemy::spawn_enemy(sf::RenderWindow& window)
{
}

Enemy::Enemy(sf::Vector2f position, float speed, std::string texture_file, sf::Vector2f scale, std::string name, sf::Vector2f origin) : GameObject(position, speed, texture_file, scale, name) {
	this->sprite.setOrigin(origin);
}