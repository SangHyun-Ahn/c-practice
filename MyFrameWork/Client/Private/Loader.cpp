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


	lstrcpy(m_szLoading, TEXT("텍스쳐를 로딩 중입니다."));
	Sleep(1500);

	lstrcpy(m_szLoading, TEXT("모델을 로딩 중입니다."));
	Sleep(1500);


	lstrcpy(m_szLoading, TEXT("셰이더를 로딩 중입니다."));
	Sleep(1500);

	lstrcpy(m_szLoading, TEXT("객체원형 로딩 중입니다."));
	
	//백그라운드 프로토타입 생성
	if (FAILED(pGameInstance->Add_Prototype(TEXT("게임오브젝트:백그라운드 프로토타입 생성"),
		CBackGround::Create(m_pGraphic_Device))))
	{
		Safe_Release(pGameInstance);
		return E_FAIL;
	}

	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다."));
	Sleep(1500);

	Safe_Release(pGameInstance);

	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::Loading_GamePlay()
{
	lstrcpy(m_szLoading, TEXT("텍스쳐를 로딩 중입니다."));
	Sleep(1500);

	lstrcpy(m_szLoading, TEXT("모델을 로딩 중입니다."));
	Sleep(1500);

	lstrcpy(m_szLoading, TEXT("셰이더를 로딩 중입니다."));
	Sleep(1500);

	lstrcpy(m_szLoading, TEXT("객체원형 로딩 중입니다."));
	Sleep(1500);

	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다."));

	m_isFinished = true;

	return S_OK;
}

CLoader* CLoader::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel)
{
	CLoader* pInstance = new CLoader(pGraphic_Device);

	if (FAILED(pInstance->Initialize(eNextLevel)))
	{
		Safe_Release(pInstance);
		MSG_BOX("로더 생성실패!");
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
