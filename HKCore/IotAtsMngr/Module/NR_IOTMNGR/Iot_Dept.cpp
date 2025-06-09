//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Dept.cpp  CIot_Dept


#include "stdafx.h"
#include "Iot_Dept.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Dept::CIot_Dept()
{
	//初始化属性
	m_nIndex_Dept = 0;
	m_nIndex_Parent_Dept = 0;

	//初始化成员变量
	m_pIot_Benchs = NULL;
	m_pIot_Users = NULL;
}

CIot_Dept::~CIot_Dept()
{
}

long CIot_Dept::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeptKey, oNode, m_nIndex_Dept);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Parent_DeptKey, oNode, m_nIndex_Parent_Dept);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	return 0;
}

long CIot_Dept::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeptKey, oElement, m_nIndex_Dept);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Parent_DeptKey, oElement, m_nIndex_Parent_Dept);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	return 0;
}

long CIot_Dept::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Parent_Dept);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Parent_Dept);
		BinarySerializeRead(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Parent_Dept);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
	}
	return 0;
}

void CIot_Dept::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == IOTCLASSID_CIOT_BENCHS)
		{
			m_pIot_Benchs = (CIot_Benchs*)p;
		}
		else if (nClassID == IOTCLASSID_CIOT_USERS)
		{
			m_pIot_Users = (CIot_Users*)p;
		}
	}

	if (m_pIot_Benchs == NULL)
	{
		m_pIot_Benchs = (CIot_Benchs*)AddNewChild(new CIot_Benchs());
	}

	if (m_pIot_Users == NULL)
	{
		m_pIot_Users = (CIot_Users*)AddNewChild(new CIot_Users());
	}

}

BOOL CIot_Dept::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Dept *p = (CIot_Dept*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_nIndex_Dept != p->m_nIndex_Dept)
	{
		return FALSE;
	}

	if(m_nIndex_Parent_Dept != p->m_nIndex_Parent_Dept)
	{
		return FALSE;
	}

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_Dept::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Dept *p = (CIot_Dept*)pDest;

	p->m_strName = m_strName;
	p->m_nIndex_Dept = m_nIndex_Dept;
	p->m_nIndex_Parent_Dept = m_nIndex_Parent_Dept;
	p->m_strType = m_strType;
	return TRUE;
}

CBaseObject* CIot_Dept::Clone()
{
	CIot_Dept *p = new CIot_Dept();
	Copy(p);
	return p;
}

CBaseObject* CIot_Dept::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Dept *p = new CIot_Dept();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Dept::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_BENCHS)
	{
		return TRUE;
	}

	if (nClassID == IOTCLASSID_CIOT_USERS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Dept::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_BenchsKey)
	{
		pNew = new CIot_Benchs();
	}
	else if (strClassID == pXmlKeys->m_strCIot_UsersKey)
	{
		pNew = new CIot_Users();
	}

	return pNew;
}

CExBaseObject* CIot_Dept::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_BENCHS)
	{
		pNew = new CIot_Benchs();
	}
	else if (nClassID == IOTCLASSID_CIOT_USERS)
	{
		pNew = new CIot_Users();
	}

	return pNew;
}
long CIot_Dept::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeptKey, m_nIndex_Dept);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Parent_DeptKey, m_nIndex_Parent_Dept);
	pRecordset->GetFieldValue(pXmlKeys->m_strTypeKey, m_strType);
	return 0;
}

long CIot_Dept::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeptKey, m_nIndex_Dept);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Parent_DeptKey, m_nIndex_Parent_Dept);
	pRecordset->SetFieldValue(pXmlKeys->m_strTypeKey, m_strType);
	return 0;
}

