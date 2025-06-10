#pragma once

#include "SttMulticastClientSocket.h"
#include "../../SttCmd/SttParas.h"

class CSttMulticastServerSocket : public CSttMulticastClientSocket
{
public:
	CSttMulticastServerSocket();
	virtual ~CSttMulticastServerSocket();

	//服务端口一启动，需更新序列号和型号
	CString m_strSN;
	CString m_strModel;
	CString m_strLocalIP;
	CString m_strLocalMASK;

	void SetLocalNetInfo(CString strLocalIP,CString strLocalMASK){m_strLocalIP=strLocalIP;
																m_strLocalMASK=strLocalMASK;}

	void SetDeviceInfo(CString strSN,CString strModel){m_strSN=strSN;
																m_strModel=strModel;}
public:
//	virtual BOOL ProcessRecvPacket(BYTE *pBuf,long nLen);

	BOOL CheckMatchSN(CSttPpDatasDriver vec);
	virtual BOOL Process_Multicast_QueryIP(CSttPpDatasDriver vec);
	virtual BOOL Process_Multicast_SetIPs(CSttPpDatasDriver vec);
	virtual BOOL Process_Multicast_StartOffProcess(CSttPpDatasDriver vec);
	virtual BOOL Process_Multicast_QueryState(CSttPpDatasDriver vec);
	virtual BOOL Process_Multicast_QuerySystemCfg(CSttPpDatasDriver vec);
};
