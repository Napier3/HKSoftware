#pragma once
#include "../StepCtrl/WzdDlgStyleGrid.h"
#include "../../GuideBook/DataSet.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../StepCtrl/UIDrawer.h"
#define XIDC_SET_GRID 2380
class CConfigSetGrid: public CWzdDlgStyleGrid
{
public:
	CConfigSetGrid(void);
	~CConfigSetGrid(void);
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};
// CWzd_ConfigSetDlg 对话框

class CWzd_ConfigSetDlg : public CUIDialog
{
	DECLARE_DYNAMIC(CWzd_ConfigSetDlg)

public:
	CUIButton m_btnOK;
	CUIButton m_btnCancel;

	CWzd_ConfigSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWzd_ConfigSetDlg();

// 对话框数据
	enum { IDD = IDD_TEST_SET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void SetGridData(CExBaseList *pDatas);
	virtual BOOL OnInitDialog();
	CString GetTestParas(){return m_strTestParas;};
private:
	CConfigSetGrid m_ConfigSetGrid;
	CExBaseList *m_pGridDatas;
	CExBaseList *m_pDatas;
	CString m_strTestParas;
};
