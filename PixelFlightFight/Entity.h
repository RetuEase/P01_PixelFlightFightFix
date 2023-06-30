#pragma once
#include "Globals.h"


//��������,�޺�������
class Block
{
public:
	InsId blockID;				//ÿ������һ��
	Block();
	~Block();
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
	static std::unordered_map<InsId, std::shared_ptr<Bullet>> AllEntities;			// ����ʵ��
	static std::vector<InsId> keysToDelete;//��ɾ������

	EntityType entityType;//ʵ������   _EntityBullet, _EntityEnemy, _EntityPlayer
	Coordinate core;	// ���ĵľ�������
	Speed autoSpeed;	// �����ٶ�
	int tileCountMax;	// ӵ�е���������
	int tileCount;		// ʣ�������

	Bullet();			//�ӵ�
	Bullet(int i);		//�����ӵ�
	~Bullet();
	bool AutoMove();						// �����ƶ�
	virtual void PlayerMove(Speed speed);	// �����ƶ�
	void Release();							//�Ƴ�ʵ��
	virtual void CollisionDetection();		// ��ײ��⣬�ƶ�����Ҫ������ײ���
	virtual void Fracture();				// BFS �ݹ��ж���Щ����û�кͺ���������ͨ��� vector������ɾ��
};



class Plane : public Bullet//�л�
{
public:
	Plane();//����Ĭ�Ϸɻ�
	Plane(Coordinate co);
	~Plane();
	virtual void PlayerMove(Speed speed)override;	// �����ƶ�
	virtual void CollisionDetection()override;	 		// ��ײ���
	virtual void Fracture()override;					// BFS �ݹ��ж���Щ����û�кͺ���������ͨ��� vector������ɾ��
};

class PlayerPlane : public Plane//��ҷɻ�
{
public:

	PlayerPlane();//����Ĭ����ҷɻ�
	PlayerPlane(std::vector<Coordinate>);			//��workshop������ҷɻ�
	~PlayerPlane();
	virtual void PlayerMove(Speed speed)override;	// �����ƶ�
	virtual void CollisionDetection()override;
	virtual void Fracture()override;				// BFS �ݹ��ж���Щ����û�кͺ���������ͨ��� vector������ɾ��
};


