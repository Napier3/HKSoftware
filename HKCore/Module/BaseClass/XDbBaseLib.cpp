#include "stdafx.h"
#include "XDbBaseLib.h"
#include "ExBaseObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXDb_PKeyValue::CXDb_PKeyValue()
{
	pRootObj = NULL;
	nType = _SQL_VT_NONE;
	oKeyValRef.pn64Value = NULL;
}

CXDb_PKeyValue::CXDb_PKeyValue(CExBaseObject *pObj, CXmlRWKeys *pXmlRWKeys)
{
	pRootObj = pObj;
	bstrPkey = pObj->DB_GetPrimaryKey(pXmlRWKeys);
	nClassID = pObj->GetClassID();
	pObj->Db_GetPkeyValue(*this);
}


void CXDb_PKeyValue::SetValue(long *pnValue)
{
	nType = _SQL_VT_LONG;
	oKeyValRef.pnValue = pnValue;
}

void CXDb_PKeyValue::SetValue(__int64 *pn64Value)
{
	nType = _SQL_VT_INT64;
	oKeyValRef.pn64Value = pn64Value;
}

void CXDb_PKeyValue::SetValue(CString *pstrValue)
{
	nType = _SQL_VT_STR;
	oKeyValRef.pstrValue = pstrValue;
}

void CXDb_PKeyValue::GetValue(CString &strValue)
{
	if (nType == _SQL_VT_STR)
	{
		strValue = *oKeyValRef.pstrValue;
	}
	else if (nType == _SQL_VT_LONG)
	{
		strValue.Format(_T("%d"), *oKeyValRef.pnValue);
	}
	else if (nType == _SQL_VT_INT64)
	{
		strValue.Format(_T("%I64u"), *oKeyValRef.pn64Value);
	}
	else
	{
		ASSERT(FALSE);
		strValue.Empty();
	}
}

BOOL CXDb_PKeyValue::operator==(long &nValue)
{
	if (nType != _SQL_VT_LONG)
	{
		return FALSE;
	}

	return *oKeyValRef.pnValue == nValue;
}

BOOL CXDb_PKeyValue::operator==(__int64 &n64Value)
{
	if (nType != _SQL_VT_INT64)
	{
		return FALSE;
	}

	return *oKeyValRef.pn64Value == n64Value;
}

BOOL CXDb_PKeyValue::operator==(const CString &strValue)
{
	if (nType != _SQL_VT_STR)
	{
		return FALSE;
	}

	return *oKeyValRef.pstrValue == strValue;
}

BOOL CXDb_PKeyValue::operator==(const CXDb_PKeyValue &oValue)
{
	if (nType != oValue.nType)
	{
		return FALSE;
	}

	switch (nType)
	{
	case _SQL_VT_LONG:
	case _SQL_VT_DWORD:
		return *oKeyValRef.pnValue == *oValue.oKeyValRef.pnValue;

	case _SQL_VT_INT64:
		return *oKeyValRef.pn64Value == *oValue.oKeyValRef.pn64Value;

	case _SQL_VT_STR:
		return *oKeyValRef.pstrValue == *oValue.oKeyValRef.pstrValue;

	default:
		return FALSE;
	}
	
	return FALSE;
}

void CXDb_PKeyValue::SetValue(long nValue)
{
	switch (nType)
	{
	case _SQL_VT_LONG:
	case _SQL_VT_DWORD:
		*oKeyValRef.pnValue = nValue;
		break;	

	case _SQL_VT_INT64:
		*oKeyValRef.pn64Value = nValue;
		break;	

	case _SQL_VT_STR:
		(*oKeyValRef.pstrValue).Format(_T("%d"),nValue);
		break;	

	default:
		break;		
	}
}

void CXDb_PKeyValue::SetValue(__int64 n64Value)
{
	switch (nType)
	{
	case _SQL_VT_LONG:
	case _SQL_VT_DWORD:
		*oKeyValRef.pnValue = (long)n64Value;
		break;	

	case _SQL_VT_INT64:
		*oKeyValRef.pn64Value = n64Value;
		break;	

	case _SQL_VT_STR:
		(*oKeyValRef.pstrValue).Format(_T("%lld"),n64Value);
		break;	

	default:
		break;		
	}
}

void CXDb_PKeyValue::SetValue(const CString &strValue)
{
	switch (nType)
	{
	case _SQL_VT_LONG:
	case _SQL_VT_DWORD:
		*oKeyValRef.pnValue = CString_To_long(strValue);
		break;	

	case _SQL_VT_INT64:
		*oKeyValRef.pn64Value = CString_To_i64(strValue);
		break;	

	case _SQL_VT_STR:
		*oKeyValRef.pstrValue = strValue;
		break;	

	default:
		break;
	}
}

