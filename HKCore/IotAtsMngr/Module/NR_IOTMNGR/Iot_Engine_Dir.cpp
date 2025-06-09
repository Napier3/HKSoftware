//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Engine_Dir.cpp  CIot_Engine_Dir


#include "stdafx.h"
#include "Iot_Engine_Dir.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Engine_Dir::CIot_Engine_Dir()
{
	//初始化属性
	m_nIndex_Engine_Dir = 0;
	m_nParent_Index = 0;
	::GetLocalTime(&m_tmDir_Name);
	::GetLocalTime(&m_tmCreate_Time);

	//初始化成员变量
}

CIot_Engine_Dir::~CIot_Engine_Dir()
{
}

long CIot_Engine_Dir::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Engine_DirKey, oNode, m_nIndex_Engine_Dir);
	xml_GetAttibuteValue(pXmlKeys->m_strParent_IndexKey, oNode, m_nParent_Index);
	xml_GetAttibuteValue(pXmlKeys->m_strDir_NameKey, oNode, m_tmDir_Name);
	xml_GetAttibuteValue(pXmlKeys->m_strCreate_TimeKey, oNode, m_tmCreate_Time);
	return 0;
}

long CIot_Engine_Dir::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Engine_DirKey, oElement, m_nIndex_Engine_Dir);
	xml_SetAttributeValue(pXmlKeys->m_strParent_IndexKey, oElement, m_nParent_Index);
	xml_SetAttributeValue(pXmlKeys->m_strDir_NameKey, oElement, m_tmDir_Name);
	xml_SetAttributeValue(pXmlKeys->m_strCreate_TimeKey, oElement, m_tmCreate_Time);
	return 0;
}

long CIot_Engine_Dir::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Engine_Dir);
		BinarySerializeCalLen(oBinaryBuffer, m_nParent_Index);
		BinarySerializeCalLen(oBinaryBuffer, m_tmDir_Name);
		BinarySerializeCalLen(oBinaryBuffer, m_tmCreate_Time);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Engine_Dir);
		BinarySerializeRead(oBinaryBuffer, m_nParent_Index);
		BinarySerializeRead(oBinaryBuffer, m_tmDir_Name);
		BinarySerializeRead(oBinaryBuffer, m_tmCreate_Time);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Engine_Dir);
		BinarySerializeWrite(oBinaryBuffer, m_nParent_Index);
		BinarySerializeWrite(oBinaryBuffer, m_tmDir_Name);
		BinarySerializeWrite(oBinaryBuffer, m_tmCreate_Time);
	}
	return 0;
}

void CIot_Engine_Dir::InitAfterRead()
{
}

BOOL CIot_Engine_Dir::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Engine_Dir *p = (CIot_Engine_Dir*)pObj;

	if(m_nIndex_Engine_Dir != p->m_nIndex_Engine_Dir)
	{
		return FALSE;
	}

	if(m_nParent_Index != p->m_nParent_Index)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_Engine_Dir::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Engine_Dir *p = (CIot_Engine_Dir*)pDest;

	p->m_nIndex_Engine_Dir = m_nIndex_Engine_Dir;
	p->m_nParent_Index = m_nParent_Index;
	p->m_tmDir_Name = m_tmDir_Name;
	p->m_tmCreate_Time = m_tmCreate_Time;
	return TRUE;
}

CBaseObject* CIot_Engine_Dir::Clone()
{
	CIot_Engine_Dir *p = new CIot_Engine_Dir();
	Copy(p);
	return p;
}

CBaseObject* CIot_Engine_Dir::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Engine_Dir *p = new CIot_Engine_Dir();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Engine_Dir::CanPaste(UINT nClassID)
{
	if (nClassID == )
	{
		return TRUE;
	}

	if (nClassID == IOTCLASSID_CIOT_ENGINE)
	{
		return TRUE;
	}

	if (nClassID == IOTCLASSID_CIOT_DVMFILE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Engine_Dir::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_EngineFolderKey)
	{
		pNew = new CIot_EngineFolder();
	}
	else if (strClassID == pXmlKeys->m_strCIot_EngineKey)
	{
		pNew = new CIot_Engine();
	}
	else if (strClassID == pXmlKeys->m_strCIot_DvmFileKey)
	{
		pNew = new CIot_DvmFile();
	}

	return pNew;
}

CExBaseObject* CIot_Engine_Dir::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == )
	{
		pNew = new CIot_EngineFolder();
	}
	else if (nClassID == IOTCLASSID_CIOT_ENGINE)
	{
		pNew = new CIot_Engine();
	}
	else if (nClassID == IOTCLASSID_CIOT_DVMFILE)
	{
		pNew = new CIot_DvmFile();
	}

	return pNew;
}
long CIot_Engine_Dir::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Engine_DirKey, m_nIndex_Engine_Dir);
	pRecordset->GetFieldValue(pXmlKeys->m_strParent_IndexKey, m_nParent_Index);
	pRecordset->GetFieldValue(pXmlKeys->m_strDir_NameKey, m_tmDir_Name);
	pRecordset->GetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

long CIot_Engine_Dir::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Engine_DirKey, m_nIndex_Engine_Dir);
	pRecordset->SetFieldValue(pXmlKeys->m_strParent_IndexKey, m_nParent_Index);
	pRecordset->SetFieldValue(pXmlKeys->m_strDir_NameKey, m_tmDir_Name);
	pRecordset->SetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

