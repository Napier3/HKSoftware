#include "stdafx.h"
#include "SttXmlSerializeBase.h"
#include <math.h>

#include"../../../Module/API/GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
#endif

#define _STT_XML_NEW_NAME_LEN_   200


BOOL CSttXmlSerializeBase::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,CString &strAttrVal, BSTR bstrElementKey ) {	return FALSE;	}
BOOL CSttXmlSerializeBase::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,wchar_t *strAttrVal, BSTR bstrElementKey ) {	return FALSE;	}
BOOL CSttXmlSerializeBase::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,long &nAttrVal, BSTR bstrElementKey ) {	return FALSE;	}
BOOL CSttXmlSerializeBase::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,int &nAttrVal, BSTR bstrElementKey ) {	return FALSE;	}
BOOL CSttXmlSerializeBase::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,unsigned int &unAttrVal, BSTR bstrElementKey ) {	return FALSE;	}
#ifdef _PSX_QT_LINUX_
BOOL CSttXmlSerializeBase::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,BOOL &bAttrVal, BSTR bstrElementKey ) {	return FALSE;	}
#endif
BOOL CSttXmlSerializeBase::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,double &dAttrVal, BSTR bstrElementKey ) {	return FALSE;	}
BOOL CSttXmlSerializeBase::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,short &unAttrVal, BSTR bstrElementKey ) {	return FALSE;	}
BOOL CSttXmlSerializeBase::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,float &fAttrVal, BSTR bstrElementKey ) {	return FALSE;	}
BOOL CSttXmlSerializeBase::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,char *strAttrVal, BSTR bstrElementKey ) {	return FALSE;	}

CSttXmlSerializeBase* CSttXmlSerializeBase::xml_serialize(const char *pszName,const char *pszID, const char *pszDataTypeID, BSTR bstrElementKey ) {	return NULL;	}
CSttXmlSerializeBase* CSttXmlSerializeBase::xml_serialize(const char *pszName,const char *pszID, long nIndex, const char *pszDataTypeID, BSTR bstrElementKey ) {	return NULL;	}

//2021-6-1  lijunqing : use bstrElementKey and nIndex 
CSttXmlSerializeBase* CSttXmlSerializeBase::xml_serialize(BSTR bstrElementKey, long nIndex, const char *pszName,const char *pszID, const char *pszDataTypeID) {	return NULL;	}

BOOL CSttXmlSerializeBase::xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
									double &dAttrVal,const char *pszSysParaID, BSTR bstrElementKey)
{
	return FALSE;
}

