// PpMmsEngine.cpp
//

#include "stdafx.h"
#include "MmsEngineAppBase.h"


#ifdef _PSX_IDE_QT_
#include "MmsEngineAppWnd_Linux.h"
#else
#include "MmsEngineAppWnd_Win.h"
#endif

#include "../MmsGlobal.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/System/TickCount32.h"
#include "../../../Module/FilterText/FilterTextMngr.h"
#include "../../../Module/API/GlobalConfigApi.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMmsEngineAppBase *CMmsEngineAppBase::g_pMmsEngine = NULL;
long CMmsEngineAppBase::g_nMmsEngineRef = 0;

CMmsEngineAppBase* CMmsEngineAppBase::Create()
{
	g_nMmsEngineRef++;

	if (g_nMmsEngineRef == 1)
	{
		g_pMmsEngine = new CMmsEngineAppBase();
		g_pMmsEngine->InitInstance();
	}

	return g_pMmsEngine;
}

void CMmsEngineAppBase::Release()
{
	g_nMmsEngineRef--;

	if (g_nMmsEngineRef == 0)
	{
		g_pMmsEngine->ExitInstance();
		delete g_pMmsEngine;
		g_pMmsEngine = NULL;
	}
}

CMmsEngineAppBase* CMmsEngineAppBase::GetMmsEngine()
{
	return g_pMmsEngine;
}

CMmsEngineAppBase::CMmsEngineAppBase()
{
	theMmsApi = this;
	m_nDeviceCount = 0;
	m_nBrcbType = rcbType_Prot;
}

void CMmsEngineAppBase::ExitMmsApi()
{

}

BOOL CMmsEngineAppBase::InitInstance()
{
	m_pMmsMsgRcvWnd = NULL;
    CMmsEngineAppWnd *pWin = NULL;
#ifdef _PSX_IDE_QT_
    pWin = new CMmsEngineAppWnd_Linux();
#else
    pWin = new CMmsEngineAppWnd_Win();
#endif

    pWin->CreateWnd();
    m_pMmsMsgRcvWnd = pWin;

    InitMmsGlobalPath();
	m_oMmsKeyConfig.Open();

	CMmsRcdFilesMngrXmlRWKeys::Create();
	CMMS_STACK_CFGXmlRWKeys::Create();

	ReadMmsEngineConfig();

	if (!g_bMultDevModel)
	{
		mmsi_InitMMSData(0, SD_TRUE);
	}

	return TRUE;
}

ST_RET CMmsEngineAppBase::enter_u_mvl_rpt_CriticSection()
{
	//m_pAutoSimpleLock->Enter(m_oAutoCriticSection);

	return 0;
}

ST_RET CMmsEngineAppBase::free_u_mvl_rpt_CriticSection()
{
	//m_pAutoSimpleLock->Free();

	return 0;
}

void CMmsEngineAppBase::AddErrorString(const CString &strMsg)
{
// 	if (m_strErrorMsg.GetLength() > 2048)
// 	{
// 		m_strErrorMsg.Empty();
// 	}
// 
// 	m_strErrorMsg += _T("\r\n"));
// 	m_strErrorMsg += strMsg;
}

void CMmsEngineAppBase::GetErrorString(CString &strMsg)
{
// 	strMsg = m_strErrorMsg;
// 	m_strErrorMsg.Empty();
}

int CMmsEngineAppBase::ExitInstance()
{
	// 确保读线程退出;
	long nDevNum = HasDevice();

	for (long nCount = 0;nCount<nDevNum;nCount++)
	{
		InitStopReportFuncParas(nCount, TRUE);	// 停止报告
	}
	
	SetThreadExit(SD_TRUE);

	Sleep(1000);
	mmsi_DisConnectServer(0);
	DestroyDataProcThread();

	Sleep(1000);
	CTickCount32 oTickCounter;

	while (GetThreadCount() > 0)
	{
		Sleep(100);

		if (oTickCounter.GetTickCountLong(FALSE) >= 5000)
		{
			break;
		}
	}

	mmsi_ReleaseMMSData(0);

	// 释放内存
	ReleaseMMSData();
	ReleaseObjData();//zhouhj 20181009 单独释放

	CMmsRcdFilesMngrXmlRWKeys::Release();
	delete m_pMmsMsgRcvWnd;

	return 0;
}


/* 2012-08-29  获取数值 */
CString CMmsEngineAppBase::GetStringFromValue(CString str, tagValue data)
{
	CString string =g_sLangTxt_Unknown /*_T("未知")*/;
	if(( 0 == str.Compare(_T("INT")))||(0 == str.Compare(_T("UINT"))))
	{
		string.Format(_T("%d"),data.i);
	}else if( 0 == str.Compare(_T("BOOL")))
	{
		string.Format(_T("%d"), data.u );
	}else if((0 == str.Compare(_T("LONG")))||( 0 == str.Compare(_T("ULONG"))))
	{
		str.Format(_T("%d"),data.l);
	}else if(0 == str.Compare(_T("FLOAT")))
	{
		string.Format(_T("%f"),data.f);
	}
	else if(0 == str.Compare(_T("V_STR")))
	{
#ifdef _use_mms_string
		string = mms_string(&data.string);
#else
		string = data.string;
#endif
	}
	else if(0 == str.Compare(_T("UTC_TIME")))
	{
		time_t t = data.l;
		CTime time(t);
		string.Format(_T("%d - %d - %d %d:%d:%d"),
			time.GetYear(),time.GetMonth(),time.GetDay(),
			time.GetHour(),time.GetMinute(),time.GetSecond());
	}

	return string;
}

