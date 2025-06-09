//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgGoutCh.cpp  CIecCfgGoutCh


#include "stdafx.h"
#include "IecCfgGoutCh.h"
#include "../../../Module/API/HexTransApi.h"

CIecCfgGoutCh::CIecCfgGoutCh()
{
	//初始化属性

	//初始化成员变量
	m_strAppChID = _T("v01");//g_strAppChID_None;
	m_strDevChID = g_strAppChID_None;//g_strAppChID_None;
	m_strDefaultValue = _T("[01]");
	m_strDataType = g_strGooseChType_Double;
	m_nIndexExternal = 65535;
}

CIecCfgGoutCh::~CIecCfgGoutCh()
{
}

void gout_tans_value(CString &strValue)
{
	if (strValue == _T("v00"))
	{
		strValue = _T("[00]");
	}
	else if (strValue == _T("v01"))
	{
		strValue = _T("[01]");
	}
	else if (strValue == _T("v10"))
	{
		strValue = _T("[10]");
	}
	else if (strValue == _T("v11"))
	{
		strValue = _T("[11]");
	}
}

long CIecCfgGoutCh::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataGooseChBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	if (m_strID.GetLength() == 0)
	{
		m_strID = m_strName;
	}

	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}

	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strDefaultValue);

	if (pXmlKeys->m_nXmlOnlyWrite_Id_Value == 0)
	{
		xml_GetAttibuteValue(pXmlKeys->m_strAddrExternalKey, oNode, m_strAddrExternal);
		xml_GetAttibuteValue(pXmlKeys->m_strDescExternalKey, oNode, m_strDescExternal);
		xml_GetAttibuteValue(pXmlKeys->m_strIndexExternalKey, oNode, m_nIndexExternal);
	}

	return 0;
}

void CIecCfgGoutCh::InitAfterRead()
{
	gout_tans_value(m_strDefaultValue);
	//gout_tans_value(m_strAppChID);

	if (m_strDataType == g_strGooseChType_Double)
	{
		CheckDefautValue_ChTypeDouble();

		if (m_strAppChID == _T("0"))
		{
			m_strAppChID = _T("[01]");
		}
	}
}

long CIecCfgGoutCh::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataGooseChBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	if (m_strDefaultValue.IsEmpty())//zhouhj 防止出现为空
	{
		if (m_strDataType == g_strGooseChType_Single)
		{
			m_strDefaultValue = _T("FALSE");
		}
		else if (m_strDataType == g_strGooseChType_Double)
		{
			m_strDefaultValue = _T("[01]");
		}
		else if (m_strDataType == g_strGooseChType_Time)//对于时间类的暂时忽略
		{
		}
		else if (m_strDataType == g_strGooseChType_Quality)
		{
			m_strDefaultValue = _T("0x0000");
		}
		else if (m_strDataType == g_strGooseChType_Float)
		{
			m_strDefaultValue = _T("0.0");
		}
		else if (m_strDataType == g_strGooseChType_Integer)
		{
			m_strDefaultValue = _T("0");
		}
		else if (m_strDataType == g_strGooseChType_UInteger)
		{
			m_strDefaultValue = _T("0");
		}
		else if (m_strDataType == g_strGooseChType_String)
		{
			m_strDefaultValue = _T("[1000000000000]");
		}
		else
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Gout通道值出现空,数据类型(%s)."),m_strDataType.GetString());
		}
	}

	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strDefaultValue);
	xml_SetAttributeValue(pXmlKeys->m_strAddrExternalKey, oElement, m_strAddrExternal);
	xml_SetAttributeValue(pXmlKeys->m_strDescExternalKey, oElement, m_strDescExternal);
	xml_SetAttributeValue(pXmlKeys->m_strIndexExternalKey, oElement, m_nIndexExternal);

	return 0;
}

BOOL CIecCfgGoutCh::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgDataGooseChBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgGoutCh *p = (CIecCfgGoutCh*)pObj;

	return TRUE;
}

