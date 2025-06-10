#include "StdAfx.h"
#include "SttParaObject.h"

 BOOL g_bParaRegisterDescInfor = FALSE;
 BOOL g_bValidateParaWhenRegist = FALSE;
 BOOL g_bValueFromStringWhenRegister = FALSE;

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

	//2018-5-25:去掉根据缺省值初始化的功能，参见：
	//CSttTestBase::RegisterParas()：注册时，初始化缺省值
	//CSttTestBase::SetParameter(CEquationBuffer *pEquation)：测试时，初始化缺省值
	//m_varValue.FromString(pszDefaultValue);

	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,long *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(strName,strID,strUnit,strDataTypeID,strDefaultValue);//,nKeyType);
	m_varValue = value;

	//2018-5-25:去掉根据缺省值初始化的功能，参见：
	//CSttTestBase::RegisterParas()：注册时，初始化缺省值
	//CSttTestBase::SetParameter(CEquationBuffer *pEquation)：测试时，初始化缺省值
	//m_varValue.FromString(pszDefaultValue);

	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,float *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(strName,strID,strUnit,strDataTypeID,strDefaultValue);//,nKeyType);
	m_varValue = value;

	//2018-5-25:去掉根据缺省值初始化的功能，参见：
	//CSttTestBase::RegisterParas()：注册时，初始化缺省值
	//CSttTestBase::SetParameter(CEquationBuffer *pEquation)：测试时，初始化缺省值
	//m_varValue.FromString(pszDefaultValue);

	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,double *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(strName,strID,strUnit,strDataTypeID,strDefaultValue);//,nKeyType);
	m_varValue = value;

	//2018-5-25:去掉根据缺省值初始化的功能，参见：
	//CSttTestBase::RegisterParas()：注册时，初始化缺省值
	//CSttTestBase::SetParameter(CEquationBuffer *pEquation)：测试时，初始化缺省值
	//m_varValue.FromString(pszDefaultValue);

	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,unsigned char *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(strName,strID,strUnit,strDataTypeID,strDefaultValue);//,nKeyType);
	m_varValue = value;

	//2018-5-25:去掉根据缺省值初始化的功能，参见：
	//CSttTestBase::RegisterParas()：注册时，初始化缺省值
	//CSttTestBase::SetParameter(CEquationBuffer *pEquation)：测试时，初始化缺省值
	//m_varValue.FromString(pszDefaultValue);

	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,short *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(strName,strID,strUnit,strDataTypeID,strDefaultValue);//,nKeyType);
	m_varValue = value;

	//2018-5-25:去掉根据缺省值初始化的功能，参见：
	//CSttTestBase::RegisterParas()：注册时，初始化缺省值
	//CSttTestBase::SetParameter(CEquationBuffer *pEquation)：测试时，初始化缺省值
	//m_varValue.FromString(pszDefaultValue);

	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,const char *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(strName,strID,strUnit,strDataTypeID,strDefaultValue);//,nKeyType);
	m_varValue = value;

	//2018-5-25:去掉根据缺省值初始化的功能，参见：
	//CSttTestBase::RegisterParas()：注册时，初始化缺省值
	//CSttTestBase::SetParameter(CEquationBuffer *pEquation)：测试时，初始化缺省值
	//m_varValue.FromString(pszDefaultValue);

	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,int *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue);//,nKeyType);
	m_varValue = value;

	//2018-5-25:去掉根据缺省值初始化的功能，参见：
	//CSttTestBase::RegisterParas()：注册时，初始化缺省值
	//CSttTestBase::SetParameter(CEquationBuffer *pEquation)：测试时，初始化缺省值
	//m_varValue.FromString(pszDefaultValue);
	if (g_bValueFromStringWhenRegister)
	{
		m_varValue.FromString(pszDefaultValue);
	}

	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,long *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue);//,nKeyType);
	m_varValue = value;

	//2018-5-25:去掉根据缺省值初始化的功能，参见：
	//CSttTestBase::RegisterParas()：注册时，初始化缺省值
	//CSttTestBase::SetParameter(CEquationBuffer *pEquation)：测试时，初始化缺省值
	//m_varValue.FromString(pszDefaultValue);
	if (g_bValueFromStringWhenRegister)
	{
		m_varValue.FromString(pszDefaultValue);
	}

	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,float *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue);//,nKeyType);
	m_varValue = value;

	//2018-5-25:去掉根据缺省值初始化的功能，参见：
	//CSttTestBase::RegisterParas()：注册时，初始化缺省值
	//CSttTestBase::SetParameter(CEquationBuffer *pEquation)：测试时，初始化缺省值
	//m_varValue.FromString(pszDefaultValue);
	if (g_bValueFromStringWhenRegister)
	{
		m_varValue.FromString(pszDefaultValue);
	}

	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,double *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue);//,nKeyType);
	m_varValue = value;

	//2018-5-25:去掉根据缺省值初始化的功能，参见：
	//CSttTestBase::RegisterParas()：注册时，初始化缺省值
	//CSttTestBase::SetParameter(CEquationBuffer *pEquation)：测试时，初始化缺省值
	//m_varValue.FromString(pszDefaultValue);
	if (g_bValueFromStringWhenRegister)
	{
		m_varValue.FromString(pszDefaultValue);
	}

	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,unsigned char *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue);//,nKeyType);
	m_varValue = value;

	//2018-5-25:去掉根据缺省值初始化的功能，参见：
	//CSttTestBase::RegisterParas()：注册时，初始化缺省值
	//CSttTestBase::SetParameter(CEquationBuffer *pEquation)：测试时，初始化缺省值
	//m_varValue.FromString(pszDefaultValue);
	if (g_bValueFromStringWhenRegister)
	{
		m_varValue.FromString(pszDefaultValue);
	}

	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,short *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue);//,nKeyType);
	m_varValue = value;

	//2018-5-25:去掉根据缺省值初始化的功能，参见：
	//CSttTestBase::RegisterParas()：注册时，初始化缺省值
	//CSttTestBase::SetParameter(CEquationBuffer *pEquation)：测试时，初始化缺省值
	//m_varValue.FromString(pszDefaultValue);
	if (g_bValueFromStringWhenRegister)
	{
		m_varValue.FromString(pszDefaultValue);
	}

	m_varValue.UpdateDefaultValue();
}

