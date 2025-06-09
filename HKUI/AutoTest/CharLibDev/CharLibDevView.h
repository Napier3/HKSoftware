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

// CharLibDevView.h : CCharLibDevView 类的接口
//


#pragma once

#include "..\Module\Characteristic\CharacterDrawWnd.h"
#include "..\module\characteristic\characterdrawwnd.h"
#include "..\Module\Characteristic\GridCharInterface.h"
#include "..\module\characteristic\gridcharelement.h"
#include "..\module\characteristic\gridcharmacrotest.h"
#include "..\Module\Characteristic\GridCharTestLine.h"
#include "..\..\module\xlanguage\xlanguagetextwnd.h"
#include "..\..\Module\XLanguage\XLanguageButton.h"
class CCharLibDevView : public CFormView, public CExBaseListGridOptrInterface
{
protected: // 仅从序列化创建
	CCharLibDevView();
	DECLARE_DYNCREATE(CCharLibDevView)

	CRect m_rcCtrls[12];
	void InitCtrlsPos();
	void AdjustCtrlsPos(long cx, long cy);

	void EnableCharInterfaceButtons();
	void EnableCharElementButtons();

	BOOL OnEditCellLBDblClk_CharElement(int nRow, int nCol, UINT nChar);
	void ShowCharElementTestLines();

	enum{ IDD = IDD_CHARLIBDEV_FORM };
public:
	virtual void OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);
	virtual BOOL OnEditCellLBDblClk(CXGridCtrlBase *pGridCtrl, int nRow, int nCol, UINT nChar);
	virtual void OnDataEditChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);

	void xlang_InitAndAdjust(); 

// 属性
public:
	CCharLibDevDoc* GetDocument() const;
	//2020-3-13  lijq  去掉CCharacteristicTmplate
	//CCharacteristicTmplate *m_pCharacteristicTmplate;
	CCharacteristic *m_pCharacteristic;
	void ShowCharacteristicTmplate();

	//变量
	CCharInterface *m_pCharInterface;
	CCharacterArea *m_pCharacterArea;


// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CCharLibDevView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CCharacterDrawWnd m_stcCharDraw;
	CGridCharInterface m_gridCharInterface;
	CGridCharElementDev m_gridCharElement;
	CGridCharTestLine m_gridCharElementTestLine;
	CXLanguageButton m_btnNewVariable;
	CXLanguageButton m_btnDeleteVariable;
	CXLanguageButton m_btnNewElement;
	CXLanguageButton m_btnDeleteElement;
	CXLanguageButton m_btnMoveUp;
	CXLanguageButton m_btnMoveDown;
	afx_msg void OnBnClickedBtnNewVariable();
	afx_msg void OnBnClickedBtnDeleteVariable();
	afx_msg void OnBnClickedBtnNewElement();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnMoveup();
	afx_msg void OnBnClickedBtnMoveDown();
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // CharLibDevView.cpp 中的调试版本
inline CCharLibDevDoc* CCharLibDevView::GetDocument() const
   { return reinterpret_cast<CCharLibDevDoc*>(m_pDocument); }
#endif

