#include "stdafx.h"
#include "PpDeviceNodeType.h"
#include "DeviceModelXmlKeys.h"

CPpDeviceNodeType::CPpDeviceNodeType()
{
	m_strName=_T("");
	m_strID=_T("");	
	m_nTypeID=0;
	m_nMinOccurs=0;
	m_nMaxOccurs=0;
}

CPpDeviceNodeType::~CPpDeviceNodeType()
{

}

void CPpDeviceNodeType::Init()
{

}

void CPpDeviceNodeType::InitAfterRead()
{
	
}

long CPpDeviceNodeType::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	xml_GetAttibuteValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strMax,oNode,m_nMaxOccurs);
	xml_GetAttibuteValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strMin,oNode,m_nMinOccurs);

	return 0;
}

long CPpDeviceNodeType::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	xml_SetAttributeValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strMax,oElement,m_nMaxOccurs);
	xml_SetAttributeValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strMin,oElement,m_nMinOccurs);

	return 0;


}


BOOL CPpDeviceNodeType::IsEqualOwn(CBaseObject* pObj)
{
	return 0;
}

BOOL CPpDeviceNodeType::CopyOwn(CBaseObject* pDesObj)
{
	if (pDesObj == this)
	{
		return FALSE;
	}

	CExBaseObject::CopyOwn(pDesObj);

	((CPpDeviceNodeType*)pDesObj)->m_nTypeID = m_nTypeID;
	((CPpDeviceNodeType*)pDesObj)->m_nMinOccurs = m_nMinOccurs;
	((CPpDeviceNodeType*)pDesObj)->m_nMaxOccurs = m_nMaxOccurs;

	return TRUE;
}

 CExBaseObject* CPpDeviceNodeType::Clone()
{
	CPpDeviceNodeType *pNew = new CPpDeviceNodeType();

	Copy(pNew);

	return pNew;
}

 CExBaseObject* CPpDeviceNodeType::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
 {
	 return NULL;
 }

 CExBaseObject* CPpDeviceNodeType::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
 {
	 if(strClassID==CDeviceModelXmlKeys::g_pXmlRWKeys->m_strNodeTypeKey)
	 {
		 return new CPpDeviceNodeType();
	 }

	 return NULL;
 }

 void CPpDeviceNodeType::GetAllNodeTypes(CExBaseList &oList)
 {
	 POS pos = GetHeadPosition();
	 CExBaseObject *p = NULL;

	 while (pos != NULL)
	 {
		 p = GetNext(pos);

		 if (p->GetClassID() == DMCLASSID_DEVICENODETYPE)
		 {
			 oList.AddTail(p);
			 ((CPpDeviceNodeType*)p)->GetAllNodeTypes(oList);
		 }

	 }
 }

 BOOL CPpDeviceNodeType::IsLeafNodeType()
 {
	 BOOL bTrue = TRUE;
	 POS pos = GetHeadPosition();
	 CExBaseObject *p = NULL;

	 while (pos != NULL)
	 {
		 p = GetNext(pos);

		 if (p->GetClassID() == DMCLASSID_DEVICENODETYPE)
		 {
			 bTrue = FALSE;
			 break;
		 }
	 }

	 return bTrue;
 }

CPpDeviceNodeDefine* CPpDeviceNodeType::CreateDeviceNodeDefine()
{
	CPpDeviceNodeDefine *pNew = NULL;

	if (IsLeafNodeType())
	{
		pNew = new CPpDeviceNodeDefine();
		CPpDeviceNodeDataDefine *pDataDefine = new CPpDeviceNodeDataDefine();
		pNew->AddNewChild(pDataDefine);
	}
	else
	{
		pNew = new CPpDeviceNodeDefine();
	}

	pNew->m_strNodeType = m_strID;
	pNew->m_strName = m_strName;
	pNew->m_strID = m_strID;
	pNew->InitAfterRead();

	return pNew;
}

