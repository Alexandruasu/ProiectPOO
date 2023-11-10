#include "Game.h"

const std::string PLAYER_TEXTURE = "./Assets/Textures/Player.png";
const std::string ENEMY_TEXTURE = "./Assets/Textures/Enemy.png";
const std::string BULLET_TEXTURE = "./Assets/Textures/Bullet.png";

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

    player = Player();
    player.setTexture(textures["player"]);
    player.setBulletTexture(textures["bullet"]);

    rowsHeights = std::vector<float>();

    createEnemyRow(4);
    createEnemyRow(3);
}

void Game::createEnemyRow(int num) {
    float y = 20.0f;
    if (!rowsHeights.empty()) {
        auto rows = (float)rowsHeights.size();
        y += 100.0f * rows;
    }
    float offset = 800.0f / (float)num;
    float x = (offset / 2.0f) - 64.0f;
    for (int i = 0; i < num; i++) {
        Enemy enemy = Enemy();
        enemy.setTexture(textures["enemy"]);
        enemy.setPosition({x + ((float)i * offset), y});
        std:: cout << x + ((float)i * offset) << std::endl;
        enemies.push_back(enemy);
    }
    rowsHeights.push_back(y);
}

void Game::run() {
    while(window.isOpen()) {
        sf::Event e = sf::Event();
        while(window.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    std::cout << "New width: " << window.getSize().x << '\n'
                              << "New height: " << window.getSize().y << '\n';
                    break;
                case sf::Event::KeyPressed:
                    std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
                    break;
                default:
                    break;
            }
        }

        window.clear(sf::Color::Black);

        player.loop(enemies.data(), (int)enemies.size());

        window.draw(player.getSprite());
        for (auto & enemy : enemies) {
            window.draw(enemy.getSprite());
        }

        player.drawBullets(window);

        window.display();
    }
}