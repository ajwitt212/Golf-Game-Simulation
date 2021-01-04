#pragma once
#include "Player.h"
#include "GolfCourse.h"
#include <string>

class Game
{
public:
	//constructors
	Game();
	//destructors
	~Game();
	//accessors
	Player* getPlayer(int playerNum);
	int getCurrentPlayer() const { return currentPlayer; }
	//mutators
	void play();  //executes game operations

private:
	Player* players[3];
	int numPlayers;
	int currentPlayer;
	GolfCourse* course;

	//helper functions
	void playRound();  //executes playing of golf round
	bool createPlayer();  //intakes info and calls function to validate creating player
	bool removePlayer();  //intakes info and calls function to validate deleting player
	void displaySaves();
	void displayRules();
	void intakeSaveInput(int& saveNumber, bool isAddingPlayer);  //validates input for save number
	void menu1(char& input);  //displays and intakes input for menu 1
	void menu2(char& input);  //displays and intakes input for menu 2
	void displayPlayerStats();
	void intakePlayerInfo(std::string& name);
	void displayPlayerHandicap(int saveNum) const;
};