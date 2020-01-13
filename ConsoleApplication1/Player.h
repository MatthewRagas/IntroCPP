#pragma once
#include "Point2D.h"

class Player
{
public:
	Player();
	Player(int x, int y);
	~Player();

	void setposition(Point2D position);

	Point2D getPosition();

	void draw();

	bool executeCommand(int command);

private:
	Point2D m_mapPosition;
};

