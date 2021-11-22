#pragma once
#include "GameObject.h"
#include <list>

class Mage :
    public GameObject
{
    float shot_speed;
    sf::Texture shot_texture;
    sf::Vector2f shot_scale;
    std::string shot_suffix;
    sf::Vector2f shot_origin;
public:
    void shoot();
    std::list<GameObject> shots;
    Mage(sf::Vector2f position, float speed, std::string texture_file, sf::Vector2f scale, std::string name, sf::Vector2f origin);
    void print_attributes();
    void set_default_shot(float shot_speed, std::string shot_texture_file, sf::Vector2f shot_scale, std::string shot_suffix, sf::Vector2f shot_origin);
    void manage_shots(sf::RenderWindow& window);

};

