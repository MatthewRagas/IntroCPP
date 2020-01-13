#include "pch.h"
#include "Game.h"
#include <iostream> 
#include <windows.h> 
#include <random> 
#include <time.h>
using namespace std;

Game::Game()
{
	m_gameOver = false;
}


Game::~Game()
{
}

bool Game::startup()
{
	if (enableVirtualTerminal() == false)
	{
		cout << "The virtual terminal processing mode could not be activated." << endl;
		cout << "Press'Enter' to exit." << endl;
		cin.get();
		return false;
	}

	initializeMap();

	m_player.setposition(Point2D{ 0,0 });

	drawWelcomeMessage();

	return true;
}

bool Game::isGameOver()
{
	return m_gameOver;
}

bool Game::enableVirtualTerminal()
{
	//set output mode to handle virtual terminal sequences
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	DWORD dwMode = 0;
	if (!SetConsoleMode(hOut, dwMode))
	{
		return false;
	}
	return true;
}

void Game::initializeMap()
{
	srand(time(nullptr));

	//fill the arrays with random room types
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			int type = rand() % (MAX_RANDOM_TYPE * 2);
			if (type < MAX_RANDOM_TYPE)
				m_map[y][x].setType(type);
			else
				m_map[y][x].setType(EMPTY);
			m_map[y][x].setPosition(Point2D{ x,y });
		}
	}
	//set the entrance and exit of the maze
	m_map[0][0].setType(ENTRANCE);
	m_map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1].setType(EXIT);
}

void Game::drawWelcomeMessage()
{
	cout << TITLE << MAGENTA << "Welcome to ZORP!" << RESET_COLOR << endl;
	cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << endl;
	cout << INDENT << "It is definitely not related to any other text-based adventure game." << endl << endl;
}

void Game::drawMap()
{
	Point2D position = { 0,0 };

	//reset draw colors
	cout << RESET_COLOR;
	for (position.y = 0; position.y < MAZE_HEIGHT; position.y++)
	{
		for (position.x = 0; position.x < MAZE_WIDTH; position.x++)
		{
			m_map[position.y][position.x].draw();
		}
		cout << endl;
	}
}

void Game::drawValidDirections()
{
	Point2D position = m_player.getPosition();

	//reset draw colors
	cout << RESET_COLOR;
	//jump to the correct location
	cout << CSI << MOVEMENT_DESC_Y + 1 << ";" << 0 << "H";
	cout << INDENT << "You can see paths leading to the " <<
		((position.x > 0) ? "west, " : "") <<
		((position.x < MAZE_WIDTH - 1) ? "east, " : "") <<
		((position.y > 0) ? "north, " : "") <<
		((position.y < MAZE_HEIGHT - 1) ? "south, " : "") << endl;
}

int Game::getCommand()
{
	//for now, we can't read command longer than 50 characters
	char input[50] = "\0";
	//jump to the correct location
	cout << CSI << "4M";
	cout << INDENT << "Enter a command.";
	//move cursor to position for player to enter input
	cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;
	//clear the input buffer, ready for player input
	cin.clear(0);
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

void Game::update()
{
	Point2D playerPos = m_player.getPosition();

	if (m_map[playerPos.y][playerPos.x].getType() == EXIT)
	{
		m_gameOver = true;
		return;
	}

	int command = getCommand();

	if (m_player.executeCommand(command))
		return;

	m_map[playerPos.y][playerPos.x].executeCommand(command);
}

void Game::draw()
{
	Point2D playerPos = m_player.getPosition();

	//list the direction the player can take 
	drawValidDirections();

	//draw the description of the current room
	m_map[playerPos.y][playerPos.x].drawDescription();

	//redraw the map
	drawMap();
	//draw the player on the map
	m_player.draw();
}