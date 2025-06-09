//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MqttPpPkg.h  CMqttPpPkg

#pragma once

#include "MqttPpCfgGlobal.h"

#include "../../../Module/DataMngr/DvmData.h"


class CMqttPpPkg : public CDvmData
{
public:
	CMqttPpPkg();
	virtual ~CMqttPpPkg();


	CString  m_strDs;
//���غ���
public:
	virtual UINT GetClassID() {    return MQTTCLASSID_CMQTTPPPKG;   }
	virtual BSTR GetXmlElementKey()  {      return CMqttPpCfgXmlRWKeys::CMqttPpPkgKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL IsMatchPkg(int nPkgType,int nCtrlType,int nRequestSetFlag);
	BOOL IsReadAinPkg();
};

