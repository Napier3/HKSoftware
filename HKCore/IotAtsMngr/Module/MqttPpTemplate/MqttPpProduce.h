//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MqttPpProduce.h  CMqttPpProduce

#pragma once

#include "MqttPpCfgGlobal.h"

#include "MqttPpPrase.h"


class CMqttPpProduce : public CMqttPpPrase
{
public:
	CMqttPpProduce();
	virtual ~CMqttPpProduce();


//���غ���
public:
	virtual UINT GetClassID() {    return MQTTCLASSID_CMQTTPPPRODUCE;   }
	virtual BSTR GetXmlElementKey()  {      return CMqttPpCfgXmlRWKeys::CMqttPpProduceKey();     }
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
};

