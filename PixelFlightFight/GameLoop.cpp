#include "GameLoop.h"
#include "Scroll.h"
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
			MainMenuLoop(); //主界面
		case 2:
			SelectLevelLoop(); //关卡界面
		case 3:
			PlaneBattleLoop();//战斗界面
		case 4:
			PlaneBattleLoop();//介绍界面
		case 5:
			PlaneWorkshopLoop();//飞机工坊
		case -1:
			return;//结束
		}
	}
}
void GameLoop::MainMenuLoop()
{
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//创建窗口并显示控制台; // 初始化图形窗口大小为800*600像素
	setbkcolor(MAINCOLOR);  //显示背景颜色
	cleardevice();      //SECONDCOLOR
	setbkmode(MAINCOLOR);//处理字体颜色
	setfillcolor(WHITE);//设置填充色，	
	setlinecolor(WHITE); //设置当前线条的颜色//line(0, 780, 620, 780);
	settextstyle(60, 0, _T("微软雅黑"));
	settextcolor(SECONDCOLOR);
	outtextxy(455, 100, _T("飞机大战"));
	setfillcolor(SECONDCOLOR);//设置填充色

	setlinecolor(SECONDCOLOR);
	fillrectangle(353, 105, 450, 160); // 按钮背景
	setlinecolor(WHITE);

	settextcolor(WHITE);
	outtextxy(355, 100, _T("像素"));

	settextcolor(WHITE);
	setfillcolor(WHITE);//设置填充色
	// 绘制按钮
	//fillrectangle(350, 100, 300, 75); // 按钮背景
	Button* Begin;//绘制按钮
	Button* WorkShop;//绘制飞机工厂
	Button* Operating_instructions;//绘制操作说明
	Button* exit_game;//退出
	Operating_instructions = new Button(OnButtonClick, 350, 300, 300, 75, L"游戏介绍");
	Begin = new Button(OnButtonClick, 350, 400, 300, 75, L"开始游戏");
	WorkShop = new Button(OnButtonClick, 350, 500, 300, 75, L"飞机工厂");
	exit_game = new Button(OnButtonClick, 350, 600, 300, 75, L"退出游戏");
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
			printf("Begin\n");
			SelectLevelLoop();
		}
		if (WorkShop->state(msg)) // 飞机工厂
		{
			flag = 5;
			printf("End\n");
			PlaneWorkshopLoop();
		}
		if (Operating_instructions->state(msg)) // 介绍
		{
			flag = 4;
			printf("End\n");
			InstructionsLoop();
		}
		if (exit_game->state(msg)) {//退出游戏
			flag = -1;
			exit(0);
		}
	}
	//getch();
}

