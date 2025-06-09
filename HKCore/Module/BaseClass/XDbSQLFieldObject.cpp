#include "stdafx.h"
#include "XDbSQLFieldObject.h"
#include "XDbBaseLib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//2018-10-7  lijq  使用ASCII的编译模式
//字符串的转换函数，StringApi.h都已经有了
char *SQL_String_To_Char(const CString &strTrans)
{
	char *pRet = NULL;
	CString_to_char(strTrans, &pRet);
	return pRet;
// 	int len = WideCharToMultiByte(CP_ACP,0,strTrans,-1,NULL,0,NULL,NULL);
// 	char * pTrans = new char[len+1];   //以字节为单位
// 	memset(pTrans,0,len+1);
// 	WideCharToMultiByte(CP_ACP,0,strTrans,-1,pTrans,len,NULL,NULL);
// 	pTrans[len] = 0; 
// 	return pTrans;
}

BOOL SQL_Val_To_String(CXDbSQLFieldObject *pObj, CString &strVal)
{
	ASSERT(pObj);

	//拼字段值
	switch(pObj->m_nValType)
	{
	case _SQL_VT_LONG:
		{
			strVal.Format(_T("\"%d\""),pObj->oMySQLValue.nValue);
			break;
		}
	case _SQL_VT_DWORD:
		{
			strVal.Format(_T("\"%d\""),pObj->oMySQLValue.dwValue);
			break;
		}
	case _SQL_VT_INT64:
		{
			strVal.Format(_T("\"%d\""),pObj->oMySQLValue.n64Value);
			break;
		}
	case _SQL_VT_FLOAT:
		{
			strVal.Format(_T("\"%.3f\""),pObj->oMySQLValue.fValue);
			break;
		}
	case _SQL_VT_DOUBLE:
		{
			strVal.Format(_T("\"%.3f\""),pObj->oMySQLValue.dfValue);
			break;
		}
	case _SQL_VT_STR:
		{
			strVal.Format(_T("\"%s\""),pObj->oMySQLValue.pString);
			break;
		}
	case _SQL_VT_TIME:
		{
			SystemTime_To_String(pObj->oMySQLValue.tmValue,strVal);
            strVal.Format(_T("\"%s\""),strVal.GetString());
			break;
		}
	default:
		return FALSE;
	}

	return TRUE;
}


CXDbSQLFieldObject::CXDbSQLFieldObject()
{
	m_nValType = 0;
}
CXDbSQLFieldObject::CXDbSQLFieldObject(const CString &strID, long nValue)
{
	m_strID = strID;
	SetValue(nValue);
}

CXDbSQLFieldObject::CXDbSQLFieldObject(const CString &strID, DWORD dwValue)
{
	m_strID = strID;
	SetValue(dwValue);
}

CXDbSQLFieldObject::CXDbSQLFieldObject(const CString &strID, __int64 n64Value)
{
	m_strID = strID;
	SetValue(n64Value);
}

CXDbSQLFieldObject::CXDbSQLFieldObject(const CString &strID, float fValue)
{
	m_strID = strID;
	SetValue(fValue);
}

CXDbSQLFieldObject::CXDbSQLFieldObject(const CString &strID, double dfValue)
{
	m_strID = strID;
	SetValue(dfValue);
}

CXDbSQLFieldObject::CXDbSQLFieldObject(const CString &strID, const CString &strValue)
{
	m_strID = strID;
	SetValue(strValue);
}

CXDbSQLFieldObject::CXDbSQLFieldObject(const CString &strID, long nLen, char *pBlob)
{
	m_strID = strID;
	SetValue(nLen,pBlob);
}

CXDbSQLFieldObject::CXDbSQLFieldObject(const CString &strID, SYSTEMTIME tmValue)
{
	m_strID = strID;
	SetValue(tmValue);
}

