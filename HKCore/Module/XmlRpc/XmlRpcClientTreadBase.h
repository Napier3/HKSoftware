#ifndef _XmlRpcClientTreadBase_h__
#define _XmlRpcClientTreadBase_h__

#include "XmlRpc.h"

class CXmlRpcClientCmdBase
{
public:
	CXmlRpcClientCmdBase()
	{
		m_pDataRef = NULL;
		m_nCmdID = 0;
		m_strCmdID = _T("");
		m_strMsg = _T("");
	}
	virtual ~CXmlRpcClientCmdBase()
	{

	}

public:
	CExBaseObject *m_pDataRef;
	UINT m_nCmdID;
	CString m_strCmdID;
	CString m_strMsg;
};


class CXmlRpcClientTreadBase : public CWinThread
{
	DECLARE_DYNCREATE(CXmlRpcClientTreadBase)

public:
	CXmlRpcClientTreadBase();           // 动态创建所使用的受保护的构造函数
	virtual ~CXmlRpcClientTreadBase();

 	void InitXmlRpcClient(const CString &strServerIP, UINT nPort);
	virtual void OnRpcCmdCall(CXmlRpcClientCmdBase *pCmd) {};

protected:
 	XmlRpc::XmlRpcClient *m_pXmlRpcClient;

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnRpcCmdCall(WPARAM wParam,LPARAM lParam);
};


#endif
