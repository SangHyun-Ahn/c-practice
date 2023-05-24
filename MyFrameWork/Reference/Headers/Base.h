#pragma once
#include "Engine_Define.h"
BEGIN(Engine)
	class ENGINE_DLL CBase abstract
	{
	protected:
		CBase();
		virtual ~CBase() = default;
	
	public:
		//������Ű�� �� �����ǰ�
		_ulong AddRef();
	
		//���ҽ�Ű�� ������ ��
		_ulong Release();
	
	private:
		_ulong m_dwRefCnt = { 0 };
	
	public:
		virtual void Free() PURE;
	};
END
