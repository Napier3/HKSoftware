//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//StkCfg_NetAddr.h  CStkCfg_NetAddr

#pragma once

#include "MMS_STACK_CFGGlobal.h"



class CStkCfg_NetAddr : public CExBaseObject
{
public:
	CStkCfg_NetAddr();
	virtual ~CStkCfg_NetAddr();


	CString  m_strType;
	CString  m_strNetAddr;
//���غ���
public:
	virtual UINT GetClassID() {    return MMSCLASSID_CSTKCFG_NETADDR;   }
	virtual BSTR GetXmlElementKey()  {      return CMMS_STACK_CFGXmlRWKeys::CStkCfg_NetAddrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

