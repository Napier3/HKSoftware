//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgGinCh.cpp  CIecCfgGinCh


#include "stdafx.h"
#include "IecCfgGinCh.h"
#include "../../../Module/System/StringTokenizer.h"
#include"../../Module/XLanguageResourceIec.h"

CIecCfgGinCh::CIecCfgGinCh()
{
	//初始化属性

	//初始化成员变量
	m_strAppChID = g_strAppChID_None;
	m_strDevChID = _T("v0");
	m_strDataType = g_strGooseChType_Single;
	m_strDefaultValue = _T("[01]");
	m_nColIndex = 0;
	m_nPos = 0;
	//m_dwAppChID = 0;
}

CIecCfgGinCh::~CIecCfgGinCh()
{
}

void gin_tans_value(CString &strValue)
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

long CIecCfgGinCh::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataGooseChBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAddrExternalKey, oNode, m_strExternAddr);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strDefaultValue);
	if (m_strID.GetLength() == 0)
	{
		m_strID = m_strName;
	}

	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}

	if (m_strAppChID == _T("---"))
	{
		m_strAppChID = g_strAppChID_None;
	}

	return 0;
}
void CIecCfgGinCh::InitAfterRead()
{
	gin_tans_value(m_strDefaultValue);
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

long CIecCfgGinCh::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
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
		//else
		//{
		//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Gout通道值出现空,数据类型(%s)."),m_strDataType.GetString());
		//}
	}
	if (pXmlKeys->m_nXmlOnlyWrite_Id_Value == 0)
	{
		xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strDefaultValue);
		xml_SetAttributeValue(pXmlKeys->m_strAddrExternalKey, oElement, m_strExternAddr);
	}

	return 0;
}

BOOL CIecCfgGinCh::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgDataGooseChBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgGinCh *p = (CIecCfgGinCh*)pObj;

	return TRUE;
}

BOOL CIecCfgGinCh::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDataGooseChBase::CopyOwn(pDest);

	CIecCfgGinCh *p = (CIecCfgGinCh*)pDest;
	p->m_strDefaultValue = m_strDefaultValue;

	return TRUE;
}

CBaseObject* CIecCfgGinCh::Clone()
{
	CIecCfgGinCh *p = new CIecCfgGinCh();
	Copy(p);
	return p;
}

DWORD CIecCfgGinCh::GetGinAppID()
{
	if (m_strAppChID == g_strAppChID_None)
	{
		return 0;
	}

	CStringTokenizer oToken;
	oToken.Init(m_strAppChID, ';');
	const char *pBinID = NULL;
	long nIndex = 0;
	DWORD dwBinValue = 0;

	while (oToken.HasMoreElements())
	{
		pBinID = oToken.NextToken();
		nIndex = iecfg_GetBinIndex(pBinID);

		if (nIndex > 0)
		{
			nIndex--;
			dwBinValue |= (1 << nIndex);
		}
	}

	return dwBinValue;
}


void CIecCfgGinCh::SetGinAppID(DWORD dwAppID)
{
	iecfg_GetBinID(dwAppID, m_strAppChID);
}

// void CIecCfgGinCh::GetChFlagHcn(long &nFlag, long &nHcn)
// {
// 
// }
// 


// void CIecCfgGinCh::SetDataTypeByName(const CString &strName)
// {
// 	CIecGooseChDataTypeMngr *pDataTtypeMngr = CIecGlobalDataMngr::GetGooseDataTypeMngr();
// 	CDataType *pGooseChType = pDataTtypeMngr->m_pGooseChType;
// 	CDataTypeValue *pValue = NULL;
// 
// 	pValue = (CDataTypeValue *)pGooseChType->FindByName(strName);
// 
// 	if (pValue == NULL)
// 	{
// 		m_strDataType = g_strGooseChType_Single;
// 	}
// 	else
// 	{
// 		m_strDataType = pValue->m_strID;
// 	}
// 
// // 	m_strAppChID = _T("无");
// 	InitDataTypeName(TRUE);
// }

void CIecCfgGinCh::SetBinString(const CString &strBinID)
{
	m_strAppChID.Format(_T("%s;"),strBinID.GetString());
}

