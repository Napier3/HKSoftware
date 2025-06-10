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

// IecConfigFrame.h : CIecConfigFrame ��Ľӿ�
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

// ����
public:
	CIecCfgFile *m_pIecCfgFile;
	CDocument   *m_pDocument;

// ����
public:
	BOOL Save(BOOL bIsAT02D_CFG = FALSE);//�ܺ�� 20200616  ����AT02����
	BOOL Save(CXFolder *pXFolder);

	BOOL SaveAs(BOOL bIsAT02D_CFG = FALSE);
	BOOL SaveAs(const CString &strFileName);
	BOOL SaveAs(CXFolder *pXFolder);

	void SetCloseFrameByDelete(BOOL b)	{	m_bCloseFrameByDelete = b;	}

// ��д
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CIecConfigFrame();
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
	afx_msg LRESULT OnIecCfgDataChanged(WPARAM, LPARAM);
	afx_msg LRESULT OnIecCfgDataMixCtrlsChanged(WPARAM, LPARAM);
	afx_msg LRESULT OnIecCfgOnlyViewUsedInChs(WPARAM, LPARAM);
	afx_msg LRESULT OnIecCfgUpdateChsGrid(WPARAM, LPARAM);
};