/* 2012-11-9  报告结果通知 */
ST_VOID CMmsEngineAppBase::mmsi_RecvRptData()
{
//	if (theApp.m_pMainWnd) 
//		::SendMessage(theApp.m_pMainWnd->m_hWnd,WM_UPDATEWIND_RPT,0,0);
}

void CMmsEngineAppBase::InitMmsGlobalPath()
{
	const char *pBinPath = _P_GetBinPath();

	sprintf(CLIENT_PATH, "%sclient.log", pBinPath);
	sprintf(LOGCFG_PATH, "%slogcfg.xml", pBinPath);
    sprintf(WMD_PATH, "%sVMD.ini", pBinPath);
	sprintf(OSICFG_PATH, "%sosicfg.xml", pBinPath);
	sprintf(SECMANCFG_PATH, "%ssecmancfg.xml", pBinPath);
}

//tagDA数据操作
CString CMmsEngineAppBase::mms_GetDAName(tagDA *pDA)
{
	CString strText;
#ifdef _use_mms_string
	strText = mms_string(&pDA->DADescri.Value.string);//mms_UTF8ToUnicode(pDA->DADescri.Value.name, strlen(pDA->DADescri.Value.name));
#else
	strText = pDA->DADescri.Value.string;//mms_UTF8ToUnicode(pDA->DADescri.Value.name, strlen(pDA->DADescri.Value.name));
#endif
	return strText;
}

CString CMmsEngineAppBase::mms_GetDADataType(tagDA *pDA)
{
	CString strText;
	return strText;
}

CString CMmsEngineAppBase::mms_GetDAPath(tagDA *pDA)
{
	CString strText;
	return strText;
}

CString CMmsEngineAppBase::mms_GetDAUnit(tagDA *pDA)
{
	CString strText;
	My_PareVarUnite(pDA->DAUnite.Value.i, strText);
	return strText;
}

BOOL CMmsEngineAppBase::SaveAllMmsDevicesRcdFiles()
{
	long nDeviceIndex = 0;
	ACSI_NODE *pDevNode = NULL;
	CMmsDevices oMmsDevices;
	CMmsDevice *pCurMmsDev = NULL;
	CRcdDir *pRcdDir = NULL;

	for(nDeviceIndex = 0;nDeviceIndex<MAX_DEVICE;nDeviceIndex++)
	{
		pDevNode = &pACSINode[nDeviceIndex];
		pCurMmsDev = new CMmsDevice;
		oMmsDevices.AddNewChild(pCurMmsDev);
		pCurMmsDev->m_strName.Format(_T("MmsDevice%ld"),nDeviceIndex);
		pRcdDir = new CRcdDir;
		pCurMmsDev->AddNewChild(pRcdDir);
		pRcdDir->m_strName = mms_string(&pDevNode->FileDir.filedir.filename);
		GetRcdDirAndFileFromMmsFileSysObj(pRcdDir ,pDevNode->FileDir.subFiles);
	}

	return oMmsDevices.SaveMmsDevicesCfgFile();
}

BOOL CMmsEngineAppBase::ReadAllMmsDevicesRcdFilesFromFile()
{
	CMmsDevices oMmsDevices;
	
	if (!oMmsDevices.OpenMmsDevicesCfgFile())
	{
		return FALSE;
	}

	long nDeviceIndex = 0;
	ACSI_NODE *pDevNode = NULL;
	CMmsDevice *pCurMmsDev = NULL;
	CRcdDir *pRcdDir = NULL;
	CString strDeviceName;
	POS pos_Dev = oMmsDevices.GetHeadPosition();

	while((pos_Dev != NULL)&&(nDeviceIndex<MAX_DEVICE))
	{
		pCurMmsDev = (CMmsDevice*)oMmsDevices.GetNext(pos_Dev);
		strDeviceName.Format(_T("MmsDevice%ld"),nDeviceIndex);

		if (strDeviceName == pCurMmsDev->m_strName)
		{
			pRcdDir = (CRcdDir *)pCurMmsDev->GetHead();
			pDevNode = &pACSINode[nDeviceIndex];
			mms_file_sys_free(&pDevNode->FileDir);
			mms_str_init(&pDevNode->FileDir.filedir.filename);
            mms_str_set(&pDevNode->FileDir.filedir.filename,pRcdDir->m_strName.GetString());
			pDevNode->FileDir.bFirstRead = FALSE;
			pDevNode->FileDir.bIsNew = FALSE;
			pDevNode->FileDir.nType =1;
			pDevNode->FileDir.readfailed = FALSE;

			if (pRcdDir != NULL)
			{
				GetMmsFileSysObjFromDir(&pDevNode->FileDir,pRcdDir);
			}	
		}

		nDeviceIndex++;
	}

	return TRUE;
}

