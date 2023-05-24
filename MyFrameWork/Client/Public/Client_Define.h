#pragma once

#include <process.h>

namespace Client
{
	enum LEVEL { LEVEL_STATIC, LEVEL_LOADING, LEVEL_LOGO, LEVEL_GAMEPLAY, LEVEL_END };
	const unsigned int	WINCX = 1280;
	const unsigned int	WINCY = 720;
}

extern HWND		g_hWnd;

#define PURE = 0
#define PI 3.14159

using namespace Client;