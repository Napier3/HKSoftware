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

	//长时间不同服务器端通讯，断开与服务器的连接
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

	int m_nClientConnectID;		//客户端登录后服务端分配的连接号
	int m_nIndex_LoginUser;		//登录用户索引

	void SetLoginUserID(int nIndex_User){	m_nIndex_LoginUser = nIndex_User;	}

	// 与服务端通信的接口
	BOOL IsServerExist();
	CString GetServerIP()	{	return m_strIP;	}

public:

	//插入
	virtual BOOL DBOptrClient_InsertOptr(int nUserID,int nClientConnectID,CExBaseList& oClientMngrList, 
		CXmlRWKeys *pXmlRWKeys);
	virtual BOOL DBOptrClient_InsertOptr(CExBaseList& oClientMngrList, CXmlRWKeys *pXmlRWKeys);

	//删除
	virtual BOOL DBOptrClient_DeleteOptr(int nUserID,int nClientConnectID,int nExtFlag,CExBaseList& oClientMngrList, 
		CXmlRWKeys *pXmlRWKeys);
	virtual BOOL DBOptrClient_DeleteOptr(int nExtFlag,CExBaseList& oClientMngrList, CXmlRWKeys *pXmlRWKeys);

	//更新
	virtual BOOL DBOptrClient_UpdateOptr(int nUserID,int nClientConnectID,CExBaseList& oClientMngrList,
		CXmlRWKeys *pXmlRWKeys);
	virtual BOOL DBOptrClient_UpdateOptr(CExBaseList& oClientMngrList,CXmlRWKeys *pXmlRWKeys);

	//查询
	virtual BOOL  DBOptrClient_QueryOptr(CExBaseList& oClientMngrList,CXmlRWKeys *pXmlRWKeys,int nUserID,
		int nClientConnectID,const CString& strTableName , const CString& strCondition, int nExtFlag,
		int nCurTable, int nInitName);
	virtual BOOL  DBOptrClient_QueryOptr(CExBaseList& oClientMngrList,CXmlRWKeys *pXmlRWKeys
		,const CString& strTableName , const CString& strCondition, int nExtFlag,
		int nCurTable, int nInitName);

	virtual BOOL  DBOptrClient_CommQueryOptr(const CString& strTableName ,const CString& strFilterXml, CString& strResultXml);
	virtual BOOL  DBOptrClient_CommDeleteOptr(const CString& strTableName ,const CString& strFilterXml);
	virtual BOOL  DBOptrClient_CommInsertOptr(const CString& strInsertXml ,BOOL bInsert, BOOL bUpdate, CString& strResultXml);

	//执行MySql 命令语句
	BOOL DBOptrClient_ExecSqlCmd(int nUserID, int nClientConnectID,const CString &strSql);
	BOOL DBOptrClient_ExecSqlCmd(const CString &strSql);

	//响应服务器函数
	virtual BOOL DBOptrClient_ExecFun(const CString &strFunID,const XmlRpc::XmlRpcValue &args,
		XmlRpc::XmlRpcValue &res,double tmOut=-1);
	//子类实例化处理
	virtual void InitAfterExecFun(XmlRpc::XmlRpcValue &res,const CString &strFunID){};
};

extern CDBOptrClientBaseApp *g_pDBOptrClientBaseApp;


inline long DBOptr_GetLoginUserIndex()	{	return g_pDBOptrClientBaseApp->m_nIndex_LoginUser;	}

void OA_LogPrintOptrErrorMsg(const CString &strOptrType);
