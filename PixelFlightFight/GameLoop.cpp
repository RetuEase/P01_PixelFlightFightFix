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
			MainMenuLoop(); //主界面
		case 2:
			SelectLevelLoop(); //关卡界面
		case 3:
			PlaneBattleLoop();//战斗界面
		case 4:
			PlaneBattleLoop();//说明界面
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
	setbkcolor(WHITE);
	cleardevice();//显示背景颜色      
	setbkmode(TRANSPARENT);//处理字体背景
	setfillcolor(CYAN);//设置填充色，这里是浅青色
	setlinecolor(BLACK); //设置当前线条的颜色为黑色
	settextstyle(45, 0, _T("微软雅黑"));//
	LPCTSTR title = _T("像素飞机大战");
	settextcolor(BLUE);
	outtextxy(400, 100, title);
	// 绘制开始游戏按钮
	setfillcolor(BLUE);
	//fillrectangle(350, 100, 300, 75); // 按钮背景
	Button* Begin;//绘制开始游戏按钮
	Button* WorkShop;//绘制飞机工厂
	Button* Operating_instructions;//绘制操作说明
	Button* exit_game;//退出
	Begin = new Button(OnButtonClick, 350, 300, 300, 75, L"开始游戏");
	WorkShop = new Button(OnButtonClick, 350, 400, 300, 75, L"飞机工厂");
	Operating_instructions = new Button(OnButtonClick, 350, 500, 300, 75, L"操作说明");
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
		if (Operating_instructions->state(msg)) // 操作说明
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
	_getch();
}

//TODO 
//介绍界面
void GameLoop::InstructionsLoop()
{

}

void GameLoop::SelectLevelLoop()
{
	initgraph(800, 600);
	setbkcolor(WHITE);
	cleardevice();

	setfillcolor(CYAN);
	fillrectangle(300, 250, 500, 75);

	settextcolor(BLUE);
	settextstyle(40, 0, _T("微软雅黑"));
	setbkmode(TRANSPARENT);
	char arr[] = "第一关";
	outtextxy(354, 280, _T("第一关"));

	//用户点击按钮跳转到战斗界面 PlaneBattleLoop（）
	//点击ESC按键跳转回主界面 MainMenuLoop（）
	ExMessage emg;

	while (1)
	{
		if (peekmessage(&emg)) {
			if (emg.message == WM_LBUTTONDOWN) {
				if ((emg.x >= 300) && (emg.x <= 500) && (emg.y >= 250) && (emg.y <= 350)) {
					PlaneBattleLoop();
				}
			}
			else if (emg.message == WM_KEYDOWN) {
				if (emg.wParam == VK_ESCAPE) {
					closegraph();
					MainMenuLoop();
				}
			}
		}

	}
	closegraph();

}


void GameLoop::PlaneBattleLoop()
{
	initgraph(800, 600);

	settextcolor(RED);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(20, 20, _T("欢迎来到战斗界面"));
	ExMessage emg;//可以循环接受鼠标信息

	//获取Scroll信息
	//Scroll sc = Scroll::GetInstance();
	//while (1)
	//{//点击esc按键跳转到游戏主菜单
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
	//    else if (sc.baseLife <= 0)//基地血量耗尽
	//    {
	//        BattleDefeatLoop();
	//    }
	//    else if (sc.insIdCounter == 0)//敌机全部被消灭
	//    {
	//        BattleVictoryLoop();
	//    }
	//}
	closegraph();
}

