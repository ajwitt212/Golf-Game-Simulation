#include "GolfHole.h"
#include "GolfCourse.h"
#include "Water.h"
#include "Util.h"
#include <iostream>

//constructors

GolfHole::GolfHole(GolfCourse* c)
{
    course = c;

    //generates ball
    int randomCol = randInt(4, 16);
    ball[0] = 19;
    ball[1] = randomCol;

    //randomly chooses par of hole
    par = randInt(3, 5);

    //generates waters
    water = new Water(this);
  
    //generates number of sand pits
    int randomSandLocationNum = randInt(0, 10);

    //creates sand pits in viable locations
    for (int numCreated = 0; numCreated < randomSandLocationNum; numCreated++)
    {
        for (;;)
        {
            int randRow{};
            int randCol{};
 
            //assigns sand locations based on par
            if (par == 3)
            {
                randRow = randInt(13, 19);
                randCol = randInt(1, 19);

            }
            else if (par == 4)
            {
                randRow = randInt(6, 19);
                randCol = randInt(1, 19);
            }
            else if (par == 5)
            {
                randRow = randInt(1, 19);
                randCol = randInt(1, 19);
            }

            //checks sand is in viable location
            if (!(water->isInWater(randRow, randCol)) && !isInSand(randRow, randCol) && (randRow != ball[0] && randCol != ball[1]))
            {
                sandLocations[numCreated][0] = randRow;
                sandLocations[numCreated][1] = randCol;
                numSandLocations++;
                break;
            }
        }
    }

    //randomly assigns hole direction
    int holeDirectionNum = randInt(1, 4);
    if (holeDirectionNum == 1)
        holeDirection = 'n';
    else if (holeDirectionNum == 2)
        holeDirection = 'e';
    else if (holeDirectionNum == 3)
        holeDirection = 's';
    else if (holeDirectionNum == 4)
        holeDirection = 'w';

    //Randomly generates flagstick
    for (;;)
    {
        int randRow{};
        int randCol{};

        if (par == 3)
        {
            randRow = randInt(13, 15);
            randCol = randInt(4, 16);
        }
        else if (par == 4)
        {
            randRow = randInt(6, 12);
            randCol = randInt(4, 16);
        }
        else if (par == 5)
        {
            randRow = randInt(1, 5);
            randCol = randInt(4, 16);
        }
        //checks flagstick is in viable location
        if (!(water->isInWater(randRow, randCol)) && !isInSand(randRow, randCol))
        {
            flagStick[0] = randRow;
            flagStick[1] = randCol;
            break;
        }
    }
}

GolfHole::~GolfHole()
{
    delete water;
}

//accessors

bool GolfHole::isBallAt(int row, int col) const
{
	if (row == ball[0] && col == ball[1])
		return true;
	return false;
}


bool GolfHole::isOutOfBounds(int row, int col) const
{
    if (row > 20 || row < 0 || col > 20 || col < 0)
        return true;
    return false;
}

bool GolfHole::isInSand(int row, int col) const
{
    for (int i = 0; i < numSandLocations; i++)
        if (sandLocations[i][0] == row && sandLocations[i][1] == col)
            return true;
    return false;
}

bool GolfHole::isInTrees(int row, int col) const
{
    if (col <= 1 || col >= 19 || row == 0 || row == 20)
        return true;
    return false;
}

