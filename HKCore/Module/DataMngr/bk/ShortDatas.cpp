// ShortDatas.cpp : CShortDatas 的实现

#include "stdafx.h"
#include "ShortDatas.h"
#include "Value.h"
#include "Values.h"
#include "BinarySerializeGlobalDefine.h"

// CShortDatas


STDMETHODIMP CShortDatas::get_Name(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strName.Copy();
	return S_OK;
}

STDMETHODIMP CShortDatas::put_Name(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strName = newVal;
	return S_OK;
}

STDMETHODIMP CShortDatas::get_ID(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	*pVal = m_strID.Copy();
	return S_OK;
}

STDMETHODIMP CShortDatas::put_ID(BSTR newVal)
{
	// TODO: 在此添加实现代码
	m_strID = newVal;
	return S_OK;
}

STDMETHODIMP CShortDatas::GetCount(LONG* pnCount)
{
	// TODO: 在此添加实现代码
	*pnCount = m_listChild.GetCount();
	return S_OK;
}

STDMETHODIMP CShortDatas::GetItem(LONG nIndex, IDispatch** pIShortData)
{
	// TODO: 在此添加实现代码
	CShortData *pShortData = m_listChild.GetAtIndex(nIndex);
	pShortData->QueryInterface(IID_IDispatch,(void**)pIShortData);

	//*pIShortData = m_listChild.GetAtIndexIDispatch(nIndex);
	return S_OK;
}

STDMETHODIMP CShortDatas::FindByName(BSTR strName, IDispatch** pIShortData)
{
	// TODO: 在此添加实现代码
	CShortData *pShortData = NULL;
	pShortData = m_listChild.FindByName(strName);
	if(pShortData != NULL)
	{
		*pIShortData = pShortData->_QueryIDispatch();
	}
	else
	{
		*pIShortData = NULL;
	}
	return S_OK;
}

STDMETHODIMP CShortDatas::FindByID(BSTR strID, IDispatch** pIShortData)
{
	// TODO: 在此添加实现代码
	CShortData *pShortData = NULL;
	pShortData = m_listChild.FindByID(strID);
	if(pShortData != NULL)
	{
		*pIShortData = pShortData->_QueryIDispatch();
	}
	else
	{
		*pIShortData = NULL;
	}
	return S_OK;
}

STDMETHODIMP CShortDatas::AddNew(IDispatch** pIShortData)
{
	CShortData *pShortData = CShortData::_new_CShortData();
	*pIShortData = pShortData->_QueryIDispatch();
	m_listChild.AddTail(pShortData);
	return S_OK;
}

STDMETHODIMP CShortDatas::AddNew2(BSTR strName,BSTR strID, BSTR strUnit, BSTR strDataTypeID, BSTR strValue, LONG nReserved,BSTR bstrFormat,BSTR bstrRemark, IDispatch** pNew)
{
	//判断strID是否已经存在
	IDispatch* pTemp;
	FindByID(strID,&pTemp);
	if(pTemp ==NULL)
	{
		CShortData *pShortData = CShortData::_new_CShortData();
		pShortData->m_strName = strName;
		pShortData->m_strID = strID;
		pShortData->m_strUnit = strUnit;
		pShortData->m_strDataTypeID = strDataTypeID;
		pShortData->m_strValue = strValue;
		pShortData->m_nReserved = nReserved;
		pShortData->m_strFormat = bstrFormat;
		pShortData->m_strReMark = bstrRemark;
		*pNew = pShortData->_QueryIDispatch();
		m_listChild.AddTail(pShortData);
	}
	else
	{
		pTemp->Release();
		*pNew = NULL;
	}

	
	return S_OK;
}

STDMETHODIMP CShortDatas::Delete(VARIANT* vIndex, LONG* pnReturn)
{
	// TODO: 在此添加实现代码
	m_listChild.Delete(vIndex,pnReturn);
	return S_OK;
}

