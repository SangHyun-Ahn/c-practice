#pragma once
#include "Client_Define.h"
#include "Level.h"
#include "Loader.h"

BEGIN(Client)

class CLevel_Loading final : public CLevel
{
private:
	CLevel_Loading(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_Loading() = default;

public:
	virtual HRESULT Initialize(LEVEL eNextLevel);
	virtual void Tick(_float _fDeltaTime) override;
	virtual void Late_Tick(_float _fDeltaTime) override;
	virtual HRESULT Render() override;

public:
	static CLevel_Loading* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel);
	virtual void Free() override;

private:
	CLoader* m_pLoader = { nullptr };
	LEVEL	m_eNextLevel = { LEVEL_END };
};

END