#pragma once
#include <afxsock.h>
#include "..\DataMngr\DvmDataset.h"

#define XUSER_TCP_BUFFERLEN   8192
#define XUSER_TCP_MAXFULLRCV_BUFFERLEN   8192

#define  XUSER_CMD_LOGIN     _T("login")
#define  XUSER_CMD_LOGOUT    _T("logout")
#define  XUSER_CMD_GETINFOR  _T("getinfor")
#define  XUSER_CMD_HASFETURE _T("has-feture")

#define  XUSER_CMD_PARA_USERID  _T("user-id")
#define  XUSER_CMD_PARA_USERPSW  _T("user-psw")
#define  XUSER_CMD_PARA_FETUREID  _T("feture-id")

#define  XUSER_CMD_PARA_develop    _T("develop")
#define  XUSER_CMD_PARA_ownership  _T("ownership")
#define  XUSER_CMD_PARA_user_cop   _T("user-cop")
#define  XUSER_CMD_PARA_user_name  _T("user-name")
#define  XUSER_CMD_PARA_sys_name  _T("sys-name")
#define  XUSER_CMD_PARA_safenet_sn  _T("safenet-sn")
#define  XUSER_CMD_PARA_user_cop_sn  _T("user-cop-sn")
#define  XUSER_CMD_PARA_test_apps  _T("test-apps")
#define  XUSER_CMD_PARA_test  _T("test")
#define  XUSER_CMD_PARA_authority_sn  _T("authority-sn")


#define  WM_XUSERTCPCLIENT_CMD   (WM_USER+2150)

class CXUserTcpClientBase : public CSocket
{
public:
	CXUserTcpClientBase(void);
	virtual ~CXUserTcpClientBase(void);

	//2018-2-1：因为四方出现网卡在收到报文的时候，一帧报文变成了两帧，所以增加缓冲区
	BYTE m_byteFullReceiveBuffer[XUSER_TCP_MAXFULLRCV_BUFFERLEN];
	long m_nFullReceiveBufferLen;
	long m_nFullReceiveBufferLen_Send;
	BYTE m_byteReceiveBuffer[XUSER_TCP_BUFFERLEN];
	BYTE m_byteSendBuffer[XUSER_TCP_BUFFERLEN];

	virtual void OnReceive_Cmd(char *pBuffer, long nLen);
	virtual void OnReceive(int nErrorCode);
	
	virtual BOOL SendXUserCmd(CDvmData *pData);
	virtual BOOL SendXUserCmd(const CString &strCmd);
	virtual BOOL IsTcpConnectSucc();
	virtual BOOL IsSendCmdFinished();
	virtual long GetSendCmdResult();

	virtual void SetMsgRcvWnd(CWnd *pMsgRcvWnd);

protected:
	virtual BOOL ProcessXUserCmd(CDvmData *pData);
	CDvmData m_oSendCmd;
	BOOL m_bIsTcpConnectSucc;
	CWnd *m_pMsgRcvWnd;
	CDvmData *m_pRcvCmdData;


	char m_xdecrypt_buffer[8192];

	long XEncrypt(const CString &strText, char *pszBuffer);
	long XDecrypt(char *strSrcText, CString &strDest);

public:
	//用户登录
	virtual BOOL Login(const CString &strUserID, const CString &strPsw);
	virtual BOOL Logoff(const CString &strUserID);

	//软件授权
	virtual BOOL hasp_has_catalog(UINT nFetureID);
	virtual BOOL hasp_get_infor();

	
	//上传文件

	//下载文件

	//获取目录

};
