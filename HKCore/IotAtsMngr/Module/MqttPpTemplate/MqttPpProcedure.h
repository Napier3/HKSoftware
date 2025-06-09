//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MqttPpProcedure.h  CMqttPpProcedure

#pragma once

#include "MqttPpCfgGlobal.h"


#include "MqttPpAcks.h"
#include "MqttPpOverTime.h"

class CMqttPpProcedure : public CExBaseList
{
public:
	CMqttPpProcedure();
	virtual ~CMqttPpProcedure();


	CString  m_strPp_Pkg;
//���غ���
public:
	virtual UINT GetClassID() {    return MQTTCLASSID_CMQTTPPPROCEDURE;   }
	virtual BSTR GetXmlElementKey()  {      return CMqttPpCfgXmlRWKeys::CMqttPpProcedureKey();     }
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
	CMqttPpAcks *m_pAcks;
	CMqttPpOverTime *m_pOvertime;

//˽�г�Ա�������ʷ���
public:
	CMqttPpAcks* GetAcks()	{	return m_pAcks;	}
	CMqttPpOverTime* GetOvertime()	{	return m_pOvertime;	}

//���Ա������ʷ���
public:
	CMqttPpAck *FindAck(const CString &strID);
};

