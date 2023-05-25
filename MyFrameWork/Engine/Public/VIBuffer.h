#pragma once
#include "Component.h"

BEGIN(Engine)
class ENGINE_DLL CVIBuffer abstract : public CComponent
{
	protected:
		CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device);
		CVIBuffer(const CVIBuffer& rhs);
		virtual ~CVIBuffer() = default;
	
	public:
		virtual HRESULT Initialize_Prototype();
		virtual HRESULT Initialize(void* pArg);
		virtual HRESULT Render();

	protected:
		LPDIRECT3DVERTEXBUFFER9				m_pVB = { nullptr };
		LPDIRECT3DINDEXBUFFER9				m_pIB = { nullptr };

	protected:
		_uint								m_iStride = { 0 }; // 정점 하나의 byte크기 //
		_uint								m_iNumVertices = { 0 }; //정점 갯수
		_ulong								m_dwFVF = { 0 }; // 정점이 어떤어떤 정보로 이루어져있는지 
		D3DPRIMITIVETYPE					m_PrimitiveType; //그리고자하는 기본형의 타입
		_uint								m_iNumPrimitive = { 0 }; //그리고자하는 기본형이 갯수
	
	protected:
		HRESULT Create_VertexBuffer();

	
	public:
		virtual CComponent* Clone(void* pArg) PURE;
		virtual void Free() override;
};

END
