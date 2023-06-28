//GameLoop.cpp  part1
#include "GameLoop.h"
//#include "Scroll.h"
#include "Button.h"
using namespace std;

/********************yjl********************/
GameLoop::GameLoop() :flag(1) {
	//memset(keyDown, 0, sizeof(bool) * KEY_COUNT);
}

GameLoop::~GameLoop()
{

}

GameLoop& GameLoop::GetInstance()
{
	static GameLoop gameLoop;
	return gameLoop;
}

void GameLoop::Run()
{
	while (1)
	{
		switch (flag)
		{
		case 1:
			MainMenuLoop(); //������
		case 2:
			SelectLevelLoop(); //�ؿ�����
		case 3:
			PlaneBattleLoop();//ս������
		case 4:
			PlaneBattleLoop();//���ܽ���
		case 5:
			PlaneWorkshopLoop();//�ɻ�����
		case -1:
			return;//����
		}
	}
}
void GameLoop::MainMenuLoop()
{
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//�������ڲ���ʾ����̨; // ��ʼ��ͼ�δ��ڴ�СΪ800*600����
	setbkcolor(CYAN);
	cleardevice();//��ʾ������ɫ      
	setbkmode(TRANSPARENT);//�������屳��
	setfillcolor(WHITE);//�������ɫ��������ǳ��ɫ
	setlinecolor(WHITE); //���õ�ǰ��������ɫΪ��ɫ
	settextstyle(60, 0, _T("΢���ź�"));//
	LPCTSTR title = _T("���طɻ���ս");
	settextcolor(WHITE);
	outtextxy(355, 100, title);
	// ���ư�ť
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // ��ť����
	Button* Begin;//���ư�ť
	Button* WorkShop;//���Ʒɻ�����
	Button* Operating_instructions;//���Ʋ���˵��
	Button* exit_game;//�˳�
	Operating_instructions = new Button(OnButtonClick, 350, 300, 300, 75, L"��Ϸ����");
	Begin = new Button(OnButtonClick, 350, 400, 300, 75, L"��ʼ��Ϸ");
	WorkShop = new Button(OnButtonClick, 350, 500, 300, 75, L"�ɻ�����");
	exit_game = new Button(OnButtonClick, 350, 600, 300, 75, L"�˳���Ϸ");
	Begin->RenderToWindows();
	WorkShop->RenderToWindows();
	Operating_instructions->RenderToWindows();
	exit_game->RenderToWindows();
	ExMessage msg;
	bool on = 1;
	while (on)
	{
		msg = getmessage();
		if (Begin->state(msg)) // ��ʼ��Ϸ ����ѡ�ؿ�ҳ��
		{
			flag = 2;
			printf("Begin\n");
			SelectLevelLoop();
		}
		if (WorkShop->state(msg)) // �ɻ�����
		{
			flag = 5;
			printf("End\n");
			PlaneWorkshopLoop();
		}
		if (Operating_instructions->state(msg)) // ����
		{
			flag = 4;
			printf("End\n");
			InstructionsLoop();
		}
		if (exit_game->state(msg)) {//�˳���Ϸ
			flag = -1;
			exit(0);
		}
	}
	//getch();
}

//TODO 
//���ܽ���
void GameLoop::InstructionsLoop()
{
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//�������ڲ���ʾ����̨; // ��ʼ��ͼ�δ��ڴ�СΪ800*600����
	setbkcolor(CYAN);
	cleardevice();//��ʾ������ɫ      
	setbkmode(TRANSPARENT);//�������屳��
	setfillcolor(WHITE);//�������ɫ��������ǳ��ɫ
	setlinecolor(WHITE); //���õ�ǰ��������ɫΪ��ɫ
	settextstyle(60, 0, _T("΢���ź�"));//
	LPCTSTR title = _T("��Ϸ����");
	settextcolor(WHITE);
	outtextxy(400, 100, title);

	//��Ϸ����


	// ���ư�ť
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // ��ť����
	Button* re_main_menu;//���ز˵�
	re_main_menu = new Button(OnButtonClick, 350, 600, 300, 75, L"���ز˵�");
	re_main_menu->RenderToWindows();
	ExMessage msg;
	bool on = 1;
	while (on)
	{
		msg = getmessage();
		if (re_main_menu->state(msg)) // ���ز˵�
		{
			flag = 1;
			printf("Return to menu\n");
			MainMenuLoop();
		}
	}
	//getch();

}

