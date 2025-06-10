#pragma once
#include "ieccfgviewmainbase.h"

#include "IecCfgGinDataView.h"
#include "IecCfgGinDataChsView.h"

class CIecCfgGinViewMain :
	public CIecCfgViewMainBase
{
public:
	CIecCfgGinViewMain(void);
	~CIecCfgGinViewMain(void);

protected:
	virtual void CreateViews(const CRect &rect, CCreateContext *pContext);

};
