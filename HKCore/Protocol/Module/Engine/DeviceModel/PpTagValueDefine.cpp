#include "stdafx.h"
#include "PpTagValueDefine.h"

CPpTagValueDefine::CPpTagValueDefine()
{
	m_strID=L"val";
	m_strValue=L"";
}

CPpTagValueDefine::~CPpTagValueDefine()
{

}

void CPpTagValueDefine::Init()
{

}

void CPpTagValueDefine::InitAfterRead()
{
	
}

//long CTTag::BinarySerializeOwn(SysTool::IBinarySerialBufferPtr &oBinaryBuff)
//{
//	return 0;
//}

long CPpTagValueDefine::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	_bstr_t bstrText=oNode->Gettext();
	m_strValue=bstrText.operator char* ();


	m_strName = m_strID + _T(":") + m_strValue;


	return 0;
}

long CPpTagValueDefine::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	oElement->put_text((_bstr_t)m_strValue);
	return 0;
}

BOOL CPpTagValueDefine::IsEqualOwn(CBaseObject* pObj)
{
	if(!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}
	
	CPpTagValueDefine *pTTag=(CPpTagValueDefine*)pObj;

	if(pTTag->m_strValue!=m_strValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPpTagValueDefine::CopyOwn(CBaseObject* pDesObj)
{
	if(!CExBaseObject::CopyOwn(pDesObj))
	{
		return FALSE;
	}

	((CPpTagValueDefine*)pDesObj)->m_strValue=m_strValue;

	return TRUE;
}

CExBaseObject* CPpTagValueDefine::Clone()
{
	CPpTagValueDefine *pVal=new CPpTagValueDefine;

	Copy(pVal);

	return pVal;
}


// CExBaseObject *CPpTagValueDefine::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
// {
// 	return NULL;
// }
// 
// CExBaseObject *CPpTagValueDefine::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
// {
// 	return NULL;
// }

void CPpTagValueDefine::SetValue(const CString &strValue)
{
	m_strValue = strValue;
	m_strName = m_strID + _T(":") + m_strValue;
}

