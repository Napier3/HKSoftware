#include "stdafx.h"
#include "EdgeMqttClientBase.h"
#include "../../../Module/System/StringTokenizer.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 

CEdgeMqttClientBase::CEdgeMqttClientBase()
:CMqttClientToPxEngine()
{

}

CEdgeMqttClientBase::~CEdgeMqttClientBase()
{

}


/************************
订阅主题：DeviceID
/v1/${edgeId}/device/request
**************************/
BOOL CEdgeMqttClientBase::SubcribeMqttTopic(int nQos)
{
	if (!ConnectServer())
	{
		return FALSE;
	}

	return TRUE;
}

//物联协议命令发送
long CEdgeMqttClientBase::Send(CExBaseObject *pCmdBase)
{
	if (!ConnectServer())
	{
		return -3;
	}

	if(pCmdBase->GetClassID() == STTCMDCLASSID_CSTTSYSSTATE)
	{
		return Send_Stt(pCmdBase);
	}

	CEdgeCmd* pCmd = (CEdgeCmd*)pCmdBase;
	char* strJson = NULL;
	//yzj 2021-10-30 自动测试是GBK的
	//pCmd->GetXml_UTF8(CEdgeCmdMngrXmlRWKeys::g_pXmlKeys, &strJson, 0, _JSON_TYPE_);
	pCmd->GetXml(CEdgeCmdMngrXmlRWKeys::g_pXmlKeys, &strJson, 0, _JSON_TYPE_);
	CString strTopic = _T("");
	strTopic.Format(_T("/v1/%s/%s/%s"), pCmd->m_strID, 
		edge_GetCmdTypeID(pCmd->GetProcedureID()), edge_GetServerToEdgeCmdID(pCmd->GetProcedureID()));

	//如果存在保留的json指针,则需要手动为生成的json报文添加字段
	CJSON* pJson = NULL;
	if(pCmd->GetEdgeParam())
	{
		pJson = CJSON_Parse(strJson);
		CJSON* pParamJson = CJSON_GetObjectItem(pJson, _T("param"));
		//分别判断param中的3个json保留指针
		if(pCmd->GetEdgeParam()->GetDevJson())
		{
			CJSON_AddItemToObject(pParamJson, EDGE_PROCEDURE_VAR_dev, pCmd->GetEdgeParam()->GetDevJson());
			pCmd->GetEdgeParam()->SetDevJson(NULL);
		}
		if (pCmd->GetEdgeParam()->GetMountJson())
		{
			CJSON_AddItemToObject(pParamJson, EDGE_PROCEDURE_VAR_mount, pCmd->GetEdgeParam()->GetMountJson());
			pCmd->GetEdgeParam()->SetMountJson(NULL);
		}
		if(pCmd->GetEdgeParam()->GetDeviceIdsJson())
		{
			CJSON_AddItemToObject(pParamJson, EDGE_PROCEDURE_VAR_deviceIds, pCmd->GetEdgeParam()->GetDeviceIdsJson());
			pCmd->GetEdgeParam()->SetDeviceIdsJson(NULL);
		}
		if(pCmd->GetEdgeParam()->GetDeviceDataJson())
		{
			CJSON_AddItemToObject(pParamJson, EDGE_PROCEDURE_VAR_data, pCmd->GetEdgeParam()->GetDeviceDataJson());
			pCmd->GetEdgeParam()->SetDeviceDataJson(NULL);
		}
		if(pCmd->GetEdgeParam()->GetContParaJson())
		{
			CJSON_AddItemToObject(pParamJson, EDGE_PROCEDURE_VAR_contPara, pCmd->GetEdgeParam()->GetContParaJson());
			pCmd->GetEdgeParam()->SetContParaJson(NULL);
		}

		strJson = CJSON_Print(pJson);
	}

	BOOL bRet = m_oMqttClient.PublicTopic(strTopic,strJson,strlen(strJson));

	delete strJson;

	CJSON_Delete(pJson);
	return bRet;
}

BOOL CEdgeMqttClientBase::Send_Stt(CExBaseObject *pCmdBase)
{
	CSttSysState *pSttSysState = (CSttSysState *)pCmdBase;
	CString strTopic;
	strTopic.Format(_T("%s/%s/IotState/UpdateDataset"), pSttSysState->m_strFromSN, m_strDeviceSN);
	char *pszBuf = NULL;
	long nLen = 0;
	nLen = pSttSysState->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszBuf,0);
	BOOL nRes = CMqttClientToPxEngine::Send(pszBuf, nLen, strTopic);
	delete pszBuf;
	return nRes;
}

CString CEdgeMqttClientBase::GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)
{
	CString strTopic;

	CString strTopicType = edge_CmdTypeID_Idx_To_Str(nCmdType);

	strTopic.Format(_T("/%s/%s/%s/%s"),m_strVersion,m_strDeviceSN,strTopicType,pszCmdID);

	return strTopic;
}

BOOL CEdgeMqttClientBase::AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType)
{
	CStringTokenizer oToken;
	oToken.Init(strTopic, '/');

	if (oToken.GetStringsCount() != 5)
	{
		return FALSE;
	}

	CString strTopicType, strVersion, strCurDeviceID;
	strVersion = oToken.GetToken(0);
	strCurDeviceID = oToken.GetToken(1);
	strTopicType = oToken.GetToken(2);

// 	if (strVersion != m_strVersion || strCurDeviceID != m_strDeviceSN)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Edge[%s][%s] != [%s][%s]")
// 			, m_strDeviceSN, m_strVersion, strCurDeviceID, strVersion);
// 	}

	strFromSN = strCurDeviceID;
	nCmdType = edge_CmdTypeID_Str_To_Idx(strTopicType);
	char *pTemp = (char *)oToken.GetToken(3);
	memcpy(pszCmdID,pTemp,strlen(pTemp));

	return TRUE;
}