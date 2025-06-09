// PoEngine.cpp : 实现文件
//

#include "stdafx.h"
#include "PoMmsEngine.h"

#include "PoMmsDevice.h"
#include "../../../Module/System/TickCount32.h"

long g_nMmsCmdFlag = 0;

// CPoMmsEngine
CPoMmsEngine *g_theMmsEngine = NULL;
CPoMmsEngine* CPoMmsEngine::g_pMmsEngine = NULL;
long CPoMmsEngine::g_nPxiEngineRef = 0;


CPoMmsEngine::CPoMmsEngine()
{
	g_theMmsEngine = this;
}

CPoMmsEngine::~CPoMmsEngine()
{

}


void CPoMmsEngine::OnFinalRelease()
{

}

CPoMmsEngine* CPoMmsEngine::Create()
{
	g_nPxiEngineRef++;

	if (g_nPxiEngineRef == 1)
	{
		g_pMmsEngine = new CPoMmsEngine();
		g_pMmsEngine->InitInstance();
		//g_pPxiEngine->InitPpBaseApp();
	}

	return g_pMmsEngine;
}

void CPoMmsEngine::Release()
{
	g_nPxiEngineRef--;

	if (g_nPxiEngineRef == 0)
	{
		//g_pPxiEngine->ExitPpBaseApp();
		g_pMmsEngine->ExitInstance();
		delete g_pMmsEngine;
		g_pMmsEngine = NULL;
	}
}

CPoMmsEngine* CPoMmsEngine::GetPxiEngine()
{
	return g_pMmsEngine;
}



// CPoMmsEngine 消息处理程序

CString CPoMmsEngine::GetVersion(void)
{
	

	CString strResult;

	// TODO: 在此添加调度处理程序代码

	return strResult;
}



CPoMmsDevice* CPoMmsEngine::CreateDevice(const CString &strTemplateFile, const CString &strDeviceFile, const CString &strDeviceID)
{
	theMmsApi->m_oFuncParamEx[0].set_DevIndex(0);//theMmsApi->m_FuncParam.set_DevIndex(0);
	CString strID;
	strID = strDeviceID;

	// 	pDevice->m_pACSI_NODE = &pACSINode[0];
	ACSI_NODE *pNode = mms_Find_ACSI_NODE_ByID(strID);

	if (pNode == NULL)
	{
		pNode = mms_Find_ACSI_NODE_UnConnect();

		if (pNode == NULL)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                                       , g_sLangTxt_ReachMax.GetString()
                                       , strID.GetString());//_T("可创建的设备数已经达到最上限，不能创建【%s】设备")
		}
		else
		{
			CString_to_char(strID, pNode->devID);
		}
	}

	if (pNode != NULL)
	{
		CPoMmsDevice *pDevice = new CPoMmsDevice();
		pDevice->m_pACSI_NODE = pNode;
		pDevice->m_strDeviceFile = strDeviceFile;
		theMmsApi->OnCreateDevice();
		pNode->pRefDevice = pDevice;  //2022-11-26  lijunqing

		return pDevice;
	}
	else
	{
		return NULL;
	}
}

long CPoMmsEngine::GetCount(void)
{
	

	// TODO: 在此添加调度处理程序代码

	return 0;
}

CPoMmsDevice* CPoMmsEngine::GetItem(long nIndex)
{
	

	// TODO: 在此添加调度处理程序代码

	return NULL;
}

long CPoMmsEngine::ShowSpyWnd(long nShow)
{
	return 0;
}

long CPoMmsEngine::ReleaseDevice(const CString &strDeviceID)
{
	CString strID;
	strID = strDeviceID;

	return 0;
}

long CPoMmsEngine::ReleaseAllDevice(void)
{
	

	theMmsApi->ReleaseAllDevice();

	return 0;
}

long CPoMmsEngine::CreateProject(const CString &strProjectFile)
{
	// TODO: 在此添加调度处理程序代码
//	CString strMsg;
//	strMsg = strProjectFile;
//
//	if (strMsg.Find("ActiveWindow")>= 0)
//	{
//		theMmsApi->ShowAppWindow(TRUE);
//	}

	return 0;
}

long CPoMmsEngine::SetProtocolParse(long nStopFlag)
{
	g_nStopProtocolParseFlag = nStopFlag;
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("PoEngine::SetProtocolParse(%d)"), nStopFlag);

	return 0;
}

long CPoMmsEngine::ConfigEngine(const CString &strDvmFile)
{
	return 0;
}

//2020-12-23  lijunqing
long CPoMmsEngine::AttatchLogWnd(long hLogWnd)
{
	return 0;
}
