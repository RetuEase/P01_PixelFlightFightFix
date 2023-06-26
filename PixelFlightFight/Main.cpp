#include "Globals.h"
#include "GameLoop.h"

int main()
{
	initgraph(WINDOWS_X, WINDOWS_Y);

	GameLoop gameLoop = GameLoop::GetInstance();
	gameLoop.Run();

	closegraph();
	return 0;
}