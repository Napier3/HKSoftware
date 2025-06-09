// ShortData.cpp : CShortData 的实现

#include "stdafx.h"
#include "ShortData.h"
#include "BinarySerializeGlobalDefine.h"

// CShortData
STDMETHODIMP CShortData::get_Name(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strName.Copy();
	return S_OK;
}

STDMETHODIMP CShortData::put_Name(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strName = newVal;
	return S_OK;
}

STDMETHODIMP CShortData::get_Unit(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strUnit.Copy();
	return S_OK;
}

STDMETHODIMP CShortData::put_Unit(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strUnit = newVal;
	return S_OK;
}

STDMETHODIMP CShortData::get_DataTypeID(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strDataTypeID.Copy();
	return S_OK;
}

STDMETHODIMP CShortData::put_DataTypeID(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strDataTypeID = newVal;
	return S_OK;
}


STDMETHODIMP CShortData::get_Reserved(LONG* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_nReserved;
	return S_OK;
}

STDMETHODIMP CShortData::put_Reserved(LONG newVal)
{
	// TODO: 在此添加实现代码
	m_nReserved = newVal;
	return S_OK;
}

STDMETHODIMP CShortData::get_Format(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strFormat.Copy();
	return S_OK;
}

STDMETHODIMP CShortData::put_Format(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strFormat = newVal;
	return S_OK;
}
STDMETHODIMP CShortData::get_DefaultValue(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strDefaultValue.Copy();
	return S_OK;
}

STDMETHODIMP CShortData::put_DefaultValue(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strDefaultValue = newVal;

	return S_OK;
}

STDMETHODIMP CShortData::get_ID( BSTR * pVal)
{
	// 在此处添加函数实现。
	*pVal = m_strID.Copy();
	return S_OK;
}
STDMETHODIMP CShortData::put_ID( BSTR newVal)
{
	// 在此处添加函数实现。
	m_strID = newVal;
	return S_OK;
}
STDMETHODIMP CShortData::get_Value( BSTR * pVal)
{
	// 在此处添加函数实现。
	*pVal = m_strValue.Copy();
	return S_OK;
}
STDMETHODIMP CShortData::put_Value( BSTR newVal)
{
	// 在此处添加函数实现。
	m_strValue = newVal;
	return S_OK;
}
STDMETHODIMP CShortData::StringSerialize( IDispatch * pIStringBuffer)
{
	ATLASSERT(pIStringBuffer!=NULL);
	IStringSerialBuffer* pIBuffer = (IStringSerialBuffer*)pIStringBuffer;
	LONG nRetSize,nRetRead,nRetWrite;

	pIBuffer->IsReadMode(&nRetRead);
	pIBuffer->IsWriteMode(&nRetWrite);
	pIBuffer->IsCalSizeMode(&nRetSize);

	if (nRetSize)
	{
		pIBuffer->AddBufferLength((m_strName.Length()+1)*2);
		pIBuffer->AddBufferLength((m_strID.Length()+1)*2);
		pIBuffer->AddBufferLength((m_strValue.Length()+1)*2);
		pIBuffer->AddBufferLength((m_strUnit.Length()+1)*2);
		pIBuffer->AddBufferLength((m_strDataTypeID.Length()+1)*2);
		pIBuffer->AddBufferLength((m_strFormat.Length()+1)*2);
		pIBuffer->AddBufferLength((m_strReMark.Length()+1)*2);
		pIBuffer->AddBufferLength((m_strDefaultValue.Length()+1)*2);
		_variant_t val(m_nReserved);
		pIBuffer->AddBufferLength(sizeof(val));
	}
	else if (nRetRead)
	{	
		pIBuffer->get_String(&m_strName);
		pIBuffer->get_String(&m_strID);
		pIBuffer->get_String(&m_strValue);
		pIBuffer->get_String(&m_strUnit);
		pIBuffer->get_String(&m_strDataTypeID);
		pIBuffer->get_String(&m_strFormat);
		pIBuffer->get_String(&m_strReMark);
		pIBuffer->get_String(&m_strDefaultValue);
		_variant_t val;
		pIBuffer->get_VBuffer(&val);
		m_nReserved = val.lVal;

	}
	else if (nRetWrite)
	{
		pIBuffer->put_String(m_strName.Copy());
		pIBuffer->put_String(m_strID.Copy());
		pIBuffer->put_String(m_strValue.Copy());
		pIBuffer->put_String(m_strUnit.Copy());
		pIBuffer->put_String(m_strDataTypeID.Copy());
		pIBuffer->put_String(m_strFormat.Copy());
		pIBuffer->put_String(m_strReMark.Copy());
		pIBuffer->put_String(m_strDefaultValue.Copy());
		_variant_t val(m_nReserved);
		pIBuffer->put_VBuffer(val);
	}
	return S_OK;
}
STDMETHODIMP CShortData::BinarySerialize( IDispatch * pIBinaryBuffer)
{
	ATLASSERT(pIBinaryBuffer!=NULL);
	IBinarySerialBuffer* pIBuffer = (IBinarySerialBuffer*)pIBinaryBuffer;
	LONG nRetSize,nRetRead,nRetWrite;

	pIBuffer->IsReadMode(&nRetRead);
	pIBuffer->IsWriteMode(&nRetWrite);
	pIBuffer->IsCalSizeMode(&nRetSize);

	if (nRetSize)
	{
		ST_BinarySerializeCalLen(pIBuffer, m_strName);
		ST_BinarySerializeCalLen(pIBuffer, m_strID);
		ST_BinarySerializeCalLen(pIBuffer, m_strValue);
		ST_BinarySerializeCalLen(pIBuffer, m_strUnit);
		ST_BinarySerializeCalLen(pIBuffer, m_strDataTypeID);
		ST_BinarySerializeCalLen(pIBuffer, m_strFormat);
		ST_BinarySerializeCalLen(pIBuffer, m_strReMark);
		ST_BinarySerializeCalLen(pIBuffer, m_strDefaultValue);
		ST_BinarySerializeCalLen(pIBuffer, m_nReserved);
	}
	else if (nRetRead)
	{	
		ST_BinarySerializeRead(pIBuffer,m_strName);
		ST_BinarySerializeRead(pIBuffer,m_strID);
		ST_BinarySerializeRead(pIBuffer,m_strValue);
		ST_BinarySerializeRead(pIBuffer,m_strUnit);
		ST_BinarySerializeRead(pIBuffer,m_strDataTypeID);
		ST_BinarySerializeRead(pIBuffer,m_strFormat);
		ST_BinarySerializeRead(pIBuffer,m_strReMark);
		ST_BinarySerializeRead(pIBuffer,m_strDefaultValue);
		ST_BinarySerializeRead(pIBuffer,m_nReserved);
	}
	else if (nRetWrite)
	{
		ST_BinarySerializeWrite(pIBuffer,m_strName);
		ST_BinarySerializeWrite(pIBuffer,m_strID);
		ST_BinarySerializeWrite(pIBuffer,m_strValue);
		ST_BinarySerializeWrite(pIBuffer,m_strUnit);
		ST_BinarySerializeWrite(pIBuffer,m_strDataTypeID);
		ST_BinarySerializeWrite(pIBuffer,m_strFormat);
		ST_BinarySerializeWrite(pIBuffer,m_strReMark);
		ST_BinarySerializeWrite(pIBuffer,m_strDefaultValue);
		ST_BinarySerializeWrite(pIBuffer,m_nReserved);
	}

	return S_OK;
}