BOOL CSttXmlSerializeBase::xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
									float &fAttrVal,const char *pszSysParaID, BSTR bstrElementKey)
{
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//
void stt_get_xml_new_name_id(const char *pszName, const char *pszID, long nIndex, char *pszNewName, char *pszNewID)
{
	memset(pszNewName, 0, _STT_XML_NEW_NAME_LEN_);
	sprintf(pszNewName, "%s%d", pszName, nIndex+1);

	memset(pszNewID, 0, _STT_XML_NEW_NAME_LEN_);
	sprintf(pszNewID, "%s%d", pszID, nIndex);
}

//////////////////////////////////////////////////////////////////////////
//CSttXmlSerializeRead
CSttXmlSerializeRead::CSttXmlSerializeRead(CXmlRWDocBase *pXmlDoc, CXmlRWElementBase *pElement)
:CSttXmlSerializeBase(pXmlDoc, pElement)
{

}

CSttXmlSerializeRead::~CSttXmlSerializeRead()
{

}

CXmlRWElementBase* CSttXmlSerializeRead::FindElement(const char *pszID, BSTR bstrElementKey)
{
	wchar_t *pwszID = NULL;
	str_char_to_wchar(&pwszID, pszID);
    CXmlRWElementBase *pFind = NULL;

	if (bstrElementKey == NULL)
    {
        pFind = (CXmlRWElementBase*)m_pXmlElement->GetChildNode(stt_ParaKey(), stt_IDKey(), pwszID);
	}
	else
	{
		pFind = (CXmlRWElementBase*)m_pXmlElement->GetChildNode(bstrElementKey, stt_IDKey(), pwszID);
	}

	delete pwszID;

	return pFind;
}

CXmlRWElementBase* CSttXmlSerializeRead::FindElement(BSTR bstrElementKey, long nIndex)
{
	CXmlRWElementBase *p = NULL;
	CXmlRWElementBase *pFind = NULL;
	CXmlRWNodeListBase *pChildNodeList = m_pXmlElement->GetChildNodes();
	long nCount = pChildNodeList->GetNodeNum();

	long k = 0;
	CXmlRWNodeBase *pNode = NULL;
	CString strNodeName;
	long nIndexFind = 0;

	for (k=0; k<nCount; k++)
	{
		pNode =pChildNodeList->GetChild(k);

		if (pNode == NULL)
		{
			continue;
		}

		strNodeName = pNode->GetNodeName();

		if (strNodeName == bstrElementKey)
		{
			if (nIndexFind == nIndex)
			{
				pFind = (CXmlRWElementBase*)pNode;
				break;
			}

			nIndexFind++;
		}
	}

	return pFind;
}

CXmlRWElementBase* CSttXmlSerializeRead::FindElement(BSTR bstrElementKey, BSTR bstrAttrID, const char *pszAttrValue,   long nIndex)  //2021-6-5  lijunqing
{
	CXmlRWElementBase *p = NULL;
	CXmlRWElementBase *pFind = NULL;
	CXmlRWNodeListBase *pChildNodeList = m_pXmlElement->GetChildNodes();
	long nCount = pChildNodeList->GetNodeNum();

	long k = 0;
	CXmlRWNodeBase *pNode = NULL;
	CString strNodeName;
	long nIndexFind = 0;
	CString strValue;

	for (k=0; k<nCount; k++)
	{
		pNode =pChildNodeList->GetChild(k);

		if (pNode == NULL)
		{
			continue;
		}

		strNodeName = pNode->GetNodeName();

		if (strNodeName == bstrElementKey)
		{
			if (!pNode->xml_GetAttibuteValue(bstrAttrID, strValue))
			{
				continue;
			}

			if (strValue != pszAttrValue)
			{
				continue;
			}

			if (nIndexFind == nIndex)
			{
				pFind = (CXmlRWElementBase*)pNode;
				break;
			}

			nIndexFind++;
		}
	}

	return pFind;
}

BOOL CSttXmlSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,CString &strAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pFind = FindElement(pszID, bstrElementKey);

	if (pFind != NULL)
	{
		if (pFind->IsEmpty())
		{
			return FALSE;
		}
		else
		{
			xml_GetAttibuteValue(stt_ValueKey(), *pFind, strAttrVal);
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CSttXmlSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,wchar_t *strAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pFind = FindElement(pszID, bstrElementKey);

	if (pFind != NULL)
	{
		if (pFind->IsEmpty())
		{
			return FALSE;
		}
		else
		{
			xml_GetAttibuteValue(stt_ValueKey(), *pFind, strAttrVal);
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CSttXmlSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,long &nAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pFind = FindElement(pszID, bstrElementKey);

	if (pFind != NULL)
	{
		if (pFind->IsEmpty())
		{
			return FALSE;
		}
		else
		{
			xml_GetAttibuteValue(stt_ValueKey(), *pFind, nAttrVal);
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CSttXmlSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,int &nAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pFind = FindElement(pszID, bstrElementKey);

	if (pFind != NULL)
	{
		if (pFind->IsEmpty())
		{
			return FALSE;
		}
		else
		{
			long nTemp;
			xml_GetAttibuteValue(stt_ValueKey(), *pFind, nTemp);
			nAttrVal = nTemp;
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CSttXmlSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,unsigned int &unAttrVal, BSTR bstrElementKey)
{
    CXmlRWElementBase *pFind = FindElement(pszID, bstrElementKey);

    if (pFind != NULL)
    {
        if (pFind->IsEmpty())
        {
            return FALSE;
        }
        else
        {
            long nTemp;
            xml_GetAttibuteValue(stt_ValueKey(), *pFind, nTemp);
            unAttrVal = nTemp;
            return TRUE;
        }
    }
    else
    {
        return FALSE;
    }
}

#ifdef _PSX_QT_LINUX_
BOOL CSttXmlSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,BOOL &bAttrVal, BSTR bstrElementKey)
{
    CXmlRWElementBase *pFind = FindElement(pszID, bstrElementKey);

    if (pFind != NULL)
    {
        if (pFind->IsEmpty())
        {
            return FALSE;
        }
        else
        {
            long nTemp;
            xml_GetAttibuteValue(stt_ValueKey(), *pFind, nTemp);
            bAttrVal = nTemp;
            return TRUE;
        }
    }
    else
    {
        return FALSE;
    }
}
#endif

BOOL CSttXmlSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,double &dAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pFind = FindElement(pszID, bstrElementKey);

	if (pFind != NULL)
	{
		if (pFind->IsEmpty())
		{
			return FALSE;
		}
		else
		{
			xml_GetAttibuteValue(stt_ValueKey(), *pFind, dAttrVal);
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CSttXmlSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,short &unAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pFind = FindElement(pszID, bstrElementKey);

	if (pFind != NULL)
	{
		if (pFind->IsEmpty())
		{
			return FALSE;
		}
		else
		{
			xml_GetAttibuteValue(stt_ValueKey(), *pFind, unAttrVal);
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CSttXmlSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,float &fAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pFind = FindElement(pszID, bstrElementKey);

	if (pFind != NULL)
	{
		if (pFind->IsEmpty())
		{
			return FALSE;
		}
		else
		{
			xml_GetAttibuteValue(stt_ValueKey(), *pFind, fAttrVal);
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CSttXmlSerializeRead::xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
												  double &dAttrVal,const char *pszSysParaID, BSTR bstrElementKey)
{
	return xml_serialize(pszName,pszID,pszUnit,pszDataTypeID,dAttrVal,bstrElementKey);
}

BOOL CSttXmlSerializeRead::xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
												  float &fAttrVal,const char *pszSysParaID, BSTR bstrElementKey)
{
	return xml_serialize(pszName,pszID,pszUnit,pszDataTypeID,fAttrVal,bstrElementKey);
}

BOOL CSttXmlSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,char *strAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pFind = FindElement(pszID, bstrElementKey);

	if (pFind != NULL)
	{
		if (pFind->IsEmpty())
		{
			return FALSE;
		}
		else
		{
			CString strTemp;
			xml_GetAttibuteValue(stt_ValueKey(), *pFind, strTemp);
			CString_to_char(strTemp, strAttrVal);
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

CSttXmlSerializeBase* CSttXmlSerializeRead::xml_serialize(const char *pszName,const char *pszID, const char *pszDataTypeID, BSTR bstrElementKey)
{
	CXmlRWElementBase *pFind = FindElement(pszID, bstrElementKey);

	if (pFind==NULL)
	{
		return NULL;
	}

	if (pFind->IsEmpty())
	{
		return NULL;
	}

	CSttXmlSerializeBase *pNew =create_new(m_pXmlDoc, pFind, TRUE);
	pNew->m_strName = pszName;
	pNew->m_strID = pszID;
	return pNew;
}

CSttXmlSerializeBase* CSttXmlSerializeRead::xml_serialize(const char *pszName,const char *pszID, long nIndex, const char *pszDataTypeID, BSTR bstrElementKey)
{
	char pszNewName[_STT_XML_NEW_NAME_LEN_], pszNewID[_STT_XML_NEW_NAME_LEN_];
	stt_get_xml_new_name_id(pszName, pszID, nIndex, pszNewName, pszNewID);

	CXmlRWElementBase *pFind = FindElement(pszNewID, bstrElementKey);

	if (pFind==NULL)
	{
		return NULL;
	}

	if (pFind->IsEmpty())
	{
		return NULL;
	}
	else
	{
		CSttXmlSerializeBase *pNew =create_new(m_pXmlDoc, pFind, TRUE);
		pNew->m_strName = pszNewName;
		pNew->m_strID = pszNewID;
		return pNew;
	}
}

//2021-6-1  lijunqing : use bstrElementKey and nIndex 
CSttXmlSerializeBase* CSttXmlSerializeRead::xml_serialize(BSTR bstrElementKey, long nIndex, const char *pszName,const char *pszID, const char *pszDataTypeID)
{
	CXmlRWElementBase *pFind = FindElement(bstrElementKey, stt_DataTypeKey(), pszDataTypeID, nIndex);

	if (pFind==NULL)
	{
		return NULL;
	}

	if (pFind->IsEmpty())
	{
		return NULL;
	}
	else
	{
		CSttXmlSerializeBase *pNew =create_new(m_pXmlDoc, pFind, TRUE);
		pNew->m_strName.Format(_T("%s%ld"),pszName,nIndex+1);
		pNew->m_strID.Format(_T("%s%ld"),pszID,nIndex);
		return pNew;
	}
}


//////////////////////////////////////////////////////////////////////////
//CSttXmlSerializeWrite
CSttXmlSerializeWrite::CSttXmlSerializeWrite(CXmlRWDocBase *pXmlDoc, CXmlRWElementBase *pElement)
:CSttXmlSerializeBase(pXmlDoc, pElement)
{

}

CSttXmlSerializeWrite::~CSttXmlSerializeWrite()
{

}

BOOL CSttXmlSerializeWrite::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,CString &strAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

//    xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	//xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	//xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	//xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, strAttrVal);

	return TRUE;
}

BOOL CSttXmlSerializeWrite::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,wchar_t *strAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

//    xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	//xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	//xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	//xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, strAttrVal);

	return TRUE;
}

BOOL CSttXmlSerializeWrite::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,long &nAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

//    xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	//xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	//xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	//xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, nAttrVal);

	return TRUE;
}

BOOL CSttXmlSerializeWrite::xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
												  double &dAttrVal,const char *pszSysParaID, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

	//    xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	//xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	//xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	//xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, dAttrVal);
	//xml_SetAttributeValue(stt_FormatKey(), *pDataElement, pszSysParaID);
	return TRUE;
	//return xml_serialize(pszName,pszID,pszUnit,pszDataTypeID,dAttrVal,bstrElementKey);
}

BOOL CSttXmlSerializeWrite::xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
												  float &fAttrVal,const char *pszSysParaID, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

	//    xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	//xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	//xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	//xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, fAttrVal);
	//xml_SetAttributeValue(stt_FormatKey(), *pDataElement, pszSysParaID);
	return TRUE;
	//return xml_serialize(pszName,pszID,pszUnit,pszDataTypeID,fAttrVal,bstrElementKey);
}

BOOL CSttXmlSerializeWrite::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,int &nAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

//    xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	//xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	//xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	//xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
	long nTemp = nAttrVal;
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, nTemp);

	return TRUE;
}

BOOL CSttXmlSerializeWrite::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,unsigned int &unAttrVal, BSTR bstrElementKey)
{
    CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
    ASSERT (pDataElement != NULL);

    if (pDataElement == NULL)
    {
        return FALSE;
    }

//    xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
    xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
    //xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
    //xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
    //xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
    long nTemp = unAttrVal;
    xml_SetAttributeValue(stt_ValueKey(), *pDataElement, nTemp);

    return TRUE;
}

#ifdef _PSX_QT_LINUX_
BOOL CSttXmlSerializeWrite::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,BOOL &bAttrVal, BSTR bstrElementKey)
{
    CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
    ASSERT (pDataElement != NULL);

    if (pDataElement == NULL)
    {
        return FALSE;
    }

//    xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
    xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
    //xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
    //xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
    //xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
    long nTemp = bAttrVal;
    xml_SetAttributeValue(stt_ValueKey(), *pDataElement, nTemp);

    return TRUE;
}
#endif

BOOL CSttXmlSerializeWrite::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,double &dAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

//    xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	//xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	//xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	//xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, dAttrVal);

	return TRUE;
}

BOOL CSttXmlSerializeWrite::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,short &unAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

//    xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	//xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	//xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	//xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, unAttrVal);

	return TRUE;
}

BOOL CSttXmlSerializeWrite::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,float &fAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

//    xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	//xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	//xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	//xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, fAttrVal);

	return TRUE;
}

BOOL CSttXmlSerializeWrite::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,char *strAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

//    xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	//xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	//xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	//xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, strAttrVal);

	return TRUE;
}

