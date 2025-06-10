#include "StdAfx.h"
#include "SttParaObjects.h"

CSttParaObjects::CSttParaObjects(void)
{
	m_strXmlElementName = NULL;
}

CSttParaObjects::~CSttParaObjects(void)
{
}

CSttParaObject* CSttParaObjects::RegisterPara(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,const char *value)//, const CString &strGroup)
{
	CSttParaObject *pParaObj = NULL;

	pParaObj = new CSttParaObject(strName,strID,strUnit,strDataTypeID,strDefaultValue,value);//,KEYTYPE_PARAMETERKEY);
	AddTail(pParaObj);
	pParaObj->SetParent(this);
	//pParaObj->SetGroup(strGroup);

	//2018-5-25：注册时，验证缺省值域设置的值是否一致
	if (g_bValidateParaWhenRegist)
	{
		pParaObj->ValidateParaWhenRegist();
	}

	return pParaObj;
}

CSttParaObject* CSttParaObjects::RegisterPara(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue, int *value)//)//, const CString &strGroup)
{
	CSttParaObject *pParaObj = NULL;

	pParaObj = new CSttParaObject(strName,strID,strUnit,strDataTypeID,strDefaultValue,value);//);//,KEYTYPE_PARAMETERKEY);
	AddTail(pParaObj);
	pParaObj->SetParent(this);
	//pParaObj->SetGroup(strGroup);

	//2018-5-25：注册时，验证缺省值域设置的值是否一致
	if (g_bValidateParaWhenRegist)
	{
		pParaObj->ValidateParaWhenRegist();
	}

	return pParaObj;
}

CSttParaObject* CSttParaObjects::RegisterPara(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue, long *value)//, const CString &strGroup)
{
	CSttParaObject *pParaObj = NULL;

	pParaObj = new CSttParaObject(strName,strID,strUnit,strDataTypeID,strDefaultValue,value);//,KEYTYPE_PARAMETERKEY);
	AddTail(pParaObj);
	pParaObj->SetParent(this);
	//pParaObj->SetGroup(strGroup);

	//2018-5-25：注册时，验证缺省值域设置的值是否一致
	if (g_bValidateParaWhenRegist)
	{
		pParaObj->ValidateParaWhenRegist();
	}

	return pParaObj;
}

CSttParaObject* CSttParaObjects::RegisterPara(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue, float *value)//, const CString &strGroup)
{
	CSttParaObject *pParaObj = NULL;

	pParaObj = new CSttParaObject(strName,strID,strUnit,strDataTypeID,strDefaultValue,value);//,KEYTYPE_PARAMETERKEY);
	AddTail(pParaObj);
	pParaObj->SetParent(this);
	//pParaObj->SetGroup(strGroup);

	//2018-5-25：注册时，验证缺省值域设置的值是否一致
	if (g_bValidateParaWhenRegist)
	{
		pParaObj->ValidateParaWhenRegist();
	}

	return pParaObj;
}

CSttParaObject* CSttParaObjects::RegisterPara(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue, double *value)//, const CString &strGroup)
{
	CSttParaObject *pParaObj = NULL;

	pParaObj = new CSttParaObject(strName,strID,strUnit,strDataTypeID,strDefaultValue,value);//,KEYTYPE_PARAMETERKEY);
	AddTail(pParaObj);
	pParaObj->SetParent(this);
	//pParaObj->SetGroup(strGroup);

	//2018-5-25：注册时，验证缺省值域设置的值是否一致
	if (g_bValidateParaWhenRegist)
	{
		pParaObj->ValidateParaWhenRegist();
	}

	return pParaObj;
}

CSttParaObject* CSttParaObjects::RegisterPara(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue, unsigned char *value)//, const CString &strGroup)
{
	CSttParaObject *pParaObj = NULL;

	pParaObj = new CSttParaObject(strName,strID,strUnit,strDataTypeID,strDefaultValue,value);//,KEYTYPE_PARAMETERKEY);
	AddTail(pParaObj);
	pParaObj->SetParent(this);
	//pParaObj->SetGroup(strGroup);

	//2018-5-25：注册时，验证缺省值域设置的值是否一致
	if (g_bValidateParaWhenRegist)
	{
		pParaObj->ValidateParaWhenRegist();
	}

	return pParaObj;
}

