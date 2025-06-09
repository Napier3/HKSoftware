// DataTypeXMLRWKeys.cpp : CDataTypeXMLRWKeys 的实现

#include "stdafx.h"
#include "DataTypeXMLRWKeys.h"


// CDataTypeXMLRWKeys


STDMETHODIMP CDataTypeXMLRWKeys::get_DataTypesElementKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strDataTypesElementKey;
	return S_OK;
}

STDMETHODIMP CDataTypeXMLRWKeys::put_DataTypesElementKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strDataTypesElementKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataTypeXMLRWKeys::get_DataTypeElementKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strDataTypeElementKey;
	return S_OK;
}

STDMETHODIMP CDataTypeXMLRWKeys::put_DataTypeElementKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strDataTypeElementKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataTypeXMLRWKeys::get_ValueElementKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strValueElementKey;
	return S_OK;
}

STDMETHODIMP CDataTypeXMLRWKeys::put_ValueElementKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strValueElementKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataTypeXMLRWKeys::get_DataTypeNameKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strDataTypeNameKey;
	return S_OK;
}

STDMETHODIMP CDataTypeXMLRWKeys::put_DataTypeNameKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strDataTypeNameKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataTypeXMLRWKeys::get_DataTypeIDKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strDataTypeIDKey;
	return S_OK;
}

STDMETHODIMP CDataTypeXMLRWKeys::put_DataTypeIDKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strDataTypeIDKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataTypeXMLRWKeys::get_ValueNameKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strValueNameKey;
	return S_OK;
}

STDMETHODIMP CDataTypeXMLRWKeys::put_ValueNameKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strValueNameKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataTypeXMLRWKeys::get_ValueIDKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strValueIDKey;
	return S_OK;
}

STDMETHODIMP CDataTypeXMLRWKeys::put_ValueIDKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strValueIDKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataTypeXMLRWKeys::get_ValueIndexKey(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strValueIndexKey;
	return S_OK;
}

STDMETHODIMP CDataTypeXMLRWKeys::put_ValueIndexKey(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strValueIndexKey = newVal;
	return S_OK;
}

STDMETHODIMP CDataTypeXMLRWKeys::get_DocPtr(IDispatch** pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_DocPtr;
	return S_OK;
}

STDMETHODIMP CDataTypeXMLRWKeys::put_DocPtr(IDispatch* newVal)
{
	// TODO: 在此添加实现代码
	m_DocPtr = newVal;
	return S_OK;
}
