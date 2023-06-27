#pragma once
#include "Globals.h"
#include "Scroll.h"

//ԭ����Instance.h
class Scroll;
// ͼ�Σ��޾�������
class Sprite
{
protected:
	PlaneId planeId;
	std::unordered_map<Coordinate, COLORREF> spriteMap;	// ͼ�ε���״��ӵ�е����أ���Բο�������꣩
public:
	Sprite();
	~Sprite();
	LONGLONG getPlaneId();
	void setPlaneId(long long id);
};

// ʵ�壬�о�������
class Bullet : public Sprite
{
public:
	int type;			// �ӵ����Ƿɻ�
	InsId insId;		// ʵ�� ID
	EntityType entityType;//�ɻ�����

	int tileCountMax;	// ӵ�е���������
	int tileCount;		// ʣ�������

	Coordinate pos;		// �ο��㴦�� Scroll �еľ�������
	Speed autoSpeed;	// �����ٶ�

	friend Scroll;
	Bullet();
	Bullet(Coordinate pos);
	Bullet(Coordinate pos, std::unordered_map<Coordinate, COLORREF> spriteMap);
	~Bullet();
	void setInsId(int id);
	int getInsId();
	void sesSpeed(int x, int y);
	Speed getSpeed();

	void AutoMove();			// �����ƶ�
	void RenderToScroll();		// �� Bullet ���ݼ�����������Ⱦ�� scrollMap��ע�� SCROLL_X ������
	/************************����֮��!**********************************/
	void CollisionDetection();	// ��ײ��⣬�ƶ�����Ҫ������ײ���
	/******************************************************************/
	void Resource();
};

class Plane : public Bullet
{
protected:
	std::vector<Coordinate> core;	// ��Щ�Ǻ�������
public:
	Plane();
	Plane(Coordinate pos, std::unordered_map<Coordinate, COLORREF> spriteMap);
	~Plane();
	void Destroy(Coordinate pos);			// ���ƻ�һ������
	void Fracture();						// BFS �ݹ��ж���Щ����û�кͺ���������ͨ��� vector������ɾ��
	void setCore(std::vector<Coordinate> core);	//���ú��Ĳ�λ

};

class PlayerPlane : public Plane
{
public:
	PlayerPlane();
	PlayerPlane(Coordinate pos, std::unordered_map<Coordinate, COLORREF> spriteMap);
	~PlayerPlane();

	void ManualMove(Speed speed);	// �ܿ��ƶ�
};