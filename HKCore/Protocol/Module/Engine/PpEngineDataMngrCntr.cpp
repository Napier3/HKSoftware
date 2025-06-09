#include "StdAfx.h"
#include "PpEngineDataMngrCntr.h"
#include "PpEngineThreadBase.h"
#include "PpEngineBaseApp.h"
#include "../PpDevConfig/PpDevConfigFileMngr.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/System/TickCount32.h"
#include "../XLanguageResourcePp.h"
#include "PpScriptGlobal.h"

#include "../../../Module/XVM/TScriptParser.h"
#include "../../../Module/XVM/TAsmParser.h"
#include "../ProcotolProject/PpCfgOptrsMngr.h"
#include "../XLanguageResourcePp_PpEngine.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// #ifdef _LUA_IN_DEVBASEAPP_
// #else
// //Lua
// #include "lua.h"
// #include "lualib.h"
// #include "lauxlib.h"
// #include "luabind.hpp"
// 
// lua_State* _PpEngineData_Get_Lua(void *p)
// {
// 	return (lua_State*)p;
// }
// 
// #endif


//////////////////////////////////////////////////////////////////////////
//CPpEngineData
CPpEngineData::CPpEngineData(const CString &strPpTemplateFile, const CString &strPpDeviceFile)
{
    m_pPxiDeviceCommCmdMessage = NULL;
	m_strRcdFilePath = _P_GetDBPath();
	CreateAllDirectories(m_strRcdFilePath);

	m_pPpScript = NULL;
	m_pScriptBuffer[0] = 0;
	//m_pszFuncName[0] = 0;

// #ifdef _LUA_IN_DEVBASEAPP_
// #else
// 	m_pLua = NULL;
// 	InitLua();
// #endif
	m_pEngineXvm = new CEngineXvm();
	m_pEngineXvm->TS_Init();
	m_pEngineXvm->RegisterHostAPIFuncs();
	m_pEngineXvm->TS_StartScript();
	m_pEngineXvm->SetRefData(this);

	m_pPpRecordMngr = NULL;
	m_pTemplate = NULL;
	m_pDevcieModel = NULL;
	m_pEngineThread = NULL;
	m_pPpDeviceRef = NULL;
	m_pDeviceCmmConfigRef = NULL;

	m_pDevcieModel = new CDevcieModel();
	m_pTemplate = new CPpTemplate();  
	m_pPpRecordMngr = new  CPpRecordMngr();

	m_pPpRecordMngr->SetParent(this);
	m_pTemplate->SetParent(this);
	m_pDevcieModel->SetParent(this);
	m_pPoDeviceProcedureInterface = NULL;

	LoadEngineFile(strPpTemplateFile, strPpDeviceFile);
	m_pRefTreeCtrl = NULL;
	m_pEngineDeviceBase = NULL;
}

CString ttt_file_GetTemplateFile(const CString &strPpTemplateFile)
{
    CString strTemp, strFile;
    strTemp = GetPathFileNameFromFilePathName(strPpTemplateFile);

    if (strTemp.GetLength() == 0)
    {
        strTemp = strPpTemplateFile;
    }

    strFile = _P_GetTemplatePath();
    strFile += strTemp;

    if (IsFileExist(strFile))
    {
        CLogPrint::LogString(XLOGLEVEL_TRACE, strFile);
        return strFile;
    }

    strFile = _P_GetInstallPath();
    strFile += _T("e-Protocol/Template/");

    strFile += strTemp;
    CLogPrint::LogString(XLOGLEVEL_TRACE, strFile);
    return strFile;
}

BOOL CPpEngineData::LoadEngineFile(const CString &strPpTemplateFile, const CString &strPpDeviceFile)
{
	CTickCount32 oTickCount32;

	m_strPpTemplateFile = strPpTemplateFile;
	m_strPpDeviceFile = strPpDeviceFile;
	m_pTemplate->SetParent(this);

	if (m_strPpTemplateFile.GetLength() <= 4)
	{
		return FALSE;
	}

	//规约模板对象
	CString strFile = strPpTemplateFile;

	GetFileAbsPath(strFile,_T("Template"));//zhouhj 2025.2.22
	
	if (!m_pTemplate->OpenXmlFile(strFile))
	{
		return FALSE;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("pTemplate->OpenXmlFile=%d"), oTickCount32.GetTickCountLong(TRUE));


	//设备数据模型
	strFile = strPpDeviceFile;

	LoadDeviceFile(strFile);

	if (!m_pTemplate->IsTemplateValid())
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                , g_sLangTxt_PrtcTempFileError.GetString()/*L"规约模板文件\"%s\"  错误"*/
                ,  strPpTemplateFile.GetString());
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("pTemplate->OpenXmlFileLoadDeviceFile=%d"), oTickCount32.GetTickCountLong(TRUE));

// 	CExBaseList *pDevice = m_pTemplate->GetDevice();
// 	const char *pszScript = scipt_SerializeAllScript(m_pTemplate, pDevice);

// #ifdef _LUA_IN_DEVBASEAPP_
// 
// #else
// 	lua_State *pLua = _PpEngineData_Get_Lua(m_pLua);
// 	CExBaseList *pDevice = m_pTemplate->GetDevice();
// 	const char *pszScript = scipt_SerializeAllScript(m_pTemplate, pDevice);
// 
// #if 1
// 	CString strLuaFile;
// 	strLuaFile = _P_GetBinPath();
// 	strLuaFile += _T("PpEngine_Lua.txt");
// 	CFile file;
// 	file.Open(strLuaFile, CFile::modeCreate | CFile::modeWrite);
// 	file.Write(pszScript, strlen(pszScript));
// 	file.Close();
// #endif
// 
// 	//组织脚本
// 	int nErr = luaL_loadstring(pLua, pszScript);
// 
// 	if (nErr)
// 	{
// 		CString strSyntax;
// 		strSyntax = lua_tostring(pLua, -1);
// 		lua_pop(pLua, 1);
// 
// 		CLogPrint::LogString(XLOGLEVEL_ERROR, strSyntax);
// 	}
// 	else
// 	{
// 		nErr = lua_pcall(pLua, 0, LUA_MULTRET, 0);
// 	}
// 
// #endif

	return IsEngineDataValid();
}


long CPpEngineData::GetSendTickLong()
{
	return m_oSendTick.GetTickCountLong(FALSE);
}

long CPpEngineData::GetRecvTickLong()
{
	return m_oRecvTick.GetTickCountLong(FALSE);
}

void CPpEngineData::ResetSendTick()
{
	m_oSendTick.Enter();
}

void CPpEngineData::ResetRecvTick()
{
	m_oRecvTick.Enter();
}

//lijunqing 2024-12-15 22:29
CString dvm_file_GetFilePath(const CString &strDeviceFile)
{
    CString strTemp, strFile;
    strTemp = GetPathFileNameFromFilePathName(strDeviceFile);

    if (strTemp.GetLength() == 0)
    {
        strTemp = strDeviceFile;
    }

    //Library
    strFile = _P_GetLibraryPath();
    strFile += strTemp;

    if (IsFileExist(strFile))
    {
        CLogPrint::LogString(XLOGLEVEL_TRACE, strFile);
        return strFile;
    }

    strFile = _P_GetInstallPath();
    strFile += _T("e-Protocol/Library/");
    strFile += strTemp;
    CLogPrint::LogString(XLOGLEVEL_TRACE, strFile);

    return strFile;
}


