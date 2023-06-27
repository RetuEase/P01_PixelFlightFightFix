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

	Coordinate pos;			// ���Ͻǵ�����
	Vector2 size;			// ����
	LabelContainer container;
public:
	Label();
	Label(IMAGE image);
	Label(LPCTSTR text);
	~Label();

	Coordinate getPos();	// ��ȡ pos
	Vector2 getSize();		// ��ȡ����
	void RenderToWindows();	// ��Ⱦ����ͼ�����Ļ�������
};

class Button : public Label
{
	int (*FuncPtr)();
public:
	Button(int (*FuncPtr)());	// ��������ťʱ�Ļص�����
	Button(IMAGE image, int (*FuncPtr)());
	Button(LPCTSTR text, int (*FuncPtr)());
	~Button();					// ������ָ��

	bool On(Coordinate pos);	// ����������꣬�����Ƿ��������ť��
	int Click();				// ��⵽����������ť�ϵ��ʱ����
};