CSttParaObject::CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,const char *value)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	SetPara(pszName,pszID,pszUnit,pszDataTypeID,pszDefaultValue);//,nKeyType);
	m_varValue = value;
	
	//2018-5-25:去掉根据缺省值初始化的功能，参见：
	//CSttTestBase::RegisterParas()：注册时，初始化缺省值
	//CSttTestBase::SetParameter(CEquationBuffer *pEquation)：测试时，初始化缺省值
	//m_varValue.FromString(pszDefaultValue);
	if (g_bValueFromStringWhenRegister)
	{
		m_varValue.FromString(pszDefaultValue);
	}

	m_varValue.UpdateDefaultValue();
}


void CSttParaObject::SetPara(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{
	if (g_bParaRegisterDescInfor)
	{
		m_strName = strName;
		m_strUnit = strUnit;
	}

	m_strID = strID;
	m_strDataTypeID = strDataTypeID;
	m_strDefaultValue = strDefaultValue;
	//m_nKeyType = nKeyType;
}

void CSttParaObject::SetPara(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue)//,long nKeyType/*=KEYTYPE_PARAMETERKEY*/)
{	
	if (g_bParaRegisterDescInfor)
	{
		m_strName = (pszName);
		m_strUnit = (pszUnit);
	}

	m_strDataTypeID = (pszDataTypeID);
	m_strID = (pszID);
	m_strDefaultValue = (pszDefaultValue);
	//m_nKeyType = nKeyType;
}

void CSttParaObject::ValidateParaWhenRegist()
{
	CString strVal, strDefVal;
	strVal=m_varValue.ToString();
	strDefVal = m_strDefaultValue;

	ChopFloatString(strVal, 0);
	ChopFloatString(strDefVal, 0);

	if (strVal != strDefVal)
	{
		CExBaseObject *pRoot = (CExBaseObject*)GetRoot();
		CString strPath = GetParaPath_ID();
        CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("%s==>>[%s] 缺省值[%s] != 实际值[%s]"), pRoot->m_strName.GetString(), strPath.GetString(), strDefVal.GetString(), strVal.GetString());
	}
}

CString CSttParaObject::GetParaPath_ID()
{
	CExBaseObject *pParent = (CExBaseObject*)m_pParent;
	CString strPath, strTemp;
	strPath = m_strID;
	UINT nClassID = 0;

	while (pParent != NULL)
	{
		nClassID = pParent->GetClassID();

		if (nClassID != PARACLASSID_PARAGROUP
			&& nClassID != PARACLASSID_PARAS)
		{
			break;
		}

		if (pParent->m_strID.GetLength() == 0)
		{
			pParent = (CExBaseObject *)pParent->GetParent();
			continue;
		}

        strTemp.Format(_T("%s$"), pParent->m_strID.GetString());
		strPath = strTemp + strPath;
		pParent = (CExBaseObject *)pParent->GetParent();
	}

	return strPath;
}

CString CSttParaObject::GetParaPath_Name()
{
	CExBaseObject *pParent = (CExBaseObject*)m_pParent;
	CString strPath, strTemp;
	strPath = m_strID;
	UINT nClassID = 0;

	while (pParent != NULL)
	{
		nClassID = pParent->GetClassID();

		if (nClassID != PARACLASSID_PARAGROUP
			|| nClassID != PARACLASSID_PARAS)
		{
			break;
		}

        strTemp.Format(_T("%s$"), pParent->m_strName.GetString());
		strPath = strTemp + strPath;
		pParent = (CExBaseObject *)pParent->GetParent();
	}

	return strPath;
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
	float fTemp;

    fTemp = (float)CString_To_double(m_varValue.ToString());

	return fTemp;
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

