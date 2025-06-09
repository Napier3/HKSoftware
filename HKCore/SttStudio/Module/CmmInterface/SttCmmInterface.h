#ifndef _SttCmmInterface_h_
#define _SttCmmInterface_h_

#include "../../../Module/BaseClass/XObjectRefBase.h"
#include "../../../Module/BaseClass/ExBaseList.h"

/*2021-7-18  lijunqing
	将接口从CXObjectRefBase派生，方便后面使用CXObjectRefDriver的模式进行引用计数处理，
例如，一个通信对象在多个地方被使用（指针方式），在释放时，delete之后，可能还有些地方
在使用，就容易造成错误。尤其是关联引用为角差的这种模式。
	暂时不从CXObjectRefBase，避免多积累的模式
	对于需要多个地方使用的，可以考虑对具体的对象就行改进，从CXObjectRefBase派生
参考CSttAtsCmd
*/
//协议通信接口

//通信消息接口
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

//通信接口
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

