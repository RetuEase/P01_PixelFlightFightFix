#pragma once
#include "Globals.h"
#include "Scroll.h"

class Scroll;
//class PlaneTemplate;

//��������,�޺�������
class Block
{
public:
	InsId blockID;//ÿ������һ��
	Block();
	~Block();
};

//ʵ�壬�о�������
class Bullet : public Block
{
public:
	EntityType entityType;//ʵ������   _EntityBullet, _EntityEnemy, _EntityPlayer
	Coordinate core;	// ���ĵľ�������
	Speed autoSpeed;	// �����ٶ�
	int tileCountMax;	// ӵ�е���������
	int tileCount;		// ʣ�������

	Bullet();	//�����ӵ�
	~Bullet();

	void AutoMove();					// �����ƶ�
	virtual void CollisionDetection();	// ��ײ��⣬�ƶ�����Ҫ������ײ���
	void Resource();					//�ͷ�
	virtual void Fracture();			// BFS �ݹ��ж���Щ����û�кͺ���������ͨ��� vector������ɾ��
};

class Plane : public Bullet//�л�
{
public:
	Plane();//����Ĭ�Ϸɻ�
	Plane(Coordinate co);
	~Plane();
	virtual void CollisionDetection();
	virtual void Fracture();						// BFS �ݹ��ж���Щ����û�кͺ���������ͨ��� vector������ɾ��
};

class PlayerPlane : public Plane//��ҷɻ�
{
public:

	PlayerPlane();//����Ĭ����ҷɻ�
	PlayerPlane(std::vector<Coordinate>);//��workshop������ҷɻ�
	~PlayerPlane();
	virtual void CollisionDetection();
	virtual void Fracture();						// BFS �ݹ��ж���Щ����û�кͺ���������ͨ��� vector������ɾ��
};

std::unordered_map<Coordinate, Bullet> ENEMYMAP;//�л�map
std::unordered_map<Coordinate, Block> blockMap;	// ʵ��ӵ�е����أ�������ĵ��������)