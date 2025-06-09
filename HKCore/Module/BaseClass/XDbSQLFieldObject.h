#ifndef _XDbSQLFieldObject_H__
#define _XDbSQLFieldObject_H__ 

#include "ExBaseList.h"
#include "StringSerializeBufferAscii.h"


typedef struct XDbSqlBlob
{
	long nLen;
	char *pBuffer;
}XDBSQLBLOB;

union UNION_DBSQLVALUE
{
	long nValue;
	DWORD dwValue;
	__int64 n64Value;
	float fValue;
	double dfValue;
	//char *pString;
	CString *pString;
	XDBSQLBLOB oBlob;
	SYSTEMTIME tmValue;
};

class CXDbSQLFieldObject : public CExBaseObject
{
public:
	CXDbSQLFieldObject();	
	CXDbSQLFieldObject(const CString &strID, long nValue);
	CXDbSQLFieldObject(const CString &strID, DWORD dwValue);
	CXDbSQLFieldObject(const CString &strID, __int64 n64Value);
	CXDbSQLFieldObject(const CString &strID, float fValue);
	CXDbSQLFieldObject(const CString &strID, double dfValue);
	CXDbSQLFieldObject(const CString &strID, const CString &strValue);
	CXDbSQLFieldObject(const CString &strID, long nLen, char *pBlob);
	CXDbSQLFieldObject(const CString &strID, SYSTEMTIME tmValue);

	virtual ~CXDbSQLFieldObject();

	void SetValue(long nValue);
	void SetValue(DWORD dwValue);
	void SetValue(__int64 n64Value);	
	void SetValue(float fValue);
	void SetValue(double dfValue);	
	void SetValue(const CString &strValue);
	void SetValue(long nLen, char *pBlob);
	void SetValue(SYSTEMTIME tmValue);

	long GetValueLength();
	BOOL FieldValSerialize(CStringSerializeBufferAscii &oStrBuf);
	BOOL IsValueEmpty();
	
public:
	UNION_DBSQLVALUE oMySQLValue;
	UINT m_nValType;
};

class CXDbSQLFieldObjects : public CExBaseList
{
public:
	CXDbSQLFieldObjects(){}
	CXDbSQLFieldObjects(const CString &strTable ){	m_strID = strTable;	}	
	CXDbSQLFieldObjects(BSTR bstrTable ){	m_strID = bstrTable;	}
	virtual ~CXDbSQLFieldObjects(){};

	void SetTableName(const CString &strTable ){	m_strID = strTable;	}	
	void SetTableName(BSTR bstrTable ){	m_strID = bstrTable;	}	

	void XDB_AddNewChild(const CString &strID);
	void XDB_AddNewChild(BSTR bstrID);

	void GetSelectSql(CString &strSql,CString strFilter=_T(""));
};

BOOL SQL_Val_To_String(CXDbSQLFieldObject *pObj, CString &strVal);
char *SQL_String_To_Char(const CString &strTrans);

void AdjustFieldString(CString *pString);


//数据库时间过滤
void GetDuringDateString(const SYSTEMTIME &tmBegin,const SYSTEMTIME &tmEnd
								,const CString &strTmKey, CString &strFilter);
void GetDuringDateString(const CString &strTmBegin,const CString &strTmEnd
								,const CString &strTmKey, CString &strFilter);
void MergeFilterString(const CString &strSrc,CString &strDest);

int FindFilterArrByValue(CUIntArray &FilterArr,UINT nValue);
void MergeFilterArr(CUIntArray &FilterArr_src,CUIntArray &FilterArr_dst);
CString GenerateFilterArrSql(CUIntArray &FilterArr);

void GenerateFilterArr(CExBaseList *pList,CUIntArray &FilterArr);
void GenerateFilterArrSql(CExBaseList *pList,CString &strArrFilter);
void GenerateFilterArrSql(CUIntArray &FilterArr,const CString &strKey,CString &strFilter);

//添加转义字符后字符串长度,20201116 xxy
long Sql_GetMySqlStringLen(char *pszData,long nLen);
long Sql_GetMySqlStringLen(const CString &strData);

#endif
