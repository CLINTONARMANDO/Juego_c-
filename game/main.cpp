#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream> // Agregar esta línea

using namespace std;

class Game
{
public:
    Game() : window(sf::VideoMode(1060, 720), "Mover Cuadrado"), stud1(sf::Vector2f(80.0f, 80.0f)), stud2(sf::Vector2f(80.0f, 80.0f)), stud3(sf::Vector2f(80.0f, 80.0f)), stud4(sf::Vector2f(80.0f, 80.0f)), stud5(sf::Vector2f(80.0f, 80.0f)), stud6(sf::Vector2f(80.0f, 80.0f))
    {
        // Cargamos la textura desde el archivo "prof.png"
        if (!texture.loadFromFile("prof.png"))
        {
            std::cerr << "Error al cargar la textura 'prof.png'" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        // Creamos un sprite con la textura cargada
        square.setTexture(texture);

        square.setPosition(0.0f, 320.0f);
        squareSpeed = 0.1250f;
        squareSpeedx = squareSpeed;
        squareSpeedy = 0.0f;

        stud1.setFillColor(sf::Color::Green);
        stud1.setPosition(160.0f, 480.0f);
        stud2.setFillColor(sf::Color::Green);
        stud2.setPosition(160.0f, 160.0f);
        stud3.setFillColor(sf::Color::Green);
        stud3.setPosition(480.0f, 480.0f);
        stud4.setFillColor(sf::Color::Green);
        stud4.setPosition(480.0f, 160.0f);
        stud5.setFillColor(sf::Color::Green);
        stud5.setPosition(800.0f, 480.0f);
        stud6.setFillColor(sf::Color::Green);
        stud6.setPosition(800.0f, 160.0f);

        isStud1Blue = false; // Variable para controlar el color de stud1
        isStud2Blue = false; // Variable para controlar el color de stud2
        isStud3Blue = false; // Variable para controlar el color de stud3
        isStud4Blue = false; // Variable para controlar el color de stud4
        isStud5Blue = false; // Variable para controlar el color de stud5
        isStud6Blue = false; // Variable para controlar el color de stud6
        timePressed = 0.0f;   // Contador de tiempo
        
        // Cargamos la fuente para mostrar el tiempo
        if (!font.loadFromFile("arial.ttf"))
        {
            std::cerr << "Error al cargar la fuente 'arial.ttf'" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        // Configuramos el texto para mostrar el tiempo
        timeDisplay.setFont(font);
        timeDisplay.setCharacterSize(20);
        timeDisplay.setPosition(window.getSize().x - 220.0f, 20.0f);
        timeDisplay.setFillColor(sf::Color::White);
    }
        sf::Clock clock;
        sf::Clock keyClock; // Reloj para medir el tiempo que se mantiene presionada la tecla "1"

    void run()
    {

        while (window.isOpen())
        {
            processEvents();
            update(clock.restart(), keyClock);
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

        // Detectar si la tecla 1 está presionada y cambiar el color de stud1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        {
            stud1.setFillColor(sf::Color::Blue);
            isStud1Blue = true;

            // Incrementar el contador de tiempo mientras la tecla está presionada
            timePressed += clock.getElapsedTime().asSeconds();
        }
        else
        {
            stud1.setFillColor(sf::Color::Green);
            isStud1Blue = false;
        }
        // Detectar si la tecla 2 está presionada y cambiar el color de stud2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        {
            stud2.setFillColor(sf::Color::Blue);
            isStud2Blue = true;

            // Incrementar el contador de tiempo mientras la tecla está presionada
            timePressed += clock.getElapsedTime().asSeconds();
        }
        else
        {
            stud2.setFillColor(sf::Color::Green);
            isStud2Blue = false;
        }
        // Detectar si la tecla 3 está presionada y cambiar el color de stud3
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        {
            stud3.setFillColor(sf::Color::Blue);
            isStud3Blue = true;

            // Incrementar el contador de tiempo mientras la tecla está presionada
            timePressed += clock.getElapsedTime().asSeconds();
        }
        else
        {
            stud3.setFillColor(sf::Color::Green);
            isStud3Blue = false;
        }
        // Detectar si la tecla 4 está presionada y cambiar el color de stud4
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        {
            stud4.setFillColor(sf::Color::Blue);
            isStud4Blue = true;

            // Incrementar el contador de tiempo mientras la tecla está presionada
            timePressed += clock.getElapsedTime().asSeconds();
        }
        else
        {
            stud4.setFillColor(sf::Color::Green);
            isStud4Blue = false;
        }
        // Detectar si la tecla 5 está presionada y cambiar el color de stud5
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        {
            stud5.setFillColor(sf::Color::Blue);
            isStud5Blue = true;

            // Incrementar el contador de tiempo mientras la tecla está presionada
            timePressed += clock.getElapsedTime().asSeconds();
        }
        else
        {
            stud5.setFillColor(sf::Color::Green);
            isStud5Blue = false;
        }
        // Detectar si la tecla 1 está presionada y cambiar el color de stud1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        {
            stud6.setFillColor(sf::Color::Blue);
            isStud6Blue = true;

            // Incrementar el contador de tiempo mientras la tecla está presionada
            timePressed += clock.getElapsedTime().asSeconds(); 
        }
        else
        {
            stud6.setFillColor(sf::Color::Green);
            isStud6Blue = false;
        }
        
    }

