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


	//���⼱ ���۷��� ī��Ʈ ������Ű�� ����
	//�Ŵ������� �����ϴ� ��ü�� �ٸ������� �����Ͽ� ������ ���۷���ī��Ʈ ������ų����!
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
