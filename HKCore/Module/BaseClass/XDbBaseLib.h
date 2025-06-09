#pragma once

#ifdef _DBLIB_USE_SHAREMEM_
#include "ShareMemSerialize.h"
#endif

#include "../API/StringApi.h"

class CExBaseObject;
class CXDbBaseLib;
class CXmlRWKeys;

#define _SQL_VT_NONE      0
#define _SQL_VT_LONG      1
#define _SQL_VT_DWORD	6
#define _SQL_VT_INT64	5
#define _SQL_VT_FLOAT	7
#define _SQL_VT_DOUBLE	8
#define _SQL_VT_STR		2
#define _SQL_VT_BLOB	3
#define _SQL_VT_TIME	4

class CXDb_PKeyValue
{
public:
        union MYKEYVAL
        {
                __int64 *pn64Value;
                long *pnValue;
                CString *pstrValue;
        };

        UINT nType;
        BSTR bstrPkey;
        UINT nClassID;

        MYKEYVAL oKeyValRef;
        CExBaseObject *pRootObj;

public:
        CXDb_PKeyValue();
        CXDb_PKeyValue(CExBaseObject *pObj, CXmlRWKeys *pXmlRWKeys);

        virtual ~CXDb_PKeyValue()	{}

public:
        void SetValue(long *pnValue);
        void SetValue(__int64 *pn64Value);
        void SetValue(CString *pstrValue);

        void operator=(long *pnValue)			{	SetValue(pnValue);			}
        void operator=(__int64 *pn64Value)	{	SetValue(pn64Value);		}
        void operator=(CString *pstrValue)		{	SetValue(pstrValue);		}

        void GetValue(CString &strValue);

        BOOL operator==(long &nValue);
        BOOL operator==(__int64 &n64Value);
        BOOL operator==(const CString &strValue);
        BOOL operator==(const CXDb_PKeyValue &oValue);

        void SetValue(long nValue);
        void SetValue(__int64 n64Value);
        void SetValue(const CString &strValue);
        void SetValue(const CXDb_PKeyValue &oSrcKeyVal);
};

// 数据库连接信息
class CDBServerInfoBase
{
public:
        CDBServerInfoBase(void)					{		m_iPort = 0;	m_strEncoding = XSTR_EncodingID_utf8mb4;	};
        virtual ~CDBServerInfoBase(void)		{							};

public:
	CString m_strHostIp;			//主机名或IP地址
	CString m_strDbName;			//数据库名称
	CString m_strUserName;        //数据库用户名
	CString m_strPasswd;          //数据库密码
	int			m_iPort;			//TCP/IP连接的端口号
	CString m_strEncoding;         //数据库的字符编码   utf8、gb2312等

	CString m_strDSN;				//DSN(ado数据源)  2019-9-17


        BOOL IsValid_ADO()
        {
                if(m_strDSN.IsEmpty()
                        || m_strHostIp.IsEmpty()
                        || m_strDbName.IsEmpty()
                        || m_strUserName.IsEmpty()
                        || m_strPasswd.IsEmpty())
                {
                        return FALSE;
                }
                else
                {
                        return TRUE;
                }
        }

        BOOL IsValid()
        {
                if(m_strHostIp.IsEmpty()
                        || m_strDbName.IsEmpty()
                        || m_strUserName.IsEmpty()
                        || m_strPasswd.IsEmpty())
                {
                        return FALSE;
                }
                else
                {
                        return TRUE;
                }
        }

public:
	BOOL Is_UTF8()	{	return m_strEncoding == XSTR_EncodingID_utf8mb4 || m_strEncoding == XSTR_EncodingID_utf8;	}
};
typedef CDBServerInfoBase *P_DB_SERVER_INFO;
typedef CDBServerInfoBase DB_SERVER_INFO;


class CXDbRecordsetBase
{
public:
        CXDbRecordsetBase(void){};
        virtual ~CXDbRecordsetBase(void){};

public:
        CString m_strTableName;

