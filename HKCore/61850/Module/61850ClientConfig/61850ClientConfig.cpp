//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//61850ClientConfig.cpp  C61850ClientConfig


#include "stdafx.h"
#include "61850ClientConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

C61850ClientConfig g_o61850ClientConfig;

C61850ClientConfig::C61850ClientConfig()
{
	//初始化属性
	m_nDebugMode = 0;
	m_nUseDvmMapFile = 0;
	m_nEnaWriteWaitAfterSel = 0;
	m_nEnaWriteWait = 0;
	m_nReadAinUseReport = 0;
	m_nAddRptBuffer = 1;
	m_nCanWriteActiveSG = 1;
	m_nEnaReadBeforeWrite = 0;
	m_nWriteDataWaitMs = 200;
	m_nProtocolVersion = 0x201;
	m_nUseDsDout = 0;
	m_nAutoGenModelDatas = 0;
	m_nUseGspLog = 0;
	m_nSpecifiedDataset = 0;

	//初始化成员变量
	m_pRemoteDevs = NULL;
}

C61850ClientConfig::~C61850ClientConfig()
{
}

long C61850ClientConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	C61850ClientCfgMngrXmlRWKeys *pXmlKeys = (C61850ClientCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDebug_ModeKey, oNode, m_nDebugMode);
	xml_GetAttibuteValue(pXmlKeys->m_strUse_Map_FileKey, oNode, m_nUseDvmMapFile);
	xml_GetAttibuteValue(pXmlKeys->m_strEna_Write_Wait_After_SelKey, oNode, m_nEnaWriteWaitAfterSel);
	xml_GetAttibuteValue(pXmlKeys->m_strEna_Write_WaitKey, oNode, m_nEnaWriteWait);
	xml_GetAttibuteValue(pXmlKeys->m_strRead_Ain_Use_ReportKey, oNode, m_nReadAinUseReport);
	xml_GetAttibuteValue(pXmlKeys->m_strAdd_Rpt_BufferKey, oNode, m_nAddRptBuffer);
	xml_GetAttibuteValue(pXmlKeys->m_strCan_Write_Active_SgKey, oNode, m_nCanWriteActiveSG);
	xml_GetAttibuteValue(pXmlKeys->m_strProtocol_VersionKey, oNode, m_nProtocolVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strUse_DsdoutKey, oNode, m_nUseDsDout);
	xml_GetAttibuteValue(pXmlKeys->m_strEna_Read_Before_WriteKey, oNode, m_nEnaReadBeforeWrite);
	xml_GetAttibuteValue(pXmlKeys->m_strWrite_Data_Wait_MsKey, oNode, m_nWriteDataWaitMs);
	xml_GetAttibuteValue(pXmlKeys->m_strAuto_Gen_Model_DatasKey, oNode, m_nAutoGenModelDatas);
	xml_GetAttibuteValue(pXmlKeys->m_strUse_Gsp_LogKey, oNode, m_nUseGspLog);
	xml_GetAttibuteValue(pXmlKeys->m_strSpecifi_DatasetKey, oNode, m_nSpecifiedDataset);
	return 0;
}

long C61850ClientConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	C61850ClientCfgMngrXmlRWKeys *pXmlKeys = (C61850ClientCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDebug_ModeKey, oElement, m_nDebugMode);
	xml_SetAttributeValue(pXmlKeys->m_strUse_Map_FileKey, oElement, m_nUseDvmMapFile);
	xml_SetAttributeValue(pXmlKeys->m_strEna_Write_Wait_After_SelKey, oElement, m_nEnaWriteWaitAfterSel);
	xml_SetAttributeValue(pXmlKeys->m_strEna_Write_WaitKey, oElement, m_nEnaWriteWait);
	xml_SetAttributeValue(pXmlKeys->m_strRead_Ain_Use_ReportKey, oElement, m_nReadAinUseReport);
	xml_SetAttributeValue(pXmlKeys->m_strAdd_Rpt_BufferKey, oElement, m_nAddRptBuffer);
	xml_SetAttributeValue(pXmlKeys->m_strCan_Write_Active_SgKey, oElement, m_nCanWriteActiveSG);
	xml_SetAttributeValue(pXmlKeys->m_strProtocol_VersionKey, oElement, m_nProtocolVersion);
	xml_SetAttributeValue(pXmlKeys->m_strUse_DsdoutKey, oElement, m_nUseDsDout);
	xml_SetAttributeValue(pXmlKeys->m_strEna_Read_Before_WriteKey, oElement, m_nEnaReadBeforeWrite);
	xml_SetAttributeValue(pXmlKeys->m_strWrite_Data_Wait_MsKey, oElement, m_nWriteDataWaitMs);
	xml_SetAttributeValue(pXmlKeys->m_strAuto_Gen_Model_DatasKey, oElement, m_nAutoGenModelDatas);
	xml_SetAttributeValue(pXmlKeys->m_strUse_Gsp_LogKey, oElement, m_nUseGspLog);
	xml_SetAttributeValue(pXmlKeys->m_strSpecifi_DatasetKey, oElement, m_nSpecifiedDataset);
	return 0;
}

