#include "..\Public\VIBuffer_Rect.h"

CVIBuffer_Rect::CVIBuffer_Rect(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_Rect::CVIBuffer_Rect(const CVIBuffer_Rect& rhs)
	: CVIBuffer(rhs)
{
}

HRESULT CVIBuffer_Rect::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	m_iNumVertices = 6; // ��������
	m_iStride = sizeof(VTXPOSTEX); // ������ (��������ü��ŭ�� ũ��)
	// m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX2 | D3DFVF_TEXCOORDSIZE2(0) | D3DFVF_TEXCOORDSIZE3(1);
	//FVF: Flexible VerTex Format = > ������ �� ������ ��������ִ��� �˷���
	//D3DFVF_TEX1 = > �����ϳ��� �ؽ����� Ư�� ������ �����ϱ����� 1���� �������ִ� <�ִ� 8�������� ������ ����������>
	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0); // 0��° Texcoord�� ������� 2�̴�.
	m_PrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = 2;

	if (FAILED(__super::Create_VertexBuffer()))
		return E_FAIL;

	VTXPOSTEX* pVertices = { nullptr };


	//**Lock() ���� �迭�� ���� �ٲٱ� ���� ����
	//(�����Ͽ� ���� �ٲٴ� ���� �ٸ� �����尡 ����� �����ϴ°� �������� �湮�� ����شٰ� �����ϸ� ���ذ� ����)
	//	** UnLock() ���� �迭�� ���� �ٲٰ� �� ����� ���־����

	//	�������۹迭�� ��, ������ָ� �������� ���� ��������.��� �������۹迭�� �⺻������ �������ӵ��� ����
	//	�������۴� �⺻���� �������ӵ��� �������� ��, ����� ȿ���� ����.
	//	dx9���� �������۹迭�� �⺻������ ���� ������

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].vPosition = _float3(-0.5f, 0.5f, 0.f);
	pVertices[0].vTexcoord = _float2(0.0f, 0.f);

	pVertices[1].vPosition = _float3(0.5f, 0.5f, 0.f);
	pVertices[1].vTexcoord = _float2(1.0f, 0.f);

	pVertices[2].vPosition = _float3(0.5f, -0.5f, 0.f);
	pVertices[2].vTexcoord = _float2(1.0f, 1.f);

	pVertices[3].vPosition = _float3(-0.5f, 0.5f, 0.f);
	pVertices[3].vTexcoord = _float2(0.0f, 0.f);

	pVertices[4].vPosition = _float3(0.5f, -0.5f, 0.f);
	pVertices[4].vTexcoord = _float2(1.0f, 1.f);

	pVertices[5].vPosition = _float3(-0.5f, -0.5f, 0.f);
	pVertices[5].vTexcoord = _float2(0.0f, 1.f);

	m_pVB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_Rect::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CVIBuffer_Rect* CVIBuffer_Rect::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	return nullptr;
}

CComponent* CVIBuffer_Rect::Clone(void* pArg)
{
	return nullptr;
}

void CVIBuffer_Rect::Free()
{
	__super::Free();
}
