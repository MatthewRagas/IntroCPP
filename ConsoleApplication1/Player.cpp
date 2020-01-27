#include "pch.h"
#include "Player.h"
#include "Room.h"
#include "Enemy.h"
#include "Powerup.h"
#include "Food.h"
#include"GameDefines.h"
#include <iostream>
#include <algorithm>
using namespace std;

Player::Player() : Character({ 0,0 },100,20,20)
{
	m_priority = PRIORITY_PLAYER;
}

Player::Player(int x, int y) : Character({ x,y },100,20,20)
{}

Player::~Player()
{}

//void Player::addPowerup(Powerup * _powerup)
//{
//	m_powerups.push_back(_powerup);
//
//	sort(m_powerups.begin(), m_powerups.end(), Powerup::compare);
//}
//
//void Player::setposition(const Point2D& position)
//{
//	m_mapPosition = position;
//}
//
//Point2D Player::getPosition()
//{
//	return m_mapPosition;
//}

void Player::draw()
{
	Point2D outPos = {
		 INDENT_X + (6 * m_mapPosition.x) + 3,
	MAP_Y + m_mapPosition.y};

	//draw the player's position on the map
	//move cursor to map pos and delte character at current position
	cout << CSI << outPos.y << ";" << outPos.x << "H";
	cout << MAGENTA << "\x81" << RESET_COLOR;

	cout << INVENTORY_OUTPUT_POS;
	for (auto it = m_powerups.begin(); it < m_powerups.end(); it++)
	{
		cout << (*it)->getName() << "\t";
	}
}

void Player::drawDescription()
{}

void Player::lookAt()
{
	cout << EXTRA_OUTPUT_POS << RESET_COLOR << "Hmmmm, I look good!" << endl;
}

void Player::executeCommand(int command, Room* _room)
{
	switch (command)
	{
	case EAST:
		if (m_mapPosition.x < MAZE_WIDTH - 1)
			m_mapPosition.x++;
		return;
	case WEST:
		if (m_mapPosition.x > 0)
			m_mapPosition.x--;
		return;
	case NORTH:
		if (m_mapPosition.y > 0)
			m_mapPosition.y--;
		return;
	case SOUTH:
		if (m_mapPosition.y < MAZE_HEIGHT - 1)
			m_mapPosition.y++;
		return;
	case LOOK:
		_room->lookAt();
		break;
	case FIGHT:
		attack(_room->getEnemy());
		break;
	case PICKUP:
		pickup(_room);
		break;
	default:
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You try, but you just can't do it." << endl;
		break;
	}
	cout << INDENT << "Press'Enter' to continue.";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.get();
}

void Player::pickup(Room* _room)
{
	if (_room->getPowerup() != nullptr)
	{
		Powerup* powerup = _room->getPowerup();
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You pick up the " << powerup->getName() << endl;

		//add the powerup to the player's inventory
		addPowerup(powerup);
		//remove the powerup from the room
		_room->removeGameObject(powerup);
	}
	else if (_room->getFood() != nullptr)
	{
		Food* food = _room->getFood();
		//eat the food
		m_healthPoints += food->getHP();
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You feel refreshed. Your health is now " << m_healthPoints << endl;
		//remove the food from the room
		_room->removeGameObject(food);
	}
	else
	{
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is no one here to pick up." << endl;
	}
}

void Player::attack(Enemy* _enemy)
{
	if (_enemy == nullptr)
	{
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is no one here you can fight with." << endl;
	}
	else
	{
		_enemy->onAttacked(m_attackPoints);

		if (_enemy->isAlive() == false)
		{
			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "you fight a grue and kill it." << endl;
		}
		else
		{
			int damage = _enemy->getAT() - m_defencePoints;
			
			if (damage < 0)
				damage = 1 + rand() % 10;

			m_healthPoints -= damage;

			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You fight a grue and take " << 
				damage << " points of damage. Your health is now at " << m_healthPoints << endl;
			cout << INDENT << "The grue has " << _enemy->getHP() << " health remaining." << endl;
		}
	}
}