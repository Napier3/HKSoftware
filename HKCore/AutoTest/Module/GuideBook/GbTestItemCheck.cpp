#include "stdafx.h"
#include "GbTestItemCheck.h"


IMPLEMENT_DYNAMIC(CGbItemCheckDlg, CDialog)

CGbItemCheckDlg::CGbItemCheckDlg(CWnd* pParent)
: CDynDialogEx(pParent)
{

}

CGbItemCheckDlg::~CGbItemCheckDlg()
{

}


BEGIN_MESSAGE_MAP(CGbItemCheckDlg, CDialog)
END_MESSAGE_MAP()

int CGbItemCheckDlg::DoModal()   
{   
	CRect rect(0,0,300,200);   
	SetDlgRect(rect);
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   


BOOL CGbItemCheckDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateControls();  //创建控件

	UpdateData(FALSE);
	CRect rc;
	GetWindowRect(&rc);
	rc.right = rc.left + 400;
	rc.bottom = rc.top + 160;
	SetWindowPos(&CWnd::wndTopMost, rc.left, rc.top, rc.Width(), rc.Height(), SWP_SHOWWINDOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CGbItemCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	if (!::IsWindow(m_editPath.m_hWnd))
	{
		return;
	}

	DDX_Text(pDX, 40001, m_strFilePath);
}


void CGbItemCheckDlg::CreateControls()
{
	CreateMultiEdit(m_editPath,                  CRect(10, 10, 390, 100),   40001, this);
	CreateButton(m_btnOK, /*_T("确定")*/g_sLangTxt_OK, CRect(340, 105, 390, 130), IDOK, this);
	m_editPath.SetReadOnly(TRUE);

	CFont *pFont = GetFont();
	m_editPath.SetFont(pFont);
	m_btnOK.SetFont(pFont);
}


//////////////////////////////////////////////////////////////////////////
CGbCommCmdCheck* CGbCommCmdCheck::g_pGbCommCmdCheck = NULL;

void CGbCommCmdCheck::Create(CWnd *pMainFrame, CTreeCtrl *pTreeCtrl, CExBaseList *pGbNode)
{
	Release();

	if (g_pGbCommCmdCheck == NULL)
	{
		g_pGbCommCmdCheck = new CGbCommCmdCheck(pMainFrame, pTreeCtrl, pGbNode);
	}
}

void CGbCommCmdCheck::Release()
{
	if (g_pGbCommCmdCheck != NULL)
	{
		delete g_pGbCommCmdCheck;
		g_pGbCommCmdCheck = NULL;
	}
}


CGbCommCmdCheck::CGbCommCmdCheck(CWnd *pMainFrame, CTreeCtrl *pTreeCtrl, CExBaseList *pGbNode)
{
	m_pMainFrame = pMainFrame;
	m_pGbTreeCtrl = pTreeCtrl;
	m_pCpus = NULL;

	CDevice *pDevice = (CDevice*)pGbNode;

	if (pDevice == NULL)
	{
		return;
	}

	m_pCpus = pDevice->GetCpus();

	if (m_pCpus == NULL)
	{
		return;
	}

	GetAllCommCmd(pDevice);
}

CGbCommCmdCheck::~CGbCommCmdCheck()
{
	RemoveAll();
}

void CGbCommCmdCheck::CreateCheckThread()
{
	ASSERT(g_pGbCommCmdCheck != NULL);
	CWinThread *pThread = ::AfxBeginThread(CheckCmdValuesThread, g_pGbCommCmdCheck);
	pThread->m_bAutoDelete = TRUE;
}

UINT CGbCommCmdCheck::CheckCmdValuesThread(LPVOID pObject)
{
	CGbCommCmdCheck *pGbCommCmdCheck = (CGbCommCmdCheck*)pObject;
	pGbCommCmdCheck->CheckCmdValues();
	
	CWnd *pMainFrame = g_pGbCommCmdCheck->m_pMainFrame;
	Release();
	pMainFrame->MessageBox(/*_T("通讯命令数据检查完成！")*/g_sLangTxt_CommCmdCheckComplete, /*_T("提示")*/g_sLangTxt_Message, MB_OK | MB_ICONINFORMATION);

	return 0;
}

void CGbCommCmdCheck::CheckCmdValues()
{
	if (m_pCpus == NULL)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CCommCmd *pCommCmd = NULL;
	BOOL bNeedEdit = FALSE;
	CWnd *pParent = CWnd::GetDesktopWindow();
	
	while (pos != NULL)
	{
		pCommCmd = (CCommCmd*)GetNext(pos);
		bNeedEdit = CheckCommCmd(pCommCmd);

		while (bNeedEdit)
		{
			CString strPath;
			strPath = pCommCmd->GetNamePathEx(GBCLASSID_DEVICE, FALSE);
			CString strMsg;
			strMsg.Format(/*_T("通讯命令:\r\n%s\r\n\r\n参数异常，请手动修改。修改完成，点击“确定”继续\r\n")*/g_sLangTxt_CommCmdParaAbnormal, strPath);
			//pParent->MessageBox(strMsg, _T("提示"), MB_OK | MB_ICONEXCLAMATION);
			CGbItemCheckDlg dlg(pParent);
			dlg.m_strFilePath = strMsg;
			dlg.DoModal();
			bNeedEdit = CheckCommCmd(pCommCmd);
		}
	}
}

void CGbCommCmdCheck::GetAllCommCmd(CExBaseList *pDataList)
{
	POS pos = pDataList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pDataList->GetNext(pos);
		UINT nClassID = p->GetClassID();

		if (nClassID == GBCLASSID_ITEMS)
		{
			GetAllCommCmd((CExBaseList*)p);
		}
		else if (nClassID == GBCLASSID_COMMCMD)
		{
			AddTail(p);
		}
	}
}