void GameLoop::SelectLevelLoop()
{
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//�������ڲ���ʾ����̨; // ��ʼ��ͼ�δ��ڴ�СΪ800*600����
	setbkcolor(CYAN);
	cleardevice();//��ʾ������ɫ      
	setbkmode(TRANSPARENT);//�������屳��
	setfillcolor(WHITE);//�������ɫ��������ǳ��ɫ
	setlinecolor(WHITE); //���õ�ǰ��������ɫΪ��ɫ
	settextstyle(60, 0, _T("΢���ź�"));//
	LPCTSTR title = _T("�ؿ�ѡ��");
	settextcolor(WHITE);
	outtextxy(400, 100, title);
	//��Ϸ����
	// ���ư�ť
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // ��ť����
	Button* re_main_menu;//���ز˵�
	Button* first_level;//��һ��

	first_level = new Button(OnButtonClick, 350, 300, 300, 75, L"��һ��");
	re_main_menu = new Button(OnButtonClick, 350, 600, 300, 75, L"���ز˵�");
	re_main_menu->RenderToWindows();
	first_level->RenderToWindows();
	ExMessage msg;
	bool on = 1;
	while (on)
	{
		msg = getmessage();
		if (first_level->state(msg)) // ��һ��
		{
			flag = 3;
			printf("Game Start!\n");
			PlaneBattleLoop();
		}
		if (re_main_menu->state(msg)) // ���ز˵�
		{
			flag = 1;
			printf("Return\n");
			MainMenuLoop();
		}
	}
	//getch();
}

//TODO
void GameLoop::PlaneBattleLoop()
{
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//�������ڲ���ʾ����̨; // ��ʼ��ͼ�δ��ڴ�СΪ800*600����
	settextcolor(CYAN);
	settextcolor(WHITE);
	settextstyle(40, 0, _T("����"));
	outtextxy(20, 20, _T("��ӭ����ս������"));
	ExMessage emg;//����ѭ�����������Ϣ
	while (1) {}
	//��ȡScroll��Ϣ
	//Scroll sc = Scroll::GetInstance();
	//while (1)
	//{//���esc������ת����Ϸ���˵�
	//    if (peekmessage(&emg))
	//    {
	//        if (emg.message == WM_KEYDOWN)
	//        {
	//            if (emg.message == VK_ESCAPE)
	//            {
	//                BattleMenuLoop();
	//            }
	//        }
	//    }
	//    else if (sc.baseLife <= 0)//����Ѫ���ľ�
	//    {
	//        BattleDefeatLoop();
	//    }
	//    else if (sc.insIdCounter == 0)//�л�ȫ��������
	//    {
	//        BattleVictoryLoop();
	//    }
	//}
	closegraph();
}

void GameLoop::PlaneWorkshopLoop()
{
	//60 X 60���� ����10 X 10

	const int ROW = 60;
	const int COL = 60;
	const int PIXEL_SIZE = 10;
	//�����鱣��ɻ���״
	int pixels[ROW][COL] = { 0 };
	initgraph(ROW * PIXEL_SIZE, COL * PIXEL_SIZE);

	// ��Ⱦ��������
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (pixels[i][j]) {
				setfillcolor(WHITE);
			}
			else {
				setfillcolor(BLACK);
			}
			fillrectangle(i * PIXEL_SIZE, j * PIXEL_SIZE,
				(i + 1) * PIXEL_SIZE, (j + 1) * PIXEL_SIZE);
		}
	}

	//����Ҽ����Ʒɻ����������˳�
	//ѭ�����������Ϣ
	while (1)
	{
		settextcolor(WHITE);
		settextstyle(20, 0, _T("����"));
		outtextxy(20, 20, _T("��ӭ�����ɻ�����"));
		ExMessage emg;
		if (peekmessage(&emg))
		{
			if (emg.message == WM_LBUTTONDOWN)
			{
				// ���������λ�ü������Ӧ����������
				int x = emg.x / PIXEL_SIZE;
				int y = emg.y / PIXEL_SIZE;
				if (x >= 0 && y >= 0 && x < ROW && y < COL)
				{
					// ��ת�����ص�ֵ
					pixels[x][y] = !pixels[x][y];

					// ����ֵ�ı仯�����þ��ε���ɫ
					if (pixels[x][y])
					{
						setfillcolor(WHITE);
					}
					else
					{
						setfillcolor(BLACK);
					}
					// ���»��ƾ���
					fillrectangle(x * PIXEL_SIZE, y * PIXEL_SIZE,
						(x + 1) * PIXEL_SIZE, (y + 1) * PIXEL_SIZE);
				}

			}//���esc�����˻�������
			else if (emg.message == WM_KEYDOWN)
			{
				if (emg.wParam == VK_ESCAPE) {
					closegraph();
					MainMenuLoop();
				}
			}

		}
	}
	closegraph();
}

