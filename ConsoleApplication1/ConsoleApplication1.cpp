// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <random>
#include <time.h>
using namespace std;

const char* CSI = "\x1b["; 
const char* TITLE = "\x1b[5;20H";
const char* INDENT = "\t";
const char* YELLOW = "\x1b[93m"; 
const char* MAGENTA = "\x1b[95m"; 
const char* RESET_COLOR = "\x1b[0m"; 

const char* RED = "\x1b[91m"; 
const char* BLUE = "\x1b[94m"; 
const char* WHITE = "\x1b[97m"; 
const char* GREEN = "\x1b[92m";

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
const int MOVEMENT_DESC_Y = 9;
const int MAP_Y = 13;

const char* EXTRA_OUTPUT_POS = "\x1b[25;6H";
const int PLAYER_INPUT_X = 30;
const int PLAYER_INPUT_Y = 23;

const int WEST = 4;
const int EAST = 6;
const int NORTH = 8;
const int SOUTH = 2;

const int LOOK = 9;
const int FIGHT = 10;

struct Point2D
{
	int x;
	int y;
};

bool enableVirtualTerminal()
{
	//Set output mode to handle virtual terminal sequences
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
	{
		return false;
	}

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hOut, dwMode))
	{
		return false;
	}
	return true;
}

void initialize(int map[MAZE_HEIGHT][MAZE_WIDTH])
{
	srand(time(nullptr));

	//fill the arrays with random room types
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			int type = rand() % (MAX_RANDOM_TYPE * 2);
			if (type < MAX_RANDOM_TYPE)
				map[y][x] = type;
			else
				map[y][x] = EMPTY;
		}
	}

	//set the entrance and exit of the maze
	map[0][0] = ENTRANCE;
	map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1] = EXIT;
}

void drawWelcomeMessage()
{
	cout << TITLE << MAGENTA << "Welcome to ZORP!" << RESET_COLOR << endl;
	cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << endl;
	cout << INDENT << "It is definitely not related to any other text-based adventure game." << endl << endl;
}

void drawRoom(int map[MAZE_HEIGHT][MAZE_WIDTH], Point2D position)
{
	//find the console output position
	int outX = INDENT_X + (6 * position.x) + 3;
	int outY = MAP_Y + position.y;

	//jump to the correct location
	cout << CSI << outY << ";" << outX << "H";

	//draw the room
	switch (map[position.y][position.x])

	{
	case EMPTY:
		std::cout << "[ " << GREEN << "\xb0" << RESET_COLOR << " ] ";
		break;
	case ENEMY:
		std::cout << "[ " << RED << "\x94" << RESET_COLOR << " ] ";
		break;
	case TREASURE:
		std::cout << "[ " << YELLOW << "$" << RESET_COLOR << " ] ";
		break;
	case FOOD:
		std::cout << "[ " << WHITE << "\xcf" << RESET_COLOR << " ] ";
		break;
	case ENTRANCE:
		std::cout << "[ " << WHITE << "\x9d" << RESET_COLOR << " ] ";
		break;
	case EXIT:
		std::cout << "[ " << WHITE << "\xFE" << RESET_COLOR << " ] ";
		break;
	}
}

void drawMap(int map[MAZE_HEIGHT][MAZE_WIDTH])
{
	Point2D position = { 0,0 };

	//reset draw colors
	cout << RESET_COLOR;
	for (position.y = 0; position.y < MAZE_HEIGHT; position.y++)
	{
		cout << INDENT;
		for (position.x = 0; position.x < MAZE_WIDTH; position.x++)
		{
			drawRoom(map, position);
		}
		cout << endl;
	}
}

