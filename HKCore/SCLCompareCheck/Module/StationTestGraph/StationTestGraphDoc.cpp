
// StationTestMainDoc.cpp : CStationTestMainDoc ���ʵ��
//

#include "stdafx.h"
#include "..\..\SclFileTest\SCLCompareCheckDev.h"

#include "StationTestGraphDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStationTestMainDoc

IMPLEMENT_DYNCREATE(CStationTestGraphDoc, CDocument)

BEGIN_MESSAGE_MAP(CStationTestGraphDoc, CDocument)
END_MESSAGE_MAP()


// CStationTestMainDoc ����/����

CStationTestGraphDoc::CStationTestGraphDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CStationTestGraphDoc::~CStationTestGraphDoc()
{
}

BOOL CStationTestGraphDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CStationTestMainDoc ���л�

void CStationTestGraphDoc::Serialize(CArchive& ar)
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


// CStationTestMainDoc ���

#ifdef _DEBUG
void CStationTestGraphDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStationTestGraphDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CStationTestMainDoc ����
