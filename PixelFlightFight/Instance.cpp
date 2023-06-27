#include "Instance.h"

Bullet::Bullet()
	:type(TYPE_BULLET)
{
}

Bullet::Bullet(Coordinate pos)
	:type(TYPE_BULLET)
{
}

Bullet::~Bullet()
{
}

void Bullet::AutoMove()
{
}

void Bullet::RenderToScroll()
{
}

/***********重中之重***********/
void Bullet::CollisionDetection()
{
}

Plane::Plane()
{
}

Plane::Plane(Coordinate pos)
	:Bullet(pos)
{
	type = TYPE_PLANE;
}

Plane::~Plane()
{
}

void Plane::Destroy(Coordinate pos)
{
}

/******DFS******/
void Plane::Fracture()
{
}

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

PlayerPlane::PlayerPlane()
{
}

PlayerPlane::~PlayerPlane()
{
}

void PlayerPlane::ManualMove(Speed speed)
{
}
