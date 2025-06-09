//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttCommCmd.cpp  CSttCommCmd


#include "stdafx.h"
#include "SttCommCmd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const CString CSttCommCmdData::g_strStt_BeginModeSynchro = _T("synchro");
const CString CSttCommCmdData::g_strStt_BeginModeAsynchronous = _T("asynchronous");

//////////////////////////////////////////////////////////////////////////
//CSttCommCmdData
CSttCommCmdData::CSttCommCmdData()
{
	m_nMaxRetrytimes = 0;
	m_nRepeatTimes = 0;
	m_nReportFillUseNoRepeat = 0;
	m_nUseCurrSetData = 1;
	m_strDelayBeforeCmd = _T("0"); 
	m_strDelayAfterCmd = _T("0");
	m_strDelayBeforeRetry = _T("0");

	if (g_bStt_InitCommCmdToAllDevice)
	{
		m_nUseDeviceEx = DSID_ALL_DVM;
	}
	else
	{
		m_nUseDeviceEx = 0;
	}
	
	m_nUseConnect = -1;
	m_strBeginMode = g_strStt_BeginModeSynchro;
	m_nZoneIndex = 0;
}

CSttCommCmdData::~CSttCommCmdData()
{

}

BSTR CSttCommCmdData::GetXmlElementKey()
{
	return CSttCmdDefineXmlRWKeys::CSttCommCmdDataKey(); 
}

long CSttCommCmdData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strDataSetPathKey,oNode,m_strDatasetPath);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strDelayBeforeCmdKey,oNode,m_strDelayBeforeCmd);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strDelayAfterCmdKey,oNode,m_strDelayAfterCmd);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strDelayBeforeTryKey,oNode,m_strDelayBeforeRetry);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strMaxRetryTimesKey,oNode,m_nMaxRetrytimes);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strRetryTimesKey,oNode,m_nRepeatTimes);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strReportFillUseNoRepeatKey,oNode,m_nReportFillUseNoRepeat);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strCalModeKey,oNode,m_strCalMode);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strTimeLongKey,oNode,m_strTimeLong);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strTimeGapKey,oNode,m_strTimeGap);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strUseCurrSetDataKey,oNode,m_nUseCurrSetData);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strUseDeviceExKey,oNode,m_nUseDeviceEx);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strBeginModeKey,oNode,m_strBeginMode);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strUseConnectKey,oNode,m_nUseConnect);

	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strZoneIndexKey,oNode,m_nZoneIndex);

	return 0;
}

long CSttCommCmdData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strDataSetPathKey,oElement,m_strDatasetPath);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strDelayBeforeCmdKey,oElement,m_strDelayBeforeCmd);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strDelayAfterCmdKey,oElement,m_strDelayAfterCmd);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strDelayBeforeTryKey,oElement,m_strDelayBeforeRetry);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strMaxRetryTimesKey,oElement,m_nMaxRetrytimes);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strRetryTimesKey,oElement,m_nRepeatTimes);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strReportFillUseNoRepeatKey,oElement,m_nReportFillUseNoRepeat);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strCalModeKey,oElement,m_strCalMode);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strTimeLongKey,oElement,m_strTimeLong);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strTimeGapKey,oElement,m_strTimeGap);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strUseCurrSetDataKey,oElement,m_nUseCurrSetData);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strUseDeviceExKey,oElement,m_nUseDeviceEx);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strBeginModeKey,oElement,m_strBeginMode);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strUseConnectKey,oElement,m_nUseConnect);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strZoneIndexKey,oElement,m_nZoneIndex);


	if (m_strBeginMode.GetLength() == 0)
	{
		m_strBeginMode = g_strStt_BeginModeSynchro;
	}
	return 0;
}

