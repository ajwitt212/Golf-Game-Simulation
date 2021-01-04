# Golf Game Simulation

## What it does
* The program simulates a retro-style golf game. Although it was designed to be played on windows formatted and in color, it can also be played on MacOS in black and white.
* There are three separate player saves that can be added to and deleted. 
Each player has a handicap that is compiled based upon the scores of their previous rounds. 
* Once a player is created and selected the user plays through 3-hole rounds of golf. 
* Each hole is randomly generated. Random factors include starting ball location, hole location, par, number of sandpits, and their locations. 
Although water generation isn't completely random, 34 different types of water are randomly selected from when a hole is generated. 
* The player has a set of 3 clubs: a driver, an iron, and a putter. The distances are six units, four units, and two units respectively. 
The distance of clubs can be buffed or nerfed by golf course conditions such as wind.
* A golf hole is 21 by 21 units wide however the length of the hole varies based upon the par of the hole.
* Screenshot of Game
> ![alt text](https://github.com/ajwitt212/GolfGame/blob/assets/Golf%20Game%20Screenshot.PNG)
## Inspiration
* To prepare for my introductory computer science final during the fall quarter of 2020 I designed a golf game project using classes. 
However, when I finished the design I realized I wanted to build and implement the project. 
I spent my childhood golfing with my father and grandpa and played golf team throughout high school. 
The idea of intertwining two of my passions in a single project encapsulated me so I spent my winter break programming the game. 

## Implementation
- Class Layout
> ![alt text](https://github.com/ajwitt212/GolfGame/blob/assets/GolfGame-1.jpg.jpeg)
- Hole Layout
> ![alt text](https://github.com/ajwitt212/GolfGame/blob/assets/GolfGame-2.jpg.jpeg)
- 3-Row Water
> ![alt text](https://github.com/ajwitt212/GolfGame/blob/assets/GolfGame-3.jpg.jpeg)
- 2-Row Water
> ![alt text](https://github.com/ajwitt212/GolfGame/blob/assets/GolfGame-4.jpg.jpeg)

## Challenges I ran into
* Throughout the program many attributes are dependent on the generation of others. This created a chicken-and-egg problem. Choosing what to generate first required planning and testing.
* While writing the program I realized I had generated the par based on the hole location and hole location based on the par. To decide which to randomize first I looked at the other variables of the golf hole and saw many more were dependent upon the par variable so I randomized that first.
* Another time I ran into this problem was when compiling my program for the first time. Each class had attributes that were dependent upon the generation of other classes. 
To solve this problem I changed the attributes to be pointers to objects and utilized forward declaration.
