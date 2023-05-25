#include "GameInstance.h"
#include "Device.h"
#include "Level_Manager.h"
#include "Object_Manager.h"


IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()
	: m_pGraphic_Device{ CDevice::Get_Instance() }
	, m_pLevel_Manager{ CLevel_Manager::Get_Instance() }
	, m_pObject_Manager{ CObject_Manager::Get_Instance() }
	, m_pComponent_Manager{ CComponent_Manager::Get_Instance() }
{
	Safe_AddRef(m_pComponent_Manager);
	Safe_AddRef(m_pObject_Manager);
	Safe_AddRef(m_pLevel_Manager);
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CGameInstance::Initialize_Engine(_uint iNumLevels, const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut)
{
	if (m_pGraphic_Device == nullptr)
		return E_FAIL;

	if (FAILED(m_pGraphic_Device->Initialize(GraphicDesc.hWnd, GraphicDesc.eWinMode, GraphicDesc.iSizeX, GraphicDesc.iSizeY, ppOut)))
		return E_FAIL;

	if (FAILED(m_pObject_Manager->Reserve_Manager(iNumLevels)))
		return E_FAIL;

	return S_OK;
}

void CGameInstance::Tick_Engine(_float _fDeltaTime)
{
	if (m_pLevel_Manager == nullptr ||
		m_pObject_Manager == nullptr ||
		m_pComponent_Manager == nullptr )
		return;

	m_pObject_Manager->Tick(_fDeltaTime);
	m_pLevel_Manager->Tick(_fDeltaTime);

	m_pObject_Manager->Late_Tick(_fDeltaTime);
	m_pLevel_Manager->Late_Tick(_fDeltaTime);
}

void CGameInstance::Clear(_uint _iLevelIndex)
{
	if (m_pObject_Manager == nullptr)
		return;

	m_pObject_Manager->Clear(_iLevelIndex);

}

void CGameInstance::Render_Begin()
{
	if (m_pGraphic_Device == nullptr)
		return;

	m_pGraphic_Device->Render_Begin();
}

void CGameInstance::Render_End(void)
{
	if (m_pGraphic_Device == nullptr)
		return;

	m_pGraphic_Device->Render_End();
}

HRESULT CGameInstance::Open_Level(_uint _iLevelIndex, CLevel* _pLevel)
{
	if (m_pLevel_Manager == nullptr)
		return E_FAIL;

	return m_pLevel_Manager->Open_Level(_iLevelIndex, _pLevel);	
}

HRESULT CGameInstance::Add_Prototype(const wstring& strPrototypeTag, CGameObject* pPrototype)
{
	if (m_pObject_Manager == nullptr)
		return E_FAIL;	

	return m_pObject_Manager->Add_Prototype(strPrototypeTag, pPrototype);
}

HRESULT CGameInstance::Add_GameObject(_uint iLevelIndex, const wstring& strLayerTag, const wstring& strPrototypeTag, void* pArg)
{
	if (m_pObject_Manager == nullptr)
		return E_FAIL;


	return m_pObject_Manager->Add_GameObject(iLevelIndex, strLayerTag, strPrototypeTag, pArg);
}

void CGameInstance::Release_Engine()
{
	CGameInstance::Get_Instance()->Destroy_Instance();
	
	CObject_Manager::Get_Instance()->Destroy_Instance();

	CComponent_Manager::Get_Instance()->Destroy_Instance();

	CLevel_Manager::Get_Instance()->Destroy_Instance();

	CDevice::Get_Instance()->Destroy_Instance();
}


void CGameInstance::Free()
{
	Safe_Release(m_pComponent_Manager);
	Safe_Release(m_pObject_Manager);
	Safe_Release(m_pLevel_Manager);
	Safe_Release(m_pGraphic_Device);
}