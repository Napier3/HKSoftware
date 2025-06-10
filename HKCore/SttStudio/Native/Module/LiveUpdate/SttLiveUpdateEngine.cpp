#include "stdafx.h"
#include "SttLiveUpdateEngine.h"
#include "LiveUpdateBaseApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttLiveUpdateEngine::CSttLiveUpdateEngine():CSttClientTestEngine()
{
}

CSttLiveUpdateEngine::~CSttLiveUpdateEngine()
{

}

void CSttLiveUpdateEngine::OnSocketClose(CSttSocketDataBase *pSocket)
{
	//区分TestServer连接的和SttLiveUpdate连接的socket
	BOOL bSttLiveupdate = FALSE;
	if(g_theLiveUpdateBaseApp->m_oSttLiveUpdateEngine.m_pSttClientSocket == pSocket)
	{
		bSttLiveupdate = TRUE;
		g_theLiveUpdateBaseApp->m_bSttLiveupdateLink = FALSE;
	}
	else
	{
		g_theLiveUpdateBaseApp->m_bSttServerLink = FALSE;
	}

	CSttTestEngineClientData::OnSocketClose(pSocket);
#ifndef _PSX_IDE_QT_
	if (g_theLiveUpdateBaseApp->m_pMsgView && bSttLiveupdate)
	{
		g_theLiveUpdateBaseApp->m_pMsgView->PostMessage(WM_USER+2022,-1,(LPARAM)pSocket);
	}
#endif	
}

long CSttLiveUpdateEngine::Process_SysState_System_LiveUpdate(CSttSysState &oSysState)
{
	CSttParas *pParas = oSysState.GetSttParas();
	CDvmData *pParaData = NULL;

	pParaData = (CDvmData*)pParas->FindByID(STT_SYS_STATE_ID_IsSuccess);   //接收SttLiveUpdate允许启动更新的应答
	if (pParaData)
	{
		if(!oSysState.Get_IsSuccess())
		{
			g_theLiveUpdateBaseApp->m_bEnableLiveUpdate = FALSE;
			g_theLiveUpdateBaseApp->SetReply(TRUE);
			return 0;
		}

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_SYSID);
		if (pParaData && pParaData->m_strValue != g_theLiveUpdateBaseApp->m_pAts_System->m_strID)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("测试仪更新：系统ID不匹配，更新操作不能进行！"));

			g_theLiveUpdateBaseApp->m_bEnableLiveUpdate = FALSE;
			g_theLiveUpdateBaseApp->SetReply(TRUE);

			return 0;
		}

		g_theLiveUpdateBaseApp->m_bEnableLiveUpdate = TRUE;
		g_theLiveUpdateBaseApp->SetReply(TRUE);

		return 1;
	}
	else
	{
		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_REPLY);
		if (pParaData)
		{
			long nValue = CString_To_long(pParaData->m_strValue);
			if (g_theLiveUpdateBaseApp->m_nUpdateState == STATE_WAITINITDRIVER)
			{
				if (nValue==1)
				{
					CDvmData *pParaData1 = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_SYSID);
					if(pParaData1)
					{
						g_theLiveUpdateBaseApp->m_strTestAppSysID = pParaData1->m_strValue;
					}

					pParaData1 = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_SYSINDEX);
					if(pParaData1)
					{
						g_theLiveUpdateBaseApp->m_nTestAppSysIdx = CString_To_long(pParaData1->m_strValue);
					}

					pParaData1 = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_VERID);
					if (pParaData1)
					{
						g_theLiveUpdateBaseApp->m_strTestAppLocalVer = pParaData1->m_strValue;				
					}

					pParaData1 = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_VERINDEX);
					if (pParaData1)
					{
						g_theLiveUpdateBaseApp->m_nTestAppLocalVer = CString_To_long(pParaData1->m_strValue);
					}

					pParaData1 = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_PREVERID);
					if (pParaData1)
					{
						g_theLiveUpdateBaseApp->m_strTestAppLocalVerPrev = pParaData1->m_strValue;				
					}

					pParaData1 = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_PREVERINDEX);
					if (pParaData1)
					{
						g_theLiveUpdateBaseApp->m_nTestAppLocalVerPrev = CString_To_long(pParaData1->m_strValue);
					}

                    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("测试仪版本：系统ID(%s)，系统索引(%d)，当前版本号(%s)，当前版本索引(%d)，上版本号(%s)，上版本索引(%d)"),g_theLiveUpdateBaseApp->m_strTestAppSysID.GetString(),g_theLiveUpdateBaseApp->m_nTestAppSysIdx,
                        g_theLiveUpdateBaseApp->m_strTestAppLocalVer.GetString(),g_theLiveUpdateBaseApp->m_nTestAppLocalVer,g_theLiveUpdateBaseApp->m_strTestAppLocalVerPrev.GetString(),g_theLiveUpdateBaseApp->m_nTestAppLocalVerPrev);

					g_theLiveUpdateBaseApp->m_bEnableSendParas = TRUE;
					g_theLiveUpdateBaseApp->m_nUpdateState = STATE_WAITPARASRECV;
				}
				else
				{
					g_theLiveUpdateBaseApp->m_bEnableSendParas = FALSE;
					g_theLiveUpdateBaseApp->m_nUpdateState = STATE_NONE;
				}
			}
			else if (g_theLiveUpdateBaseApp->m_nUpdateState == STATE_WAITPARASRECV)
			{
				if (nValue==1)
				{
					g_theLiveUpdateBaseApp->m_bEnableSendFile = TRUE;
				}
				else
				{
					g_theLiveUpdateBaseApp->m_bEnableSendFile = FALSE;
				}
			}
			else if (g_theLiveUpdateBaseApp->m_nUpdateState == STATE_WAITFILERECV)
			{
				g_theLiveUpdateBaseApp->m_nUpdateState = STATE_WAITUPDATERESULT;
			}

			g_theLiveUpdateBaseApp->SetReply(TRUE);
			return 1;
		}

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_UPDATEINFO);
		if (pParaData)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,pParaData->m_strValue.GetString());
			g_theLiveUpdateBaseApp->m_bRecvUpdateInfo = TRUE;
		}

		pParaData = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_RESULT);
		if (pParaData)
		{
			CDvmData *pParaData1 = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_VERID);
			if (pParaData1)
			{
				g_theLiveUpdateBaseApp->m_strTestAppLocalVer = pParaData1->m_strValue;				
			}

			pParaData1 = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_VERINDEX);
			if (pParaData1)
			{
				g_theLiveUpdateBaseApp->m_nTestAppLocalVer = CString_To_long(pParaData1->m_strValue);
			}

			pParaData1 = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_PREVERID);
			if (pParaData1)
			{
				g_theLiveUpdateBaseApp->m_strTestAppLocalVerPrev = pParaData1->m_strValue;				
			}

			pParaData1 = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_PREVERINDEX);
			if (pParaData1)
			{
				g_theLiveUpdateBaseApp->m_nTestAppLocalVerPrev = CString_To_long(pParaData1->m_strValue);
			}

			g_theLiveUpdateBaseApp->SetReply(TRUE);
#ifndef _PSX_IDE_QT_
			if (g_theLiveUpdateBaseApp->m_pMsgView)
			{
				g_theLiveUpdateBaseApp->m_pMsgView->PostMessage(WM_USER+2022,CString_To_long(pParaData->m_strValue),0);
			}
#endif
		}
	}

	return 1;
}



