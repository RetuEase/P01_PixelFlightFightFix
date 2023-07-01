#include "GameLoop.h"
#include <iostream>
#include <filesystem>

#ifdef UNICODE
// 如果定义了 UNICODE 宏，将字符串字面量转换为宽字符
#define TSTRING std::wstring
#define TOSTRING std::to_wstring
#else
// 如果未定义 UNICODE 宏，将字符串字面量转换为多字节字符
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

	// 主循环
	while (true)
	{
		cleardevice();
		MainMenuLoop();//主界面
		//// 清空屏幕
		//cleardevice();

		//// 根据当前页面状态绘制页面
		//if (flag == 1)
		//{
		//	MainMenuLoop();//主界面
		//}
		//else if (flag == 2)
		//{
		//	SelectLevelLoop(); //关卡界面
		//}
		//else if (flag == 3)
		//{
		//	PlaneBattleLoop();//战斗界面

		//}
		//else if (flag == 4)
		//{
		//	PlaneBattleLoop();//介绍界面
		//}
		//else if (flag == 5)
		//{
		//	PlaneWorkshopLoop();//飞机工坊
		//}
		//// 等待一段时间，控制刷新速度
		//Sleep(100);
	}

}
void GameLoop::MainMenuLoop()		
{
	EndBatchDraw();
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//创建窗口并显示控制台; // 初始化图形窗口大小为800*600像素
	setbkcolor(BGCOLOR);  //显示背景颜色
	cleardevice();      //SECONDCOLOR
	setbkmode(BGCOLOR);//处理字体颜色
	setfillcolor(WHITE);//设置填充色，	
	setlinecolor(WHITE); //设置当前线条的颜色//line(0, 780, 620, 780);
	settextstyle(60, 50, _T("微软雅黑"));
	settextcolor(GOLDENCOLOR);

	IMAGE img;
	loadimage(&img, _T("title.png"));
	//setaspectratio(0.9, 0.9);
	putimage(0, 10, &img);
	setaspectratio(1, 1);
	setfillcolor(SECONDCOLOR);//设置填充色
	setlinecolor(SECONDCOLOR);
	//fillrectangle(353, 105, 450, 160); // 按钮背景
	setlinecolor(WHITE);

	//settextcolor(WHITE);
	//outtextxy(355, 100, _T("像素"));

	settextcolor(GOLDENCOLOR);
	setfillcolor(BGCOLOR);//设置填充色
	// 绘制按钮
	//fillrectangle(350, 100, 300, 75); // 按钮背景
	Button* Begin;//绘制按钮
	Button* WorkShop;//绘制飞机工厂
	Button* Operating_instructions;//绘制操作说明
	Button* exit_game;//退出
	Operating_instructions = new Button(OnButtonClick, 470, 380, 300, 75, L"游戏介绍");
	Begin = new Button(OnButtonClick, 470, 480, 300, 75, L"开始游戏");
	WorkShop = new Button(OnButtonClick, 470, 580, 300, 75, L"飞机工厂");
	exit_game = new Button(OnButtonClick, 470, 680, 300, 75, L"退出游戏");
	Begin->RenderToWindows();
	WorkShop->RenderToWindows();
	Operating_instructions->RenderToWindows();
	exit_game->RenderToWindows();
	ExMessage msg;
	bool on = 1;
	while (on)
	{
		msg = getmessage();
		if (Begin->state(msg)) // 开始游戏 进入选关卡页面
		{
			flag = 2;
			SelectLevelLoop();
		}
		if (WorkShop->state(msg)) // 飞机工厂
		{
			flag = 5;
			PlaneWorkshopLoop();
		}
		if (Operating_instructions->state(msg)) // 介绍
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
		if (exit_game->state(msg)) {//退出游戏
			flag = 0;
			exit(0);
		}
	}
}
//getch();