        virtual char* Item(long nColIndex, long &nDataLen);
        virtual char* Item(const CString &strID, long &nDataLen);

	//设置记录集游标
        virtual void MoveNext() = 0;
        virtual void MovePrev() = 0;
        virtual void MoveFirst() = 0;
        virtual void MoveLast() = 0;

        virtual BOOL IsBof() = 0;
        virtual BOOL IsEof() = 0;
        virtual void Free() = 0;

        virtual void AddNew() = 0;

	//刷新当前记录，约定包含“index_”、“idx_”字符串的为自动编号的字段（主键）
	//lijq  2019-4-14  增加返回值
	virtual BOOL Update(BSTR bstrPrimaryKey, BOOL bInsert=FALSE) = 0;	

	virtual void UpdateAll() = 0;	//刷新记录集
	virtual void DeleteAll() = 0;	//删除记录

	// 功能描述: 获取插入记录后的自动增长的主键
        virtual long GetInsertId(void)	{ return 1;}

        virtual CString GetFieldName(long index);

	//获取当前记录值
        virtual BOOL GetFieldValue(long nFieldIndex, CString &strValue) = 0;
        virtual BOOL GetFieldValue(long nFieldIndex, long &nValue) = 0;
        virtual BOOL GetFieldValue(long nFieldIndex, double &fValue) = 0;
        virtual BOOL GetFieldValue(long nFieldIndex, float &fValue) = 0;
        virtual BOOL GetFieldValue(long nFieldIndex, DWORD &dwValue) = 0;
        virtual BOOL GetFieldValue(long nFieldIndex, __int64 &n64Value) = 0;
        virtual BOOL GetFieldValue(long nFieldIndex, SYSTEMTIME &tmValue) = 0;
        virtual BOOL GetFieldValue(long nFieldIndex, char **blobData, long &nLen) = 0;

        virtual BOOL GetFieldValue(const CString &strID, CString &strValue) = 0;
        virtual BOOL GetFieldValue(const CString &strID, long &nValue) = 0;
        virtual BOOL GetFieldValue(const CString &strID, double &fValue) = 0;
        virtual BOOL GetFieldValue(const CString &strID, float &fValue) = 0;
        virtual BOOL GetFieldValue(const CString &strID, DWORD &dwValue) = 0;
        virtual BOOL GetFieldValue(const CString &strID, __int64 &n64Value) = 0;
        virtual BOOL GetFieldValue(const CString &strID, SYSTEMTIME &tmValue) = 0;
        virtual BOOL GetFieldValue(const CString &strID, char **blobData, long &nLen) = 0;

        virtual BOOL GetFieldValue(BSTR strID, CString &strValue) = 0;
        virtual BOOL GetFieldValue(BSTR strID, long &nValue) = 0;
        virtual BOOL GetFieldValue(BSTR strID, double &fValue) = 0;
        virtual BOOL GetFieldValue(BSTR strID, float &fValue) = 0;
        virtual BOOL GetFieldValue(BSTR strID, DWORD &dwValue) = 0;
        virtual BOOL GetFieldValue(BSTR strID, __int64 &n64Value) = 0;
        virtual BOOL GetFieldValue(BSTR strID, SYSTEMTIME &tmValue) = 0;
        virtual BOOL GetFieldValue(BSTR strID, char **blobData, long &nLen) = 0;

	//设置当前记录值
        virtual void SetFieldValue(long nFieldIndex, const CString &strValue) = 0;
        virtual void SetFieldValue(long nFieldIndex, long &nValue) = 0;
        virtual void SetFieldValue(long nFieldIndex, double &fValue) = 0;
        virtual void SetFieldValue(long nFieldIndex, float &fValue) = 0;
        virtual void SetFieldValue(long nFieldIndex, DWORD &dwValue) = 0;
        virtual void SetFieldValue(long nFieldIndex, __int64 &n64Value) = 0;
        virtual void SetFieldValue(long nFieldIndex, SYSTEMTIME &tmValue) = 0;
        virtual void SetFieldValue(long nFieldIndex, char **blobData, long &nLen) = 0;

