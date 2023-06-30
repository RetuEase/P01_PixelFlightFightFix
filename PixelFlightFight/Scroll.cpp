#include "Scroll.h"

/********************暮炊雪********************/
Scroll::Scroll()
{
	// 构造函数  初始化成员变量
	// 初始化成员变量

	baseLifeMax = 100;     // 基地满血
	baseLife = baseLifeMax; // 基地剩余血量等于满血状态
	//dark = false;          // 当有弹出界面时，绘制整体变暗至原来的 1/4
	enemiesNum = ENEMIESNUM;		//剩余敌人数量
	refleshCount = 0;	//刷新计数
	playSpeed = { 0,0 };

	// 初始化基地血条
	//int bloodBarWidth = 10;    // 血条宽度，使用10个像素点表示
	//bloodBar = std::string(bloodBarWidth, '*');

	// 初始化基地血条边框
	//bloodBarBorder = "[" + std::string(bloodBarWidth, '-') + "]";
}

Scroll::~Scroll()
{}

Scroll& Scroll::GetInstance()
{
	// 获取Scroll类的实例的静态成员函数的实现
	// 使用静态局部变量确保只有一个实例存在，并在需要时返回该实例的引用

	static Scroll scroll;
	return scroll;
}


void Scroll::GameUpdate()
{
	int playerMove = 0;
	int enemyMove = 0;
	int bulletMove = 1;
	int fire = 0;

	if (refleshCount == 0) {
		enemyMove = 1;
	}
	if (refleshCount % 2 == 0)
	{
		playerMove = 1;
	}
	if (refleshCount == 3 || refleshCount == 7)
	{
		fire = 1;
	}
	if (enemyMove)
	{
		Bullet::ENEMYMAP.clear();
	}
	for (auto i : Bullet::AllEntities)
	{
		//1敌机动
		if (enemyMove)
		{
			if (i->entityType == _EntityEnemy) {
				i->AutoMove();
				Bullet::ENEMYMAP.insert(std::make_pair(i->core, *i));
				std::cout << "敌人位置:" << i->core.x << " " << i->core.y;
				//i->CollisionDetection();
			}
		}
		//2子弹动
		if (bulletMove)
		{
			if (i->entityType == _EntityBullet) {
				i->AutoMove();
				//i->CollisionDetection();
			}
		}
		//3自机
		if (playerMove)
		{
			if (i->entityType == _EntityPlayer) {
				i->PlayerMove(playSpeed);
				//i->CollisionDetection();
			}
		}
		//4发射子弹
		if (fire) {
			//Bullet newBullet;
		}
	}

	++refleshCount;
	if (refleshCount == 8) {
		refleshCount = 0;
	}
}

//void Scroll::DeleteInstance(InsId id)
//{
	// 从卷轴和仓库删除实体的函数的实现
	// 可以在这里根据给定的实体ID，从卷轴和仓库中删除对应的实体

	// 从卷轴中删除实体
	/*for (auto& entry : scrollMap)
	{
		std::vector<InsId>& tileContainer = entry.second.tileContainer;
		tileContainer.erase(std::remove(tileContainer.begin(), tileContainer.end(), id), tileContainer.end());
	}*/
	// 从仓库中删除实体
//	for (auto it = allEntities.begin(); it != allEntities.end(); ++it) {
//		Block b = **it;
//		if (b.blockID = id) {
//			allEntities.erase(it);
//			break;
//		}
//	}
//}


//// 析构函数的实现
	//// 可以在这里进行资源的释放操作
	//closegraph(); // 关闭easyX绘图窗口
	//// 释放子弹资源
	//for (auto& entry : allEntities)
	//{
	//	Bullet& bullet = entry.second;
	//	if (bullet.entityType == EntityType::_EntityBullet)
	//	{
	//		Bullet& bullet = static_cast<Bullet&>(bullet);
	//		// 根据具体的资源释放方式释放子弹资源
	//		bullet.Resource();
	//	}
	//}

	//// 释放敌机资源
	//for (auto& entry : allEntities)
	//{
	//	Bullet& bullet = entry.second;
	//	if (bullet.entityType == EntityType::_EntityEnemy)
	//	{
	//		PlayerPlane& enemy = static_cast<PlayerPlane&>(bullet);
	//		// 根据具体的资源释放方式释放敌机资源
	//		bullet.Resource();
	//	}
	//}

	//// 释放我方飞机资源
	//for (auto& entry : allEntities)
	//{
	//	Bullet& bullet = entry.second;
	//	if (bullet.entityType == EntityType::_EntityPlayer)
	//	{
	//		PlayerPlane& player = static_cast<PlayerPlane&>(bullet);
	//		// 根据具体的资源释放方式释放我方飞机资源
	//		bullet.Resource();
	//	}
	//}

//void Scroll::ControlPlayer()
//{
	//Coordinate speed = Coordinate(0, 0);

	//if (_kbhit())
	//{
	//	int key = _getch();
	//	switch (key)
	//	{
	//	case 'W':
	//	case 'w':
	//		speed = Coordinate(0, -1);
	//		break;
	//	case 'S':
	//	case 's':
	//		speed = Coordinate(0, 1);
	//		break;
	//	case 'A':
	//	case 'a':
	//		speed = Coordinate(-1, 0);
	//		break;
	//	case 'D':
	//	case 'd':
	//		speed = Coordinate(1, 0);
	//		break;
	//	default:
	//		speed = Coordinate(0, 0);
	//		break;
	//	}
	//}
//}

