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

// StateToolFrame.h : CStateToolFrame ��Ľӿ�
//

#pragma once

#include "..\Module\IecCfgTool\IecCfgFile.h"
#include "..\..\Module\XfileMngrBase\XFolder.h"

class CStateToolFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CStateToolFrame)
public:
	CStateToolFrame();

// ����
public:
	CDocument   *m_pDocument;
	void GetTestPara(CString &strParas);

// ����
public:


// ��д
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CStateToolFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnClose();
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd*, CWnd*);
};
