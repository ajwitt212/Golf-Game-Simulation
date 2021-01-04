#include "Player.h"
#include <vector>

//constructors

Player::Player(std::string n, Game* g)
{
	name = n;
	game = g;
}

//accessors

int Player::calcHandicap() const
{
	int vecSize{ static_cast<int>(scores.size()) };
	if (vecSize == 0)
		return 37; //an illegal handicap that denotes no rounds have been played
	int sum{};
	for (int i = 0; i < vecSize; i++)  //finds average of all scores
		sum += scores[i];
	int handicap{ sum / vecSize };
	if (handicap >= 36)
		return 36;
    return handicap;
}

//mutators

void Player::addGolfRound(int round)
{
	scores.push_back(round);
}