//TODO 
//介绍界面
void GameLoop::InstructionsLoop()
{
	IMAGE images[42];
	loadimage(&images[0], _T("intro/title00.gif"));	loadimage(&images[1], _T("intro/title01.gif"));	loadimage(&images[2], _T("intro/title02.gif"));	loadimage(&images[3], _T("intro/title03.gif"));	loadimage(&images[4], _T("intro/title04.gif"));	loadimage(&images[5], _T("intro/title05.gif"));	loadimage(&images[6], _T("intro/title06.gif"));	loadimage(&images[7], _T("intro/title07.gif"));	loadimage(&images[8], _T("intro/title08.gif"));	loadimage(&images[9], _T("intro/title09.gif"));	loadimage(&images[10], _T("intro/title10.gif"));	loadimage(&images[11], _T("intro/title11.gif"));	loadimage(&images[12], _T("intro/title12.gif"));	loadimage(&images[13], _T("intro/title13.gif"));	loadimage(&images[14], _T("intro/title14.gif"));	loadimage(&images[15], _T("intro/title15.gif"));	loadimage(&images[16], _T("intro/title16.gif"));	loadimage(&images[17], _T("intro/title17.gif"));	loadimage(&images[18], _T("intro/title18.gif"));	loadimage(&images[19], _T("intro/title19.gif"));	loadimage(&images[20], _T("intro/title20.gif"));	loadimage(&images[21], _T("intro/title21.gif"));	loadimage(&images[22], _T("intro/title22.gif"));	loadimage(&images[23], _T("intro/title23.gif"));	loadimage(&images[24], _T("intro/title24.gif"));	loadimage(&images[25], _T("intro/title25.gif"));	loadimage(&images[26], _T("intro/title26.gif"));	loadimage(&images[27], _T("intro/title27.gif"));	loadimage(&images[28], _T("intro/title28.gif"));	loadimage(&images[29], _T("intro/title29.gif"));	loadimage(&images[30], _T("intro/title30.gif"));	loadimage(&images[31], _T("intro/title31.gif"));	loadimage(&images[32], _T("intro/title32.gif"));	loadimage(&images[33], _T("intro/title33.gif"));	loadimage(&images[34], _T("intro/title34.gif"));	loadimage(&images[35], _T("intro/title35.gif"));	loadimage(&images[36], _T("intro/title36.gif"));	loadimage(&images[37], _T("intro/title37.gif"));	loadimage(&images[38], _T("intro/title38.gif"));	loadimage(&images[39], _T("intro/title39.gif"));	loadimage(&images[40], _T("intro/title40.gif"));	loadimage(&images[41], _T("intro/title41.gif"));	int imgNumber = 42;	int x = 100, y = 100;// 定义图片的初始位置	

	int imageIndex = 0;// 图片的索引

	// 开始绘制动画
	BeginBatchDraw();//开始批量绘图

	for(; imageIndex <imgNumber; imageIndex++)
	{
		// 清空绘图窗口
		//cleardevice();
		// 绘制当前图片
		putimage(x, y, &images[imageIndex]);
		Sleep(400);
		// 前进到下一张图片		
		FlushBatchDraw();
	}

	BeginBatchDraw();
}



