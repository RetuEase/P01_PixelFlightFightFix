#include "Globals.h"
#include "GameLoop.h"
#include "Entity.h"

int main()
{
	//setaspectratio(10,10);
	//initgraph(WINDOWS_X, WINDOWS_Y);

	GameLoop gameLoop = GameLoop::GetInstance();
	gameLoop.Run();

	closegraph();
	return 0;
}