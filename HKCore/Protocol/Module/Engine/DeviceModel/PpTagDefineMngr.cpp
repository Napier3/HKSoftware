#include "stdafx.h"
#include "PpTagDefineMngr.h"
#include"PpTagDefine.h"
#include "DeviceClassIDDefine.h"

CPpTagDefineMngr::CPpTagDefineMngr()
{

	m_strName = "tags";
	m_strID = m_strName;

}

CPpTagDefineMngr::~CPpTagDefineMngr()
{

}

void CPpTagDefineMngr::Init()
{

}

void CPpTagDefineMngr::InitAfterRead()
{
	
}

//long BinarySerializeOwn(SysTool::IBinarySerialBufferPtr &oBinaryBuff)
//{
//	return 0;
//}

long CPpTagDefineMngr::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	
	return 0;
}

long CPpTagDefineMngr::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}


BOOL CPpTagDefineMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}
	else if (!IsEqualChildren(pObj))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPpTagDefineMngr::CopyOwn(CBaseObject* pDesObj)
{
	if (pDesObj == this)
	{
		return FALSE;
	}

	CExBaseObject::CopyOwn(pDesObj);

	return TRUE;	
}

CExBaseObject* CPpTagDefineMngr::Clone()
{
	CPpTagDefineMngr *pTTags= new CPpTagDefineMngr;

	Copy(pTTags);

	return pTTags;
}


CExBaseObject* CPpTagDefineMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	if(nClassID==DMCLASSID_TAGDEFINE)
	{
		return new CPpTagDefine(); 
	}

	return NULL;
}

CExBaseObject* CPpTagDefineMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTagKey)
	{
		return new CPpTagDefine();
	}

	return NULL;
}

CPpTags *CPpTagDefineMngr::CreateTags()
{
	//创建CPpTags
	CPpTag *pNewTag = NULL;
	CPpTags *pNewTags = NULL;
	pNewTags = new CPpTags();
 	pNewTags->m_strID = CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTagsKey;
	pNewTags->m_strName = CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTagsKey;
	ASSERT(pNewTags != NULL);

	//遍历PpTagDefineMngr，逐项创建CPpTag
	CPpTagDefine *pTagDefine = NULL;
	POS pos = GetHeadPosition();
	BOOL bAddToTail = TRUE;

	while (pos != NULL)
	{
		pTagDefine = (CPpTagDefine *)GetNext(pos);
		ASSERT(pTagDefine != NULL);

		if (pTagDefine != NULL)
		{
			pTagDefine->CreateTag(&pNewTags);
		}
	}

	return pNewTags;
}

CPpTagDefine* CPpTagDefineMngr::NewTagDef(CPpTagDefine *pSrcTagDef)
{
	CPpTagDefine *pNew = NULL;

	if (pSrcTagDef == NULL)
	{
		pNew = new CPpTagDefine();
	}
	else
	{
		pNew = (CPpTagDefine*)pSrcTagDef->Clone();
	}

	AddNewChild(pNew);

	return pNew;
}

CPpTagDefine* CPpTagDefineMngr::GetIndexTagDef()
{
	CPpTagDefine *pFind = NULL;

	pFind = (CPpTagDefine*)FindByID(CString(CDeviceModelXmlKeys::DmDataTag_Index()));

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = (CPpTagDefine*)FindByID(CString(CDeviceModelXmlKeys::DmDataTag_ItemIndex()));

	return pFind;
}