void GameLoop::SelectLevelLoop()
{
	Sleep(500);

	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//创建窗口并显示控制台; // 初始化图形窗口大小为800*600像素
	setbkcolor(BGCOLOR);
	cleardevice();//显示背景颜色      
	setbkmode(TRANSPARENT);//处理字体背景
	setfillcolor(WHITE);//设置填充色，这里是浅青色
	setlinecolor(WHITE); //设置当前线条的颜色为黑色
	settextstyle(60, 0, _T("微软雅黑"));//
	LPCTSTR title = _T("关卡选择");
	settextcolor(SECONDCOLOR);
	outtextxy(525, 100, title);
	settextcolor(GOLDENCOLOR);
	// 绘制按钮
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // 按钮背景
	Button* re_main_menu;//返回菜单
	Button* first_level;//第一关

	first_level = new Button(OnButtonClick, 470, 380, 300, 75, L"第一关");
	re_main_menu = new Button(OnButtonClick, 470, 680, 300, 75, L"返回菜单");
	re_main_menu->RenderToWindows();
	first_level->RenderToWindows();
	ExMessage msg;
	bool on = 1;
	while (on)
	{
		msg = getmessage();
		if (first_level->state(msg)) // 第一关
		{
			flag = 3;
			printf("Game Start!\n");
			PlaneBattleLoop();
		}
		if (re_main_menu->state(msg)) // 返回菜单
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
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//创建窗口

	setbkcolor(BGCOLOR);
	cleardevice();//显示背景颜色      
	setbkmode(TRANSPARENT);//处理字体背景
	setfillcolor(WHITE);//设置填充色
	setlinecolor(WHITE); //设置当前线条的颜色
	GAMEEND = false;
	//获取Scroll信息
	Scroll sc = Scroll::GetInstance();
	int space = 1;
	//绘制网格
	while (1)
	{
		BeginBatchDraw();//开始批量绘图
		setbkcolor(BGCOLOR);
		cleardevice();  // 清空窗口
		setfillcolor(OTHERCOLOR);
		settextcolor(GOLDENCOLOR);
		//outtextxy(20, 20, _T("分数"));
		settextstyle(30, 15, _T("微软雅黑"));
		std::wstring str = std::to_wstring(SCORE);
		LPCTSTR score = str.c_str();//分数
		outtextxy(615, 20, score);
		settextcolor(GOLDENCOLOR);
		setfillcolor(OTHERCOLOR);
		rectangle(BLANK_L - 90, BLANK_U, BLANK_L - 30, BLANK_U + 30);
		settextstyle(30, 0, _T("微软雅黑"));
		outtextxy(BLANK_L - 80, BLANK_U, _T("ESC"));
		setlinecolor(BACKCOLOR); //设置当前线条的颜色
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
		//		line(x, BLANK_U, x, BLANK_D);  // 绘制垂直线
		//		line(BLANK_L, y, BLANK_R, y);  // 绘制水平线
		//	}
		//}
		bool fire = false;
		//点击esc按键跳转到游戏主菜单
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
				//cout << "暂停!" << endl;
				EndBatchDraw();
				BattleMenuLoop();//切换至菜单		
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
			settextstyle(30, 0, _T("微软雅黑"));
			outtextxy(600, 320, _T("SPACE"));
		}

		//发射子弹
		if (fire && sc.fireCD >= 15) {
			if (space == 1)
			{
				space = 0;
				cleardevice();  // 清空窗口
			}

			Bullet* b = new Bullet(1);
			//cout << b->blockID;
			sc.fireCD = 0;
			fire = false;

		}
		sc.GameUpdate();

		//处理所有实体
		//cout << "size: " << Bullet::AllEntities.size() << endl;
		for (const auto& pair : Bullet::AllEntities) {
			std::shared_ptr<Bullet> bulletptr = pair.second;

			//敌机	
			if (bulletptr->entityType == _EntityEnemy) {
				if (bulletptr->core.y <= MAPSIZE_Y - 1 && bulletptr->core.y >= 0 && bulletptr->core.x <= MAPSIZE_X - 1 && bulletptr->core.x >= 0) {
					//line(BLANK_L, BLANK_U, BLANK_R, BLANK_D);  // 绘制垂直线
					// 计算坐标在窗口中的位置
					int x = BLANK_L + bulletptr->core.x * BLOCKSIZE;
					int y = BLANK_U + bulletptr->core.y * BLOCKSIZE;
					// 绘制 Block
					setlinecolor(WHITE);
					setfillcolor(CORECOLOR);
					solidrectangle(x, y, x + BLOCKSIZE, y + BLOCKSIZE); // 绘制矩形，边长为 BLOCKSIZE
				}
			}
			//子弹
			else if (bulletptr->entityType == _EntityBullet) {
				//line(BLANK_L, BLANK_U, BLANK_R, BLANK_D);  // 绘制垂直线
				// 计算坐标在窗口中的位置
				if (bulletptr->core.y <= MAPSIZE_Y - 1 && bulletptr->core.y >= 0 && bulletptr->core.x <= MAPSIZE_X - 1 && bulletptr->core.x >= 0) {
					//cout << "!!!" << endl;
					int x = BLANK_L + bulletptr->core.x * BLOCKSIZE;
					int y = BLANK_U + bulletptr->core.y * BLOCKSIZE;

					// 绘制 Block
					setlinecolor(WHITE);
					setfillcolor(BULLETCOLOR);
					solidrectangle(x, y, x + BLOCKSIZE, y + BLOCKSIZE); // 绘制矩形，边长为 BLOCKSIZE
				}
			}
			//自机
			else if (bulletptr->entityType == _EntityPlayer) {
				//绘制核心
				int corex = BLANK_L + bulletptr->core.x * BLOCKSIZE;
				int corey = BLANK_U + bulletptr->core.y * BLOCKSIZE;
				setlinecolor(SECONDCOLOR);
				setfillcolor(GOLDENCOLOR);
				solidrectangle(corex, corey, corex + BLOCKSIZE, corey + BLOCKSIZE);
				//绘制副自机
				setfillcolor(BULLETCOLOR);
				for (const auto& pair : Bullet::PlayerPlaneBlock) {
					const Coordinate& coord = pair.first;
					if (bulletptr->core.y + coord.y <= MAPSIZE_Y - 1 && bulletptr->core.y + coord.y >= 0 && bulletptr->core.x + coord.x <= MAPSIZE_X - 1 && bulletptr->core.x + coord.x >= 0) {
						// 计算坐标在窗口中的位置
						int x = BLANK_L + bulletptr->core.x * BLOCKSIZE + coord.x * BLOCKSIZE;
						int y = BLANK_U + bulletptr->core.y * BLOCKSIZE + coord.y * BLOCKSIZE;
						// 绘制 Block
						setlinecolor(WHITE);
						setfillcolor(BULLETCOLOR);
						solidrectangle(x, y, x + BLOCKSIZE, y + BLOCKSIZE);
					}
				}

			}
		}
		EndBatchDraw();//执行未完成的绘制任务

		if (GAMEEND)//核心被打爆
		{
			EndBatchDraw();// 结束批量绘制
			BattleDefeatLoop();
		}
		if (Bullet::enemiesNum <= 0)//敌机全部被消灭
		{
			EndBatchDraw();// 结束批量绘制
			BattleVictoryLoop();
		}

		Sleep(FRAMEINTERVAL);

	}
	//closegraph();
}

