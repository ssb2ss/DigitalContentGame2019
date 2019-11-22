#include "stdafx.h"
#include "Framework.h"
#include "TitleScene.h"
#include "Math.h"

#include <ctime>

int main()
{
	srand((size_t)time(NULL));

	Framework& f = Framework::GetInstance();
	f.Run(new TitleScene(), TITLE, WIDTH, HEIGHT, false);
	return 0;
}