#pragma once
//#pragma comment( linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" )
#include <iostream>
//#include <fstream>
//#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <random>
//#include <unordered_set>
#include <unordered_map>
#include <conio.h>
//#include <Windows.h>
#include <graphics.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib") 

#define DEBUG

// �����С
#define WINDOWS_X	1265//���ڴ�С
#define WINDOWS_Y	780

#define MAPSIZE_X	31//��Ϸ���泤��  ��ͼ31*50 
#define MAPSIZE_Y	50//��Ϸҳ��߶�
#define BLOCKSIZE	15//���ӿ��


#define WORKSHOP_X	10//��	�ɻ��������� 
#define WORKSHOP_Y	10//��
#define WORKSHOP_SIZE	46//��
#define WORKSHOP_U 	266//��
#define WORKSHOP_D 	726//��
#define WORKSHOP_L 	402//��
#define WORKSHOP_R 	862//��

#define BLANK_U 15	//�ϱ߿�
#define BLANK_D 765	//��
#define BLANK_L 400	//��
#define BLANK_R 865	//��


//��ɫ BGR
#define BGCOLOR		0X020202//��//0Xecec81	//light blue ����
#define OTHERCOLOR	0X612C18//���� //0Xc9ce00	//blue		 ǰ��
#define BACKCOLOR	0Xfba464//�߿� �� //0Xc9ce00	//blue		 ��
#define SECONDCOLOR	0Xfba464//ҳ��ǿ�� ��ɫ
#define CORECOLOR	0X3f30d3//���� ��ɫ
#define BULLETCOLOR 0X612C18//�ӵ�/�Լ� ����

#define GOLDENCOLOR 0X00f2ff//���� ��
//#fff200
//0X612C18
//0X971f34
//0Xc3beb2	��ɫ
//0X3f30d3  ��
//0X3ec8d4  ��ɫ #fbc531
//0Xfba464
//0X66acae
//ˢ�����ƶ�
#define WORKSHOPFLASH	30	//�ɻ�����ˢ�����ڼ�� ms


#define FRAMEINTERVAL	20	//���ڼ�� ms
#define UNITTIME	8	//��λʱ��ˢ�´���
#define PLANERATE	4	//�Ի�����ˢ���� 
#define BULLETRATE	8	//�ӵ�����ˢ���� 
#define ENEMYRATE	1	//�л�����ˢ���� 
#define FIRERATE	2	//������ˢ���� 

#define ENEMIESNUM	20	//��������

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

#define ENEMIESNUMBER 40

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
// ��ϣ�����ػ�
namespace std {
	template <>
	struct hash<Vector2> {
		std::size_t operator()(const Vector2& v) const {
			return std::hash<int>()(v.x) + std::hash<int>()(v.y) * MAPSIZE_X;
		}
	};
}
//typedef Bullet* bulletptr->
using InsId = long long;
using PlaneId = long long;
//int I_IdCounter = 1;
//bool GAMEEND = false;
//int score = 0;//����

//ʵ������
enum EntityType { _EntityNull, _EntityBullet, _EntityEnemy, _EntityPlayer };

using Coordinate = Vector2;	// ���� (x,y)
using Speed = Vector2;		// �ٶȷ��� (x,y)

extern int I_IdCounter;
extern int GAMEEND;
extern int SCORE;
//struct ScrollTile
//{
//	std::vector<InsId> tileContainer;	// ��һ���ذ�����Щʲôʵ�� id
//};
