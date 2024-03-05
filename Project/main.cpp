#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>
#include <cstdint>
#include <chrono>
#include"Ball.h"
#include"Button.h"
#include"Court.h"
#include"GameRenderer.h"
#include"GAME_STATE.h"
#include"MOUSE_STATE.h"
#include"Paddle.h"
#include"PLAY_STATE.h"
#include"PongGame.h"
#include"PongMenu.h"
#include"RectangleShape.h"
#include"Vector2D.h"
using namespace std;
int main()
{
    
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Pong");

    sf::Font font;
    if (!font.loadFromFile("font.ttf"))
    {
        std::cerr << "could not load font " << std::endl;
        return 0;
    }

    GAME_STATE gameState = GAME_STATE::MENU;

    PongGame pong(3, window, font);//max score
    PongMenu menu(window, font);

    std::chrono::system_clock::time_point lastTime = std::chrono::system_clock::now();
    float frameLag = 0;

    while (window.isOpen() && gameState != GAME_STATE::EXIT)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
        std::chrono::milliseconds elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime);
        lastTime = currentTime;
        frameLag += elapsedTime.count();

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        while (frameLag >= 5)
        {
            frameLag -= 5;
            if (gameState == GAME_STATE::MENU)
                gameState = menu.Update(5, { (float)mousePos.x,(float)mousePos.y });
            else
            {
                gameState = pong.Update(5);
                if (gameState == GAME_STATE::MENU)
                    menu.Reset();
            }
        }

        window.clear();

        if (gameState == GAME_STATE::MENU)
            menu.Render(elapsedTime.count());
        else
            pong.Render(elapsedTime.count());

        window.display();
    }

    window.close();

    return 0;
}