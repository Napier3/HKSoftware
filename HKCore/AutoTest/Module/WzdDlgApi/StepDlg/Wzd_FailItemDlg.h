#pragma once
#include "WzdDlgBase.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../../../Module/GuideBook/Items.h"
#include "ListCtrlEx.h"
#include "afxwin.h"

// CWzd_FailItemDlg 对话框

#define  WM_FAIL_ITEM_FING_CHANG WM_USER+1001

class CWzd_FailItemDlg : public CWzdDlgBase
{
	DECLARE_DYNAMIC(CWzd_FailItemDlg)

public:
	CWzd_FailItemDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWzd_FailItemDlg();

// 对话框数据
	enum { IDD = IDD_FAIL_ITEM_DIALOG };
	virtual void XUI_InitAdjust();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	
public:
	//初始化 列表的值
	void InitFailItemInfo();
	//检测过程中，更新测试值 测试的状态图标
	void UpdateFailItemInfo(CGbItemBase* pTestItem);

	//删除后期 检测通过的测试项
	void DeleteFailItemItem(CGbItemBase* pTestItem);

	int FindRow(CGbItemBase* pTestItem);

protected:
	//消息响应函数
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMRClickFailItemList(NMHDR *pNMHDR, LRESULT *pResult);
	//右键菜单
	afx_msg void OnFindFailItem();
	afx_msg void OnFailItemAdvise();

private:
	// 不合格检查项目信息
	CListCtrlEx m_ctrlFailItemList;
	int			m_nInitWidth;
	// 提示
	CStatic m_Static1;
	CImageList m_ImageList;

};