BOOL CGbCommCmdCheck::CheckCommCmd(CCommCmd *pCommCmd)
{
	CCmd *pCmd = pCommCmd->GetCmd();
	POS pos1 = pCmd->GetHeadPosition();
	POS pos2 = NULL;

	if (pos1 == NULL)
	{
		return FALSE;
	}

	CValue *pValue1 = NULL;
	CValue *pValue2 = NULL;
	BOOL bNeedEdit = FALSE;

	while (pos1 != NULL)
	{
		pos2 = pos1;
		pCmd->GetNext(pos2);
		pValue1 = (CValue *)pCmd->GetAt(pos1);

		while (pos2 != NULL)
		{
			pValue2 = (CValue *)pCmd->GetAt(pos2);

			if (IsCmdValueSame(pValue1, pValue2))
			{
				//if (pValue1->m_strValue == pValue2->m_strValue)
				{
					pCmd->Delete(pValue2);
					pos2 = pos1;
					GetNext(pos2);
				}
// 				else
// 				{
// 					bNeedEdit = TRUE;
// 					break;
// 				}
			}
			else
			{
				pValue2 = (CValue *)pCmd->GetNext(pos2);
			}
		}

		pValue1 = (CValue *)pCmd->GetNext(pos1);
	}

	if (bNeedEdit)
	{
		m_pGbTreeCtrl->SendMessage(WM_USER + 1055, (WPARAM)pCommCmd, (LPARAM)pCommCmd);
	}

	return bNeedEdit;
}

