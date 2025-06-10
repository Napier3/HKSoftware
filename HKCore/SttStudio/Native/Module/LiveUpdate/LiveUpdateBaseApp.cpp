//LiveUpdateBaseApp.cpp

#include "stdafx.h"
#include "LiveUpdateBaseApp.h"
#include "../../../Module/System/StringTokenizer.h"
#include "../SttFileToolMngr.h"
#include "../SttSocket/TestTerminal/VC/SttClientSocket.h"
#include "../SttGlobalDef.h"
#include "../../../Module/System/StringTokenizer.h"
#ifndef NOT_USE_XLANGUAGE
#include "../../../AutoTest/Module/XLanguageResourceAts.h"
#endif
#ifndef _PSX_IDE_QT_
CSttTestAppCfg  g_SttTestAppCfg;
#endif

#ifdef _PSX_IDE_QT_
#include <QCoreApplication>
#include <QTextCodec>
#endif

#define UPINFO_SEND_TIME 10000

// CLiveUpdateBaseAp

CLiveUpdateBaseApp* g_theLiveUpdateBaseApp = NULL; 

CLiveUpdateBaseApp::CLiveUpdateBaseApp()
{
	g_theLiveUpdateBaseApp = this;
#ifdef _PSX_IDE_QT_
    m_pServerSocket = NULL;
#endif
    m_nLogUpdateString = 0;

	m_bInConnect = FALSE;

	m_pAts_MainSystem = NULL;
	m_pAts_System = NULL;
	m_pAts_Version = NULL;
	m_pNativeSys = NULL;
	m_bSttServerLink = FALSE;

	m_strServerIP = CLOUDSERVER_IP;					//云平台IP
	m_nServerPort = CLOUDSERVER_PORT_CMD;
	m_nServerFtpPort = CLOUDSERVER_PORT_FILE;

	m_nStartMode = MODE_DIRECT;
	m_strSysID = _T("");
	m_strShellFullPath = _T("");
	m_strVerID = _T("");
	m_nVerIdx = 0;

	m_strTestAppSysID = _T("");
	m_nTestAppSysIdx = 0;
	m_strTestAppLocalVer = _T("");
	m_nTestAppLocalVer = 0;
	m_strTestAppLocalVerPrev = _T("");
	m_nTestAppLocalVerPrev = 0;
	
	m_strTestAppSN = _T("");				
	m_strTestAppModel = _T("");

	m_strVertempPath = _T("");
	m_strUnzipPath = _T("");
	m_bLocalTestApp = TRUE;
	m_nTestAppPort = STTTESTSERVER_PORT;
	m_bEnableLiveUpdate = FALSE;
	m_bEnableSendParas = FALSE;
	m_bEnableSendFile = FALSE;
	m_bRecvUpdateInfo = false;
	m_bEndUpdate = false;
	m_pVerUpdateHisVer = new CVerUpdateHisVer;
	
	SetLoginUserID(ID_VERUPDATE_DEFAULT_USER);

#ifndef _PSX_IDE_QT_
	m_pMsgWnd = NULL;
	m_pMsgView = NULL;
	m_pProgress = NULL;
	m_pSttMulticastClientSocket = NULL;
#endif

#ifdef _PSX_IDE_QT_
	m_nUpdateState = STATE_NONE;
	m_nIdxSys = 0;
	m_nIdxVer = 0;
	m_strIDSys = _T("");					
	m_strIDVer = _T("");					
	m_bParasRecvSuc = false;
	m_bFileRecvOver = false;
	m_bInitDriver = false;
	m_bStopUpdate = false;
#endif

	m_bInTestappUpdate = FALSE;
}

CLiveUpdateBaseApp::~CLiveUpdateBaseApp()
{
	m_oAts_MainSystems.RemoveAll();
	m_oAts_SubSystems.RemoveAll();

	delete m_pVerUpdateHisVer;
}

// CLiveUpdateBaseApp 成员函数
BOOL CLiveUpdateBaseApp::InitLiveUpdateBaseApp()
{
	_P_InitSystemPath();

	CMacroXmlKeys::Create();
	CSttFileToolMngr::Create();
	CSttCmdOverTimeTool::Create();
	CDataMngrXmlRWKeys::Create();
	CPowerSky_OAXmlRWKeys::Create();
	CCfgDataMngrXmlRWKeys::Create();
	CVerUpdateCfgXmlRWKeys::Create();
	CSttCmdDefineXmlRWKeys::Create();
	CVerUpdateHisXmlRWKeys::Create();

#ifndef _PSX_IDE_QT_
	g_SttTestAppCfg.SttOpen(g_SttTestAppCfg.GetOldCfgFile());
	m_strTestAppIP = g_SttTestAppCfg.GetTestAppIP();
	m_nTestAppPort = g_SttTestAppCfg.GetTestServerPort();
	m_bLocalTestApp = g_SttTestAppCfg.IsLocal();
#endif

	if(m_oVerUpdateCfgMngr.Open())
	{
		m_strServerIP = m_oVerUpdateCfgMngr.GetCfgYun()->GetIP();
		m_nServerPort = m_oVerUpdateCfgMngr.GetCfgYun()->GetPort();
		m_nServerFtpPort = m_oVerUpdateCfgMngr.GetCfgYun()->GetFtpPort();
	}
	else
	{
#ifndef _PSX_IDE_QT_
		CString strInfo;
		strInfo.Format(_T("版本更新配置文件 %s 内容非法，程序退出!"),m_oVerUpdateCfgMngr.GetCfgFile());

		MessageBox(NULL,strInfo,_T("警告"),MB_OK);
#endif
		return FALSE;
	}
	
	if(!m_oVerUpdateHisSysMngr.Open())
	{
#ifndef _PSX_IDE_QT_
		CString strInfo;
		strInfo.Format(_T("版本更新记录文件 %s 内容非法，程序退出!"),m_oVerUpdateHisSysMngr.GetHistoryFile());
		MessageBox(NULL,strInfo,_T("警告"),MB_OK);
#endif
		return FALSE;
	}

#ifndef _PSX_IDE_QT_
	if(m_nStartMode == MODE_DIRECT)
	{
		CSafenet_Login::Create(FETUREID_AUTOTEST);
		m_strSN_Client = _T("POWER-SKY")/*CSafenet_Login::hasp_get_user_cop_sn()*/;

		if (!IsValidSoftDog())
		{
			//输出错误信息
			CString strInfo;
			strInfo = _T("此软件狗客户编码为空，未经授权不能进行版本更新，请插入经过授权的客户软件狗再重启进行操作!");
			MessageBox(NULL,strInfo,_T("警告"),MB_OK);

			return FALSE;
		}
	}
#endif
	CDBOptrClientBaseApp::InitRpcClient(m_strServerIP,m_nServerPort);

#ifndef _PSX_IDE_QT_
	if(!m_oSttClientEngine.ConnectServer(m_strServerIP, m_nServerFtpPort))
	{
		CString strInfo;
		strInfo.Format(_T("云平台服务器【%s,%d】连接失败，请选择云平台配置重新连接"), m_strServerIP, m_nServerFtpPort);
		MessageBox(NULL,strInfo,_T("提示"),MB_OK);

		return TRUE;
	}
#endif

	if (m_nStartMode <= MODE_SHELL_LOCAL)
	{
		InitLiveUpdateSys();
	}
	
	m_bInUpdate = FALSE;

	if (m_nStartMode == MODE_SHELL_LOCAL)
	{
		return InitShellSystem();
	}
	
#ifndef _PSX_IDE_QT_
	COaMngrInterface::Create();
#endif

	g_nSttCmdOverTimeEnable = 0;//调试不用超时

	return TRUE;
}

void CLiveUpdateBaseApp::ExitLiveUpdateBaseApp()
{
	m_oVerUpdateCfgMngr.Save();
	ExitRpcClient();

#ifndef _PSX_IDE_QT_
	CSafenet_Login::Release();
//	CSttTestAppCfg::Release();

	m_oVerUpdateHisSysMngr.Save();
	CVerUpdateHisXmlRWKeys::Release();
	
	COaMngrInterface::Release();

	if (m_oSttClientEngine.m_pSttClientSocket != NULL)
	{
		m_oSttClientEngine.SetTestEventInterface(NULL);
		m_oSttClientEngine.PrepareFreeClientEngine();
	}
	
	UpdateTestApp_Disconnect();
	UpdateTestApp_DisconnectLiveUpdate();

	if(m_pSttMulticastClientSocket != NULL)
	{ 
		delete m_pSttMulticastClientSocket;
		m_pSttMulticastClientSocket = NULL;
	}

#endif

	CMacroXmlKeys::Release();
	CSttFileToolMngr::Release();
	CDataMngrXmlRWKeys::Release();
	CPowerSky_OAXmlRWKeys::Release();
	CCfgDataMngrXmlRWKeys::Release();
	CVerUpdateCfgXmlRWKeys::Release();
	CSttCmdDefineXmlRWKeys::Release();
	CSttCmdOverTimeTool::Release();
}

#ifndef _PSX_IDE_QT_

BOOL CLiveUpdateBaseApp::IsTestAppExist()
{
	char* pszIP = NULL;
	CString strTestAppIP = g_SttTestAppCfg.GetTestAppIP();
	CString_to_char(strTestAppIP,&pszIP);

	BOOL bConnect = xping(pszIP);
	delete pszIP;

	if (!bConnect)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("测试仪：%s 网络连接不通！"),strTestAppIP);
	}

	return bConnect;
}

void CLiveUpdateBaseApp::ReConnectServer()
{
	m_strServerIP = m_oVerUpdateCfgMngr.GetCfgYun()->GetIP();
	m_nServerPort = m_oVerUpdateCfgMngr.GetCfgYun()->GetPort();
	m_nServerFtpPort = m_oVerUpdateCfgMngr.GetCfgYun()->GetFtpPort();

	if (m_oSttClientEngine.m_pSttClientSocket)
	{
		m_oSttClientEngine.PrepareFreeClientEngine();
	}	
	
	if(!m_oSttClientEngine.ConnectServer(m_strServerIP, m_nServerFtpPort))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("云平台【%s,%d】文件传输服务连接失败!"), m_strServerIP, m_nServerFtpPort);
	}
}
#endif

BOOL CLiveUpdateBaseApp::InitCommandLine(const CString& strCommandLine)
{
	CString strCmdLine = strCommandLine;
	strCmdLine.Trim();
	strCmdLine.Replace(_T("\""),_T(""));

	if (strCmdLine.GetLength()==0 || strCmdLine==_T("$"))
	{
		m_nStartMode = MODE_DIRECT;
		return TRUE;
	}

	if(strCmdLine.Right(1)==_T("$"))
	{
		strCmdLine = strCmdLine.Left(strCmdLine.GetLength()-1);
		strCmdLine.Trim();
	}

	CStringTokenizer token;
	token.Init(strCmdLine,_T('$'));

	if (token.GetStringsCount()==1)
	{
		m_strSysID = token.GetToken(0);
		
		m_nStartMode = MODE_SHELL_TESTAPP;
		return TRUE;
	}
	else if(token.GetStringsCount()==4)
	{
		m_strSysID = token.GetToken(0);
		m_strVerID = token.GetToken(1);
		m_nVerIdx = CString_To_long(token.GetToken(2));
		m_strShellFullPath = token.GetToken(3);

		m_nStartMode = MODE_SHELL_LOCAL;
		return TRUE;
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("启动参数【%s】非法"),strCommandLine.GetString());
		return FALSE;
	}
}

