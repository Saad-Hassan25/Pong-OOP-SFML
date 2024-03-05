#ifndef _PONGGAME_H
#define _PONGGAME_H
#include <SFML/Graphics.hpp>
#include<iostream>
#include"Paddle.h"
#include"PLAY_STATE.h"
#include"Court.h"
#include"Ball.h"
#include"GAME_STATE.h"
#include"GameRenderer.h"

class PongGame
{
	int m_playerOneScore;
	int m_playerTwoScore;
	int m_maxScore;
	Court m_court;
	Ball m_ball;
	Paddle m_playerOne;
	Paddle m_playerTwo;
	PLAY_STATE m_playState;

public:

	PongGame(int scoreToWin, sf::RenderTarget& target, sf::Font& font):
        m_playerOneScore(0),
        m_playerTwoScore(0),
        m_maxScore(scoreToWin),
        m_court({
            15,
            15,
            1600 - 15 * 2,
            900 - 15 * 2
        }),
        m_ball({
                1600 / 2,
                900 / 2
            },
            10
        ),
        m_playerOne({
            15 + 20,
            900 / 2 - (70 / 2),
            10,
            70
            }),
        m_playerTwo({
            1600 - 15 - 20 - 10,
            900 / 2 - (70 / 2),
            10,
            70
            }),
        m_playState(PLAY_STATE::SERVE_PLAYER_ONE)
	{
        GameRenderer::Init(&target, &font);
	}

    GAME_STATE Update(float elapsedMilliseconds)
    {
        float timeMultiplier = elapsedMilliseconds / 700.0f;///////////////////////////

         RectangleShape paddle1 = m_playerOne.GetPositionSize();
         RectangleShape paddle2 = m_playerTwo.GetPositionSize();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            m_playerOne.SetPosition({ paddle1.x,paddle1.y - 500 * timeMultiplier });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            m_playerOne.SetPosition({ paddle1.x,paddle1.y + 500 * timeMultiplier });

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
            m_playerTwo.SetPosition({ paddle2.x,paddle2.y - 500 * timeMultiplier });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            m_playerTwo.SetPosition({ paddle2.x,paddle2.y + 500 * timeMultiplier });

        switch (m_playState)
        {
        case PLAY_STATE::SERVE_PLAYER_ONE:
        {
            m_ball.SetVelocity({ 0,0 });
             RectangleShape paddle = m_playerOne.GetPositionSize();
            m_ball.SetPosition({ paddle.x + 10,paddle.y + 70 / 2 });

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                m_ball.SetVelocity({ 500,0 });
                m_playState = PLAY_STATE::TOWARD_PLAYER_TWO;
            }
            break;
        }
        case PLAY_STATE::SERVE_PLAYER_TWO:
        {
            m_ball.SetVelocity({ 0,0 });
             RectangleShape paddle = m_playerTwo.GetPositionSize();
            m_ball.SetPosition({ paddle.x - 10,paddle.y + 70 / 2 });

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                m_ball.SetVelocity({ -500,0 });
                m_playState = PLAY_STATE::TOWARD_PLAYER_ONE;
            }
            break;
        }
        default:
            break;
        }

        Vector2D ballPos = m_ball.GetPosition();
        Vector2D ballVelocity = m_ball.GetVelocity();
         RectangleShape courtShape = m_court.GetDimensions();

        ballPos.x += ballVelocity.x * timeMultiplier;
        ballPos.y += ballVelocity.y * timeMultiplier;

        m_ball.SetPosition(ballPos);

        switch (m_playState)
        {
        case PLAY_STATE::TOWARD_PLAYER_ONE:
        {
            if (ballPos.x - 10 > paddle1.x + 10)
                break; // ball hasn't reached player 1

            if (ballPos.y + 10 >= paddle1.y && ballPos.y - 10 <= paddle1.y + 70)
            {
                m_ball.SetPosition({ paddle1.x + 10 + 10 + 1, ballPos.y });

                ballVelocity.x = -ballVelocity.x;

                if (ballPos.y + 10 <= paddle1.y + 70 / 3)
                    ballVelocity.y -= 500 / 2;
                else if (ballPos.y - 10 >= paddle1.y + 70 / 3 * 2)
                    ballVelocity.y += 500 / 2;

                if (ballVelocity.x > 0)
                    ballVelocity.x += 200;
                else
                    ballVelocity.x -= 200;

                if (ballVelocity.y > 0)
                    ballVelocity.y += 200;
                else
                    ballVelocity.y -= 200;

                m_ball.SetVelocity(ballVelocity);
                m_playState = PLAY_STATE::TOWARD_PLAYER_TWO;

                break;
            }

            if (ballPos.x + 10 < paddle1.x)
            {
                ++m_playerTwoScore;
                m_playState = PLAY_STATE::SERVE_PLAYER_ONE;
            }

            break;
        }
        case PLAY_STATE::TOWARD_PLAYER_TWO:
        {
            if (ballPos.x + 10 < paddle2.x)
                break;

            if (ballPos.y + 10 >= paddle2.y && ballPos.y - 10 <= paddle2.y + 70)
            {
                m_ball.SetPosition({ paddle2.x - 10 - 1, ballPos.y });

                ballVelocity.x = -ballVelocity.x;

                if (ballPos.y + 10 <= paddle2.y + 70 / 3)
                    ballVelocity.y -= 500 / 2;
                else if (ballPos.y - 10 >= paddle2.y + 70 / 3 * 2)
                    ballVelocity.y += 500 / 2;

                if (ballVelocity.x > 0)
                    ballVelocity.x += 200;
                else
                    ballVelocity.x -= 200;

                if (ballVelocity.y > 0)
                    ballVelocity.y += 200;
                else
                    ballVelocity.y -= 200;

                m_ball.SetVelocity(ballVelocity);
                m_playState = PLAY_STATE::TOWARD_PLAYER_ONE;

                break;
            }

            if (ballPos.x - 10 > paddle2.x + 10)
            {
                ++m_playerOneScore;
                m_playState = PLAY_STATE::SERVE_PLAYER_TWO;
            }

            break;
        }
        default:
            break;
        }

        if (ballPos.y <= courtShape.y)
        {
            m_ball.SetPosition({ ballPos.x,courtShape.y });
            m_ball.SetVelocity({ ballVelocity.x,-ballVelocity.y });
        }
        else if (ballPos.y >= courtShape.y + courtShape.height)
        {
            m_ball.SetPosition({ ballPos.x,courtShape.y + courtShape.height });
            m_ball.SetVelocity({ ballVelocity.x,-ballVelocity.y });
        }

        if (m_playerOneScore >= m_maxScore || m_playerTwoScore >= m_maxScore)
            return GAME_STATE::MENU;

        return GAME_STATE::IN_GAME;
    }

    void Render(const float elapsedMilliseconds) 
    {
        GameRenderer::Render(elapsedMilliseconds, m_playerOne, m_playerTwo, m_ball, m_court, m_playerOneScore, m_playerTwoScore);
    }

};


#endif