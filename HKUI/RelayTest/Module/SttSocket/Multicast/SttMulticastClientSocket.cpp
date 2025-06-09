#include "stdafx.h"

#include "SttMulticastClientSocket.h"
#include <algorithm>

#ifndef _PSX_QT_LINUX_
#include <ws2ipdef.h>
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttMulticastClientSocket::CSttMulticastClientSocket()
{
	m_pSttMulticastMsgViewInterface = NULL;
}

CSttMulticastClientSocket::~CSttMulticastClientSocket()
{

}

BOOL CSttMulticastClientSocket::Create(const CString &strMultiIP, long nPort,int nType)
{
	char pszMultiIP[64] = {0};

	CString_to_char(strMultiIP,pszMultiIP);


	BOOL bRet = CreateMulticastClientEx(pszMultiIP, nPort,nType);

	if (bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("组播初始化[%s][%d]成功"), pszMultiIP, nPort);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("组播初始化[%s][%d]失败"), pszMultiIP, nPort);
	}

	return bRet;
}

BOOL CSttMulticastClientSocket::Create(const CString &strMultiIP,long nMultiPort,const CString strLocalIP, long nLocalPort)
{
	char pszMultiIP[64] = {0};
	char pszLocalIP[64] = {0};
	CString_to_char(strMultiIP,pszMultiIP);
	CString_to_char(strLocalIP,pszLocalIP);

#ifdef _PSX_QT_LINUX_
	BOOL bRet = CreateMulticastServerEx(pszMultiIP,pszLocalIP, nMultiPort);

	if (bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("组播初始化[%s][%d]成功"), pszMultiIP, nMultiPort);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("组播初始化[%s][%d]失败"), pszMultiIP, nMultiPort);
	}

	return bRet;
#else
	//组播服务端localPort==multiPort
	if (!CreateServer(pszLocalIP, nLocalPort))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("组播服务初始化[%s][%d]失败"), pszLocalIP, nLocalPort);
		return FALSE;
	}

	int loop=0;//1-接送自发消息 0-不接收自发消息
	int bRet = setsockopt(m_hSocket,IPPROTO_IP,IP_MULTICAST_LOOP,(char *)(&loop),sizeof(loop));

	set_ReceiveTimeout(200);

	ip_mreq multiCast; 
	multiCast.imr_interface.s_addr = /*INADDR_ANY*/inet_addr(pszLocalIP); 
	multiCast.imr_multiaddr.s_addr = inet_addr(pszMultiIP); 
	setsockopt(m_hSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&multiCast, sizeof(multiCast)); 

	
	//组播地址定义
	m_sktMultiCast.sin_family = AF_INET;
	Socket_InitSocketAddr(m_sktMultiCast, pszMultiIP, nMultiPort);

// 	BOOL bEnable = FALSE;
// 	setsockopt(m_hSocket,SOL_SOCKET,SO_BROADCAST,(char *)&bEnable,sizeof(BOOL));

	CreateThead();

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("组播初始化[%s][%d]成功，绑定本地IP[%s]"), pszMultiIP, nMultiPort,pszLocalIP);

	return TRUE;
#endif
}

long CSttMulticastClientSocket::OnReceive(BYTE *pRcvBuf, int iLen,sockaddr_in* fsockaddr)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("CSttMulticastClientSocket::OnReceive:[%d]"),iLen);
	if(m_pSttMulticastMsgViewInterface != NULL)
	{
		m_pSttMulticastMsgViewInterface->OnMulticastReceiveMsg(pRcvBuf, iLen,fsockaddr);
	}

	OnReceiveBuffer(pRcvBuf, iLen);
	return 0;
}

long CSttMulticastClientSocket::SendBuffer(BYTE *pBuf, long nLen,sockaddr_in* tsockaddr)
{
	return Send((char*)pBuf, nLen,tsockaddr);
}

void CSttMulticastClientSocket::OnClose(int nErrorCode)
{
	if(m_pSttMulticastMsgViewInterface != NULL)
	{
		m_pSttMulticastMsgViewInterface->OnStopMulticastMsg();
	}
}

void CSttMulticastClientSocket::CloseSocket()
{
	Close();
}

BOOL CSttMulticastClientSocket::ProcessRecvPacket(BYTE *pBuf,long nLen)
{
	BYTE nCmdType = (BYTE)stt_pkg_get_cmd_type(pBuf);

	long nReadPos = STT_PKG_INDEX_DATA;
	BYTE *pPos = pBuf + STT_PKG_INDEX_DATA;
	CSttPpDatasDriver oDriver;
	CSttPpDatas *pDatas = oDriver.CreateDatas();
	stt_pp_pkt_parse_pp_datas(pPos, nLen - STT_PKG_INDEX_DATA, pDatas);
	ProcessRecvPacket(nCmdType,oDriver);
	
	return TRUE;
}

