#include "stdafx.h"
#include "FactoryBatchTestMngr.h"
#include "TaskMngr/TestTask.h"
#include "TCtrlCntrDefine.h"

#include "TCtrlCntrConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CFactoryBatchTestMngr* CFactoryBatchTestMngr::g_pFactoryBatchTestMngr = NULL;
long CFactoryBatchTestMngr::g_nFactoryBatchTestMngrRef = 0;

CFactoryBatchTestMngr::CFactoryBatchTestMngr()
{
	m_pCurrTestTasks = NULL;
	m_nCurrTestTaskCount = 0;
	m_pMsgRcvWnd = NULL;
	m_pMainTestControl = NULL;
	m_bModifiedFlag = FALSE;
}


CFactoryBatchTestMngr* CFactoryBatchTestMngr::Create()
{
	g_nFactoryBatchTestMngrRef ++;

	if(g_pFactoryBatchTestMngr == NULL)
	{
		g_pFactoryBatchTestMngr = new CFactoryBatchTestMngr();
		g_pFactoryBatchTestMngr->Open();
	}

	return g_pFactoryBatchTestMngr;
}

void CFactoryBatchTestMngr::Release()
{
	g_nFactoryBatchTestMngrRef --;

	if(g_nFactoryBatchTestMngrRef == 0)
	{
		delete g_pFactoryBatchTestMngr;
		g_pFactoryBatchTestMngr = NULL;
	}
}

CFactoryBatchTestMngr::~CFactoryBatchTestMngr()
{
}

CString CFactoryBatchTestMngr::GetFactoryBatchTestMngrFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += CTCtrlCntrConfig::g_pTCtrlCntrConfig->m_strFacBatchTestMngrFile;

	return strFile;
}

BOOL CFactoryBatchTestMngr::Init()
{
	return Open();
}

void CFactoryBatchTestMngr::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CTestTasks *pTestTasks = NULL;

	while (pos != NULL)
	{
		pTestTasks = (CTestTasks *)GetNext(pos);
		pTestTasks->ValidateSystemPath();
	}

	InitCurrTestTasks();

	if (m_pCurrTestTasks != NULL)
	{
		m_pCurrTestTasks->ReportSNGenClear();
		m_pCurrTestTasks->EmptyDeviceAttr();
	}
}

UINT CFactoryBatchTestMngr::GetClassID()
{
	return CLASSID_WORKSPACE;
}

long CFactoryBatchTestMngr::BinarySerializeOwn(CBinarySerialBuffer& oBinaryBuff)
{
	return 0;
}

long CFactoryBatchTestMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAutoTestXMLRWKeys* pKeys = (CAutoTestXMLRWKeys*)pXmlRWKeys;

	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CFactoryBatchTestMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAutoTestXMLRWKeys* pKeys = (CAutoTestXMLRWKeys*)pXmlRWKeys;

	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

BSTR CFactoryBatchTestMngr::GetXmlElementKey()
{
	ASSERT ( CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);
	return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strWorkspaceKeyEx;
}

CExBaseObject* CFactoryBatchTestMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	ASSERT ( CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);

	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskMngrKey)
	{
		CTestTasks* pTasks = new CTestTasks;
		return pTasks;
	}

	return NULL;
}

CExBaseObject* CFactoryBatchTestMngr::CreateNewChild(long nClassID)
{
	return  new CTestTasks;
}

//根据workspace.xml初始化
long CFactoryBatchTestMngr::Open()
{
	ASSERT (CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);

	CString strFile = GetFactoryBatchTestMngrFile();

	DeleteAll();
	OpenXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);

	return 1;
}

//保存workspace修改 xml格式
long CFactoryBatchTestMngr::Save()
{
	CString strFile = GetFactoryBatchTestMngrFile();
	SaveXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);

	return 0;
}

CTestTasks* CFactoryBatchTestMngr::InitCurrTestTasks()
{
	CTestTasks *pTestTasks = (CTestTasks*)g_pFactoryBatchTestMngr->FindByID(g_pFactoryBatchTestMngr->m_strID);

	//2021-3-14  lijunqing
	if (pTestTasks == NULL)
	{
		pTestTasks = (CTestTasks*)g_pFactoryBatchTestMngr->GetHead();
	}

	if (pTestTasks != NULL)
	{
		CExBaseList listTask;
		pTestTasks->SelectAllTestTask(listTask);
		g_pFactoryBatchTestMngr->m_nCurrTestTaskCount = listTask.GetCount();
		listTask.RemoveAll();
	}

	g_pFactoryBatchTestMngr->m_pCurrTestTasks = pTestTasks;
	pTestTasks->InitProjectIndex();

	return pTestTasks;
}

CTestTasks* CFactoryBatchTestMngr::GetCurrTestTasks()
{
	return g_pFactoryBatchTestMngr->m_pCurrTestTasks;
}

CTestProject* CFactoryBatchTestMngr::FindProjectByPrjIndex(CTestProject *pProject)
{
	return FindProjectByPrjIndex(pProject->m_nProjectIndex);
}

CTestProject* CFactoryBatchTestMngr::FindProjectByPrjIndex(long nProjectIndex)
{
	CTestTasks *pFacTestTasks = CFactoryBatchTestMngr::GetCurrTestTasks();
	CTestProject *pFind = pFacTestTasks->FindProjectByPrjIndex(nProjectIndex);
	return pFind;
}

void CFactoryBatchTestMngr::SetCurrTestTasks(CTestTasks *pTestTasks)
{
	g_pFactoryBatchTestMngr->m_strID = pTestTasks->m_strID;
	g_pFactoryBatchTestMngr->m_strName = pTestTasks->m_strName;
	g_pFactoryBatchTestMngr->Save();
}

long CFactoryBatchTestMngr::GetCurrCount()
{
	return g_pFactoryBatchTestMngr->m_nCurrTestTaskCount;
}

BOOL CFactoryBatchTestMngr::HasTestTasks()
{
	return (g_pFactoryBatchTestMngr->m_nCurrTestTaskCount > 0);
}

void CFactoryBatchTestMngr::AttachMsgRcvWnd(CWnd *pWnd)
{
	g_pFactoryBatchTestMngr->m_pMsgRcvWnd = pWnd;
}

void CFactoryBatchTestMngr::PostFacBatchTestMsg(WPARAM wParam, LPARAM lParam)
{
	if (g_pFactoryBatchTestMngr == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("g_pFactoryBatchTestMngr == NULL"));
		return;
	}

	if (g_pFactoryBatchTestMngr->m_pMsgRcvWnd == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("g_pFactoryBatchTestMngr->m_pMsgRcvWnd == NULL"));
		return;
	}

	g_pFactoryBatchTestMngr->m_pMsgRcvWnd->PostMessage(WM_FACBATCHTEST, wParam, lParam);
}

void CFactoryBatchTestMngr::AttachMainTestControl(CExBaseObject *pTestControl)
{
	g_pFactoryBatchTestMngr->m_pMainTestControl = pTestControl;
}

CExBaseObject* CFactoryBatchTestMngr::GetMainTestControl()
{
	return g_pFactoryBatchTestMngr->m_pMainTestControl;
}

//2021-3-14  lijunqing  
void CFactoryBatchTestMngr::BatchTestChanged()
{
	g_pFactoryBatchTestMngr->SetModifiedFlagOwn();
}

void CFactoryBatchTestMngr::SaveBatchTest()
{
	if (!g_pFactoryBatchTestMngr->m_bModifiedFlag)
	{
		return;
	}

	g_pFactoryBatchTestMngr->m_bModifiedFlag = FALSE;
	g_pFactoryBatchTestMngr->Save();
}

