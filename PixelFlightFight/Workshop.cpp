#include "Workshop.h"

/********************ֻȡ����********************/

std::vector<Coordinate> PlaneTemplate::Defalut_Plane{ {0,0},{0,-1},{1,0},{-1,0} };//Ĭ�Ϸɻ�

//PlaneCanvas::PlaneCanvas(COLORREF color) : paintColor(color) //  �����color�涨�����Ǹ���ɫ ����ͨ�Ļ��Ǻ��ĵ�
//{
//#ifdef DEBUG
//	TCHAR input[10];
//	//InputBox(input, 10, L"��������Ҫ�ĺ�������������9λ�����ڣ�", L"��������", L"0");
//
//#ifdef UNICODE
//	//paintPlane = PlaneTemplate(_wtoi(input)); //��ʼ�� planeTemplate ����
//#else
//	paintPlane = PlaneTemplate(atoi(input));
//#endif
//#endif
//}

PlaneCanvas::~PlaneCanvas()
{}


void PlaneCanvas::Click(Coordinate pos, int button)
{//�ĳ������������ �Ҽ����� �м�ź���  ��� 1 �м�2 �Ҽ�3  
	if (button == 3) {
		paintPlane.SetCore(pos);
	}
	else {

		if (button == 1)//������
		{
			int i = 1;
			// ���� spriteMap ������ִ����Ӧ�Ĳ���
			for (auto it = paintPlane.spriteMap.begin(); it != paintPlane.spriteMap.end(); ++it) {
				// ���û�еĻ��ͼ����Ԫ��
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
		else if (button == 2) //������Ҽ����
		{
			for (auto it = paintPlane.spriteMap.begin(); it != paintPlane.spriteMap.end(); ++it) {
				// ����ҵ��ˣ���ɾ������
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

//���ӻ���ȡ��һ������
void PlaneTemplate::AddPixel(Coordinate pos)
{
	if (spriteMap.size() < planCountMax) {
		spriteMap.push_back(pos);
	}

}

void PlaneTemplate::ErasePixel(Coordinate pos)
{
	//������
	//���б�����ɾ��----------------------������Ĳ���---�ѽ��
	for (auto it = spriteMap.begin(); it != spriteMap.end(); ++it)
	{
		if (*it == pos) {
			spriteMap.erase(it);
			return;
		}
	}
}


//����һ������ ����һ������
void PlaneTemplate::SetCore(Coordinate pos)
{
	if (core.size() < coreCountMax)
	{
		//�ŵ����ı�����
		core.push_back(pos);
		//��ɫ��click����ȷ�������
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
//	//��ɫ����
//	setfillcolor(BLACK);
//	solidrectangle(dX, dY, dX + 9, dY + 9);
//
//	//�Ӻ��ı�����ɾ��  -----------------������Ĳ���
//	for (auto it = core.begin(); it != core.end(); ++it)
//	{
//		if (*it == cor) {
//			core.erase(it);
//			return;
//		}
//	}
//}

//------------------------------------------------
//���� auto һ��ʹ�þͻᱨ�� ����ԭ��֪��
// ���ǽӴ����������ĵط����ᱨ��ԭ������� ͷ������������ȷʵʲô ���ϸ�����һ��

void PlaneTemplate::DesignPlane()
{
	if (core.size())
	{
		Defalut_Plane.clear();
		Defalut_Plane.push_back({ 0,0 });
		Coordinate cor = *core.begin();
		//��Ҫ�õ�ƫ��ֵ
		int dx = cor.x;
		int dy = cor.y;
		if (spriteMap.size())
		{
			for (std::vector<Coordinate>::iterator it = spriteMap.begin(); it != spriteMap.end(); it++)
			{
				Coordinate cor((*it).x - dx, (*it).y - dy); //�� ��0��0��Ϊ����Ԫ�ص�λ������ȥ����Ԫ�ص�λ��
				Defalut_Plane.push_back(cor);
			}
		}
	}
}

/********************�tɫ�E�~********************/
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
