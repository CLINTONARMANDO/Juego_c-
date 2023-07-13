#include <SFML/Graphics.hpp>

class Game
{
public:
    Game() : window(sf::VideoMode(1200, 900), "Mover Cuadrado"), square(sf::Vector2f(100.0f, 100.0f))
    {
        square.setFillColor(sf::Color::Red);
        square.setPosition(0.0f, 400.0f);
        squareSpeed = 200.0f;
        sf::RectangleShape stud1(sf::Vector2f(100.0f, 100.0f));
    	stud1.setFillColor(sf::Color::Green);
    	stud1.setPosition(200.0f, 600.0f);
        sf::RectangleShape stud2(sf::Vector2f(100.0f, 100.0f));
    	stud2.setFillColor(sf::Color::Green);
    	stud2.setPosition(200.0f, 200.0f);
        sf::RectangleShape stud3(sf::Vector2f(100.0f, 100.0f));
    	stud3.setFillColor(sf::Color::Green);
    	stud3.setPosition(600.0f, 600.0f);
        sf::RectangleShape stud4(sf::Vector2f(100.0f, 100.0f));
    	stud4.setFillColor(sf::Color::Green);
    	stud4.setPosition(600.0f, 200.0f);
        sf::RectangleShape stud5(sf::Vector2f(100.0f, 100.0f));
    	stud5.setFillColor(sf::Color::Green);
    	stud5.setPosition(1000.0f, 600.0f);
        sf::RectangleShape stud6(sf::Vector2f(100.0f, 100.0f));
    	stud6.setFillColor(sf::Color::Green);
    	stud6.setPosition(1000.0f, 200.0f);
        
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

