#pragma once
#include <random>
#include <windows.h>

//generates random int from min to max inclusive
int randInt(int min, int max);

//clears screen
void clearScreen();

//makes user press enter to continue
void enterToContinue();

//tells user their input was invalid
bool invalidInput();

//changes color of terminal text
void changeColor(int color);