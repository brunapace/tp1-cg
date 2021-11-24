#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position, float speed, sf::Vector2f scale, std::string name, int life, std::vector<directions> movement) : GameObject(position, speed, scale, name, life)
{
	this->movement = movement;
	this->movement_index = 0;
}

void Enemy::automatic_move()
{
	this->move(this->movement.at(this->movement_index));
	if (this->movement_index < this->movement.size()-1) {
		this->movement_index++;
	}
	else {
		this->movement_index = 0;
	}
}
