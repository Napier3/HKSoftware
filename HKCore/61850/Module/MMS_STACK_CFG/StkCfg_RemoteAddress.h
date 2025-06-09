//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//StkCfg_RemoteAddress.h  CStkCfg_RemoteAddress

#pragma once

#include "MMS_STACK_CFGGlobal.h"


#include "StkCfg_NetAddr.h"

class CStkCfg_RemoteAddress : public CExBaseList
{
public:
	CStkCfg_RemoteAddress();
	virtual ~CStkCfg_RemoteAddress();


	CString  m_strAR_Name;
	CString  m_strAP_Title;
	CString  m_strAE_Qualifier;
	CString  m_strPsel;
	CString  m_strSsel;
	CString  m_strTsel;
	CString m_strModel;

	CString  m_strPSW;
	CString  m_strKey;

//���غ���
public:
	virtual UINT GetClassID() {    return MMSCLASSID_CSTKCFG_REMOTEADDRESS;   }
	virtual BSTR GetXmlElementKey()  {      return CMMS_STACK_CFGXmlRWKeys::CStkCfg_RemoteAddressKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void SetIP(const CString &strIP);
	CString GetIP();
};