long CSttCommCmdData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
// 	CExBaseObject::SerializeOwn(oBinaryBuffer);
// 
// 	if (oBinaryBuffer.IsCalSizeMode())
// 	{
// 		BinarySerializeCalLen(oBinaryBuffer, m_strDatasetPath);
// 		BinarySerializeCalLen(oBinaryBuffer, m_strDelayBeforeCmd);
// 		BinarySerializeCalLen(oBinaryBuffer, m_strDelayAfterCmd);
// 		BinarySerializeCalLen(oBinaryBuffer, m_strDelayBeforeRetry);
// 		BinarySerializeCalLen(oBinaryBuffer, m_nMaxRetrytimes);
// 		BinarySerializeCalLen(oBinaryBuffer, m_nRepeatTimes);
// 		BinarySerializeCalLen(oBinaryBuffer, m_strCalMode);
// 		BinarySerializeCalLen(oBinaryBuffer, m_strTimeLong);
// 		BinarySerializeCalLen(oBinaryBuffer, m_strTimeGap);
// 		BinarySerializeCalLen(oBinaryBuffer, m_nUseCurrSetData);
// 		BinarySerializeCalLen(oBinaryBuffer, m_nUseDeviceEx);
// 		BinarySerializeCalLen(oBinaryBuffer, m_strBeginMode);	
// 		BinarySerializeCalLen(oBinaryBuffer, m_nUseConnect);	
// 		BinarySerializeCalLen(oBinaryBuffer, m_nZoneIndex);	
// 		BinarySerializeCalLen(oBinaryBuffer, m_nReportFillUseNoRepeat);
// 	}
// 	else if (oBinaryBuffer.IsReadMode())
// 	{
// 		BinarySerializeRead(oBinaryBuffer, m_strDatasetPath);
// 		//BinarySerializeRead(oBinaryBuffer, m_nDelayBeforeCmd);
// 		//BinarySerializeRead(oBinaryBuffer, m_nDelayAfterCmd);
// 		BinarySerializeRead(oBinaryBuffer, m_strDelayBeforeCmd);
// 		BinarySerializeRead(oBinaryBuffer, m_strDelayAfterCmd);
// 		BinarySerializeRead(oBinaryBuffer, m_strDelayBeforeRetry);
// 		BinarySerializeRead(oBinaryBuffer, m_nMaxRetrytimes);
// 		BinarySerializeRead(oBinaryBuffer, m_nRepeatTimes);
// 		BinarySerializeRead(oBinaryBuffer, m_strCalMode);
// 		BinarySerializeRead(oBinaryBuffer, m_strTimeLong);
// 		BinarySerializeRead(oBinaryBuffer, m_strTimeGap);
// 
// 		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_0)
// 		{
// 			BinarySerializeRead(oBinaryBuffer, m_nUseCurrSetData);
// 		}
// 
// 		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_3)
// 		{
// 			BinarySerializeRead(oBinaryBuffer, m_nUseDeviceEx);
// 		}
// 
// 		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_6)
// 		{
// 			BinarySerializeRead(oBinaryBuffer, m_strBeginMode);
// 		}
// 
// 		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_15)
// 		{
// 			BinarySerializeRead(oBinaryBuffer, m_nUseConnect);
// 		}
// 
// 		if (m_strBeginMode.GetLength() == 0)
// 		{
// 			m_strBeginMode = g_strStt_BeginModeSynchro;
// 		}
// 
// 		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_18)
// 		{
// 			BinarySerializeRead(oBinaryBuffer, m_nZoneIndex);
// 		}
// 
// 		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_30)
// 		{
// 			BinarySerializeRead(oBinaryBuffer, m_nReportFillUseNoRepeat);
// 		}
// 	}
// 	else
// 	{
// 		BinarySerializeWrite(oBinaryBuffer, m_strDatasetPath);
// 		//BinarySerializeWrite(oBinaryBuffer, m_nDelayBeforeCmd);
// 		//BinarySerializeWrite(oBinaryBuffer, m_nDelayAfterCmd);
// 		BinarySerializeWrite(oBinaryBuffer, m_strDelayBeforeCmd);
// 		BinarySerializeWrite(oBinaryBuffer, m_strDelayAfterCmd);
// 		BinarySerializeWrite(oBinaryBuffer, m_strDelayBeforeRetry);
// 		BinarySerializeWrite(oBinaryBuffer, m_nMaxRetrytimes);
// 		BinarySerializeWrite(oBinaryBuffer, m_nRepeatTimes);
// 		BinarySerializeWrite(oBinaryBuffer, m_strCalMode);
// 		BinarySerializeWrite(oBinaryBuffer, m_strTimeLong);
// 		BinarySerializeWrite(oBinaryBuffer, m_strTimeGap);
// 		BinarySerializeWrite(oBinaryBuffer, m_nUseCurrSetData);
// 		BinarySerializeWrite(oBinaryBuffer, m_nUseDeviceEx);
// 		BinarySerializeWrite(oBinaryBuffer, m_strBeginMode);
// 		BinarySerializeWrite(oBinaryBuffer, m_nUseConnect);
// 		BinarySerializeWrite(oBinaryBuffer, m_nZoneIndex);
// 		BinarySerializeWrite(oBinaryBuffer, m_nReportFillUseNoRepeat);
// 	}
// 	//	m_pValues->Serialize(oBinaryBuffer);

	return 0;
}

void CSttCommCmdData::InitAfterRead()
{

}

