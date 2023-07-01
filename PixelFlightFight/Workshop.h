#pragma once
#include "Globals.h"
//#include "Entity.h"
class PlaneTemplate
{
public:
	std::vector<Coordinate> core;		// ��Щ�Ǻ�������
	int coreCountMax;					// ��������
	int planCountMax;					// ��������
	std::vector<Coordinate> spriteMap;	//��������˸�spriteMap �������ͨ��Ԫ��----ȡ��
	static std::vector<Coordinate> Defalut_Plane;	//���˸���̬��Ա����

	PlaneTemplate();					// core Ĭ��Ϊ1
	//PlaneTemplate(int coreCount);		// ָ�������������������� BOSS ����1��
	~PlaneTemplate();
	void AddPixel(Coordinate pos);		// ����һ������
	void ErasePixel(Coordinate pos);	// ȡ��һ������
	void SetCore(Coordinate pos);		// ����һ����������

	//void UnsetCore(Coordinate pos);		// ȡ������һ����������
	/*void SavePlane();
	static PlaneTemplate LoadPlane(PlaneId id);*/

	//ȡ�����������һ�����������طɻ������أ��÷ɻ����ص�λ���� �Ժ��� ��0�� 0������ŵ� 
	void DesignPlane();	//Ӧ�÷ɻ���� //ֱ�Ӿ�̬����
};


/******�ص�*******/
class PlaneCanvas
{
public:
	//COLORREF paintColor;
	PlaneTemplate paintPlane;
	//PlaneCanvas(COLORREF color);					// �������ǰ��ָ�� RGB�������� #FF0000 (���ĵ���ɫ)�������ڲ��Խ׶Σ�Ϊ��������BOSS��������������ӦΪ1
	~PlaneCanvas();
	//static PlaneCanvas& GetPlaneCanvas();					//��ȡ��������
	//void On(Coordinate pos);						// ����������꣬�û���֪���������
	void Click(Coordinate pos, int button);			// ���-1 �м�0 �Ҽ�1  �ĳ������������ �Ҽ����� �м�ź���///// ��������������������Ҽ����û���֪��������ɶ�����һ�����أ��Ҽ����ģ�

};

//����ɻ�ģ�壬��������һ��ʵ���ģ�� InstanceTemplate��ֻ����Ϊ���ֻ������������ɻ������ԲŽ� PlaneTemplate