BOOL CGbCommCmdCheck::IsCmdValueSame(CValue *pValueSrc, CValue *pValueDest)
{
	if (pValueDest->m_strID == pValueSrc->m_strID)
	{
		return TRUE;
	}

	CExBaseObject *pSrc = FindDataObjByRptDataPath(pValueSrc->m_strID);
	CExBaseObject *pDest = FindDataObjByRptDataPath(pValueDest->m_strID);

	if (pSrc == pDest)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CExBaseObject* CGbCommCmdCheck::FindDataObjByRptDataPath(const CString &strPath)
{
	CString strTemp = strPath;
	long nPos = 0;
	CExBaseObject *pFind = NULL;
	
	while (TRUE)
	{
		pFind = m_pCpus->SelectDataObj(strTemp);

		if (pFind != NULL)
		{
			break;
		}

		nPos = strTemp.Find('$');

		if (nPos == -1)
		{
			break;
		}

		strTemp = strTemp.Mid(nPos+1);
	}

	return pFind;
}

void Gb_CheckMacroTestItem(CMacroTest *pMacroTest)
{
	//数据的有效性检查
	CMacroTestParaDatas *pParaDatas = pMacroTest->GetFaultParaDatas();
	POS pos = pParaDatas->GetHeadPosition();
	CMacroTestParaData* pParaData = NULL;//(CMacroTestParaData*)pParaDatas->AddPara(strId);
	CMacroTestParaData* pTemp = NULL;
	//CExBaseList oListDelete;
	CTestMacro *pTestMacro = Gb_GetMacroPtr(pMacroTest);

	if(pTestMacro == NULL)
	{
		return;
	}

	//数据的有效性检查
	while (pos != NULL)
	{
		pParaData = (CMacroTestParaData*)pParaDatas->GetNext(pos);

		if (pTestMacro->FindDataByID(pParaData->m_strID) == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("删除无效参数：【%s】=【%s】")*/g_sLangTxt_DeleteInvalidPara, pParaData->m_strID, pParaData->m_strExpression);
			pParaDatas->Delete(pParaData);
		}
	}

	POS posPrev = pParaDatas->GetHeadPosition();
	pos = posPrev;

	while (pos != NULL)
	{
		pParaData = (CMacroTestParaData*)pParaDatas->GetNext(pos);

		POS posTemp = pos;

		while (posTemp != NULL)
		{
			posPrev = posTemp;
			pTemp = (CMacroTestParaData*)pParaDatas->GetNext(posTemp);

			if (pTemp->m_strID == pParaData->m_strID)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("删除无效参数：【%s】=【%s】")*/g_sLangTxt_DeleteInvalidPara, pTemp->m_strID, pTemp->m_strExpression);
				pParaDatas->Delete(pTemp);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CGbMacroTestItemCheck* CGbMacroTestItemCheck::g_pGbMacroTestCheck = NULL;

void CGbMacroTestItemCheck::Create(CWnd *pMainFrame, CTreeCtrl *pTreeCtrl, CExBaseList *pGbNode)
{
	Release();

	if (g_pGbMacroTestCheck == NULL)
	{
		g_pGbMacroTestCheck = new CGbMacroTestItemCheck(pMainFrame, pTreeCtrl, pGbNode);
	}
}

void CGbMacroTestItemCheck::Release()
{
	if (g_pGbMacroTestCheck != NULL)
	{
		delete g_pGbMacroTestCheck;
		g_pGbMacroTestCheck = NULL;
	}
}


CGbMacroTestItemCheck::CGbMacroTestItemCheck(CWnd *pMainFrame, CTreeCtrl *pTreeCtrl, CExBaseList *pGbNode)
{
	m_pMainFrame = pMainFrame;
	m_pGbTreeCtrl = pTreeCtrl;
	m_pCpus = NULL;

	CDevice *pDevice = (CDevice*)pGbNode;

	if (pDevice == NULL)
	{
		return;
	}

	m_pCpus = pDevice->GetCpus();

	if (m_pCpus == NULL)
	{
		return;
	}

	GetAllMacroTest(pDevice);
}

CGbMacroTestItemCheck::~CGbMacroTestItemCheck()
{
	RemoveAll();
}

void CGbMacroTestItemCheck::CreateCheckThread()
{
	ASSERT(g_pGbMacroTestCheck != NULL);
	CWinThread *pThread = ::AfxBeginThread(CheckMacroTestParasThread, g_pGbMacroTestCheck);
	pThread->m_bAutoDelete = TRUE;
}

UINT CGbMacroTestItemCheck::CheckMacroTestParasThread(LPVOID pObject)
{
	CGbMacroTestItemCheck *pGbMacroTestCheck = (CGbMacroTestItemCheck*)pObject;
	pGbMacroTestCheck->CheckMacroTestParas();

	CWnd *pMainFrame = g_pGbMacroTestCheck->m_pMainFrame;
	Release();
	pMainFrame->MessageBox(/*_T("电气量测试功能数据检查完成！")*/g_sLangTxt_ElectricCheckComplete, /*_T("提示")*/g_sLangTxt_Message, MB_OK | MB_ICONINFORMATION);


	return 0;
}

void CGbMacroTestItemCheck::CheckMacroTestParas()
{
	if (m_pCpus == NULL)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CMacroTest *pMacroTest = NULL;
	BOOL bNeedEdit = FALSE;
	CWnd *pParent = CWnd::GetDesktopWindow();

	while (pos != NULL)
	{
		pMacroTest = (CMacroTest*)GetNext(pos);
		bNeedEdit = CheckMacroTest(pMacroTest);

		while (bNeedEdit)
		{
			CString strPath;
			strPath = pMacroTest->GetNamePathEx(GBCLASSID_DEVICE, FALSE);
			CString strMsg;
			strMsg.Format(/*_T("电气量测试:\r\n%s\r\n\r\n参数异常，请手动修改。修改完成，点击“确定”继续\r\n")*/g_sLangTxt_ElectricParaAbnormal, strPath);
			//pParent->MessageBox(strMsg, _T("提示"), MB_OK | MB_ICONEXCLAMATION);
			CGbItemCheckDlg dlg(pParent);
			dlg.m_strFilePath = strMsg;
			dlg.DoModal();
			bNeedEdit = CheckMacroTest(pMacroTest);
		}
	}
}

void CGbMacroTestItemCheck::GetAllMacroTest(CExBaseList *pDataList)
{
	POS pos = pDataList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pDataList->GetNext(pos);
		UINT nClassID = p->GetClassID();

		if (nClassID == GBCLASSID_ITEMS)
		{
			GetAllMacroTest((CExBaseList*)p);
		}
		else if (nClassID == GBCLASSID_MACROTEST)
		{
			AddTail(p);
		}
	}
}

BOOL CGbMacroTestItemCheck::CheckMacroTest(CMacroTest *pMacroTest)
{
	BOOL bNeedEdit = FALSE;
// 	CCmd *pCmd = pMacroTest->GetCmd();
// 	POS pos1 = pCmd->GetHeadPosition();
// 	POS pos2 = NULL;
// 
// 	if (pos1 == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	CValue *pValue1 = NULL;
// 	CValue *pValue2 = NULL;
// 
// 	while (pos1 != NULL)
// 	{
// 		pos2 = pos1;
// 		pCmd->GetNext(pos2);
// 		pValue1 = (CValue *)pCmd->GetAt(pos1);
// 
// 		while (pos2 != NULL)
// 		{
// 			pValue2 = (CValue *)pCmd->GetAt(pos2);
// 
// 			if (IsMacroTestParaSame(pValue1, pValue2))
// 			{
// 				//if (pValue1->m_strValue == pValue2->m_strValue)
// 				{
// 					pCmd->Delete(pValue2);
// 					pos2 = pos1;
// 					GetNext(pos2);
// 				}
// 				// 				else
// 				// 				{
// 				// 					bNeedEdit = TRUE;
// 				// 					break;
// 				// 				}
// 			}
// 			else
// 			{
// 				pValue2 = (CValue *)pCmd->GetNext(pos2);
// 			}
// 		}
// 
// 		pValue1 = (CValue *)pCmd->GetNext(pos1);
// 	}

	Gb_CheckMacroTestItem(pMacroTest);

	if (bNeedEdit)
	{
		m_pGbTreeCtrl->SendMessage(WM_USER + 1055, (WPARAM)pMacroTest, (LPARAM)pMacroTest);
	}

	return bNeedEdit;
}
// 
// BOOL CGbMacroTestItemCheck::IsMacroTestParaSame(CValue *pValueSrc, CValue *pValueDest)
// {
// 	if (pValueDest->m_strID == pValueSrc->m_strID)
// 	{
// 		return TRUE;
// 	}
// 
// 	CExBaseObject *pSrc = FindDataObjByRptDataPath(pValueSrc->m_strID);
// 	CExBaseObject *pDest = FindDataObjByRptDataPath(pValueDest->m_strID);
// 
// 	if (pSrc == pDest)
// 	{
// 		return TRUE;
// 	}
// 	else
// 	{
// 		return FALSE;
// 	}
// }
// 
// CExBaseObject* CGbMacroTestItemCheck::FindDataObjByRptDataPath(const CString &strPath)
// {
// 	CString strTemp = strPath;
// 	long nPos = 0;
// 	CExBaseObject *pFind = NULL;
// 
// 	while (TRUE)
// 	{
// 		pFind = m_pCpus->SelectDataObj(strTemp);
// 
// 		if (pFind != NULL)
// 		{
// 			break;
// 		}
// 
// 		nPos = strTemp.Find('$');
// 
// 		if (nPos == -1)
// 		{
// 			break;
// 		}
// 
// 		strTemp = strTemp.Mid(nPos+1);
// 	}
// 
// 	return pFind;
// }
