//#include "Workshop.h"
//
///********************ֻȡ����********************/
//PlaneCanvas::PlaneCanvas(COLORREF color) : paintColor(color) //  �����color�涨�����Ǹ���ɫ ����ͨ�Ļ��Ǻ��ĵ�
//{
//#ifdef DEBUG
//	TCHAR input[10];
//	InputBox(input, 10, L"��������Ҫ�ĺ�������������9λ�����ڣ�", L"��������", L"0");
//
//#ifdef UNICODE
//	paintPlane = PlaneTemplate(_wtoi(input)); //��ʼ�� planeTemplate ����
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
//	//����click ���Ŀǰ����֪����ôȥ��
//}
////
//
//void PlaneCanvas::Click(Coordinate pos, bool left)
//{
//
//	if (GetAsyncKeyState(VK_LBUTTON))
//	{
//		auto it = std::find(paintPlane.spriteMap.begin(), paintPlane.spriteMap.end(), pos);
//		if (it == paintPlane.spriteMap.end()) //��ȥ�жϸò�����û��Ԫ�� ����еĻ��͵���ɾ��
//		{
//			paintPlane.ErasePixel(pos);
//		}
//		else //û�еĻ��ͼ����Ԫ��
//		{
//			paintPlane.AddPixel(pos);
//
//		}
//	}
//	if (GetAsyncKeyState(VK_RBUTTON)) //������Ҽ����
//	{
//		auto it = std::find(paintPlane.core.begin(), paintPlane.core.end(), pos);
//		if (it == paintPlane.core.end()) //�ж�ԭ����λ����û��Ԫ�� �еĻ���ɾ��
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
////ȷ�����ĵ�����
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
////���ӻ���ȡ��һ������
//void PlaneTemplate::AddPixel(Coordinate pos)
//{
//	int dX = (pos.x / 10) * 10;
//	int dY = (pos.y / 10) * 10;
//	Coordinate cor(dX, dY);
//	//��ӵ����ر����� ��ɫ���Ĭ��Ϊ��ɫ������
//	//��ӵ����ر����������click����
//	spriteMap[cor] = WHITE;
//	solidrectangle(dX, dY, dX + 9, dY + 9);
//}
//void PlaneTemplate::ErasePixel(Coordinate pos)
//{
//	int dX = (pos.x / 10) * 10;
//	int dY = (pos.y / 10) * 10;
//	//������
//	setfillcolor(BLACK);
//	solidrectangle(dX, dY, dX + 9, dY + 9);
//	Coordinate cor(dX, dY);
//
//	//���б�����ɾ��----------------------������Ĳ���
//	auto it = std::find_if(spriteMap.begin(), spriteMap.end(), cor);
//	spriteMap.erase(it);
//}
//
////����һ������ ����һ������
//void PlaneTemplate::SetCore(Coordinate pos)
//{
//	int dX = (pos.x / 10) * 10;
//	int dY = (pos.y / 10) * 10;
//	Coordinate cor(dX, dY);
//	//�ŵ����ı�����
//	core.push_back(cor);
//
//	//��ɫ��click����ȷ�������
//	solidrectangle(dX, dY, dX + 9, dY + 9);
//}
//void PlaneTemplate::UnsetCore(Coordinate pos)
//{
//	int dX = (pos.x / 10) * 10;
//	int dY = (pos.y / 10) * 10;
//	Coordinate cor(dX, dY);
//	//��ɫ����
//	setfillcolor(BLACK);
//	solidrectangle(dX, dY, dX + 9, dY + 9);
//
//	//�Ӻ��ı�����ɾ��  -----------------������Ĳ���
//	std::vector<Coordinate>::iterator it = std::find_if(core.begin(), core.end(), cor);
//	core.erase(it);
//}
//
////------------------------------------------------
////���� auto һ��ʹ�þͻᱨ�� ����ԭ��֪��
//// ���ǽӴ����������ĵط����ᱨ��ԭ������� ͷ������������ȷʵʲô ���ϸ�����һ��
//
//
///********************�tɫ�E�~********************/
//void PlaneTemplate::SavePlane()
//{
//	std::stringstream ss;
//
//	// ʵ��ID
//	ss << planeId;
//	std::string str = "./saveData/";
//	std::ofstream fout(str + ss.str() + ".txt");
//
//	// ͼ��
//	fout << spriteMap.size() << std::endl;
//	for (auto& i : spriteMap)
//	{
//		fout << i.first.x << " " << i.first.y << " " << i.second << std::endl;
//	}
//
//	// ����
//	fout << core.size() << " " << coreCountMax << std::endl;
//	for (auto& c : core)
//	{
//		fout << c.x << " " << c.y << std::endl;
//	}
//
//	// �ٶ�
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
//	// ʵ��ID
//	ss << id;
//	std::string str = "./saveData/";
//	std::ifstream fin(str + ss.str() + ".txt");
//
//	// ͼ��
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
//	// ����
//	fin >> size >> newPlane.coreCountMax;
//	for (int i = 0; i < size; i++)
//	{
//		fin >> tempCoord.x >> tempCoord.y;
//		newPlane.core.push_back(tempCoord);
//	}
//
//	// �ٶ�
//	fin >> newPlane.speed.x >> newPlane.speed.y;
//
//	fin.close();
//
//	return newPlane;
//}