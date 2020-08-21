

#ifndef GAMEOBJECT_INCLUDED
#define GAMEOBJECT_INCLUDED

class Grid : public Game
{
public:
	Grid();	
	void initializeGrid();			//initialized grid to null values
	void drawDungeon();				//constructs the walls of the dungeon on the grid (randomized)	
	char getGrid(int, int);			//return the character (char) associated with the position passed in
	void setGrid(int, int, char);	//x position, y position, character (char) in that x,y position	
	
	char grid[70][18];				//array of chars that makes up the "board" of the game

};

class Character
{
public:
	Character();
	void initializeCharacter(Grid*);	//randomly place a character (player, goblin, weapon, etc) on the board at start of game

	char icon;							//how the character object is displayed on the grid (eg Player is '@')
	int x_pos, y_pos;					//keeps track of the object's position in the grid
};

class Player : public Character
{
public:
	Player(Grid*);						//player constructor takes argument: pointer to Grid object, allows for manipulation of grid array within player class functions
	void movePlayer(char, Grid*);		//char argument is for captured keystrokes indicating which direction player is being directed to move		
};

class Goblin : public Character
{
public:
	Goblin(Grid*);
	void moveGoblin(Grid*);			//random movmement of Goblin
};

#endif