void CLiveUpdateBaseApp::InitLiveUpdateSys()
{
	if (!IsServerExist())
	{
		m_bInConnect = FALSE;
		return;
	}

	CString strTableName = (CString)CPowerSky_OAXmlRWKeys::CAts_SystemKey();

	//根据客户SN过滤
	CString strFilter;

	if (m_nStartMode == MODE_DIRECT)
	{
		if (!IsPowerSky())
		{
			CString strSN_ClientKey = (CString)CPowerSky_OAXmlRWKeys::SN_ClientKey();

			//筛选出指定客户SN、客户为POWER-SKY及客户为空（默认为能云）的所有系统（包括父系统和子系统）
			strFilter.Format(_T("%s='%s' or %s='%s'"),strSN_ClientKey.GetString(),m_strSN_Client.GetString(),strSN_ClientKey.GetString(),_T("POWER-SKY"));
		}
	}
	
	m_oAts_Systems.DeleteAll();
	
	BOOL bRet = DBOptrClient_QueryOptr(m_oAts_Systems,CPowerSky_OAXmlRWKeys::g_pXmlKeys,strTableName,strFilter,0,0,1);

	if (bRet)
	{
		m_bInConnect = TRUE;
		SaveLocalSysCfg();

		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("查询系统表信息成功!"));
	}
	else
	{
		m_bInConnect = FALSE;
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("查询系统表信息失败，请检查云平台的IP和端口及配置的FTP参数是否正确!"));

		return;
	}

	//遍历初始化主系统
	GetTopSystems(m_oAts_MainSystems);
}

void CLiveUpdateBaseApp::InitLiveUpdateTestAppSys()
{
	if(m_oAts_TestAppSys.GetCount()>0)
	{
		return;
	}

	if (!IsServerExist())
	{
		m_bInConnect = FALSE;
		return;
	}

	CString strTableName = (CString)CPowerSky_OAXmlRWKeys::CAts_SystemKey();
	CString strType_SystemKey = (CString)CPowerSky_OAXmlRWKeys::Type_SystemKey();

	CString strFilter;
    strFilter.Format(_T("%s='%s'"),strType_SystemKey.GetString(),SYSTYPE_EMBED);

	m_oAts_TestAppSys.DeleteAll();

	BOOL bRet = DBOptrClient_QueryOptr(m_oAts_TestAppSys,CPowerSky_OAXmlRWKeys::g_pXmlKeys,strTableName,strFilter,0,0,1);

	if (bRet)
	{
		m_bInConnect = TRUE;
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("查询系统表信息成功!"));
	}
	else
	{
		m_bInConnect = FALSE;
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("查询系统表信息失败，请检查云平台的IP和端口及配置的FTP参数是否正确!"));
		return;
	}
}

void CLiveUpdateBaseApp::UpdateMainSysNewestVer()
{
	if (m_pAts_MainSystem ==NULL)
	{
		return;
	}

	m_oAts_SubSystems.RemoveAll();

	GetSubSystems(m_pAts_MainSystem,m_oAts_SubSystems);
	m_oAts_SubSystems.AddHead(m_pAts_MainSystem);

	GetNewestUpdateVer(m_oAts_SubSystems);
}

void CLiveUpdateBaseApp::GetTopSystems(CAts_Systems& listSys)
{
	listSys.RemoveAll();

	CAts_System* pSystem = NULL;

	POS pos = m_oAts_Systems.GetHeadPosition();
	while(pos)
	{
		pSystem = (CAts_System*)m_oAts_Systems.GetNext(pos);
		if (pSystem->m_nIndex_ParentSys == 0 && pSystem->m_strType_System == SYSTYPE_DESKTOP)
		{
			listSys.AddTail(pSystem);
		}
	}
}

void CLiveUpdateBaseApp::GetSubSystems(CAts_System* pAts_MainSystem,CAts_Systems& listSys)
{
	ASSERT(pAts_MainSystem != NULL);

	listSys.RemoveAll();

	CAts_System* pAts_System = NULL;

	POS pos = m_oAts_Systems.GetHeadPosition();
	while(pos)
	{
		pAts_System = (CAts_System*)m_oAts_Systems.GetNext(pos);
		if (pAts_System->m_nIndex_ParentSys == pAts_MainSystem->m_nIndex_System && IsIncludeSys(pAts_System))
		{
			listSys.AddTail(pAts_System);
		}
	}
}

BOOL CLiveUpdateBaseApp::InitShellSystem()
{
	ASSERT (m_nStartMode == MODE_SHELL_LOCAL);

	m_oAts_SubSystems.RemoveAll();
	CString strInfo;

	CAts_System* pAts_System = (CAts_System*)m_oAts_Systems.FindByID(m_strSysID);
	if (pAts_System == NULL)
	{
		strInfo = _T("没有找到对应的软件系统，请联系软件发布/更新管理员！");
		CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo.GetString());
#ifndef _PSX_IDE_QT_
		MessageBox(NULL,strInfo,_T("提示"),MB_OK);
#endif
		return FALSE;
	}

	if (pAts_System->m_nIndex_ParentSys > 0)
	{
		CAts_System* pAts_MainSystem = (CAts_System*)m_oAts_Systems.FindByPkValue(pAts_System->m_nIndex_ParentSys);

		if (pAts_MainSystem == NULL)
		{
			strInfo.Format(_T("没有找到索引为%d的主系统，请联系软件发布/更新管理员！"),pAts_System->m_nIndex_ParentSys);
			CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo.GetString());
#ifndef _PSX_IDE_QT_
			MessageBox(NULL,strInfo,_T("提示"),MB_OK);
#endif
			return FALSE;
		}

		m_pAts_MainSystem = pAts_MainSystem;
		
		m_oAts_SubSystems.AddTail(m_pAts_MainSystem);
		GetNewestUpdateVer(m_pAts_MainSystem);

		m_oAts_SubSystems.AddTail(pAts_System);
		GetNewestUpdateVer(pAts_System);
	}
	else
	{
		m_pAts_MainSystem = pAts_System;

		m_oAts_SubSystems.AddTail(m_pAts_MainSystem);
		GetNewestUpdateVer(m_pAts_MainSystem);
	}

	return TRUE;
}

void CLiveUpdateBaseApp::SaveLocalSysCfg()
{
	CAts_System* pSystem = NULL;
	CVerUpdateCfgSys* pCfgSys = NULL;
	CVerUpdateCfgSyses* pCfgSyses = m_oVerUpdateCfgMngr.GetCfgSyses();

	pCfgSyses->DeleteAll();

	POS pos = m_oAts_Systems.GetHeadPosition();
	while (pos)
	{
		pSystem = (CAts_System*)m_oAts_Systems.GetNext(pos);

		pCfgSys = (CVerUpdateCfgSys*)pCfgSyses->AddNewChild(new CVerUpdateCfgSys);

		pCfgSys->m_strName = pSystem->m_strName;
		pCfgSys->m_strID = pSystem->m_strID;
		pCfgSys->SetIdxSys(pSystem->m_nIndex_System);
		pCfgSys->SetType(pSystem->m_strType_System);
		pCfgSys->SetRunPath(pSystem->m_strRunPath);
		pCfgSys->SetVerPath(pSystem->m_strVerPath);
		pCfgSys->SetBackupPath(pSystem->m_strBackupPath);
	}

	m_oVerUpdateCfgMngr.Save();
}

void CLiveUpdateBaseApp::InitCurrDataObj()
{
	m_pAts_System = NULL;
	m_pAts_Version = NULL;
}

int CLiveUpdateBaseApp::GetSystemLocalVer(CAts_System* pAts_System)
{
	if(pAts_System == NULL)
	{
		return 0;
	}

	CVerUpdateHisSysVers* pSysVers = (CVerUpdateHisSysVers*)m_oVerUpdateHisSysMngr.FindByName(pAts_System->m_strName);
	if (pSysVers != NULL)
	{
		return pSysVers->GetLocalCurrVerIdx();
	}

	return 0;
}

void CLiveUpdateBaseApp::ShowSystemLocalVerInfo()
{
	if (m_pAts_System)
	{
		int nIdxSystem,nLocalIdxVer;
		nIdxSystem = m_pAts_System->m_nIndex_System;
		nLocalIdxVer = m_oVerUpdateHisSysMngr.GetSysLocalVerIdx(nIdxSystem);

		CString strLocalVer;
		strLocalVer = m_oVerUpdateHisSysMngr.GetSysLocalVer(nIdxSystem);

        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前软件：【%s】，当前版本【%s】【%d】."),m_pAts_System->m_strName.GetString(),strLocalVer.GetString(),nLocalIdxVer);
	}
}

void CLiveUpdateBaseApp::GetVer(const CString& strFilter)
{
	ASSERT(m_pAts_System != NULL);

	if (!IsServerExist())
	{
		return;
	}

	CString strTableName = (CString)CPowerSky_OAXmlRWKeys::CAts_VersionKey();
	m_pAts_System->DeleteAll();

	CAts_System oList;
	BOOL bRet = DBOptrClient_QueryOptr(oList,CPowerSky_OAXmlRWKeys::g_pXmlKeys,strTableName,strFilter,0,0,1);
	if (bRet)
	{
		oList.CopyChildren(m_pAts_System);
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("查询版本表信息成功!"));
	}
	else
	{
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("查询版本表信息失败!"));
	}
}

void CLiveUpdateBaseApp::GetVerDeatil(const CString &strFilter)
{
	ASSERT(m_pAts_Version != NULL);

	if (!IsServerExist())
	{
		return;
	}

	CString strTableName = (CString)CPowerSky_OAXmlRWKeys::CAts_VerDetailKey();
	m_pAts_Version->DeleteAll();

	CAts_Version oList;
	BOOL bRet = DBOptrClient_QueryOptr(oList,CPowerSky_OAXmlRWKeys::g_pXmlKeys,strTableName,strFilter,0,0,1);
	if (bRet)
	{
		oList.CopyChildren(m_pAts_Version);
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("查询版本详情表信息成功!"));
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("查询版本详情表信息失败!"));
	}
}

void CLiveUpdateBaseApp::GetNewestUpdateVer(CAts_System* pAts_System)
{
	if(!IsServerExist())
	{
		return;
	}

	if (pAts_System == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE,_T("没有选择当前更新的系统！"));
		return;
	}

	CString strFilter,strFilter1,strVerTypePK,strNewestPK;

	strFilter = CPowerSky_OAXmlRWKeys::Index_SystemKey();
	strFilter.AppendFormat(_T("=%d"), pAts_System->m_nIndex_System);

	if (IsPowerSky() || m_nStartMode > MODE_DIRECT)
	{
		strVerTypePK = CPowerSky_OAXmlRWKeys::Type_VerKey();
        strFilter1.Format(_T("%s > %d"),strVerTypePK.GetString(),VERSIONTYPE_TEST);
	}
	else
	{
		strVerTypePK = CPowerSky_OAXmlRWKeys::Type_VerKey();
        strFilter1.Format(_T("%s = %d"),strVerTypePK.GetString(),VERSIONTYPE_PUBLIC);
	}
	strFilter += _T(" and ");
	strFilter += strFilter1;

	strFilter += _T(" and ");
	strNewestPK = CPowerSky_OAXmlRWKeys::IsNewestKey();
    strFilter.AppendFormat(_T(" %s = 1 "),strNewestPK.GetString());

	CString strTableName = (CString)CPowerSky_OAXmlRWKeys::CAts_VersionKey();

	CAts_System oList;
	BOOL bRet = DBOptrClient_QueryOptr(oList,CPowerSky_OAXmlRWKeys::g_pXmlKeys,strTableName,strFilter,0,0,1);
	if (bRet)
	{
		if (oList.GetHead())
		{
			pAts_System->DeleteAll();
			pAts_System->AddTail(oList.GetHead());
		}

		oList.RemoveAll();

		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("查询版本表信息成功!"));
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("查询版本表信息失败!"));
	}
}

void CLiveUpdateBaseApp::GetNewestUpdateVer(CAts_Systems& oAts_Systems)
{
	CAts_System* pAts_System = NULL;
	POS pos = oAts_Systems.GetHeadPosition();

	while (pos)
	{
		pAts_System = (CAts_System*)oAts_Systems.GetNext(pos);
		GetNewestUpdateVer(pAts_System);
	}
}