BOOL CPpEngineData::GetFileAbsPath(CString &strFile,const CString &strModuleFolder)
{
	if (IsFileExist(strFile))//先判断参数1的路径是否已经为绝对路径,如果是则直接使用
	{
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "GetFileAbsPath(strFile == %s) IsFileExist1",  strFile.GetString());
		return TRUE;
	}

	CString strInstPath,strSystemPath,strPath;
	strInstPath = _P_GetInstallPath();
	strInstPath += _T("e-Protocol/");
	strInstPath += strModuleFolder;
	strInstPath += "/";//对应安装路径文件夹,固定到e-Protocol\文件夹下的Template/或library/文件夹
	strSystemPath = _P_GetSystemPath();
	strSystemPath += strModuleFolder;//对应系统路径文件夹,固定到系统文件夹下的Template/或library/文件夹
	strSystemPath += "/";
	strPath = strInstPath + strFile;//先使用安装路径文件夹

	if (IsFileExist(strPath))
	{
		strFile = strPath;
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "GetFileAbsPath(strFile == %s) IsFileExist2",  strFile.GetString());
		return TRUE;
	}
//	else
//	{
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "GetFileAbsPath(strPath == %s) IsFileNotExist2",  strPath.GetString());
//	}

	strPath = strSystemPath + strFile;//再使用系统安装路径文件夹判断

	if (IsFileExist(strPath))
	{
		strFile = strPath;
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "GetFileAbsPath(strFile == %s) IsFileExist3",  strFile.GetString());
		return TRUE;
	}
//	else
//	{
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "GetFileAbsPath(strPath == %s) IsFileNotExist3",  strPath.GetString());
//	}

	CString strTemp;
	strTemp = GetPathFileNameFromFilePathName(strFile);//以上方法都不行的情况下,提取strFile的最后面的文件名进行拼接匹配


	if (strTemp.GetLength() == 0)//如果最后一级为文件夹路径则返回
	{
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "GetFileAbsPath(strFile == %s) strTemp.GetLength() == 0",  strFile.GetString());
		return FALSE;
	}

	strPath = strInstPath + strTemp;//采用文件名与安装路径文件夹拼接匹配

	if (IsFileExist(strPath))
	{
		strFile = strPath;
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "GetFileAbsPath(strFile == %s) IsFileExist4",  strFile.GetString());
		return TRUE;
	}

	strPath = strSystemPath + strTemp;//采用文件名与系统路径文件夹拼接匹配

	if (IsFileExist(strPath))
	{
		strFile = strPath;
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "GetFileAbsPath(strFile == %s) IsFileExist5",  strFile.GetString());
		return TRUE;
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "GetFileAbsPath(strFile == %s) IsFileNotExist",  strFile.GetString());
	return FALSE;
}

BOOL CPpEngineData::LoadDeviceFile(const CString &strDeviceFile)
{
	CString strFile = strDeviceFile;
	BOOL bSucc = FALSE;

	if (strFile.GetLength() <= 4)
	{
		strFile = m_pTemplate->GetDeviceFilePathForDebug();
	}

	GetFileAbsPath(strFile,_T("Library"));
	bSucc = m_pDevcieModel->OpenFile(strFile);

	m_pPpDeviceRef = m_pDevcieModel->GetPpDevice();
	m_pDeviceCmmConfigRef = m_pDevcieModel->GetDeviceCmmConfig();
	m_pTemplate->SetDevice(m_pPpDeviceRef);

	if (m_pPpDeviceRef == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                 , g_sLangTxt_CreatDevFail.GetString()/*L"创建设备对象失败，设备点表文件\"%s\"错误"*/
                 ,  strFile.GetString());
	}

	//创建设备数据模型中的集合节点，即node-type=LIST的节点
	CreateDeviceListNodes();

	//初始化额定值的数据变量
	InitNomVarsScript();

	ValidateDeviceModel();

	return TRUE;
}

//2020-5-19  lijunqing
BOOL CPpEngineData::InitCmmConfig(CDataGroup *pGroup)
{
    m_pPpDeviceRef = m_pDevcieModel->GetPpDevice();
    m_pDevcieModel->InitCmmConfig(pGroup);
    m_pDeviceCmmConfigRef = m_pDevcieModel->GetDeviceCmmConfig();

    return TRUE;
}

void CPpEngineData::CreateDeviceFileForDebug()
{

}

void CPpEngineData::ValidateDeviceModel()
{
	if (m_pPpDeviceRef == NULL)
	{
		return;
	}

	CDvmDevice *pDvmDevice = m_pPpDeviceRef->m_pDevice;
	CDvmLogicDevice *pLDevice = (CDvmLogicDevice*)pDvmDevice->FindByID(g_strReportLogicDeviceID);
	
	if (pLDevice == NULL)
	{
		pLDevice = new CDvmLogicDevice();
		pLDevice->m_strName = g_strReportLogicDeviceID;
		pLDevice->m_strID = g_strReportLogicDeviceID;
		pLDevice->m_nIndex = 65535;
		pDvmDevice->AddNewChild(pLDevice);
	}

	CDvmDataset *pDataset = (CDvmDataset*)pLDevice->FindByID(g_strReportPackageID);

	if (pDataset == NULL)
	{
		pDataset = new CDvmDataset();
		pDataset->m_strName = g_strReportPackageID;
		pDataset->m_strID = g_strReportPackageID;
		pDataset->m_nIndex = 65535;
		pLDevice->AddNewChild(pDataset);
	}

	m_pPpRecordMngr->SetPackageDataset(pDataset);

	pDataset = (CDvmDataset*)pLDevice->FindByID(g_strReportSOEID);

	if (pDataset == NULL)
	{
		pDataset = new CDvmDataset();
		pDataset->m_strName = g_strReportSOEID;
		pDataset->m_strID = g_strReportSOEID;
		pDataset->m_nIndex = 65534;
		pLDevice->AddNewChild(pDataset);
	}
}

BOOL CPpEngineData::IsConnectSuccessful()
{
	if (m_pEngineThread == NULL)
	{
		return FALSE;
	}

	CPpEngineThreadBase *pThread = (CPpEngineThreadBase*)m_pEngineThread;

	return pThread->IsConnectSuccessful();
}

BOOL CPpEngineData::IsConnecting()
{
	if (m_pEngineThread == NULL)
	{
		return FALSE;
	}

	CPpEngineThreadBase *pThread = (CPpEngineThreadBase*)m_pEngineThread;

	return pThread->IsConnecting();
}

BOOL CPpEngineData::IsEngineDataValid()
{
	if (m_pPpDeviceRef == NULL|| m_pTemplate == NULL)
	{
		return FALSE;
	}

// 	if (m_pDevice->GetCount() <= 1)
// 	{
// 		return FALSE;
// 	}

	if (! m_pTemplate->IsTemplateValid())
	{
		return FALSE;
	}

	return TRUE;
}

//创建设备数据模型中的集合节点，即node-type=LIST的节点
void CPpEngineData::CreateDeviceListNodes()
{
	
}

CPpEngineData::~CPpEngineData()
{
	if (m_pEngineThread != NULL)
	{
		//m_pEngineThread->SuspendThread();
		//delete m_pEngineThread;
		//m_pEngineThread = NULL;
		m_pEngineThread->PostThreadMessage(WM_QUIT, 0, 0);
	}

	if (m_pDevcieModel != NULL)
	{
		delete m_pDevcieModel;
		m_pDevcieModel = NULL;
	}

	if (m_pTemplate != NULL)
	{
		delete m_pTemplate;
		m_pTemplate = NULL;
	}

	if (m_pPpRecordMngr != NULL)
	{
		delete m_pPpRecordMngr;
		m_pPpRecordMngr = NULL;
	}

	m_pEngineXvm->TS_ShutDown();
	//m_pXvm->TS_UnloadScript();
	delete m_pEngineXvm;
// #ifdef _LUA_IN_DEVBASEAPP_
// #else
// 	CloseLua();
// #endif

#ifndef _PP_DEV_MODE_
	m_listTrigers.RemoveAll();
	m_listTrigerScriptRun.RemoveAll();
	m_listTrigerScriptTimerRun.RemoveAll();
#endif
}

