#include "Game.h"
#include "Util.h"
#include <iostream>
#include <string>

//constructors

Game::Game()
{
	for (int i = 0; i < 3; i++)
		players[i] = nullptr;
	numPlayers = 0;
}

//destructors

Game::~Game()
{
	for (int i = 0; i < 3; i++)
		delete players[i];
}

//accessors

Player* Game::getPlayer(int playerNum)
{
	return players[playerNum];
}

//mutators

void Game::play()
{
	char input{};
	for (;;)
	{
		menu1(input);

		if (input == 'q')
			break;
		else if (input == 'c')
			createPlayer();
		else if (input == 'd')
			removePlayer();
		else if (input == 'h')
			displayRules();
		else if (input == 's')
		{
			intakeSaveInput(currentPlayer, false);
			if (currentPlayer == 3)  //3 is code for return to menu 1
				continue;
			for (;;)
			{
				menu2(input);
				if (input == 'r')
					break;
				else if (input == 'v')
					displayPlayerStats();
				else if (input == 'p')
					playRound();
			}
		}
	}
	clearScreen();
	std::cout << "-----------------------------" << std::endl;
	std::cout << "Thanks for playing!" << std::endl;
	std::cout << "-----------------------------" << std::endl;
}

void Game::playRound()  
{
	course = new GolfCourse(this);
	while (course->getHoleNum() <= 3)
	{
		course->playHole(); //plays hole
		if (course->getHoleNum() <= 2)  //if not the last hole
			course->nextHole();  //moves to next hole
		else if (course->getHoleNum() == 3)  //if its the last hole
			course->finishRound();  //finishes round
	}
}

bool Game::createPlayer() 
{
	int saveNumber{};
	intakeSaveInput(saveNumber, true);

	if (saveNumber == 3)  //means user wants to return to previous menu
		return false;

	std::string name;
	intakePlayerInfo(name);

	players[saveNumber] = new Player(name, this);
	numPlayers++;

	std::cout << "-----------------------------" << std::endl;
	std::cout << "Player Created!" << std::endl;
	enterToContinue();

	return true;
}

bool Game::removePlayer() 
{
	int saveNumber{};
	intakeSaveInput(saveNumber, false);

	if (saveNumber == 3)  //means user wants to return to previous menu
		return false;

	delete players[saveNumber];
	players[saveNumber] = nullptr;
	numPlayers--;

	std::cout << "Player Deleted!" << std::endl;
	enterToContinue();

	return true;
}

void Game::displaySaves()
{
	std::cout << "-----------------------------" << std::endl;
	if(players[0] == nullptr)
		std::cout << "Save A: Empty" << std::endl;
	else
	{
		std::cout << "Save A: " << players[0]->getName() << ", ";
		displayPlayerHandicap(0);
	}
	if (players[1] == nullptr)
		std::cout << "Save B: Empty" << std::endl;
	else
	{
		std::cout << "Save B: " << players[1]->getName() << ", ";
		displayPlayerHandicap(1);
	}
	if (players[2] == nullptr)
		std::cout << "Save C: Empty" << std::endl;
	else
	{
		std::cout << "Save C: " << players[2]->getName() << ", ";
		displayPlayerHandicap(2);
	}
	std::cout << "-----------------------------" << std::endl;
}

void Game::displayRules()
{
	clearScreen();
	std::cout << "-----------------------------" << std::endl;
	std::cout << "How To Play" << std::endl;
	std::cout << "-----------------------------" << std::endl;
	std::cout << "Rounds are a set of 3 randomly generated golf holes" << std::endl;
	std::cout << "The player uses a set of 3 golf clubs with predefined distances to try to hit the ball in the hole in as few shots as possible" << std::endl;
	std::cout << "Player has option to swing in the cardinal and diagonal directions, swinging diagonally decreases distance of the ball by one" << std::endl;
	std::cout << "Unless using the putter, the distance of the ball is also affected by external factors such as wind and is decreased if the ball is in trees or sand" << std::endl;
	std::cout << "If the ball goes out of bounds or lands in the water it will be moved back on the line of the shot in bounds and will result in a one stroke penalty" << std::endl;
	std::cout << "At end of players turn they will have the opportunity to take a shorter swing and decrease the distance by one unit" << std::endl;
	std::cout << "-----------------------------" << std::endl;
	enterToContinue();
}

