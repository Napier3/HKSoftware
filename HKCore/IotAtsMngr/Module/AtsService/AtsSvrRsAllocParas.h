//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AtsSvrRsAllocParas.h  CAtsSvrRsAllocParas

#pragma once

#include "AtsServiceGlobal.h"



class CAtsSvrRsAllocParas : public CExBaseList
{
public:
	CAtsSvrRsAllocParas();
	virtual ~CAtsSvrRsAllocParas();


	CString  m_strDeviceType;
	CString  m_strDeviceSN;
	CString  m_strMacroID;
//���غ���
public:
	virtual UINT GetClassID() {    return ATSVRCLASSID_CATSSVRRSALLOCPARAS;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsServiceXmlRWKeys::CAtsSvrRsAllocParasKey();     }
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

