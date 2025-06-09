//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Bout.cpp  CBout


#include "stdafx.h"
#include "Bout.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CBout::CBout()
{
	//初始化属性

	//初始化成员变量
}

CBout::~CBout()
{
}

long CBout::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strApp_ChKey, oNode, m_strAppCh);
	return 0;
}

long CBout::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strApp_ChKey, oElement, m_strAppCh);
	return 0;
}

long CBout::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CBout::InitAfterRead()
{
}

BOOL CBout::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CBout *p = (CBout*)pObj;

	if(m_strAppCh != p->m_strAppCh)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CBout::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CBout *p = (CBout*)pDest;

	p->m_strAppCh = m_strAppCh;
	return TRUE;
}

CBaseObject* CBout::Clone()
{
	CBout *p = new CBout();
	Copy(p);
	return p;
}

CBaseObject* CBout::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CBout *p = new CBout();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CBout::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CKEYS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CBout::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCKeysKey)
	{
		pNew = new CKeys();
	}

	return pNew;
}

CExBaseObject* CBout::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CKEYS)
	{
		pNew = new CKeys();
	}

	return pNew;
}
long CBout::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strApp_ChKey, m_strAppCh);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	return 0;
}

long CBout::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strApp_ChKey, m_strAppCh);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	return 0;
}

CExBaseObject* CBout::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CKeys();

	return pNew;
}


BOOL CBout::SetChMap(CIecCfgGoutData *pIecCfgGoutData)
{
	CKeys *pKeys = (CKeys*)FindByClassID(MNGRCLASSID_CKEYS);

	if (pKeys == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前GOOSE发布通道(%s)缺少关键字描述对象."),m_strID);
		return FALSE;
	}

	CStringArray astrDesc;
	pKeys->GetKeys(astrDesc);

	CIecCfgDataGooseChBase* pCfgGooseDataCh = NULL;
	ASSERT(pIecCfgGoutData->m_pCfgChs);
	POS pos = pIecCfgGoutData->m_pCfgChs->GetHeadPosition();

	while(pos)
	{
		pCfgGooseDataCh = (CIecCfgDataGooseChBase*)pIecCfgGoutData->m_pCfgChs->GetNext(pos);

		for (int nIndex = 0; nIndex < astrDesc.GetCount(); nIndex++)
		{
			if (pCfgGooseDataCh->m_strName.Find(astrDesc[nIndex]) != -1)
			{
				pCfgGooseDataCh->m_strAppChID = m_strAppCh;
				pIecCfgGoutData->m_nUseFlag = 1;
				return TRUE;
			}
		}
	}

	return FALSE;
}
