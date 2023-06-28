#pragma once
#include "Globals.h"

// ѭ��������
class GameLoop
{
	int flag;					// ����������
	//bool keyDown[KEY_COUNT];	// �����İ���״̬
	GameLoop();
public:
	~GameLoop();
	static GameLoop& GetInstance();	// ���ص���
	void Run();						// ��ʼѭ��
	void MainMenuLoop();		// ������
	void SelectLevelLoop();		// ѡ�ؽ���	
	void PlaneBattleLoop();		// �ɻ�ս������
	void PlaneWorkshopLoop();	// �ɻ���������
	void InstructionsLoop();	// ����˵������   //TODO


	void BattleMenuLoop();		// ս���˵���������
	void BattleDefeatLoop();	// ս��ʧ�ܵ�������
	void BattleVictoryLoop();	// ս��ʤ����������
};
#pragma once