        virtual void SetFieldValue(const CString &strID, const CString &strValue) = 0;
        virtual void SetFieldValue(const CString &strID, long &nValue) = 0;
        virtual void SetFieldValue(const CString &strID, double &fValue) = 0;
        virtual void SetFieldValue(const CString &strID, float &fValue) = 0;
        virtual void SetFieldValue(const CString &strID, DWORD &dwValue) = 0;
        virtual void SetFieldValue(const CString &strID, __int64 &n64Value) = 0;
        virtual void SetFieldValue(const CString &strID, SYSTEMTIME &tmValue) = 0;
        virtual void SetFieldValue(const CString &strID, char **blobData, long &nLen) = 0;

        virtual void SetFieldValue(BSTR strID, const CString &strValue) = 0;
        virtual void SetFieldValue(BSTR strID, long &nValue) = 0;
        virtual void SetFieldValue(BSTR strID, double &fValue) = 0;
        virtual void SetFieldValue(BSTR strID, float &fValue) = 0;
        virtual void SetFieldValue(BSTR strID, DWORD &dwValue) = 0;
        virtual void SetFieldValue(BSTR strID, __int64 &n64Value) = 0;
        virtual void SetFieldValue(BSTR strID, SYSTEMTIME &tmValue) = 0;
        virtual void SetFieldValue(BSTR strID, char **blobData, long &nLen) = 0;

public:
        virtual BOOL GetFieldValue_Blob(BSTR strID, CString &strBlob)
        {
                char *pblobData =NULL;
                long nLen = 0;

                if (GetFieldValue(strID, &pblobData, nLen))
                {
                        strBlob = pblobData;
                        return TRUE;
                }
                else
                {
                        strBlob.Empty();
                        return FALSE;
                }
        }

        virtual void SetFieldValue_Blob(BSTR strID, const CString &strBlob)
        {
                char *pBlob = NULL;
                long nLen = CString_to_char(strBlob, &pBlob);
                SetFieldValue(strID, &pBlob, nLen);
//		delete pBlob;		//????delete  xxy
        }

        virtual void SetFieldValue_Blob(BSTR strID, const BSTR bstrBlob)
        {
                char *pBlob = NULL;
                long nLen = str_wchar_to_char(&pBlob, bstrBlob);
                SetFieldValue(strID, &pBlob, nLen);
                //		delete pBlob;		//????delete  xxy
        }

//2018-10-12  lijq  数据库读写 二进制串行化缓冲区
public:
        virtual CXDbBaseLib* GetXDbBaseLib() = 0;

#ifdef _DBLIB_USE_SHAREMEM_
        virtual CShareMemSerialize* GetShareMemSerialize();
#endif
};

typedef CXDbRecordsetBase CXDbBaseRow;

class CXDbBaseLib
{
public:
        CXDbBaseLib(void)
        {
#ifdef _DBLIB_USE_SHAREMEM_
                m_pShareMemSerialize_SingleRW = NULL;
#endif
        }
        virtual ~CXDbBaseLib(void)
        {
#ifdef _DBLIB_USE_SHAREMEM_
                if (m_pShareMemSerialize_SingleRW != NULL)
                {
                        m_pShareMemSerialize_SingleRW->SerializeFree();
                }
#endif
        };

public:
        virtual BOOL InitMySqlDB(CDBServerInfoBase &oServerInfo);
        virtual BOOL ConnectDB(CDBServerInfoBase &oServerInfo);   //连接数据库
        virtual void DisconnectDB(void) = 0;											//断开数据库连接

