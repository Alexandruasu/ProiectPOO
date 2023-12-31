#include "Game.h"
#include "../Exceptions/Exceptions.h"

const std::string PLAYER_TEXTURE = "./Assets/Textures/Player.png";
const std::string ENEMY_TEXTURE = "./Assets/Textures/Enemy.png";
const std::string BULLET_TEXTURE = "./Assets/Textures/Bullet.png";

int Game::currentLevel = 1;

void Game::increaseLevel() {
    Game::currentLevel++;
}

Game::Game() {
    window.create(sf::VideoMode(800, 600), "Space Invaders", sf::Style::Default);
    window.setFramerateLimit(60);
    textures = std::map<std::string, sf::Texture>();

    sf::Texture playerTexture = sf::Texture();
    playerTexture.loadFromFile(PLAYER_TEXTURE);

    sf::Texture enemyTexture = sf::Texture();
    enemyTexture.loadFromFile(ENEMY_TEXTURE);

    sf::Texture bulletTexture = sf::Texture();
    bulletTexture.loadFromFile(BULLET_TEXTURE);

    textures["player"] = playerTexture;
    textures["enemy"] = enemyTexture;
    textures["bullet"] = bulletTexture;

    player = new Player(&textures["player"]);
    player->setBulletTexture(textures["bullet"]);
    player->setIsAlive(true);
    entities.push_back(player);

    rowsHeights = std::vector<float>();

    createEnemyRow(4);
}

void Game::createEnemyRow(int num) {
    float y = 20.0f;
    if (!rowsHeights.empty()) {
        auto rows = (float)rowsHeights.size();
        y += 120.0f * rows;
    }
    float offset = 800.0f / (float)num;
    float x = (offset / 2.0f) - 64.0f;
    for (int i = 0; i < num; i++) {
        auto enemy = new Enemy({x + ((float)i * offset), y}, &textures["enemy"]);
        enemies.push_back(enemy);
        entities.push_back(enemy);
    }
    rowsHeights.push_back(y);
}

void Game::run() {
    while (true) {
        while(window.isOpen()) {
            if (enemies.empty()) {
                Game::increaseLevel();
                break;
            }

            sf::Event e = sf::Event();
            while(window.pollEvent(e)) {
                switch(e.type) {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    default:
                        break;
                }
            }

            window.clear(sf::Color::Black);

            for (Entity* entity : entities) {
                entity->update();

                if (entity->getIsAlive()) {
                    entity->draw(window);

                    auto* player_ = dynamic_cast<Player*>(entity);
                    if (player_ != nullptr) {
                        player_->loop(enemies);
                        player_->drawBullets(window);
                        continue;
                    }

                    auto* enemy = dynamic_cast<Enemy*>(entity);
                    if (enemy != nullptr) {
                        // enemy code here...
                    }
                }
            }

            window.display();
        }

        if (enemies.empty()) {
            enemies = std::vector<Enemy*>();
            rowsHeights = std::vector<float>();
            
            switch (Game::currentLevel) {
                case 2:
                    createEnemyRow(3);
                    createEnemyRow(4);
                    continue;
                case 3:
                    createEnemyRow(4);
                    createEnemyRow(3);
                    createEnemyRow(4);
                    continue;
                default:
                    throw InvalidGameStateException();
            }
        }
    }
}