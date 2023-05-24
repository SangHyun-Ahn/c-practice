#pragma once

#include "Base.h"
BEGIN(Engine)

//기존의 Scene에 해당함
class ENGINE_DLL CLevel abstract : public CBase
{
protected:
	CLevel(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float _fDeltaTime);
	virtual void Late_Tick(_float _fDeltaTime);
	virtual HRESULT Render();

protected:
	LPDIRECT3DDEVICE9		m_pGraphic_Device = { nullptr };

public:
	virtual void Free() override;
};

END