// LongDatas.cpp : CLongDatas ��ʵ��

#include "stdafx.h"
#include "LongDatas.h"
#include "DataTypes.h"
#include "Equation.h"

// CLongDatas

STDMETHODIMP CLongDatas::get_Name(BSTR* pVal)
{
	// TODO: �ڴ����ʵ�ִ���
	*pVal = m_strName.Copy();
	return S_OK;
}

STDMETHODIMP CLongDatas::put_Name(BSTR newVal)
{
	// TODO: �ڴ����ʵ�ִ���
	m_strName = newVal;
	return S_OK;
}

STDMETHODIMP CLongDatas::get_ID(BSTR* pVal)
{
	// TODO: �ڴ����ʵ�ִ���
	*pVal = m_strID.Copy();
	return S_OK;
}

STDMETHODIMP CLongDatas::put_ID(BSTR newVal)
{
	// TODO: �ڴ����ʵ�ִ���
	m_strID = newVal;
	return S_OK;
}

STDMETHODIMP CLongDatas::get_Script(BSTR* pVal)
{
	// TODO: �ڴ����ʵ�ִ���
	*pVal = m_strScript;
	return S_OK;
}

STDMETHODIMP CLongDatas::put_Script(BSTR newVal)
{
	// TODO: �ڴ����ʵ�ִ���
	m_strScript = newVal;
	return S_OK;
}



STDMETHODIMP CLongDatas::get_Show(SHORT* pVal)
{
	// TODO: �ڴ����ʵ�ִ���
	*pVal = m_sShow;
	return S_OK;
}

STDMETHODIMP CLongDatas::put_Show(SHORT newVal)
{
	// TODO: �ڴ����ʵ�ִ���
	m_sShow = newVal;
	return S_OK;
}

STDMETHODIMP CLongDatas::get_Enable(SHORT* pVal)
{
	// TODO: �ڴ����ʵ�ִ���
	*pVal = m_sEnable;
	return S_OK;
}

STDMETHODIMP CLongDatas::put_Enable(SHORT newVal)
{
	// TODO: �ڴ����ʵ�ִ���
	m_sEnable = newVal;
	return S_OK;
}

STDMETHODIMP CLongDatas::GetCount(LONG* pnCount)
{
	// TODO: �ڴ����ʵ�ִ���
	*pnCount = m_listChild.GetCount();
	return S_OK;
}

STDMETHODIMP CLongDatas::GetItem(LONG nIndex, IDispatch** pILongData)
{
	// TODO: �ڴ����ʵ�ִ���
	CLongData *pLongData = m_listChild.GetAtIndex(nIndex);
	pLongData->QueryInterface(IID_IDispatch,(void**)pILongData);
	//m_listChild.GetAtIndexIDispatch(nIndex);
	return S_OK;
}

STDMETHODIMP CLongDatas::FindByName(BSTR bstrName, IDispatch** pILongData)
{
	// TODO: �ڴ����ʵ�ִ���
	CLongData *pLongData = NULL;
	pLongData = m_listChild.FindByName(bstrName);
	if(pLongData != NULL)
	{
		*pILongData = pLongData->_QueryIDispatch();
	}
	else
	{
		*pILongData = NULL;
	}
	return S_OK;
}

STDMETHODIMP CLongDatas::FindByID(BSTR bstrID, IDispatch** pILongData)
{
	// TODO: �ڴ����ʵ�ִ���
	CLongData *pLongData = NULL;
	pLongData = m_listChild.FindByID(bstrID);
	if(pLongData != NULL)
	{
		*pILongData = pLongData->_QueryIDispatch();
	}
	else
	{
		*pILongData = NULL;
	}
	return S_OK;
}

STDMETHODIMP CLongDatas::AddNew(IDispatch** pILongData)
{
	// TODO: �ڴ����ʵ�ִ���
	CLongData *pLongData = CLongData::_new_CLongData();
	if(pLongData != NULL)
	{
		*pILongData = pLongData->_QueryIDispatch();
		m_listChild.AddTail(pLongData);
	}
	return S_OK;
}

STDMETHODIMP CLongDatas::AddNew2(BSTR bstrName, BSTR bstrID, BSTR bstrDataTypeID, BSTR bstrUnit, BSTR bstrValue, IDispatch** pILongData)
{
	// TODO: �ڴ����ʵ�ִ���
	if (m_listChild.FindByID(bstrID)!=NULL)
	{
		*pILongData =NULL;
		return S_FALSE;
	}

	CLongData *pLongData = CLongData::_new_CLongData();
	ATLASSERT(pLongData != NULL);
	if(pLongData != NULL)
	{
		pLongData->m_strName = bstrName;
		pLongData->m_strID = bstrID;
		pLongData->m_strUnit = bstrUnit;
		pLongData->m_strDataTypeID = bstrDataTypeID;
		pLongData->m_strValue = bstrValue;
		*pILongData = pLongData->_QueryIDispatch();
		m_listChild.AddTail(pLongData);
	}
	return S_OK;
}

