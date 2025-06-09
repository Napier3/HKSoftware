#include "stdafx.h"
#include "SttMqttEngineBase.h"
#include "../../SttRegisterCode.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 

CSttXDevice g_oTheOwnIotDevice;

CSttMqttEngineBase::CSttMqttEngineBase()
{
	m_strIP = _T("127.0.0.1");
	m_nPort = 1886;
	m_strClientID = _T("TestClientID");

	CSttParas oSttParas;
	stt_mqtt_GetParasBuffer(oSttParas, m_oTopicHeartCmbn);
}

CSttMqttEngineBase::~CSttMqttEngineBase()
{

}

void CSttMqttEngineBase::ReSubcribeMqttTopic()
{
	UnSubcribeMqttTopic();
	SubcribeMqttTopic(0);
}

BOOL CSttMqttEngineBase::SubscribeTopic(const char* pszTopic,int nQos)
{
	return m_oMqttClient.SubscribeTopic(pszTopic, nQos);
}

BOOL CSttMqttEngineBase::UnSubscribeTopic(const char* pszTopic)
{
	return m_oMqttClient.UnSubscribeTopic(pszTopic);
}

void CSttMqttEngineBase::OnMqttMsgRecieve(CSttMqttTopicParser &oSttMqttTopicParser)
{
	switch (oSttMqttTopicParser.m_nCount)
	{
	case 2:
		//²âÊÔÒÇSN/Register
		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[1], STT_CMD_TYPE_REMOTE_Register) == 0)
		{
			return OnRegister(oSttMqttTopicParser);
		}

		//²âÊÔÒÇSN/UnRegister¡£
		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[1], STT_CMD_TYPE_REMOTE_UnRegister) == 0)
		{
			return OnUnRegister(oSttMqttTopicParser);
		}

		//²âÊÔ¶ËSN/QueryDevice¡£
		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[1], STT_CMD_TYPE_TEST_QueryDevice) == 0)
		{
			return OnQueryDevice(oSttMqttTopicParser);
		}

		//²âÊÔ¶ËSN/QueryFile¡£
		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[1], STT_CMD_TYPE_TEST_QueryFile) == 0)
		{
			return OnQueryFile(oSttMqttTopicParser);
		}

		//²âÊÔÒÇSN/RTDATA
		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[1], SYS_STATE_RETTYPE_RTDATA) == 0)
		{
			// return OnRTDATA(oSttMqttTopicParser);
		}

		//²âÊÔÒÇSN/EXCEPTION
		if  (strcmp(oSttMqttTopicParser.m_pszSubTopic[1], SYS_STATE_RETTYPE_EXCEPTION) == 0)
		{
			// return OnEXCEPTION(oSttMqttTopicParser);
		}

		//²âÊÔÒÇSN/Debug
		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[1], STT_CMD_TYPE_DEBUG_ConfigDebug) == 0)
		{
			return ;//OnConfigDebug(oSttMqttTopicParser);
		}

		//²âÊÔÒÇSN/HeartBeat
		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[1], STT_CMD_TYPE_TEST_HeartBeat) == 0)
		{
			// return OnHeartBeat(oSttMqttTopicParser);
		}
		break;

	case 3:
		//²âÊÔ¶ËSN/²âÊÔÒÇSN/CreateTest
		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2], STT_CMD_TYPE_ATS_CreateTest) == 0)
		{
			return OnCreateTest(oSttMqttTopicParser);
		}

		//²âÊÔ¶ËSN/²âÊÔÒÇSN/CloseTest
		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2],STT_CMD_TYPE_ATS_CloseTest) == 0)
		{
			return OnCloseTest(oSttMqttTopicParser);
		}

		//²âÊÔ¶ËSN/²âÊÔÒÇSN/StartTest¡£
		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2], STT_CMD_TYPE_TEST_StartTest) == 0)
		{
			return OnStartTest(oSttMqttTopicParser);
		}        

		//²âÊÔ¶ËSN/²âÊÔÒÇSN/StopTest
		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2], STT_CMD_TYPE_TEST_StopTest) == 0)
		{
			return OnStopTest(oSttMqttTopicParser);
		}

		//²âÊÔ¶ËSN/²âÊÔÒÇSN/ConfigDevice
		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2], STT_CMD_TYPE_TEST_ConfigDevice) == 0)
		{
			return OnConfigDevice(oSttMqttTopicParser);
		}

		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[1], SYS_STATE_RETTYPE_EVENT) == 0)
		{
			//²âÊÔÒÇSN/EVENT/TestStarted
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2], SYS_STATE_EVENT_OnTestStarted) == 0)
			{
				// return OnEVENT_TestStarted(oSttMqttTopicParser);
			}
			//²âÊÔÒÇSN/EVENT/TestFinished
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2], SYS_STATE_EVENT_OnTestFinished) == 0)
			{
				// return OnEVENT_TestFinished(oSttMqttTopicParser);
			}

			//²âÊÔÒÇSN/EVENT/TestStoped
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2], SYS_STATE_EVENT_OnTestStoped) == 0)
			{
				// return OnEVENT_TestStoped(oSttMqttTopicParser);
			}

			//²âÊÔÒÇSN/EVENT/RcdDataLoadFinished
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2], SYS_STATE_EVENT_OnRcdDataLoadFinished) == 0)
			{
				// return OnEVENT_RcdDataLoadFinished(oSttMqttTopicParser);
			}
		}

		//²âÊÔÒÇSN/Register/Reply
		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2], STT_CMD_TYPE_ALL_Reply) == 0)
		{
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[1], STT_CMD_TYPE_REMOTE_Register) == 0)
			{
				// return OnRegisterReply(oSttMqttTopicParser);
			}

			//²âÊÔÒÇSN/UnRegister/Reply
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[1], STT_CMD_TYPE_REMOTE_UnRegister) == 0)
			{
				// return OnUnRegisterReply(oSttMqttTopicParser);
			}

			//²âÊÔ¶ËSN/QueryDevice/Reply
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[1], STT_CMD_TYPE_TEST_QueryDevice) == 0)
			{
				// return OnQueryDeviceReply(oSttMqttTopicParser);
			}

			//²âÊÔ¶ËSN/QueryFile/Reply
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[1], STT_CMD_TYPE_TEST_QueryFile) == 0)
			{
				// return OnQueryFileReply(oSttMqttTopicParser);
			}
		}
		break;

	case 4:
		//·¢ËÍ¶ËSN/½ÓÊÕ¶ËSN/Record/Begin
		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2], STT_CMD_TYPE_TEST_Record) == 0)
		{
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[3], STT_CMD_TYPE_TEST_RecordBegin) == 0)
			{
				return OnRecordBegin(oSttMqttTopicParser);
			}

			//·¢ËÍ¶ËSN/½ÓÊÕ¶ËSN/Record/Finish
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[3], STT_CMD_TYPE_TEST_RecordFinish) == 0)
			{
				return OnRecordFinish(oSttMqttTopicParser);
			}	

			//¿ØÖÆ¶ËSN/·¢ËÍ¶ËSN/Record/Cancel
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[3], STT_CMD_TYPE_TEST_RecordCancel) == 0)
			{
				return OnRecordCancel(oSttMqttTopicParser);
			}	

			//·¢ËÍ¶ËSN/½ÓÊÕ¶ËSN/Record/Call
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[3], STT_CMD_TYPE_TEST_RecordCall) == 0)
			{
				return OnRecordCall(oSttMqttTopicParser);
			}	
		}

		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[3], STT_CMD_TYPE_ALL_Reply) == 0)
		{
			//²âÊÔ¶ËSN/²âÊÔÒÇSN/CreateTest/Reply
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2], STT_CMD_TYPE_ATS_CreateTest) == 0)
			{
				// return OnCreateTestReply(oSttMqttTopicParser);
			}	

			//²âÊÔ¶ËSN/²âÊÔÒÇSN/CloseTest/Reply
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2], STT_CMD_TYPE_ATS_CloseTest) == 0)
			{
				// return OnCloseTestReply(oSttMqttTopicParser);
			}	

			//²âÊÔ¶ËSN/²âÊÔÒÇSN/StartTest/Reply
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2], STT_CMD_TYPE_ATS_StartTest) == 0)
			{
				// return OnStartTestReply(oSttMqttTopicParser);
			}	

			//²âÊÔ¶ËSN/²âÊÔÒÇSN/StopTest/Reply
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2], STT_CMD_TYPE_ATS_StopTest) == 0)
			{
				// return OnStopTestReply(oSttMqttTopicParser);
			}

			//²âÊÔ¶ËSN/²âÊÔÒÇSN/ConfigDevice/Reply
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2], STT_CMD_TYPE_ATS_ConfigDevice) == 0)
			{
				// return OnConfigDeviceReply(oSttMqttTopicParser);
			}
		}

		break;


		//·¢ËÍ¶ËSN/½ÓÊÕ¶ËSN/Record/Data/±àºÅ

	case 5:
		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2], STT_CMD_TYPE_TEST_Record) == 0)
		{
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[3], STT_CMD_TYPE_TEST_RecordData) == 0)

			{
				return OnRecordData(oSttMqttTopicParser);
			}	
		}
		//·¢ËÍ¶ËSN/½ÓÊÕ¶ËSN/Record/Data/Reply
		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2], STT_CMD_TYPE_TEST_Record) == 0)
		{
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[4], STT_CMD_TYPE_ALL_Reply) == 0)	

			{

				if (strcmp(oSttMqttTopicParser.m_pszSubTopic[3], STT_CMD_TYPE_TEST_RecordData) == 0)
				{

					// return OnRecordDataReply(oSttMqttTopicParser);
				}
				//·¢ËÍ¶ËSN/½ÓÊÕ¶ËSN/Record/Begin/Reply
				if (strcmp(oSttMqttTopicParser.m_pszSubTopic[3], STT_CMD_TYPE_TEST_RecordBegin) == 0)
				{

					// return OnRecordBeginReply(oSttMqttTopicParser);
				}
				//·¢ËÍ¶ËSN/½ÓÊÕ¶ËSN/Record/Finish/Reply
				if (strcmp(oSttMqttTopicParser.m_pszSubTopic[3], STT_CMD_TYPE_TEST_RecordFinish) == 0)
				{

					// return OnRecordFinishReply(oSttMqttTopicParser);
				}
				//¿ØÖÆ¶ËSN/·¢ËÍ¶ËSN/Record/Cancel/Reply
				if (strcmp(oSttMqttTopicParser.m_pszSubTopic[3], STT_CMD_TYPE_TEST_RecordCancel) == 0)
				{

					// return OnRecordCancelReply(oSttMqttTopicParser);
				}
				//·¢ËÍ¶ËSN/½ÓÊÕ¶ËSN/Record/Call/Reply
				if (strcmp(oSttMqttTopicParser.m_pszSubTopic[3], STT_CMD_TYPE_TEST_RecordCall) == 0)
				{

					// return OnRecordCallReply(oSttMqttTopicParser);
				}
			}
		}

		break;
	}

}

