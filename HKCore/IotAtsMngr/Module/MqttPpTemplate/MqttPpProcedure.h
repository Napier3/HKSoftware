//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
//重载函数
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

//私有成员变量
private:
	CMqttPpAcks *m_pAcks;
	CMqttPpOverTime *m_pOvertime;

//私有成员变量访问方法
public:
	CMqttPpAcks* GetAcks()	{	return m_pAcks;	}
	CMqttPpOverTime* GetOvertime()	{	return m_pOvertime;	}

//属性变量访问方法
public:
	CMqttPpAck *FindAck(const CString &strID);
};