#ifndef _PSX_IDE_QT_
BOOL CLiveUpdateBaseApp::UpdateTestApp_Connect(const CString &strIPServer,long nPort)
{
	if (m_oSttConnectSvrEngine.m_pSttClientSocket)
	{
		m_bSttServerLink = TRUE;
	}
	else
	{
		if(!m_oSttConnectSvrEngine.ConnectServer(strIPServer, nPort))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("连接测试控制服务[%s][%d]失败"), strIPServer, nPort);
			m_bSttServerLink = FALSE;
		}
		else
		{
			m_bSttServerLink = TRUE;
		}
	}

	return m_bSttServerLink;
}


BOOL CLiveUpdateBaseApp::UpdateTestApp_ConnectOfflineUpdate(const CString &strIPServer,long nPort,long nTimeOut)
{
	if (m_oSttConnectSvrEngine.m_pSttClientSocket)
	{
		m_bSttLiveupdateLink = TRUE;
	}
	else
	{
		CTickCount32 oTickCount32;
		long nCount = 0;

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("正在连接底层LiveUpdate【%s】......"),strIPServer.GetString());

		while (nCount <= nTimeOut)
		{
			if (m_oSttConnectSvrEngine.ConnectServer(strIPServer, nPort))
			{
				m_bSttLiveupdateLink = TRUE;
				break;
			}
			else
			{
				oTickCount32.DoEvents(1000);
			}

			nCount++;
		}

		if (nCount>nTimeOut)
		{
			m_bSttLiveupdateLink = FALSE;
		}
	}

	return m_bSttLiveupdateLink;
}

BOOL CLiveUpdateBaseApp::UpdateTestApp_ConnectLiveUpdate(const CString &strIPServer,long nPort,long nTimeOut)
{
	if (m_oSttLiveUpdateEngine.m_pSttClientSocket)
	{
		m_bSttLiveupdateLink = TRUE;
	}
	else
	{
		CTickCount32 oTickCount32;
		long nCount = 0;

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("正在连接底层LiveUpdate【%s】......"),strIPServer.GetString());

		while (nCount <= nTimeOut)
		{
			if (m_oSttLiveUpdateEngine.ConnectServer(strIPServer, nPort))
			{
				m_bSttLiveupdateLink = TRUE;
				break;
			}
			else
			{
				oTickCount32.DoEvents(1000);
			}

			nCount++;
		}

		if (nCount>nTimeOut)
		{
			m_bSttLiveupdateLink = FALSE;
		}
	}
	
	return m_bSttLiveupdateLink;
}

void CLiveUpdateBaseApp::UpdateTestApp_Disconnect()
{
	if (m_oSttConnectSvrEngine.m_pSttClientSocket != NULL)
	{
		m_oSttConnectSvrEngine.PrepareFreeClientEngine();
		m_bSttServerLink = FALSE;
	}
}

void CLiveUpdateBaseApp::UpdateTestApp_DisconnectLiveUpdate()
{
	if (m_oSttLiveUpdateEngine.m_pSttClientSocket != NULL)
	{
		m_oSttLiveUpdateEngine.PrepareFreeClientEngine();
		m_bSttLiveupdateLink = FALSE;
	}
}

BOOL CLiveUpdateBaseApp::UpdateTestApp_SendFileOffline()
{

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("版本更新包文件[%s]正在下传到测试仪!"),m_strOffLineFilePath.GetString());

	CString strVerRemoteRelPath,strFileName;
	strFileName = GetFileNameFromFilePath(m_strOffLineFilePath.GetString());
	strVerRemoteRelPath.Format(_T("%s%s"),LIVEUPDATE_PATH_TEMP,strFileName.GetString());

	//	g_strFtpRootFile = STTNATIVE_PATH_ROOT;	//底层更新设置
	 return m_oSttConnectSvrEngine.m_pSttClientSocket->SttSendFile(m_strOffLineFilePath.GetString(),strVerRemoteRelPath.GetString(),0,m_pProgress);
}

BOOL CLiveUpdateBaseApp::UpdateTestApp_SendFile()
{
	ASSERT(m_pAts_System != NULL && m_pAts_Version != NULL);
	
	if(!IsFileExist(m_pAts_Version->m_strVer_LocalPath))
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("选择的版本文件包本地不存在，请先连接云平台下载再选择更新到测试仪!"));
		return FALSE;
	}

	if (!UpdateTestApp_ConnectLiveUpdate(m_strTestAppIP))
	{
		return FALSE;
	}
	
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("版本更新包文件[%s]正在下传到测试仪!"),m_pAts_Version->m_strVer_LocalPath);

	CString strVerRemoteRelPath,strFileName;
	strFileName = GetFileNameFromFilePath(m_pAts_Version->m_strVer_LocalPath);
	strVerRemoteRelPath.Format(_T("%s%s"),LIVEUPDATE_PATH_TEMP,strFileName);

//	g_strFtpRootFile = STTNATIVE_PATH_ROOT;	//底层更新设置
	return m_oSttLiveUpdateEngine.m_pSttClientSocket->SttSendFile(m_pAts_Version->m_strVer_LocalPath,strVerRemoteRelPath,0,m_pProgress);
}

BOOL CLiveUpdateBaseApp::UpdateTestApp_SendCmd_Request()
{
	ASSERT(m_pAts_System != NULL);

/*连接TestServer
	if(!UpdateTestApp_Connect(m_strTestAppIP,m_nTestAppPort))
	{
		return FALSE;
	}
*/
	//连接SttLiveUpdate
	if (!UpdateTestApp_ConnectLiveUpdate(m_strTestAppIP))
	{
		return FALSE;
	}
	
	CSttSystemCmd oCmd;
	oCmd.m_strID = STT_CMD_TYPE_SYSTEM_LiveUpdate;

	CSttParas oParas;
	oParas.m_strID = UPDATEPARAS_TYPE_REQUEST;

	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_SYSID,m_pAts_Version->m_strID_System);	//字符串型系统id（一般以测试仪系统的型号命名）
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_SYSINDEX,m_pAts_System->m_nIndex_System); //整型系统索引
	oCmd.AddNewChild(&oParas);

//	long nLenSend = m_oSttConnectSvrEngine.m_pSttClientSocket->SendCmd(&oCmd);
	long nLenSend = 0;
	if (m_oSttLiveUpdateEngine.m_pSttClientSocket)
	{
		nLenSend = m_oSttLiveUpdateEngine.m_pSttClientSocket->SendCmd(&oCmd);
	}

	oCmd.RemoveAll();

	if (nLenSend>0)
	{
		SetReply(FALSE);
	}

	return (nLenSend>0);
}

BOOL CLiveUpdateBaseApp::UpdateTestApp_SendFileOver()
{
	if (!UpdateTestApp_ConnectLiveUpdate(m_strTestAppIP))
	{
		return FALSE;
	}

	CSttSystemCmd oCmd;
	oCmd.m_strID = STT_CMD_TYPE_SYSTEM_LiveUpdate;

	CSttParas oParas;
	oParas.m_strID = UPDATEPARAS_TYPE_FILE;

	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_FILEOVER,_T("1"));
	oCmd.AddNewChild(&oParas);

	long nLenSend = 0;
	if (m_oSttLiveUpdateEngine.m_pSttClientSocket)
	{
		nLenSend = m_oSttLiveUpdateEngine.m_pSttClientSocket->SendCmd(&oCmd);
	}

	oCmd.RemoveAll();

	if (nLenSend>0)
	{
		SetReply(FALSE);
	}

	return (nLenSend>0);
}

BOOL CLiveUpdateBaseApp::UpdateTestApp_SendFileOverOffline()
{
	CSttSystemCmd oCmd;
	oCmd.m_strID = STT_CMD_TYPE_SYSTEM_LiveUpdate;

	CSttParas oParas;
	oParas.m_strID = UPDATEPARAS_TYPE_FILE;

	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_FILEOVER,_T("1"));
	oCmd.AddNewChild(&oParas);

	long nLenSend = 0;
	if (m_oSttConnectSvrEngine.m_pSttClientSocket)
	{
		nLenSend = m_oSttConnectSvrEngine.m_pSttClientSocket->SendCmd(&oCmd);
	}

	oCmd.RemoveAll();

	if (nLenSend>0)
	{
		SetReply(FALSE);
	}

	return (nLenSend>0);
}

BOOL CLiveUpdateBaseApp::UpdateTeatApp_SendCmd_Stop()
{
	if (!UpdateTestApp_ConnectLiveUpdate(m_strTestAppIP))
	{
		return FALSE;
	}

	CSttSystemCmd oCmd;
	oCmd.m_strID = STT_CMD_TYPE_SYSTEM_LiveUpdate;

	CSttParas oParas;
	oParas.m_strID = UPDATEPARAS_TYPE_STOP;

	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_STOP,_T("1"));
	oCmd.AddNewChild(&oParas);

	long nLenSend = 0;
	if (m_oSttLiveUpdateEngine.m_pSttClientSocket)
	{
		nLenSend = m_oSttLiveUpdateEngine.m_pSttClientSocket->SendCmd(&oCmd);
	}

	oCmd.RemoveAll();

	return (nLenSend>0);
}

BOOL CLiveUpdateBaseApp::SendCmd_Cloud()
{
	CSttSystemCmd oCmd;
	oCmd.m_strID = STT_CMD_TYPE_SYSTEM_LiveUpdate;

	CSttParas oParas;
	oParas.m_strID = UPDATEPARAS_TYPE_REMOTE;

	CVerUpdateCfgYun* pCfgYun = m_oVerUpdateCfgMngr.GetCfgYun();
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_IPCLOUD,pCfgYun->GetIP());
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_PORTCLOUD,pCfgYun->GetPort());	
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_FTPPORTCLOUD,pCfgYun->GetFtpPort());
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_SYSINDEX,m_pAts_Version->m_nIndex_System);	//系统索引
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_VERID,m_pAts_Version->m_strID);				//版本号
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_VERINDEX,m_pAts_Version->m_nIndex_Version);	//版本索引
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_UNZIPPATH,LIVEUPDATE_PATH_UNZIP);

	oCmd.AddNewChild(&oParas);

	long nLenSend = 0;
	if (m_oSttLiveUpdateEngine.m_pSttClientSocket)
	{
		nLenSend = m_oSttLiveUpdateEngine.m_pSttClientSocket->SendCmd(&oCmd);
	}
	
	oCmd.RemoveAll();

	if (nLenSend>0)
	{
		SetReply(FALSE);
	}

	return (nLenSend>0);
}

BOOL CLiveUpdateBaseApp::UpdateTestApp_SendCmd_Cloud()
{
	if(m_pAts_Version == NULL)
	{
		return FALSE;
	}

	if (!UpdateTestApp_ConnectLiveUpdate(m_strTestAppIP))
	{
		return FALSE;
	}
	else
	{
		return SendCmd_Cloud();
	}
}

BOOL CLiveUpdateBaseApp::SendCmd_Local()
{
	CSttSystemCmd oCmd;
	oCmd.m_strID = STT_CMD_TYPE_SYSTEM_LiveUpdate;

	CSttParas oParas;
	oParas.m_strID = UPDATEPARAS_TYPE_LOCAL;

	CString strVerRemoteRelPath;
	strVerRemoteRelPath.Format(_T("%s%s"),LIVEUPDATE_PATH_TEMP,GetFileNameFromFilePath(m_pAts_Version->m_strVer_LocalPath));

	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_VERFILE,strVerRemoteRelPath);
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_SYSINDEX,m_pAts_Version->m_nIndex_System); //系统索引

	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_VERID,m_pAts_Version->m_strID);			 //版本号
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_VERINDEX,m_pAts_Version->m_nIndex_Version);//版本索引

	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_UNZIPPATH,LIVEUPDATE_PATH_UNZIP);

	oCmd.AddNewChild(&oParas);

	long nLenSend = 0;
	if (m_oSttLiveUpdateEngine.m_pSttClientSocket)
	{
		nLenSend = m_oSttLiveUpdateEngine.m_pSttClientSocket->SendCmd(&oCmd);
	}

	oCmd.RemoveAll();

	if (nLenSend>0)
	{
		SetReply(FALSE);
	}

	return (nLenSend>0);
}


