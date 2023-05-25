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
	//���� �̴ϼȶ����� (�׷���,���� ���)
	HRESULT Initialize_Engine(_uint iNumLevels, const GRAPHICDESC & GraphicDesc, LPDIRECT3DDEVICE9 * ppOut);
	void Tick_Engine(_float _fDeltaTime);
	void Clear(_uint _iLevelIndex);
public:
	//�׷��� ����̽� ����
	void Render_Begin(void);
	void Render_End(void);

	//�����Ŵ�������
public:
	HRESULT Open_Level(_uint _iLevelIndex, class CLevel* _pLevel);

	//������Ʈ�Ŵ�������
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

