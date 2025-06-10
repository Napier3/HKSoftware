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

// StateToolView.h : CStateToolView ��Ľӿ�
//


#pragma once

#include "..\..\AutoTest\Module\GbMacroUIInterface.h"

class CStateToolView : public CFormView
{
protected: // �������л�����
	CStateToolView();
	DECLARE_DYNCREATE(CStateToolView)
	CGbMacroUI *m_pGbMacroUI;

	void CreateGbUI();
public:
	enum{ IDD = IDD_STATETOOL_FORM };

// ����
public:
	CStateToolDoc* GetDocument() const;

// ����
public:
	void GetTestPara(CString &strParas);

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CStateToolView();
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

#ifndef _DEBUG  // StateToolView.cpp �еĵ��԰汾
inline CStateToolDoc* CStateToolView::GetDocument() const
   { return reinterpret_cast<CStateToolDoc*>(m_pDocument); }
#endif

