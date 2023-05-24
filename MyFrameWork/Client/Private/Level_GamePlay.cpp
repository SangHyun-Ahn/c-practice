#include "framework.h"
#include "Level_GamePlay.h"

CLevel_GamePlay::CLevel_GamePlay(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel(pGraphic_Device)
{
}

HRESULT CLevel_GamePlay::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	return S_OK;
}

void CLevel_GamePlay::Tick(_float _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
}

void CLevel_GamePlay::Late_Tick(_float _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);

	SetWindowText(g_hWnd, TEXT("인게임"));
}

HRESULT CLevel_GamePlay::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

CLevel_GamePlay* CLevel_GamePlay::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_GamePlay* pInstance = new CLevel_GamePlay(pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		Safe_Release(pInstance);
		MSG_BOX("게임플레이레벨 생성실패!");
	}

	return pInstance;
}

void CLevel_GamePlay::Free()
{
	__super::Free();
}
