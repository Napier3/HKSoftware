//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Stt_RemoteUserHis.cpp  CStt_RemoteUserHis


#include "stdafx.h"
#include "Stt_RemoteUserHis.h"
#include "../../SttGlobalDef.h"
#include "../../SttCmd/SttParas.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CStt_RemoteUserHis::CStt_RemoteUserHis()
{
	//初始化属性
	m_nIndex_User = 0;
	m_nIndex_Register = 0;
	m_nID_Test = 0;
	m_nID_Authority = 0;

	//初始化成员变量
}

CStt_RemoteUserHis::~CStt_RemoteUserHis()
{
}

long CStt_RemoteUserHis::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_UserKey, oNode, m_nIndex_User);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_RegisterKey, oNode, m_nIndex_Register);
	xml_GetAttibuteValue(pXmlKeys->m_strName_CopKey, oNode, m_strName_Cop);
	xml_GetAttibuteValue(pXmlKeys->m_strName_UserKey, oNode, m_strName_User);
	xml_GetAttibuteValue(pXmlKeys->m_strIPKey, oNode, m_strIP);
	xml_GetAttibuteValue(pXmlKeys->m_strID_TestKey, oNode, m_nID_Test);
	xml_GetAttibuteValue(pXmlKeys->m_strID_TerminalKey, oNode, m_strID_Terminal);
	xml_GetAttibuteValue(pXmlKeys->m_strID_AuthorityKey, oNode, m_nID_Authority);

	CString strTemp = ID_STT_USER_ATTR_os;
	BSTR bstrTemp = strTemp.AllocSysString();
	xml_GetAttibuteValue(bstrTemp, oNode, m_strOs);
	SysFreeString(bstrTemp);

	strTemp = ID_STT_USER_ATTR_id_soft;
	bstrTemp = strTemp.AllocSysString();
	xml_GetAttibuteValue(bstrTemp, oNode, m_strId_Soft);
	SysFreeString(bstrTemp);

	strTemp = ID_STT_USER_ATTR_ver_soft;
	bstrTemp = strTemp.AllocSysString();
	xml_GetAttibuteValue(bstrTemp, oNode, m_strVer_Soft);
	SysFreeString(bstrTemp);

	return 0;
}

long CStt_RemoteUserHis::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_UserKey, oElement, m_nIndex_User);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_RegisterKey, oElement, m_nIndex_Register);
	xml_SetAttributeValue(pXmlKeys->m_strName_CopKey, oElement, m_strName_Cop);
	xml_SetAttributeValue(pXmlKeys->m_strName_UserKey, oElement, m_strName_User);
	xml_SetAttributeValue(pXmlKeys->m_strIPKey, oElement, m_strIP);
	xml_SetAttributeValue(pXmlKeys->m_strID_TestKey, oElement, m_nID_Test);
	xml_SetAttributeValue(pXmlKeys->m_strID_TerminalKey, oElement, m_strID_Terminal);
	xml_SetAttributeValue(pXmlKeys->m_strID_AuthorityKey, oElement, m_nID_Authority);

	CString strTemp = ID_STT_USER_ATTR_os;
	BSTR bstrTemp = strTemp.AllocSysString();
	xml_SetAttributeValue(bstrTemp, oElement, m_strOs);
	SysFreeString(bstrTemp);

	strTemp = ID_STT_USER_ATTR_id_soft;
	bstrTemp = strTemp.AllocSysString();
	xml_SetAttributeValue(bstrTemp, oElement, m_strId_Soft);
	SysFreeString(bstrTemp);

	strTemp = ID_STT_USER_ATTR_ver_soft;
	bstrTemp = strTemp.AllocSysString();
	xml_SetAttributeValue(bstrTemp, oElement, m_strVer_Soft);
	SysFreeString(bstrTemp);

	return 0;
}

