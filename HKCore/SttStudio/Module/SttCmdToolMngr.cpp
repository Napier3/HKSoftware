#include "stdafx.h"
#include "SttCmdToolMngr.h"
#include "../../Module/System/TickCount32.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////文件上传下载工具类///////////////////////

CSttCmdTool::CSttCmdTool()
{
	m_nRetResult = STT_CMD_RET_RESULT_NULL;

	m_pCmdOverTimeMsgRcv = NULL;
}

CSttCmdTool::~CSttCmdTool()
{

}

void CSttCmdTool::OnSendCmdFailFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID)
{
	SetRetResult_Failure();

	if (m_pCmdOverTimeMsgRcv != NULL)
	{	
		m_pCmdOverTimeMsgRcv->OnSendCmdFinish(pSocketRef,nCmdType,pszCmdID);		
	}
}

void CSttCmdTool::OnSendCmdFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID)
{
	SetRetResult_Finish();

	if (m_pCmdOverTimeMsgRcv != NULL)
	{	
		m_pCmdOverTimeMsgRcv->OnSendCmdFinish(pSocketRef,nCmdType,pszCmdID);		
	}
}

void CSttCmdTool::OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID)
{
	SetRetResult_Timeout();

	if (m_pCmdOverTimeMsgRcv != NULL)
	{	
		m_pCmdOverTimeMsgRcv->OnSendCmdOverTime(pSocketRef,nCmdType,pszCmdID);		
	}
}

void CSttCmdTool::AttachCmdOverTimeMsgRcv(CSttCmdOverTimeMsgRcv *pCmdOverTimeMsgRcv)
{
	m_pCmdOverTimeMsgRcv = pCmdOverTimeMsgRcv;
}

BOOL CSttCmdTool::SendCmd(CSttSocketDataBase *pSocket,CSttCmdBase *pCmd,long nTimeout)
{
	long nCount = GetCount();
	CTickCount32 oTickCount32(FALSE);

	CSttCmdOverTimeTool::AddSttCmd(pSocket,pCmd->m_nType_Cmd,pCmd->m_strID,GetTickCount(), nTimeout, this);

	pSocket->SendCmd(pCmd);

	while(TRUE)
	{
		oTickCount32.DoEvents(10);
		if (IsRetResult_Finish() 
			|| IsRetResult_Failure()
			|| IsRetResult_Timeout())
		{
			break;
		}		
	}

	if (IsRetResult_Finish())
	{
		return TRUE;
	}

	return FALSE;
}

void CSttCmdTool::SetRetResult_NULL()
{
	m_nRetResult = STT_CMD_RET_RESULT_NULL;
}

void CSttCmdTool::SetRetResult_Proccessing()
{
	m_nRetResult = STT_CMD_RET_RESULT_PROCESSING;
}

void CSttCmdTool::SetRetResult_Failure()
{
	m_nRetResult = STT_CMD_RET_RESULT_FAILURE;
}

void CSttCmdTool::SetRetResult_Timeout()
{
	m_nRetResult = STT_CMD_RET_RESULT_TIMEOUT;
}

void CSttCmdTool::SetRetResult_Finish()
{
	m_nRetResult = STT_CMD_RET_RESULT_FINISH;
}

BOOL CSttCmdTool::IsRetResult_NULL()
{
	return m_nRetResult==STT_CMD_RET_RESULT_NULL;
}

BOOL CSttCmdTool::IsRetResult_Proccessing()
{
	return m_nRetResult==STT_CMD_RET_RESULT_PROCESSING;
}

BOOL CSttCmdTool::IsRetResult_Finish()
{
	return m_nRetResult==STT_CMD_RET_RESULT_FINISH;
}

BOOL CSttCmdTool::IsRetResult_Failure()
{
	return m_nRetResult==STT_CMD_RET_RESULT_FAILURE;
}

BOOL CSttCmdTool::IsRetResult_Timeout()
{
	return m_nRetResult==STT_CMD_RET_RESULT_TIMEOUT;
}