void CIecCfgGinCh::AddBinString(const CString &strBinID)
{
	if ((strBinID == g_strAppChID_None))
	{
		m_strAppChID = g_strAppChID_None;
		return;
	}

	if (m_strAppChID == g_strAppChID_None)
	{
		m_strAppChID.Format(_T("%s;"),strBinID.GetString());
		return;
	}

	CString strTemp;
	strTemp.Format(_T("%s;"),strBinID.GetString());

	if (m_strAppChID.Find(strTemp) >= 0)
	{
		return;
	}

	if (m_strAppChID.GetLength() == 0)
	{
		m_strAppChID = strTemp;
		return;
	}

	if (m_strAppChID.Find(g_strAppChID_None) >= 0)
	{
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("m_strAppChID=%s错误,不应包含%s."),m_strAppChID.GetString(),g_strAppChID_None.GetString());
		m_strAppChID = strTemp;
	}
	else
	{
		if (m_strAppChID.Right(1) == _T(";"))
		{
			m_strAppChID += strTemp;
		}
		else
		{
            m_strAppChID.AppendFormat(_T(";%s"), strTemp.GetString());
		}
	}
}

void CIecCfgGinCh::RemoveBinString(const CString &strBinID)
{
	CString strTmp;
	strTmp.Format(_T("%s;"),strBinID.GetString());//固定先增加分隔符
	long nIndex = m_strAppChID.Find(strTmp);

	if (nIndex == -1)//如果查找失败
	{
		nIndex = m_strAppChID.ReverseFind(';');//先反向查找分割符,找到最后一个映射

		if (nIndex == -1)//如果未找到,说明只有一个映射
		{
			if (m_strAppChID == strBinID)//如果相同,直接去除
			{
				m_strAppChID = g_strAppChID_None;
			} 
		} 
		else
		{
			strTmp = m_strAppChID.Mid(nIndex+1);//查找成功,先取出最后一个映射

			if (strTmp == strBinID)//如果最后一个映射与当前相同
			{
				strTmp = m_strAppChID.Left(nIndex);
				m_strAppChID = strTmp;
			}
		}
	} 
	else//查找成功,直接替换
	{
		m_strAppChID.Replace(strTmp, _T(""));
	}
	

	if (m_strAppChID.GetLength() > 3)
	{
		m_strAppChID.Replace(_T(";;"), _T(";"));
	}
	else
	{
		m_strAppChID = g_strAppChID_None;
	}

// 	if (m_strAppChID.GetLength() == 0)
// 	{
// 		m_strAppChID = g_strAppChID_None;
// 	}
}

void CIecCfgGinCh::InitDataTypeName(BOOL bInitBin)
{
	CDataType *pGooseChType = CCfgDataMngrConstGlobal::FindIecRtdDataType(iecfg_GooseChDataType);
	CDataTypeValue *pValue = NULL;

	if (pGooseChType == NULL)
	{
		m_strAppChID = g_strAppChID_None;//_T("0");
		m_strDataTypeName = _T("0");
		return;
	}

	pValue = (CDataTypeValue *)pGooseChType->FindByID(m_strDataType);

	if (pValue == NULL)
	{
		m_strDataTypeName = _T("0");
	}
	else
	{
		m_strDataTypeName = pValue->m_strName;
	}

	if (!bInitBin)
	{
		return;
	}

	if (m_strDataType == g_strGooseChType_Single) //       = _T("single");
	{
		m_strAppChID = g_strAppChID_None;//_T("0");
	}
	else if (m_strDataType == g_strGooseChType_Double) //       = _T("double");
	{
		m_strAppChID = g_strAppChID_None;
	}
	else if (m_strDataType == g_strGooseChType_Time) //         = _T("time");
	{
		m_strAppChID = _T("0");
	}
	else if (m_strDataType == g_strGooseChType_Quality) //      = _T("quality");
	{
		m_strAppChID = _T("0");
	}
	else if (m_strDataType == g_strGooseChType_Integer) //      = _T("integer");
	{
		m_strAppChID = _T("0");
	}
	else if (m_strDataType == g_strGooseChType_Float) //        = _T("float");
	{
		m_strAppChID = _T("0.0");
	}
	else if (m_strDataType == g_strGooseChType_String) //       = _T("string");
	{
		m_strAppChID = _T("0");
	}
	else if (m_strDataType == g_strGooseChType_Struct) //       = _T("struct");
	{
		m_strAppChID = _T("0");
	}
	else
	{
		m_strAppChID = _T("0");
	}
}

