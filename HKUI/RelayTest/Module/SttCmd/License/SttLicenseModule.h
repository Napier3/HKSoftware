//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttLicenseModule.h  CSttLicenseModule

#pragma once

#ifdef SttLicense_Own
#include "SttLicenseGlobal.h"
#else
#include "../SttCmdDefineGlobal.h"
#endif


class CSttLicenseModule : public CExBaseObject
{
public:
	CSttLicenseModule();
	virtual ~CSttLicenseModule();


	CString  m_strKey;
	long  m_nYear;
	long  m_nMonth;
	long  m_nDay;
	long  m_nDays;
	long  m_nTimes;
//���غ���
public:
    virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTLICENSEMODULE;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttLicenseModuleKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

