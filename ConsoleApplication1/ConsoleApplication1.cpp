// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <random>
#include <time.h>

const char* CSI = "\x1b["; 
const char* TITLE = "\x1b[5;20H";
const char* INDENT = "\t";
const char* YELLOW = "\x1b[93m"; 
const char* MAGENTA = "\x1b[95m"; 
const char* RESET_COLOR = "\x1b[0m"; 
const char* SAVE_CURSOR_POS = "\x1b[s"; 
const char* RESTORE_CURSOR_POS = "\x1b[u";

const char* RED = "\x1b[91m"; 
const char* BLUE = "\x1b[94m"; 
const char* WHITE = "\x1b[97m"; 
const char* GREEN = "\x1b[92m";

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
	//Set output mode to handle virtual terminal sequences
	DWORD dwMode = 0;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	const int EMPTY = 0;
	const int ENEMY = 1;
	const int TREASURE = 2;
	const int FOOD = 3;
	const int ENTRANCE = 4;
	const int EXIT = 5;

	const int MAX_RANDOM_TYPE = FOOD + 1;

	const int MAZE_WIDTH = 10;
	const int MAZE_HEIGHT = 6;

	const int INDENT_X = 5;
	const int ROOM_DESC_Y = 8;
	const int MAP_Y = 13;
	const int PLAYER_INPUT_X = 30;
	const int PLAYER_INPUT_Y = 11;

	const int WEST = 4;
	const int EAST = 6;
	const int NORTH = 8;
	const int SOUTH = 2;

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
	//set the entrance and exit of the maze
	rooms[0][0] = ENTRANCE;
	rooms[MAZE_HEIGHT - 1][MAZE_WIDTH - 1] = EXIT;


	system("cls");

	std::cout << TITLE << MAGENTA << "Welcome to ZORP!" << RESET_COLOR << std::endl;
	std::cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << std::endl;
	std::cout << INDENT << "It is definitely not related to any other text-based adventure game." << std::endl << std::endl;

	//std::cout << INDENT << "First, some questions..." << std::endl;

	//fill the arrays with random room types
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			int type = rand() % (MAX_RANDOM_TYPE * 2);
			if (type < MAX_RANDOM_TYPE)
				rooms[y][x] = type;
			else
				rooms[y][x] = EMPTY;
		}
	}

	//output the map
	std::cout << CSI << MAP_Y << ";" << 0 << "H";
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		std::cout << INDENT;
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			switch (rooms[y][x])
			{
			case EMPTY:
				std::cout << "[ " << GREEN << "\xb0" << RESET_COLOR << " ]";
				break;
			case ENEMY:
				std::cout << "[ " << RED << "\x94" << RESET_COLOR << " ]";
				break;
			case TREASURE:
				std::cout << "[ " << YELLOW << "$" << RESET_COLOR << " ]";
				break;
			case FOOD:
				std::cout << "[ " << WHITE << "\xcf" << RESET_COLOR << " ]";
				break;
			case ENTRANCE:
				std::cout << "[ " << WHITE << "\x9d" << RESET_COLOR << " ]";
				break;
			case EXIT:
				std::cout << "[ " << WHITE << "\xFE" << RESET_COLOR << " ]";
				break;
			}

			/*std::cout << "[ " << rooms[y][x] << " ]";*/
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	////save cursor position
	//std::cout << SAVE_CURSOR_POS;
	//std::cout << INDENT << "How tall are you in centimeters?" << INDENT << YELLOW;
	//std::cin >> height;
	//std::cout << RESET_COLOR << std::endl;
	//
	//if (std::cin.fail())
	//{
	//	std::cout << INDENT << "You have failed the first challenge and are eaten by a grue." << std::endl;
	//}
	//else
	//{
	//	std::cout << INDENT << "You entered: " << height << std::endl;
	//}

	//std::cin.clear();
	//std::cin.ignore(std::cin.rdbuf()->in_avail());
	//std::cin.get();

	////move the cursor to the start of the 1st question
	//std::cout << RESTORE_CURSOR_POS;
	////delete the next 3 lines of text
	//std::cout << CSI << "3M";
	////insert 3 lines (so map stays in the same place)
	//std::cout << CSI << "3L";

	//std::cout << INDENT << "What is the first letter of your name?" << INDENT << YELLOW;

	//std::cin.clear();
	//std::cin.ignore(std::cin.rdbuf()->in_avail());
	//std::cin >> firstLetterOfName;
	//std::cout << RESET_COLOR << std::endl;

	//if (std::cin.fail() || !isalpha(firstLetterOfName))
	//{
	//	std::cout << INDENT << "You have failed the second challenge and are eaten by a grue." << std::endl;
	//}
	//else
	//{
	//	std::cout << INDENT << "You enetered: " << firstLetterOfName << std::endl;
	//}

	//std::cin.clear();
	//std::cin.ignore(std::cin.rdbuf()->in_avail());
	//std::cin.get();

	////move the cursor to the start of the 1st question
	//std::cout << RESTORE_CURSOR_POS;
	//std::cout << CSI << "A";		//cursor up 1
	//std::cout << CSI << "4M" << CSI << "4L";		//delete the next 4 lines of text

	//if (firstLetterOfName != 0) 
	//{
	//	avatarHP = (float)height / (firstLetterOfName * 0.02f);
	//}
	//else
	//{
	//	avatarHP = 0;
	//}

	//std::cout << INDENT << "Using a complex deterministic algorithm, it has been "
	//	"caculated that you have " << avatarHP << " hit point(s)." << std::endl;
		
	std::cout << std::endl << INDENT << "Press 'Enter' to exit the program.";

	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
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