CSttXmlSerializeBase* CSttXmlSerializeWrite::xml_serialize(const char *pszName,const char *pszID, const char *pszDataTypeID, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return NULL;
	}

//	xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);

	CSttXmlSerializeBase *pNew = create_new(m_pXmlDoc, pDataElement, TRUE);
	pNew->m_strName = pszName;
	pNew->m_strID = pszID;

	// 	CSttXmlSerializeRegister *pNew = new CSttXmlSerializeRegister(m_pXmlDoc, pDataElement);
	// 	AddNewChild(pNew);

	return pNew;
}

CSttXmlSerializeBase* CSttXmlSerializeWrite::xml_serialize(const char *pszName,const char *pszID, long nIndex, const char *pszDataTypeID, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return NULL;
	}

	char pszNewName[_STT_XML_NEW_NAME_LEN_], pszNewID[_STT_XML_NEW_NAME_LEN_];
	stt_get_xml_new_name_id(pszName, pszID, nIndex, pszNewName, pszNewID);

//	xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszNewName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszNewID);
	xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);

	CSttXmlSerializeBase *pNew = create_new(m_pXmlDoc, pDataElement, TRUE);
	pNew->m_strName = pszNewName;
	pNew->m_strID = pszNewID;

// 	CSttXmlSerializeRegister *pNew = new CSttXmlSerializeRegister(m_pXmlDoc, pDataElement);
// 	AddNewChild(pNew);

	return pNew;
}


//2021-6-1  lijunqing : use bstrElementKey and nIndex 
CSttXmlSerializeBase* CSttXmlSerializeWrite::xml_serialize(BSTR bstrElementKey, long nIndex, const char *pszName,const char *pszID, const char *pszDataTypeID)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return NULL;
	}

//	xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);

	CSttXmlSerializeBase *pNew = create_new(m_pXmlDoc, pDataElement, TRUE);
	pNew->m_strName.Format(_T("%s%ld"),pszName,nIndex+1);
	pNew->m_strID.Format(_T("%s%ld"),pszID,nIndex);

	return pNew;
}


