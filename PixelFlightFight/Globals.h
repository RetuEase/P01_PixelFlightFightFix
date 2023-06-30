#pragma once
//#pragma comment( linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" )
#include <iostream>
//#include <fstream>
//#include <sstream>
#include <string>
#include <vector>
#include <queue>
//#include <unordered_set>
#include <unordered_map>
#include <conio.h>
//#include <Windows.h>
#include <graphics.h>

#define DEBUG

// 界面大小
#define WINDOWS_X	1265
#define WINDOWS_Y	780

#define MAPSIZE_X	31	//游戏界面宽度
#define MAPSIZE_Y	50 //游戏页面高度
#define BLOCKSIZE	15

#define BLANK_U 15	//上边框
#define BLANK_D 765	//下
#define BLANK_L 400	//左
#define BLANK_R 865	//右


//颜色 BGR
#define BGCOLOR		0X020202//黑//0Xecec81	//light blue 背景
#define OTHERCOLOR	0X612C18//深蓝 //0Xc9ce00	//blue		 前景
#define BACKCOLOR	0Xfba464//边框 蓝 //0Xc9ce00	//blue		 后景
#define SECONDCOLOR	0Xfba464//页面强调 金色
#define CORECOLOR	0X3f30d3//核心 红色
#define BULLETCOLOR 0X612C18//子弹/自己 深蓝

#define GOLDENCOLOR 0X00f2ff//字体 金
//#fff200
//0X612C18
//0X971f34
//0Xc3beb2	灰色
//0X3f30d3  红
//0X3ec8d4  金色 #fbc531
//0Xfba464
//0X66acae
//刷新与移动
#define FRAMEINTERVAL 40	//周期间隔 ms
#define UNITTIME	8	//单位时间刷新次数
#define PLANERATE	4	//自机周期刷新率 
#define BULLETRATE	8	//子弹周期刷新率 
#define ENEMYRATE	1	//敌机周期刷新率 
#define FIRERATE	2	//发射间隔刷新率 

#define ENEMIESNUM	20	//敌人数量

// 飞机移动方向
#define MOVE_RIGHT	1	//0001
#define MOVE_UP		2	//0010
#define MOVE_LEFT	4	//0100
#define MOVE_DOWN	8	//1000

#define MOVE_RU		3	//0011
#define MOVE_UL		6	//0110
#define MOVE_LD		12	//1100
#define MOVE_DR		9	//1001

// 瓦片容器元素中包含特别的实体信息
#define TILE_PLAYER			1
#define TILE_PLAYER_BULLET -1

// type
#define TYPE_PLANE	1
#define TYPE_BULLET 2

// 按键识别数组长度
#define KEY_COUNT	6

// 飞机最大的规格
#define PLANE_MAX_X 60
#define PLANE_MAX_Y 60

// 飞机工坊中的单元像素边长
#define UNIT_EDGE 10

// 二维结构
struct Vector2
{
	int x, y;
	Vector2()
		:x(0), y(0) {}
	/*explicit Vector2(Vector2& v)
	{
		this->x = v.x;
		this->y = v.y;
	}*/
	Vector2(int x, int y)
		:x(x), y(y) {}
	bool operator==(const Vector2& other) const
	{
		return x == other.x && y == other.y;
	}
};
// 哈希函数特化
namespace std {
	template <>
	struct hash<Vector2> {
		std::size_t operator()(const Vector2& v) const {
			return std::hash<int>()(v.x) + std::hash<int>()(v.y) * MAPSIZE_X;
		}
	};
}
//typedef Bullet* BulletPtr;
using InsId = long long;
using PlaneId = long long;
//int I_IdCounter = 1;
//bool GAMEEND = false;
//int score = 0;//分数

//实体类型
enum EntityType { _EntityBullet, _EntityEnemy, _EntityPlayer, _EntityNull };

using Coordinate = Vector2;	// 坐标 (x,y)
using Speed = Vector2;		// 速度方向 (x,y)

extern int I_IdCounter;
extern int GAMEEND;
extern int SCORE;
//struct ScrollTile
//{
//	std::vector<InsId> tileContainer;	// 这一像素包含了些什么实体 id
//};
