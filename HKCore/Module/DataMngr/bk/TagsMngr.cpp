// TagsMngr.cpp : CTagsMngr 的实现

#include "stdafx.h"
#include "TagsMngr.h"
#include "BinarySerializeGlobalDefine.h"

// CTagsMngr
const WCHAR* CTagsMngr::g_pstrKeyID = L"ID";
const WCHAR* CTagsMngr::g_pstrKeyTagsMngr = L"TagsMngr";

STDMETHODIMP CTagsMngr::GetCount(LONG* pnCount)
{
	// TODO: 在此添加实现代码
	*pnCount = m_listChild.GetCount();
	return S_OK;
}

STDMETHODIMP CTagsMngr::GetItem(LONG nIndex, IDispatch** pIValues)
{
	// TODO: 在此添加实现代码
	if (m_listChild.GetCount() == 0)
	{
		*pIValues = NULL;
	}
	else
	{
		GETITEM(CTags,nIndex,pIValues)
	}

	return S_OK;
}

STDMETHODIMP CTagsMngr::AddNew(IDispatch** pIValues)
{
	// TODO: 在此添加实现代码
	ADDNEW(CTags,pIValues)
	return S_OK;
}

STDMETHODIMP CTagsMngr::AddNew2(BSTR bstrName, BSTR bstrID, IDispatch** pIValues)
{
	// TODO: 在此添加实现代码
	if (m_listChild.FindByID(bstrID)!=NULL)
	{
		*pIValues =NULL;
		return S_FALSE;
	}
	CTags *pData = CTags::_new_CTags();
	ATLASSERT(pData != NULL);
	if (pData != NULL)
	{
		pData->m_strID = bstrID;
		*pIValues = pData->_QueryIDispatch();
		m_listChild.AddTail(pData);
	}
	return S_OK;
}

STDMETHODIMP CTagsMngr::FindByName(BSTR bstrName, IDispatch** pIValues)
{
	// TODO: 在此添加实现代码

	return S_OK;
}

STDMETHODIMP CTagsMngr::FindByID(BSTR bstrID, IDispatch** pIValues)
{
	// TODO: 在此添加实现代码
	FINDBYID(CTags,bstrID,pIValues)
	return S_OK;
}

STDMETHODIMP CTagsMngr::Delete(VARIANT* vIndex, LONG* pnReturn)
{
	// TODO: 在此添加实现代码
	DELETEELEMENT(vIndex,pnReturn)

	return S_OK;
}

STDMETHODIMP CTagsMngr::ChangePosition(VARIANT* vIndex1, VARIANT* vIndex2)
{
	// TODO: 在此添加实现代码
	m_listChild.ChangePosition(vIndex1,vIndex2);

	return S_OK;
}

STDMETHODIMP CTagsMngr::BrindToTail(VARIANT* vIndex)
{
	// TODO: 在此添加实现代码
	m_listChild.BringToTail(vIndex);

	return S_OK;
}

STDMETHODIMP CTagsMngr::BringToHead(VARIANT* vIndex)
{
	// TODO: 在此添加实现代码
	m_listChild.BringToHead(vIndex);
	return S_OK;
}

STDMETHODIMP CTagsMngr::BinarySerialize(IDispatch* pIBinaryBuffer)
{
	// TODO: 在此添加实现代码
	ATLASSERT(pIBinaryBuffer!=NULL);
	IBinarySerialBuffer* pIBuffer = (IBinarySerialBuffer*)pIBinaryBuffer;
	LONG nRetSize,nRetRead,nRetWrite;

	pIBuffer->IsReadMode(&nRetRead);
	pIBuffer->IsWriteMode(&nRetWrite);
	pIBuffer->IsCalSizeMode(&nRetSize);

	if (nRetSize)
	{
		ST_BinarySerializeCalLen(pIBuffer, m_strID);
	}
	else if (nRetRead)
	{	
		ST_BinarySerializeRead(pIBuffer, m_strID);
	}
	else if (nRetWrite)
	{
		ST_BinarySerializeWrite(pIBuffer, m_strID);
	}

	_BinarySerializeChild(pIBinaryBuffer);
	return S_OK;
}

STDMETHODIMP CTagsMngr::XMLWrite(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	// TODO: 在此添加实现代码
	MSXML::IXMLDOMElementPtr pIElement;
	pIXMLElement->QueryInterface(__uuidof(MSXML::IXMLDOMElement),(void**)&pIElement);

	CValueXMLRWKeys* pXmlKeys = NULL;
	pXmlKeys = CValueXMLRWKeys::FromIDispatch(pIXMLKeys);

	_XmlWrite(pIElement,pXmlKeys);

	return S_OK;
}