CXDbSQLFieldObject::~CXDbSQLFieldObject()
{
	switch(m_nValType)
	{
	case _SQL_VT_STR:
		{
//			delete oMySQLValue.pString;
			oMySQLValue.pString = NULL;
			break;
		}
	case _SQL_VT_BLOB:
		{
#ifndef _DBLIB_USE_SHAREMEM_
			if (oMySQLValue.oBlob.nLen)
			{
				delete oMySQLValue.oBlob.pBuffer;
			}			
#endif

			oMySQLValue.oBlob.pBuffer = NULL;
			oMySQLValue.oBlob.nLen = 0;
			break;
		}
	}

	m_nValType = 0;
}

void CXDbSQLFieldObject::SetValue(long nValue)
{
	m_nValType = _SQL_VT_LONG;
	oMySQLValue.nValue = nValue;
}

void CXDbSQLFieldObject::SetValue(DWORD dwValue)
{
	m_nValType = _SQL_VT_DWORD;
	oMySQLValue.dwValue = dwValue;
}

void CXDbSQLFieldObject::SetValue(__int64 n64Value)
{
	m_nValType = _SQL_VT_INT64;
	oMySQLValue.n64Value = n64Value;
}	

void CXDbSQLFieldObject::SetValue(float fValue)
{
	m_nValType = _SQL_VT_FLOAT;
	oMySQLValue.fValue = fValue;
}

void CXDbSQLFieldObject::SetValue(double dfValue)
{
	m_nValType = _SQL_VT_DOUBLE;
	oMySQLValue.dfValue = dfValue;
}

void CXDbSQLFieldObject::SetValue(const CString &strValue)
{
	m_nValType = _SQL_VT_STR;
	oMySQLValue.pString = (CString*)(&strValue);
	//CString_to_char(strValue, &oMySQLValue.pString);
	//oMySQLValue.pString = My_String_To_Char(strValue);
}

void CXDbSQLFieldObject::SetValue(long nLen, char *pBlob)
{
	m_nValType = _SQL_VT_BLOB;
	oMySQLValue.oBlob.pBuffer = pBlob;
	oMySQLValue.oBlob.nLen = nLen;
}

void CXDbSQLFieldObject::SetValue(SYSTEMTIME tmValue)
{
	m_nValType = _SQL_VT_TIME;
	oMySQLValue.tmValue = tmValue;
}

long CXDbSQLFieldObject::GetValueLength()
{
	long nSize = 0;
	switch (m_nValType)
	{
	case _SQL_VT_LONG:
		nSize = sizeof(long);
		break;
	case _SQL_VT_DWORD:
		nSize = sizeof(DWORD);
		break;
	case _SQL_VT_INT64:
		nSize = sizeof(__int64);
		break;
	case _SQL_VT_FLOAT:
		nSize = sizeof(float);
		break;
	case _SQL_VT_DOUBLE:
		nSize = sizeof(double);
		break;
	case _SQL_VT_STR:
		//20201116 xxy:计算添加转义符之后的长度
		nSize = Sql_GetMySqlStringLen(*oMySQLValue.pString);
		//nSize = String_Char_Count(*oMySQLValue.pString);
		break;
	case _SQL_VT_BLOB:
		//20201116 xxy:计算添加转义符之后的长度
		nSize = Sql_GetMySqlStringLen(oMySQLValue.oBlob.pBuffer, oMySQLValue.oBlob.nLen);
		//nSize = oMySQLValue.oBlob.nLen;
		break;
	case _SQL_VT_TIME:
		nSize = sizeof(SYSTEMTIME);
		break;
	}

	return nSize;
}

