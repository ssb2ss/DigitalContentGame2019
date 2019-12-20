#pragma once
#include "stdafx.h"

//�۾��� ��Ÿ�� ������Ʈ�� �Ӽ��� �����մϴ�.
//�⺻������ ��Ʈ �̸�, ��Ʈ ũ��, ����, ���� ���� �����մϴ�.
//DWRITE_FONT_XXXX ������ ������ enum(������)�����̰�, ���۸��� �غ��ø� ���� �ɼ��� ã�� �� �ֽ��ϴ�. �������� ��ġ ������ �����ϴ� �����ϼ���.

class Font
{
public:
	Font(const wchar_t* fontName, float fontSize = 20.0f, float red=0.0f, float green = 0.0f, float blue = 0.0f, float alpha=1.0f,  bool isBold=false);
	virtual ~Font();
public:
	const wchar_t* fontName;		//��Ʈ��
	DWRITE_FONT_WEIGHT fontWeight;	//��Ʈ ����
	DWRITE_FONT_STYLE fontStyle;	//��Ʈ ��Ÿ��
	DWRITE_FONT_STRETCH fontStretch;//���� ���� ����
	float fontSize;
	IDWriteTextFormat* textFormat;	//���� dwrite �ؽ�Ʈ ����
	ID2D1SolidColorBrush* colorBrush;
};

