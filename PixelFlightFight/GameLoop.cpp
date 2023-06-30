#include "GameLoop.h"



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
	setbkcolor(BGCOLOR);
	cleardevice();//��ʾ������ɫ      
	setbkmode(TRANSPARENT);//�������屳��
	setfillcolor(WHITE);//�������ɫ��������ǳ��ɫ
	setlinecolor(WHITE); //���õ�ǰ��������ɫΪ��ɫ
	settextstyle(60, 0, _T("΢���ź�"));//
	settextcolor(SECONDCOLOR);
	LPCTSTR title = _T("��Ϸ����");
	outtextxy(525, 100, title);
	settextcolor(GOLDENCOLOR);
	//��Ϸ����:
	//TODO


	// ���ư�ť
	setfillcolor(WHITE);

	Button* re_main_menu;//���ز˵�
	re_main_menu = new Button(OnButtonClick, 470, 680, 300, 75, L"���ز˵�");
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
	LevelSetUp();
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//��������
	BeginBatchDraw();//��ʼ������ͼ
	setbkcolor(BGCOLOR);
	cleardevice();//��ʾ������ɫ      
	setbkmode(TRANSPARENT);//�������屳��
	setfillcolor(WHITE);//�������ɫ
	setlinecolor(WHITE); //���õ�ǰ��������ɫ
	GAMEEND = false;
	//��ȡScroll��Ϣ
	Scroll sc = Scroll::GetInstance();
	BeginBatchDraw();//��ʼ������ͼ	


	//��������
	while (1)
	{
		setbkcolor(BGCOLOR);
		cleardevice();  // ��մ���
		setfillcolor(OTHERCOLOR);
		settextcolor(GOLDENCOLOR);
		outtextxy(20, 20, _T("����"));
		std::wstring str = std::to_wstring(SCORE);
		LPCTSTR score = str.c_str();//����
		outtextxy(70, 20, score);
		settextcolor(GOLDENCOLOR);

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
		//���esc������ת����Ϸ���˵�
		if (_kbhit()) {
			bool esc = GetAsyncKeyState(VK_ESCAPE) & 0x8000;
			if (esc)
			{
				cout << "��ͣ!" << endl;
				EndBatchDraw();
				BattleMenuLoop();//�л����˵�		
			}
			else {
				//bool fire = GetAsyncKeyState(VK_SPACE) & 0x8000;
				bool up = GetAsyncKeyState(VK_UP) & 0x8000;
				bool down = GetAsyncKeyState(VK_DOWN) & 0x8000;
				bool left = GetAsyncKeyState(VK_LEFT) & 0x8000;
				bool right = GetAsyncKeyState(VK_RIGHT) & 0x8000;
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
		//�����ӵ�
		if (sc.fireCD >= 5) {//fire &&
			Bullet* b = new Bullet(1);
			//cout << b->blockID;
			sc.fireCD = 0;
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
		FlushBatchDraw();//ִ��δ��ɵĻ�������

		//if (GAMEEND)//���ı���
		//{
		//	EndBatchDraw();// ������������
		//	BattleDefeatLoop();
		//}
		//if (sc.enemiesNum <= 0)//�л�ȫ��������
		//{
		//	EndBatchDraw();// ������������
		//	BattleVictoryLoop();
		//}

		Sleep(FRAMEINTERVAL);

	}
	//closegraph();
}


//REDO
void GameLoop::PlaneWorkshopLoop()
{
	//60 X 60���� ����10 X 10
	const int ROW = 60;
	const int COL = 60;
	const int PIXEL_SIZE = 10;
	//�����鱣��ɻ���״
	int pixels[ROW][COL] = { 0 };
	initgraph(ROW * PIXEL_SIZE, COL * PIXEL_SIZE);

	//��Ⱦ��������
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
	PlaneCanvas pc(WHITE);
	while (1)
	{
		ExMessage emg;
		if (peekmessage(&emg))
		{
			if (emg.message == WM_LBUTTONDOWN)
			{
				Coordinate cor(emg.x, emg.y); //����λ��
				pc.Click(cor, true);
			}//���esc�����˻�������
			else if (emg.message == WM_RBUTTONDOWN)
			{
				Coordinate cor(emg.x, emg.y); //����λ��
				pc.Click(cor, false);
			}
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

	//60 X 60���� ����10 X 10
	//const int ROW = 60;
	//const int COL = 60;
	//const int PIXEL_SIZE = 10;
	////�����鱣��ɻ���״
	//int pixels[ROW][COL] = { 0 };
	//initgraph(ROW * PIXEL_SIZE, COL * PIXEL_SIZE);
	//// ��Ⱦ��������
	//for (int i = 0; i < ROW; i++)
	//{
	//	for (int j = 0; j < COL; j++)
	//	{
	//		if (pixels[i][j]) {
	//			setfillcolor(WHITE);
	//		}
	//		else {
	//			setfillcolor(BLACK);
	//		}
	//		fillrectangle(i * PIXEL_SIZE, j * PIXEL_SIZE,
	//			(i + 1) * PIXEL_SIZE, (j + 1) * PIXEL_SIZE);
	//	}
	//}
	////����Ҽ����Ʒɻ����������˳�
	////ѭ�����������Ϣ
	//while (1)
	//{
	//	settextcolor(WHITE);
	//	settextstyle(20, 0, _T("����"));
	//	outtextxy(20, 20, _T("��ӭ�����ɻ�����"));
	//	ExMessage emg;
	//	if (peekmessage(&emg))
	//	{
	//		if (emg.message == WM_LBUTTONDOWN)
	//		{
	//			// ���������λ�ü������Ӧ����������
	//			int x = emg.x / PIXEL_SIZE;
	//			int y = emg.y / PIXEL_SIZE;
	//			if (x >= 0 && y >= 0 && x < ROW && y < COL)
	//			{
	//				// ��ת�����ص�ֵ
	//				pixels[x][y] = !pixels[x][y];
	//				// ����ֵ�ı仯�����þ��ε���ɫ
	//				if (pixels[x][y])
	//				{
	//					setfillcolor(WHITE);
	//				}
	//				else
	//				{
	//					setfillcolor(BLACK);
	//				}
	//				// ���»��ƾ���
	//				fillrectangle(x * PIXEL_SIZE, y * PIXEL_SIZE,
	//					(x + 1) * PIXEL_SIZE, (y + 1) * PIXEL_SIZE);
	//			}
	//		}//���esc�����˻�������
	//		else if (emg.message == WM_KEYDOWN)
	//		{
	//			if (emg.wParam == VK_ESCAPE) {
	//				closegraph();
	//				MainMenuLoop();
	//			}
	//		}
	//	}
	//}
	//closegraph();
}
void GameLoop::LevelSetUp()
{
	I_IdCounter = 1;
	SCORE = 0;
	GAMEEND = 1;
	std::vector<Coordinate> DEFAULTPLANE{ {0,0},{0,-1},{1,0},{0,1} };//Ĭ�Ϸɻ�
	Coordinate PLAYERPLANECORE(15, 35);	//Ĭ�Ϸɻ�����λ��

	Bullet::ENEMYMAP.clear();
	Bullet::PlayerPlaneBlock.clear();
	Bullet::AllEntities.clear();
	Bullet::keysToDelete.clear();

	//���ɵ���
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(-31, 0);
	int enemies[ENEMIESNUMBER];

	Plane* b1 = new Plane({ 4,4 });	//������

	//for (int i = 0; i < ENEMIESNUMBER; i++) {
	//	std::cout << "(" << dist(gen) << ", " << dist(gen) * dist(gen) * dist(gen) % 200 << ")" << std::endl;
	//	Coordinate co(dist(gen), dist(gen) * dist(gen) * dist(gen) % 200);
	//	Plane* b2 = new Plane(co);	//û������
	//}
	PlayerPlane mp;
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
			flag = -1;
			exit(0);
		}
	}
}

void GameLoop::BattleDefeatLoop()
{
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
			flag = -1;
			exit(0);
		}
	}
}

