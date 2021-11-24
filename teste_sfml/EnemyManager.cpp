#include "EnemyManager.h"

std::vector<directions> EnemyManager::get_directions(enemyType enemy_type)
{
	std::vector<directions> movement = std::vector<directions>();
	switch (enemy_type){
	case enemyType::ENEMY_A:
		movement.insert(movement.end(), {
			directions::LD_DIAG,
			directions::LD_DIAG,
			directions::RD_DIAG,
			directions::RD_DIAG,
			});
		return movement;
	default:
		movement.push_back(directions::DOWN);
		return movement;
	}
	
}

void EnemyManager::print_attributes()
{
	for (auto it = this->enemies.begin(); it != this->enemies.end(); it++) {
		it->print_attributes();
	}
}

void EnemyManager::set_default_enemy(float enemy_speed, std::string enemy_texture_file, sf::Vector2f enemy_scale, std::string enemy_suffix, int life, enemyType enemy_type)
{
	this->enemy_speed = enemy_speed;
	if (!this->enemy_texture.loadFromFile(enemy_texture_file)) {
		std::cout << "erro ao carregar textura de " << enemy_suffix << std::endl;
	}
	this->enemy_scale = enemy_scale;
	this->enemy_suffix = enemy_suffix;
	this->enemy_life = life;
	this->enemy_movement = this->get_directions(enemy_type);
}

bool is_dead(const GameObject& enemy) {
	return enemy.life <= 0;
}

bool EnemyManager::manage_enemies(sf::RenderWindow& window, std::list<GameObject> &shots){

	for (auto it = this->enemies.begin(); it != this->enemies.end(); it++) {
		it->automatic_move();
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
	Enemy enemy = Enemy(enemy_position, this->enemy_speed, this->enemy_scale, enemy_name, this->enemy_life,this->enemy_movement);
	enemy.sprite.setTexture(this->enemy_texture);
	this->enemies.push_back(enemy);
}
