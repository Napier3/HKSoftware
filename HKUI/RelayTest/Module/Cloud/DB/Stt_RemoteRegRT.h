//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Stt_RemoteRegRT.h  CStt_RemoteRegRT

#pragma once

#include "RemoteCtrlMngrGlobal.h"

#include "Stt_RemoteRegHis.h"

#include "Stt_RemoteUserRT.h"

class CStt_RemoteRegRT : public CStt_RemoteRegHis
{
public:
	CStt_RemoteRegRT();
	virtual ~CStt_RemoteRegRT();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTT_REMOTEREGRT;   }
	virtual BSTR GetXmlElementKey()  {      return CRemoteCtrlMngrXmlRWKeys::CStt_RemoteRegRTKey();     }
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CRemoteCtrlMngrXmlRWKeys::CStt_RemoteRegRTKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CRemoteCtrlMngrXmlRWKeys::CStt_RemoteUserRTKey();     }
	virtual CExBaseObject* DB_CreateNewChild();

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	CStt_RemoteUserRT *FindMacthUser(CStt_RemoteUserRT *pUser);
	CStt_RemoteUserRT *FindByIDTest(DWORD nDestID);
	void ClearOtherAuthoritys(CExBaseList *pParas, CStt_RemoteUserRT *pCurrUser
		,CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);
};

