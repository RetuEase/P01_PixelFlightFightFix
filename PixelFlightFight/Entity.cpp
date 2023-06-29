#include "Entity.h"

using namespace std;
/// <summary>
/// Block
/// </summary>
Block::Block()
{
	blockID = I_IdCounter++;//分配id
}
Block::~Block() {}

/// <summary>
/// Bullet
/// </summary>
Bullet::Bullet() {//子弹构造函数 
	entityType = _EntityBullet;		//默认是子弹
	core = MyPLANECORE;				// 核心坐标
	autoSpeed = { 0,-1 };			// 固有速度
	tileCountMax = 1;				// 拥有的像素上限
	tileCount = 1;					// 剩余的像素
	Scroll scroll = Scroll::GetInstance();
	scroll.allEntities.push_back(this);//将自己放入allEntities
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



void Bullet::CollisionDetection()//碰撞检测
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
	entityType = _EntityEnemy;	//默认是敌机
	core = { 50,0 };
	autoSpeed = { 1,0 };	// 固有速度
	tileCountMax = 1;	// 拥有的像素上限
	tileCount = 1;		// 剩余的像素
}
Plane::Plane(Coordinate co)
{
	entityType = _EntityEnemy;	//默认是敌机
	core = co;
	autoSpeed = { 1,0 };	// 固有速度
	tileCountMax = 1;	// 拥有的像素上限
	tileCount = 1;		// 剩余的像素
}
Plane::~Plane() {}

//void Plane::Destroy(Coordinate core){}
void Plane::Fracture() {}

/// <summary>
/// PlayerPlane
/// </summary>
PlayerPlane::PlayerPlane()//默认飞机 
{
	entityType = _EntityPlayer;
	core = MyPLANECORE;
	autoSpeed = { 0,0 };
	tileCountMax = 4;	// 拥有的像素上限
	tileCount = 4;		// 剩余的像素
	Block pp1;
	Block pp2;
	Block pp3;
	unordered_map<Coordinate, Block> hmap{ {{-1,0},pp1},{{1,0},pp2},{{0,-1},pp3} };
	blockMap = hmap;
};

//<Coordinate, Block>

PlayerPlane::PlayerPlane(std::vector<Coordinate> tblockMap) //创建飞机 
{
	entityType = _EntityPlayer;
	core = MyPLANECORE;
	autoSpeed = { 0,0 };
	tileCountMax = tblockMap.size();	// 拥有的像素上限
	tileCount = tblockMap.size();		// 剩余的像素
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
	int count = 0;//用于记录BFS搜索了几个点
	unordered_map<Coordinate, bool> temp;
	for (auto& pair : this->blockMap) {
		temp.insert(make_pair(pair.first, false));//将全部点装入临时map
	}
	//bool containCore = false;//标记BFS是否搜索到了核心
	queue<Coordinate> myQueue;
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
	std::cout << count << endl;
	std::cout << temp.size() << endl;
	if (count != temp.size()) {//有坐标没被搜索到则说明有断裂
		//将BFS未搜索到的点删除
		for (auto& pair : temp) {
			if (!(pair.second)) {
				std::cout << "删除点" << pair.first.x << "," << pair.first.y << endl;
				this->blockMap.erase(pair.first);
				count++;
			}
		}
	}
	std::cout << count << endl;
}

