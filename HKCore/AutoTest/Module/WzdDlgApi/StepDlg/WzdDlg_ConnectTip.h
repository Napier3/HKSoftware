#pragma once
#include "WzdDlgBase.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../StepCtrl/WzdDlgStyleGrid.h"
#include "../StepCtrl/WzdDlgButton.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgDevice.h"

class CConnectSVGrid : public CWzdDlgStyleGrid
{
public:
	CConnectSVGrid(){}
	virtual ~CConnectSVGrid(){}

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow =TRUE);
};

class CConnectGsGrid : public CWzdDlgStyleGrid
{
public:
	CConnectGsGrid(){}
	virtual ~CConnectGsGrid(){}

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow =TRUE);
};

class CWzdDlg_ConnectTip : public CWzdDlgBase
{
	DECLARE_DYNAMIC(CWzdDlg_ConnectTip)
private:
	CStatic m_txtDevice;
	CStatic m_txtFactor;
	CStatic m_txtFactor2;
	CStatic m_txtIP;
	CStatic m_txtIP2;
	CStatic m_txtConnect;
	CStatic m_txtSV;
	CStatic m_txtGOOSE;
	CStatic m_txtInfo;

	CConnectSVGrid m_gridSV;
	CConnectGsGrid m_gridGs;

	CWzdDlgButton m_btnJumpFactory;
	CWzdDlgButton m_btnJumpIP;
	CWzdDlgButton m_btnJumpSV;
	CWzdDlgButton m_btnJumpGs;

	CIecCfgDevice* m_pIecFileDevice;

	CString m_strParameterMd5;
	CString m_strSettingMd5;
	CString m_strEnaMd5;

public:
	CWzdDlg_ConnectTip(CWnd* pParent = NULL);
	virtual ~CWzdDlg_ConnectTip();

	enum { IDD = IDD_CONNECTTIP_DIALOG };

protected:
	virtual void XUI_InitAdjust();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	virtual void OnInitialUpdate();
	void SetAddress(const CString& strIP);
	void SetFactory(const CString& strFactory);
	void UpdateGrid(CExBaseObject* pIecFileDevice);
	void SetMd5(const CString& strParameterMd5, const CString& strSettingMd5, const CString& strEnaMd5);
	virtual BOOL DoNext();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedBtnFactoryJump();
	afx_msg void OnBnClickedBtnIpJump();
	afx_msg void OnBnClickedBtnSvJump();
	afx_msg void OnBnClickedBtnGsJump();
};