void drawRoomDescription(int roomType)
{
	//reset draw colors
	cout << RESET_COLOR;
	//jump to the correct location
	cout << CSI << ROOM_DESC_Y << ";" << 0 << "H";
	//delete 4lines and insert 4 empty lines
	cout << CSI << "4M" << CSI << "4L" << endl;

	//write description of current room
	switch (roomType)
	{
	case EMPTY:
		cout << INDENT << "You are in an empty meadow. There is nothing of note here." << endl;
		break;
	case ENEMY:
		cout << INDENT << "BEWARE. An enemy is approaching." << std::endl;
		break;
	case TREASURE:
		cout << INDENT << "Your journey has been rewarded. You have found some treasure." << std::endl;
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

void drawPlayer(Point2D position)
{
	Point2D outPos = { INDENT_X + (6 * position.x) + 3,
	MAP_Y + position.y };

	//draw the player's positioni on the map
	//move cursor to map pos and delete character at current position
	cout << CSI << outPos.y << ";" << outPos.x << "H";
	cout << MAGENTA << "\x81" << RESET_COLOR;
}

void drawValidDirections(Point2D position)
{
	//reset draw colors
	cout << RESET_COLOR;
	//jump to the corect location
	cout << CSI << MOVEMENT_DESC_Y + 1 << ";" << 0 << "H";
	cout << INDENT << "You can see paths leading to the " <<
		((position.x > 0) ? "west, " : "") <<
		((position.x < MAZE_WIDTH - 1) ? "east, " : "") <<
		((position.y > 0) ? "north, " : "") <<
		((position.y < MAZE_HEIGHT - 1) ? "south, " : "") << std::endl;
}

int getMovementDirection()
{
	//jump to the correct location
	cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	cout << INDENT << "Where to now?";

	int direction;
	//move cursor to position for player to enter input
	cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;

	//clear the input buffer, ready for player input
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	cin >> direction;
	cout << RESET_COLOR;

	if (cin.fail())
		return 0;

	return direction;
}

int getCommand()
{
	//fo now, we can't read commands longer than 50 characters
	char input[50] = "\0";

	//jump to correct location 
	cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	//Clear existing text
	cout << CSI << "4M";

	cout << INDENT << "Enter a command.";
	//move cursor to position for player to enter input
	cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;

	//clear the input buffer, ready for player input
	cin.clear();
	cin.ignore(std::cin.rdbuf()->in_avail());

	cin >> input;
	cout << RESET_COLOR;

	bool bMove = false;
		while (input)
		{
			if (strcmp(input, "move") == 0)
			{
				bMove = true;
			}
			else if (bMove == true)
			{
				if (strcmp(input, "north") == 0)
					return NORTH;
				if (strcmp(input, "south") == 0)
					return SOUTH;
				if (strcmp(input, "east") == 0)
					return EAST;
				if (strcmp(input, "west") == 0)
					return WEST;
			}

			if (strcmp(input, "look") == 0)
				return LOOK;
			if (strcmp(input, "fight") == 0)
				return FIGHT;

			char next = cin.peek();
			if (next == '\n' || next == EOF)
				break;
			cin >> input;
		}
		return 0;
}

void main()
{
	//Set output mode to handle virtual terminal sequences
	DWORD dwMode = 0;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);    

	int height = 0;
	char firstLetterOfName = 0;
	int avatarHP = 0;

	//Creates 2D array
	int rooms[MAZE_HEIGHT][MAZE_WIDTH];

	bool gameOver = false;
	Point2D player = { 0,0 };

	if (enableVirtualTerminal() == false)
	{
		cout << "The virtual terminal processing mode cout not be activated." << endl;
		cout << "Press 'Enter' to exit." << endl;
		cin.get();
		return;
	}

	initialize(rooms);

	drawWelcomeMessage();

	//output the map
	drawMap(rooms);

	//game loop
	while (!gameOver)
	{
		drawRoomDescription(rooms[player.y][player.x]);

		drawPlayer(player);

		if (rooms[player.x][player.y] == EXIT)
		{
			gameOver = true;
			continue;
		}
		
		//list the directions the player can take
		drawValidDirections(player);
		
		int command = getCommand();

		drawRoom(rooms, player);

		switch (command)
		{
		case EAST:
			if (player.x < MAZE_WIDTH - 1)
				player.x++;
			break;
		case WEST:
			if (player.x > 0)
				player.x--;
			break;
		case NORTH:
			if (player.y > 0)
				player.y--;
			break;
		case SOUTH:
			if (player.y < MAZE_HEIGHT - 1)
				player.y++;
			break;
		case FIGHT:
			drawPlayer(player);
			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You coud try to fight, but you don't have a weapon." << endl;
			cout << INDENT << "Press 'Enter' to continue.";
			cin.clear();
			cin.ignore(std::cin.rdbuf()->in_avail());
			cin.get();
			break;
		case LOOK:
			drawPlayer(player);
			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning.";
			cin.clear();
			cin.ignore(std::cin.rdbuf()->in_avail());
			cin.get();
		default:
			//do nothing, go back to the top of the loop and ask again
			break;
		}		
	}//end of game loop
		
	//jump to the correct location
	cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	std::cout << std::endl << INDENT << "Press 'Enter' to exit the program.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();	
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
