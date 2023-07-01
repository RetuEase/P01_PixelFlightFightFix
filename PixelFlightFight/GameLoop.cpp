#include "GameLoop.h"
#include <iostream>
#include <filesystem>

#ifdef UNICODE
// ��������� UNICODE �꣬���ַ���������ת��Ϊ���ַ�
#define TSTRING std::wstring
#define TOSTRING std::to_wstring
#else
// ���δ���� UNICODE �꣬���ַ���������ת��Ϊ���ֽ��ַ�
#define TSTRING std::string
#define TOSTRING std::to_string
#endif

/********************yjl********************/
GameLoop::GameLoop() :flag(1) {
	iintroKey = 0;
	//memset(keyDown, 0, sizeof(bool) * KEY_COUNT);
	mciSendString(L"open \"bgm.mp3\" alias bgm", NULL, 0, NULL);
	mciSendString(L"play bgm repeat", NULL, 0, NULL);
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
	Sleep(500);

	// ��ѭ��
	while (true)
	{
		cleardevice();
		MainMenuLoop();//������
		//// �����Ļ
		//cleardevice();

		//// ���ݵ�ǰҳ��״̬����ҳ��
		//if (flag == 1)
		//{
		//	MainMenuLoop();//������
		//}
		//else if (flag == 2)
		//{
		//	SelectLevelLoop(); //�ؿ�����
		//}
		//else if (flag == 3)
		//{
		//	PlaneBattleLoop();//ս������

		//}
		//else if (flag == 4)
		//{
		//	PlaneBattleLoop();//���ܽ���
		//}
		//else if (flag == 5)
		//{
		//	PlaneWorkshopLoop();//�ɻ�����
		//}
		//// �ȴ�һ��ʱ�䣬����ˢ���ٶ�
		//Sleep(100);
	}

}
void GameLoop::MainMenuLoop()		
{
	EndBatchDraw();
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//�������ڲ���ʾ����̨; // ��ʼ��ͼ�δ��ڴ�СΪ800*600����
	setbkcolor(BGCOLOR);  //��ʾ������ɫ
	cleardevice();      //SECONDCOLOR
	setbkmode(BGCOLOR);//����������ɫ
	setfillcolor(WHITE);//�������ɫ��	
	setlinecolor(WHITE); //���õ�ǰ��������ɫ//line(0, 780, 620, 780);
	settextstyle(60, 50, _T("΢���ź�"));
	settextcolor(GOLDENCOLOR);

	IMAGE img;
	loadimage(&img, _T("title.png"));
	//setaspectratio(0.9, 0.9);
	putimage(0, 10, &img);
	setaspectratio(1, 1);
	setfillcolor(SECONDCOLOR);//�������ɫ
	setlinecolor(SECONDCOLOR);
	//fillrectangle(353, 105, 450, 160); // ��ť����
	setlinecolor(WHITE);

	//settextcolor(WHITE);
	//outtextxy(355, 100, _T("����"));

	settextcolor(GOLDENCOLOR);
	setfillcolor(BGCOLOR);//�������ɫ
	// ���ư�ť
	//fillrectangle(350, 100, 300, 75); // ��ť����
	Button* Begin;//���ư�ť
	Button* WorkShop;//���Ʒɻ�����
	Button* Operating_instructions;//���Ʋ���˵��
	Button* exit_game;//�˳�
	Operating_instructions = new Button(OnButtonClick, 470, 380, 300, 75, L"��Ϸ����");
	Begin = new Button(OnButtonClick, 470, 480, 300, 75, L"��ʼ��Ϸ");
	WorkShop = new Button(OnButtonClick, 470, 580, 300, 75, L"�ɻ�����");
	exit_game = new Button(OnButtonClick, 470, 680, 300, 75, L"�˳���Ϸ");
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
			SelectLevelLoop();
		}
		if (WorkShop->state(msg)) // �ɻ�����
		{
			flag = 5;
			PlaneWorkshopLoop();
		}
		if (Operating_instructions->state(msg)) // ����
		{
			if (iintroKey == 0)
			{
				InstructionsLoop();
				iintroKey = 1;
				return;
			}
			else {
				iintroKey = 0;
			} 

			
		}
		if (exit_game->state(msg)) {//�˳���Ϸ
			flag = 0;
			exit(0);
		}
	}
}
//getch();

