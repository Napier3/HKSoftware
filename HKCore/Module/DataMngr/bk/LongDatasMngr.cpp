// LongDatasMngr.cpp : CLongDatasMngr 的实现

#include "stdafx.h"
#include "LongDatasMngr.h"


// CLongDatasMngr


STDMETHODIMP CLongDatasMngr::GetCount(LONG* pnCount)
{
	// TODO: 在此添加实现代码
	*pnCount = m_listChild.GetCount();
	return S_OK;
}

STDMETHODIMP CLongDatasMngr::GetItem(LONG nIndex, IDispatch** pILongDatas)
{
	// TODO: 在此添加实现代码
	GETITEM(CLongDatas,nIndex,pILongDatas)
	return S_OK;
}

STDMETHODIMP CLongDatasMngr::AddNew(IDispatch** pILongDatas)
{
	// TODO: 在此添加实现代码
	ADDNEW(CLongDatas,pILongDatas)
	return S_OK;
}

STDMETHODIMP CLongDatasMngr::AddNew2(BSTR bstrName, BSTR bstrID, IDispatch** pILongDatas)
{
	// TODO: 在此添加实现代码
	CLongDatas *pData = CLongDatas::_new_CLongDatas();
	ATLASSERT(pData != NULL);
	if (pData != NULL)
	{
		pData->m_strID = bstrID;
		pData->m_strName = bstrName;
		*pILongDatas = pData->_QueryIDispatch();
		m_listChild.AddTail(pData);
	}
	return S_OK;
}

STDMETHODIMP CLongDatasMngr::FindByName(BSTR bstrName, IDispatch** pILongDatas)
{
	// TODO: 在此添加实现代码
	CLongDatas *pData = NULL;
	pData = m_listChild.FindByName(bstrName);

	if (pData != NULL)
	{
		*pILongDatas = pData->_QueryIDispatch();
	}
	else
	{
		*pILongDatas = NULL;
	}
	return S_OK;
}

STDMETHODIMP CLongDatasMngr::FindByID(BSTR bstrID, IDispatch** pILongDatas)
{
	// TODO: 在此添加实现代码
	FINDBYID(CLongDatas,bstrID,pILongDatas)
	return S_OK;
}

STDMETHODIMP CLongDatasMngr::Delete(VARIANT* vIndex, LONG* pnReturn)
{
	// TODO: 在此添加实现代码
	DELETEELEMENT(vIndex,pnReturn)
	return S_OK;
}

STDMETHODIMP CLongDatasMngr::ChangePosition(VARIANT* vIndex1, VARIANT* vIndex2)
{
	// TODO: 在此添加实现代码
	m_listChild.ChangePosition(vIndex1,vIndex2);
	return S_OK;
}

STDMETHODIMP CLongDatasMngr::BringToTail(VARIANT* vIndex)
{
	// TODO: 在此添加实现代码
	m_listChild.BringToTail(vIndex);
	return S_OK;
}

STDMETHODIMP CLongDatasMngr::BringToHead(VARIANT* vIndex)
{
	// TODO: 在此添加实现代码
	m_listChild.BringToHead(vIndex);
	return S_OK;
}

STDMETHODIMP CLongDatasMngr::BinarySerialize(IDispatch* pIBinaryBuffer)
{
	// TODO: 在此添加实现代码

	return S_OK;
}

STDMETHODIMP CLongDatasMngr::XMLWrite(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	// TODO: 在此添加实现代码
	XML_INTERFACE_WRITE(pIXMLElement,pIXMLKeys)
	return S_OK;
}

STDMETHODIMP CLongDatasMngr::XMLRead(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	// TODO: 在此添加实现代码
	XML_INTERFACE_READ(pIXMLElement,pIXMLKeys)
	return S_OK;
}
long CLongDatasMngr::_XmlReadOwn(const MSXML::IXMLDOMNodePtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{

	return 0;
}

long CLongDatasMngr::_XmlReadChildren(const MSXML::IXMLDOMNodeListPtr &oNodes, CDataXMLRWKeys *pXmlRWKeys)
{
	XML_READ_CHILDREN_CODE(oNodes,pXmlRWKeys);
	return 0;
}

IDispatch* CLongDatasMngr::_CreateNewChild(MSXML::IXMLDOMNodePtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{
	XML_CREATE_NEW_CHILD_CODE(CLongDatas,pXmlRWKeys->m_strDatasElementKey,oNode,pXmlRWKeys);
}

long CLongDatasMngr::_XmlWriteOwn(MSXML::IXMLDOMElementPtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{
	return 0;
}

long CLongDatasMngr::_XmlWriteChildren(MSXML::IXMLDOMElementPtr &oParent, CDataXMLRWKeys *pXmlRWKeys)
{
	XML_WRITE_CHILDREN_CODE(CLongDatas,pXmlRWKeys->m_strDatasElementKey,oParent,pXmlRWKeys);
	return 0;
}