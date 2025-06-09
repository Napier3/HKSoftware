#include "stdafx.h"
#include "AudioConfigMngr.h"
#include "AudioDef.h"

CAudioConfigMngr::CAudioConfigMngr()
{
	m_pAudioConfig = NULL;
	m_pInspectData = NULL;
	m_pDeviceData = NULL;
	m_pProtocolData = NULL;
}

CAudioConfigMngr::~CAudioConfigMngr()
{
	if(m_pAudioConfig)
	{
		delete m_pAudioConfig;
		m_pAudioConfig = NULL;
	}
}

BOOL CAudioConfigMngr::InitConfig()
{
	//初始化软件配置
	CString strPath = _P_GetConfigPath();
	strPath += "Audio/";

	CString strAppConfigPath = strPath + "VoiceConfig.xml";
	m_oAppConfig.OpenXmlFile(strAppConfigPath, CDataMngrXmlRWKeys::g_pXmlKeys);

	//初始化语音配置
// 	CDvmData* pPath = (CDvmData*)m_oAppConfig.FindByID(CFG_VOICEWORDPATH);
// 	if(!pPath)
// 	{
// 		return FALSE;
// 	}

	CString strWordConfigPath = strPath + "VoiceWord.xml";
	m_pAudioConfig = new CAudioTestWords;
	if(!m_pAudioConfig->OpenXmlFile(/*pPath->m_strValue*/strWordConfigPath, CVoiceWordXmlRWKeys::g_pXmlKeys))
	{
		return FALSE;
	}

	CExBaseList* pData = (CExBaseList*)m_pAudioConfig->FindByClassID(VWCLASSID_CAUDIOTIPWORDS);
	m_oMatchWords.m_lstTipKeyWord = pData;
	pData = (CExBaseList*)m_pAudioConfig->FindByClassID(VWCLASSID_CAUDIOKEYWORDS);
	m_oMatchWords.m_lstKeyWord = pData;
	pData = (CExBaseList*)m_pAudioConfig->FindByClassID(VWCLASSID_CAUDIOORDERWORDS);
	m_oMatchWords.m_lstOrderKeyWord = pData;
	pData = (CExBaseList*)m_pAudioConfig->FindByClassID(VWCLASSID_CAUDIOFLOWWORDS);
	m_oMatchWords.m_lstFlowKeyWord = pData;

	//初始化界面参数
	CString strDlgConfigPath = strPath + "DlgConfig.xml";
	if(!m_DlgConfig.OpenXmlFile(strDlgConfigPath, CDataMngrXmlRWKeys::g_pXmlKeys))
	{
		return FALSE;
	}

	m_pInspectData = (CDvmData*)m_DlgConfig.FindByID("TestTypeSet");
	m_pDeviceData = (CDvmData*)m_DlgConfig.FindByID("DeviceTypeSet");
	m_pProtocolData = (CDvmData*)m_DlgConfig.FindByID("ProtTypeSet");
	
	return TRUE;
}

void CAudioConfigMngr::SaveConfig()
{
	CString strPath = _P_GetConfigPath();
	strPath += "Audio/";
	strPath += "VoiceConfig.xml";
	m_oAppConfig.SaveXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void CAudioConfigMngr::SetConfigValue(CString strID, CString strValue)
{
	CDvmData* pData = (CDvmData*)m_oAppConfig.FindByID(strID);
	if(pData)
	{
		pData->m_strValue = strValue;
	}
}

CString CAudioConfigMngr::GetConfigValue(CString strID)
{
	CDvmData* pData = (CDvmData*)m_oAppConfig.FindByID(strID);
	if(pData)
	{
		return pData->m_strValue;
	}
	return "";
}
