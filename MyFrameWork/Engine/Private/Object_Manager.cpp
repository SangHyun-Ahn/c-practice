#include "Object_Manager.h"
#include "Layer.h"
#include "GameObject.h"

IMPLEMENT_SINGLETON(CObject_Manager)

CObject_Manager::CObject_Manager()
{
}

//Ŭ�󿡼� ������ ����� �Ű������� ����
HRESULT CObject_Manager::Reserve_Manager(_uint _iNumLevels)
{
	if (m_pLayers != nullptr)
		return E_FAIL;

	m_iNumLevels = _iNumLevels;
	//���� ������ŭ ���̾�迭 �����Ҵ�
	//������ �������� ����� ���̾���� �и�
	m_pLayers = new LAYERS[_iNumLevels];

	return S_OK;
}

HRESULT CObject_Manager::Add_Prototype(const wstring& _strPrototypeTag, CGameObject* _pPrototype)
{
	/* �ߺ��� Ű�� �߰��ϸ� �ȵǴϱ�.*/
	if (Find_Prototype(_strPrototypeTag) != nullptr)
		return E_FAIL;

	m_Prototypes.emplace(_strPrototypeTag, _pPrototype);

	return S_OK;
}

HRESULT CObject_Manager::Add_GameObject(_uint iLevelIndex, const wstring& strLayerTag, const wstring& strPrototypeTag, void* pArg)
{
	//������Ʈ�� �����˻�
	CGameObject* pPrototype = Find_Prototype(strPrototypeTag);
	
	if (pPrototype == nullptr)
		return E_FAIL;

	//Ŭ���Ҷ� ������ ���鶧 ������ �� �̿��� �߰����� ���� ������ �� �ֵ���
	//void* Arg�� Ŭ���Լ��� ���ڷ� �޴´�.
	CGameObject* pObj = pPrototype->Clone(pArg);

	if (pObj == nullptr)
		return E_FAIL;

	//�纻��ü�� �߰��ϱ����� ���ڷ� ���� ������ ���̾ ã��
	CLayer* pLayer = Find_Layer(iLevelIndex, strLayerTag);

	//������ ���� ���̾ �������� �������� ���ʿ� ���̾� ������ �纻��ü�߰���
	if (pLayer == nullptr)
	{
		pLayer = CLayer::Create();

		if (pLayer == nullptr)
			return E_FAIL;

		pLayer->Add_GameObject(pObj);

		m_pLayers[iLevelIndex].emplace(strLayerTag, pLayer);
	}
	else //�׷��������� �׳� �ش緹�̾ �纻��ü�߰�
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