BOOL CLiveUpdateBaseApp::SendCmd_Local(const CString &strOffLineFilePath)
{
	CSttSystemCmd oCmd;
	oCmd.m_strID = STT_CMD_TYPE_SYSTEM_LiveUpdate;

	CSttParas oParas;
	oParas.m_strID = UPDATEPARAS_TYPE_LOCAL;

	CString strVerRemoteRelPath,strTmpText;
	strTmpText = GetFileNameFromFilePath(strOffLineFilePath);
	strVerRemoteRelPath.Format(_T("%s%s"),LIVEUPDATE_PATH_TEMP,strTmpText.GetString());

	m_strOffLineFilePath = strOffLineFilePath;

	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_VERFILE,strVerRemoteRelPath);
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_SYSINDEX,g_theLiveUpdateBaseApp->m_nTestAppSysIdx); //系统索引

	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_VERID,g_theLiveUpdateBaseApp->m_strTestAppLocalVer);			 //版本号
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_VERINDEX,g_theLiveUpdateBaseApp->m_nTestAppLocalVer);//版本索引

	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_UNZIPPATH,LIVEUPDATE_PATH_UNZIP);

	oCmd.AddNewChild(&oParas);

	long nLenSend = 0;
	if (m_oSttConnectSvrEngine.m_pSttClientSocket)
	{
		nLenSend = m_oSttConnectSvrEngine.m_pSttClientSocket->SendCmd(&oCmd);
	}

	oCmd.RemoveAll();

	if (nLenSend>0)
	{
		SetReply(FALSE);
	}

	return (nLenSend>0);
}

BOOL CLiveUpdateBaseApp::UpdateTestApp_SendCmd_Local()
{
	if(m_pAts_Version == NULL)
	{
		return FALSE;
	}

	if (!UpdateTestApp_ConnectLiveUpdate(m_strTestAppIP))
	{
		return FALSE;
	}
	else
	{
		return SendCmd_Local();
	}
}

BOOL CLiveUpdateBaseApp::SendCmd_Rollback()
{
	CSttSystemCmd oCmd;
	oCmd.m_strID = STT_CMD_TYPE_SYSTEM_LiveUpdate;

	CSttParas oParas;
	oParas.m_strID = UPDATEPARAS_TYPE_ROLLBACK;

	oCmd.AddNewChild(&oParas);

	long nLenSend = 0;
	if (m_oSttLiveUpdateEngine.m_pSttClientSocket)
	{
		nLenSend = m_oSttLiveUpdateEngine.m_pSttClientSocket->SendCmd(&oCmd);
	}

	oCmd.RemoveAll();

	if (nLenSend>0)
	{
		SetReply(FALSE);
	}

	return (nLenSend>0);
}

BOOL CLiveUpdateBaseApp::UpdateTestApp_SendCmd_Rollback()
{
	if(m_pAts_Version == NULL)
	{
		return FALSE;
	}

	if (!UpdateTestApp_ConnectLiveUpdate(m_strTestAppIP))
	{
		return FALSE;
	}
	else
	{
		return SendCmd_Rollback();
	}
}

void CLiveUpdateBaseApp::ExitSttLiveupdateMulticastSocket()
{
	if(m_pSttMulticastClientSocket != NULL)
	{ 
		delete m_pSttMulticastClientSocket;
		m_pSttMulticastClientSocket = NULL;
	}
}

BOOL CLiveUpdateBaseApp::MulticastStartSttLiveUpdate()
{
	ExitSttLiveupdateMulticastSocket();

	m_pSttMulticastClientSocket = new CSttMulticastClientSocket;

	if(!m_pSttMulticastClientSocket->Create(g_SttTestAppCfg.GetMulticastIP()
		,g_SttTestAppCfg.GetMulticastPort()
		,g_SttTestAppCfg.GetLocalIP()
		,g_SttTestAppCfg.GetMulticastPort()))
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("组播socket创建失败！"));
		return FALSE;
	}
/*
	map<CString,BYTE> mapProcessState;
	mapProcessState.insert(pair<CString,BYTE>(STT_PROCESS_PUDA,STT_DATAID_OFFPROCESS));
	mapProcessState.insert(pair<CString,BYTE>(STT_PROCESS_TESTSERVER,STT_DATAID_OFFPROCESS));
	mapProcessState.insert(map<CString,BYTE>::value_type(STT_PROCESS_LIVEUPDATE,STT_DATAID_STARTPROCESS));

	long nLenSend =  m_pSttMulticastClientSocket->Multicast_StartOffProcess(m_strTestAppSN,m_strTestAppModel,mapProcessState);
	mapProcessState.clear();
*/
	CStringArray astrCloseProc,astrRunProc;
	astrCloseProc.Add(STT_PROCESS_PUDA);
	astrCloseProc.Add(STT_PROCESS_TESTSERVER);
	astrCloseProc.Add(STT_PROCESS_TESTMAINCORE);
	astrRunProc.Add(STT_PROCESS_LIVEUPDATE);

	long nLenSend = m_pSttMulticastClientSocket->Multicast_Process(m_strTestAppSN,m_strTestAppModel,astrRunProc,astrCloseProc);

	if (nLenSend>0)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("启动底层更新服务组播命令发送成功！"));
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("启动底层更新服务组播命令发送失败！"));

	}

	ExitSttLiveupdateMulticastSocket();

	return (nLenSend>0);
}

void CLiveUpdateBaseApp::InitUpdateState()
{
	m_bInTestappUpdate = FALSE;

	m_nUpdateState = STATE_NONE;
	m_bEnableSendFile = FALSE;
	m_bEndUpdate = TRUE;
}

#endif

BOOL CLiveUpdateBaseApp::VerUpdateRpc_BeginUpdate(int nLocalIdxVer,int nDestIdxVer,int nIdxSystem,CString& strSvrZipFile)
{
	XmlRpc::XmlRpcValue args, res;

	args[0] = nLocalIdxVer;
	args[1] = nDestIdxVer;
	args[2] = nIdxSystem;

	try
	{
		BOOL bRet = m_pMngrRpcClient->execute(XOAMngr_Method_BeginUpdateVersion, args, res, 50);
		if (bRet)
		{
			int nRet = res[0];
			if (nRet == 0)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("从版本【%d】到版本【%d】开始更新失败!"),nLocalIdxVer,nDestIdxVer);
				return FALSE;
			}
			else
			{
#ifndef _PSX_IDE_QT_
				XmlRpcValue_To_String(res[1],strSvrZipFile);
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("从版本【%d】到版本【%d】开始更新成功!"),nLocalIdxVer,nDestIdxVer);
#else
				std::string* pstrRes = res[1].get_string();
				QTextCodec* codec = QTextCodec::codecForName("GBK");
				strSvrZipFile = codec->toUnicode(pstrRes->c_str(),pstrRes->length());
				m_nIdxVer = res[2];
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("从版本【%d】到版本【%d】开始更新成功!"),nLocalIdxVer,m_nIdxVer);
#endif
			}
		}
		else
		{
			return FALSE;
		}
	}
	catch (...)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("从版本【%d】到版本【%d】开始更新失败!"),nLocalIdxVer,nDestIdxVer);
		return FALSE;
	}

	return TRUE;
}

BOOL CLiveUpdateBaseApp::VerUpdateRpc_FinishUpdate(int nLocalIdxVer,int nDestIdxVer,int nIdxSystem)
{
	XmlRpc::XmlRpcValue args, res;

	args[0] = nLocalIdxVer;
	args[1] = nDestIdxVer;
	args[2] = nIdxSystem;

	try
	{
		BOOL bRet = m_pMngrRpcClient->execute(XOAMngr_Method_FinishUpdateVersion, args, res, 50);
		if (bRet)
		{
			int nRet = res[0];
			if (nRet == 0)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("从版本【%d】到版本【%d】更新失败!"),nLocalIdxVer,nDestIdxVer);
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}
	catch (...)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("从版本【%d】到版本【%d】更新失败!"),nLocalIdxVer,nDestIdxVer);
		return FALSE;
	}

	return TRUE;
}

BOOL CLiveUpdateBaseApp::DownloadSvrZipFile(const CString& strSvrZipFile,const CString& strLocalPath)
{
	CString strFileName = GetPathFileNameFromFilePathName(strSvrZipFile);
	CreateAllDirectories(strLocalPath);

	CString strLocalFile;

#ifndef _PSX_IDE_QT_
	strLocalFile.Format(_T("%s%s"),strLocalPath,strFileName);

	if(m_oSttClientEngine.m_pSttClientSocket == NULL)
	{
		if(!m_oSttClientEngine.ConnectServer(m_strServerIP, m_nServerFtpPort))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("与云平台服务器连接不上，下载文件【%s】失败！"),strLocalFile.GetString());
			return FALSE;
		}
	}

	if(m_oSttClientEngine.m_pSttClientSocket->SttDownloadFile(strLocalFile,strSvrZipFile,0,m_pProgress))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("下载文件【%s】成功!"), strLocalFile.GetString());
		return TRUE;
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("下载文件【%s】失败!"), strLocalFile.GetString());
		return FALSE;
	}

#else
	strLocalFile = strLocalPath;
	strLocalFile.append(strFileName);
	
	if(m_oSttLiveUpdateEngine.m_pSttClientSocket == NULL)
	{
		if(!m_oSttLiveUpdateEngine.ConnectServer(m_strServerIP, m_nServerFtpPort))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("云平台服务器连接失败，下载文件【%s】失败!"), strLocalFile.GetString());
			return FALSE;
		}
	}
	
	if(m_oSttLiveUpdateEngine.m_pSttClientSocket->SttDownloadFile(strLocalFile,strSvrZipFile,0,NULL))
	{
		m_strLocalZipFile = strLocalFile;
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("下载文件【%s】成功!"), strLocalFile.GetString());
		return TRUE;
	}
	else
	{
		m_strLocalZipFile = _T("");
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("下载文件【%s】失败!"), strLocalFile.GetString());
		return FALSE;
	}
#endif
}

#ifndef _PSX_IDE_QT_
void CLiveUpdateBaseApp::DownloadModifyDoc(const CString& strRemoteDoc,const CString& strLocalPath,BOOL bOpen)
{
	CString strFileName = GetPathFileNameFromFilePathName(strRemoteDoc);
	CreateAllDirectories(strLocalPath);

	CString strLocalFile = strLocalPath;
	strLocalFile += strFileName;

	BOOL bRet = FALSE;

	if(m_oSttClientEngine.m_pSttClientSocket == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE,_T("与云平台服务器连接中断，请点击云平台配置按钮连接云平台成功后再进行更新或下载！"));
		return;
	}

	bRet = m_oSttClientEngine.m_pSttClientSocket->SttDownloadFile(strLocalFile,strRemoteDoc,0,m_pProgress);
	if(bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("下载文件【%s】成功!"), strLocalFile.GetString());
		bRet = TRUE;
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("下载文件【%s】失败!"), strLocalFile.GetString());
	}

	if (bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("下载文件【%s】成功!"), strLocalFile.GetString());

		if (bOpen)
		{
			ShellExecute(NULL, "open", strLocalFile, 0, 0, SW_SHOW);
		}
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("服务器上不存在文件【%s】!"), strLocalFile.GetString());
	}
}
#endif