void GameLoop::BattleVictoryLoop()
{
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
			flag = -1;
			exit(0);
		}
	}
}


//
//void GameLoop::TestLoop() {
//	initgraph(MAPSIZE_X* BLOCKSIZE, MAPSIZE_Y*BLOCKSIZE);
//	BeginBatchDraw();//��ʼ������ͼ
//	Plane p1({ 31,20 });
//	Bullet b1;
//
//	while (!_kbhit())  // ���¼���������˳�ѭ��
//	{
//		setbkcolor(MAINCOLOR);
//		cleardevice();  // ��մ���
//		setfillcolor(OTHERCOLOR);
//
//		b1.AutoMove();
//		//b1.CollisionDetection();
//
//		p1.AutoMove();
//		//p1.CollisionDetection();
//
//
//		for (const auto& block : Bullet::AllEntities)
//		{
//			
//			int x = block->core.x;  // ��ȡ��� x ����
//			int y = block->core.y;  // ��ȡ��� y ����
//
//			// ���ƿ�
//			rectangle(x * BLOCKSIZE, y * BLOCKSIZE, x * BLOCKSIZE + BLOCKSIZE, y * BLOCKSIZE + BLOCKSIZE);
//		}
//		FlushBatchDraw();//ִ��δ��ɵĻ�������
//		Sleep(150);  // ��ͣ250���룬����ˢ���ٶ�
//	
//	}

//}