//////////////////////////////////////////////////////////////////////////
//CSttXmlSerializeRegister
CSttXmlSerializeRegister::CSttXmlSerializeRegister(CXmlRWDocBase *pXmlDoc, CXmlRWElementBase *pElement)
:CSttXmlSerializeWrite(pXmlDoc, pElement)
{

}

CSttXmlSerializeRegister::~CSttXmlSerializeRegister()
{

}

BOOL CSttXmlSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,CString &strAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

	xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, strAttrVal);
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, strAttrVal);

	return TRUE;
}

BOOL CSttXmlSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,wchar_t *strAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

	xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, strAttrVal);
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, strAttrVal);

	return TRUE;
}

BOOL CSttXmlSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,long &nAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

	char pszDefaultValue[32];
	sprintf(pszDefaultValue, "%d", nAttrVal);

	xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, nAttrVal);

	return TRUE;
}

BOOL CSttXmlSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,int &nAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

	char pszDefaultValue[32];
	sprintf(pszDefaultValue, "%d", nAttrVal);

	xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);

	long nTemp = nAttrVal;
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, nTemp);

	return TRUE;
}

BOOL CSttXmlSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,unsigned int &unAttrVal, BSTR bstrElementKey)
{
    CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
    ASSERT (pDataElement != NULL);

    if (pDataElement == NULL)
    {
        return FALSE;
    }

    char pszDefaultValue[32];
    sprintf(pszDefaultValue, "%d", unAttrVal);

    xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
    xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
    xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
    xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
    xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);

    long nTemp = unAttrVal;
    xml_SetAttributeValue(stt_ValueKey(), *pDataElement, nTemp);

    return TRUE;
}

BOOL CSttXmlSerializeRegister::xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
												  double &dAttrVal,const char *pszSysParaID, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

	char pszDefaultValue[32];
	sprintf(pszDefaultValue, "%f", dAttrVal);

	xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
//	xml_SetAttributeValue(stt_FormatKey(), *pDataElement, pszSysParaID);

	long nTemp = dAttrVal;
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, nTemp);

	return TRUE;
	//return xml_serialize(pszName,pszID,pszUnit,pszDataTypeID,dAttrVal,bstrElementKey);
}

BOOL CSttXmlSerializeRegister::xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
												  float &fAttrVal,const char *pszSysParaID, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

	char pszDefaultValue[32];
	sprintf(pszDefaultValue, "%f", fAttrVal);

	xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
//	xml_SetAttributeValue(stt_FormatKey(), *pDataElement, pszSysParaID);

// 	long nTemp = fAttrVal;
// 	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, nTemp);
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, fAttrVal);//dingxy 20240530 float型不需要转成long,小数位会丢失

	return TRUE;
	//return xml_serialize(pszName,pszID,pszUnit,pszDataTypeID,fAttrVal,bstrElementKey);
}

#ifdef _PSX_QT_LINUX_
BOOL CSttXmlSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,BOOL &bAttrVal, BSTR bstrElementKey)
{
    CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
    ASSERT (pDataElement != NULL);

    if (pDataElement == NULL)
    {
        return FALSE;
    }

    char pszDefaultValue[32];
    sprintf(pszDefaultValue, "%d", (int)bAttrVal);

    xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
    xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
    xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
    xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
    xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);

    long nTemp = bAttrVal;
    xml_SetAttributeValue(stt_ValueKey(), *pDataElement, nTemp);

    return TRUE;
}
#endif

BOOL CSttXmlSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,double &dAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

	char pszDefaultValue[32];
	sprintf(pszDefaultValue, "%f", dAttrVal);

	xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, dAttrVal);

	return TRUE;
}

BOOL CSttXmlSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,short &unAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

	char pszDefaultValue[32];
	sprintf(pszDefaultValue, "%d", unAttrVal);

	xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, unAttrVal);

	return TRUE;
}

BOOL CSttXmlSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,float &fAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

	char pszDefaultValue[32];
	sprintf(pszDefaultValue, "%f", fAttrVal);

	xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, pszDefaultValue);
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, fAttrVal);

	return TRUE;
}

BOOL CSttXmlSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,char *strAttrVal, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return FALSE;
	}

	xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	xml_SetAttributeValue(stt_UnitKey(), *pDataElement, pszUnit);
	xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);
	xml_SetAttributeValue(stt_DefValueKey(), *pDataElement, strAttrVal);
	xml_SetAttributeValue(stt_ValueKey(), *pDataElement, strAttrVal);

	return TRUE;
}


CSttXmlSerializeBase* CSttXmlSerializeRegister::xml_serialize(const char *pszName,const char *pszID, const char *pszDataTypeID, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return NULL;
	}

	xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);

	CSttXmlSerializeBase *pNew = create_new(m_pXmlDoc, pDataElement, TRUE);
	pNew->m_strName = pszName;
	pNew->m_strID = pszID;

	return pNew;
}

CSttXmlSerializeBase* CSttXmlSerializeRegister::xml_serialize(const char *pszName,const char *pszID, long nIndex, const char *pszDataTypeID, BSTR bstrElementKey)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return NULL;
	}

	char pszNewName[_STT_XML_NEW_NAME_LEN_], pszNewID[_STT_XML_NEW_NAME_LEN_];
	stt_get_xml_new_name_id(pszName, pszID, nIndex, pszNewName, pszNewID);

	xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszNewName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszNewID);
	xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);

	CSttXmlSerializeBase *pNew = create_new(m_pXmlDoc, pDataElement, TRUE);
	pNew->m_strName = pszNewName;
	pNew->m_strID = pszNewID;

	return pNew;
}

CSttXmlSerializeBase* CSttXmlSerializeRegister::xml_serialize(BSTR bstrElementKey, long nIndex, const char *pszName,const char *pszID, const char *pszDataTypeID)
{
	CXmlRWElementBase *pDataElement = CreateElement(bstrElementKey);
	ASSERT (pDataElement != NULL);

	if (pDataElement == NULL)
	{
		return NULL;
	}

	char pszNewName[200];
	memset(pszNewName, 0, 200);
	sprintf(pszNewName, "%s%d", pszName, nIndex);

	xml_SetAttributeValue(stt_NameKey(), *pDataElement, pszNewName);
	xml_SetAttributeValue(stt_IDKey(), *pDataElement, pszID);
	xml_SetAttributeValue(stt_DataTypeKey(), *pDataElement, pszDataTypeID);

	CSttXmlSerializeBase *pNew = create_new(m_pXmlDoc, pDataElement, TRUE);
	pNew->m_strName.Format(_T("%s%ld"),pszName,nIndex+1);
	pNew->m_strID.Format(_T("%s%ld"),pszID,nIndex);

	return pNew;
}



