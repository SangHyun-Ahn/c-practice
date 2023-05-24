#include "framework.h"
#include "Loader.h"
#include "GameInstance.h"
#include "BackGround.h"

CLoader::CLoader(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}


unsigned int APIENTRY ThreadEntry(void* pArg)
{
	CLoader* pLoader = (CLoader*)pArg;

	if (FAILED(pLoader->LoadingForNextLevel()))
		return 1;

	return 0;
}


HRESULT CLoader::Initialize(LEVEL eNextLevel)
{
	m_eNextLevel = eNextLevel;

	InitializeCriticalSection(&m_CriticalSection);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadEntry, this, 0, nullptr);

	if (m_hThread == 0)
		return E_FAIL;

	return S_OK;
}

HRESULT CLoader::LoadingForNextLevel()
{
	EnterCriticalSection(&m_CriticalSection);

	HRESULT		hr = { 0 };

	switch (m_eNextLevel)
	{
	case LEVEL_LOGO:
		hr = Loading_Logo();
		break;
	case LEVEL_GAMEPLAY:
		hr = Loading_GamePlay();
		break;
	}

	if (FAILED(hr))
	{
		LeaveCriticalSection(&m_CriticalSection);
		return E_FAIL;
	}
	else
	{
		LeaveCriticalSection(&m_CriticalSection);
		return S_OK;
	}
}

HRESULT CLoader::Loading_Logo()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);


	lstrcpy(m_szLoading, TEXT("�ؽ��ĸ� �ε� ���Դϴ�."));
	Sleep(1500);

	lstrcpy(m_szLoading, TEXT("���� �ε� ���Դϴ�."));
	Sleep(1500);


	lstrcpy(m_szLoading, TEXT("���̴��� �ε� ���Դϴ�."));
	Sleep(1500);

	lstrcpy(m_szLoading, TEXT("��ü���� �ε� ���Դϴ�."));
	
	//��׶��� ������Ÿ�� ����
	if (FAILED(pGameInstance->Add_Prototype(TEXT("���ӿ�����Ʈ:��׶��� ������Ÿ�� ����"),
		CBackGround::Create(m_pGraphic_Device))))
	{
		Safe_Release(pGameInstance);
		return E_FAIL;
	}

	lstrcpy(m_szLoading, TEXT("�ε��� �Ϸ�Ǿ����ϴ�."));
	Sleep(1500);

	Safe_Release(pGameInstance);

	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::Loading_GamePlay()
{
	lstrcpy(m_szLoading, TEXT("�ؽ��ĸ� �ε� ���Դϴ�."));
	Sleep(1500);

	lstrcpy(m_szLoading, TEXT("���� �ε� ���Դϴ�."));
	Sleep(1500);

	lstrcpy(m_szLoading, TEXT("���̴��� �ε� ���Դϴ�."));
	Sleep(1500);

	lstrcpy(m_szLoading, TEXT("��ü���� �ε� ���Դϴ�."));
	Sleep(1500);

	lstrcpy(m_szLoading, TEXT("�ε��� �Ϸ�Ǿ����ϴ�."));

	m_isFinished = true;

	return S_OK;
}

CLoader* CLoader::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel)
{
	CLoader* pInstance = new CLoader(pGraphic_Device);

	if (FAILED(pInstance->Initialize(eNextLevel)))
	{
		Safe_Release(pInstance);
		MSG_BOX("�δ� ��������!");
	}

	return pInstance;
}

void CLoader::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);

	CloseHandle(m_hThread);

	DeleteObject(m_hThread);

	DeleteCriticalSection(&m_CriticalSection);

	Safe_Release(m_pGraphic_Device);
}
