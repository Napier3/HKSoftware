#pragma once

#include "ieccfgviewmainbase.h"

#include "IecCfgSmvDataView.h"
#include "IecCfgSmvDataChsView.h"

#include "..\Module\IecCfgTool\IecCfgFile.h"


class CIecCfgSmvViewMain : public CIecCfgViewMainBase //	public CIecCfgDlgMainBase
{
public:
	CIecCfgSmvViewMain(void);
	~CIecCfgSmvViewMain(void);

protected:
	virtual void CreateViews(const CRect &rect, CCreateContext *pContext);
};
