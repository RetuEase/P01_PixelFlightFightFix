//#include "Workshop.h"
//
///********************只取余数********************/
//PlaneCanvas::PlaneCanvas(COLORREF color) : paintColor(color) //  这里的color规定的是那个颜色 是普通的还是核心的
//{
//#ifdef DEBUG
//	TCHAR input[10];
//	InputBox(input, 10, L"请输入需要的核心像素数量（9位数以内）", L"核心像素", L"0");
//
//#ifdef UNICODE
//	paintPlane = PlaneTemplate(_wtoi(input)); //初始化 planeTemplate 对象
//#else
//	paintPlane = PlaneTemplate(atoi(input));
//#endif
//#endif
//}
//
//PlaneCanvas::~PlaneCanvas()
//{
//
//}
////
//void PlaneCanvas::On(Coordinate pos)
//{
//	//有了click 这个目前还不知道怎么去用
//}
////
//
//void PlaneCanvas::Click(Coordinate pos, bool left)
//{
//
//	if (GetAsyncKeyState(VK_LBUTTON))
//	{
//		auto it = std::find(paintPlane.spriteMap.begin(), paintPlane.spriteMap.end(), pos);
//		if (it == paintPlane.spriteMap.end()) //先去判断该部分有没有元素 如果有的话就调用删除
//		{
//			paintPlane.ErasePixel(pos);
//		}
//		else //没有的话就加入改元素
//		{
//			paintPlane.AddPixel(pos);
//
//		}
//	}
//	if (GetAsyncKeyState(VK_RBUTTON)) //如果是右键点击
//	{
//		auto it = std::find(paintPlane.core.begin(), paintPlane.core.end(), pos);
//		if (it == paintPlane.core.end()) //判断原来的位置有没有元素 有的话就删除
//		{
//			paintPlane.UnsetCore(pos);
//		}
//		else
//		{
//			setfillcolor(paintColor);
//		}
//	}
//
//}
//
//PlaneTemplate::PlaneTemplate()
//	:coreCountMax(1)
//{
//}
//
////确定核心的数量
//PlaneTemplate::PlaneTemplate(int coreCount)
//	:coreCountMax(coreCount)
//{
//	coreCountMax = coreCount;
//}
//
//PlaneTemplate::~PlaneTemplate()
//{
//}
//
////增加或者取消一个像素
//void PlaneTemplate::AddPixel(Coordinate pos)
//{
//	int dX = (pos.x / 10) * 10;
//	int dY = (pos.y / 10) * 10;
//	Coordinate cor(dX, dY);
//	//添加到像素表里面 颜色这个默认为白色？？？
//	//添加到像素表这个方法在click里面
//	spriteMap[cor] = WHITE;
//	solidrectangle(dX, dY, dX + 9, dY + 9);
//}
//void PlaneTemplate::ErasePixel(Coordinate pos)
//{
//	int dX = (pos.x / 10) * 10;
//	int dY = (pos.y / 10) * 10;
//	//覆盖了
//	setfillcolor(BLACK);
//	solidrectangle(dX, dY, dX + 9, dY + 9);
//	Coordinate cor(dX, dY);
//
//	//从列表里面删除----------------------有问题的部分
//	auto it = std::find_if(spriteMap.begin(), spriteMap.end(), cor);
//	spriteMap.erase(it);
//}
//
////增加一个核心 减少一个核心
//void PlaneTemplate::SetCore(Coordinate pos)
//{
//	int dX = (pos.x / 10) * 10;
//	int dY = (pos.y / 10) * 10;
//	Coordinate cor(dX, dY);
//	//放到核心表里面
//	core.push_back(cor);
//
//	//颜色在click里面确定添加了
//	solidrectangle(dX, dY, dX + 9, dY + 9);
//}
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
//	std::vector<Coordinate>::iterator it = std::find_if(core.begin(), core.end(), cor);
//	core.erase(it);
//}
//
////------------------------------------------------
////问题 auto 一旦使用就会报错， 具体原因不知道
//// 凡是接触到迭代器的地方都会报错，原因不清楚， 头函数？？还是确实什么 和上个问题一样
//
//
///********************紅色鯡魚********************/
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