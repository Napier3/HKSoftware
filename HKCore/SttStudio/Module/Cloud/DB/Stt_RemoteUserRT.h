//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Stt_RemoteUserRT.h  CStt_RemoteUserRT

#pragma once

#include "RemoteCtrlMngrGlobal.h"

#include "Stt_RemoteUserHis.h"


class CStt_RemoteUserRT : public CStt_RemoteUserHis
{
public:
	CStt_RemoteUserRT();
	virtual ~CStt_RemoteUserRT();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTT_REMOTEUSERRT;   }
	virtual BSTR GetXmlElementKey()  {      return CRemoteCtrlMngrXmlRWKeys::CStt_RemoteUserRTKey();     }
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CRemoteCtrlMngrXmlRWKeys::CStt_RemoteUserRTKey();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	void GetUserAuthorityDetail(CString &strUserAuthorityDetail);
	BOOL UpdateDB_Authority(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);

	void ClearAuthoritys(CExBaseList *pParas,CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);
};

