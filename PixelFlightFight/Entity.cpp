#include "Entity.h"

int I_IdCounter = 1;
int SCORE = 0;
int GAMEEND = 1;
std::vector<Coordinate> DEFAULTPLANE{ {0,0},{0,-1},{1,0},{0,1} };//Ĭ�Ϸɻ�
Coordinate PLAYERPLANECORE(15, 35);	//Ĭ�Ϸɻ�����λ��

std::unordered_map<Coordinate, Bullet> Bullet::ENEMYMAP;			//�л�map
std::unordered_map<Coordinate, Block> Bullet::PlayerPlaneBlock;		// ��ҷɻ�ӵ�е����أ�������ĵ��������)
std::vector<Bullet*> Bullet::AllEntities;// ����ʵ��

/// <summary>
/// Block
/// </summary>
Block::Block()
{
	blockID = I_IdCounter++;//����id
	std::cout << "����ID " << blockID << " / " << I_IdCounter << std::endl;
}
Block::~Block()
{
	std::cout << "�ͷſ�: " << blockID << std::endl;
	// ��PlayerPlaneBlock���Ƴ�
	/*for (auto it = PlayerPlaneBlock.begin(); it != PlayerPlaneBlock.end(); ++it) {
		if (it->second == *this) {
			PlayerPlaneBlock.erase(it);
			break;
		}
	}*/
}

void Block::Resource()
{
	std::cout << "�Ƴ���ʵ��: " << blockID << std::endl;

}


/// <summary>
/// Bullet
/// </summary>
Bullet::Bullet()//�ӵ����캯�� 
{
	entityType = _EntityBullet;		//Ĭ�����ӵ�
	core = PLAYERPLANECORE;				// ��������
	autoSpeed = Speed(0, -1);			// �����ٶ�
	tileCountMax = 1;				// ӵ�е���������
	tileCount = 1;					// ʣ�������
	//Scroll scroll = Scroll::GetInstance();
	AllEntities.push_back(this);//���Լ�����allEntities
}


Bullet::~Bullet()
{
	std::cout << "�ͷ��ӵ�: ";
	// ��Bullet�����������Ƴ�ʵ��	
}


void Bullet::AutoMove()
{
	this->core.x += this->autoSpeed.x;
	this->core.y += this->autoSpeed.y;
}

void Bullet::PlayerMove(Speed speed) {}

void Bullet::CollisionDetection()//��ײ���
{
	//if (entityType = _EntityBullet) {//�ӵ�
	auto it = ENEMYMAP.find(core);
	if (it != ENEMYMAP.end())//������ײ
	{
		std::cout << "�ӵ���ײ: " << blockID << std::endl;
		it->second.Resource();
		ENEMYMAP.erase(it);
		Resource();
		return;
	}
	//}
}

void Bullet::Resource()//����
{
	std::cout << "��allEntities���Ƴ�: " << blockID << std::endl;

	for (auto it = AllEntities.begin(); it != AllEntities.end(); ++it) {
		if (*it == this) {
			AllEntities.erase(it);
			break;
		}
	}
}


void Bullet::Fracture() {}

