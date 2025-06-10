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

// StateToolDoc.cpp : CStateToolDoc ���ʵ��
//

#include "stdafx.h"
#include "Iec61850Config.h"

#include "StateToolDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStateToolDoc

IMPLEMENT_DYNCREATE(CStateToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CStateToolDoc, CDocument)
	ON_COMMAND(ID_FILE_SAVE, &CStateToolDoc::OnFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &CStateToolDoc::OnUpdateFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CStateToolDoc::OnFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, &CStateToolDoc::OnUpdateFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE_AT02D, &CStateToolDoc::OnFileSaveAT02D)//�ܺ�� 20200616  ����AT02����
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AT02D, &CStateToolDoc::OnUpdateFileSaveAT02D)
	ON_COMMAND(ID_FILE_SAVE_AS_AT02D, &CStateToolDoc::OnFileSaveAsAT02D)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS_AT02D, &CStateToolDoc::OnUpdateFileSaveAsAT02D)
END_MESSAGE_MAP()


// CStateToolDoc ����/����

CStateToolDoc::CStateToolDoc()
{
	m_pIecCfgFile = NULL;
}

CStateToolDoc::~CStateToolDoc()
{
}

BOOL CStateToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CStateToolDoc ���л�

void CStateToolDoc::Serialize(CArchive& ar)
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

void CStateToolDoc::SetTitle(LPCTSTR lpszTitle)
{
	CDocument::SetTitle(lpszTitle);

}

// CStateToolDoc ���

#ifdef _DEBUG
void CStateToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStateToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CStateToolDoc ����

void CStateToolDoc::OnFileSave()
{
	theApp.OnFileSave();
// 	CFrameWnd *pFrame = GetActiveFrame();
// 
// 	if (!pFrame->IsKindOf(RUNTIME_CLASS(CStateToolFrame)))
// 	{
// 		return;
// 	}
// 
// 	// 	CXFileMngr *pFileMngr = CIecCfgTool::GetIecCfgFileMngr();
// 	// 	CXFolder *pFolder = pFileMngr->GetCurrFolder();
// 	CStateToolFrame *pStateToolFrame = (CStateToolFrame*)pFrame;
// 	pStateToolFrame->Save();
}

void CStateToolDoc::OnUpdateFileSave(CCmdUI *pCmdUI)
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
// 	BOOL b = pFrame->IsKindOf(RUNTIME_CLASS(CStateToolFrame));
// 	pCmdUI->Enable(b);
}

void CStateToolDoc::OnFileSaveAs()
{
	theApp.OnFileSaveAs();
// 	CFrameWnd *pFrame = GetActiveFrame();
// 
// 	if (!pFrame->IsKindOf(RUNTIME_CLASS(CStateToolFrame)))
// 	{
// 		return;
// 	}
// 
// 	CStateToolFrame *pStateToolFrame = (CStateToolFrame*)pFrame;
	//pStateToolFrame->SaveAs();
}

void CStateToolDoc::OnUpdateFileSaveAs(CCmdUI *pCmdUI)
{
	theApp.OnUpdateFileSaveAs(pCmdUI);
	//OnUpdateFileSave(pCmdUI);
}

void CStateToolDoc::OnFileSaveAT02D()//�ܺ�� 20200616  ����AT02����
{
	theApp.OnFileSaveAT02D();
}

void CStateToolDoc::OnUpdateFileSaveAT02D(CCmdUI *pCmdUI)
{
	theApp.OnUpdateFileSaveAT02D(pCmdUI);
}

void CStateToolDoc::OnFileSaveAsAT02D()
{
	theApp.OnFileSaveAsAT02D();
}

void CStateToolDoc::OnUpdateFileSaveAsAT02D(CCmdUI *pCmdUI)
{
	theApp.OnUpdateFileSaveAsAT02D(pCmdUI);
}
