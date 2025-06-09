// DataTypes.cpp : CDataTypes 的实现

#include "stdafx.h"
#include "DataTypes.h"


// CDataTypes


STDMETHODIMP CDataTypes::GetCount(LONG* pnCount)
{
	// TODO: 在此添加实现代码
	*pnCount = m_listChild.GetCount();
	return S_OK;
}

STDMETHODIMP CDataTypes::GetItem(LONG nIndex, IDispatch** pIDataType)
{
	// TODO: 在此添加实现代码
	CDataType* pvalue = NULL;
	pvalue = m_listChild.GetAtIndex(nIndex);
	pvalue->QueryInterface(IID_IDispatch,(void**)pIDataType);
	return S_OK;
}

STDMETHODIMP CDataTypes::FindByName(BSTR bstrName, IDispatch** pIDataType)
{
	// TODO: 在此添加实现代码
	CDataType *pData = NULL;
	pData = m_listChild.FindByName(bstrName);

	if (pData != NULL)
	{
		*pIDataType = pData->_QueryIDispatch();
	}
	else
	{
		*pIDataType = NULL;
	}
	return S_OK;
}

STDMETHODIMP CDataTypes::FindByID(BSTR bstrID, IDispatch** pIDataType)
{
	// TODO: 在此添加实现代码
	CDataType *pData = NULL;
	pData = m_listChild.FindByID(bstrID);

	if (pData != NULL)
	{
		*pIDataType = pData->_QueryIDispatch();
	}
	else
	{
		*pIDataType = NULL;
	}
	return S_OK;
}

STDMETHODIMP CDataTypes::AddNew(IDispatch** pIDataType)
{
	// TODO: 在此添加实现代码
	ADDNEW(CDataType,pIDataType);
	return S_OK;
}

STDMETHODIMP CDataTypes::AddNew2(BSTR bstrName, BSTR bstrID, IDispatch** pIDataType)
{
	// TODO: 在此添加实现代码
	CDataType *pData = CDataType::_new_CDataType();
	ATLASSERT(pData != NULL);
	if (pData != NULL)
	{
		pData->m_strID = bstrID;
		pData->m_strName = bstrName;
		*pIDataType = pData->_QueryIDispatch();
		if (m_listChild.FindByID(bstrID))
		{
			return S_OK;
		}
		else
		m_listChild.AddTail(pData);
	}
	return S_OK;
}

STDMETHODIMP CDataTypes::Delete(VARIANT* vIndex, LONG* pnReturn)
{
	// TODO: 在此添加实现代码
	DELETEELEMENT(vIndex,pnReturn);
	return S_OK;
}



STDMETHODIMP CDataTypes::ChangePosition(VARIANT* vIndex1, VARIANT* vIndex2)
{
	// TODO: 在此添加实现代码
	m_listChild.ChangePosition(vIndex1,vIndex2);
	return S_OK;
}

STDMETHODIMP CDataTypes::BinarySerialize(IDispatch* pIBinaryBuffer)
{
	// TODO: 在此添加实现代码

	return S_OK;
}

