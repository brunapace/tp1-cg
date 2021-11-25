#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include<math.h>
enum class directions
{
	RIGHT, LEFT, UP, DOWN, RU_DIAG, RD_DIAG, LU_DIAG, LD_DIAG, RIGHT_BOSS, LEFT_BOSS, DOWN_BOSS
};
class GameObject
{
protected:
	float speed;
	std::string name;
	sf::Texture texture;
public:
	bool operator == (const GameObject& go) const { return name == go.name; }
	bool operator != (const GameObject& go) const { return !operator==(go); }
	sf::Sprite sprite;
	int life;
	GameObject();
	GameObject(sf::Vector2f position, float speed, std::string texture_file, sf::Vector2f scale, std::string name, int life);
	GameObject(sf::Vector2f position, float speed, sf::Vector2f scale, std::string name, int life);
	void print_attributes();
	void move(directions direction);
	sf::Vector2f get_position();
	bool check_collision(GameObject &other_object);
	void draw(sf::RenderWindow &window);
};

