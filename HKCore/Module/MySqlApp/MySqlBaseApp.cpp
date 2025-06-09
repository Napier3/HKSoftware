// MySqlBaseApp.cpp: implementation of the CMySqlBaseApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySqlBaseApp.h"
#include "..\MemBuffer\StringToSystimeBuffer.h"

#include "..\..\module\system\tickcount32.h"
#include "..\..\Module\mysql\include\errmsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



CMySqlBaseApp *g_pTheMySqlApp = NULL;

////////////////CMySqlRecordset///////////////////////////

CMySqlRecordset::CMySqlRecordset(void)
:CXDbRecordsetBase()
{
	m_pMySqlBaseApp = NULL;
	m_pRecordsets = NULL;
	m_pMySqlRow = NULL;
	m_pFields = NULL;
	m_ArrColLens = NULL;

	m_CurRowPos = NULL;
	m_BeginRowPos = NULL;

	m_nCols = 0;
	m_nRows = 0;

	m_pPKObj = NULL;
	m_bPKAutoIncreaceFlg = TRUE;

#ifdef _DBLIB_USE_SHAREMEM_

#else
	m_pStrBufValue = new CStringSerializeBufferAscii();
#endif
}

CMySqlRecordset::CMySqlRecordset(CMySqlBaseApp *pBaseApp, MYSQL_RES *pRecordsets)
:CXDbRecordsetBase()
{
#ifdef _DBLIB_USE_SHAREMEM_
	m_pStrBufValue = NULL;
#else
	m_pStrBufValue = new CStringSerializeBufferAscii();
#endif
	
	InitRecordset(pBaseApp, pRecordsets);
}

CMySqlRecordset::~CMySqlRecordset()
{
#ifdef _DBLIB_USE_SHAREMEM_

#else
	delete m_pStrBufValue;
	m_pStrBufValue = NULL;
#endif
}

CXDbBaseLib* CMySqlRecordset::GetXDbBaseLib()
{
	return m_pMySqlBaseApp;
}

BOOL CMySqlRecordset::InitRecordset(CMySqlBaseApp *pBaseApp, MYSQL_RES *pRecordsets)
{
	m_pMySqlBaseApp = pBaseApp;
	m_pRecordsets = pRecordsets;
	
	//当记录集为空，只能插入
	if ((!m_pRecordsets) || (mysql_num_rows(m_pRecordsets) <= 0))
	{
		m_pMySqlRow = NULL;
		m_ArrColLens = NULL;
		m_CurRowPos = NULL;
		m_BeginRowPos = NULL;
		m_nRows = 0;
		if (m_pRecordsets)
		{
			m_pFields = mysql_fetch_fields(m_pRecordsets);
			if (m_pFields)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("mysql_store_result:%s 返回为空"),m_pFields[0].table);
			}
			else
			{
				CLogPrint::LogString(XLOGLEVEL_INFOR, _T("mysql_store_result: 返回为空"));
			}
			
		}		
		return FALSE;
	} 

	m_CurRowPos = mysql_row_tell(m_pRecordsets);
	m_BeginRowPos = m_CurRowPos;

	m_pFields = mysql_fetch_fields(m_pRecordsets);
	m_pMySqlRow = mysql_fetch_row(m_pRecordsets);
	m_ArrColLens = mysql_fetch_lengths(m_pRecordsets);

	m_nCols = mysql_num_fields(m_pRecordsets); 
	m_nRows = mysql_num_rows(m_pRecordsets);

	return TRUE;
}

BOOL CMySqlRecordset::InitPrimaryState(CString &strPK)
{
	m_pPKObj = (CXDbSQLFieldObject *)FindByID(strPK);
	ASSERT(m_pPKObj);

	m_bPKAutoIncreaceFlg = mysql_IsFieldNameAutoPKey(strPK);

	return m_bPKAutoIncreaceFlg;
}

// 功能描述: 获取插入记录后的自动增长的主键
long CMySqlRecordset::GetInsertId(void)
{
	ASSERT(m_pMySqlBaseApp);
	return mysql_insert_id(&m_pMySqlBaseApp->m_Mysql);
}

long CMySqlRecordset::FindField(const CString &strID)
{
	long nFindIndex = -1;
#ifdef _UNICODE
	CString strName;
#endif
	
	for(long i=0; i<m_nCols; i++)
	{	
	#ifdef _UNICODE
		strName = m_pFields[i].name;
		if (wcsicmp( strName, strID) == 0)
	#else
		if (stricmp( m_pFields[i].name, strID) == 0)
	#endif
		{
			nFindIndex = i;
			break; 
		}
	}

	return nFindIndex;
}

char* CMySqlRecordset::Item(const CString &strID)
{
	if(!m_pRecordsets)
		return NULL;

	long int nIndex = FindField(strID);
	if(nIndex < 0)
	{
//		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("FindField 失败。"));
		return NULL;
	}

	return Item(nIndex);
}

