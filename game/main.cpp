#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>


using namespace std;


float timePressed=0.0f;
class Personaje
{
public:
    Personaje() {}
    virtual ~Personaje() {}

    virtual void update(sf::Time elapsedTime) = 0;
    virtual void render(sf::RenderWindow &window) = 0;
};

class Square : public Personaje
{
public:
    Square( float speed,float winsizex, float winsizey) : speed(speed)
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
        squareSpeedx = speed;
        squareSpeedy = 0.0f;
        windowx=winsizex;
        windowy=winsizey;
    }

    void update(sf::Time elapsedTime)
    {
        float movementx = squareSpeedx;
        float movementy = squareSpeedy;
        square.move(movementx, movementy);

        int numrand = 0;
        //caso cuadrado en los topes derecho e izquierdo
        if ((square.getPosition().x + square.getLocalBounds().width > windowx || square.getPosition().x < 0) && (square.getPosition().y == 320)) {
            numrand = 1 + rand() % (3 - 1);
            switch (numrand) {
            case 1:
                if (square.getPosition().x < 0) {
                    squareSpeedy = 0;
                    squareSpeedx = speed;
                }
                else {
                    squareSpeedy = 0;
                    squareSpeedx = -speed;
                }
                break;
            case 2:
                squareSpeedx = 0;
                squareSpeedy = -speed;
                break;
            case 3:
                squareSpeedx = 0;
                squareSpeedy = speed;
                break;
            }
        }
        //caso cuadrado en los topes inferiores y superiores
        else if ((square.getPosition().y + square.getLocalBounds().height > windowy|| square.getPosition().y < 0) && (square.getPosition().x == 320 || square.getPosition().x == 640)) {
            numrand = 1 + rand() % (3 - 1);
            switch (numrand) {
            case 1:
                squareSpeedy = 0;
                squareSpeedx = -speed;
                break;
            case 2:
                squareSpeedy = 0;
                squareSpeedx = speed;
                break;
            case 3:
                if (square.getPosition().y < 0) {
                    squareSpeedx = 0;
                    squareSpeedy = speed;
                }
                else {
                    squareSpeedx = 0;
                    squareSpeedy = -speed;
                }
                break;
            }
        }
        //caso cuadrado en las esquinas
        else if ((square.getPosition().x < 0 && square.getPosition().y < 0) || (square.getPosition().x < 0 && square.getPosition().y + square.getLocalBounds().height > windowy) || (square.getPosition().x + square.getLocalBounds().width > windowx && square.getPosition().y < 0) || (square.getPosition().x + square.getLocalBounds().width > windowx && square.getPosition().y + square.getLocalBounds().height > windowy)) {
            numrand = 1 + rand() % (3 - 1);
            switch (numrand) {
            case 1:
                if (square.getPosition().y < 0) {
                    squareSpeedx = 0;
                    squareSpeedy = speed;
                }
                else {
                    squareSpeedx = 0;
                    squareSpeedy = -speed;
                }
                break;
            case 2:
                if (square.getPosition().x < 0) {
                    squareSpeedy = 0;
                    squareSpeedx = speed;
                }
                else {
                    squareSpeedy = 0;
                    squareSpeedx = -speed;
                }
                break;
            }
        }
    }

    void render(sf::RenderWindow &window)
    {
        window.draw(square);
    }

private:
    sf::Texture texture;        // Textura para la imagen
    sf::Sprite square;          // Sprite para la imagen
    float windowy;
    float windowx;
    float speed;
    float squareSpeedx;
    float squareSpeedy;
};