//TODO 
//介绍界面
void GameLoop::InstructionsLoop()
{
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//创建窗口并显示控制台; // 初始化图形窗口大小为800*600像素
	setbkcolor(MAINCOLOR);
	cleardevice();//显示背景颜色      
	setbkmode(TRANSPARENT);//处理字体背景
	setfillcolor(WHITE);//设置填充色，这里是浅青色
	setlinecolor(WHITE); //设置当前线条的颜色为黑色
	settextstyle(60, 0, _T("微软雅黑"));//
	settextcolor(SECONDCOLOR);
	LPCTSTR title = _T("游戏介绍");
	outtextxy(400, 100, title);
	settextcolor(WHITE);
	//游戏介绍:
	//TODO


	// 绘制按钮
	setfillcolor(WHITE);

	Button* re_main_menu;//返回菜单
	re_main_menu = new Button(OnButtonClick, 350, 600, 300, 75, L"返回菜单");
	re_main_menu->RenderToWindows();
	ExMessage msg;
	bool on = 1;
	while (on)
	{
		msg = getmessage();
		if (re_main_menu->state(msg)) // 返回菜单
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
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//创建窗口并显示控制台; // 初始化图形窗口大小为800*600像素
	setbkcolor(MAINCOLOR);
	cleardevice();//显示背景颜色      
	setbkmode(TRANSPARENT);//处理字体背景
	setfillcolor(WHITE);//设置填充色，这里是浅青色
	setlinecolor(WHITE); //设置当前线条的颜色为黑色
	settextstyle(60, 0, _T("微软雅黑"));//
	LPCTSTR title = _T("关卡选择");
	settextcolor(SECONDCOLOR);
	outtextxy(400, 100, title);
	settextcolor(WHITE);
	// 绘制按钮
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // 按钮背景
	Button* re_main_menu;//返回菜单
	Button* first_level;//第一关

	first_level = new Button(OnButtonClick, 350, 300, 300, 75, L"第一关");
	re_main_menu = new Button(OnButtonClick, 350, 600, 300, 75, L"返回菜单");
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
	//getch();
}


void GameLoop::PlaneBattleLoop()
{

	initgraph(MAPSIZE_X * BLOCKSIZE, MAPSIZE_Y * BLOCKSIZE, EW_SHOWCONSOLE);
	setbkcolor(MAINCOLOR);
	cleardevice();//显示背景颜色      
	setbkmode(TRANSPARENT);//处理字体背景
	setfillcolor(WHITE);//设置填充色，这里是浅青色
	setlinecolor(WHITE); //设置当前线条的颜色为黑色
	settextstyle(30, 0, _T("微软雅黑"));//


	ExMessage emg;//可以循环接受鼠标信息
	GAMEEND = false;
	//获取Scroll信息
	Scroll sc = Scroll::GetInstance();
	BeginBatchDraw();//开始批量绘图
	while (1)
	{
		settextcolor(SECONDCOLOR);
		outtextxy(20, 20, _T("分数"));
		std::wstring str = std::to_wstring(SCORE);
		LPCTSTR score = str.c_str();//分数
		outtextxy(70, 20, score);
		settextcolor(WHITE);

		//点击esc按键跳转到游戏主菜单
		if (_kbhit()) {
			bool esc = GetAsyncKeyState(VK_ESCAPE) & 0x8000;
			if (esc)
			{
				BattleMenuLoop();
			}
			else {
				bool up = GetAsyncKeyState(VK_UP) & 0x8000;
				bool down = GetAsyncKeyState(VK_DOWN) & 0x8000;
				bool left = GetAsyncKeyState(VK_LEFT) & 0x8000;
				bool right = GetAsyncKeyState(VK_RIGHT) & 0x8000;
				int u = 0;
				int d = 0;
				int l = 0;
				int r = 0;
				if (up) { u = -1; }
				if (down) { d = 1; }
				if (left) { l = -1; }
				if (right) { r = 1; }
				sc.playSpeed = { l + r,u + d };
			}
		}
		else {
			sc.playSpeed = { 0,0 };
		}
		sc.GameUpdate();

		//更新画布

		// 在这里处理 所有实体 对象
		for (Bullet* bullet : sc.allEntities) {
			//敌机和子弹
			if (bullet->entityType == _EntityEnemy || bullet->entityType == _EntityBullet) {
				// 计算坐标在窗口中的位置
				int x = bullet->core.x * BLOCKSIZE; // 每个 Block 边长为 10
				int y = bullet->core.y * BLOCKSIZE;

				// 绘制 Block
				setfillcolor(OTHERCOLOR); // 设置填充颜色
				solidrectangle(x, y, x + BLOCKSIZE, y + BLOCKSIZE); // 绘制矩形，边长为 BLOCKSIZE

			}
			//自机
			else if (bullet->entityType == _EntityPlayer) {
				//绘制核心
				int x = bullet->core.x * BLOCKSIZE;
				int y = bullet->core.y * BLOCKSIZE;
				setfillcolor(SECONDCOLOR);
				solidrectangle(x, y, x + BLOCKSIZE, y + BLOCKSIZE);
				//绘制副自机
				setfillcolor(OTHERCOLOR);
				for (const auto& pair : blockMap) {
					const Coordinate& coord = pair.first;
					const Block& block = pair.second;
					// 计算坐标在窗口中的位置
					int x = coord.x * BLOCKSIZE;
					int y = coord.y * BLOCKSIZE;
					// 绘制 Block

					solidrectangle(x, y, x + BLOCKSIZE, y + BLOCKSIZE);
				}

			}
		}
		FlushBatchDraw();//执行未完成的绘制任务

		if (GAMEEND)//核心被打爆
		{
			EndBatchDraw();// 结束批量绘制
			BattleDefeatLoop();
		}
		if (sc.enemiesNum <= 0)//敌机全部被消灭
		{
			EndBatchDraw();// 结束批量绘制
			BattleVictoryLoop();
		}

		Sleep(FRAMEINTERVAL);

	}
	//closegraph();
}

//REDO
void GameLoop::PlaneWorkshopLoop()
{
	////60 X 60界面 像素10 X 10

	//const int ROW = 60;
	//const int COL = 60;
	//const int PIXEL_SIZE = 10;
	////用数组保存飞机形状
	//int pixels[ROW][COL] = { 0 };
	//initgraph(ROW * PIXEL_SIZE, COL * PIXEL_SIZE);

	//// 渲染像素数组
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

	////点击右键绘制飞机，点击左键退出
	////循环接受鼠标信息
	//while (1)
	//{
	//	settextcolor(WHITE);
	//	settextstyle(20, 0, _T("黑体"));
	//	outtextxy(20, 20, _T("欢迎来到飞机工坊"));
	//	ExMessage emg;
	//	if (peekmessage(&emg))
	//	{
	//		if (emg.message == WM_LBUTTONDOWN)
	//		{
	//			// 根据鼠标点击位置计算出对应的像素坐标
	//			int x = emg.x / PIXEL_SIZE;
	//			int y = emg.y / PIXEL_SIZE;
	//			if (x >= 0 && y >= 0 && x < ROW && y < COL)
	//			{
	//				// 反转该像素的值
	//				pixels[x][y] = !pixels[x][y];

	//				// 根据值的变化，设置矩形的颜色
	//				if (pixels[x][y])
	//				{
	//					setfillcolor(WHITE);
	//				}
	//				else
	//				{
	//					setfillcolor(BLACK);
	//				}
	//				// 重新绘制矩形
	//				fillrectangle(x * PIXEL_SIZE, y * PIXEL_SIZE,
	//					(x + 1) * PIXEL_SIZE, (y + 1) * PIXEL_SIZE);
	//			}

	//		}//点击esc按键退回主界面
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
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//创建窗口 800*600像素
	setbkcolor(MAINCOLOR);
	cleardevice();//显示背景颜色      
	setbkmode(TRANSPARENT);//处理字体背景
	setfillcolor(WHITE);//设置填充色，这里是浅青色
	setlinecolor(WHITE); //设置当前线条的颜色为黑色
	settextstyle(60, 0, _T("微软雅黑"));
	LPCTSTR title = _T("选项");
	settextcolor(SECONDCOLOR);
	outtextxy(450, 100, title);
	settextcolor(WHITE);
	// 绘制按钮
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // 按钮背景
	Button* re_game;//绘制重新游玩按钮
	Button* re_main_menu;//绘制返回菜单
	Button* exit_game;//退出
	re_game = new Button(OnButtonClick, 350, 300, 300, 75, L"选择关卡");
	re_main_menu = new Button(OnButtonClick, 350, 400, 300, 75, L"返回菜单");
	exit_game = new Button(OnButtonClick, 350, 500, 300, 75, L"退出游戏");
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
			flag = -1;
			exit(0);
		}
	}
	//getch();
}

