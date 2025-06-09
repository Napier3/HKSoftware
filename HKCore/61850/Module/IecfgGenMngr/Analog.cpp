//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Analog.cpp  CAnalog


#include "stdafx.h"
#include "Analog.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAnalog::CAnalog()
{
	//初始化属性

	//初始化成员变量
}

CAnalog::~CAnalog()
{
}

long CAnalog::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCh_TypeKey, oNode, m_strChType);
	return 0;
}

long CAnalog::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCh_TypeKey, oElement, m_strChType);
	return 0;
}

long CAnalog::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strChType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strChType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strChType);
	}
	return 0;
}

void CAnalog::InitAfterRead()
{
}

BOOL CAnalog::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAnalog *p = (CAnalog*)pObj;

	if(m_strChType != p->m_strChType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAnalog::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAnalog *p = (CAnalog*)pDest;

	p->m_strChType = m_strChType;
	return TRUE;
}

CBaseObject* CAnalog::Clone()
{
	CAnalog *p = new CAnalog();
	Copy(p);
	return p;
}

CBaseObject* CAnalog::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAnalog *p = new CAnalog();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAnalog::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CKEYS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAnalog::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCKeysKey)
	{
		pNew = new CKeys();
	}

	return pNew;
}

CExBaseObject* CAnalog::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CKEYS)
	{
		pNew = new CKeys();
	}

	return pNew;
}
long CAnalog::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strCh_TypeKey, m_strChType);
	pRecordset->GetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	return 0;
}

long CAnalog::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strCh_TypeKey, m_strChType);
	pRecordset->SetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	return 0;
}

CExBaseObject* CAnalog::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CKeys();

	return pNew;
}

BOOL CAnalog::SetChMap(CIecCfgChsBase *pIecCfgChsBase)
{
	CKeys *pKeys = (CKeys*)FindByClassID(MNGRCLASSID_CKEYS);

	if (pKeys == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前模拟量通道(%s)缺少关键字描述对象."),m_strID);
		return FALSE;
	}

	CStringArray astrDesc;
	pKeys->GetKeys(astrDesc);

	CIecCfgDataSmvChBase* pCfgSmvDataCh = NULL;
	POS pos = pIecCfgChsBase->GetHeadPosition();

	while(pos)
	{
		pCfgSmvDataCh = (CIecCfgDataSmvChBase*)pIecCfgChsBase->GetNext(pos);
		
		for (int nIndex = 0; nIndex < astrDesc.GetCount(); nIndex++)
		{
 			if (pCfgSmvDataCh->m_strName.Find(astrDesc[nIndex]) != -1)
 			{
				pCfgSmvDataCh->m_strAppChID = m_strID;
				pCfgSmvDataCh->m_strChType = m_strChType;
				CIecCfg92Data *pIecCfg92Data = (CIecCfg92Data*)pCfgSmvDataCh->GetAncestor(CFGCLASSID_CIECCFG92DATA);
				ASSERT(pIecCfg92Data);
				pIecCfg92Data->m_nUseFlag = 1;
				return TRUE;
 			}
		}
	}

	return FALSE;
}