BOOL CMySqlRecordset::GetFieldBaseValue(long nFieldIndex,char **pchVal)
{
	*pchVal = Item(nFieldIndex);
	if(!*pchVal)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMySqlRecordset::GetFieldBaseValue(const CString &strID,char **pchVal)
{
	*pchVal = Item(strID);
	if(!*pchVal)
	{
		return FALSE;
	}

	return TRUE;
}

//获取当前记录值
BOOL CMySqlRecordset::GetFieldValue(long nFieldIndex, CString &strValue)
{
	char *pchVal = NULL;

	if (!GetFieldBaseValue(nFieldIndex, &pchVal))
	{
		return FALSE;
	}
	strValue = pchVal;
//	strValue = CharToString(pchVal);
	return TRUE;
}

BOOL CMySqlRecordset::GetFieldValue(long nFieldIndex, long &nValue)
{
	CString strValue;
	if (!GetFieldValue(nFieldIndex, strValue))
	{
		return FALSE;
	}

	nValue = CString_To_long(strValue);
	return TRUE;
}

BOOL CMySqlRecordset::GetFieldValue(long nFieldIndex, double &fValue)
{
	CString strValue;
	if (!GetFieldValue(nFieldIndex, strValue))
	{
		return FALSE;
	}

	fValue = CString_To_double(strValue);
	return TRUE;
}

BOOL CMySqlRecordset::GetFieldValue(long nFieldIndex, float &fValue)
{
	CString strValue;
	if (!GetFieldValue(nFieldIndex, strValue))
	{
		return FALSE;
	}

	fValue = (float)CString_To_double(strValue);
	return TRUE;
}

BOOL CMySqlRecordset::GetFieldValue(long nFieldIndex, DWORD &dwValue)
{
	CString strValue;
	if (!GetFieldValue(nFieldIndex, strValue))
	{
		return FALSE;
	}

	dwValue = (DWORD)CString_To_ulong(strValue);
	return TRUE;
}

BOOL CMySqlRecordset::GetFieldValue(long nFieldIndex, __int64 &n64Value)
{
	CString strValue;
	if (!GetFieldValue(nFieldIndex, strValue))
	{
		return FALSE;
	}

	n64Value = CString_To_i64(strValue);
	return TRUE;
}

BOOL CMySqlRecordset::GetFieldValue(long nFieldIndex, SYSTEMTIME &tmValue)
{
	char *pchVal = Item(nFieldIndex);
	if(!pchVal)
	{
		return FALSE;
	}

	CString strTime;
	strTime = pchVal;

	CStringToSystimeBuffer oBuffer;
	oBuffer.CString_To_SystemTime(strTime, tmValue);

	return TRUE;
	//return CString_To_SystemTime_Ex(strTime,tmValue);
}

BOOL CMySqlRecordset::GetFieldValue(long nFieldIndex, char **blobData, long &nLen)
{
	*blobData = Item(nFieldIndex);
	if(!(*blobData))
	{
		return FALSE;
	} 
	nLen = nCurFieldDataLen;
	return TRUE;
}

BOOL CMySqlRecordset::GetFieldValue(const CString &strID, CString &strValue)
{
	char *pchVal = NULL;

	if (!GetFieldBaseValue(strID, &pchVal))
	{
		return FALSE;
	}

	if (m_pStrBufValue->GetEncoding() == XSTR_EncodingIdx_gb2312)
	{
		strValue = pchVal;
	}
	else
	{
		char *pBuffer = NULL;
		long nLen = strlen(pchVal);
		charUtf8_to_charGBK(pchVal, nLen, &pBuffer, nLen);
		strValue = pBuffer;
		delete pBuffer;
	}

	//strValue = pchVal;
//	strValue = CharToString(pchVal);
	return TRUE;
}

BOOL CMySqlRecordset::GetFieldValue(const CString &strID, long &nValue)
{
	CString strValue;
	if (!GetFieldValue(strID, strValue))
	{
		return FALSE;
	}

	nValue = CString_To_long(strValue);
	return TRUE;
}

BOOL CMySqlRecordset::GetFieldValue(const CString &strID, double &fValue)
{
	CString strValue;
	if (!GetFieldValue(strID, strValue))
	{
		return FALSE;
	}

	fValue = CString_To_double(strValue);
	return TRUE;
}

BOOL CMySqlRecordset::GetFieldValue(const CString &strID, float &fValue)
{
	CString strValue;
	if (!GetFieldValue(strID, strValue))
	{
		return FALSE;
	}

	fValue = (float)CString_To_double(strValue);
	return TRUE;	
}

BOOL CMySqlRecordset::GetFieldValue(const CString &strID, DWORD &dwValue)
{
	CString strValue;
	if (!GetFieldValue(strID, strValue))
	{
		return FALSE;
	}

	dwValue = (DWORD)CString_To_ulong(strValue);
	return TRUE;
}

BOOL CMySqlRecordset::GetFieldValue(const CString &strID, __int64 &n64Value)
{
	CString strValue;
	if (!GetFieldValue(strID, strValue))
	{
		return FALSE;
	}

	n64Value = CString_To_i64(strValue);
	return TRUE;
}

BOOL CMySqlRecordset::GetFieldValue(const CString &strID, SYSTEMTIME &tmValue)
{
	char *pchVal = Item(strID);
	if(!pchVal)
	{
		return FALSE;
	}

	CString strTime;
	strTime = pchVal;

	CStringToSystimeBuffer oBuffer;
	oBuffer.CString_To_SystemTime(strTime, tmValue);

	return TRUE;
	//return CString_To_SystemTime_Ex(strTime,tmValue);
}

BOOL CMySqlRecordset::GetFieldValue(const CString &strID, char **blobData, long &nLen)
{
	*blobData = Item(strID);
	if(!(*blobData))
	{
		return FALSE;
	}
	nLen = nCurFieldDataLen; 

	return TRUE;
}

BOOL CMySqlRecordset::GetFieldValue(BSTR strID, CString &strValue)
{
	return GetFieldValue((const CString)strID,strValue);
}

BOOL CMySqlRecordset::GetFieldValue(BSTR strID, long &nValue)
{
	return GetFieldValue((const CString)strID,nValue);
}

BOOL CMySqlRecordset::GetFieldValue(BSTR strID, double &fValue)
{
	return GetFieldValue((const CString)strID,fValue);
}

BOOL CMySqlRecordset::GetFieldValue(BSTR strID, float &fValue)
{
	return GetFieldValue((const CString)strID,fValue);
}

BOOL CMySqlRecordset::GetFieldValue(BSTR strID, DWORD &dwValue)
{
	return GetFieldValue((const CString)strID,dwValue);
}

BOOL CMySqlRecordset::GetFieldValue(BSTR strID, __int64 &n64Value)
{
	return GetFieldValue((const CString)strID,n64Value);
}

BOOL CMySqlRecordset::GetFieldValue(BSTR strID, SYSTEMTIME &tmValue)
{
	return GetFieldValue((const CString)strID,tmValue);
}

BOOL CMySqlRecordset::GetFieldValue(BSTR strID, char **blobData, long &nLen)
{
	return GetFieldValue((const CString)strID,blobData,nLen);
}

//设置当前记录值
void CMySqlRecordset::SetFieldValue(long nFieldIndex, const CString &strValue)
{

}

void CMySqlRecordset::SetFieldValue(long nFieldIndex, long &nValue)
{

}

void CMySqlRecordset::SetFieldValue(long nFieldIndex, double &fValue)
{

}

void CMySqlRecordset::SetFieldValue(long nFieldIndex, float &fValue)
{
	
}

void CMySqlRecordset::SetFieldValue(long nFieldIndex, DWORD &dwValue)
{

}

void CMySqlRecordset::SetFieldValue(long nFieldIndex, __int64 &n64Value)
{
	
}

void CMySqlRecordset::SetFieldValue(long nFieldIndex, SYSTEMTIME &tmValue)
{

}

void CMySqlRecordset::SetFieldValue(long nFieldIndex, char **blobData, long &nLen)
{

}

void CMySqlRecordset::SetFieldValue(const CString &strID, const CString &strValue)
{
	CXDbSQLFieldObject *pFind = (CXDbSQLFieldObject *)FindByID(strID);

	if (pFind == NULL)
	{
		pFind = new CXDbSQLFieldObject(strID, strValue);
		AddNewChild(pFind);
	}
	else
	{
		pFind->SetValue(strValue);
	}
}

void CMySqlRecordset::SetFieldValue(const CString &strID, long &nValue)
{
	CXDbSQLFieldObject *pFind = (CXDbSQLFieldObject *)FindByID(strID);

	if (pFind == NULL)
	{
		pFind = new CXDbSQLFieldObject(strID, nValue);
		AddNewChild(pFind);
	}
	else
	{
		pFind->SetValue(nValue);
	}
}

void CMySqlRecordset::SetFieldValue(const CString &strID, double &fValue)
{
	CXDbSQLFieldObject *pFind = (CXDbSQLFieldObject *)FindByID(strID);

	if (pFind == NULL)
	{
		pFind = new CXDbSQLFieldObject(strID, fValue);
		AddNewChild(pFind);
	}
	else
	{
		pFind->SetValue(fValue);
	}
}

void CMySqlRecordset::SetFieldValue(const CString &strID, float &fValue)
{
	CXDbSQLFieldObject *pFind = (CXDbSQLFieldObject *)FindByID(strID);

	if (pFind == NULL)
	{
		pFind = new CXDbSQLFieldObject(strID, fValue);
		AddNewChild(pFind);
	}
	else
	{
		pFind->SetValue(fValue);
	}
}

void CMySqlRecordset::SetFieldValue(const CString &strID, DWORD &dwValue)
{
	CXDbSQLFieldObject *pFind = (CXDbSQLFieldObject *)FindByID(strID);

	if (pFind == NULL)
	{
		pFind = new CXDbSQLFieldObject(strID, dwValue);
		AddNewChild(pFind);
	}
	else
	{
		pFind->SetValue(dwValue);
	}
}

void CMySqlRecordset::SetFieldValue(const CString &strID, __int64 &n64Value)
{
	CXDbSQLFieldObject *pFind = (CXDbSQLFieldObject *)FindByID(strID);

	if (pFind == NULL)
	{
		pFind = new CXDbSQLFieldObject(strID, n64Value);
		AddNewChild(pFind);
	}
	else
	{
		pFind->SetValue(n64Value);
	}
}

void CMySqlRecordset::SetFieldValue(const CString &strID, SYSTEMTIME &tmValue)
{
	CXDbSQLFieldObject *pFind = (CXDbSQLFieldObject *)FindByID(strID);

	if (pFind == NULL)
	{
		pFind = new CXDbSQLFieldObject(strID, tmValue);
		AddNewChild(pFind);
	}
	else
	{
		pFind->SetValue(tmValue);
	}
}

void CMySqlRecordset::SetFieldValue(const CString &strID, char **blobData, long &nLen)
{
	CXDbSQLFieldObject *pFind = (CXDbSQLFieldObject *)FindByID(strID);

	if (pFind == NULL)
	{
		pFind = new CXDbSQLFieldObject(strID, nLen, *blobData);
		AddNewChild(pFind);
	}
	else
	{
		pFind->SetValue(nLen, *blobData);
	}
}

void CMySqlRecordset::SetFieldValue(BSTR strID, const CString &strValue)
{
	//2018-10-7  lijq  使用ASCII的编译模式
	CString strTemp;
	strTemp = strID;
	SetFieldValue(strTemp, strValue);
}

void CMySqlRecordset::SetFieldValue(BSTR strID, long &nValue)
{
	SetFieldValue((const CString)strID, nValue);
}

void CMySqlRecordset::SetFieldValue(BSTR strID, double &fValue)
{
	SetFieldValue((const CString)strID, fValue);
}

void CMySqlRecordset::SetFieldValue(BSTR strID, float &fValue)
{
	SetFieldValue((const CString)strID, fValue);
}

void CMySqlRecordset::SetFieldValue(BSTR strID, DWORD &dwValue)
{
	SetFieldValue((const CString)strID, dwValue);
}

void CMySqlRecordset::SetFieldValue(BSTR strID, __int64 &n64Value)
{
	SetFieldValue((const CString)strID, n64Value);
}

void CMySqlRecordset::SetFieldValue(BSTR strID, SYSTEMTIME &tmValue)
{
	SetFieldValue((const CString)strID, tmValue);
}

void CMySqlRecordset::SetFieldValue(BSTR strID, char **blobData, long &nLen)
{
	SetFieldValue((const CString)strID, blobData, nLen);
}

// 获取查询结果的列数	
long CMySqlRecordset::GetQueryNumCols(void)	
{
	ASSERT(m_pRecordsets);
	return m_nCols;
}

// 获取查询结果的列数	
long CMySqlRecordset::GetQueryNumRows(void)	
{
	ASSERT(m_pRecordsets);
	return m_nRows;
}

// 释放查询结果空间
void CMySqlRecordset::Free(void)
{
	if (m_pRecordsets)
	{
		mysql_free_result(m_pRecordsets);
		m_pRecordsets = NULL;
	}

	if (m_ArrColLens)
	{
		m_ArrColLens = NULL;
	}

	m_pMySqlBaseApp = NULL;

	delete this;
}

//设置记录集游标
void CMySqlRecordset::MoveNext()
{
	ASSERT(m_pRecordsets);

	m_CurRowPos = mysql_row_tell(m_pRecordsets);
	m_pMySqlRow = mysql_fetch_row(m_pRecordsets);
	m_ArrColLens = mysql_fetch_lengths(m_pRecordsets);
	
}

void CMySqlRecordset::MovePrev()
{

}

void CMySqlRecordset::MoveFirst()
{
	ASSERT(m_pRecordsets);

	m_CurRowPos = mysql_row_seek(m_pRecordsets, m_BeginRowPos);	
	m_pMySqlRow = mysql_fetch_row(m_pRecordsets);
	m_ArrColLens = mysql_fetch_lengths(m_pRecordsets);
}

void CMySqlRecordset::MoveLast()
{
	ASSERT(m_pRecordsets);
	ASSERT(m_BeginRowPos);

	MYSQL_ROW_OFFSET tmpPos = m_BeginRowPos;
	while(tmpPos->next != NULL)
	{
		tmpPos = tmpPos->next;
	}
	m_CurRowPos = mysql_row_seek(m_pRecordsets, tmpPos);
	m_pMySqlRow = mysql_fetch_row(m_pRecordsets);
	m_ArrColLens = mysql_fetch_lengths(m_pRecordsets);
}

BOOL CMySqlRecordset::IsBof()
{
	ASSERT(m_pRecordsets);
	return (m_CurRowPos == m_BeginRowPos);
}

BOOL CMySqlRecordset::IsEof()
{
	ASSERT(m_pRecordsets);

	MYSQL_ROW_OFFSET tmpPos = mysql_row_tell(m_pRecordsets);
	if (tmpPos || m_pMySqlRow)
	{
		return FALSE;
	}

	m_ArrColLens = NULL;
	return TRUE;

//	return mysql_eof(m_pRecordsets);
}

BOOL CMySqlRecordset::DB_AllocStringBuffer()
{
#ifdef _DBLIB_USE_SHAREMEM_
#else
	m_pStrBufValue->SetBufferLength(0);
	CXDbSQLFieldObject *p = NULL;
	POS pos = NULL;
	
	m_pStrBufValue->AddBufLenByVal(m_strTableName);
	m_pStrBufValue->AddBufferLength(50);//"insert into"   “value("

	pos = GetHeadPosition();
	while (pos != NULL)
	{
		p = (CXDbSQLFieldObject *)GetNext(pos);
		m_pStrBufValue->AddBufLenByVal(p->m_strID);
		m_pStrBufValue->AddBufferLength(32);		//中间分隔符长度
		m_pStrBufValue->AddBufferLength(p->GetValueLength());
	}
#endif

	return m_pStrBufValue->AllocBuffer(0);
}


BOOL CMySqlRecordset::DB_InsertStrBufSerialize()
{
	CString strSql = _T("");
	CXDbSQLFieldObject *p = NULL;
	POS pos = NULL;
	int index = 0;

	//2021-3-23 shaolei 防止主键在最后一个，导致插入失败
	BringToHead(m_pPKObj);

	//拼开头
	*m_pStrBufValue << "insert into " << m_strTableName << "(";

	index = 0;
	pos = GetHeadPosition();
	while (pos != NULL)
	{
		p = (CXDbSQLFieldObject *)GetNext(pos);

		if (m_pPKObj == p && m_bPKAutoIncreaceFlg)
		{
			if (m_pPKObj->IsValueEmpty())
			{
				continue;
			}
		}
		
		*m_pStrBufValue << p->m_strID;

		if (pos == NULL)
		{
			*m_pStrBufValue << ")";
		}
		else
		{
			*m_pStrBufValue << ", ";
		}
	}

	//拼字段名
	*m_pStrBufValue << " values( ";

	index = 0;
	pos = GetHeadPosition();
	while (pos != NULL)
	{
		p = (CXDbSQLFieldObject *)GetNext(pos);

		if (m_pPKObj == p && m_bPKAutoIncreaceFlg)
		{
			if (m_pPKObj->IsValueEmpty())
			{
				continue;
			}
		}

// 		if (p->m_nValType ==_SQL_VT_BLOB)
// 		{
// 			m_oStrBufValue << "\"";
// 			int offset = 0;
// 			char *pEnd = (char *)m_oStrBufValue.GetBuffer() + m_oStrBufValue.Tell();
// 			offset = mysql_real_escape_string(&m_pMySqlBaseApp->m_Mysql, pEnd,
// 				p->oMySQLValue.oBlob.pBuffer, p->oMySQLValue.oBlob.nLen);
// 			m_oStrBufValue.Offset(offset);
// 			m_oStrBufValue << "\"";
// 		}
// 		else
			p->FieldValSerialize(*m_pStrBufValue);

		if (pos == NULL)
		{
			*m_pStrBufValue << ")";
		}
		else
		{
			*m_pStrBufValue << ", ";
		}
	}

	return TRUE;
}

BOOL CMySqlRecordset::DB_UpdateStrBufSerialize()
{
	CXDbSQLFieldObject *p = NULL;
	POS pos = NULL;

	//拼开头
	*m_pStrBufValue << "update " << m_strTableName << " set ";

	pos = GetHeadPosition();
	while (pos != NULL)
	{
		p = (CXDbSQLFieldObject *)GetNext(pos);

		//20190513，去掉这个部分，如果不用Index，在DB_WriteFields修改?????????
		if (m_pPKObj == p)
		{
			continue;
		}

		//拼字段名
		*m_pStrBufValue << p->m_strID << "=";

		//拼段值
		p->FieldValSerialize(*m_pStrBufValue);

		if (pos != NULL)
		{
			*m_pStrBufValue << ", ";
		}
		else
		{
			*m_pStrBufValue << " where " << m_pPKObj->m_strID << "=";

			//拼段值
			m_pPKObj->FieldValSerialize(*m_pStrBufValue);
		}
	}

	return TRUE;
}

//失败3次，则失败
BOOL CMySqlRecordset::DB_ExecCmd()
{
	int ret = 0;
	m_pStrBufValue->StringEnd();
	long nLen = m_pStrBufValue->Tell();
	ret = mysql_real_query(&m_pMySqlBaseApp->m_Mysql, m_pStrBufValue->GetBuffer(), m_pStrBufValue->Tell());
	
	if (ret)
	{
		if (m_pMySqlBaseApp->ReConnectDB_Ex())
		{
			ret = mysql_real_query(&m_pMySqlBaseApp->m_Mysql, m_pStrBufValue->GetBuffer(), m_pStrBufValue->Tell());
		}
	}

	if (ret == 0)
	{
		return TRUE;
	}

	CString strFile;
	strFile = _P_GetDBPath();
	CreateAllDirectories(strFile);

	SYSTEMTIME tmSys;
	::GetLocalTime(&tmSys);
	CString strTime;
	strTime.Format(_T("%d-%d-%d-%d-%d-%d"), 
		tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
	strFile.AppendFormat(_T("%s.sqltxt"), strTime);
	m_pStrBufValue->WriteToFile(strFile);
	CLogPrint::LogString(XLOGLEVEL_ERROR, _T("mysql_real_query 失败"));

	return FALSE;
}

BOOL CMySqlRecordset::DB_InsertSql()
{
	DB_AllocStringBuffer();

	DB_InsertStrBufSerialize();

	//执行SQL
	return DB_ExecCmd();
}

BOOL CMySqlRecordset::DB_UpdateSql()
{
//	ASSERT(m_pRecordsets);

	DB_AllocStringBuffer();

	DB_UpdateStrBufSerialize();

	//执行SQL
	return DB_ExecCmd();
}

//lijq  2019-4-14  增加返回值
BOOL CMySqlRecordset::Update(BSTR bstrPrimaryKey, BOOL bInsert)
{
	CString strPK;
	strPK = bstrPrimaryKey;
	m_bPKAutoIncreaceFlg = InitPrimaryState(strPK);

	if(bInsert)
	{
		return DB_InsertSql();
	}
	else
	{
		return DB_UpdateSql();
	}
}

//刷新记录集
void CMySqlRecordset::UpdateAll()
{
	
}

void CMySqlRecordset::AddNew()
{

}

//删除记录
void CMySqlRecordset::Delete()
{

}

//删除记录
void CMySqlRecordset::DeleteAll()
{
	if (m_pFields)
	{
		delete m_pFields;
	}
	if (m_pRecordsets)
	{
		mysql_free_result(m_pRecordsets);
	}
}

/////////////////////////////////////////////////////////////////////////


////////////////////////CMySqlBaseApp////////////////////////////////////////

CMySqlBaseApp::CMySqlBaseApp(void)
{
	g_pTheMySqlApp = this;
	m_bConnectStatus = FALSE;
}

CMySqlBaseApp::~CMySqlBaseApp(void)
{
	DisconnectDB();
}

BOOL CMySqlBaseApp::ReConnectDB_Ex()
{
	int nRet = mysql_errno(&m_Mysql);
	CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("mysql_errno【%d】"),nRet);

	if((nRet == CR_SERVER_LOST) 
		|| (nRet == CR_SERVER_GONE_ERROR)
		|| (nRet == CR_COMMANDS_OUT_OF_SYNC))	//与服务器断链
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("服务器断开【%d】，正在重连……"),nRet);
		
		if(ReConnectDB())
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("重连成功"));
			return TRUE;
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("重连失败"));
			return FALSE;
		}
	}
	
	return FALSE;
}

