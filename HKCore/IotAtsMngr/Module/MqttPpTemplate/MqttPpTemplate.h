//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MqttPpTemplate.h  CMqttPpTemplate

#pragma once

#include "MqttPpCfgGlobal.h"


#include "MqttPpProduces.h"
#include "MqttPpPrases.h"
#include "MqttPpProcedures.h"

class CMqttPpTemplate : public CExBaseList
{
public:
	CMqttPpTemplate();
	virtual ~CMqttPpTemplate();


	CString  m_strDvm_File;
//���غ���
public:
	virtual UINT GetClassID() {    return MQTTCLASSID_CMQTTPPTEMPLATE;   }
	virtual BSTR GetXmlElementKey()  {      return CMqttPpCfgXmlRWKeys::CMqttPpTemplateKey();     }
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

//˽�г�Ա����
private:
	CMqttPpPrases *m_pPpPrases;
	CMqttPpProduces *m_pPpproduces;
	CMqttPpProcedures *m_pProcedures;

//˽�г�Ա�������ʷ���
public:
	CMqttPpPrases* GetPpprases()	{	return m_pPpPrases;	}
	CMqttPpProduces* GetPpproduces()	{	return m_pPpproduces;	}
	CMqttPpProcedures* GetProcedures()	{	return m_pProcedures;	}

//���Ա������ʷ���
public:
	CMqttPpProcedure *FindProcedure(const CString &strProcedureID);
	CMqttPpProduce *FindProduce(const CString &strID);
	CMqttPpPrase *FindPrase(int nPkgType,int nCtrlType,int nRequestSetFlag);
	CString FindReadAinDsID();
};

