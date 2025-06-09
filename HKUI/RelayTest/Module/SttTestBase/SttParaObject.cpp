//#include "StdAfx.h"
#include "../../../Module/OSInterface/QT/stdafx.h"
#include "SttParaObject.h"

 long g_nParaRegisterDescInfor = REGSTER_MODE_ALL;

CSttParaObject::CSttParaObject(void)
{
	
}

CSttParaObject::~CSttParaObject(void)
{
}

CSttParaObject::CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,int *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(strName,strID,strUnit,strDataTypeID,strDefaultValue);//,nKeyType);
	m_varValue = value;
	//SetParaValue(strDefaultValue);
	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,long *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(strName,strID,strUnit,strDataTypeID,strDefaultValue);//,nKeyType);
	m_varValue = value;
	//SetParaValue(strDefaultValue);
	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,float *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(strName,strID,strUnit,strDataTypeID,strDefaultValue);//,nKeyType);
	m_varValue = value;
	//SetParaValue(strDefaultValue);
	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,double *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(strName,strID,strUnit,strDataTypeID,strDefaultValue);//,nKeyType);
	m_varValue = value;
	//SetParaValue(strDefaultValue);
	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,unsigned char *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(strName,strID,strUnit,strDataTypeID,strDefaultValue);//,nKeyType);
	m_varValue = value;
	//SetParaValue(strDefaultValue);
	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,short *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(strName,strID,strUnit,strDataTypeID,strDefaultValue);//,nKeyType);
	m_varValue = value;
	//SetParaValue(strDefaultValue);
	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,const char *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(strName,strID,strUnit,strDataTypeID,strDefaultValue);//,nKeyType);
	m_varValue = value;
	//SetParaValue(strDefaultValue);
	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,int *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue);//,nKeyType);
	m_varValue = value;
	m_varValue.FromString(pszDefaultValue);
	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,long *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue);//,nKeyType);
	m_varValue = value;
	m_varValue.FromString(pszDefaultValue);
	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,float *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue);//,nKeyType);
	m_varValue = value;
	m_varValue.FromString(pszDefaultValue);
	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,double *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue);//,nKeyType);
	m_varValue = value;
	m_varValue.FromString(pszDefaultValue);
	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,unsigned char *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue);//,nKeyType);
	m_varValue = value;
	m_varValue.FromString(pszDefaultValue);
	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,short *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue);//,nKeyType);
	m_varValue = value;
	m_varValue.FromString(pszDefaultValue);
	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,const char *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue);//,nKeyType);
	m_varValue = value;
	m_varValue.FromString(pszDefaultValue);
	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue, VAR_DOUBLE_LIST *val)
{
    SetPara(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue);
    m_varValue = val;
}

CSttParaObject::CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue, VAR_FLOAT_LIST *val)
{
    SetPara(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue);
    m_varValue = val;
}

CSttParaObject::CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue, VAR_INT_LIST *val)
{
    SetPara(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue);
    m_varValue = val;
}


void CSttParaObject::SetPara(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
    if (g_nParaRegisterDescInfor == REGSTER_MODE_ALL)
	{
		m_strName = strName;
		m_strUnit = strUnit;
	}
    else if (g_nParaRegisterDescInfor == REGSTER_MODE_NAME_EQ_ID)
    {
        m_strName = strID;
    }
    else
    {
    }

	m_strID = strID;
	m_strDataTypeID = strDataTypeID;
	m_strDefaultValue = strDefaultValue;
	//m_nKeyType = nKeyType;
}

void CSttParaObject::SetPara(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{	
    if (g_nParaRegisterDescInfor == REGSTER_MODE_ALL)
    {
        m_strName = pszName;
        m_strUnit = pszUnit;
    }
    else if (g_nParaRegisterDescInfor == REGSTER_MODE_NAME_EQ_ID)
    {
        m_strName = pszID;
    }
    else
    {
    }

	m_strDataTypeID = (pszDataTypeID);
	m_strID = (pszID);
	m_strDefaultValue = (pszDefaultValue);
	//m_nKeyType = nKeyType;
}

long CSttParaObject::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMacroXmlKeys *pOnlyCtrlXmlKeys = (CMacroXmlKeys *)pXmlRWKeys;
	xml_GetAttibuteValue(pOnlyCtrlXmlKeys->m_strParaUnitKey, oNode, m_strUnit);
	xml_GetAttibuteValue(pOnlyCtrlXmlKeys->m_strParaDataTypeKey, oNode, m_strDataTypeID);
	xml_GetAttibuteValue(pOnlyCtrlXmlKeys->m_strParaDefValueKey, oNode, m_strDefaultValue);
	xml_GetAttibuteValue(pOnlyCtrlXmlKeys->m_strCreateGroupKey, oNode, m_strCreateGroup);

	return 0;
}

long CSttParaObject::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMacroXmlKeys *pOnlyCtrlXmlKeys = (CMacroXmlKeys *)pXmlRWKeys;
	xml_SetAttributeValue(pOnlyCtrlXmlKeys->m_strParaUnitKey, oElement, m_strUnit);
	xml_SetAttributeValue(pOnlyCtrlXmlKeys->m_strParaDataTypeKey, oElement, m_strDataTypeID);
	xml_SetAttributeValue(pOnlyCtrlXmlKeys->m_strParaValueKey, oElement, m_varValue.ToString());
	xml_SetAttributeValue(pOnlyCtrlXmlKeys->m_strParaDefValueKey, oElement, m_strDefaultValue);

	if (m_strCreateGroup.GetLength() > 0)
	{
		xml_SetAttributeValue(pOnlyCtrlXmlKeys->m_strCreateGroupKey, oElement, m_strCreateGroup);
	}

	return 0;
}


void CSttParaObject::SetParaValue(const CString &strValue, BOOL bUpdateDefault)
{
	char *pStr = NULL;
//	pStr = StringToChar(strValue);
	CString_to_char(strValue, &pStr);	//JJJJ
	m_varValue.FromString(pStr);

	if (bUpdateDefault)
	{
		m_varValue.UpdateDefaultValue();
	}

	delete []pStr;
}

float CSttParaObject::GetValue()
{
    return m_varValue.get_float();
}

BOOL CSttParaObject::IsParaChanged()
{
	return m_varValue.IsValueChange();

	CString strTemp;
	strTemp = m_varValue.ToString();

	if (strTemp != m_strDefaultValue)
	{
		if (IsStringNumber(strTemp) && IsStringNumber(m_strDefaultValue))
		{
			if (CString_To_double(strTemp) != CString_To_double(m_strDefaultValue))
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

void CSttParaObject::InitByDefault()
{
	m_varValue.InitByDefault();
}

CDvmData* CSttParaObject::ToDvmData()
{
    CDvmData *pNew = new CDvmData();
    pNew->m_strName = m_strName;
    pNew->m_strID = m_strID;
    pNew->m_strDataType = m_strDataTypeID;
    pNew->m_strDefaultValue = m_strDefaultValue;
    pNew->m_strValue = m_varValue.ToString();

    return pNew;
}