void CMmsEngineAppBase::GetRcdDirAndFileFromMmsFileSysObj(CRcdDir *pRcdDir,const MMS_ADDR_VECTOR &oMmsAddrVector)
{
	long nCurDirFile = 0;
	XMMS_FILE_SYS_OBJ *pMmsFileObj = NULL;
	CRcdDir *pSubRcdDir = NULL;
	CRcdFile *pSubRcdFile = NULL;

	for (nCurDirFile = 0;nCurDirFile<oMmsAddrVector.numOfData;nCurDirFile++)
	{
		pMmsFileObj = (XMMS_FILE_SYS_OBJ*)oMmsAddrVector.Datas[nCurDirFile];

		if (pMmsFileObj->nType)
		{
			pSubRcdDir = new CRcdDir;
			pRcdDir->AddNewChild(pSubRcdDir);
			pSubRcdDir->m_strName = mms_string(&pMmsFileObj->filedir.filename);
			pSubRcdDir->m_nDirSize = pMmsFileObj->filedir.fsize;
			pSubRcdDir->m_fDirTime = pMmsFileObj->filedir.mtime;
			GetRcdDirAndFileFromMmsFileSysObj(pSubRcdDir,pMmsFileObj->subFiles);
		} 
		else
		{
			pSubRcdFile = new CRcdFile;
			pRcdDir->AddNewChild(pSubRcdFile);
			pSubRcdFile->m_strName = mms_string(&pMmsFileObj->filedir.filename);
			pSubRcdFile->m_nFileSize = pMmsFileObj->filedir.fsize;
			pSubRcdFile->m_fFileTime = 	pMmsFileObj->filedir.mtime;
		}
	}
}

void CMmsEngineAppBase::GetMmsFileSysObjFromDir(XMMS_FILE_SYS_OBJ *pMmsFileSysObj,CRcdDir *pRcdDir)
{
	long nCurDirFile = 0;
	XMMS_FILE_SYS_OBJ *pMmsFileObj = NULL;
	CRcdDir *pSubRcdDir = NULL;
	CRcdFile *pSubRcdFile = NULL;
	CExBaseObject *pFileSysObj = NULL;
	MMS_ADDR_VECTOR *pMmsAddrVector = &pMmsFileSysObj->subFiles;
	vector_add_capacity(pMmsAddrVector ,pRcdDir->GetCount());
	POS pos_file_dir = pRcdDir->GetHeadPosition();

	while(pos_file_dir != NULL)
	{
		pFileSysObj = pRcdDir->GetNext(pos_file_dir);
		vector_set_add_data(pMmsAddrVector,(LPVOID*)&pMmsFileObj,sizeof(XMMS_FILE_SYS_OBJ));
		pMmsFileObj->bIsNew = FALSE;	
		pMmsFileObj->bFirstRead = FALSE;
		mms_str_init(&pMmsFileObj->filedir.filename);
        mms_str_set(&pMmsFileObj->filedir.filename,pFileSysObj->m_strName.GetString());
		pMmsFileObj->parent = pMmsFileSysObj;

		if (pFileSysObj->GetClassID() == MNGRCLASSID_CRCDDIR)
		{
			pSubRcdDir = (CRcdDir *)pFileSysObj;
			pMmsFileObj->nType = 1;
			pMmsFileObj->filedir.fsize = pSubRcdDir->m_nDirSize;
			pMmsFileObj->filedir.mtime = pSubRcdDir->m_fDirTime;
			GetMmsFileSysObjFromDir(pMmsFileObj,pSubRcdDir);
		}
		else if (pFileSysObj->GetClassID() == MNGRCLASSID_CRCDFILE)
		{
			pSubRcdFile = (CRcdFile *)pFileSysObj;
			pMmsFileObj->nType = 0;
			pMmsFileObj->filedir.fsize = pSubRcdFile->m_nFileSize;
			pMmsFileObj->filedir.mtime = pSubRcdFile->m_fFileTime;
		}

		nCurDirFile++;
	}
}

/* 2012-11-22  基本数据操作过程 */
long CMmsEngineAppBase::MMS_DataOpeProc(CFuncParamEx *pFuncParaEx)
{
	long nRet = CMmsApi::MMS_DataOpeProc(pFuncParaEx);

	if (nRet == -1)
	{
		return nRet;
	}

	ST_INT nFuncID = pFuncParaEx->get_FuncID();

	if (nFuncID != FuncID_TestProc)
	{
		SendMessage_TestFuncFinished((WPARAM)pFuncParaEx,nRet);
	}

	return nRet;
}

BOOL CMmsEngineAppBase::SendMessage_TestFuncFinished(WPARAM wParam,LPARAM lParam)
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



