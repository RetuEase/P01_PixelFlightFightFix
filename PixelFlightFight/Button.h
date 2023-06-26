#pragma once
#include "Globals.h"
int OnButtonClick();

class Label
{
protected:
	int x;
	int y;
	int width;
	int height;//长宽高
	union LabelContainer
	{
		IMAGE image;
		LPCTSTR text;

		LabelContainer();
		~LabelContainer();
	};
	Coordinate  pos;
	LabelContainer container;
public:
	Label(int x = 0, int y = 0, int width = 100, int height = 60);//pos.x=x
	Coordinate getPos();//获取pos
	Vector2 getSize();
	virtual void RenderRoWindows() = 0;//渲染到绘图区，这里动态绑定一下
};

class Button : public Label
{
public:
	Button(int x = 0, int y = 0, int width = 100, int height = 60, const LPCTSTR& text = _T("按钮"), int (*FuncPtr)());
	void RenderRoWindows();//显示按钮
	bool state(const ExMessage& msg);//显示按钮点击状态，点和未点击
	bool On(const ExMessage& msg);//是否点击到按钮
	int Click();//检测到鼠标在这个按钮上点击时调用

protected:
	LPCTSTR text;
	bool ischange;//按钮状态是否改变
	int (*FuncPtr)();
};