BOOL CSttCommCmdData::IsEqualOwn(CBaseObject* pObj)
{
	if (!CValues::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttCommCmdData *p = (CSttCommCmdData *)pObj;

	if(m_strDatasetPath != p->m_strDatasetPath)
	{
		return FALSE;
	}

	if(m_strDelayBeforeCmd != p->m_strDelayBeforeCmd)
	{
		return FALSE;
	}

	if(m_strDelayAfterCmd != p->m_strDelayAfterCmd)
	{
		return FALSE;
	}

	if(m_strDelayBeforeRetry != p->m_strDelayBeforeRetry)
	{
		return FALSE;
	}

	if(m_nMaxRetrytimes != p->m_nMaxRetrytimes)
	{
		return FALSE;
	}

	if(m_strTimeLong != p->m_strTimeLong)
	{
		return FALSE;
	}

	if(m_strTimeGap != p->m_strTimeGap)
	{
		return FALSE;
	}

	if(m_strCalMode != p->m_strCalMode)
	{
		return FALSE;
	}

	if(m_nRepeatTimes != p->m_nRepeatTimes)
	{
		return FALSE;
	}

	if(m_nReportFillUseNoRepeat != p->m_nReportFillUseNoRepeat)
	{
		return FALSE;
	}

	if(m_nUseCurrSetData != p->m_nUseCurrSetData)
	{
		return FALSE;
	}

	if(m_nUseDeviceEx != p->m_nUseDeviceEx)
	{
		return FALSE;
	}

	if(m_strBeginMode != p->m_strBeginMode)
	{
		return FALSE;
	}

	if(m_nUseConnect != p->m_nUseConnect)
	{
		return FALSE;
	}

	if(m_nZoneIndex != p->m_nZoneIndex)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttCommCmdData::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
	{
		return TRUE;
	}

	CSttCommCmdData* pCmd = (CSttCommCmdData*)pDesObj;

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

CBaseObject* CSttCommCmdData::Clone()
{
	CSttCommCmdData* pCmd = new CSttCommCmdData();
	Copy(pCmd);

	return pCmd;
}


//////////////////////////////////////////////////////////////////////////
//CSttCommCmd
CSttCommCmd::CSttCommCmd()
{
	//初始化属性
	m_nSortSoeByT = 0;
	m_nDsvRunAfterResultScript = 0;
	m_nCmdExecModeForMgrpt = 0;
	m_nFillRptDataset = 0;

	//初始化成员变量
}

CSttCommCmd::~CSttCommCmd()
{
}

BSTR CSttCommCmd::GetXmlElementKey()
{
	if (CSttCmdDefineXmlRWKeys::stt_Is_GuideBookUseItemKey(NULL))
	{
		return CSttCmdDefineXmlRWKeys::CSttItemBaseKey();
	}
	else
	{
		return CSttCmdDefineXmlRWKeys::CSttCommCmdKey(); 
	}
}

long CSttCommCmd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey,oNode,m_strCommCmdID);
	xml_GetAttibuteValue(pXmlKeys->m_strCmdRwKey, oNode, m_strRwOptr);
	xml_GetAttibuteValue(pXmlKeys->m_strSortSoeByTKey, oNode, m_nSortSoeByT);
	xml_GetAttibuteValue(pXmlKeys->m_strDsvRunAfterResultScriptKey, oNode, m_nDsvRunAfterResultScript);
	xml_GetAttibuteValue(pXmlKeys->m_strCmdExecModeForMgrptKey, oNode, m_nCmdExecModeForMgrpt);
	xml_GetAttibuteValue(pXmlKeys->m_strFillRptDatasetKey, oNode, m_nFillRptDataset);
	return 0;
}

long CSttCommCmd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);


	if (CSttCmdDefineXmlRWKeys::IsOnlyGetItem())
	{
		return 0;
	}

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strCommCmdID);
	xml_SetAttributeValue(pXmlKeys->m_strCmdRwKey, oElement, m_strRwOptr);
	xml_SetAttributeValue(pXmlKeys->m_strSortSoeByTKey, oElement, m_nSortSoeByT);
	xml_SetAttributeValue(pXmlKeys->m_strDsvRunAfterResultScriptKey, oElement, m_nDsvRunAfterResultScript);
	xml_SetAttributeValue(pXmlKeys->m_strCmdExecModeForMgrptKey, oElement, m_nCmdExecModeForMgrpt);
	xml_SetAttributeValue(pXmlKeys->m_strFillRptDatasetKey, oElement, m_nFillRptDataset);
	return 0;
}

