// DataType.cpp : CDataType 的实现

#include "stdafx.h"
#include "DataType.h"


// CDataType


STDMETHODIMP CDataType::get_Name(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strName.Copy();
	return S_OK;
}

STDMETHODIMP CDataType::put_Name(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strName = newVal;
	return S_OK;
}

STDMETHODIMP CDataType::get_ID(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strID.Copy();
	return S_OK;
}

STDMETHODIMP CDataType::put_ID(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strID = newVal;
	return S_OK;
}

STDMETHODIMP CDataType::GetCount(LONG* pnCount)
{
	// TODO: 在此添加实现代码
	*pnCount = m_listChild.GetCount();
	return S_OK;
}

STDMETHODIMP CDataType::GetItem(LONG nIndex, IDispatch** pIDataTypeValue)
{
	// TODO: 在此添加实现代码
	CDataTypeValue* pvalue = NULL;
	pvalue = m_listChild.GetAtIndex(nIndex);
	pvalue->QueryInterface(IID_IDispatch,(void**)pIDataTypeValue);
	return S_OK;
}

STDMETHODIMP CDataType::FindByName(BSTR bstrName, IDispatch** pIDataTypeValue)
{
	// TODO: 在此添加实现代码
	CDataTypeValue *pData = NULL;
	pData = m_listChild.FindByName(bstrName);

	if (pData != NULL)
	{
		*pIDataTypeValue = pData->_QueryIDispatch();
	}
	else
	{
		*pIDataTypeValue = NULL;
	}
	return S_OK;
}

STDMETHODIMP CDataType::FindByID(BSTR bstrID, IDispatch** pIDataTypeValue)
{
	// TODO: 在此添加实现代码
	CDataTypeValue *pData = NULL;
	pData = m_listChild.FindByID(bstrID);

	if (pData != NULL)
	{
		*pIDataTypeValue = pData->_QueryIDispatch();
	}
	else
	{
		*pIDataTypeValue = NULL;
	}
	return S_OK;
}

STDMETHODIMP CDataType::AddNew(IDispatch** pIDataTypeValue)
{
	// TODO: 在此添加实现代码
	CDataTypeValue *pData = CDataTypeValue::_new_CDataTypeValue();

	if (pData != NULL)
	{
		*pIDataTypeValue = pData->_QueryIDispatch();
		m_listChild.AddTail(pData);
	}
	return S_OK;
}

STDMETHODIMP CDataType::AddNew2(BSTR bstrName, BSTR bstrID, LONG nIndex, IDispatch** pIDataTypeValue)
{
	// TODO: 在此添加实现代码
	CDataTypeValue *pData = CDataTypeValue::_new_CDataTypeValue();
	ATLASSERT(pData != NULL);

	if (pData != NULL)
	{
		pData->m_strID = bstrID;
		pData->m_strName = bstrName;
		pData->m_nIndex = nIndex;
		*pIDataTypeValue = pData->_QueryIDispatch();
		m_listChild.AddTail(pData);
	}

	return S_OK;
}

STDMETHODIMP CDataType::Delete(VARIANT* vIndex, LONG* pnReturn)
{
	// TODO: 在此添加实现代码
	m_listChild.Delete(vIndex, pnReturn);
	return S_OK;
}

STDMETHODIMP CDataType::DeleteAll(void)
{
	// TODO: 在此添加实现代码
	m_listChild.DeleteAll();
	return S_OK;
}

STDMETHODIMP CDataType::ChangePosition(VARIANT* vIndex1, VARIANT* vIndex2)
{
	// TODO: 在此添加实现代码
	m_listChild.ChangePosition(vIndex1,vIndex2);
	return S_OK;
}
long CDataType::_XmlReadOwn(const MSXML::IXMLDOMNodePtr &oNode, CDataTypeXMLRWKeys *pXmlRWKeys)
{
	BSTR strValuesName = pXmlRWKeys->m_strDataTypeIDKey.Copy();

	xml_GetAttibuteValue(strValuesName, oNode, m_strID);
	xml_GetAttibuteValue(pXmlRWKeys->m_strDataTypeNameKey, oNode, m_strName);

	return 0;
}

long CDataType::_XmlReadChildren(const MSXML::IXMLDOMNodeListPtr &oNodes, CDataTypeXMLRWKeys *pXmlRWKeys)
{
	long nCount = oNodes->Getlength();
	long nIndex = 0;
	IDispatch *pNew = NULL;
	MSXML::IXMLDOMNodePtr oNode = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		oNode = oNodes->Getitem(nIndex);
		pNew = _CreateNewChild(oNode,pXmlRWKeys);
	}
	return 0;
}

IDispatch* CDataType::_CreateNewChild(MSXML::IXMLDOMNodePtr &oNode, CDataTypeXMLRWKeys *pXmlRWKeys)
{
	_bstr_t strNodeName;
	strNodeName = oNode->GetnodeName();
	IDispatch* pNew = NULL;
	CComBSTR bstrNodeName = strNodeName.GetBSTR();

	if (bstrNodeName == pXmlRWKeys->m_strValueElementKey)
	{
		CDataTypeValue *pVal = CDataTypeValue::_new_CDataTypeValue();
		pVal->_XmlRead(oNode, pXmlRWKeys);
		m_listChild.AddTail(pVal);
// 		if(m_listChild.FindByID(pVal->m_strID)==NULL)
// 			m_listChild.AddTail(pVal);
// 		else
// 			delete pVal;
	}
	else
	{
	}

	return pNew;
}


long CDataType::_XmlWriteOwn(MSXML::IXMLDOMElementPtr &oNode, CDataTypeXMLRWKeys *pXmlRWKeys)
{
	oNode->setAttribute(_bstr_t(pXmlRWKeys->m_strDataTypeIDKey),(_bstr_t)(m_strID));
	oNode->setAttribute(_bstr_t(pXmlRWKeys->m_strDataTypeNameKey),(_bstr_t)(m_strName));

	return 0;
}

long CDataType::_XmlWriteChildren(MSXML::IXMLDOMElementPtr &oParent, CDataTypeXMLRWKeys *pXmlRWKeys)
{
	MSXML::IXMLDOMElementPtr oData;
	int nCount = m_listChild.GetCount();
	CDataTypeValue* pValue = NULL;

	MSXML::IXMLDOMDocumentPtr oXMLDoc = pXmlRWKeys->m_DocPtr;

	for (int i=0;i<nCount;i++)
	{
		pValue = m_listChild.GetAtIndex(i);
		oData = oXMLDoc->createElement(_bstr_t(pXmlRWKeys->m_strValueElementKey));
		oParent->appendChild(oData);
		pValue->_XmlWrite(oData,pXmlRWKeys);
	}
	return 0;
}
STDMETHODIMP CDataType::XMLWrite(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
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

STDMETHODIMP CDataType::XMLRead(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
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