//TODO 
//���ܽ���
void GameLoop::InstructionsLoop()
{
	IMAGE images[42];
	loadimage(&images[0], _T("intro/title00.gif"));	loadimage(&images[1], _T("intro/title01.gif"));	loadimage(&images[2], _T("intro/title02.gif"));	loadimage(&images[3], _T("intro/title03.gif"));	loadimage(&images[4], _T("intro/title04.gif"));	loadimage(&images[5], _T("intro/title05.gif"));	loadimage(&images[6], _T("intro/title06.gif"));	loadimage(&images[7], _T("intro/title07.gif"));	loadimage(&images[8], _T("intro/title08.gif"));	loadimage(&images[9], _T("intro/title09.gif"));	loadimage(&images[10], _T("intro/title10.gif"));	loadimage(&images[11], _T("intro/title11.gif"));	loadimage(&images[12], _T("intro/title12.gif"));	loadimage(&images[13], _T("intro/title13.gif"));	loadimage(&images[14], _T("intro/title14.gif"));	loadimage(&images[15], _T("intro/title15.gif"));	loadimage(&images[16], _T("intro/title16.gif"));	loadimage(&images[17], _T("intro/title17.gif"));	loadimage(&images[18], _T("intro/title18.gif"));	loadimage(&images[19], _T("intro/title19.gif"));	loadimage(&images[20], _T("intro/title20.gif"));	loadimage(&images[21], _T("intro/title21.gif"));	loadimage(&images[22], _T("intro/title22.gif"));	loadimage(&images[23], _T("intro/title23.gif"));	loadimage(&images[24], _T("intro/title24.gif"));	loadimage(&images[25], _T("intro/title25.gif"));	loadimage(&images[26], _T("intro/title26.gif"));	loadimage(&images[27], _T("intro/title27.gif"));	loadimage(&images[28], _T("intro/title28.gif"));	loadimage(&images[29], _T("intro/title29.gif"));	loadimage(&images[30], _T("intro/title30.gif"));	loadimage(&images[31], _T("intro/title31.gif"));	loadimage(&images[32], _T("intro/title32.gif"));	loadimage(&images[33], _T("intro/title33.gif"));	loadimage(&images[34], _T("intro/title34.gif"));	loadimage(&images[35], _T("intro/title35.gif"));	loadimage(&images[36], _T("intro/title36.gif"));	loadimage(&images[37], _T("intro/title37.gif"));	loadimage(&images[38], _T("intro/title38.gif"));	loadimage(&images[39], _T("intro/title39.gif"));	loadimage(&images[40], _T("intro/title40.gif"));	loadimage(&images[41], _T("intro/title41.gif"));	int imgNumber = 42;	int x = 100, y = 100;// ����ͼƬ�ĳ�ʼλ��	

	int imageIndex = 0;// ͼƬ������

	// ��ʼ���ƶ���
	BeginBatchDraw();//��ʼ������ͼ

	for(; imageIndex <imgNumber; imageIndex++)
	{
		// ��ջ�ͼ����
		//cleardevice();
		// ���Ƶ�ǰͼƬ
		putimage(x, y, &images[imageIndex]);
		Sleep(400);
		// ǰ������һ��ͼƬ		
		FlushBatchDraw();
	}

	BeginBatchDraw();
}



void GameLoop::SelectLevelLoop()
{
	Sleep(500);

	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//�������ڲ���ʾ����̨; // ��ʼ��ͼ�δ��ڴ�СΪ800*600����
	setbkcolor(BGCOLOR);
	cleardevice();//��ʾ������ɫ      
	setbkmode(TRANSPARENT);//�������屳��
	setfillcolor(WHITE);//�������ɫ��������ǳ��ɫ
	setlinecolor(WHITE); //���õ�ǰ��������ɫΪ��ɫ
	settextstyle(60, 0, _T("΢���ź�"));//
	LPCTSTR title = _T("�ؿ�ѡ��");
	settextcolor(SECONDCOLOR);
	outtextxy(525, 100, title);
	settextcolor(GOLDENCOLOR);
	// ���ư�ť
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // ��ť����
	Button* re_main_menu;//���ز˵�
	Button* first_level;//��һ��

	first_level = new Button(OnButtonClick, 470, 380, 300, 75, L"��һ��");
	re_main_menu = new Button(OnButtonClick, 470, 680, 300, 75, L"���ز˵�");
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
}

