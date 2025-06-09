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

// AutoTestBaseReportView.h : CAutoTestBaseReportView ��Ľӿ�
//


#pragma once

//////////////////////////////////////////////////////////////////////////
//������
#include "AutoTestBaseDoc.h"

//////////////////////////////////////////////////////////////////////////
class CAutoTestBaseDoc;
class CAutoTestBaseTreeView;

class CAutoTestBaseReportView : public CScrollView
{
protected:// �������л�����
	CAutoTestBaseReportView();
	DECLARE_DYNCREATE(CAutoTestBaseReportView)

// ����
public:
	CAutoTestBaseDoc* GetDocument() const;
	CTestControl* m_pTestControl;
	UINT m_nTestControlMode;
	CAutoTestBaseTreeView *m_pTreeView;

// ����
public: 
	virtual CRptFillInterface* GetRptFillInterface();
	virtual long OpenReportView();
	virtual void CreateTestControlView(CTestControl *pTestControl);
	virtual void CloseTestControl();

protected:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
protected:

// ʵ��
public:
	virtual ~CAutoTestBaseReportView();
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
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) ;
	afx_msg LRESULT OnCreateNewTestProject(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnAdjustViewSize(WPARAM wParam,LPARAM lParam);

	DECLARE_MESSAGE_MAP()
	
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	afx_msg void OnDestroy();
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // AutoTestBaseReportView.cpp �еĵ��԰汾
inline CAutoTestBaseDoc* CAutoTestBaseReportView::GetDocument() const
   { return reinterpret_cast<CAutoTestBaseDoc*>(m_pDocument); }
#endif

