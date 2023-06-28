#include "GameLoop.h"
#include "Scroll.h"
#include "Button.h"
using namespace std;

/********************yjl********************/

GameLoop::GameLoop()
	:flag(1)
{
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
			MainMenuLoop();//主页面
		case 2:
			SelectLevelLoop();//选择关卡
		case 3:
			PlaneBattleLoop();//战斗页面
		case 4:
			PlaneWorkshopLoop();//飞机工坊页面
		case -1:
			return;

		}
	}
}

void GameLoop::MainMenuLoop()
{

	initgraph(800, 600, EW_SHOWCONSOLE);//创建窗口并显示控制台; // 初始化图形窗口大小为800*600像素
	setbkcolor(WHITE);
	//cleardevice();
	setbkmode(TRANSPARENT);//处理字体背景
	setfillcolor(CYAN);//设置填充色，这里是浅青色
	setlinecolor(BLACK); //设置当前线条的颜色为黑色
	cleardevice();//显示背景颜色
	settextstyle(45, 0, _T("微软雅黑"));
	LPCTSTR title = _T("像素飞机大战");
	outtextxy(500 - textwidth(title), 100, title);
	// 绘制开始游戏按钮
	//setfillcolor(BLUE);
	//fillrectangle(300, 200, 500, 250); // 按钮背景

	Button *Begin;//绘制开始游戏按钮
	Button* WorkShop;
	Button* Operating_instructions;//绘制飞机工厂
	Button* exit_game;
	//Button* Operating_instructions;
	//Button* exit_game;//绘制操作说明
	Begin = new Button(OnButtonClick, 340, 200, 500, 250,L"开始游戏");
	WorkShop = new Button (OnButtonClick, 340, 300, 500, 250, L"飞机工厂");
	Operating_instructions = new Button(OnButtonClick, 340, 400, 500, 250, L"操作说明");
	exit_game = new Button(OnButtonClick, 340, 500, 500, 250, L"退出游戏");
	Begin->RenderToWindows();
	WorkShop->RenderToWindows();
	Operating_instructions->RenderToWindows();
	exit_game->RenderToWindows();
	ExMessage msg;
	bool on = 1;
	while (on)
	{
		msg = getmessage();

		if (Begin->state(msg))		// 开始游戏
		{
			printf("Begin\n");
			SelectLevelLoop();
		}
		if (WorkShop->state(msg))		// 飞机工厂
		{
			printf("End\n");
			PlaneWorkshopLoop();
		}
		if (Operating_instructions->state(msg))		// 操作提示
		{
			
		}
		if (exit_game->state(msg)) {//退出游戏
			exit(0);
		}
	}

	_getch();


	int mouseX, mouseY;
	MOUSEMSG mouseMsg;

	while (1)
	{
		// 处理鼠标事件
		mouseMsg = GetMouseMsg();
		if (mouseMsg.uMsg == WM_LBUTTONDOWN)
		{
			mouseX = mouseMsg.x;
			mouseY = mouseMsg.y;
			if (mouseX >= 300 && mouseX <= 500 && mouseY >= 200 && mouseY <= 250)
			{
				// 用户点击了开始游戏按钮，跳转到游戏选关界面
				SelectLevelLoop();
			}
			else if (mouseX >= 300 && mouseX <= 500 && mouseY >= 300 && mouseY <= 350)
			{
				// 用户点击了飞机工厂按钮，跳转到飞机工坊界面
				PlaneWorkshopLoop();
			}
			else if (mouseX >= 300 && mouseX <= 500 && mouseY >= 400 && mouseY <= 450)
			{
				// 用户点击了操作说明按钮，跳转到说明界面

			}
			else if (mouseX >= 300 && mouseX <= 500 && mouseY >= 500 && mouseY <= 550)
			{
				// 用户点击了退出游戏按钮
				exit(0);
				break;
			}
		}



	}

	cleardevice();
	closegraph();
}