        virtual CXDbRecordsetBase* ExecuteQuery(CString &strQuerry) = 0; 
        virtual BOOL ExecuteCmd(const CString &strCmd) = 0;									//执行命令  

        virtual BOOL GetSQLSelect(CString &stSQL, const CString &strTable, const CString &strPrimaryKey, const CString &strPrimaryKeyValue)
        {
                if (strPrimaryKey.GetLength() > 0 && strPrimaryKeyValue.GetLength() > 0)
                {
                        stSQL.Format(_T("select * from %s where %s=\"%s\""), strTable.GetString()
                                     , strPrimaryKey.GetString(), strPrimaryKeyValue.GetString());
                }
                else
                {
                        stSQL.Format(_T("select * from %s"), strTable.GetString());
                }

                return TRUE;
        }

        virtual BOOL GetSQLDelete(CString &stSQL, const CString &strTable, const CString &strPrimaryKey, const CString &strPrimaryKeyValue)
        {
                if (strPrimaryKey.GetLength() > 0 && strPrimaryKeyValue.GetLength() > 0)
                {
                        stSQL.Format(_T("delete from %s where %s=\"%s\""), strTable.GetString()
                                     , strPrimaryKey.GetString(), strPrimaryKeyValue.GetString());
                }
                else
                {
                        stSQL.Format(_T("truncate table %s"), strTable.GetString());
                }

                return TRUE;
        }

		virtual CXDbRecordsetBase* SQLNewRecordset(const CString &strTable, const CString &strPrimaryKey, const CString &strPrimaryKeyValue);
        virtual CXDbRecordsetBase* SQLSelect(const CString &strTable, const CString &strPrimaryKey, const CString &strPrimaryKeyValue);
        virtual BOOL SQLDelete(const CString &strTable, const CString &strPrimaryKey, const CString &strPrimaryKeyValue);
        virtual BOOL StartTransaction() {	return FALSE;	}
        virtual BOOL Commit() {	return FALSE;	}

//数据库二进制BLOB区块序列化缓冲区：共享缓冲区，缓冲区只能提供为单线程使用，不能被多线程同时使用
private:
#ifdef _DBLIB_USE_SHAREMEM_
        CShareMemSerialize *m_pShareMemSerialize_SingleRW;
        DWORD m_dwLen_SmSerialize_SingleRW;
#endif


public:
	//缺省值：128M
#ifdef _DBLIB_USE_SHAREMEM_
        CShareMemSerialize* CreateShareMemSerialize(const CString &strMapFileName=_T(""), DWORD dwLen=128);
        void FreeShareMemSerialize();
        CShareMemSerialize* GetShareMemSerialize()	{		return m_pShareMemSerialize_SingleRW;		}
#endif
};

//记录的是，是否继续查询当前对象的子对象
class CXDbQueryChildrenMask
{
public:
        CXDbQueryChildrenMask()	{		m_bQueryAll = FALSE;	}
        virtual ~CXDbQueryChildrenMask()	{}

        virtual void AddClassID(UINT nClassID)
        {
                m_arrMask.Add(nClassID);
        }

        virtual BOOL NeedQueryChildren(UINT nClassID)
        {
                if (m_bQueryAll)
                {
                        return TRUE;
                }

                long nIndex = 0;
                long nCount = m_arrMask.GetCount();

                for (nIndex=0; nIndex<nCount; nIndex++)
                {
                        if (nClassID == m_arrMask.GetAt(nIndex))
                        {
                                return TRUE;
                        }
                }

                return FALSE;
        }

        virtual void SetQueryAll(BOOL b=TRUE)	{	m_arrMask.RemoveAll(); m_bQueryAll = b;	}
        virtual void RemoveAll()		{	m_arrMask.RemoveAll();			}

protected:
        CUIntArray m_arrMask;
        BOOL m_bQueryAll;
};


BOOL mysql_IsFieldNameAutoPKey(const CString &strFieldName);