BOOL CMySqlBaseApp::ReConnectDB()
{
	CTickCount32 oTick;
	if (m_bConnectStatus)
	{
		mysql_close(&m_Mysql);
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("mysql_close=%d"), oTick.GetTickCountLong());
		m_bConnectStatus = false;
// 		mysql_library_end();
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("mysql_library_end=%d"), oTick.GetTickCountLong());
		m_bConnectStatus = FALSE;
	}
	
	BOOL bRet = ConnectDB(m_oServerInfo);
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("ConnectDB=%d"), oTick.GetTickCountLong());

	return bRet;
}

BOOL CMySqlBaseApp::InitMySqlDB(CDBServerInfoBase &oServerInfo)
{
	m_oServerInfo = oServerInfo;

	if (!ConnectDB(m_oServerInfo))
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("连接数据库失败。"));
		return FALSE;
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("连接数据库成功。"));
		return TRUE;
	}
}

//连接数据库
BOOL CMySqlBaseApp::ConnectDB(CDBServerInfoBase &oDBServerInfo)
{
	if(! oDBServerInfo.IsValid())
	{
		return FALSE;
	}

	m_bConnectStatus = FALSE;
	char strHostIp[200];
	char strUserName[200];
	char strPasswd[200];
	char strDbName[200];

	if (!mysql_init(&m_Mysql))//初始化环境
	{
		return m_bConnectStatus;
	}

	CString_to_char(oDBServerInfo.m_strHostIp, strHostIp);
	CString_to_char(oDBServerInfo.m_strUserName, strUserName);
	CString_to_char(oDBServerInfo.m_strPasswd, strPasswd);
	CString_to_char(oDBServerInfo.m_strDbName, strDbName);

	if (!mysql_real_connect(&m_Mysql,strHostIp, 
		strUserName, strPasswd, strDbName,
		oDBServerInfo.m_iPort,NULL,0))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("mysql_real_connect 失败:  HostIp[%s]  UserName[%s]  Passwd[%s]  DbName[%s] Port[%d]"), strHostIp, strUserName, strPasswd, strDbName, oDBServerInfo.m_iPort);
		return m_bConnectStatus;
	}

	//设置断链自动重连机制
	// 		char value = 1;
	// 		mysql_options(&m_Mysql, MYSQL_OPT_RECONNECT, (char *)&value);

	CString strEncoding = oDBServerInfo.m_strEncoding;
	if (strEncoding.CompareNoCase(_T("utf8mb4")) == 0)
	{
		mysql_query(&m_Mysql,"SET NAMES utf8mb4");
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("SET NAMES utf8mb4"));
	}
	else if (strEncoding.CompareNoCase(_T("GB2312")) == 0)
	{
		mysql_query(&m_Mysql,"SET NAMES GB2312");
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("SET NAMES GB2312"));
	}
	else if (strEncoding.CompareNoCase(_T("utf8")) == 0)
	{
		mysql_query(&m_Mysql,"SET NAMES utf8");
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("SET NAMES utf8"));
	}
	else   //默认GB2312  改为默认GB2312  shaolei 20210923
	{
		mysql_query(&m_Mysql,"SET NAMES GB2312");
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("SET NAMES GB2312"));
	}

