//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Stt_RemoteRegHis.cpp  CStt_RemoteRegHis


#include "stdafx.h"
#include "Stt_RemoteRegHis.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CStt_RemoteRegHis::CStt_RemoteRegHis()
{
	//初始化属性
	m_nIndex_Register = 0;
	::GetLocalTime(&m_tmTm_Register);
	::GetLocalTime(&m_tmTm_UnRegister);
	m_nMode_Register = 0;

	//初始化成员变量
	m_pRef_Socket = NULL;
}

CStt_RemoteRegHis::~CStt_RemoteRegHis()
{
}

long CStt_RemoteRegHis::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_RegisterKey, oNode, m_nIndex_Register);
	xml_GetAttibuteValue(pXmlKeys->m_strSN_TestAppKey, oNode, m_strSN_TestApp);
	xml_GetAttibuteValue(pXmlKeys->m_strModel_TestAppKey, oNode, m_strModel_TestApp);
	xml_GetAttibuteValue(pXmlKeys->m_strModel_DvKey, oNode, m_strModel_Dv);
	xml_GetAttibuteValue(pXmlKeys->m_strName_CopKey, oNode, m_strName_Cop);
	xml_GetAttibuteValue(pXmlKeys->m_strName_UserKey, oNode, m_strName_User);
	xml_GetAttibuteValue(pXmlKeys->m_strCode_RegisterKey, oNode, m_strCode_Register);
	xml_GetAttibuteValue(pXmlKeys->m_strTm_RegisterKey, oNode, m_tmTm_Register);
	xml_GetAttibuteValue(pXmlKeys->m_strTm_UnRegisterKey, oNode, m_tmTm_UnRegister);
	xml_GetAttibuteValue(pXmlKeys->m_strMode_RegisterKey, oNode, m_nMode_Register);
	xml_GetAttibuteValue(pXmlKeys->m_strDescriptionKey, oNode, m_strDescription);
	xml_GetAttibuteValue(pXmlKeys->m_strPath_HisFilesKey, oNode, m_strPath_HisFiles);

	xml_GetAttibuteValue(pXmlKeys->m_strVer_PpMmsEngineKey, oNode, m_strVer_PpMmsEngine);
	xml_GetAttibuteValue(pXmlKeys->m_strVer_PpEngineKey, oNode, m_strVer_PpEngine);
	xml_GetAttibuteValue(pXmlKeys->m_strVer_SttTestStudioKey, oNode, m_strVer_SttTestStudio);
	xml_GetAttibuteValue(pXmlKeys->m_strVer_SttTestCntrKey, oNode, m_strVer_SttTestCntr);
	xml_GetAttibuteValue(pXmlKeys->m_strVer_Iec61850ConfigKey, oNode, m_strVer_Iec61850Config);
	xml_GetAttibuteValue(pXmlKeys->m_strVer_DvmTestKey, oNode, m_strVer_DvmTest);
	xml_GetAttibuteValue(pXmlKeys->m_strVer_SmartTestKey, oNode, m_strVer_SmartTest);
	xml_GetAttibuteValue(pXmlKeys->m_strVer_TestServerKey, oNode, m_strVer_TestServer);
	return 0;
}

long CStt_RemoteRegHis::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_RegisterKey, oElement, m_nIndex_Register);
	xml_SetAttributeValue(pXmlKeys->m_strSN_TestAppKey, oElement, m_strSN_TestApp);
	xml_SetAttributeValue(pXmlKeys->m_strModel_TestAppKey, oElement, m_strModel_TestApp);
	xml_SetAttributeValue(pXmlKeys->m_strModel_DvKey, oElement, m_strModel_Dv);
	xml_SetAttributeValue(pXmlKeys->m_strName_CopKey, oElement, m_strName_Cop);
	xml_SetAttributeValue(pXmlKeys->m_strName_UserKey, oElement, m_strName_User);
	xml_SetAttributeValue(pXmlKeys->m_strCode_RegisterKey, oElement, m_strCode_Register);
	xml_SetAttributeValue(pXmlKeys->m_strTm_RegisterKey, oElement, m_tmTm_Register);
	xml_SetAttributeValue(pXmlKeys->m_strTm_UnRegisterKey, oElement, m_tmTm_UnRegister);
	xml_SetAttributeValue(pXmlKeys->m_strMode_RegisterKey, oElement, m_nMode_Register);
	xml_SetAttributeValue(pXmlKeys->m_strDescriptionKey, oElement, m_strDescription);
	xml_SetAttributeValue(pXmlKeys->m_strPath_HisFilesKey, oElement, m_strPath_HisFiles);

	xml_SetAttributeValue(pXmlKeys->m_strVer_PpMmsEngineKey, oElement, m_strVer_PpMmsEngine);
	xml_SetAttributeValue(pXmlKeys->m_strVer_PpEngineKey, oElement, m_strVer_PpEngine);
	xml_SetAttributeValue(pXmlKeys->m_strVer_SttTestStudioKey, oElement, m_strVer_SttTestStudio);
	xml_SetAttributeValue(pXmlKeys->m_strVer_SttTestCntrKey, oElement, m_strVer_SttTestCntr);
	xml_SetAttributeValue(pXmlKeys->m_strVer_Iec61850ConfigKey, oElement, m_strVer_Iec61850Config);
	xml_SetAttributeValue(pXmlKeys->m_strVer_DvmTestKey, oElement, m_strVer_DvmTest);
	xml_SetAttributeValue(pXmlKeys->m_strVer_SmartTestKey, oElement, m_strVer_SmartTest);
	xml_SetAttributeValue(pXmlKeys->m_strVer_TestServerKey, oElement, m_strVer_TestServer);

	return 0;
}

