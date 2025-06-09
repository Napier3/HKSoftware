#pragma once

#include "..\..\..\Module\DialogBase\DynDialogEx.h"
#include "..\..\..\Module\GridBase\ExBaseListGrid.h"
#include "..\..\..\Module\BaseClass\ExBaseListComboBox.h"
#include "..\..\..\Module\DataMngr\DvmDevice.h"

#include "..\GuideBook\GuideBookDefine.h"

//////////////////////////////////////////////////////////////////////////
//CTestWzdDvHistory
class CTestWzdDvHistory : public CDvmDevice
{
public:
	CTestWzdDvHistory();
	virtual ~CTestWzdDvHistory();

public:
	virtual void InitAfterRead();

	CDvmLogicDevice *m_pTestAppHis;
	CDvmLogicDevice *m_pDeviceAttrHis;

	void OpenHisFile();
	void SaveHisFile();

protected:
	CString GetHisFile();
};


//////////////////////////////////////////////////////////////////////////
//CTestWzdTestAppGrid
class CTestWzdDeviceEditGrid : public CExBaseListGrid
{
public:
	CTestWzdDeviceEditGrid();
	virtual ~CTestWzdDeviceEditGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

};

//////////////////////////////////////////////////////////////////////////
//CTestWzdDvDlg
class CTestWzdDeviceEditDlg : public CDynDialogEx
{
public:
	CTestWzdDeviceEditDlg(CWnd* pParent = NULL); 
	virtual ~CTestWzdDeviceEditDlg();

	CDvmDataset *m_pTestWzdDeviceDef;
	CDvmDataset m_oTestWzdDevice;
	CTestWzdDvHistory m_oTestWzdDvHistory;

protected:
	CDvmLogicDevice *m_pTestWzdDvHis;
	void EnableOkButton();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	CButton m_btnOK;
	CButton m_btnCancel;
	CExBaseListComboBox m_cmbHishory;
	CTestWzdDeviceEditGrid m_gridTestWzdDeviceEdit;
	CString m_strTestWzdTitle;

	void OnCmbHistoryChanged(CExBaseObject *pDvObj);
	void SaveHisFile();

protected:
	virtual void OnOK();
	afx_msg void OnCbnSelchangeCmbHistory();
};
