
// iSmartTestNewTestDoc.cpp : CiSmartTestNewTestDoc ���ʵ��
//

#include "stdafx.h"

#include "EdgeSmartTestNewTestDoc.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  


// CiSmartTestNewTestDoc

IMPLEMENT_DYNCREATE(CEdgeSmartTestNewTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CEdgeSmartTestNewTestDoc, CDocument)
END_MESSAGE_MAP()


// CiSmartTestNewTestDoc ����/����

CEdgeSmartTestNewTestDoc::CEdgeSmartTestNewTestDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CEdgeSmartTestNewTestDoc::~CEdgeSmartTestNewTestDoc()
{
}

BOOL CEdgeSmartTestNewTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CiSmartTestNewTestDoc ���л�

void CEdgeSmartTestNewTestDoc::Serialize(CArchive& ar)
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


// CiSmartTestNewTestDoc ���

#ifdef _DEBUG
void CEdgeSmartTestNewTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEdgeSmartTestNewTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CiSmartTestNewTestDoc ����
