#include "Game.h"
#include "GameObject.h"
#include "utilities.h"
#include <iostream>
using namespace std;

//////////////////////////PLAYER class////////////////////////////
Player::Player()
{
	initializeObject('@');
}

void Player::movePlayer(char direction)
{
	if (direction == ARROW_UP)
		if (getGrid(x_pos, y_pos - 1) != '#') {	//check the space player is trying to move to for a wall
			//TODO what if... can the player leave something behind ? (i.e. is setting the old pos to ' ' (blank) not a good idea?)
			//line below is problematic: what if there was a weapon the player chose not to pick up? this line makes it disappear...
			setGrid(x_pos, y_pos, ' ');			//delete the player from old grid space
			y_pos--;						//ARROW_UP means move "up" y one position (which is acutally in the negative y direction)
			setGrid(x_pos, y_pos, '@');			//move the player to the new grid space			
		}	
	if (direction == ARROW_DOWN)
		if (getGrid(x_pos, y_pos + 1) != '#') {	
			setGrid(x_pos, y_pos, ' ');			
			y_pos++;						
			setGrid(x_pos, y_pos, '@');	
		}
	if (direction == ARROW_LEFT)
		if (getGrid(x_pos - 1, y_pos) != '#') {
			setGrid(x_pos, y_pos, ' ');
			x_pos--;
			setGrid(x_pos, y_pos, '@');
		}
	if (direction == ARROW_RIGHT)
		if (getGrid(x_pos + 1, y_pos) != '#') {
			setGrid(x_pos, y_pos, ' ');
			x_pos++;
			setGrid(x_pos, y_pos, '@');			
		}
}

//////////////////////////////GRID class//////////////////////////////
Grid::Grid()
{
	system("cls");		//otherwise some #'s are left printed from the last time it ran, and the @ goes right thru them
	drawDungeon();
}

void Grid::initializeObject(char icon)	//argument is object icon ('@' for palyer, 'G' for goblin per game rules)
{
	int random_x, random_y;
	bool found = false;		//if stmt will set to true when it has "found" a location to place object
	while (!found) {
		random_x = rand() % 69 + 1;		//random number between 1 and 69 (0 and 70 already taken up by the walls of the dungeon)
		random_y = rand() % 16 + 1;
		if (getGrid(random_x, random_y) != '#') {	//if the random location is not a wall of the dungeon TODO check for other objects?
			x_pos = random_x;
			y_pos = random_y;
			setGrid(x_pos, y_pos, icon);		//set the position of the object in the grid and print the object's icon at that location on the grid														
			found = true;							//exit the while loop
		}
	}
}

void Grid::setGrid(int x, int y, char c)		//sets grid array and prints corresponding char at that position on the grid
{
	grid[x][y] = c;
	gotoxy(x, y);	
	printf(&c);
}

char Grid::getGrid(int x, int y)
{
	return grid[x][y];
}

void Grid::drawDungeon()
{
	for (int i = 0; i < 70; i++) {		//print the upper and lower boundaries
		setGrid(i, 0, '#');
		setGrid(i, 17, '#');
	}
	for (int i = 0; i < 18; i++) {		//print the left and right boundaries
		setGrid(0, i, '#');
		setGrid(69, i, '#');
	}
	for (int i = 1; i < 16; i++) {		//prints random length "middle" segments of dungeon wall
		int width = 1;						//for loop will printing at width, end at width_plus
		int width_plus = 0;
		while (width_plus < 69) {
			width_plus = width + rand() % 10 + 5;		//length of segment randomized between 5 and 10
			if (width_plus > 69) width_plus = 69;		//stop from printing past edge of dungeon
			for (int j = width; j < width_plus; j++) {
				setGrid(j, i, '#');
			}
			width = width_plus + rand() % 20 + 10;		//length of open space between segments randomized between 10 and 20
		}		
	}	
}


