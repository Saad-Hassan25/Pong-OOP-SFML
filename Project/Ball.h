#ifndef _BALL_H
#define _BALL_H
#include<iostream>
#include"Vector2D.h"

class Ball
{
	Vector2D m_position;
	float m_radius;
	Vector2D m_velocity;

public:
	
	Ball(Vector2D startingPosition, float radius)
	{
		m_position = startingPosition;
		m_velocity = startingPosition;
		m_radius = radius;
	}
	Vector2D GetPosition()
	{
		return m_position;
	}
	Vector2D GetVelocity()
	{
		return m_velocity;
	}
	float GetRadius()
	{
		return m_radius;
	}
	void SetPosition(Vector2D position)
	{
		m_position = position;
	}
	void SetVelocity(Vector2D velocity)
	{
		m_velocity = velocity;
	}
};
#endif