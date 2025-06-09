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

	//���ü�¼���α�
	virtual void MoveNext();
	virtual void MovePrev();
	virtual void MoveFirst();
	virtual void MoveLast();

	virtual BOOL IsBof();
	virtual BOOL IsEof();
	virtual void Free();

	virtual void AddNew();
	virtual BOOL Update(BSTR bstrPrimaryKey, BOOL bInsert=FALSE);		//ˢ�µ�ǰ��¼  //lijq  2019-4-14  ���ӷ���ֵ
	virtual void UpdateAll();	//ˢ�¼�¼��
	virtual void Delete();		//ɾ����ǰ��¼
	virtual void DeleteAll();	//ɾ����¼��

	BOOL GetFieldBaseValue(long nFieldIndex,char **pchVal);
	BOOL GetFieldBaseValue(const CString &strID,char **pchVal);

	//��ȡ��ǰ��¼ֵ
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

	//���õ�ǰ��¼ֵ(MySqlֻ���ö������ã��ű�֤��ADO�ӿڼ���)
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

	// ��ȡ��ѯ���������	
	virtual long GetQueryNumCols(void);
	virtual long GetQueryNumRows(void);

	BOOL DB_InsertSql();
	BOOL DB_UpdateSql();

	BOOL DB_AllocStringBuffer();
	BOOL DB_InsertStrBufSerialize();
	BOOL DB_UpdateStrBufSerialize();
	BOOL DB_ExecCmd();

	BOOL InitPrimaryState(CString &strPK);
	// ��������: ��ȡ�����¼����Զ�����������
	virtual long GetInsertId(void);
public:	
	MYSQL_RES*	    m_pRecordsets;  //��¼��
	MYSQL_ROW		m_pMySqlRow;	//��ǰ��¼ָ��
	MYSQL_FIELD *	m_pFields;		//�μ���ָ��

	int m_nCols;					//�λ��и���
	int m_nRows;					//��¼���и���
	MYSQL_ROW_OFFSET m_CurRowPos;		//��ǰ��¼������
	MYSQL_ROW_OFFSET m_BeginRowPos;
	

	//�����¼��Ҫ�������ԱΪ�ֶ�ֵ����Update������strSql��ִ�в�������
	CMySqlBaseApp *	m_pMySqlBaseApp;
//	CString m_strTableName;	

	unsigned long *m_ArrColLens;		//��ǰ��¼���ݳ�������
	unsigned long nCurFieldDataLen;		//��ǰ��¼���е�ǰ�ֶ����ݳ���

	BOOL m_bPKAutoIncreaceFlg;			//�Զ�����������־
	CXDbSQLFieldObject *m_pPKObj;		//��������ָ�룬��Update�������

//	int m_nMode;						//Ĭ��Ϊ0,��д�����ֶΣ�1��ֻ��ͳ���ֶ�
protected:

	//2018-10-12  lijq  ���ݿ��д �����ƴ��л�������
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
	virtual BOOL ConnectDB(CDBServerInfoBase &oDBServerInfo);		//�������ݿ�
	virtual void DisconnectDB();								//�Ͽ����ݿ�����
	virtual BOOL ReConnectDB();

	virtual CXDbRecordsetBase* ExecuteQuery(CString &strQuery);		//ִ�в���
	virtual BOOL ExecuteCmd(const CString &strCmd);						//ִ������ 

	//ִ��MySql���������ʧ�ܣ��Ҽ������������������½���������ִ������
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

	//ɾ��ָ������ָ�������ļ�¼
	virtual BOOL DeleteDataFromDB(const CString &strTableName,const CString &strConditionName,long lCondition);
	virtual BOOL DeleteDataFromDB(const CString &strTableName,const CString &strConditionName,const CString &strCondition);

	CString GetErrorMsg(void) ;                                     //���ش�����Ϣ
	virtual BOOL StartTransaction()	{	return mysql_autocommit(&m_Mysql, 0);	}
	virtual BOOL Commit() {	return mysql_autocommit(&m_Mysql, 1);	}

public:
	MYSQL				m_Mysql;
	BOOL				m_bConnectStatus;			//����״̬

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
