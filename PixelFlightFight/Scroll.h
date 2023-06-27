#pragma once
#include "Globals.h"
#include "Workshop.h"
#include "GameLoop.h"
#include "Entity.h"

class Bullet;
// 战斗卷轴类（卷轴知晓关于战斗的一切）
class Scroll
{
public:
	//friend GameLoop;
	struct ScrollTile
	{
		std::vector<InsId> tileContainer;	// 这一像素包含了些什么实体 id
	};

	std::unordered_map<Coordinate, ScrollTile> scrollMap;	// 坐标对应的信息
	std::unordered_map<InsId, Bullet> instanceRepo;			// 存在实体的仓库

	int insIdCounter;	// 实体 ID 计数器（用于生成 ID）
	int score;			// 分数
	int baseLifeMax;	// 基地满血
	int baseLife;		// 基地剩余血量
	bool dark;			// 当有弹出界面时，绘制整体变暗至原来的 1/4
	Scroll();


	std::string bloodBar;     // 基地血条
	std::string bloodBarBorder; // 基地血条边框

	~Scroll();
	static Scroll& GetInstance();

	void ControlPlayer();

	void AllMove();				// 遍历实体调用：惯性移动+受控移动+碰撞检测
	void RenderToWindows();		// 渲染卷轴信息到绘图区（的缓冲区）
	void RenderInfo();			// 渲染基地血条和分数等到绘图区（的缓冲区）
	/**
	 * @brief 控制玩家飞机的移动速度
	 * @param speed 移动速度
	 */
	void ControlPlayer(Coordinate speed);
	/**
	 * @brief 绘制卷轴的一行内容
	 * @param scrollRow 滚动行的位置
	 */
	void DrawRowOfScroll(int scrollRow);

	/**
	 * @brief 绘制玩家飞机
	 * @param playerPos 玩家飞机的位置
	 * @param scrollOffset 卷轴的滚动偏移量
	 */
	void DrawPlayer(Coordinate playerPos, int scrollOffset);

	/**
	 * @brief 绘制敌机
	 * @param enemyPos 敌机的位置
	 * @param scrollOffset 卷轴的滚动偏移量
	 */
	void DrawEnemy(Coordinate enemyPos, int scrollOffset);
	void InitiateInstance(PlaneTemplate pt, Coordinate pos);	// 生成实体到卷轴和仓库
	void DeleteInstance(InsId id);								// 从卷轴和仓库删除实体	


};