/// <summary>
/// PLANE
/// </summary>
Plane::Plane()
{
	entityType = _EntityEnemy;	//Ĭ���ǵл�
	core = { 50,0 };
	autoSpeed = { 0,1 };	// �����ٶ�
	tileCountMax = 1;	// ӵ�е���������
	tileCount = 1;		// ʣ�������
}
Plane::Plane(Coordinate co)
{
	entityType = _EntityEnemy;	//Ĭ���ǵл�
	core = co;
	autoSpeed = { 0,1 };	// �����ٶ�
	tileCountMax = 1;	// ӵ�е���������
	tileCount = 1;		// ʣ�������
}
Plane::~Plane() {
	std::cout << "�ͷŷɻ�: " << blockID << std::endl;
}
void Plane::PlayerMove(Speed speed) {}
void Plane::CollisionDetection()
{
	if (entityType = _EntityEnemy) {//�л�
		{

			for (std::vector<Bullet*>::iterator it = Bullet::AllEntities.begin(); it != Bullet::AllEntities.end(); ++it) {
				Bullet* bullet = *it;

				if (bullet->core == core)
				{
					std::cout << "�л���ײ: " << blockID << std::endl;
					ENEMYMAP.erase(ENEMYMAP.find(core));
					bullet->Resource();
					Resource();
					return;
				}

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
	autoSpeed = { 0,0 };
	tileCountMax = 4;	// ӵ�е���������
	tileCount = 4;		// ʣ�������
	Block pp1;
	Block pp2;
	Block pp3;
	std::unordered_map<Coordinate, Block> hmap{ {{-1,0},pp1},{{1,0},pp2},{{0,-1},pp3} };
	PlayerPlaneBlock.clear();
	PlayerPlaneBlock = hmap;
};

PlayerPlane::PlayerPlane(std::vector<Coordinate> tblockMap) //�����ɻ� 
{
	blockID = 0;
	entityType = _EntityPlayer;
	core = PLAYERPLANECORE;
	autoSpeed = { 0,0 };
	tileCountMax = tblockMap.size();	// ӵ�е���������
	tileCount = tblockMap.size();		// ʣ�������
	PlayerPlaneBlock.clear();
	for (auto& i : tblockMap)
	{
		if (!(i.x && i.y))
		{
			Block pp;
			PlayerPlaneBlock.insert({ i, pp });
		}
	}
}

PlayerPlane::~PlayerPlane() {
	std::cout << "�ͷ���ҷɻ�: " << blockID << std::endl;
}

void PlayerPlane::PlayerMove(Speed speed)
{
	if (this->core.x + speed.x <= MAPSIZE_X && this->core.x + speed.x >= 0) {
		this->core.x += speed.x;
		PLAYERPLANECORE.x += speed.x;
	}
	else {
		setlinecolor(SECONDCOLOR);
		setlinestyle(PS_SOLID, 2);
		line(BLANK_L, BLANK_U, BLANK_R, BLANK_U);  // ���ƴ�ֱ��
		line(BLANK_L, BLANK_U, BLANK_L, BLANK_D);  // ���ƴ�ֱ��
		line(BLANK_L, BLANK_D, BLANK_R, BLANK_D);  // ���ƴ�ֱ��
		line(BLANK_R, BLANK_U, BLANK_R, BLANK_D);  // ���ƴ�ֱ��
	}
	if (this->core.y + speed.y <= MAPSIZE_Y && this->core.x + speed.x >= 0) {
		this->core.y += speed.y;
		PLAYERPLANECORE.y += speed.y;
	}
	else {
		setlinecolor(SECONDCOLOR);
		setlinestyle(PS_SOLID, 2);
		line(BLANK_L, BLANK_U, BLANK_R, BLANK_U);  // ���ƴ�ֱ��
		line(BLANK_L, BLANK_U, BLANK_L, BLANK_D);  // ���ƴ�ֱ��
		line(BLANK_L, BLANK_D, BLANK_R, BLANK_D);  // ���ƴ�ֱ��
		line(BLANK_R, BLANK_U, BLANK_R, BLANK_D);  // ���ƴ�ֱ��

	}
}

void PlayerPlane::CollisionDetection()
{
	if (entityType = _EntityPlayer) {//�Ի�

		if (ENEMYMAP.find(core) != ENEMYMAP.end())
		{
			std::cout << "������ײ: " << blockID << std::endl;

			GAMEEND = 0;//��Ϸ����		
		}
		else {
			for (auto it = PlayerPlaneBlock.begin(); it != PlayerPlaneBlock.end(); )
			{
				const Coordinate& coord = it->first;

				if (ENEMYMAP.find(coord) != ENEMYMAP.end())
				{
					std::cout << "�һ���ײ: " << it->second.blockID << std::endl;
					PlayerPlaneBlock.erase(it);
					ENEMYMAP.erase(ENEMYMAP.find(coord));
					tileCount--;
					return;
				}
				else
				{
					++it;
				}
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
	std::cout << count << std::endl;
	std::cout << temp.size() << std::endl;
	if (count != temp.size()) {//������û����������˵���ж���
		//��BFSδ�������ĵ�ɾ��
		for (auto& pair : temp) {
			if (!(pair.second)) {
				std::cout << "ɾ����" << pair.first.x << "," << pair.first.y << std::endl;
				//blockMap.erase(pair.first);
				count++;
			}
		}
	}
	std::cout << count << std::endl;
}