void GameLoop::PlaneBattleLoop()
{
	Sleep(500);

	LevelSetUp();
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//��������

	setbkcolor(BGCOLOR);
	cleardevice();//��ʾ������ɫ      
	setbkmode(TRANSPARENT);//�������屳��
	setfillcolor(WHITE);//�������ɫ
	setlinecolor(WHITE); //���õ�ǰ��������ɫ
	GAMEEND = false;
	//��ȡScroll��Ϣ
	Scroll sc = Scroll::GetInstance();
	int space = 1;
	//��������
	while (1)
	{
		BeginBatchDraw();//��ʼ������ͼ
		setbkcolor(BGCOLOR);
		cleardevice();  // ��մ���
		setfillcolor(OTHERCOLOR);
		settextcolor(GOLDENCOLOR);
		//outtextxy(20, 20, _T("����"));
		settextstyle(30, 15, _T("΢���ź�"));
		std::wstring str = std::to_wstring(SCORE);
		LPCTSTR score = str.c_str();//����
		outtextxy(615, 20, score);
		settextcolor(GOLDENCOLOR);
		setfillcolor(OTHERCOLOR);
		rectangle(BLANK_L - 90, BLANK_U, BLANK_L - 30, BLANK_U + 30);
		settextstyle(30, 0, _T("΢���ź�"));
		outtextxy(BLANK_L - 80, BLANK_U, _T("ESC"));
		setlinecolor(BACKCOLOR); //���õ�ǰ��������ɫ
		setlinestyle(PS_SOLID, 2);
		line(BLANK_L - 2, BLANK_U - 2, BLANK_R + 2, BLANK_U - 2);
		line(BLANK_L - 2, BLANK_U - 2, BLANK_L - 2, BLANK_D + 2);
		line(BLANK_L - 2, BLANK_D + 2, BLANK_R + 2, BLANK_D + 2);
		line(BLANK_R + 2, BLANK_U - 2, BLANK_R + 2, BLANK_D + 2);



		setlinestyle(PS_SOLID, 1);

		++sc.fireCD;

		//for (int x = BLANK_L; x <= BLANK_R; x += BLOCKSIZE)
		//{
		//	for (int y = BLANK_U; y <= BLANK_D; y += BLOCKSIZE)
		//	{
		//		line(x, BLANK_U, x, BLANK_D);  // ���ƴ�ֱ��
		//		line(BLANK_L, y, BLANK_R, y);  // ����ˮƽ��
		//	}
		//}
		bool fire = false;
		//���esc������ת����Ϸ���˵�
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000 ||
			GetAsyncKeyState(VK_UP) & 0x8000 ||
			GetAsyncKeyState(VK_DOWN) & 0x8000 ||
			GetAsyncKeyState(VK_LEFT) & 0x8000 ||
			GetAsyncKeyState(VK_RIGHT) & 0x8000 ||
			GetAsyncKeyState(VK_SPACE) & 0x8000
			) {
			bool esc = GetAsyncKeyState(VK_ESCAPE) & 0x8000;
			if (esc)
			{
				//cout << "��ͣ!" << endl;
				EndBatchDraw();
				BattleMenuLoop();//�л����˵�		
			}
			else {
				//bool fire = GetAsyncKeyState(VK_SPACE) & 0x8000;
				bool up = GetAsyncKeyState(VK_UP) & 0x8000;
				bool down = GetAsyncKeyState(VK_DOWN) & 0x8000;
				bool left = GetAsyncKeyState(VK_LEFT) & 0x8000;
				bool right = GetAsyncKeyState(VK_RIGHT) & 0x8000;
				fire = GetAsyncKeyState(VK_SPACE) & 0x8000;
				int u = 0;
				int d = 0;
				int l = 0;
				int r = 0;
				if (up) {
					u = -1;
				}
				if (down) { d = 1; }
				if (left) { l = -1; }
				if (right) { r = 1; }

				sc.playSpeed = { l + r,u + d };
			}
		}
		else {
			sc.playSpeed = { 0,0 };
		}

		if (space == 1) {
			setfillcolor(OTHERCOLOR);
			settextcolor(GOLDENCOLOR);
			settextstyle(30, 0, _T("΢���ź�"));
			outtextxy(600, 320, _T("SPACE"));
		}

		//�����ӵ�
		if (fire && sc.fireCD >= 15) {
			if (space == 1)
			{
				space = 0;
				cleardevice();  // ��մ���
			}

			Bullet* b = new Bullet(1);
			//cout << b->blockID;
			sc.fireCD = 0;
			fire = false;

		}
		sc.GameUpdate();

		//��������ʵ��
		//cout << "size: " << Bullet::AllEntities.size() << endl;
		for (const auto& pair : Bullet::AllEntities) {
			std::shared_ptr<Bullet> bulletptr = pair.second;

			//�л�	
			if (bulletptr->entityType == _EntityEnemy) {
				if (bulletptr->core.y <= MAPSIZE_Y - 1 && bulletptr->core.y >= 0 && bulletptr->core.x <= MAPSIZE_X - 1 && bulletptr->core.x >= 0) {
					//line(BLANK_L, BLANK_U, BLANK_R, BLANK_D);  // ���ƴ�ֱ��
					// ���������ڴ����е�λ��
					int x = BLANK_L + bulletptr->core.x * BLOCKSIZE;
					int y = BLANK_U + bulletptr->core.y * BLOCKSIZE;
					// ���� Block
					setlinecolor(WHITE);
					setfillcolor(CORECOLOR);
					solidrectangle(x, y, x + BLOCKSIZE, y + BLOCKSIZE); // ���ƾ��Σ��߳�Ϊ BLOCKSIZE
				}
			}
			//�ӵ�
			else if (bulletptr->entityType == _EntityBullet) {
				//line(BLANK_L, BLANK_U, BLANK_R, BLANK_D);  // ���ƴ�ֱ��
				// ���������ڴ����е�λ��
				if (bulletptr->core.y <= MAPSIZE_Y - 1 && bulletptr->core.y >= 0 && bulletptr->core.x <= MAPSIZE_X - 1 && bulletptr->core.x >= 0) {
					//cout << "!!!" << endl;
					int x = BLANK_L + bulletptr->core.x * BLOCKSIZE;
					int y = BLANK_U + bulletptr->core.y * BLOCKSIZE;

					// ���� Block
					setlinecolor(WHITE);
					setfillcolor(BULLETCOLOR);
					solidrectangle(x, y, x + BLOCKSIZE, y + BLOCKSIZE); // ���ƾ��Σ��߳�Ϊ BLOCKSIZE
				}
			}
			//�Ի�
			else if (bulletptr->entityType == _EntityPlayer) {
				//���ƺ���
				int corex = BLANK_L + bulletptr->core.x * BLOCKSIZE;
				int corey = BLANK_U + bulletptr->core.y * BLOCKSIZE;
				setlinecolor(SECONDCOLOR);
				setfillcolor(GOLDENCOLOR);
				solidrectangle(corex, corey, corex + BLOCKSIZE, corey + BLOCKSIZE);
				//���Ƹ��Ի�
				setfillcolor(BULLETCOLOR);
				for (const auto& pair : Bullet::PlayerPlaneBlock) {
					const Coordinate& coord = pair.first;
					if (bulletptr->core.y + coord.y <= MAPSIZE_Y - 1 && bulletptr->core.y + coord.y >= 0 && bulletptr->core.x + coord.x <= MAPSIZE_X - 1 && bulletptr->core.x + coord.x >= 0) {
						// ���������ڴ����е�λ��
						int x = BLANK_L + bulletptr->core.x * BLOCKSIZE + coord.x * BLOCKSIZE;
						int y = BLANK_U + bulletptr->core.y * BLOCKSIZE + coord.y * BLOCKSIZE;
						// ���� Block
						setlinecolor(WHITE);
						setfillcolor(BULLETCOLOR);
						solidrectangle(x, y, x + BLOCKSIZE, y + BLOCKSIZE);
					}
				}

			}
		}
		EndBatchDraw();//ִ��δ��ɵĻ�������

		if (GAMEEND)//���ı���
		{
			EndBatchDraw();// ������������
			BattleDefeatLoop();
		}
		if (Bullet::enemiesNum <= 0)//�л�ȫ��������
		{
			EndBatchDraw();// ������������
			BattleVictoryLoop();
		}

		Sleep(FRAMEINTERVAL);

	}
	//closegraph();
}

