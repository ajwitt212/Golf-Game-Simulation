#include "Weather.h"
#include "Game.h"
#include "Util.h"
#include <random>

//constructors

Weather::Weather()
{
    //randomly generates speed of wind
    windSpeed = randInt(0, 30);

    //randomly generates wind direction
    int windDirectionInt = randInt(0, 3);
    switch (windDirectionInt)
    {
    case 0:
        windDirection = 'n';
        break;
    case 1:
        windDirection = 's';
        break;
    case 2:
        windDirection = 'e';
        break;
    case 3:
        windDirection = 'w';
        break;
    }
}

//mutators

void Weather::newWindSpeed()
{
    int windSpeedIncrementBy{ randInt(-5, 5) };
    if (windSpeed - windSpeedIncrementBy <= 0)  //stays in bounds above 0
        windSpeed = 0;
    else if (windSpeed + windSpeedIncrementBy >= 30) //stays in bounds below 30
        windSpeed = 30;
    else
        windSpeed += windSpeedIncrementBy;
}