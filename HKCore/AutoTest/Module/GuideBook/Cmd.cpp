#include "stdafx.h"
#include "Cmd.h"
#include "Device.h"
#include "CommCmd.h"
#include "MacroTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "../XLanguageResourceAts.h"

const CString CCmd::g_strBeginModeSynchro = _T("synchro");
const CString CCmd::g_strBeginModeAsynchronous = _T("asynchronous");

CCmd::CCmd()
{
	//m_nDelayBeforeCmd = 0;
	//m_nDelayAfterCmd = 0;
	//m_nDelayBeforeRetry = 0;
	m_nMaxRetrytimes = 0;
	m_nRepeatTimes = 0;
	m_nReportFillUseNoRepeat = 0;
	m_nUseCurrSetData = 1;
	//m_nTimeLong = 0;
	//m_nTimeGap = 0;

	m_strDelayBeforeCmd = _T("0"); //Modify 2010-12-27
	m_strDelayAfterCmd = _T("0");
	//LONG m_nDelayBeforeRetry;
	m_strDelayBeforeRetry = _T("0");

	if (g_bInitCommCmdToAllDevice)
	{
		m_nUseDeviceEx = DSID_ALL_DVM;
	}
	else
	{
		m_nUseDeviceEx = 0;
	}

	m_nUseConnect = -1;
	m_strBeginMode = g_strBeginModeSynchro;
	m_nZoneIndex = 0;
}

CCmd::~CCmd()
{
	
}

long CCmd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,CGbXMLKeys::g_pGbXMLKeys);

	//xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strIDKey,oNode,m_strCpuID);

	try
	{
		xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strCpuIDKey,oNode,m_strDatasetPath);
	}
	catch (...)
	{
	}

	if (m_strDatasetPath.GetLength() == 0)
	{
		xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDataSetPathKey,oNode,m_strDatasetPath);
	}
	
	//xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDelayBeforeCmdKey,oNode,m_nDelayBeforeCmd);
	//xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDelayAfterCmdKey,oNode,m_nDelayAfterCmd);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDelayBeforeCmdKey,oNode,m_strDelayBeforeCmd);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDelayAfterCmdKey,oNode,m_strDelayAfterCmd);
	//xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDelayBeforeTryKey,oNode,m_nDelayBeforeRetry);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDelayBeforeTryKey,oNode,m_strDelayBeforeRetry);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strMaxRetryTimesKey,oNode,m_nMaxRetrytimes);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strRetryTimesKey,oNode,m_nRepeatTimes);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strReportFillUseNoRepeatKey,oNode,m_nReportFillUseNoRepeat);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strCalModeKey,oNode,m_strCalMode);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strTimeLongKey,oNode,m_strTimeLong);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strTimeGapKey,oNode,m_strTimeGap);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strUseCurrSetDataKey,oNode,m_nUseCurrSetData);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strUseDeviceExKey,oNode,m_nUseDeviceEx);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strBeginModeKey,oNode,m_strBeginMode);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strUseConnectKey,oNode,m_nUseConnect);
	
	//2020-07-03  lijunqing  兼容错误的文档：之前版本使用m_nUseConnect标识了ZoneIndex
	//所以，如果没有定义ZoneIndex，
	if (!xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strZoneIndexKey,oNode,m_nZoneIndex))
	{
		m_nZoneIndex = m_nUseConnect;
	}

	if (m_nZoneIndex < 0)
	{
		m_nZoneIndex = 0;
	}

	if (m_strBeginMode.GetLength() == 0)
	{
		m_strBeginMode = g_strBeginModeSynchro;
	}

	return 0;
}

long CCmd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,CGbXMLKeys::g_pGbXMLKeys);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strDataSetPathKey,oElement,m_strDatasetPath);
	//xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strDelayBeforeCmdKey,oElement,m_nDelayBeforeCmd);
	//xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strDelayAfterCmdKey,oElement,m_nDelayAfterCmd);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strDelayBeforeCmdKey,oElement,m_strDelayBeforeCmd);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strDelayAfterCmdKey,oElement,m_strDelayAfterCmd);
	//xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strDelayBeforeTryKey,oElement,m_nDelayBeforeRetry);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strDelayBeforeTryKey,oElement,m_strDelayBeforeRetry);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strMaxRetryTimesKey,oElement,m_nMaxRetrytimes);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strRetryTimesKey,oElement,m_nRepeatTimes);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strReportFillUseNoRepeatKey,oElement,m_nReportFillUseNoRepeat);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strCalModeKey,oElement,m_strCalMode);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strTimeLongKey,oElement,m_strTimeLong);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strTimeGapKey,oElement,m_strTimeGap);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strUseCurrSetDataKey,oElement,m_nUseCurrSetData);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strUseDeviceExKey,oElement,m_nUseDeviceEx);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strBeginModeKey,oElement,m_strBeginMode);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strUseConnectKey,oElement,m_nUseConnect);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strZoneIndexKey,oElement,m_nZoneIndex);

