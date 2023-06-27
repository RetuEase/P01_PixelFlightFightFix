#pragma once
#include "Globals.h"
#include "Entity.h"

/******�ص�*******/
class PlaneCanvas
{
	COLORREF paintColor;
	PlaneTemplate paintPlane;

public:
	PlaneCanvas(COLORREF color);					// �������ǰ��ָ�� RGB�������� #FF0000 (���ĵ���ɫ)�������ڲ��Խ׶Σ�Ϊ��������BOSS��������������ӦΪ1
	~PlaneCanvas();

	void On(Coordinate pos);						// ����������꣬�û���֪���������
	void Click(Coordinate pos, bool left = true);	// ��������������������Ҽ����û���֪��������ɶ�����һ�����أ��Ҽ����ģ�
};

// ����ɻ�ģ�壬��������һ��ʵ���ģ�� InstanceTemplate��ֻ����Ϊ���ֻ������������ɻ������ԲŽ� PlaneTemplate
class PlaneTemplate : public Sprite
{
	friend PlaneCanvas;
	std::vector<Coordinate> core;		// ��Щ�Ǻ�������
	int coreCountMax;					// ������������
	Speed speed;						// �ӵ�/�ɻ��ٶ�

public:
	PlaneTemplate();					// core Ĭ��Ϊ1
	PlaneTemplate(int coreCount);		// ָ�������������������� BOSS ����1��
	~PlaneTemplate();

	void AddPixel(Coordinate pos);		// ����һ������
	void ErasePixel(Coordinate pos);	// ȡ��һ������
	void SetCore(Coordinate pos);		// ����һ����������
	void UnsetCore(Coordinate pos);		// ȡ������һ����������

	void SavePlane();
	static PlaneTemplate LoadPlane(PlaneId id);
}; 


#pragma once
