#pragma once
#include "Globals.h"
#include "Scroll.h"


class Scroll;
//class PlaneTemplate;



//��������,�޺�������
class Block
{
protected:
	InsId blockID;		//ÿ������һ��
public:
	Block();
	~Block();
	long long getId();			//get
	void setId(long long id);	//set
};


//ʵ�壬�о�������
class Bullet : public Block
{
public:
	EntityType entityType;//ʵ������   _EntityBullet, _EntityEnemy, _EntityPlayer
	Coordinate core;	// ���ĵľ�������
	Speed autoSpeed;	// �����ٶ�
	std::vector<Coordinate> spriteMap;	// ʵ��ӵ�е����أ�������ĵ�������꣩

	int tileCountMax;	// ӵ�е���������
	int tileCount;		// ʣ�������

	Bullet();
	Bullet(Coordinate pos);
	Bullet(Coordinate pos, std::unordered_map<Coordinate, COLORREF> spriteMap);
	~Bullet();

	void Move();			// �����ƶ�
	void RenderToScroll();		// �� Bullet ���ݼ�����������Ⱦ�� scrollMap��ע�� SCROLL_X ������
	/************************����֮��!**********************************/
	void CollisionDetection();	// ��ײ��⣬�ƶ�����Ҫ������ײ���
	/******************************************************************/
	void Resource();			//�ͷ�
	//void SetPlaneTemplate(PlaneTemplate pt);
//
//};
//
//class Plane : public Bullet
//{
//protected:
//	std::vector<Coordinate> core;	// ��Щ�Ǻ�������
//public:
//	Plane();
//	Plane(Coordinate pos, std::unordered_map<Coordinate, COLORREF> spriteMap);
//	~Plane();
//	void Destroy(Coordinate pos);			// ���ƻ�һ������
//	void Fracture();						// BFS �ݹ��ж���Щ����û�кͺ���������ͨ��� vector������ɾ��
//	void setCore(std::vector<Coordinate> core);	//���ú��Ĳ�λ
//};
//
//class PlayerPlane : public Plane
//{
//public:
//	PlayerPlane();
//	PlayerPlane(Coordinate pos, std::unordered_map<Coordinate, COLORREF> spriteMap);
//	~PlayerPlane();
//
//	void ManualMove(Speed speed);	// �ܿ��ƶ�
};