#include "Entity.h"
#include "Globals.h"
#include <unordered_set>
#include <queue>
#include <iostream>


using namespace std;

Sprite::Sprite()
{
	this->planeId = 0;
}

Sprite::~Sprite()
{
}
LONGLONG Sprite::getPlaneId() {
	return this->planeId;
}
void Sprite::setPlaneId(long long id) {
	this->planeId = id;
}
Bullet::Bullet()
	:type(TYPE_BULLET), tileCountMax(9), tileCount(9), insId(0)
{
}
Bullet::Bullet(Coordinate pos)
	:type(TYPE_BULLET), tileCountMax(9), tileCount(9), insId(0)
{
	this->pos = pos;
	//3*3的默认白色子弹
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			Vector2 point(i, j);
			this->spriteMap.insert(std::make_pair(point, 0xffffff));
		}
	}
	this->tileCountMax = 9;
	this->tileCount = 9;
}
Bullet::Bullet(Coordinate pos, std::unordered_map<Coordinate, COLORREF> spriteMap)
	:type(TYPE_BULLET), tileCountMax(9), tileCount(9), insId(0)
{
	int count = 0;
	for (auto& pair : spriteMap) {
		this->spriteMap.insert(std::make_pair(pair.first, pair.second));
		count++;
	}
	this->pos = pos;//3*3的子弹，中心坐标即为POS
	this->tileCountMax = count;
	this->tileCount = count;
}

Bullet::~Bullet()
{
}
void Bullet::setInsId(int id) {
	this->insId = id;
}
int Bullet::getInsId() {
	return this->insId;
}
void Bullet::sesSpeed(int x, int y) {
	this->autoSpeed.x = x;
	this->autoSpeed.y = y;
}
Speed Bullet::getSpeed() {
	return this->autoSpeed;
}

void Bullet::AutoMove()
{
	this->pos.x += this->autoSpeed.x;
	this->pos.y += this->autoSpeed.y;
}

void Bullet::RenderToScroll()
{
	for (const auto& pair : this->spriteMap) {
		Coordinate key = pair.first;
		COLORREF value = pair.second;
		putpixel(this->pos.x + key.x, this->pos.y + key.y, value);
	}
}

/***********重中之重***********/
//加了个全局变量 哈希表<自己的ID,和自己相撞的ID> 待消除实体列表
std::unordered_map<InsId, InsId> waitingEliminatedInsId;

void Bullet::CollisionDetection()
{
	//检测碰撞检测
	//会调用scroll的DeleteInstance()消除碰撞相消的实例
	//重叠而不会湮灭的不消除

	Scroll scroll = Scroll::GetInstance();	//调用Scroll单例
	
	//先判断自己是否在待消除列表里
	if (waitingEliminatedInsId.find(insId) != waitingEliminatedInsId.end())
	{
		std::unordered_map < InsId, InsId > ::iterator itr = waitingEliminatedInsId.find(insId);
		std::pair<InsId, InsId> pair = *itr;
		scroll.DeleteInstance(pair.first);
		scroll.DeleteInstance(pair.second);
		std::shared_ptr<Bullet> p1(this);
		return;
	}
	else if (autoSpeed.y == 0)
	{
		return;
	}
	else
	{
		Coordinate nowCoordinate = pos;			//当前位置坐标

		std::unordered_map<Coordinate, Scroll::ScrollTile>::iterator  itr = scroll.scrollMap.end();//scrollMap的迭代器
		Coordinate tCoordinate{ pos.x,pos.y };				//检测位置坐标
		int isNeg = 0;
		if (autoSpeed.y > 0)
		{
			isNeg = 1;
		}
		else {
			isNeg = -1;
		}
		//检测尾迹
		for (int i = nowCoordinate.y - autoSpeed.y; i != nowCoordinate.y; i -= isNeg)
		{
			tCoordinate.y = i;
			std::pair<Coordinate, Scroll::ScrollTile> CSpair = *scroll.scrollMap.find(tCoordinate);
			Scroll::ScrollTile st = CSpair.second;
			std::vector<InsId> tv = st.tileContainer;
			if (tv.size() != 0)
			{
				std::unordered_map<InsId, Bullet>::iterator iter;
				std::pair<InsId, Bullet> pair;
				std::pair<InsId, Bullet> endPair = *scroll.instanceRepo.end();
				//如果自身是子弹，则只会碰撞敌机
				if (GetEntityType() == EntityType::_EntityBullet) {
					for (int i = 0; i < tv.size(); i++)
					{
						InsId tid = tv[i];
						iter = scroll.instanceRepo.find(tid);
						pair = *iter;
						if (pair != endPair)
						{
							pair = *iter;
							if (pair.second.GetEntityType() == EntityType::_EntityEnemy)
							{
								scroll.DeleteInstance(pair.second.insId);
								scroll.DeleteInstance(insId);
								return;
							}

						}
					}
				}
				//如果自身是敌机，则会碰撞子弹和自机
				if (GetEntityType() == EntityType::_EntityEnemy) {
					for (int i = 0; i < tv.size(); i++)
					{
						InsId tid = tv[i];
						iter = scroll.instanceRepo.find(tid);
						pair = *iter;
						if (pair != endPair)
						{
							pair = *iter;
							if (pair.second.GetEntityType() == EntityType::_EntityBullet || pair.second.GetEntityType() == EntityType::_EntityPlayer)
							{
								scroll.DeleteInstance(pair.second.insId);
								scroll.DeleteInstance(insId);
								return;
							}

						}
					}
				}
				//自机不自己检测碰撞
			}

		}
		//检测轨迹,下次检测时消除
		for (int i = nowCoordinate.y; i != nowCoordinate.y + autoSpeed.y; i += isNeg)
		{
			tCoordinate.y = autoSpeed.y + i;
			std::pair<Coordinate, Scroll::ScrollTile> CSpair = *scroll.scrollMap.find(tCoordinate);
			Scroll::ScrollTile st = CSpair.second;
			std::vector<InsId> tv = st.tileContainer;
			if (tv.size() != 0)
			{
				std::unordered_map<InsId, Bullet>::iterator iter;
				std::pair<InsId, Bullet> pair;
				std::pair<InsId, Bullet> endPair = *scroll.instanceRepo.end();
				//如果自身是子弹，则只会碰撞敌机
				if (GetEntityType() == EntityType::_EntityBullet) {
					for (int i = 0; i < tv.size(); i++)
					{
						InsId tid = tv[i];
						iter = scroll.instanceRepo.find(tid);
						pair = *iter;
						if (pair != endPair) {

							if (pair.second.GetEntityType() == EntityType::_EntityEnemy)
							{
								waitingEliminatedInsId.insert({ insId,pair.second.insId });
								return;
							}

						}
					}
				}
				//如果自身是敌机，则会碰撞子弹和自机
				if (GetEntityType() == EntityType::_EntityEnemy) {
					for (int i = 0; i < tv.size(); i++)
					{
						InsId tid = tv[i];
						iter = scroll.instanceRepo.find(tid);
						pair = *iter;
						if (pair != endPair) {
							pair = *iter;
							if (pair.second.GetEntityType() == EntityType::_EntityBullet || pair.second.GetEntityType() == EntityType::_EntityPlayer)
							{
								waitingEliminatedInsId.insert({ insId,pair.second.insId });
								return;
							}

						}
					}
				}
				//自机不自己检测碰撞
			}
		}
	}
}