//////////////////////////////////////////////////////////////////////////
#include "../SttCmd/SttParas.h"
//////////////////////////////////////////////////////////////////////////
//CSttXmlSerializeRead
CSttDataGroupSerializeRead::CSttDataGroupSerializeRead(CDataGroup *pDataGroup)
:CSttXmlSerializeBase(pDataGroup)
{

}

CSttDataGroupSerializeRead::~CSttDataGroupSerializeRead()
{

}

BOOL CSttDataGroupSerializeRead::AddSysPara(const CString &strSysParaID,const CString &strOldSysParaID,double dCurrValue)
{
	if (m_pDataGroup == NULL)
	{
		return FALSE;
	}

	double dOldValue = 0;

	if (!m_pDataGroup->GetDataValue(strSysParaID,dOldValue))
	{
		return FALSE;
	}

	if (fabs(dCurrValue-dOldValue) < 0.001f)//如何模板中与当前的额定值是相同的则不需要再处理
	{
		return FALSE;
	}

	m_oSysParasList.AddNewData(strSysParaID,dCurrValue);
	m_oSysParasList.AddNewData(strOldSysParaID,dOldValue);
	return TRUE;
}

BOOL CSttDataGroupSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,CString &strAttrVal, BSTR bstrElementKey)
{
	return stt_GetDataValueByID(m_pDataGroup, pszID, strAttrVal);	
}

BOOL CSttDataGroupSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,wchar_t *strAttrVal, BSTR bstrElementKey)
{
	return FALSE;
}

BOOL CSttDataGroupSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,long &nAttrVal, BSTR bstrElementKey)
{
	return stt_GetDataValueByID(m_pDataGroup, pszID, nAttrVal);	
}

BOOL CSttDataGroupSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,int &nAttrVal, BSTR bstrElementKey)
{
	long nTemp = 0;
	if ( stt_GetDataValueByID(m_pDataGroup, pszID, nTemp) )
	{
		nAttrVal = nTemp;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CSttDataGroupSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,unsigned int &unAttrVal, BSTR bstrElementKey)
{
	long nTemp = 0;
	if ( stt_GetDataValueByID(m_pDataGroup, pszID, nTemp) )
	{
		unAttrVal = nTemp;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

#ifdef _PSX_QT_LINUX_
BOOL CSttDataGroupSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,BOOL &bAttrVal, BSTR bstrElementKey)
{
    long nTemp = 0;
    if ( stt_GetDataValueByID(m_pDataGroup, pszID, nTemp) )
    {
        bAttrVal = nTemp;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#endif

BOOL CSttDataGroupSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,double &dAttrVal, BSTR bstrElementKey)
{
	return stt_GetDataValueByID(m_pDataGroup, pszID, dAttrVal);
}

BOOL CSttDataGroupSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,short &unAttrVal, BSTR bstrElementKey)
{
	{
		return FALSE;
	}
}

BOOL CSttDataGroupSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,float &fAttrVal, BSTR bstrElementKey)
{
	return stt_GetDataValueByID(m_pDataGroup, pszID, fAttrVal);
}

BOOL CSttDataGroupSerializeRead::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,char *strAttrVal, BSTR bstrElementKey)
{
	CString strValue;

	BOOL bRet = stt_GetDataValueByID(m_pDataGroup, pszID, strValue);

	if (bRet)
	{
		CString_to_char(strValue,strAttrVal);
	}

	return bRet;
}

BOOL CSttDataGroupSerializeRead::xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
												  double &dAttrVal,const char *pszSysParaID, BSTR bstrElementKey)
{
	//系统参数数据链表为空,则与原有保持一致,不更新系统参数
	if (m_oSysParasList.GetCount()<=0)
	{
		return xml_serialize(pszName,pszID,pszUnit,pszDataTypeID,dAttrVal,bstrElementKey);
	}

	double dCurrSysParaValue = 0.0f,dOldSysParaValue = 0.0f;

	//获取当前系统参数失败,也不更新系统参数
	if (!m_oSysParasList.GetDataValue(pszSysParaID,dCurrSysParaValue))
	{
		return xml_serialize(pszName,pszID,pszUnit,pszDataTypeID,dAttrVal,bstrElementKey);
	}

	//当前数据查找失败时,不更新系统参数
	if (!stt_GetDataValueByID(m_pDataGroup, pszID, dAttrVal))
	{
		return FALSE;
	}

	if (strcmp(pszSysParaID, STT_XML_SERIALIZE_SYS_PARA_ID_VNom) == 0)
	//if (pszSysParaID == STT_XML_SERIALIZE_SYS_PARA_ID_VNom)
	{
		//模板中的系统参数查找失败,不更新系统参数
		if (!stt_GetDataValueByID(&m_oSysParasList, STT_XML_SERIALIZE_SYS_PARA_ID_OldVNom, dOldSysParaValue))
		{
			return TRUE;
		}
	} 
	else if (strcmp(pszSysParaID, STT_XML_SERIALIZE_SYS_PARA_ID_INom) == 0)
	//else if (pszSysParaID == STT_XML_SERIALIZE_SYS_PARA_ID_INom)
	{
		//模板中的系统参数查找失败,不更新系统参数
		if (!stt_GetDataValueByID(&m_oSysParasList, STT_XML_SERIALIZE_SYS_PARA_ID_OldINom, dOldSysParaValue))
		{
			return TRUE;
		}
	}
	else if (strcmp(pszSysParaID, STT_XML_SERIALIZE_SYS_PARA_ID_FNom) == 0)
	//else if (pszSysParaID == STT_XML_SERIALIZE_SYS_PARA_ID_FNom)
	{
		//模板中的系统参数查找失败,不更新系统参数
		if (!stt_GetDataValueByID(&m_oSysParasList, STT_XML_SERIALIZE_SYS_PARA_ID_OldFNom, dOldSysParaValue))
		{
			return TRUE;
		}
	}
	else
		return TRUE;

	//当前参数值与旧有模板中的不一致,则保持原有值,不更新为系统参数
	if (fabs(dAttrVal - dOldSysParaValue) >= 0.001f)
	{
		return TRUE;
	}

	//当前参数值与旧有模板中的一致,则更新为系统参数
	dAttrVal = dCurrSysParaValue;
	return TRUE;
}

