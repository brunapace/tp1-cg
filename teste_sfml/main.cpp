#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "GameObject.h"
#include "Mage.h"
#include "EnemyManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(566, 830), "Teste SFML");
    bool pause = false;
    bool debug = false;
    bool debug_single_loop = false;
    bool shot = false;

    sf::Texture bg_texture;
    sf::Clock clock;
    sf::Time timer;
    int count = 0;
      
    if (!bg_texture.loadFromFile("Images/Background (pd).png")) {
        std::cout << "erro ao carregar textura Background" << std::endl;
    }
    
    Mage mage = Mage(sf::Vector2f(215.f, 652.f), 0.1, "Images/Black mage.png", sf::Vector2f(2.f, 2.f), "mage", sf::Vector2f(11.f, 11.f), 3);
    mage.set_default_shot(0.1, "Images/projetil.png", sf::Vector2f(2.f, 2.f), "shot_", sf::Vector2f(6.5f, 13.5f));
    GameObject boss = GameObject(sf::Vector2f(215.f, 50.f), 0, "Images/boss 1.png",sf::Vector2f(2.f, 2.f), "boss", 3);
    EnemyManager enemies_a = EnemyManager();
    enemies_a.set_default_enemy(0.05, "Images/inimigo a.png", sf::Vector2f(2.f, 2.f), "enemy_a_", 2);
    sf::Sprite bg_sprite;

    bg_sprite.setTexture(bg_texture);
    bg_sprite.setPosition(sf::Vector2f(0, 0));
    bg_sprite.scale(sf::Vector2f(2.f, 2.f));
    
    bool open = true;
    while (open)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                open = false;
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Right) {
                    if (debug) {
                        debug = false;
                        debug_single_loop = false;
                        pause = false;
                    }
                    else {
                        pause = !pause;
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Middle) {
                    debug = true;
                    debug_single_loop = true;
                    mage.print_attributes();
                    boss.print_attributes();
                }
                else if (event.mouseButton.button == sf::Mouse::Left) {
                    mage.shoot();
                    enemies_a.spawn_enemy(sf::Vector2f(215.f, 100.f));
                }
                break;
            }
        }
        
        if (pause) {
            continue;
        }
        if (debug && !debug_single_loop) {
            continue;
        }
        else {
            debug_single_loop = false;
        }
            
        if (sf::Mouse::getPosition(window).x > 283 && mage.sprite.getPosition().x <= 510) {
            if (mage.sprite.getPosition().x < sf::Mouse::getPosition(window).x) {
                mage.move(directions::RIGHT);
            }
        }
        else if (sf::Mouse::getPosition(window).x < 283 && mage.sprite.getPosition().x >= 56) {
            if (mage.sprite.getPosition().x > sf::Mouse::getPosition(window).x) {
                mage.move(directions::LEFT);
            }
        }

        window.clear();
        window.draw(bg_sprite);
        enemies_a.manage_enemies(window, mage.shots);
        mage.draw(window);
        boss.draw(window);
        mage.manage_shots(window);
        window.display();
    }

    return 0;
}