void CXDb_PKeyValue::SetValue(const CXDb_PKeyValue &oSrcKeyVal)
{
	ASSERT (oSrcKeyVal.nType == nType);

	if (oSrcKeyVal.nType != nType)
	{
		return;
	}

	switch (nType)
	{
	case _SQL_VT_LONG:
	case _SQL_VT_DWORD:
		*oKeyValRef.pnValue = *oSrcKeyVal.oKeyValRef.pnValue;
		break;	

	case _SQL_VT_INT64:
		*oKeyValRef.pn64Value = *oSrcKeyVal.oKeyValRef.pn64Value;
		break;	

	case _SQL_VT_STR:
		*oKeyValRef.pstrValue = *oSrcKeyVal.oKeyValRef.pstrValue;
		break;	

	default:
		break;
	}
}

char* CXDbRecordsetBase::Item(long nColIndex, long &nDataLen) {return NULL;}
char* CXDbRecordsetBase::Item(const CString &strID, long &nDataLen) {return NULL;}

CString CXDbRecordsetBase::GetFieldName(long index)	{	return _T("");	}

BOOL CXDbBaseLib::InitMySqlDB(CDBServerInfoBase &oServerInfo){	return false;	}
BOOL CXDbBaseLib::ConnectDB(CDBServerInfoBase &oServerInfo)		{	return false;	}   //连接数据库

CXDbRecordsetBase* CXDbBaseLib::SQLNewRecordset(const CString &strTable, const CString &strPrimaryKey, const CString &strPrimaryKeyValue)
{
	return NULL;
}
CXDbRecordsetBase* CXDbBaseLib::SQLSelect(const CString &strTable, const CString &strPrimaryKey, const CString &strPrimaryKeyValue)
{
	CString stSQL;
	GetSQLSelect(stSQL, strTable, strPrimaryKey, strPrimaryKeyValue);

	return ExecuteQuery(stSQL);
}

BOOL CXDbBaseLib::SQLDelete(const CString &strTable, const CString &strPrimaryKey, const CString &strPrimaryKeyValue)
{
	CString stSQL;
	GetSQLDelete(stSQL, strTable, strPrimaryKey, strPrimaryKeyValue);

	return ExecuteCmd(stSQL);
}

//////////////////////////////////////////////////////////////////////////
#ifdef _DBLIB_USE_SHAREMEM_
CShareMemSerialize* CXDbRecordsetBase::GetShareMemSerialize()
{
	CXDbBaseLib *pXDbLib = GetXDbBaseLib();
	return pXDbLib->GetShareMemSerialize();
}

CShareMemSerialize* CXDbBaseLib::CreateShareMemSerialize(const CString &strMapFileName, DWORD dwLen)
{
	if (m_pShareMemSerialize_SingleRW == NULL)
	{
		m_pShareMemSerialize_SingleRW = new CShareMemSerialize();
	}

	if (dwLen < 64)
	{
		dwLen = 64;
	}

	if (dwLen > m_dwLen_SmSerialize_SingleRW)
	{
		CString strFileName;
		strFileName = _P_GetDBPath();

		if (strMapFileName.GetLength() == 0)
		{
			strFileName += _T("XdbRWMem.xdbm");
		}
		else
		{
			strFileName += strMapFileName;
		}

		m_dwLen_SmSerialize_SingleRW = dwLen;
		m_pShareMemSerialize_SingleRW->CreateFileEx(strFileName, m_dwLen_SmSerialize_SingleRW);
	}

	return m_pShareMemSerialize_SingleRW;
	
}

void CXDbBaseLib::FreeShareMemSerialize()
{
	m_pShareMemSerialize_SingleRW->SerializeFree();
	delete m_pShareMemSerialize_SingleRW;
	m_pShareMemSerialize_SingleRW = NULL;
}
#endif


BOOL mysql_IsFieldNameAutoPKey(const CString &strFieldName)
{
	CString strTemp = strFieldName;
	strTemp.MakeLower();

	//北京团队使用VC++编译QT工程，这个部分的代码会出错
	if (strTemp.Find(_T("idx_")) >= 0)
	{
		return TRUE;
	}

	if (strTemp.Find(_T("index_")) >= 0)
	{
		return TRUE;
	}
	return FALSE;
}
