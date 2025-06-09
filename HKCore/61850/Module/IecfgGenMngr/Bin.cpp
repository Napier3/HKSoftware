//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Bin.cpp  CBin


#include "stdafx.h"
#include "Bin.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CBin::CBin()
{
	//初始化属性

	//初始化成员变量
}

CBin::~CBin()
{
}

long CBin::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strApp_ChKey, oNode, m_strAppCh);
	return 0;
}

long CBin::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strApp_ChKey, oElement, m_strAppCh);
	return 0;
}

long CBin::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strAppCh);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strAppCh);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strAppCh);
	}
	return 0;
}

void CBin::InitAfterRead()
{
}

BOOL CBin::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CBin *p = (CBin*)pObj;

	if(m_strAppCh != p->m_strAppCh)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CBin::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CBin *p = (CBin*)pDest;

	p->m_strAppCh = m_strAppCh;
	return TRUE;
}

CBaseObject* CBin::Clone()
{
	CBin *p = new CBin();
	Copy(p);
	return p;
}

CBaseObject* CBin::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CBin *p = new CBin();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CBin::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CKEYS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CBin::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCKeysKey)
	{
		pNew = new CKeys();
	}

	return pNew;
}

CExBaseObject* CBin::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CKEYS)
	{
		pNew = new CKeys();
	}

	return pNew;
}
long CBin::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strApp_ChKey, m_strAppCh);
	pRecordset->GetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	return 0;
}

long CBin::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strApp_ChKey, m_strAppCh);
	pRecordset->SetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	return 0;
}

CExBaseObject* CBin::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CKeys();

	return pNew;
}

BOOL CBin::SetChMap(CIecCfgGinData *pIecCfgGinData)
{
	CKeys *pKeys = (CKeys*)FindByClassID(MNGRCLASSID_CKEYS);

	if (pKeys == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前GOOSE订阅通道(%s)缺少关键字描述对象."),m_strID);
		return FALSE;
	}

	CStringArray astrDesc;
	pKeys->GetKeys(astrDesc);

	CIecCfgDataGooseChBase* pCfgGooseDataCh = NULL;
	ASSERT(pIecCfgGinData->m_pCfgChs);
	POS pos = pIecCfgGinData->m_pCfgChs->GetHeadPosition();

	while(pos)
	{
		pCfgGooseDataCh = (CIecCfgDataGooseChBase*)pIecCfgGinData->m_pCfgChs->GetNext(pos);

		for (int nIndex = 0; nIndex < astrDesc.GetCount(); nIndex++)
		{
			if (pCfgGooseDataCh->m_strName.Find(astrDesc[nIndex]) != -1)
			{
				pCfgGooseDataCh->m_strAppChID = m_strAppCh;
				pIecCfgGinData->m_nUseFlag = 1;
				return TRUE;
			}
		}
	}

	return FALSE;
}