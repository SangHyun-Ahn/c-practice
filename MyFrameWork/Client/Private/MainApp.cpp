#include "framework.h"
#include "MainApp.h"
#include "GameInstance.h"
#include "Level_Loading.h"

CMainApp::CMainApp()
	: m_pGameInstance{ CGameInstance::Get_Instance() }
{
	Safe_AddRef(m_pGameInstance);
}


CMainApp* CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp();

	if (FAILED(pInstance->Initialize()))
	{
		Safe_Release(pInstance);
		MSG_BOX("메인앱 생성실패!");
	}

	return pInstance;
}


HRESULT CMainApp::Initialize()
{
	GRAPHICDESC			GraphicDesc;
	ZeroMemory(&GraphicDesc, sizeof GraphicDesc);

	GraphicDesc.hWnd = g_hWnd;
	GraphicDesc.iSizeX = WINCX;
	GraphicDesc.iSizeY = WINCY;
	GraphicDesc.eWinMode = GRAPHICDESC::WINMODE_WINDOW;

	if (FAILED(m_pGameInstance->Initialize_Engine(LEVEL_END, GraphicDesc, &m_pGraphic_Device)))
		return E_FAIL;

	if (FAILED(Open_Level(LEVEL_LOGO)))
		return E_FAIL;

	return S_OK;
}


void CMainApp::Tick(_float _fDeltaTime)
{
	if (m_pGameInstance == nullptr)
		return;

	m_pGameInstance->Tick_Engine(_fDeltaTime);
}




HRESULT CMainApp::Render()
{
	if (m_pGameInstance == nullptr)
		return E_FAIL;

	m_pGameInstance->Render_Begin();

	m_pGameInstance->Render_End();

	return S_OK;
}



void CMainApp::Free()
{

	Safe_Release(m_pGraphic_Device);
	Safe_Release(m_pGameInstance);
	CGameInstance::Release_Engine();
}

HRESULT CMainApp::Open_Level(LEVEL _eNextLevel)
{
	if (m_pGameInstance == nullptr)
		return E_FAIL;

	if (FAILED(m_pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, _eNextLevel))))
		return E_FAIL;

	return S_OK;
}