void GameLoop::PlaneWorkshopLoop()
{
	Sleep(500);

	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//�������ڲ���ʾ����̨; // ��ʼ��ͼ�δ��ڴ�СΪ800*600����
	setbkcolor(BGCOLOR);
	PlaneCanvas pc;
	while (1) {
		cleardevice();
		setbkmode(TRANSPARENT);//�������屳��
		setfillcolor(WHITE);//�������ɫ��������ǳ��ɫ
		setlinecolor(WHITE); //���õ�ǰ��������ɫΪ��ɫ
		settextstyle(60, 0, _T("΢���ź�"));//
		settextcolor(GOLDENCOLOR);
		LPCTSTR title = _T("�ɻ�����");
		outtextxy(525, 80, title);
		settextstyle(40, 0, _T("΢���ź�"));
		settextcolor(GOLDENCOLOR);
		LPCTSTR intro1 = _T("��༭�Լ��ķɻ�");
		outtextxy(500, 140, intro1);
		LPCTSTR intro2 = _T("�����ӻ��� �м�ѡ����� �Ҽ�ɾ������");
		outtextxy(350, 180, intro2);
		settextstyle(30, 0, _T("΢���ź�"));
		LPCTSTR intro4 = _T("ע��: ������������Ļ�������");
		outtextxy(460, 230, intro4);
		LPCTSTR intro3 = _T("ֻ������˺��Ĳ���Ӧ��");
		outtextxy(950, 620, intro3);

		settextcolor(GOLDENCOLOR);
		BeginBatchDraw();//��ʼ������ͼ

		//��������
		setlinecolor(BACKCOLOR); //���õ�ǰ��������ɫ
		setlinestyle(PS_SOLID, 2);
		line(WORKSHOP_L - 2, WORKSHOP_U - 2, WORKSHOP_R + 2, WORKSHOP_U - 2);
		line(WORKSHOP_L - 2, WORKSHOP_U - 2, WORKSHOP_L - 2, WORKSHOP_D + 2);
		line(WORKSHOP_L - 2, WORKSHOP_D + 2, WORKSHOP_R + 2, WORKSHOP_D + 2);
		line(WORKSHOP_R + 2, WORKSHOP_U - 2, WORKSHOP_R + 2, WORKSHOP_D + 2);
		setlinestyle(PS_SOLID, 1);

		setlinestyle(PS_DASHDOT, 1);
		for (int x = WORKSHOP_L; x <= WORKSHOP_R; x += WORKSHOP_SIZE)
		{
			for (int y = WORKSHOP_U; y <= WORKSHOP_D; y += WORKSHOP_SIZE)
			{
				line(x, WORKSHOP_U, x, WORKSHOP_D);  // ���ƴ�ֱ��
				line(WORKSHOP_L, y, WORKSHOP_R, y);  // ����ˮƽ��
			}
		}
		// ѭ������������¼�
		setfillcolor(WHITE);	// ���ư�ť
		Button* re_main_menu;//����
		re_main_menu = new Button(OnButtonClick, 920, 680, 300, 75, L"Ӧ�ò�����");
		re_main_menu->RenderToWindows();
		while (true)
		{
			FlushMouseMsgBuffer();
			// ���������¼�
			if (MouseHit())
			{

				// ��ȡ������¼�
				MOUSEMSG msg = GetMouseMsg();
				//cout << "click" << left << " " << " " << msg.x << " " << msg.y << endl;// �������ĸ�������

				if (msg.x >= 920 && msg.x <= 1220 && msg.y >= 680 && msg.y <= 755) // ����
				{
					if (msg.mkLButton)
					{
						pc.paintPlane.DesignPlane();
						EndBatchDraw();
						flag = 1;
						MainMenuLoop();
					}
				}
				// �����������Ļ����ת��Ϊ����������
				int x = (msg.x - WORKSHOP_L) / WORKSHOP_SIZE;
				int y = (msg.y - WORKSHOP_U) / WORKSHOP_SIZE;

				// �жϵ���ĸ����Ƿ��ڴ�����
				if (x >= 0 && x < WORKSHOP_X && y >= 0 && y < WORKSHOP_Y)
				{
					int button = 0;	//���1 �Ҽ�2 �м�3
					if (msg.mkLButton)
					{
						button = 1;
					}
					if (msg.mkRButton)
					{
						button = 2;
					}
					if (msg.mkMButton)
					{
						button = 3;
					}
					//cout << button<<endl;
					pc.Click({ x, y }, button);
					//cout << "click " << x << ", " << y << endl;// �������ĸ�������
					break;
				}
			}
			//Sleep(WORKSHOPFLASH);
		}
		//���ƻ���
		for (const Coordinate& coordinate : pc.paintPlane.spriteMap) {
			setfillcolor(BULLETCOLOR);
			int x = WORKSHOP_SIZE * coordinate.x + WORKSHOP_L;
			int y = WORKSHOP_SIZE * coordinate.y + WORKSHOP_U;
			solidrectangle(x + 1, y + 1, x + WORKSHOP_SIZE - 1, y + WORKSHOP_SIZE - 1); // ���ƻ����߳�Ϊ WORKSHOP_SIZE
		}
		//���ƺ���
		for (const Coordinate& ccoordinate : pc.paintPlane.core) {
			setfillcolor(CORECOLOR);
			int x = WORKSHOP_SIZE * ccoordinate.x + WORKSHOP_L;
			int y = WORKSHOP_SIZE * ccoordinate.y + WORKSHOP_U;
			solidrectangle(x + 1, y + 1, x + WORKSHOP_SIZE - 1, y + WORKSHOP_SIZE - 1); // ���ƺ��ģ��߳�Ϊ WORKSHOP_SIZE

		}

		setlinestyle(PS_SOLID, 1);
		setfillcolor(OTHERCOLOR);
		settextcolor(GOLDENCOLOR);
		settextstyle(40, 0, _T("΢���ź�"));
		outtextxy(50, 520, _T("ʣ���������: "));
		std::wstring planeNumStr = std::to_wstring(pc.paintPlane.planCountMax - pc.paintPlane.spriteMap.size());
		LPCTSTR planeNum = planeNumStr.c_str();//��������
		outtextxy(250, 520, planeNum);
		outtextxy(50, 620, _T("ʣ���������:"));
		std::wstring coreNumStr = std::to_wstring(pc.paintPlane.coreCountMax - pc.paintPlane.core.size());
		LPCTSTR coreNum = coreNumStr.c_str();//��������
		outtextxy(250, 620, coreNum);

		FlushBatchDraw();//ִ��δ��ɵĻ�������	

		//�����鱣��ɻ���״
		//int pixels[WORKSHOP_X][WORKSHOP_Y] = { 0 };
		//for (const auto& pair : Bullet::AllEntities) {
		//	std::shared_ptr<Bullet> bulletptr = pair.second;
		//	//�л�	
		//	if (bulletptr->entityType == _EntityEnemy) {
		//		if (bulletptr->core.y <= MAPSIZE_Y - 1 && bulletptr->core.y >= 0 && bulletptr->core.x <= MAPSIZE_X - 1 && bulletptr->core.x >= 0) {
		//			//line(BLANK_L, BLANK_U, BLANK_R, BLANK_D);  // ���ƴ�ֱ��
		//			// ���������ڴ����е�λ��
		//			int x = BLANK_L + bulletptr->core.x * BLOCKSIZE;
		//			int y = BLANK_U + bulletptr->core.y * BLOCKSIZE;
		//			// ���� Block
		//			setlinecolor(WHITE);
		//			setfillcolor(CORECOLOR);
		//			solidrectangle(x, y, x + BLOCKSIZE, y + BLOCKSIZE); // ���ƾ��Σ��߳�Ϊ BLOCKSIZE
		//		}
		//	}
		//
		////��Ⱦ��������
		//for (int i = 0; i < WORKSHOP_X; i++)
		//{
		//	for (int j = 0; j < WORKSHOP_Y; j++)
		//	{
		//		if (pixels[i][j])
		//		{
		//			if (pixels[i][j] == 999) {
		//				setfillcolor(CORECOLOR);
		//			}
		//			else{
		//				setfillcolor(BULLETCOLOR);
		//			}
		//			int x = WORKSHOP_SIZE * i;
		//			int y = WORKSHOP_SIZE * j;
		//			solidrectangle(x, y, x + WORKSHOP_SIZE, y + WORKSHOP_SIZE); // ���ƾ��Σ��߳�Ϊ WORKSHOP_SIZE
		//		}
		//	}
		//}


	}

	//ExMessage emg;
	//	if (peekmessage(&emg))
	//	{
	//		if (emg.message == WM_LBUTTONDOWN)
	//		{
	//			Coordinate cor(emg.x, emg.y); //����λ��
	//			pc.Click(cor, true);
	//		}//���esc�����˻�������
	//		else if (emg.message == WM_RBUTTONDOWN)
	//		{
	//			Coordinate cor(emg.x, emg.y); //����λ��
	//			pc.Click(cor, false);
	//		}
	//		else if (emg.message == WM_KEYDOWN)
	//		{				
	//		}
	//	}


}

