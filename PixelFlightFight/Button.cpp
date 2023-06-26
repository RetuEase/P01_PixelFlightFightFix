#include"Button.h"
#include<iostream>

Label::Label(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
	pos.x = x;
	pos.y = y;
}
Coordinate Label::getPos() {
	return Coordinate(pos.x, pos.y);
}
Label::LabelContainer::LabelContainer()
{
	text = L"";
}

Label::LabelContainer::~LabelContainer()
{
}

Vector2 Label::getSize() {
	return Vector2(width, height);
}
Button::Button(int x, int y, int width, int height, const LPCTSTR& text, int (*FuncPtr)()) :Label(x, y, width, height), text(text), FuncPtr(FuncPtr), ischange(false) {
	this->FuncPtr = FuncPtr;
}
Button :: ~Button() {

}
void Button::RenderRoWindows() {
	setlinestyle(PS_SOLID, 2);	//PS_SOLID是指一条由特定颜色的实线，该线的宽度由调用GDI API的参数所指定的宽度决定。
	//PS_SOLID通常用于创建线框，边框或其他需要绘制线条的图形元素
	setfillcolor(CYAN);
	settextstyle(25, 0, L"微软雅黑");

	// 绘制按钮
	fillrectangle(x, y, x + width, y + height);

	// 绘制文本
	RECT rect = { x, y, x + width, y + height };
	drawtext(text, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}
bool Button::state(const ExMessage& msg) {
	if (msg.message == WM_MOUSEMOVE && On(msg))	// 按钮悬浮
	{
		// 设置样式
		setlinestyle(PS_SOLID, 2);
		setfillcolor(LIGHTBLUE);
		settextstyle(25, 0, L"微软雅黑");

		// 绘制按钮
		fillrectangle(x, y, x + width, y + height);

		// 绘制文本
		RECT rect = { x, y, x + width, y + height };
		drawtext(text, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		ischange = true;

		return false;
	}
	else if ((msg.message == WM_LBUTTONDOWN || msg.message == WM_LBUTTONUP) && On(msg))	// 按钮被点击
	{
		// 设置样式
		setlinestyle(PS_SOLID, 2);
		setfillcolor(LIGHTBLUE);
		settextstyle(25, 0, L"微软雅黑");

		// 绘制按钮
		fillrectangle(x, y, x + width, y + height);

		// 绘制文本
		RECT rect = { x, y, x + width, y + height };
		drawtext(text, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		Click();
		return true;
	}
	else	// 在按钮状态改变的时候，恢复按钮原来的状态，防止屏闪
	{
		if (ischange)
		{
			RenderRoWindows();
			ischange = false;
		}
		return false;
	}


}
bool Button::On(const ExMessage& msg) {
	if (msg.x >= this->x && msg.x <= this->x + width && msg.y >= this->y && msg.y <= this->y + height)
	{
		return true;
	}
	return false;
}
int Button::Click() {
	if (FuncPtr != nullptr) {
		FuncPtr();
	}
	ischange = true;
	return 0;

}
int OnButtonClick()//这个函数要传给Funcptr产生点击控制台会输出内容
{
	std::cout << "Button Clicked!" << std::endl;
	return 0;
}