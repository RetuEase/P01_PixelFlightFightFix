#include "Globals.h"
#include "GameLoop.h"
#include "Entity.h"

int main()
{
	//setaspectratio(10,10);
	//initgraph(WINDOWS_X, WINDOWS_Y);
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//�������ڲ���ʾ����̨; // ��ʼ��ͼ�δ��ڴ�СΪ800*600����
	GameLoop gameLoop = GameLoop::GetInstance();
	gameLoop.Run();
	//gameLoop.BattleVictoryLoop();	
	//gameLoop.PlaneWorkshopLoop();
	closegraph();
	return 0;
}