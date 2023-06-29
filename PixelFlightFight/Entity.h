#pragma once
#include "Globals.h"
#include "Scroll.h"


class Scroll;
//class PlaneTemplate;



//单个像素,无核心坐标
class Block
{
protected:
	InsId blockID;		//每个像素一个
public:
	Block();
	~Block();
	long long getId();			//get
	void setId(long long id);	//set
};


//实体，有绝对坐标
class Bullet : public Block
{
public:
	EntityType entityType;//实体类型   _EntityBullet, _EntityEnemy, _EntityPlayer
	Coordinate core;	// 核心的绝对坐标
	Speed autoSpeed;	// 固有速度
	std::vector<Coordinate> spriteMap;	// 实体拥有的像素（对与核心的相对坐标）

	int tileCountMax;	// 拥有的像素上限
	int tileCount;		// 剩余的像素

	Bullet();
	Bullet(Coordinate pos);
	Bullet(Coordinate pos, std::unordered_map<Coordinate, COLORREF> spriteMap);
	~Bullet();

	void Move();			// 惯性移动
	void RenderToScroll();		// 将 Bullet 依据计算后的坐标渲染到 scrollMap，注意 SCROLL_X 的限制
	/************************重中之重!**********************************/
	void CollisionDetection();	// 碰撞检测，移动后需要进行碰撞检测
	/******************************************************************/
	void Resource();			//释放
	//void SetPlaneTemplate(PlaneTemplate pt);
//
//};
//
//class Plane : public Bullet
//{
//protected:
//	std::vector<Coordinate> core;	// 哪些是核心像素
//public:
//	Plane();
//	Plane(Coordinate pos, std::unordered_map<Coordinate, COLORREF> spriteMap);
//	~Plane();
//	void Destroy(Coordinate pos);			// 被破坏一个像素
//	void Fracture();						// BFS 递归判断哪些像素没有和核心像素连通存进 vector，遍历删掉
//	void setCore(std::vector<Coordinate> core);	//设置核心部位
//};
//
//class PlayerPlane : public Plane
//{
//public:
//	PlayerPlane();
//	PlayerPlane(Coordinate pos, std::unordered_map<Coordinate, COLORREF> spriteMap);
//	~PlayerPlane();
//
//	void ManualMove(Speed speed);	// 受控移动
};