// #ifdef WIN32
// 	mysql_query(&m_Mysql,"SET NAMES GB2312");
// 	CLogPrint::LogString(XLOGLEVEL_ERROR, _T("SET NAMES GB2312"));
// #else
// 	//  		mysql_query(&m_Mysql,"SET NAMES utf8");
// 	mysql_query(&m_Mysql,"SET NAMES utf8mb4");
// 	CLogPrint::LogString(XLOGLEVEL_ERROR, _T("SET NAMES utf8mb4"));
// #endif

	m_bConnectStatus = TRUE;

// 	CString strQuery = _T("set sql_safe_updates=1");
// 	ExecuteCmd(strQuery);

	return m_bConnectStatus;
}

//断开数据库连接
void CMySqlBaseApp::DisconnectDB(void)
{
	if (m_bConnectStatus)
	{
		mysql_close(&m_Mysql);
		m_bConnectStatus = false;
		mysql_library_end();
		m_bConnectStatus = FALSE;
	}	
}

//操作失败，检查服务器连接，失败重连再重传
BOOL CMySqlBaseApp::MySql_ExecCmdEx(const CString &strQuery)
{
	char* pcsSql = NULL;
	pcsSql = SQL_String_To_Char(strQuery);

	//mysql_query返回0表示查询成功
	int ret = mysql_query(&m_Mysql, pcsSql);
	if(ret != 0) 
	{
		if (ReConnectDB_Ex())
		{
			ret = mysql_query(&m_Mysql, pcsSql);
		}	
	}
	
	if (ret != 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("mysql_query 失败: %s"), strQuery);
	}

	delete pcsSql;

	return (ret == 0);
}

