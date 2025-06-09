#pragma once
#include "../baseclass/exbaselist.h"
#include "../CriticalSection/SynCriticalSection.h"

#define MSGSENDTYPE_WINDOW   0
#define MSGSENDTYPE_THREAD     1

#define MSREGMASK_MSGTYPE  0X00000001
#define MSREGMASK_HWNDORTHREADID  0X00000002
#define MSREGMASK_MESSAGEID  0X00000004
#define MSREGMASK_LPARAM  0X00000008
#define MSREGMASK_WPARAM  0X00000010
#define MSREGMASK_ITEMDATA  0X00000020
#define MSREGMASK_ID  0X00000040
#define MSREGMASK_ALL  0XFFFFFFFF

//#pragma pack(1)

typedef struct structMsgSendRegister
{
	ULONG nMsgType;   //线程消息、窗口消息
	ULONG nHWndOrThreadID;  //窗口的句本或者线程的ID
	ULONG nMessageID;           //消息ID
	LPARAM lParam;
	WPARAM wParam;     
	ULONG nItemData;           //关联的数据
	CString strID;
}MSGSENDREGISTER, *PMSGSENDREGISTER;

class CMsgSendRegister : public CExBaseObject
{
public:
	CMsgSendRegister();
	virtual ~CMsgSendRegister();

public:
	ULONG m_nMsgType;   //线程消息、窗口消息
	ULONG m_nHWndOrThreadID;  //窗口的句本或者线程的ID
	ULONG m_nMessageID;           //消息ID
	LPARAM m_lParam;
	WPARAM m_wParam;     
	ULONG m_nItemData;           //关联的数据

public:
	BOOL IsEqual(PMSGSENDREGISTER pMsgRegister, DWORD dwMask);
	void Init(PMSGSENDREGISTER pMsgRegister, DWORD dwMask);
	void PostMessage(long wPara, long lPara);
	
};

class CMessageMngr :	public CExBaseList
{
public:
	CMessageMngr(void);
	virtual ~CMessageMngr(void);
	CAutoCriticSection m_oMsgMngrCriticSection;

public:
	CMsgSendRegister* Register(ULONG nMsgType, ULONG nHWndOrThreadID, ULONG nMessageID, LPARAM lParam, WPARAM wParam, ULONG nItemData);
	CMsgSendRegister* Find(PMSGSENDREGISTER pMsgRegister, DWORD dwMask);
	void UnRegister(PMSGSENDREGISTER pMsgRegister, DWORD dwMask);
	CMsgSendRegister* Register(PMSGSENDREGISTER pMsgRegister, DWORD dwMask);

	void PostMessageByID(const CString &strProcedureID, long wPara=0, long lPara=0);
	void PostMessageByItemData(ULONG nItemData, long wPara, long lPara);
};
