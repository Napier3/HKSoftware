//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGenCfgDataMngrRule.cpp  CIecGenCfgDataMngrRule


#include "stdafx.h"
#include "IecGenCfgDataMngrRule.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecGenCfgDataMngrRule::CIecGenCfgDataMngrRule()
{
	//初始化属性

	//初始化成员变量
	m_pSmvRule = NULL;
	m_pGinRule = NULL;
	m_pGoutRule = NULL;
}

CIecGenCfgDataMngrRule::~CIecGenCfgDataMngrRule()
{
}

long CIecGenCfgDataMngrRule::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strGin_Ch_File_NameKey, oNode, m_strGinChFileName);
	return 0;
}

long CIecGenCfgDataMngrRule::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strGin_Ch_File_NameKey, oElement, m_strGinChFileName);
	return 0;
}

long CIecGenCfgDataMngrRule::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strGinChFileName);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strGinChFileName);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strGinChFileName);
	}
	return 0;
}

void CIecGenCfgDataMngrRule::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *pCurObj = NULL;

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == GENRATECLASSID_CIECGENCFGDATAMNGRRULE_SMV)
		{
			m_pSmvRule = (CIecGenCfgDataMngrRule_SMV*)pCurObj;
		}
		else if (pCurObj->GetClassID() == GENRATECLASSID_CIECGENCFGDATAMNGRRULE_GIN)
		{
			m_pGinRule = (CIecGenCfgDataMngrRule_Gin*)pCurObj;
		}
		else if (pCurObj->GetClassID() == GENRATECLASSID_CIECGENCFGDATAMNGRRULE_GOUT)
		{
			m_pGoutRule = (CIecGenCfgDataMngrRule_Gout*)pCurObj;
		}
	}
}

BOOL CIecGenCfgDataMngrRule::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecGenCfgDataMngrRule *p = (CIecGenCfgDataMngrRule*)pObj;

	if(m_strGinChFileName != p->m_strGinChFileName)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecGenCfgDataMngrRule::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecGenCfgDataMngrRule *p = (CIecGenCfgDataMngrRule*)pDest;

	p->m_strGinChFileName = m_strGinChFileName;
	return TRUE;
}

CBaseObject* CIecGenCfgDataMngrRule::Clone()
{
	CIecGenCfgDataMngrRule *p = new CIecGenCfgDataMngrRule();
	Copy(p);
	return p;
}

CBaseObject* CIecGenCfgDataMngrRule::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecGenCfgDataMngrRule *p = new CIecGenCfgDataMngrRule();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecGenCfgDataMngrRule::CanPaste(UINT nClassID)
{
	if (nClassID == GENRATECLASSID_CIECGENCFGDATAMNGRRULE_SMV)
	{
		return TRUE;
	}

	if (nClassID == GENRATECLASSID_CIECGENCFGDATAMNGRRULE_GIN)
	{
		return TRUE;
	}

	if (nClassID == GENRATECLASSID_CIECGENCFGDATAMNGRRULE_GOUT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIecGenCfgDataMngrRule::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecGenCfgDataMngrRule_SMVKey)
	{
		pNew = new CIecGenCfgDataMngrRule_SMV();
	}
	else if (strClassID == pXmlKeys->m_strCIecGenCfgDataMngrRule_GinKey)
	{
		pNew = new CIecGenCfgDataMngrRule_Gin();
	}
	else if (strClassID == pXmlKeys->m_strCIecGenCfgDataMngrRule_GoutKey)
	{
		pNew = new CIecGenCfgDataMngrRule_Gout();
	}

	return pNew;
}

CExBaseObject* CIecGenCfgDataMngrRule::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GENRATECLASSID_CIECGENCFGDATAMNGRRULE_SMV)
	{
		pNew = new CIecGenCfgDataMngrRule_SMV();
	}
	else if (nClassID == GENRATECLASSID_CIECGENCFGDATAMNGRRULE_GIN)
	{
		pNew = new CIecGenCfgDataMngrRule_Gin();
	}
	else if (nClassID == GENRATECLASSID_CIECGENCFGDATAMNGRRULE_GOUT)
	{
		pNew = new CIecGenCfgDataMngrRule_Gout();
	}

	return pNew;
}
long CIecGenCfgDataMngrRule::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	return 0;
}

long CIecGenCfgDataMngrRule::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	return 0;
}

CIecGenCfgDataMngrRule_SMV* CIecGenCfgDataMngrRule::GetSmvRule()
{
	if (m_pSmvRule != NULL)
	{
		return m_pSmvRule;
	}

	m_pSmvRule = (CIecGenCfgDataMngrRule_SMV*)FindByClassID(GENRATECLASSID_CIECGENCFGDATAMNGRRULE_SMV);
	return m_pSmvRule;
}

CIecGenCfgDataMngrRule_Gin* CIecGenCfgDataMngrRule::GetGinRule()
{
	if (m_pGinRule != NULL)
	{
		return m_pGinRule;
	}

	m_pGinRule = (CIecGenCfgDataMngrRule_Gin*)FindByClassID(GENRATECLASSID_CIECGENCFGDATAMNGRRULE_GIN);
	return m_pGinRule;
}

CIecGenCfgDataMngrRule_Gout* CIecGenCfgDataMngrRule::GetGoutRule()
{
	if (m_pGoutRule != NULL)
	{
		return m_pGoutRule;
	}

	m_pGoutRule = (CIecGenCfgDataMngrRule_Gout*)FindByClassID(GENRATECLASSID_CIECGENCFGDATAMNGRRULE_GOUT);
	return m_pGoutRule;
}