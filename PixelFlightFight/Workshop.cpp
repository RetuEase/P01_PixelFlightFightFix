#include "Workshop.h"

/********************只取余数********************/

std::vector<Coordinate> PlaneTemplate::Defalut_Plane{ {0,0},{0,-1},{1,0},{-1,0} };//默认飞机

//PlaneCanvas::PlaneCanvas(COLORREF color) : paintColor(color) //  这里的color规定的是那个颜色 是普通的还是核心的
//{
//#ifdef DEBUG
//	TCHAR input[10];
//	//InputBox(input, 10, L"请输入需要的核心像素数量（9位数以内）", L"核心像素", L"0");
//
//#ifdef UNICODE
//	//paintPlane = PlaneTemplate(_wtoi(input)); //初始化 planeTemplate 对象
//#else
//	paintPlane = PlaneTemplate(atoi(input));
//#endif
//#endif
//}

PlaneCanvas::~PlaneCanvas()
{}


void PlaneCanvas::Click(Coordinate pos, int button)
{//改成了左键放像素 右键消除 中间放核心  左键 1 中键2 右键3  
	if (button == 3) {
		paintPlane.SetCore(pos);
	}
	else {

		if (button == 1)//放像素
		{
			int i = 1;
			// 遍历 spriteMap 向量并执行相应的操作
			for (auto it = paintPlane.spriteMap.begin(); it != paintPlane.spriteMap.end(); ++it) {
				// 如果没有的话就加入该元素
				if (*it == pos) {
					i = 0;
					break;
				}
			}
			if (i)
			{
				paintPlane.AddPixel(pos);
			}
			return;
		}
		else if (button == 2) //如果是右键点击
		{
			for (auto it = paintPlane.spriteMap.begin(); it != paintPlane.spriteMap.end(); ++it) {
				// 如果找到了，则删除该项
				if (*it == pos) {
					paintPlane.ErasePixel(pos);
					return;
				}
			}
		}
	}

}

PlaneTemplate::PlaneTemplate()
	:coreCountMax(1), planCountMax(10)
{
}

PlaneTemplate::~PlaneTemplate()
{
}

//增加或者取消一个像素
void PlaneTemplate::AddPixel(Coordinate pos)
{
	if (spriteMap.size() < planCountMax) {
		spriteMap.push_back(pos);
	}

}

void PlaneTemplate::ErasePixel(Coordinate pos)
{
	//覆盖了
	//从列表里面删除----------------------有问题的部分---已解决
	for (auto it = spriteMap.begin(); it != spriteMap.end(); ++it)
	{
		if (*it == pos) {
			spriteMap.erase(it);
			return;
		}
	}
}


//增加一个核心 减少一个核心
void PlaneTemplate::SetCore(Coordinate pos)
{
	if (core.size() < coreCountMax)
	{
		//放到核心表里面
		core.push_back(pos);
		//颜色在click里面确定添加了
		//solidrectangle(dX, dY, dX + 9, dY + 9);
	}
	else
	{
		core.pop_back();
		core.push_back(pos);
	}
}

//
//void PlaneTemplate::UnsetCore(Coordinate pos)
//{
//	int dX = (pos.x / 10) * 10;
//	int dY = (pos.y / 10) * 10;
//	Coordinate cor(dX, dY);
//	//颜色覆盖
//	setfillcolor(BLACK);
//	solidrectangle(dX, dY, dX + 9, dY + 9);
//
//	//从核心表里面删除  -----------------有问题的部分
//	for (auto it = core.begin(); it != core.end(); ++it)
//	{
//		if (*it == cor) {
//			core.erase(it);
//			return;
//		}
//	}
//}

//------------------------------------------------
//问题 auto 一旦使用就会报错， 具体原因不知道
// 凡是接触到迭代器的地方都会报错，原因不清楚， 头函数？？还是确实什么 和上个问题一样

void PlaneTemplate::DesignPlane()
{
	if (core.size())
	{
		Defalut_Plane.clear();
		Defalut_Plane.push_back({ 0,0 });
		Coordinate cor = *core.begin();
		//先要得到偏移值
		int dx = cor.x;
		int dy = cor.y;
		if (spriteMap.size())
		{
			for (std::vector<Coordinate>::iterator it = spriteMap.begin(); it != spriteMap.end(); it++)
			{
				Coordinate cor((*it).x - dx, (*it).y - dy); //以 （0，0）为核心元素的位置重新去储存元素的位置
				Defalut_Plane.push_back(cor);
			}
		}
	}
}

/********************紅色鯡魚********************/
//void PlaneTemplate::SavePlane()
//{
//	std::stringstream ss;
//
//	// 实体ID
//	ss << planeId;
//	std::string str = "./saveData/";
//	std::ofstream fout(str + ss.str() + ".txt");
//
//	// 图形
//	fout << spriteMap.size() << std::endl;
//	for (auto& i : spriteMap)
//	{
//		fout << i.first.x << " " << i.first.y << " " << i.second << std::endl;
//	}
//
//	// 核心
//	fout << core.size() << " " << coreCountMax << std::endl;
//	for (auto& c : core)
//	{
//		fout << c.x << " " << c.y << std::endl;
//	}
//
//	// 速度
//	fout << speed.x << " " << speed.y << std::endl;
//
//	fout.close();
//
//	return;
//}
//
//PlaneTemplate PlaneTemplate::LoadPlane(PlaneId id)
//{
//	std::stringstream ss;
//
//	// 实体ID
//	ss << id;
//	std::string str = "./saveData/";
//	std::ifstream fin(str + ss.str() + ".txt");
//
//	// 图形
//	PlaneTemplate newPlane;
//	int size = 0;
//	fin >> size;
//	Coordinate tempCoord;
//	for (int i = 0; i < size; i++)
//	{
//		fin >> tempCoord.x >> tempCoord.y;
//		fin >> newPlane.spriteMap[tempCoord];
//	}
//
//	// 核心
//	fin >> size >> newPlane.coreCountMax;
//	for (int i = 0; i < size; i++)
//	{
//		fin >> tempCoord.x >> tempCoord.y;
//		newPlane.core.push_back(tempCoord);
//	}
//
//	// 速度
//	fin >> newPlane.speed.x >> newPlane.speed.y;
//
//	fin.close();
//
//	return newPlane;
//}
