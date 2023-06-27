#pragma once
#include "Globals.h"

class Label
{
protected:
	union LabelContainer
	{
		IMAGE image;
		LPCTSTR text;

		LabelContainer();
		~LabelContainer();
	};

	Coordinate pos;			// 左上角的坐标
	Vector2 size;			// 长宽
	LabelContainer container;
public:
	Label();
	Label(IMAGE image);
	Label(LPCTSTR text);
	~Label();

	Coordinate getPos();	// 获取 pos
	Vector2 getSize();		// 获取长宽
	void RenderToWindows();	// 渲染到绘图区（的缓冲区）
};

class Button : public Label
{
	int (*FuncPtr)();
public:
	Button(int (*FuncPtr)());	// 传入点击按钮时的回调函数
	Button(IMAGE image, int (*FuncPtr)());
	Button(LPCTSTR text, int (*FuncPtr)());
	~Button();					// 清理函数指针

	bool On(Coordinate pos);	// 传入鼠标坐标，返回是否在这个按钮上
	int Click();				// 检测到鼠标在这个按钮上点击时调用
};