#include "stdafx.h"
#include "InputManager.h"
#include "Framework.h"

POINT InputManager::mousePosition;

bool InputManager::lkey[256];
bool InputManager::rkey[256];

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}


int InputManager::GetMouseX()
{
	return mousePosition.x;
}

int InputManager::GetMouseY()
{
	return mousePosition.y;
}

Vector2 InputManager::GetMouseVector2()
{
	return Vector2((float)mousePosition.x,(float)mousePosition.y);
}

void InputManager::UpdateKeyState()
{
	static HWND hWnd = Framework::GetInstance().GetWinApp().GetHWND();

	//���콺 ��ġ ����
	GetCursorPos(&mousePosition);
	ScreenToClient(hWnd,&mousePosition);

	//����, Ű ���� ����
	for (int i = 0; i < 256; ++i)
	{
		lkey[i] = rkey[i];
		rkey[i] = GetAsyncKeyState(i) & 0x8000;
	}
}

int InputManager::GetMyKeyState(int vk)
{
	if (lkey[vk] && rkey[vk]) return 2; //�Ʊ �������� ���ݵ� ���������� ��
	if (!lkey[vk] && rkey[vk]) return 1; //�Ʊ�� �ƴ����� ������ ����������
	if (lkey[vk] && !rkey[vk]) return -1; //������ ������
	return 0;	//������ �ʾ��� ���
}

bool InputManager::GetKeyDown(int vk)
{
	return (!lkey[vk] && rkey[vk])?true:false;
}

bool InputManager::GetKeyPressed(int vk)
{
	return (lkey[vk] && rkey[vk])?true:false;
}

bool InputManager::GetKeyUp(int vk)
{
	return (lkey[vk] && !rkey[vk])?true:false;
}