void CSttMqttEngineBase::OnMqttDisconnected(char *pszErr)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnDisconnected:[ErrInfo=%s]"),pszErr);
}

long CSttMqttEngineBase::PublicTopic(char *strTopic, char *pBuf, long nLen)
{
	BOOL bRet = m_oMqttClient.PublicTopic(strTopic, pBuf, nLen);

	if (bRet)
	{
		return nLen;
	}

	return -1;
}

long CSttMqttEngineBase::PublicTopic(CSttMqttTopicCmbn &oTopicCmbn)
{
	BOOL bRet = m_oMqttClient.PublicTopic(oTopicCmbn.CmbnTopic()
		, oTopicCmbn.m_pszBuffer, oTopicCmbn.m_nBufferLength);

	if (bRet)
	{
		return oTopicCmbn.m_nBufferLength;
	}

	return -1;
}

BOOL CSttMqttEngineBase::Connect(const CString &strIP,long nPort, const CString &strClientIDKey,const CString &strUser,const CString &strPwd,BOOL bAuthority)
{
	if (m_oMqttClient.IsConnectSuccessful())
	{
		return TRUE;
	}

	m_strIP = strIP;
	m_nPort = nPort;

	if (strClientIDKey.GetLength() > 0)
	{
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		m_strClientID.Format(_T("%s_%u_%02d%02d%03d"), strClientIDKey.GetString()
			,stt_GetMachineCode_U32(),tm.wMinute,tm.wSecond,tm.wMilliseconds);
	}


	m_oMqttClient.AttachMqttMsgInterface(this);
	BOOL bRet = m_oMqttClient.InitMqttClient(strIP,nPort,m_strClientID,strUser,strPwd,bAuthority);

	if (bRet)
	{
		//Á¬½Ó³É¹¦ºó£¬Ö÷¶¯¶©ÔÄÖ÷Ìâ
		SubcribeMqttTopic(0);
	}

	return bRet;
}

