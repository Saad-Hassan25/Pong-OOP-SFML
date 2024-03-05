#ifndef _PADDLE_H
#define _PADDLE_H
#include<iostream>
#include"RectangleShape.h"
#include"Vector2D.h"

class Paddle
{
	RectangleShape m_rect;

public:
	Paddle() {};
	Paddle(RectangleShape startingPosition)
	{
		m_rect = startingPosition;
	}
	RectangleShape GetPositionSize()
	{
		return m_rect;
	}
	void SetPositionSize(RectangleShape newPositionAndSize)
	{
		m_rect = newPositionAndSize;
	}
	void SetPosition(Vector2D newPosition)
	{
		m_rect.x = newPosition.x;
		m_rect.y = newPosition.y;
	}

};
#endif