//执行查找
CXDbRecordsetBase* CMySqlBaseApp::ExecuteQuery(CString &strQuery)
{
	//查询锁
	CAutoSimpleLock oLock(m_oQueryCriticSection);

	if (!m_bConnectStatus || strQuery.IsEmpty())
	{
		return NULL;
	}

	BOOL bRet = MySql_ExecCmdEx(strQuery);
	if (!bRet)
	{
		return NULL;
	}

// 	char* pcsSql = NULL;
// 	pcsSql = SQL_String_To_Char(strQuery);
// 	//mysql_query返回0表示查询成功
// 	int ret = mysql_query(&m_Mysql, pcsSql);
// 	if(ret != 0) 
// 	{
// 		do 
// 		{
// 			int nRet = mysql_errno(&m_Mysql);
// 			if(nRet == 2006)
// 			{
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("服务器断开，正在重连……"));
// 				if(ReConnectDB())
// 				{
// 					CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("重连成功"));
// 					ret = mysql_query(&m_Mysql, pcsSql);
// 					if (ret == 0)
// 					{
// 						break;
// 					}
// 				}
// 				else
// 				{
// 					CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("重连失败"));
// 				}
// 			}
// 			delete pcsSql;
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("mysql_query 失败: %s"), strQuery);
// 			return  NULL;
// 		} while (0);	
// 	}
// 	
// 	delete pcsSql;
// //	oTickObj.LogTickCountLong(_T("mysql_query:") + strQuery, TRUE);

	MYSQL_RES* pRecordsets = mysql_store_result(&m_Mysql);
	ASSERT(pRecordsets != NULL);

	CMySqlRecordset* pMySqlRecordset = new CMySqlRecordset(this,pRecordsets);