/********************ldy********************/
//struct LButton
//{
//	int x1;
//	int x2;
//	int y1;
//	int y2;
//};
//void setVertexAndShowButton(LButton btn, int x1, int x2, int y1, int y2, TCHAR text[1000], int tlength, int twidth, int tsetoff, string tcolor, string lcolor, string fcolor)
//{
//	BeginBatchDraw();//��ͣ�滭
//	//���ö�������
//	btn.x1 = x1;
//	btn.x2 = x2;
//	btn.y1 = y1;
//	btn.y2 = y2;
//	//���ñ߿���ɫ
//	if (lcolor == "red" || lcolor == "RED")setlinecolor(RED);//���ñ߿���ɫΪ��ɫ
//	else if (lcolor == "green" || lcolor == "GREEN")setlinecolor(GREEN);//���ñ߿���ɫΪ��ɫ
//	else if (lcolor == "blue" || lcolor == "BLUE")setlinecolor(BLUE);//���ñ߿���ɫΪ��ɫ
//	else if (lcolor == "yellow" || lcolor == "YELLOW")setlinecolor(YELLOW);//���ñ߿���ɫΪ��ɫ
//	else if (lcolor == "black" || lcolor == "BLACK")setlinecolor(BLACK);//���ñ߿���ɫΪ��ɫ
//	else if (lcolor == "white" || lcolor == "WHITE")setlinecolor(WHITE);//���ñ߿���ɫΪ��ɫ
//	else {
//		int x;
//		x = MessageBox(GetForegroundWindow(), TEXT("���鰴ť�߿���ɫ�Ƿ�������ȷ��Ŀǰ������ɫ������red��green��blue��yellow��black��white��"), TEXT("��ť�߿���ɫ���ô���"), 1);
//		cout << x;
//	}
//	//���ư�ť�߿�
//	rectangle(btn.x1, btn.y1, btn.x2, btn.y2);
//	//���������ɫ
//	if (fcolor == "red" || fcolor == "RED")setfillcolor(RED);//���������ɫΪ��ɫ
//	else if (fcolor == "green" || fcolor == "GREEN")setfillcolor(GREEN);//���������ɫΪ��ɫ
//	else if (fcolor == "blue" || fcolor == "BLUE")setfillcolor(BLUE);//���������ɫΪ��ɫ
//	else if (fcolor == "yellow" || fcolor == "YELLOW")setfillcolor(YELLOW);//���������ɫΪ��ɫ
//	else if (fcolor == "black" || fcolor == "BLACK")setfillcolor(BLACK);//���������ɫΪ��ɫ
//	else if (fcolor == "white" || fcolor == "WHITE")setfillcolor(WHITE);//���������ɫΪ��ɫ
//	else {
//		int x;
//		x = MessageBox(GetForegroundWindow(), TEXT("���鰴ť�����ɫ�Ƿ�������ȷ��Ŀǰ�����ɫ������red��green��blue��yellow��black��white��"), TEXT("��ť�����ɫ���ô���"), 1);
//		cout << x;
//	}
//	fillrectangle(btn.x1, btn.y1, btn.x2, btn.y2);
//	//���ð�ť����
//	setbkmode(TRANSPARENT);//����͸������
//
//	if (tcolor == "red" || tcolor == "RED")settextcolor(RED);//����������ɫΪ��ɫ
//	else if (tcolor == "green" || tcolor == "GREEN")settextcolor(GREEN);//����������ɫΪ��ɫ
//	else if (tcolor == "blue" || tcolor == "BLUE")settextcolor(BLUE);//����������ɫΪ��ɫ
//	else if (tcolor == "yellow" || tcolor == "YELLOW")settextcolor(YELLOW);//����������ɫΪ��ɫ
//	else if (tcolor == "black" || tcolor == "BLACK")settextcolor(BLACK);//����������ɫΪ��ɫ
//	else if (tcolor == "white" || tcolor == "WHITE")settextcolor(WHITE);//����������ɫΪ��ɫ
//	else {
//		int x;
//		x = MessageBox(GetForegroundWindow(), TEXT("����������ɫ�Ƿ�������ȷ��Ŀǰ������ɫ������red��green��blue��yellow��black��white��"), TEXT("������ɫ���ô���"), 1);
//		cout << x;
//	}
//	//settextcolor(BLUE);//����������ɫ
//	settextstyle(tlength, twidth, _T("����"));//���������ʽ
//	outtextxy(x1 + tsetoff, y1 + tsetoff, text);//������ʾλ��
//
//
//	//���ð�ť������Ӧ
//	//MOUSEMSG m;// ���������Ϣ
//	int change = 10;
//	ExMessage m;//����һ����Ϣ����
//	m = getmessage(EM_MOUSE);//��ȡ�����Ϣ
//	switch (m.message)
//	{
//	case WM_MOUSEMOVE:
//		// ����ƶ���ťʱ��ť���
//		if (m.x >= btn.x1 && m.x <= btn.x2)
//		{
//			if (m.y >= btn.y1 && m.y <= btn.y2)
//			{
//				rectangle(btn.x1 - change, btn.y1 - change, btn.x2 + change, btn.y2 + change);
//			}
//			else
//			{
//				FlushBatchDraw();//��������
//				//cleardevice();
//			}
//		}
//		else
//		{
//			FlushBatchDraw();//��������
//			//cleardevice();
//		}
//		break;
//
//	case WM_LBUTTONDOWN:
//		// �������ť�����ɫ
//		if (m.x >= btn.x1 && m.x <= btn.x2)
//		{
//			if (m.y >= btn.y1 && m.y <= btn.y2)
//			{
//				setfillcolor(GREEN);
//				fillrectangle(btn.x1, btn.y1, btn.x2, btn.y2);
//				FlushBatchDraw();//��������
//			}
//			else
//			{
//				FlushBatchDraw();//��������
//				//cleardevice();
//			}
//		}
//		break;
//	}
//
//	//�ָ����ߺ������ɫ
//	setlinecolor(WHITE);
//	setfillcolor(WHITE);
//}

