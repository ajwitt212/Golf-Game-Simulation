#include "GolfCourse.h"
#include "GolfHole.h"
#include "Game.h"
#include "Player.h"
#include "Util.h"
#include <iostream>

//constructors

GolfCourse::GolfCourse(Game* g)
{
	game = g;
	roundScore = 0;
	currentHole = new GolfHole(this);
	holeNum = 1;
}

//mutators

void GolfCourse::playHole() 
{
	bool holeFinished{ false };
	while (!holeFinished)
	{
		holeFinished = currentHole->takeTurn();
	}
}

void GolfCourse::nextHole()  
{
	roundScore += currentHole->getHoleScore() - currentHole->getPar();  //stores hole score
	
	clearScreen();
	currentHole->display();

	std::cout << "-------------------------------" << std::endl;
	std::cout << "Hole " << holeNum << " completed!" << std::endl;
	std::cout << "-------------------------------" << std::endl;
	if (currentHole->getHoleScore() == 1)  //hole in one
		std::cout << "A HOLE IN ONE!!!!!" << std::endl;
	else if (currentHole->getHoleScore() - currentHole->getPar() == -2)  //eagle
		std::cout << "Amazing! you scored an EAGLE!!" << std::endl;
	else if (currentHole->getHoleScore() - currentHole->getPar() == -1) //birdie
		std::cout << "Great hole, you got a birdie!" << std::endl;
	else if (currentHole->getHoleScore() - currentHole->getPar() == 0)  //par
		std::cout << "Nice job, you got a Par." << std::endl;
	else if (currentHole->getHoleScore() - currentHole->getPar() == 1) //bogey
		std::cout << "Oops, you scored a bogey, still time to turn it around" << std::endl;
	else if (currentHole->getHoleScore() - currentHole->getPar() >= 2)  //double bogey or worse
		std::cout << "Better luck next hole" << std::endl;
	std::cout << "-------------------------------" << std::endl;

	enterToContinue();

	delete currentHole;  //deletes hole
	weather.newWindSpeed();  //changes wind
	holeNum++;
	currentHole = new GolfHole(this);  //creates new hole
}

void GolfCourse::finishRound()  
{
	clearScreen();
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "Congrats! Round Completed!" << std::endl;
	std::cout << "----------------------------------------" << std::endl;

	enterToContinue();

	roundScore += currentHole->getHoleScore() - currentHole->getPar();  //stores hole score
	game->getPlayer(game->getCurrentPlayer())->addGolfRound(roundScore);  //stores roundScore
	delete currentHole;
	holeNum++;
}
