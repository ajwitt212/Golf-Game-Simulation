#pragma once
class GolfCourse;
class Water;
#include <string>

class GolfHole
{
public:
	//constructors
	GolfHole(GolfCourse* c);
	~GolfHole();
	//accessors
	bool isBallAt (int row, int col) const;
	bool isOutOfBounds(int row, int col) const;
	bool isInSand(int row, int col) const;
	bool isInTrees(int row, int col) const;
	char getHoleDirection() const { return holeDirection; }
	int getHoleScore() const { return holeScore; }
	int getPar() const { return par; }
	void display() const;  //displays GolfHole
	//mutators
	bool takeTurn();  //executes one "swing", intakes all info moves ball, alerts players, and adjusts variables
	void moveBall(std::string swingDirection);   //moves ball in swingDirection
	void reverseBall(std::string swingDirection);  //moves ball in opposite direction of swingDirection
	bool incurPenalty(std::string swingDirection);  //handles if ball goes in water or OB

private:
	int par;
	char holeDirection;
	int ball[2];  //array holds x and y coordinate
	int flagStick[2];  //array holds x and y coordinate
	int sandLocations[10][2];  // array of x and y coordinates
	int numSandLocations;
	Water* water;
	GolfCourse* course;
	int holeScore;

	//helpers
	void displayClubsMenu() const;
	void displaySwingDirectionMenu() const;
	void displayUnitsChange(std::string swingDirection) const;  //displays how swinging in each direction affects distance
	void intakeClub(char& club);   //validates input for club
	bool intakeShortSwing(char club, int distance, std::string swingDirection) const;   //validates input for intaking short swing
	void intakeSwingDirection(std::string& swingDirec, char club, int distance);  //validates input for intaking swing direction
	bool intakeSwingFinalize(char club, int distance, std::string swingDirection);  //validates input for intaking the confirmation of swing info
	int calcUnitsChange(std::string swingDirection) const;   //calculates change in distance of ball based on weather and user input
	std::string clubToString(char club) const;  //returns club character as string
	bool isUpWind(std::string swingDirection) const;  //if wind is against you
	bool isDownWind(std::string swingDirection) const;  //if wind is with you
	bool isOppositeDirection(char d1, char d2) const;
	char trueSwingDirection(char swingDirection) const;  //returns cardinal direction of player swing
};