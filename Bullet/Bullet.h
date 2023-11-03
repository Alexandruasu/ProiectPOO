#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet {
private:
    float damage{};
    sf::Vector2f position{};
    sf::Vector2f velocity{};
    sf::Sprite sprite{};
    sf::Texture* texture{};
public:
    explicit Bullet(sf::Vector2f position_);
    friend std::ostream& operator<<(std::ostream& os, const Bullet& bullet);
    sf::Sprite getSprite() { return sprite; }
    void update();
    bool checkCollision() const;
    float getDamage() const { return damage; }
    Bullet() = default;
    Bullet(const Bullet& obj) : damage{obj.damage}, position{obj.position},velocity{obj.velocity}, sprite{obj.sprite}, texture{obj.texture} {};
    Bullet &operator=(const Bullet &obj) = default;
};