BOOL CSttMulticastClientSocket::ProcessRecvPacket(BYTE nCmdType,CSttPpDatasDriver vec)
{
	if (m_pSttMulticastMsgViewInterface != NULL)
	{
		m_pSttMulticastMsgViewInterface->OnProcessDataMsg(nCmdType,vec);
	}

	BOOL bRet = FALSE;
	switch (nCmdType)
	{
		case MULTICAST_CMD_QUERYIPS:
		{
			bRet = Process_Multicast_QueryIP(vec);
			break;
		}
		case MULTICAST_CMD_QUERYIPS_ACK:
		{
			bRet = Process_Multicast_QueryIP_ACK(vec);
			break;
		}
		case MULTICAST_CMD_SETIP:
		{
			bRet = Process_Multicast_SetIPs(vec);
			break;
		}
		case MULTICAST_CMD_SETIP_ACK:
		{
			bRet = Process_Multicast_SetIPs_ACK(vec);	
			break;
		}
		case MULTICAST_CMD_PROCESS:
		{
			bRet = Process_Multicast_StartOffProcess(vec);
			break;
		}
		case MULTICAST_CMD_PROCESS_ACK:
		{
			bRet = Process_Multicast_StartOffProcess_ACK(vec);
			break;
		}
		case MULTICAST_CMD_QUERYSERVERSTATE:
		{
			bRet = Process_Multicast_QueryState(vec);
			break;
		}
		case MULTICAST_CMD_QUERYSYSTEMCFG:
		{
			bRet = Process_Multicast_QuerySystemCfg(vec);
			break;
		}
		case MULTICAST_CMD_QUERYSERVERSTATE_ACK:
		{
			bRet = Process_Multicast_QueryState_ACK(vec);
			break;
		}
//		case MULTICAST_CMD_QUERYSYSTEMCFG_ACK:
//		{
//			bRet = Process_Multicast_QuerySystemCfg_ACK(vec);
//			break;
//		}
		default:
			break;	
	}

	//如果收到期待应答，清除记录
	if (nCmdType > 0x20)
	{
		PopCurRetCmd(nCmdType);
	}
	return bRet;
}

void CSttMulticastClientSocket::AddRetCmd(BYTE nCmd)
{
// 	vector<BYTE>::iterator it = find(m_RetCmdList.begin(),m_RetCmdList.end(),nCmd);
// 	if (it == m_RetCmdList.end())
// 	{
// 		m_RetCmdList.push_back(nCmd);
// 	}
}

void CSttMulticastClientSocket::PopCurRetCmd(BYTE nCmd)
{
// 	vector<BYTE>::iterator it = find(m_RetCmdList.begin(),m_RetCmdList.end(),nCmd);
// 	if (it != m_RetCmdList.end())
// 	{
// 		m_RetCmdList.erase(it);
// 	}
}

long CSttMulticastClientSocket::Multicast_QueryIP()
{
	long nSendBufLen = STT_PKG_HEAD_LEN;
	BYTE *pSendBuf = new BYTE[nSendBufLen];
	stt_InitPktBuffer_Head(pSendBuf,MULTICAST_CMD_QUERYIPS, 0, 0, 0, 0);

	long nRet = SendBuffer(pSendBuf,nSendBufLen,&m_sktMultiCast);
	if (nRet > 0)
	{
		AddRetCmd(MULTICAST_CMD_QUERYIPS_ACK);
	}
	delete pSendBuf;

	return nRet;
}

long CSttMulticastClientSocket::Multicast_SetIPs(const CString &strTestAppSN,const CString &strTestAppModel
												 ,BYTE *pIPBuf,BYTE *pMaskBuf,BOOL bIPV4)
{
	long nSendBufLen = 1024;
	BYTE *pSendBuf = new BYTE[nSendBufLen];
	BYTE *pHead = pSendBuf + STT_PKG_HEAD_LEN;
	BYTE *pPos = pHead;
	
	stt_pp_pkt_pack_stringVal(pPos,STT_PP_DATAID_SN, strTestAppSN);
	stt_pp_pkt_pack_stringVal(pPos, STT_PP_DATAID_MODEL, strTestAppModel);
	stt_pp_pkt_pack_ipVal(pPos, pIPBuf, pMaskBuf, bIPV4);

	long nDataLen = pPos - pHead;
	stt_InitPktBuffer_Head(pSendBuf,MULTICAST_CMD_SETIP, nDataLen, 0, 0, 0);

	long nRet = SendBuffer(pSendBuf,nDataLen + STT_PKG_HEAD_LEN,&m_sktMultiCast);

	if (nRet > 0)
	{
		AddRetCmd(MULTICAST_CMD_SETIP_ACK);
	}
	delete pSendBuf;

	return nRet;
}

