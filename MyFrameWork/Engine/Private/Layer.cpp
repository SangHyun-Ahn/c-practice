#include "Layer.h"
#include "GameObject.h"


CLayer::CLayer()
{
}

HRESULT CLayer::Add_GameObject(CGameObject* pGameObject)
{
	if (pGameObject == nullptr)
		return E_FAIL;

	m_GameObjects.push_back(pGameObject);

	return S_OK;
}

void CLayer::Tick(_float _fDeltaTime)
{
	for (auto& pGameObject : m_GameObjects)
	{
		if (pGameObject != nullptr)
			pGameObject->Tick(_fDeltaTime);
	}
}

void CLayer::Late_Tick(_float _fDeltaTime)
{
	for (auto& pGameObject : m_GameObjects)
	{
		if (pGameObject != nullptr)
			pGameObject->Late_Tick(_fDeltaTime);
	}
}

CLayer* CLayer::Create()
{
	return new CLayer;
}

void CLayer::Free()
{
	for (auto& pGameObject : m_GameObjects)
	{
		Safe_Release(pGameObject);
	}

	m_GameObjects.clear();
}


