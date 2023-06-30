#pragma once
#include "Entity.h"

// ս�������ࣨ����֪������ս����һ�У�����
class Scroll
{
private:
	Scroll();	//���캯��
public:

	//bool dark;			// ���е�������ʱ����������䰵��ԭ���� 1/4
	int enemiesNum;		//ʣ���������
	int baseLifeMax;	// ������Ѫ
	int baseLife;		// ����ʣ��Ѫ��
	int refleshCount;	//ˢ�¼���
	Speed playSpeed;	//�������
	int fireCD;	//ˢ�¼���

	//std::string bloodBar;     // ����Ѫ��
	//std::string bloodBarBorder; // ����Ѫ���߿�		

	~Scroll();		//��������
	static Scroll& GetInstance();

	void Fire();				//����
	void GameUpdate();			//һ��ˢ��

	//void TraverseEntity(int i);		// �������ͱ���ʵ�� 0Ϊ�Ի�,1Ϊ�ӵ� 2Ϊ�л�
	//void DeleteInstance(InsId id);	// �Ӿ���Ͳֿ�ɾ�����ؿ�


	//void ControlPlayer();	

	//void RenderToWindows();		// ��Ⱦ������Ϣ����ͼ�����Ļ�������
	//void RenderInfo();			// ��Ⱦ����Ѫ���ͷ����ȵ���ͼ�����Ļ�������
	/**
	 * @brief ������ҷɻ����ƶ��ٶ�
	 * @param speed �ƶ��ٶ�
	 */
	 //void ControlPlayer(Coordinate speed);
	 ///**
	 // * @brief ���ƾ����һ������
	 // * @param scrollRow �����е�λ��
	 // */
	 //void DrawRowOfScroll(int scrollRow);

	 ///**
	 // * @brief ������ҷɻ�
	 // * @param playerPos ��ҷɻ���λ��	
	 // * @param scrollOffset ����Ĺ���ƫ����
	 // */
	 //void DrawPlayer(Coordinate playerPos, int scrollOffset);

	 ///**
	 // * @brief ���Ƶл�
	 // * @param enemyPos �л���λ��
	 // * @param scrollOffset ����Ĺ���ƫ����
	 // */
	 //void DrawEnemy(Coordinate enemyPos, int scrollOffset);
	 //void InitiateInstance(PlaneTemplate pt, Coordinate pos);	// ����ʵ�嵽����Ͳֿ�

};
