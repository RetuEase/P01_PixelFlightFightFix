#pragma once
#include "Globals.h"
//#include "Entity.h"
class PlaneTemplate
{
public:
	std::vector<Coordinate> core;		// 哪些是核心像素
	int coreCountMax;					// 核心上限
	int planCountMax;					// 机身上限
	std::vector<Coordinate> spriteMap;	//在这里加了个spriteMap 来存放普通的元素----取余
	static std::vector<Coordinate> Defalut_Plane;	//加了个静态成员变量

	PlaneTemplate();					// core 默认为1
	//PlaneTemplate(int coreCount);		// 指定核心像素数量（除了 BOSS 都是1）
	~PlaneTemplate();
	void AddPixel(Coordinate pos);		// 增加一个像素
	void ErasePixel(Coordinate pos);	// 取消一个像素
	void SetCore(Coordinate pos);		// 设置一个核心像素

	//void UnsetCore(Coordinate pos);		// 取消设置一个核心像素
	/*void SavePlane();
	static PlaneTemplate LoadPlane(PlaneId id);*/

	//取余在这里加了一个方法来返回飞机的像素，该飞机像素的位置是 以核心 （0， 0）来存放的 
	void DesignPlane();	//应用飞机设计 //直接静态向量
};


/******重点*******/
class PlaneCanvas
{
public:
	//COLORREF paintColor;
	PlaneTemplate paintPlane;
	//PlaneCanvas(COLORREF color);					// 进入界面前须指定 RGB，不能是 #FF0000 (核心的颜色)，除非在测试阶段（为创造多核心BOSS）核心像素数量应为1
	~PlaneCanvas();
	//static PlaneCanvas& GetPlaneCanvas();					//获取单例对象
	//void On(Coordinate pos);						// 传入鼠标坐标，让画布知道鼠标在哪
	void Click(Coordinate pos, int button);			// 左键-1 中键0 右键1  改成了左键放像素 右键消除 中间放核心///// 传入鼠标坐标和左键还是右键，让画布知道鼠标点了啥（左键一般像素，右键核心）

};

//这个飞机模板，本质上是一切实体的模板 InstanceTemplate，只是因为玩家只能用它来创造飞机，所以才叫 PlaneTemplate