void CIecCfgGinCh::InitAppIDText()
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(iecfg_GinAppChDataType);
	ASSERT (pDataType != NULL);
	m_strAppChIDText.Empty();

	if (pDataType == NULL)
	{
#ifdef NOT_USE_XLANGUAGE
        m_strAppChIDText = _T("无");
#else
        m_strAppChIDText = g_sLangTxt_None/*_T("无")*/;
#endif
		return;
	}

	CStringTokenizer oToken;
	oToken.Init(m_strAppChID, ';');
	const char *pBinID = NULL;
	long nIndex = 0;
	DWORD dwBinValue = 0;
	CString strBinID;
	CDataTypeValue *pValue = NULL;
	CExBaseList oListValues;

	while (oToken.HasMoreElements())
	{
		pBinID = oToken.NextToken();
		strBinID = pBinID;
		pValue = (CDataTypeValue *)pDataType->FindByID(strBinID);

		//20231016 huangliang 后面程序的检测步骤需要使用带“;”的
		if(pValue == NULL)
		{
			strBinID += ";";
			pValue = (CDataTypeValue *)pDataType->FindByID(strBinID);
		}

		if (pValue != NULL)
		{
			oListValues.AddTail(pValue);
		}
	}

	if (oListValues.GetCount() == 0)
	{
#ifdef NOT_USE_XLANGUAGE
        m_strAppChIDText = _T("无");
#else
        m_strAppChIDText = g_sLangTxt_None/*_T("无")*/;
#endif
	}
	else
	{

	}

	POS pos = pDataType->GetHeadPosition();

	while (pos != NULL)
	{
		pValue = (CDataTypeValue *)pDataType->GetNext(pos);

		if (oListValues.Find(pValue) != NULL)
		{
            m_strAppChIDText.AppendFormat(_T("%s;"), pValue->m_strName.GetString());
		}
	}
	oListValues.RemoveAll();

	if (m_strAppChIDText.Right(1) == _T(";"))
	{
		m_strAppChIDText = m_strAppChIDText.Left(m_strAppChIDText.GetLength()-1);
	}
}

int CIecCfgGinCh::GetChPos()
{
	if (m_strDataType == _T("BOOLEAN"))
	{
		m_nPos = 0;
	}
	else if (m_strDataType == _T("Dbpos"))
	{
		m_nPos = 2;
	}

	return m_nPos;
}

void CIecCfgGinCh::CopyToGoutCh(CIecCfgDataGooseChBase *pGoutCh)
{
	CIecCfgDataGooseChBase::CopyOwn(pGoutCh);
}
BOOL CIecCfgGinCh::IsDefaultValue()
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
void CIecCfgGinCh::CheckDefautValue()
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
void CIecCfgGinCh::CheckDefautValue_ChTypeSingle()
{

}
void CIecCfgGinCh::CheckDefautValue_ChTypeDouble()
{
	if ((m_strDefaultValue != _T("[00]"))&&(m_strDefaultValue != _T("[01]"))&&
		(m_strDefaultValue != _T("[10]"))&&(m_strDefaultValue != _T("[11]")))
	{
		m_strDefaultValue = _T("[01]");
	}
}
void CIecCfgGinCh::CheckDefautValue_ChTypeQuality()
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
}

void CIecCfgGinCh::CheckDefautValue_ChTypeFloat()
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

void CIecCfgGinCh::CheckDefautValue_ChTypeString()
{
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

void CIecCfgGinCh::CheckDefautValue_ChTypeInteger()
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

void CIecCfgGinCh::CheckDefautValue_ChTypeUInteger()
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