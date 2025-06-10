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

// IecConfigView.h : CIecConfigView ��Ľӿ�
//


#pragma once

#include "IecCfgSmvViewMain.h"
#include "IecCfgGoutViewMain.h"
#include "IecCfgGinViewMain.h"
#include "..\Module\ScdDraw\XscdViewMain.h"
#include "IecCfgSysParasView.h"

//#define _use_CXscdViewMain

class CIecConfigView : public CFormView
{
protected: // �������л�����
	CIecConfigView();
	DECLARE_DYNCREATE(CIecConfigView)

public:
	enum{ IDD = IDD_IEC61850CONFIG_FORM };

// ����
public:
	CIecConfigDoc* GetDocument() const;
	CMFCTabCtrl m_tabPara;

#ifdef _use_CXscdViewMain
	CXscdViewCfgMain *m_pXscdViewMain;
#endif

	CIecCfgSmvViewMain *m_pViewSmvMain;
	CIecCfgGinViewMain *m_pViewGinMain;
	CIecCfgGoutViewMain *m_pViewGoutMain;
	CIecCfgSysParasView *m_pSysParasView;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

// ʵ��
public:
	virtual ~CIecConfigView();
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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // IecConfigView.cpp �еĵ��԰汾
inline CIecConfigDoc* CIecConfigView::GetDocument() const
   { return reinterpret_cast<CIecConfigDoc*>(m_pDocument); }
#endif

