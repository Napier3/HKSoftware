//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ComtradeRateData.h  CComtradeRateData

#pragma once

#include "ComtradeFileGlobal.h"

#include "ComtradeDataBase.h"

class CComtradeRateData : public CComtradeDataBase
{
public:
	CComtradeRateData();
	virtual ~CComtradeRateData();


	long  m_nSamprate;
	long  m_nEndsamp;
//���غ���
public:
	virtual UINT GetClassID() {    return GLOBALCLASSID_CCOMTRADERATEDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CComtradeFileXmlRWKeys::CComtradeRateDataKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

	virtual BOOL IsAnalogData()			{	return FALSE;				}
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

