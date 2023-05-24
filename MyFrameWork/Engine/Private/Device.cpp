#include "Device.h"

IMPLEMENT_SINGLETON(CDevice)

CDevice::CDevice() 
	: m_pSDK(nullptr),
	  m_pDevice(nullptr)
{
}




HRESULT CDevice::Initialize(HWND _hwnd, GRAPHICDESC::WINMODE _eMode, _uint _wincx, _uint _wincy, LPDIRECT3DDEVICE9* ppOut)
{
	// 1. ��ġ�� ������ ��ü ����
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	// 2. ��ġ ����
	D3DCAPS9	DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));


	// GetDeviceCaps : ��ġ�� ���� ����(���� ����)�� ������ �Լ�
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, // ������ �������� �⺻ �׷��� ī�带 �ǹ�
		D3DDEVTYPE_HAL,
		&DeviceCaps)))
	{
		MSG_BOX("GetDeviceCaps Failed");
		return E_FAIL;
	}
	
	// ���ؽ� ���μ��� = ������ ��ȯ + ���� ����

	_ulong vp = 0;

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// 3. ��ġ ���� ��ü ����

	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferWidth = _wincx;
	d3dpp.BackBufferHeight = _wincy;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	// D3DSWAPEFFECT_DISCARD : ���� ü�� ��� 
	// D3DSWAPEFFECT_FLIP : ���� �ϳ��� �������鼭 ����ϴ� ���
	// D3DSWAPEFFECT_COPY : ���� ���۸��� ������ ���� ���
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	//�� �κ� ����******************
	d3dpp.hDeviceWindow = _hwnd;//g_hWnd;

	// â���� ������ ���ΰ� ��ü ȭ�� ���� ������ ���ΰ�
	d3dpp.Windowed = _eMode;		// â ���

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	// ��üȭ�� ����� �� ���Ǵ� ������

	// ��üȭ�� ����� �� ����� ������� ���α׷��� ��� ���踦 ��� ������ ���ΰ�
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	// D3DPRESENT_INTERVAL_IMMEDIATE : ��� �ÿ�
	// D3DPRESENT_INTERVAL_DEFAULT : ������ ������ ��ġ�� ����, ���� ����� ������� ����
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hwnd,//g_hWnd, //�� �κ� ����
		vp,
		&d3dpp,
		&m_pDevice)))
	{
		MSG_BOX("CreateDevice Failed");
		return E_FAIL;
	}

	*ppOut = m_pDevice;

	Safe_AddRef(m_pDevice);

	//m_pDevice->SetTransform(D3DTS_WORLD,) //�������
	//m_pDevice->SetLight()// ������
	//m_pDevice->SetMaterial();
	//m_pDevice->LightEnable(0);


	return S_OK;
}

void CDevice::Render_Begin(void)
{
	m_pDevice->Clear(0,				// ��Ʈ�� ����
		nullptr,		// ��Ʈ �迭�� ù ��° �ּ�
		D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 125, 125, 125),	// �� ���� �ؽ�ó�� ����
		1.f,	// Z������ �ʱ�ȭ �� (���� ����) ������ȯ�� ������ (ī�޶� �����ִ� ���� ���� ����)
		0);		// ���ٽ� �ʱ�ȭ ��


	m_pDevice->BeginScene();	// ���⼭���� �ĸ� ���ۿ� �׸��� ����
}

void CDevice::Render_End()
{
	m_pDevice->EndScene();

	// 1.2�� ���� : D3DSWAPEFFECT_COPY�� �ɼ��� �������� �ʴ��� nullptr
	// 3�� ���� : ��� ��� ������ �ڵ�
	// 4�� ���� :  D3DSWAPEFFECT_COPY�� �ɼ��� �������� �ʴ��� nullptr
	m_pDevice->Present(nullptr, nullptr, nullptr, nullptr);
}


//CDevice* CDevice::Create(HWND _hwnd, UINT _wincx, UINT _wincy)
//{
//	CDevice* pInstance = new CDevice();
//
//	if (FAILED(pInstance->Initialize(_hwnd,  _wincx, _wincy)))
//	{
//		Safe_Release(pInstance);
//		MSG_BOX("����̽� ��ġ�ʱ�ȭ ����!");
//	}
//
//	return pInstance;
//}

void CDevice::Free()
{
	Safe_Release(m_pDevice);
	Safe_Release(m_pSDK);
}
