// Tag.cpp : CTag 的实现

#include "stdafx.h"
#include "Tag.h"
#include "BinarySerializeGlobalDefine.h"

// CTag
const WCHAR* CTag::g_pstrKeyID = L"ID";
const WCHAR* CTag::g_pstrKeyDataType = L"DataType";
const WCHAR* CTag::g_pstrKeyValue = L"Value";

STDMETHODIMP CTag::get_ID(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strID.Copy();
	return S_OK;
}

STDMETHODIMP CTag::put_ID(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strID = newVal;
	return S_OK;
}

STDMETHODIMP CTag::get_DataType(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strDataType.Copy();
	return S_OK;
}

STDMETHODIMP CTag::put_DataType(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strDataType = newVal;
	return S_OK;
}

STDMETHODIMP CTag::get_Value(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strValue.Copy();
	return S_OK;
}

STDMETHODIMP CTag::put_Value(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strValue = newVal;
	return S_OK;
}

long CTag::_XmlReadOwn(const MSXML::IXMLDOMNodePtr &oNode, CValueXMLRWKeys *pXmlRWKeys)
{
	xml_GetAttibuteValue((BSTR)g_pstrKeyID, oNode, m_strID);
	xml_GetAttibuteValue((BSTR)g_pstrKeyDataType, oNode, m_strDataType);
	xml_GetAttibuteValue((BSTR)g_pstrKeyValue,oNode,m_strValue);

	return 0;
}

long CTag::_XmlReadChildren(const MSXML::IXMLDOMNodeListPtr  &oParent, CValueXMLRWKeys *pXmlRWKeys)
{
	return 0;
}

long CTag::_XmlWriteOwn(MSXML::IXMLDOMElementPtr &oNode, CValueXMLRWKeys *pXmlRWKeys)
{
	oNode->setAttribute((_bstr_t)g_pstrKeyID,(_bstr_t)m_strID);
	oNode->setAttribute((_bstr_t)g_pstrKeyDataType,(_bstr_t)m_strDataType);
	_variant_t vValue(m_strValue);
	oNode->setAttribute((_bstr_t)g_pstrKeyValue,vValue);

	return 0;
}

long CTag::_XmlWriteChildren(MSXML::IXMLDOMElementPtr &oParent, CValueXMLRWKeys *pXmlRWKeys)
{
	return 0;
}

BOOL CTag::_Copy(CTag* pTag)
{
	ATLASSERT((pTag!=this)&&(pTag!=NULL));
	m_strID = pTag->m_strID;
	m_strValue = pTag->m_strValue;
	m_strDataType = pTag->m_strDataType;

	return 0;
}

long  CTag::_IsEqual(CTag* pTag)
{
	ATLASSERT(pTag != NULL);
	if(pTag == NULL)
		return 0;

	if(pTag->m_strID == m_strID && pTag->m_strValue == m_strValue && pTag->m_strDataType == m_strDataType)	//这里不比较Name
		return 1;
	else 
		return 0;
}

STDMETHODIMP CTag::BinarySerialize(IDispatch* pIBinaryBuffer)
{
	// TODO: 在此添加实现代码
	ATLASSERT(pIBinaryBuffer!=NULL);
	IBinarySerialBuffer* pIBuffer = (IBinarySerialBuffer*)pIBinaryBuffer;

	LONG nRetSize,nRetRead,nRetWrite;

	pIBuffer->IsReadMode(&nRetRead);
	pIBuffer->IsWriteMode(&nRetWrite);
	pIBuffer->IsCalSizeMode(&nRetSize);

	if (nRetSize)
	{
		ST_BinarySerializeCalLen(pIBuffer, m_strID);
		ST_BinarySerializeCalLen(pIBuffer, m_strValue);
		ST_BinarySerializeCalLen(pIBuffer,m_strDataType);
	}
	else if (nRetRead)
	{	
		ST_BinarySerializeRead(pIBuffer,m_strID);
		ST_BinarySerializeRead(pIBuffer,m_strValue);
		ST_BinarySerializeRead(pIBuffer,m_strDataType);
	}
	else if (nRetWrite)
	{
		ST_BinarySerializeWrite(pIBuffer,m_strID);
		ST_BinarySerializeWrite(pIBuffer,m_strValue);
		ST_BinarySerializeWrite(pIBuffer,m_strDataType);
	}

	return S_OK;
}

STDMETHODIMP CTag::XMLWrite(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	// TODO: 在此添加实现代码
	MSXML::IXMLDOMElementPtr pIElement;
	CValueXMLRWKeys* pXmlKeys = NULL;
	IValueXMLRWKeys* pIValueXmlKeys = NULL;

	pIXMLKeys->QueryInterface(IID_IValueXMLRWKeys,(void**)&pIValueXmlKeys);
	pIXMLElement->QueryInterface(IID_IXMLDOMElement,(void**)&pIElement);

#ifdef _ATL_DEBUG_INTERFACES
	_QIThunk* pThunk = (_QIThunk*)pIValueXmlKeys;
	pXmlKeys = (CValueXMLRWKeys*)pThunk->m_pUnk;
#else
	pXmlKeys = (CValueXMLRWKeys*)pIValueXmlKeys;
#endif

	_XmlWrite(pIElement,pXmlKeys);
	pIValueXmlKeys->Release();

	return S_OK;
}

STDMETHODIMP CTag::XMLRead(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	// TODO: 在此添加实现代码
	MSXML::IXMLDOMNodePtr pIElement;
	CValueXMLRWKeys* pXmlKeys = NULL;
	IValueXMLRWKeys* pIValueXmlKeys = NULL;

	pIXMLKeys->QueryInterface(IID_IValueXMLRWKeys,(void**)&pIValueXmlKeys);
	pIXMLElement->QueryInterface(IID_IXMLDOMElement,(void**)&pIElement);

#ifdef _ATL_DEBUG_INTERFACES
	_QIThunk* pThunk = (_QIThunk*)pIValueXmlKeys;
	pXmlKeys = (CValueXMLRWKeys*)pThunk->m_pUnk;
#else
	pXmlKeys = (CValueXMLRWKeys*)pIValueXmlKeys;
#endif

	_XmlRead(pIElement,pXmlKeys);
	pIValueXmlKeys->Release();

	return S_OK;
}