STDMETHODIMP CShortDatas::Append(IDispatch* pIShortDatas)
{
	// TODO: 在此添加实现代码
	ATLASSERT(pIShortDatas != NULL);
	if(pIShortDatas == NULL)
	{
		return S_OK;
	}
	CShortDatas *pShortDatas = CShortDatas::FromIDispatch(pIShortDatas);
	_Append(pShortDatas);
	return S_OK;
}

STDMETHODIMP CShortDatas::Clone(IDispatch** pIShortDatas)
{
	// TODO: 在此添加实现代码
	CComObject<CShortDatas> *pShortDatas = NULL;
	CComObject<CShortDatas>::CreateInstance(&pShortDatas);

	if(pShortDatas != NULL)
	{
		pShortDatas->_CloneAppend(this);
		pShortDatas->QueryInterface(IID_IShortDatas,(void**)pIShortDatas);
	}
	else
	{
		*pIShortDatas = NULL;
	}
	return S_OK;
}

STDMETHODIMP CShortDatas::SetValueByName(BSTR bstrName, BSTR bstrValue)
{
	// TODO: 在此添加实现代码
	CShortData* pShortData = m_listChild.FindByName(bstrName);
	ATLASSERT(pShortData != NULL);
	pShortData->m_strValue = bstrValue;
	return S_OK;
}

STDMETHODIMP CShortDatas::SetValueByID(BSTR bstrID, BSTR bstrValue)
{
	// TODO: 在此添加实现代码
	CShortData* pShortData = m_listChild.FindByID(bstrID);
	ATLASSERT(pShortData != NULL);
	if(pShortData != NULL)
		pShortData->m_strValue = bstrValue;
	return S_OK;
}

STDMETHODIMP CShortDatas::DeleteAll(void)
{
	// TODO: 在此添加实现代码
	m_listChild.DeleteAll();
	return S_OK;
}

STDMETHODIMP CShortDatas::ChangePosition(VARIANT* vIndex1, VARIANT* vIndex2)
{
	// TODO: 在此添加实现代码
	m_listChild.ChangePosition(vIndex1,vIndex2);
	return S_OK;
}

STDMETHODIMP CShortDatas::SetValuesByDatas(IDispatch* pIShortDatas)
{
	// TODO: 在此添加实现代码
	ATLASSERT(pIShortDatas != NULL);
	if(pIShortDatas == NULL)
	{
		return S_OK;
	}
	CShortDatas *pSrcShortDatas = FromIDispatch(pIShortDatas);
	if(pSrcShortDatas == NULL)
	{
		return S_OK;
	}

	CShortData *pShortData = NULL;
	CShortData *pSrcShortData = NULL;

	long nCount = pSrcShortDatas->m_listChild.GetCount();
	long nIndex = 0;
	POS pos = pSrcShortDatas->m_listChild.GetHeadPosition();

	while(pos != NULL)
	{
		pSrcShortData = pSrcShortDatas->m_listChild.GetNext(pos);
		pShortData = m_listChild.FindByID(pSrcShortData->m_strID);
		if(pShortData != NULL)
		{
			pShortData->m_strValue = pSrcShortData->m_strValue.Copy();
		}
	}
	return S_OK;
}

STDMETHODIMP CShortDatas::SetValuesByEquation(IDispatch* pIEquation)
{
	// TODO: 在此添加实现代码
	SETVALUESBYEQUATION(CShortData,pIEquation);
	return S_OK;
}

STDMETHODIMP CShortDatas::SetValuesByString(BSTR bstrValues)
{
	// TODO: 在此添加实现代码
	SETVALUESBYSTRING(bstrValues);
	return S_OK;
}

