// PoCmsEngine.cpp : 实现文件
//

#include "stdafx.h"
#include "PoCmsEngine.h"
#include "PoCmsDevice.h"
#include "../../../Module/System/TickCount32.h"
#include "../dlt860/ClientCallBack.h"
#include "DltEngineAppBase.h"

extern long g_nMmsCmdFlag;

CPoCmsEngine *g_theCmsEngine = NULL;
CPoCmsEngine* CPoCmsEngine::g_pCmsEngine = NULL;
long CPoCmsEngine::g_nCmsEngineRef = 0;

CPoCmsEngine* CPoCmsEngine::Create()
{
	g_nCmsEngineRef++;

	if (g_nCmsEngineRef == 1)
	{
		g_pCmsEngine = new CPoCmsEngine();
		g_pCmsEngine->InitInstance();
	}

	return g_pCmsEngine;
}

void CPoCmsEngine::Release()
{
	g_nCmsEngineRef--;

	if (g_nCmsEngineRef == 0)
	{
		g_pCmsEngine->ExitInstance();
		delete g_pCmsEngine;
		g_pCmsEngine = NULL;
	}
}

CPoCmsEngine* CPoCmsEngine::GetPxiEngine()
{
	return g_pCmsEngine;
}

CPoCmsEngine::CPoCmsEngine()
{
	g_theCmsEngine = this;
}

CPoCmsEngine::~CPoCmsEngine()
{

}

CPoCmsDevice* CPoCmsEngine::CreateDevice(const CString &strTemplateFile, const CString &strDeviceFile, const CString &strDeviceID)
{
	// TODO: 在此添加调度处理程序代码
#ifdef PPMMSENGINE_DEMO
	return NULL;
#else
	CLogPrint::LogString(XLOGLEVEL_TRACE, "CPpEngine::CreateDevice");

	theCmsApp->m_oFuncParamEx[0].set_DevIndex(0);//theCmsApp->m_FuncParam.set_DevIndex(0);
	CString strID;
	strID = strDeviceID;

	if (strID.Find(_T("MmsCmd")) >= 0)
	{
		if (g_nMmsCmdFlag == 0)
		{
			g_nMmsCmdFlag = 1;
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("创建为MMS通讯命令模式【%s】") , strID.GetString());//_T("创建为MMS通讯命令模式【%s】")
		}
	}

// 	pDevice->m_pACSI_NODE = &pACSINode[0];
	ACSI_NODE *pNode = g_o61850ClientConfig.mms_Find_ACSI_NODE_ByID(strID);

	if (pNode == NULL)
	{
		pNode = g_o61850ClientConfig.mms_Find_ACSI_NODE_UnConnect();

		if (pNode == NULL)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("可创建的设备数已经达到最上限，不能创建【%s】设备") , strID.GetString());//_T("可创建的设备数已经达到最上限，不能创建【%s】设备")
		}
		else
		{
			CString_to_char(strID, pNode->devID);
		}
	}

	if (pNode != NULL)
	{
		CPoCmsDevice *pDevice = new CPoCmsDevice();
		pDevice->m_pACSI_NODE = pNode;
		pDevice->m_strDeviceFile = strDeviceFile;
		pNode->pRefDevice = pDevice;  //2022-11-26  lijunqing
		return pDevice;
	}
	else
	{
		return NULL;
	}
#endif
}

CPoCmsDevice* CPoCmsEngine::GetItem(LONG nIndex)
{

	return NULL;
}

CString CPoCmsEngine::GetVersion(void)
{


	CString strResult;

	// TODO: 在此添加调度处理程序代码

	return strResult;
}


long CPoCmsEngine::GetCount(void)
{


	// TODO: 在此添加调度处理程序代码

	return 0;
}

long CPoCmsEngine::ShowSpyWnd(long nShow)
{
	return 0;
}

long CPoCmsEngine::ReleaseDevice(const CString &strDeviceID)
{
	CString strID;
	strID = strDeviceID;

	return 0;
}

long CPoCmsEngine::ReleaseAllDevice(void)
{
	//zhouhj 2024.9.21 代码递归调用,导致死循环
//	g_theCmsEngine->ReleaseAllDevice();
	return 0;
}

long CPoCmsEngine::CreateProject(const CString &strProjectFile)
{
	// TODO: 在此添加调度处理程序代码
	//	CString strMsg;
	//	strMsg = strProjectFile;
	//
	//	if (strMsg.Find("ActiveWindow")>= 0)
	//	{
	//		g_theCmsEngine->ShowAppWindow(TRUE);
	//	}

	return 0;
}

long CPoCmsEngine::SetProtocolParse(long nStopFlag)
{
	g_nStopProtocolParseFlag = nStopFlag;
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("PoEngine::SetProtocolParse(%d)"), nStopFlag);

	return 0;
}

long CPoCmsEngine::ConfigEngine(const CString &strDvmFile)
{
	return 0;
}

//2020-12-23  lijunqing
long CPoCmsEngine::AttatchLogWnd(long hLogWnd)
{
	return 0;
}
