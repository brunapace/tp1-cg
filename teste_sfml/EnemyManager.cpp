#include "EnemyManager.h"

void EnemyManager::print_attributes()
{
	for (auto it = this->enemies.begin(); it != this->enemies.end(); it++) {
		it->print_attributes();
	}
}

void EnemyManager::set_default_enemy(float enemy_speed, std::string enemy_texture_file, sf::Vector2f enemy_scale, std::string enemy_suffix, int life)
{
	this->enemy_speed = enemy_speed;
	if (!this->enemy_texture.loadFromFile(enemy_texture_file)) {
		std::cout << "erro ao carregar textura de " << enemy_suffix << std::endl;
	}
	this->enemy_scale = enemy_scale;
	this->enemy_suffix = enemy_suffix;
	this->enemy_life = life;
}

bool is_dead(const GameObject& enemy) {
	return enemy.life <= 0;
}

bool EnemyManager::manage_enemies(sf::RenderWindow& window, std::list<GameObject> &shots)
{
	for (auto it = this->enemies.begin(); it != this->enemies.end(); it++) {
		it->move(directions::DOWN);
		it->draw(window);
		if (it->get_position().y >= 830) {
			return true;
		}
		for (auto st = shots.begin(); st != shots.end(); st++) {
			if (it->check_collision(*st)) {
				it->life--;
				st->life--;
			}
		}
	}
	this->enemies.remove_if(is_dead);
	return false;
}

void EnemyManager::spawn_enemy(sf::Vector2f enemy_position)
{
	std::string enemy_name = this->enemy_suffix + std::to_string(this->enemies.size());
	GameObject enemy = GameObject(enemy_position, this->enemy_speed, this->enemy_scale, enemy_name, 1);
	enemy.sprite.setTexture(this->enemy_texture);
	this->enemies.push_back(enemy);
}
