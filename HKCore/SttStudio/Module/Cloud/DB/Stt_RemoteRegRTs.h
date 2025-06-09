//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Stt_RemoteRegRTs.h  CStt_RemoteRegRTs

#pragma once

#include "RemoteCtrlMngrGlobal.h"


#include "Stt_RemoteRegRT.h"

class CStt_RemoteRegRTs : public CExBaseList
{
public:
	CStt_RemoteRegRTs();
	virtual ~CStt_RemoteRegRTs();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTT_REMOTEREGRTS;   }
	virtual BSTR GetXmlElementKey()  {      return CRemoteCtrlMngrXmlRWKeys::CStt_RemoteRegRTsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CRemoteCtrlMngrXmlRWKeys::CStt_RemoteRegRTKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CRemoteCtrlMngrXmlRWKeys::CStt_RemoteRegRTKey();     }
	virtual CExBaseObject* DB_CreateNewChild();

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	void GenerateQuerySysState(CSttSysState &oSysState);
};

