//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Stt_RemoteRegHiss.h  CStt_RemoteRegHiss

#pragma once

#include "RemoteCtrlMngrGlobal.h"


#include "Stt_RemoteRegHis.h"

class CStt_RemoteRegHiss : public CExBaseList
{
public:
	CStt_RemoteRegHiss();
	virtual ~CStt_RemoteRegHiss();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTT_REMOTEREGHISS;   }
	virtual BSTR GetXmlElementKey()  {      return CRemoteCtrlMngrXmlRWKeys::CStt_RemoteRegHissKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CRemoteCtrlMngrXmlRWKeys::CStt_RemoteRegHisKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CRemoteCtrlMngrXmlRWKeys::CStt_RemoteRegHisKey();     }
	virtual CExBaseObject* DB_CreateNewChild();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

