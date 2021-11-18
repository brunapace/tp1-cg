#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(566, 830), "Teste SFML");
    bool pause = false;
    bool shot = false;
    sf::Texture boss_texture;
    sf::Texture bg_texture;
    sf::Texture mage_texture;
    sf::Texture shot_texture;
    sf::Texture enemy_texture;
      
    if (!boss_texture.loadFromFile("Images/boss 1.png")) {
        //std::cout << "erro ao carregar imagem" << std::endl;
    }
    if (!bg_texture.loadFromFile("Images/Background (pd).png")) {
        //std::cout << "erro ao carregar imagem" << std::endl;
    }
    if (!mage_texture.loadFromFile("Images/Black mage.png")) {
        //std::cout << "erro ao carregar imagem" << std::endl;
    }
    if (!shot_texture.loadFromFile("Images/projetil.png")) {
        //std::cout << "erro ao carregar imagem" << std::endl;
    }
    if (!enemy_texture.loadFromFile("Images/inimigo a.png")) {
        //std::cout << "erro ao carregar imagem" << std::endl;
    }

    sf::Sprite boss_sprite;
    sf::Sprite bg_sprite;
    sf::Sprite mage_sprite;
    sf::Sprite shot_sprite;

    boss_sprite.setPosition(sf::Vector2f(215.f, 50.f));
    boss_sprite.setTexture(boss_texture);
    boss_sprite.scale(sf::Vector2f(2.f, 2.f));

    bg_sprite.setTexture(bg_texture);
    bg_sprite.setPosition(sf::Vector2f(0, 0));
    bg_sprite.scale(sf::Vector2f(2.f, 2.f));

    mage_sprite.setTexture(mage_texture);
    mage_sprite.setPosition(sf::Vector2f(215.f, 652.f));
    mage_sprite.scale(sf::Vector2f(2.f, 2.f));
    mage_sprite.setOrigin(sf::Vector2f(32.f, 32.f));

    shot_sprite.setTexture(shot_texture);
    shot_sprite.setPosition(mage_sprite.getPosition());
    shot_sprite.scale(sf::Vector2f(2.f, 2.f));
    shot_sprite.setOrigin(sf::Vector2f(32.f, 32.f));

    /*enemy.setFillColor(sf::Color(100, 250, 50));
    enemy.setPosition(sf::Vector2f(215.f, 50.f));*/
    
    bool open = true;

    while (open)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                open = false;
        }

        if (pause) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                pause = false;
            }
        }
        
        if (!pause) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                pause = true;
            }
            
            if (sf::Mouse::getPosition(window).x > 283 && mage_sprite.getPosition().x <= 510) {
                if (mage_sprite.getPosition().x < sf::Mouse::getPosition(window).x) {
                    mage_sprite.move(0.1, 0);
                }
            }
            else if (sf::Mouse::getPosition(window).x < 283 && mage_sprite.getPosition().x >= 56) {
                if (mage_sprite.getPosition().x > sf::Mouse::getPosition(window).x) {
                    mage_sprite.move(-0.1, 0);
                }
            }

            window.clear();

            window.draw(bg_sprite);
            window.draw(mage_sprite);
            window.draw(boss_sprite);
            //window.draw(enemy);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                window.draw(shot_sprite);
                shot = true;
            }
            if (shot) {
                shot_sprite.move(0, -0.1);
                window.draw(shot_sprite);
                if (shot_sprite.getPosition().y <= 0) {
                    shot = false;
                    shot_sprite.setPosition(mage_sprite.getPosition());
                }
            }
        }

        window.display();
    }

    return 0;
}