BOOL CSttDataGroupSerializeRead::xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
												  float &fAttrVal,const char *pszSysParaID, BSTR bstrElementKey)
{
	//系统参数数据链表为空,则与原有保持一致,不更新系统参数
	if (m_oSysParasList.GetCount()<=0)
	{
		return xml_serialize(pszName,pszID,pszUnit,pszDataTypeID,fAttrVal,bstrElementKey);
	}

	double dCurrSysParaValue = 0.0f,dOldSysParaValue = 0.0f;

	//获取当前系统参数失败,也不更新系统参数
	if (!m_oSysParasList.GetDataValue(pszSysParaID,dCurrSysParaValue))
	{
		return xml_serialize(pszName,pszID,pszUnit,pszDataTypeID,fAttrVal,bstrElementKey);
	}

	//当前数据查找失败时,不更新系统参数
	if (!stt_GetDataValueByID(m_pDataGroup, pszID, fAttrVal))
	{
		return FALSE;
	}

	if (strcmp(pszSysParaID, STT_XML_SERIALIZE_SYS_PARA_ID_VNom) == 0)
	//if (pszSysParaID == STT_XML_SERIALIZE_SYS_PARA_ID_VNom)
	{
		//模板中的系统参数查找失败,不更新系统参数
		if (!stt_GetDataValueByID(&m_oSysParasList, STT_XML_SERIALIZE_SYS_PARA_ID_OldVNom, dOldSysParaValue))
		{
			return TRUE;
		}
	} 
	else if (strcmp(pszSysParaID, STT_XML_SERIALIZE_SYS_PARA_ID_INom) == 0)
	//else if (pszSysParaID == STT_XML_SERIALIZE_SYS_PARA_ID_INom)
	{
		//模板中的系统参数查找失败,不更新系统参数
		if (!stt_GetDataValueByID(&m_oSysParasList, STT_XML_SERIALIZE_SYS_PARA_ID_OldINom, dOldSysParaValue))
		{
			return TRUE;
		}
	}
	else if (strcmp(pszSysParaID, STT_XML_SERIALIZE_SYS_PARA_ID_FNom) == 0)
	//else if (pszSysParaID == STT_XML_SERIALIZE_SYS_PARA_ID_FNom)
	{
		//模板中的系统参数查找失败,不更新系统参数
		if (!stt_GetDataValueByID(&m_oSysParasList, STT_XML_SERIALIZE_SYS_PARA_ID_OldFNom, dOldSysParaValue))
		{
			return TRUE;
		}
	}
	else
		return TRUE;

	//当前参数值与旧有模板中的不一致,则保持原有值,不更新为系统参数
	if (fabs(fAttrVal - dOldSysParaValue) >= 0.001f)
	{
		return TRUE;
	}

	//当前参数值与旧有模板中的一致,则更新为系统参数
	fAttrVal = dCurrSysParaValue;
	return TRUE;
//	return xml_serialize(pszName,pszID,pszUnit,pszDataTypeID,fAttrVal,bstrElementKey);
}

CSttXmlSerializeBase* CSttDataGroupSerializeRead::xml_serialize(const char *pszName,const char *pszID, const char *pszDataTypeID, BSTR bstrElementKey)
{
	CExBaseObject *pFind = m_pDataGroup->FindByID(pszID);

	if (pFind == NULL)
	{
		return NULL;
	}

	if (pFind->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return NULL;
	}

	CSttDataGroupSerializeRead *pNew = new CSttDataGroupSerializeRead((CDataGroup*)pFind);
	AddNewChild(pNew);

	return pNew;
}

CSttXmlSerializeBase* CSttDataGroupSerializeRead::xml_serialize(const char *pszName,const char *pszID, long nIndex, const char *pszDataTypeID, BSTR bstrElementKey)
{
	char pszNewName[_STT_XML_NEW_NAME_LEN_], pszNewID[_STT_XML_NEW_NAME_LEN_];
	stt_get_xml_new_name_id(pszName, pszID, nIndex, pszNewName, pszNewID);

	CExBaseObject *pFind = m_pDataGroup->FindByID(pszNewID);

	if (pFind == NULL)
	{
		return NULL;
	}

	if (pFind->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return NULL;
	}

	CSttDataGroupSerializeRead *pNew = new CSttDataGroupSerializeRead((CDataGroup*)pFind);
	AddNewChild(pNew);

	return pNew;
}

//2021-6-1  lijunqing : use bstrElementKey and nIndex 
CSttXmlSerializeBase* CSttDataGroupSerializeRead::xml_serialize(BSTR bstrElementKey, long nIndex, const char *pszName,const char *pszID, const char *pszDataTypeID)
{
// 	CXmlRWElementBase *pFind = FindElement(bstrElementKey, stt_DataTypeKey(), pszDataTypeID, nIndex);
// 
// 	if (pFind==NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	if (pFind->IsEmpty())
// 	{
// 		return NULL;
// 	}
// 	else
// 	{
// 		CSttXmlSerializeBase *pNew =create_new(m_pXmlDoc, pFind, TRUE);
// 		pNew->m_strName.Format(_T("%s%ld"),pszName,nIndex+1);
// 		pNew->m_strID.Format(_T("%s%ld"),pszID,nIndex);
// 		return pNew;
// 	}
	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//CSttXmlSerializeRead
CSttDataGroupSerializeRegister::CSttDataGroupSerializeRegister(CDataGroup *pDataGroup)
:CSttXmlSerializeBase(pDataGroup)
{

}

CSttDataGroupSerializeRegister::~CSttDataGroupSerializeRegister()
{

}

BOOL CSttDataGroupSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,CString &strAttrVal, BSTR bstrElementKey)
{
	m_pDataGroup->AddNewData(pszName, pszID, pszDataTypeID, strAttrVal, pszUnit);
	return TRUE;
}

BOOL CSttDataGroupSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,wchar_t *strAttrVal, BSTR bstrElementKey)
{
	return FALSE;
}