Plane::Plane()
{
}

Plane::Plane(Coordinate pos, std::unordered_map<Coordinate, COLORREF> spriteMap)
	:Bullet(pos, spriteMap)
{
	type = TYPE_PLANE;
	core.push_back(Vector2(0, 0));
}

Plane::~Plane()
{
}

void Plane::Destroy(Coordinate pos)
{
	if (this->spriteMap.find(pos) != this->spriteMap.end()) {
		this->spriteMap.erase(pos);
	}
}
/******BFS******/
void Plane::Fracture()
{
	int arr[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
	int count = 0;//用于记录BFS搜索了几个点
	unordered_map<Coordinate, bool> temp;
	for (auto& pair : this->spriteMap) {
		temp.insert(make_pair(pair.first, false));//将全部点装入临时map
	}
	//bool containCore = false;//标记BFS是否搜索到了核心
	queue<Coordinate> myQueue;
	myQueue.push(this->core[0]);//从核心位置开始BFS
	temp[core[0]] = 1;
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
	cout << count << endl;
	cout << temp.size() << endl;
	if (count != temp.size()) {//有坐标没被搜索到则说明有断裂
		//将BFS未搜索到的点删除
		for (auto& pair : temp) {
			if (!(pair.second)) {
				cout << "删除点" << pair.first.x << "," << pair.first.y << endl;
				this->spriteMap.erase(pair.first);
				count++;
			}
		}
	}
	cout << count << endl;
}
void Plane::setCore(vector<Coordinate> core) {
	for (int i = 0; i < core.size(); i++) {
		this->core.push_back(core[i]);
	}
}

PlayerPlane::PlayerPlane()
{
}

PlayerPlane::~PlayerPlane()
{
}
PlayerPlane::PlayerPlane(Coordinate pos, std::unordered_map<Coordinate, COLORREF> spriteMap)
	:Plane(pos, spriteMap)
{
}
void PlayerPlane::ManualMove(Speed speed)
{
	//x的处理
	if (this->pos.x == SCROLL_X) {
		this->pos.x += min(speed.x, 0);
	}
	else if (this->pos.x == 0) {
		this->pos.x += max(speed.x, 0);
	}
	else {
		this->pos.x += speed.x;
	}
	//y的处理
	if (this->pos.y == WINDOWS_Y) {
		this->pos.y += min(speed.y, 0);
	}
	else if (this->pos.y == 0) {
		this->pos.y += max(speed.y, 0);
	}
	else {
		this->pos.y += speed.y;
	}
}