void GameLoop::PlaneWorkshopLoop()
{
	//60 X 60界面 像素10 X 10

	const int ROW = 60;
	const int COL = 60;
	const int PIXEL_SIZE = 10;
	//用数组保存飞机形状
	int pixels[ROW][COL] = { 0 };
	initgraph(ROW * PIXEL_SIZE, COL * PIXEL_SIZE);

	// 渲染像素数组
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

	//点击右键绘制飞机，点击左键退出
	//循环接受鼠标信息
	while (1)
	{
		settextcolor(WHITE);
		settextstyle(20, 0, _T("黑体"));
		outtextxy(20, 20, _T("欢迎来到飞机工坊"));
		ExMessage emg;
		if (peekmessage(&emg))
		{
			if (emg.message == WM_LBUTTONDOWN)
			{
				// 根据鼠标点击位置计算出对应的像素坐标
				int x = emg.x / PIXEL_SIZE;
				int y = emg.y / PIXEL_SIZE;
				if (x >= 0 && y >= 0 && x < ROW && y < COL)
				{
					// 反转该像素的值
					pixels[x][y] = !pixels[x][y];

					// 根据值的变化，设置矩形的颜色
					if (pixels[x][y])
					{
						setfillcolor(WHITE);
					}
					else
					{
						setfillcolor(BLACK);
					}
					// 重新绘制矩形
					fillrectangle(x * PIXEL_SIZE, y * PIXEL_SIZE,
						(x + 1) * PIXEL_SIZE, (y + 1) * PIXEL_SIZE);
				}

			}//点击esc按键退回主界面
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
	while (1)
	{
		initgraph(640, 480);//初始化界面
		//setbkcolor(BLUE);
		cleardevice();
		settextcolor(GREEN);
		settextstyle(100, 0, L"微软雅黑");
		outtextxy(100, 70, L"暂停");
		setfillcolor(BLUE);
		fillrectangle(300, 200, 500, 250); // 按钮背景
		Button* re_play;
		Button* re_main_menu;
		Button* return_game;
		return_game = new Button(OnButtonClick, 300, 300, 400, 20, L"返回游戏");
		re_play = new Button(OnButtonClick, 300, 100, 40, 20, L"重新游玩");
		re_main_menu = new Button(OnButtonClick, 300, 200, 400, 20, L"返回主菜单");
		re_play->RenderToWindows();
		re_main_menu->RenderToWindows();
		return_game->RenderToWindows();
		ExMessage msg;
		bool on = 1;
		while (on) {
			if (re_play->state(msg)) {
				SelectLevelLoop(); //进入关卡页面
			}
			if (re_main_menu->state(msg)) {
				MainMenuLoop();
			}
			if (return_game->state(msg)) {

				//TODO
			}
		}
	}
}


void GameLoop::BattleDefeatLoop()
{
	while (1)
	{
		initgraph(640, 480);//初始化界面
		//setbkcolor(BLUE);
		cleardevice();
		settextcolor(GREEN);
		settextstyle(100, 0, L"微软雅黑");
		outtextxy(100, 70, L"任务失败！");
		//        LButton btns[3];
		//        TCHAR tex1[1000] = _T("重新开始");
		//        TCHAR tex2[1000] = _T("回到主菜单");
		//        TCHAR tex3[1000] = _T("退出游戏");
		//        while (1)
		//        {
		//            setVertexAndShowButton(btns[0], 280, 360, 220, 260, tex1, 20, 10, 5, "green", "green", "red");
		//            setVertexAndShowButton(btns[1], 280, 360, 270, 310, tex2, 20, 10, 5, "white", "green", "red");
		//            setVertexAndShowButton(btns[2], 280, 360, 320, 360, tex3, 20, 10, 5, "YELLOW", "green", "red");
		//        }
		setfillcolor(BLUE);
		fillrectangle(300, 200, 500, 250); // 按钮背景
		Button* re_play;
		Button* re_main_menu;
		Button* exit_game;
		re_play = new Button(OnButtonClick, 300, 100, 40, 20, L"重新游玩");
		re_main_menu = new Button(OnButtonClick, 300, 200, 400, 20, L"返回主菜单");
		exit_game = new Button(OnButtonClick, 300, 300, 400, 20, L"退出游戏");
		re_play->RenderToWindows();
		re_main_menu->RenderToWindows();
		exit_game->RenderToWindows();
		ExMessage msg;
		bool on = 1;
		while (on) {
			if (re_play->state(msg)) {
				SelectLevelLoop(); //进入关卡页面
			}
			if (re_main_menu->state(msg)) {
				MainMenuLoop();
			}
			if (exit_game->state(msg)) {
				exit(0);
			}
		}
	}
}

void GameLoop::BattleVictoryLoop()
{
	while (1)
	{
		initgraph(640, 480);//初始化界面
		setbkcolor(GREEN);
		cleardevice();
		settextcolor(BLUE);
		settextstyle(100, 0, L"微软雅黑");
		outtextxy(100, 70, L"任务完成！");
		Button* next_game;
		Button* re_main_menu;
		Button* exit_game;
		next_game = new Button(OnButtonClick, 300, 100, 40, 20, L"下一关");
		re_main_menu = new Button(OnButtonClick, 300, 200, 400, 20, L"返回主菜单");
		exit_game = new Button(OnButtonClick, 300, 300, 400, 20, L"退出游戏");
		next_game->RenderToWindows();
		re_main_menu->RenderToWindows();
		exit_game->RenderToWindows();

		ExMessage msg;
		bool on = 1;
		while (on) {
			if (next_game->state(msg)) {
				SelectLevelLoop();//进入关卡页面
			}
			if (re_main_menu->state(msg)) {
				MainMenuLoop();
			}
			if (exit_game->state(msg)) {
				exit(0);
			}
		}
	}
}


