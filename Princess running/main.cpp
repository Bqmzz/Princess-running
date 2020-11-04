#include <SFML/Graphics.hpp>
#include <iostream>
#include<vector>
#include "Player.h"
#include "Platform.h"

static const float VIEW_HEIGHT = 700.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x / float(window.getSize().y));
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1060, 750), "Princess running", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

    sf::Texture playerTexture;
    playerTexture.loadFromFile("princessrun.png");

    Player player(&playerTexture, sf::Vector2u(5, 1), 0.3f, 100.0f, 100.0f);

    std::vector<Platform> platforms;

    //platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f)));

    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                ResizeView(window, view);
                break;
            }
        }

        player.Update(deltaTime);

        sf::Vector2f direction;

        Collider playerCollision = player.GetCollider();

        for (Platform& platform : platforms)
            if (platform.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
                player.OnCollision(direction);

        view.setCenter(player.GetPosition());

        window.clear(sf::Color(150, 160, 190)); // 150 150 190
        window.setView(view);
        player.Draw(window);

        for (Platform& platform : platforms)
            platform.Draw(window);


        window.display();
    }

    return 0;
}