STDMETHODIMP CLongDatas::AddNew3(BSTR bstrName, BSTR bstrID, BSTR bstrUnit, BSTR bstrDataTypeID, BSTR bstrValue, 
								 BSTR bstrValueName, BSTR bstrDefaultValue, BSTR bstrScript, BSTR bstrDataTypeDomain, 
								 BSTR bstrMessage, SHORT nType, SHORT nShow, SHORT nEnable, LONG nReserved, 
								 LONG nReserved2, BSTR strFormat, IDispatch** pILongData)
{
	// TODO: �ڴ����ʵ�ִ���
	if (m_listChild.FindByID(bstrID)!=NULL)
	{
		*pILongData =NULL;
		return S_FALSE;
	}
	CLongData *pLongData = CLongData::_new_CLongData();
	ATLASSERT(pLongData != NULL);
	if(pLongData != NULL)
	{
		pLongData->m_strName = bstrName;
		pLongData->m_strID = bstrID;
		pLongData->m_strUnit = bstrUnit;
		pLongData->m_strDataTypeID = bstrDataTypeID;
		pLongData->m_strValue = bstrValue;
		pLongData->m_strValueName = bstrValueName;
		pLongData->m_strDefaultValue = bstrDefaultValue;
		pLongData->m_strScript = bstrScript;
		pLongData->m_strDataTypeDomain = bstrDataTypeDomain;
		pLongData->m_strMessage = bstrMessage;
		pLongData->m_sType = nType;
		pLongData->m_sShow = nShow;
		pLongData->m_sEnable = nEnable;
		pLongData->m_nReserved = nReserved;
		pLongData->m_nReserved2 = nReserved2;
		pLongData->m_strFormat = strFormat;
		*pILongData = pLongData->_QueryIDispatch();
		m_listChild.AddTail(pLongData);
	}
	return S_OK;
}

STDMETHODIMP CLongDatas::Delete(VARIANT* vIndex, LONG* pnReturn)
{
	// TODO: �ڴ����ʵ�ִ���
	m_listChild.Delete(vIndex,pnReturn);
	return S_OK;
}

STDMETHODIMP CLongDatas::Append(IDispatch* pILongDatas)
{
	// TODO: �ڴ����ʵ�ִ���
	ATLASSERT(pILongDatas != NULL);
	if(pILongDatas == NULL)
	{
		return S_OK;
	}
	CLongDatas *pLongDatas = CLongDatas::FromIDispatch(pILongDatas);
	_Append(pLongDatas);
	return S_OK;
}

STDMETHODIMP CLongDatas::Clone(IDispatch** pILongDatas)
{
	// TODO: �ڴ����ʵ�ִ���
	CComObject<CLongDatas> *pLongDatas = NULL;
	CComObject<CLongDatas>::CreateInstance(&pLongDatas);

	if(pLongDatas != NULL)
	{
		pLongDatas->_Append(this);
		pLongDatas->QueryInterface(IID_ILongDatas,(void**)pILongDatas);
	}
	else
	{
		*pILongDatas = NULL;
	}
	return S_OK;
}

STDMETHODIMP CLongDatas::SetValueByName(BSTR bstrName, BSTR bstrValue)
{
	// TODO: �ڴ����ʵ�ִ���
	CLongData* pLongData = m_listChild.FindByName(bstrName);
	ATLASSERT(pLongData != NULL);
	pLongData->m_strValue = bstrValue;
	return S_OK;
}

STDMETHODIMP CLongDatas::SetValueByID(BSTR bstrID, BSTR bstrValue)
{
	// TODO: �ڴ����ʵ�ִ���
	CLongData* pLongData = m_listChild.FindByID(bstrID);
	ATLASSERT(pLongData != NULL);
	if(pLongData != NULL)
		pLongData->m_strValue = bstrValue;
	return S_OK;
}

STDMETHODIMP CLongDatas::DeleteAll(void)
{
	// TODO: �ڴ����ʵ�ִ���
	m_listChild.DeleteAll();
	return S_OK;
}

