#pragma once
#include "IECCfgGridBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgDataChBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgChsBase.h"

#define IECCFG_COL_ID_DATA_CHECK   1

class CIECCfgDataChsGridBase : public CIECCfgGridBase
{
public:
	CIECCfgDataChsGridBase();
	virtual ~CIECCfgDataChsGridBase();
	
public:
	void AttachRefDataGrid(CIECCfgGridBase *pRefDataGrid) {	m_pRefDataGrid = pRefDataGrid;}
	virtual BOOL OnCellRButtonUp(const CCellID &idCell);

public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void SetViewChsPath(long nViewChsPath){m_nViewChsPath = nViewChsPath;}

protected:
	CIECCfgGridBase *m_pRefDataGrid;
	long m_nViewChsPath;//zhouhj 20211118 是否显示通道路径信息
};

