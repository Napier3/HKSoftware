#pragma once

#include "resource.h"
#include "..\Module\IecCfgTool\IecCfgFile.h"
#include "IecCfgDataViewBase.h"
#include "..\Module\UI\IecCfgGoutDataGrid.h"

// class CIecCfgGoutDataChsView;

// CIecCfgGoutDataView ������ͼ

class CIecCfgGoutDataView : public CIecCfgDataViewBase
{
	DECLARE_DYNCREATE(CIecCfgGoutDataView)

public:
	virtual CIecCfgDatasBase* GetIecCfgDatas();
	virtual void CreateIecCfgDataGrid();

protected:
	CIecCfgGoutDataView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIecCfgGoutDataView();

public:
	enum { IDD = IDD_IECCFG_GOUTCTRL_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
// 	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


