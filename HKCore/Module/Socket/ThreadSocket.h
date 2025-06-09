#if !defined(_THREAD_SOCKET_H__)
#define _THREAD_SOCKET_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThreadSocket.h : header file
//
#include <winsock2.h>
#include <winsock.h>

#define WM_TCPIP (WM_USER+1109)
#include "..\BaseClass\TLinkList.h"
#include "..\MemBuffer\CycleMemBuffer.h"
#define RECEIVEBUFFER_LENGTH    10240
/////////////////////////////////////////////////////////////////////////////
// CThreadSocket window

class CThreadSocket : public CWnd
{
// Construction
public:
	CThreadSocket();

// Attributes
public:
	SOCKET m_hSocket;
	unsigned long m_nIPAddr;
	int m_nSocketPort;

	CCycleMemBuffer m_oBufferReceive;
	CCycleMemBuffer m_oBufferSend;
	
// Operations
protected:
	virtual void OnAccept()    {}	
	virtual void OnClose()     {}
	virtual long OnReceive();
	
public:
	BOOL CreateOwnSocket(char* lpszSocketAddress = NULL, UINT nSocketPort = 0, int nSocketType = SOCK_STREAM, int nProtocol=0);
	BOOL ListenOwnSocket();
	BOOL ConnectOwnSocket(char* lpszHostAddress, UINT nHostPort);
	void CloseOwnSocket();
	void Close();
	int SendOwnSocket(const void* lpBuf, int nBufLen, int nFlags = 0);
	int SendOwnSocket(int nFlags = 0);
	virtual int ReceiveOwnSocket(void* lpBuf, int nBufLen, int nFlags = 0);
	BOOL AcceptOwnSocket(CThreadSocket& rConnectedSocket, SOCKADDR* lpSockAddr = NULL, int* lpSockAddrLen = NULL);
	
	BOOL GetPeerName(CString& rPeerAddress, UINT& rPeerPort);//获取与套接口相连的端地址
	BOOL GetPeerName(SOCKADDR* lpSockAddr, int* lpSockAddrLen);
	
	BOOL GetSockName(CString& rSocketAddress, UINT& rSocketPort);
	BOOL GetSockName(SOCKADDR* lpSockAddr, int* lpSockAddrLen);

	CCycleMemBuffer* GetReceiveBuffer()    {     return &m_oBufferReceive;               }
	CCycleMemBuffer* GetSendBuffer()       {     return &m_oBufferSend;                  }
	BYTE* GetReceiveBuffer2()              {     return m_oBufferReceive.GetBuffer();    }
	BYTE* GetSendBuffer2()                 {     return m_oBufferSend.GetBuffer();       }
	
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThreadSocket)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CThreadSocket();

	// Generated message map functions
protected:
	//{{AFX_MSG(CThreadSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg LRESULT OnTCPIP(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

inline BOOL CThreadSocket::GetPeerName(SOCKADDR* lpSockAddr, int* lpSockAddrLen)
{ return (SOCKET_ERROR != getpeername(m_hSocket, lpSockAddr, lpSockAddrLen)); }
inline BOOL CThreadSocket::GetSockName(SOCKADDR* lpSockAddr, int* lpSockAddrLen)
{ return (SOCKET_ERROR != getsockname(m_hSocket, lpSockAddr, lpSockAddrLen)); }


class CThreadSocketList
{
public:
	CThreadSocketList();
	virtual ~CThreadSocketList();

	typedef CTLinkList<CThreadSocket> CSocketList;

protected:
	CSocketList m_listChild;
	
public:
	long GetCount()                        {   return m_listChild.GetCount();      }
	CThreadSocket* GetAt(int nIndex)       {   return m_listChild.GetAt(nIndex);   }
	POS AddTail(CThreadSocket *pData)    {   return m_listChild.AddNode(pData);  }
	POS AddHead(CThreadSocket *pData)    {   return m_listChild.AddHead(pData);  }
	POS InsertBefore(POS pos, CThreadSocket *pData)    {   return m_listChild.InsertBefore(pos, pData);    }
	POS InsertAfter(POS pos, CThreadSocket *pData)     {   m_listChild.InsertAfter(pos, pData);            }
	void RemoveAll()                       {   m_listChild.RemoveAll();                 }
	CThreadSocket* RemoveAt(int nIndex)    {   return m_listChild.RemoveAt(nIndex);     }
	CThreadSocket* RemoveAt(POS pos)     {   return m_listChild.RemoveAt(pos);        }
	void DeleteAll()                       {   m_listChild.DeleteAll();                 }
	void DeleteAt(int nIndex)              {   m_listChild.DeleteAt(nIndex);            }
	void DeleteHead()                      {   m_listChild.DeleteHead();                }
	void DeleteTail()                      {   m_listChild.DeleteTail();                }
	CThreadSocket* GetHead()               {   return m_listChild.GetHead();            }
	CThreadSocket* GetTail()               {   return m_listChild.GetTail();            }
	POS GetHeadPosition()                {   return m_listChild.GetHeadPosition();    }
	POS GetTailPosition()                {   return m_listChild.GetTailPosition();    }
	CThreadSocket* GetNext(POS &pos)     {   return m_listChild.GetNext(pos);         }
	CThreadSocket* GetAt(POS pos)        {   return m_listChild.GetAt(pos);           }
	POS FindByIndex(int nIndex)          {   return m_listChild.FindIndex(nIndex);  }
	POS Find(CThreadSocket *pObj)        {   return m_listChild.Find(pObj);           }
	void BringToTail(long nIndex)		   {   return m_listChild.BringToTail(nIndex);		}
	void BringToHead(long nIndex)           {   return m_listChild.BringToHead(nIndex);	    }
	void ChangePos(POS pos1, POS pos2){   return m_listChild.ChangePosition(pos1, pos2);}

	CThreadSocket* FindByIP(const char* pstrIP, UINT nPort);
	CThreadSocket* FindByIP(DWORD dwIP, UINT nPort);
	CThreadSocket* FindByIP(BYTE b1, BYTE b2, BYTE b3, BYTE b4, UINT nPort);	
};

//发送的数据包的数据起始位置,数据长度
typedef struct ThrdScktSndMsg
{
	CThreadSocket *pSocket;
	DWORD dwDataBeginPos;
	DWORD dwDataLen;
}* PTHRDSCKTSNDMSG , THRDSCKTSNDMSG;

inline PTHRDSCKTSNDMSG CreateThrdScktSndMsg()
{
	PTHRDSCKTSNDMSG pMsg = (PTHRDSCKTSNDMSG)malloc(sizeof(THRDSCKTSNDMSG));
	memset(pMsg, 0, sizeof(THRDSCKTSNDMSG));
	return pMsg;
}

inline PTHRDSCKTSNDMSG CreateThrdScktSndMsg(CThreadSocket *pSocket, DWORD dwDataBeginPos, DWORD dwDataLen)
{
	PTHRDSCKTSNDMSG pMsg = (PTHRDSCKTSNDMSG)malloc(sizeof(THRDSCKTSNDMSG));
	pMsg->pSocket = pSocket;
	pMsg->dwDataBeginPos = dwDataBeginPos;
	pMsg->dwDataLen = dwDataLen;
	return pMsg;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_THREAD_SOCKET_H__)