BOOL CSttDataGroupSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,long &nAttrVal, BSTR bstrElementKey)
{
	CString strValue;
	strValue.Format(_T("%d"), nAttrVal);
	m_pDataGroup->AddNewData(pszName, pszID, pszDataTypeID, strValue, pszUnit);
	return TRUE;
}

BOOL CSttDataGroupSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,int &nAttrVal, BSTR bstrElementKey)
{
	CString strValue;
	strValue.Format(_T("%d"), nAttrVal);
	m_pDataGroup->AddNewData(pszName, pszID, pszDataTypeID, strValue, pszUnit);
	return TRUE;
}

BOOL CSttDataGroupSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,unsigned int &unAttrVal, BSTR bstrElementKey)
{
	CString strValue;
	strValue.Format(_T("%d"), unAttrVal);
	m_pDataGroup->AddNewData(pszName, pszID, pszDataTypeID, strValue, pszUnit);
	return TRUE;
}

#ifdef _PSX_QT_LINUX_
BOOL CSttDataGroupSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,BOOL &bAttrVal, BSTR bstrElementKey)
{
    CString strValue;
    strValue.Format(_T("%d"), (int)bAttrVal);
    m_pDataGroup->AddNewData(pszName, pszID, pszDataTypeID, strValue, pszUnit);
    return TRUE;
}
#endif

BOOL CSttDataGroupSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,double &dAttrVal, BSTR bstrElementKey)
{
	CString strValue;
	strValue.Format(_T("%f"), dAttrVal);
	m_pDataGroup->AddNewData(pszName, pszID, pszDataTypeID, strValue, pszUnit);
	return TRUE;
}

BOOL CSttDataGroupSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,short &unAttrVal, BSTR bstrElementKey)
{
	{
		return FALSE;
	}
}

BOOL CSttDataGroupSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,float &fAttrVal, BSTR bstrElementKey)
{
	CString strValue;
	strValue.Format(_T("%f"), fAttrVal);
	m_pDataGroup->AddNewData(pszName, pszID, pszDataTypeID, strValue, pszUnit);
	return TRUE;
}

BOOL CSttDataGroupSerializeRegister::xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,char *strAttrVal, BSTR bstrElementKey)
{
	//2022.5.12 caoxc
	//{
	//	return FALSE;
	//}
	CString strValue = CString(strAttrVal);
	m_pDataGroup->AddNewData(pszName, pszID, pszDataTypeID, strValue, pszUnit);
	return TRUE;
}

BOOL CSttDataGroupSerializeRegister::xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
												  double &dAttrVal,const char *pszSysParaID, BSTR bstrElementKey)
{
	CString strValue;
	strValue.Format(_T("%d"), dAttrVal);
	CDvmData* pDvmData = m_pDataGroup->AddNewData(pszName, pszID, pszDataTypeID, strValue, pszUnit);
 //	pDvmData->m_strFormat = pszSysParaID;
 	return TRUE;
	//return xml_serialize(pszName,pszID,pszUnit,pszDataTypeID,dAttrVal,bstrElementKey);
}

BOOL CSttDataGroupSerializeRegister::xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
												  float &fAttrVal,const char *pszSysParaID, BSTR bstrElementKey)
{
	CString strValue;
	strValue.Format(_T("%f"), fAttrVal);
	CDvmData* pDvmData = m_pDataGroup->AddNewData(pszName, pszID, pszDataTypeID, strValue, pszUnit);
//	pDvmData->m_strFormat = pszSysParaID;
	return TRUE;
	//return xml_serialize(pszName,pszID,pszUnit,pszDataTypeID,fAttrVal,bstrElementKey);
}

CSttXmlSerializeBase* CSttDataGroupSerializeRegister::xml_serialize(const char *pszName,const char *pszID, const char *pszDataTypeID, BSTR bstrElementKey)
{
	CDataGroup *pNew = new CDataGroup();
	pNew->m_strName = pszName;
	pNew->m_strID = pszID;
	pNew->m_strDataType = pszDataTypeID;
	m_pDataGroup->AddNewChild(pNew);

	CSttDataGroupSerializeRegister *pNewRegister = new CSttDataGroupSerializeRegister(pNew);
	AddNewChild(pNewRegister);

	return pNewRegister;
}

CSttXmlSerializeBase* CSttDataGroupSerializeRegister::xml_serialize(const char *pszName,const char *pszID, long nIndex, const char *pszDataTypeID, BSTR bstrElementKey)
{
	CDataGroup *pNew = new CDataGroup();
	char pszNewName[_STT_XML_NEW_NAME_LEN_], pszNewID[_STT_XML_NEW_NAME_LEN_]; //20220803  zhouhj  与Read的保持一致,增加ID的编号
	stt_get_xml_new_name_id(pszName, pszID, nIndex, pszNewName, pszNewID);

	pNew->m_strName = pszNewName;
	pNew->m_strID = pszNewID;
	pNew->m_strDataType = pszDataTypeID;
	m_pDataGroup->AddNewChild(pNew);

	CSttDataGroupSerializeRegister *pNewRegister = new CSttDataGroupSerializeRegister(pNew);
	pNewRegister->m_strName = pNew->m_strName;
	pNewRegister->m_strID = pNew->m_strID;
	AddNewChild(pNewRegister);

	return pNewRegister;
}

