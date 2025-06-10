#pragma once
#include "ieccfgviewmainbase.h"

#include "IecCfgGoutDataView.h"
#include "IecCfgGoutDataChsView.h"

class CIecCfgGoutViewMain :
	public CIecCfgViewMainBase
{
public:
	CIecCfgGoutViewMain(void);
	~CIecCfgGoutViewMain(void);

protected:
	virtual void CreateViews(const CRect &rect, CCreateContext *pContext);

};
