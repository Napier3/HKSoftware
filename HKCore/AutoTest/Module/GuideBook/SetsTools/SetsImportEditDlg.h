#pragma once

#include "SetsFileToolInterface.h"
#include "../../../../Module/DialogBase/DynDialogEx.h"
#include "../../../../Module/GridBase/ExBaseListGrid.h"

#define XIDC_GRID_FILE   2350
#define XIDC_GRID_GB     2351
#define XIDC_DS_SEL_SETS     2352
#define XIDC_DS_SEL_ENA     2353
#define XIDC_DS_SEL_DEV_PARAS     2354
#define XIDC_DS_SEL_CTRL_WORD     2355
#define XIDC_DS_SEL_OUT_MATR     2356
#define XIDC_BTN_OK     2357
#define XIDC_BTN_TIME_S_TO_MS     2358

class CSetsImportEditGrid_File : public CExBaseListGrid
{
public:
	CSetsImportEditGrid_File();
	virtual ~CSetsImportEditGrid_File();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};

class CSetsImportEditGrid_Gb : public CExBaseListGrid
{
public:
	CSetsImportEditGrid_Gb();
	virtual ~CSetsImportEditGrid_Gb();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};




// CSetsImportEditDlg 对话框

class CSetsImportEditDlg : public CDynDialogEx
{
public:
	CSetsImportEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetsImportEditDlg();

	CSetsFileToolInterface *m_pStesFileTool;
	void ShowSets();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedDsSelSets();
	afx_msg void OnBnClickedDsSelEna();
	afx_msg void OnBnClickedDsSelDevParas();
	afx_msg void OnBnClickedDsSelCtrlWord();
	afx_msg void OnBnClickedDsSelOutMatr();
	afx_msg void OnBnClickedTime_S_to_ms();
	virtual BOOL OnInitDialog();
	CSetsImportEditGrid_File m_gridDsFile;
	CSetsImportEditGrid_Gb m_gridDsGb;
	CButton m_btnSets;
	CButton m_btnEna;
	CButton m_btnParameter;
	CButton m_btnCtrl;
	CButton m_btnOutMatr;
	CButton m_btnOK;
	CButton m_btnTimeToMs;
	int m_nSetsType;
};