// 	ASSERT(m_pValues != NULL);
// 	m_pValues->XmlWrite(oXMLDoc, oElement, CGbXMLKeys::g_pGbXMLKeys->m_pReportValueKeys);

	return 0;
}

long CCmd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDatasetPath);
		BinarySerializeCalLen(oBinaryBuffer, m_strDelayBeforeCmd);
		BinarySerializeCalLen(oBinaryBuffer, m_strDelayAfterCmd);
		BinarySerializeCalLen(oBinaryBuffer, m_strDelayBeforeRetry);
		BinarySerializeCalLen(oBinaryBuffer, m_nMaxRetrytimes);
		BinarySerializeCalLen(oBinaryBuffer, m_nRepeatTimes);
		BinarySerializeCalLen(oBinaryBuffer, m_strCalMode);
		BinarySerializeCalLen(oBinaryBuffer, m_strTimeLong);
		BinarySerializeCalLen(oBinaryBuffer, m_strTimeGap);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseCurrSetData);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseDeviceEx);
		BinarySerializeCalLen(oBinaryBuffer, m_strBeginMode);	
		BinarySerializeCalLen(oBinaryBuffer, m_nUseConnect);	
		BinarySerializeCalLen(oBinaryBuffer, m_nZoneIndex);	
		BinarySerializeCalLen(oBinaryBuffer, m_nReportFillUseNoRepeat);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDatasetPath);
		//BinarySerializeRead(oBinaryBuffer, m_nDelayBeforeCmd);
		//BinarySerializeRead(oBinaryBuffer, m_nDelayAfterCmd);
		BinarySerializeRead(oBinaryBuffer, m_strDelayBeforeCmd);
		BinarySerializeRead(oBinaryBuffer, m_strDelayAfterCmd);
		BinarySerializeRead(oBinaryBuffer, m_strDelayBeforeRetry);
		BinarySerializeRead(oBinaryBuffer, m_nMaxRetrytimes);
		BinarySerializeRead(oBinaryBuffer, m_nRepeatTimes);
		BinarySerializeRead(oBinaryBuffer, m_strCalMode);
		BinarySerializeRead(oBinaryBuffer, m_strTimeLong);
		BinarySerializeRead(oBinaryBuffer, m_strTimeGap);
	
		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_0)
		{
			BinarySerializeRead(oBinaryBuffer, m_nUseCurrSetData);
		}
	
		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_3)
		{
			BinarySerializeRead(oBinaryBuffer, m_nUseDeviceEx);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_6)
		{
			BinarySerializeRead(oBinaryBuffer, m_strBeginMode);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_15)
		{
			BinarySerializeRead(oBinaryBuffer, m_nUseConnect);
		}

		if (m_strBeginMode.GetLength() == 0)
		{
			m_strBeginMode = g_strBeginModeSynchro;
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_18)
		{
			BinarySerializeRead(oBinaryBuffer, m_nZoneIndex);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_30)
		{
			BinarySerializeRead(oBinaryBuffer, m_nReportFillUseNoRepeat);
		}
	}
	else
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDatasetPath);
		//BinarySerializeWrite(oBinaryBuffer, m_nDelayBeforeCmd);
		//BinarySerializeWrite(oBinaryBuffer, m_nDelayAfterCmd);
		BinarySerializeWrite(oBinaryBuffer, m_strDelayBeforeCmd);
		BinarySerializeWrite(oBinaryBuffer, m_strDelayAfterCmd);
		BinarySerializeWrite(oBinaryBuffer, m_strDelayBeforeRetry);
		BinarySerializeWrite(oBinaryBuffer, m_nMaxRetrytimes);
		BinarySerializeWrite(oBinaryBuffer, m_nRepeatTimes);
		BinarySerializeWrite(oBinaryBuffer, m_strCalMode);
		BinarySerializeWrite(oBinaryBuffer, m_strTimeLong);
		BinarySerializeWrite(oBinaryBuffer, m_strTimeGap);
		BinarySerializeWrite(oBinaryBuffer, m_nUseCurrSetData);
		BinarySerializeWrite(oBinaryBuffer, m_nUseDeviceEx);
		BinarySerializeWrite(oBinaryBuffer, m_strBeginMode);
		BinarySerializeWrite(oBinaryBuffer, m_nUseConnect);
		BinarySerializeWrite(oBinaryBuffer, m_nZoneIndex);
		BinarySerializeWrite(oBinaryBuffer, m_nReportFillUseNoRepeat);
	}
//	m_pValues->Serialize(oBinaryBuffer);

	return 0;
}

