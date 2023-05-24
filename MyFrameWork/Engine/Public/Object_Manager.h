#pragma once

#include "Base.h"

BEGIN(Engine)

class CObject_Manager final : public CBase
{
	DECLARE_SINGLETON(CObject_Manager)
private:
	CObject_Manager();
	virtual ~CObject_Manager() = default;

public:
	HRESULT Reserve_Manager(_uint _iNumLevels);
	HRESULT Add_Prototype(const wstring& _strPrototypeTag, class CGameObject* _pPrototype);
	HRESULT Add_GameObject(_uint iLevelIndex, const wstring& strLayerTag, const wstring& strPrototypeTag, void* pArg);


	void Tick(_float _fDeltaTime);
	void Late_Tick(_float _fDeltaTime);
	void Clear(_uint _iLevelIndex);

private:
	map<wstring, class CGameObject*>		m_Prototypes;

private:
	_uint						 m_iNumLevels = { 0 };

	//레이어 => 게임오브젝트들이 담긴 리스트를 갖고 있는 객체
	map<wstring, class CLayer*>* m_pLayers = { nullptr };
	typedef map<wstring, class CLayer*>		LAYERS;

private:
	class CGameObject* Find_Prototype(const wstring& _strPrototypeTag);
	class CLayer* Find_Layer(_uint _iLevelIndex,const wstring& _strLayerTag);

public:
	virtual void Free() override;
};

END