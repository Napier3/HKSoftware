//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//StkCfg_RemoteAddressList.h  CStkCfg_RemoteAddressList

#pragma once

#include "MMS_STACK_CFGGlobal.h"


#include "StkCfg_RemoteAddress.h"

class CStkCfg_RemoteAddressList : public CExBaseList
{
public:
	CStkCfg_RemoteAddressList();
	virtual ~CStkCfg_RemoteAddressList();


//���غ���
public:
	virtual UINT GetClassID() {    return MMSCLASSID_CSTKCFG_REMOTEADDRESSLIST;   }
	virtual BSTR GetXmlElementKey()  {      return CMMS_STACK_CFGXmlRWKeys::CStkCfg_RemoteAddressListKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void SetCount(long nCount);
};

