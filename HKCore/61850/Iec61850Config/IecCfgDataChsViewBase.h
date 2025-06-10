#pragma once


#include "resource.h"
#include "..\Module\IecCfgTool\IecCfgFile.h"
#include "..\Module\UI\IecCfgDataChsGridBase.h"

#define IDC_GRID_IECCFG_DATACHS_BASE         21001

#define IDC_IECCFG_DATACHSVIEW_CY_MIN        130

// CIecCfgDataChsViewBase 窗体视图

class CIecCfgDataChsViewBase : public CFormView
{
public:
	virtual void ShowIecCfgDataChs(CIecCfgDataBase *pIecCfgData);
	virtual void CreateChsGrid() = 0;
	virtual void FreeGrid(CRect &rcGrid);
	virtual void FreeGrid();

	virtual void UpdateGrid(BOOL bInitTile = FALSE);
public:
	CIecCfgFile *m_pIecCfgFile;
	CIecCfgDataChsGridBase *m_pIecCfgDataChsGrid;
	CIecCfgDataBase *m_pIecCfgData;    //关联显示的控制块数据对象
	CString  m_strLastRefIecCfgDataType;

protected:
	long    m_nGridTop;
	CIecCfgDataChsViewBase(UINT nIDTemplate);
	virtual ~CIecCfgDataChsViewBase();

	virtual void InitView(CIecCfgDataChsGridBase *pIecCfgDataChsGrid);
	virtual void AdjustSize(int cx, int cy);

public:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

};


