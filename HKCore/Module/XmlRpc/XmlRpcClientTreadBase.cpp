// XmlRpcClientTreadBase.cpp : 实现文件
//

#include "stdafx.h"
#include "XmlRpcClientTreadBase.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

#define WM_EXEC_ATS_CMD  (WM_USER + 345)

IMPLEMENT_DYNCREATE(CXmlRpcClientTreadBase, CWinThread)

CXmlRpcClientTreadBase::CXmlRpcClientTreadBase()
{
	m_pXmlRpcClient = NULL;
}

CXmlRpcClientTreadBase::~CXmlRpcClientTreadBase()
{
	m_pXmlRpcClient->close();
	delete m_pXmlRpcClient;
}

void CXmlRpcClientTreadBase::InitXmlRpcClient(const CString &strServerIP, UINT nPort)
{
	m_pXmlRpcClient = new XmlRpc::XmlRpcClient(strServerIP, nPort, NULL);
}

BEGIN_MESSAGE_MAP(CXmlRpcClientTreadBase, CWinThread)
	ON_THREAD_MESSAGE(WM_EXEC_ATS_CMD, OnRpcCmdCall)
END_MESSAGE_MAP()


void CXmlRpcClientTreadBase::OnRpcCmdCall(WPARAM wParam,LPARAM lParam)
{
	CXmlRpcClientCmdBase *pCmd = (CXmlRpcClientCmdBase*)wParam;
	OnRpcCmdCall(pCmd );
	delete pCmd;
}
