#pragma once

#include "Base.h"

BEGIN(Engine)

class CLevel_Manager final : public CBase
{
	DECLARE_SINGLETON(CLevel_Manager)
private:
	CLevel_Manager();
	virtual ~CLevel_Manager() = default;

public:
	HRESULT Open_Level(_uint iLevelIndex, class CLevel* pLevel);
	void Tick(_float _fDeltaTime);
	void Late_Tick(_float _fDeltaTime);


private:
	class CLevel* m_pCurrentLevel = { nullptr };
	_uint m_iLevelIndex = { 0 };

public:
	virtual void Free() override;
};

END