STDMETHODIMP CTagsMngr::XMLRead(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	// TODO: 在此添加实现代码
	MSXML::IXMLDOMNodePtr pIElement;
	pIXMLElement->QueryInterface(__uuidof(MSXML::IXMLDOMNodePtr),(void**)&pIElement);

	CValueXMLRWKeys* pXmlKeys = NULL;
	pXmlKeys = CValueXMLRWKeys::FromIDispatch(pIXMLKeys);

	_XmlRead(pIElement,pXmlKeys);

	return S_OK;
}

long CTagsMngr::_XmlReadOwn(const MSXML::IXMLDOMNodePtr &oNode,CValueXMLRWKeys *pXmlRWKeys)
{
	xml_GetAttibuteValue((BSTR)g_pstrKeyID, oNode, m_strID);

	return 0;
}

long CTagsMngr::_XmlReadChildren(const MSXML::IXMLDOMNodeListPtr &oNodes,CValueXMLRWKeys *pXmlRWKeys)
{
	long nCount = oNodes->Getlength();
	long nIndex = 0;
	IDispatch* pNew = NULL;
	MSXML::IXMLDOMNodePtr oNode = NULL;

	for(nIndex=0;nIndex<nCount;nIndex++)
	{
		oNode = oNodes->Getitem(nIndex);
		pNew = _CreateNewChild(oNode,pXmlRWKeys);
	}

	return 0;
}

long CTagsMngr::_XmlWriteOwn(MSXML::IXMLDOMElementPtr &oNode,CValueXMLRWKeys *pXmlRWKeys)
{
	oNode->setAttribute((_bstr_t)g_pstrKeyID,(_bstr_t)m_strID);

	return 0;
}

long CTagsMngr::_XmlWriteChildren(MSXML::IXMLDOMElementPtr &oParent, CValueXMLRWKeys *pXmlRWKeys)
{
	MSXML::IXMLDOMElementPtr oData;
	int nCount = m_listChild.GetCount();
	CTags* pTags = NULL;

	MSXML::IXMLDOMDocumentPtr oXMLDoc = pXmlRWKeys->m_oXMLDoc;
	ATLASSERT(oXMLDoc != NULL);

	for (int i=0;i<nCount;i++)
	{
		pTags = m_listChild.GetAtIndex(i);
		oData = oXMLDoc->createElement(_bstr_t(g_pstrKeyTagsMngr));
		oParent->appendChild(oData);
		pTags->_XmlWrite(oData,pXmlRWKeys);
	}

	return 0;
}

IDispatch* CTagsMngr::_CreateNewChild(MSXML::IXMLDOMNodePtr &oNode, CValueXMLRWKeys *pXmlRWKeys)
{
	_bstr_t strNodeName;
	strNodeName = oNode->GetnodeName();
	IDispatch* pNew = NULL;
	CComBSTR bstrNodeName = strNodeName.GetBSTR();

	if (bstrNodeName == (BSTR)g_pstrKeyTagsMngr)
	{
		CTags *pVal = CTags::_new_CTags();
		pVal->_XmlRead(oNode, pXmlRWKeys);
		if(m_listChild.FindByID(pVal->m_strID) == NULL)
			m_listChild.AddTail(pVal);
		else
			delete pVal;
	}
	else
	{
	}
	return pNew;
}

void CTagsMngr::_BinarySerializeChild(IDispatch* pIBinaryBuffer)
{
	IBinarySerialBuffer* pBuffer = (IBinarySerialBuffer*)pIBinaryBuffer;
	ATLASSERT(pBuffer!=NULL);
	long nCount = 0;
	long nReturn = 0;
	CTags* pValue = NULL;

	LONG nRetSize,nRetRead;
	pBuffer->IsCalSizeMode(&nRetSize);
	pBuffer->IsReadMode(&nRetRead);


	if (nRetSize)
	{
		pBuffer->AddBufferLength(sizeof(long));
		nCount = m_listChild.GetCount();
		for (int i = 0;i<nCount;i++)
		{
			pValue = m_listChild.GetAtIndex(i);
			pValue->BinarySerialize(pBuffer);
		}
	}
	else if (nRetRead)
	{
		pBuffer->get_Long(&nCount);

		for (int i=0;i<nCount;i++)
		{
			pValue = CTags::_new_CTags();
			pValue->BinarySerialize(pBuffer);
			m_listChild.AddTail(pValue);
		}
	}
	else
	{
		nCount = m_listChild.GetCount();
		pBuffer->put_Long(nCount);
		for (int i=0;i<nCount;i++)
		{
			pValue = m_listChild.GetAtIndex(i);
			pValue->BinarySerialize(pBuffer);
		}
	}
}

STDMETHODIMP CTagsMngr::DeleteAll(void)
{
	// TODO: 在此添加实现代码
	m_listChild.DeleteAll();
	return S_OK;
}

STDMETHODIMP CTagsMngr::get_ID(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strID.Copy();

	return S_OK;
}

STDMETHODIMP CTagsMngr::put_ID(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strID = newVal;

	return S_OK;
}