void GameLoop::SelectLevelLoop()
{
	initgraph(800, 600);
	setbkcolor(WHITE);
	cleardevice();

	setfillcolor(RED);
	fillrectangle(300, 250, 500, 350);

	settextcolor(BLACK);
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


void GameLoop::PlaneBattleLoop()
{
    initgraph(800, 600);

    settextcolor(RED);
    settextstyle(20, 0, _T("黑体"));
    outtextxy(20, 20, _T("欢迎来到战斗界面"));
    ExMessage emg;//可以循环接受鼠标信息

    //获取Scroll信息
    Scroll sc = Scroll::GetInstance();
    while (1)
    {//点击esc按键跳转到游戏主菜单
        if (peekmessage(&emg))
        {
            if (emg.message == WM_KEYDOWN)
            {
                if (emg.message == VK_ESCAPE)
                {
                    BattleMenuLoop();
                }
            }
        }
        else if (sc.baseLife <= 0)//基地血量耗尽
        {
            BattleDefeatLoop();
        }
        else if (sc.insIdCounter == 0)//敌机全部被消灭
        {
            BattleVictoryLoop();
        }


    }
    closegraph();
}

/********************禁区林黛玉********************/

struct LButton
{
	int x1;
	int x2;
	int y1;
	int y2;
};
void setVertexAndShowButton(LButton btn, int x1, int x2, int y1, int y2, TCHAR text[1000], int tlength, int twidth, int tsetoff, string tcolor, string lcolor, string fcolor)
{
	BeginBatchDraw();//暂停绘画
	//设置顶点坐标
	btn.x1 = x1;
	btn.x2 = x2;
	btn.y1 = y1;
	btn.y2 = y2;
	//设置边框颜色
	if (lcolor == "red" || lcolor == "RED")setlinecolor(RED);//设置边框颜色为红色
	else if (lcolor == "green" || lcolor == "GREEN")setlinecolor(GREEN);//设置边框颜色为红色
	else if (lcolor == "blue" || lcolor == "BLUE")setlinecolor(BLUE);//设置边框颜色为红色
	else if (lcolor == "yellow" || lcolor == "YELLOW")setlinecolor(YELLOW);//设置边框颜色为黄色
	else if (lcolor == "black" || lcolor == "BLACK")setlinecolor(BLACK);//设置边框颜色为黑色
	else if (lcolor == "white" || lcolor == "WHITE")setlinecolor(WHITE);//设置边框颜色为白色
	else {
		int x;
		x = MessageBox(GetForegroundWindow(), TEXT("请检查按钮边框颜色是否设置正确，目前字体颜色包含：red、green、blue、yellow、black、white。"), TEXT("按钮边框颜色设置错误"), 1);
		cout << x;
	}
	//绘制按钮边框
	rectangle(btn.x1, btn.y1, btn.x2, btn.y2);
	//设置填充颜色
	if (fcolor == "red" || fcolor == "RED")setfillcolor(RED);//设置填充颜色为红色
	else if (fcolor == "green" || fcolor == "GREEN")setfillcolor(GREEN);//设置填充颜色为红色
	else if (fcolor == "blue" || fcolor == "BLUE")setfillcolor(BLUE);//设置填充颜色为红色
	else if (fcolor == "yellow" || fcolor == "YELLOW")setfillcolor(YELLOW);//设置填充颜色为黄色
	else if (fcolor == "black" || fcolor == "BLACK")setfillcolor(BLACK);//设置填充颜色为黑色
	else if (fcolor == "white" || fcolor == "WHITE")setfillcolor(WHITE);//设置填充颜色为白色
	else {
		int x;
		x = MessageBox(GetForegroundWindow(), TEXT("请检查按钮填充颜色是否设置正确，目前填充颜色包含：red、green、blue、yellow、black、white。"), TEXT("按钮填充颜色设置错误"), 1);
		cout << x;
	}
	fillrectangle(btn.x1, btn.y1, btn.x2, btn.y2);
	//设置按钮文字
	setbkmode(TRANSPARENT);//设置透明字体

	if (tcolor == "red" || tcolor == "RED")settextcolor(RED);//设置字体颜色为红色
	else if (tcolor == "green" || tcolor == "GREEN")settextcolor(GREEN);//设置字体颜色为红色
	else if (tcolor == "blue" || tcolor == "BLUE")settextcolor(BLUE);//设置字体颜色为红色
	else if (tcolor == "yellow" || tcolor == "YELLOW")settextcolor(YELLOW);//设置字体颜色为黄色
	else if (tcolor == "black" || tcolor == "BLACK")settextcolor(BLACK);//设置字体颜色为黑色
	else if (tcolor == "white" || tcolor == "WHITE")settextcolor(WHITE);//设置字体颜色为白色
	else {
		int x;
		x = MessageBox(GetForegroundWindow(), TEXT("请检查字体颜色是否设置正确，目前字体颜色包含：red、green、blue、yellow、black、white。"), TEXT("字体颜色设置错误"), 1);
		cout << x;
	}
	//settextcolor(BLUE);//设置字体颜色
	settextstyle(tlength, twidth, _T("宋体"));//设置字体格式
	outtextxy(x1 + tsetoff, y1 + tsetoff, text);//设置显示位置


	//设置按钮交互响应
	//MOUSEMSG m;// 定义鼠标消息
	int change = 10;
	ExMessage m;//定义一个消息变量
	m = getmessage(EM_MOUSE);//获取鼠标消息
	switch (m.message)
	{
	case WM_MOUSEMOVE:
		// 鼠标移动按钮时按钮变大
		if (m.x >= btn.x1 && m.x <= btn.x2)
		{
			if (m.y >= btn.y1 && m.y <= btn.y2)
			{
				rectangle(btn.x1 - change, btn.y1 - change, btn.x2 + change, btn.y2 + change);
			}
			else
			{
				FlushBatchDraw();//批量绘制
				//cleardevice();
			}
		}
		else
		{
			FlushBatchDraw();//批量绘制
			//cleardevice();
		}
		break;

	case WM_LBUTTONDOWN:
		// 鼠标点击按钮会变绿色
		if (m.x >= btn.x1 && m.x <= btn.x2)
		{
			if (m.y >= btn.y1 && m.y <= btn.y2)
			{
				setfillcolor(GREEN);
				fillrectangle(btn.x1, btn.y1, btn.x2, btn.y2);
				FlushBatchDraw();//批量绘制
			}
			else
			{
				FlushBatchDraw();//批量绘制
				//cleardevice();
			}
		}
		break;
	}

	//恢复画线和填充颜色
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void GameLoop::BattleMenuLoop()
{
	while (1)
	{
		LButton btns[3]; //初始化按钮结构体数组
		initgraph(640, 480);//初始化界面
		setbkcolor(WHITE);
		cleardevice();
		settextcolor(GREEN);
		settextstyle(100, 0, L"楷体");
		outtextxy(225, 70, L"菜单");
		TCHAR tex1[1000] = _T("重新开始");
		TCHAR tex2[1000] = _T("继续游戏");
		TCHAR tex3[1000] = _T("退出游戏");

		while (1)
		{
			setVertexAndShowButton(btns[0], 280, 360, 220, 260, tex1, 20, 10, 5, "green", "green", "red");
			setVertexAndShowButton(btns[1], 280, 360, 270, 310, tex2, 20, 10, 5, "white", "green", "red");
			setVertexAndShowButton(btns[2], 280, 360, 320, 360, tex3, 20, 10, 5, "YELLOW", "green", "red");
		}

		_getch();//等待用户输入

	}
}

void GameLoop::BattleDefeatLoop()
{
	while (1)
	{
		initgraph(640, 480);//初始化界面
		setbkcolor(BLUE);
		cleardevice();
		settextcolor(GREEN);
		settextstyle(100, 0, L"楷体");
		outtextxy(100, 70, L"您失败了！");
		LButton btns[3];
		TCHAR tex1[1000] = _T("重新开始");
		TCHAR tex2[1000] = _T("回到主菜单");
		TCHAR tex3[1000] = _T("退出游戏");
		while (1)
		{
			setVertexAndShowButton(btns[0], 280, 360, 220, 260, tex1, 20, 10, 5, "green", "green", "red");
			setVertexAndShowButton(btns[1], 280, 360, 270, 310, tex2, 20, 10, 5, "white", "green", "red");
			setVertexAndShowButton(btns[2], 280, 360, 320, 360, tex3, 20, 10, 5, "YELLOW", "green", "red");
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
		settextstyle(100, 0, L"楷体");
		outtextxy(100, 70, L"您获胜了！");
		LButton btns[3];
		TCHAR tex1[1000] = _T("下一关");
		TCHAR tex2[1000] = _T("回到主菜单");
		TCHAR tex3[1000] = _T("退出游戏");
		while (1)
		{
			setVertexAndShowButton(btns[0], 280, 360, 220, 260, tex1, 20, 10, 5, "green", "green", "red");
			setVertexAndShowButton(btns[1], 280, 360, 270, 310, tex2, 20, 10, 5, "white", "green", "red");
			setVertexAndShowButton(btns[2], 280, 360, 320, 360, tex3, 20, 10, 5, "YELLOW", "green", "red");
		}
	}
}
