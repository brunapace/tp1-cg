#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "GameObject.h"
#include "Mage.h"
#include "EnemyManager.h"

enum class gamestates {INIT,  STAGE_1, STAGE_2, STAGE_3, STAGE_4, VICTORY, GAMEOVER, END_OF_LIST};

gamestates& operator++( gamestates &c ) {
  using IntType = typename std::underlying_type<gamestates>::type ;
  c = static_cast<gamestates>( static_cast<IntType>(c) + 1 );
  if ( c == gamestates::END_OF_LIST )
    c = static_cast<gamestates>(0);
  return c;
}

gamestates operator++( gamestates &c, int ) {
  gamestates result = c;
  ++c;
  return result;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(566, 830), "Teste SFML");
    bool pause = false;
    bool debug = false;
    bool debug_single_loop = false;
    bool shot = false;
    float pos_x[3];
    float mov_time[4] = {1, 2, 2, 2};
    int life[4] = {2, 3, 4, 5};
    int num_enemy[3] = {1, 1, 5};
    gamestates gamestate = gamestates::INIT;

    sf::Texture bg_texture;
    sf::Clock clock_spawn;

    int count = 0;    
    
    Mage mage = Mage(sf::Vector2f(215.f, 652.f), 0.15, "Images/Black mage.png", sf::Vector2f(2.f, 2.f), "mage", sf::Vector2f(11.f, 11.f), 3);
    EnemyManager enemies_a;
    EnemyManager enemies_b;
    EnemyManager enemies_c;
    EnemyManager boss;
    sf::Sprite bg_sprite;
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
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    open = false;
                }
                else if (event.key.code == sf::Keyboard::R) {
                    gamestate = gamestates::INIT;
                }
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
                    enemies_a.print_attributes();
                    enemies_b.print_attributes();
                    enemies_c.print_attributes();
                }
                else if (event.mouseButton.button == sf::Mouse::Left) {
                    mage.shoot();
                }
                break;
            }
            
        }
        switch(gamestate){
                case gamestates::INIT:
                    if (!bg_texture.loadFromFile("Images/Background (pd).png")) {
                        std::cout << "erro ao carregar textura Background" << std::endl;
                    }
                    bg_sprite.setTexture(bg_texture);
                    pos_x[0] = 390;
                    pos_x[1] = 170;
                    pos_x[2] = 390;
                    enemies_a = EnemyManager();
                    enemies_b = EnemyManager();
                    enemies_c = EnemyManager();
                    boss = EnemyManager();
                    mage.set_default_shot(0.1, "Images/projetil.png", sf::Vector2f(2.f, 2.f), "shot_", sf::Vector2f(1.5f, 30.5f));
                    enemies_a.set_default_enemy(0.08, "Images/inimigo a.png", sf::Vector2f(2.f, 2.f), "enemy_a_", life[0], enemyType::ENEMY_A,num_enemy[0]);
                    enemies_b.set_default_enemy(0.08, "Images/inimigo b.png", sf::Vector2f(2.f, 2.f), "enemy_b_", life[1], enemyType::ENEMY_B,num_enemy[1]);
                    enemies_c.set_default_enemy(0.08, "Images/inimigo c.png", sf::Vector2f(2.f, 2.f), "enemy_c_", life[2], enemyType::ENEMY_C,num_enemy[2]);
                    boss.set_default_enemy(0.08, "Images/boss 1.png", sf::Vector2f(2.f, 2.f), "boss", life[3], enemyType::BOSS, 1);
                    gamestate++;
                    break;
                case gamestates::STAGE_1:
                    window.clear();
                    if(clock_spawn.getElapsedTime().asSeconds() >= 1){
                        if(enemies_a.spawn_enemy(sf::Vector2f(pos_x[0], 170.f))){
                            gamestate++;
                        }
                        if(pos_x[0] > 60){
                            pos_x[0]-=50;
                        }
                        else{
                            pos_x[0]+=50;
                        }                        
                        clock_spawn.restart();
                    }
                    window.draw(bg_sprite);
                    if(enemies_a.manage_enemies(window, mage.shots, mov_time[0])){
                        gamestate = gamestates::GAMEOVER;
                    };
                    mage.draw(window);
                    mage.manage_shots(window);
                break;
                case gamestates::STAGE_2:
                    window.clear();
                    if(clock_spawn.getElapsedTime().asSeconds() >= 1){
                        if(enemies_b.spawn_enemy(sf::Vector2f(pos_x[1], 170.f))){
                            gamestate++;
                        }
                        clock_spawn.restart();
                    }
                    window.draw(bg_sprite);
                    if(enemies_b.manage_enemies(window, mage.shots, mov_time[1])){
                        gamestate = gamestates::GAMEOVER;
                    };
                    mage.draw(window);
                    mage.manage_shots(window);
                break;
                case gamestates::STAGE_3:
                    window.clear();
                    if(clock_spawn.getElapsedTime().asSeconds() >= 1){
                        if(enemies_c.spawn_enemy(sf::Vector2f(pos_x[2], 170.f))){
                            gamestate++;
                        }
                        clock_spawn.restart();
                    }
                    window.draw(bg_sprite);
                    if(enemies_c.manage_enemies(window, mage.shots, mov_time[2])){
                        gamestate = gamestates::GAMEOVER;
                    };
                    mage.draw(window);
                    mage.manage_shots(window);
                break;
                case gamestates::STAGE_4:
                    window.clear();
                    if(clock_spawn.getElapsedTime().asSeconds() >= 1){
                        if(boss.spawn_enemy(sf::Vector2f(170.f, 100.f))){
                            gamestate++;
                        }
                        clock_spawn.restart();
                    }
                    window.draw(bg_sprite);
                    if(boss.manage_enemies(window, mage.shots, mov_time[3])){
                        gamestate = gamestates::GAMEOVER;
                    };
                    mage.draw(window);
                    mage.manage_shots(window);
                break;
                case gamestates::GAMEOVER:
                    window.clear();
                    if (!bg_texture.loadFromFile("Images/Background Lose.png")) {
                        std::cout << "erro ao carregar textura Background Tela Final" << std::endl;
                    }
                    bg_sprite.setTexture(bg_texture);
                    window.draw(bg_sprite);
                break;
                case gamestates::VICTORY:
                    window.clear();
                    /* tentativa de fazer trocar a tela pra telinha de vitória
                    bg_texture.loadFromFile("Images/Background Win.png");
                    bg_sprite.setTexture(bg_texture);
                    window.draw(bg_sprite);*/                    
                break;
                default:
                break;
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
        
        //window.clear();
        /*window.draw(bg_sprite);
        enemies_a.manage_enemies(window, mage.shots);
        mage.draw(window);
        boss.manage_enemies(window, mage.shots);
        mage.manage_shots(window);*/
        window.display();
    }

    return 0;
}

