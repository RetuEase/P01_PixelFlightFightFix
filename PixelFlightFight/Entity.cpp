#include "Entity.h"

int I_IdCounter = 1;
int SCORE = 0;
int GAMEEND = 0;//1����

Coordinate PLAYERPLANECORE(15, 35);	//Ĭ�Ϸɻ�����λ��

std::unordered_map<Coordinate, Bullet> Bullet::ENEMYMAP;			//�л�map
std::unordered_map<Coordinate, Block> Bullet::PlayerPlaneBlock;		// ��ҷɻ�ӵ�е����أ�������ĵ��������)
std::unordered_map<InsId, std::shared_ptr<Bullet>> Bullet::AllEntities;// ����ʵ��
std::vector<InsId> Bullet::keysToDelete;//��ɾ������
int Bullet::enemiesNum = 21;
/// <summary>
/// Block
/// </summary>
Block::Block()
{
	blockID = I_IdCounter++;//����id
}
Block::~Block()
{
	/*for (auto it = PlayerPlaneBlock.begin(); it != PlayerPlaneBlock.end(); ++it) {
		if (it->second == *this) {
			PlayerPlaneBlock.erase(it);
			break;
		}
	}*/
}

/// <summary>
/// Bullet
/// </summary>
Bullet::Bullet()//�ӵ����캯�� 
{
	entityType = _EntityNull;		//Ĭ�����ӵ�
	core = { -1, -1 };				// ��������
	autoSpeed = Speed(0, 0);			// �����ٶ�
	tileCountMax = 1;				// ӵ�е���������
	tileCount = 1;					// ʣ�������
}
Bullet::Bullet(int i)
{
	//std::cout << "������Bullet(i)" << std::endl;
	entityType = _EntityBullet;		//Ĭ�����ӵ�
	core = PLAYERPLANECORE;			// ��������
	autoSpeed = Speed(0, -1);		// �����ٶ�
	tileCountMax = 1;				// ӵ�е���������
	tileCount = 1;					// ʣ�������
	std::shared_ptr<Bullet> bulletptr = std::make_shared<Bullet>(*this);
	AllEntities[blockID] = bulletptr;	//���Լ�����AllEntities
	//std::cout << "�����ӵ�" << blockID << " / " << AllEntities.size() << std::endl;
}
Bullet::~Bullet()
{
	//std::cout << "�ͷ��ӵ�: ";
}
bool Bullet::AutoMove()
{
	if (entityType == _EntityBullet && this->core.y >= 0)
	{
		this->core.x += this->autoSpeed.x;
		this->core.y += this->autoSpeed.y;
		return true;
	}
	else {
		this->Release();
		return false;
	}
}
void Bullet::PlayerMove(Speed speed) {}

void Bullet::CollisionDetection()//��ײ���
{
	//if (entityType = _EntityBullet) {//�ӵ�
	auto it = ENEMYMAP.find(core);
	if (it != ENEMYMAP.end())//������ײ
	{
		//std::cout << "�ӵ���ײ: " << blockID << std::endl;
		SCORE += 1;
		it->second.Release();
		ENEMYMAP.erase(it);
		Release();
		return;
	}

}
void Bullet::Release()//����
{
	if (entityType == _EntityEnemy)
	{
		--enemiesNum;//ʣ���������	
	}
	keysToDelete.push_back(blockID);
}
void Bullet::Fracture() {}

/// <summary>
/// PLANE
/// </summary>
Plane::Plane() {}
Plane::Plane(Coordinate co)
{
	entityType = _EntityEnemy;	//Ĭ���ǵл�
	core = co;
	autoSpeed = { 0,1 };	// �����ٶ�
	tileCountMax = 1;	// ӵ�е���������
	tileCount = 1;		// ʣ�������
	std::shared_ptr<Bullet> bulletptr = std::make_shared<Plane>(*this);
	AllEntities[blockID] = bulletptr;	//���Լ�����AllEntities

}
Plane::~Plane() {
	//std::cout << "�ͷŷɻ�: " << blockID << std::endl;
}

bool Plane::AutoMove()//�л��ƶ�
{
	if (entityType == _EntityEnemy && this->core.y <= MAPSIZE_Y - 1)
	{
		this->core.x += this->autoSpeed.x;
		this->core.y += this->autoSpeed.y;
		return true;
	}
	else {
		//���˵������,��Ѫ/�۷�
		this->Release();
		return false;
	}
}

void Plane::PlayerMove(Speed speed) {}

void Plane::CollisionDetection()
{
	//if (entityType = _EntityEnemy) {//�л�
	{
		if (core == PLAYERPLANECORE)
		{
			//std::cout << "�л�ײ�Ի�,��Ϸ���� " << blockID << std::endl;
			GAMEEND = 1;
		}
		for (auto it = Bullet::AllEntities.begin(); it != Bullet::AllEntities.end(); ++it) {
			InsId key = it->first;
			std::shared_ptr<Bullet> bulletptr = it->second;
			if (bulletptr->core == core && bulletptr->entityType == _EntityBullet)
			{
				//std::cout << "�л���ײ: " << blockID << std::endl;
				SCORE += 1;
				ENEMYMAP.erase(ENEMYMAP.find(core));
				bulletptr->Release();
				Release();
				return;
			}
		}
	}
}


void Plane::Fracture() {}