STDMETHODIMP CDataTypes::XMLWrite(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
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
STDMETHODIMP CDataTypes::XMLRead(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
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
long CDataTypes::_XmlReadOwn(const MSXML::IXMLDOMNodePtr &oNode, CDataTypeXMLRWKeys *pXmlRWKeys)
{

	return 0;
}

long CDataTypes::_XmlReadChildren(const MSXML::IXMLDOMNodeListPtr &oNodes, CDataTypeXMLRWKeys *pXmlRWKeys)
{
	XML_READ_CHILDREN_CODE(oNodes,pXmlRWKeys)

	return 0;
}

IDispatch* CDataTypes::_CreateNewChild(MSXML::IXMLDOMNodePtr &oNode, CDataTypeXMLRWKeys *pXmlRWKeys)
{
	XML_CREATE_NEW_CHILD_CODE(CDataType,pXmlRWKeys->m_strDataTypeElementKey,oNode,pXmlRWKeys)

}


long CDataTypes::_XmlWriteOwn(MSXML::IXMLDOMElementPtr &oNode, CDataTypeXMLRWKeys *pXmlRWKeys)
{
	return 0;
}

long CDataTypes::_XmlWriteChildren(MSXML::IXMLDOMElementPtr &oParent, CDataTypeXMLRWKeys *pXmlRWKeys)
{
	//XML_WRITE_CHILDREN_CODE(CDataType,pXmlRWKeys->m_strDataTypeElementKey,oParent,pXmlRWKeys)
	MSXML::IXMLDOMElementPtr oData;
	int nCount = m_listChild.GetCount();
	CDataType* pValue = NULL;

	MSXML::IXMLDOMDocumentPtr oXMLDoc = pXmlRWKeys->m_DocPtr;

	for (int i=0;i<nCount;i++)
	{
		pValue = m_listChild.GetAtIndex(i);
		oData = oXMLDoc->createElement(_bstr_t(pXmlRWKeys->m_strDataTypeElementKey));
		oParent->appendChild(oData);
		pValue->_XmlWrite(oData,pXmlRWKeys);
	}
	return 0;
}
STDMETHODIMP CDataTypes::Open(BSTR bstrFile, IDispatch* pXmlKeys, ULONG* pnReturn)
{
	MSXML::IXMLDOMDocumentPtr oDoc = NULL;
	HRESULT hr = oDoc.CreateInstance(__uuidof(MSXML::DOMDocument));

	if(!SUCCEEDED(hr)) 
	{ 
		return S_FALSE;
	} 

	BOOL bTrue = oDoc->load(bstrFile);

	if (!bTrue)
	{
		return S_FALSE;
	}

	CDataTypeXMLRWKeys* pXmlRWKeys = CDataTypeXMLRWKeys::FromIDispatch(pXmlKeys);
	if (pXmlRWKeys!=NULL)
	{
		pXmlRWKeys->AddRef();
	}
	else
	{
		pXmlRWKeys = CDataTypeXMLRWKeys::_new_CDataTypeXMLRWKeys();
		pXmlRWKeys->AddRef();
	}

	MSXML::IXMLDOMElementPtr oDataTypes = NULL;
	oDataTypes = oDoc->selectSingleNode(_bstr_t(pXmlRWKeys->m_strDataTypesElementKey));

	if (oDataTypes == NULL)
	{
		pXmlRWKeys->Release();
		return S_FALSE;
	}

	_XmlRead(oDataTypes, pXmlRWKeys);
	pXmlRWKeys->Release();

	return S_OK;
}

STDMETHODIMP CDataTypes::Save(BSTR bstrFile, IDispatch* pXmlKeys, ULONG* pnReturn)
{
	MSXML::IXMLDOMDocumentPtr oDoc = NULL;
	HRESULT hr = oDoc.CreateInstance(__uuidof(MSXML::DOMDocument));

	if(!SUCCEEDED(hr)) 
	{ 
		return S_FALSE;
	} 

	CDataTypeXMLRWKeys* pXmlRWKeys = CDataTypeXMLRWKeys::FromIDispatch(pXmlKeys);
	if (pXmlRWKeys!=NULL)
	{
		pXmlRWKeys->AddRef();
	}
	else
	{
		pXmlRWKeys = CDataTypeXMLRWKeys::_new_CDataTypeXMLRWKeys();
	}

	MSXML::IXMLDOMElementPtr oDataTypes = NULL;
	oDataTypes = oDoc->selectSingleNode(_bstr_t(pXmlRWKeys->m_strDataTypesElementKey));

	if (oDataTypes == NULL)
	{
		pXmlRWKeys->Release();
		return S_FALSE;
	}

	_XmlWrite(oDataTypes, pXmlRWKeys);
	pXmlRWKeys->Release();

	BOOL bTrue = oDoc->save(bstrFile);

	if (!bTrue)
	{
		return S_FALSE;
	}

	return S_OK;
}
