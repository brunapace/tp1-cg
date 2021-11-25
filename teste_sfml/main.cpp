#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "GameObject.h"
#include "Mage.h"
#include "EnemyManager.h"

enum class gamestates {PRE_INIT, INIT,  STAGE_1, STAGE_2, STAGE_3, STAGE_4, VICTORY, GAMEOVER, END_OF_LIST};

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
    float pos_x[3] = {380, 170, 390};

    float mov_time[4] = {1, 0.8, 2, 2};
    int life[4] = {2, 3, 4, 7};
    int num_enemy[3] = {20, 15, 10};
    gamestates gamestate = gamestates::PRE_INIT;

    sf::Texture bg_texture;
    if (!bg_texture.loadFromFile("Images/Background (pd).png")) {
        std::cout << "erro ao carregar textura Background" << std::endl;
    }
    sf::Texture game_over;
    if (!game_over.loadFromFile("Images/GameOver.png")) {
        std::cout << "erro ao carregar textura Game Over" << std::endl;
    }
    sf::Texture victory;
    if (!victory.loadFromFile("Images/TelaVitoria.png")) {
        std::cout << "erro ao carregar textura Vitoria" << std::endl;
    }
    sf::Texture pre_init;
    if (!pre_init.loadFromFile("Images/TelaInicial.png")) {
        std::cout << "erro ao carregar textura Tela Inicial" << std::endl;
    }

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
                else if (event.key.code == sf::Keyboard::Enter) {
                    if(gamestate == gamestates::PRE_INIT){
                        gamestate = gamestates::INIT;
                    }
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
         if (pause) {
            continue;
        }
        if (debug && !debug_single_loop) {
            continue;
        }
        else {
            debug_single_loop = false;
        }
        switch(gamestate){
                case gamestates::PRE_INIT:
                    bg_sprite.setTexture(pre_init);
                    window.draw(bg_sprite);
                break;
                case gamestates::INIT:
                    bg_sprite.setTexture(bg_texture);
                    enemies_a = EnemyManager();
                    enemies_b = EnemyManager();
                    enemies_c = EnemyManager();
                    boss = EnemyManager();
                    mage.set_default_shot(0.1, "Images/projetil.png", sf::Vector2f(2.f, 2.f), "shot_", sf::Vector2f(1.5f, 30.5f));
                    enemies_a.set_default_enemy(0.08, "Images/inimigo a.png", sf::Vector2f(2.f, 2.f), "enemy_a_", life[0], enemyType::ENEMY_A,num_enemy[0]);
                    enemies_b.set_default_enemy(0.15, "Images/inimigo b.png", sf::Vector2f(2.f, 2.f), "enemy_b_", life[1], enemyType::ENEMY_B,num_enemy[1]);
                    enemies_c.set_default_enemy(0.08, "Images/inimigo c.png", sf::Vector2f(2.f, 2.f), "enemy_c_", life[2], enemyType::ENEMY_C,num_enemy[2]);
                    boss.set_default_enemy(0.1, "Images/boss 1.png", sf::Vector2f(2.f, 2.f), "boss", life[3], enemyType::BOSS, 1);
                    gamestate++;
                    break;
                case gamestates::STAGE_1:
                    window.clear();
                    if(clock_spawn.getElapsedTime().asSeconds() >= 1){
                        if(enemies_a.spawn_enemy(sf::Vector2f(pos_x[0], 170.f))){
                            gamestate++;
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
                        if(boss.spawn_enemy(sf::Vector2f(240.f, 100.f))){
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
                    bg_sprite.setTexture(game_over);
                    window.draw(bg_sprite);
                break;
                case gamestates::VICTORY:
                    window.clear();
                    bg_sprite.setTexture(victory);
                    window.draw(bg_sprite);                            
                break;
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

