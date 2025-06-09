//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgSmvRate.cpp  CIecCfgSmvRate


#include "stdafx.h"
#include "IecCfgSmvRate.h"

CIecCfgSmvRate::CIecCfgSmvRate()
{
	//初始化属性
	m_fRate = 0;

	m_nCodeValue = 1000;
	m_nMeasCurrCodeValue = 1000;
	m_fPrimValue = 100;
	m_strAliasName = "";

	//初始化成员变量
}

CIecCfgSmvRate::~CIecCfgSmvRate()
{
}

long CIecCfgSmvRate::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strRateKey, oNode, m_fRate);
	xml_GetAttibuteValue(pXmlKeys->m_strCodeValueKey, oNode, m_nCodeValue);
	xml_GetAttibuteValue(pXmlKeys->m_strMeasCurrCodeValueKey, oNode, m_nMeasCurrCodeValue);
	xml_GetAttibuteValue(pXmlKeys->m_strPrimValueKey, oNode, m_fPrimValue);
	xml_GetAttibuteValue(pXmlKeys->m_strAliasNameKey, oNode, m_strAliasName);

	return 0;
}

long CIecCfgSmvRate::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strRateKey, oElement, m_fRate);
	xml_SetAttributeValue (pXmlKeys->m_strCodeValueKey, oElement, m_nCodeValue);
	xml_SetAttributeValue (pXmlKeys->m_strMeasCurrCodeValueKey, oElement, m_nMeasCurrCodeValue);
	xml_SetAttributeValue (pXmlKeys->m_strPrimValueKey, oElement, m_fPrimValue);
	xml_SetAttributeValue (pXmlKeys->m_strAliasNameKey, oElement, m_strAliasName);

	return 0;
}

long CIecCfgSmvRate::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_fRate);
		BinarySerializeCalLen(oBinaryBuffer, m_nCodeValue);
		BinarySerializeCalLen(oBinaryBuffer, m_nMeasCurrCodeValue);
		BinarySerializeCalLen(oBinaryBuffer, m_fPrimValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strAliasName);

	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_fRate);
		BinarySerializeRead(oBinaryBuffer, m_nCodeValue);
		BinarySerializeRead(oBinaryBuffer, m_nMeasCurrCodeValue);
		BinarySerializeRead(oBinaryBuffer, m_fPrimValue);
		BinarySerializeRead(oBinaryBuffer, m_strAliasName);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_fRate);
		BinarySerializeWrite(oBinaryBuffer, m_nCodeValue);
		BinarySerializeWrite(oBinaryBuffer, m_nMeasCurrCodeValue);
		BinarySerializeWrite(oBinaryBuffer, m_fPrimValue);
		BinarySerializeWrite(oBinaryBuffer, m_strAliasName);
	}
	return 0;
}

void CIecCfgSmvRate::InitAfterRead()
{
	if (m_strAliasName.GetLength()<=2)
	{
		InitDefaultAliasName();
	}
}

BOOL CIecCfgSmvRate::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgSmvRate *p = (CIecCfgSmvRate*)pObj;

	if(m_fRate != p->m_fRate)
	{
		return FALSE;
	}

	if(m_nCodeValue!= p->m_nCodeValue)
	{
		return FALSE;
	}

	if(m_nMeasCurrCodeValue!= p->m_nMeasCurrCodeValue)
	{
		return FALSE;
	}

	if(m_fPrimValue!= p->m_fPrimValue)
	{
		return FALSE;
	}
	if(m_strAliasName!= p->m_strAliasName)
	{
		return FALSE;
	}


	return TRUE;
}

BOOL CIecCfgSmvRate::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecCfgSmvRate *p = (CIecCfgSmvRate*)pDest;

	p->m_fRate = m_fRate;
	p->m_nCodeValue = m_nCodeValue;
	p->m_nMeasCurrCodeValue = m_nMeasCurrCodeValue;
	p->m_fPrimValue = m_fPrimValue;
	p->m_strAliasName = m_strAliasName;

	return TRUE;
}

CBaseObject* CIecCfgSmvRate::Clone()
{
	CIecCfgSmvRate *p = new CIecCfgSmvRate();
	Copy(p);
	return p;
}

