
// TestGridViewDoc.cpp : CTestGridViewDoc ���ʵ��
//

#include "stdafx.h"
#include "TestGridView.h"

#include "TestGridViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestGridViewDoc

IMPLEMENT_DYNCREATE(CTestGridViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestGridViewDoc, CDocument)
END_MESSAGE_MAP()


// CTestGridViewDoc ����/����

CTestGridViewDoc::CTestGridViewDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CTestGridViewDoc::~CTestGridViewDoc()
{
}

BOOL CTestGridViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CTestGridViewDoc ���л�

void CTestGridViewDoc::Serialize(CArchive& ar)
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


// CTestGridViewDoc ���

#ifdef _DEBUG
void CTestGridViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestGridViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTestGridViewDoc ����
