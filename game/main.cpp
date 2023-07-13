#include <SFML/Graphics.hpp>

class Game
{
public:
    Game() : window(sf::VideoMode(800, 600), "Mover Cuadrado"), square(sf::Vector2f(100.0f, 100.0f))
    {
        square.setFillColor(sf::Color::Red);
        square.setPosition(0.0f, 250.0f);
        squareSpeed = 200.0f;
    }

    void run()
    {
        sf::Clock clock;

        while (window.isOpen())
        {
            processEvents();
            update(clock.restart());
            render();
        }
    }

private:
    void processEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    void update(sf::Time elapsedTime)
    {
        float movement = squareSpeed * elapsedTime.asSeconds();
        square.move(movement, 0.0f);

        if (square.getPosition().x + square.getSize().x > window.getSize().x || square.getPosition().x < 0)
        {
            squareSpeed = -squareSpeed;
        }
    }

    void render()
    {
        window.clear();
        window.draw(square);
        window.display();
    }

    sf::RenderWindow window;
    sf::RectangleShape square;
    float squareSpeed;
};

int main()
{
    Game game;
    game.run();

    return 0;
}

