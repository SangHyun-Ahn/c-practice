#pragma once

#include "Component_Manager.h"

BEGIN(Engine)
class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance)
private:
	CGameInstance();
	virtual ~CGameInstance() = default;

public: 
	//엔진 이니셜라이즈 (그래픽,사운드 등등)
	HRESULT Initialize_Engine(_uint iNumLevels, const GRAPHICDESC & GraphicDesc, LPDIRECT3DDEVICE9 * ppOut);
	void Tick_Engine(_float _fDeltaTime);
	void Clear(_uint _iLevelIndex);
public:
	//그래픽 디바이스 렌더
	void Render_Begin(void);
	void Render_End(void);

	//레벨매니저관련
public:
	HRESULT Open_Level(_uint _iLevelIndex, class CLevel* _pLevel);

	//오브젝트매니저관련
public:
	HRESULT Add_Prototype(const wstring & strPrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_GameObject(_uint iLevelIndex, const wstring & strLayerTag, const wstring & strPrototypeTag, void* pArg = nullptr);


private:
	class CDevice*		  m_pGraphic_Device = { nullptr };
	class CLevel_Manager* m_pLevel_Manager = { nullptr };
	class CObject_Manager* m_pObject_Manager = { nullptr };
	class CComponent_Manager* m_pComponent_Manager = { nullptr };

public:
	static void Release_Engine();
	virtual void Free() override;

};
END

