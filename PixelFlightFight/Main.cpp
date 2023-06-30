#include "Globals.h"
#include "GameLoop.h"
#include "Entity.h"

int main()
{
	//setaspectratio(10,10);
	//initgraph(WINDOWS_X, WINDOWS_Y);
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//创建窗口并显示控制台; // 初始化图形窗口大小为800*600像素
	GameLoop gameLoop = GameLoop::GetInstance();
	gameLoop.Run();
	//gameLoop.BattleVictoryLoop();	
	//gameLoop.PlaneWorkshopLoop();
	closegraph();
	return 0;
}