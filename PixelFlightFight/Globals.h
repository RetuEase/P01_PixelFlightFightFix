#pragma once
#pragma comment( linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" )
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <graphics.h>

/*
	熊猫giegie良心分享
	共同写代码
	创建文明小组
	哈哈哈哈哈
*/

#define DEBUG

// 界面大小
#define WINDOWS_X	1000
#define SCROLL_X	600
#define WINDOWS_Y	800

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

using InsId = int;
using PlaneId = long long;

// 二维结构
struct Vector2
{
	int x, y;

	Vector2()
		:x(0), y(0) {}

	Vector2(int x, int y)
		:x(x), y(y) {}

	bool operator==(const Vector2& other) const
	{
		return x == other.x && y == other.y;
	}
};

using Coordinate = Vector2;	// 坐标 (x,y)
using Speed = Vector2;		// 速度方向 (x,y)

// 哈希函数特化
namespace std
{
	template <>
	struct hash<Vector2>
	{
		std::size_t operator()(const Vector2& obj) const
		{
			// 使用哈希算法计算对象的哈希值
			return std::hash<int>()(obj.x) + std::hash<int>()(obj.y);
		}
	};
}