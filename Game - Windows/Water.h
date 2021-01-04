#pragma once
class GolfHole;

class Water
{
public:
	//constructors
	Water(GolfHole* h);
	//accessors
	bool isInWater(int row, int col) const;

private:
	//attributes
	int waters[3];

	//helpers
	bool isIn3RowWater(int waterNum, int row, int col) const;  //if ball is in a 3 row water, uses waterNum bc of randomization
	bool isIn2RowWater(int waterNum, int row, int col) const;  //if ball is in a 2 row water, uses waterNum bc of randomization
};