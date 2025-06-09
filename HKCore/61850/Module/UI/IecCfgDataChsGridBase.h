#pragma once
#include "IecCfgGridBase.h"

#include "..\CfgDataMngr\IecCfgDataChBase.h"
#include "..\CfgDataMngr\IecCfgChsBase.h"

#define IECCFG_COL_ID_DATA_CHECK   1

class CIecCfgDataChsGridBase : public CIecCfgGridBase
{
public:
	CIecCfgDataChsGridBase();
	virtual ~CIecCfgDataChsGridBase();
	
public:

	virtual BOOL OnCellRButtonUp(const CCellID &idCell);

public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void SetViewChsPath(long nViewChsPath){m_nViewChsPath = nViewChsPath;}

protected:
	long m_nViewChsPath;//zhouhj 20211118 是否显示通道路径信息
};

