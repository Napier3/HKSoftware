#include "stdafx.h"
#include "SttLiveUpdateServerEngine.h"
#include "SttLiveUpdateCoreBaseApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttLiveUpdateServerEngine::CSttLiveUpdateServerEngine()
{
}

CSttLiveUpdateServerEngine::~CSttLiveUpdateServerEngine()
{

}

CSttLiveUpdateServerEngine* CSttLiveUpdateServerEngine::Create(char *pszIP, int nPort)
{
	m_nSttTestServerEngineRef++;

	if (m_nSttTestServerEngineRef == 1)
	{
		g_pSttTestServerEngine = new CSttLiveUpdateServerEngine();
		g_pSttTestServerEngine->InitSttServerEngine(pszIP, nPort);
	}

	return (CSttLiveUpdateServerEngine*)g_pSttTestServerEngine;
}

void CSttLiveUpdateServerEngine::Release()
{
	m_nSttTestServerEngineRef--;

	if (m_nSttTestServerEngineRef == 0)
	{
		CSttLiveUpdateServerEngine *pTestServer = (CSttLiveUpdateServerEngine*)g_pSttTestServerEngine;
		pTestServer->ExitSttServerEngine();
		delete pTestServer;
		g_pSttTestServerEngine = NULL;
	}
}

void CSttLiveUpdateServerEngine::SendRetState(CSttSocketDataBase *pClientSocket, BOOL bRet)
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
	pClientSocket->SendCmd(&oSysState);
	oSysState.RemoveAll();
}

void CSttLiveUpdateServerEngine::OnSocketClose(CSttSocketDataBase *pSocket)
{
	CSttTestEngineServerBase::OnSocketClose(pSocket);
}

long CSttLiveUpdateServerEngine::Process_Cmd_System_LiveUpdate(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
	CDvmData* pParaData = NULL;
	CSttParas *pParas = oSysCmd.GetSttParas();

	if(pParas->m_strID == UPDATEPARAS_TYPE_LOCAL)
	{
		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_VERFILE); 
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_strLocalZipFile.Format(_T("%s%s"),_P_GetSystemPath(),pParaData->m_strValue.GetString());
		}

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_SYSINDEX);
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_nIdxSys = CString_To_long(pParaData->m_strValue);
		}

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_VERID);
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_strIDVer = pParaData->m_strValue;
		}

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_VERINDEX);
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_nIdxVer = CString_To_long(pParaData->m_strValue);
		}

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_UNZIPPATH);
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_strUnzipPath.Format(_T("%s%s"),_P_GetSystemPath(),pParaData->m_strValue.GetString());
		}

		g_theLiveUpdateBaseApp->m_nUpdateStyle = UPDATESTYLE_LOCAL;

		g_theLiveUpdateBaseApp->m_bParasRecvSuc = TRUE;
		SendRetState(pClientSocket,true);
	}
	else if (pParas->m_strID == UPDATEPARAS_TYPE_REMOTE)
	{
		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_IPCLOUD); 
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_strServerIP = pParaData->m_strValue;
		}

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_PORTCLOUD); 
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_nServerPort = CString_To_long(pParaData->m_strValue);
		}

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_FTPPORTCLOUD); 
		g_theLiveUpdateBaseApp->m_nServerFtpPort = CString_To_long(pParaData->m_strValue);

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_SYSINDEX); 
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_nIdxSys = CString_To_long(pParaData->m_strValue);
		}

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_VERID);
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_strIDVer = pParaData->m_strValue;
		}

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_VERINDEX); 
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_nIdxVer = CString_To_long(pParaData->m_strValue);
		}

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_UNZIPPATH); 
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_strUnzipPath.Format(_T("%s%s"),_P_GetSystemPath(),pParaData->m_strValue.GetString());
		}

		g_theLiveUpdateBaseApp->m_nUpdateStyle = UPDATESTYLE_REMOTE;

		g_theLiveUpdateBaseApp->m_bParasRecvSuc = TRUE;
		SendRetState(pClientSocket,true);
	}
	else if (pParas->m_strID == UPDATEPARAS_TYPE_MOBILE)
	{
		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_IPCLOUD); 
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_strServerIP = pParaData->m_strValue;
		}

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_PORTCLOUD); 
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_nServerPort = CString_To_long(pParaData->m_strValue);
		}

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_FTPPORTCLOUD); 
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_nServerFtpPort = CString_To_long(pParaData->m_strValue);
		}

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_SYSID); 
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_strIDSys = pParaData->m_strValue;
		}

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_VERID);
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_strIDVer = pParaData->m_strValue;
		}

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_UNZIPPATH); 
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_strUnzipPath.Format(_T("%s%s"),_P_GetSystemPath(),pParaData->m_strValue.GetString());
		}

		CSttNativeCfgLiveUpdate* pNativeLiveUpdate = g_theLiveUpdateBaseApp->m_oNativeCfgMngr.GetCfgLiveUpdate();
		ASSERT(pNativeLiveUpdate != NULL);
		if(pNativeLiveUpdate->m_strID_System != g_theLiveUpdateBaseApp->m_strIDSys)
		{
			CString strInfo;
			strInfo.Format(_T("测试仪更新：更新命令的系统ID【%s】与测试仪系统ID不一致，更新不能完成!"),g_theLiveUpdateBaseApp->m_strIDSys.GetString());
			g_theLiveUpdateBaseApp->SendUpdateInfo(strInfo);
			g_theLiveUpdateBaseApp->m_bParasRecvSuc = FALSE;
			SendRetState(pClientSocket,false);
		}
		else
		{
			g_theLiveUpdateBaseApp->m_nIdxSys = pNativeLiveUpdate->m_nIndex_System;
			g_theLiveUpdateBaseApp->m_nIdxVer = LIVEUPDATE_NEWEST_VERINDEX;		//移动更新时为最新版
			g_theLiveUpdateBaseApp->m_nUpdateStyle = UPDATESTYLE_MOBILE;
			g_theLiveUpdateBaseApp->m_bParasRecvSuc = TRUE;
			SendRetState(pClientSocket,true);
		}
	}
	else if(pParas->m_strID==UPDATEPARAS_TYPE_FILE)	//文件结束
	{
		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_FILEOVER);
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_bFileRecvOver = TRUE;
		}

		SendRetState(pClientSocket,true);
	}
	else if(pParas->m_strID==UPDATEPARAS_TYPE_STOP) //停止更新加电重启
	{
		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_STOP);
		if(pParaData)
		{
			g_theLiveUpdateBaseApp->m_bStopUpdate = TRUE;
		}

		SendRetState(pClientSocket,true);
	}
	else if(pParas->m_strID==UPDATEPARAS_TYPE_ROLLBACK)
	{
		g_theLiveUpdateBaseApp->m_bParasRecvSuc = TRUE;
		g_theLiveUpdateBaseApp->m_nUpdateStyle = UPDATESTYLE_ROLLBACK;

		SendRetState(pClientSocket,true);
	}

	return 1;
}


