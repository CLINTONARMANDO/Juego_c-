#include <SFML/Graphics.hpp>
#include<stdlib.h>
#include<iostream>

using namespace std;

class Game
{
public:
    Game() : window(sf::VideoMode(1060, 720), "Mover Cuadrado"), square(sf::Vector2f(80.0f, 80.0f)), stud1(sf::Vector2f(80.0f, 80.0f)), stud2(sf::Vector2f(80.0f, 80.0f)), stud3(sf::Vector2f(80.0f, 80.0f)), stud4(sf::Vector2f(80.0f, 80.0f)), stud5(sf::Vector2f(80.0f, 80.0f)), stud6(sf::Vector2f(80.0f, 80.0f))
    {
        square.setFillColor(sf::Color::Red);
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
        float movementx = squareSpeedx;
        float movementy = squareSpeedy;
        square.move(movementx, movementy);
		int numrand=0; 	
		//caso cuadrado en los topes derecho e izquierdo
        if ((square.getPosition().x + square.getSize().x > window.getSize().x || square.getPosition().x < 0) && (square.getPosition().y == 320)){
        	numrand = 1+rand()%(3-1);
            switch(numrand){
            	case 1:
            		if(square.getPosition().x < 0){
            			squareSpeedy = 0;
            			squareSpeedx = squareSpeed;
					}
					else{
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
        else if ((square.getPosition().y + square.getSize().y > window.getSize().y || square.getPosition().y < 0) && (square.getPosition().x == 320 || square.getPosition().x == 640)){
        	numrand = 1+rand()%(3-1);
            switch(numrand){
            	case 1:
            		squareSpeedy = 0;
            		squareSpeedx = -squareSpeed;
            		break;
            	case 2:
            		squareSpeedy = 0;
            		squareSpeedx = squareSpeed;
            		break;
            	case 3:
            		if(square.getPosition().y < 0){
            			squareSpeedx = 0;
            			squareSpeedy = squareSpeed;
					}
					else{
            			squareSpeedx = 0;
            			squareSpeedy = -squareSpeed;
					}
            		break;
            	
			}
		}
		//caso cuadrado en las esquinas
        else if ((square.getPosition().x < 0 && square.getPosition().y < 0) || (square.getPosition().x < 0 && square.getPosition().y + square.getSize().y > window.getSize().y) || (square.getPosition().x + square.getSize().x > window.getSize().x && square.getPosition().y < 0) || (square.getPosition().x + square.getSize().x > window.getSize().x && square.getPosition().y + square.getSize().y > window.getSize().y)){
        	numrand = 1+rand()%(3-1);
            switch(numrand){
            	case 1:
            		if(square.getPosition().y < 0){
            			squareSpeedx = 0;
            			squareSpeedy = squareSpeed;
					}
					else{
            			squareSpeedx = 0;
            			squareSpeedy = -squareSpeed;
					}
            		break;
            	case 2:
            		if(square.getPosition().x < 0){
            			squareSpeedy = 0;
            			squareSpeedx = squareSpeed;
					}
					else{
            			squareSpeedy = 0;
            			squareSpeedx = -squareSpeed;
					}
            		break;
            	
			}
		}
		
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
        window.display();
    }

    sf::RenderWindow window;
    sf::RectangleShape square;
    sf::RectangleShape stud1;
    sf::RectangleShape stud2;
    sf::RectangleShape stud3;
    sf::RectangleShape stud4;
    sf::RectangleShape stud5;
    sf::RectangleShape stud6;
    float squareSpeed;
    float squareSpeedx;
    float squareSpeedy;
};

int main()
{
    Game game;
    game.run();

    return 0;
}

