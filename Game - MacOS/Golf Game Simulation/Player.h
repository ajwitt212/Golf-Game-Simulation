#pragma once
class Game;
#include <string>
#include <vector>

class Player
{
public:
	//constructors
	Player(std::string n, Game* g);
	//accessors
	std::string getName() const { return name; }
	std::vector<int> getHandicap() const { return scores; }
	int calcHandicap() const;
	//mutators
	void addGolfRound(int round);

private:
	std::string name;
	std::vector<int> scores;
	Game* game;
};