long CStt_RemoteRegHis::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Register);
		BinarySerializeCalLen(oBinaryBuffer, m_strSN_TestApp);
		BinarySerializeCalLen(oBinaryBuffer, m_strModel_TestApp);
		BinarySerializeCalLen(oBinaryBuffer, m_strModel_Dv);
		BinarySerializeCalLen(oBinaryBuffer, m_strName_Cop);
		BinarySerializeCalLen(oBinaryBuffer, m_strName_User);
		BinarySerializeCalLen(oBinaryBuffer, m_strCode_Register);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTm_Register);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTm_UnRegister);
		BinarySerializeCalLen(oBinaryBuffer, m_nMode_Register);
		BinarySerializeCalLen(oBinaryBuffer, m_strDescription);
		BinarySerializeCalLen(oBinaryBuffer, m_strPath_HisFiles);

		BinarySerializeCalLen(oBinaryBuffer, m_strVer_PpMmsEngine);
		BinarySerializeCalLen(oBinaryBuffer, m_strVer_PpEngine);
		BinarySerializeCalLen(oBinaryBuffer, m_strVer_SttTestStudio);
		BinarySerializeCalLen(oBinaryBuffer, m_strVer_SttTestCntr);
		BinarySerializeCalLen(oBinaryBuffer, m_strVer_Iec61850Config);
		BinarySerializeCalLen(oBinaryBuffer, m_strVer_DvmTest);
		BinarySerializeCalLen(oBinaryBuffer, m_strVer_SmartTest);
		BinarySerializeCalLen(oBinaryBuffer, m_strVer_TestServer);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Register);
		BinarySerializeRead(oBinaryBuffer, m_strSN_TestApp);
		BinarySerializeRead(oBinaryBuffer, m_strModel_TestApp);
		BinarySerializeRead(oBinaryBuffer, m_strModel_Dv);
		BinarySerializeRead(oBinaryBuffer, m_strName_Cop);
		BinarySerializeRead(oBinaryBuffer, m_strName_User);
		BinarySerializeRead(oBinaryBuffer, m_strCode_Register);
		BinarySerializeRead(oBinaryBuffer, m_tmTm_Register);
		BinarySerializeRead(oBinaryBuffer, m_tmTm_UnRegister);
		BinarySerializeRead(oBinaryBuffer, m_nMode_Register);
		BinarySerializeRead(oBinaryBuffer, m_strDescription);
		BinarySerializeRead(oBinaryBuffer, m_strPath_HisFiles);

		BinarySerializeRead(oBinaryBuffer, m_strVer_PpMmsEngine);
		BinarySerializeRead(oBinaryBuffer, m_strVer_PpEngine);
		BinarySerializeRead(oBinaryBuffer, m_strVer_SttTestStudio);
		BinarySerializeRead(oBinaryBuffer, m_strVer_SttTestCntr);
		BinarySerializeRead(oBinaryBuffer, m_strVer_Iec61850Config);
		BinarySerializeRead(oBinaryBuffer, m_strVer_DvmTest);
		BinarySerializeRead(oBinaryBuffer, m_strVer_SmartTest);
		BinarySerializeRead(oBinaryBuffer, m_strVer_TestServer);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Register);
		BinarySerializeWrite(oBinaryBuffer, m_strSN_TestApp);
		BinarySerializeWrite(oBinaryBuffer, m_strModel_TestApp);
		BinarySerializeWrite(oBinaryBuffer, m_strModel_Dv);
		BinarySerializeWrite(oBinaryBuffer, m_strName_Cop);
		BinarySerializeWrite(oBinaryBuffer, m_strName_User);
		BinarySerializeWrite(oBinaryBuffer, m_strCode_Register);
		BinarySerializeWrite(oBinaryBuffer, m_tmTm_Register);
		BinarySerializeWrite(oBinaryBuffer, m_tmTm_UnRegister);
		BinarySerializeWrite(oBinaryBuffer, m_nMode_Register);
		BinarySerializeWrite(oBinaryBuffer, m_strDescription);
		BinarySerializeWrite(oBinaryBuffer, m_strPath_HisFiles);

		BinarySerializeWrite(oBinaryBuffer, m_strVer_PpMmsEngine);
		BinarySerializeWrite(oBinaryBuffer, m_strVer_PpEngine);
		BinarySerializeWrite(oBinaryBuffer, m_strVer_SttTestStudio);
		BinarySerializeWrite(oBinaryBuffer, m_strVer_SttTestCntr);
		BinarySerializeWrite(oBinaryBuffer, m_strVer_Iec61850Config);
		BinarySerializeWrite(oBinaryBuffer, m_strVer_DvmTest);
		BinarySerializeWrite(oBinaryBuffer, m_strVer_SmartTest);
		BinarySerializeWrite(oBinaryBuffer, m_strVer_TestServer);
	}
	return 0;
}

