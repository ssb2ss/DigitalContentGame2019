#include <Windows.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>

//���̷�Ʈx ���� ���
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

//COM
#include <wincodec.h>

//SOUND
#include <xaudio2.h>
#include <mfapi.h>		//wmf
#include <mfidl.h>
#include <mfreadwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "Dwrite.lib")
#pragma comment(lib, "WindowsCodecs.lib")
#pragma comment(lib, "Winmm.lib")

//SOUND
#pragma comment (lib, "Xaudio2.lib")
#pragma comment (lib, "mfreadwrite.lib")
#pragma comment (lib, "mfplat.lib")
#pragma comment (lib, "mfuuid")


#define SAFE_RELEASE(p) { if(p){p->Release();} p=NULL; }
#define SAFE_DELETE(p) {if(p!=nullptr){delete(p);} p=nullptr; }

typedef D2D1_POINT_2F Point;


#define TITLE L"����ȿ��"
#define WIDTH 1920
#define HEIGHT 1080