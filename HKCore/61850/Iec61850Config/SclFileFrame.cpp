// SclFileFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "SclFileFrame.h"

#include "SclFileTreeView.h"
#include "SclFileDetailView.h"
#include "TestEngine.h"

// CSclFileFrame

IMPLEMENT_DYNCREATE(CSclFileFrame, CMDIChildWndEx)

CSclFileFrame::CSclFileFrame()
{
	m_pSclFile = NULL;
	m_pSclFileRead = NULL;
}

CSclFileFrame::~CSclFileFrame()
{
	theApp.m_pSclFileFrame = NULL;

	if (theApp.IsRunAutomaition()&&(strlen(g_szEngineSCLPath)>0)&&(IsFileExist(g_szEngineSCLPath)))
	{
		theApp.OpenSclFile(g_szEngineSCLPath);
		memset(g_szEngineSCLPath,0,500);
	}
}

BOOL CSclFileFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	CRect rect;
	GetClientRect(&rect);

	m_wndSplitter.CreateStatic(this, //������ָ��
		1, // �зֵ�����
		2); // �зֵ�����

	m_wndSplitter.CreateView(0,0, // ������С�������
		RUNTIME_CLASS(CSclFileTreeView),//��ͼ��
		CSize(rect.Width()/3,rect.Height()),//��ʼ����С
		pContext);//�����ڵĴ�������

	//Ϊ�ڶ������������ͼ
	m_wndSplitter.CreateView(0,1,
		RUNTIME_CLASS(CSclFileDetailView),
		CSize(rect.Width()*2/3,rect.Height()),
		pContext);

	CSclFileDetailView *pSclFileDetailView = (CSclFileDetailView*)m_wndSplitter.GetPane(0, 1);
	pSclFileDetailView->AttachSclFileTreeView((CView*)m_wndSplitter.GetPane(0, 0));
	pSclFileDetailView->InitViews();

	return TRUE;
}

BEGIN_MESSAGE_MAP(CSclFileFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSclFileFrame ��Ϣ�������

void CSclFileFrame::OnClose()
{
	ASSERT (m_pSclFile != NULL);
	CString strMsg;

	if (m_pSclFile == NULL)
	{
		strMsg.Format(_T("ϵͳ���ã����ܹرա�%s��"), m_strTscdFile);
		MessageBox(strMsg, _T("��ʾ"), MB_OK | MB_ICONWARNING);
		return;
	}

	strMsg.Format(_T("��ȷʵҪ�رա�%s����"), m_pSclFile->m_strName);

	UINT nRet = MessageBox(strMsg, _T("��ʾ"), MB_YESNO | MB_ICONQUESTION);

	if (nRet == IDNO)
	{
		return;
	}

	CSclFile *pFile = m_pSclFile;
	CMDIChildWndEx::OnClose();

	CIecCfgTool::FreeSclFileRead(pFile);
	theApp.m_pCurrSelSclIed = NULL;
}

void CSclFileFrame::CloseSclFileFrame()
{
	if (m_pSclFile == NULL)
	{
		return;
	}

	CSclFile *pFile = m_pSclFile;
	CMDIChildWndEx::OnClose();

	CIecCfgTool::FreeSclFileRead(pFile);
	theApp.m_pCurrSelSclIed = NULL;
}

void CSclFileFrame::UpdateIecCfgFilesComboBox()
{
	CSclFileDetailView *pSclFileDetailView = (CSclFileDetailView*)m_wndSplitter.GetPane(0, 1);
	CSclFileCtrlView *pCtrlView = pSclFileDetailView->GetSclFileCtrlView();
	pCtrlView->UpdateIecCfgFilesComboBox();
}

void CSclFileFrame::OpenTscdFile(const CString &strTscdFile)
{
	if (m_strTscdFile != strTscdFile)
	{
		m_oSclStation.DeleteAll();
		m_oSclStation.OpenSclStationFile(strTscdFile);
	}

	m_strTscdFile = strTscdFile;

	CSclFileTreeView *pTreeView = (CSclFileTreeView*)m_wndSplitter.GetPane(0, 0);
	ASSERT(pTreeView);
	pTreeView->m_treeSclIecCfg.AttachMsgRcvWnd(pTreeView->m_pSclFileCtrlView);
	pTreeView->m_treeSclIecCfg.ShowIecfgSclIeds(&m_oSclStation);
}

void CSclFileFrame::OpenTscdFile(const CString &strTscdFile, const CString &strIedId)
{
	OpenTscdFile(strTscdFile);
	OnShowCurIED(strIedId);
// 	CSclFileTreeView *pTreeView = (CSclFileTreeView*)m_wndSplitter.GetPane(0, 0);
// 	pTreeView->ShowSclStation(strIedId);
}

void CSclFileFrame::OnShowCurIED(const CString &strIedId)
{
	CSclFileTreeView *pTreeView = (CSclFileTreeView*)m_wndSplitter.GetPane(0, 0);

	if (pTreeView == NULL)
	{
		return;
	}

	pTreeView->ShowSelectIED(strIedId);
}

