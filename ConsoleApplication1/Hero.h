#pragma once
class MyHero
{
private:
	int _health = 100;
	int _attackVal = 10;

public:
	void Fight(MyHero hero);
	void takeDamage();
};
