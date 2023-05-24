#include "Device.h"

IMPLEMENT_SINGLETON(CDevice)

CDevice::CDevice() 
	: m_pSDK(nullptr),
	  m_pDevice(nullptr)
{
}




HRESULT CDevice::Initialize(HWND _hwnd, GRAPHICDESC::WINMODE _eMode, _uint _wincx, _uint _wincy, LPDIRECT3DDEVICE9* ppOut)
{
	// 1. 장치를 조사할 객체 생성
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	// 2. 장치 조사
	D3DCAPS9	DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));


	// GetDeviceCaps : 장치에 대한 정보(지원 수준)를 얻어오는 함수
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, // 정보를 얻으려는 기본 그래픽 카드를 의미
		D3DDEVTYPE_HAL,
		&DeviceCaps)))
	{
		MSG_BOX("GetDeviceCaps Failed");
		return E_FAIL;
	}
	
	// 버텍스 프로세싱 = 정점의 변환 + 조명 연산

	_ulong vp = 0;

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// 3. 장치 제어 객체 생성

	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferWidth = _wincx;
	d3dpp.BackBufferHeight = _wincy;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	// D3DSWAPEFFECT_DISCARD : 스왑 체인 방식 
	// D3DSWAPEFFECT_FLIP : 버퍼 하나를 뒤집으면서 사용하는 방식
	// D3DSWAPEFFECT_COPY : 더블 버퍼링과 유사한 복사 방식
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	//이 부분 문제******************
	d3dpp.hDeviceWindow = _hwnd;//g_hWnd;

	// 창모드로 실행할 것인가 전체 화면 모드로 실행할 것인가
	d3dpp.Windowed = _eMode;		// 창 모드

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	// 전체화면 모드일 때 사용되는 변수들

	// 전체화면 모드일 때 모니터 재생률과 프로그램의 재생 관계를 어떻게 설정할 것인가
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	// D3DPRESENT_INTERVAL_IMMEDIATE : 즉시 시연
	// D3DPRESENT_INTERVAL_DEFAULT : 적절한 간격을 장치가 결정, 보통 모니터 재생율을 따라감
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hwnd,//g_hWnd, //이 부분 문제
		vp,
		&d3dpp,
		&m_pDevice)))
	{
		MSG_BOX("CreateDevice Failed");
		return E_FAIL;
	}

	*ppOut = m_pDevice;

	Safe_AddRef(m_pDevice);

	//m_pDevice->SetTransform(D3DTS_WORLD,) //행렬저장
	//m_pDevice->SetLight()// 빛저장
	//m_pDevice->SetMaterial();
	//m_pDevice->LightEnable(0);


	return S_OK;
}

void CDevice::Render_Begin(void)
{
	m_pDevice->Clear(0,				// 렉트의 개수
		nullptr,		// 렉트 배열의 첫 번째 주소
		D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 125, 125, 125),	// 백 버퍼 텍스처의 색상
		1.f,	// Z버퍼의 초기화 값 (깊이 버퍼) 최종변환된 상대버퍼 (카메라가 볼수있는 가장 깊은 버퍼)
		0);		// 스텐실 초기화 값


	m_pDevice->BeginScene();	// 여기서부터 후면 버퍼에 그리기 시작
}

void CDevice::Render_End()
{
	m_pDevice->EndScene();

	// 1.2번 인자 : D3DSWAPEFFECT_COPY로 옵션이 설정되지 않는한 nullptr
	// 3번 인자 : 출력 대상 윈도우 핸들
	// 4번 인자 :  D3DSWAPEFFECT_COPY로 옵션이 설정되지 않는한 nullptr
	m_pDevice->Present(nullptr, nullptr, nullptr, nullptr);
}


//CDevice* CDevice::Create(HWND _hwnd, UINT _wincx, UINT _wincy)
//{
//	CDevice* pInstance = new CDevice();
//
//	if (FAILED(pInstance->Initialize(_hwnd,  _wincx, _wincy)))
//	{
//		Safe_Release(pInstance);
//		MSG_BOX("디바이스 장치초기화 실패!");
//	}
//
//	return pInstance;
//}

void CDevice::Free()
{
	Safe_Release(m_pDevice);
	Safe_Release(m_pSDK);
}