void Game::intakeSaveInput(int& saveNumber, bool isAddingPlayer)  
{
	for (;;)
	{
		clearScreen();
		displaySaves();

		std::cout << "Enter R to return to previous menu" << std::endl;
		std::cout << "Otherwise select save (A-C): ";

		char save{};
		std::cin >> save;
		save = tolower(save);
		if (save == 'a')
			saveNumber = 0;
		else if (save == 'b')
			saveNumber = 1;
		else if (save == 'c')
			saveNumber = 2;
		else if (save == 'r')
			saveNumber = 3;
		else
			saveNumber = -1;

		std::cout << "-----------------------------" << std::endl;

		if (saveNumber == 3)  //exits
			break;

		else if (saveNumber == -1)  //checks its a valid input
		{
			std::cout << "Invalid save input" << std::endl;
		}
		
		else if (isAddingPlayer)  //if adding player 
		{
			if (players[saveNumber] == nullptr)  //makes sure nothing is in save location
				break;
			std::cout << "Save location taken" << std::endl;
		}
		else if (!isAddingPlayer)  //if removing player
		{
			if (players[saveNumber] != nullptr)   //makes sure player is in save location
				break;
			std::cout << "No player in save location" << std::endl;
		}
		enterToContinue();
	}
}

void Game::menu1(char& input)  
{
	for (;;)
	{
		clearScreen();

		//menu
		std::cout << "-----------------------------" << std::endl;
		std::cout << "Welcome to the Golf Simulator" << std::endl;
		std::cout << "-----------------------------" << std::endl;
		std::cout << "Create New Player: C" << std::endl;
		std::cout << "Select Player: S" << std::endl;
		std::cout << "Delete Player: D" << std::endl;
		std::cout << "How to Play: H" << std::endl;
		std::cout << "Quit: Q" << std::endl;
		std::cout << "-----------------------------" << std::endl;

		//intaking input
		std::cout << "Selection: ";
		std::cin >> input;
		input = tolower(input);
		if (input == 'q' || input == 'c' || input == 'd' || input == 's' || input == 'h')
			break;
		invalidInput();
	}
}

void Game::menu2(char& input)
{
	for (;;)
	{
		clearScreen();
		//menu
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "Selected Player: " << players[currentPlayer]->getName() << ", ";
		displayPlayerHandicap(currentPlayer);
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "Return To Main Menu: R" << std::endl;
		std::cout << "Play Round: P" << std::endl;
		std::cout << "View Stats: V" << std::endl;
		std::cout << "-----------------------------------" << std::endl;

		//intaking input
		std::cout << "Selection: ";
		std::cin >> input;
		input = tolower(input);
		if (input == 'r' || input == 'p' || input == 'v')
			break;
		else
			invalidInput();
	}
}

void Game::displayPlayerStats()
{
	clearScreen();
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "Player Statistics" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "Name: " << players[currentPlayer]->getName() << std::endl;
	std::cout << "Handicap: ";
	displayPlayerHandicap(currentPlayer);
	std::cout << "Rounds Played: " << players[currentPlayer]->getHandicap().size() << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	enterToContinue();
}

void Game::intakePlayerInfo(std::string& name)
{
	std::cout << "Enter character's name: ";
	std::cin >> name;

}

void Game::displayPlayerHandicap(int saveNum) const
{
	if (players[saveNum]->calcHandicap() == 37)  //37 denotes no rounds have been played
		std::cout << "No Handicap" << std::endl;
	else
		std::cout << players[saveNum]->calcHandicap() << std::endl;
}