long C61850ClientConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nDebugMode);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseDvmMapFile);
		BinarySerializeCalLen(oBinaryBuffer, m_nEnaWriteWaitAfterSel);
		BinarySerializeCalLen(oBinaryBuffer, m_nEnaWriteWait);
		BinarySerializeCalLen(oBinaryBuffer, m_nReadAinUseReport);
		BinarySerializeCalLen(oBinaryBuffer, m_nAddRptBuffer);
		BinarySerializeCalLen(oBinaryBuffer, m_nCanWriteActiveSG);
		BinarySerializeCalLen(oBinaryBuffer, m_nProtocolVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseDsDout);
		BinarySerializeCalLen(oBinaryBuffer, m_nEnaReadBeforeWrite);
		BinarySerializeCalLen(oBinaryBuffer, m_nWriteDataWaitMs);
		BinarySerializeCalLen(oBinaryBuffer, m_nAutoGenModelDatas);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseGspLog);
		BinarySerializeCalLen(oBinaryBuffer, m_nSpecifiedDataset);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nDebugMode);
		BinarySerializeRead(oBinaryBuffer, m_nUseDvmMapFile);
		BinarySerializeRead(oBinaryBuffer, m_nEnaWriteWaitAfterSel);
		BinarySerializeRead(oBinaryBuffer, m_nEnaWriteWait);
		BinarySerializeRead(oBinaryBuffer, m_nReadAinUseReport);
		BinarySerializeRead(oBinaryBuffer, m_nAddRptBuffer);
		BinarySerializeRead(oBinaryBuffer, m_nCanWriteActiveSG);
		BinarySerializeRead(oBinaryBuffer, m_nProtocolVersion);
		BinarySerializeRead(oBinaryBuffer, m_nUseDsDout);
		BinarySerializeRead(oBinaryBuffer, m_nEnaReadBeforeWrite);
		BinarySerializeRead(oBinaryBuffer, m_nWriteDataWaitMs);
		BinarySerializeRead(oBinaryBuffer, m_nAutoGenModelDatas);
		BinarySerializeRead(oBinaryBuffer, m_nUseGspLog);
		BinarySerializeRead(oBinaryBuffer, m_nSpecifiedDataset);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nDebugMode);
		BinarySerializeWrite(oBinaryBuffer, m_nUseDvmMapFile);
		BinarySerializeWrite(oBinaryBuffer, m_nEnaWriteWaitAfterSel);
		BinarySerializeWrite(oBinaryBuffer, m_nEnaWriteWait);
		BinarySerializeWrite(oBinaryBuffer, m_nReadAinUseReport);
		BinarySerializeWrite(oBinaryBuffer, m_nAddRptBuffer);
		BinarySerializeWrite(oBinaryBuffer, m_nCanWriteActiveSG);
		BinarySerializeWrite(oBinaryBuffer, m_nProtocolVersion);
		BinarySerializeWrite(oBinaryBuffer, m_nUseDsDout);
		BinarySerializeWrite(oBinaryBuffer, m_nEnaReadBeforeWrite);
		BinarySerializeWrite(oBinaryBuffer, m_nWriteDataWaitMs);
		BinarySerializeWrite(oBinaryBuffer, m_nAutoGenModelDatas);
		BinarySerializeWrite(oBinaryBuffer, m_nUseGspLog);
		BinarySerializeWrite(oBinaryBuffer, m_nSpecifiedDataset);
	}
	return 0;
}

void C61850ClientConfig::InitAfterRead()
{
}