STDMETHODIMP CLongDatas::ChangePosition(VARIANT* vIndex1, VARIANT* vIndex2)
{
	// TODO: �ڴ����ʵ�ִ���
	m_listChild.ChangePosition(vIndex1,vIndex2);
	return S_OK;
}

STDMETHODIMP CLongDatas::ReSetValues(void)
{
	// TODO: �ڴ����ʵ�ִ���
	CLongData* pLongData = NULL;
	int nCount = m_listChild.GetCount();
	for (int i=0;i<nCount;i++)
	{
		pLongData = m_listChild.GetAtIndex(i);
		ATLASSERT(pLongData!=NULL);
		pLongData->m_strValue = pLongData->m_strDefaultValue;
	}
	return S_OK;
}

STDMETHODIMP CLongDatas::InitValueName(IDispatch* pIDataTypes)
{
	// TODO: �ڴ����ʵ�ִ���
	CLongData* pLongData = NULL;
	CDataTypes* pDataTypes = CDataTypes::FromIDispatch(pIDataTypes);
	CDataType* pDataType = NULL;
	int nCount = m_listChild.GetCount();
	int nTypes = pDataTypes->m_listChild.GetCount();

	for (int i=0;i<nCount;i++)
	{
		pLongData = m_listChild.GetAtIndex(i);
		for (int j=0;j<nTypes;j++)
		{
			pDataType = pDataTypes->m_listChild.GetAtIndex(i);
			if (pDataType!=NULL)
			{
				if (pLongData->m_strID==pDataType->m_strID)
				{
					pLongData->m_strValueName = pDataType->m_strName;
					break;
				}
			}
		}
	}

	return S_OK;
}

STDMETHODIMP CLongDatas::SetValuesByDatas(IDispatch* pILongDatas)
{
	// TODO: �ڴ����ʵ�ִ���
	ATLASSERT(pILongDatas!=NULL);
	CLongDatas *pSrcLongDatas = FromIDispatch(pILongDatas);
	ATLASSERT(pSrcLongDatas!=NULL);
	CLongData* pLongData = NULL;
	CLongData* pSrcLongData = NULL;

	int nCount = pSrcLongDatas->m_listChild.GetCount();
	int nIndex = 0;

	POS pos = pSrcLongDatas->m_listChild.GetHeadPosition();
	while (pos != NULL)
	{
		pSrcLongData = pSrcLongDatas->m_listChild.GetNext(pos);
		pLongData = m_listChild.FindByID(pSrcLongData->m_strID);

		if (pLongData != NULL)
		{
			pLongData->m_strValue = pSrcLongData->m_strValue;
		}
	}

	return S_OK;
}

STDMETHODIMP CLongDatas::SetValuesByEquation(IDispatch* pIEquation)
{
	// TODO: �ڴ����ʵ�ִ���
	CWEquationBuffer* pEquationBuf = CEquation::FromIDispatch(pIEquation);
	CWEqtnKey* pEqtnKey = NULL;
	int nCountEqt = pEquationBuf->GetKeyCount();

	CLongData* pLongData = NULL;
	int nCount = m_listChild.GetCount();

		for (int j=0;j<nCountEqt;j++)
		{
			pEqtnKey = pEquationBuf->FindEquationKey(j);
			pLongData = m_listChild.FindByID(pEqtnKey->m_strKeyName);
			if (pLongData!=NULL)
			{
				pLongData->m_strValue = pEqtnKey->m_strKeyValue.Copy();
			}
		}

	return S_OK;
}

STDMETHODIMP CLongDatas::SetValuesByString(BSTR bstrValues)
{
	// TODO: �ڴ����ʵ�ִ���
	LONG n;
	CComObject<CEquation>* pEquation = NULL;
	CComObject<CEquation>::CreateInstance(&pEquation);
	pEquation->SetEquation(bstrValues,&n);
	IDispatchPtr pIDisp=NULL;
	pEquation->QueryInterface(IID_IDispatch,(void**)&pIDisp);
	SetValuesByEquation(pIDisp);

	return S_OK;
}

int CLongDatas::_Append(CLongDatas* pLongDatas)
{
	CLongData *pData = NULL;
	CLongData *pNew = NULL;
	POS pos = pLongDatas->m_listChild.GetHeadPosition();

	while (pos != NULL)
	{
		pData = pLongDatas->m_listChild.GetNext(pos);
		m_listChild.AddTail(pData);
	}
	return 1;
}

int CLongDatas::_CloneAppend(CLongDatas* pLongDatas)
{
	CLongData *pData = NULL;
	CLongData *pNew = NULL;
	POS pos = pLongDatas->m_listChild.GetHeadPosition();

	while (pos != NULL)
	{
		pData = pLongDatas->m_listChild.GetNext(pos);
		pNew = CLongData::_new_CLongData(pData);
		m_listChild.AddTail(pNew);
	}

	return 1;
}

