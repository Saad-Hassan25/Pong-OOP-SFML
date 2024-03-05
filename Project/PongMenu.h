#ifndef _PONGMENU_H
#define _PONGMENU_H
#include <SFML/Graphics.hpp>
#include<iostream>
#include"Paddle.h"
#include"PLAY_STATE.h"
#include"Court.h"
#include"Ball.h"
#include"GAME_STATE.h"
#include"GameRenderer.h"
#include"Button.h"

class PongMenu
{
	Button m_playButton;
	Button m_exitButton;
	bool m_shouldExit;
	bool m_shouldStart;

	sf::RenderTarget& m_target;
	sf::Font& m_font;

public:
    PongMenu(sf::RenderTarget& target, sf::Font& font)
        :
        m_target(target),
        m_font(font),
        m_playButton("PLAY", { 1600 / 2,900 / 2,140,65 }),
        m_exitButton("EXIT", { 1600 / 2,900 / 2 + 100,130,65 }),
        m_shouldExit(false),
        m_shouldStart(false)
    {
        m_playButton.SetCallback([this]() {m_shouldStart = true; });
        m_exitButton.SetCallback([this]() {m_shouldExit = true; });
    }

    GAME_STATE Update(float elapsedMilliseconds, Vector2D mousePos)
    {
        MOUSE_STATE state = MOUSE_STATE::UP;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
            sf::Mouse::isButtonPressed(sf::Mouse::Middle) ||
            sf::Mouse::isButtonPressed(sf::Mouse::Right))
            state = MOUSE_STATE::DOWN;

        m_playButton.HandleInput(mousePos, state);
        m_exitButton.HandleInput(mousePos, state);

        if (m_shouldExit)
            return GAME_STATE::EXIT;
        if (m_shouldStart)
            return GAME_STATE::IN_GAME;
        return GAME_STATE::MENU;
    }

    void Render(float elapsedMilliseconds) 
    {
        m_playButton.Render(m_target, m_font);
        m_exitButton.Render(m_target, m_font);
    }

    void Reset()
    {
        m_shouldExit = false;
        m_shouldStart = false;
    }

};


#endif