BOOL C61850ClientConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	C61850ClientConfig *p = (C61850ClientConfig*)pObj;

	if(m_nDebugMode != p->m_nDebugMode)
	{
		return FALSE;
	}

	if(m_nUseDvmMapFile != p->m_nUseDvmMapFile)
	{
		return FALSE;
	}

	if(m_nEnaWriteWaitAfterSel != p->m_nEnaWriteWaitAfterSel)
	{
		return FALSE;
	}

	if(m_nEnaWriteWait != p->m_nEnaWriteWait)
	{
		return FALSE;
	}

	if(m_nReadAinUseReport != p->m_nReadAinUseReport)
	{
		return FALSE;
	}

	if(m_nAddRptBuffer != p->m_nAddRptBuffer)
	{
		return FALSE;
	}

	if(m_nCanWriteActiveSG != p->m_nCanWriteActiveSG)
	{
		return FALSE;
	}

	if(m_nProtocolVersion != p->m_nProtocolVersion)
	{
		return FALSE;
	}

	if(m_nUseDsDout != p->m_nUseDsDout)
	{
		return FALSE;
	}

	if(m_nEnaReadBeforeWrite != p->m_nEnaReadBeforeWrite)
	{
		return FALSE;
	}

	if(m_nWriteDataWaitMs != p->m_nWriteDataWaitMs)
	{
		return FALSE;
	}

	if(m_nAutoGenModelDatas != p->m_nAutoGenModelDatas)
	{
		return FALSE;
	}

	if(m_nUseGspLog != p->m_nUseGspLog)
	{
		return FALSE;
	}

	if(m_nSpecifiedDataset != p->m_nSpecifiedDataset)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL C61850ClientConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	C61850ClientConfig *p = (C61850ClientConfig*)pDest;

	p->m_nDebugMode = m_nDebugMode;
	p->m_nUseDvmMapFile = m_nUseDvmMapFile;
	p->m_nEnaWriteWaitAfterSel = m_nEnaWriteWaitAfterSel;
	p->m_nEnaWriteWait = m_nEnaWriteWait;
	p->m_nReadAinUseReport = m_nReadAinUseReport;
	p->m_nAddRptBuffer = m_nAddRptBuffer;
	p->m_nCanWriteActiveSG = m_nCanWriteActiveSG;
	p->m_nProtocolVersion = m_nProtocolVersion;
	p->m_nUseDsDout = m_nUseDsDout;
	p->m_nEnaReadBeforeWrite = m_nEnaReadBeforeWrite;
	p->m_nWriteDataWaitMs = m_nWriteDataWaitMs;
	p->m_nAutoGenModelDatas = m_nAutoGenModelDatas;
	p->m_nUseGspLog = m_nUseGspLog;
	p->m_nSpecifiedDataset = m_nSpecifiedDataset;
	return TRUE;
}

CBaseObject* C61850ClientConfig::Clone()
{
	C61850ClientConfig *p = new C61850ClientConfig();
	Copy(p);
	return p;
}

CBaseObject* C61850ClientConfig::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	C61850ClientConfig *p = new C61850ClientConfig();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL C61850ClientConfig::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CREMOTEDEVS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* C61850ClientConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	C61850ClientCfgMngrXmlRWKeys *pXmlKeys = (C61850ClientCfgMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRemoteDevsKey)
	{
		pNew = new CRemoteDevs();
	}

	return pNew;
}

CExBaseObject* C61850ClientConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CREMOTEDEVS)
	{
		pNew = new CRemoteDevs();
	}

	return pNew;
}

long C61850ClientConfig::GetRemoteDevCount()
{
	CRemoteDevs *pRemoteDevs = (CRemoteDevs*)FindByClassID(MNGRCLASSID_CREMOTEDEVS);

	if (pRemoteDevs == NULL)
	{
		return 0;
	}

	return pRemoteDevs->GetCount();
}

long C61850ClientConfig::GetIntgPdTime()
{
	CRemoteDevs *pRemoteDevs = GetRemoteDevs();

	if (pRemoteDevs->m_nIntgPd<=0)
	{
		pRemoteDevs->m_nIntgPd = 3000;
	}

	return pRemoteDevs->m_nIntgPd;
}

long C61850ClientConfig::GetCtrlType()
{
	CRemoteDevs *pRemoteDevs = GetRemoteDevs();

	if ((pRemoteDevs->m_nWriteCtrlType<DLT_WRITE_CTRL_TYPE_DIRECT)||(pRemoteDevs->m_nWriteCtrlType>DLT_WRITE_CTRL_TYPE_SBO))
	{
		pRemoteDevs->m_nWriteCtrlType = DLT_WRITE_CTRL_TYPE_SWV;
	}

	return pRemoteDevs->m_nWriteCtrlType;
}

BOOL C61850ClientConfig::HasCtrlTest()
{
	CRemoteDevs *pRemoteDevs = GetRemoteDevs();
	return (pRemoteDevs->m_nCtrlTest != 0);
}

BOOL C61850ClientConfig::HasCtrlSynCheck()
{
	CRemoteDevs *pRemoteDevs = GetRemoteDevs();
	return (pRemoteDevs->m_nCtrlCheck%2 != 0);
}

BOOL C61850ClientConfig::HasCtrlInterlockCheck()
{
	CRemoteDevs *pRemoteDevs = GetRemoteDevs();
	return (pRemoteDevs->m_nCtrlCheck/2 != 0);
}

BOOL C61850ClientConfig::HasTimeActived()
{
	CRemoteDevs *pRemoteDevs = GetRemoteDevs();
	return (pRemoteDevs->m_nHasTimeAct != 0);
}

