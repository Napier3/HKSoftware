#include "stdafx.h"
#include "XmlRpcServerThreadBase.h"

#include "..\..\Module\System\TickCount32.h"

using namespace XmlRpc;
using namespace std;


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CXmlRpcServerThreadBase::CXmlRpcServerThreadBase()
{
    
}

CXmlRpcServerThreadBase::~CXmlRpcServerThreadBase()
{
	
}

void CXmlRpcServerThreadBase::InitXmlRpcServerThread(const CString &strServerIP, UINT nServerPort)
{
	//call register methods
    RegisterMethods();

    //set port bind and listen
    int port = 9998;
	port = nServerPort;
    bool ret = false;
	char pszIP[32];
	pszIP[0] = 0;
	CString_to_char(strServerIP, pszIP);

	CString strRet = _T("成功");
	ret = m_oXmlRpcServer.bindAndListen(pszIP, port);
	if(ret == FALSE)
	{
		strRet = _T("失败");
	}
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("XmlRpc Server【%s,%d】创建%s")
		,strServerIP,port,strRet);


	m_pXmlRpcServerThread = AfxBeginThread(XmlRpcServerThread, this);
	m_pXmlRpcServerThread->m_bAutoDelete = TRUE;
}

void CXmlRpcServerThreadBase::run()
{
#ifdef _DEBUG
	XmlRpc::XmlRpcUtil::log(1,"start run");
#endif
    m_oXmlRpcServer.work(-1);

	int i = 0;
}

void CXmlRpcServerThreadBase::exit()
{
	m_oXmlRpcServer.shutdown();
	m_oXmlRpcServer.close();
	m_oXmlRpcServer.exit();

	CTickCount32 oTick;
	while (m_pXmlRpcServerThread != NULL)
	{
		oTick.DoEvents(50);
	}
}

UINT CXmlRpcServerThreadBase::XmlRpcServerThread(LPVOID pPara)
{
	if (!AfxOleInit())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("AfxOleInit() 错误。"));
		return 1;
	}

	CXmlRpcServerThreadBase* pTemp = (CXmlRpcServerThreadBase*)pPara;
	pTemp->run();
	pTemp->m_pXmlRpcServerThread = NULL;

	return 0;
}