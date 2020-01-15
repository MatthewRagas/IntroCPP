#include "pch.h"
#include "Player.h"
#include"GameDefines.h"
#include <iostream>
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

void Player::setposition(Point2D position)
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
}

bool Player::executeCommand(int command, int roomType)
{
	switch (command)
	{
	case EAST:
		if (m_mapPosition.x < MAZE_WIDTH - 1)
			m_mapPosition.x++;
		return true;
	case WEST:
		if (m_mapPosition.x > 0)
			m_mapPosition.x--;
		return true;
	case NORTH:
		if (m_mapPosition.y > 0)
			m_mapPosition.y--;
		return true;
	case SOUTH:
		if (m_mapPosition.y < MAZE_HEIGHT - 1)
			m_mapPosition.y++;
		return true;
	}
	return false;
}

bool Player::pickup(int roomType)
{
	static const char itemNames[15][30] = {
		"indifference","invisibility", "invulnerability", "incontinence",
		"improbability", "impatience", "indecision", "inspiration",
		"independence", "incurability", "integration", "invocation",
		"inferno", "indeigestion", "inoculation"
	};

	int item = rand() % 15;
	
	switch (roomType)
	{
	case TREASURE_HP:
		strcpy(name, "potion of ");
		break;
	case TREASURE_AT:
		strcpy(name, "sword of ");
		break;
	case TREASURE_DF:
		strcpy(name, "shield of ");
		break;
	default:
		return false;
	}

	//append the item name to the string
	strncat(name, itemNames[item], 30);
	cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You pick up the " << name << endl;
}