BOOL CXDbSQLFieldObject::FieldValSerialize(CStringSerializeBufferAscii &oStrBuf)
{
	long nSize = 0;
	switch (m_nValType)
	{
	case _SQL_VT_LONG:
		oStrBuf << oMySQLValue.nValue;
		break;
	case _SQL_VT_DWORD:
		oStrBuf << oMySQLValue.dwValue;
		break;
	case _SQL_VT_INT64:
		oStrBuf << oMySQLValue.n64Value;
		break;
	case _SQL_VT_FLOAT:
		oStrBuf << oMySQLValue.fValue;
		break;
	case _SQL_VT_DOUBLE:
		oStrBuf << oMySQLValue.dfValue;
		break;
	case _SQL_VT_STR:
		oStrBuf << "\"";
		//处理转义字符
		oStrBuf.Append_String(*oMySQLValue.pString);
		oStrBuf << "\"";
		break;
	case _SQL_VT_BLOB:
		oStrBuf << "\"";
		//处理转义字符
		oStrBuf.Append_MySql(oMySQLValue.oBlob.pBuffer, oMySQLValue.oBlob.nLen);
		oStrBuf << "\"";		
		break;
	case _SQL_VT_TIME:
		oStrBuf << "\"";
		oStrBuf << oMySQLValue.tmValue;
		oStrBuf << "\"";
		break;
	default:
		return FALSE;
	}

	return TRUE;
}

BOOL CXDbSQLFieldObject::IsValueEmpty()
{
	switch (m_nValType)
	{
	case _SQL_VT_LONG:
		return (oMySQLValue.nValue == 0);
	
	case _SQL_VT_DWORD:
		return (oMySQLValue.dwValue == 0);
		
	case _SQL_VT_INT64:
		return (oMySQLValue.n64Value == 0);

	default:
		return FALSE;
	}

	return FALSE;
}

//////////////////////////////////////////////////////////

void CXDbSQLFieldObjects::XDB_AddNewChild(const CString &strID)
{
	CXDbSQLFieldObject *pNew = new CXDbSQLFieldObject(strID,(long)0);
	AddNewChild(pNew);
}

void CXDbSQLFieldObjects::XDB_AddNewChild(BSTR bstrID)
{
    CString strID;
    strID = bstrID;
    XDB_AddNewChild(strID);
}

void CXDbSQLFieldObjects::GetSelectSql(CString &strSql,CString strFilter)
{
	ASSERT( !m_strID.IsEmpty());

	POS pos = GetHeadPosition();
	CXDbSQLFieldObject *p = NULL;
	CString strSelectKey = _T("");

	while(pos != NULL)
	{
		p = (CXDbSQLFieldObject *)GetNext(pos);
		
		if (pos != NULL)
		{//不是最后一个
            strSelectKey.AppendFormat(_T("%s,"),p->m_strID.GetString());
		}
		else
		{
            strSelectKey.AppendFormat(_T("%s"),p->m_strID.GetString());
		}
	}

	if (strSelectKey.IsEmpty())
	{
		strSelectKey = _T("*");
	}

    strSql.Format(_T("select %s from %s"),strSelectKey.GetString(),m_strID.GetString());

	if (!strFilter.IsEmpty())
	{
        strSql.AppendFormat(_T(" where %s"),strFilter.GetString());
	}
}

/////////////////////////////////////////////////////

void AdjustFieldString(CString *pString)
{
	pString->Replace(_T("\\"),_T("\\\\"));
}

//数据库时间过滤
 void GetDuringDateString(const SYSTEMTIME &tmBegin,const SYSTEMTIME &tmEnd,const CString &strTmKey, CString &strFilter)
{
	strFilter.Format(_T("(%s >= \"%d-%d-%d\" and %s <= \"%d-%d-%d\")")
        ,strTmKey.GetString(),tmBegin.wYear,tmBegin.wMonth,tmBegin.wDay
        ,strTmKey.GetString(),tmEnd.wYear,tmEnd.wMonth,tmEnd.wDay);
}

void GetDuringDateString(const CString &strTmBegin,const CString &strTmEnd,const CString &strTmKey, CString &strFilter)
{
	strFilter = _T("");

	if ((!strTmBegin.IsEmpty()) && (!strTmEnd.IsEmpty()))
	{
		SYSTEMTIME tmBegin,tmEnd;
		CString_To_SystemTime(strTmBegin, tmBegin);
		CString_To_SystemTime(strTmEnd, tmEnd);

		//时间过滤
		GetDuringDateString(tmBegin,tmEnd,strTmKey,strFilter);
	}
}