void GameLoop::LevelSetUp()
{
	Sleep(500);

	I_IdCounter = 1;
	SCORE = 0;
	GAMEEND = 0;

	Bullet::PLAYERPLANECORE = Coordinate( 15, 35);	//Ĭ�Ϸɻ�����λ��
	Bullet::ENEMYMAP.clear();
	Bullet::PlayerPlaneBlock.clear();
	Bullet::AllEntities.clear();
	Bullet::keysToDelete.clear();

	//���ɵ���
	Plane* b = new Plane(Coordinate(12, -12));
	Plane* b1 = new Plane(Coordinate(25, -56));
	Plane* b2 = new Plane(Coordinate(30, -192));
	Plane* b3 = new Plane(Coordinate(25, -56));
	Plane* b4 = new Plane(Coordinate(24, -50));
	Plane* b5 = new Plane(Coordinate(20, -68));
	Plane* b6 = new Plane(Coordinate(2, -150));
	Plane* b7 = new Plane(Coordinate(28, -175));
	Plane* b8 = new Plane(Coordinate(27, -153));
	Plane* b9 = new Plane(Coordinate(17, -50));
	Plane* b10 = new Plane(Coordinate(9, -184));
	Plane* b11 = new Plane(Coordinate(11, -8));
	Plane* b12 = new Plane(Coordinate(16, -120));
	Plane* b13 = new Plane(Coordinate(26, -12));
	Plane* b14 = new Plane(Coordinate(9, -104));
	Plane* b15 = new Plane(Coordinate(28, -172));
	Plane* b16 = new Plane(Coordinate(22, -120));
	Plane* b17 = new Plane(Coordinate(29, -32));
	Plane* b18 = new Plane(Coordinate(14, -64));
	Plane* b19 = new Plane(Coordinate(30, -40));
	Plane* b20 = new Plane(Coordinate(31, -20));

	//std::random_device rd;
	//std::mt19937 gen(rd());
	//std::uniform_int_distribution<int> dist(-31, 0);
	//for (int i = 0; i < ENEMIESNUMBER; i++) {
	//	std::cout << "(" << dist(gen) << ", " << dist(gen) * dist(gen) * dist(gen) % 200 << ")" << std::endl;
	//	Coordinate co(dist(gen), dist(gen) * dist(gen) * dist(gen) % 200);
	//
	//}

	//��ʼ����ҷɻ�
	PlayerPlane mp(PlaneTemplate::Defalut_Plane);
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
	Sleep(500);

	//EndBatchDraw();
	//initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//�������� 800*600����
	setbkcolor(BGCOLOR);
	cleardevice();
	setbkmode(TRANSPARENT);//�������屳��
	setfillcolor(WHITE);//�������ɫ��������ǳ��ɫ
	setlinecolor(WHITE); //���õ�ǰ��������ɫΪ��ɫ
	settextstyle(60, 0, _T("΢���ź�"));
	LPCTSTR title = _T("��ͣ");
	settextcolor(GOLDENCOLOR);
	outtextxy(570, 100, title);
	// ���ư�ť
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // ��ť����
	Button* re_game;//�����������水ť
	Button* re_main_menu;//���Ʒ��ز˵�
	Button* exit_game;//�˳�
	re_game = new Button(OnButtonClick, 470, 480, 300, 75, L"���عؿ�");
	re_main_menu = new Button(OnButtonClick, 470, 580, 300, 75, L"���ز˵�");
	exit_game = new Button(OnButtonClick, 470, 680, 300, 75, L"�˳���Ϸ");
	re_game->RenderToWindows();
	re_main_menu->RenderToWindows();
	exit_game->RenderToWindows();
	ExMessage msg;
	bool on = 1;
	while (on)
	{
		msg = getmessage();
		if (re_game->state(msg)) // ���عؿ�
		{
			flag = 2;
			printf("Restart\n");
			//BeginBatchDraw();
			//closegraph();
			return;

		}
		if (re_main_menu->state(msg)) // ���ز˵�
		{
			flag = 1;
			printf("Return\n");
			MainMenuLoop();
		}

		if (exit_game->state(msg)) {//�˳���Ϸ
			flag = 0;
			exit(0);
		}
	}
}

