#pragma once

#include "..\CfgDataMngr\IecCfgSMVDatas.h"

// CIecCfgSmvTypeComboBox

class CIecCfgSmvTypeComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CIecCfgSmvTypeComboBox)

public:
	CIecCfgSmvTypeComboBox();
	virtual ~CIecCfgSmvTypeComboBox();

	void InitIt();
	void InitIt_SmvIn();
	long GetSmvType();
	void SetSmvType(long nSmvType);

protected:
	DECLARE_MESSAGE_MAP()
};


