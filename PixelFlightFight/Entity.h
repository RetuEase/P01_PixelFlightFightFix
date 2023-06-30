#pragma once
#include "Globals.h"


//单个像素,无核心坐标
class Block
{
public:
	InsId blockID;				//每个像素一个
	Block();
	~Block();
	bool operator==(const Block other) const {
		if (blockID == other.blockID)
			return true;
	}
};

//实体，有绝对坐标
class Bullet : public Block
{
public:
	static std::unordered_map<Coordinate, Bullet> ENEMYMAP;				//敌机map
	static std::unordered_map<Coordinate, Block> PlayerPlaneBlock;		// 玩家飞机拥有的像素（对与核心的相对坐标)
	static std::unordered_map<InsId, std::shared_ptr<Bullet>> AllEntities;			// 所有实体
	static std::vector<InsId> keysToDelete;//待删除的项

	EntityType entityType;//实体类型   _EntityBullet, _EntityEnemy, _EntityPlayer
	Coordinate core;	// 核心的绝对坐标
	Speed autoSpeed;	// 固有速度
	int tileCountMax;	// 拥有的像素上限
	int tileCount;		// 剩余的像素

	Bullet();			//子弹
	Bullet(int i);		//生成子弹
	~Bullet();
	bool AutoMove();						// 惯性移动
	virtual void PlayerMove(Speed speed);	// 主动移动
	void Release();							//移除实体
	virtual void CollisionDetection();		// 碰撞检测，移动后需要进行碰撞检测
	virtual void Fracture();				// BFS 递归判断哪些像素没有和核心像素连通存进 vector，遍历删掉
};



class Plane : public Bullet//敌机
{
public:
	Plane();//创建默认飞机
	Plane(Coordinate co);
	~Plane();
	virtual void PlayerMove(Speed speed)override;	// 主动移动
	virtual void CollisionDetection()override;	 		// 碰撞检测
	virtual void Fracture()override;					// BFS 递归判断哪些像素没有和核心像素连通存进 vector，遍历删掉
};

class PlayerPlane : public Plane//玩家飞机
{
public:

	PlayerPlane();//创建默认玩家飞机
	PlayerPlane(std::vector<Coordinate>);			//由workshop创建玩家飞机
	~PlayerPlane();
	virtual void PlayerMove(Speed speed)override;	// 主动移动
	virtual void CollisionDetection()override;
	virtual void Fracture()override;				// BFS 递归判断哪些像素没有和核心像素连通存进 vector，遍历删掉
};


