#include "Instance.h"
#include "Globals.h"
#include <unordered_set>
#include <queue>
#include <iostream>
using namespace std;

/******* �����ˣ�null *******/

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
	//3*3��Ĭ�ϰ�ɫ�ӵ�
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
	this->pos = pos;//3*3���ӵ����������꼴ΪPOS
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

/***********����֮��***********/
void Bullet::CollisionDetection()
{
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
	int count = 0;//���ڼ�¼BFS�����˼�����
	unordered_map<Coordinate, bool> temp;
	for (auto& pair : this->spriteMap) {
		temp.insert(make_pair(pair.first, false));//��ȫ����װ����ʱmap
	}
	//bool containCore = false;//���BFS�Ƿ��������˺���
	queue<Coordinate> myQueue;
	myQueue.push(this->core[0]);//�Ӻ���λ�ÿ�ʼBFS
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
			if (it != temp.end() && !(it->second)) {//����ڵ������δ�����ʹ�
				myQueue.push(xy2);
				it->second = true;
			}
		}
	}
	cout << count << endl;
	cout << temp.size() << endl;
	if (count != temp.size()) {//������û����������˵���ж���
		//��BFSδ�������ĵ�ɾ��
		for (auto& pair : temp) {
			if (!(pair.second)) {
				//cout << "ɾ����" << pair.first.x << "," << pair.first.y << endl;
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
	//x�Ĵ���
	if (this->pos.x == SCROLL_X) {
		this->pos.x += min(speed.x, 0);
	}
	else if (this->pos.x == 0) {
		this->pos.x += max(speed.x, 0);
	}
	else {
		this->pos.x += speed.x;
	}
	//y�Ĵ���
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