void GameLoop::PlaneWorkshopLoop()
{
	Sleep(500);

	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//创建窗口并显示控制台; // 初始化图形窗口大小为800*600像素
	setbkcolor(BGCOLOR);
	PlaneCanvas pc;
	while (1) {
		cleardevice();
		setbkmode(TRANSPARENT);//处理字体背景
		setfillcolor(WHITE);//设置填充色，这里是浅青色
		setlinecolor(WHITE); //设置当前线条的颜色为黑色
		settextstyle(60, 0, _T("微软雅黑"));//
		settextcolor(GOLDENCOLOR);
		LPCTSTR title = _T("飞机工坊");
		outtextxy(525, 80, title);
		settextstyle(40, 0, _T("微软雅黑"));
		settextcolor(GOLDENCOLOR);
		LPCTSTR intro1 = _T("请编辑自己的飞机");
		outtextxy(500, 140, intro1);
		LPCTSTR intro2 = _T("左键添加机身 中键选择核心 右键删除机身");
		outtextxy(350, 180, intro2);
		settextstyle(30, 0, _T("微软雅黑"));
		LPCTSTR intro4 = _T("注意: 不与核心相连的机身会断裂");
		outtextxy(460, 230, intro4);
		LPCTSTR intro3 = _T("只有添加了核心才能应用");
		outtextxy(950, 620, intro3);

		settextcolor(GOLDENCOLOR);
		BeginBatchDraw();//开始批量绘图

		//绘制网格
		setlinecolor(BACKCOLOR); //设置当前线条的颜色
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
				line(x, WORKSHOP_U, x, WORKSHOP_D);  // 绘制垂直线
				line(WORKSHOP_L, y, WORKSHOP_R, y);  // 绘制水平线
			}
		}
		// 循环接受鼠标点击事件
		setfillcolor(WHITE);	// 绘制按钮
		Button* re_main_menu;//返回
		re_main_menu = new Button(OnButtonClick, 920, 680, 300, 75, L"应用并返回");
		re_main_menu->RenderToWindows();
		while (true)
		{
			FlushMouseMsgBuffer();
			// 检测鼠标点击事件
			if (MouseHit())
			{

				// 获取鼠标点击事件
				MOUSEMSG msg = GetMouseMsg();
				//cout << "click" << left << " " << " " << msg.x << " " << msg.y << endl;// 输出点击的格子坐标

				if (msg.x >= 920 && msg.x <= 1220 && msg.y >= 680 && msg.y <= 755) // 返回
				{
					if (msg.mkLButton)
					{
						pc.paintPlane.DesignPlane();
						EndBatchDraw();
						flag = 1;
						MainMenuLoop();
					}
				}
				// 将鼠标点击的屏幕坐标转换为窗口内坐标
				int x = (msg.x - WORKSHOP_L) / WORKSHOP_SIZE;
				int y = (msg.y - WORKSHOP_U) / WORKSHOP_SIZE;

				// 判断点击的格子是否在窗口内
				if (x >= 0 && x < WORKSHOP_X && y >= 0 && y < WORKSHOP_Y)
				{
					int button = 0;	//左键1 右键2 中键3
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
					//cout << "click " << x << ", " << y << endl;// 输出点击的格子坐标
					break;
				}
			}
			//Sleep(WORKSHOPFLASH);
		}
		//绘制机身
		for (const Coordinate& coordinate : pc.paintPlane.spriteMap) {
			setfillcolor(BULLETCOLOR);
			int x = WORKSHOP_SIZE * coordinate.x + WORKSHOP_L;
			int y = WORKSHOP_SIZE * coordinate.y + WORKSHOP_U;
			solidrectangle(x + 1, y + 1, x + WORKSHOP_SIZE - 1, y + WORKSHOP_SIZE - 1); // 绘制机身，边长为 WORKSHOP_SIZE
		}
		//绘制核心
		for (const Coordinate& ccoordinate : pc.paintPlane.core) {
			setfillcolor(CORECOLOR);
			int x = WORKSHOP_SIZE * ccoordinate.x + WORKSHOP_L;
			int y = WORKSHOP_SIZE * ccoordinate.y + WORKSHOP_U;
			solidrectangle(x + 1, y + 1, x + WORKSHOP_SIZE - 1, y + WORKSHOP_SIZE - 1); // 绘制核心，边长为 WORKSHOP_SIZE

		}

		setlinestyle(PS_SOLID, 1);
		setfillcolor(OTHERCOLOR);
		settextcolor(GOLDENCOLOR);
		settextstyle(40, 0, _T("微软雅黑"));
		outtextxy(50, 520, _T("剩余机身数量: "));
		std::wstring planeNumStr = std::to_wstring(pc.paintPlane.planCountMax - pc.paintPlane.spriteMap.size());
		LPCTSTR planeNum = planeNumStr.c_str();//机身数量
		outtextxy(250, 520, planeNum);
		outtextxy(50, 620, _T("剩余核心数量:"));
		std::wstring coreNumStr = std::to_wstring(pc.paintPlane.coreCountMax - pc.paintPlane.core.size());
		LPCTSTR coreNum = coreNumStr.c_str();//核心数量
		outtextxy(250, 620, coreNum);

		FlushBatchDraw();//执行未完成的绘制任务	

		//用数组保存飞机形状
		//int pixels[WORKSHOP_X][WORKSHOP_Y] = { 0 };
		//for (const auto& pair : Bullet::AllEntities) {
		//	std::shared_ptr<Bullet> bulletptr = pair.second;
		//	//敌机	
		//	if (bulletptr->entityType == _EntityEnemy) {
		//		if (bulletptr->core.y <= MAPSIZE_Y - 1 && bulletptr->core.y >= 0 && bulletptr->core.x <= MAPSIZE_X - 1 && bulletptr->core.x >= 0) {
		//			//line(BLANK_L, BLANK_U, BLANK_R, BLANK_D);  // 绘制垂直线
		//			// 计算坐标在窗口中的位置
		//			int x = BLANK_L + bulletptr->core.x * BLOCKSIZE;
		//			int y = BLANK_U + bulletptr->core.y * BLOCKSIZE;
		//			// 绘制 Block
		//			setlinecolor(WHITE);
		//			setfillcolor(CORECOLOR);
		//			solidrectangle(x, y, x + BLOCKSIZE, y + BLOCKSIZE); // 绘制矩形，边长为 BLOCKSIZE
		//		}
		//	}
		//
		////渲染像素数组
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
		//			solidrectangle(x, y, x + WORKSHOP_SIZE, y + WORKSHOP_SIZE); // 绘制矩形，边长为 WORKSHOP_SIZE
		//		}
		//	}
		//}


	}

	//ExMessage emg;
	//	if (peekmessage(&emg))
	//	{
	//		if (emg.message == WM_LBUTTONDOWN)
	//		{
	//			Coordinate cor(emg.x, emg.y); //鼠标的位置
	//			pc.Click(cor, true);
	//		}//点击esc按键退回主界面
	//		else if (emg.message == WM_RBUTTONDOWN)
	//		{
	//			Coordinate cor(emg.x, emg.y); //鼠标的位置
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

	Bullet::PLAYERPLANECORE = Coordinate( 15, 35);	//默认飞机核心位置
	Bullet::ENEMYMAP.clear();
	Bullet::PlayerPlaneBlock.clear();
	Bullet::AllEntities.clear();
	Bullet::keysToDelete.clear();

	//生成敌人
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

	//初始化玩家飞机
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
//	BeginBatchDraw();//暂停绘画
//	//设置顶点坐标
//	btn.x1 = x1;
//	btn.x2 = x2;
//	btn.y1 = y1;
//	btn.y2 = y2;
//	//设置边框颜色
//	if (lcolor == "red" || lcolor == "RED")setlinecolor(RED);//设置边框颜色为红色
//	else if (lcolor == "green" || lcolor == "GREEN")setlinecolor(GREEN);//设置边框颜色为红色
//	else if (lcolor == "blue" || lcolor == "BLUE")setlinecolor(BLUE);//设置边框颜色为红色
//	else if (lcolor == "yellow" || lcolor == "YELLOW")setlinecolor(YELLOW);//设置边框颜色为黄色
//	else if (lcolor == "black" || lcolor == "BLACK")setlinecolor(BLACK);//设置边框颜色为黑色
//	else if (lcolor == "white" || lcolor == "WHITE")setlinecolor(WHITE);//设置边框颜色为白色
//	else {
//		int x;
//		x = MessageBox(GetForegroundWindow(), TEXT("请检查按钮边框颜色是否设置正确，目前字体颜色包含：red、green、blue、yellow、black、white。"), TEXT("按钮边框颜色设置错误"), 1);
//		cout << x;
//	}
//	//绘制按钮边框
//	rectangle(btn.x1, btn.y1, btn.x2, btn.y2);
//	//设置填充颜色
//	if (fcolor == "red" || fcolor == "RED")setfillcolor(RED);//设置填充颜色为红色
//	else if (fcolor == "green" || fcolor == "GREEN")setfillcolor(GREEN);//设置填充颜色为红色
//	else if (fcolor == "blue" || fcolor == "BLUE")setfillcolor(BLUE);//设置填充颜色为红色
//	else if (fcolor == "yellow" || fcolor == "YELLOW")setfillcolor(YELLOW);//设置填充颜色为黄色
//	else if (fcolor == "black" || fcolor == "BLACK")setfillcolor(BLACK);//设置填充颜色为黑色
//	else if (fcolor == "white" || fcolor == "WHITE")setfillcolor(WHITE);//设置填充颜色为白色
//	else {
//		int x;
//		x = MessageBox(GetForegroundWindow(), TEXT("请检查按钮填充颜色是否设置正确，目前填充颜色包含：red、green、blue、yellow、black、white。"), TEXT("按钮填充颜色设置错误"), 1);
//		cout << x;
//	}
//	fillrectangle(btn.x1, btn.y1, btn.x2, btn.y2);
//	//设置按钮文字
//	setbkmode(TRANSPARENT);//设置透明字体
//
//	if (tcolor == "red" || tcolor == "RED")settextcolor(RED);//设置字体颜色为红色
//	else if (tcolor == "green" || tcolor == "GREEN")settextcolor(GREEN);//设置字体颜色为红色
//	else if (tcolor == "blue" || tcolor == "BLUE")settextcolor(BLUE);//设置字体颜色为红色
//	else if (tcolor == "yellow" || tcolor == "YELLOW")settextcolor(YELLOW);//设置字体颜色为黄色
//	else if (tcolor == "black" || tcolor == "BLACK")settextcolor(BLACK);//设置字体颜色为黑色
//	else if (tcolor == "white" || tcolor == "WHITE")settextcolor(WHITE);//设置字体颜色为白色
//	else {
//		int x;
//		x = MessageBox(GetForegroundWindow(), TEXT("请检查字体颜色是否设置正确，目前字体颜色包含：red、green、blue、yellow、black、white。"), TEXT("字体颜色设置错误"), 1);
//		cout << x;
//	}
//	//settextcolor(BLUE);//设置字体颜色
//	settextstyle(tlength, twidth, _T("宋体"));//设置字体格式
//	outtextxy(x1 + tsetoff, y1 + tsetoff, text);//设置显示位置
//
//
//	//设置按钮交互响应
//	//MOUSEMSG m;// 定义鼠标消息
//	int change = 10;
//	ExMessage m;//定义一个消息变量
//	m = getmessage(EM_MOUSE);//获取鼠标消息
//	switch (m.message)
//	{
//	case WM_MOUSEMOVE:
//		// 鼠标移动按钮时按钮变大
//		if (m.x >= btn.x1 && m.x <= btn.x2)
//		{
//			if (m.y >= btn.y1 && m.y <= btn.y2)
//			{
//				rectangle(btn.x1 - change, btn.y1 - change, btn.x2 + change, btn.y2 + change);
//			}
//			else
//			{
//				FlushBatchDraw();//批量绘制
//				//cleardevice();
//			}
//		}
//		else
//		{
//			FlushBatchDraw();//批量绘制
//			//cleardevice();
//		}
//		break;
//
//	case WM_LBUTTONDOWN:
//		// 鼠标点击按钮会变绿色
//		if (m.x >= btn.x1 && m.x <= btn.x2)
//		{
//			if (m.y >= btn.y1 && m.y <= btn.y2)
//			{
//				setfillcolor(GREEN);
//				fillrectangle(btn.x1, btn.y1, btn.x2, btn.y2);
//				FlushBatchDraw();//批量绘制
//			}
//			else
//			{
//				FlushBatchDraw();//批量绘制
//				//cleardevice();
//			}
//		}
//		break;
//	}
//
//	//恢复画线和填充颜色
//	setlinecolor(WHITE);
//	setfillcolor(WHITE);
//}