void C61850ClientConfig::SetCtrlTest(BOOL bValue)
{
	CRemoteDevs *pRemoteDevs = GetRemoteDevs();
	pRemoteDevs->m_nCtrlTest = bValue;
}

void C61850ClientConfig::SetCtrlSynCheck(BOOL bValue)
{
	CRemoteDevs *pRemoteDevs = GetRemoteDevs();

	if (pRemoteDevs->m_nCtrlCheck>1)
	{
		pRemoteDevs->m_nCtrlCheck = 2;
	}
	else
	{
		pRemoteDevs->m_nCtrlCheck = 0;
	}

	pRemoteDevs->m_nCtrlCheck += bValue;
}

void C61850ClientConfig::SetCtrlInterlockCheck(BOOL bValue)
{
	CRemoteDevs *pRemoteDevs = GetRemoteDevs();
	long nValue1 = pRemoteDevs->m_nCtrlCheck%2;
	pRemoteDevs->m_nCtrlCheck = nValue1 + bValue*2;
}

void C61850ClientConfig::SetTimeActived(BOOL bValue)
{
	CRemoteDevs *pRemoteDevs = GetRemoteDevs();
	pRemoteDevs->m_nHasTimeAct = bValue;
}

void C61850ClientConfig::SetCtrlType(long nCtrlType)
{
	CRemoteDevs *pRemoteDevs = GetRemoteDevs();
	pRemoteDevs->m_nWriteCtrlType = nCtrlType;
}

BOOL C61850ClientConfig::OpenClientConfg(const CString &strConfigPath)
{
	m_strConfigPath = strConfigPath;
	return OpenXmlFile(m_strConfigPath,C61850ClientCfgMngrXmlRWKeys::g_pXmlKeys);
}

BOOL C61850ClientConfig::SaveClientConfg(const CString &strConfigPath)
{
	if ((!strConfigPath.IsEmpty())/*&&IsFileExist(strConfigPath)*/)
	{
		m_strConfigPath = strConfigPath;
	}

	return SaveXmlFile(m_strConfigPath,C61850ClientCfgMngrXmlRWKeys::g_pXmlKeys);
}

CRemoteDevs* C61850ClientConfig::GetRemoteDevs()
{
	if (m_pRemoteDevs != NULL)
	{
		return m_pRemoteDevs;
	}

	m_pRemoteDevs = (CRemoteDevs*)FindByClassID(MNGRCLASSID_CREMOTEDEVS);

	if (m_pRemoteDevs == NULL)
	{
		m_pRemoteDevs = new CRemoteDevs;
		AddNewChild(m_pRemoteDevs);
	}

	return m_pRemoteDevs;
}

CRemoteDev* C61850ClientConfig::GetRemoteDev(long nDevIndex)
{
	CRemoteDevs *pRemoteDevs = g_o61850ClientConfig.GetRemoteDevs();
	CRemoteDev *pRemoteDev = (CRemoteDev*)pRemoteDevs->GetAtIndex(nDevIndex);

	if (pRemoteDev == NULL)
	{
		pRemoteDev = new CRemoteDev();
		pRemoteDev->m_strID.Format(_T("Dev%ld"),nDevIndex);
		pRemoteDev->m_strName = pRemoteDev->m_strID;
		pRemoteDevs->AddNewChild(pRemoteDev);
	}

	return pRemoteDev;
}

#ifdef USE_61850CLient_STRCUT
void C61850ClientConfig::UpdateProtocolVersion()
{
	if ((m_nProtocolVersion <0x200)||(m_nProtocolVersion >0x201))
	{
		return;
	}

	g_nProtocolVersion = m_nProtocolVersion;
}

ACSI_NODE* C61850ClientConfig::mms_Find_ACSI_NODE_ByID(const CString &strDeviceID)
{
	CRemoteDevs *pRemoteDevs = GetRemoteDevs();
	return pRemoteDevs->FindAcsiNodeByID(strDeviceID);
}

ACSI_NODE* C61850ClientConfig::mms_Find_ACSI_NODE_UnConnect()
{
	CRemoteDevs *pRemoteDevs = GetRemoteDevs();
	return pRemoteDevs->FindAcsiNode_UnConnect();
}


ACSI_NODE* Client61850_GetAcsiNode(const long &nDevIndex)
{
	CRemoteDevs *pRemoteDevs = g_o61850ClientConfig.GetRemoteDevs();
	CRemoteDev *pRemoteDev = (CRemoteDev*)pRemoteDevs->GetAtIndex(nDevIndex);

	if (pRemoteDev == NULL)
	{
		return NULL;
	}

	return pRemoteDev->GetAcsiNode();
}

#endif
