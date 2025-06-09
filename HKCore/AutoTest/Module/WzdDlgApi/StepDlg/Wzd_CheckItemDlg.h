#pragma once
#include "WzdDlgBase.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../../../Module/GuideBook/Items.h"
#include "ListCtrlEx.h"
// CWzd_CheckItemDlg 对话框

class CWzd_CheckItemDlg : public CWzdDlgBase
{
	DECLARE_DYNAMIC(CWzd_CheckItemDlg)

public:
	CWzd_CheckItemDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWzd_CheckItemDlg();

// 对话框数据
	enum { IDD = IDD_CHECK_ITEM__DIALOG };
	virtual void XUI_InitAdjust();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	


public:
	//初始化 列表的值 二级节点
	void InitCheckItemInfo(CItems* pStep);
	//根据测试指导书的 当前项 更新检测项
	void UpdateCheckItemInfo(CItems* pStep);
	//检测过程中，更新测试值 测试的状态图标，不合格显示在不合格列表
	void UpdateCheckItemState(CGbItemBase* pTestItem);
	void UpdateCheckItemState2();
	//获取当前选中节点
	bool GetCurrentItemInfo(CItems* &pTestItem);
	//设置当前选中项
	void SetSelectRow(CItems* pTestItem);

protected:
	//消息响应函数
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMClickCheckItemList(NMHDR *pNMHDR, LRESULT *pResult);	
	//右键菜单
	afx_msg void OnNMRClickCheckItemList(NMHDR *pNMHDR, LRESULT *pResult);
	//菜单按钮  测试当前项目  从当前项目开始测试  查看详细信息
	afx_msg void OnTestCurrentItem();
	afx_msg void OnFromTestItem();
	afx_msg void OnCheckDetailInfo();

private:
	// 检验项目信息
	//CListCtrl m_ctrlChectItemList;
	CListCtrlEx m_ctrlChectItemList;
	CImageList m_ImageList;

	CItems*  m_pCurrentStepItem;
	CItems*  m_pTestItem;
};
