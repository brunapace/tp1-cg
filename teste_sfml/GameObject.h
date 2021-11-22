#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include<math.h>
enum class directions
{
	RIGHT, LEFT, UP, DOWN, RU_DIAG, RD_DIAG, LU_DIAG, LD_DIAG
};
class GameObject
{
protected:
	float speed;
	std::string name;
	sf::Texture texture;
public:	
	sf::Sprite sprite;
	GameObject();
	GameObject(sf::Vector2f position, float speed, std::string texture_file, sf::Vector2f scale, std::string name);
	GameObject(sf::Vector2f position, float speed, sf::Vector2f scale, std::string name);
	void print_attributes();
	void move(directions direction);
	sf::Vector2f get_position();
	void check_collision(GameObject other_object);
	void draw(sf::RenderWindow &window);
};

