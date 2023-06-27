#pragma once
#include "Globals.h"
#include "Scroll.h"

//原来的Instance.h
class Scroll;
// 图形，无绝对坐标
class Sprite
{
protected:
	PlaneId planeId;
	std::unordered_map<Coordinate, COLORREF> spriteMap;	// 图形的形状、拥有的像素（相对参考点的坐标）
public:
	Sprite();
	~Sprite();
	LONGLONG getPlaneId();
	void setPlaneId(long long id);
};

// 实体，有绝对坐标
class Bullet : public Sprite
{
public:
	int type;			// 子弹还是飞机
	InsId insId;		// 实体 ID
	EntityType entityType;//飞机类型

	int tileCountMax;	// 拥有的像素上限
	int tileCount;		// 剩余的像素

	Coordinate pos;		// 参考点处于 Scroll 中的绝对坐标
	Speed autoSpeed;	// 惯性速度

	friend Scroll;
	Bullet();
	Bullet(Coordinate pos);
	Bullet(Coordinate pos, std::unordered_map<Coordinate, COLORREF> spriteMap);
	~Bullet();
	void setInsId(int id);
	int getInsId();
	void sesSpeed(int x, int y);
	Speed getSpeed();

	void AutoMove();			// 惯性移动
	void RenderToScroll();		// 将 Bullet 依据计算后的坐标渲染到 scrollMap，注意 SCROLL_X 的限制
	/************************重中之重!**********************************/
	void CollisionDetection();	// 碰撞检测，移动后需要进行碰撞检测
	/******************************************************************/
	void Resource();
};

class Plane : public Bullet
{
protected:
	std::vector<Coordinate> core;	// 哪些是核心像素
public:
	Plane();
	Plane(Coordinate pos, std::unordered_map<Coordinate, COLORREF> spriteMap);
	~Plane();
	void Destroy(Coordinate pos);			// 被破坏一个像素
	void Fracture();						// BFS 递归判断哪些像素没有和核心像素连通存进 vector，遍历删掉
	void setCore(std::vector<Coordinate> core);	//设置核心部位

};

class PlayerPlane : public Plane
{
public:
	PlayerPlane();
	PlayerPlane(Coordinate pos, std::unordered_map<Coordinate, COLORREF> spriteMap);
	~PlayerPlane();

	void ManualMove(Speed speed);	// 受控移动
};