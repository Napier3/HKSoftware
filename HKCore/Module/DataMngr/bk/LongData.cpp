// LongData.cpp : CLongData 的实现

#include "stdafx.h"
#include "LongData.h"


// CLongData


STDMETHODIMP CLongData::get_ValueName(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strValueName;
	return S_OK;
}

STDMETHODIMP CLongData::put_ValueName(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strValueName = newVal;
	return S_OK;
}

STDMETHODIMP CLongData::get_DefaultValue(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strDefaultValue;
	return S_OK;
}

STDMETHODIMP CLongData::put_DefaultValue(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strDefaultValue = newVal;

	return S_OK;
}

STDMETHODIMP CLongData::get_Script(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strScript;
	return S_OK;
}

STDMETHODIMP CLongData::put_Script(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strScript = newVal;

	return S_OK;
}

STDMETHODIMP CLongData::get_DataTypeDomain(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strDataTypeDomain;
	return S_OK;
}

STDMETHODIMP CLongData::put_DataTypeDomain(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strDataTypeDomain = newVal;
	return S_OK;
}

STDMETHODIMP CLongData::get_Message(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strMessage;
	return S_OK;
}

STDMETHODIMP CLongData::put_Message(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strMessage = newVal;
	return S_OK;
}

STDMETHODIMP CLongData::get_Type(SHORT* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_sType;
	return S_OK;
}

STDMETHODIMP CLongData::put_Type(SHORT newVal)
{
	// TODO: 在此添加实现代码
	m_sType = newVal;
	return S_OK;
}

STDMETHODIMP CLongData::get_Show(SHORT* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_sShow;
	return S_OK;
}

STDMETHODIMP CLongData::put_Show(SHORT newVal)
{
	// TODO: 在此添加实现代码
	m_sShow = newVal;
	return S_OK;
}

STDMETHODIMP CLongData::get_Enable(SHORT* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_sEnable;
	return S_OK;
}

STDMETHODIMP CLongData::put_Enable(SHORT newVal)
{
	// TODO: 在此添加实现代码
	m_sEnable = newVal;
	return S_OK;
}

STDMETHODIMP CLongData::get_Reserved2(LONG* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_nReserved2;
	return S_OK;
}

STDMETHODIMP CLongData::put_Reserved2(LONG newVal)
{
	// TODO: 在此添加实现代码
	m_nReserved2 = newVal;
	return S_OK;
}
long CLongData::_XmlReadOwn(const MSXML::IXMLDOMNodePtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{
	xml_GetAttibuteValue(pXmlRWKeys->m_strIDKey,oNode,m_strID);
	xml_GetAttibuteValue(pXmlRWKeys->m_strValueKey,oNode,m_strValue);
	xml_GetAttibuteValue(pXmlRWKeys->m_strUnitKey,oNode,m_strUnit);
	xml_GetAttibuteValue(pXmlRWKeys->m_strNameKey,oNode,m_strUnit);
	xml_GetAttibuteValue(pXmlRWKeys->m_strDataTypeIDKey,oNode,m_strUnit);

	xml_GetAttibuteValue(pXmlRWKeys->m_strReservedKey,oNode,m_nReserved);
	xml_GetAttibuteValue(pXmlRWKeys->m_strFormatKey,oNode,m_strFormat);
	xml_GetAttibuteValue(pXmlRWKeys->m_strValueNameKey,oNode,m_strValueName);
	xml_GetAttibuteValue(pXmlRWKeys->m_strDefaultValueKey,oNode,m_strDefaultValue);
	xml_GetAttibuteValue(pXmlRWKeys->m_strScriptKey,oNode,m_strScript);
	xml_GetAttibuteValue(pXmlRWKeys->m_strMessageKey,oNode,m_strMessage);
	
	xml_GetAttibuteValue(pXmlRWKeys->m_strTypeKey,oNode,m_sType);
	xml_GetAttibuteValue(pXmlRWKeys->m_strShowKey,oNode,m_sShow);
	xml_GetAttibuteValue(pXmlRWKeys->m_strEnableKey,oNode,m_sEnable);
	xml_GetAttibuteValue(pXmlRWKeys->m_strReserved2Key,oNode,m_nReserved2);

	return 0;
}

long CLongData::_XmlReadChildren(const MSXML::IXMLDOMNodeListPtr &oNodes, CDataXMLRWKeys *pXmlRWKeys)
{

	return 0;
}

IDispatch* CLongData::_CreateNewChild(MSXML::IXMLDOMNodePtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{
	return 0;
}

long CLongData::_XmlWriteOwn(MSXML::IXMLDOMElementPtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strIDKey,(_bstr_t)m_strID);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strValueKey,(_bstr_t)m_strValue);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strNameKey,(_bstr_t)m_strName);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strUnitKey,(_bstr_t)m_strUnit);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strDataTypeIDKey,(_bstr_t)m_strDataTypeID);

	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strReservedKey,m_nReserved);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strFormatKey,(_bstr_t)m_strFormat);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strValueNameKey,(_bstr_t)m_strValueName);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strDefaultValueKey,(_bstr_t)m_strDefaultValue);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strScriptKey,(_bstr_t)m_strScript);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strMessageKey,(_bstr_t)m_strMessage);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strReserved2Key,m_nReserved2);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strTypeKey,m_sType);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strShowKey,m_sShow);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strEnableKey,m_sEnable);

	return 0;
}

long CLongData::_XmlWriteChildren(MSXML::IXMLDOMElementPtr &oParent, CDataXMLRWKeys *pXmlRWKeys)
{
	
	return 0;
}
STDMETHODIMP CLongData::IsEqual(IDispatch* pISrcObj, LONG* pnEqual)
{
	// TODO: 在此添加实现代码

	return S_OK;
}

STDMETHODIMP CLongData::get_Remark(BSTR* pVal)
{
	// TODO: 在此添加实现代码

	return S_OK;
}

STDMETHODIMP CLongData::put_Remark(BSTR newVal)
{
	// TODO: 在此添加实现代码

	return S_OK;
}
