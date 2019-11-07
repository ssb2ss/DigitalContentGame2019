#include "stdafx.h"
#include "TimeManager.h"

float TimeManager::deltaTime;

void TimeManager::UpdateTime()
{
	static DWORD oldTime = timeGetTime();		//static ���� �ʱ�ȭ�� 1ȸ�� �����

	DWORD curTime = timeGetTime();				//���� �ð� �޾ƿ�
	deltaTime = (curTime - oldTime) * 0.001f;	//ms(�и�������), ���� �ð�-���� �ð� = ��Ÿ�ð�
	oldTime = curTime;							//���� �ð��� ���� �ð� ����
}

float TimeManager::GetDeltaTime()
{
	return deltaTime;
}