void CPpEngineData::OnProcedureEnd(const CString &strProcedureID, long wPara, long lPara)
{
	//shaolei ljq 2023-9-13 如果都是PP_PROCEDURE_RUN_STATE_NOMAL，表示通讯结束
	if (wPara == PP_PROCEDURE_RUN_STATE_NOMAL && lPara == PP_PROCEDURE_RUN_STATE_NOMAL)
	{
		wPara = engineCommFinish;
		lPara = engineCommFinish;
	}

	if (m_pPoDeviceProcedureInterface != NULL)
	{
		m_pPoDeviceProcedureInterface->OnProcedureEnd(strProcedureID, wPara, lPara);
	}

	m_oMessageMngr.PostMessageByID(strProcedureID, wPara, lPara);
}

void CPpEngineData::OnDeviceConnectFinish(BOOL bConnectSuccessful)
{
	ASSERT (g_pTheEngineApp != NULL);

    //TRACE(_T("\r\n\r\nPpEngineData::OnDeviceConnectFinish(%d)\r\n\r\n"), bConnectSuccessful);
	m_oSystemMsgSendRegister.m_wParam = bConnectSuccessful;
	m_oSystemMsgSendRegister.m_lParam = bConnectSuccessful;

// #ifdef _PSX_QT_LINUX_
    if (m_pPoDeviceProcedureInterface != NULL)
    {
        if (bConnectSuccessful)
        {
            m_pPoDeviceProcedureInterface->OnSystemMsg(0, engineConnectDeviceSuccessful);
        }
        else
        {
            m_pPoDeviceProcedureInterface->OnSystemMsg(0, engineConnectDeviceFailed);
        }
    }
// #endif

//    if (    m_pPxiDeviceCommCmdMessage != NULL)
//    {
//		if (bConnectSuccessful)
//		{
//			m_pPxiDeviceCommCmdMessage->OnSysMessage(0, engineConnectDeviceSuccessful);
//		}
//		else
//		{
//			m_pPxiDeviceCommCmdMessage->OnSysMessage(0, engineConnectDeviceFailed);
//		}
        
//    }

    if (bConnectSuccessful)
    {
        m_oSystemMsgSendRegister.PostMessage(0, engineConnectDeviceSuccessful);
    }
    else
    {
        m_oSystemMsgSendRegister.PostMessage(0, engineConnectDeviceFailed);
    }

#ifndef _PSX_IDE_QT_
	if (bConnectSuccessful)
	{
		if (m_pRefTreeCtrl != NULL)
		{
			m_pRefTreeCtrl->SetItemImage((HTREEITEM)m_dwItemData, 2,2);
		}

		CWnd *pWnd = AfxGetMainWnd();
		
		if (pWnd != NULL)
		{
			pWnd->PostMessage(WM_CONNECT_SUCCESS, 0, 0);
		}
	}
	else
	{
		if (m_pRefTreeCtrl != NULL)
		{
			m_pRefTreeCtrl->SetItemImage((HTREEITEM)m_dwItemData, 3,3);
		}
	}
#endif
}

void CPpEngineData::OnDeviceDisConnectFinish(BOOL bConnectSuccessful)
{
#ifndef _PSX_IDE_QT_
	if (m_pRefTreeCtrl == NULL)
	{
		return;
	}

    if (::IsWindow(m_pRefTreeCtrl->m_hWnd))
	{
		m_pRefTreeCtrl->SetItemImage((HTREEITEM)m_dwItemData, 1,1);
	}
#endif
}

BOOL CPpEngineData::IsThreadExit()
{
	if (m_pEngineThread == NULL)
	{
		return TRUE;
	}

	return ((CPpEngineThreadBase*)m_pEngineThread)->IsThreadExitExtern();
}

BOOL CPpEngineData::ExitEngineThread()
{
#ifndef _PSX_IDE_QT_
	CWnd *pWnd = AfxGetMainWnd();

    if (IsThreadExit() && pWnd != NULL)
	{
		pWnd->PostMessage(WM_DISCONNECT_SUCCESS, (WPARAM)this, (LPARAM)this);
		return TRUE;
	}
#endif

	if (m_pEngineThread != NULL)
	{
		((CPpEngineThreadBase*)m_pEngineThread)->SetDeleteEngineDataInExit(TRUE);
		((CPpEngineThreadBase*)m_pEngineThread)->ExitEngineThread();
		return FALSE;
	}
	else
	{
		return TRUE;
	}

}



const CString CPpEngineData::g_strNomVariableUn = _T("Un");
const CString CPpEngineData::g_strNomVariableIn = _T("In");
const CString CPpEngineData::g_strNomVarKeyID_UNom = _T("UNom");
const CString CPpEngineData::g_strNomVarKeyID_INom = _T("INom");

void CPpEngineData::InitNomVarsScript()
{
	m_strNomVarsScript.Empty();
	CString strVal;

	if (m_pPpDeviceRef == NULL)
	{
		return;
	}

	if (m_pPpDeviceRef->GetDeviceAttribute(g_strNomVarKeyID_UNom, strVal))
	{
        m_strNomVarsScript.AppendFormat(_T("%s=%s;"),g_strNomVariableUn.GetString(), strVal.GetString());
	}

	if (m_pPpDeviceRef->GetDeviceAttribute(g_strNomVarKeyID_INom, strVal))
	{
        m_strNomVarsScript.AppendFormat(_T("%s=%s;"),g_strNomVariableIn.GetString(), strVal.GetString());
	}


	if (m_pPpDeviceRef->GetDeviceAttribute(g_strNomVariableUn, strVal))
	{
        m_strNomVarsScript.AppendFormat(_T("%s=%s;"),g_strNomVariableUn.GetString(), strVal.GetString());
	}

	if (m_pPpDeviceRef->GetDeviceAttribute(g_strNomVariableIn, strVal))
	{
        m_strNomVarsScript.AppendFormat(_T("%s=%s;"),g_strNomVariableIn.GetString(), strVal.GetString());
	}

}

void CPpEngineData::RunReset(CDvmDevice *pDvmDevice)
{
	if (pDvmDevice == NULL)
	{
		return;
	}

	CDvmLogicDevice *pLDevice = NULL;
	pLDevice = (CDvmLogicDevice*)pDvmDevice->FindByID(g_strReportLogicDeviceID);

	if (pLDevice == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                   , g_sLangTxt_RptDataSetUnExist.GetString()/*_T("Reset:报告数据集不存在【%s】")*/
                   , g_strReportLogicDeviceID.GetString());
		return;
	}

	POS pos = pLDevice->GetHeadPosition();
	CDvmDataset *pDataset = NULL;

	while (pos != NULL)
	{
		pDataset = (CDvmDataset *)pLDevice->GetNext(pos);
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                , g_sLangTxt_RptDataSet.GetString()/*_T("Reset:报告数据集【%d】=>>0")*/
                , pDataset->GetCount());

		//if (pDataset->m_strID != g_strReportPackageID)
		{
			pDataset->DeleteAll();
		}
	}
}

void CPpEngineData::RunReset()
{
	//复归全部报文
	long nRecordCount = m_pPpRecordMngr->GetCount();
	m_pPpRecordMngr->DeleteAllPackage();
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE
              , g_sLangTxt_ResetMessage.GetString()/*_T("Reset:报文抓包【%d】=>>0")*/
              , nRecordCount);

	//清除报告
	//g_oDeviceBindListCriticSection
	CAutoSimpleLock oLock(g_oDeviceBindListCriticSection);
	CDvmLogicDevice *pLDevice = NULL;

	if (m_pPpDeviceRef->m_pDevice != NULL)
	{
		RunReset(m_pPpDeviceRef->m_pDevice);
	}
	
	if (m_pPpDeviceRef->IsDeviceModel_Single())
	{
	}
	else
	{
		if (m_pPpDeviceRef->m_pDevices == NULL)
		{
			return;
		}

		POS pos = m_pPpDeviceRef->m_pDevices->GetHeadPosition();
		CDvmDevice *pDvmDevice = NULL;

		while (pos != NULL)
		{
			pDvmDevice = (CDvmDevice *)m_pPpDeviceRef->m_pDevices->GetNext(pos);
			RunReset(m_pPpDeviceRef->m_pDevice);
		}
	}
}

