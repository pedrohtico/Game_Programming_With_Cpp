//  MADE AS A LESSON FOR "GAME PROGRAMMING IN C++: CREATING 3D GAMES" BOOK, CHAPTER 3
//  BY PEDRO HENRIQUE FERREIRA DOS SANTOS
//  25 / 04 / 2021


#include "Game.h"

int main(int argc, char** argv)
{	
	Game *game = new Game();

	bool success = game->Initialize();
	if (success)
		game->RunLoop();

	game->Shutdown();

	return 0;
}
