#pragma once

#include "Client_Define.h"
#include "GameObject.h"

BEGIN(Client)

class CBackGround final : public CGameObject
{
protected:
	CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device);
	CBackGround(const CBackGround& rhs);
	virtual ~CBackGround() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Tick(_float _fDeltaTime);
	virtual void Late_Tick(_float _fDeltaTime);
	virtual HRESULT Render();

public:
	static CBackGround* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END