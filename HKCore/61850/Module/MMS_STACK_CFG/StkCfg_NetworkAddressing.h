//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//StkCfg_NetworkAddressing.h  CStkCfg_NetworkAddressing

#pragma once

#include "MMS_STACK_CFGGlobal.h"


#include "StkCfg_LocalAddressList.h"
#include "StkCfg_RemoteAddressList.h"

class CStkCfg_NetworkAddressing : public CExBaseList
{
public:
	CStkCfg_NetworkAddressing();
	virtual ~CStkCfg_NetworkAddressing();


//���غ���
public:
	virtual UINT GetClassID() {    return MMSCLASSID_CSTKCFG_NETWORKADDRESSING;   }
	virtual BSTR GetXmlElementKey()  {      return CMMS_STACK_CFGXmlRWKeys::CStkCfg_NetworkAddressingKey();     }
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
	CStkCfg_RemoteAddressList *m_pRemoteAddressList;

//˽�г�Ա�������ʷ���
public:
	CStkCfg_RemoteAddressList* GetRemoteAddressList()	{	return m_pRemoteAddressList;	}

};