#ifdef _DBLIB_USE_SHAREMEM_
	pMySqlRecordset->m_pStrBufValue = &m_oStringSerializeBufferAscii_ShareMem;
	//pMySqlRecordset->m_pStrBufValue = &m_oStringSerializeBufferAscii;
#endif

	pMySqlRecordset->InitEncoding(XSTR_Encoding_GetIdx(m_oServerInfo.m_strEncoding));
	return pMySqlRecordset;	
}

//执行命令
BOOL CMySqlBaseApp::ExecuteCmd(const CString &strCmd)
{
	if (!m_bConnectStatus || strCmd.IsEmpty())
	{
		return FALSE;
	}

	return MySql_ExecCmdEx(strCmd);
}

CXDbRecordsetBase* CMySqlBaseApp::SQLNewRecordset(const CString &strTable, const CString &strPrimaryKey, const CString &strPrimaryKeyValue)
{
	CMySqlRecordset *pNew = new CMySqlRecordset(this, NULL);
	pNew->m_strTableName = strTable;

#ifdef _DBLIB_USE_SHAREMEM_
	pNew->m_pStrBufValue = &m_oStringSerializeBufferAscii_ShareMem;
	//pNew->m_pStrBufValue = &m_oStringSerializeBufferAscii;
#endif

	return pNew;
}

