#include "GameLoop.h"

GameLoop::GameLoop()
{
}

GameLoop::~GameLoop()
{
}

GameLoop& GameLoop::GetInstance()
{
	static GameLoop gameLoop;
	return gameLoop;
}

void GameLoop::Run()
{
	MainMenuLoop();
}

void GameLoop::MainMenuLoop()
{
	while (1)
	{

	}
}

void GameLoop::SelectLevelLoop()
{
	while (1)
	{

	}
}

void GameLoop::PlaneWorkshopLoop()
{
	while (1)
	{

	}
}

void GameLoop::PlaneBattleLoop()
{
	while (1)
	{

	}
}

void GameLoop::BattleMenuLoop()
{
	while (1)
	{

	}
}

void GameLoop::BattleDefeatLoop()
{
	while (1)
	{

	}
}

void GameLoop::BattleVictoryLoop()
{
	while (1)
	{

	}
}
