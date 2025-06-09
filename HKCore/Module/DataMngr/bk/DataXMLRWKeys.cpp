// DataXMLRWKeys.cpp : CDataXMLRWKeys 的实现

#include "stdafx.h"
#include "DataXMLRWKeys.h"


// CDataXMLRWKeys

STDMETHODIMP CDataXMLRWKeys::get_NameKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strNameKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_NameKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strNameKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_IDKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strIDKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_IDKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strIDKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_UnitKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strUnitKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_UnitKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strUnitKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_ValueKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strValueKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_ValueKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strValueKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_ValueNameKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strValueNameKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_ValueNameKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strValueNameKey = newVal;
	return S_OK;	
}

STDMETHODIMP CDataXMLRWKeys::get_DefaultValueKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strDefaultValueKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_DefaultValueKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strDefaultValueKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_ScriptKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strScriptKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_ScriptKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strScriptKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_DataTypeIDKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strDataTypeIDKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_DataTypeIDKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strDataTypeIDKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_MessageKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strMessageKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_MessageKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strMessageKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_TypeKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strTypeKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_TypeKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strTypeKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_ShowKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strShowKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_ShowKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strShowKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_EnableKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strEnableKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_EnableKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strEnableKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_ReservedKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strReservedKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_ReservedKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strReservedKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_Reserved2Key(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strReserved2Key.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_Reserved2Key(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strReserved2Key = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_FormatKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strFormatKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_FormatKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strFormatKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_DataElementKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strDataElementKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_DataElementKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strDataElementKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_DatasElementKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strDatasElementKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_DatasElementKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strDatasElementKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_DatasNameAttrKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strDatasNameAttrKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_DatasNameAttrKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strDatasNameAttrKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_DatasIDAttrKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strDatasIDAttrKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_DatasIDAttrKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strDatasIDAttrKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::get_DatasMngrElementKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strDatasMngrElementKey.Copy();
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_DatasMngrElementKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strDatasMngrElementKey = newVal;
	return S_OK;
}
STDMETHODIMP CDataXMLRWKeys::get_DocPtr(IDispatch** pVal)
{
	// TODO: 在此添加实现代码
	m_oXMLDoc->QueryInterface(IID_IDispatch,(void**)pVal);
	return S_OK;
}

STDMETHODIMP CDataXMLRWKeys::put_DocPtr(IDispatch* newVal)
{
	// TODO: 在此添加实现代码
	m_oXMLDoc = newVal;
	return S_OK;
}