BOOL CIecCfgGoutCh::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDataGooseChBase::CopyOwn(pDest);

	CIecCfgGoutCh *p = (CIecCfgGoutCh*)pDest;
	p->m_strDefaultValue = m_strDefaultValue;
	p->m_strAddrExternal = m_strAddrExternal;
	p->m_strDescExternal = m_strDescExternal;
	p->m_nIndexExternal = m_nIndexExternal;

	return TRUE;
}

CBaseObject* CIecCfgGoutCh::Clone()
{
	CIecCfgGoutCh *p = new CIecCfgGoutCh();
	Copy(p);
	return p;
}


// void CIecCfgGoutCh::GetChFlagHcn(long &nFlag, long &nHcn)
// {
// 
// }

BYTE CIecCfgGoutCh::Get_hbo()
{
// 	CIecGooseChDataTypeMngr *pDataTtypeMngr = CIecGlobalDataMngr::GetGooseDataTypeMngr();
// 	CDataType *pGooseChDataType = NULL;
// 	BYTE nHbo = 0;
// 	long nIndex = 0;
// 
// 	if (m_strDataType == g_strGooseChType_Single)
// 	{
// 		pGooseChDataType=pDataTtypeMngr->m_pGooseOutChSingle;
// 		nIndex = pGooseChDataType->FindIndexByID(m_strAppChID);
// 
// 		if (nIndex == 0)
// 		{
// 			nHbo = 0xF2;//nHbo = 0xF0;
// 		}
// 		else if (nIndex == 1)
// 		{
// 			nHbo = 0xF2;//nHbo = 0xF1;
// 		}
// 		else
// 		{
// 			nHbo = nIndex - 2;
// 		}
// 	}
// 	else if (m_strDataType == g_strGooseChType_Double)
// 	{
// 		pGooseChDataType=pDataTtypeMngr->m_pGooseOutChDouble;
// 		nIndex = pGooseChDataType->FindIndexByID(m_strAppChID);
// 
// 		if (nIndex == 0)
// 		{
// 			nHbo = 0xF2;//nHbo = 0xF0;
// 		}
// 		else if (nIndex == 1)
// 		{
// 			nHbo = 0xF2;//nHbo = 0xF1;
// 		}
// 		else if (nIndex == 2)
// 		{
// 			nHbo = 0xF2;//nHbo = 0xF0;
// 		}
// 		else if (nIndex == 3)
// 		{
// 			nHbo = 0xF2;//nHbo = 0xF1;
// 		}
// 		else
// 		{
// 			nHbo = nIndex - 4;
// 		}
// 	}
// 	else
// 	{
// 		nHbo = 0xF2;
// 	}
// 
// 	return nHbo;
	return 0;
}

