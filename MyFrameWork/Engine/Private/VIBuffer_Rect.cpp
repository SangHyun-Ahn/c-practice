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

	m_iNumVertices = 6; // 정점갯수
	m_iStride = sizeof(VTXPOSTEX); // 사이즈 (정점구조체만큼의 크기)
	// m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX2 | D3DFVF_TEXCOORDSIZE2(0) | D3DFVF_TEXCOORDSIZE3(1);
	//FVF: Flexible VerTex Format = > 정점이 어떤어떤 정보로 만들어져있는지 알려줌
	//D3DFVF_TEX1 = > 정점하나는 텍스쳐의 특정 부위를 참고하기위해 1가지 가지고있다 <최대 8가지까지 가지고 있을수있음>
	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0); // 0번째 Texcoord의 사이즈는 2이다.
	m_PrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = 2;

	if (FAILED(__super::Create_VertexBuffer()))
		return E_FAIL;

	VTXPOSTEX* pVertices = { nullptr };


	//**Lock() 정점 배열의 값을 바꾸기 위해 해줌
	//(접근하여 값을 바꾸는 동안 다른 쓰레드가 여기로 접근하는걸 막기위해 방문을 잠궈준다고 생각하면 이해가 편함)
	//	** UnLock() 정점 배열의 값을 바꾸고 꼭 언락을 해주어야함

	//	정적버퍼배열을 락, 언락해주면 프레임이 많이 떨어진다.대신 정적버퍼배열은 기본적으로 렌더링속도가 빠름
	//	동적버퍼는 기본적인 렌더링속도는 느리지만 락, 언락의 효율이 높다.
	//	dx9에선 정적버퍼배열로 기본적으로 만들어서 쓸것임

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
