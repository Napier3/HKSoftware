//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_RTTaskBatch.cpp  CAts_RTTaskBatch


#include "stdafx.h"
#include "Ats_RTTaskBatch.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_RTTaskBatch::CAts_RTTaskBatch()
{
	//初始化属性
	m_nIndex_TaskBatch = 0;
	m_nIndex_Task = 0;
	::GetLocalTime(&m_tmStartTime);
	::GetLocalTime(&m_tmEndTime);
	m_nState = 0;

	m_pDvmDeviceRef = NULL;
	m_pSensorPpCfg = NULL;
}

CAts_RTTaskBatch::~CAts_RTTaskBatch()
{
	if (m_pDvmDeviceRef != NULL)
	{
		delete m_pDvmDeviceRef;
		m_pDvmDeviceRef = NULL;
	}
}

long CAts_RTTaskBatch::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TaskBatchKey, oNode, m_nIndex_TaskBatch);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TaskKey, oNode, m_nIndex_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strDvmFileKey, oNode, m_strDvmFile);
	xml_GetAttibuteValue(pXmlKeys->m_strGbxmlFileKey, oNode, m_strGbxmlFile);
	xml_GetAttibuteValue(pXmlKeys->m_strReportPkgFileKey, oNode, m_strReportPkgFile);
	xml_GetAttibuteValue(pXmlKeys->m_strEngineRawPkgFileKey, oNode, m_strEngineRawPkgFile);
	xml_GetAttibuteValue(pXmlKeys->m_strVmRawPkgFileKey, oNode, m_strVmRawPkgFile);
	xml_GetAttibuteValue(pXmlKeys->m_strStartTimeKey, oNode, m_tmStartTime);
	xml_GetAttibuteValue(pXmlKeys->m_strEndTimeKey, oNode, m_tmEndTime);
	xml_GetAttibuteValue(pXmlKeys->m_strStateKey, oNode, m_nState);
	return 0;
}

long CAts_RTTaskBatch::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_TaskBatchKey, oElement, m_nIndex_TaskBatch);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TaskKey, oElement, m_nIndex_Task);
	xml_SetAttributeValue(pXmlKeys->m_strDvmFileKey, oElement, m_strDvmFile);
	xml_SetAttributeValue(pXmlKeys->m_strGbxmlFileKey, oElement, m_strGbxmlFile);
	xml_SetAttributeValue(pXmlKeys->m_strReportPkgFileKey, oElement, m_strReportPkgFile);
	xml_SetAttributeValue(pXmlKeys->m_strEngineRawPkgFileKey, oElement, m_strEngineRawPkgFile);
	xml_SetAttributeValue(pXmlKeys->m_strVmRawPkgFileKey, oElement, m_strVmRawPkgFile);
	xml_SetAttributeValue(pXmlKeys->m_strStartTimeKey, oElement, m_tmStartTime);
	xml_SetAttributeValue(pXmlKeys->m_strEndTimeKey, oElement, m_tmEndTime);
	xml_SetAttributeValue(pXmlKeys->m_strStateKey, oElement, m_nState);
	return 0;
}

long CAts_RTTaskBatch::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_TaskBatch);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvmFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strGbxmlFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strReportPkgFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strEngineRawPkgFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strVmRawPkgFile);
		BinarySerializeCalLen(oBinaryBuffer, m_tmStartTime);
		BinarySerializeCalLen(oBinaryBuffer, m_tmEndTime);
		BinarySerializeCalLen(oBinaryBuffer, m_nState);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_TaskBatch);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeRead(oBinaryBuffer, m_strDvmFile);
		BinarySerializeRead(oBinaryBuffer, m_strGbxmlFile);
		BinarySerializeRead(oBinaryBuffer, m_strReportPkgFile);
		BinarySerializeRead(oBinaryBuffer, m_strEngineRawPkgFile);
		BinarySerializeRead(oBinaryBuffer, m_strVmRawPkgFile);
		BinarySerializeRead(oBinaryBuffer, m_tmStartTime);
		BinarySerializeRead(oBinaryBuffer, m_tmEndTime);
		BinarySerializeRead(oBinaryBuffer, m_nState);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_TaskBatch);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeWrite(oBinaryBuffer, m_strDvmFile);
		BinarySerializeWrite(oBinaryBuffer, m_strGbxmlFile);
		BinarySerializeWrite(oBinaryBuffer, m_strReportPkgFile);
		BinarySerializeWrite(oBinaryBuffer, m_strEngineRawPkgFile);
		BinarySerializeWrite(oBinaryBuffer, m_strVmRawPkgFile);
		BinarySerializeWrite(oBinaryBuffer, m_tmStartTime);
		BinarySerializeWrite(oBinaryBuffer, m_tmEndTime);
		BinarySerializeWrite(oBinaryBuffer, m_nState);
	}
	return 0;
}

