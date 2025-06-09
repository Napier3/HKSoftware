// Tags.cpp : CTags 的实现

#include "stdafx.h"
#include "Tags.h"
#include "Tag.h"
#include "Values.h"
#include "BinarySerializeGlobalDefine.h"

// CTags
const WCHAR* CTags::g_pstrKeyID = L"ID";
const WCHAR* CTags::g_pstrKeyTags = L"Tags";
const WCHAR* CTags::g_pstrKeyTag = L"Tag";


STDMETHODIMP CTags::get_ID(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strID.Copy();
	return S_OK;
}

STDMETHODIMP CTags::put_ID(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strID = newVal;
	return S_OK;
}

STDMETHODIMP CTags::Add(BSTR strID, BSTR strDataType, BSTR strValue, IDispatch** pITag)
{
	// TODO: 在此添加实现代码
	if (m_listChild.FindByID(strID)!=NULL)
	{
		*pITag =NULL;
		return S_OK;
	}

	CTag *pData = CTag::_new_CTag();
	ATLASSERT(pData != NULL);
	if (pData != NULL)
	{
		pData->m_strID = strID;
		pData->m_strDataType = strDataType;
		pData->m_strValue = strValue;
		*pITag = pData->_QueryIDispatch();
		m_listChild.AddTail(pData);
	}
	return S_OK;
}

STDMETHODIMP CTags::BinarySerialize(IDispatch* pIBinaryBuffer)
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

STDMETHODIMP CTags::XMLWrite(IDispatch* pIXMLElement,IDispatch* pIXMLKeys)
{
	// TODO: 在此添加实现代码
	MSXML::IXMLDOMElementPtr pIElement;
	pIXMLElement->QueryInterface(__uuidof(MSXML::IXMLDOMElement),(void**)&pIElement);

	CValueXMLRWKeys* pXmlKeys = NULL;
	pXmlKeys = CValueXMLRWKeys::FromIDispatch(pIXMLKeys);

	_XmlWrite(pIElement,pXmlKeys);

	return S_OK;
}

STDMETHODIMP CTags::XMLRead(IDispatch* pIXMLElement,IDispatch* pIXMLKeys)
{
	// TODO: 在此添加实现代码
	MSXML::IXMLDOMNodePtr pIElement;
	pIXMLElement->QueryInterface(__uuidof(MSXML::IXMLDOMNodePtr),(void**)&pIElement);

	CValueXMLRWKeys* pXmlKeys = NULL;
	pXmlKeys = CValueXMLRWKeys::FromIDispatch(pIXMLKeys);

	_XmlRead(pIElement,pXmlKeys);

	return S_OK;
}

long CTags::_XmlReadOwn(const MSXML::IXMLDOMNodePtr &oNode, CValueXMLRWKeys *pXmlRWKeys)
{
	xml_GetAttibuteValue((BSTR)g_pstrKeyID, oNode, m_strID);

	return 0;
}

long CTags::_XmlReadChildren(const MSXML::IXMLDOMNodeListPtr &oNodes, CValueXMLRWKeys *pXmlRWKeys)
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

long CTags::_XmlWriteOwn(MSXML::IXMLDOMElementPtr &oNode, CValueXMLRWKeys *pXmlRWKeys)
{
	oNode->setAttribute((_bstr_t)g_pstrKeyID,(_bstr_t)m_strID);
	
	return 0;
}

long CTags::_XmlWriteChildren(MSXML::IXMLDOMElementPtr &oParent, CValueXMLRWKeys *pXmlRWKeys)
{
	MSXML::IXMLDOMElementPtr oData;
	int nCount = m_listChild.GetCount();
	CTag* pTag = NULL;

	MSXML::IXMLDOMDocumentPtr oXMLDoc = pXmlRWKeys->m_oXMLDoc;
	ATLASSERT(oXMLDoc != NULL);

	for (int i=0;i<nCount;i++)
	{
		pTag = m_listChild.GetAtIndex(i);
		oData = oXMLDoc->createElement(_bstr_t(g_pstrKeyTag));
		oParent->appendChild(oData);
		pTag->_XmlWrite(oData,pXmlRWKeys);
	}

	return 0;
}

