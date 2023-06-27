#pragma once
#include <vector>
#include <unordered_map>
#include <graphics.h>

#include "Globals.h"

using InsId = int;

// 坐标结构
struct Vector2
{
	int x, y;

	Vector2()
		:x(0), y(0) {}

	Vector2(int x, int y)
		:x(x), y(y) {}
};

using Coordinate = Vector2;	// 坐标 (x,y)
using Speed = Vector2;		// 速度方向 (x,y)

// 循环单例类
class GameLoop
{
	int flag;					// 所处界面编号
	bool keyDown[KEY_COUNT];	// 按键的按下状态
	GameLoop();

public:
	~GameLoop();
	static GameLoop& GetInstance();	// 返回单例
	void Run();						// 开始循环

private:
	void MainMenuLoop();		// 主界面
	void SelectLevelLoop();		// 选关界面
	void PlaneWorkshopLoop();	// 飞机工坊界面
	void PlaneBattleLoop();		// 飞机战斗界面

	void BattleMenuLoop();		// 战斗菜单弹出界面
	void BattleDefeatLoop();	// 战斗失败弹出界面
	void BattleVictoryLoop();	// 战斗胜利弹出界面
};

/* 其他界面 */
class Label
{
protected:
	union LabelContainer
	{
		IMAGE image;
		LPCTSTR text;
	};
	Coordinate pos;			// 左上角的坐标
	LabelContainer container;
public:
	Label();
	Label(IMAGE image);
	Label(LPCTSTR text);
	~Label();
	Coordinate getPos();	// 获取 pos
	void RenderToWindows();	// 渲染到窗口
};

class Button : public Label
{
	int (*FuncPtr)();
public:
	Button(int (*FuncPtr)());	// 传入点击按钮时的回调函数
	Button(IMAGE image, int (*FuncPtr)());
	Button(LPCTSTR text, int (*FuncPtr)());
	~Button();					// 清理函数指针
	bool On(Coordinate pos);	// 传入鼠标坐标，返回是否在这个按钮上
	int Click();				// 检测到鼠标在这个按钮上点击时调用
};

/* 飞机战斗界面 */

// 战斗卷轴类（卷轴知晓关于战斗的一切）
class Scroll
{
protected:
	struct ScrollTile
	{
		std::vector<InsId> tileContainer;	// 这一像素包含了些什么实体 id
	};
	std::unordered_map<Coordinate, ScrollTile> scrollMap;	// 坐标对应的信息
	std::unordered_map<InsId, Bullet> instanceRepo;			// 存在实体的仓库
public:
	Scroll();
	~Scroll();
};

// 结算绘图的单位
class Sprite
{
protected:
	std::unordered_map<Coordinate, COLORREF> spriteMap;		// 拥有的像素
public:
	Sprite();
	Sprite(Coordinate pos);
	void RenderToWindows();
};

// 结算移动时的单位
class Bullet : public Sprite
{
protected:
	int type;
	InsId id;
	Speed autoSpeed;			// 惯性速度
public:
	Bullet();
	Bullet(Coordinate pos);
	void AutoMove();			// 惯性移动
	void CollisionDetection();	// 碰撞检测
};

class Plane : public Bullet
{
public:
	Plane();
	Plane(Coordinate pos);
};

class PlayerPlane : public Plane
{
public:
	void ManualMove(Speed speed);	// 临时速度（只有当受到控制时产生的速度）
};