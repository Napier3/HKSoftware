// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// ("Fluent UI")����ʾ������Ϊ�ο������ṩ�� 
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ���� (C) Microsoft Corporation
// ��������Ȩ����

// AutoTestBaseTreeView.h : CAutoTestBaseTreeView ��Ľӿ�
//


#pragma once

//////////////////////////////////////////////////////////////////////////
//������
#include "AutoTestBaseDoc.h"

//////////////////////////////////////////////////////////////////////////
class CAutoTestBaseReportView;
class CAutoTestBaseLogicView;

#define ID_GUIDEBOOK_TEST_TREECTRL  3123


class CAutoTestBaseTreeView : public CView
{
protected: // �������л�����
	CAutoTestBaseTreeView();
	DECLARE_DYNCREATE(CAutoTestBaseTreeView)

public:
	void AdjustLayout(int cx, int cy);//����Ӧ�����ߴ�
	CGuideBookTreeCtrl* GetGuideBookTree()							{		return &m_treeGuideBook;		}

// ����
public:
	CAutoTestBaseDoc* GetDocument() const;
	CTestControl* m_pTestControl;
	CAutoTestBaseReportView *m_pReportView;
	CAutoTestBaseLogicView *m_pLogicView;
	CGuideBookTreeCtrl m_treeGuideBook;

// ����
public: 
	virtual CRptFillInterface* GetRptFillInterface();
	virtual void CloseTestControl();
	long OnCurrItemStateChanged(CGbItemBase* pItem, BOOL bBringToTop);
	void SelectTestItem(CExBaseObject *pItem);
	void LocateVisio(CExBaseObject *pItem);

	//shaolei 20220622 SV����ѹ��һ���Բ��ԣ���Ҫ��̬������Ŀ����Ҫɾ�������
	void InsertItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem);
	void DeleteItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem);
	//shaolei 2023-6-14��������Ŀʱ���ݹ��������Ŀ
	void InsertItemEx(CGbItemBase *pParentItem, CGbItemBase *pSubItem);

protected:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
protected:

// ʵ��
public:
	virtual ~CAutoTestBaseTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
public:
	afx_msg void OnDestroy();
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // AutoTestBaseTreeView.cpp �еĵ��԰汾
inline CAutoTestBaseDoc* CAutoTestBaseTreeView::GetDocument() const
   { return reinterpret_cast<CAutoTestBaseDoc*>(m_pDocument); }
#endif

