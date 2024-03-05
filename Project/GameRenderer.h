#ifndef _GAMERENDERER_H
#define _GAMERENDERER_H
#include <SFML/Graphics.hpp>
#include<iostream>
#include"Paddle.h"
#include"Court.h"
#include"Ball.h"
#include"Vector2D.h"

class GameRenderer
{
public:

    static void Init(sf::RenderTarget* target, sf::Font* font)
    {
        m_target = target;
        m_font = font;
    }

    static void Render( float elapsedMilliseconds,
         Paddle playerOne,
         Paddle playerTwo,
         Ball ball,
         Court court,
         int p1Score,
         int p2Score)
    {
        sf::RectangleShape courtShape;
        RectangleShape cShape = court.GetDimensions();
        courtShape.setPosition({ cShape.x,cShape.y });
        courtShape.setSize({ cShape.width,cShape.height });
        courtShape.setFillColor(sf::Color::Blue);
        courtShape.setOutlineColor(sf::Color::White);
        courtShape.setOutlineThickness(-5);

        m_target->draw(courtShape);

        courtShape.setPosition({ 798,15 });
        courtShape.setSize({ 5,900 - 15 * 2 });
        m_target->draw(courtShape);

        sf::RectangleShape paddleShape;

        RectangleShape p1Shape = playerOne.GetPositionSize();
        paddleShape.setPosition({ p1Shape.x,p1Shape.y });
        paddleShape.setSize({ p1Shape.width,p1Shape.height });
        paddleShape.setFillColor(sf::Color::White);
        m_target->draw(paddleShape);

        RectangleShape p2Shape = playerTwo.GetPositionSize();
        paddleShape.setPosition({ p2Shape.x,p2Shape.y });
        paddleShape.setSize({ p2Shape.width,p2Shape.height });
        paddleShape.setFillColor(sf::Color::White);
        m_target->draw(paddleShape);

        sf::CircleShape ballShape;
        Vector2D ballPosition = ball.GetPosition();
        float ballRadius = ball.GetRadius();
        ballShape.setPosition({ ballPosition.x - 10,ballPosition.y - 10 });
        ballShape.setRadius(ballRadius);
        ballShape.setFillColor(sf::Color::White);
        m_target->draw(ballShape);

        sf::Text score(std::to_string(p1Score) + "   " + std::to_string(p2Score), *m_font, 40);
        sf::FloatRect bounds = score.getLocalBounds();
        score.setPosition({ 1600 / 2 - bounds.width / 2,15 + 5 + 5 });
        m_target->draw(score);
    }
private:
    static sf::RenderTarget* m_target;
    static sf::Font* m_font;
};

sf::RenderTarget* GameRenderer::m_target = nullptr;
sf::Font* GameRenderer::m_font = nullptr;


#endif