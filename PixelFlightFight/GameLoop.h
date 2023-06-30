#pragma once
#include "Scroll.h"
#include "Button.h"

// 循环单例类
class GameLoop
{
	int flag;					// 所处界面编号
	//bool keyDown[KEY_COUNT];	// 按键的按下状态
	GameLoop();
public:
	~GameLoop();
	static GameLoop& GetInstance();	// 返回单例
	void Run();						// 开始循环
	void MainMenuLoop();		// 主界面
	void SelectLevelLoop();		// 选关界面	
	void PlaneBattleLoop();		// 飞机战斗界面
	void PlaneWorkshopLoop();	// 飞机工坊界面
	void InstructionsLoop();	// 操作说明界面

	void LevelSetUp();			// 战斗初始化
	void BattleMenuLoop();		// 战斗菜单弹出界面
	void BattleDefeatLoop();	// 战斗失败弹出界面
	void BattleVictoryLoop();	// 战斗胜利弹出界面



	//void TestLoop();	// 测试界面
};


