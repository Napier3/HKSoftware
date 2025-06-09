#pragma once

#include "../../Protocol/SttProtocolDatas.h"
//////////////////////////////////////////////

//命令类型
#define MULTICAST_CMD_QUERYIPS							0x01
#define MULTICAST_CMD_SETIP								0x02
#define MULTICAST_CMD_PROCESS							0x03
#define MULTICAST_CMD_QUERYSERVERSTATE					0x04
#define MULTICAST_CMD_QUERYSYSTEMCFG					0x05

#define MULTICAST_CMD_QUERYIPS_ACK						0x21
#define MULTICAST_CMD_SETIP_ACK							0x22
#define MULTICAST_CMD_PROCESS_ACK						0x23
#define MULTICAST_CMD_QUERYSERVERSTATE_ACK				0x24
#define MULTICAST_CMD_QUERYSYSTEMCFG_ACK				0x25

//数据ID
#define STT_PP_DATAID_SN						0x01
#define STT_PP_DATAID_MODEL						0x02
#define STT_PP_DATAID_RUNSTATE					0x03
#define STT_PP_DATAID_IP						0x04
#define STT_PP_DATAID_CLOSE_PROC				0x05
#define STT_PP_DATAID_RUN_PROC					0x06
#define STT_PP_DATAID_NET_CARD					0x07
#define STT_PP_DATAID_PROCESSID					0x08
#define STT_PP_DATAID_DEFAULT_RUNPROC			0x09
#define STT_PP_DATAID_CFG_PROC					0x0A
#define STT_PP_DATAID_CFG_DRIVER				0x0B

class CSttMulticastMsgViewInterface
{
public:
	virtual void OnMulticastReceiveMsg(BYTE *pBuf, long nLen,LPVOID fsockaddr){}
	virtual void OnProcessDataMsg(BYTE nCmdType, CSttPpDatasDriver oDatas){}
	virtual void OnStopMulticastMsg(){}
};