/// <summary>
/// PlayerPlane
/// </summary>
PlayerPlane::PlayerPlane()//Ĭ�Ϸɻ� 
{
	blockID = 0;
	entityType = _EntityPlayer;
	core = PLAYERPLANECORE;
	autoSpeed = Speed(0, 0);
	tileCountMax = 4;	// ӵ�е���������
	tileCount = 4;		// ʣ�������
	Block pp1;
	Block pp2;
	Block pp3;
	std::unordered_map<Coordinate, Block> hmap{ {{-1,0},pp1},{{1,0},pp2},{{0,-1},pp3} };
	PlayerPlaneBlock.clear();
	PlayerPlaneBlock = hmap;
	std::shared_ptr<Bullet> bulletptr = std::make_shared<PlayerPlane>(*this);
	AllEntities[blockID] = bulletptr;	//���Լ�����AllEntities

};

PlayerPlane::PlayerPlane(std::vector<Coordinate> tblockMap) //�����ɻ� 
{
	blockID = 0;
	entityType = _EntityPlayer;
	core = PLAYERPLANECORE;
	autoSpeed = Speed(0, 0);
	tileCountMax = tblockMap.size();	// ӵ�е���������
	tileCount = tblockMap.size();		// ʣ�������
	PlayerPlaneBlock.clear();
	for (auto& i : tblockMap)
	{
		if (i.x != 0 || i.y != 0)
		{
			Block pp;
			PlayerPlaneBlock.insert({ i, pp });
			//std::cout << "!!!!!!" << PlayerPlaneBlock.size() << std::endl;
		}
	}

	std::shared_ptr<Bullet> bulletptr = std::make_shared<PlayerPlane>(*this);
	AllEntities[blockID] = bulletptr;	//���Լ�����AllEntities
}

PlayerPlane::~PlayerPlane() {
	//std::cout << "�ͷ���ҷɻ�: " << blockID << std::endl;
}

void PlayerPlane::PlayerMove(Speed speed)
{
	if (this->core.x + speed.x <= MAPSIZE_X - 1 && this->core.x + speed.x >= 0) {
		this->core.x += speed.x;
		PLAYERPLANECORE.x += speed.x;
	}
	else {
		setlinecolor(CORECOLOR);
		setlinestyle(PS_SOLID, 2);
		line(BLANK_L - 2, BLANK_U - 2, BLANK_R + 2, BLANK_U - 2);
		line(BLANK_L - 2, BLANK_U - 2, BLANK_L - 2, BLANK_D + 2);
		line(BLANK_L - 2, BLANK_D + 2, BLANK_R + 2, BLANK_D + 2);
		line(BLANK_R + 2, BLANK_U - 2, BLANK_R + 2, BLANK_D + 2);
	}
	if (this->core.y + speed.y <= MAPSIZE_Y - 1 && this->core.y + speed.y >= 0) {
		this->core.y += speed.y;
		PLAYERPLANECORE.y += speed.y;
	}
	else {
		setlinecolor(CORECOLOR);
		setlinestyle(PS_SOLID, 2);
		line(BLANK_L - 2, BLANK_U - 2, BLANK_R + 2, BLANK_U - 2);
		line(BLANK_L - 2, BLANK_U - 2, BLANK_L - 2, BLANK_D + 2);
		line(BLANK_L - 2, BLANK_D + 2, BLANK_R + 2, BLANK_D + 2);
		line(BLANK_R + 2, BLANK_U - 2, BLANK_R + 2, BLANK_D + 2);
	}
}

void PlayerPlane::CollisionDetection()
{
	//if (entityType = _EntityPlayer) {//�Ի�
	if (ENEMYMAP.find(core) != ENEMYMAP.end())
	{
		//std::cout << "������ײ: " << blockID << std::endl;
		GAMEEND = 1;//��Ϸ����		
	}
	else {
		for (auto it = PlayerPlaneBlock.begin(); it != PlayerPlaneBlock.end(); ++it)
		{
			const Coordinate& coord = it->first;
			Coordinate realCoord(coord.x + core.x, coord.y + core.y);
			auto itr = ENEMYMAP.find(realCoord);
			if (itr != ENEMYMAP.end())
			{
				//std::cout << "�һ���ײ: " << it->second.blockID << std::endl;
				PlayerPlaneBlock.erase(it);
				itr->second.Release();
				ENEMYMAP.erase(itr);
				tileCount--;
				return;
			}

		}
	}

}

/******BFS******/
void PlayerPlane::Fracture()
{
	int arr[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
	int count = 0;//���ڼ�¼BFS�����˼�����
	std::unordered_map<Coordinate, bool> temp;
	for (auto& pair : PlayerPlaneBlock) {
		temp.insert(std::make_pair(pair.first, false));//��ȫ����װ����ʱmap
	}
	bool containCore = false;//���BFS�Ƿ��������˺���
	std::queue<Coordinate> myQueue;
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
	//std::
	//  << count << std::endl;
	//std::cout << temp.size() << std::endl;
	if (count != temp.size()) {//������û����������˵���ж���
		//��BFSδ�������ĵ�ɾ��
		for (auto& pair : temp) {
			if (!(pair.second)) {
				//std::cout << "ɾ����" << pair.first.x << "," << pair.first.y << std::endl;
				//blockMap.erase(pair.first);
				count++;
			}
		}
	}
	//std::cout << count << std::endl;
}

