// ValuesMngr.cpp : CValuesMngr ��ʵ��

#include "stdafx.h"
#include "ValuesMngr.h"


// CValuesMngr

STDMETHODIMP CValuesMngr::GetCount(LONG* pnCount)
{
	// TODO: �ڴ����ʵ�ִ���
	*pnCount = m_listChild.GetCount();
	return S_OK;
}

STDMETHODIMP CValuesMngr::GetItem(LONG nIndex, IDispatch** pIValues)
{
	// TODO: �ڴ����ʵ�ִ���
	GETITEM(CValues,nIndex,pIValues)
		return S_OK;
}

STDMETHODIMP CValuesMngr::AddNew(IDispatch** pIValues)
{
	// TODO: �ڴ����ʵ�ִ���
	ADDNEW(CValues,pIValues)
		return S_OK;
}

STDMETHODIMP CValuesMngr::AddNew2(BSTR bstrName, BSTR bstrID, IDispatch** pIValues)
{
	// TODO: �ڴ����ʵ�ִ���
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
	// TODO: �ڴ����ʵ�ִ���
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
	// TODO: �ڴ����ʵ�ִ���
	FINDBYID(CValues,bstrID,pIValues)
		return S_OK;
}

STDMETHODIMP CValuesMngr::Delete(VARIANT* vIndex, LONG* pnReturn)
{
	// TODO: �ڴ����ʵ�ִ���
	DELETEELEMENT(vIndex,pnReturn)
		return S_OK;
}

STDMETHODIMP CValuesMngr::ChangePosition(VARIANT* vIndex1, VARIANT* vIndex2)
{
	// TODO: �ڴ����ʵ�ִ���
	m_listChild.ChangePosition(vIndex1,vIndex2);
	return S_OK;
}

STDMETHODIMP CValuesMngr::BringToTail(VARIANT* vIndex)
{
	// TODO: �ڴ����ʵ�ִ���
	m_listChild.BringToTail(vIndex);
	return S_OK;
}

STDMETHODIMP CValuesMngr::BringToHead(VARIANT* vIndex)
{
	// TODO: �ڴ����ʵ�ִ���
	m_listChild.BringToHead(vIndex);
	return S_OK;
}

STDMETHODIMP CValuesMngr::BinarySerialize(IDispatch* pIBinaryBuffer)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}

STDMETHODIMP CValuesMngr::XMLWrite(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	// TODO: �ڴ����ʵ�ִ���
	MSXML::IXMLDOMElementPtr pIElement;
	pIXMLElement->QueryInterface(__uuidof(MSXML::IXMLDOMElement),(void**)&pIElement);
	CValueXMLRWKeys* pXmlKeys = NULL;
	pXmlKeys = CValueXMLRWKeys::FromIDispatch(pIXMLKeys);
	_XmlWrite(pIElement,pXmlKeys);
	return S_OK;
}

STDMETHODIMP CValuesMngr::XMLRead(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	// TODO: �ڴ����ʵ�ִ���
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