STDMETHODIMP CShortDatas::GetDatasString(LONG nNameFormat, LONG nWithUnit,BSTR *pbstrValues)
{
	// TODO: 在此添加实现代码
	CShortData* pShortData = NULL;
	int nCount = m_listChild.GetCount();
	CComBSTR str;
	long nLength = str.Length();
	for (int Index=0;Index<nCount;Index++)
	{
		pShortData = m_listChild.GetAtIndex(Index);
		if (0 == nNameFormat)
		{
			str += pShortData->m_strName;
			str += L"=";
			str += pShortData->m_strValue;
		}
		else if (1 == nNameFormat)
		{
			str += pShortData->m_strID;
			str += L"=";
			str += pShortData->m_strValue;
		}
		if (0 == nWithUnit)
		{
			str += pShortData->m_strUnit;
		}
		str += L";";
	}
	*pbstrValues = str.Copy();
	return S_OK;
}

STDMETHODIMP CShortDatas::StringSerialize(IDispatch* pStringBuffer, LONG nNameFormat, LONG nWithUnit)
{
	ATLASSERT(pStringBuffer!=NULL);
	IStringSerialBuffer* pIBuffer = (IStringSerialBuffer*)pStringBuffer;
	LONG nRetSize,nRetRead,nRetWrite;

	pIBuffer->IsReadMode(&nRetRead);
	pIBuffer->IsWriteMode(&nRetWrite);
	pIBuffer->IsCalSizeMode(&nRetSize);

	if (nRetSize)
	{
		pIBuffer->AddBufferLength(m_strName.Length()+1);
		pIBuffer->AddBufferLength(m_strID.Length()+1);
	}
	else if (nRetRead)
	{	
		pIBuffer->get_String(&m_strName);
		pIBuffer->get_String(&m_strID);

	}
	else if (nRetWrite)
	{
		pIBuffer->put_String(m_strName.Copy());
		pIBuffer->put_String(m_strID.Copy());
	}
	_StringSerializeChild(pStringBuffer);

	return S_OK;
}

STDMETHODIMP CShortDatas::BinarySerialize(IDispatch* pIBinaryBuffer)
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
	}
	else if (nRetRead)
	{	
		ST_BinarySerializeRead(pIBuffer,m_strName);
		ST_BinarySerializeRead(pIBuffer,m_strID);

	}
	else if (nRetWrite)
	{
		ST_BinarySerializeWrite(pIBuffer,m_strName);
		ST_BinarySerializeWrite(pIBuffer,m_strID);
	}

	_BinarySerializeChild(pIBinaryBuffer);

	return S_OK;
}

void CShortDatas::_BinarySerializeChild(IDispatch* pIBinaryBuffer)
{
	IBinarySerialBuffer* pIBuffer = (IBinarySerialBuffer*)pIBinaryBuffer;
	LONG nRetSize,nRetRead,nRetWrite;
	LONG nCount;

	pIBuffer->IsReadMode(&nRetRead);
	pIBuffer->IsWriteMode(&nRetWrite);
	pIBuffer->IsCalSizeMode(&nRetSize);
	CShortData* pShortData = NULL;

	if (nRetSize)
	{
		nCount = m_listChild.GetCount();
		pIBuffer->AddBufferLength(sizeof(nCount));
		for (int i=0;i<nCount;i++)
		{
			pShortData = m_listChild.GetAtIndex(i);
			pShortData->BinarySerialize(pIBuffer);
		}

	}
	else if (nRetRead)
	{	
		pIBuffer->get_Long(&nCount);
		for (int i=0;i<nCount;i++)
		{
			pShortData = CShortData::_new_CShortData();
			pShortData->BinarySerialize(pIBuffer);
			m_listChild.AddTail(pShortData);
		}
	}
	else if (nRetWrite)
	{
		nCount = m_listChild.GetCount();
		pIBuffer->put_Long(nCount);
		for (int i=0;i<nCount;i++)
		{
			pShortData = m_listChild.GetAtIndex(i);
			pShortData->BinarySerialize(pIBuffer);
		}
	}
}

