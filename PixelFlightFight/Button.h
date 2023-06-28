#pragma once

#include "Globals.h"
int OnButtonClick();

class Label
{
protected:
	int x;
	int y;
	int width;
	int height;//�����
	union LabelContainer
	{
		IMAGE image;
		LPCSTR text;

		LabelContainer();
		~LabelContainer();
	};
	Coordinate  pos;
	LabelContainer container;
public:
	Label(int x = 0, int y = 0, int width = 100, int height = 60);//pos.x=x
	Coordinate getPos();//��ȡpos
	Vector2 getSize();
	virtual void RenderToWindows() = 0;//��Ⱦ����ͼ�������ﶯ̬��һ��
	Label(IMAGE image);
	Label(LPCTSTR text);
	~Label();

};

class Button : public Label
{
public:
	Button(int (*FuncPtr)(), int x = 0, int y = 0, int width = 100, int height = 60, LPCTSTR text = L"��ť");
	void RenderToWindows();//��ʾ��ť
	bool state(const ExMessage& msg);//��ʾ��ť���״̬�����δ���
	bool On(const ExMessage& msg);//�Ƿ�������ť
	int Click();//��⵽����������ť�ϵ��ʱ����
	~Button();

protected:
	LPCTSTR text;
	bool ischange;//��ť״̬�Ƿ�ı�
	int (*FuncPtr)();
};
#pragma once
