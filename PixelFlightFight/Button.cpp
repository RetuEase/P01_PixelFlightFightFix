#include "Button.h"

Button::Button(int (*FuncPtr)())
	:FuncPtr(FuncPtr)
{
}

Button::Button(IMAGE image, int(*FuncPtr)())
	:Label(image)
	, FuncPtr(FuncPtr)
{
}

Button::Button(LPCTSTR text, int(*FuncPtr)())
{
}

Button::~Button()
{
}

bool Button::On(Coordinate pos)
{
	return false;
}

int Button::Click()
{
	return 0;
}

Label::Label()
{
}

Label::Label(IMAGE image)
{
	container.image = image;
}

Label::Label(LPCTSTR text)
{
}

Label::~Label()
{
}

Coordinate Label::getPos()
{
	return Coordinate();
}

Vector2 Label::getSize()
{
	return Vector2();
}

void Label::RenderToWindows()
{
}

Label::LabelContainer::LabelContainer()
{
	text = L"";
}

Label::LabelContainer::~LabelContainer()
{
}