//返回错误信息  
CString CMySqlBaseApp::GetErrorMsg(void)
{
	CString strValue;
	strValue.Format(_T("%s"),mysql_error(&m_Mysql));
	return strValue;
}

BOOL CMySqlBaseApp::DeleteDataFromDB(const CString &strTableName,const CString &strConditionName,long lCondition)
{
	CString strSQL;
	strSQL.Format(_T("delete * from %s where %s=%d"),strTableName,strConditionName,lCondition);

	return ExecuteCmd(strSQL);
}

BOOL CMySqlBaseApp::DeleteDataFromDB(const CString &strTableName,const CString &strConditionName,const CString &strCondition)
{
	//从数据库删除自身数据
	CString strSQL;
	strSQL.Format(_T("delete * from %s where %s=\'%s\'"),strTableName,strConditionName,strCondition);

	return ExecuteCmd(strSQL);
}

#ifdef _DBLIB_USE_SHAREMEM_
void CMySqlBaseApp::InitSerializeSmBuffer()
{
	CreateShareMemSerialize();

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("MySqlRecordRW.xdbsm");
	m_oStringSerializeBufferAscii_ShareMem.CreateShareMemSerialize(strFile);

	m_oStringSerializeBufferAscii.SetBufferLength(4 *1024 * 1024);//4M
	m_oStringSerializeBufferAscii.AllocBuffer(0);
}

