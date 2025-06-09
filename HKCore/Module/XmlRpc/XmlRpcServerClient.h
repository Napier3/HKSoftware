
#ifndef _XmlRpcServerClient_H_
#define _XmlRpcServerClient_H_
//
// XmlRpc++ Copyright (c) 2002-2003 by Chris Morley
//
#if defined(_MSC_VER)
# pragma warning(disable:4786)    // identifier was truncated in debug info
#endif


#ifndef MAKEDEPEND
# include <string>
#endif

#include "XmlRpcDispatch.h"
#include "XmlRpcSource.h"

namespace XmlRpc
{

	// Arguments and results are represented by XmlRpcValues
	class XmlRpcValue;
	class XmlRpcServerConnection;
	class XmlRpcServer;

	//2019-04-30  服务端，改为多线程，server为一个线程、每个client的连接为一个线程
	class XmlRpcServerClient : public XmlRpcSource
	{
	public:
		XmlRpcServerClient(XmlRpcServerConnection *pServerConnection, unsigned eventMask);
		virtual ~XmlRpcServerClient();

		XmlRpcServerConnection *m_pServerConnection;
		XmlRpcServer *m_pXmlRpcServerRef;

		bool execute();

		virtual unsigned handleEvent(unsigned eventType)	{	return 0;	}

		// XmlRpcSource interface implementation
		//! Close the connection
		virtual void close();

		// Event dispatcher
		XmlRpcDispatch _disp;

		void begin_Client_Thread();

	private:
        #ifndef _PSX_IDE_QT_
                static DWORD WINAPI Client_Thread(LPVOID);
        #else
                static DWORD Client_Thread(LPVOID);
        #endif
		HANDLE m_hClient_Thread;
		DWORD  m_dwClient_ThreadID;
	};	// class XmlRpcServerClient

	typedef std::list< XmlRpcServerClient* > XmlRpcServerClientList; 

}	// namespace XmlRpc

#endif	// _XmlRpcServerClient_H_
