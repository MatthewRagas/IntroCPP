#pragma once
#include "Character.h"
#include <vector>


class Powerup;
class Room;
class Enemy;

class Player : public Character
{
public:
	Player();
	Player(int x, int y);
	~Player();

	/*void addPowerup(Powerup* _powerup);
	void setposition(const Point2D& position);
	Point2D getPosition();
*/
	void draw();
	void drawDescription();
	void lookAt();
	void executeCommand(int command, Room* _room);

private:
	void pickup(Room* _room);
	void attack(Enemy* _enemy);

//private:
//	Point2D m_mapPosition;
//
//	std::vector<Powerup*> m_powerups;
//
//	int m_healthPoints;
//	int m_attackPoints;
//	int m_defencePoints;
};

