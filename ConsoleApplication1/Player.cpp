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

Player::Player() : m_mapPosition{ 0, 0 }, m_healthPoints{100}, m_attackPoints{20}, m_defencePoints{20}
{	
}

Player::Player(int x, int y) : m_mapPosition{ x, y }, m_healthPoints{ 100 }, m_attackPoints{ 20 }, m_defencePoints{ 20 }
{	
}

Player::~Player()
{
	
}

void Player::addPowerup(Powerup * _powerup)
{
	m_powerups.push_back(_powerup);

	sort(m_powerups.begin(), m_powerups.end(), Powerup::compare);
}

void Player::setposition(const Point2D& position)
{
	m_mapPosition = position;
}

Point2D Player::getPosition()
{
	return m_mapPosition;
}

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
		cout << (*it)->getname() << "\t";
	}
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
		if (_room->getenemy() != nullptr)
		{
			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "LOOK OUT! An enemy is approaching." << endl;
		}
		else if (_room->getPowerup() != nullptr)
		{
			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some treasure here. I looks small enough to pick up." << endl;
		}
		else if(_room->getFood() != nullptr)
		{
			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning." << endl;
		}
		break;
	case FIGHT:
		attack(_room->getenemy());
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
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You pick up the " << _room->getPowerup()->getname() << endl;

		//add the powerup to the player's inventory
		addPowerup(_room->getPowerup());
		//remove the powerup from the room
		_room->setPowerup(nullptr);
	}
	else if (_room->getFood() != nullptr)
	{
		//eat the food
		m_healthPoints += _room->getFood()->getHP();
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You feel refreshed. Your health is now " << m_healthPoints << endl;
		//remove the food from the room
		_room->setFood(nullptr);
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
			m_healthPoints -= damage;

			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You fight a grue and take " << 
				damage << " points of damage. Your health is now at " << m_healthPoints << endl;
			cout << INDENT << "The grue has " << _enemy->getHP() << " health remaining." << endl;
		}
	}
}