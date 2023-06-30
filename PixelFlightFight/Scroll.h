#pragma once
#include "Entity.h"

// 战斗卷轴类（卷轴知晓关于战斗的一切）单例
class Scroll
{
private:
	Scroll();	//构造函数
public:

	//bool dark;			// 当有弹出界面时，绘制整体变暗至原来的 1/4
	int enemiesNum;		//剩余敌人数量
	int baseLifeMax;	// 基地满血
	int baseLife;		// 基地剩余血量
	int refleshCount;	//刷新计数
	Speed playSpeed;	//玩家移速
	int fireCD;	//刷新计数

	//std::string bloodBar;     // 基地血条
	//std::string bloodBarBorder; // 基地血条边框		

	~Scroll();		//析构函数
	static Scroll& GetInstance();

	void Fire();				//发射
	void GameUpdate();			//一次刷新

	//void TraverseEntity(int i);		// 根据类型遍历实体 0为自机,1为子弹 2为敌机
	//void DeleteInstance(InsId id);	// 从卷轴和仓库删除像素块


	//void ControlPlayer();	

	//void RenderToWindows();		// 渲染卷轴信息到绘图区（的缓冲区）
	//void RenderInfo();			// 渲染基地血条和分数等到绘图区（的缓冲区）
	/**
	 * @brief 控制玩家飞机的移动速度
	 * @param speed 移动速度
	 */
	 //void ControlPlayer(Coordinate speed);
	 ///**
	 // * @brief 绘制卷轴的一行内容
	 // * @param scrollRow 滚动行的位置
	 // */
	 //void DrawRowOfScroll(int scrollRow);

	 ///**
	 // * @brief 绘制玩家飞机
	 // * @param playerPos 玩家飞机的位置	
	 // * @param scrollOffset 卷轴的滚动偏移量
	 // */
	 //void DrawPlayer(Coordinate playerPos, int scrollOffset);

	 ///**
	 // * @brief 绘制敌机
	 // * @param enemyPos 敌机的位置
	 // * @param scrollOffset 卷轴的滚动偏移量
	 // */
	 //void DrawEnemy(Coordinate enemyPos, int scrollOffset);
	 //void InitiateInstance(PlaneTemplate pt, Coordinate pos);	// 生成实体到卷轴和仓库

};