void CStt_RemoteRegHis::InitAfterRead()
{
}

BOOL CStt_RemoteRegHis::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CStt_RemoteRegHis *p = (CStt_RemoteRegHis*)pObj;

	if(m_nIndex_Register != p->m_nIndex_Register)
	{
		return FALSE;
	}

	if(m_strSN_TestApp != p->m_strSN_TestApp)
	{
		return FALSE;
	}

	if(m_strModel_TestApp != p->m_strModel_TestApp)
	{
		return FALSE;
	}

	if(m_strModel_Dv != p->m_strModel_Dv)
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

	if(m_strCode_Register != p->m_strCode_Register)
	{
		return FALSE;
	}

	if(m_nMode_Register != p->m_nMode_Register)
	{
		return FALSE;
	}

	if(m_strDescription != p->m_strDescription)
	{
		return FALSE;
	}

	if(m_strPath_HisFiles != p->m_strPath_HisFiles)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CStt_RemoteRegHis::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CStt_RemoteRegHis *p = (CStt_RemoteRegHis*)pDest;

	p->m_nIndex_Register = m_nIndex_Register;
	p->m_strSN_TestApp = m_strSN_TestApp;
	p->m_strModel_TestApp = m_strModel_TestApp;
	p->m_strModel_Dv = m_strModel_Dv;
	p->m_strName_Cop = m_strName_Cop;
	p->m_strName_User = m_strName_User;
	p->m_strCode_Register = m_strCode_Register;
	p->m_tmTm_Register = m_tmTm_Register;
	p->m_tmTm_UnRegister = m_tmTm_UnRegister;
	p->m_nMode_Register = m_nMode_Register;
	p->m_strDescription = m_strDescription;
	p->m_strPath_HisFiles = m_strPath_HisFiles;

	p->m_strVer_PpMmsEngine = m_strVer_PpMmsEngine;
	p->m_strVer_PpEngine = m_strVer_PpEngine;
	p->m_strVer_SttTestStudio = m_strVer_SttTestStudio;
	p->m_strVer_SttTestCntr = m_strVer_SttTestCntr;
	p->m_strVer_Iec61850Config = m_strVer_Iec61850Config;
	p->m_strVer_DvmTest = m_strVer_DvmTest;
	p->m_strVer_SmartTest = m_strVer_SmartTest;
	p->m_strVer_TestServer = m_strVer_TestServer;

	p->SetRefSocket(m_pRef_Socket);

	return TRUE;
}

CBaseObject* CStt_RemoteRegHis::Clone()
{
	CStt_RemoteRegHis *p = new CStt_RemoteRegHis();
	Copy(p);
	return p;
}

CBaseObject* CStt_RemoteRegHis::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CStt_RemoteRegHis *p = new CStt_RemoteRegHis();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CStt_RemoteRegHis::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTT_REMOTEUSERHIS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CStt_RemoteRegHis::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCStt_RemoteUserHisKey)
	{
		pNew = new CStt_RemoteUserHis();
	}

	return pNew;
}

