#include "Entity.h"

int I_IdCounter = 1;
int SCORE = 0;
int GAMEEND = 1;
std::vector<Coordinate> DEFAULTPLANE{ {0,0},{0,-1},{1,0},{0,1} };//默认飞机
Coordinate PLAYERPLANECORE(15, 35);	//默认飞机核心位置

std::unordered_map<Coordinate, Bullet> Bullet::ENEMYMAP;			//敌机map
std::unordered_map<Coordinate, Block> Bullet::PlayerPlaneBlock;		// 玩家飞机拥有的像素（对与核心的相对坐标)
std::vector<Bullet*> Bullet::AllEntities;// 所有实体

/// <summary>
/// Block
/// </summary>
Block::Block()
{
	blockID = I_IdCounter++;//分配id
	std::cout << "分配ID " << blockID << " / " << I_IdCounter << std::endl;
}
Block::~Block()
{
	std::cout << "释放块: " << blockID << std::endl;
	// 从PlayerPlaneBlock中移除
	/*for (auto it = PlayerPlaneBlock.begin(); it != PlayerPlaneBlock.end(); ++it) {
		if (it->second == *this) {
			PlayerPlaneBlock.erase(it);
			break;
		}
	}*/
}

void Block::Resource()
{
	std::cout << "移除块实例: " << blockID << std::endl;

}


/// <summary>
/// Bullet
/// </summary>
Bullet::Bullet()//子弹构造函数 
{
	entityType = _EntityBullet;		//默认是子弹
	core = PLAYERPLANECORE;				// 核心坐标
	autoSpeed = Speed(0, -1);			// 固有速度
	tileCountMax = 1;				// 拥有的像素上限
	tileCount = 1;					// 剩余的像素
	//Scroll scroll = Scroll::GetInstance();
	AllEntities.push_back(this);//将自己放入allEntities
}


Bullet::~Bullet()
{
	std::cout << "释放子弹: ";
	// 在Bullet析构函数中移除实例	
}


void Bullet::AutoMove()
{
	this->core.x += this->autoSpeed.x;
	this->core.y += this->autoSpeed.y;
}

void Bullet::PlayerMove(Speed speed) {}

void Bullet::CollisionDetection()//碰撞检测
{
	//if (entityType = _EntityBullet) {//子弹
	auto it = ENEMYMAP.find(core);
	if (it != ENEMYMAP.end())//发生碰撞
	{
		std::cout << "子弹碰撞: " << blockID << std::endl;
		it->second.Resource();
		ENEMYMAP.erase(it);
		Resource();
		return;
	}
	//}
}

void Bullet::Resource()//销毁
{
	std::cout << "从allEntities中移除: " << blockID << std::endl;

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
	entityType = _EntityEnemy;	//默认是敌机
	core = { 50,0 };
	autoSpeed = { 0,1 };	// 固有速度
	tileCountMax = 1;	// 拥有的像素上限
	tileCount = 1;		// 剩余的像素
}
Plane::Plane(Coordinate co)
{
	entityType = _EntityEnemy;	//默认是敌机
	core = co;
	autoSpeed = { 0,1 };	// 固有速度
	tileCountMax = 1;	// 拥有的像素上限
	tileCount = 1;		// 剩余的像素
}
Plane::~Plane() {
	std::cout << "释放飞机: " << blockID << std::endl;
}
void Plane::PlayerMove(Speed speed) {}
void Plane::CollisionDetection()
{
	if (entityType = _EntityEnemy) {//敌机
		{

			for (std::vector<Bullet*>::iterator it = Bullet::AllEntities.begin(); it != Bullet::AllEntities.end(); ++it) {
				Bullet* bullet = *it;

				if (bullet->core == core)
				{
					std::cout << "敌机碰撞: " << blockID << std::endl;
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
PlayerPlane::PlayerPlane()//默认飞机 
{
	blockID = 0;
	entityType = _EntityPlayer;
	core = PLAYERPLANECORE;
	autoSpeed = { 0,0 };
	tileCountMax = 4;	// 拥有的像素上限
	tileCount = 4;		// 剩余的像素
	Block pp1;
	Block pp2;
	Block pp3;
	std::unordered_map<Coordinate, Block> hmap{ {{-1,0},pp1},{{1,0},pp2},{{0,-1},pp3} };
	PlayerPlaneBlock.clear();
	PlayerPlaneBlock = hmap;
};

PlayerPlane::PlayerPlane(std::vector<Coordinate> tblockMap) //创建飞机 
{
	blockID = 0;
	entityType = _EntityPlayer;
	core = PLAYERPLANECORE;
	autoSpeed = { 0,0 };
	tileCountMax = tblockMap.size();	// 拥有的像素上限
	tileCount = tblockMap.size();		// 剩余的像素
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
	std::cout << "释放玩家飞机: " << blockID << std::endl;
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
		line(BLANK_L, BLANK_U, BLANK_R, BLANK_U);  // 绘制垂直线
		line(BLANK_L, BLANK_U, BLANK_L, BLANK_D);  // 绘制垂直线
		line(BLANK_L, BLANK_D, BLANK_R, BLANK_D);  // 绘制垂直线
		line(BLANK_R, BLANK_U, BLANK_R, BLANK_D);  // 绘制垂直线
	}
	if (this->core.y + speed.y <= MAPSIZE_Y && this->core.x + speed.x >= 0) {
		this->core.y += speed.y;
		PLAYERPLANECORE.y += speed.y;
	}
	else {
		setlinecolor(SECONDCOLOR);
		setlinestyle(PS_SOLID, 2);
		line(BLANK_L, BLANK_U, BLANK_R, BLANK_U);  // 绘制垂直线
		line(BLANK_L, BLANK_U, BLANK_L, BLANK_D);  // 绘制垂直线
		line(BLANK_L, BLANK_D, BLANK_R, BLANK_D);  // 绘制垂直线
		line(BLANK_R, BLANK_U, BLANK_R, BLANK_D);  // 绘制垂直线

	}
}

void PlayerPlane::CollisionDetection()
{
	if (entityType = _EntityPlayer) {//自机

		if (ENEMYMAP.find(core) != ENEMYMAP.end())
		{
			std::cout << "核心碰撞: " << blockID << std::endl;

			GAMEEND = 0;//游戏结束		
		}
		else {
			for (auto it = PlayerPlaneBlock.begin(); it != PlayerPlaneBlock.end(); )
			{
				const Coordinate& coord = it->first;

				if (ENEMYMAP.find(coord) != ENEMYMAP.end())
				{
					std::cout << "我机碰撞: " << it->second.blockID << std::endl;
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
	std::cout << count << std::endl;
	std::cout << temp.size() << std::endl;
	if (count != temp.size()) {//有坐标没被搜索到则说明有断裂
		//将BFS未搜索到的点删除
		for (auto& pair : temp) {
			if (!(pair.second)) {
				std::cout << "删除点" << pair.first.x << "," << pair.first.y << std::endl;
				//blockMap.erase(pair.first);
				count++;
			}
		}
	}
	std::cout << count << std::endl;
}

