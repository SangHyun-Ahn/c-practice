#include "Object_Manager.h"
#include "Layer.h"
#include "GameObject.h"

IMPLEMENT_SINGLETON(CObject_Manager)

CObject_Manager::CObject_Manager()
{
}

//클라에서 레벨이 몇개인지 매개변수로 받음
HRESULT CObject_Manager::Reserve_Manager(_uint _iNumLevels)
{
	if (m_pLayers != nullptr)
		return E_FAIL;

	m_iNumLevels = _iNumLevels;
	//레벨 개수만큼 레이어배열 동적할당
	//각각의 레벨에서 사용할 레이어들을 분리
	m_pLayers = new LAYERS[_iNumLevels];

	return S_OK;
}

HRESULT CObject_Manager::Add_Prototype(const wstring& _strPrototypeTag, CGameObject* _pPrototype)
{
	/* 중복된 키로 추가하면 안되니까.*/
	if (Find_Prototype(_strPrototypeTag) != nullptr)
		return E_FAIL;

	m_Prototypes.emplace(_strPrototypeTag, _pPrototype);

	return S_OK;
}

HRESULT CObject_Manager::Add_GameObject(_uint iLevelIndex, const wstring& strLayerTag, const wstring& strPrototypeTag, void* pArg)
{
	//오브젝트의 원형검색
	CGameObject* pPrototype = Find_Prototype(strPrototypeTag);
	
	if (pPrototype == nullptr)
		return E_FAIL;

	//클론할때 원형을 만들때 세팅한 값 이외의 추가적인 값을 세팅할 수 있도록
	//void* Arg을 클론함수의 인자로 받는다.
	CGameObject* pObj = pPrototype->Clone(pArg);

	if (pObj == nullptr)
		return E_FAIL;

	//사본객체를 추가하기위해 인자로 받은 레벨의 레이어를 찾음
	CLayer* pLayer = Find_Layer(iLevelIndex, strLayerTag);

	//위에서 받은 레이어가 존재하지 않을때는 최초에 레이어 생성후 사본객체추가함
	if (pLayer == nullptr)
	{
		pLayer = CLayer::Create();

		if (pLayer == nullptr)
			return E_FAIL;

		pLayer->Add_GameObject(pObj);

		m_pLayers[iLevelIndex].emplace(strLayerTag, pLayer);
	}
	else //그렇지않으면 그냥 해당레이어에 사본객체추가
		pLayer->Add_GameObject(pObj);

	return S_OK;
}

void CObject_Manager::Tick(_float _fDeltaTime)
{
	for (_uint i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			if (nullptr != Pair.second)
				Pair.second->Tick(_fDeltaTime);

		}
	}
}

void CObject_Manager::Late_Tick(_float _fDeltaTime)
{
	for (_uint i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			if (nullptr != Pair.second)
				Pair.second->Late_Tick(_fDeltaTime);
		}
	}
}

void CObject_Manager::Clear(_uint _iLevelIndex)
{
	if (_iLevelIndex >= m_iNumLevels)
		return;

	for (auto& Pair : m_pLayers[_iLevelIndex])
		Safe_Release(Pair.second);

	m_pLayers[_iLevelIndex].clear();

}



CGameObject* CObject_Manager::Find_Prototype(const wstring& _strPrototypeTag)
{
	auto	iter = m_Prototypes.find(_strPrototypeTag);

	if (iter == m_Prototypes.end())
		return nullptr;

	return iter->second;
}

CLayer* CObject_Manager::Find_Layer(_uint _iLevelIndex, const wstring& _strLayerTag)
{
	if (_iLevelIndex >= m_iNumLevels)
		return nullptr;

	auto	iter = m_pLayers[_iLevelIndex].find(_strLayerTag);

	if (iter == m_pLayers[_iLevelIndex].end())
		return nullptr;

	return iter->second;
}

void CObject_Manager::Free()
{
	for (_uint i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			Safe_Release(Pair.second);
		}
		m_pLayers[i].clear();
	}
	Safe_Delete_Array(m_pLayers);


	for (auto& Pair : m_Prototypes)
		Safe_Release(Pair.second);

	m_Prototypes.clear();

}