IDispatch* CTags::_CreateNewChild(MSXML::IXMLDOMNodePtr &oNode, CValueXMLRWKeys *pXmlRWKeys)
{
	_bstr_t strNodeName;
	strNodeName = oNode->GetnodeName();
	IDispatch* pNew = NULL;
	CComBSTR bstrNodeName = strNodeName.GetBSTR();

	if (bstrNodeName == (BSTR)g_pstrKeyTag)
	{
		CTag *pVal = CTag::_new_CTag();
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

STDMETHODIMP CTags::GetCount(LONG* pnCount)
{
	// TODO: 在此添加实现代码
	*pnCount = m_listChild.GetCount();
	return S_OK;
}

STDMETHODIMP CTags::GetItem(LONG nIndex, IDispatch** pIValue)
{
	// TODO: 在此添加实现代码
	CTag* pvalue = NULL;
	pvalue = m_listChild.GetAtIndex(nIndex);
	pvalue->QueryInterface(IID_IDispatch,(void**)pIValue);

	return S_OK;
}

STDMETHODIMP CTags::FindByID(BSTR strID, IDispatch** pIValue)
{
	// TODO: 在此添加实现代码
	CTag *pData = NULL;
	pData = m_listChild.FindByID(strID);

	if (pData != NULL)
	{
		*pIValue = pData->_QueryIDispatch();
	}
	else
	{
		*pIValue = NULL;
	}
	return S_OK;
}

STDMETHODIMP CTags::AddNew(IDispatch** pIValue)
{
	// TODO: 在此添加实现代码
	CTag *pData = CTag::_new_CTag();

	if (pData != NULL)
	{
		*pIValue = pData->_QueryIDispatch();
		m_listChild.AddTail(pData);
	}

	return S_OK;
}

STDMETHODIMP CTags::AddNew2(BSTR strID, BSTR strValue, BSTR strDataType, IDispatch** pIValue)
{
	// TODO: 在此添加实现代码
	if (m_listChild.FindByID(strID)!=NULL)
	{
		*pIValue =NULL;
		return S_OK;
	}

	CTag *pData = CTag::_new_CTag();
	ATLASSERT(pData != NULL);

	if (pData != NULL)
	{
		pData->m_strID = strID;
		pData->m_strValue = strValue;
		pData->m_strDataType = strDataType;
		*pIValue = pData->_QueryIDispatch();
		m_listChild.AddTail(pData);
	}

	return S_OK;
}

STDMETHODIMP CTags::Delete(VARIANT* vIndex, LONG* pnReturn)
{
	// TODO: 在此添加实现代码
	m_listChild.Delete(vIndex, pnReturn);
	return S_OK;
}

STDMETHODIMP CTags::Append(IDispatch* pIValues)
{
	// TODO: 在此添加实现代码
	ATLASSERT(pIValues != NULL);
	if (pIValues == NULL)
	{
		return S_OK;
	}
	CTags* pValues = CTags::FromIDispatch(pIValues);
	_Append(pValues);

	return S_OK;
}

STDMETHODIMP CTags::Clone(IDispatch** pIValues)
{
	// TODO: 在此添加实现代码
	CTags *pDatas = CTags::_new_CTags();

	if (pDatas != NULL)
	{
		pDatas->_CloneAppend(this);
		pDatas->QueryInterface(IID_ITags, (void**)pIValues);
	}
	else
	{
		*pIValues = NULL;
	}
	return S_OK;
}

STDMETHODIMP CTags::DeleteAll(void)
{
	// TODO: 在此添加实现代码
	m_listChild.DeleteAll();
	return S_OK;
}

STDMETHODIMP CTags::GetValues(IDispatch** pIValues)
{
	// TODO: 在此添加实现代码
	CValues *pValues = CValues::_new_CValues();
	long nCount = m_listChild.GetCount();
	for(long i=0;i<nCount;i++)
	{
		CTag *pTag = m_listChild.GetAtIndex(i);
		CValue* pValue = NULL;
		pValue = CValue::_new_CValue();
		pValue->m_strID = pTag->m_strID;
		pValue->m_strValue = pTag->m_strValue;
		pValues->m_listChild.AddTail(pValue);
	}
	pValues->QueryInterface(IID_IDispatch,(void**)pIValues);  

	return S_OK;
}

int CTags::_Append(CTags* pValues)
{
	CTag *pData = NULL;
	CTag *pNew = NULL;
	POS pos = pValues->m_listChild.GetHeadPosition();

	while (pos != NULL)
	{
		pData = pValues->m_listChild.GetNext(pos);
		m_listChild.AddTail(pData);
	}

	return 1;
}

int CTags::_CloneAppend(CTags* pSrcValues)
{
	CTag *pData = NULL;
	CTag *pNew = NULL;
	POS pos = pSrcValues->m_listChild.GetHeadPosition();

	while (pos != NULL)
	{
		pData = pSrcValues->m_listChild.GetNext(pos);
		pNew = CTag::_new_CTag(pData);
		m_listChild.AddTail(pNew);
	}

	return 1;
}

/*************************************************
函数名称：		_BinarySerializeChild
描述：    		 二进制系列化子对象
*************************************************/
void CTags::_BinarySerializeChild(IDispatch* pIBinaryBuffer)
{
	IBinarySerialBuffer* pBuffer = (IBinarySerialBuffer*)pIBinaryBuffer;
	ATLASSERT(pBuffer!=NULL);
	long nCount = 0;
	long nReturn = 0;
	CTag* pValue = NULL;

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
			pValue = CTag::_new_CTag();
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
/*************************************************
函数名称：		_StringSerializeChild
描述：    		StringSerialize子对象
*************************************************/
void CTags::_StringSerializeChild(IDispatch* pIStringBuffer)
{

}