CSttParaObject* CSttParaObjects::RegisterPara(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue, short *value)//, const CString &strGroup)
{
	CSttParaObject *pParaObj = NULL;

	pParaObj = new CSttParaObject(strName,strID,strUnit,strDataTypeID,strDefaultValue,value);//,KEYTYPE_PARAMETERKEY);
	AddTail(pParaObj);
	pParaObj->SetParent(this);
	//pParaObj->SetGroup(strGroup);

	//2018-5-25：注册时，验证缺省值域设置的值是否一致
	if (g_bValidateParaWhenRegist)
	{
		pParaObj->ValidateParaWhenRegist();
	}

	return pParaObj;
}

CSttParaObject* CSttParaObjects::RegisterPara(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,const char *value)//, const char* strGroup)
{
	CSttParaObject *pParaObj = NULL;

	pParaObj = new CSttParaObject(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue,value);//,KEYTYPE_PARAMETERKEY);
	AddTail(pParaObj);
	pParaObj->SetParent(this);
	//pParaObj->SetGroup(strGroup);

	//2018-5-25：注册时，验证缺省值域设置的值是否一致
	if (g_bValidateParaWhenRegist)
	{
		pParaObj->ValidateParaWhenRegist();
	}

	return pParaObj;
}

CSttParaObject* CSttParaObjects::RegisterPara(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue, int *value)//, const char* strGroup)
{
	CSttParaObject *pParaObj = NULL;

	pParaObj = new CSttParaObject(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue,value);//,KEYTYPE_PARAMETERKEY);
	AddTail(pParaObj);
	pParaObj->SetParent(this);
	//pParaObj->SetGroup(strGroup);

	//2018-5-25：注册时，验证缺省值域设置的值是否一致
	if (g_bValidateParaWhenRegist)
	{
		pParaObj->ValidateParaWhenRegist();
	}

	return pParaObj;
}
CSttParaObject* CSttParaObjects::RegisterPara(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue, long *value)//, const char* strGroup)
{
	CSttParaObject *pParaObj = NULL;

	pParaObj = new CSttParaObject(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue,value);//,KEYTYPE_PARAMETERKEY);
	AddTail(pParaObj);
	pParaObj->SetParent(this);
	//pParaObj->SetGroup(strGroup);

	//2018-5-25：注册时，验证缺省值域设置的值是否一致
	if (g_bValidateParaWhenRegist)
	{
		pParaObj->ValidateParaWhenRegist();
	}

	return pParaObj;
}

CSttParaObject* CSttParaObjects::RegisterPara(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue, float *value)//, const char* strGroup)
{
	CSttParaObject *pParaObj = NULL;

	pParaObj = new CSttParaObject(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue,value);//,KEYTYPE_PARAMETERKEY);
	AddTail(pParaObj);
	pParaObj->SetParent(this);
	//pParaObj->SetGroup(strGroup);

	//2018-5-25：注册时，验证缺省值域设置的值是否一致
	if (g_bValidateParaWhenRegist)
	{
		pParaObj->ValidateParaWhenRegist();
	}

	return pParaObj;
}

CSttParaObject* CSttParaObjects::RegisterPara(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue, double *value)//, const char* strGroup)
{
	CSttParaObject *pParaObj = NULL;

	pParaObj = new CSttParaObject(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue,value);//,KEYTYPE_PARAMETERKEY);
	AddTail(pParaObj);
	pParaObj->SetParent(this);
	//pParaObj->SetGroup(strGroup);

	//2018-5-25：注册时，验证缺省值域设置的值是否一致
	if (g_bValidateParaWhenRegist)
	{
		pParaObj->ValidateParaWhenRegist();
	}

	return pParaObj;
}

CSttParaObject* CSttParaObjects::RegisterPara(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue, unsigned char *value)//, const char* strGroup)
{
	CSttParaObject *pParaObj = NULL;

	pParaObj = new CSttParaObject(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue,value);//,KEYTYPE_PARAMETERKEY);
	AddTail(pParaObj);
	pParaObj->SetParent(this);
	//pParaObj->SetGroup(strGroup);

	//2018-5-25：注册时，验证缺省值域设置的值是否一致
	if (g_bValidateParaWhenRegist)
	{
		pParaObj->ValidateParaWhenRegist();
	}

	return pParaObj;
}

CSttParaObject* CSttParaObjects::RegisterPara(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue, short *value)//, const char* strGroup)
{
	CSttParaObject *pParaObj = NULL;

	pParaObj = new CSttParaObject(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue,value);//,KEYTYPE_PARAMETERKEY);
	AddTail(pParaObj);
	pParaObj->SetParent(this);
	//pParaObj->SetGroup(strGroup);

	//2018-5-25：注册时，验证缺省值域设置的值是否一致
	if (g_bValidateParaWhenRegist)
	{
		pParaObj->ValidateParaWhenRegist();
	}

	return pParaObj;
}