CExBaseObject* CStt_RemoteRegHis::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTT_REMOTEUSERHIS)
	{
		pNew = new CStt_RemoteUserHis();
	}

	return pNew;
}
long CStt_RemoteRegHis::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_RegisterKey, m_nIndex_Register);
	pRecordset->GetFieldValue(pXmlKeys->m_strSN_TestAppKey, m_strSN_TestApp);
	pRecordset->GetFieldValue(pXmlKeys->m_strModel_TestAppKey, m_strModel_TestApp);
	pRecordset->GetFieldValue(pXmlKeys->m_strModel_DvKey, m_strModel_Dv);
	pRecordset->GetFieldValue(pXmlKeys->m_strName_CopKey, m_strName_Cop);
	pRecordset->GetFieldValue(pXmlKeys->m_strName_UserKey, m_strName_User);
	pRecordset->GetFieldValue(pXmlKeys->m_strCode_RegisterKey, m_strCode_Register);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_RegisterKey, m_tmTm_Register);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_UnRegisterKey, m_tmTm_UnRegister);
	pRecordset->GetFieldValue(pXmlKeys->m_strMode_RegisterKey, m_nMode_Register);
	pRecordset->GetFieldValue(pXmlKeys->m_strDescriptionKey, m_strDescription);
	pRecordset->GetFieldValue(pXmlKeys->m_strPath_HisFilesKey, m_strPath_HisFiles);

	return 0;
}

long CStt_RemoteRegHis::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_RegisterKey, m_nIndex_Register);
	pRecordset->SetFieldValue(pXmlKeys->m_strSN_TestAppKey, m_strSN_TestApp);
	pRecordset->SetFieldValue(pXmlKeys->m_strModel_TestAppKey, m_strModel_TestApp);
	pRecordset->SetFieldValue(pXmlKeys->m_strModel_DvKey, m_strModel_Dv);
	pRecordset->SetFieldValue(pXmlKeys->m_strName_CopKey, m_strName_Cop);
	pRecordset->SetFieldValue(pXmlKeys->m_strName_UserKey, m_strName_User);
	pRecordset->SetFieldValue(pXmlKeys->m_strCode_RegisterKey, m_strCode_Register);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_RegisterKey, m_tmTm_Register);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_UnRegisterKey, m_tmTm_UnRegister);
	pRecordset->SetFieldValue(pXmlKeys->m_strMode_RegisterKey, m_nMode_Register);
	pRecordset->SetFieldValue(pXmlKeys->m_strDescriptionKey, m_strDescription);
	pRecordset->SetFieldValue(pXmlKeys->m_strPath_HisFilesKey, m_strPath_HisFiles);

	return 0;
}

void CStt_RemoteRegHis::DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  
{    
	if (m_nIndex_Register == 0)
	{
		m_nIndex_Register = pRecordset->GetInsertId();  
	}   
}

CExBaseObject* CStt_RemoteRegHis::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CStt_RemoteUserHis();

	return pNew;
}

void CStt_RemoteRegHis::SetRefSocket(CSttCloudServerClientSocketBase *pRef_Socket)
{
	ASSERT(pRef_Socket != NULL);

	m_pRef_Socket = pRef_Socket;

	m_strSN_TestApp = pRef_Socket->m_strSN_TestApp;
	m_strCode_Register = pRef_Socket->m_strCode_Register;

	if (pRef_Socket->IsSocketType_Own())
	{
		m_nMode_Register = ID_STT_REGISTER_MODE_TEST;
	}
	else
	{
		m_nMode_Register = ID_STT_REGISTER_MODE_ASSIST;
	}
}

void CStt_RemoteRegHis::GetRegDetail(CString &strRegDetail)
{
	strRegDetail = _T("");
	CString strTime;
	CString strVerInfo;

	SystemTime_To_String(m_tmTm_Register,strTime);

	if(IsRegister_Test())
	{	
		strVerInfo.Format(_T("Ver_SmartTest:%s\r\nVer_TestServer:%s\r\n")
			,m_strVer_SmartTest,m_strVer_TestServer);

		strRegDetail.Format(_T("问题描述：%s\r\n远程注册时间：%s\r\n控制记录目录：%s\r\n%s")
			,m_strDescription,strTime,m_strPath_HisFiles,strVerInfo);
	}
	else
	{
		strVerInfo.Format(_T("Ver_PpMmsEngine:%s\r\nVer_PpEngine:%s\r\nVer_SttTestStudio:%s\r\nVer_SttTestCntr:%s\r\nVer_Iec61850Config:%s\r\nVer_DvmTest:%s\r\nVer_SmartTest:%s\r\n")
			,m_strVer_PpMmsEngine,m_strVer_PpEngine,m_strVer_SttTestStudio,m_strVer_SttTestCntr,m_strVer_Iec61850Config,m_strVer_DvmTest,m_strVer_SmartTest);

		strRegDetail.Format(_T("问题描述：%s\r\n远程注册时间：%s\r\n控制记录目录：%s\r\n装置型号：%s\r\n%s")
			,m_strDescription,strTime,m_strPath_HisFiles,strVerInfo);
	}
}