STDMETHODIMP CLongDatas::GetDatasString(LONG nNameFormat,LONG nValueFormat, LONG nWithUnit,BSTR *pbstrValues)
{
	// TODO: �ڴ����ʵ�ִ���
	CLongData* pLongData = NULL;
	int nCount = m_listChild.GetCount();
	CComBSTR str;
	CComBSTR strTemp;
	for (int Index=0;Index<nCount;Index++)
	{
		pLongData = m_listChild.GetAtIndex(Index);
		if (0==nNameFormat&&0==nValueFormat)
		{
			str += pLongData->m_strName;
			str+=L"=";
			str+=pLongData->m_strValue;
		}
		else if (0==nNameFormat&&1==nValueFormat)
		{
			str += pLongData->m_strName;
			str+=L"=";
			str+=pLongData->m_strValueName;
		}
		else if (1==nNameFormat&&0==nValueFormat)
		{
			str += pLongData->m_strID;
			str+=L"=";
			str+=pLongData->m_strValue;
		}
		else
		{
			str += pLongData->m_strID;
			str+=L"=";
			str+=pLongData->m_strValueName;
		}
		if (0==nWithUnit)
		{
			str+=pLongData->m_strUnit;
		}
		str+=L";";
		strTemp = str.Copy();
		strTemp+=";";
	}
	*pbstrValues = str.Copy();
	return S_OK;
}
long CLongDatas::_XmlReadOwn(const MSXML::IXMLDOMNodePtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{
	xml_GetAttibuteValue(pXmlRWKeys->m_strDatasNameAttrKey,oNode,m_strName);
	xml_GetAttibuteValue(pXmlRWKeys->m_strDatasIDAttrKey,oNode,m_strID);
	xml_GetAttibuteValue(pXmlRWKeys->m_strScriptKey,oNode,m_strScript);
	CComBSTR bstr1;
	LONG_to_CComBSTR(m_sShow,bstr1);
	xml_GetAttibuteValue(pXmlRWKeys->m_strShowKey,oNode,bstr1);
	LONG_to_CComBSTR(m_sEnable,bstr1);
	xml_GetAttibuteValue(pXmlRWKeys->m_strEnableKey,oNode,bstr1);

	return 0;
}

long CLongDatas::_XmlReadChildren(const MSXML::IXMLDOMNodeListPtr &oNodes, CDataXMLRWKeys *pXmlRWKeys)
{
	XML_READ_CHILDREN_CODE(oNodes,pXmlRWKeys);
	return 0;
}

IDispatch* CLongDatas::_CreateNewChild(MSXML::IXMLDOMNodePtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{
	XML_CREATE_NEW_CHILD_CODE(CLongData,pXmlRWKeys->m_strDataElementKey,oNode,pXmlRWKeys);
}

long CLongDatas::_XmlWriteOwn(MSXML::IXMLDOMElementPtr &oNode, CDataXMLRWKeys *pXmlRWKeys)
{
	oNode->setAttribute(_bstr_t(pXmlRWKeys->m_strDatasNameAttrKey),(_bstr_t)(m_strName));
	oNode->setAttribute(_bstr_t(pXmlRWKeys->m_strDatasIDAttrKey),(_bstr_t)(m_strID));
	oNode->setAttribute(_bstr_t(pXmlRWKeys->m_strScriptKey),(_bstr_t)(m_strScript));

	oNode->setAttribute(_bstr_t(pXmlRWKeys->m_strShowKey),m_sShow);
	oNode->setAttribute(_bstr_t(pXmlRWKeys->m_strEnableKey),m_sEnable);
	return 0;
}

long CLongDatas::_XmlWriteChildren(MSXML::IXMLDOMElementPtr &oParent, CDataXMLRWKeys *pXmlRWKeys)
{
	XML_WRITE_CHILDREN_CODE(CLongData,pXmlRWKeys->m_strDataElementKey,oParent,pXmlRWKeys)
	return 0;
}
STDMETHODIMP CLongDatas::XMLWrite(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	XML_INTERFACE_WRITE(pIXMLElement,pIXMLKeys)
	return S_OK;
}
STDMETHODIMP CLongDatas::XMLRead(IDispatch* pIXMLElement, IDispatch* pIXMLKeys)
{
	XML_INTERFACE_READ(pIXMLElement,pIXMLKeys)
	return S_OK;
}