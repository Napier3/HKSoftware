// DltEngine.cpp 
//

#include "stdafx.h"
#include "DltEngineAppBase.h"

#ifdef _PSX_IDE_QT_
#include "CmsEngineAppWnd_Linux.h"
#else
#include "CmsEngineAppWnd_Win.h"
#endif

#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/XMinidmp/XMinidmp.h"
#include "../../../Module/API/SingleAppMutexApi.h"
#include "../dlt860/DLT860Engine.h"
#include "../MmsGlobal.h"
#include "../EnumType.h"

CDltEngineAppBase *theCmsApp = NULL;

// CDltEngineAppBase 构造
CDltEngineAppBase::CDltEngineAppBase()
{
	theCmsApp = this;
	g_oDLT860Api = this;
}

CDltEngineAppBase::~CDltEngineAppBase()
{
	
}

// CDltEngineAppBase 初始化
BOOL CDltEngineAppBase::InitInstance()
{
	m_pMmsMsgRcvWnd = NULL;
	CCmsEngineAppWnd *pWin = NULL;
#ifdef _PSX_IDE_QT_
	pWin = new CCmsEngineAppWnd_Linux();
#else
	pWin = new CCmsEngineAppWnd_Win();
#endif

	pWin->CreateWnd();
	m_pMmsMsgRcvWnd = pWin;

	//初始化
	CDataMngrXmlRWKeys::Create();
	C61850ClientCfgMngrXmlRWKeys::Create();
	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += _T("860ClientConfig.xml");

	InitGlobalDatasets_DescDef();

	if (!g_o61850ClientConfig.OpenClientConfg(strPath))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("配置文件(%s)打开失败."),strPath.GetString());
	}

	g_o61850ClientConfig.UpdateProtocolVersion();
	g_bMmsEngineDebugMode = g_o61850ClientConfig.m_nDebugMode;
	g_nCfgMaxDevNum = g_o61850ClientConfig.GetRemoteDevCount();

	CString strExeDateTime;
	strExeDateTime += __DATE__;
	strExeDateTime += " ";
	strExeDateTime += __TIME__;
    CString strMsg;
    strMsg = _T("DLT860当前程序版本:");
    strMsg += strExeDateTime;
    CLogPrint::LogString(XLOGLEVEL_INFOR, strMsg);

	return TRUE;
}

void CDltEngineAppBase::AddErrorString(const CString &strMsg)
{
	CAutoSimpleLock oLock(m_oAutoCriticSectionErrorMsg);

	if (m_strErrorMsg.GetLength() > 2048)
	{
		m_strErrorMsg.Empty();
	}

    m_strErrorMsg.AppendFormat(_T("%s\r\n"), strMsg.GetString());
}

void CDltEngineAppBase::GetErrorString(CString &strMsg)
{
	CAutoSimpleLock oLock(m_oAutoCriticSectionErrorMsg);
	strMsg = m_strErrorMsg;
	m_strErrorMsg.Empty();
}

// CDltEngineAppBase 消息处理程序

int CDltEngineAppBase::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pProgressInterface = NULL;

/*	if (m_pProgDlg != NULL)
	{
		delete m_pProgDlg;
		m_pProgDlg = NULL;
	}
*/

	DestroyDataProcThread();
	g_o61850ClientConfig.SaveClientConfg();
	C61850ClientCfgMngrXmlRWKeys::Release();
	CDataMngrXmlRWKeys::Release();
	delete m_pMmsMsgRcvWnd;

	ReleaseGlobalDatasets_DescDef();

	return 0;
}

long CDltEngineAppBase::Client61850_DataOpeProc(CFuncParamEx *pFuncParaEx)
{
	long nRet = CDLT860Api::Client61850_DataOpeProc(pFuncParaEx);

	if (nRet == -1)
	{
		return nRet;
	}

	ST_INT nFuncID = pFuncParaEx->get_FuncID();

	if (nFuncID != FuncID_TestProc)
	{
		SendMessage_TestFuncFinished((WPARAM)pFuncParaEx,nRet);
		//		pFuncParaEx->MySendMessage();//参数1在函数中未使用，实际无效
	}

	return nRet;
}

