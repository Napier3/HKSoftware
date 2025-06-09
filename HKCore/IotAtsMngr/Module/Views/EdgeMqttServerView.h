#pragma once

#include "../../../Module/BaseClass/ExBaseListComboBox.h"
#include "../../../Module/GridCtrl/Gridctrl.h"
#include "../../EdgeEngineProtocolServer/Resource.h"
#include "../../EdgeEngineProtocolServer/EdgeGrid.h"
#include "../../../Module/WndGroupMngr/XUIAutoAdjTool.h"

class CEdgeMqttServerView : public CFormView, public CXUIAdjItem_Area
{
	DECLARE_DYNCREATE(CEdgeMqttServerView)
private:
	CMqttServerGrid m_oMqttClientList;
	CExBaseList m_oClientList;

protected:
	CEdgeMqttServerView();
	virtual ~CEdgeMqttServerView();
	
public:
	enum { IDD = IDD_FORMVIEW_MQTTSERVER };

public:
	void InitUI();
	void XUI_InitAdjust();
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö
	virtual void OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	LRESULT Process_Connect(WPARAM wParam, LPARAM lParam);
	LRESULT Process_Disconnect(WPARAM wParam, LPARAM lParam);
	LRESULT Process_Subscribe(WPARAM wParam, LPARAM lParam);
	LRESULT Process_Unsubscribe(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};