void CSttParaObjects::FindPara(const char *pszID, CSttParaObject **ppFind, POS *pPos)
{
	CSttParaObject* pParaObj = NULL;
	POS pos = GetHeadPosition();
	POS posPrev = pos;

	while (pos != NULL)
	{
		posPrev = pos;
		pParaObj = (CSttParaObject*)GetNext(pos);

		if( pParaObj->CompareID(pszID))
		{
			*ppFind = pParaObj;
			*pPos = posPrev;
			break;
		}
	}
}

void CSttParaObjects::FindPara(const CString &strID, CSttParaObject **ppFind, POS *pPos)
{
	CSttParaObject* pParaObj = NULL;
	POS pos = GetHeadPosition();
	POS posPrev = pos;

	while (pos != NULL)
	{
		posPrev = pos;
		pParaObj = (CSttParaObject*)GetNext(pos);

		if( pParaObj->CompareID(strID))
		{
			*ppFind = pParaObj;
			*pPos = posPrev;
			break;
		}
	}
}

void CSttParaObjects::FindPara(LPVOID pValAddr, CSttParaObject **ppFind, POS *pPos)
{
	CSttParaObject* pParaObj = NULL;
	POS pos = GetHeadPosition();
	POS posPrev = pos;

	while (pos != NULL)
	{
		posPrev = pos;
		pParaObj = (CSttParaObject*)GetNext(pos);

		if( pParaObj->CompareValAddr(pValAddr))
		{
			*ppFind = pParaObj;
			*pPos = posPrev;
			break;
		}
	}
}

void CSttParaObjects::UnRegisterPara(const char *pszID)
{
	CSttParaObject* pFind = NULL;
	POS pos = NULL;
	
	FindPara(pszID, &pFind, &pos);

	if (pFind != NULL)
	{
		RemoveAt(pos);
		delete pFind;
	}
}

void CSttParaObjects::UnRegisterPara(const CString &strID)
{
	CSttParaObject* pFind = NULL;
	POS pos = NULL;

	FindPara(strID, &pFind, &pos);

	if (pFind != NULL)
	{
		RemoveAt(pos);
		delete pFind;
	}
}

void CSttParaObjects::UnRegisterPara(LPVOID pValAddr)
{
	CSttParaObject* pFind = NULL;
	POS pos = NULL;

	FindPara(pValAddr, &pFind, &pos);

	if (pFind != NULL)
	{
		RemoveAt(pos);
		delete pFind;
	}
}

void CSttParaObjects::EditParaName(const char *pszID, const char *pszName)
{
	CSttParaObject* pFind = NULL;
	POS pos = NULL;

	FindPara(pszID, &pFind, &pos);

	if (pFind != NULL)
	{
		pFind->m_strName = (CString)pszName;
	}
}

void CSttParaObjects::EditParaName(const CString &strID, const CString &strName)
{
	CSttParaObject* pFind = NULL;
	POS pos = NULL;

	FindPara(strID, &pFind, &pos);

	if (pFind != NULL)
	{
		pFind->m_strName = strName;
	}
}

void CSttParaObjects::EditParaName(LPVOID pValAddr, const char *pszName)
{
	CSttParaObject* pFind = NULL;
	POS pos = NULL;

	FindPara(pValAddr, &pFind, &pos);

	if (pFind != NULL)
	{
		pFind->m_strName = (CString)pszName;
	}
}



//long CSttParaObjects::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
//{
//	CSttParaObject *pParaObj = NULL;
//	POS pos = GetHeadPosition();
//	while (pos != NULL)
//	{
//		pParaObj = (CSttParaObject *)GetNext(pos);
//		if (pParaObj != NULL)
//		{
//			pParaObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
//		}
//	}
//
//	return 0;
//}


CSttParaObject* CSttParaObjects::FindByVariable(const CString strID)
{
	CSttParaObject* pParaObj = NULL;
	long nIndex = 0;
	int nCount = GetCount();
	for(nIndex=0; nIndex<nCount; nIndex++)
	{
		pParaObj = (CSttParaObject*)GetAt(nIndex);
		if(pParaObj != NULL && pParaObj->GetVariable() == strID)
		{
			return pParaObj;
		}
	}

	return NULL;
}


float CSttParaObjects::GetValueByVariable(CString strID)
{
	CSttParaObject *pParaObj = NULL;

	pParaObj = FindByVariable(strID);
	if(pParaObj != NULL)
	{
		return pParaObj->GetValue();
	}

	return 0.0;
}

