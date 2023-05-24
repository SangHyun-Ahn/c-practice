#pragma once

#include "Client_Define.h"
#include "Base.h"

/* 다음레벨에 대한 자원을 생성하는 역활을 멀티스레드를 생성하여 수행한다. */

BEGIN(Client)

class CLoader final : public CBase
{
private:
	CLoader(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLoader() = default;

public: 
	const _tchar* Get_LoadingText() const { return m_szLoading; }
	_bool Get_Finished()			const { return m_isFinished; }

public:
	HRESULT Initialize(LEVEL eNextLevel);
	HRESULT LoadingForNextLevel();

private:
	LPDIRECT3DDEVICE9		m_pGraphic_Device = { nullptr };
	HANDLE					m_hThread = { 0 };
	CRITICAL_SECTION		m_CriticalSection;
	LEVEL					m_eNextLevel = { LEVEL_END };

	_bool					m_isFinished = { false };
	_tchar					m_szLoading[MAX_PATH] = TEXT("");

private:
	HRESULT Loading_Logo();
	HRESULT Loading_GamePlay();

public:
	static CLoader* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel);
	virtual void Free() override;
};

END