long CStt_RemoteUserHis::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_User);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Register);
		BinarySerializeCalLen(oBinaryBuffer, m_strName_Cop);
		BinarySerializeCalLen(oBinaryBuffer, m_strName_User);
		BinarySerializeCalLen(oBinaryBuffer, m_strIP);
		BinarySerializeCalLen(oBinaryBuffer, m_nID_Test);
		BinarySerializeCalLen(oBinaryBuffer, m_strID_Terminal);
		BinarySerializeCalLen(oBinaryBuffer, m_nID_Authority);
		BinarySerializeCalLen(oBinaryBuffer, m_strOs);
		BinarySerializeCalLen(oBinaryBuffer, m_strId_Soft);
		BinarySerializeCalLen(oBinaryBuffer, m_strVer_Soft);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_User);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Register);
		BinarySerializeRead(oBinaryBuffer, m_strName_Cop);
		BinarySerializeRead(oBinaryBuffer, m_strName_User);
		BinarySerializeRead(oBinaryBuffer, m_strIP);
		BinarySerializeRead(oBinaryBuffer, m_nID_Test);
		BinarySerializeRead(oBinaryBuffer, m_strID_Terminal);
		BinarySerializeRead(oBinaryBuffer, m_nID_Authority);
		BinarySerializeRead(oBinaryBuffer, m_strOs);
		BinarySerializeRead(oBinaryBuffer, m_strId_Soft);
		BinarySerializeRead(oBinaryBuffer, m_strVer_Soft);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_User);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Register);
		BinarySerializeWrite(oBinaryBuffer, m_strName_Cop);
		BinarySerializeWrite(oBinaryBuffer, m_strName_User);
		BinarySerializeWrite(oBinaryBuffer, m_strIP);
		BinarySerializeWrite(oBinaryBuffer, m_nID_Test);
		BinarySerializeWrite(oBinaryBuffer, m_strID_Terminal);
		BinarySerializeWrite(oBinaryBuffer, m_nID_Authority);
		BinarySerializeWrite(oBinaryBuffer, m_strOs);
		BinarySerializeWrite(oBinaryBuffer, m_strId_Soft);
		BinarySerializeWrite(oBinaryBuffer, m_strVer_Soft);
	}
	return 0;
}

void CStt_RemoteUserHis::InitAfterRead()
{
}

BOOL CStt_RemoteUserHis::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CStt_RemoteUserHis *p = (CStt_RemoteUserHis*)pObj;

	if(m_nIndex_User != p->m_nIndex_User)
	{
		return FALSE;
	}

	if(m_nIndex_Register != p->m_nIndex_Register)
	{
		return FALSE;
	}

	if(m_strName_Cop != p->m_strName_Cop)
	{
		return FALSE;
	}

	if(m_strName_User != p->m_strName_User)
	{
		return FALSE;
	}

	if(m_strIP != p->m_strIP)
	{
		return FALSE;
	}

	if(m_nID_Test != p->m_nID_Test)
	{
		return FALSE;
	}

	if(m_strID_Terminal != p->m_strID_Terminal)
	{
		return FALSE;
	}

	if(m_nID_Authority != p->m_nID_Authority)
	{
		return FALSE;
	}

	if(m_strId_Soft != p->m_strId_Soft)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CStt_RemoteUserHis::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CStt_RemoteUserHis *p = (CStt_RemoteUserHis*)pDest;

	p->m_nIndex_User = m_nIndex_User;
	p->m_nIndex_Register = m_nIndex_Register;
	p->m_strName_Cop = m_strName_Cop;
	p->m_strName_User = m_strName_User;
	p->m_strIP = m_strIP;
	p->m_nID_Test = m_nID_Test;
	p->m_strID_Terminal = m_strID_Terminal;
	p->m_nID_Authority = m_nID_Authority;
	p->m_strOs = m_strOs;
	p->m_strId_Soft = m_strId_Soft;
	p->m_strVer_Soft = m_strVer_Soft;
	return TRUE;
}

CBaseObject* CStt_RemoteUserHis::Clone()
{
	CStt_RemoteUserHis *p = new CStt_RemoteUserHis();
	Copy(p);
	return p;
}

CBaseObject* CStt_RemoteUserHis::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CStt_RemoteUserHis *p = new CStt_RemoteUserHis();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CStt_RemoteUserHis::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_UserKey, m_nIndex_User);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_RegisterKey, m_nIndex_Register);
	pRecordset->GetFieldValue(pXmlKeys->m_strName_CopKey, m_strName_Cop);
	pRecordset->GetFieldValue(pXmlKeys->m_strName_UserKey, m_strName_User);
	pRecordset->GetFieldValue(pXmlKeys->m_strIPKey, m_strIP);
	pRecordset->GetFieldValue((const CString)ID_STT_USER_ATTR_os, m_strOs);
	pRecordset->GetFieldValue((const CString)ID_STT_USER_ATTR_id_soft, m_strId_Soft);
	pRecordset->GetFieldValue((const CString)ID_STT_USER_ATTR_ver_soft, m_strVer_Soft);

	return 0;
}

long CStt_RemoteUserHis::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_UserKey, m_nIndex_User);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_RegisterKey, m_nIndex_Register);
	pRecordset->SetFieldValue(pXmlKeys->m_strName_CopKey, m_strName_Cop);
	pRecordset->SetFieldValue(pXmlKeys->m_strName_UserKey, m_strName_User);
	pRecordset->SetFieldValue(pXmlKeys->m_strIPKey, m_strIP);
	pRecordset->SetFieldValue((const CString)ID_STT_USER_ATTR_os, m_strOs);
	pRecordset->SetFieldValue((const CString)ID_STT_USER_ATTR_id_soft, m_strId_Soft);
	pRecordset->SetFieldValue((const CString)ID_STT_USER_ATTR_ver_soft, m_strVer_Soft);	

	return 0;
}