void GameLoop::BattleMenuLoop()
{
	Sleep(500);

	//EndBatchDraw();
	//initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//创建窗口 800*600像素
	setbkcolor(BGCOLOR);
	cleardevice();
	setbkmode(TRANSPARENT);//处理字体背景
	setfillcolor(WHITE);//设置填充色，这里是浅青色
	setlinecolor(WHITE); //设置当前线条的颜色为黑色
	settextstyle(60, 0, _T("微软雅黑"));
	LPCTSTR title = _T("暂停");
	settextcolor(GOLDENCOLOR);
	outtextxy(570, 100, title);
	// 绘制按钮
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // 按钮背景
	Button* re_game;//绘制重新游玩按钮
	Button* re_main_menu;//绘制返回菜单
	Button* exit_game;//退出
	re_game = new Button(OnButtonClick, 470, 480, 300, 75, L"返回关卡");
	re_main_menu = new Button(OnButtonClick, 470, 580, 300, 75, L"返回菜单");
	exit_game = new Button(OnButtonClick, 470, 680, 300, 75, L"退出游戏");
	re_game->RenderToWindows();
	re_main_menu->RenderToWindows();
	exit_game->RenderToWindows();
	ExMessage msg;
	bool on = 1;
	while (on)
	{
		msg = getmessage();
		if (re_game->state(msg)) // 返回关卡
		{
			flag = 2;
			printf("Restart\n");
			//BeginBatchDraw();
			//closegraph();
			return;

		}
		if (re_main_menu->state(msg)) // 返回菜单
		{
			flag = 1;
			printf("Return\n");
			MainMenuLoop();
		}

		if (exit_game->state(msg)) {//退出游戏
			flag = 0;
			exit(0);
		}
	}
}

