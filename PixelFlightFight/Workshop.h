//#pragma once
////#include "Globals.h"
//#include "Entity.h"
//class PlaneTemplate : public Block //--------------->>>>>���ﻹ��Ҫ�̳���
//{
//public:
//	std::vector<Coordinate> core;		// ��Щ�Ǻ�������
//	int coreCountMax;					// ������������
//	Speed speed;						// �ӵ�/�ɻ��ٶ�
//
//	//ȡ�� --------------------------------------���������������������������������������һ��spriteMap �������ͨ��Ԫ��
//	std::vector<Coordinate> spriteMap;
//
//	PlaneTemplate();					// core Ĭ��Ϊ1
//	PlaneTemplate(int coreCount);		// ָ�������������������� BOSS ����1��
//	~PlaneTemplate();
//
//	void AddPixel(Coordinate pos);		// ����һ������
//	void ErasePixel(Coordinate pos);	// ȡ��һ������
//	void SetCore(Coordinate pos);		// ����һ����������
//	void UnsetCore(Coordinate pos);		// ȡ������һ����������
//	/*void SavePlane();
//	static PlaneTemplate LoadPlane(PlaneId id);*/
//
//	//ȡ�����������һ�����������طɻ������أ��÷ɻ����ص�λ���� �Ժ��� ��0�� 0������ŵ� 
//	std::vector<Coordinate> DesignPlane();
//};
//
//
///******�ص�*******/
//class PlaneCanvas
//{
//public:
//	COLORREF paintColor;
//	PlaneTemplate paintPlane;
//
//	PlaneCanvas(COLORREF color);					// �������ǰ��ָ�� RGB�������� #FF0000 (���ĵ���ɫ)�������ڲ��Խ׶Σ�Ϊ��������BOSS��������������ӦΪ1
//	~PlaneCanvas();
//
//	void On(Coordinate pos);						// ����������꣬�û���֪���������
//	void Click(Coordinate pos, bool left = true);	// ��������������������Ҽ����û���֪��������ɶ�����һ�����أ��Ҽ����ģ�
//};
//
//// ����ɻ�ģ�壬��������һ��ʵ���ģ�� InstanceTemplate��ֻ����Ϊ���ֻ������������ɻ������ԲŽ� PlaneTemplate
//
//
//