BOOL CLiveUpdateBaseApp::UnzipUpdateFiles(const CString& strLocalZipFile,const CString& strLocalVerPath,CStringArray& arrUnzipFiles)
{
    CString strTempZipFile,strInfo;
	if (strLocalZipFile.IsEmpty() || !IsFileExist(strLocalZipFile))
	{
#ifdef _PSX_IDE_QT_
        strInfo.Format(_T("strLocalZipFile文件不存在（%s）【UnzipUpdateFiles】!"),strLocalZipFile.GetString());
        SendUpdateInfo(strInfo);
#endif
		return FALSE;
	}
	else
	{
		if (FilesUnzip(strLocalZipFile,strLocalVerPath,arrUnzipFiles)!=0)
		{
#ifdef _PSX_IDE_QT_
            strInfo.Format(_T("FilesUnzip执行失败(strLocalZipFile=%s)(strLocalVerPath=%s)【UnzipUpdateFiles】!"),strLocalZipFile.GetString(),strLocalVerPath.GetString());
            SendUpdateInfo(strInfo);
#endif
			return FALSE;

		}
		else
		{
			CString strPosix;
			bool bZip = false;
			for (int i=0;i<arrUnzipFiles.GetCount();i++)
			{
				strTempZipFile = arrUnzipFiles.GetAt(i);
				strPosix = ParseFilePostfix(strTempZipFile);
				if(strPosix.CompareNoCase(_T("zip")))
				{
					continue;
				}
				
				arrUnzipFiles.RemoveAt(i);
				bZip = true;
				break;
			}

			if (bZip)
			{
				if (FilesUnzip(strTempZipFile,strLocalVerPath,arrUnzipFiles,false)!=0)	//解压后同名文件已存在则忽略
                {
#ifdef _PSX_IDE_QT_
                    strInfo.Format(_T("FilesUnzip执行失败(strTempZipFile=%s)(strLocalVerPath=%s)【UnzipUpdateFiles】!"),strTempZipFile.GetString(),strLocalVerPath.GetString());
                    SendUpdateInfo(strInfo);
#endif
					return FALSE;
				}
			}
			
			return TRUE;
		}
	}
}

BOOL CLiveUpdateBaseApp::UpdateInstall(const CString& strLocalZipFile,const CString& strLocalVerPath)
{
	CString strInfo;
	if (strLocalZipFile.IsEmpty() || !IsFileExist(strLocalZipFile))
	{
#ifndef _PSX_IDE_QT_
		strInfo.Format(_T("指定的更新包文件%s不存在，解压更新包失败!"),strLocalZipFile.GetString());
		CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);
#else 
		strInfo.Format(_T("测试仪更新：指定的更新包文件%s不存在，解压更新包失败!"),strLocalZipFile.GetString());
		SendUpdateInfo(strInfo);
#endif
		return FALSE;
	}

	CStringArray arrUnzipFiles;
	if (UnzipUpdateFiles(strLocalZipFile,strLocalVerPath,arrUnzipFiles))
	{
// #ifdef _PSX_QT_LINUX_//已判断在linux下,相对路径以"Common/"开头的,统一拷贝到/mnt/文件夹下,此处不需要再处理,防止将该文件夹重复拷贝到/Stt/文件夹(系统文件夹)下
// 		CString strCommonFolderPath,strDesFolderPath;
// 		strCommonFolderPath.Format(_T("%sCommon/"),strLocalVerPath.GetString());
// 		strDesFolderPath = _T("/mnt/Common/");
// 		CopyDirectory(strDesFolderPath,strCommonFolderPath,true);
// #endif
#ifdef NOT_USE_XLANGUAGE
#ifndef _PSX_IDE_QT_
		strInfo.Format(_T("解压本地更新包【%s】成功!"),strLocalZipFile.GetString());
		CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);
#else
		strInfo.Format(_T("测试仪更新：解压本地更新包【%s】成功!"),strLocalZipFile.GetString());
		SendUpdateInfo(strInfo);
#endif
	}
	else
	{
#ifndef _PSX_IDE_QT_
		strInfo.Format(_T("解压本地更新包【%s】失败!"),strLocalZipFile.GetString());
		CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);
		DeleteAllDirectorys(m_pAts_System->m_strVerPath,FALSE);
#else
		strInfo.Format(_T("测试仪更新：解压本地更新包【%s】失败!"),strLocalZipFile.GetString());
		SendUpdateInfo(strInfo);
		DeleteAllDirectorys(m_strVertempPath,FALSE);
#endif
		m_strLocalZipFile = _T("");

		return FALSE;
	}
#else
  #ifndef _PSX_IDE_QT_
		strInfo.Format(g_sLangTxt_UnpackSucc.GetString(),strLocalZipFile.GetString());
		CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);
#else
		strInfo.Format(g_sLangTxt_UnpackSucc.GetString(),strLocalZipFile.GetString());
		SendUpdateInfo(strInfo);
#endif
	}
	else
	{
#ifndef _PSX_IDE_QT_
		strInfo.Format(g_sLangTxt_UnpackFail.GetString(),strLocalZipFile.GetString());
		CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);
		DeleteAllDirectorys(m_pAts_System->m_strVerPath,FALSE);
#else
		strInfo.Format(g_sLangTxt_UnpackFail.GetString(),strLocalZipFile.GetString());
		SendUpdateInfo(strInfo);
		DeleteAllDirectorys(m_strVertempPath,FALSE);
#endif
		m_strLocalZipFile = _T("");

		return FALSE;
	}
 
#endif

	BOOL bSuc = TRUE;

#ifndef _PSX_IDE_QT_
	bSuc = UpdateFiles(strLocalVerPath);
	if (bSuc)
	{
		UpdateVerHistory();
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("本地更新包【%s】安装失败！"),strLocalZipFile.GetString());
	}

	DeleteAllDirectorys(m_pAts_System->m_strVerPath,FALSE);
#else
	DeleteAllDirectorys(m_strVerBkPath,FALSE);
	CopyAllFiles(arrUnzipFiles);

	DeleteAllDirectorys(m_strVertempPath,FALSE);
	DeleteAllDirectorys(m_strUnzipPath,FALSE);
#endif

	m_strLocalZipFile = _T("");

#ifdef _PSX_QT_LINUX_
	sync();
#endif

	return bSuc;
}

BOOL CLiveUpdateBaseApp::UnzipSpecPathUpdate(const CString& strLocalZipFile,const CString& strLocalVerPath)
    {
    CString strInfo;
    if (strLocalZipFile.IsEmpty() || !IsFileExist(strLocalZipFile))
    {
#ifndef _PSX_IDE_QT_
        strInfo.Format(_T("指定的更新包文件%s不存在，解压更新包失败!"),strLocalZipFile.GetString());
        CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);
#else 
        strInfo.Format(_T("测试仪更新：指定的更新包文件%s不存在，解压更新包失败!"),strLocalZipFile.GetString());
        SendUpdateInfo(strInfo);
#endif
        return FALSE;
    }

    CStringArray arrZipFiles;
#ifdef NOT_USE_XLANGUAGE
    if (UnzipSpecPathUpdateFiles(strLocalZipFile,strLocalVerPath,arrZipFiles))
    {
#ifndef _PSX_IDE_QT_
        strInfo.Format(_T("解压本地更新包【%s】成功!"),strLocalZipFile.GetString());
        CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);
#else
        strInfo.Format(_T("测试仪更新：解压本地更新包【%s】成功!"),strLocalZipFile.GetString());
        SendUpdateInfo(strInfo);
#endif
    }
    else
    {
#ifndef _PSX_IDE_QT_
        strInfo.Format(_T("解压本地更新包【%s】失败!"),strLocalZipFile.GetString());
        CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);
        DeleteAllDirectorys(m_pAts_System->m_strVerPath,FALSE);
#else
        strInfo.Format(_T("测试仪更新：解压本地更新包【%s】失败!"),strLocalZipFile.GetString());
        SendUpdateInfo(strInfo);
        DeleteAllDirectorys(m_strVertempPath,FALSE);
#endif
        m_strLocalZipFile = _T("");

        return FALSE;
    }
#else
    if (UnzipSpecPathUpdateFiles(strLocalZipFile,strLocalVerPath,arrZipFiles))
    {
        #ifndef _PSX_IDE_QT_
            strInfo.Format(g_sLangTxt_UnpackSucc.GetString(),strLocalZipFile.GetString());
            CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);
        #else
            strInfo.Format(g_sLangTxt_UnpackSucc.GetString(),strLocalZipFile.GetString());
            SendUpdateInfo(strInfo);
        #endif
    }
    else
    {
        #ifndef _PSX_IDE_QT_
            strInfo.Format(g_sLangTxt_UnpackFail.GetString(),strLocalZipFile.GetString());
            CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);
            DeleteAllDirectorys(m_pAts_System->m_strVerPath,FALSE);
        #else
            strInfo.Format(g_sLangTxt_UnpackFail.GetString(),strLocalZipFile.GetString());
            SendUpdateInfo(strInfo);
        #endif
        m_strLocalZipFile = _T("");

        return FALSE;
    }
#endif


    BOOL bSuc = TRUE;


    X_DeleteFile(strLocalZipFile); 
    X_DeleteFile(strLocalZipFile +_T("bk")); 

    m_strLocalZipFile = _T("");

#ifdef _PSX_QT_LINUX_
    sync();
#endif

    return bSuc;
}

BOOL CLiveUpdateBaseApp::UnzipSpecPathUpdateFiles(const CString& strLocalZipFile,const CString& strLocalVerPath,CStringArray& arrZipFiles)
{
    CString strTempZipFile;
    if (strLocalZipFile.IsEmpty() || !IsFileExist(strLocalZipFile))
    {
        return FALSE;
    }
    else
    {
        if (FilesUnzip(strLocalZipFile,strLocalVerPath,arrZipFiles)!=0)
        {
            return FALSE;
        }
        else
        {
            CString strPosix;
            bool bZip = false;
            for (int i=0;i<arrZipFiles.GetCount();i++)
            {
                strTempZipFile = arrZipFiles.GetAt(i);
                strPosix = ParseFilePostfix(strTempZipFile);
                if(strPosix.CompareNoCase(_T("zip")))
                {
                    continue;
                }

                arrZipFiles.RemoveAt(i);
                bZip = true;
                break;
            }

            if (bZip)
            {
                if (FilesUnzip(strTempZipFile,strLocalVerPath,arrZipFiles,false)!=0)	//解压后同名文件已存在则忽略
                {					
                    return FALSE;
                }

                X_DeleteFile(strTempZipFile); 
            }

        return TRUE;
        }
    }
}