void CSttMqttEngineBase::Disconnect()
{
	m_oMqttClient.Disconnect();
}



//////////////////////////////////////////////////////////////////////////
CSttParas* stt_mqtt_get_paras(CSttMqttTopicParser &oParser)
{
	CSttParas *pParas = new CSttParas();

	stt_mqtt_get_paras(oParser, *pParas);

	return pParas;
}

void stt_mqtt_get_paras(CSttMqttTopicParser &oParser, CSttParas &oSttParas)
{
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oSttParas.SetXml_UTF8(oParser.m_pMqttPkgBuffer, oParser.m_nMqttPkgBufferLen, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

void stt_mqtt_get_paras(CSttMqttTopicParser &oParser, CSttTestCmd &oSttTestCmd, const long &nXmlRWType)
{
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oSttTestCmd.SetXml_UTF8(oParser.m_pMqttPkgBuffer, oParser.m_nMqttPkgBufferLen, CSttCmdDefineXmlRWKeys::g_pXmlKeys, nXmlRWType);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

//

//////////////////////////////////////////////////////////////////////////
//
void stt_mqtt_GetParasBuffer(CSttParas &oParas, CSttMqttTopicCmbn &oTopicCmbn)
{
	CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oTopicCmbn.m_nBufferLength = oParas.GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &oTopicCmbn.m_pszBuffer);
	CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void stt_mqtt_GetParasBuffer(CDataGroup *pDataGroup, CSttMqttTopicCmbn &oTopicCmbn)
{
	CSttParas oParas;
	oParas.Append(pDataGroup);

	stt_mqtt_GetParasBuffer(oParas, oTopicCmbn);

	oParas.RemoveAll();
}

void stt_mqtt_GetParasBuffer(CSttTestCmd &oCmd, CSttMqttTopicCmbn &oTopicCmbn, const long &nXmlRWType)
{
	CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oTopicCmbn.m_nBufferLength = oCmd.GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &oTopicCmbn.m_pszBuffer, 0, nXmlRWType);
	CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void stt_mqtt_InitTopicCmbn(CSttMqttTopicCmbn &oTopicCmbn, CSttXDevice *pDestDevice)
{
	oTopicCmbn.AddSubTopic(g_oTheOwnIotDevice.GetSN());

	if (pDestDevice != NULL)
	{
		oTopicCmbn.AddSubTopic(pDestDevice->GetSN());
	}
}

void stt_mqtt_InitTopicCmbn(CSttMqttTopicCmbn &oTopicCmbn, const char *pszSttCmdID, const char *pszSttCmdID2, CSttXDevice *pDestDevice)
{
	oTopicCmbn.ResetSubTopics();
	stt_mqtt_InitTopicCmbn(oTopicCmbn, pDestDevice);
	oTopicCmbn.AddSubTopic(pszSttCmdID);

	if (pszSttCmdID2 != NULL)
	{
		oTopicCmbn.AddSubTopic(pszSttCmdID2);
	}
}