void CShortDatas::_StringSerializeChild(IDispatch* pIStringBuffer)
{
	int nCount = m_listChild.GetCount();
	CShortData* pValue = NULL;
	for (int i=0;i<nCount;i++)
	{
		pValue = m_listChild.GetAtIndex(i);
		pValue->StringSerialize(pIStringBuffer);
	}
}

STDMETHODIMP CShortDatas::XMLWrite(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	// TODO: 在此添加实现代码
	MSXML::IXMLDOMElementPtr pIElement;
	pIXMLElement->QueryInterface(__uuidof(MSXML::IXMLDOMElement),(void**)&pIElement);

	CDataXMLRWKeys* pXmlKeys = NULL;
	pXmlKeys = CDataXMLRWKeys::FromIDispatch(pIXMLKeys);

	_XmlWrite(pIElement,pXmlKeys);
	return S_OK;
}

STDMETHODIMP CShortDatas::XMLRead(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	// TODO: 在此添加实现代码
	MSXML::IXMLDOMNodePtr pIElement = pIXMLElement;
	//pIXMLElement->QueryInterface(__uuidof(MSXML::IXMLDOMNodePtr),(void**)&pIElement);

	CDataXMLRWKeys* pXmlKeys = NULL;
	pXmlKeys = CDataXMLRWKeys::FromIDispatch(pIXMLKeys);

	_XmlRead(pIElement,pXmlKeys);
	return S_OK;
}

int CShortDatas::_Append(CShortDatas* pShortDatas)
{
	CShortData *pShortData = NULL;
	CShortData *pNew = NULL;
	POS pos = pShortDatas->m_listChild.GetHeadPosition();
	while(pos != NULL)
	{
		pShortData = pShortDatas->m_listChild.GetNext(pos);
		m_listChild.AddTail(pShortData);
	}
	return 1;
}

int CShortDatas::_CloneAppend(CShortDatas* pShortDatas)
{
	CShortData *pShortData = NULL;
	CShortData *pNew = NULL;
	POS pos = pShortDatas->m_listChild.GetHeadPosition();

	while(pos != NULL)
	{
		pShortData = pShortDatas->m_listChild.GetNext(pos);
		pNew = CShortData::_new_CShortData(pShortData);
		m_listChild.AddTail(pNew);
	}

	return 1;
}

STDMETHODIMP CShortDatas::SetValuesByValues(IDispatch* pIValues)
{
	// TODO: 在此添加实现代码
	ATLASSERT(pIValues != NULL);
	if(pIValues == NULL)
		return S_OK;
	CValues *pSrcValues = NULL;
	pSrcValues = CValues::FromIDispatch(pIValues);
	ATLASSERT(pSrcValues != NULL);
	if(pSrcValues == NULL)
		return S_OK;

	CShortData *pShortData = NULL;
	CValue *pSrcValue = NULL;
	POS pos = pSrcValues->m_listChild.GetHeadPosition();
	while(pos != NULL)
	{
		pSrcValue = pSrcValues->m_listChild.GetNext(pos);
		pShortData = m_listChild.FindByID(pSrcValue->m_strID);
		if(pShortData != NULL)
			pShortData->m_strValue = pSrcValue->m_strValue;
	}
	return S_OK;
}

STDMETHODIMP CShortDatas::GetValues(IDispatch** pIValues)
{
	// TODO: 在此添加实现代码
	CValues *pValues = CValues::_new_CValues();
	long nCount = m_listChild.GetCount();
	for(long i=0;i<nCount;i++)
	{
		CShortData *pShortData = m_listChild.GetAtIndex(i);
		CValue* pValue = NULL;
		pValue = CValue::_new_CValue();
		pValue->m_strID = pShortData->m_strID;
		pValue->m_strValue = pShortData->m_strValue;
		pValues->m_listChild.AddTail(pValue);
	}
	pValues->QueryInterface(IID_IDispatch,(void**)pIValues);  

	return S_OK;
}


