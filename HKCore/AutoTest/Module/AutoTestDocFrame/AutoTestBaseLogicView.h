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

// AutoTestBaseLogicView.h : CAutoTestBaseLogicView ��Ľӿ�
//


#pragma once

#include "../GuideBook/ReportMap/VisioLogicRpt/VisioLogicRptFill.h"
#include "AutoTestBaseDoc.h"

//////////////////////////////////////////////////////////////////////////
class CAutoTestBaseDoc;

class CAutoTestBaseLogicView : public CScrollView
{
protected: // �������л�����
	CAutoTestBaseLogicView();
	DECLARE_DYNCREATE(CAutoTestBaseLogicView)

// ����
public:
	CAutoTestBaseDoc* GetDocument() const;
	CTestControl* m_pTestControl;

	//���ӳ�Աָ��
	CVisioLogicRptFill *m_pVisioRptFill;

// ����
public: 
	virtual void CreateTestControlView(CTestControl *pTestControl);
	virtual void CloseTestControl();
	void LocateVisio(CExBaseObject *pItem);
	void SetParentWnd(CWnd *pParent)	{	m_pParentWnd = pParent;	}
	CWnd* GetParentWnd()	{	return m_pParentWnd;	}

protected:
	CWnd *m_pParentWnd;

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
protected:

// ʵ��
public:
	virtual ~CAutoTestBaseLogicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) ;

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
	long OnCurrItemStateChanged(CGbItemBase* pItem);
};

#ifndef _DEBUG  // AutoTestBaseLogicView.cpp �еĵ��԰汾
inline CAutoTestBaseDoc* CAutoTestBaseLogicView::GetDocument() const
   { return reinterpret_cast<CAutoTestBaseDoc*>(m_pDocument); }
#endif