long CSttMulticastClientSocket::Multicast_SetIPV4s(const CString &strTestAppSN,const CString &strTestAppModel
						,const CString &strIP,const CString &strMask)
{
	long nSendBufLen = 1024;
	BYTE *pSendBuf = new BYTE[nSendBufLen];

	BYTE *pHead = pSendBuf + STT_PKG_HEAD_LEN;
	BYTE *pPos = pHead;
	stt_pp_pkt_pack_stringVal(pPos,STT_PP_DATAID_SN,strTestAppSN);
	stt_pp_pkt_pack_stringVal(pPos,STT_PP_DATAID_MODEL,strTestAppModel);
	stt_pp_pkt_pack_ipV4Val(pPos,STT_PP_DATAID_IP, strIP,strMask);

	long nDataLen = pPos - pHead;
	stt_InitPktBuffer_Head(pSendBuf,MULTICAST_CMD_SETIP, nDataLen, 0, 0, 0);
	long nRet = SendBuffer(pSendBuf,nDataLen + STT_PKG_HEAD_LEN, &m_sktMultiCast);

	if (nRet > 0)
	{
		AddRetCmd(MULTICAST_CMD_SETIP_ACK);
	}
	delete pSendBuf;

	return nRet;
}


long CSttMulticastClientSocket::Multicast_SetIPV4Array(const CString &strTestAppSN,const CString &strTestAppModel
									,const CStringArray &astrIP,const CStringArray &astrMask)
{

	long nSendBufLen = 1024;
	BYTE *pSendBuf = new BYTE[nSendBufLen];

	BYTE *pHead = pSendBuf + STT_PKG_HEAD_LEN;
	BYTE *pPos = pHead;
	stt_pp_pkt_pack_stringVal(pPos,STT_PP_DATAID_SN,strTestAppSN);
	stt_pp_pkt_pack_stringVal(pPos,STT_PP_DATAID_MODEL,strTestAppModel);

	for(int i = 0;i < astrIP.GetCount();i++)
	{
		stt_pp_pkt_pack_ipV4Val(pPos, STT_PP_DATAID_IP, astrIP.GetAt(i), astrMask.GetAt(i));
	}

	long nDataLen = pPos - pHead;
	stt_InitPktBuffer_Head(pSendBuf,MULTICAST_CMD_SETIP, nDataLen, 0, 0, 0);
	long nRet = SendBuffer(pSendBuf,nDataLen + STT_PKG_HEAD_LEN, &m_sktMultiCast);

	if (nRet > 0)
	{
		AddRetCmd(MULTICAST_CMD_SETIP_ACK);
	}
	delete pSendBuf;

	return nRet;
}

long CSttMulticastClientSocket::Multicast_Process(BYTE* &pPkg, CStringArray &astrProc, BYTE nDataID)
{
	long nCount = astrProc.GetCount();
	long nIndex = 0;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		stt_pp_pkt_pack_stringVal(pPkg, nDataID, astrProc.GetAt(nIndex));
	}

	return 0;
}

long CSttMulticastClientSocket::Multicast_Process(const CString &strTestAppSN,const CString &strTestAppModel
														  ,CStringArray &astrProcRun, CStringArray &astrProcClose)
{
	long nSendBufLen = 1024;
	BYTE *pSendBuf = new BYTE[nSendBufLen];

	BYTE *pHead = pSendBuf + STT_PKG_HEAD_LEN;
	BYTE *pPos = pHead;
	stt_pp_pkt_pack_stringVal(pPos,STT_PP_DATAID_SN,strTestAppSN);
	stt_pp_pkt_pack_stringVal(pPos,STT_PP_DATAID_MODEL,strTestAppModel);
	Multicast_Process(pPos, astrProcClose, STT_PP_DATAID_CLOSE_PROC);
	Multicast_Process(pPos, astrProcRun, STT_PP_DATAID_RUN_PROC);	
	
	stt_InitPktBuffer_Head(pSendBuf, MULTICAST_CMD_PROCESS, pPos - pHead, 0, 0, 0);

	long nRet = SendBuffer(pSendBuf, pPos - pSendBuf, &m_sktMultiCast);

	if (nRet > 0)
	{
		AddRetCmd(MULTICAST_CMD_PROCESS_ACK);
	}

	delete pSendBuf;

	return nRet;
}

