#pragma once
//#include "stdlib.h"
#include <map>
using namespace std;

#ifdef _PSX_QT_LINUX_
#include "../../../../Module/Socket/WinUdpScoket.h"
#else
#include "../../../../Module/Socket/WinUdpScoket.h"
#endif

#include "../../SttProtocolBufBase.h"
#include "SttGlobalMulticastDef.h"


class CSttMulticastClientSocket : public CWinUdpSocket,public CSttProtocolBufBase
{
public:
	CSttMulticastClientSocket();
	virtual ~CSttMulticastClientSocket();

	sockaddr_in m_sktMultiCast;//×é²¥socket
public:
	CSttMulticastMsgViewInterface *m_pSttMulticastMsgViewInterface;
	void AttatchSttMulticastMsgViewInterface(CSttMulticastMsgViewInterface *pSttMulticastMsgViewInterface)
	{
		m_pSttMulticastMsgViewInterface = pSttMulticastMsgViewInterface;
	}

public:
	virtual BOOL Create(const CString &strMultiIP,long nMultiPort,const CString strLocalIP, long nLocalPort=0);
	virtual BOOL Create(const CString &strMultiIP, long nPort,int nType);
	virtual long OnReceive(BYTE *pRcvBuf, int iLen,sockaddr_in* fsockaddr);
	virtual long SendBuffer(BYTE *pBuf, long nLen,sockaddr_in* tsockaddr=NULL);

	virtual void OnClose(int nErrorCode);
	virtual void CloseSocket();
	virtual BOOL ProcessRecvPacket(BYTE *pBuf,long nLen);
	virtual BOOL ProcessRecvPacket(BYTE nCmdType,CSttPpDatasDriver vec);

public:
	//vector<BYTE> m_RetCmdList;
	void AddRetCmd(BYTE nCmd);
	void PopCurRetCmd(BYTE nCmd);

	virtual long Multicast_QueryIP();
	virtual long Multicast_SetIPs(const CString &strTestAppSN,const CString &strTestAppModel
		,BYTE *pIPBuf,BYTE *pMaskBuf,BOOL bIPV4=TRUE);
	virtual long Multicast_SetIPV4s(const CString &strTestAppSN,const CString &strTestAppModel
		,const CString &strIP,const CString &strMask);
	virtual long Multicast_SetIPV4Array(const CString &strTestAppSN,const CString &strTestAppModel
		,const CStringArray &astrIP,const CStringArray &astrMask);
	virtual long Multicast_Process(const CString &strTestAppSN,const CString &strTestAppModel
		,CStringArray &astrProcRun, CStringArray &astrProcClose);
	virtual long Multicast_QueryState(const CString &strTestAppSN,const CString &strTestAppModel);
	virtual long Multicast_QuerySystemCfg(const CString &strTestAppSN,const CString &strTestAppModel);

	virtual long Multicast_CommonACK(BYTE nAckCmd,const CString &strSN,const CString &strModel,int nErrCode);

	virtual BOOL Process_Multicast_QueryIP(CSttPpDatasDriver vec);//{return TRUE;}
	virtual BOOL Process_Multicast_QueryIP_ACK(CSttPpDatasDriver vec){return TRUE;}
	virtual BOOL Process_Multicast_SetIPs(CSttPpDatasDriver vec);//{return TRUE;}
	virtual BOOL Process_Multicast_SetIPs_ACK(CSttPpDatasDriver vec){return TRUE;}
	virtual BOOL Process_Multicast_StartOffProcess(CSttPpDatasDriver vec){return TRUE;}
	virtual BOOL Process_Multicast_StartOffProcess_ACK(CSttPpDatasDriver vec){return TRUE;}
	virtual BOOL Process_Multicast_QueryState(CSttPpDatasDriver vec){return TRUE;}
	virtual BOOL Process_Multicast_QueryState_ACK(CSttPpDatasDriver vec){return TRUE;}
	virtual BOOL Process_Multicast_QuerySystemCfg(CSttPpDatasDriver vec){return TRUE;}

protected:
	long Multicast_Process(BYTE* &pPkg, CStringArray &astrProc, BYTE nDataID);

};
