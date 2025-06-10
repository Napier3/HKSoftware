#ifndef _SttCmmInterface_h_
#define _SttCmmInterface_h_

#include "../../../Module/BaseClass/XObjectRefBase.h"
#include "../../../Module/BaseClass/ExBaseList.h"

/*2021-7-18  lijunqing
	���ӿڴ�CXObjectRefBase�������������ʹ��CXObjectRefDriver��ģʽ�������ü�������
���磬һ��ͨ�Ŷ����ڶ���ط���ʹ�ã�ָ�뷽ʽ�������ͷ�ʱ��delete֮�󣬿��ܻ���Щ�ط�
��ʹ�ã���������ɴ��������ǹ�������Ϊ�ǲ������ģʽ��
	��ʱ����CXObjectRefBase���������۵�ģʽ
	������Ҫ����ط�ʹ�õģ����Կ��ǶԾ���Ķ�����иĽ�����CXObjectRefBase����
�ο�CSttAtsCmd
*/
//Э��ͨ�Žӿ�

//ͨ����Ϣ�ӿ�
class CSttCmmMsgInterface //: public CXObjectRefBase
{
public:
	CSttCmmMsgInterface(){}
	virtual ~CSttCmmMsgInterface(){}

public:
	//2021-8-22 lijunqing  Add strFromSN
	virtual void OnRecieve(const CString &strFromSN, char *pBuf,long nLen,long nCmdType, char *pszCmdID, char *pszRetType)=0;
	virtual void OnClose(char *pszErr)=0;
};

//ͨ�Žӿ�
class CSttCmmOptrInterface //: public CXObjectRefBase
{
public:
	CSttCmmOptrInterface(){}
	virtual ~CSttCmmOptrInterface(){}

public:
	virtual long Send(const CString &strToSN, char *pBuf,long nLen,long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)=0;
	virtual long Send(CExBaseObject *pCmdBase)=0;
	virtual BOOL Connect(const char *pszIP,long nPort , const char *pszClientIDKey)=0;
	virtual void Disconnect()=0;	
	virtual long Send(char *pBuf,long nLen, const CString &strTopic)=0;
};

#endif

