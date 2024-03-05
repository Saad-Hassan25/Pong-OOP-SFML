#ifndef _COURT_H
#define _COURT_H
#include<iostream>
#include"RectangleShape.h"

class Court
{
	RectangleShape m_dimensions;

public:
	Court() {};
	Court(RectangleShape dimensions)
	{
		m_dimensions = dimensions;
	}
	RectangleShape GetDimensions()
	{
		return m_dimensions;
	}
};
#endif