#ifndef _PSX_IDE_QT_
BOOL CLiveUpdateBaseApp::UpdateFiles(const CString& strLocalVerPath)
{
	CXFileMngr m_oWordXFileMngr;

	CXFileType *pFileType = m_oWordXFileMngr.AddFileType(_T("Executable program"), _T("Executable program"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("Executable program"), _T("exe"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("DLL program"), _T("DLL program"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("DLL program"), _T("dll"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("XML File"), _T("XML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("XML File"), _T("xml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("INI File"), _T("INI File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("INI File"), _T("ini"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("GBXML File"), _T("GBXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("GBXML File"), _T("gbxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("IXML File"), _T("IXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("IXML File"), _T("ixml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("IECFG File"), _T("IECFG File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("IECFG File"), _T("iecfg"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("PNG File"), _T("PNG File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("PNG File"), _T("png"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("ICON File"), _T("ICON File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("ICON File"), _T("ico"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("ATSXML File"), _T("ATSXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("ATSXML File"), _T("atsxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("ATTXML File"), _T("ATTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("ATTXML File"), _T("attxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("CITXML File"), _T("CITXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("CITXML File"), _T("citxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("CBTXML File"), _T("CBTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("CBTXML File"), _T("cbtxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("DFTXML File"), _T("DFTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("DFTXML File"), _T("dftxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("DSTXML File"), _T("DSTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("DSTXML File"), _T("dstxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("DTTXML File"), _T("DTTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("DTTXML File"), _T("dttxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("EDFTXML File"), _T("EDFTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("EDFTXML File"), _T("edftxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("GDFTXML File"), _T("GDFTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("GDFTXML File"), _T("gdftxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("GRTXML File"), _T("GRTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("GRTXML File"), _T("grtxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("HRMXML File"), _T("HRMXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("HRMXML File"), _T("hrmxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("LFTXML File"), _T("LFTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("LFTXML File"), _T("lftxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("LUTXML File"), _T("LUTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("LUTXML File"), _T("lutxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("MNTXML File"), _T("MNTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("MNTXML File"), _T("mntxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("OATXML File"), _T("OATXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("OATXML File"), _T("oatxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("OCTXML File"), _T("OCTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("OCTXML File"), _T("octxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("OVTXML File"), _T("OVTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("OVTXML File"), _T("ovtxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("PDTXML File"), _T("PDTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("PDTXML File"), _T("pdtxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("PFTXML File"), _T("PFTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("PFTXML File"), _T("pftxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("RLTXML File"), _T("RLTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("RLTXML File"), _T("rltxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("SOEXML File"), _T("SOEXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("SOEXML File"), _T("soexml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("STTXML File"), _T("STTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("STTXML File"), _T("sttxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("SYSXML File"), _T("SYSXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("SYSXML File"), _T("sysxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("UCLXML File"), _T("UCLXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("UCLXML File"), _T("uclxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("ZSTXML File"), _T("ZSTXML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("ZSTXML File"), _T("zstxml"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("HTML File"), _T("HTML File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("HTML File"), _T("html"));

	pFileType = m_oWordXFileMngr.AddFileType(_T("JavaScript File"), _T("JavaScript File"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("JavaScript File"), _T("js"));

    pFileType = m_oWordXFileMngr.AddFileType(_T("TXT File"), _T("TXT File"), _T(""), _T(""));
    pFileType->AddNewPostfix(_T("TXT File"), _T("txt"));

    pFileType = m_oWordXFileMngr.AddFileType(_T("XSD File"), _T("XSD File"), _T(""), _T(""));
    pFileType->AddNewPostfix(_T("XSD File"), _T("xsd"));

    pFileType = m_oWordXFileMngr.AddFileType(_T("6U6I File"), _T("6U6I File"), _T(""), _T(""));
    pFileType->AddNewPostfix(_T("6U6I File"), _T("6u6i"));
    pFileType = m_oWordXFileMngr.AddFileType(_T("4U3I File"), _T("4U3I File"), _T(""), _T(""));
    pFileType->AddNewPostfix(_T("4U3I File"), _T("4u3i"));
    pFileType = m_oWordXFileMngr.AddFileType(_T("SYNC File"), _T("SYNC File"), _T(""), _T(""));
    pFileType->AddNewPostfix(_T("SYNC File"), _T("sync"));
    pFileType = m_oWordXFileMngr.AddFileType(_T("DSCXML File"), _T("DSCXML File"), _T(""), _T(""));
    pFileType->AddNewPostfix(_T("DSCXML File"), _T("dscxml"));
    pFileType = m_oWordXFileMngr.AddFileType(_T("CSS File"), _T("CSS File"), _T(""), _T(""));
    pFileType->AddNewPostfix(_T("CSS File"), _T("css"));
    pFileType = m_oWordXFileMngr.AddFileType(_T("EOT File"), _T("EOT File"), _T(""), _T(""));
    pFileType->AddNewPostfix(_T("EOT File"), _T("eot"));
    pFileType = m_oWordXFileMngr.AddFileType(_T("SVG File"), _T("SVG File"), _T(""), _T(""));
    pFileType->AddNewPostfix(_T("SVG File"), _T("svg"));
    pFileType = m_oWordXFileMngr.AddFileType(_T("TTF File"), _T("TTF File"), _T(""), _T(""));
    pFileType->AddNewPostfix(_T("TTF File"), _T("ttf"));
    pFileType = m_oWordXFileMngr.AddFileType(_T("WOFF File"), _T("WOFF File"), _T(""), _T(""));
    pFileType->AddNewPostfix(_T("WOFF File"), _T("woff"));
    pFileType = m_oWordXFileMngr.AddFileType(_T("WOFF2 File"), _T("WOFF2 File"), _T(""), _T(""));
    pFileType->AddNewPostfix(_T("WOFF2 File"), _T("woff2"));

	m_oWordXFileMngr.InitByXFileTypes();
	m_oWordXFileMngr.SetLibraryPath(strLocalVerPath);

	if(m_nStartMode == MODE_DIRECT)
	{ 
		GetSelectFilePaths(m_oWordXFileMngr);	//取得文件更新选择集合
	}
	
	CStringArray strAllFilePaths,strAllProcessPaths;
	GetAllFilePaths(&m_oWordXFileMngr,strAllFilePaths,strAllProcessPaths);

	if(strAllFilePaths.GetCount()==0)
	{
		return FALSE;
	}

	BOOL bSuc = ExitExeDllProcess(strAllProcessPaths);
	if (bSuc)
	{
		CopyAllFiles(strAllFilePaths);
	}

	return bSuc;
}

void CLiveUpdateBaseApp::GetAllFilePaths(CXFolder *pXFolder,CStringArray &strFilePaths,CStringArray &strProcessPaths)
{
	CXFile *pXFile = NULL;
	CExBaseObject *pExBaseObject = NULL;
	CString strFilePath,strProcessPath,strSystemPath;

#ifndef _PSX_IDE_QT_ 
	strSystemPath = m_pAts_System->m_strRunPath;
#else
	strSystemPath = _P_GetInstallPath();
#endif

	POS pos = pXFolder->GetHeadPosition();

	while(pos != NULL)
	{
		pExBaseObject = pXFolder->GetNext(pos);

		if (pExBaseObject->GetClassID() == CLASSID_XFOLDER)
		{
			GetAllFilePaths((CXFolder*)pExBaseObject,strFilePaths,strProcessPaths);
		}
		else if (pExBaseObject->GetClassID() == CLASSID_XFILE)
		{
			pXFile = (CXFile *)pExBaseObject;
			strFilePath = pXFile->GetRelativePath(TRUE);
			strFilePaths.Add(strFilePath);

			strProcessPath = GetModuleProcessPath(strSystemPath,pXFile->GetRelativePath(FALSE));
			strProcessPaths.Add(strProcessPath);
		}
	}
}

void CLiveUpdateBaseApp::GetSelectFilePaths(CXFileMngr& oXFileMngr)
{
	if(m_pMsgWnd != NULL)
	{
		m_pMsgWnd->SendMessage(WM_USER + 2021,(WPARAM)&oXFileMngr,0);
	}
}

BOOL CLiveUpdateBaseApp::ExitExeDllProcess(CStringArray& strAllProcessPaths)
{
	CLocalProgresses* pLocalProgresses = new CLocalProgresses;
	BOOL bSuc = FindExeDllProcess(strAllProcessPaths,pLocalProgresses);
	if (bSuc)
	{
		if (pLocalProgresses->GetCount()>0)
		{
			if(m_nStartMode ==	MODE_DIRECT)
			{
				if(m_pMsgWnd != NULL)
				{
					m_pMsgWnd->SendMessage(WM_USER + 2020,(WPARAM)pLocalProgresses,0);
				}
			}
			else
			{
				TerminateProcess(*pLocalProgresses);
			}
		}
	}

	if (pLocalProgresses != NULL)
	{
		delete pLocalProgresses;
	}

	return bSuc;
}

void CLiveUpdateBaseApp::UpdateVerHistory()
{
	CVerUpdateHisSysVers* pHisSysVers = (CVerUpdateHisSysVers*)m_oVerUpdateHisSysMngr.FindByName(m_pAts_System->m_strName);

	if(pHisSysVers == NULL)
	{
		pHisSysVers = (CVerUpdateHisSysVers*)m_oVerUpdateHisSysMngr.AddNewChild(new CVerUpdateHisSysVers);
		pHisSysVers->m_strName = m_pAts_System->m_strName;
		pHisSysVers->m_strID.Format(_T("%d"),m_pAts_System->m_nIndex_System);
	}

	pHisSysVers->AddHisVer(m_pVerUpdateHisVer);

	m_oVerUpdateHisSysMngr.Save();
}
#endif


void CLiveUpdateBaseApp::CopyAllFiles(const CStringArray &strFilePaths)
{
	CString strDestFilePath,strSrcFilePath,strBkFilePath,strSystemPath,strModulePath,strBkPath;
	CString strTmp1,strTmp2;
	BOOL bRet = FALSE;

#ifndef _PSX_IDE_QT_
	strSystemPath = m_pAts_System->m_strRunPath;

	TCHAR strShortPath[MAX_PATH];
	GetModuleFileName(NULL,strShortPath,MAX_PATH);

	TCHAR strFullPath[MAX_PATH] = { 0 };  
	GetLongPathName( strShortPath, strFullPath, sizeof(strFullPath)/sizeof(TCHAR) );  
	strModulePath = strFullPath;

	strTmp1 = GetFileNameFromFilePath(strModulePath);

	CTime t = CTime::GetCurrentTime();
	strBkPath.Format(_T("%s%04d%02d%02d%02d%02d\\"),m_pAts_System->m_strBackupPath,t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute());

#else
	strSystemPath = _P_GetSystemPath();

	strModulePath = QCoreApplication::applicationFilePath();
	strTmp1 = GetFileNameFromFilePath(strModulePath,_T('//'));

	strBkPath.Format(_T("%s%s"),_P_GetSystemPath(),LIVEUPDATE_PATH_BK);
#endif

	CreateAllDirectories(strBkPath);

	CTickCount32 oTickCount32;
	long nTickCountLong = 0;

    CString strInfo,strCommonDirName,strEProtocolDirName;
	strCommonDirName = _T("Common/");
    strEProtocolDirName = _T("e-Protocol/");

	for (long nCount = 0;nCount<strFilePaths.GetSize();nCount++)
	{
		strSrcFilePath = strFilePaths.GetAt(nCount);

		if (IsFileExist(strSrcFilePath))
		{
#ifndef _PSX_IDE_QT_
			CString strRelative = strSrcFilePath.Right(strSrcFilePath.GetLength() - m_pAts_System->m_strVerPath.GetLength());
#else
			CString strUnzipPath;
			strUnzipPath.Format(_T("%s%s"),_P_GetSystemPath(),LIVEUPDATE_PATH_UNZIP);
			CString strRelative = strSrcFilePath.Right(strSrcFilePath.GetLength() - strUnzipPath.GetLength());
#endif


#ifdef _PSX_QT_LINUX_//在Linux下如果当前文件相对路径是以"Common/",则将其拷贝到/mnt/文件夹下
			if (strRelative.Find(strCommonDirName) == 0)
			{
				strDestFilePath = "/mnt/" + strRelative;
			}
            else if (strRelative.Find(strEProtocolDirName) == 0)//在Linux下如果当前文件相对路径是以"e-Protocol/",则将其拷贝到/mnt/文件夹下
            {
                strDestFilePath = "/mnt/" + strRelative;
            }
			else
#endif
			{
			strDestFilePath = GetModuleProcessPath(strSystemPath,strRelative);
			}

			strBkFilePath = strBkPath;
			strBkFilePath += strRelative;

#ifndef _PSX_IDE_QT_
			CreateAllDirectories(GetPathFromFilePathName(strBkFilePath));
#else
			CreateAllDirectories(GetPathFromFilePathName(strBkFilePath,_T('//')));
#endif
			if (IsFileExist(strDestFilePath))
			{
				bRet = X_CopyFile(strDestFilePath,strBkFilePath);
				if (bRet)
				{
#ifdef NOT_USE_XLANGUAGE		
#ifndef _PSX_IDE_QT_
					strInfo.Format(_T("文件【%s】备份成功!"),strDestFilePath.GetString());
					CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);
#else
                    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("测试仪更新：文件【%s】备份成功!"),strDestFilePath.GetString());
//					strInfo.Format(_T("测试仪更新：文件【%s】备份成功!"),strDestFilePath.GetString());
//					SendUpdateInfo(strInfo); //20220630 zhouhj 发送消息耗时太长
#endif
				}
				else
				{
#ifndef _PSX_IDE_QT_
					strInfo.Format(_T("文件【%s】备份失败!"),strDestFilePath.GetString());
					CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);
#else
					strInfo.Format(_T("测试仪更新：文件【%s】备份失败!"),strDestFilePath.GetString());
					SendUpdateInfo(strInfo);
#endif
				}

#else
				#ifndef _PSX_IDE_QT_
									strInfo.Format(_T("文件【%s】备份成功!"),strDestFilePath.GetString());
									CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);
				#else
				                    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,g_sLangTxt_BackupSucc.GetString(),strDestFilePath.GetString());
				//					strInfo.Format(_T("测试仪更新：文件【%s】备份成功!"),strDestFilePath.GetString());
				//					SendUpdateInfo(strInfo); //20220630 zhouhj 发送消息耗时太长
				#endif
								}
								else
								{
				#ifndef _PSX_IDE_QT_
									strInfo.Format(_T("文件【%s】备份失败!"),strDestFilePath.GetString());
									CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);
				#else
									strInfo.Format(g_sLangTxt_BackupFail.GetString(),strDestFilePath.GetString());
									SendUpdateInfo(strInfo);
				#endif
					}
#endif
				if (m_nLogUpdateString)
				{
                    m_oLiveUpdateTickCount.DoEvents(1000);
				}
			}

#ifndef _PSX_IDE_QT_
			strTmp2 = GetFileNameFromFilePath(strSrcFilePath);
#else
			strTmp2 = GetFileNameFromFilePath(strSrcFilePath,_T('//'));
#endif
			if (strTmp1.CompareNoCase(strTmp2) == 0)		
			{
#ifndef _PSX_IDE_QT_
				strDestFilePath = GetPathFromFilePathName(strModulePath);
				strDestFilePath += LOCAL_LIVEUPDATE_NEWNAME;
				X_CopyFile(strSrcFilePath,strDestFilePath);

				CString strTip;
				strTip.Format(_T("更新包中包含LiveUpdate，已更名拷贝到路径：%s，在本工具退出后在此路径下先删除文件【%s】,后将文件【%s】改名【%s】完成手动更新!")
					,strDestFilePath.GetString(),LOCAL_LIVEUPDATE_NAME, LOCAL_LIVEUPDATE_NEWNAME, LOCAL_LIVEUPDATE_NAME);
				CLogPrint::LogString(XLOGLEVEL_INFOR,strTip.GetString());
#else
				strDestFilePath.Format(_T("%s%s"),_P_GetSystemPath(),LIVEUPDATE_PATH_SELFTEMP);
				CreateAllDirectories(strDestFilePath);

				strDestFilePath += _T('/');
				strDestFilePath += STT_LIVEUPDATE_NAME;
				X_CopyFile(strSrcFilePath,strDestFilePath);
#endif
				continue;
			}

			if(!IsFileExist(strDestFilePath))
			{
#ifndef _PSX_IDE_QT_
                CreateAllDirectories(GetPathFromFilePathName(strDestFilePath.GetString()));
#else
				CreateAllDirectories(GetPathFromFilePathName(strDestFilePath.GetString(),_T('//')));
#endif
			}

#ifndef _PSX_IDE_QT_
			if(strTmp2.CompareNoCase(LIVEUPDATE_CFG_BASE)==0)
			{
				m_oVerUpdateCfgMngr.Save();
				m_oVerUpdateCfgMngr.DeleteAll();
			}
			if(strTmp2.CompareNoCase(LIVEUPDATE_CFG_HIS)==0)
			{
				m_oVerUpdateHisSysMngr.Save();
				m_oVerUpdateHisSysMngr.DeleteAll();
			}	
#else
			CSttNativeCfgHisVer* pTempHis = NULL;
			if(strTmp2.CompareNoCase(LIVEUPDATE_CFG_NATIVE)==0)
			{
				CSttNativeCfgLiveUpdate* pLiveUpdate = m_oNativeCfgMngr.GetCfgLiveUpdate();
				CSttNativeCfgHisVer* pHis = (CSttNativeCfgHisVer*)pLiveUpdate->GetCfgHisVer();
				pTempHis = (CSttNativeCfgHisVer*)pHis->CloneEx();
				m_oNativeCfgMngr.Save();
			}
#endif

			ClearFileReadOnlyAttr(strDestFilePath);
			bRet = X_CopyFile(strSrcFilePath,strDestFilePath);

			if(bRet)
			{
#ifndef _PSX_IDE_QT_
				strInfo.Format(_T("文件【%s】更新成功!"),strDestFilePath.GetString());
				CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);

				if(strTmp2.CompareNoCase(LIVEUPDATE_CFG_BASE)==0)
				{
					m_oVerUpdateCfgMngr.Open();
					m_strServerIP = m_oVerUpdateCfgMngr.GetCfgYun()->GetIP();
					m_nServerPort = m_oVerUpdateCfgMngr.GetCfgYun()->GetPort();
					m_nServerFtpPort = m_oVerUpdateCfgMngr.GetCfgYun()->GetFtpPort();
					continue;
				}

				if(strTmp2.CompareNoCase(LIVEUPDATE_CFG_HIS)==0)
				{
					m_oVerUpdateHisSysMngr.Open();
					continue;
				}
#else
	#ifdef NOT_USE_XLANGUAGE
                CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("测试仪更新：文件【%s】拷贝成功!"),strDestFilePath.GetString());
	#else
		   CLogPrint::LogFormatString(XLOGLEVEL_INFOR,g_sLangTxt_CopySucc.GetString(),strDestFilePath.GetString());
	#endif

//				strInfo.Format(_T("测试仪更新：文件【%s】拷贝成功!"),strDestFilePath.GetString());
//				SendUpdateInfo(strInfo);//20220630 zhouhj 发送消息耗时太长

				if(strTmp2.CompareNoCase(LIVEUPDATE_CFG_NATIVE)==0)
				{
					m_oNativeCfgMngr.DeleteAll();
					m_oNativeCfgMngr.Open();

					if(pTempHis)
					{
						CSttNativeCfgLiveUpdate* pLiveUpdate = m_oNativeCfgMngr.GetCfgLiveUpdate();
						CSttNativeCfgHisVer* pHis = (CSttNativeCfgHisVer*)pLiveUpdate->GetCfgHisVer();
						pTempHis->CopyOwn(pHis);
						delete pTempHis;
						pTempHis = NULL;
					}

					continue;
				}
#endif
				if(IsFPGAFile(strDestFilePath))
				{
                    //UpdateFPGAFile(strDestFilePath);//2023.7.11 zhouhj
				}
				else if(IsMntSysFile(strDestFilePath))
				{
					UpdateMntSysFile(strDestFilePath);
				}
			}
			else
			{
#ifndef _PSX_IDE_QT_
				strInfo.Format(_T("文件【%s】更新失败!"),strDestFilePath.GetString());
				CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);
#else
	#ifdef NOT_USE_XLANGUAGE
		   CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("测试仪更新：文件【%s】更新失败!"),strDestFilePath.GetString());
	#else
		   CLogPrint::LogFormatString(XLOGLEVEL_INFOR,g_sLangTxt_CopySucc.GetString(),strDestFilePath.GetString());
			strInfo.Format(g_sLangTxt_TesterUpdataFail.GetString(),strDestFilePath.GetString());
	#endif
				SendUpdateInfo(strInfo);

				if(strTmp2.CompareNoCase(LIVEUPDATE_CFG_NATIVE)==0)
				{
					if(pTempHis)
					{
						delete pTempHis;
						pTempHis = NULL;
					}
				}
#endif
			}

			if (m_nLogUpdateString)
			{
                m_oLiveUpdateTickCount.DoEvents(1000);
			}
		}

#ifdef _PSX_IDE_QT_
        nTickCountLong = oTickCount32.GetTickCountLong(FALSE);
        if (nTickCountLong >= UPINFO_SEND_TIME)
            {
            float fPercent = 100*(nCount+1)/strFilePaths.GetSize();
    #ifdef NOT_USE_XLANGUAGE
            strInfo.Format(_T("测试仪更新：已更新%.02f"),fPercent);
	#else
           strInfo.Format(g_sLangTxt_TesterUpdate.GetString(), fPercent);
	#endif
		   strInfo += " %.";
            SendUpdateInfo(strInfo);
            oTickCount32.Enter();
            }
#endif

	}
}

#ifdef _PSX_IDE_QT_
void CLiveUpdateBaseApp::SendUpdateRet(BOOL bRet)
{
	CSttSysState oSysState;
	oSysState.m_strID = STT_CMD_TYPE_SYSTEM_LiveUpdate;
	oSysState.m_strRetType = SYS_STATE_RETTYPE_REPLY;
	oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_SYSTEM;

	CSttParas oParas;
	if (bRet)
	{
		oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_REPLY,_T("1"));
	}
	else
	{
		oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_REPLY,_T("0"));
	}

	oSysState.AddNewChild(&oParas);

	CSttServerClientSocket* pClientSocket = NULL;

    if(m_pServerSocket)
    {
        POS pos = m_pServerSocket->GetHeadPosition();
        while(pos)
        {
            pClientSocket = (CSttServerClientSocket*)m_pServerSocket->GetNext(pos);
            pClientSocket->SendSysState(&oSysState);
        }
    }

	oSysState.RemoveAll();

#ifdef _USE_NO_GUI_
    qsleep(1000);
#else
     CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("SendUpdateRet(%d)"),bRet);
    m_oLiveUpdateTickCount.DoEvents(1000);
#endif
}

void CLiveUpdateBaseApp::SendUpdateResult(BOOL bResult)
{
	CSttNativeCfgLiveUpdate* pLiveUpdate = m_oNativeCfgMngr.GetCfgLiveUpdate();
	CSttNativeCfgHisVer* pCfgHisVer = pLiveUpdate->GetCfgHisVer();

	CSttSysState oSysState;
	oSysState.m_strID = STT_CMD_TYPE_SYSTEM_LiveUpdate;
	oSysState.m_strRetType = SYS_STATE_RETTYPE_REPLY;
	oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_SYSTEM;

	CSttParas oParas;
	if (bResult)
	{
		oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_RESULT,_T("1"));
		oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_VERID,pCfgHisVer->m_strCurrVer);
		oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_VERINDEX,pCfgHisVer->m_nCurrVerIdx);
		oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_PREVERID,pCfgHisVer->m_strPrevVer);
		oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_PREVERINDEX,pCfgHisVer->m_nPrevVerIdx);
#ifndef _USE_NO_GUI_
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("SendUpdateResult(%d),CurrVer=%s,CurrVerIdx=%d,PrevVer=%s,PrevVerIdx=%d"),
                                   bResult,pCfgHisVer->m_strCurrVer.GetString(),pCfgHisVer->m_nCurrVerIdx,pCfgHisVer->m_strPrevVer.GetString(),
                                   pCfgHisVer->m_nPrevVerIdx);
#endif
	}
	else
	{
		oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_RESULT,_T("0"));
#ifndef _USE_NO_GUI_
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("SendUpdateResult(%d)"),bResult);
#endif
	}

	oSysState.AddNewChild(&oParas);

	CSttServerClientSocket* pClientSocket = NULL;

    if(m_pServerSocket)
    {
        POS pos = m_pServerSocket->GetHeadPosition();
        while(pos)
        {
            pClientSocket = (CSttServerClientSocket*)m_pServerSocket->GetNext(pos);
            pClientSocket->SendSysState(&oSysState);
        }
    }

	oSysState.RemoveAll();

//	qsleep(1000);
#ifdef _USE_NO_GUI_
    qsleep(1000);
#else
    m_oLiveUpdateTickCount.DoEvents(1000);
#endif
}

void CLiveUpdateBaseApp::SendUpdateInfo(const CString& strInfo)
{
	CSttSysState oSysState;
	oSysState.m_strID = STT_CMD_TYPE_SYSTEM_LiveUpdate;
	oSysState.m_strRetType = SYS_STATE_RETTYPE_REPLY;
	oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_SYSTEM;

	CSttParas oParas;
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_UPDATEINFO,strInfo);

	oSysState.AddNewChild(&oParas);

	CSttServerClientSocket* pClientSocket = NULL;

    if(m_pServerSocket)
    {
        POS pos = m_pServerSocket->GetHeadPosition();
        while(pos)
        {
            pClientSocket = (CSttServerClientSocket*)m_pServerSocket->GetNext(pos);
            pClientSocket->SendSysState(&oSysState);
        }
    }

	oSysState.RemoveAll();

#ifdef _USE_NO_GUI_
	qsleep(1000);
#else
    CLogPrint::LogFormatString(XLOGLEVEL_RESULT,strInfo.GetString());
    m_oLiveUpdateTickCount.DoEvents(1000);
#endif
}

void CLiveUpdateBaseApp::SendInitRet()
{
	CSttNativeCfgLiveUpdate* pLiveUpdate = m_oNativeCfgMngr.GetCfgLiveUpdate();
	CSttNativeCfgHisVer* pCfgHisVer = pLiveUpdate->GetCfgHisVer();

	CSttSysState oSysState;
	oSysState.m_strID = STT_CMD_TYPE_SYSTEM_LiveUpdate;
	oSysState.m_strRetType = SYS_STATE_RETTYPE_REPLY;
	oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_SYSTEM;

	CSttParas oParas;
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_REPLY,_T("1"));
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_SYSID,pLiveUpdate->m_strID_System);
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_SYSINDEX,pLiveUpdate->m_nIndex_System);
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_VERID,pCfgHisVer->m_strCurrVer);
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_VERINDEX,pCfgHisVer->m_nCurrVerIdx);
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_PREVERID,pCfgHisVer->m_strPrevVer);
	oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_PREVERINDEX,pCfgHisVer->m_nPrevVerIdx);

	oSysState.AddNewChild(&oParas);

	CSttServerClientSocket* pClientSocket = NULL;

    if(m_pServerSocket)
    {
        POS pos = m_pServerSocket->GetHeadPosition();
        while(pos)
        {
            pClientSocket = (CSttServerClientSocket*)m_pServerSocket->GetNext(pos);
            pClientSocket->SendSysState(&oSysState);
        }
    }

	oSysState.RemoveAll();

//	qsleep(1000);
#ifdef _USE_NO_GUI_
    qsleep(1000);
#else
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("SendInitRet,ID_System=%s,Index_System=%d,CurrVer=%s,CurrVerIdx=%d,PrevVer=%s,PrevVerIdx=%d"),
                               pLiveUpdate->m_strID_System.GetString(),pLiveUpdate->m_nIndex_System,pCfgHisVer->m_strCurrVer.GetString(),
                               pCfgHisVer->m_nCurrVerIdx,pCfgHisVer->m_strPrevVer.GetString(),
                               pCfgHisVer->m_nPrevVerIdx);
    m_oLiveUpdateTickCount.DoEvents(1000);
#endif
}

BOOL CLiveUpdateBaseApp::WaitForParas(int nTimeOut)
{
	long nCount = 1;
	CTickCount32 oTickCount32;

	while (nCount<=nTimeOut)
	{
		nCount++;
		if (m_bParasRecvSuc == TRUE)
		{	
			return TRUE;
		}
		else
		{
			oTickCount32.DoEvents(100);
		}
	}

	return FALSE;
}

BOOL CLiveUpdateBaseApp::WaitForFileRecv(int nTimeOut)
{
	long nCount = 1;
	CTickCount32 oTickCount32;

	while (nCount<=nTimeOut)
	{
		nCount++;
		if (m_bFileRecvOver == TRUE)
		{	
			return TRUE;
		}
		else
		{
			oTickCount32.DoEvents(100);
		}
	}

	return FALSE;
}

void CLiveUpdateBaseApp::InitFlags()
{
//	m_bInitDriver = false;
	m_bParasRecvSuc = false;
	m_bFileRecvOver = false;
	m_bStopUpdate = false;
	m_nUpdateStyle = UPDATESTYLE_NONE;
}

void CLiveUpdateBaseApp::qsleep(int msec)
{
	QDateTime last = QDateTime::currentDateTime();
	QDateTime now;
	while (1)
	{
		now = QDateTime::currentDateTime();
		if (last.msecsTo(now) >= msec)
		{
			break;
		}
	}
}
#endif

CString CLiveUpdateBaseApp::GetModuleProcessPath(const CString& strSystemPath,const CString& strRelativePath)
{
	CString strProcessPath,strTmp1,strTmp2;
#ifndef _PSX_IDE_QT_
	int pos = strRelativePath.Find(_T("\\"));
#else
	int pos = strRelativePath.Find(_T("/"));
#endif
	if (pos < 0)
	{
		strProcessPath = strSystemPath;
		strProcessPath += strRelativePath;
	}
	else
	{
		CString strTmp3 = strRelativePath.Left(pos);
		pos = strSystemPath.Find(strTmp3);
		if (pos < 0)
		{
			strProcessPath = strSystemPath;
			strProcessPath += strRelativePath;
		}
		else
		{
			strTmp1 = strSystemPath.Mid(pos);
			strTmp2 = strRelativePath.Left(strTmp1.GetLength());
			if (strTmp1.CompareNoCase(strTmp2) == 0)
			{
				strProcessPath = strSystemPath.Left(pos);
			}
			else
			{
				strProcessPath = strSystemPath;
			}

			strProcessPath += strRelativePath;
		}
	}

	return strProcessPath;
}

BOOL CLiveUpdateBaseApp::IsValidDateTime(SYSTEMTIME tmBegin,SYSTEMTIME tmEnd)
{
#ifndef _PSX_IDE_QT_
	CTime oT_Start(tmBegin.wYear,tmBegin.wMonth,tmBegin.wDay,0,0,0);
	CTime oT_End(tmEnd.wYear,tmEnd.wMonth,tmEnd.wDay,0,0,0);
	CTime oT_Now = CTime::GetCurrentTime();
#else
	CString str;
	str.Format(_T("%4d-%02d-%02d 00:00:00"),tmBegin.wYear,tmBegin.wMonth,tmBegin.wDay);
	QDateTime oT_Start = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");

	str.Format(_T("%4d-%02d-%02d 00:00:00"),tmEnd.wYear,tmEnd.wMonth,tmEnd.wDay);
	QDateTime oT_End = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");

	QDateTime oT_Now = QDateTime::currentDateTime();
#endif

	CString strInfo;
	if (oT_Start > oT_Now || oT_End > oT_Now)
	{
		strInfo = _T("查询时间设置错误：起始时间或结束时间超过今日截止时间!");
		CLogPrint::LogString(XLOGLEVEL_RESULT,strInfo);

		return FALSE;
	}

	if (oT_Start > oT_End)
	{
		strInfo = _T("查询时间设置错误：起始时间大于结束时间!");
		CLogPrint::LogString(XLOGLEVEL_RESULT,strInfo);

		return FALSE;
	}

	return TRUE;
}

BOOL CLiveUpdateBaseApp::IsIncludeSys(CAts_System* pAts_System)
{
	if (pAts_System == NULL)
	{
		return FALSE;
	}

	if (pAts_System->m_strID.IsEmpty())
	{
		return FALSE;
	}

	if (pAts_System->m_strSN_Client.CompareNoCase(_T("POWER-SKY"))==0 || pAts_System->m_strTestMacros.IsEmpty())
	{
		return TRUE;
	}

#ifndef _PSX_IDE_QT_
	//比较m_strAuthoritys_TestMacros与pAts_System->m_strTestMacros
	CStringTokenizer token;
	CString strTestMacro;

	token.Init(pAts_System->m_strTestMacros,_T('$'));
	int count = token.GetStringsCount()-1;

	int i;
	for(i=0;i<count;i++)
	{
		strTestMacro = token.NextToken();

		if(CSafenet_hasp::hasp_can_use_test_macro(strTestMacro))
		{
			return TRUE;
		}
	}

	return FALSE;

#else
	return TRUE;
#endif
}

BOOL CLiveUpdateBaseApp::WaitForReply(int nTimeOut)
{
	long nCount = 1;
	CTickCount32 oTickCount32;

	while (nCount<=nTimeOut)
	{
		nCount++;
		if (GetReply()==TRUE)
		{	
			return TRUE;
		}
		else
		{
			oTickCount32.DoEvents(100);
		}
	}

	return FALSE;
}

BOOL CLiveUpdateBaseApp::WaitForXftp(const CString& strFilePath,int nTimeOut)
{
	long nCount = 1;
	CTickCount32 oTickCount32;

	while (nCount<=nTimeOut)
	{
		nCount++;

		CFile file;
		if(file.Open(strFilePath, CFile::modeRead))
		{
			file.Close();
			return TRUE;
		}
		else
		{
			oTickCount32.DoEvents(100);
		}
	}

	return FALSE;
}

BOOL CLiveUpdateBaseApp::WaitForUpdateInfo(int nTimeOut)
{
	long nCount = 1;
	CTickCount32 oTickCount32;

	while (nCount<=nTimeOut)
	{
		nCount++;

		if (m_bRecvUpdateInfo)	//收到过程信息，继续等待
		{	
			nCount = 0;		
			m_bRecvUpdateInfo = false;
		}
		else if(m_bEndUpdate)
		{
			return TRUE;		//收到结束信息，退出超时判断
		}
		else
		{
			oTickCount32.DoEvents(100);
		}
	}

	return FALSE;
}

void CLiveUpdateBaseApp::WaitForExit(int nTimeOut)
{
	long nCount = 1;
	CTickCount32 oTickCount32;

	while (nCount<=nTimeOut)
	{
		nCount++;
		oTickCount32.DoEvents(100);
	}
}

void CLiveUpdateBaseApp::ResetWaitFlags()
{
	m_bReply = TRUE;
	m_bEndUpdate = TRUE;
#ifdef  _PSX_IDE_QT_
	m_bParasRecvSuc = TRUE;
	m_bFileRecvOver = TRUE;
#endif
}

#ifdef _PSX_QT_LINUX_
#include<QDir>
bool CLiveUpdateBaseApp::CopyDirectory(const CString &strDstPath,const CString &strSrcFolderPath,  bool bCoverFileExist)
{
	QDir oSrcDir(strSrcFolderPath);
	QDir oDstDir(strDstPath);

	if (!oDstDir.exists()) { //目的文件目录不存在则创建文件目录
		if (!oDstDir.mkdir(oDstDir.absolutePath()))
			return false;
	}

	QFileInfoList oFileInfoList = oSrcDir.entryInfoList();
	QFileInfo oCurrFileInfo;//文件信息变量

	for (int nIndex = 0;nIndex<oFileInfoList.length();nIndex++)
	{
		oCurrFileInfo = oFileInfoList.at(nIndex);

		if (oCurrFileInfo.fileName() == "." || oCurrFileInfo.fileName() == "..")
			continue;

		if (oCurrFileInfo.isDir()) 
		{    // 当为目录时，递归的进行copy 
            if (!CopyDirectory(oDstDir.filePath(oCurrFileInfo.fileName()),oCurrFileInfo.filePath(),bCoverFileExist))
			{
				return false;
			}
		}
		else 
		{            //当允许覆盖操作时，将旧文件进行删除操作 
			if (bCoverFileExist && oDstDir.exists(oCurrFileInfo.fileName())) 
			{
				oDstDir.remove(oCurrFileInfo.fileName());
			}
			/// 进行文件copy
			if (!QFile::copy(oCurrFileInfo.filePath(), oDstDir.filePath(oCurrFileInfo.fileName()))) 
			{          
				return false;
			}
#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux下写文件后,需要进行同步操作
                system("sync");
#endif
		}
	}

#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux下写文件后,需要进行同步操作
                system("sync");
#endif
	return true;
}
#endif
