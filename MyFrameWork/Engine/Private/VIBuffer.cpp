#include "VIBuffer.h"

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device)
    : CComponent(pGraphic_Device)
{
}

CVIBuffer::CVIBuffer(const CVIBuffer& rhs)
	: CComponent(rhs)
	, m_pVB(rhs.m_pVB)
	, m_pIB(rhs.m_pIB)
	, m_iStride(rhs.m_iStride)
	, m_iNumVertices(rhs.m_iNumVertices)
	, m_dwFVF(rhs.m_dwFVF)
	, m_PrimitiveType(rhs.m_PrimitiveType)
	, m_iNumPrimitive(rhs.m_iNumPrimitive)
{
	Safe_AddRef(m_pVB);
	Safe_AddRef(m_pIB);
}
HRESULT CVIBuffer::Initialize_Prototype()
{
    return S_OK;
}

HRESULT CVIBuffer::Initialize(void* pArg)
{
    return S_OK;
}

HRESULT CVIBuffer::Render()
{
	if (m_pGraphic_Device == nullptr)
		return E_FAIL;

	
	m_pGraphic_Device->SetStreamSource(0, m_pVB, 0, m_iStride);
	m_pGraphic_Device->SetFVF(m_dwFVF);
	m_pGraphic_Device->DrawPrimitive(m_PrimitiveType, 0, m_iNumPrimitive);

	return S_OK;
}

HRESULT CVIBuffer::Create_VertexBuffer()
{
	if (m_pGraphic_Device == nullptr)
		return E_FAIL;

	
	/* 정점(Vertex) 배열을 할당한다. */
	//	D3DPOOL_DEFAULT : 정점배열을 할당하려고 할떄 VRAM에 할당,
	//	D3DPOOL_SYSTEMMEM : 정점배열을 할당하려고 할떄 시스템RAM에 할당,
	//	D3DPOOL_MANAGED : 정점배열을 할당하려고 시스템상황에 맞춰서 알아서함

	//	VRAM이 가장 빠르긴 하지만 VRAM은 가상메모리가 적어 정말 필수적으로 VRAM에 할당해야되는 부분에서 터질수 있음

	if (FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iStride * m_iNumVertices, 0 /* 0으로 하면 정적버퍼배열 , D3DUSAGE_DYNAMIC 으로 하면 동적버퍼배열*/, m_dwFVF, D3DPOOL_MANAGED, &m_pVB, 0)))
		return E_FAIL;

	return S_OK;
}

void CVIBuffer::Free()
{
    __super::Free();

	Safe_Release(m_pVB);
	Safe_Release(m_pIB);
}
