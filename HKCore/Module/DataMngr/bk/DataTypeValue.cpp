// DataTypeValue.cpp : CDataTypeValue 的实现

#include "stdafx.h"
#include "DataTypeValue.h"


// CDataTypeValue


STDMETHODIMP CDataTypeValue::get_Name(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strName.Copy();
	return S_OK;
}

STDMETHODIMP CDataTypeValue::put_Name(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strName = newVal;
	return S_OK;
}

STDMETHODIMP CDataTypeValue::get_ID(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strID.Copy();
	return S_OK;
}

STDMETHODIMP CDataTypeValue::put_ID(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strID = newVal;
	return S_OK;
}

STDMETHODIMP CDataTypeValue::get_Index(LONG* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_nIndex;
	return S_OK;
}

STDMETHODIMP CDataTypeValue::put_Index(LONG newVal)
{
	// TODO: 在此添加实现代码
	m_nIndex  = newVal;
	return S_OK;
}
STDMETHODIMP CDataTypeValue::XMLWrite(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	// TODO: 在此添加实现代码
	CDataTypeXMLRWKeys* pXmlRWKeys = CDataTypeXMLRWKeys::FromIDispatch(pIXMLKeys);
	ATLASSERT(pXmlRWKeys!=NULL);
	MSXML::IXMLDOMElementPtr oNode = NULL;
	pIXMLElement->QueryInterface(__uuidof(MSXML::IXMLDOMElementPtr),(void**)&oNode);
	ATLASSERT(oNode!=NULL);
	_XmlWrite(oNode,pXmlRWKeys);
	return S_OK;
}

STDMETHODIMP CDataTypeValue::XMLRead(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	// TODO: 在此添加实现代码
	CDataTypeXMLRWKeys* pXmlRWKeys = CDataTypeXMLRWKeys::FromIDispatch(pIXMLKeys);
	ATLASSERT(pXmlRWKeys!=NULL);
	MSXML::IXMLDOMElementPtr oNode = NULL;
	pIXMLElement->QueryInterface(__uuidof(MSXML::IXMLDOMElementPtr),(void**)&oNode);
	ATLASSERT(oNode!=NULL);
	_XmlRead(oNode,pXmlRWKeys);
	return S_OK;
}

long CDataTypeValue::_XmlReadOwn(const MSXML::IXMLDOMNodePtr &oNode, CDataTypeXMLRWKeys *pXmlRWKeys)
{
	BSTR strIDKey = pXmlRWKeys->m_strValueIDKey;
	xml_GetAttibuteValue(strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlRWKeys->m_strValueNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlRWKeys->m_strValueIndexKey, oNode, m_nIndex);
	return 0;
}

long CDataTypeValue::_XmlReadChildren(const MSXML::IXMLDOMNodeListPtr &oNodes, CDataTypeXMLRWKeys *pXmlRWKeys)
{
	return 0;
}


long CDataTypeValue::_XmlWriteOwn(MSXML::IXMLDOMElementPtr &oNode, CDataTypeXMLRWKeys *pXmlRWKeys)
{
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strValueIDKey,(_bstr_t)m_strID);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strValueNameKey,(_bstr_t)m_strName);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strValueIndexKey,m_nIndex);
	return 0;
}

long CDataTypeValue::_XmlWriteChildren(MSXML::IXMLDOMElementPtr &oParent, CDataTypeXMLRWKeys *pXmlRWKeys)
{
	return 0;
}
