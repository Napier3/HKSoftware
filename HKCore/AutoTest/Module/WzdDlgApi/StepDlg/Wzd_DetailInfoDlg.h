#pragma once


// CWzd_DetailInfoDlg 对话框
#include "WzdDlgBase.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../../../Module/GuideBook/Items.h"
#include "../StepCtrl/WzdDlgTabCtrl.h"
#include "..\..\..\..\Module\BaseClass\ExBaseListTreeCtrl.h"
#include "../StepCtrl/GridiDetailInfoReportWzd.h"
#include "../StepCtrl/WzdDlgComboBox.h"
#include "../StepCtrl/UIDrawer.h"


class CWzd_DetailInfoDlg : public CUIDialog, public CExBaseListTreeOptrInterface
{
	DECLARE_DYNAMIC(CWzd_DetailInfoDlg)

public:
	CWzd_DetailInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWzd_DetailInfoDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_DETAILINFO };

	virtual BOOL OnInitDialog();
	virtual void OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
	//消息响应函数
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg void OnCbnSelchangeComboxIndex();
	afx_msg void OnSelchangeTabReportData(NMHDR* pNMHDR, LRESULT* pResult);

public:
	CUITabCtrl m_tabTestStep;
	CUITabCtrl m_tabReportData;

	CUITreeCtrl m_treeTestStep;
	CGridiDetailInfoReportWzd m_gridReportData1;
	CGridiDetailInfoReportWzd m_gridReportData2;

	CUIButton m_btnOK;
	CUIButton m_btnCancel;

	CStatic m_wordTiShi1_Head;
	CStatic m_wordTiShi1_Tail;
	CUIComboBox m_comboxIndex;

private:
	CItems* m_pShowTestItem;

	CReports* m_pReports;
	int m_iReportTime;

	void ClearReportDataShow();
	void SetSelectReports(CGbItemBase* pSelectBaseItem);

public:
	void ShowItemDetailInfo(CItems* pTestItem);
	void SetDataTable(int iIndex);
	void AddComBoxData(int iCount);

	void ShowTreeData();
	void ShowReportData();
};
