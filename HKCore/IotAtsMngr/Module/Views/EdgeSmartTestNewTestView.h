#pragma once

#include "../../../Module/BaseClass/ExBaseListComboBox.h"
#include "../../../Module/GridCtrl/Gridctrl.h"
#include "../../EdgeEngineProtocolServer/Resource.h"

class CEdgeSmartTestNewTestView : public CFormView
{
	DECLARE_DYNCREATE(CEdgeSmartTestNewTestView)

protected:
	CEdgeSmartTestNewTestView();
	virtual ~CEdgeSmartTestNewTestView();


public:
	enum { IDD = IDD_FORMVIEW_NEWTEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	virtual void OnInitialUpdate();
	virtual void OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);
	void EnableBtns();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//其他消息
	afx_msg LRESULT OnAdjMainWnd(WPARAM wParam, LPARAM lParam);
};


