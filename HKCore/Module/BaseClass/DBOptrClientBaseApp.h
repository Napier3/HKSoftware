#pragma once

#include "../XmlRpc/XmlRpc.h"
#include "../XmlRpc/XmlRpcApi_MFC.h"
#include "../CriticalSection/SynCriticalSection.h"
#include "DBOptrBaseDefine.h"
#include "../System/TickCount32.h"

#define  XMLRPC_RESEND_CNT    1

#define ID_RPCCLIENT_TIMER    1026
#define ID_RPCCLIENT_TIMER_LONG    1000

class CDBOptrClientBaseApp
{
public:
	CDBOptrClientBaseApp();
	virtual ~CDBOptrClientBaseApp();

	//��ʱ�䲻ͬ��������ͨѶ���Ͽ��������������
	void OnTimer(unsigned int nIDEvent);

public:
	//XML RPC Client
	XmlRpc::XmlRpcClient *m_pMngrRpcClient;
	virtual void InitRpcClient(const CString &strIP,int nPort);
	virtual void ExitRpcClient();

private:
	CTickCount32 m_oTickRpcClient;

public:
	CAutoCriticSection m_oRpcClentCriticSection;

	CString m_strIP;
	int m_nPort;

	int m_nClientConnectID;		//�ͻ��˵�¼�����˷�������Ӻ�
	int m_nIndex_LoginUser;		//��¼�û�����

	void SetLoginUserID(int nIndex_User){	m_nIndex_LoginUser = nIndex_User;	}

	// ������ͨ�ŵĽӿ�
	BOOL IsServerExist();
	CString GetServerIP()	{	return m_strIP;	}

public:

	//����
	virtual BOOL DBOptrClient_InsertOptr(int nUserID,int nClientConnectID,CExBaseList& oClientMngrList, 
		CXmlRWKeys *pXmlRWKeys);
	virtual BOOL DBOptrClient_InsertOptr(CExBaseList& oClientMngrList, CXmlRWKeys *pXmlRWKeys);

	//ɾ��
	virtual BOOL DBOptrClient_DeleteOptr(int nUserID,int nClientConnectID,int nExtFlag,CExBaseList& oClientMngrList, 
		CXmlRWKeys *pXmlRWKeys);
	virtual BOOL DBOptrClient_DeleteOptr(int nExtFlag,CExBaseList& oClientMngrList, CXmlRWKeys *pXmlRWKeys);

	//����
	virtual BOOL DBOptrClient_UpdateOptr(int nUserID,int nClientConnectID,CExBaseList& oClientMngrList,
		CXmlRWKeys *pXmlRWKeys);
	virtual BOOL DBOptrClient_UpdateOptr(CExBaseList& oClientMngrList,CXmlRWKeys *pXmlRWKeys);

	//��ѯ
	virtual BOOL  DBOptrClient_QueryOptr(CExBaseList& oClientMngrList,CXmlRWKeys *pXmlRWKeys,int nUserID,
		int nClientConnectID,const CString& strTableName , const CString& strCondition, int nExtFlag,
		int nCurTable, int nInitName);
	virtual BOOL  DBOptrClient_QueryOptr(CExBaseList& oClientMngrList,CXmlRWKeys *pXmlRWKeys
		,const CString& strTableName , const CString& strCondition, int nExtFlag,
		int nCurTable, int nInitName);

	virtual BOOL  DBOptrClient_CommQueryOptr(const CString& strTableName ,const CString& strFilterXml, CString& strResultXml);
	virtual BOOL  DBOptrClient_CommDeleteOptr(const CString& strTableName ,const CString& strFilterXml);
	virtual BOOL  DBOptrClient_CommInsertOptr(const CString& strInsertXml ,BOOL bInsert, BOOL bUpdate, CString& strResultXml);

	//ִ��MySql �������
	BOOL DBOptrClient_ExecSqlCmd(int nUserID, int nClientConnectID,const CString &strSql);
	BOOL DBOptrClient_ExecSqlCmd(const CString &strSql);

	//��Ӧ����������
	virtual BOOL DBOptrClient_ExecFun(const CString &strFunID,const XmlRpc::XmlRpcValue &args,
		XmlRpc::XmlRpcValue &res,double tmOut=-1);
	//����ʵ��������
	virtual void InitAfterExecFun(XmlRpc::XmlRpcValue &res,const CString &strFunID){};
};

extern CDBOptrClientBaseApp *g_pDBOptrClientBaseApp;


inline long DBOptr_GetLoginUserIndex()	{	return g_pDBOptrClientBaseApp->m_nIndex_LoginUser;	}

void OA_LogPrintOptrErrorMsg(const CString &strOptrType);
