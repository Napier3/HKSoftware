// ADOBaseApp.h: interface for the CADOBaseApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MySqlBaseApp_H__)
#define _MySqlBaseApp_H__ 

#include "..\..\Module\mysql\include\mysql.h"
#include "..\BaseClass\xdbbaselib.h"
#include "..\BaseClass\XDbSQLFieldObject.h"
#include "..\CriticalSection\SynCriticalSection.h"

#define MYSQLRECORDSET_NORMAL		0
#define MYSQLRECORDSET_STATISTIC	1

class CMySqlBaseApp;

class CMySqlRecordset : public CXDbRecordsetBase, public CExBaseList
{
public:
	CMySqlRecordset(CMySqlBaseApp *pBaseApp, MYSQL_RES *pRecordsets);
	virtual ~CMySqlRecordset(void);

	CStringSerializeBufferAscii *m_pStrBufValue;
private:
	CMySqlRecordset(void);
//	CStringSerializeBufferAscii m_oStrBufField;

public:
	virtual long FindField(const CString &strID);
	virtual char* Item(long nColIndex)
	{
		if(!m_pRecordsets)
			return NULL;
		ASSERT(m_pMySqlRow);
		ASSERT(m_ArrColLens);

		nCurFieldDataLen = m_ArrColLens[nColIndex];
		return m_pMySqlRow[nColIndex];
	}
	virtual char* Item(const CString &strID);

	virtual BOOL InitRecordset(CMySqlBaseApp *pBaseApp, MYSQL_RES *pRecordsets);

	//设置记录集游标
	virtual void MoveNext();
	virtual void MovePrev();
	virtual void MoveFirst();
	virtual void MoveLast();

	virtual BOOL IsBof();
	virtual BOOL IsEof();
	virtual void Free();

	virtual void AddNew();
	virtual BOOL Update(BSTR bstrPrimaryKey, BOOL bInsert=FALSE);		//刷新当前记录  //lijq  2019-4-14  增加返回值
	virtual void UpdateAll();	//刷新记录集
	virtual void Delete();		//删除当前记录
	virtual void DeleteAll();	//删除记录集

	BOOL GetFieldBaseValue(long nFieldIndex,char **pchVal);
	BOOL GetFieldBaseValue(const CString &strID,char **pchVal);

	//获取当前记录值
	virtual BOOL GetFieldValue(long nFieldIndex, CString &strValue);
	virtual BOOL GetFieldValue(long nFieldIndex, long &nValue);
	virtual BOOL GetFieldValue(long nFieldIndex, double &fValue);
	virtual BOOL GetFieldValue(long nFieldIndex, float &fValue);
	virtual BOOL GetFieldValue(long nFieldIndex, DWORD &dwValue);
	virtual BOOL GetFieldValue(long nFieldIndex, __int64 &n64Value);
	virtual BOOL GetFieldValue(long nFieldIndex, SYSTEMTIME &tmValue);
	virtual BOOL GetFieldValue(long nFieldIndex, char **blobData, long &nLen);

	virtual BOOL GetFieldValue(const CString &strID, CString &strValue);
	virtual BOOL GetFieldValue(const CString &strID, long &nValue);
	virtual BOOL GetFieldValue(const CString &strID, double &fValue);
	virtual BOOL GetFieldValue(const CString &strID, float &fValue);
	virtual BOOL GetFieldValue(const CString &strID, DWORD &dwValue);
	virtual BOOL GetFieldValue(const CString &strID, __int64 &n64Value);
	virtual BOOL GetFieldValue(const CString &strID, SYSTEMTIME &tmValue);
	virtual BOOL GetFieldValue(const CString &strID, char **blobData, long &nLen);

	virtual BOOL GetFieldValue(BSTR strID, CString &strValue);
	virtual BOOL GetFieldValue(BSTR strID, long &nValue);
	virtual BOOL GetFieldValue(BSTR strID, double &fValue);
	virtual BOOL GetFieldValue(BSTR strID, float &fValue);
	virtual BOOL GetFieldValue(BSTR strID, DWORD &dwValue);
	virtual BOOL GetFieldValue(BSTR strID, __int64 &n64Value);
	virtual BOOL GetFieldValue(BSTR strID, SYSTEMTIME &tmValue);
	virtual BOOL GetFieldValue(BSTR strID, char **blobData, long &nLen);

	//设置当前记录值(MySql只能用段名设置，才保证与ADO接口兼容)
	virtual void SetFieldValue(long nFieldIndex, const CString &strValue);
	virtual void SetFieldValue(long nFieldIndex, long &nValue);
	virtual void SetFieldValue(long nFieldIndex, double &fValue);
	virtual void SetFieldValue(long nFieldIndex, float &fValue);
	virtual void SetFieldValue(long nFieldIndex, DWORD &dwValue);
	virtual void SetFieldValue(long nFieldIndex, __int64 &n64Value);
	virtual void SetFieldValue(long nFieldIndex, SYSTEMTIME &tmValue);
	virtual void SetFieldValue(long nFieldIndex, char **blobData, long &nLen);

	virtual void SetFieldValue(const CString &strID, const CString &strValue);
	virtual void SetFieldValue(const CString &strID, long &nValue);
	virtual void SetFieldValue(const CString &strID, double &fValue);
	virtual void SetFieldValue(const CString &strID, float &fValue);
	virtual void SetFieldValue(const CString &strID, DWORD &dwValue);
	virtual void SetFieldValue(const CString &strID, __int64 &n64Value);
	virtual void SetFieldValue(const CString &strID, SYSTEMTIME &tmValue);
	virtual void SetFieldValue(const CString &strID, char **blobData, long &nLen);

