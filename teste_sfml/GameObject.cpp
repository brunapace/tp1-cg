#include "GameObject.h"

GameObject::GameObject()
{
	this->speed = NULL;
	this->name = "";
}

GameObject::GameObject(sf::Vector2f position, float speed, std::string texture_file, sf::Vector2f scale, std::string name, int life) {
	this->speed = speed;
	this->name = name;
	this->life = life;
	if (!this->texture.loadFromFile(texture_file)) {
		std::cout << "erro ao carregar textura de " << name << std::endl;
	}
	this->sprite = sf::Sprite();
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(position);
	this->sprite.scale(scale);
}

GameObject::GameObject(sf::Vector2f position, float speed, sf::Vector2f scale, std::string name, int life)
{
	this->speed = speed;
	this->name = name;
	this->life = life;
	this->sprite = sf::Sprite();
	this->sprite.setPosition(position);
	this->sprite.scale(scale);
}


void GameObject::print_attributes()
{
	std::cout << this->name << "\tposition: " << this->sprite.getPosition().x << ", " << this->sprite.getPosition().y << "\tspeed: " << this->speed << "\tlife: " << this->life << std::endl;
}

void GameObject::move(directions direction)
{
	float move_to = this->speed* sqrt(2);;
	switch (direction)
	{
	case directions::RIGHT:
		this->sprite.move(this->speed, 0.0);
		break;
	case directions::LEFT:
		this->sprite.move(-this->speed, 0.0);
		break;
	case directions::UP:
		this->sprite.move(0.0, -this->speed);
		break;
	case directions::DOWN:
		this->sprite.move(0.0, this->speed);
		break;
	case directions::RU_DIAG:
		this->sprite.move(move_to, -move_to);
		break;
	case directions::RD_DIAG:
		this->sprite.move(move_to, move_to);
		break;
	case directions::LU_DIAG:
		this->sprite.move(-move_to, -move_to);
		break;
	case directions::LD_DIAG:
		this->sprite.move(-move_to, move_to);
		break;
	default:
		break;
	}
}

sf::Vector2f GameObject::get_position()
{
	return this->sprite.getPosition();
}

bool GameObject::check_collision(GameObject &other_object)
{
	return this->sprite.getGlobalBounds().intersects(other_object.sprite.getGlobalBounds());
}

void GameObject::draw(sf::RenderWindow &window)
{
	window.draw(this->sprite);
}