void GolfHole::display() const  
{
    //top menu
    std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "| F - Flagstick | @ - Ball | T - Trees | W - Water | S - Sand | * - Ball in trees or sand |" << std::endl;
    std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "\t\t\t\t\t\t\t\t\t\t " << "Hole Info" << std::endl;
    std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "| Hole Number: " << course->getHoleNum();
    std::cout << " | Par: " << par;
    std::cout << " | Shot Number: " << holeScore + 1;
    std::cout << " | Hole Direction: " << static_cast<char>(toupper(holeDirection));
    std::cout << " | Wind: " << course->getWeather().getWindSpeed() << "mph " << static_cast<char>(toupper(course->getWeather().getWindDirection()));
    std::cout << " | To Par: " << course->getRoundScore() << " |" << std::endl;
	std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
	
    //golf hole
    char hole[21][21];
    for (int row = 0; row < 21; row++)
        for (int col = 0; col < 21; col++)
            hole[row][col] = '^';

    for (int row = 0; row < 21; row++)
    {
        for (int col = 0; col < 21; col++)
        {
            if (isInSand(row, col))
                hole[row][col] = 'S';
            if (isInTrees(row, col))
                hole[row][col] = 'T';
            if (water->isInWater(row, col))
                hole[row][col] = 'W';
            if (row == flagStick[0] && col == flagStick[1])
                hole[row][col] = 'F';
        }
    }

    if (hole[ball[0]][ball[1]] == '^')
        hole[ball[0]][ball[1]] = '@';
    else
        hole[ball[0]][ball[1]] = '*';

    for (int row = 0; row < 21; row++)
    {
        std::cout << "\t\t\t\t\t\t ";
        for (int col = 0; col < 21; col++)
        {
            std::cout << hole[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

//mutators

bool GolfHole::takeTurn()
{
    char club{};
    int distance{};
    std::string swingDirection;

    for (;;)
    {
        //intake clubs
        intakeClub(club);

        //assigns distances
        if (club == 'd')
            distance = 6;
        else if (club == 'i')
            distance = 4;
        else if (club == 'p')
            distance = 2;

        //intakes swing direction
        intakeSwingDirection(swingDirection, club, distance);

        //adjusts distances
        if (club != 'p')
            distance += calcUnitsChange(swingDirection);

        //intakes shorter swing
        if (intakeShortSwing(club, distance, swingDirection))
            distance--;
        
        //finalizes info
        if(intakeSwingFinalize(club, distance, swingDirection))
            break;
    }

    //moves ball and makes checks along way
    for (int spacesMoved = 0; spacesMoved < distance; spacesMoved++)
    {
        moveBall(swingDirection);
        if (ball[0] == flagStick[0] && ball[1] == flagStick[1])  //checks to see if ball enters hole
        {
            holeScore++;
            return true;
        }
        else if (club == 'p' && isInSand(ball[0], ball[1]))  //can't putt through sand
        {
            holeScore++;
            return false;
        }
        else if (isOutOfBounds(ball[0], ball[1]) || (club == 'p' && water->isInWater(ball[0], ball[1]))) //if OB or putts into water
            return incurPenalty(swingDirection);
    }
    if (water->isInWater(ball[0], ball[1]))
        return incurPenalty(swingDirection);
    holeScore++;
    return false;
}

void GolfHole::moveBall(std::string swingDirection) 
{
    if (swingDirection == "ff")
        ball[0] -= 1;
    else if (swingDirection == "fr")
    {
        ball[0] -= 1;
        ball[1] += 1;
    }
    else if (swingDirection == "rr")
        ball[1] += 1;
    else if (swingDirection == "br")
    {
        ball[0] += 1;
        ball[1] += 1;
    }
    else if (swingDirection == "bb")
        ball[0] += 1;
    else if (swingDirection == "bl")
    {
        ball[0] += 1;
        ball[1] -= 1;
    }
    else if (swingDirection == "ll")
        ball[1] -= 1;
    else if (swingDirection == "fl")
    {
        ball[0] -= 1;
        ball[1] -= 1;
    }
}

void GolfHole::reverseBall(std::string swingDirection)
{
    if (swingDirection == "ff")
        ball[0] += 1;
    else if (swingDirection == "fr")
    {
        ball[0] += 1;
        ball[1] -= 1;
    }
    else if (swingDirection == "rr")
        ball[1] -= 1;
    else if (swingDirection == "br")
    {
        ball[0] -= 1;
        ball[1] -= 1;
    }
    else if (swingDirection == "bb")
        ball[0] -= 1;
    else if (swingDirection == "bl")
    {
        ball[0] -= 1;
        ball[1] += 1;
    }
    else if (swingDirection == "ll")
        ball[1] += 1;
    else if (swingDirection == "fl")
    {
        ball[0] += 1;
        ball[1] += 1;
    }
}

bool GolfHole::incurPenalty(std::string swingDirection)  
{
    holeScore += 2;

    bool OB = isOutOfBounds(ball[0], ball[1]);
    if (OB)  //moves ball to better show where it went out
        reverseBall(swingDirection);

    clearScreen();
    display();

    if (OB)
    {
        while (water->isInWater(ball[0], ball[1]))  //moves ball back in event ball went OB over water
            reverseBall(swingDirection);
        std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
        std::cout << "Ball went out of bounds" << std::endl;
    }
    else if (water->isInWater(ball[0], ball[1]))
    {
        while (water->isInWater(ball[0], ball[1]))  //moves ball back after display to show where ball entered water
            reverseBall(swingDirection);
        std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
        std::cout << "Ball went in water" << std::endl;
    }
    enterToContinue();
    return false;
}

//helpers

void GolfHole::displayClubsMenu() const
{
    std::cout << "\t\t\t\t  " << "-----------------------------------------------------" << std::endl;
    std::cout << "\t\t\t\t\t\t\t\t  " << "Clubs and Distances" << std::endl;
    std::cout << "\t\t\t\t  " << "-----------------------------------------------------" << std::endl;
    std::cout << "\t\t\t\t  " << "| Driver: " << 6 << " units ";
    std::cout << "| Iron: " << 4 << " units ";
    std::cout << "| Putter: " << 2 << " units |" << std::endl;
    std::cout << "\t\t\t\t  " << "-----------------------------------------------------" << std::endl << std::endl;
}

void GolfHole::displaySwingDirectionMenu() const
{
    std::cout << "\t\t\t" << "---------------------------------------------------------------------" << std::endl;
    std::cout << "\t\t\t\t\t\t " << "Swing Direction Menu & Change in Distance" << std::endl;
    std::cout << "\t\t\t" << "---------------------------------------------------------------------" << std::endl;
    
    std::cout << "\t\t\t" << "| forward-left: FL |\t\t" << "| forward: FF |\t\t" << "| forward-right: FR |" << std::endl;

    std::cout << "\t\t\t";
    displayUnitsChange("fl");
    std::cout << "\t\t\t\t";
    displayUnitsChange("ff");
    std::cout << "\t\t";
    displayUnitsChange("fr");
    std::cout << "\n\n";


    std::cout << "\t\t\t" << "| left: LL |" << "\t\t\t\t\t\t\t\t\t" << "| right: RR |" << std::endl;
    
    std::cout << "\t\t\t";
    displayUnitsChange("ll");
    std::cout << "\t\t\t\t\t\t\t\t\t";
    displayUnitsChange("rr");
    std::cout << "\n\n";


    std::cout << "\t\t\t" << "| backward-left: BL |\t\t" << "| backward: BB |\t" << "| backward-right: BR |" << std::endl;

    std::cout << "\t\t\t";
    displayUnitsChange("bl");
    std::cout << "\t\t\t\t";
    displayUnitsChange("bb");
    std::cout << "\t\t";
    displayUnitsChange("br");
    std::cout << std::endl;


    std::cout << "\t\t\t" << "----------------------------------------------------------------------" << std::endl << std::endl;
}

void GolfHole::displayUnitsChange(std::string swingDirection) const
{
    std::cout << "| ";

    int unitsChange = calcUnitsChange(swingDirection);

    if (unitsChange == 0)
        std::cout << "no change |";
    else if (unitsChange > 0)
        std::cout << "+" << unitsChange << " units |";
    else if (unitsChange < 0)
        std::cout << unitsChange << " units |";
}

void GolfHole::intakeClub(char& club) 
{
    for (;;)  
    {
        clearScreen();
        display();
        displaySwingDirectionMenu();
        displayClubsMenu();

        std::cout << "Please make a selection (D/I/P): ";
        std::cin >> club;
        club = tolower(club);
        if (club == 'd' && (isInSand(ball[0], ball[1]) || isInTrees(ball[0], ball[1])))  //driver can't be hit out of sand
            std::cout << "Can't hit driver out of the sand or trees" << std::endl;
        else if (club == 'i' || club == 'p' || club == 'd')
            break;
        std::cout << "-----------------------------" << std::endl;
        invalidInput();
    }
}

bool GolfHole::intakeShortSwing(char club, int distance, std::string swingDirection) const 
{
    char input{};
    for (;;)  
    {
        clearScreen();
        display();
        std::cout << "\t\t\t" << "-------------------------------------------------------------------" << std::endl;
        std::cout << "\t\t\t" << "| Selected Club: " << clubToString(club);
        std::cout << " | Swing Direction: " << swingDirection;
        std::cout << " | Distance: " << distance << " units";
        std::cout <<" |" << std::endl;
        std::cout << "\t\t\t" << "-------------------------------------------------------------------" << std::endl << std::endl;

        std::cout << "Would you like to take a shorter swing (distance 1 less)? (y/n): ";
        std::cin >> input;
        input = tolower(input);
        if (input == 'y')
            return true;
        else if (input == 'n')
            return false;
        std::cout << "-----------------------------" << std::endl;
        invalidInput();
    }
}

void GolfHole::intakeSwingDirection(std::string& swingDirec, char club, int distance) 
{
    for (;;)
    {
        clearScreen();
        display();
        std::cout << "\t\t\t\t\t   " << "---------------------------------------------" << std::endl;
        std::cout << "\t\t\t\t\t   " << "| Selected Club: " << clubToString(club);
        std::cout << " | Distance: " << distance << " units";
        std::cout << " |" << std::endl;
        std::cout << "\t\t\t\t\t   " << "---------------------------------------------" << std::endl;
        displaySwingDirectionMenu();

        std::cout << "Please enter the two character swing direction: ";
        std::cin >> swingDirec;
        for (int i = 0; i < 2; i++)
            swingDirec[i] = tolower(swingDirec[i]);
        if (swingDirec.size() == 2)
            if (swingDirec[0] == 'f' || swingDirec[0] == 'r' || swingDirec[0] == 'b' || swingDirec[0] == 'l')
                if (swingDirec[1] == 'f' || swingDirec[1] == 'r' || swingDirec[1] == 'b' || swingDirec[1] == 'l')
                    break;
        std::cout << "-----------------------------" << std::endl;
        invalidInput();
    }
}

bool GolfHole::intakeSwingFinalize(char club, int distance, std::string swingDirection)  
{
    char input{};
    for (int i = 0; i < 2; i++)
        swingDirection[i] = toupper(swingDirection[i]);
    for (;;)  //validates input
    {
        clearScreen();
        display();
        std::cout << "\t\t\t" << "-------------------------------------------------------------------" << std::endl;
        std::cout << "\t\t\t" << "| Selected Club: " << clubToString(club);
        std::cout << " | Swing Direction: " << swingDirection;
        std::cout << " | Distance: " << distance << " units";
        std::cout << " |" << std::endl;
        std::cout << "\t\t\t" << "-------------------------------------------------------------------" << std::endl << std::endl;

        std::cout << "Enter R to re-enter info or S to swing: ";
        std::cin >> input;
        input = tolower(input);
        if (input == 's')
            return true;
        else if (input == 'r')
            return false;
        else
        {
            std::cout << "-----------------------------" << std::endl;
            invalidInput();
        }
    }
}

int GolfHole::calcUnitsChange(std::string swingDirection) const 
{
    int distance{};
    //if its diagonal
    if (swingDirection[0] != swingDirection[1])
        distance--;
    //if the ball is in trees or sand
    if (isInSand(ball[0], ball[1]) || isInTrees(ball[0], ball[1]))
        distance--;
    //if wind is against swingDirection
    if (isUpWind(swingDirection))
        distance--;
    //wind is with swingDirection
    if (isDownWind(swingDirection))
        distance++;
    return distance;
}

std::string GolfHole::clubToString(char club) const  
{
    if (club == 'p')
        return "Putter";
    else if (club == 'i')
        return "Iron";
    return "Driver";
}

bool GolfHole::isUpWind(std::string swingDirection) const  
{
    char windDirection = course->getWeather().getWindDirection();
    char trueSwingDirec = trueSwingDirection(swingDirection[0]);
    if (isOppositeDirection(trueSwingDirec, windDirection) && course->getWeather().getWindSpeed() > 10)
        return true;
    return false;
}

bool GolfHole::isDownWind(std::string swingDirection) const 
{
    char windDirection = course->getWeather().getWindDirection();
    char trueSwingDirec = trueSwingDirection(swingDirection[0]);
    if (trueSwingDirec == windDirection && course->getWeather().getWindSpeed() > 10)
        return true;
    return false;
}

bool GolfHole::isOppositeDirection(char d1, char d2) const //return true if directions are opposite
{
    if (d1 == 's' && d2 == 'n')
        return true;
    if (d1 == 'n' && d2 == 's')
        return true;
    if (d1 == 'e' && d2 == 'w')
        return true;
    if (d1 == 'w' && d2 == 'e')
        return true;
    return false;
}

char GolfHole::trueSwingDirection(char swingDirection) const
{
    if (swingDirection == 'f')   //if swinging forwards swinging in direction of hole
        return holeDirection;
    else if (swingDirection == 'r')  //returns right of hole direction
    {
        if (holeDirection == 'n')
            return 'e';
        else if (holeDirection == 'e')
            return 's';
        else if (holeDirection == 's')
            return 'w';
        else if (holeDirection == 'w')
            return 'n';
    }
    else if (swingDirection == 'l')  //returns left of hole direction
    {
        if (holeDirection == 'n')
            return 'w';
        else if (holeDirection == 'e')
            return 'n';
        else if (holeDirection == 's')
            return 'e';
        else if (holeDirection == 'w')
            return 's';
    }
    else if (swingDirection == 'b')  //returns opposite of hole direction
    {
        if (holeDirection == 'n')
            return 's';
        else if (holeDirection == 'e')
            return 'w';
        else if (holeDirection == 's')
            return 'n';
        else if (holeDirection == 'w')
            return 'e';
    }
    return '\0';
}
