// ValuesMngr.cpp : CValuesMngr 的实现

#include "stdafx.h"
#include "ValuesMngr.h"


// CValuesMngr

STDMETHODIMP CValuesMngr::GetCount(LONG* pnCount)
{
	// TODO: 在此添加实现代码
	*pnCount = m_listChild.GetCount();
	return S_OK;
}

STDMETHODIMP CValuesMngr::GetItem(LONG nIndex, IDispatch** pIValues)
{
	// TODO: 在此添加实现代码
	GETITEM(CValues,nIndex,pIValues)
		return S_OK;
}

STDMETHODIMP CValuesMngr::AddNew(IDispatch** pIValues)
{
	// TODO: 在此添加实现代码
	ADDNEW(CValues,pIValues)
		return S_OK;
}

STDMETHODIMP CValuesMngr::AddNew2(BSTR bstrName, BSTR bstrID, IDispatch** pIValues)
{
	// TODO: 在此添加实现代码
	if (m_listChild.FindByID(bstrID)!=NULL)
	{
		*pIValues =NULL;
		return S_FALSE;
	}
	CValues *pData = CValues::_new_CValues();
	ATLASSERT(pData != NULL);
	if (pData != NULL)
	{
		pData->m_strID = bstrID;
		pData->m_strName = bstrName;
		*pIValues = pData->_QueryIDispatch();
		m_listChild.AddTail(pData);
	}
	return S_OK;
}

STDMETHODIMP CValuesMngr::FindByName(BSTR bstrName, IDispatch** pIValues)
{
	// TODO: 在此添加实现代码
	CValues *pData = NULL;
	pData = m_listChild.FindByName(bstrName);

	if (pData != NULL)
	{
		*pIValues = pData->_QueryIDispatch();
	}
	else
	{
		*pIValues = NULL;
	}
	return S_OK;
}

STDMETHODIMP CValuesMngr::FindByID(BSTR bstrID, IDispatch** pIValues)
{
	// TODO: 在此添加实现代码
	FINDBYID(CValues,bstrID,pIValues)
		return S_OK;
}

STDMETHODIMP CValuesMngr::Delete(VARIANT* vIndex, LONG* pnReturn)
{
	// TODO: 在此添加实现代码
	DELETEELEMENT(vIndex,pnReturn)
		return S_OK;
}

STDMETHODIMP CValuesMngr::ChangePosition(VARIANT* vIndex1, VARIANT* vIndex2)
{
	// TODO: 在此添加实现代码
	m_listChild.ChangePosition(vIndex1,vIndex2);
	return S_OK;
}

STDMETHODIMP CValuesMngr::BringToTail(VARIANT* vIndex)
{
	// TODO: 在此添加实现代码
	m_listChild.BringToTail(vIndex);
	return S_OK;
}

STDMETHODIMP CValuesMngr::BringToHead(VARIANT* vIndex)
{
	// TODO: 在此添加实现代码
	m_listChild.BringToHead(vIndex);
	return S_OK;
}

STDMETHODIMP CValuesMngr::BinarySerialize(IDispatch* pIBinaryBuffer)
{
	// TODO: 在此添加实现代码

	return S_OK;
}

STDMETHODIMP CValuesMngr::XMLWrite(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	// TODO: 在此添加实现代码
	MSXML::IXMLDOMElementPtr pIElement;
	pIXMLElement->QueryInterface(__uuidof(MSXML::IXMLDOMElement),(void**)&pIElement);
	CValueXMLRWKeys* pXmlKeys = NULL;
	pXmlKeys = CValueXMLRWKeys::FromIDispatch(pIXMLKeys);
	_XmlWrite(pIElement,pXmlKeys);
	return S_OK;
}

STDMETHODIMP CValuesMngr::XMLRead(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	// TODO: 在此添加实现代码
	MSXML::IXMLDOMNodePtr pIElement;
	pIXMLElement->QueryInterface(__uuidof(MSXML::IXMLDOMNodePtr),(void**)&pIElement);
	CValueXMLRWKeys* pXmlKeys = NULL;
	pXmlKeys = CValueXMLRWKeys::FromIDispatch(pIXMLKeys);
	_XmlRead(pIElement,pXmlKeys);
	return S_OK;
}


long CValuesMngr::_XmlReadOwn(const MSXML::IXMLDOMNodePtr &oNode, CValueXMLRWKeys *pXmlRWKeys)
{
	
	return 0;
}

long CValuesMngr::_XmlReadChildren(const MSXML::IXMLDOMNodeListPtr &oNodes, CValueXMLRWKeys *pXmlRWKeys)
{
	XML_READ_CHILDREN_CODE(oNodes,pXmlRWKeys);
	return 0;
}

IDispatch* CValuesMngr::_CreateNewChild(MSXML::IXMLDOMNodePtr &oNode, CValueXMLRWKeys *pXmlRWKeys)
{
	XML_CREATE_NEW_CHILD_CODE(CValues,pXmlRWKeys->m_strValuesElementKey,oNode,pXmlRWKeys);
}

long CValuesMngr::_XmlWriteOwn(MSXML::IXMLDOMElementPtr &oNode, CValueXMLRWKeys *pXmlRWKeys)
{
	return 0;
}

long CValuesMngr::_XmlWriteChildren(MSXML::IXMLDOMElementPtr &oParent, CValueXMLRWKeys *pXmlRWKeys)
{
	XML_WRITE_CHILDREN_CODE(CValues,pXmlRWKeys->m_strValuesElementKey,oParent,pXmlRWKeys)
	return 0;
}