void GameLoop::BattleDefeatLoop()
{
	Sleep(500);

	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//�������� 800*600����
	setbkcolor(BGCOLOR);
	cleardevice();//��ʾ������ɫ      
	setbkmode(TRANSPARENT);//�������屳��
	setfillcolor(WHITE);//�������ɫ��������ǳ��ɫ
	setlinecolor(WHITE); //���õ�ǰ��������ɫΪ��ɫ
	settextstyle(60, 0, _T("΢���ź�"));
	LPCTSTR title = _T("����ʧ��");
	settextcolor(GOLDENCOLOR);
	outtextxy(525, 100, title);

	settextstyle(40, 0, _T("΢���ź�"));
	settextcolor(OTHERCOLOR);
	outtextxy(580, 180, _T("����: "));
	settextcolor(GOLDENCOLOR);
	std::wstring str = std::to_wstring(SCORE);
	LPCTSTR score = str.c_str();//����
	outtextxy(650, 180, score);


	// ���ư�ť
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // ��ť����
	Button* re_game;//�����������水ť
	Button* re_main_menu;//���Ʒ��ز˵�
	Button* exit_game;//�˳�
	re_game = new Button(OnButtonClick, 470, 480, 300, 75, L"ѡ��ؿ�");
	re_main_menu = new Button(OnButtonClick, 470, 580, 300, 75, L"���ز˵�");
	exit_game = new Button(OnButtonClick, 470, 680, 300, 75, L"�˳���Ϸ");
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
			flag = 0;
			exit(0);
		}
	}
}