long CSttMulticastClientSocket::Multicast_QueryState(const CString &strTestAppSN,const CString &strTestAppModel)
{
	long nSendBufLen = 1024;
	BYTE *pSendBuf = new BYTE[nSendBufLen];

	BYTE *pHead = pSendBuf + STT_PKG_HEAD_LEN;
	BYTE *pPos = pHead;
	stt_pp_pkt_pack_stringVal(pPos,STT_PP_DATAID_SN,strTestAppSN);
	stt_pp_pkt_pack_stringVal(pPos,STT_PP_DATAID_MODEL,strTestAppModel);

	stt_InitPktBuffer_Head(pSendBuf,MULTICAST_CMD_QUERYSERVERSTATE, pPos - pHead, 0, 0, 0);

	long nRet = SendBuffer(pSendBuf, pPos - pSendBuf, &m_sktMultiCast);
	if (nRet > 0)
	{
		AddRetCmd(MULTICAST_CMD_QUERYSERVERSTATE_ACK);
	}
	delete pSendBuf;

	return nRet;
}

long CSttMulticastClientSocket::Multicast_QuerySystemCfg(const CString &strTestAppSN,const CString &strTestAppModel)
{
	long nSendBufLen = 1024;
	BYTE *pSendBuf = new BYTE[nSendBufLen];

	BYTE *pHead = pSendBuf + STT_PKG_HEAD_LEN;
	BYTE *pPos = pHead;
	stt_pp_pkt_pack_stringVal(pPos,STT_PP_DATAID_SN,strTestAppSN);
	stt_pp_pkt_pack_stringVal(pPos,STT_PP_DATAID_MODEL,strTestAppModel);

	stt_InitPktBuffer_Head(pSendBuf,MULTICAST_CMD_QUERYSYSTEMCFG, pPos - pHead, 0, 0, 0);

	long nRet = SendBuffer(pSendBuf, pPos - pSendBuf, &m_sktMultiCast);
	if (nRet > 0)
	{
		AddRetCmd(MULTICAST_CMD_QUERYSYSTEMCFG_ACK);
	}
	delete pSendBuf;

	return nRet;
}

long CSttMulticastClientSocket::Multicast_CommonACK(BYTE nAckCmd,const CString &strSN,const CString &strModel,int nErrCode)
{
	long nSendBufLen = 1024;
	BYTE *pSendBuf = new BYTE[nSendBufLen];

	BYTE *pHead = pSendBuf + STT_PKG_HEAD_LEN;
	BYTE *pPos = pHead;
	stt_pp_pkt_pack_stringVal(pPos,STT_PP_DATAID_SN,strSN);
	stt_pp_pkt_pack_stringVal(pPos,STT_PP_DATAID_MODEL,strModel);
	stt_pp_pkt_pack_longVal(pPos,STT_PP_DATAID_RUNSTATE, nErrCode);
	stt_InitPktBuffer_Head(pSendBuf,nAckCmd,pPos - pHead, 0, 0, 0);

	long nRet = SendBuffer(pSendBuf, pPos - pSendBuf, &m_sktMultiCast);
	delete pSendBuf;

	return nRet;
}

BOOL CSttMulticastClientSocket::Process_Multicast_QueryIP(CSttPpDatasDriver vec)
{
// 	CString strSN = _T("PSL001"),strModel = _T("PSL001");
// 	CString strIP = _T("192.168.1.15"),strMask = _T("255.255.255.0");
// 	//需更新上面四个参数
// 
// 	long nSendBufLen = 1024;
// 	BYTE *pSendBuf = new BYTE[nSendBufLen];
// 
// 	long nOffset = STT_PKG_HEAD_LEN;
// 	stt_pp_pkt_pack_stringVal(pSendBuf,STT_PP_DATAID_SN,strSN);
// 	stt_pp_pkt_pack_stringVal(pSendBuf,STT_PP_DATAID_MODEL,strModel);
// 	stt_pp_pkt_pack_ipV4Val(pSendBuf,strIP,strMask);
// 	stt_InitPktBuffer_Head(pSendBuf,MULTICAST_CMD_QUERYIPS_ACK, nOffset - STT_PKG_HEAD_LEN, 0, 0, 0);
// 
// 	long nRet = SendBuffer(pSendBuf,&m_sktMultiCast);
// 	delete pSendBuf;

	return TRUE;
}

BOOL CSttMulticastClientSocket::Process_Multicast_SetIPs(CSttPpDatasDriver vec)
{
// 	ASSERT(vec.size() > 2);
// 
// 	CString strSN = _T("PSL001"),strModel = _T("PSL001");
// 	CString strIP = _T(""),strMask = _T("");
// 	multicast_pkt_get_ipVal(vec[2],strIP,strMask);
// 
// 	//设置IP
// 
// 
// 	//更新错误码
// 	int nErrCode = 0;
// 	Multicast_CommonACK(MULTICAST_CMD_SETIP_ACK,strSN,strModel,nErrCode);

	return TRUE;
}
