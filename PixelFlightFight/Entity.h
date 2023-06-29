#pragma once
#include "Globals.h"
#include "Scroll.h"

class Scroll;
//class PlaneTemplate;

//单个像素,无核心坐标
class Block
{
public:
	InsId blockID;//每个像素一个
	Block();
	~Block();
};

//实体，有绝对坐标
class Bullet : public Block
{
public:
	EntityType entityType;//实体类型   _EntityBullet, _EntityEnemy, _EntityPlayer
	Coordinate core;	// 核心的绝对坐标
	Speed autoSpeed;	// 固有速度
	int tileCountMax;	// 拥有的像素上限
	int tileCount;		// 剩余的像素

	Bullet();	//创建子弹
	~Bullet();

	void AutoMove();			// 惯性移动
	//void RenderToScroll();		// 将 Bullet 依据计算后的坐标渲染到 scrollMap，注意 SCROLL_X 的限制
	void CollisionDetection();	// 碰撞检测，移动后需要进行碰撞检测
	void Resource();			//释放

	//virtual void Destroy(Coordinate pos);			// 被破坏一个像素
	virtual void Fracture();						// BFS 递归判断哪些像素没有和核心像素连通存进 vector，遍历删掉
};

class Plane : public Bullet//敌机
{
public:
	Plane();//创建默认飞机
	Plane(Coordinate co);
	~Plane();

	//virtual void Destroy(Coordinate pos);			// 被破坏一个像素
	virtual void Fracture();						// BFS 递归判断哪些像素没有和核心像素连通存进 vector，遍历删掉
};

class PlayerPlane : public Plane//玩家飞机
{
public:
	std::unordered_map<Coordinate, Block> blockMap;	// 实体拥有的像素（对与核心的相对坐标)
	PlayerPlane();//创建默认玩家飞机
	PlayerPlane(std::vector<Coordinate>);//由workshop创建玩家飞机
	~PlayerPlane();

	//virtual void Destroy(Coordinate pos);			// 被破坏一个像素
	virtual void Fracture();						// BFS 递归判断哪些像素没有和核心像素连通存进 vector，遍历删掉
};
