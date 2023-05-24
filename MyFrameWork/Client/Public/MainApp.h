#pragma once
#include "Client_Define.h"
#include "Base.h"
// 전방선언 (엔진프로젝트의 게임인스턴스)
BEGIN(Engine)
class CGameInstance; 
END

BEGIN(Client)
class CMainApp final : public CBase
{
private: 
	CMainApp();
	virtual ~CMainApp() = default;



public: 
	HRESULT Initialize();
	void Tick(_float _fDeltaTime);
	HRESULT Render();

public:
	static CMainApp* Create();
	virtual void Free() override;

private:
	HRESULT Open_Level(LEVEL _eNextLevel);

private: 
	LPDIRECT3DDEVICE9 m_pGraphic_Device = { nullptr };

	CGameInstance* m_pGameInstance = { nullptr };

};

END