void GameLoop::BattleDefeatLoop()
{
	Sleep(500);

	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//创建窗口 800*600像素
	setbkcolor(BGCOLOR);
	cleardevice();//显示背景颜色      
	setbkmode(TRANSPARENT);//处理字体背景
	setfillcolor(WHITE);//设置填充色，这里是浅青色
	setlinecolor(WHITE); //设置当前线条的颜色为黑色
	settextstyle(60, 0, _T("微软雅黑"));
	LPCTSTR title = _T("任务失败");
	settextcolor(GOLDENCOLOR);
	outtextxy(525, 100, title);

	settextstyle(40, 0, _T("微软雅黑"));
	settextcolor(OTHERCOLOR);
	outtextxy(580, 180, _T("分数: "));
	settextcolor(GOLDENCOLOR);
	std::wstring str = std::to_wstring(SCORE);
	LPCTSTR score = str.c_str();//分数
	outtextxy(650, 180, score);


	// 绘制按钮
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // 按钮背景
	Button* re_game;//绘制重新游玩按钮
	Button* re_main_menu;//绘制返回菜单
	Button* exit_game;//退出
	re_game = new Button(OnButtonClick, 470, 480, 300, 75, L"选择关卡");
	re_main_menu = new Button(OnButtonClick, 470, 580, 300, 75, L"返回菜单");
	exit_game = new Button(OnButtonClick, 470, 680, 300, 75, L"退出游戏");
	re_game->RenderToWindows();
	re_main_menu->RenderToWindows();
	exit_game->RenderToWindows();
	ExMessage msg;
	bool on = 1;
	while (on)
	{
		msg = getmessage();
		if (re_game->state(msg)) // 选择关卡
		{
			flag = 2;
			printf("Restart\n");
			SelectLevelLoop();
		}
		if (re_main_menu->state(msg)) // 返回菜单
		{
			flag = 1;
			printf("Return\n");
			MainMenuLoop();
		}

		if (exit_game->state(msg)) {//退出游戏
			flag = 0;
			exit(0);
		}
	}
}

