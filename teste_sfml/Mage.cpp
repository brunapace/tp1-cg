#include "Mage.h"

void Mage::shoot()
{
	std::string shot_name = this->shot_suffix + std::to_string(this->shots.size());
	GameObject shot = GameObject(this->sprite.getPosition(), this->shot_speed, this->shot_scale, shot_name, 1);
	shot.sprite.setTexture(this->shot_texture);
	shot.sprite.setOrigin(this->shot_origin);
	this->shots.push_back(shot);
}

Mage::Mage(sf::Vector2f position, float speed, std::string texture_file, sf::Vector2f scale, std::string name, sf::Vector2f origin, int life): GameObject(position, speed, texture_file, scale, name, life)
{
	this->sprite.setOrigin(origin);
	this->shot_speed = 0.0;
}

void Mage::print_attributes()
{
	std::cout << this->name << "\tposition: " << this->sprite.getPosition().x << ", " << this->sprite.getPosition().y << "\tspeed: " << this->speed << std::endl;
	for (auto it = this->shots.begin(); it != this->shots.end(); it++) {
		it->print_attributes();
	}

}

void Mage::set_default_shot(float shot_speed, std::string shot_texture_file, sf::Vector2f shot_scale, std::string shot_suffix, sf::Vector2f shot_origin)
{
	this->shot_speed = shot_speed;
	if (!this->shot_texture.loadFromFile(shot_texture_file)) {
		std::cout << "erro ao carregar textura de " << shot_suffix << std::endl;
	}
	this->shot_scale = shot_scale;
	this->shot_suffix = shot_suffix;
	this->shot_origin = shot_origin;
}

bool has_reached_end(const GameObject& shot) {
	return shot.sprite.getPosition().y <= 0;
}

bool has_collided(const GameObject& shot) {
	return shot.life <= 0;
}

void Mage::manage_shots(sf::RenderWindow& window)
{
	for (auto it = this->shots.begin(); it != this->shots.end(); it++) {
		it->move(directions::UP);
		it->draw(window);
	}
	this->shots.remove_if(has_reached_end);
	this->shots.remove_if(has_collided);
}