long CShortDatas::_XmlReadOwn(const MSXML::IXMLDOMNodePtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{
	xml_GetAttibuteValue(pXmlRWKeys->m_strDatasNameAttrKey,oNode,m_strName);
	xml_GetAttibuteValue(pXmlRWKeys->m_strDatasIDAttrKey,oNode,m_strID);
	return 0;
}

long CShortDatas::_XmlReadChildren(const MSXML::IXMLDOMNodeListPtr &oNodes, CDataXMLRWKeys *pXmlRWKeys)
{
	long nCount = oNodes->Getlength();
	long nIndex = 0;
	IDispatch *pNew = NULL;
	

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		MSXML::IXMLDOMNodePtr oNode = NULL;
		oNode = oNodes->Getitem(nIndex);
		pNew = _CreateNewChild(oNode,pXmlRWKeys);
	}
	return 0;
}

IDispatch* CShortDatas::_CreateNewChild(MSXML::IXMLDOMNodePtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{
	_bstr_t strNodeName;
	strNodeName = oNode->GetnodeName();
	IDispatch* pNew = NULL;
	CComBSTR bstrNodeName = strNodeName.GetBSTR();
	if (bstrNodeName == pXmlRWKeys->m_strDataElementKey)
	{
		CShortData *pVal = CShortData::_new_CShortData();
		pVal->_XmlRead(oNode, pXmlRWKeys);
		m_listChild.AddTail(pVal);
	}
	else
	{
	}
	return pNew;
}

long CShortDatas::_XmlWriteOwn(MSXML::IXMLDOMElementPtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{
	oNode->setAttribute(_bstr_t(pXmlRWKeys->m_strDatasNameAttrKey),(_bstr_t)(m_strName));
	oNode->setAttribute(_bstr_t(pXmlRWKeys->m_strDatasIDAttrKey),(_bstr_t)(m_strID));
	return 0;
}

long CShortDatas::_XmlWriteChildren(MSXML::IXMLDOMElementPtr &oParent, CDataXMLRWKeys *pXmlRWKeys)
{
	int nCount = m_listChild.GetCount();
	CShortData* pValue = NULL;

	MSXML::IXMLDOMDocumentPtr oXMLDoc = pXmlRWKeys->m_oXMLDoc;

	for (int i=0;i<nCount;i++)
	{
		MSXML::IXMLDOMElementPtr oData;
		pValue = m_listChild.GetAtIndex(i);
		oData = oXMLDoc->createElement(_bstr_t(pXmlRWKeys->m_strDataElementKey));
		oParent->appendChild(oData);
		pValue->_XmlWrite(oData,pXmlRWKeys);
	}
	return 0;
}
STDMETHODIMP CShortDatas::IsEqual(IDispatch* pISrcObj, LONG* pnEqual)
{
	// TODO: 在此添加实现代码
	ATLASSERT(pISrcObj != NULL);
	if(pISrcObj == NULL)
	{
		*pnEqual = 0;
		return S_OK;
	}
	
	CShortDatas* pShortDatas = FromIDispatch(pISrcObj);
	ATLASSERT(pShortDatas != NULL);
	if(pShortDatas == NULL)
	{
		*pnEqual = 0;
		return S_OK;
	}
	
	long nCount1 = m_listChild.GetCount();
	long nCount2 = pShortDatas->m_listChild.GetCount();

	if(nCount1 != nCount2)
	{
		*pnEqual = 0;
		return S_OK;
	}
	if(nCount1 == 0 && nCount2 ==0)
	{
		*pnEqual = 1;
		return S_OK;
	}
	for(long i=0;i<nCount1;i++)
	{
		CShortData *pShortData = m_listChild.GetAtIndex(i);
		CShortData* pShortDataSrc = pShortDatas->m_listChild.GetAtIndex(i);
		if(!pShortData->_IsEqual(pShortDataSrc))
			*pnEqual = 0;
	}
	*pnEqual = 1;

	return S_OK;
}
