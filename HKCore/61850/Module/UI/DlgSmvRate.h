#pragma once

#include "..\..\..\Module\DialogBase\DynDialogEx.h"

#include "SmvRateGrid.h"

#include "afxwin.h"
// CDlgSmvRate �Ի���

#define IECFG_IDC_GRID_SMVRATE             8700
#define IECFG_IDC_BUTTON_CHK_ALL           8715

class CDlgSmvRate : public CDynDialogEx
{
public:
	CDlgSmvRate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSmvRate();

	void CreateControls();
	
	void ShowSmvRate();
	void SaveSmvRate();

	void InitDialog();
	void InitIecCfgSmvRates(CIecCfgSmvRates *pIecCfgSmvRates);
	CIecCfgSmvRates* GetIecCfgSmvRates()	{	return m_pCloneIecCfgSmvRates;	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	CButton m_btnOK;
	CButton m_btnCancel;
	CButton m_btnCheckAll;
	CSmvRateGrid m_grid;
	BOOL m_bEditAll;

private:
	CIecCfgSmvRates *m_pCloneIecCfgSmvRates;

protected:
	virtual void OnOK();
	virtual void OnCancel();

public:

};
