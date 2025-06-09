#include "stdafx.h"
#include "DBOptrClientBaseApp.h"
#include "../Socket/XPing.h"

CDBOptrClientBaseApp *g_pDBOptrClientBaseApp = NULL;

CDBOptrClientBaseApp::CDBOptrClientBaseApp()
{
	m_nPort = 0;

	m_nClientConnectID = 0;
	m_nIndex_LoginUser = 0;
}

CDBOptrClientBaseApp::~CDBOptrClientBaseApp()
{
}

void CDBOptrClientBaseApp::InitRpcClient(const CString &strIP,int nPort)
{
	char *server;
	const char *uri = NULL;

	CString_to_char(strIP, &server);

	m_oTickRpcClient.Enter();
	m_pMngrRpcClient = new XmlRpc::XmlRpcClient(server, nPort, uri);

	m_strIP = strIP;
	m_nPort = nPort;

	delete server;
}

BOOL CDBOptrClientBaseApp::IsServerExist()
{
	char* pszIP = NULL;
	CString_to_char(m_strIP,&pszIP);

	BOOL bConnect = xping(pszIP);
	delete pszIP;

	if (!bConnect)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("测试服务器：%s 网络连接不通！"),m_strIP.GetString());
	}

	return bConnect;
}

void CDBOptrClientBaseApp::ExitRpcClient()
{
	if (m_pMngrRpcClient)
	{
		delete m_pMngrRpcClient;
		m_pMngrRpcClient = NULL;
	}
}

void CDBOptrClientBaseApp::OnTimer(unsigned int nIDEvent)
{
	if (ID_RPCCLIENT_TIMER != nIDEvent)
	{
		return;
	}

	if (m_oTickRpcClient.GetTickCountLong(FALSE) >= 20000)
	{
#ifdef _DEBUG
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("长时间没使用，断开连接  m_pMngrRpcClient->close()"));
#endif

		m_oTickRpcClient.Enter();

		CAutoSimpleLock oLock(m_oRpcClentCriticSection);
		m_pMngrRpcClient->close();	
	}
}


BOOL CDBOptrClientBaseApp::DBOptrClient_ExecFun(const CString &strFunID,
												const XmlRpc::XmlRpcValue &args,XmlRpc::XmlRpcValue &res,double tmOut)
{
	if (tmOut < 20)
	{
		tmOut = 20;
	}
	BOOL bRet = FALSE;
	long nCount = 1;
	CTickCount32 oTickCount32;
	CAutoSimpleLock oLock(m_oRpcClentCriticSection); 

	while (nCount <= XMLRPC_RESEND_CNT)
	{
		//yyj
#ifndef _PSX_IDE_QT_
		bRet = m_pMngrRpcClient->execute(strFunID, args, res, tmOut);
#else
		char* pstrFuncID;
		CString_to_char(strFunID,&pstrFuncID);
		bRet = m_pMngrRpcClient->execute(pstrFuncID, args, res, tmOut);
#endif

		nCount++;
		if (bRet)
		{
			InitAfterExecFun(res,strFunID);
			m_oTickRpcClient.Enter();
			break;
		}
		else
		{
			oTickCount32.DoEvents(100);
		}
	}

	return bRet;
}

/*插入操作*/
BOOL CDBOptrClientBaseApp::DBOptrClient_InsertOptr(int nUserID,int nClientConnectID,CExBaseList& oClientMngrList, CXmlRWKeys *pXmlRWKeys)
{
	XmlRpc::XmlRpcValue args, res;
	args[0] = nUserID;
	ExBaseObject_to_XmlRpcValue(oClientMngrList,args[1],pXmlRWKeys);
	args[2] = nClientConnectID;

	try
	{
		BOOL bRet = DBOptrClient_ExecFun(DBOptrBase_Method_Insert, args , res , 20);
		if (!bRet)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("插入操作失败。"));
			return FALSE;
		}
		int nRet = res[0];
		if ((nRet == 0) || (nRet == 2))
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("插入操作失败。"));
			return FALSE;
		}

		oClientMngrList.DeleteAll();
		XmlRpcValue_to_ExBaseObject(res[1],oClientMngrList,pXmlRWKeys);
		return TRUE;
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("插入操作失败。"));
		return FALSE;
	}
	return FALSE;
}

BOOL CDBOptrClientBaseApp::DBOptrClient_InsertOptr(CExBaseList& oClientMngrList, CXmlRWKeys *pXmlRWKeys)
{
	return DBOptrClient_InsertOptr(m_nIndex_LoginUser, m_nClientConnectID,oClientMngrList,pXmlRWKeys);
}

