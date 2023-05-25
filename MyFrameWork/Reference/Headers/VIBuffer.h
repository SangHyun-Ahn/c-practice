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
		_uint								m_iStride = { 0 }; // ���� �ϳ��� byteũ�� //
		_uint								m_iNumVertices = { 0 }; //���� ����
		_ulong								m_dwFVF = { 0 }; // ������ �� ������ �̷�����ִ��� 
		D3DPRIMITIVETYPE					m_PrimitiveType; //�׸������ϴ� �⺻���� Ÿ��
		_uint								m_iNumPrimitive = { 0 }; //�׸������ϴ� �⺻���� ����
	
	protected:
		HRESULT Create_VertexBuffer();

	
	public:
		virtual CComponent* Clone(void* pArg) PURE;
		virtual void Free() override;
};

END