void CStt_RemoteUserHis::DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)
{
	if (m_nIndex_User == 0)
	{
		m_nIndex_User = pRecordset->GetInsertId();  
	}  
}

BOOL CStt_RemoteUserHis::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == MNGRCLASSID_CSTT_REMOTEREGHIS)
	{
		m_nIndex_Register = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

void CStt_RemoteUserHis::AnalysisData(CDvmData *pData)
{
	long nID_Local = 0;
	long nID_Remote = 0;

	pData->GetValueByID(ID_STT_USER_ATTR_ID_Terminal,m_strID_Terminal);
	pData->GetValueByID(ID_STT_USER_ATTR_Name_Cop,m_strName_Cop);
	pData->GetValueByID(ID_STT_USER_ATTR_Name_User,m_strName_User);
	pData->GetValueByID(ID_STT_USER_ATTR_IP_User,m_strIP);
	pData->GetValueByID(STT_CMD_PARA_IDTESTER,m_nID_Test);
	pData->GetValueByID(ID_STT_USER_ATTR_os,m_strOs);
	pData->GetValueByID(ID_STT_USER_ATTR_id_soft,m_strId_Soft);
	pData->GetValueByID(ID_STT_USER_ATTR_ver_soft,m_strVer_Soft);

	SetAuthoritys(pData);
}

void CStt_RemoteUserHis::SetAuthoritys(CExBaseList *pParas)
{
	long nAuthority_Test = 0;
	long nAuthority_ClientEngine = 0;
	long nAuthority_Ats	 = 0;
	long nAuthority_PpMmsEngine = 0;
	long nAuthority_PpEngine = 0;
	long nAuthority_SttTestStudio = 0;
	long nAuthority_SttTestCntr	 = 0;
	long nAuthority_Iec61850Config = 0;
	long nAuthority_DvmTest	 = 0;
	long nAuthority_SmartTest	 = 0;

	if (pParas->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		CDvmData *pData = (CDvmData *)pParas;

		pData->GetValueByID(KEY_AUTHORITY_MODULE_Test,nAuthority_Test);
		pData->GetValueByID(KEY_AUTHORITY_MODULE_ClientEngine,nAuthority_ClientEngine);
		pData->GetValueByID(KEY_AUTHORITY_MODULE_Ats,nAuthority_Ats);
		
		pData->GetValueByID(KEY_AUTHORITY_MODULE_PpMmsEngine,nAuthority_PpMmsEngine);
		pData->GetValueByID(KEY_AUTHORITY_MODULE_PpEngine,nAuthority_PpEngine);
		pData->GetValueByID(KEY_AUTHORITY_MODULE_SttTestStudio,nAuthority_SttTestStudio);
		pData->GetValueByID(KEY_AUTHORITY_MODULE_SttTestCntr,nAuthority_SttTestCntr);
		pData->GetValueByID(KEY_AUTHORITY_MODULE_Iec61850Config,nAuthority_Iec61850Config);
		pData->GetValueByID(KEY_AUTHORITY_MODULE_DvmTest,nAuthority_DvmTest);
		pData->GetValueByID(KEY_AUTHORITY_MODULE_SmartTest,nAuthority_SmartTest);
	}
	else
	{
		stt_GetDataValueByID(pParas, KEY_AUTHORITY_MODULE_Test, nAuthority_Test);
		stt_GetDataValueByID(pParas, KEY_AUTHORITY_MODULE_ClientEngine, nAuthority_ClientEngine);
		stt_GetDataValueByID(pParas, KEY_AUTHORITY_MODULE_Ats,nAuthority_Ats);
		stt_GetDataValueByID(pParas, KEY_AUTHORITY_MODULE_PpMmsEngine,nAuthority_PpMmsEngine);
		stt_GetDataValueByID(pParas, KEY_AUTHORITY_MODULE_PpEngine,nAuthority_PpEngine);
		stt_GetDataValueByID(pParas, KEY_AUTHORITY_MODULE_SttTestStudio,nAuthority_SttTestStudio);
		stt_GetDataValueByID(pParas, KEY_AUTHORITY_MODULE_SttTestCntr,nAuthority_SttTestCntr);
		stt_GetDataValueByID(pParas, KEY_AUTHORITY_MODULE_Iec61850Config,nAuthority_Iec61850Config);
		stt_GetDataValueByID(pParas, KEY_AUTHORITY_MODULE_DvmTest,nAuthority_DvmTest);
		stt_GetDataValueByID(pParas, KEY_AUTHORITY_MODULE_SmartTest,nAuthority_SmartTest);
	}

	m_nID_Authority = 0;

	if(nAuthority_Test != 0)
	{
		m_nID_Authority |= ID_AUTHORITY_MODULE_Test;
	}
	if(nAuthority_ClientEngine != 0)
	{
		m_nID_Authority |= ID_AUTHORITY_MODULE_ClientEngine;
	}
	if(nAuthority_Ats != 0)
	{
		m_nID_Authority |= ID_AUTHORITY_MODULE_Ats;
	}
	if(nAuthority_PpMmsEngine != 0)
	{
		m_nID_Authority |= ID_AUTHORITY_MODULE_PpMmsEngine;
	}
	if(nAuthority_PpEngine != 0)
	{
		m_nID_Authority |= ID_AUTHORITY_MODULE_PpEngine;
	}
	if(nAuthority_SttTestStudio != 0)
	{
		m_nID_Authority |= ID_AUTHORITY_MODULE_SttTestStudio;
	}
	if(nAuthority_SttTestCntr != 0)
	{
		m_nID_Authority |= ID_AUTHORITY_MODULE_SttTestCntr;
	}
	if(nAuthority_Iec61850Config != 0)
	{
		m_nID_Authority |= ID_AUTHORITY_MODULE_Iec61850Config;
	}
	if(nAuthority_DvmTest != 0)
	{
		m_nID_Authority |= ID_AUTHORITY_MODULE_DvmTest;
	}
	if(nAuthority_SmartTest != 0)
	{
		m_nID_Authority |= ID_AUTHORITY_MODULE_SmartTest;
	}
}

void CStt_RemoteUserHis::SetAuthority(const CString &strModuleID, long nValue)
{
	if (strModuleID == KEY_AUTHORITY_MODULE_Test)
	{
		SetAuthority(ID_AUTHORITY_MODULE_Test,nValue);
	}
	else if (strModuleID == KEY_AUTHORITY_MODULE_ClientEngine)
	{
		SetAuthority(ID_AUTHORITY_MODULE_ClientEngine,nValue);
	}
	else if (strModuleID == KEY_AUTHORITY_MODULE_Ats)
	{
		SetAuthority(ID_AUTHORITY_MODULE_Ats,nValue);
	}
	else if (strModuleID == KEY_AUTHORITY_MODULE_PpMmsEngine)
	{
		SetAuthority(ID_AUTHORITY_MODULE_PpMmsEngine,nValue);
	}
	else if (strModuleID == KEY_AUTHORITY_MODULE_PpEngine)
	{
		SetAuthority(ID_AUTHORITY_MODULE_PpEngine,nValue);
	}
	else if (strModuleID == KEY_AUTHORITY_MODULE_SttTestStudio)
	{
		SetAuthority(ID_AUTHORITY_MODULE_SttTestStudio,nValue);
	}
	else if (strModuleID == KEY_AUTHORITY_MODULE_SttTestCntr)
	{
		SetAuthority(ID_AUTHORITY_MODULE_SttTestCntr,nValue);
	}
	else if (strModuleID == KEY_AUTHORITY_MODULE_Iec61850Config)
	{
		SetAuthority(ID_AUTHORITY_MODULE_Iec61850Config,nValue);
	}
	else if (strModuleID == KEY_AUTHORITY_MODULE_DvmTest)
	{
		SetAuthority(ID_AUTHORITY_MODULE_DvmTest,nValue);
	}
	else if (strModuleID == KEY_AUTHORITY_MODULE_SmartTest)
	{
		SetAuthority(ID_AUTHORITY_MODULE_SmartTest,nValue);
	}
}

void CStt_RemoteUserHis::SetAuthority(long nIDAuthority, long nValue)
{
	if (nValue != 0)
	{
		m_nID_Authority |= nIDAuthority;
	}
	else
	{
		m_nID_Authority &= (~nIDAuthority);
	}
}

BOOL CStt_RemoteUserHis::GetDB_SelectSql(CString &strSql)
{
	CString strTable,strRegisterPK,strIPKey,strUserKey;
	strTable = CRemoteCtrlMngrXmlRWKeys::CStt_RemoteUserHisKey();
	strRegisterPK = CRemoteCtrlMngrXmlRWKeys::Index_RegisterKey();
	strIPKey = CRemoteCtrlMngrXmlRWKeys::IPKey();
	strUserKey = CRemoteCtrlMngrXmlRWKeys::Name_UserKey();

	strSql.Format(_T("select * from %s where (%s=%d) and (%s=\"%s\") and (%s=\"%s\")")
		,strTable, strRegisterPK,m_nIndex_Register
		,strUserKey,m_strName_User
		,strIPKey,m_strIP);

	return TRUE;
}