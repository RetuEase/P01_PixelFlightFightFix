#pragma once
#include "Globals.h"

// ͼ�Σ��޾�������
class Sprite
{
protected:
	PlaneId planeId;
	std::unordered_map<Coordinate, COLORREF> spriteMap;	// ͼ�ε���״��ӵ�е����أ���Բο�������꣩
public:
	Sprite();
	~Sprite();
};

// ʵ�壬�о�������
class Bullet : public Sprite
{
protected:
	int type;			// �ӵ����Ƿɻ�
	InsId insId;		// ʵ�� ID

	int tileCountMax;	// ӵ�е���������
	int tileCount;		// ʣ�������

	Coordinate pos;		// �ο��㴦�� Scroll �еľ�������
	Speed autoSpeed;	// �����ٶ�
public:
	Bullet();
	Bullet(Coordinate pos);
	~Bullet();

	void AutoMove();			// �����ƶ�
	void RenderToScroll();		// �� Bullet ���ݼ�����������Ⱦ�� scrollMap��ע�� SCROLL_X ������
	/************************����֮��!**********************************/
	void CollisionDetection();	// ��ײ��⣬�ƶ�����Ҫ������ײ���
	/******************************************************************/
};

class Plane : public Bullet
{
protected:
	std::vector<Coordinate> core;	// ��Щ�Ǻ�������
public:
	Plane();
	Plane(Coordinate pos);
	~Plane();

	void Destroy(Coordinate pos);	// ���ƻ�һ������
	void Fracture();				// DFS �ݹ��ж���Щ����û�кͺ���������ͨ��� vector������ɾ��
};

class PlayerPlane : public Plane
{
public:
	PlayerPlane();
	~PlayerPlane();

	void ManualMove(Speed speed);	// �ܿ��ƶ�
};