void MergeFilterString(const CString &strSrc,CString &strDest)
{
	if (strDest.IsEmpty())
	{
		strDest = strSrc;
	}
    else
    {
        if (strSrc.IsEmpty())
        {

        }
        else
        {
            strDest = strDest + _T(" and ") + strSrc;
        }
    }
}

int FindFilterArrByValue(CUIntArray &FilterArr,UINT nValue)
{
	int nCount = FilterArr.GetSize();
	int nFind = -1;

	for (int i=0; i < nCount; i++)
	{
		if (FilterArr[i] == nValue)
		{
			nFind = i;
			break;
		}
	}
	return nFind;
}

void MergeFilterArr(CUIntArray &FilterArr_src,CUIntArray &FilterArr_dst)
{
	int nCount = FilterArr_src.GetSize();
	int nFind = -1;

	for (int i=0; i < nCount; i++)
	{
		nFind = FindFilterArrByValue(FilterArr_dst,FilterArr_src[i]);
		if (nFind < 0)
		{
			FilterArr_dst.Add(FilterArr_src[i]);
		}
	}
}

CString GenerateFilterArrSql(CUIntArray &FilterArr)
{
	CString strFilter = _T("(");
	int nCount = FilterArr.GetSize();
	if (nCount <= 0)
	{
		return _T("");
	}

	CString tmpStr = _T("");

	for (int i=0; i < nCount; i++)
	{
		if (i < nCount-1)
		{
			tmpStr.Format(_T("%d,"),FilterArr[i]);
		}
		else
		{
			tmpStr.Format(_T("%d)"),FilterArr[i]);
		}

		strFilter = strFilter + tmpStr;
	}

	return strFilter;
}

void GenerateFilterArr(CExBaseList *pList,CUIntArray &FilterArr)
{
	ASSERT( pList != NULL );

	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	int nFind = -1;
	CXDb_PKeyValue oPKeyValue;
	long nIndex=0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);

		p->Db_GetPkeyValue(oPKeyValue);
		nIndex = *oPKeyValue.oKeyValRef.pnValue;

		nFind = FindFilterArrByValue(FilterArr,nIndex);
		if (nFind < 0)
		{
			FilterArr.Add(nIndex);
		}
	}
}

void GenerateFilterArrSql(CExBaseList *pList,CString &strArrFilter)
{
	ASSERT( pList != NULL );

	CUIntArray oFilterArr;
	GenerateFilterArr(pList,oFilterArr);

	strArrFilter = GenerateFilterArrSql(oFilterArr);
}

void GenerateFilterArrSql(CUIntArray &FilterArr,const CString &strKey,CString &strFilter)
{
	ASSERT(!strKey.IsEmpty());

	CString strArrFilter;
	strFilter = _T("");

	strArrFilter = GenerateFilterArrSql(FilterArr);

	if (!strArrFilter.IsEmpty())
	{
        strFilter.Format(_T("%s in %s"),strKey.GetString(),strArrFilter.GetString());
	}
}

//添加转义字符后字符串长度
long Sql_GetMySqlStringLen(char *pszData,long nLen)
{
	char *pSrc = pszData;
	char *pEnd = pszData + nLen;
	long nAddLen = 0;

	while (pSrc < pEnd)
	{
		if ((*pSrc == 0x22) || (*pSrc == 0x5c)
			|| (*pSrc == 0x27))
		{
			nAddLen++;
		}
		pSrc++;
	}

	return (nLen + nAddLen);
}

long Sql_GetMySqlStringLen(const CString &strData)
{
	char *pBuffer = NULL;
	long nLen = 0;
	nLen = CString_to_char(strData, &pBuffer);

	long nRet = Sql_GetMySqlStringLen(pBuffer,nLen);
	delete pBuffer;

	return nRet;
}