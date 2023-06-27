#pragma once
#include "Globals.h"
#include "Entity.h"

/******重点*******/
class PlaneCanvas
{
	COLORREF paintColor;
	PlaneTemplate paintPlane;

public:
	PlaneCanvas(COLORREF color);					// 进入界面前须指定 RGB，不能是 #FF0000 (核心的颜色)，除非在测试阶段（为创造多核心BOSS）核心像素数量应为1
	~PlaneCanvas();

	void On(Coordinate pos);						// 传入鼠标坐标，让画布知道鼠标在哪
	void Click(Coordinate pos, bool left = true);	// 传入鼠标坐标和左键还是右键，让画布知道鼠标点了啥（左键一般像素，右键核心）
};

// 这个飞机模板，本质上是一切实体的模板 InstanceTemplate，只是因为玩家只能用它来创造飞机，所以才叫 PlaneTemplate
class PlaneTemplate : public Sprite
{
	friend PlaneCanvas;
	std::vector<Coordinate> core;		// 哪些是核心像素
	int coreCountMax;					// 核心像素上限
	Speed speed;						// 子弹/飞机速度

public:
	PlaneTemplate();					// core 默认为1
	PlaneTemplate(int coreCount);		// 指定核心像素数量（除了 BOSS 都是1）
	~PlaneTemplate();

	void AddPixel(Coordinate pos);		// 增加一个像素
	void ErasePixel(Coordinate pos);	// 取消一个像素
	void SetCore(Coordinate pos);		// 设置一个核心像素
	void UnsetCore(Coordinate pos);		// 取消设置一个核心像素

	void SavePlane();
	static PlaneTemplate LoadPlane(PlaneId id);
}; 


#pragma once