//2021-6-1  lijunqing : use bstrElementKey and nIndex 
CSttXmlSerializeBase* CSttDataGroupSerializeRegister::xml_serialize(BSTR bstrElementKey, long nIndex, const char *pszName,const char *pszID, const char *pszDataTypeID)
{
	char pszNewName[_STT_XML_NEW_NAME_LEN_], pszNewID[_STT_XML_NEW_NAME_LEN_];
	stt_get_xml_new_name_id(pszName, pszID, nIndex, pszNewName, pszNewID);

	CDataGroup *pNew = new CDataGroup();
	pNew->m_strName = pszNewName;
	pNew->m_strID = pszNewID;
	pNew->m_strDataType = pszDataTypeID;
	m_pDataGroup->AddNewChild(pNew);

	CSttDataGroupSerializeRegister *pNewRegister = new CSttDataGroupSerializeRegister(pNew);
	AddNewChild(pNewRegister);

	return pNewRegister;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttSerializeUpdateSysParas::CSttSerializeUpdateSysParas()
:CSttXmlSerializeBase(NULL)
{

}

CSttSerializeUpdateSysParas::~CSttSerializeUpdateSysParas()
{

}

BOOL CSttSerializeUpdateSysParas::AddSysPara(const CString &strSysParaID,const CString &strOldSysParaID
											 ,double dCurrValue,double dOldValue)
{
	if (fabs(dCurrValue-dOldValue) < 0.001f)//如修改前后相同则不需要修改
	{
		return FALSE;
	}

	m_oSysParasList.AddNewData(strSysParaID,dCurrValue);
	m_oSysParasList.AddNewData(strOldSysParaID,dOldValue);
	return TRUE;
}

BOOL CSttSerializeUpdateSysParas::xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
														double &dAttrVal,const char *pszSysParaID, BSTR bstrElementKey)
{
	//系统参数数据链表为空,则与原有保持一致,不更新系统参数
	if (m_oSysParasList.GetCount()<=0)
	{
		return FALSE;
	}

	double dCurrSysParaValue = 0.0f,dOldSysParaValue = 0.0f;

	//获取当前系统参数失败,也不更新系统参数
	if (!m_oSysParasList.GetDataValue(pszSysParaID,dCurrSysParaValue))
	{
		return FALSE;
	}

	if (strcmp(pszSysParaID, STT_XML_SERIALIZE_SYS_PARA_ID_VNom) == 0)
	//if (pszSysParaID == STT_XML_SERIALIZE_SYS_PARA_ID_VNom)
	{
		//模板中的系统参数查找失败,不更新系统参数
		if (!stt_GetDataValueByID(&m_oSysParasList, STT_XML_SERIALIZE_SYS_PARA_ID_OldVNom, dOldSysParaValue))
		{
			return FALSE;
		}
	} 
	else if (strcmp(pszSysParaID, STT_XML_SERIALIZE_SYS_PARA_ID_INom) == 0)
	//else if (pszSysParaID == STT_XML_SERIALIZE_SYS_PARA_ID_INom)
	{
		//模板中的系统参数查找失败,不更新系统参数
		if (!stt_GetDataValueByID(&m_oSysParasList, STT_XML_SERIALIZE_SYS_PARA_ID_OldINom, dOldSysParaValue))
		{
			return FALSE;
		}
	}
	else if (strcmp(pszSysParaID, STT_XML_SERIALIZE_SYS_PARA_ID_FNom) == 0)
	//else if (pszSysParaID == STT_XML_SERIALIZE_SYS_PARA_ID_FNom)
	{
		//模板中的系统参数查找失败,不更新系统参数
		if (!stt_GetDataValueByID(&m_oSysParasList, STT_XML_SERIALIZE_SYS_PARA_ID_OldFNom, dOldSysParaValue))
		{
			return FALSE;
		}
	}
	else
		return FALSE;

	//当前参数值与旧有模板中的不一致,则保持原有值,不更新为系统参数
	if (fabs(dAttrVal - dOldSysParaValue) >= 0.001f)
	{
		return FALSE;
	}

	//当前参数值与旧有模板中的一致,则更新为系统参数
	dAttrVal = dCurrSysParaValue;
	return TRUE;
}

BOOL CSttSerializeUpdateSysParas::xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
														float &fAttrVal,const char *pszSysParaID, BSTR bstrElementKey)
{
	//系统参数数据链表为空,则与原有保持一致,不更新系统参数
	if (m_oSysParasList.GetCount()<=0)
	{
		return FALSE;
	}

	double dCurrSysParaValue = 0.0f,dOldSysParaValue = 0.0f;

	//获取当前系统参数失败,也不更新系统参数
	if (!m_oSysParasList.GetDataValue(pszSysParaID,dCurrSysParaValue))
	{
		return FALSE;
	}

	//if (pszSysParaID == STT_XML_SERIALIZE_SYS_PARA_ID_VNom)
	if (strcmp(pszSysParaID, STT_XML_SERIALIZE_SYS_PARA_ID_VNom) == 0)
	{
		//模板中的系统参数查找失败,不更新系统参数
		if (!stt_GetDataValueByID(&m_oSysParasList, STT_XML_SERIALIZE_SYS_PARA_ID_OldVNom, dOldSysParaValue))
		{
			return FALSE;
		}
	} 
	//else if (pszSysParaID == STT_XML_SERIALIZE_SYS_PARA_ID_INom)
	else if(strcmp(pszSysParaID, STT_XML_SERIALIZE_SYS_PARA_ID_INom) == 0)
	{
		//模板中的系统参数查找失败,不更新系统参数
		if (!stt_GetDataValueByID(&m_oSysParasList, STT_XML_SERIALIZE_SYS_PARA_ID_OldINom, dOldSysParaValue))
		{
			return FALSE;
		}
	}
	//else if (pszSysParaID == STT_XML_SERIALIZE_SYS_PARA_ID_FNom)
	else if(strcmp(pszSysParaID, STT_XML_SERIALIZE_SYS_PARA_ID_FNom) == 0)
	{
		//模板中的系统参数查找失败,不更新系统参数
		if (!stt_GetDataValueByID(&m_oSysParasList, STT_XML_SERIALIZE_SYS_PARA_ID_OldFNom, dOldSysParaValue))
		{
			return FALSE;
		}
	}
	else
		return FALSE;

	//当前参数值与旧有模板中的不一致,则保持原有值,不更新为系统参数
	if (fabs(fAttrVal - dOldSysParaValue) >= 0.001f)
	{
		return FALSE;
	}

	//当前参数值与旧有模板中的一致,则更新为系统参数
	fAttrVal = dCurrSysParaValue;
	return TRUE;
}

CSttXmlSerializeBase* CSttSerializeUpdateSysParas::xml_serialize( const char *pszName,const char *pszID, long nIndex, const char *pszDataTypeID, BSTR bstrElementKey /*= NULL*/ )
{
	return this;
}

CSttXmlSerializeBase* CSttSerializeUpdateSysParas::xml_serialize( const char *pszName,const char *pszID, const char *pszDataTypeID, BSTR bstrElementKey /*= NULL*/ )
{
	return this;
}

