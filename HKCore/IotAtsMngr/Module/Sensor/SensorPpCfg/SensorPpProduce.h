//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SensorPpProduce.h  CSensorPpProduce

#pragma once

#include "PpCfgGlobal.h"

#include "SensorPpPrase.h"


class CSensorPpProduce : public CSensorPpPrase
{
public:
	CSensorPpProduce();
	virtual ~CSensorPpProduce();


//���غ���
public:
	virtual UINT GetClassID() {    return PPCFGCLASSID_CSENSORPPPRODUCE;   }
	virtual BSTR GetXmlElementKey()  {      return CPpCfgXmlRWKeys::CSensorPpProduceKey();     }
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