class Estudiante : public Personaje
{
public:
    Estudiante(string nam, string nam1, float x,float y,sf::Keyboard::Key key) : isBlue(false)
    {
    	name=nam;
    	name1=nam1;
    	if (!texture.loadFromFile(name))
        {
            std::cerr << "Error al cargar la textura 'prof.png'" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    	if (!texture1.loadFromFile(name1))
        {
            std::cerr << "Error al cargar la textura 'prof.png'" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        estudiante.setTexture(texture1);
    	tecla=key;
        estudiante.setPosition(x, y);
    }

    void update(sf::Time elapsedTime)
    {
        // Check if the key "1" is pressed and change color
        if (sf::Keyboard::isKeyPressed(tecla))
        {
            isBlue = true;
        	estudiante.setTexture(texture1);

        }
        else
        {
            isBlue = false;
        	estudiante.setTexture(texture);
        }
        if (isBlue)
        {
            timePressed += elapsedTime.asSeconds();
        }
        
    }

    void render(sf::RenderWindow &window)
    {
        window.draw(estudiante);
    }

private:
    sf::Texture texture;        // Textura para la imagen
    sf::Texture texture1;        // Textura para la imagen
    sf::Sprite estudiante;          // Sprite para la imagen
    bool isBlue;
    sf::Keyboard::Key tecla;
    string name;
    string name1;
};

class Game
{
public:
    Game() : window(sf::VideoMode(1060, 720), "Mover Cuadrado")
    {
        square = new Square( 0.1250f, 1060, 720);
        Estudiante1 = new Estudiante("1a.png","1b.png", 160.0f,160.0f, sf::Keyboard::Num1);
        Estudiante2 = new Estudiante("2a.png","2b.png", 480.0f,160.0f, sf::Keyboard::Num2);
        Estudiante3 = new Estudiante("3a.png","3b.png", 800.0f,160.0f, sf::Keyboard::Num3);
        Estudiante4 = new Estudiante("4a.png","4b.png", 160.0f,480.0f, sf::Keyboard::Num4);
        Estudiante5 = new Estudiante("5a.png","5b.png", 480.0f,480.0f, sf::Keyboard::Num5);
        Estudiante6 = new Estudiante("6a.png","6b.png", 800.0f,480.0f, sf::Keyboard::Num6);
        
        // Configuramos el texto para mostrar el tiempo
        timeDisplay.setFont(font);
        timeDisplay.setCharacterSize(20);
        timeDisplay.setPosition(window.getSize().x - 220.0f, 20.0f);
        timeDisplay.setFillColor(sf::Color::White);
        
                      // Fuente para el texto
    	if (!font.loadFromFile("arial.ttf"))
    	{
        	std::cerr << "Error al cargar la fuente 'arial.ttf'" << std::endl;
        	return;
    	}
    }

    ~Game()
    {
        delete square;
        delete Estudiante1;
        delete Estudiante2;
        delete Estudiante3;
        delete Estudiante4;
        delete Estudiante5;
        delete Estudiante6;
    }

    void run()
    {
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
        // Update entities
        square->update(elapsedTime);
        Estudiante1->update(elapsedTime);
        Estudiante2->update(elapsedTime);
        Estudiante3->update(elapsedTime);
        Estudiante4->update(elapsedTime);
        Estudiante5->update(elapsedTime);
        Estudiante6->update(elapsedTime);
        // Actualizar el tiempo mostrado en la esquina superior derecha
        float currentTime = timePressed;
        stringstream ss;
    	ss << "Puntaje: " <<setprecision(3)<< currentTime;
        string timeText = ss.str();
        timeDisplay.setString(timeText);
    }

    void render()
    {
        window.clear();

        // Render entities
        square->render(window);
        Estudiante1->render(window);
        Estudiante2->render(window);
        Estudiante3->render(window);
        Estudiante4->render(window);
        Estudiante5->render(window);
        Estudiante6->render(window);
        window.draw(timeDisplay);

        window.display();
    }
    sf::Text timeDisplay;       // Texto para mostrar el tiempo
    sf::Font font;
    sf::RenderWindow window;
    sf::Clock clock;
    Square* square;
    Estudiante* Estudiante1;
    Estudiante* Estudiante2;
    Estudiante* Estudiante3;
    Estudiante* Estudiante4;
    Estudiante* Estudiante5;
    Estudiante* Estudiante6;
    sf::Clock keyClock; // Reloj para medir el tiempo que se mantiene presionada la tecla "1"
};

int main()
{
    Game game;
    game.run();

    return 0;
}

