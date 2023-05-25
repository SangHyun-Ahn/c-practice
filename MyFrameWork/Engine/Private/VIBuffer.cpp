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

	
	/* ����(Vertex) �迭�� �Ҵ��Ѵ�. */
	//	D3DPOOL_DEFAULT : �����迭�� �Ҵ��Ϸ��� �ҋ� VRAM�� �Ҵ�,
	//	D3DPOOL_SYSTEMMEM : �����迭�� �Ҵ��Ϸ��� �ҋ� �ý���RAM�� �Ҵ�,
	//	D3DPOOL_MANAGED : �����迭�� �Ҵ��Ϸ��� �ý��ۻ�Ȳ�� ���缭 �˾Ƽ���

	//	VRAM�� ���� ������ ������ VRAM�� ����޸𸮰� ���� ���� �ʼ������� VRAM�� �Ҵ��ؾߵǴ� �κп��� ������ ����

	if (FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iStride * m_iNumVertices, 0 /* 0���� �ϸ� �������۹迭 , D3DUSAGE_DYNAMIC ���� �ϸ� �������۹迭*/, m_dwFVF, D3DPOOL_MANAGED, &m_pVB, 0)))
		return E_FAIL;

	return S_OK;
}

void CVIBuffer::Free()
{
    __super::Free();

	Safe_Release(m_pVB);
	Safe_Release(m_pIB);
}
