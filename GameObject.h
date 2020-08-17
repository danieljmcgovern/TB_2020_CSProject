

#ifndef GAMEOBJECT_INCLUDED
#define GAMEOBJECT_INCLUDED

class Grid : public Game
{
public:
	Grid();	
	void drawDungeon();				//constructs the walls of the dungeon on the grid (randomized)	
	char getGrid(int, int);			//return the character associated with the position passed in
	void setGrid(int, int, char);	//x position, y position, character in that x,y position	
	char grid[70][18];				//array of chars that makes up the "board" of the game
	int x_pos, y_pos;				//keeps track of the object's position in the grid

};

class Player : public Grid
{
public:
	Player();
	void initializePlayer(char);	//randomly place the player on the board at start of game
	void movePlayer(char);			

	
};

#endif