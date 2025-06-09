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

// AutoTestDoc.cpp : CAutoTestDoc ���ʵ��
//

#include "stdafx.h"

#include "AutoTestBaseDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoTestDoc

IMPLEMENT_DYNCREATE(CAutoTestBaseDoc, CDocument)

BEGIN_MESSAGE_MAP(CAutoTestBaseDoc, CDocument)
END_MESSAGE_MAP()


// CAutoTestDoc ����/����

CAutoTestBaseDoc::CAutoTestBaseDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CAutoTestBaseDoc::~CAutoTestBaseDoc()
{
	
}

BOOL CAutoTestBaseDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}

BOOL CAutoTestBaseDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	return TRUE;
}

// CAutoTestDoc ���л�

void CAutoTestBaseDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


void CAutoTestBaseDoc::SetTitle(LPCTSTR lpszTitle)
{
	m_strTitle = lpszTitle;

	if (m_strTitle.GetLength() > 30)
	{
		m_strTitle = GetPathFileNameFromFilePathName(m_strTitle);
	}

	if (m_strTitle.GetLength() == 0)
	{
		m_strTitle = lpszTitle;
	}

	UpdateFrameCounts();        // will cause name change in views
}

// CAutoTestDoc ���

#ifdef _DEBUG
void CAutoTestBaseDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAutoTestBaseDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAutoTestDoc ����
