// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// IecConfigFrame.h : CIecConfigFrame 类的接口
//

#pragma once

#include "..\Module\IecCfgTool\IecCfgFile.h"
#include "..\..\Module\XfileMngrBase\XFolder.h"

class CIecConfigFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CIecConfigFrame)
public:
	CIecConfigFrame();

protected:
	BOOL m_bCloseFrameByDelete;

// 属性
public:
	CIecCfgFile *m_pIecCfgFile;
	CDocument   *m_pDocument;

// 操作
public:
	BOOL Save(BOOL bIsAT02D_CFG = FALSE);//周宏军 20200616  增加AT02配置
	BOOL Save(CXFolder *pXFolder);

	BOOL SaveAs(BOOL bIsAT02D_CFG = FALSE);
	BOOL SaveAs(const CString &strFileName);
	BOOL SaveAs(CXFolder *pXFolder);

	void SetCloseFrameByDelete(BOOL b)	{	m_bCloseFrameByDelete = b;	}

// 重写
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CIecConfigFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnClose();
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd*, CWnd*);
	afx_msg LRESULT OnIecCfgDataChanged(WPARAM, LPARAM);
	afx_msg LRESULT OnIecCfgDataMixCtrlsChanged(WPARAM, LPARAM);
	afx_msg LRESULT OnIecCfgOnlyViewUsedInChs(WPARAM, LPARAM);
	afx_msg LRESULT OnIecCfgUpdateChsGrid(WPARAM, LPARAM);
};