void GameLoop::BattleVictoryLoop()
{
	Sleep(500);

	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//�������� 800*600����
	setbkcolor(BGCOLOR);
	cleardevice();//��ʾ������ɫ      
	setbkmode(TRANSPARENT);//�������屳��
	setfillcolor(WHITE);//�������ɫ��������ǳ��ɫ
	setlinecolor(WHITE); //���õ�ǰ��������ɫΪ��ɫ
	settextstyle(60, 0, _T("΢���ź�"));
	LPCTSTR title = _T("�������");
	settextcolor(GOLDENCOLOR);
	outtextxy(525, 100, title);
	settextstyle(40, 0, _T("΢���ź�"));
	settextcolor(OTHERCOLOR);
	outtextxy(580, 180, _T("����: "));
	settextcolor(GOLDENCOLOR);
	std::wstring str = std::to_wstring(SCORE);
	LPCTSTR score = str.c_str();//����
	outtextxy(650, 180, score);

	// ���ư�ť
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // ��ť����
	Button* re_game;//�����������水ť
	Button* re_main_menu;//���Ʒ��ز˵�
	Button* exit_game;//�˳�
	re_game = new Button(OnButtonClick, 470, 480, 300, 75, L"ѡ��ؿ�");
	re_main_menu = new Button(OnButtonClick, 470, 580, 300, 75, L"���ز˵�");
	exit_game = new Button(OnButtonClick, 470, 680, 300, 75, L"�˳���Ϸ");
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
			flag = 0;
			exit(0);
		}
	}
}
