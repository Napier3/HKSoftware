//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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


//���غ���
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

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	CStt_RemoteUserRT *FindMacthUser(CStt_RemoteUserRT *pUser);
	CStt_RemoteUserRT *FindByIDTest(DWORD nDestID);
	void ClearOtherAuthoritys(CExBaseList *pParas, CStt_RemoteUserRT *pCurrUser
		,CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);
};

