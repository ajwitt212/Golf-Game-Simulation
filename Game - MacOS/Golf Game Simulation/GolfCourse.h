#pragma once
#include "Weather.h"
#include "Player.h"
class GolfHole;
class Game;

class GolfCourse
{
public:
	//constructors
	GolfCourse(Game* g);
	//accessors
	Weather getWeather() const { return weather; }
	int getHoleNum() const { return holeNum; }
	int getRoundScore() const { return roundScore; }
	//mutators
	void playHole();  //executes playing of golf hole
	void nextHole();  //deallocates old hole, stores info and create new one
	void finishRound();  //called after final hole completed, stores round data and deallocates memory

private:
	GolfHole* currentHole;
	int holeNum;
	Weather weather;
	int roundScore;
	Game* game;
};