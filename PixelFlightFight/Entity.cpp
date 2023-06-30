#include "Entity.h"

int I_IdCounter = 1;
int SCORE = 0;
int GAMEEND = 0;//1结束

Coordinate PLAYERPLANECORE(15, 35);	//默认飞机核心位置

std::unordered_map<Coordinate, Bullet> Bullet::ENEMYMAP;			//敌机map
std::unordered_map<Coordinate, Block> Bullet::PlayerPlaneBlock;		// 玩家飞机拥有的像素（对与核心的相对坐标)
std::unordered_map<InsId, std::shared_ptr<Bullet>> Bullet::AllEntities;// 所有实体
std::vector<InsId> Bullet::keysToDelete;//待删除的项
int Bullet::enemiesNum = 21;
/// <summary>
/// Block
/// </summary>
Block::Block()
{
	blockID = I_IdCounter++;//分配id
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
Bullet::Bullet()//子弹构造函数 
{
	entityType = _EntityNull;		//默认是子弹
	core = { -1, -1 };				// 核心坐标
	autoSpeed = Speed(0, 0);			// 固有速度
	tileCountMax = 1;				// 拥有的像素上限
	tileCount = 1;					// 剩余的像素
}
Bullet::Bullet(int i)
{
	//std::cout << "调用了Bullet(i)" << std::endl;
	entityType = _EntityBullet;		//默认是子弹
	core = PLAYERPLANECORE;			// 核心坐标
	autoSpeed = Speed(0, -1);		// 固有速度
	tileCountMax = 1;				// 拥有的像素上限
	tileCount = 1;					// 剩余的像素
	std::shared_ptr<Bullet> bulletptr = std::make_shared<Bullet>(*this);
	AllEntities[blockID] = bulletptr;	//将自己插入AllEntities
	//std::cout << "生成子弹" << blockID << " / " << AllEntities.size() << std::endl;
}
Bullet::~Bullet()
{
	//std::cout << "释放子弹: ";
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

void Bullet::CollisionDetection()//碰撞检测
{
	//if (entityType = _EntityBullet) {//子弹
	auto it = ENEMYMAP.find(core);
	if (it != ENEMYMAP.end())//发生碰撞
	{
		//std::cout << "子弹碰撞: " << blockID << std::endl;
		SCORE += 1;
		it->second.Release();
		ENEMYMAP.erase(it);
		Release();
		return;
	}

}
void Bullet::Release()//销毁
{
	if (entityType == _EntityEnemy)
	{
		--enemiesNum;//剩余敌人数量	
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
	entityType = _EntityEnemy;	//默认是敌机
	core = co;
	autoSpeed = { 0,1 };	// 固有速度
	tileCountMax = 1;	// 拥有的像素上限
	tileCount = 1;		// 剩余的像素
	std::shared_ptr<Bullet> bulletptr = std::make_shared<Plane>(*this);
	AllEntities[blockID] = bulletptr;	//将自己插入AllEntities

}
Plane::~Plane() {
	//std::cout << "释放飞机: " << blockID << std::endl;
}

bool Plane::AutoMove()//敌机移动
{
	if (entityType == _EntityEnemy && this->core.y <= MAPSIZE_Y - 1)
	{
		this->core.x += this->autoSpeed.x;
		this->core.y += this->autoSpeed.y;
		return true;
	}
	else {
		//敌人到达底线,扣血/扣分
		this->Release();
		return false;
	}
}

void Plane::PlayerMove(Speed speed) {}

void Plane::CollisionDetection()
{
	//if (entityType = _EntityEnemy) {//敌机
	{
		if (core == PLAYERPLANECORE)
		{
			//std::cout << "敌机撞自机,游戏结束 " << blockID << std::endl;
			GAMEEND = 1;
		}
		for (auto it = Bullet::AllEntities.begin(); it != Bullet::AllEntities.end(); ++it) {
			InsId key = it->first;
			std::shared_ptr<Bullet> bulletptr = it->second;
			if (bulletptr->core == core && bulletptr->entityType == _EntityBullet)
			{
				//std::cout << "敌机碰撞: " << blockID << std::endl;
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
PlayerPlane::PlayerPlane()//默认飞机 
{
	blockID = 0;
	entityType = _EntityPlayer;
	core = PLAYERPLANECORE;
	autoSpeed = Speed(0, 0);
	tileCountMax = 4;	// 拥有的像素上限
	tileCount = 4;		// 剩余的像素
	Block pp1;
	Block pp2;
	Block pp3;
	std::unordered_map<Coordinate, Block> hmap{ {{-1,0},pp1},{{1,0},pp2},{{0,-1},pp3} };
	PlayerPlaneBlock.clear();
	PlayerPlaneBlock = hmap;
	std::shared_ptr<Bullet> bulletptr = std::make_shared<PlayerPlane>(*this);
	AllEntities[blockID] = bulletptr;	//将自己插入AllEntities

};

PlayerPlane::PlayerPlane(std::vector<Coordinate> tblockMap) //创建飞机 
{
	blockID = 0;
	entityType = _EntityPlayer;
	core = PLAYERPLANECORE;
	autoSpeed = Speed(0, 0);
	tileCountMax = tblockMap.size();	// 拥有的像素上限
	tileCount = tblockMap.size();		// 剩余的像素
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
	AllEntities[blockID] = bulletptr;	//将自己插入AllEntities
}

PlayerPlane::~PlayerPlane() {
	//std::cout << "释放玩家飞机: " << blockID << std::endl;
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
	//if (entityType = _EntityPlayer) {//自机
	if (ENEMYMAP.find(core) != ENEMYMAP.end())
	{
		//std::cout << "核心碰撞: " << blockID << std::endl;
		GAMEEND = 1;//游戏结束		
	}
	else {
		for (auto it = PlayerPlaneBlock.begin(); it != PlayerPlaneBlock.end(); ++it)
		{
			const Coordinate& coord = it->first;
			Coordinate realCoord(coord.x + core.x, coord.y + core.y);
			auto itr = ENEMYMAP.find(realCoord);
			if (itr != ENEMYMAP.end())
			{
				//std::cout << "我机碰撞: " << it->second.blockID << std::endl;
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
	int count = 0;//用于记录BFS搜索了几个点
	std::unordered_map<Coordinate, bool> temp;
	for (auto& pair : PlayerPlaneBlock) {
		temp.insert(std::make_pair(pair.first, false));//将全部点装入临时map
	}
	bool containCore = false;//标记BFS是否搜索到了核心
	std::queue<Coordinate> myQueue;
	myQueue.push(this->core);//从核心位置开始BFS
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
			if (it != temp.end() && !(it->second)) {//如果邻点存在且未被访问过
				myQueue.push(xy2);
				it->second = true;
			}
		}
	}
	//std::
	//  << count << std::endl;
	//std::cout << temp.size() << std::endl;
	if (count != temp.size()) {//有坐标没被搜索到则说明有断裂
		//将BFS未搜索到的点删除
		for (auto& pair : temp) {
			if (!(pair.second)) {
				//std::cout << "删除点" << pair.first.x << "," << pair.first.y << std::endl;
				//blockMap.erase(pair.first);
				count++;
			}
		}
	}
	//std::cout << count << std::endl;
}