void GameLoop::BattleVictoryLoop()
{
	Sleep(500);

	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//创建窗口 800*600像素
	setbkcolor(BGCOLOR);
	cleardevice();//显示背景颜色      
	setbkmode(TRANSPARENT);//处理字体背景
	setfillcolor(WHITE);//设置填充色，这里是浅青色
	setlinecolor(WHITE); //设置当前线条的颜色为黑色
	settextstyle(60, 0, _T("微软雅黑"));
	LPCTSTR title = _T("任务完成");
	settextcolor(GOLDENCOLOR);
	outtextxy(525, 100, title);
	settextstyle(40, 0, _T("微软雅黑"));
	settextcolor(OTHERCOLOR);
	outtextxy(580, 180, _T("分数: "));
	settextcolor(GOLDENCOLOR);
	std::wstring str = std::to_wstring(SCORE);
	LPCTSTR score = str.c_str();//分数
	outtextxy(650, 180, score);

	// 绘制按钮
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // 按钮背景
	Button* re_game;//绘制重新游玩按钮
	Button* re_main_menu;//绘制返回菜单
	Button* exit_game;//退出
	re_game = new Button(OnButtonClick, 470, 480, 300, 75, L"选择关卡");
	re_main_menu = new Button(OnButtonClick, 470, 580, 300, 75, L"返回菜单");
	exit_game = new Button(OnButtonClick, 470, 680, 300, 75, L"退出游戏");
	re_game->RenderToWindows();
	re_main_menu->RenderToWindows();
	exit_game->RenderToWindows();
	ExMessage msg;
	bool on = 1;
	while (on)
	{
		msg = getmessage();
		if (re_game->state(msg)) // 选择关卡
		{
			flag = 2;
			printf("Restart\n");
			SelectLevelLoop();
		}
		if (re_main_menu->state(msg)) // 返回菜单
		{
			flag = 1;
			printf("Return\n");
			MainMenuLoop();
		}

		if (exit_game->state(msg)) {//退出游戏
			flag = 0;
			exit(0);
		}
	}
}
