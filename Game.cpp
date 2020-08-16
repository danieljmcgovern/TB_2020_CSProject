// Game.cpp

#include "Game.h"
#include "utilities.h"
#include "GameObject.h"
#include<windows.h>
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
{}
Game::Game()
{}

void Game::gotoxy(int x, int y)		//goes to a particular x,y coordinate on the console
{
		COORD coord = { 0,0 };	
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	
}

void Game::play()
{
	
	
	cout << "Press q to exit game." << endl;

	Grid dungeon;
	Player player;

	while (1)		//moved getCharacter() != q out of while condition to fix bug (double tapping arrow key to move)
	{		
		char key_stroke = getCharacter();
		if (key_stroke == 'q') return;		
		if (key_stroke == ARROW_UP || key_stroke == ARROW_DOWN || key_stroke == ARROW_LEFT || key_stroke == ARROW_RIGHT)
			player.movePlayer(key_stroke);

	}
		

		
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
