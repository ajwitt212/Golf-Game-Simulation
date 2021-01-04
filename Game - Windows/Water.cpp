#include "Water.h"
#include "GolfHole.h"
#include "Util.h"

//constructors

Water::Water(GolfHole* h)
{
	waters[0] = randInt(0, 12);  //water 1
	waters[1] = randInt(0, 9);  //water 2
	if (h->getPar() != 3)
		waters[2] = randInt(0, 12);  //generate water 3 if hole is par 4 or 5
}

//accessors

bool Water::isInWater(int row, int col) const
{

	//water 1
	int rowHolder{ row };
	bool toTest{ false };

	if (row >= 14 && row <= 16)
	{
		row -= 14;
		if (isIn3RowWater(0, row, col))
			return true;
		row = rowHolder;
	}

	//water 3
	else if (row >= 7 && row <= 9)
	{
		row -= 7;
		if (isIn3RowWater(2, row, col))
			return true;
		row = rowHolder;
	}


	//water 2
	else if (row == 11 || row == 12)
	{
		row -= 11;
		toTest = true;
		if (toTest)
		{
			if (isIn2RowWater(1, row, col))
				return true;
		}
	}
	return false;
}

//helpers

bool Water::isIn3RowWater(int waterNum, int row, int col) const
{
	if (waters[waterNum] == 1)
		return true;
	if (waters[waterNum] == 2)
		if (row != 2)
			return true;
	if (waters[waterNum] == 3)
		if (row != 0)
			return true;
	if (waters[waterNum] == 4)
		if (row == 0)
			return true;
	if (waters[waterNum] == 5)
		if (row == 1)
			return true;
	if (waters[waterNum] == 6)
		if (row == 2)
			return true;
	if (waters[waterNum] == 7)
		if ((row == 0 && col >= 11) || (row == 1 && col >= 6 && col <= 11) || (row == 2 && col <= 6))
			return true;
	if (waters[waterNum] == 8)
		if ((row == 0 && col <= 6) || (row == 1 && col >= 6 && col <= 11) || (row == 2 && col >= 11))
			return true;
	if (waters[waterNum] == 9)
		if ((row == 0 && (col <= 2 || col >= 14)) || (row == 1 && (col <= 4 || col >= 12)) || (row == 2 && (col <= 6 || col >= 10)))
			return true;
	if (waters[waterNum] == 0)
		if ((row == 2 && (col <= 2 || col >= 14)) || (row == 1 && (col <= 4 || col >= 12)) || (row == 0 && (col <= 6 || col >= 10)))
			return true;
	if (waters[waterNum] == 11)
		if (((row == 0) && (col >= 12 || col <= 7)) || ((row == 1) && (col >= 10 || col <= 5)) || ((row == 2) && (col >= 8 || col <= 3)))
			return true;
	if (waters[waterNum] == 12)
		if (((row == 2) && (col >= 12 || col <= 7)) || ((row == 1) && (col >= 10 || col <= 5)) || ((row == 0) && (col >= 8 || col <= 3)))
			return true;
	return false;
}

bool Water::isIn2RowWater(int waterNum, int row, int col) const
{
	if (waters[waterNum] == 1)
		return true;
	if (waters[waterNum] == 2)
		if (row == 1)
			return true;
	if (waters[waterNum] == 3)
		if (row == 0)
			return true;
	if (waters[waterNum] == 4)
		if ((row == 0 && col >= 9) || (row == 1 && col <= 9))
			return true;
	if (waters[waterNum] == 5)
		if ((row == 1 && col >= 9) || (row == 0 && col <= 9))
			return true;
	if (waters[waterNum] == 6)
		if ((row == 0 && (col <= 6 || col >= 12)) || (row == 1 && (col <= 4 || col >= 10)))
			return true;
	if (waters[waterNum] == 7)
		if ((row == 1 && (col <= 6 || col >= 12)) || (row == 0 && (col <= 4 || col >= 10)))
			return true;
	if (waters[waterNum] == 8)
		if ((row == 0 && (col <= 5 || col >= 11)) || (row == 1 && (col <= 4 || col >= 12)))
			return true;
	if (waters[waterNum] == 9)
		if ((row == 1 && (col <= 5 || col >= 11)) || (row == 0 && (col <= 4 || col >= 12)))
			return true;
	return false;
}