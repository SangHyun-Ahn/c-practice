#pragma once

namespace Engine
{
	typedef struct tagGraphicDesc
	{
		enum WINMODE { WINMODE_FULL, WINMODE_WINDOW, WINMODE_END };

		HWND			hWnd;
		unsigned int	iSizeX, iSizeY;
		WINMODE			eWinMode;

	}GRAPHICDESC;
	
	//정점구조체의 멤버변수는 아주 중요함! 
	//_D3DDECLUSAGE 의 열거체 순서대로 꼭 멤버로 넣을것
	typedef struct tagVertex_Position_Texcoord
	{
		D3DXVECTOR3			vPosition;
		D3DXVECTOR2			vTexcoord;
	} VTXPOSTEX;

}
