// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <random>
#include <time.h>
const char* INDENT = "\t";

int AddArrays(int _arr1[], int _arr2[], int array_length)
{
	int sum = 0;
	for (int i = 0; i < array_length; i++)
	{
		sum += _arr1[i] + _arr2[i];
	}

	return sum;
}

void main()
{
	const int EMPTY = 0;
	const int ENEMY = 1;
	const int TREASURE = 2;
	const int FOOD = 3;
	const int ENTRANCE = 4;
	const int EXIT = 5;
	const int MAX_RANDOM_TYPE = FOOD + 1;

	const int MAZE_WIDTH = 10;
	const int MAZE_HEIGHT = 6;

    //std::cout << "Hello World!\n"; 
	//C * 9/5 + 32
	/*std::cout << "What the temp is?"<<std::endl;
	int c = 0;
	
	std::cin >> c;
	int f = c * 9 / 5 + 32;
	std::cout << f;*/
	/*int arr1[3] = { 1,1,1 };
	int arr2[3] = { 1,1,1 };
	std::cout << AddArrays(arr1, arr2, 3);
	system("pause");*/

	int height = 0;
	char firstLetterOfName = 0;
	int avatarHP = 0;

	//Creates 2D array
	int rooms[MAZE_HEIGHT][MAZE_WIDTH];

	srand(time(nullptr));

	//fill the arrays with random room types
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			rooms[y][x] = rand() % MAX_RANDOM_TYPE;
		}
	}

	system("cls");

	std::cout << INDENT << INDENT << "Welcome to ZORP!" << std::endl;
	std::cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << std::endl;
	std::cout << "It is definitely not related to any other text-based adventure game." << std::endl << std::endl;

	std::cout << INDENT << "First, some questions..." << std::endl;
	std::cout << INDENT << "How tall are you in centimeters?" << std::endl;
	
	std::cin >> height;
	std::cout << std::endl;
	if (std::cin.fail())
	{
		std::cout << INDENT << "You have failed the first challenge and are eaten by a grue." << std::endl;
	}
	else
	{
		std::cout << INDENT << "You entered: " << height << std::endl;
	}

	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	std::cout << INDENT << "What is the first letter of your name?" << std::endl;

	std::cin >> firstLetterOfName;

	if (std::cin.fail() || !isalpha(firstLetterOfName))
	{
		std::cout << INDENT << "You have failed the second challenge and are eaten by a grue." << std::endl;
	}
	else
	{
		std::cout << INDENT << "You enetered: " << firstLetterOfName << std::endl;
	}
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	if (firstLetterOfName != 0) 
	{
		avatarHP = (float)height / (firstLetterOfName * 0.02f);
	}
	else
	{
		avatarHP = 0;
	}

	std::cout << INDENT << "Using a complex deterministic algorithm, it has been "
		"caculated that you have " << avatarHP << " hit point(s)." << std::endl;
		
	std::cout << std::endl << INDENT << "Press 'Enter' to exit the program." << std::endl;
	std::cin.get();
	return;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
