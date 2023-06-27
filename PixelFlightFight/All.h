#pragma once
#include <vector>
#include <unordered_map>
#include <graphics.h>

#include "Globals.h"

using InsId = int;

// ����ṹ
struct Vector2
{
	int x, y;

	Vector2()
		:x(0), y(0) {}

	Vector2(int x, int y)
		:x(x), y(y) {}
};

using Coordinate = Vector2;	// ���� (x,y)
using Speed = Vector2;		// �ٶȷ��� (x,y)

// ѭ��������
class GameLoop
{
	int flag;					// ����������
	bool keyDown[KEY_COUNT];	// �����İ���״̬
	GameLoop();

public:
	~GameLoop();
	static GameLoop& GetInstance();	// ���ص���
	void Run();						// ��ʼѭ��

private:
	void MainMenuLoop();		// ������
	void SelectLevelLoop();		// ѡ�ؽ���
	void PlaneWorkshopLoop();	// �ɻ���������
	void PlaneBattleLoop();		// �ɻ�ս������

	void BattleMenuLoop();		// ս���˵���������
	void BattleDefeatLoop();	// ս��ʧ�ܵ�������
	void BattleVictoryLoop();	// ս��ʤ����������
};

/* �������� */
class Label
{
protected:
	union LabelContainer
	{
		IMAGE image;
		LPCTSTR text;
	};
	Coordinate pos;			// ���Ͻǵ�����
	LabelContainer container;
public:
	Label();
	Label(IMAGE image);
	Label(LPCTSTR text);
	~Label();
	Coordinate getPos();	// ��ȡ pos
	void RenderToWindows();	// ��Ⱦ������
};

class Button : public Label
{
	int (*FuncPtr)();
public:
	Button(int (*FuncPtr)());	// ��������ťʱ�Ļص�����
	Button(IMAGE image, int (*FuncPtr)());
	Button(LPCTSTR text, int (*FuncPtr)());
	~Button();					// ������ָ��
	bool On(Coordinate pos);	// ����������꣬�����Ƿ��������ť��
	int Click();				// ��⵽����������ť�ϵ��ʱ����
};

/* �ɻ�ս������ */

// ս�������ࣨ����֪������ս����һ�У�
class Scroll
{
protected:
	struct ScrollTile
	{
		std::vector<InsId> tileContainer;	// ��һ���ذ�����Щʲôʵ�� id
	};
	std::unordered_map<Coordinate, ScrollTile> scrollMap;	// �����Ӧ����Ϣ
	std::unordered_map<InsId, Bullet> instanceRepo;			// ����ʵ��Ĳֿ�
public:
	Scroll();
	~Scroll();
};

// �����ͼ�ĵ�λ
class Sprite
{
protected:
	std::unordered_map<Coordinate, COLORREF> spriteMap;		// ӵ�е�����
public:
	Sprite();
	Sprite(Coordinate pos);
	void RenderToWindows();
};

// �����ƶ�ʱ�ĵ�λ
class Bullet : public Sprite
{
protected:
	int type;
	InsId id;
	Speed autoSpeed;			// �����ٶ�
public:
	Bullet();
	Bullet(Coordinate pos);
	void AutoMove();			// �����ƶ�
	void CollisionDetection();	// ��ײ���
};

class Plane : public Bullet
{
public:
	Plane();
	Plane(Coordinate pos);
};

class PlayerPlane : public Plane
{
public:
	void ManualMove(Speed speed);	// ��ʱ�ٶȣ�ֻ�е��ܵ�����ʱ�������ٶȣ�
};