#pragma once

#include "XUserTcpClientBase.h"
#include "ServerUserListCtrl.h"

class CXUserTcpServer;

class CXUserTcpServerClientObject : public CExBaseObject
{
public:
	CXUserTcpServerClientObject()
	{
		m_nReotePort = 0;
		m_nLocalPort = 0;
		m_pCurrUser = NULL;
	};
	virtual ~CXUserTcpServerClientObject(){};

	CXUser *m_pCurrUser;
	CString m_strRemoteIp;
	UINT m_nReotePort;
	UINT m_nLocalPort;
	CString m_strModule;

	void SetModuleID(UINT nModuleID)
	{
		switch (nModuleID)
		{
		case FETUREID_AUTOTEST://     100
			m_strModule = _T("�Զ�����ģ��");
			break;

		case FETUREID_RPTDEV://       101
			m_strModule = _T("����ģ��༭");
			break;

		case FETUREID_GBDEV://        102
			m_strModule = _T("����ģ��༭");
			break;

		case FETUREID_STXML://        103
			m_strModule = _T("��ģ��༭");
			break;

		case FETUREID_PPDEV://        104
			m_strModule = _T("��ͳ��Լ����");
			break;

		case FETUREID_PPENGINE://     105
			m_strModule = _T("��ͳ��Լ����");
			break;

		case FETUREID_MMSENGINE://    106
			m_strModule = _T("MMS��Լ����");
			break;

		case FETUREID_ATSREGISTER://  107
			m_strModule = _T("ע��������");
			break;
		
		default:
			m_strModule = _T("δ֪ģ��");
		}

	}
};

class CXUserTcpServerClient : public CXUserTcpClientBase
{
public:
	CXUserTcpServerClient(void);
	virtual ~CXUserTcpServerClient(void);
	
	CXUserTcpServer *m_pServerRef;
	CXUserTcpServerClientObject *m_pObjectRef;

public:
	virtual void OnClose(int nErrorCode);

protected:
	virtual BOOL ProcessXUserCmd(CDvmData *pData);

	BOOL ProcessXUserCmd_Login(CDvmData *pData);
	BOOL ProcessXUserCmd_Logout(CDvmData *pData);
	BOOL ProcessXUserCmd_GetInfor(CDvmData *pData);
	BOOL ProcessXUserCmd_HasFetureID(CDvmData *pData);
};

typedef CTLinkListEx<CXUserTcpServerClient>  CXUserTcpServerClientList;

class CXUserTcpServer : public CSocket
{
public:
	CXUserTcpServer(void);
	virtual ~CXUserTcpServer(void);

	CXUserTcpServerClientList m_listTcpClient;
	CExBaseList m_listClientObject;
	CServerUserListCtrl *m_pListCtrlRef;

public:
	virtual BOOL CreateServer(const CString &strIP, UINT nPort);
	virtual BOOL CloseServer();
	virtual BOOL IsServerClosed();

	virtual void OnAccept(int nErrorCode);
	void CloseTcpClient(CXUserTcpServerClient *pSockt);
	void UpdateTcpClient(CXUserTcpServerClient *pSockt);
};
