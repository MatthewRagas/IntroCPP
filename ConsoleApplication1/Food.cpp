#include "pch.h"
#include "Food.h"
#include "GameDefines.h"
#include <iostream>
using namespace std;

Food::Food() : m_healthPoints{10}
{
	m_priority = PRIORITY_FOOD;
};

Food::Food(Point2D position) : GameObject{ position }, m_healthPoints{ 10 }
{
	m_priority = PRIORITY_FOOD;
};

void Food::draw()
{
	cout << "[ " << WHITE << "\xcf" << RESET_COLOR << " ] ";
}

void Food::drawDescription()
{
	cout << INDENT << "You find some delicious food." << endl;
}

void Food::lookAt()
{
	cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some food here." << endl;
}