void GameLoop::BattleDefeatLoop()
{
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//创建窗口 800*600像素
	setbkcolor(MAINCOLOR);
	cleardevice();//显示背景颜色      
	setbkmode(TRANSPARENT);//处理字体背景
	setfillcolor(WHITE);//设置填充色，这里是浅青色
	setlinecolor(WHITE); //设置当前线条的颜色为黑色
	settextstyle(60, 0, _T("微软雅黑"));
	LPCTSTR title = _T("任务失败");
	settextcolor(SECONDCOLOR);
	outtextxy(400, 100, title);
	settextcolor(WHITE);
	// 绘制按钮
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // 按钮背景
	Button* re_game;//绘制重新游玩按钮
	Button* re_main_menu;//绘制返回菜单
	Button* exit_game;//退出
	re_game = new Button(OnButtonClick, 350, 300, 300, 75, L"选择关卡");
	re_main_menu = new Button(OnButtonClick, 350, 400, 300, 75, L"返回菜单");
	exit_game = new Button(OnButtonClick, 350, 500, 300, 75, L"退出游戏");
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
			flag = -1;
			exit(0);
		}
	}
}

void GameLoop::BattleVictoryLoop()
{
	initgraph(WINDOWS_X, WINDOWS_Y, EW_SHOWCONSOLE);//创建窗口 800*600像素
	setbkcolor(MAINCOLOR);
	cleardevice();//显示背景颜色      
	setbkmode(TRANSPARENT);//处理字体背景
	setfillcolor(WHITE);//设置填充色，这里是浅青色
	setlinecolor(WHITE); //设置当前线条的颜色为黑色
	settextstyle(60, 0, _T("微软雅黑"));
	LPCTSTR title = _T("任务完成");
	settextcolor(SECONDCOLOR);
	outtextxy(400, 100, title);
	settextcolor(WHITE);
	// 绘制按钮
	setfillcolor(WHITE);
	//fillrectangle(350, 100, 300, 75); // 按钮背景
	Button* re_game;//绘制重新游玩按钮
	Button* re_main_menu;//绘制返回菜单
	Button* exit_game;//退出
	re_game = new Button(OnButtonClick, 350, 300, 300, 75, L"选择关卡");
	re_main_menu = new Button(OnButtonClick, 350, 400, 300, 75, L"返回菜单");
	exit_game = new Button(OnButtonClick, 350, 500, 300, 75, L"退出游戏");
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
			flag = -1;
			exit(0);
		}
	}
}


