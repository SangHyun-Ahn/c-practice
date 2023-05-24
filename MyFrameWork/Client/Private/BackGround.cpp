#include "framework.h"
#include "BackGround.h"

CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{

}

CBackGround::CBackGround(const CBackGround& rhs)
	: CGameObject(rhs)
{

}

HRESULT CBackGround::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CBackGround::Initialize(void* pArg)
{
	return S_OK;
}

void CBackGround::Tick(_float _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
}

void CBackGround::Late_Tick(_float _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
}

HRESULT CBackGround::Render()
{
	return S_OK;
}

CBackGround* CBackGround::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBackGround* pInstance = new CBackGround(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		Safe_Release(pInstance);
		MSG_BOX("백그라운드 객체 생성실패!");
	}

	return pInstance;
}

CGameObject* CBackGround::Clone(void* pArg)
{
	CBackGround* pInstance = new CBackGround(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		Safe_Release(pInstance);
		MSG_BOX("백그라운드 객체 클론실패!");
	}

	return pInstance;
}

void CBackGround::Free()
{
	__super::Free();
}
