//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TtmgStation.h  CTtmgStation

#pragma once

#include "TestTasksMngrGenerateGlobal.h"



class CTtmgStation : public CExBaseObject
{
public:
	CTtmgStation();
	virtual ~CTtmgStation();


//���غ���
public:
	virtual UINT GetClassID() {    return TTMGCLASSID_CTTMGSTATION;   }
	virtual BSTR GetXmlElementKey()  {      return CTestTasksMngrGenerateXmlRWKeys::CTtmgStationKey();     }
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

CTtmgStation* TTMG_FindStation(const CString &strStation);