void GameLoop::BattleMenuLoop()
{
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//�������� 800*600����
	setbkcolor(CYAN);
	cleardevice();//��ʾ������ɫ      
	setbkmode(TRANSPARENT);//�������屳��
	setfillcolor(WHITE);//�������ɫ��������ǳ��ɫ
	setlinecolor(WHITE); //���õ�ǰ��������ɫΪ��ɫ
	settextstyle(60, 0, _T("΢���ź�"));
	LPCTSTR title = _T("ѡ��");
	settextcolor(WHITE);
	outtextxy(450, 100, title);
	settextcolor(WHITE);
	// ���ư�ť
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // ��ť����
	Button* re_game;//�����������水ť
	Button* re_main_menu;//���Ʒ��ز˵�
	Button* exit_game;//�˳�
	re_game = new Button(OnButtonClick, 350, 300, 300, 75, L"ѡ��ؿ�");
	re_main_menu = new Button(OnButtonClick, 350, 400, 300, 75, L"���ز˵�");
	exit_game = new Button(OnButtonClick, 350, 500, 300, 75, L"�˳���Ϸ");
	re_game->RenderToWindows();
	re_main_menu->RenderToWindows();
	exit_game->RenderToWindows();
	ExMessage msg;
	bool on = 1;
	while (on)
	{
		msg = getmessage();
		if (re_game->state(msg)) // ѡ��ؿ�
		{
			flag = 2;
			printf("Restart\n");
			SelectLevelLoop();
		}
		if (re_main_menu->state(msg)) // ���ز˵�
		{
			flag = 1;
			printf("Return\n");
			MainMenuLoop();
		}

		if (exit_game->state(msg)) {//�˳���Ϸ
			flag = -1;
			exit(0);
		}
	}
	//getch();
}

