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
	setlinestyle(PS_SOLID, 2);	//PS_SOLID��ָһ�����ض���ɫ��ʵ�ߣ����ߵĿ���ɵ���GDI API�Ĳ�����ָ���Ŀ�Ⱦ�����
	//PS_SOLIDͨ�����ڴ����߿򣬱߿��������Ҫ����������ͼ��Ԫ��
	setfillcolor(CYAN);
	settextstyle(25, 0, L"΢���ź�");

	// ���ư�ť
	fillrectangle(x, y, x + width, y + height);

	// �����ı�
	RECT rect = { x, y, x + width, y + height };
	drawtext(text, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}
bool Button::state(const ExMessage& msg) {
	if (msg.message == WM_MOUSEMOVE && On(msg))	// ��ť����
	{
		// ������ʽ
		setlinestyle(PS_SOLID, 2);
		setfillcolor(LIGHTBLUE);
		settextstyle(25, 0, L"΢���ź�");

		// ���ư�ť
		fillrectangle(x, y, x + width, y + height);

		// �����ı�
		RECT rect = { x, y, x + width, y + height };
		drawtext(text, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		ischange = true;

		return false;
	}
	else if ((msg.message == WM_LBUTTONDOWN || msg.message == WM_LBUTTONUP) && On(msg))	// ��ť�����
	{
		// ������ʽ
		setlinestyle(PS_SOLID, 2);
		setfillcolor(LIGHTBLUE);
		settextstyle(25, 0, L"΢���ź�");

		// ���ư�ť
		fillrectangle(x, y, x + width, y + height);

		// �����ı�
		RECT rect = { x, y, x + width, y + height };
		drawtext(text, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		Click();
		return true;
	}
	else	// �ڰ�ť״̬�ı��ʱ�򣬻ָ���ťԭ����״̬����ֹ����
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
int OnButtonClick()//�������Ҫ����Funcptr�����������̨���������
{
	std::cout << "Button Clicked!" << std::endl;
	return 0;
}