/*删除操作*/
BOOL CDBOptrClientBaseApp::DBOptrClient_DeleteOptr(int nUserID,int nClientConnectID,int nExtFlag,CExBaseList& oClientMngrList, CXmlRWKeys *pXmlRWKeys)
{
	XmlRpc::XmlRpcValue args, res;

	args[0] = nUserID;
	ExBaseObject_to_XmlRpcValue(oClientMngrList,args[1],pXmlRWKeys);
	args[2] = nExtFlag;
	args[3] = nClientConnectID;

	try
	{
		BOOL bRet = DBOptrClient_ExecFun(DBOptrBase_Method_Delete, args, res,20);
		if (!bRet)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("删除操作失败。"));
			return FALSE;
		}
		int nRet = res[0];
		if ((nRet == 0) || (nRet == 2))
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("删除操作失败。"));
			return FALSE;
		}
		return TRUE;
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("删除操作失败。"));
		return FALSE;
	}
	return FALSE;
}

BOOL CDBOptrClientBaseApp::DBOptrClient_DeleteOptr(int nExtFlag,CExBaseList& oClientMngrList, CXmlRWKeys *pXmlRWKeys)
{
	return DBOptrClient_DeleteOptr(m_nIndex_LoginUser,m_nClientConnectID,nExtFlag,oClientMngrList,pXmlRWKeys);
}

/*更新操作*/
BOOL CDBOptrClientBaseApp::DBOptrClient_UpdateOptr(int nUserID,int nClientConnectID,CExBaseList& oClientMngrList,CXmlRWKeys *pXmlRWKeys)
{
	XmlRpc::XmlRpcValue args, res;

	args[0] = nUserID;
	ExBaseObject_to_XmlRpcValue(oClientMngrList,args[1],pXmlRWKeys);
	args[2] = nClientConnectID;

	try
	{
		BOOL bRet = DBOptrClient_ExecFun(DBOptrBase_Method_Update, args, res, 3);
		if (!bRet)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("编辑操作失败。"));
			return FALSE;
		}
		int nRet = res[0];
		if ((nRet == 0) || (nRet == 2))
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("编辑操作失败。"));
			return FALSE;
		}
		return TRUE;
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("编辑操作失败。"));
		return FALSE;
	}
	return FALSE;
}

BOOL CDBOptrClientBaseApp::DBOptrClient_UpdateOptr(CExBaseList& oClientMngrList,CXmlRWKeys *pXmlRWKeys)
{
	return DBOptrClient_UpdateOptr(m_nIndex_LoginUser,m_nClientConnectID,oClientMngrList,pXmlRWKeys);
}

/*查询操作*/
BOOL CDBOptrClientBaseApp::DBOptrClient_QueryOptr(CExBaseList& oClientMngrList,CXmlRWKeys *pXmlRWKeys,int nUserID,
												  int nClientConnectID,const CString& strTableName , const CString& strCondition,
												  int nExtFlag ,int nCurTable, int nInitName)
{
	XmlRpc::XmlRpcValue args, res;

	args[0] = nUserID;

	if (strTableName.GetLength() == 0)
	{
		CString strTable;
		strTable = oClientMngrList.DB_GetOwnTableName(NULL);
		String_To_XmlRpcValue(strTable,args[1]);
	}
	else
	{
		String_To_XmlRpcValue(strTableName,args[1]);
	}

	String_To_XmlRpcValue(strCondition,args[2]);

	int nExtend = 0;
	if (nCurTable == 0 )
	{
		nExtend |= QUERY_EX_D0_CUR_TABLE;
	}
	if (nExtFlag != 0 )
	{
		nExtend |= QUERY_EX_D1_CHILD_TABLE;
	}
	if (nInitName != 0 )
	{
		nExtend |= QUERY_EX_D2_RELATION_INFO;
	}
	args[3] = nExtend;
	args[4] = nClientConnectID;
	try
	{
		BOOL bRet = DBOptrClient_ExecFun(DBOptrBase_Method_Query, args, res, 5);
		if (!bRet)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("查询操作失败。"));
			return FALSE;
		}
		int nRet = res[0];
		if ((nRet == 0) || (nRet == 2))
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("查询操作失败。"));
			return FALSE;
		}

		oClientMngrList.DeleteAll();
		XmlRpcValue_to_ExBaseObject(res[1],oClientMngrList,pXmlRWKeys);
		return TRUE;
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("查询操作失败。"));
		return FALSE;
	}
	return FALSE;
}

