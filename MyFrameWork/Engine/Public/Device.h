#pragma once
#include "Base.h"

BEGIN(Engine)
class CDevice : public CBase
{
	DECLARE_SINGLETON(CDevice)

private:
	CDevice();
	virtual ~CDevice() = default;
	
public:
	//static CDevice* Create(HWND _hwnd, UINT _wincx, UINT _wincy);
	virtual void Free() override;

public:
	HRESULT Initialize(HWND _hwnd, GRAPHICDESC::WINMODE _eMode, _uint _wincx, _uint _wincy, LPDIRECT3DDEVICE9* ppOut);
	void	Render_Begin(void);
	void	Render_End(void);

private:
	LPDIRECT3DDEVICE9		Get_Device(void) { return m_pDevice; }
private:
	LPDIRECT3D9			m_pSDK; // 장치(그래픽 카드 성능) 조사할 객체
	LPDIRECT3DDEVICE9	m_pDevice; // 그래픽 장치를 통한 렌더링을 제어하는 객체

};
END
