#include "pch.h"
#include "Powerup.h"


Powerup::Powerup(const char name[30], float health, float attack, float defence)
{
}


Powerup::~Powerup()
{
}

char* Powerup::getname()
{
	return m_name;
}

float Powerup::getHealthMultiplier()
{
	return m_healthMultiplier;
}

float Powerup::getAttackMultiplier()
{
	return m_attackMultiplier;
}

float Powerup::getDefenceMultiplier()
{
	return
}