STDMETHODIMP CShortData::XMLWrite( IDispatch * pIXMLElement,  IDispatch * pIXMLKeys)
{
	// 在此处添加函数实现。
	MSXML::IXMLDOMElementPtr pIElement;
	CDataXMLRWKeys* pXmlKeys = NULL;
	IDataXMLRWKeys* pIValueXmlKeys = NULL;

	pIXMLKeys->QueryInterface(IID_IValueXMLRWKeys,(void**)&pIValueXmlKeys);
	pIXMLElement->QueryInterface(IID_IXMLDOMElement,(void**)&pIElement);

#ifdef _ATL_DEBUG_INTERFACES
	_QIThunk* pThunk = (_QIThunk*)pIValueXmlKeys;
	pXmlKeys = (CDataXMLRWKeys*)pThunk->m_pUnk;
#else
	pXmlKeys = (CDataXMLRWKeys*)pIValueXmlKeys;
#endif

	_XmlWrite(pIElement,pXmlKeys);
	pIValueXmlKeys->Release();
	return S_OK;
}

STDMETHODIMP CShortData::XMLRead( IDispatch * pIXMLElement,  IDispatch * pIXMLKeys)
{
	// 在此处添加函数实现。
	MSXML::IXMLDOMNodePtr pIElement;
	CDataXMLRWKeys* pXmlKeys = NULL;
	IDataXMLRWKeys* pIValueXmlKeys = NULL;

	pIXMLKeys->QueryInterface(IID_IValueXMLRWKeys,(void**)&pIValueXmlKeys);
	pIXMLElement->QueryInterface(IID_IXMLDOMElement,(void**)&pIElement);

#ifdef _ATL_DEBUG_INTERFACES
	_QIThunk* pThunk = (_QIThunk*)pIValueXmlKeys;
	pXmlKeys = (CDataXMLRWKeys*)pThunk->m_pUnk;
#else
	pXmlKeys = (CDataXMLRWKeys*)pIValueXmlKeys;
#endif

	_XmlRead(pIElement,pXmlKeys);
	pIValueXmlKeys->Release();
	return S_OK;
}