BOOL CDltEngineAppBase::SendMessage_TestFuncFinished(WPARAM wParam,LPARAM lParam)
{
	CFuncParamEx *pFuncParaEx = (CFuncParamEx*)wParam;

	if (pFuncParaEx->m_bHasPostMsg)
	{
		return FALSE;
	}

	pFuncParaEx->m_bHasPostMsg = TRUE;
    m_pMmsMsgRcvWnd->PostMessage(WM_Notify_Msg,(WPARAM )pFuncParaEx,lParam);
	return TRUE;
}

BOOL CDltEngineAppBase::CallFirstFunc(long nDeviceIndex)
{
	BOOL bRet = CDLT860Api::CallFirstFunc(nDeviceIndex);
	CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];
	pFuncParaEx->m_posCurrFuncPara = pFuncParaEx->GetHeadPosition();
	long nCount = m_oFuncParamEx[nDeviceIndex].GetCount();

	if (pFuncParaEx->m_posCurrFuncPara != NULL)
	{
		StartProgress();
/*
		if (m_pProgDlg != NULL)
		{
			m_pProgDlg->SetMaxRange(nCount);
		}
*/
	}

	return bRet;
}

void CDltEngineAppBase::StartProgress()
{		

}

BOOL CDltEngineAppBase::CallCurrFunc(long nDeviceIndex)
{
	BOOL bRet = CDLT860Api::CallCurrFunc(nDeviceIndex);

	if (!bRet)
	{
		return FALSE;
	}

/*
	if (m_pProgDlg == NULL)
	{
		return TRUE;
	}
*/

	ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);

	if (pDevice == NULL)
	{
		return FALSE;
	}

	LD_NODE *pLD_NODE = &pDevice->LD[m_oFuncParamEx[nDeviceIndex].get_LDvIndex()];
	ST_INT nFuncID = m_oFuncParamEx[nDeviceIndex].get_FuncID();
	ST_INT nDsDaType = m_oFuncParamEx[nDeviceIndex].get_DSID();

	long nIndex = m_oFuncParamEx[nDeviceIndex].FindIndex(m_oFuncParamEx[nDeviceIndex].m_posCurrFuncPara)+1;
	long nCount = m_oFuncParamEx[nDeviceIndex].GetCount();
	CString strFuncID , strDsDaType;

	// 增加校验 && nFuncID < FUNCID_MAX_COUNT
	if (nFuncID != FuncID_UnKnow && nFuncID != FuncID_TestProc && nFuncID < FUNCID_MAX_COUNT)
	{
		strFuncID = g_strFuncIDame[nFuncID];
	}

	// 增加校验  
	if (nDsDaType != dsType_NULL && nDsDaType < MAX_DASET_NUM)
	{
		LD_DATASET_INFO *pLD_INFO = &pLD_NODE->DataInfo[nDsDaType];
		strDsDaType = pLD_INFO->DataSetID;
	}

	CString strTitle;

	if (nFuncID != FuncID_Link)
	{
		if (nFuncID == FuncID_ReadFile)
		{
            strTitle.Format(_T("第%d步 共%d步 ： %s"), nIndex, nCount
                            , m_oFuncParamEx[nDeviceIndex].get_FileName() );
		}
		else
		{
			strTitle.Format(_T("第%d步 共%d步 ： 设备%d - 逻辑设备%d - %s - %s")
				, nIndex, nCount,
                nDeviceIndex + 1, m_oFuncParamEx[nDeviceIndex].get_LDvIndex() + 1
                , strFuncID.GetString(), strDsDaType.GetString());
		}
	}
	else
	{
		strTitle.Format(_T("联机：%s"), mms_string(&pDevice->IpAddr));
	}

/*
	m_pProgDlg->StepIt();
	m_pProgDlg->SetTitle(strTitle);
	m_pProgDlg->ShowMsg(strTitle);
*/

	return TRUE;
}

BOOL CDltEngineAppBase::InitCallReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bStart, BOOL bFreeFuncParas)
{
	if (!CDLT860Api::InitCallReportFuncParas(nDeviceIndex, nLDIndex, nDsIndex, bStart,bFreeFuncParas))
	{
		return FALSE;
	}

	ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);
	pDevice->hRptMsgWnd = (unsigned long)m_pMmsMsgRcvWnd->m_hWnd;
	pDevice->nRptMsg = WM_MMS_REPORT;
	return TRUE;
}