BOOL CCmd::IsEqual(CBaseObject* pObj)
{
	return CBaseObject::IsEqual(pObj);
}

BOOL CCmd::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
	{
		return TRUE;
	}
	
	CCmd* pCmd = (CCmd*)pDesObj;

	pCmd->m_nMaxRetrytimes =  m_nMaxRetrytimes;
	pCmd->m_nRepeatTimes =  m_nRepeatTimes;
	pCmd->m_nReportFillUseNoRepeat =  m_nReportFillUseNoRepeat;
	pCmd->m_nUseCurrSetData =  m_nUseCurrSetData;
	pCmd->m_nUseDeviceEx =  m_nUseDeviceEx;
	pCmd->m_strCalMode = m_strCalMode;
	pCmd->m_strDelayBeforeCmd =  m_strDelayBeforeCmd;
	pCmd->m_strDelayAfterCmd =  m_strDelayAfterCmd;
	pCmd->m_strDelayBeforeRetry = m_strDelayBeforeRetry;
	pCmd->m_strTimeLong =  m_strTimeLong;
	pCmd->m_strTimeGap =  m_strTimeGap;
	pCmd->m_strDatasetPath = m_strDatasetPath;
	pCmd->m_strBeginMode = m_strBeginMode;

	pCmd->m_nZoneIndex = m_nZoneIndex;
	pCmd->m_nUseConnect = m_nUseConnect;

	return TRUE;
}


BOOL CCmd::UpdateOwn(CBaseObject* pDest)
{
	CopyOwn(pDest);

	CCmd *pCmd = (CCmd*)pDest;
	pCmd->DeleteAll();
	pCmd->AppendClone(this);

	return TRUE;
}


CBaseObject* CCmd::Clone()
{
	CCmd* pCmd = new CCmd();
	Copy(pCmd);

	return pCmd;
}

long CCmd::GetValueBySysPara(const CString& strFind)
{
	CDataObj  *pShorData = NULL;
	CDevice* pDevice = (CDevice*)this->GetAncestor(GBCLASSID_DEVICE);
	long nDelayBeforeCmd = 0;

	if(pDevice != NULL)
	{
		if(pDevice->m_pSysParas != NULL)
		{
// 			CDataObj* pPara = (CDataObj*)pDevice->m_pSysParas->FindByID(strFind);
// 			if(pPara != NULL)
// 			{
// 				nDelayBeforeCmd = _wtol(pPara->m_strValue);
// 			}
// 			else
// 			{
// 				nDelayBeforeCmd = _wtol(strFind);
// 			}
			nDelayBeforeCmd = pDevice->m_pSysParas->GetValueLong(strFind);
		}
	}

	return nDelayBeforeCmd;
}

LONG CCmd::GetCalMode()
{
	CCommCmd *pCommCmd = (CCommCmd*)GetParent();
	CString strReportMode;
	CExBaseObject *pParent = (CExBaseObject*)pCommCmd->GetParent();

	if (pParent->GetClassID() == GBCLASSID_MACROTEST)
	{
		strReportMode = ((CMacroTest*)pParent)->m_strReportMode;
	}
	else
	{
		strReportMode = m_strCalMode;
	}

	return Gb_GetReportCalMode(strReportMode);
}

void CCmd::UpdateCmdData(CCmd *pCmd, UINT nDataID, BOOL bShowLog)
{
	
	if (bShowLog)
	{
		CString strText;

		switch (nDataID)
		{
		case CMD_PARA_ID_BEFORE:
            strText.Format(g_sLangTxt_PreDelay/*_T("[%s]通讯前延时 (%s)==>>(%s)")*/,m_strName.GetString(), m_strDelayBeforeCmd.GetString(), pCmd->m_strDelayBeforeCmd.GetString());
			break;
		case CMD_PARA_ID_AFTER:
            strText.Format(g_sLangTxt_PostDelay/*_T("[%s]通讯后延时 (%s)==>>(%s)")*/,m_strName.GetString(), m_strDelayAfterCmd.GetString(), pCmd->m_strDelayAfterCmd.GetString());
			break;
		case CMD_PARA_ID_RETRYMAX:
			break;
		case CMD_PARA_ID_RETRY_BEFORE:
            strText.Format(g_sLangTxt_RetryDelay/*_T("[%s]重试前延时 (%s)==>>(%s)")*/,m_strName.GetString(), m_strDelayBeforeRetry.GetString(), pCmd->m_strDelayBeforeRetry.GetString());
			break;
		case CMD_PARA_ID_RETRY_TIMES:
			break;
		case CMD_PARA_ID_RETRY_GAP:
			break;
		case CMD_PARA_ID_CMMTIMES:
			break;
		case CMD_PARA_ID_CMM_CALMODE:
			break;
		}

		CLogPrint::LogString(XLOGLEVEL_TRACE, strText);
	}

	switch (nDataID)
	{
	case CMD_PARA_ID_BEFORE:
		m_strDelayBeforeCmd = pCmd->m_strDelayBeforeCmd;
		break;
	case CMD_PARA_ID_AFTER:
		m_strDelayAfterCmd = pCmd->m_strDelayAfterCmd;
		break;
	case CMD_PARA_ID_RETRYMAX:
		break;
	case CMD_PARA_ID_RETRY_BEFORE:
		m_strDelayBeforeRetry = pCmd->m_strDelayBeforeRetry;
		break;
	case CMD_PARA_ID_RETRY_TIMES:
		break;
	case CMD_PARA_ID_RETRY_GAP:
		break;
	case CMD_PARA_ID_CMMTIMES:
		break;
	case CMD_PARA_ID_CMM_CALMODE:
		break;
	}
}


