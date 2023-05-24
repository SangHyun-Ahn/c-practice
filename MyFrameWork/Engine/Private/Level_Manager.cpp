#include "Level_Manager.h"
#include "GameInstance.h"
#include "Level.h"
IMPLEMENT_SINGLETON(CLevel_Manager)

CLevel_Manager::CLevel_Manager()
{

}

HRESULT CLevel_Manager::Open_Level(_uint _iLevelIndex, CLevel* _pLevel)
{
	if (Safe_Release(m_pCurrentLevel) != 0)
	{
		return E_FAIL;
	}

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	pGameInstance->Clear(m_iLevelIndex);

	Safe_Release(pGameInstance);


	//여기선 레퍼런스 카운트 증가시키지 않음
	//매니저에서 보관하는 객체를 다른곳에서 참조하여 쓸때만 레퍼런스카운트 증가시킬것임!
	m_pCurrentLevel = _pLevel;
	m_iLevelIndex = _iLevelIndex;

	return S_OK;
}

void CLevel_Manager::Tick(_float _fDeltaTime)
{
	if (m_pCurrentLevel == nullptr)
		return;

	m_pCurrentLevel->Tick(_fDeltaTime);
}

void CLevel_Manager::Late_Tick(_float _fDeltaTime)
{
	if (m_pCurrentLevel == nullptr)
		return;

	m_pCurrentLevel->Late_Tick(_fDeltaTime);
}

void CLevel_Manager::Free()
{
	Safe_Release(m_pCurrentLevel);

}
