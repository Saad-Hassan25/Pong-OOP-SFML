#ifndef _BUTTON_H
#define _BUTTON_H
#include <SFML/Graphics.hpp>
#include<iostream>
#include <functional>
#include<cstring>
#include"Paddle.h"
#include"PLAY_STATE.h"
#include"MOUSE_STATE.h"
#include"Court.h"
#include"Ball.h"
#include"GAME_STATE.h"
#include"GameRenderer.h"
using namespace std;

class Button
{
public:
	typedef std::function<void(void)> CallbackFunc;
	enum class STATE
	{
		UP,
		DOWN,
		HOVER
	};

	Button(const std::string text, const RectangleShape positionAndSize)
		:
		m_text(text),
		m_positionAndSize(positionAndSize),
		m_colorUp(sf::Color::Black),
		m_colorDown(sf::Color::Red),
		m_colorHover(sf::Color::Yellow),
		m_callback([]() {}),
		m_state(STATE::UP)
	{}


	RectangleShape GetPositionAndSize()
	{
		return m_positionAndSize;
	}
	void setPositionAndSize(RectangleShape newPositionAndSize)
	{
		m_positionAndSize = newPositionAndSize;
	}
	void setPosition(Vector2D newPosition)
	{
		m_positionAndSize.x = newPosition.x;
		m_positionAndSize.y = newPosition.y;
	}
	void SetSize(Vector2D newSize)
	{
		m_positionAndSize.width = newSize.x;
		m_positionAndSize.height = newSize.y;
	}

	bool HandleInput(Vector2D mousePosition, MOUSE_STATE mouseState)
	{
		if (mousePosition.x >= m_positionAndSize.x &&
			mousePosition.x <= m_positionAndSize.x + m_positionAndSize.width &&
			mousePosition.y >= m_positionAndSize.y &&
			mousePosition.y <= m_positionAndSize.y + m_positionAndSize.height)
		{
			m_state = STATE::HOVER;
		}

		else
		{
			m_state = STATE::UP;
		}

		if (mouseState == MOUSE_STATE::DOWN && m_state == STATE::HOVER)
		{
			m_state = STATE::DOWN;
			m_callback();
			return true;
		}

		return false;
	}

	void SetColors(sf::Color upColor, sf::Color downColor, sf::Color hoverColor)
	{
		m_colorUp = upColor;
		m_colorDown = downColor;
		m_colorHover = hoverColor;
	}

    void SetCallback(const CallbackFunc callback)
    {
        m_callback = callback;
    }

	Button::STATE GetState()
	{
		return m_state;
	}

	void SetState(Button::STATE newState)
	{
		m_state = newState;
	}

	void Render(sf::RenderTarget& target,  sf::Font& font) 
	{
		sf::Text buttonText(m_text, font, 60);
		//buttonText.setColor(m_colorUp);
		/*if (m_state == STATE::DOWN)
			buttonText.setColor(m_colorDown);
		else if (m_state == STATE::HOVER)
			buttonText.setColor(m_colorHover);*/

		buttonText.setPosition({ m_positionAndSize.x,m_positionAndSize.y });

		sf::RectangleShape bg;
		bg.setPosition({ m_positionAndSize.x,m_positionAndSize.y });
		bg.setSize({ m_positionAndSize.width,m_positionAndSize.height });
		bg.setFillColor(sf::Color::White);

		target.draw(bg);
		target.draw(buttonText);
	}

private:
	string m_text;
	RectangleShape m_positionAndSize;
	sf::Color m_colorUp;
	sf::Color m_colorDown;
	sf::Color m_colorHover;
	CallbackFunc m_callback;
	STATE m_state;
};


#endif