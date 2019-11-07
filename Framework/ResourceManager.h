#pragma once
#include "stdafx.h"
#include "Math.h"

//�����ӿ�ũ ���������� �۵��ϴ� ��ü�Դϴ�.

struct Sprite {
	const wchar_t* uri;
	ID2D1Bitmap* bitmap;	//��Ʈ���� ����Ǿ��ִ� ������
	
	Vector2 GetSize();
};


//���� �̹����� ������ �ε��ϴ� ���� �����ϱ� ���� ��ü.
//�̹��� ���ҽ��� �����մϴ�.
class ResourceManager
{
public:
	~ResourceManager();
public:
	std::list<Sprite*> spriteList;		//�̹����� ������ ����Ʈ
	Sprite* LoadBitmapFromFile(PCWSTR uri, UINT destinationWidth, UINT destinationHeight);
};

