#define SDL_MAIN_HANDLED
#include "..\include\Game\Game.h"

int main(int argc, char** argv)
{
	Game app;
	if ( app.Init(
		"Template", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		WINDOW_SIZE_W, WINDOW_SIZE_H, 
		220, 
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED
		)
	)
	app.Run();

	return 0;
}