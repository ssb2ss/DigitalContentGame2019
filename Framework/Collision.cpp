#include "stdafx.h"
#include "Collision.h"
#include "Collider.h"


bool Collision::Intersected(const Collider::AABBBox& a, const Collider::AABBBox& b)
{
	//���� ������ �� ���� ��츦 ���� ��, �� ���� ��ȯ
	return !(
		(a.rightBottom.x < b.leftTop.x) ||
		(b.rightBottom.x < a.leftTop.x) ||
		(a.rightBottom.y < b.leftTop.y) ||
		(b.rightBottom.y < a.leftTop.y));
}

bool Collision::Intersected(const Collider::AABBBox& a, const Collider::Circle& b)
{
	Vector2 circleDistance;
	circleDistance.x = (a.rightBottom.x + a.leftTop.x) * 0.5f - b.center.x;
	circleDistance.y = (a.rightBottom.y + a.leftTop.y) * 0.5f - b.center.y;
	Vector2 halfBox = Vector2((a.rightBottom-a.leftTop)*0.5f);

	circleDistance.x *= (circleDistance.x >= 0) ? 1.0f : -1.0f;
	circleDistance.y *= (circleDistance.y >= 0) ? 1.0f : -1.0f;

	if (circleDistance.x > (halfBox.x + b.radius)) { return false; }
	if (circleDistance.y > (halfBox.y + b.radius)) { return false; }

	if (circleDistance.x <= halfBox.x) { return true; }
	if (circleDistance.y <= halfBox.y) { return true; }

	Vector2 corner = circleDistance - halfBox;

	return (corner.DotProduct(corner) <= (b.radius * b.radius));
}

bool Collision::Intersected(const Collider::Circle& a, const Collider::Circle& b)
{
	Vector2 centerVector = b.center - a.center;					//�߽��� �մ� ����
	float distance = centerVector.DotProduct(centerVector);		//�ڱ� �ڽ��� ����==����
	return distance < ((a.radius + b.radius) * (a.radius + b.radius));	//�Ÿ���
}

bool Collision::Intersected(const Collider::AABBBox& a, const Vector2& b)
{
	return a.leftTop.x<b.x && a.rightBottom.x>b.x &&
		a.leftTop.y<b.y && a.rightBottom.y>b.y;
}

bool Collision::Intersected(const Collider::Circle& a, const Vector2& b)
{
	Vector2 v = b - a.center;
	return v.DotProduct(v) <= a.radius*a.radius;
}