BOOL CShortData::_Copy(CShortData* pShortData)
{
	ATLASSERT(pShortData != NULL);
	if(pShortData != this && pShortData != NULL)
	{
		m_strID = pShortData->m_strID;
		m_strDataTypeID = pShortData->m_strDataTypeID;
		m_strFormat = pShortData->m_strFormat;
		m_strReMark = pShortData->m_strReMark;
		m_strID = pShortData->m_strID;
		m_strName = pShortData->m_strName;
		m_strUnit = pShortData->m_strUnit;
		m_strValue = pShortData->m_strValue;
		m_nReserved = pShortData->m_nReserved;
		m_strDefaultValue = pShortData->m_strDefaultValue;
	}
	return 0;
}

long CShortData::_XmlReadOwn(const MSXML::IXMLDOMNodePtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{
	xml_GetAttibuteValue(pXmlRWKeys->m_strIDKey,oNode,m_strID);
	xml_GetAttibuteValue(pXmlRWKeys->m_strNameKey,oNode,m_strName);
	xml_GetAttibuteValue(pXmlRWKeys->m_strValueKey,oNode,m_strValue);
	xml_GetAttibuteValue(pXmlRWKeys->m_strUnitKey,oNode,m_strUnit);
	xml_GetAttibuteValue(pXmlRWKeys->m_strDataTypeIDKey,oNode,m_strDataTypeID);
	xml_GetAttibuteValue(pXmlRWKeys->m_strFormatKey,oNode,m_strFormat);
	xml_GetAttibuteValue(pXmlRWKeys->m_strRemarkKey,oNode,m_strReMark);
	xml_GetAttibuteValue(pXmlRWKeys->m_strDefaultValueKey,oNode,m_strDefaultValue);
	
	return 0;
}

long CShortData::_XmlReadChildren(const MSXML::IXMLDOMNodeListPtr &oNodes, CDataXMLRWKeys *pXmlRWKeys)
{
	return 0;
}

long CShortData::_XmlWriteOwn(MSXML::IXMLDOMElementPtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strIDKey,(_bstr_t)m_strID);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strNameKey,(_bstr_t)m_strName);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strValueKey,(_bstr_t)m_strValue);
	
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strUnitKey,(_bstr_t)m_strUnit);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strDataTypeIDKey,(_bstr_t)m_strDataTypeID);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strFormatKey,(_bstr_t)m_strFormat);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strRemarkKey,(_bstr_t)m_strReMark);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strDefaultValueKey,(_bstr_t)m_strDefaultValue);
	/*_variant_t nValue(m_nReserved);
	oNode->setAttribute((_bstr_t)pXmlRWKeys->m_strReservedKey,nValue);*/
	
	return 0;
}

long CShortData::_XmlWriteChildren(MSXML::IXMLDOMElementPtr &oParent, CDataXMLRWKeys *pXmlRWKeys)
{
	return 0;
}

IDispatch* CShortData::_CreateNewChild(MSXML::IXMLDOMNodePtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{
	return 0;
}

//added by zah 2010-06-04
STDMETHODIMP CShortData::IsEqual(IDispatch* pISrcObj, LONG* pnEqual)
{
	// TODO: 在此添加实现代码
	ATLASSERT(pISrcObj != NULL);
	if(pISrcObj == NULL)
	{
		*pnEqual = 0;
		return S_OK;
	}
	
	CShortData* pShortData = FromIDispatch(pISrcObj);
	ATLASSERT(pShortData != NULL);
	if(pShortData == NULL)
	{
		*pnEqual = 0;
		return S_OK;
	}
	*pnEqual = _IsEqual(pShortData);

	return S_OK;
}

long CShortData::_IsEqual(CShortData* pShortData)
{
	ATLASSERT(pShortData != NULL);
	if(pShortData == NULL)
		return 0;

	if(pShortData->m_nReserved ==m_nReserved && pShortData->m_strDataTypeID == m_strDataTypeID && pShortData->m_strFormat == m_strFormat&& pShortData->m_strReMark == m_strReMark
		&&pShortData->m_strID == m_strID && pShortData->m_strName == m_strName && pShortData->m_strUnit == m_strUnit 
		&& pShortData->m_strValue == m_strValue)
	{
		return 1;
	}
	else
		return 0;
}
STDMETHODIMP CShortData::get_Remark(BSTR* pVal)
{

	*pVal = m_strReMark.Copy();
	return S_OK;
}

STDMETHODIMP CShortData::put_Remark(BSTR newVal)
{
	m_strReMark = newVal;

	return S_OK;
}
