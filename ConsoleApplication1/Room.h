#pragma once
#include "Point2D.h"

class Powerup;
class Player;
class Enemy;
class Food;

class Room
{
public:
	Room();
	~Room();

	void setPosition(Point2D position);
	void setType(int type);
	void setEnemy(Enemy* _enemy) { m_enemy = _enemy; }
	void setPowerup(Powerup* _powerup) { m_powerup = _powerup; }
	void setFood(Food* _food) { m_food = _food; }

	int getType();
	Enemy* getenemy() { return m_enemy; }
	Powerup* getPowerup() { return m_powerup; }
	Food* getFood() { return m_food; }

	void draw();
	void drawDescription();

	bool executeCommand(int command, Player* _player);

private:
	Point2D m_mapPosition;
	int m_type;

	Powerup* m_powerup;
	Enemy* m_enemy;
	Food* m_food;
};

