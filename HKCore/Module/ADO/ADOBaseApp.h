// ADOBaseApp.h: interface for the CADOBaseApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ADOBaseApp_H__)
#define _ADOBaseApp_H__

#import "msado15.dll" rename ("EOF", "adoEOF")  rename ("BOF", "adoBOF")  

#include "..\BaseClass\xdbbaselib.h"


class CXDbRecordset : public CXDbRecordsetBase
{
public:
	CXDbRecordset(void);
	CXDbRecordset(ADODB::_RecordsetPtr pRecordset);
	virtual ~CXDbRecordset(void);

	BOOL Open(ADODB::_ConnectionPtr &pConnection, const CString &strSQL);

public:
	//设置记录集游标
	virtual void MoveNext();
	virtual void MovePrev();
	virtual void MoveFirst();
	virtual void MoveLast();

	virtual BOOL IsBof();
	virtual BOOL IsEof();
	virtual void Free();

	virtual void AddNew();
	virtual BOOL Update(BSTR bstrPrimaryKey, BOOL bInsert=FALSE);		//刷新当前记录
	virtual void UpdateAll();	//刷新记录集
	virtual void Delete();		//删除当前记录
	virtual void DeleteAll();	//删除记录集

	virtual BOOL GetFieldBaseValue(long nFieldIndex,_variant_t &vt);
	virtual BOOL GetFieldBaseValue(const CString &strID,_variant_t &vt);

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

	//设置当前记录值
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


	virtual CXDbBaseLib* GetXDbBaseLib();

	// 获取查询结果的列数	
	virtual long GetQueryNumCols(void);

public:
	ADODB::_RecordsetPtr m_pRecordset;
};


class CADOBaseApp : public CXDbBaseLib
{
public:
	CADOBaseApp(void);
	virtual ~CADOBaseApp(void);
	BOOL IsConnectStatus(){return m_bConnectStatus;}

public:
	virtual BOOL ConnectDB(CDBServerInfoBase &oDBServerInfo);		//连接数据库
	virtual void DisconnectDB();								//断开数据库连接

	virtual CXDbRecordsetBase* ExecuteQuery(CString &strQuery);		//执行查找
	virtual BOOL ExecuteCmd(const CString &strCmd);						//执行命令 

	//从数据库中删除所有的子对象的数据
	virtual BOOL DeleteDataFromDB(const CString &strTableName,const CString &strConditionName,long lCondition);
	virtual BOOL DeleteDataFromDB(const CString &strTableName,const CString &strConditionName,const CString &strCondition);

private:
	ADODB::_ConnectionPtr		m_pConnection;
	BOOL				m_bConnectStatus;			//连接状态
};

extern CADOBaseApp *g_ptheADOApp;

//#################  ###############################
//从数据库读取大二进制数据的函数
BOOL ADO_GetChunk(ADODB::_RecordsetPtr pRecordset,CString strTableField,CString &strData);

//向数据库写大二进制数据
BOOL ADO_AppendChunk(ADODB::_RecordsetPtr pRecordset,CString strTableField,CString strData);

#endif // !defined(_ADOBaseApp_H__)