BOOL CDBOptrClientBaseApp::DBOptrClient_QueryOptr(CExBaseList& oClientMngrList,CXmlRWKeys *pXmlRWKeys
												  ,const CString& strTableName , const CString& strCondition,
												  int nExtFlag ,int nCurTable, int nInitName)
{
	return DBOptrClient_QueryOptr(oClientMngrList,pXmlRWKeys,m_nIndex_LoginUser
		,m_nClientConnectID,strTableName , strCondition,nExtFlag ,nCurTable, nInitName);
}

BOOL CDBOptrClientBaseApp::DBOptrClient_CommQueryOptr(const CString& strTableName ,const CString& strFilterXml, CString& strResultXml)
{
	if (strTableName.GetLength() == 0)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("通用查询表名为空。"));
		return FALSE;
	}

	XmlRpc::XmlRpcValue args, res;

	args[0] = m_nIndex_LoginUser;
	String_To_XmlRpcValue(strTableName,args[1]);
	String_To_XmlRpcValue(strFilterXml,args[2]);

	try
	{
		BOOL bRet = DBOptrClient_ExecFun(DBOptrBase_Method_CommQuery, args, res, 5);
		if (!bRet)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("通用查询操作失败。"));
			return FALSE;
		}
		int nRet = res[0];
		if ((nRet == 0) || (nRet == 2))
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("通用查询操作失败。"));
			return FALSE;
		}

		XmlRpcValue_To_String(res[1],strResultXml);
		return TRUE;
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("通用查询操作失败。"));
		return FALSE;
	}
	return FALSE;
}

BOOL CDBOptrClientBaseApp::DBOptrClient_CommDeleteOptr(const CString& strTableName ,const CString& strFilterXml)
{
	if (strTableName.GetLength() == 0)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("通用删除表名为空。"));
		return FALSE;
	}

	XmlRpc::XmlRpcValue args, res;

	args[0] = m_nIndex_LoginUser;
	String_To_XmlRpcValue(strTableName,args[1]);
	String_To_XmlRpcValue(strFilterXml,args[2]);

	try
	{
		BOOL bRet = DBOptrClient_ExecFun(DBOptrBase_Method_CommDelete, args, res, 5);
		if (!bRet)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("通用删除操作失败。"));
			return FALSE;
		}
		int nRet = res[0];
		if ((nRet == 0) || (nRet == 2))
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("通用删除操作失败。"));
			return FALSE;
		}

		return TRUE;
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("通用删除操作失败。"));
		return FALSE;
	}
	return FALSE;
}

BOOL CDBOptrClientBaseApp::DBOptrClient_CommInsertOptr(const CString& strInsertXml ,BOOL bInsert, BOOL bUpdate, CString& strResultXml)
{
	ASSERT(!strInsertXml.IsEmpty());
	XmlRpc::XmlRpcValue args, res;

	args[0] = m_nIndex_LoginUser;
	String_To_XmlRpcValue(strInsertXml,args[1]);
	args[2] = bInsert;
	args[3] = bUpdate;

	try
	{
		BOOL bRet = DBOptrClient_ExecFun(DBOptrBase_Method_CommInsert, args, res, 5);
		if (!bRet)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("通用插入操作失败。"));
			return FALSE;
		}
		int nRet = res[0];
		if ((nRet == 0) || (nRet == 2))
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("通用插入操作失败。"));
			return FALSE;
		}

		XmlRpcValue_To_String(res[1],strResultXml);
		return TRUE;
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("通用插入操作失败。"));
		return FALSE;
	}
	return FALSE;
}

BOOL CDBOptrClientBaseApp::DBOptrClient_ExecSqlCmd(int nUserID, int nClientConnectID,const CString &strSql)
{
	XmlRpc::XmlRpcValue args, res;

	args[0] = nUserID;
	String_To_XmlRpcValue(strSql,args[1]);
	args[2] = m_nClientConnectID;

	try
	{
		BOOL bRet = DBOptrClient_ExecFun(DBOptrBase_Method_ExecSqlCmd, args, res, 3);

		if (!bRet)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("执行数据库命令失败。"));
			return FALSE;
		}

		int nRet = res[0];
		if ((nRet == 0) || (nRet == 2))
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("执行数据库命令失败。"));
			return FALSE;
		}

		return TRUE;
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("执行数据库命令失败。"));
		return FALSE;
	}

	return FALSE;
}

BOOL CDBOptrClientBaseApp::DBOptrClient_ExecSqlCmd(const CString &strSql)
{
	return DBOptrClient_ExecSqlCmd(m_nIndex_LoginUser,m_nClientConnectID,strSql);
}

////////////////////////////////////////////////////

void OA_LogPrintOptrErrorMsg(const CString &strOptrType)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s失败。如果再次操作失败，请联系系统管理员解决问题！"), strOptrType.GetString());
}