long CCmd::GetDelayBeforeCmd()
{
	return this->GetValueBySysPara(m_strDelayBeforeCmd);
}

long CCmd::GetDelayAfterCmd()
{
	long nDelayAfter = GetValueBySysPara(m_strDelayAfterCmd);
	return nDelayAfter;
}

long CCmd::GetDelayBeforeRetry()
{
	return this->GetValueBySysPara(m_strDelayBeforeRetry);
}

long CCmd::GetTimeLong()
{
	return this->GetValueBySysPara(m_strTimeLong);
}

long CCmd::GetTimeGap()
{
	return this->GetValueBySysPara(m_strTimeGap);
}

BOOL CCmd::GetCmdScript(CString &strScript)
{
	
	return TRUE;
}

BOOL CCmd::IsCmdDataset(UINT nDatasetID)
{
	long nPos = m_strDatasetPath.ReverseFind('$');
	CString strTemp;

	if (nPos > 0)
	{
		strTemp = m_strDatasetPath.Mid(nPos+1);
	}
	else
	{
		strTemp = m_strDatasetPath;
	}

	if (nDatasetID >= DSID_dsMaxCount)
	{
		return FALSE;
	}
	else
	{
		return (strTemp.Find(g_strDataSetIDKey[nDatasetID]) >= 0);
	}
}

BOOL CCmd::IsCmdNeedWriteToLocal()
{
	long nPos = m_strDatasetPath.ReverseFind('$');
	CString strTemp;

	if (nPos > 0)
	{
		strTemp = m_strDatasetPath.Mid(nPos+1);
	}
	else
	{
		strTemp = m_strDatasetPath;
	}

	if (strTemp.Find(g_strDataSetIDKey[DSID_dsSetting]) )
	{
		return TRUE;
	}

	if (strTemp.Find(g_strDataSetIDKey[DSID_dsEna]) )
	{
		return TRUE;
	}

	if (strTemp.Find(g_strDataSetIDKey[DSID_dsParameter]) )
	{
		return TRUE;
	}

	if (strTemp.Find(g_strDataSetIDKey[DSID_dsAin]) )
	{
		return TRUE;
	}

	return FALSE;
}

CValue* CCmd::FindValue(CDataObj *pDataObj)
{
	CValue *pValue = (CValue*)FindByID(pDataObj->m_strID);

	if (pValue == NULL)
	{
		CString strPath = pDataObj->GetIDPathEx(GBCLASSID_CPU, TRUE);
		pValue = (CValue*)FindByID(strPath);
	}

	return pValue;
}

BOOL CCmd::IsEmptyDataset()
{
	return (m_strDatasetPath.GetLength() == 0 || m_strDatasetPath == _T("none"));
}

BOOL CCmd::IsBeginModeSynchro()
{
	return (m_strBeginMode == g_strBeginModeSynchro);
}

BOOL CCmd::IsBeginModeAsynchronous()
{
	return (m_strBeginMode == g_strBeginModeAsynchronous);
}

void CCmd::SetBeginModeSynchro()
{
	m_strBeginMode = g_strBeginModeSynchro;
}

void CCmd::SetBeginModeAsynchronous()
{
	m_strBeginMode = g_strBeginModeAsynchronous;
}


long CCmd::CalTestTimeLong()
{
	long nTimeLong = 0;

	nTimeLong = GetDelayBeforeCmd() + GetDelayAfterCmd();

	if (m_nRepeatTimes <= 1)
	{
		nTimeLong *= m_nRepeatTimes;
	}
	
	return nTimeLong;
}

void CCmd::ClearCommCmdParas()
{
	DeleteAll();
}

void CCmd::AddCommCmdParaValue(const CString &strValID, const CString &strValue)
{
	CValue *pValue = (CValue*)FindByID(strValID);

	if (pValue == NULL)
	{
		pValue = AddValue(strValID, strValue);
	}
	else
	{
		pValue->m_strValue = strValue;
	}
}