void CStt_RemoteRegHis::AnalysisRegisterAttr(CSttRemoteCmd &oRemoteCmd
						,CSttCloudServerClientSocketBase *pRef_Socket,const CString &strRootPath)
{
	CString strFolder = _T("");

	SetRefSocket(pRef_Socket);
	GetLocalTime(&m_tmTm_Register);
	strFolder.Format(_T("Register_%04d%02d%02d%02d%02d%02d_%s\\")
						,m_tmTm_Register.wYear,m_tmTm_Register.wMonth
						,m_tmTm_Register.wDay,m_tmTm_Register.wHour
						,m_tmTm_Register.wMinute,m_tmTm_Register.wSecond,m_strSN_TestApp);
	m_strPath_HisFiles = strRootPath + strFolder;		

	oRemoteCmd.GetParasDataValueByID(ID_STT_REGISTER_ATTR_Model_TestApp, m_strModel_TestApp);
	oRemoteCmd.GetParasDataValueByID(ID_STT_REGISTER_ATTR_Model_Dv, m_strModel_Dv);
	oRemoteCmd.GetParasDataValueByID(ID_STT_USER_ATTR_Name_Cop, m_strName_Cop);
	oRemoteCmd.GetParasDataValueByID(ID_STT_USER_ATTR_Name_User, m_strName_User);
	oRemoteCmd.GetParasDataValueByID(ID_STT_REGISTER_ATTR_Description, m_strDescription);
	oRemoteCmd.GetParasDataValueByID(ID_STT_REGISTER_ATTR_Ver_PpMmsEngine, m_strVer_PpMmsEngine);
	oRemoteCmd.GetParasDataValueByID(ID_STT_REGISTER_ATTR_Ver_PpEngine, m_strVer_PpEngine);
	oRemoteCmd.GetParasDataValueByID(ID_STT_REGISTER_ATTR_Ver_SttTestStudio, m_strVer_SttTestStudio);
	oRemoteCmd.GetParasDataValueByID(ID_STT_REGISTER_ATTR_Ver_SttTestCntr, m_strVer_SttTestCntr);
	oRemoteCmd.GetParasDataValueByID(ID_STT_REGISTER_ATTR_Ver_Iec61850Config, m_strVer_Iec61850Config);
	oRemoteCmd.GetParasDataValueByID(ID_STT_REGISTER_ATTR_Ver_DvmTest, m_strVer_DvmTest);
	oRemoteCmd.GetParasDataValueByID(ID_STT_REGISTER_ATTR_Ver_SmartTest, m_strVer_SmartTest);
	oRemoteCmd.GetParasDataValueByID(ID_STT_REGISTER_ATTR_Ver_TestServer, m_strVer_TestServer);
}

void CStt_RemoteRegHis::InitDvmData(CDvmData &oData)
{
	oData.AddValue(ID_STT_USER_ATTR_SN_TestApp, m_strSN_TestApp);
	oData.AddValue(ID_STT_REGISTER_ATTR_Model_TestApp, m_strModel_TestApp);
	oData.AddValue(ID_STT_REGISTER_ATTR_Model_Dv, m_strModel_Dv);
	oData.AddValue(ID_STT_USER_ATTR_Name_Cop, m_strName_Cop);
	oData.AddValue(ID_STT_USER_ATTR_Name_User, m_strName_User);
	oData.AddValue(ID_STT_REGISTER_ATTR_Description, m_strDescription);

	oData.AddValue(ID_STT_REGISTER_ATTR_Ver_PpMmsEngine, m_strVer_PpMmsEngine);
	oData.AddValue(ID_STT_REGISTER_ATTR_Ver_PpEngine, m_strVer_PpEngine);
	oData.AddValue(ID_STT_REGISTER_ATTR_Ver_SttTestStudio, m_strVer_SttTestStudio);
	oData.AddValue(ID_STT_REGISTER_ATTR_Ver_SttTestCntr, m_strVer_SttTestCntr);
	oData.AddValue(ID_STT_REGISTER_ATTR_Ver_Iec61850Config, m_strVer_Iec61850Config);
	oData.AddValue(ID_STT_REGISTER_ATTR_Ver_DvmTest, m_strVer_DvmTest);
	oData.AddValue(ID_STT_REGISTER_ATTR_Ver_SmartTest, m_strVer_SmartTest);
	oData.AddValue(ID_STT_REGISTER_ATTR_Ver_TestServer, m_strVer_TestServer);
}