#pragma once
#include "Globals.h"
#include "Workshop.h"
#include "GameLoop.h"
#include "Entity.h"

class Bullet;
// ս�������ࣨ����֪������ս����һ�У�
class Scroll
{
public:
	//friend GameLoop;
	struct ScrollTile
	{
		std::vector<InsId> tileContainer;	// ��һ���ذ�����Щʲôʵ�� id
	};

	std::unordered_map<Coordinate, ScrollTile> scrollMap;	// �����Ӧ����Ϣ
	std::unordered_map<InsId, Bullet> instanceRepo;			// ����ʵ��Ĳֿ�

	int insIdCounter;	// ʵ�� ID ���������������� ID��
	int score;			// ����
	int baseLifeMax;	// ������Ѫ
	int baseLife;		// ����ʣ��Ѫ��
	bool dark;			// ���е�������ʱ����������䰵��ԭ���� 1/4
	Scroll();


	std::string bloodBar;     // ����Ѫ��
	std::string bloodBarBorder; // ����Ѫ���߿�

	~Scroll();
	static Scroll& GetInstance();

	void ControlPlayer();

	void AllMove();				// ����ʵ����ã������ƶ�+�ܿ��ƶ�+��ײ���
	void RenderToWindows();		// ��Ⱦ������Ϣ����ͼ�����Ļ�������
	void RenderInfo();			// ��Ⱦ����Ѫ���ͷ����ȵ���ͼ�����Ļ�������
	/**
	 * @brief ������ҷɻ����ƶ��ٶ�
	 * @param speed �ƶ��ٶ�
	 */
	void ControlPlayer(Coordinate speed);
	/**
	 * @brief ���ƾ����һ������
	 * @param scrollRow �����е�λ��
	 */
	void DrawRowOfScroll(int scrollRow);

	/**
	 * @brief ������ҷɻ�
	 * @param playerPos ��ҷɻ���λ��
	 * @param scrollOffset ����Ĺ���ƫ����
	 */
	void DrawPlayer(Coordinate playerPos, int scrollOffset);

	/**
	 * @brief ���Ƶл�
	 * @param enemyPos �л���λ��
	 * @param scrollOffset ����Ĺ���ƫ����
	 */
	void DrawEnemy(Coordinate enemyPos, int scrollOffset);
	void InitiateInstance(PlaneTemplate pt, Coordinate pos);	// ����ʵ�嵽����Ͳֿ�
	void DeleteInstance(InsId id);								// �Ӿ���Ͳֿ�ɾ��ʵ��	


};