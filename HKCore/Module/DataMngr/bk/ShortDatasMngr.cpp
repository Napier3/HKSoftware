// ShortDatasMngr.cpp : CShortDatasMngr 的实现

#include "stdafx.h"
#include "ShortDatasMngr.h"


// CShortDatasMngr


STDMETHODIMP CShortDatasMngr::GetCount(LONG* pnCount)
{
	// TODO: 在此添加实现代码
	*pnCount = m_listChild.GetCount();
	return S_OK;
}

STDMETHODIMP CShortDatasMngr::GetItem(LONG nIndex, IDispatch** pIShortDatas)
{
	// TODO: 在此添加实现代码
	CShortDatas *pShortDatas = m_listChild.GetAtIndex(nIndex);
	pShortDatas->QueryInterface(IID_IDispatch,(void**)pIShortDatas);
	return S_OK;
}

STDMETHODIMP CShortDatasMngr::AddNew(IDispatch** pNew)
{
	// TODO: 在此添加实现代码
	CShortDatas *pShortDatas = CShortDatas::_new_CShortDatas();
	*pNew = pShortDatas->_QueryIDispatch();
	m_listChild.AddTail(pShortDatas);
	return S_OK;
}

STDMETHODIMP CShortDatasMngr::AddNew2(BSTR bstrName, BSTR bstrID,IDispatch **pNew)
{
	// TODO: 在此添加实现代码
	CShortDatas *pShortDatas = CShortDatas::_new_CShortDatas();
	IDispatch *pTemp = NULL;
	FindByID(bstrID,&pTemp);
	if(pTemp == NULL)
	{
		pShortDatas->m_strID = bstrID;
		pShortDatas->m_strName = bstrName;
		*pNew = pShortDatas->_QueryIDispatch();
		m_listChild.AddTail(pShortDatas);
	}
	else
		*pNew = NULL;
	return S_OK;
}

STDMETHODIMP CShortDatasMngr::FindByName(BSTR bstrName, IDispatch** pIShortDatas)
{
	// TODO: 在此添加实现代码
	CShortDatas *pShortDatas = NULL;
	pShortDatas = m_listChild.FindByName(bstrName);
	if(pShortDatas != NULL)
	{
		*pIShortDatas = pShortDatas->_QueryIDispatch();
	}
	else
	{
		*pIShortDatas = NULL;
	}
	return S_OK;
}

STDMETHODIMP CShortDatasMngr::FindByID(BSTR bstrID, IDispatch** pIShortDatas)
{
	// TODO: 在此添加实现代码
	CShortDatas *pShortDatas = NULL;
	pShortDatas = m_listChild.FindByID(bstrID);
	if(pShortDatas != NULL)
	{
		*pIShortDatas = pShortDatas->_QueryIDispatch();
	}
	else
	{
		*pIShortDatas = NULL;
	}
	return S_OK;
}

STDMETHODIMP CShortDatasMngr::Delete(VARIANT* vIndex, LONG* pnReturn)
{
	// TODO: 在此添加实现代码
	m_listChild.Delete(vIndex,pnReturn);
	return S_OK;
}

STDMETHODIMP CShortDatasMngr::ChangePosition(VARIANT* vIndex1, VARIANT* vIndex2)
{
	// TODO: 在此添加实现代码
	m_listChild.ChangePosition(vIndex1,vIndex2);
	return S_OK;
}

STDMETHODIMP CShortDatasMngr::BringToTail(VARIANT* vIndex)
{
	// TODO: 在此添加实现代码
	m_listChild.BringToTail(vIndex);
	return S_OK;
}

STDMETHODIMP CShortDatasMngr::BringToHead(VARIANT* vIndex)
{
	// TODO: 在此添加实现代码
	m_listChild.BringToHead(vIndex);
	return S_OK;
}

STDMETHODIMP CShortDatasMngr::BinarySerialize(IDispatch* pIBinaryBuffer)
{
	// TODO: 在此添加实现代码

	return S_OK;
}

STDMETHODIMP CShortDatasMngr::XMLWrite(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	// TODO: 在此添加实现代码
	XML_INTERFACE_WRITE(pIXMLElement,pIXMLKeys);	
	return S_OK;
}

STDMETHODIMP CShortDatasMngr::XMLRead(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	// TODO: 在此添加实现代码
	XML_INTERFACE_READ(pIXMLElement,pIXMLKeys);
	return S_OK;
}

long CShortDatasMngr::_XmlReadOwn(const MSXML::IXMLDOMNodePtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{

	return 0;
}

long CShortDatasMngr::_XmlReadChildren(const MSXML::IXMLDOMNodeListPtr &oNodes, CDataXMLRWKeys *pXmlRWKeys)
{
	XML_READ_CHILDREN_CODE(oNodes,pXmlRWKeys);
	return 0;
}

IDispatch* CShortDatasMngr::_CreateNewChild(MSXML::IXMLDOMNodePtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{
	XML_CREATE_NEW_CHILD_CODE(CShortDatas,pXmlRWKeys->m_strDatasElementKey,oNode,pXmlRWKeys);
}

long CShortDatasMngr::_XmlWriteOwn(MSXML::IXMLDOMElementPtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{
	return 0;
}

long CShortDatasMngr::_XmlWriteChildren(MSXML::IXMLDOMElementPtr &oParent, CDataXMLRWKeys *pXmlRWKeys)
{
	XML_WRITE_CHILDREN_CODE(CShortDatas,pXmlRWKeys->m_strDatasElementKey,oParent,pXmlRWKeys);
	return 0;
}