void CSttParaObjects::GetParameter(CString &strParameter, BOOL bOnlyGetChange)
{
	POS pos = GetHeadPosition();
	CSttParaObject *pPara = NULL;

	if (bOnlyGetChange)
	{
		CString strTemp;
		while (pos != NULL)
		{
			pPara = (CSttParaObject*)GetNext(pos);

			if (pPara->IsParaChanged())
			{
                strParameter.AppendFormat(_T("%s=%s;"),  pPara->m_strID.GetString(), pPara->m_varValue.ToString().GetString());
			}
		}
	}
	else
	{
		while (pos != NULL)
		{
			pPara = (CSttParaObject*)GetNext(pos);
            strParameter.AppendFormat(_T("%s=%s;"),  pPara->m_strID.GetString(), pPara->m_varValue.ToString().GetString());
		}
	}
}

CExBaseObject* CSttParaObjects::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CMacroXmlKeys::g_pMacroXmlKeys->m_strParaKey)
	{
		return new CSttParaObject();
	}

	return NULL;
}


void CSttParaObjects::GetReportEx(CString &strReport)
{
	CSttParaObject* pObject = NULL;
	POS pos = GetHeadPosition();
	CString strValue;

	while (pos != NULL)
	{
		pObject = (CSttParaObject*)GetNext(pos);
		strValue = pObject->m_varValue.ToString();
        strReport.AppendFormat(_T("%s=%s;"), pObject->m_strID.GetString(), strValue.GetString());
	}
}

void CSttParaObjects::GetReportEx(CStringSerializeBuffer &oBinaryBuffer)
{
	CSttParaObject* pObject = NULL;
	POS pos = GetHeadPosition();
	CString strValue;

	while (pos != NULL)
	{
		pObject = (CSttParaObject*)GetNext(pos);
		strValue = pObject->m_varValue.ToString();
	
		oBinaryBuffer << pObject->m_strID;
		oBinaryBuffer << _T("=");
		oBinaryBuffer << strValue;
		oBinaryBuffer << _T(";");
	}
}

void CSttParaObjects::Parser(CEquationBuffer *pEquation)
{
	CSttParaObject* pObject = NULL;
	POS pos = GetHeadPosition();
	CString strValue;

	while (pos != NULL)
	{
		pObject = (CSttParaObject*)GetNext(pos);

		if (pObject != NULL)
		{
			strValue = _T("");
			pEquation->ParseString(pObject->m_strID, strValue);

			if(strValue.GetLength() > 0)
			{
				pObject->SetParaValue(strValue, FALSE);
			}
			else
			{
				strValue = pObject->GetValueString();
				pObject->SetParaValue(strValue, FALSE);
			}
		}
	}
}

void CSttParaObjects::InitDefault()
{
	CSttParaObject* pObject = NULL;
	POS pos = GetHeadPosition();
	//CString strValue;

	while (pos != NULL)
	{
		pObject = (CSttParaObject*)GetNext(pos);
		//pObject->SetParaValue(pObject->m_strDefaultValue);
		pObject->InitByDefault();
	}
}

void CSttParaObjects::ReadParas(CXmlRWNodeBase &oNode, BSTR bstrParasKey)
{
    CXmlRWNodeListBase *oParas = NULL;
    CXmlRWNodeBase *oTemp = NULL;
    CXmlRWNodeListBase *oChildList = oNode.GetChildNodes();
    long nCount = oChildList->GetNodeNum();
	long nIndex = 0;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
        oTemp = oChildList->GetChild(nIndex);
        CString bstrID = oTemp->GetNodeName();

        if (bstrID == bstrParasKey)
		{
            oParas = oTemp->GetChildNodes();
			break;
		}
	}

	if(oParas == NULL)
	{
		return;
	}

    ReadParas(*oParas);
}

void CSttParaObjects::ReadParas(CXmlRWNodeListBase &oParas)
{
    long nCount = oParas.GetNodeNum();
	long nIndex = 0;
    CXmlRWNodeBase *oParaNode = NULL;
	CString strID;
 	CSttParaObject *p = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
        oParaNode = oParas.GetChild(nIndex);
        xml_GetAttibuteValue(CMacroXmlKeys::g_pMacroXmlKeys->m_strIDKey, *oParaNode, strID);
		
		p = (CSttParaObject *)FindByVariable(strID);

		if (p != NULL)
		{
            xml_GetAttibuteValue(CMacroXmlKeys::g_pMacroXmlKeys->m_strParaValueKey, *oParaNode, strID);
			p->SetParaValue(strID, FALSE);
		}
	}
}
