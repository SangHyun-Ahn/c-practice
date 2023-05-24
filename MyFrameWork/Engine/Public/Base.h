#pragma once
#include "Engine_Define.h"
BEGIN(Engine)
	class ENGINE_DLL CBase abstract
	{
	protected:
		CBase();
		virtual ~CBase() = default;
	
	public:
		//증가시키고 난 이후의값
		_ulong AddRef();
	
		//감소시키기 이전의 값
		_ulong Release();
	
	private:
		_ulong m_dwRefCnt = { 0 };
	
	public:
		virtual void Free() PURE;
	};
END