long CPpEngineData::PPS_InitStrTok(char *pszString, char *pControl)
{
	char ch = '\n';
	char *p = pControl;

	if (*pControl != 0)
	{
		ch = *pControl;
		p = pControl + 1;
	}

	m_oStringTokenizer.Init(pszString, ch);

	while (*p != 0)
	{
		m_oStringTokenizer.Format(*p);
		p++;
	}

	return m_oStringTokenizer.GetStringsCount();
}

long CPpEngineData::PPS_StrTokCount()
{
	return m_oStringTokenizer.GetStringsCount();
}

const char* CPpEngineData::PPS_StrTokIndex(long nIndex)
{
	return (char*)m_oStringTokenizer.GetToken(nIndex);
}

const char* CPpEngineData::PPS_StrTokNext()
{
	return m_oStringTokenizer.NextToken();
}



//////////////////////////////////////////////////////////////////////////
//CPpEngineDataMngrCntr
CPpEngineDataMngrCntr::CPpEngineDataMngrCntr(void)
{
	m_strName = _T("设备列表");
}

CPpEngineDataMngrCntr::~CPpEngineDataMngrCntr(void)
{
}

CPpEngineData*  CPpEngineDataMngrCntr::Create(const CString &strPpTemplateFile, const CString &strDeviceFile)
{
	CPpEngineData *pNew = new CPpEngineData(strPpTemplateFile, strDeviceFile);

// 	CString strPpFileName, strDvmFileName;
// 	strPpFileName = GetPathFileNameFromFilePathName(strPpTemplateFile);
// 	strDvmFileName = GetPathFileNameFromFilePathName(strDeviceFile);
// 
// 	long nIndex = 1;
// 	pNew->m_strID.Format(_T("%s+%s(%d)"), strPpFileName, strDvmFileName, nIndex);
// 
// 	while (TRUE)
// 	{
// 		if (FindByID(pNew->m_strID) == NULL)
// 		{
// 			break;
// 		}
// 
// 		pNew->m_strID.Format(_T("%s+%s(%d)"), strPpFileName, strDvmFileName, nIndex);
// 		nIndex++;
// 	}

	pNew->m_strID = Pp_GetPopCfgDeviceName(strPpTemplateFile, strDeviceFile, this);
	pNew->m_strName = pNew->m_strID;
	AddTail(pNew);

	return pNew;
}

CPpEngineData* CPpEngineDataMngrCntr::Find(CPpDvmDevice *pDevice)
{
	CPpEngineData *pFind = NULL;
	CPpEngineData *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CPpEngineData*)GetNext(pos);

		if (pDevice == p->m_pPpDeviceRef)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CPpEngineData* CPpEngineDataMngrCntr::Find2(CDvmDevice *pDevice)
{
	CPpEngineData *pFind = NULL;
	CPpEngineData *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CPpEngineData*)GetNext(pos);

		if (pDevice == p->m_pPpDeviceRef->GetDeviceModel())
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CPpEngineData* CPpEngineDataMngrCntr::Find(CPpTemplate *pTemplate)
{
	CPpEngineData *pFind = NULL;
	CPpEngineData *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CPpEngineData*)GetNext(pos);

		if (pTemplate == p->m_pTemplate)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CPpEngineData* CPpEngineDataMngrCntr::Find(CDeviceCmmConfig *pCmmConfig)
{
	CPpEngineData *pFind = NULL;
	CPpEngineData *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CPpEngineData*)GetNext(pos);

		if (pCmmConfig == p->m_pDeviceCmmConfigRef)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

//###error###
void CPpEngineDataMngrCntr::InsertNodeToTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent)
{
#ifndef _PSX_IDE_QT_
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(m_strName, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);

	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CPpEngineData *pEngineData = (CPpEngineData *)GetNext(pos);
		ASSERT(pEngineData != NULL);
		CPpDvmDevice *pDevice = pEngineData->m_pPpDeviceRef;
		ASSERT(pDevice != NULL);

		if (pDevice != NULL)
		{
			pDevice->InsertTreeCtrl(pTreeCtrl, (HTREEITEM)m_dwItemData);
		}

	}

    pTreeCtrl->Expand((HTREEITEM)m_dwItemData, TVE_EXPAND);
#endif
}

void CPpEngineDataMngrCntr::ConnectDeviceAll()
{
	CPpEngineData *pEngineData = NULL;
	POS pos = GetHeadPosition();
	CPpEngineThreadBase *pThread = NULL;

	while (pos != NULL)
	{
		pEngineData = (CPpEngineData*)GetNext(pos);
		pThread = (CPpEngineThreadBase*)pEngineData->m_pEngineThread;
	
		if (pThread != NULL)
		{
			pThread->PostConnectDeviceMsg();
		}
	}
}

BOOL CPpEngineDataMngrCntr::IsAllDeviceConnectFinished()
{
	BOOL bTrue = TRUE;
	CPpEngineData *pEngineData = NULL;
	POS pos = GetHeadPosition();
	CPpEngineThreadBase *pThread = NULL;

	while (pos != NULL)
	{
		pEngineData = (CPpEngineData*)GetNext(pos);
		
		if (pEngineData->IsConnecting())
		{
			bTrue = FALSE;
			break;
		}
	}

	return bTrue;
}

void CPpEngineDataMngrCntr::WaitAllDeviceConnectFinished()
{
	CTickCount32 oTick;
	long nIndex = 0;

	if (IsAllDeviceConnectFinished())
	{
		return;
	}

	while (TRUE)
	{
		oTick.DoEvents(50);

		if (IsAllDeviceConnectFinished())
		{
			break;
		}

		if (nIndex > 200)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("系统错误，与装置一致处于连接状态"));
			break;
		}
	}
}

BOOL CPpEngineDataMngrCntr::IsAllDeviceEngineThreadExit()
{
	BOOL bTrue = TRUE;
	CPpEngineData *pEngineData = NULL;
	POS pos = GetHeadPosition();
	CPpEngineThreadBase *pThread = NULL;

	while (pos != NULL)
	{
		pEngineData = (CPpEngineData*)GetNext(pos);

		if (!pEngineData->IsThreadExit())
		{
			bTrue = FALSE;
			break;
		}
	}

	return bTrue;
}

void CPpEngineDataMngrCntr::ExitAllEngineThread()
{
	CPpEngineData *pEngineData = NULL;
	POS pos = GetHeadPosition();
	CPpEngineThreadBase *pEngineThread = NULL;

	while (pos != NULL)
	{
		pEngineData = (CPpEngineData*)GetNext(pos);
		pEngineData->ExitEngineThread();

		if (pEngineThread != NULL)
		{
			pEngineThread = (CPpEngineThreadBase*)pEngineData->m_pEngineThread;
			pEngineThread->WaitDeviceConnectFinished();
		}
	}
}


void CPpEngineDataMngrCntr::WaitExitAllEngineThread()
{
	CTickCount32 oTick;
	long nIndex = 0;

	if (IsAllDeviceEngineThreadExit())
	{
		return;
	}

	while (TRUE)
	{
		oTick.DoEvents(50);

		if (IsAllDeviceEngineThreadExit())
		{
			break;
		}

		if (nIndex > 200)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("系统错误，与装置断开连接不成功"));
			break;
		}
	}
}

//批量修改
void CPpEngineDataMngrCntr::BatchEditData(CDvmDataset *pSrcDataset)
{
	CPpEngineData *pEngineData = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pEngineData = (CPpEngineData *)GetNext(pos);
		BatchEditData(pEngineData, pSrcDataset);
	}
}

void CPpEngineDataMngrCntr::BatchEditData(CDvmData *pSrcData, const CString &strDatasetID)
{
	CPpEngineData *pEngineData = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pEngineData = (CPpEngineData *)GetNext(pos);
		BatchEditData(pEngineData, strDatasetID, pSrcData);
	}
}

