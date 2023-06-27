#pragma once
#include "Globals.h"

// ѭ��������
class GameLoop
{
	int flag;					// ����������
	bool keyDown[KEY_COUNT];	// �����İ���״̬

	GameLoop();
public:
	~GameLoop();
	static GameLoop& GetInstance();	// ���ص���
	void Run();						// ��ʼѭ��

private:
	void MainMenuLoop();		// ������
	void SelectLevelLoop();		// ѡ�ؽ���
	void PlaneWorkshopLoop();	// �ɻ���������
	void PlaneBattleLoop();		// �ɻ�ս������

	void BattleMenuLoop();		// ս���˵���������
	void BattleDefeatLoop();	// ս��ʧ�ܵ�������
	void BattleVictoryLoop();	// ս��ʤ����������
};