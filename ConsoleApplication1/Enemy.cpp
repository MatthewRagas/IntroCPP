#include "pch.h"
#include "Enemy.h"


Enemy::~Enemy()
{
}

void Enemy::onAttacked(int attackPoints)
{
	m_healthPoints -= attackPoints - m_defensePoints;
	if (m_healthPoints < 0)
		m_healthPoints = 0;
}