void CPpEngineDataMngrCntr::BatchEditData(CDvmDataset *pDestDataset, CDvmDataset *pSrcDataset)
{
	POS pos = pSrcDataset->GetHeadPosition();
	CDvmData *pDest = NULL;
	CDvmData *pSrc = NULL;

	while (pos != NULL)
	{
		pSrc = (CDvmData *)pSrcDataset->GetNext(pos);

		if (pSrc->m_nChange == 0)
		{
			continue;
		}

		BatchEditData(pDestDataset, pSrc);
	}
}

void CPpEngineDataMngrCntr::BatchEditData(CDvmDataset *pDestDataset, CDvmData *pSrcData)
{
	CDvmData *pDest = NULL;

	pDest = (CDvmData *)pDestDataset->FindByID(pSrcData->m_strID);

	//相同的一个数据，不修改
	if (pDest == pSrcData)
	{
		return;
	}

	if (pDest != NULL)
	{
#ifdef _DVM_VALUE_USE_CHAR_
		wcscpy(pDest->m_strValue, pSrcData->m_strValue);
#else
		pDest->m_strValue = pSrcData->m_strValue;
#endif
		pDest->m_nChange = 1;
	}
}

void CPpEngineDataMngrCntr::BatchEditData(CPpEngineData *pEngineData, CDvmDataset *pSrcDataset)
{
	if (pEngineData->m_pTemplate->IsMultiDeviceMode())
	{
		return;
	}

	CDvmDevice *pDevice = (CDvmDevice*)pEngineData->m_pTemplate->GetDevice();
	POS posLd = pDevice->GetHeadPosition();
	CDvmLogicDevice *pLd = NULL;

	while (posLd != NULL)
	{
		pLd = (CDvmLogicDevice *)pDevice->GetNext(posLd);
		POS posDs = pLd->GetHeadPosition();
		CDvmDataset *pDsDest = NULL;

		while (posDs != NULL)
		{
			pDsDest = (CDvmDataset *)pLd->GetNext(posDs);

			if (pDsDest->m_strID == pSrcDataset->m_strID)
			{
				BatchEditData(pDsDest, pSrcDataset);
			}
		}
	}
}

void CPpEngineDataMngrCntr::BatchEditData(CPpEngineData *pEngineData, const CString &strDatasetID, CDvmData *pSrcData)
{
	if (pEngineData->m_pTemplate->IsMultiDeviceMode())
	{
		return;
	}

	CDvmDevice *pDevice = (CDvmDevice*)pEngineData->m_pTemplate->GetDevice();
	POS posLd = pDevice->GetHeadPosition();
	CDvmLogicDevice *pLd = NULL;

	while (posLd != NULL)
	{
		pLd = (CDvmLogicDevice *)pDevice->GetNext(posLd);
		POS posDs = pLd->GetHeadPosition();
		CDvmDataset *pDsDest = NULL;

		while (posDs != NULL)
		{
			pDsDest = (CDvmDataset *)pLd->GetNext(posDs);

			//如果传入了ID，则判断数据集ID，否则不判断
			if (strDatasetID.GetLength() > 0)
			{
				if (pDsDest->m_strID == strDatasetID)
				{
					BatchEditData(pDsDest, pSrcData);
				}
			}
			else
			{
				BatchEditData(pDsDest, pSrcData);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// 
// #ifdef _LUA_IN_DEVBASEAPP_
// 
// #else
BOOL CPpEngineData::BuildScript(const char *pszScript, long nBufferLen)
{
	CTScriptParser oTScriptParser;
	CTAsmParser oTasmParser;
	CTickCount32 oTickCount32;

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Build script: parse script......"));
#ifdef _PP_DEV_MODE_
	long nErrors = oTScriptParser.ParseText(pszScript, "PpDev");
#else
	long nErrors = oTScriptParser.ParseText(pszScript, "PpEngine");
#endif
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Build script: parse script:[%d]"), oTickCount32.GetTickCountLong(TRUE));

	if (nErrors > 0)
	{
		CTSyntaxs *pSyntaxs = oTScriptParser.GetTSyntaxs();
		CString strSyntax;
		//pSyntax->GetSyntax(strSyntax);
		POS pos = pSyntaxs->GetHeadPosition();
		CTSyntax *pSyntax = NULL;

		while (pos != NULL)
		{
			strSyntax.Empty();
			pSyntax = (CTSyntax*)pSyntaxs->GetNext(pos);
			pSyntax->GetSyntax(strSyntax);
			CLogPrint::LogString(pSyntax, XLOGLEVEL_TRACE, strSyntax);
		}

		return FALSE;
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Build script: ParseAsm......"));
	oTScriptParser.ParseAsm(&oTasmParser);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Build script: ParseAsm [%d]"), oTickCount32.GetTickCountLong(TRUE));
	CWSerializeBuff oBuffer;
	oTasmParser.WriteToBuffer(oBuffer);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Build script: WriteToBuffer [%d]"), oTickCount32.GetTickCountLong(TRUE));

	//保存到二进制文件
	CString strFile;
	strFile = m_pTemplate->GetXvmTasmExeFile();
	oBuffer.WriteToFile(strFile);

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Build script: Load script......"));
	m_pEngineXvm->TS_UnloadScript();
	int iErrorCode = m_pEngineXvm->TS_LoadScriptFromBuffer(oBuffer);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Build script: Load script:%d"), oTickCount32.GetTickCountLong(TRUE));

	if ( iErrorCode != TS_LOAD_OK )
	{
		return FALSE;
	}

	return TRUE;
}

	//20170304  组织脚本
BOOL CPpEngineData::BuildScript()
{
#ifdef _PP_DEV_MODE_
	BuildScript(m_pTemplate);
#else
	//首先加载二进制的exe文件，如果加载成功，则返回，否则编译
//#ifndef _PSX_IDE_QT_
	CString strFile;
	strFile = m_pTemplate->GetXvmTasmExeFile();
	CWSerializeBuff oBuffer;
	
	if (oBuffer.ReadFromFile(strFile))
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Build script: Load script......"));
		m_pEngineXvm->TS_UnloadScript();
		int iErrorCode = m_pEngineXvm->TS_LoadScriptFromBuffer(oBuffer);

		if ( iErrorCode == TS_LOAD_OK )
		{
			long nScriptIndex = 0;
			g_oPpXvmScriptBuilder.xvm_script_SerializeScriptFunc(m_pTemplate, nScriptIndex);
			return TRUE;
		}
	}
//#endif

	BuildScript(m_pTemplate);
#endif


	return TRUE;
}

BOOL CPpEngineData::BuildScript(CExBaseList *pPpList)
{
	//2020-06-02  lijunqing
	g_oPpXvmScriptBuilder.xvm_script_ResetBuffer();

	CTickCount32 oTickCount32;
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Build script: Add all script to string buffer"));

	//2020-06-02  lijunqing
	CStringSerializeBuffer *pBuffer = g_oPpXvmScriptBuilder.xvm_script_StringSerializeBuffer();
	m_pEngineXvm->SerializeHostAPIFuncs(*pBuffer);
	long nScriptIndex = 0;
	const char *pszScript = NULL;
	
	if (pPpList->GetClassID() == PPCLASSID_PPSCRIPT)
	{
		//2020-06-02  lijunqing
		pszScript = g_oPpXvmScriptBuilder.xvm_script_SerializeScript((CPpScript*)pPpList, nScriptIndex);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Build script: Add all script to string buffer template"));
		//2020-06-02  lijunqing
		pszScript = g_oPpXvmScriptBuilder.xvm_script_SerializeScript(pPpList, nScriptIndex);
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Build script: Add all script to string buffer project"));
		SerializeTrigerScript(nScriptIndex);
	}

	//2020-06-02  lijunqing
	long nBufferLen = g_oPpXvmScriptBuilder.xvm_script_GetBufferLength();
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Build script: Add all script to string buffer finish=%d"), nBufferLen);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Build script: %d"), oTickCount32.GetTickCountLong());

	BOOL bRet = BuildScript(pszScript, nBufferLen);

#ifdef _PP_DEV_MODE_
	if (bRet)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Build script: Success......"));
	}
#endif

	return bRet;
}


long CPpEngineData::CompileScript(CPpScript *pScript, const CString &strVariables)
{
	m_pPpScript = pScript;

	if (pScript->m_strScript.GetLength() < 6)
	{
		return 1;
	}

// 	xvm_script_ResetBuffer();
// 	long nScriptIndex = 0;
// 	const char *pszScript = xvm_script_SerializeScript(pScript, nScriptIndex);
// 	long nBufferLen = xvm_script_GetBufferLength();
// 
// 	BuildScript(pszScript, nBufferLen);
	if (BuildScript(pScript))
	{
		RunScript(pScript/*, strVariables, NULL*/);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Script Return = %d"), pScript->m_dwReturn);
	}

	return 0;
}


//脚本执行，函数返回，结束互斥处理
long CPpEngineData::RunScript(CPpScript *pScript/*, const CString &strVariables, CBbVariables *pVariables*/)
{
	// 执行脚本
	m_pPpScript = pScript;
	pScript->m_dwReturnType = OPERAND_TYPE_INT;
	pScript->m_dwReturn = 1;

	if (m_pPpScript->m_pszFuncName[0] == 0)
	{
		return 1;
	}

	m_pEngineXvm->TS_StartScript();
	m_pEngineXvm->TS_CallScriptFunc ( m_pPpScript->m_pszFuncName );
	pScript->m_dwReturnType = m_pEngineXvm->m_Script._RetVal.iType;
	pScript->m_dwReturn = m_pEngineXvm->TS_GetReturnValueAsInt( );

//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s=%d"), m_pPpScript->m_strFuncName, oTickcount.GetTickCountLong());

	return pScript->m_dwReturn;

// 	// 首先做互斥处理
// 	lua_State *pLua = _PpEngineData_Get_Lua(m_pLua);
// 
// 
// 	if (pScript == NULL || pLua == NULL)
// 	{
// 		return 0;
// 	}
// 
// 	if (pScript->m_strFuncName.GetLength() == 0)
// 	{
// 		return 0;
// 	}
// 
// // 	CString strTemp = strVariables+L"      \n";
// // 	strTemp +=pScript->m_strScript;
// // 	strTemp += L"        ";
// // 	CString_to_char(strTemp, m_pScriptBuffer);
// // 	int nErr = luaL_loadstring(pLua, m_pScriptBuffer);
// // 
// // 	if (nErr)
// // 	{
// // 		pScript->m_strSyntax = lua_tostring(pLua, -1);
// // 		lua_pop(pLua, 1);
// // 
// // 		PPS_LogScriptPath(pScript);
// // 
// // 		CLogPrint::LogString(XLOGLEVEL_ERROR, pScript->m_strSyntax);
// // 	}
// // 	else
// // 	{
// // 		nErr = lua_pcall(pLua, 0, LUA_MULTRET, 0);
// // 
// // 		if (nErr)
// // 		{
// // 			pScript->m_strSyntax = lua_tostring(pLua, -1);
// // 			lua_pop(pLua, -1);
// // 
// // 			PPS_LogScriptPath(pScript);
// // 			CLogPrint::LogString(XLOGLEVEL_ERROR, pScript->m_strSyntax);
// // 		}
// // 		else
// // 		{
// // 			//获取脚本返回值
// // 			GetLuaReturn();
// // 
// // 			//获取变量的值
// // 			GetLuaGolbalVariables(pVariables);
// // 		}
// // 	}
// 
// 	/* the function name */
// 
// 	try
// 	{
// 		char strFuncName[MAX_PATH];
// 		ZeroMemory(strFuncName, MAX_PATH);
// 		CString_to_char(m_pPpScript->m_strFuncName, strFuncName);
// 		lua_getglobal(pLua, strFuncName);
// 		lua_call(pLua, 0, 1);
// 		GetLuaReturn();
// 	}
// 	catch (...)
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("LUA Script Error"));
// 	}
// 	
// 	
// 
// // 	if (pVariables != NULL)
// // 	{
// // 		CString strVarVals;
// // 		pVariables->GetVariablesString(strVarVals);
// // 		CLogPrint::LogString(XLOGLEVEL_TRACE, strVarVals);
// // 	}

	return 0;
}