void CAts_RTTaskBatch::InitAfterRead()
{
}

BOOL CAts_RTTaskBatch::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAts_RTTaskBatch *p = (CAts_RTTaskBatch*)pObj;

	if(m_nIndex_TaskBatch != p->m_nIndex_TaskBatch)
	{
		return FALSE;
	}

	if(m_nIndex_Task != p->m_nIndex_Task)
	{
		return FALSE;
	}

	if(m_strDvmFile != p->m_strDvmFile)
	{
		return FALSE;
	}

	if(m_strGbxmlFile != p->m_strGbxmlFile)
	{
		return FALSE;
	}

	if(m_strReportPkgFile != p->m_strReportPkgFile)
	{
		return FALSE;
	}

	if(m_strEngineRawPkgFile != p->m_strEngineRawPkgFile)
	{
		return FALSE;
	}

	if(m_strVmRawPkgFile != p->m_strVmRawPkgFile)
	{
		return FALSE;
	}

	if(m_nState != p->m_nState)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_RTTaskBatch::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAts_RTTaskBatch *p = (CAts_RTTaskBatch*)pDest;

	p->m_nIndex_TaskBatch = m_nIndex_TaskBatch;
	p->m_nIndex_Task = m_nIndex_Task;
	p->m_strDvmFile = m_strDvmFile;
	p->m_strGbxmlFile = m_strGbxmlFile;
	p->m_strReportPkgFile = m_strReportPkgFile;
	p->m_strEngineRawPkgFile = m_strEngineRawPkgFile;
	p->m_strVmRawPkgFile = m_strVmRawPkgFile;
	p->m_tmStartTime = m_tmStartTime;
	p->m_tmEndTime = m_tmEndTime;
	p->m_nState = m_nState;
	return TRUE;
}

CBaseObject* CAts_RTTaskBatch::Clone()
{
	CAts_RTTaskBatch *p = new CAts_RTTaskBatch();
	Copy(p);
	return p;
}

CBaseObject* CAts_RTTaskBatch::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_RTTaskBatch *p = new CAts_RTTaskBatch();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_RTTaskBatch::CanPaste(UINT nClassID)
{
	if (nClassID == ATSCLASSID_CATS_RTDEVICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_RTTaskBatch::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_RTDeviceKey)
	{
		pNew = new CAts_RTDevice();
	}

	return pNew;
}

CExBaseObject* CAts_RTTaskBatch::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSCLASSID_CATS_RTDEVICE)
	{
		pNew = new CAts_RTDevice();
	}

	return pNew;
}
long CAts_RTTaskBatch::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TaskBatchKey, m_nIndex_TaskBatch);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceTypeNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceTypeIDKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strDvmFileKey, m_strDvmFile);
	pRecordset->GetFieldValue(pXmlKeys->m_strGbxmlFileKey, m_strGbxmlFile);
	pRecordset->GetFieldValue(pXmlKeys->m_strReportPkgFileKey, m_strReportPkgFile);
	pRecordset->GetFieldValue(pXmlKeys->m_strEngineRawPkgFileKey, m_strEngineRawPkgFile);
	pRecordset->GetFieldValue(pXmlKeys->m_strVmRawPkgFileKey, m_strVmRawPkgFile);
	pRecordset->GetFieldValue(pXmlKeys->m_strStartTimeKey, m_tmStartTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strEndTimeKey, m_tmEndTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strStateKey, m_nState);
	return 0;
}

