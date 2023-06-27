#include "Workshop.h"

PlaneCanvas::PlaneCanvas(COLORREF color)
	:paintColor(color)
{
#ifdef DEBUG
	TCHAR input[10];
	InputBox(input, 10, L"请输入需要的核心像素数量（9位数以内）", L"核心像素", L"0");

#ifdef UNICODE
	paintPlane = PlaneTemplate(_wtoi(input));
#else
	paintPlane = PlaneTemplate(atoi(input));
#endif

#endif
}

PlaneCanvas::~PlaneCanvas()
{
}

void PlaneCanvas::On(Coordinate pos)
{
}

void PlaneCanvas::Click(Coordinate pos, bool left)
{
}

PlaneTemplate::PlaneTemplate()
	:coreCountMax(1)
{
}

PlaneTemplate::PlaneTemplate(int coreCount)
	:coreCountMax(coreCount)
{
}

PlaneTemplate::~PlaneTemplate()
{
}

void PlaneTemplate::AddPixel(Coordinate pos)
{
}

void PlaneTemplate::ErasePixel(Coordinate pos)
{
}

void PlaneTemplate::SetCore(Coordinate pos)
{
}

void PlaneTemplate::UnsetCore(Coordinate pos)
{
}