BOOL CPpEngineData::InitTrigerScriptRun(CPpPackageDetail *pPkgDetail)
{
#ifdef _PP_DEV_MODE_
	return FALSE;
#else
	POS pos = m_listTrigers.GetHeadPosition();
	CPpCfgOptr *pOptr = NULL;

	while (pos != NULL)
	{
		pOptr = (CPpCfgOptr *)m_listTrigers.GetNext(pos);
		
		if (pPkgDetail->m_strID == pOptr->m_strPachageID)
		{
			m_listTrigerScriptRun.AddTail(pOptr->m_pPpScript);
			pOptr->EnterRun();
		}
	}

	return TRUE;
#endif
}

BOOL CPpEngineData::InitTrigerScriptTimerRun()
{
#ifdef _PP_DEV_MODE_
	return FALSE;
#else
	POS pos = m_listTrigers.GetHeadPosition();
	CPpCfgOptr *pOptr = NULL;

	while (pos != NULL)
	{
		pOptr = (CPpCfgOptr *)m_listTrigers.GetNext(pos);

		if (pOptr->m_nTDelay > 0 && pOptr->m_strPachageID.GetLength() == 0)
		{
			m_listTrigerScriptTimerRun.AddTail(pOptr->m_pPpScript);
			pOptr->EnterRun();
		}
	}

	return TRUE;
#endif
}

BOOL CPpEngineData::RunTrigerScript_Timer()
{
#ifdef _PP_DEV_MODE_
	return FALSE;
#else
	POS pos = m_listTrigers.GetHeadPosition();
	CPpCfgOptr *pOptr = NULL;

	while (pos != NULL)
	{
		pOptr = (CPpCfgOptr *)m_listTrigers.GetNext(pos);

		if (pOptr->CanRun())
		{
			//m_listTrigerScriptTimerRun.AddTail(pOptr->m_pPpScript);
			RunScript(pOptr->m_pPpScript);
			pOptr->EnterRun();
		}
	}

	return TRUE;
#endif
}

BOOL CPpEngineData::SerializeTrigerScript(long &nScriptIndex)
{
#ifdef _PP_DEV_MODE_
	return FALSE;
#else
	CPpEngineBaseApp *pApp = g_pTheEngineApp;
	pApp->SerializeTrigerScript(nScriptIndex, m_listTrigers, m_strID);
	return TRUE;
#endif
}

BOOL CPpEngineData::CanRunWPackageOnReceive()
{//2019-5-27  lijq
	return m_pTemplate->CanRunWPackageOnReceive();
}