//void Scroll::TraverseEntity(int i)//0为自机,1为子弹 2为敌机
//{
//	//移动 + 碰撞检测
//	EntityType et;
//	switch (i)
//	{
//	case 0:
//		et = _EntityPlayer;
//	case 1:
//		et = _EntityBullet;
//	case 2:
//		et = _EntityEnemy;
//	}
//	// 遍历实体列表，执行移动和碰撞检测
//	for (auto& entry : allEntities)
//	{
//		Bullet& bullet = entry.second;
//		if (bullet.entityType == et)
//		{
//			bullet.AutoMove();
//			if (et != _EntityEnemy) {
//				bullet.CollisionDetection();
//			}
//		}
//	}
	//// 判断实体类型
	//if (bullet.entityType == EntityType::_EntityPlayer)
	//{
	//	// 我方飞机的移动控制
	//	PlayerPlane& player = static_cast<PlayerPlane&>(bullet);
	//	player.ManualMove(speed); // 假设speed为玩家控制的速度
	//}
	//else if (bullet.entityType == EntityType::_EntityBullet)
	//{
	//	// 子弹的移动
	//	Bullet& bullet = static_cast<Bullet&>(bullet);
	//	bullet.AutoMove();
	//	// 判断子弹是否与敌机发生碰撞
	//	bullet.CollisionDetection();
	//}
	//else if (bullet.entityType == EntityType::_EntityEnemy)
	//{
	//	// 敌机的移动
	//	Plane& enemy = static_cast<Plane&>(bullet);
	//	enemy.AutoMove();
	//	// 判断敌机与子弹的碰撞
	//	enemy.CollisionDetection();
	//	// 判断敌机与我方飞机的碰撞
	//	PlayerPlane& player = static_cast<PlayerPlane&>(instanceRepo[EntityType::_EntityPlayer]);
	//	player.CollisionDetection();
	//}
	// 将实体渲染到scrollMap中
	//bullet.RenderToScroll();

//}
//
//void Scroll::RenderToWindows()
//{
	//// 将卷轴信息渲染到窗口的函数的实现
	//// 可以在这里将卷轴的信息绘制到绘图区的缓冲区中
	//const int windowWidth = 800;  // 窗口宽度
	//const int windowHeight = 600; // 窗口高度
	//const int scrollSpeed = 1;    // 卷轴滚动速度

	//// 计算卷轴滚动偏移量
	//static int scrollOffset = 0;
	//scrollOffset = (scrollOffset + scrollSpeed) % windowHeight;

	//// 清空窗口内容
	//cleardevice();

	//// 绘制卷轴内容（背景图像）
	//for (int y = 0; y < windowHeight; y++)
	//{
	//	// 计算绘制行的实际位置（滚动偏移量）
	//	int scrollRow = (y + scrollOffset) % windowHeight;

	//	// 绘制背景图像的一行
	//	DrawRowOfScroll(scrollRow);
	//}

	//// 获取玩家飞机位置
	//PlayerPlane& player = static_cast<PlayerPlane&>(instanceRepo[EntityType::_EntityPlayer]);
	//Coordinate playerPos = player.pos;

	//// 绘制敌机
	//for (auto& entry : instanceRepo)
	//{
	//	Bullet& bullet = entry.second;
	//	if (bullet.entityType == EntityType::_EntityEnemy)
	//	{
	//		Plane& enemy = static_cast<Plane&>(bullet);
	//		Coordinate enemyPos = enemy.pos;
	//		// 根据实际位置绘制敌机
	//		DrawEnemy(enemyPos, scrollOffset);
	//	}
	//}

	//// 绘制玩家飞机
	//DrawPlayer(playerPos, scrollOffset);
//	BeginBatchDraw();
//	// 刷新窗口显示
//	FlushBatchDraw();
//}




//void Scroll::DrawRowOfScroll(int scrollRow)
//{
//	// 根据滚动行的实际位置绘制背景图像的一行
//	// 这里使用easyX库提供的绘图函数line()绘制一行直线作为示例
//	line(0, scrollRow, 800, scrollRow);
//}
//void Scroll::DrawPlayer(Coordinate playerPos, int scrollOffset)
//{
//	//这个地方到时候等飞机工坊写好再说
//}
//
//void Scroll::DrawEnemy(Coordinate enemyPos, int scrollOffset)
//{
//	//这个也是，输出像素，我不知道它是如何保存，还是说要我遍历
//}

//void Scroll::RenderInfo()
//{
//	// 渲染基地血条和分数等信息的函数的实现
//	// 可以在这里将基地的血条、分数等信息绘制到绘图区的缓冲区中
//
//	// 输出分数
//	std::cout << "Score: " << score << std::endl;
//
//	// 渲染基地血条和边框
//	std::cout << "Base Life: " << bloodBarBorder << std::endl;
//	std::cout << "          " << bloodBar << std::endl;
//	// ...
//}

//void Scroll::InitiateInstance(PlaneTemplate pt, Coordinate pos)
//{
//	// 生成实体到卷轴和仓库的函数的实现
//	// 可以在这里根据给定的PlaneTemplate和位置信息生成实体，并将其添加到卷轴和仓库中
//
//	// 创建实体并初始化
//	Bullet bullet;
//	bullet.SetPlaneTemplate(pt);			//差一个以PlaneTemplate创建Bullet实体
//	bullet.pos = pos;
//	bullet.insId = insIdCounter++;
//
//	// 将实体添加到卷轴
//	Coordinate coordinate = bullet.pos;
//	scrollMap[coordinate].tileContainer.push_back(bullet.insId);
//
//	// 将实体添加到仓库
//	instanceRepo[bullet.insId] = bullet;
//}
