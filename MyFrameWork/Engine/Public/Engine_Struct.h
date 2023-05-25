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
	
	//��������ü�� ��������� ���� �߿���! 
	//_D3DDECLUSAGE �� ����ü ������� �� ����� ������
	typedef struct tagVertex_Position_Texcoord
	{
		D3DXVECTOR3			vPosition;
		D3DXVECTOR2			vTexcoord;
	} VTXPOSTEX;

}
