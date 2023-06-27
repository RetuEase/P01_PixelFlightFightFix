#pragma once
#pragma comment( linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" )
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <graphics.h>

/*
	��ègiegie���ķ���
	��ͬд����
	��������С��
	����������
*/

#define DEBUG

// �����С
#define WINDOWS_X	1000
#define SCROLL_X	600
#define WINDOWS_Y	800

// �ɻ��ƶ�����
#define MOVE_RIGHT	1	//0001
#define MOVE_UP		2	//0010
#define MOVE_LEFT	4	//0100
#define MOVE_DOWN	8	//1000

#define MOVE_RU		3	//0011
#define MOVE_UL		6	//0110
#define MOVE_LD		12	//1100
#define MOVE_DR		9	//1001

// ��Ƭ����Ԫ���а����ر��ʵ����Ϣ
#define TILE_PLAYER			1
#define TILE_PLAYER_BULLET -1

// type
#define TYPE_PLANE	1
#define TYPE_BULLET 2

// ����ʶ�����鳤��
#define KEY_COUNT	6

// �ɻ����Ĺ��
#define PLANE_MAX_X 60
#define PLANE_MAX_Y 60

// �ɻ������еĵ�Ԫ���ر߳�
#define UNIT_EDGE 10

using InsId = int;
using PlaneId = long long;

// ��ά�ṹ
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

using Coordinate = Vector2;	// ���� (x,y)
using Speed = Vector2;		// �ٶȷ��� (x,y)

// ��ϣ�����ػ�
namespace std
{
	template <>
	struct hash<Vector2>
	{
		std::size_t operator()(const Vector2& obj) const
		{
			// ʹ�ù�ϣ�㷨�������Ĺ�ϣֵ
			return std::hash<int>()(obj.x) + std::hash<int>()(obj.y);
		}
	};
}