BOOL CDltEngineAppBase::InitCallReportFuncParasEx(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, UINT nBrcbIndex, BOOL bFreeFuncParas)
{
	if (!CDLT860Api::InitCallReportFuncParasEx(nDeviceIndex, nLDIndex, nDsIndex, nBrcbIndex,bFreeFuncParas))
	{
		return FALSE;
	}

	ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);
	pDevice->hRptMsgWnd = (unsigned long)m_pMmsMsgRcvWnd->m_hWnd;
	pDevice->nRptMsg = WM_MMS_REPORT;
	return TRUE;
}

BOOL CDltEngineAppBase::InitStopReportFuncParas(ST_INT nDeviceIndex, BOOL bFreeFuncParas)
{
	if (!CDLT860Api::InitStopReportFuncParas(nDeviceIndex,bFreeFuncParas))
	{
		return FALSE;
	}

	ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);

	if (m_pMmsMsgRcvWnd !=NULL)
		pDevice->hRptMsgWnd = (unsigned long)m_pMmsMsgRcvWnd->m_hWnd;

	pDevice->nRptMsg = WM_MMS_REPORT;
	return TRUE;
}

BOOL CDltEngineAppBase::InitStopReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex)
{
	return CDLT860Api::InitStopReportFuncParas(nDeviceIndex,nLDIndex,nDsIndex);
}

void CDltEngineAppBase::SetReportRet(CFuncParamEx *pFuncParaEx,BOOL bSucc, BOOL bStart_NotStop)
{
	if (bSucc)
	{
		int nDeviceIndex = pFuncParaEx->get_DevIndex();
		int nLDIndex = pFuncParaEx->get_LDvIndex();
		int nDsIndex = pFuncParaEx->get_DSID();

		ACSI_NODE *pDevice = GetAcsiNode(nDeviceIndex);

		if (pDevice == NULL)
		{
			return;
		}

		if (bStart_NotStop)
		{
			BOOL b = mms_GetReportFlag(pDevice,nLDIndex,nDsIndex);
			mms_SetReportRet(pDevice,nLDIndex,nDsIndex, b);
		}
		else
		{
			mms_SetReportFlag(pDevice,nLDIndex,nDsIndex, FALSE);
			mms_SetReportRet(pDevice,nLDIndex,nDsIndex, FALSE);
		}
	}
}


BOOL CDltEngineAppBase::IsFuncsAllFinish(long nDeviceIndex)
{
	CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];

	if (pFuncParaEx->m_posCurrFuncPara == NULL)
	{
		StopProgress(nDeviceIndex);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CDltEngineAppBase::StopProgress(long nDeviceIndex)
{
/*
	if (m_pProgDlg->GetSafeHwnd())
	{
		m_pProgDlg->ShowWindow(SW_HIDE);
	}
*/

	m_oFuncParamEx[nDeviceIndex].m_posCurrFuncPara = NULL;
}

void CDltEngineAppBase::UpdateDeviceIP_Desc(long nDeviceIndex)
{
	if (m_pMmsMsgRcvWnd != NULL)
	{
		m_pMmsMsgRcvWnd->PostMessage(WM_UPDATE_DEVICE_IP_DESC, nDeviceIndex, 0);
	}
}

CString CDltEngineAppBase::Cms_GetDAUnit(tagDA *pDA)
{
	CString strText;
	My_PareVarUnite(pDA->DAUnite.Value.i, strText);
	return strText;
}

ST_VOID CDltEngineAppBase::My_PareVarUnite(int nValue, CString &strText)
{
	ST_CHAR*pValue = (ST_CHAR*)&nValue;

	CString strUnit = "";
	CString strMuti = "";

	if (pValue)
	{
		CSIUnit SIUnit;
		int nIndex = *pValue;
		strUnit = SIUnit.GetSIUnite(nIndex);

		CMultiplier Multiplier;
		nIndex = *(++pValue);
		strMuti = Multiplier.GetMultiplierUnite(nIndex);
	}

    strText.Format("%s%s",strMuti.GetString(),strUnit.GetString());
}


