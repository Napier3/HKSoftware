#include "stdafx.h"
#include "MqttFileOptrMngr.h"
#include "../SttMqttClientEngineConfig.h"
#include "../SttMqttClientTool.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CMqttFileOptrMngr::CMqttFileOptrMngr()
{

}
CMqttFileOptrMngr::~CMqttFileOptrMngr()
{

}

void CMqttFileOptrMngr::OnSendCmdFailFinish(const char *pszSrcID, const char *pszCmdType, UINT nErrCode)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnSendCmdFailFinish:[%s][%s][%d]"),pszSrcID,pszCmdType,nErrCode);

	CString strID = pszSrcID;
	CMqttFileOptr *pFind = (CMqttFileOptr *)FindByID(strID);
	if (pFind != NULL)
	{
		pFind->m_bValid = FALSE;
	}
}

void CMqttFileOptrMngr::OnSendCmdFinish(const char *pszSrcID, const char *pszCmdType)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnSendCmdFinish:[%s][%s]"),pszSrcID,pszCmdType);

	CString strID = pszSrcID;
	CMqttFileOptr *pFind = (CMqttFileOptr *)FindByID(strID);
	if (pFind != NULL)
	{
		pFind->m_bValid = FALSE;
	}
}

void CMqttFileOptrMngr::OnSendCmdOverTime(const char *pszSrcID, const char *pszTopic)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnSendCmdOverTime:[%s][%s]"),pszSrcID,pszTopic);

	CString strID = pszSrcID;
	CMqttFileOptr *pFind = (CMqttFileOptr *)FindByID(strID);
	if (pFind != NULL)
	{
		pFind->m_bValid = FALSE;
	}
}

void CMqttFileOptrMngr::SubcribeFtpToic()
{
	CString strDstID;
	CSttMqttClientEngineConfig::GetMqttFtpServerIP(strDstID);

	CString strTopic1,strTopic2,strTopic3,strTopic4,strTopic5;
	strTopic1.Format(_T("%s/+/UploadCmd/UploadFileName"),strDstID);
	strTopic2.Format(_T("%s/+/UploadCmd/UploadFileData"),strDstID);
	strTopic3.Format(_T("%s/+/DownloadCmd/DownloadFileName"),strDstID);
	strTopic4.Format(_T("%s/+/DownloadCmd/UploadFileName/Reply"),strDstID);
	strTopic5.Format(_T("%s/+/DownloadCmd/UploadFileData/Reply"),strDstID);

	CSttMqttClientTool::SubscribeTopic(strTopic1,0);
	CSttMqttClientTool::SubscribeTopic(strTopic2,0);
	CSttMqttClientTool::SubscribeTopic(strTopic3,0);
	CSttMqttClientTool::SubscribeTopic(strTopic4,0);
	CSttMqttClientTool::SubscribeTopic(strTopic5,0);
}

void CMqttFileOptrMngr::CheckMqttFtpMsgRecv(CStringTokenizer &oToken,char *pBuf,long nLen)
{
	if (IsUploadCmdTopic(oToken))
	{
		Process_UploadFileCmd(oToken,pBuf,nLen);
	}
	else if (IsDownloadCmdTopic(oToken))
	{
		Process_DownloadFileCmd(oToken,pBuf,nLen);
	}
}

