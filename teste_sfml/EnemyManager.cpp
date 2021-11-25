#include "EnemyManager.h"

std::vector<directions> EnemyManager::get_directions(enemyType enemy_type)
{
	std::vector<directions> movement = std::vector<directions>();
	switch (enemy_type){
	case enemyType::ENEMY_A:
		movement.insert(movement.end(), {
			directions::LD_DIAG,
			directions::RD_DIAG,
		});
		return movement;
	case enemyType::ENEMY_B:
		movement.insert(movement.end(), {
			directions::RIGHT,
			directions::LD_DIAG,
			directions::RIGHT,
			directions::DOWN,
			directions::LEFT,			
			directions::RD_DIAG,
			directions::LEFT,
			directions::DOWN,
		});
		return movement;
	case enemyType::ENEMY_C:
		movement.insert(movement.end(), {
			directions::LEFT,
			directions::DOWN,
			directions::RIGHT,
			directions::DOWN,
		});
		return movement;
	default:
		movement.insert(movement.end(), {
			directions::LEFT,
			directions::RIGHT,
			directions::DOWN,
		});
		return movement;
	}
	
}

void EnemyManager::print_attributes()
{
	for (auto it = this->enemies.begin(); it != this->enemies.end(); it++) {
		it->print_attributes();
	}
}

void EnemyManager::set_default_enemy(float enemy_speed, std::string enemy_texture_file, sf::Vector2f enemy_scale, std::string enemy_suffix, int life, enemyType enemy_type, int max_enemy)
{
	this->enemy_speed = enemy_speed;
	if (!this->enemy_texture.loadFromFile(enemy_texture_file)) {
		std::cout << "erro ao carregar textura de " << enemy_suffix << std::endl;
	}
	this->enemy_scale = enemy_scale;
	this->enemy_suffix = enemy_suffix;
	this->enemy_life = life;
	this->enemy_movement = this->get_directions(enemy_type);
	this->max_enemy = max_enemy;
	this->enemy_count = 0;
}

bool is_dead(const GameObject& enemy) {
	return enemy.life <= 0;
}

bool EnemyManager::manage_enemies(sf::RenderWindow& window, std::list<GameObject> &shots, float time){

	for (auto it = this->enemies.begin(); it != this->enemies.end(); it++) {
		it->automatic_move(time);
		it->draw(window);
		if (it->get_position().y >= 652) {
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

bool EnemyManager::spawn_enemy(sf::Vector2f enemy_position)
{
	if(this->max_enemy > this->enemy_count){
		std::string enemy_name = this->enemy_suffix + std::to_string(this->enemies.size());
		Enemy enemy = Enemy(enemy_position, this->enemy_speed, this->enemy_scale, enemy_name, this->enemy_life,this->enemy_movement);
		enemy.sprite.setTexture(this->enemy_texture);
		this->enemies.push_back(enemy);
		this->enemy_count ++;
		return false;
	}
	else if(this->max_enemy == this->enemy_count && this->enemies.size()<1){
		return true;

	}
	return false;
}
	
