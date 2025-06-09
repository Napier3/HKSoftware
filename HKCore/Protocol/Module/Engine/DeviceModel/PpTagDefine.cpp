#include "stdafx.h"
#include "PpTagDefine.h"

CPpTagDefine::CPpTagDefine()
{
	m_strIsKey="";
	m_strType="";
	m_strCtrlType = L"";
}

CPpTagDefine::~CPpTagDefine()
{

}

void CPpTagDefine::Init()
{

}

void CPpTagDefine::InitAfterRead()
{
	
}

//long CTTag::BinarySerializeOwn(SysTool::IBinarySerialBufferPtr &oBinaryBuff)
//{
//	return 0;
//}

long CPpTagDefine::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strIsKeyKey, oNode, m_strIsKey);
	xml_GetAttibuteValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strDataTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strCtrlTypeKey, oNode, m_strCtrlType);

	return 0;
}

long CPpTagDefine::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	xml_SetAttributeValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strIsKeyKey, oElement, m_strIsKey);
	xml_SetAttributeValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strDataTypeKey, oElement, m_strType);
	xml_SetAttributeValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strCtrlTypeKey, oElement, m_strCtrlType);

	return 0;
}

BOOL CPpTagDefine::IsEqualOwn(CBaseObject* pObj)
{
	if(!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}
	
	CPpTagDefine *pTTag=(CPpTagDefine*)pObj;

	if((pTTag->m_strIsKey!=m_strIsKey) || (pTTag->m_strType!=m_strType))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPpTagDefine::CopyOwn(CBaseObject* pDesObj)
{
	if (pDesObj == this)
	{
		return FALSE;
	}

	CExBaseObject::CopyOwn(pDesObj);

	((CPpTagDefine*)pDesObj)->m_strType=m_strType;
	((CPpTagDefine*)pDesObj)->m_strIsKey=m_strIsKey;
	((CPpTagDefine*)pDesObj)->m_strCtrlType=m_strCtrlType;

	return TRUE;
}

CExBaseObject* CPpTagDefine::Clone()
{
	CPpTagDefine *pTTag=new CPpTagDefine;

	Copy(pTTag);	

	return pTTag;
}


CExBaseObject *CPpTagDefine::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CPpTagValueDefine *pTagVal = NULL;

	if (strClassID == CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTagValueKey)
	{
		pTagVal = new CPpTagValueDefine();
		pTagVal->m_strID = strClassID;


		pTagVal->m_strName = strClassID;

	}

	return pTagVal;
}

CExBaseObject *CPpTagDefine::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return NULL;
}

void CPpTagDefine::CreateTag(CPpTags **pNewTags)
{
	ASSERT(pNewTags != NULL);
	CPpTag *pNewTag = NULL;
	CPpTagValueDefine *pTagVal = NULL;
	BOOL bAddTail = TRUE;
	long nCount = 0;
	nCount = GetCount();

	if (nCount > 0)
	{
		for (long nIndex = 0; nIndex < nCount;nIndex++)
		{
			pTagVal = (CPpTagValueDefine *)GetAt(nIndex);
			ASSERT(pTagVal != NULL);

			//´´½¨CPpTag
			pNewTag = (CPpTag *)(*pNewTags)->CreateNewChild(m_strID, bAddTail, NULL);
			pNewTag->m_strValue = pTagVal->m_strValue;
			(*pNewTags)->AddTail(pNewTag);
			pNewTag->SetParent(*pNewTags);
		}
	}
	else
	{
		pNewTag = (CPpTag *)(*pNewTags)->CreateNewChild(m_strID, bAddTail, NULL);
		(*pNewTags)->AddTail(pNewTag);
		pNewTag->SetParent(*pNewTags);
	}
}

CPpTagValueDefine* CPpTagDefine::FindTagValue(const CString &strValue)
{
	POS pos = GetHeadPosition();
	CPpTagValueDefine *pFind = NULL;
	CPpTagValueDefine *p = NULL;

	while (pos != NULL)
	{
		p = (CPpTagValueDefine *)GetNext(pos);

		if (p->m_strValue == strValue)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CPpTagValueDefine* CPpTagDefine::AddTagValue(const CString &strValue)
{
	CPpTagValueDefine *pValue = FindTagValue(strValue);

	if (pValue != NULL)
	{
		return pValue;
	}

	pValue = new CPpTagValueDefine();
	pValue->SetValue(strValue);
	AddNewChild(pValue);

	return pValue;
}
