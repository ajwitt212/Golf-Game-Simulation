#pragma once
class Weather
{
public:
	//constructors
	Weather();
	//accessors
	int getWindSpeed() const { return windSpeed; }
	char getWindDirection() const { return windDirection; }
	//mutators
	void newWindSpeed();  //changes wind by random amount between holes

private:
	int windSpeed;
	char windDirection;
};