long CAts_RTTaskBatch::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TaskBatchKey, m_nIndex_TaskBatch);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceTypeNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceTypeIDKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strDvmFileKey, m_strDvmFile);
	pRecordset->SetFieldValue(pXmlKeys->m_strGbxmlFileKey, m_strGbxmlFile);
	pRecordset->SetFieldValue(pXmlKeys->m_strReportPkgFileKey, m_strReportPkgFile);
	pRecordset->SetFieldValue(pXmlKeys->m_strEngineRawPkgFileKey, m_strEngineRawPkgFile);
	pRecordset->SetFieldValue(pXmlKeys->m_strVmRawPkgFileKey, m_strVmRawPkgFile);
	pRecordset->SetFieldValue(pXmlKeys->m_strStartTimeKey, m_tmStartTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strEndTimeKey, m_tmEndTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strStateKey, m_nState);
	return 0;
}

BOOL CAts_RTTaskBatch::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == ATSCLASSID_CATS_RTTASK)
	{
		m_nIndex_Task = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

CExBaseObject* CAts_RTTaskBatch::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_RTDevice();

	return pNew;
}

CDvmDevice *CAts_RTTaskBatch::GetDvmDevice()
{
	if (m_pDvmDeviceRef == NULL)
	{
		CDvmDevice *pDevice = new CDvmDevice;
		BOOL bRet = pDevice->OpenXmlFile(m_strDvmFile,CDataMngrXmlRWKeys::g_pXmlKeys);
		if (!bRet)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("当前装置分类数据模型文件不存在或错误。"));
			delete pDevice;
			pDevice = NULL;
		}

		m_pDvmDeviceRef = pDevice;	
	}

	return m_pDvmDeviceRef;
}

CDvmDataset *CAts_RTTaskBatch::FindDataModel(const CString &strID)
{
	GetDvmDevice();
	if (m_pDvmDeviceRef == NULL)
	{
		return NULL;
	}

	return m_pDvmDeviceRef->FindDataset(strID);
}

CAts_RTTaskBatch *CAts_RTTaskBatch::CreateRTTaskBatch(const CString &strName,const CString &strID
													  ,const CString &strGbxml,const CString &strPacketPath)
{
	CString strPath = _P_GetLibraryPath();
	CString strDvmFile = strPath + strID + _T(".xml");
	if (!IsFileExist(strDvmFile))
	{
		return NULL;
	}
	if (!IsFileExist(strGbxml))
	{
		return NULL;
	}

	CAts_RTTaskBatch *pNew = new CAts_RTTaskBatch;
	pNew->m_strName = strName;
	pNew->m_strID = strID;
	pNew->m_strGbxmlFile = strGbxml;
	pNew->m_strDvmFile = strDvmFile;

	CString strTemp;
	strTemp.Format(_T("%s%s_%04d%02d%02d%02d%02d%02d")
		,strPacketPath,strName,pNew->m_tmStartTime.wYear,pNew->m_tmStartTime.wMonth
		,pNew->m_tmStartTime.wDay,pNew->m_tmStartTime.wHour,pNew->m_tmStartTime.wMinute
		,pNew->m_tmStartTime.wSecond);

	pNew->m_strReportPkgFile = strTemp + _T("_Rpt.data");
	pNew->m_strEngineRawPkgFile = strTemp + _T("_EngineRawPkg.data");
	pNew->m_strVmRawPkgFile = strTemp + _T("_VmRawPkg.data");
	pNew->SetState_NotStart();
	return pNew;
}

BOOL CAts_RTTaskBatch::WriteReportData(char *pBuf,long nLen,long &nWritePos)
{
	if (m_oRptFile.m_hFile == INVALID_HANDLE_VALUE)
	{
		if(m_strReportPkgFile.IsEmpty())
		{
			return FALSE;
		}

		CString strPath = GetPathFromFilePathName(m_strReportPkgFile);
		CreateAllDirectories(strPath);

		BOOL bRet = m_oRptFile.Open(m_strReportPkgFile, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive);
		if (!bRet)
		{
			return FALSE;
		}
	}

	nWritePos = (long)m_oRptFile.SeekToEnd();
	m_oRptFile.Write(&nLen,4);
	m_oRptFile.Write(pBuf,nLen);
	m_oRptFile.Flush();
	return TRUE;
}