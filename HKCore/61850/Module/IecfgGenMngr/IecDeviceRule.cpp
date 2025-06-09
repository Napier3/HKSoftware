//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecDeviceRule.cpp  CIecDeviceRule


#include "stdafx.h"
#include "IecDeviceRule.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecDeviceRule::CIecDeviceRule()
{
	//初始化属性

	//初始化成员变量
}

CIecDeviceRule::~CIecDeviceRule()
{
}

long CIecDeviceRule::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIecfgKey, oNode, m_strIecfg);
	return 0;
}

long CIecDeviceRule::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIecfgKey, oElement, m_strIecfg);
	return 0;
}

long CIecDeviceRule::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strIecfg);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strIecfg);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strIecfg);
	}
	return 0;
}

void CIecDeviceRule::InitAfterRead()
{
}

BOOL CIecDeviceRule::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecDeviceRule *p = (CIecDeviceRule*)pObj;

	if(m_strIecfg != p->m_strIecfg)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecDeviceRule::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecDeviceRule *p = (CIecDeviceRule*)pDest;

	p->m_strIecfg = m_strIecfg;
	return TRUE;
}

CBaseObject* CIecDeviceRule::Clone()
{
	CIecDeviceRule *p = new CIecDeviceRule();
	Copy(p);
	return p;
}

CBaseObject* CIecDeviceRule::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecDeviceRule *p = new CIecDeviceRule();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecDeviceRule::CanPaste(UINT nClassID)
{
	if (nClassID == GENRATECLASSID_CIECGENCFGDATAMNGRRULE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIecDeviceRule::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecGenCfgDataMngrRuleKey)
	{
		pNew = new CIecGenCfgDataMngrRule();
	}

	return pNew;
}

CExBaseObject* CIecDeviceRule::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GENRATECLASSID_CIECGENCFGDATAMNGRRULE)
	{
		pNew = new CIecGenCfgDataMngrRule();
	}

	return pNew;
}
long CIecDeviceRule::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strIecfgKey, m_strIecfg);
	return 0;
}

long CIecDeviceRule::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strIecfgKey, m_strIecfg);
	return 0;
}

CExBaseObject* CIecDeviceRule::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIecGenCfgDataMngrRule();

	return pNew;
}