long CSttCommCmd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttItemBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strCommCmdID);
		BinarySerializeCalLen(oBinaryBuffer, m_strRwOptr);
		BinarySerializeCalLen(oBinaryBuffer, m_nSortSoeByT);
		BinarySerializeCalLen(oBinaryBuffer, m_nDsvRunAfterResultScript);
		BinarySerializeCalLen(oBinaryBuffer, m_nCmdExecModeForMgrpt);
		BinarySerializeCalLen(oBinaryBuffer, m_nFillRptDataset);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strCommCmdID);
		BinarySerializeRead(oBinaryBuffer, m_strRwOptr);
		BinarySerializeRead(oBinaryBuffer, m_nSortSoeByT);
		BinarySerializeRead(oBinaryBuffer, m_nDsvRunAfterResultScript);
		BinarySerializeRead(oBinaryBuffer, m_nCmdExecModeForMgrpt);
		BinarySerializeRead(oBinaryBuffer, m_nFillRptDataset);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strCommCmdID);
		BinarySerializeWrite(oBinaryBuffer, m_strRwOptr);
		BinarySerializeWrite(oBinaryBuffer, m_nSortSoeByT);
		BinarySerializeWrite(oBinaryBuffer, m_nDsvRunAfterResultScript);
		BinarySerializeWrite(oBinaryBuffer, m_nCmdExecModeForMgrpt);
		BinarySerializeWrite(oBinaryBuffer, m_nFillRptDataset);
	}
	return 0;
}

void CSttCommCmd::InitAfterRead()
{
	CSttItemBase::InitAfterRead();
}

BOOL CSttCommCmd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttItemBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttCommCmd *p = (CSttCommCmd*)pObj;

	if(m_strCommCmdID != p->m_strCommCmdID)
	{
		return FALSE;
	}

	if(m_strRwOptr != p->m_strRwOptr)
	{
		return FALSE;
	}

	if(m_nSortSoeByT != p->m_nSortSoeByT)
	{
		return FALSE;
	}

	if(m_nDsvRunAfterResultScript != p->m_nDsvRunAfterResultScript)
	{
		return FALSE;
	}

	if(m_nCmdExecModeForMgrpt != p->m_nCmdExecModeForMgrpt)
	{
		return FALSE;
	}

	if(m_nFillRptDataset != p->m_nFillRptDataset)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttCommCmd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttItemBase::CopyOwn(pDest);

	CSttCommCmd *p = (CSttCommCmd*)pDest;

	p->m_strCommCmdID = m_strCommCmdID;
	p->m_strRwOptr = m_strRwOptr;
	p->m_nSortSoeByT = m_nSortSoeByT;
	p->m_nDsvRunAfterResultScript = m_nDsvRunAfterResultScript;
	p->m_nCmdExecModeForMgrpt = m_nCmdExecModeForMgrpt;
	p->m_nFillRptDataset = m_nFillRptDataset;
	return TRUE;
}

CBaseObject* CSttCommCmd::Clone()
{
	CSttCommCmd *p = new CSttCommCmd();
	Copy(p);
	return p;
}

CBaseObject* CSttCommCmd::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttCommCmd *p = new CSttCommCmd();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttCommCmd::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CSttCommCmd::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CSttCmdDefineXmlRWKeys::CSttCommCmdDataKey())
	{
		return new CSttCommCmdData();
	}

	return CSttItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}

CExBaseObject* CSttCommCmd::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	if (nClassID == STTGBXMLCLASSID_CSTTCOMM_DATA)
	{
		return new CSttCommCmdData();
	}

	return CSttItemBase::CreateNewChild(nClassID);
}


long CSttCommCmd::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (CSttCmdDefineXmlRWKeys::IsOnlyGetItem())
		{
			//只获取项目目录的情况下，不需要特性曲线相关以及测试功能参数
			//2022-10-14  lijunqing
			if (nClassID == STTGBXMLCLASSID_CSTTCOMM_DATA
				|| nClassID == STTGBXMLCLASSID_CSTTREPORTMAP)
				//|| nClassID == STTCMDCLASSID_REPORTS)
			{
				continue;
			}
		}

		pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	return 0;
}

CSttCommCmdData* CSttCommCmd::GetCommCmdData(BOOL bCreate)
{
	CSttCommCmdData *pFind = (CSttCommCmdData*)FindByClassID(STTGBXMLCLASSID_CSTTCOMM_DATA);

	if (pFind == NULL)
	{
		if (bCreate)
		{
			pFind = new CSttCommCmdData();
			AddNewChild(pFind);
		}
	}

	return pFind;
}


void CSttCommCmd::UpdateEx(CSttCommCmd *pDest)
{
	CopyOwn(pDest);
	CSttCommCmdData *pDestData = pDest->GetCommCmdData(TRUE);
	CSttCommCmdData *pData = GetCommCmdData(FALSE);

	pData->CopyOwn(pDestData);
	pData->CopyChildren(pDestData);
}

long CSttCommCmd::GetItemTestCount()
{
	CSttItemBase *pParent = (CSttItemBase *)GetParent();

	return pParent->GetItemTestCount();
}