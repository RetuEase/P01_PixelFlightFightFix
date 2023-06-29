#include "Entity.h"

using namespace std;
/// <summary>
/// Block
/// </summary>
Block::Block()
{
	blockID = I_IdCounter++;//����id
}
Block::~Block() {}

/// <summary>
/// Bullet
/// </summary>
Bullet::Bullet() {//�ӵ����캯�� 
	entityType = _EntityBullet;		//Ĭ�����ӵ�
	core = MyPLANECORE;				// ��������
	autoSpeed = { 0,-1 };			// �����ٶ�
	tileCountMax = 1;				// ӵ�е���������
	tileCount = 1;					// ʣ�������
	Scroll scroll = Scroll::GetInstance();
	scroll.allEntities.push_back(this);//���Լ�����allEntities
}


Bullet::~Bullet()
{
	Scroll scroll = Scroll::GetInstance();
	scroll.DeleteInstance(blockID);

}

void Bullet::AutoMove()
{
	this->core.x += this->autoSpeed.x;
	this->core.y += this->autoSpeed.y;
}



void Bullet::CollisionDetection()//��ײ���
{
	if (entityType = _EntityPlayer) {
		{
		}
		delete this;
	}
	else {

	}
}

void Bullet::Resource()
{
	std::shared_ptr<Bullet> p1(this);
}

//void Bullet::Destroy(Coordinate pos){}
void Bullet::Fracture() {}

/// <summary>
/// PLAN
/// </summary>
Plane::Plane()
{
	entityType = _EntityEnemy;	//Ĭ���ǵл�
	core = { 50,0 };
	autoSpeed = { 1,0 };	// �����ٶ�
	tileCountMax = 1;	// ӵ�е���������
	tileCount = 1;		// ʣ�������
}
Plane::Plane(Coordinate co)
{
	entityType = _EntityEnemy;	//Ĭ���ǵл�
	core = co;
	autoSpeed = { 1,0 };	// �����ٶ�
	tileCountMax = 1;	// ӵ�е���������
	tileCount = 1;		// ʣ�������
}
Plane::~Plane() {}

//void Plane::Destroy(Coordinate core){}
void Plane::Fracture() {}

/// <summary>
/// PlayerPlane
/// </summary>
PlayerPlane::PlayerPlane()//Ĭ�Ϸɻ� 
{
	entityType = _EntityPlayer;
	core = MyPLANECORE;
	autoSpeed = { 0,0 };
	tileCountMax = 4;	// ӵ�е���������
	tileCount = 4;		// ʣ�������
	Block pp1;
	Block pp2;
	Block pp3;
	unordered_map<Coordinate, Block> hmap{ {{-1,0},pp1},{{1,0},pp2},{{0,-1},pp3} };
	blockMap = hmap;
};

//<Coordinate, Block>

PlayerPlane::PlayerPlane(std::vector<Coordinate> tblockMap) //�����ɻ� 
{
	entityType = _EntityPlayer;
	core = MyPLANECORE;
	autoSpeed = { 0,0 };
	tileCountMax = tblockMap.size();	// ӵ�е���������
	tileCount = tblockMap.size();		// ʣ�������
	for (auto& i : tblockMap)
	{
		if (!(i.x && i.y))
		{
			Block pp;
			blockMap.insert({ { i, pp } });
		}
	}
}

PlayerPlane::~PlayerPlane() {}


//void PlayerPlane::Destroy(Coordinate core) {}

/******BFS******/
void PlayerPlane::Fracture()
{
	int arr[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
	int count = 0;//���ڼ�¼BFS�����˼�����
	unordered_map<Coordinate, bool> temp;
	for (auto& pair : this->blockMap) {
		temp.insert(make_pair(pair.first, false));//��ȫ����װ����ʱmap
	}
	//bool containCore = false;//���BFS�Ƿ��������˺���
	queue<Coordinate> myQueue;
	myQueue.push(this->core);//�Ӻ���λ�ÿ�ʼBFS
	temp[core] = 1;
	//int step = 0;
	Coordinate xy;
	while (!myQueue.empty()) {
		xy = myQueue.front();
		myQueue.pop();
		count++;
		//step = temp.find(xy)->second;
		for (int i = 0; i < 4; i++) {
			Coordinate xy2(xy.x + arr[i][0], xy.y + arr[i][1]);
			auto it = temp.find(xy2);
			if (it != temp.end() && !(it->second)) {//����ڵ������δ�����ʹ�
				myQueue.push(xy2);
				it->second = true;
			}
		}
	}
	std::cout << count << endl;
	std::cout << temp.size() << endl;
	if (count != temp.size()) {//������û����������˵���ж���
		//��BFSδ�������ĵ�ɾ��
		for (auto& pair : temp) {
			if (!(pair.second)) {
				std::cout << "ɾ����" << pair.first.x << "," << pair.first.y << endl;
				this->blockMap.erase(pair.first);
				count++;
			}
		}
	}
	std::cout << count << endl;
}

