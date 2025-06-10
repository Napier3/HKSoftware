#pragma once


#include "resource.h"
#include "IecCfgDataChsViewBase.h"
#include "..\Module\UI\IecCfgGoutDataChsGrid.h"

// CIecCfgGoutDataChsView 窗体视图

class CIecCfgGoutDataChsView : public CIecCfgDataChsViewBase
{
	DECLARE_DYNCREATE(CIecCfgGoutDataChsView)

public:
	virtual void CreateChsGrid();

protected:
	CIecCfgGoutDataChsView();           // 动态创建所使用的受保护的构造函数
	virtual ~CIecCfgGoutDataChsView();

public:
	enum { IDD = IDD_IECCFG_GOUTCTRL_CHS_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


