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

// IecConfigDoc.cpp : CIecConfigDoc ���ʵ��
//

#include "stdafx.h"
#include "Iec61850Config.h"

#include "IecConfigDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIecConfigDoc

IMPLEMENT_DYNCREATE(CIecConfigDoc, CDocument)

BEGIN_MESSAGE_MAP(CIecConfigDoc, CDocument)
	ON_COMMAND(ID_FILE_SAVE, &CIecConfigDoc::OnFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &CIecConfigDoc::OnUpdateFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CIecConfigDoc::OnFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, &CIecConfigDoc::OnUpdateFileSaveAs)

	ON_COMMAND(ID_FILE_SAVE_AT02D, &CIecConfigDoc::OnFileSaveAT02D)//�ܺ�� 20200616  ����AT02����
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AT02D, &CIecConfigDoc::OnUpdateFileSaveAT02D)
	ON_COMMAND(ID_FILE_SAVE_AS_AT02D, &CIecConfigDoc::OnFileSaveAsAT02D)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS_AT02D, &CIecConfigDoc::OnUpdateFileSaveAsAT02D)
END_MESSAGE_MAP()


// CIecConfigDoc ����/����

CIecConfigDoc::CIecConfigDoc()
{
	m_pIecCfgFile = NULL;
}

CIecConfigDoc::~CIecConfigDoc()
{
}

BOOL CIecConfigDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CIecConfigDoc ���л�

void CIecConfigDoc::Serialize(CArchive& ar)
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

void CIecConfigDoc::SetTitle(LPCTSTR lpszTitle)
{
	CDocument::SetTitle(lpszTitle);
}

// CIecConfigDoc ���

#ifdef _DEBUG
void CIecConfigDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIecConfigDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CIecConfigDoc ����

void CIecConfigDoc::OnFileSave()
{
	theApp.OnFileSave();
// 	CFrameWnd *pFrame = GetActiveFrame();
// 
// 	if (!pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)))
// 	{
// 		return;
// 	}
// 
// 	// 	CXFileMngr *pFileMngr = CIecCfgTool::GetIecCfgFileMngr();
// 	// 	CXFolder *pFolder = pFileMngr->GetCurrFolder();
// 	CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pFrame;
// 	pIecConfigFrame->Save();
}

void CIecConfigDoc::OnUpdateFileSave(CCmdUI *pCmdUI)
{
	theApp.OnUpdateFileSave(pCmdUI);
// 	CFrameWnd *pFrame = GetActiveFrame();
// 
// 	if (pFrame == NULL)
// 	{
// 		pCmdUI->Enable(FALSE);
// 		return;
// 	}
// 
// 	BOOL b = pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame));
// 	pCmdUI->Enable(b);
}

void CIecConfigDoc::OnFileSaveAs()
{
	theApp.OnFileSaveAs();
// 	CFrameWnd *pFrame = GetActiveFrame();
// 
// 	if (!pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)))
// 	{
// 		return;
// 	}
// 
// 	CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pFrame;
	//pIecConfigFrame->SaveAs();
}

void CIecConfigDoc::OnUpdateFileSaveAs(CCmdUI *pCmdUI)
{
	theApp.OnUpdateFileSaveAs(pCmdUI);
	//OnUpdateFileSave(pCmdUI);
}

void CIecConfigDoc::OnFileSaveAT02D()//�ܺ�� 20200616  ����AT02����
{
	theApp.OnFileSaveAT02D();
}

void CIecConfigDoc::OnUpdateFileSaveAT02D(CCmdUI *pCmdUI)
{
	theApp.OnUpdateFileSaveAT02D(pCmdUI);
}

void CIecConfigDoc::OnFileSaveAsAT02D()
{
	theApp.OnFileSaveAsAT02D();
}

void CIecConfigDoc::OnUpdateFileSaveAsAT02D(CCmdUI *pCmdUI)
{
	theApp.OnUpdateFileSaveAsAT02D(pCmdUI);
}