/*******************************
DstID/+[SrcID]/UploadCmd/UploadFileName
DstID/+[SrcID]/UploadCmd/UploadFileData
*******************************/
long CMqttFileOptrMngr::Process_UploadFileCmd(CStringTokenizer &oToken,char *pBuf,long nLen)
{
	CString strDstID,strSrcID,strCmd;
	strDstID = oToken.GetToken(0);
	strSrcID = oToken.GetToken(1);
	strCmd = oToken.GetToken(3);

	CMqttFileOptr *pFind = (CMqttFileOptr *)FindByID(strSrcID);
	if (pFind != NULL)
	{
		if (!pFind->m_bValid)
		{
			Delete(pFind);
			pFind = NULL;
		}
	}

	if (strCmd == MQTT_FTP_CMD_UploadFileName)
	{//开始上传文件
		if(pFind != NULL)
		{//当前正在传文件，提示失败
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("UploadCmd/UploadFileName:系统忙。"));
			return 1;
		}

		pFind = (CMqttFileOptr *)AddNewChild(new CMqttFileOptr);
		pFind->AttachCmdOverTimeMsgRcv(this);
		pFind->Process_UploadCmd_UploadFileName(strSrcID,strDstID,pBuf,nLen);
	}
	else if (strCmd == MQTT_FTP_CMD_UploadFileData)
	{
		if(pFind == NULL)
		{//对象不存在
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("UploadCmd/UploadFileData:管理对象不存在。"));
			return 1;
		}

		CString strTopic;
		strTopic.Format(_T("%s/%s/UploadCmd/UploadFileData"),strDstID,strSrcID);

		if (pFind->m_strCurExceptTopic != strTopic)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("UploadCmd/UploadFileData:与期待主题不一致[%s]。"),pFind->m_strCurExceptTopic);
			return 1;
		}

		pFind->Process_UploadCmd_UploadFileData(pBuf,nLen);
	}

	return 0;
}

/*******************************
DstID/+[SrcID]/DownloadCmd/DownloadFileName
DstID/+[SrcID]/DownloadCmd/UploadFileName/Reply
DstID/+[SrcID]/DownloadCmd/UploadFileData/Reply
*******************************/
long CMqttFileOptrMngr::Process_DownloadFileCmd(CStringTokenizer &oToken,char *pBuf,long nLen)
{
	CString strDstID,strSrcID,strCmd;
	strDstID = oToken.GetToken(0);
	strSrcID = oToken.GetToken(1);
	strCmd = oToken.GetToken(3);

	CMqttFileOptr *pFind = (CMqttFileOptr *)FindByID(strSrcID);
	if (pFind != NULL)
	{
		if (!pFind->m_bValid)
		{
			Delete(pFind);
			pFind = NULL;
		}
	}

	if (strCmd == MQTT_FTP_CMD_DownloadFileName)
	{//开始上传文件
		if(pFind != NULL)
		{//当前正在传文件，提示失败
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("DownloadCmd/DownloadFileName:系统忙。"));
			return 1;
		}

		pFind = (CMqttFileOptr *)AddNewChild(new CMqttFileOptr);
		pFind->AttachCmdOverTimeMsgRcv(this);
		pFind->Process_DownloadCmd_DownloadFileName(strSrcID,strDstID,pBuf,nLen);
	}
	else if (strCmd == MQTT_FTP_CMD_UploadFileName)
	{// UploadFileName/Reply
		if(pFind == NULL)
		{//对象不存在
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("DownloadCmd/UploadFileName/Reply:管理对象不存在。"));
			return 1;
		}

		CString strTopic;
		strTopic.Format(_T("%s/%s/DownloadCmd/UploadFileName/Reply"),strDstID,strSrcID);

		if (pFind->m_strCurExceptTopic != strTopic)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("DownloadCmd/UploadFileName/Reply:与期待主题不一致[%s]。"),pFind->m_strCurExceptTopic);
			return 1;
		}

		pFind->Process_DownloadCmd_UploadFileNameReply(pBuf,nLen);
	}
	else if (strCmd == MQTT_FTP_CMD_UploadFileData)
	{// UploadFileData/Reply
		if(pFind == NULL)
		{//对象不存在
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("DownloadCmd/UploadFileData/Reply:管理对象不存在。"));
			return 1;
		}

		CString strTopic;
		strTopic.Format(_T("%s/%s/DownloadCmd/UploadFileData/Reply"),strDstID,strSrcID);

		if (pFind->m_strCurExceptTopic != strTopic)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("DownloadCmd/UploadFileData/Reply:与期待主题不一致[%s]。"),pFind->m_strCurExceptTopic);
			return 1;
		}

		pFind->Process_DownloadCmd_UploadFileDataReply(pBuf,nLen);
	}

	return 0;
}