// 
// void CPpEngineData::GetLuaReturn()
// {
// 	lua_State *pLua = _PpEngineData_Get_Lua(m_pLua);
// 	int top = lua_gettop(pLua);
// 
// 	//lua的编号从1开始，不是从0开始
// 	if (top < 1)
// 	{//如果没有返回值，则不处理
// 		m_pPpScript->m_dwReturnType = LUA_TBOOLEAN;
// 		m_pPpScript->m_dReturn = 1;
// 		return;
// 	}
// 
// 	int iPos = 1;
// 	int t = lua_type(pLua, iPos);   //lua的编号从1开始，不是从0开始
// 	m_pPpScript->m_dwReturnType = t;
// 
// 	switch (t) 
// 	{
// 	case LUA_TSTRING:  /* strings */
// 		m_pPpScript->m_strReturn = lua_tostring(pLua, iPos);
// 		break;
// 
// 	case LUA_TBOOLEAN:  /* booleans */
// 		m_pPpScript->m_dwReturn = lua_toboolean(pLua, iPos);
// 		break;
// 
// 	case LUA_TNUMBER:  /* numbers */
// 		m_pPpScript->m_dReturn = lua_tonumber(pLua,iPos);
// 		m_pPpScript->m_dwReturn = (DWORD)m_pPpScript->m_dReturn;
// 		break;
// 	default:  /* other values */
// 		break;
// 	}
// 
// 	//lua_pop(pLua, 1);
// 	lua_settop(pLua, 0);
// }
// 
// void CPpEngineData::GetLuaGolbalVariables(CBbVariables *pVariables)
// {
// 	if (pVariables == NULL)
// 	{
// 		return;
// 	}
// 
// 	lua_State *pLua = _PpEngineData_Get_Lua(m_pLua);
// 	char pszBuffer[MAX_PATH];
// 	POS pos = pVariables->GetHeadPosition();
// 	CBbVariable *pVariable = NULL;
// 
// 	//设置LUA堆栈
// 	while (pos != NULL)
// 	{
// 		pVariable = (CBbVariable*)pVariables->GetNext(pos);
// 		CString_to_char(pVariable->m_strID, pszBuffer);
// 		lua_getglobal(pLua, pszBuffer);
// 	}
// 
// 	//遍历LUA堆栈，获取变量的值
// 	int top = lua_gettop(pLua);
// 	int i = 0;
// 
// 	for (i = 1; i <= top; i++) 
// 	{ 
// 		int t = lua_type(pLua, i);
// 		pVariable = (CBbVariable*)pVariables->GetAtIndex(i-1);
// 
// 		//变量不存在
// 		if (pVariable == NULL)
// 		{
// 			break;
// 		}
// 
// 		switch (t) 
// 		{
// 		case LUA_TSTRING:  /* strings */
// 			pVariable->m_strValue = CString(lua_tostring(pLua, i));
// 			break;
// 
// 		case LUA_TBOOLEAN:  /* booleans */
// 			break;
// 
// 		case LUA_TNUMBER:  /* numbers */
// 			pVariable->m_strValue.Format(TEXT("%g"), lua_tonumber(pLua, i));
// 			break;
// 
// 		default:  /* other values */
// 			pVariable->m_strValue = L"";
// 			break;
// 
// 		}
// 
// 		//CLogPrint::LogFormatString(NULL, XLOGLEVEL_ERROR, _T("%s=%s"), pVariable->m_strID, pVariable->m_strValue);
// 	}
// 
// 	//清空堆栈
// 	lua_settop(pLua, 0);
// }
// 
// 
// 
// BOOL CPpEngineData::InitLua()
// {
// 	lua_State *pLua = _PpEngineData_Get_Lua(m_pLua);
// 
// 	if( pLua == NULL)  // 确保只会初始化一次 
// 	{ 
// 		pLua = luaL_newstate(); // 创建Lua状态 
// 
// 		if( pLua == NULL) 
// 		{
// 			return false; 
// 		}
// 
// 		luaL_openlibs( pLua ); // 为该Lua状态打开所有Lua库 
// 		luabind::open( pLua ); // 为该Lua状态打开luabind库 
// 
// 		m_pLua = pLua;
// 		BindFuncToLua();		//绑定全局脚本函数
// 	} 
// 
// 	return TRUE;
// }
// 
// void CPpEngineData::CloseLua()
// {
// 	lua_State *pLua = _PpEngineData_Get_Lua(m_pLua);
// 
// 	if (pLua != NULL)
// 	{
// 		lua_settop(pLua, 0);
// 		lua_close(pLua);
// 	}
// 
// 	m_pLua = NULL;
// }
// 
// 
// void CPpEngineData::BindFuncToLua()
// {
// 	lua_State *pLua = _PpEngineData_Get_Lua(m_pLua);
// 
// 	luabind::module( pLua ) 
// 		[ 
// 			luabind::def("GetValDataType", &script_GetCurrValueDataType ),
// 			luabind::def("GetValDataLen", &script_GetCurrValueDataLength ), 
// 			luabind::def("GetBbValLong", &script_GetBbCurrValue),
// 			luabind::def("GetBbValLong1", &script_GetBbCurrValue1),
// 			luabind::def("GetBbValLong2", &script_GetBbCurrValue2),
// 			luabind::def("SetBbValLong", &script_SetBbCurrValue),
// 			luabind::def("SetBbValLong1", &script_SetBbCurrValue1),
// 			luabind::def("SetBbValLong2", &script_SetBbCurrValue2),
// 			luabind::def("SetBbValStr", &script_SetBbCurrValueString),
// 			luabind::def("GetBbValStr", &script_GetBbCurrValueString),
// 			luabind::def("GetBbFdataStr", &script_GetBbFormatDataString),
// 			luabind::def("SetBbValFloat", &script_SetBbCurrValueFloat),
// 			luabind::def("GetBbValFloat", &script_GetBbCurrValueFloat),
// 			luabind::def("SetBbValByte", &script_SetBbCurrValueByte),
// 			luabind::def("GetBbValByte", &script_GetBbCurrValueByte),
// 			luabind::def("LAnd", &script_LAnd),
// 			luabind::def("LOr", &script_LOr),
// 			luabind::def("LNot", &script_LNot),
// 			luabind::def("LComp", &script_LComplement),
// 			luabind::def("LComp2", &script_LComplement2),
// 			luabind::def("LComp1", &script_LComplement1),
// 			luabind::def("LRComp", &script_LRComplement),
// 			luabind::def("LShift", &script_LShift),
// 			luabind::def("RShift", &script_RShift ),
// 			luabind::def("MkWord", &script_MkWord ), 
// 
// 			luabind::def("BcdToHex", &script_BcdToHex ),
// 			luabind::def("HexToBcd", &script_HexToBcd ), 
// 
// 			luabind::def("GetYear", &script_GetYear ),
// 			luabind::def("GetMonth", &script_GetMonth ), 
// 			luabind::def("GetDay", &script_GetDay ),
// 			luabind::def("GetHour", &script_GetHour), 
// 			luabind::def("GetMinute", &script_GetMinute ),
// 			luabind::def("GetSecond", &script_GetSecond ), 
// 			luabind::def("GetMSecond", &script_GetMillionSecond ), 
// 
// 			luabind::def("SetBbEnable", &script_SetByteBlockEnable),
// 			luabind::def("SetBbLen", &script_SetByteBlockLength),
// 			luabind::def("GetBbLen", &script_GetByteBlockLength),
// 			luabind::def("SetTimerLong", &script_SetTimerLong),
// 			luabind::def("GetValue", &script_GetValue),
// 			luabind::def("GetValueStr", &script_GetValueString),
// 			luabind::def("SetValueLong", &script_SetValueLong),
// 			luabind::def("SetValueDouble", &script_SetValueDouble),
// 			luabind::def("SetValueStr", &script_SetValueString),
// 			luabind::def("SetPkgLen", &script_SetPkgLen),
// 			luabind::def("SetPkgValid", &script_SetPkgValid),
// 			luabind::def("GetPkgLen", &script_GetPkgLen),
// 			luabind::def("GetPkgParsePos", &script_GetPkgParsePos),
// 			luabind::def("GetPkgNum", &script_GetPkgNum),
// 			luabind::def("SetBindDataL", &script_SetBindDataL),
// 			luabind::def("GetNextNdDataByAttr", &script_GetNextDeviceNodeDataByAttrValue),
// 			luabind::def("GetNdDataAttrL", &script_GetDeviceNodeDataAttrValueL),
// 			luabind::def("GetNdDataAttrD", &script_GetDeviceNodeDataAttrValueD),
// 			luabind::def("SetNdDatasAttr", &script_SetDeviceNodeDataAttrs),
// 			luabind::def("SetWBindDataL", &script_SetWBindDataL),
// 			luabind::def("InsertBindData", &script_InsertBindData),
// 			luabind::def("InsertBindDataset", &script_InsertBindDataset),
// 			luabind::def("InsertBindLogicDevice", &script_InsertBindLogicDevice),
// 			luabind::def("GetBindDataL", &script_GetBindDataL),
// 			luabind::def("GetWBindDataL", &script_GetWBindDataL),
// 			luabind::def("SetBindDataD", &script_SetBindDataD),
// 			luabind::def("SetWBindDataD", &script_SetWBindDataD),
// 			luabind::def("GetBindDataD", &script_GetBindDataD),
// 			luabind::def("GetWBindDataD", &script_GetWBindDataD),
// 			luabind::def("GetBindDataStr", &script_GetBindDataStr),
// 			luabind::def("GetWBindDataStr", &script_GetWBindDataStr),
// 			luabind::def("SetBindDataStr", &script_SetBindDataStr),
// 			luabind::def("SetBindDatasetStr", &script_SetBindDatasetStr),
// 			luabind::def("SetBindLogicDeviceStr", &script_SetBindLogicDeviceStr),
// 			luabind::def("GetPkgMaxLen", &script_GetPkgMaxLen),
// 			luabind::def("AdBindDataList", &script_AdBindDataList),
// 			luabind::def("GetMEA", &script_GetMEA),
// 			luabind::def("CalMEA", &script_CalMEA),
// 			luabind::def("FireDataMsg", &script_FireDataChangeMessage),
// 			luabind::def("GetCP24Time2a", &script_GetCP24Time2a),
// 			luabind::def("SetCP24Time2a", &script_SetBbCurrValueCP24Time2a),
// 			luabind::def("GetCP32Time2a", &script_GetCP32Time2a),
// 			luabind::def("SetCP32Time2a", &script_SetBbCurrValueCP32Time2a),
// 			luabind::def("GetCP56Time2a", &script_GetCP56Time2a),
// 			luabind::def("SetCP56Time2a", &script_SetBbCurrValueCP56Time2a),
// 			luabind::def("SetCP56Time2aEx", &script_SetBbCurrValueCP56Time2aEx),
// 			luabind::def("BindItemIndex", &script_BindItemIndex),
// 			luabind::def("GetBitInLong16", &script_GetBitInLong16),
// 			luabind::def("SetBitInLong16", &script_SetBitInLong16),
// 			luabind::def("ClearBitInLong16", &script_ClearBitInLong16),
// 			luabind::def("GetBitInLong32", &script_GetBitInLong32),
// 			luabind::def("SetBitInLong32", &script_SetBitInLong32),
// 			luabind::def("ClearBitInLong32", &script_ClearBitInLong32),
// 			luabind::def("GetBitInLong8", &script_GetBitInLong8),
// 			luabind::def("SetBitInLong8", &script_SetBitInLong8),
// 			luabind::def("ClearBitInLong8", &script_ClearBitInLong8),
// 			luabind::def("GetBitRangeInLong8", &script_GetBitRangeInLong8),
// 
// 			luabind::def("LogPrint", &script_LogPrint),
// 			luabind::def("ShowMsg", &script_ShowMsg),
// 			luabind::def("SfCalFloat", &script_SF_ToThreeFloat),
// 			luabind::def("SfGetAna24Float", &script_SF_GetANA24Float),
// 			luabind::def("SfGetBcd24Float", &script_SF_GetBcd24Float),
// 			luabind::def("SfSetBcd24Float", &script_SF_SetBcd24Float),
// 			luabind::def("SfSetBcd24FloatEx", &script_SF_SetBcd24FloatEx),
// 			luabind::def("GetGlobal", &script_GetGlobal),
// 			luabind::def("SetGlobal", &script_SetGlobal),
// 			luabind::def("AddGlobal", &script_AddGlobal),
// 			luabind::def("SubGlobal", &script_SubGlobal),
// 
// 			luabind::def("GetDeviceAddr", &script_GetDeviceAddr),
// 			luabind::def("GetDeviceAttrL", &script_GetDeviceAttrL),
// 			luabind::def("SetDeviceAttrL", &script_SetDeviceAttrL),
// 			luabind::def("GetDeviceAttrStr", &script_GetDeviceAttrStr),
// 			luabind::def("SetDeviceAttrStr", &script_SetDeviceAttrStr),
// 			luabind::def("GetCmmMode", &script_GetCmmMode),
// 			luabind::def("GetPort", &script_GetPort),
// 			luabind::def("GetSystemPara", &script_GetSystemPara),
// 			luabind::def("GetIP", &script_GetIP),
// 
// 			luabind::def("Run", &script_Run),
// 			luabind::def("Connect", &script_Connect),
// 			luabind::def("DisConnect", &script_DisConnect),
// 			luabind::def("GetRemoteIP", &script_GetRemoteIP),
// 			luabind::def("SetPpRunState", &script_SetPpRunState),
// 			luabind::def("SetPpValid", &script_SetPpValid),
// 
// 			luabind::def("GetIEEE754", &script_GetIEEE754),
// 			luabind::def("SetIEEE754", &script_SetIEEE754),
// 			luabind::def("GetASCII", &script_GetASCII),
// 			luabind::def("CrcClear",&script_CrcClear),
// 			luabind::def("CrcPush",&script_CrcPushback),
// 			luabind::def("CrcPushBb",&script_CrcPushbackBb),
// 			luabind::def("CrcCDT",&script_CrcCDT),
// 			luabind::def("CrcSf2000",&script_CrcSfWord),
// 			luabind::def("CrcModbus16",&script_CrcModbus16),
// 
// 
// 			luabind::def("CombineDsPathStr", &script_CombineDsPathStr),
// 			luabind::def("CombineDsPathL", &script_CombineDsPathL),
// 			luabind::def("ClearDsPath", &script_ClearDsPath),
// 			luabind::def("GetDsPath",&script_GetDsPath),
// 			luabind::def("InsertDsData",&script_InsertDsData),
// 			luabind::def("InsertDataset", &script_InsertDataset),
// 			luabind::def("InsertLogicDevice", &script_InsertLogicDevice),
// 			luabind::def("InsertDevice", &script_InsertDevice),
// 			luabind::def("SetDsDataL",&script_SetDsDataL),
// 			luabind::def("SetDsDataD",&script_SetDsDataD),
// 			luabind::def("SetDsDataStr", &script_SetDsDataStr),
// 			luabind::def("SetDatasetStr", &script_SetDatasetStr),
// 			luabind::def("SetLogicDeviceStr", &script_SetLogicDeviceStr),
// 			luabind::def("GetDsDataL", &script_GetDsDataL),
// 			luabind::def("CountDsData", &script_CountDsData),
// 			luabind::def("GetSequenceDsDatas", &script_GetSequenceDsDatas),
// 			luabind::def("GetDsDataD", &script_GetDsDataD),
// 			luabind::def("GetDsDataStr",&script_GetDsDataStr),
// 			luabind::def("AdDsDataList",&script_AdDsDataList),
// 			luabind::def("AdDsPkgDetail",&script_AdDsPkgDetail),
// 			luabind::def("AdValPkgDetail",&script_AdValPkgDetail),
// 			luabind::def("GetRcvIdle",&script_GetRcvIdle),
// 			luabind::def("GetSendIdle",&script_GetSendIdle),
// 			luabind::def("AddSectionData",&script_AddSectionData),
// 			luabind::def("Fis103SaveRCDFile", &script_Fis103SaveRCDFile),
// 			luabind::def("Fis103SaveCommonFile", &script_Fis103SaveCommonFile)
// 		];
// }
// 
// #endif
// 

void PPS_LogScriptPath(CPpScript *pScript)
{
	CExBaseObject *pParent = (CExBaseObject*)pScript->GetParent();
	CString strLogPath;

	while (pParent != NULL)
	{
		if (pParent->GetClassID() == PPCLASSID_PPTEMPLATE)
		{
			break;
		}

		strLogPath = pParent->m_strName + _T(" - ") +strLogPath;
		pParent = (CExBaseObject*)pParent->GetParent();
	}

    CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("\r\n%s Script Error"), strLogPath.GetString());
}
