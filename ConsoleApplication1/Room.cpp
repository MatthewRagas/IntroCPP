#include "pch.h"
#include "Room.h"
#include "GameDefines.h"
#include "Powerup.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Food.h"
#include <iostream>
#include <algorithm>
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

void Room::addGameObject(GameObject* object)
{
	m_objects.push_back(object);
	sort(m_objects.begin(), m_objects.end(), GameObject::compare);
}

void Room::removeGameObject(GameObject* object)
{
	for (auto it = m_objects.begin(); it != m_objects.end(); it++)
	{
		if (*it == object)
		{
			m_objects.erase(it);
			return;
		}
	}
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
			//assume the first object in the vector take priority
			if (m_objects.size() > 0)
				m_objects[0]->draw();
			else
				cout << "[ " << GREEN << "\xb0" << RESET_COLOR << " ] ";
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
		if (m_objects.size() > 0)
			m_objects[0]->drawDescription();
		else
			cout << INDENT << "You are in an empty meadow. There is nothing of note here." << endl;
		break;
	case ENTRANCE:
		cout << INDENT << "The entrance you used to enter this maze is blocked. There is no going back." << std::endl;
		break;
	case EXIT:
		cout << INDENT << "Despite all odds, you made it to the exit. Congratulations." << std::endl;
		break;
	}
}

void Room::lookAt()
{
	if (m_objects.size() > 0)
	
		m_objects[0]->lookAt();
	else
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning" << endl;	
}

Enemy* Room::getEnemy()
{	
	for (GameObject* obj : m_objects)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(obj);
		if (enemy != nullptr)
			return enemy;
	}
	return nullptr;
}

Powerup* Room::getPowerup()
{
	for (GameObject* Obj : m_objects)
	{
		Powerup* powerup = dynamic_cast<Powerup*>(Obj);
		if (powerup != nullptr)
			return powerup;
	}
	return nullptr;
}

Food* Room::getFood()
{
	for (GameObject* Obj : m_objects)
	{
		Food* food = dynamic_cast<Food*>(Obj);
		if (food != nullptr)
			return food;
	}
	return nullptr;
}

//bool Room::executeCommand(int command, Player* _player)
//{
//	cout << EXTRA_OUTPUT_POS;
//	switch (command)
//	{
//	case FIGHT:		
//		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You coud try to fight, but you don't have a weapon." << endl;
//		cout << INDENT << "Press 'Enter' to continue.";
//		cin.clear();
//		cin.ignore(std::cin.rdbuf()->in_avail());
//		cin.get();
//		return true;
//	/*case LOOK:
//		if (m_type == TREASURE_HP || m_type == TREASURE_AT || m_type == TREASURE_DF)
//		{
//			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some treasure here. It looks small enought to pick up." << endl;
//		}
//		else
//		{
//			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning." << endl;
//		}		*/
//		cin.clear();
//		cin.ignore(std::cin.rdbuf()->in_avail());
//		cin.get();
//		return true;	
//	default:
//		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You try, but you just can't do it." << endl;
//		cout << INDENT << "Press 'Enter' to continue.";
//		cin.clear();
//		cin.ignore(cin.rdbuf()->in_avail());
//		cin.get();
//		break;
//	}
//	return false;
//}