BOOL CIecCfgSmvRate::IsVolChsGroup()
{
	if (m_strID.Find("U")>=0)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CIecCfgSmvRate::IsDcFT3VolChsGroup()
{
	if(m_strID == "Uabcz" || m_strID == "Up-abcz")
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CIecCfgSmvRate::IsDcFT3CurChsGroup()
{
	if(m_strID == "Iabc" || m_strID == "Ip-abc" || 
		m_strID == "Is-abc" || m_strID == "It-abc")
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CIecCfgSmvRate::IsAcFT3VolChsGroup()
{
	if(m_strID == "Us-abcz" || m_strID == "Ut-abcz")
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CIecCfgSmvRate::IsAcFT3CurChsGroup()
{
	if(m_strID == "I5-abc" || m_strID == "I6-abc")
	{
		return TRUE;
	}

	return FALSE;
}

void CIecCfgSmvRate::InitDefaultAliasName()
{	
	if(m_strID == "Uabcz")
	{
		m_strAliasName = "U1-1/2/3";
	}
	if(m_strID == "Iabc")
	{
		m_strAliasName = "I1-1/2/3";
	}
	if(m_strID == "Up-abcz")
	{
		m_strAliasName = "U2-1/2/3";
	}
	if(m_strID == "Ip-abc")
	{
		m_strAliasName = "I2-1/2/3";
	}
	if(m_strID == "Us-abcz")
	{
		m_strAliasName = "U1-a/b/c";
	}
	if(m_strID == "Is-abc")
	{
		m_strAliasName = "I3-1/2/3";
	}
	if(m_strID == "Ut-abcz")
	{
		m_strAliasName = "U2-a/b/c";
	}
	if(m_strID == "It-abc")
	{
		m_strAliasName = "I4-1/2/3";
	}
	if(m_strID == "I5-abc")
	{
		m_strAliasName = "I1-a/b/c";
	}
	if(m_strID == "I6-abc")
	{
		m_strAliasName = "I2-a/b/c";
	}
}

CString st_GetSmvRateID(const CString& strAppCh,BOOL bDCFT3)
{
	CString strSmvRateID = _T("");

	if (strAppCh == _T("Ua1")||strAppCh==_T("Ub1")||strAppCh==_T("Uc1")||strAppCh==_T("U01"))
	{
		if (bDCFT3)
		{
			strSmvRateID = g_strSmvVolRateID[2/*4*/];//zhouhj 2024.2.29 交流电压通道从原有第5组改为第3组
		}
		else
		{
			strSmvRateID = g_strSmvVolRateID[0];
		}
	}
	else if (strAppCh == _T("Ia1")||strAppCh==_T("Ib1")||strAppCh==_T("Ic1")||strAppCh==_T("I01"))
	{
		if (bDCFT3)
			strSmvRateID = g_strSmvCurrentRateID[4];
		else
			strSmvRateID = g_strSmvCurrentRateID[0];
	}
	else if (strAppCh == _T("Ua2")||strAppCh==_T("Ub2")||strAppCh==_T("Uc2")||strAppCh==_T("U02"))
	{
		if (bDCFT3)
		{
			strSmvRateID = g_strSmvVolRateID[3/*5*/];//zhouhj 2024.2.29 交流电压通道从原有第6组改为第4组
		} 
		else
		{
			strSmvRateID = g_strSmvVolRateID[1];
		}
	}
	else if (strAppCh == _T("Ia2")||strAppCh==_T("Ib2")||strAppCh==_T("Ic2")||strAppCh==_T("I02"))
	{
		if (bDCFT3)
		{
			strSmvRateID = g_strSmvCurrentRateID[5];
		} 
		else
		{
			strSmvRateID = g_strSmvCurrentRateID[1];
		}
	}
	else if (strAppCh == _T("Ua3")||strAppCh==_T("Ub3")||strAppCh==_T("Uc3")||strAppCh==_T("U03"))
	{
		strSmvRateID = _T("Us-abcz");
	}
	else if (strAppCh == _T("Ia3")||strAppCh==_T("Ib3")||strAppCh==_T("Ic3")||strAppCh==_T("I03"))
	{
		strSmvRateID = _T("Is-abc");
	}
	else if (strAppCh == _T("Ua4")||strAppCh==_T("Ub4")||strAppCh==_T("Uc4")||strAppCh==_T("U04"))
	{
		strSmvRateID = _T("Ut-abcz");
	}
	else if (strAppCh == _T("Ia4")||strAppCh==_T("Ib4")||strAppCh==_T("Ic4")||strAppCh==_T("I04"))
	{
		strSmvRateID = _T("It-abc");
	}
	else if (strAppCh == _T("Ua5")||strAppCh==_T("Ub5")||strAppCh==_T("Uc5")||strAppCh==_T("U05"))
	{
		strSmvRateID = _T("U5-abcz");
	}
	else if (strAppCh == _T("Ia5")||strAppCh==_T("Ib5")||strAppCh==_T("Ic5")||strAppCh==_T("I05"))
	{
		strSmvRateID = _T("I5-abc");
	}
	else if (strAppCh == _T("Ua6")||strAppCh==_T("Ub6")||strAppCh==_T("Uc6")||strAppCh==_T("U06"))
	{
		strSmvRateID = _T("U6-abcz");
	}
	else if (strAppCh == _T("Ia6")||strAppCh==_T("Ib6")||strAppCh==_T("Ic6")||strAppCh==_T("I06"))
	{
		strSmvRateID = _T("I6-abc");
	}
	else if ((strAppCh.Find("-") == 2)&&(strAppCh.GetLength() == 4))
	{
		long nIndex = strAppCh.GetAt(1) - '1';

		if (nIndex<0)
		{
			return strSmvRateID;
		}

		if (nIndex>=SMV_RATE_MAX_NUM)
		{
			return strSmvRateID;
		}

		if (strAppCh.GetAt(0) == 'U')
		{
			strSmvRateID = g_strSmvVolRateID[nIndex];
		} 
		else if (strAppCh.GetAt(0) == 'I')
		{
			strSmvRateID = g_strSmvCurrentRateID[nIndex];
		}
	}

	return strSmvRateID;
}

