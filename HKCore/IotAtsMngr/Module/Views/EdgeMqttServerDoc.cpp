
// iSmartTestNewTestDoc.cpp : CiSmartTestNewTestDoc ���ʵ��
//

#include "stdafx.h"

#include "EdgeMqttServerDoc.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

// CiSmartTestNewTestDoc

IMPLEMENT_DYNCREATE(CEdgeMqttServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CEdgeMqttServerDoc, CDocument)
END_MESSAGE_MAP()


// CiSmartTestNewTestDoc ����/����

CEdgeMqttServerDoc::CEdgeMqttServerDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CEdgeMqttServerDoc::~CEdgeMqttServerDoc()
{
}

BOOL CEdgeMqttServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CiSmartTestNewTestDoc ���л�

void CEdgeMqttServerDoc::Serialize(CArchive& ar)
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
void CEdgeMqttServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEdgeMqttServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CiSmartTestNewTestDoc ����
