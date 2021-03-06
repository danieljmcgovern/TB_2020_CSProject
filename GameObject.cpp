#include "Game.h"
#include "GameObject.h"
#include "utilities.h"
#include <iostream>
using namespace std;

///////////////////////////CHARACTER class/////////////////////////
Character::Character()
{}

void Character::initializeCharacter(Grid* g)
{
	int random_x, random_y;
	bool found = false;		//if stmt will set to true when it has "found" a location to place object
	while (!found) {
		random_x = rand() % 69 + 1;		//random number between 1 and 69 (0 and 70 already taken up by the walls of the dungeon)
		random_y = rand() % 16 + 1;
		if (g->getGrid(random_x, random_y) == 0) {	//if the random location is empty
			x_pos = random_x;
			y_pos = random_y;
			g->setGrid(x_pos, y_pos, icon);		//set the position of the object in the grid and print the object's icon at that location on the grid														
			found = true;							//exit the while loop
		}
	}
}

void Character::doBattle(Character* combatant1, Character* combatant2)
{
	cout << "Battle!";
}


//////////////////////////PLAYER class////////////////////////////
Player::Player(Grid* g)
{
	icon = '@';
	initializeCharacter(g);
}

void Player::movePlayer(char direction, Grid * g, Character * goblin)
{
	if (direction == ARROW_UP)
		if (g->getGrid(x_pos, y_pos - 1) != '#') {	//check the space player is trying to move to for a wall
			if (g->getGrid(x_pos, y_pos - 1) == 'G')	doBattle(this, goblin);

			//TODO what if... can the player leave something behind ? (i.e. is setting the old pos to ' ' (blank) not a good idea?)
			//line below is problematic: what if there was a weapon the player chose not to pick up? this line makes it disappear...
					//probably some if statemnet will catch that before getting here... maybe
			g->setGrid(x_pos, y_pos, ' ');			//delete the player from old grid space
			y_pos--;						//ARROW_UP means move "up" y one position (which is acutally in the negative y direction)
			g->setGrid(x_pos, y_pos, icon);			//move the player to the new grid space			
		}	
	if (direction == ARROW_DOWN)
		if (g->getGrid(x_pos, y_pos + 1) != '#') {
			if (g->getGrid(x_pos, y_pos + 1) == 'G')	doBattle(this, goblin);
			g->setGrid(x_pos, y_pos, ' ');
			y_pos++;						
			g->setGrid(x_pos, y_pos, icon);
		}
	if (direction == ARROW_LEFT)
		if (g->getGrid(x_pos - 1, y_pos) != '#') {
			if (g->getGrid(x_pos - 1, y_pos) == 'G')	doBattle(this, goblin);
			g->setGrid(x_pos, y_pos, ' ');
			x_pos--;
			g->setGrid(x_pos, y_pos, icon);
		}
	if (direction == ARROW_RIGHT)
		if (g->getGrid(x_pos + 1, y_pos) != '#') {
			if (g->getGrid(x_pos + 1, y_pos) == 'G')	doBattle(this, goblin);
			g->setGrid(x_pos, y_pos, ' ');
			x_pos++;
			g->setGrid(x_pos, y_pos, icon);
		}
}

/////////////////////////GOBLIN class///////////////////////////////
Goblin::Goblin(Grid * g)
{
	icon = 'G';
	initializeCharacter(g);
}

void Goblin::moveGoblin(Grid* g, Character * player)
{
	int random = rand() % 4 + 1;
	if (random == 1) {
		if (g->getGrid(x_pos, y_pos - 1) != '#') {
			if (g->getGrid(x_pos, y_pos - 1) == '@')	doBattle(this, player);
			g->setGrid(x_pos, y_pos, ' ');
			y_pos--;
			g->setGrid(x_pos, y_pos, icon);
		}
	}
	if (random == 2) {
		if (g->getGrid(x_pos, y_pos + 1) != '#') {
			if (g->getGrid(x_pos, y_pos + 1) == '@')	doBattle(this, player);
			g->setGrid(x_pos, y_pos, ' ');
			y_pos++;
			g->setGrid(x_pos, y_pos, icon);
		}
	}
	if (random == 3) {
		if (g->getGrid(x_pos - 1, y_pos) != '#') {
			if (g->getGrid(x_pos - 1, y_pos) == '@')	doBattle(this, player);
			g->setGrid(x_pos, y_pos, ' ');
			x_pos--;
			g->setGrid(x_pos, y_pos, icon);
		}
	}
	if (random == 4) {
		if (g->getGrid(x_pos + 1, y_pos) != '#') {
			if (g->getGrid(x_pos + 1, y_pos) == '@')	doBattle(this, player);
			g->setGrid(x_pos, y_pos, ' ');
			x_pos++;
			g->setGrid(x_pos, y_pos, icon);
		}
	}

}

//////////////////////////////GRID class//////////////////////////////
Grid::Grid()
{
	system("cls");		//otherwise some '#'s are left printed from the last time it ran, and the @ goes right thru them	
	initializeGrid();
	drawDungeon();
}

void Grid::initializeGrid()
{
	for (int i = 0; i < 70; i++)
		for (int j = 0; j < 18; j++)
			grid[i][j] = 0;
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
	//prints random length "middle" segments of dungeon wall
	for (int i = 1; i < 16; i++) {		//loop stops at row 15, leaving row 16 blank, ensuring a passage through the "middle"walls always exists. TODO randomize this passage
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


