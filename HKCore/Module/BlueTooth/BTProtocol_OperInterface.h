#pragma once

#define BT_HEAD_LEN         13
#define BT_TAIL_LEN          2
#define BT_EX_LEN            BT_HEAD_LEN + BT_TAIL_LEN
#define BT_TEXT_LEN          4096
#define BT_FILE_NAME_MAX     256
#define BT_SOCKET_RECV_SIZE  (BT_EX_LEN + BT_TEXT_LEN)


class CBTProtocol_OperInterface
{
public:
	CBTProtocol_OperInterface(void);
	~CBTProtocol_OperInterface(void);

	void bt_set_head(BYTE *pPkg, BYTE &bCmmd, int &nLen);
	void bt_set_tail(BYTE *pPkg, int &nAllLen);

	int CalcTotalLen(BYTE *pPkg);
	int CalDataLen(BYTE *pPkg);
	BOOL CalCRC(BYTE *pPkg,int &nAllLen);
	void JointMessage(BYTE *pPkg, char *pchMsg,BYTE bCmmd,int nLen);

	unsigned short CRC16(unsigned char *Frame, int Length);
};
