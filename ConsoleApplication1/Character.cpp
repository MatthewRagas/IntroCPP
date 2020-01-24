#include "pch.h"
#include "Character.h"
#include"Powerup.h"
#include <algorithm>


Character::Character() : GameObject{ {0,0} }, m_healthPoints{ 0 }, m_attackPoints{ 0 }, 
m_defencePoints{ 0 }
{}

Character::Character(Point2D position, int health, int attack, int defence) :
	GameObject{ position }, m_healthPoints{ health }, m_attackPoints{ attack }, 
	m_defencePoints{ defence }
{}

Character::~Character()
{}

void Character::addPowerup(Powerup* pPowerup)
{
	m_powerups.push_back(pPowerup);
	std::sort(m_powerups.begin(), m_powerups.end(), Powerup::compare);
}