	virtual void SetFieldValue(BSTR strID, const CString &strValue);
	virtual void SetFieldValue(BSTR strID, long &nValue);
	virtual void SetFieldValue(BSTR strID, double &fValue);
	virtual void SetFieldValue(BSTR strID, float &fValue);
	virtual void SetFieldValue(BSTR strID, DWORD &dwValue);
	virtual void SetFieldValue(BSTR strID, __int64 &n64Value);
	virtual void SetFieldValue(BSTR strID, SYSTEMTIME &tmValue);
	virtual void SetFieldValue(BSTR strID, char **blobData, long &nLen);

	// 获取查询结果的列数	
	virtual long GetQueryNumCols(void);
	virtual long GetQueryNumRows(void);

	BOOL DB_InsertSql();
	BOOL DB_UpdateSql();

	BOOL DB_AllocStringBuffer();
	BOOL DB_InsertStrBufSerialize();
	BOOL DB_UpdateStrBufSerialize();
	BOOL DB_ExecCmd();

	BOOL InitPrimaryState(CString &strPK);
	// 功能描述: 获取插入记录后的自动增长的主键
	virtual long GetInsertId(void);
public:	
	MYSQL_RES*	    m_pRecordsets;  //记录集
	MYSQL_ROW		m_pMySqlRow;	//当前记录指针
	MYSQL_FIELD *	m_pFields;		//段集合指针

	int m_nCols;					//段或列个数
	int m_nRows;					//记录或行个数
	MYSQL_ROW_OFFSET m_CurRowPos;		//当前记录行索引
	MYSQL_ROW_OFFSET m_BeginRowPos;
	

	//插入记录需要，链表成员为字段值，在Update中生成strSql，执行插入命令
	CMySqlBaseApp *	m_pMySqlBaseApp;
//	CString m_strTableName;	

	unsigned long *m_ArrColLens;		//当前记录数据长度数组
	unsigned long nCurFieldDataLen;		//当前记录行中当前字段数据长度

	BOOL m_bPKAutoIncreaceFlg;			//自动递增主键标志
	CXDbSQLFieldObject *m_pPKObj;		//主键对象指针，在Update里面更新

//	int m_nMode;						//默认为0,读写所有字段，1：只读统计字段
protected:

	//2018-10-12  lijq  数据库读写 二进制串行化缓冲区
public:
	virtual CXDbBaseLib* GetXDbBaseLib();

	virtual CString GetFieldName(long index)	{	CString strName;	strName = m_pFields[index].name;	return strName;	}

	//shaolei  20210818 
	void InitEncoding(UINT nEncoding)	{	m_pStrBufValue->SetEncoding(nEncoding);	}

};


class CMySqlBaseApp : public CXDbBaseLib
{
public:
	CMySqlBaseApp(void);
	virtual ~CMySqlBaseApp(void);

	BOOL ReConnectDB_Ex();
public:
	virtual BOOL InitMySqlDB(CDBServerInfoBase &oServerInfo);
	virtual BOOL ConnectDB(CDBServerInfoBase &oDBServerInfo);		//连接数据库
	virtual void DisconnectDB();								//断开数据库连接
	virtual BOOL ReConnectDB();

	virtual CXDbRecordsetBase* ExecuteQuery(CString &strQuery);		//执行查找
	virtual BOOL ExecuteCmd(const CString &strCmd);						//执行命令 

	//执行MySql命令，若操作失败，且检查服务器断链，则重新建链和重新执行命令
	BOOL MySql_ExecCmdEx(const CString &strQuery);

	virtual CXDbRecordsetBase* SQLNewRecordset(const CString &strTable, const CString &strPrimaryKey, const CString &strPrimaryKeyValue);
	virtual CXDbRecordsetBase* SQLSelect(const CString &strTable, const CString &strPrimaryKey, const CString &strPrimaryKeyValue)
	{
		CString stSQL;
		GetSQLSelect(stSQL, strTable, strPrimaryKey, strPrimaryKeyValue);

// 		m_strTableName = strTable;
		CMySqlRecordset *pRecordset = (CMySqlRecordset*)ExecuteQuery(stSQL);

		if (pRecordset != NULL)
		{
			pRecordset->m_strTableName = strTable;
		}

		return pRecordset;
	}

	//删除指定表中指定条件的记录
	virtual BOOL DeleteDataFromDB(const CString &strTableName,const CString &strConditionName,long lCondition);
	virtual BOOL DeleteDataFromDB(const CString &strTableName,const CString &strConditionName,const CString &strCondition);

	CString GetErrorMsg(void) ;                                     //返回错误信息
	virtual BOOL StartTransaction()	{	return mysql_autocommit(&m_Mysql, 0);	}
	virtual BOOL Commit() {	return mysql_autocommit(&m_Mysql, 1);	}

public:
	MYSQL				m_Mysql;
	BOOL				m_bConnectStatus;			//连接状态

	CDBServerInfoBase m_oServerInfo;
	//CString m_strTableName;

	CAutoCriticSection m_oQueryCriticSection;

#ifdef _DBLIB_USE_SHAREMEM_
private:
	CStringSerializeBufferAscii_ShareMem m_oStringSerializeBufferAscii_ShareMem;
	CStringSerializeBufferAscii m_oStringSerializeBufferAscii;

public:
	void InitSerializeSmBuffer();
	void ExitSerializeSmBuffer();
#endif

};

extern CMySqlBaseApp *g_pTheMySqlApp;

#endif // !defined(_ADOBaseApp_H__)