void GameLoop::BattleDefeatLoop()
{
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//�������� 800*600����
	setbkcolor(CYAN);
	cleardevice();//��ʾ������ɫ      
	setbkmode(TRANSPARENT);//�������屳��
	setfillcolor(WHITE);//�������ɫ��������ǳ��ɫ
	setlinecolor(WHITE); //���õ�ǰ��������ɫΪ��ɫ
	settextstyle(60, 0, _T("΢���ź�"));
	LPCTSTR title = _T("����ʧ��");
	settextcolor(WHITE);
	outtextxy(400, 100, title);
	settextcolor(WHITE);
	// ���ư�ť
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // ��ť����
	Button* re_game;//�����������水ť
	Button* re_main_menu;//���Ʒ��ز˵�
	Button* exit_game;//�˳�
	re_game = new Button(OnButtonClick, 350, 300, 300, 75, L"ѡ��ؿ�");
	re_main_menu = new Button(OnButtonClick, 350, 400, 300, 75, L"���ز˵�");
	exit_game = new Button(OnButtonClick, 350, 500, 300, 75, L"�˳���Ϸ");
	re_game->RenderToWindows();
	re_main_menu->RenderToWindows();
	exit_game->RenderToWindows();
	ExMessage msg;
	bool on = 1;
	while (on)
	{
		msg = getmessage();
		if (re_game->state(msg)) // ѡ��ؿ�
		{
			flag = 2;
			printf("Restart\n");
			SelectLevelLoop();
		}
		if (re_main_menu->state(msg)) // ���ز˵�
		{
			flag = 1;
			printf("Return\n");
			MainMenuLoop();
		}

		if (exit_game->state(msg)) {//�˳���Ϸ
			flag = -1;
			exit(0);
		}
	}
}

void GameLoop::BattleVictoryLoop()
{
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//�������� 800*600����
	setbkcolor(CYAN);
	cleardevice();//��ʾ������ɫ      
	setbkmode(TRANSPARENT);//�������屳��
	setfillcolor(WHITE);//�������ɫ��������ǳ��ɫ
	setlinecolor(WHITE); //���õ�ǰ��������ɫΪ��ɫ
	settextstyle(60, 0, _T("΢���ź�"));
	LPCTSTR title = _T("�������");
	settextcolor(WHITE);
	outtextxy(400, 100, title);
	settextcolor(WHITE);
	// ���ư�ť
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // ��ť����
	Button* re_game;//�����������水ť
	Button* re_main_menu;//���Ʒ��ز˵�
	Button* exit_game;//�˳�
	re_game = new Button(OnButtonClick, 350, 300, 300, 75, L"ѡ��ؿ�");
	re_main_menu = new Button(OnButtonClick, 350, 400, 300, 75, L"���ز˵�");
	exit_game = new Button(OnButtonClick, 350, 500, 300, 75, L"�˳���Ϸ");
	re_game->RenderToWindows();
	re_main_menu->RenderToWindows();
	exit_game->RenderToWindows();
	ExMessage msg;
	bool on = 1;
	while (on)
	{
		msg = getmessage();
		if (re_game->state(msg)) // ѡ��ؿ�
		{
			flag = 2;
			printf("Restart\n");
			SelectLevelLoop();
		}
		if (re_main_menu->state(msg)) // ���ز˵�
		{
			flag = 1;
			printf("Return\n");
			MainMenuLoop();
		}

		if (exit_game->state(msg)) {//�˳���Ϸ
			flag = -1;
			exit(0);
		}
	}
}


