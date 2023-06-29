#pragma once
#include "Globals.h"


//��������,�޺�������
class Block
{
public:
	InsId blockID;				//ÿ������һ��
	Block();
	~Block();
	virtual void Resource();	//�Ƴ�ʵ��
	bool operator==(const Block other) const {
		if (blockID == other.blockID)
			return true;
	}
};

//ʵ�壬�о�������
class Bullet : public Block
{
public:
	static std::unordered_map<Coordinate, Bullet> ENEMYMAP;				//�л�map
	static std::unordered_map<Coordinate, Block> PlayerPlaneBlock;		// ��ҷɻ�ӵ�е����أ�������ĵ��������)
	static std::vector<Bullet*> AllEntities;							// ����ʵ��


	EntityType entityType;//ʵ������   _EntityBullet, _EntityEnemy, _EntityPlayer
	Coordinate core;	// ���ĵľ�������
	Speed autoSpeed;	// �����ٶ�
	int tileCountMax;	// ӵ�е���������
	int tileCount;		// ʣ�������

	Bullet();	//�����ӵ�
	~Bullet();

	void AutoMove();						// �����ƶ�
	virtual void PlayerMove(Speed speed);	// �����ƶ�
	virtual void CollisionDetection();		// ��ײ��⣬�ƶ�����Ҫ������ײ���
	void Resource();						//�Ƴ�ʵ��
	virtual void Fracture();				// BFS �ݹ��ж���Щ����û�кͺ���������ͨ��� vector������ɾ��
};



class Plane : public Bullet//�л�
{
public:
	Plane();//����Ĭ�Ϸɻ�
	Plane(Coordinate co);
	~Plane();
	virtual void PlayerMove(Speed speed);		// �����ƶ�
	virtual void CollisionDetection();			// ��ײ���
	virtual void Fracture();					// BFS �ݹ��ж���Щ����û�кͺ���������ͨ��� vector������ɾ��
};

class PlayerPlane : public Plane//��ҷɻ�
{
public:

	PlayerPlane();//����Ĭ����ҷɻ�
	PlayerPlane(std::vector<Coordinate>);			//��workshop������ҷɻ�
	~PlayerPlane();
	virtual void PlayerMove(Speed speed);			// �����ƶ�
	virtual void CollisionDetection();
	virtual void Fracture();						// BFS �ݹ��ж���Щ����û�кͺ���������ͨ��� vector������ɾ��
};


