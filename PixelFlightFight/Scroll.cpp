#include "Scroll.h"

/********************ĺ��ѩ********************/
Scroll::Scroll()
{
	// ���캯��  ��ʼ����Ա����
	// ��ʼ����Ա����

	baseLifeMax = 100;     // ������Ѫ
	baseLife = baseLifeMax; // ����ʣ��Ѫ��������Ѫ״̬
	//dark = false;          // ���е�������ʱ����������䰵��ԭ���� 1/4
	enemiesNum = ENEMIESNUM;		//ʣ���������
	refleshCount = 0;	//ˢ�¼���
	playSpeed = { 0,0 };

	// ��ʼ������Ѫ��
	//int bloodBarWidth = 10;    // Ѫ����ȣ�ʹ��10�����ص��ʾ
	//bloodBar = std::string(bloodBarWidth, '*');

	// ��ʼ������Ѫ���߿�
	//bloodBarBorder = "[" + std::string(bloodBarWidth, '-') + "]";
}

Scroll::~Scroll()
{}

Scroll& Scroll::GetInstance()
{
	// ��ȡScroll���ʵ���ľ�̬��Ա������ʵ��
	// ʹ�þ�̬�ֲ�����ȷ��ֻ��һ��ʵ�����ڣ�������Ҫʱ���ظ�ʵ��������

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
		//1�л���
		if (enemyMove)
		{
			if (i->entityType == _EntityEnemy) {
				i->AutoMove();
				Bullet::ENEMYMAP.insert(std::make_pair(i->core, *i));
				std::cout << "����λ��:" << i->core.x << " " << i->core.y;
				//i->CollisionDetection();
			}
		}
		//2�ӵ���
		if (bulletMove)
		{
			if (i->entityType == _EntityBullet) {
				i->AutoMove();
				//i->CollisionDetection();
			}
		}
		//3�Ի�
		if (playerMove)
		{
			if (i->entityType == _EntityPlayer) {
				i->PlayerMove(playSpeed);
				//i->CollisionDetection();
			}
		}
		//4�����ӵ�
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
	// �Ӿ���Ͳֿ�ɾ��ʵ��ĺ�����ʵ��
	// ������������ݸ�����ʵ��ID���Ӿ���Ͳֿ���ɾ����Ӧ��ʵ��

	// �Ӿ�����ɾ��ʵ��
	/*for (auto& entry : scrollMap)
	{
		std::vector<InsId>& tileContainer = entry.second.tileContainer;
		tileContainer.erase(std::remove(tileContainer.begin(), tileContainer.end(), id), tileContainer.end());
	}*/
	// �Ӳֿ���ɾ��ʵ��
//	for (auto it = allEntities.begin(); it != allEntities.end(); ++it) {
//		Block b = **it;
//		if (b.blockID = id) {
//			allEntities.erase(it);
//			break;
//		}
//	}
//}


//// ����������ʵ��
	//// ���������������Դ���ͷŲ���
	//closegraph(); // �ر�easyX��ͼ����
	//// �ͷ��ӵ���Դ
	//for (auto& entry : allEntities)
	//{
	//	Bullet& bullet = entry.second;
	//	if (bullet.entityType == EntityType::_EntityBullet)
	//	{
	//		Bullet& bullet = static_cast<Bullet&>(bullet);
	//		// ���ݾ������Դ�ͷŷ�ʽ�ͷ��ӵ���Դ
	//		bullet.Resource();
	//	}
	//}

	//// �ͷŵл���Դ
	//for (auto& entry : allEntities)
	//{
	//	Bullet& bullet = entry.second;
	//	if (bullet.entityType == EntityType::_EntityEnemy)
	//	{
	//		PlayerPlane& enemy = static_cast<PlayerPlane&>(bullet);
	//		// ���ݾ������Դ�ͷŷ�ʽ�ͷŵл���Դ
	//		bullet.Resource();
	//	}
	//}

	//// �ͷ��ҷ��ɻ���Դ
	//for (auto& entry : allEntities)
	//{
	//	Bullet& bullet = entry.second;
	//	if (bullet.entityType == EntityType::_EntityPlayer)
	//	{
	//		PlayerPlane& player = static_cast<PlayerPlane&>(bullet);
	//		// ���ݾ������Դ�ͷŷ�ʽ�ͷ��ҷ��ɻ���Դ
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

//void Scroll::TraverseEntity(int i)//0Ϊ�Ի�,1Ϊ�ӵ� 2Ϊ�л�
//{
//	//�ƶ� + ��ײ���
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
//	// ����ʵ���б�ִ���ƶ�����ײ���
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
	//// �ж�ʵ������
	//if (bullet.entityType == EntityType::_EntityPlayer)
	//{
	//	// �ҷ��ɻ����ƶ�����
	//	PlayerPlane& player = static_cast<PlayerPlane&>(bullet);
	//	player.ManualMove(speed); // ����speedΪ��ҿ��Ƶ��ٶ�
	//}
	//else if (bullet.entityType == EntityType::_EntityBullet)
	//{
	//	// �ӵ����ƶ�
	//	Bullet& bullet = static_cast<Bullet&>(bullet);
	//	bullet.AutoMove();
	//	// �ж��ӵ��Ƿ���л�������ײ
	//	bullet.CollisionDetection();
	//}
	//else if (bullet.entityType == EntityType::_EntityEnemy)
	//{
	//	// �л����ƶ�
	//	Plane& enemy = static_cast<Plane&>(bullet);
	//	enemy.AutoMove();
	//	// �жϵл����ӵ�����ײ
	//	enemy.CollisionDetection();
	//	// �жϵл����ҷ��ɻ�����ײ
	//	PlayerPlane& player = static_cast<PlayerPlane&>(instanceRepo[EntityType::_EntityPlayer]);
	//	player.CollisionDetection();
	//}
	// ��ʵ����Ⱦ��scrollMap��
	//bullet.RenderToScroll();

//}
//
//void Scroll::RenderToWindows()
//{
	//// ��������Ϣ��Ⱦ�����ڵĺ�����ʵ��
	//// ���������ｫ�������Ϣ���Ƶ���ͼ���Ļ�������
	//const int windowWidth = 800;  // ���ڿ��
	//const int windowHeight = 600; // ���ڸ߶�
	//const int scrollSpeed = 1;    // ��������ٶ�

	//// ����������ƫ����
	//static int scrollOffset = 0;
	//scrollOffset = (scrollOffset + scrollSpeed) % windowHeight;

	//// ��մ�������
	//cleardevice();

	//// ���ƾ������ݣ�����ͼ��
	//for (int y = 0; y < windowHeight; y++)
	//{
	//	// ��������е�ʵ��λ�ã�����ƫ������
	//	int scrollRow = (y + scrollOffset) % windowHeight;

	//	// ���Ʊ���ͼ���һ��
	//	DrawRowOfScroll(scrollRow);
	//}

	//// ��ȡ��ҷɻ�λ��
	//PlayerPlane& player = static_cast<PlayerPlane&>(instanceRepo[EntityType::_EntityPlayer]);
	//Coordinate playerPos = player.pos;

	//// ���Ƶл�
	//for (auto& entry : instanceRepo)
	//{
	//	Bullet& bullet = entry.second;
	//	if (bullet.entityType == EntityType::_EntityEnemy)
	//	{
	//		Plane& enemy = static_cast<Plane&>(bullet);
	//		Coordinate enemyPos = enemy.pos;
	//		// ����ʵ��λ�û��Ƶл�
	//		DrawEnemy(enemyPos, scrollOffset);
	//	}
	//}

	//// ������ҷɻ�
	//DrawPlayer(playerPos, scrollOffset);
//	BeginBatchDraw();
//	// ˢ�´�����ʾ
//	FlushBatchDraw();
//}




//void Scroll::DrawRowOfScroll(int scrollRow)
//{
//	// ���ݹ����е�ʵ��λ�û��Ʊ���ͼ���һ��
//	// ����ʹ��easyX���ṩ�Ļ�ͼ����line()����һ��ֱ����Ϊʾ��
//	line(0, scrollRow, 800, scrollRow);
//}
//void Scroll::DrawPlayer(Coordinate playerPos, int scrollOffset)
//{
//	//����ط���ʱ��ȷɻ�����д����˵
//}
//
//void Scroll::DrawEnemy(Coordinate enemyPos, int scrollOffset)
//{
//	//���Ҳ�ǣ�������أ��Ҳ�֪��������α��棬����˵Ҫ�ұ���
//}

//void Scroll::RenderInfo()
//{
//	// ��Ⱦ����Ѫ���ͷ�������Ϣ�ĺ�����ʵ��
//	// ���������ｫ���ص�Ѫ������������Ϣ���Ƶ���ͼ���Ļ�������
//
//	// �������
//	std::cout << "Score: " << score << std::endl;
//
//	// ��Ⱦ����Ѫ���ͱ߿�
//	std::cout << "Base Life: " << bloodBarBorder << std::endl;
//	std::cout << "          " << bloodBar << std::endl;
//	// ...
//}

//void Scroll::InitiateInstance(PlaneTemplate pt, Coordinate pos)
//{
//	// ����ʵ�嵽����Ͳֿ�ĺ�����ʵ��
//	// ������������ݸ�����PlaneTemplate��λ����Ϣ����ʵ�壬��������ӵ�����Ͳֿ���
//
//	// ����ʵ�岢��ʼ��
//	Bullet bullet;
//	bullet.SetPlaneTemplate(pt);			//��һ����PlaneTemplate����Bulletʵ��
//	bullet.pos = pos;
//	bullet.insId = insIdCounter++;
//
//	// ��ʵ����ӵ�����
//	Coordinate coordinate = bullet.pos;
//	scrollMap[coordinate].tileContainer.push_back(bullet.insId);
//
//	// ��ʵ����ӵ��ֿ�
//	instanceRepo[bullet.insId] = bullet;
//}
