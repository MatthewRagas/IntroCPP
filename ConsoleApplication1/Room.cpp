#include "pch.h"
#include "Room.h"
#include "GameDefines.h"
#include <iostream>
using namespace std;

Room::Room() : m_type{ EMPTY }, m_mapPosition{ 0,0 }
{
}

Room::~Room()
{
}

void Room::setPosition(Point2D position)
{
	m_mapPosition = position;
}

void Room::setType(int type)
{
	m_type = type;
}

int Room::getType()
{
	return m_type;
}

void Room::draw()
{
	//find the console output position
	int outX = INDENT_X + (6 * m_mapPosition.x) + 1;
	int outY = MAP_Y + m_mapPosition.y;

	//jump to the correct locaiton
	cout << CSI << outY << ";" << outX << "H";
	//draw the room
	switch(m_type)
	{
		case EMPTY:
			cout << "[ " << GREEN << "\xb0" << RESET_COLOR << " ] ";
			break;
		case ENEMY:
			cout << "[ " << RED << "\x94" << RESET_COLOR << " ] ";
			break;
		case TREASURE_HP:
		case TREASURE_AT:
		case TREASURE_DF:
			cout << "[ " << YELLOW << "\$" << RESET_COLOR << " ] ";
			break;
		case FOOD:
			cout << "[ " << WHITE << "\xcf" << RESET_COLOR << " ] ";
			break;
		case ENTRANCE:
			cout << "[ " << WHITE << "\x9d" << RESET_COLOR << " ] ";
			break;
		case EXIT:
			cout << "[ " << WHITE << "\xFE" << RESET_COLOR << " ] ";
			break;
	}
}

void Room::drawDescription()
{
	cout << RESET_COLOR;//reset draw colors
	cout << CSI << ROOM_DESC_Y << ";" << 0 << "H";//jump to correct pos
	//delete 4 lines and insert 4 empty lines
	cout<<CSI<<"4M"<<CSI<<"4L"<<endl;
	//write description of current room
	switch (m_type)
	{
	case EMPTY:
		cout << INDENT << "You are in an empty meadow. There is nothing of note here." << endl;
		break;
	case ENEMY:
		cout << INDENT << "BEWARE. An enemy is approaching." << std::endl;
		break;
	case TREASURE_HP:
	case TREASURE_AT:
	case TREASURE_DF:
		cout << INDENT << "There appears to be some treasure here. Perhaps you should investigate further." << std::endl;
		break;
	case FOOD:
		cout << INDENT << "At last! You collect some food to sustain you on your journey." << std::endl;
		break;
	case ENTRANCE:
		cout << INDENT << "The entrance you used to enter this maze is blocked. There is no going back." << std::endl;
		break;
	case EXIT:
		cout << INDENT << "Despite all odds, you made it to the exit. Congratulations." << std::endl;
		break;
	}
}

bool Room::executeCommand(int command)
{
	cout << EXTRA_OUTPUT_POS;
	switch (command)
	{
	case FIGHT:		
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You coud try to fight, but you don't have a weapon." << endl;
		cout << INDENT << "Press 'Enter' to continue.";
		cin.clear();
		cin.ignore(std::cin.rdbuf()->in_avail());
		cin.get();
		return true;
	case LOOK:
		if (m_type == TREASURE_HP || m_type == TREASURE_AT || m_type == TREASURE_DF)
		{
			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some treasure here. It looks small enought to pick up." << endl;
		}
		else
		{
			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning." << endl;
		}		
		cin.clear();
		cin.ignore(std::cin.rdbuf()->in_avail());
		cin.get();
		return true;
	default:
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You try, but you just can't do it." << endl;
		cout << INDENT << "Press 'Enter' to continue.";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin.get();
		break;
	}
	return false;
}