void CMySqlBaseApp::ExitSerializeSmBuffer()
{
	FreeShareMemSerialize();

	m_oStringSerializeBufferAscii_ShareMem.FreeBuff();
}
#endif

//#################  ###############################
//从数据库读取大二进制数据的函数
// BOOL ADO_GetChunk(ADODB::_RecordsetPtr pRecordset,CString strTableField,CString &strData)
// {
// 	_variant_t vTable(strTableField);
// 	long lDataSize = pRecordset->GetFields()->GetItem(vTable)->ActualSize;
// 
// 	if(lDataSize > 0) 
// 	{
// 		_variant_t varBLOB;
// 		varBLOB = pRecordset->GetFields()->GetItem(vTable)->GetChunk(lDataSize);
// 		if(varBLOB.vt == (VT_ARRAY | VT_UI1)) ///判断数据类型是否正确
// 		{
// 			BSTR HUGEP *pbstr;
// 			SafeArrayAccessData(varBLOB.parray,(void **)&pbstr); 
// 			///得到指向数据的指针 /*****在这里我们可以对pBuf中的数据进行处理*****/
// 			strData = *pbstr;	
// 			SafeArrayUnaccessData (varBLOB.parray);
// 		}
// 		else
// 			strData="";
// 	} 
// 	else
// 		strData="";
// 	return TRUE;
// }
// 
// //向数据库写大二进制数据
// BOOL ADO_AppendChunk(ADODB::_RecordsetPtr pRecordset,CString strTableField,CString strData)
// {
// 	_variant_t vTable(strTableField);
// 	char *pBuff=NULL;
// 	long lLength=strData.GetLength()+1;
// 	pBuff=new char [lLength+2];
// 	CString_to_char(strData, pBuff);
// 	VARIANT varBLOB;
// 	SAFEARRAY *psa; 
// 	SAFEARRAYBOUND rgsabound[1];
// 
// 	char *p=pBuff;
// 	rgsabound[0].lLbound = 0;
// 	rgsabound[0].cElements = lLength;
// 	psa = SafeArrayCreate(VT_UI1, 1,rgsabound);		///创建SAFEARRAY对象
// 	for(long i = 0; i < (long)lLength; i++)			
// 		SafeArrayPutElement (psa,&i,p++);			///将pBuf指向的二进制数据保存到SAFEARRAY对象psa中
// 	varBLOB.vt = VT_ARRAY | VT_UI1;					///将varBLOB的类型设置为BYTE类型的数组
// 	varBLOB.parray = psa; 							///为varBLOB变量赋值 
// 	pRecordset->GetFields()->GetItem(vTable)->AppendChunk(varBLOB); 	///加入BLOB类型的数据
// 
// 	delete pBuff;
// 
// 	return TRUE;
// }
