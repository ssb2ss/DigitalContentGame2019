#include "stdafx.h"
#include "ExitButton.h"

//생성 : 이주형

ExitButton::ExitButton(float x, float y) : Button(L"resources/sprites/button/exitButton.png", x,y)
{

}


ExitButton::~ExitButton()
{
}

void ExitButton::OnClick()
{
	exit(0);
}