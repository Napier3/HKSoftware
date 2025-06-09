//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgSmvRates.h  CIecCfgSmvRates

#pragma once

#include "IecCfgDataMngrGlobal.h"
#include "IecCfgSmvRate.h"

class CIecCfgSmvRates : public CExBaseList
{
public:
	CIecCfgSmvRates();
	virtual ~CIecCfgSmvRates();


//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGSMVRATES;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgSmvRatesKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	void InitDefault();
	CIecCfgSmvRate* AddSmvRate(const CString &strName, float fRate);
	CString GetCfgDefaultConfigFile();

//˽�г�Ա�������ʷ���
public:
	virtual BOOL OpenCfgDefaultConfigFile();
	virtual BOOL SaveCfgDefaultConfigFile();
	
	float GetSmvRate(const CString &strSmvRatrID);
	float GetSmvRate(UINT nSmvRatrID);

	void TransSmvRateID();//zhouhj20210320 ת����Ӧ��ID,Ϊ�뵥���������һ�½�Ip��Up��ͳһ��ΪI2��U2

private:
	void TransSmvRateID(const CString &strOldID,const CString &strNewID,float fDefautValue);
};

CString iecfg_GetSmvRateID(UINT nSmvRatrID);