BOOL CIecCfgGoutCh::IsDefaultValue()
{
	if (m_strDataType == g_strGooseChType_Single) 
	{
		if ( ( m_strAppChID == _T("0")) || (m_strAppChID == g_strAppChID_None) ) 
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else if (m_strDataType == g_strGooseChType_Double) 
	{
		if ( ( m_strAppChID == _T("01")) || (m_strAppChID == g_strAppChID_None) ) 
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
		return FALSE;
	}
}

void CIecCfgGoutCh::CheckDefautValue()
{
	if (m_strDataType == g_strGooseChType_Single)
	{
		CheckDefautValue_ChTypeSingle();
	}
	else if (m_strDataType == g_strGooseChType_Double)
	{
		CheckDefautValue_ChTypeDouble();
	}
	else if (m_strDataType == g_strGooseChType_Quality)
	{
		CheckDefautValue_ChTypeQuality();
	}
	else if (m_strDataType == g_strGooseChType_Float)
	{
		CheckDefautValue_ChTypeFloat();
	}
	else if (m_strDataType == g_strGooseChType_String)
	{
		CheckDefautValue_ChTypeString();
	}
	else if (m_strDataType == g_strGooseChType_Integer)
	{
		CheckDefautValue_ChTypeInteger();
	}
	else if (m_strDataType == g_strGooseChType_UInteger)
	{
		CheckDefautValue_ChTypeUInteger();
	}
	else if (m_strDataType == g_strGooseChType_Time)
	{
		m_strDefaultValue = _T("");
	}
}

void CIecCfgGoutCh::CheckDefautValue_ChTypeSingle()
{
// 	if (m_strAppChID == _T("v0"))//zhouhj 20211014 初始值独立设置
// 	{
// 		m_strDefaultValue = _T("FALSE");
// 	}
// 	else if (m_strAppChID == _T("v1"))
// 	{
// 		m_strDefaultValue = _T("TRUE");
// 	}
// 	else if ((m_strDefaultValue != _T("FALSE"))&&(m_strDefaultValue != _T("TRUE")))
// 	{
// 		m_strDefaultValue = _T("FALSE");
// 	}
}

void CIecCfgGoutCh::CheckDefautValue_ChTypeDouble()
{
// 	if (m_strAppChID == _T("v00"))//zhouhj 20211014 初始值独立设置
// 	{
// 		m_strDefaultValue = _T("[00]");
// 	}
// 	else if (m_strAppChID == _T("v01"))
// 	{
// 		m_strDefaultValue = _T("[01]");
// 	}
// 	else if (m_strAppChID == _T("v10"))
// 	{
// 		m_strDefaultValue = _T("[10]");
// 	}
// 	else if (m_strAppChID == _T("v11"))
// 	{
// 		m_strDefaultValue = _T("[11]");
// 	}
// 	else 
	
	if ((m_strDefaultValue != _T("[00]"))&&(m_strDefaultValue != _T("[01]"))&&
		(m_strDefaultValue != _T("[10]"))&&(m_strDefaultValue != _T("[11]")))
 	{
 		m_strDefaultValue = _T("[01]");
 	}
}

void CIecCfgGoutCh::CheckDefautValue_ChTypeQuality()
{
	if (m_strDefaultValue.GetLength()<=2)
	{
		m_strDefaultValue = _T("0X0000");
		return;
	}

	m_strDefaultValue.MakeUpper();
	BOOL bInvalid = FALSE;
	CString strTmp = m_strDefaultValue.Mid(2);

	if (m_strDefaultValue.Find(_T("0X")) != 0)//如果不是以0x开头,则默认为不带0x的16进制数据,后期固定增加0X
	{
		strTmp = m_strDefaultValue;
	}

	long nLength = strTmp.GetLength();
	char zfTmp;

	for (int nIndex = 0;nIndex<nLength;nIndex++)
	{
		zfTmp = strTmp.GetAt(nIndex);

		if ((zfTmp<'0')||(zfTmp>'F'))
		{
			bInvalid = TRUE;
			break;
		}

		if ((zfTmp>'9')&&(zfTmp<'A'))
		{
			bInvalid = TRUE;
			break;
		}
	}

	if (bInvalid)//如果无效，将其设置为初始值
	{
		m_strDefaultValue = _T("0X0000");
		return;
	}

	long nValue = 0;
#ifdef UNICODE
	char *pzfTmp = NULL;
	CString_to_char(strTmp,&pzfTmp);
	HexToLong(pzfTmp,nValue);
	delete pzfTmp;

#else
	HexToLong(strTmp.GetString(),nValue);
#endif
	nValue = nValue%0x10000;

	m_strDefaultValue.Format(_T("0X%04X"),nValue);
//	m_strDefaultValue.Format(_T("0X%s"),strTmp.GetString());
}

void CIecCfgGoutCh::CheckDefautValue_ChTypeFloat()
{
	if ((m_strDefaultValue.IsEmpty())||(m_strDefaultValue.Find('.') != m_strDefaultValue.ReverseFind('.')))//如果为空,或者有多个'.'则为无效数据
	{
		m_strDefaultValue = _T("0.0");
		return;
	}

	CString strTmp = m_strDefaultValue;
	BOOL bNeg = FALSE,bInvalid = FALSE;

	if (m_strDefaultValue.GetAt(0) == '-')
	{
		strTmp = m_strDefaultValue.Mid(1);
		bNeg = TRUE;
	}

	long nLength = strTmp.GetLength();
	char zfTmp;

	for (int nIndex = 0;nIndex<nLength;nIndex++)
	{
		zfTmp = strTmp.GetAt(nIndex);

		if ((zfTmp == '.'))
		{
			continue;
		}

		if ((zfTmp<'0')||(zfTmp>'9'))
		{
			bInvalid = TRUE;
			break;
		}
	}

	if (bInvalid)
	{
		m_strDefaultValue = _T("0.0");
	}
	else 
	{
		long nIndex = m_strDefaultValue.Find(_T("."));
		long nInterLenth = 0,nDecimalLenth = 0;
		CString strInter,strDeci;

		if (nIndex == -1)
		{
			nInterLenth = m_strDefaultValue.GetLength();
			strInter = m_strDefaultValue;
		} 
		else
		{
			strInter = m_strDefaultValue.Left(nIndex);
			nInterLenth = strInter.GetLength();
			strDeci = m_strDefaultValue.Mid(nIndex+1);
			nDecimalLenth = strDeci.GetLength();
		}

		if ((nInterLenth>7)||(nDecimalLenth>4))//整数位长度不超过7,小数位长度不超过4
		{
			if (nInterLenth>7)
			{
				m_strDefaultValue = strInter.Left(7);
			} 
			else
			{
				m_strDefaultValue = strInter;
			}

			if (nDecimalLenth == 0)
			{
			}
			else if (nDecimalLenth>4)
			{
                strTmp = strDeci.Left(4);
                m_strDefaultValue.AppendFormat(_T(".%s"),strTmp.GetString());
			}
			else
			{
                m_strDefaultValue.AppendFormat(_T(".%s"),strDeci.GetString());
			}
		}
	}
}

void CIecCfgGoutCh::CheckDefautValue_ChTypeString()
{
// 	if (m_strDefaultValue.IsEmpty())
// 	{
// 		m_strDefaultValue = _T("[0000000000000]");
// 	}
	long nLength = m_strDefaultValue.GetLength();

	if ((nLength<=2)||(nLength>34))//总长度不能超过32位,去除括号,不能小于0
	{
		m_strDefaultValue = _T("[0000000000000]");
		return;
	}

	BOOL bInvalid = FALSE;

	if (m_strDefaultValue.GetAt(0) != '[')
	{
		bInvalid = TRUE;
	}

	if (m_strDefaultValue.GetAt(nLength-1) != ']')
	{
		bInvalid = TRUE;
	}

	char zfTmp;
	nLength--;//去除最后一个字符

	for (int nIndex = 1;nIndex<nLength;nIndex++)
	{
		zfTmp = m_strDefaultValue.GetAt(nIndex);

		if ((zfTmp != '0')&&(zfTmp != '1'))
		{
			bInvalid = TRUE;
		}
	}

	if (bInvalid)
	{
		m_strDefaultValue = _T("[0000000000000]");
	}
}

void CIecCfgGoutCh::CheckDefautValue_ChTypeInteger()
{
	if (m_strDefaultValue.IsEmpty())//如果为空
	{
		m_strDefaultValue = _T("0");
		return;
	}

	CString strTmp = m_strDefaultValue;
	BOOL bNeg = FALSE,bInvalid = FALSE;

	if (m_strDefaultValue.GetAt(0) == '-')
	{
		strTmp = m_strDefaultValue.Mid(1);
		bNeg = TRUE;
	}

	long nLength = strTmp.GetLength();
	char zfTmp;

	for (int nIndex = 0;nIndex<nLength;nIndex++)
	{
		zfTmp = strTmp.GetAt(nIndex);

		if ((zfTmp<'0')||(zfTmp>'9'))
		{
			bInvalid = TRUE;
			break;
		}
	}

	if (bInvalid)
	{
		m_strDefaultValue = _T("0");
	}
}

void CIecCfgGoutCh::CheckDefautValue_ChTypeUInteger()
{
	if (m_strDefaultValue.IsEmpty())//如果为空
	{
		m_strDefaultValue = _T("0");
		return;
	}

	BOOL bInvalid = FALSE;
	long nLength = m_strDefaultValue.GetLength();
	char zfTmp;

	for (int nIndex = 0;nIndex<nLength;nIndex++)
	{
		zfTmp = m_strDefaultValue.GetAt(nIndex);

		if ((zfTmp<'0')||(zfTmp>'9'))
		{
			bInvalid = TRUE;
			break;
		}
	}

	if (bInvalid)
	{
		m_strDefaultValue = _T("0");
	}
}