    void update(sf::Time elapsedTime, sf::Clock &keyClock)
    {
        float movementx = squareSpeedx;
        float movementy = squareSpeedy;
        square.move(movementx, movementy);
        int numrand = 0;
        //caso cuadrado en los topes derecho e izquierdo
        if ((square.getPosition().x + square.getLocalBounds().width > window.getSize().x || square.getPosition().x < 0) && (square.getPosition().y == 320)) {
            numrand = 1 + rand() % (3 - 1);
            switch (numrand) {
            case 1:
                if (square.getPosition().x < 0) {
                    squareSpeedy = 0;
                    squareSpeedx = squareSpeed;
                }
                else {
                    squareSpeedy = 0;
                    squareSpeedx = -squareSpeed;
                }
                break;
            case 2:
                squareSpeedx = 0;
                squareSpeedy = -squareSpeed;
                break;
            case 3:
                squareSpeedx = 0;
                squareSpeedy = squareSpeed;
                break;
            }
        }
        //caso cuadrado en los topes inferiores y superiores
        else if ((square.getPosition().y + square.getLocalBounds().height > window.getSize().y || square.getPosition().y < 0) && (square.getPosition().x == 320 || square.getPosition().x == 640)) {
            numrand = 1 + rand() % (3 - 1);
            switch (numrand) {
            case 1:
                squareSpeedy = 0;
                squareSpeedx = -squareSpeed;
                break;
            case 2:
                squareSpeedy = 0;
                squareSpeedx = squareSpeed;
                break;
            case 3:
                if (square.getPosition().y < 0) {
                    squareSpeedx = 0;
                    squareSpeedy = squareSpeed;
                }
                else {
                    squareSpeedx = 0;
                    squareSpeedy = -squareSpeed;
                }
                break;
            }
        }
        //caso cuadrado en las esquinas
        else if ((square.getPosition().x < 0 && square.getPosition().y < 0) || (square.getPosition().x < 0 && square.getPosition().y + square.getLocalBounds().height > window.getSize().y) || (square.getPosition().x + square.getLocalBounds().width > window.getSize().x && square.getPosition().y < 0) || (square.getPosition().x + square.getLocalBounds().width > window.getSize().x && square.getPosition().y + square.getLocalBounds().height > window.getSize().y)) {
            numrand = 1 + rand() % (3 - 1);
            switch (numrand) {
            case 1:
                if (square.getPosition().y < 0) {
                    squareSpeedx = 0;
                    squareSpeedy = squareSpeed;
                }
                else {
                    squareSpeedx = 0;
                    squareSpeedy = -squareSpeed;
                }
                break;
            case 2:
                if (square.getPosition().x < 0) {
                    squareSpeedy = 0;
                    squareSpeedx = squareSpeed;
                }
                else {
                    squareSpeedy = 0;
                    squareSpeedx = -squareSpeed;
                }
                break;
            }
        }

        // Actualizar el tiempo mostrado en la esquina superior derecha
        float currentTime = timePressed;
        stringstream ss;
    	ss << "Time Pressed (s): " << currentTime;
        string timeText = ss.str();
        timeDisplay.setString(timeText);
    }

    void render()
    {
        window.clear();
        window.draw(square);
        window.draw(stud1);
        window.draw(stud2);
        window.draw(stud3);
        window.draw(stud4);
        window.draw(stud5);
        window.draw(stud6);
        window.draw(timeDisplay);
        window.display();
    }

    sf::RenderWindow window;
    sf::Texture texture;        // Textura para la imagen
    sf::Sprite square;          // Sprite para la imagen
    sf::RectangleShape stud1;
    sf::RectangleShape stud2;
    sf::RectangleShape stud3;
    sf::RectangleShape stud4;
    sf::RectangleShape stud5;
    sf::RectangleShape stud6;
    sf::Text timeDisplay;       // Texto para mostrar el tiempo
    sf::Font font;              // Fuente para el texto
    float squareSpeed;
    float squareSpeedx;
    float squareSpeedy;
    bool isStud1Blue;           // Variable para controlar el color de stud1
    bool isStud2Blue;           // Variable para controlar el color de stud2
    bool isStud3Blue;           // Variable para controlar el color de stud3
    bool isStud4Blue;           // Variable para controlar el color de stud4
    bool isStud5Blue;           // Variable para controlar el color de stud5
    bool isStud6Blue;           // Variable para controlar el color de stud6
    float timePressed;          // Contador de tiempo
};

int main()
{ 	
    Game game;
    sf::Clock keyClock;
    game.run();

    return 0;
}


