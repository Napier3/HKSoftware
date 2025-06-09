//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgSmvRates.h  CIecCfgSmvRates

#pragma once

#include "IecCfgDataMngrGlobal.h"
#include "IecCfgSmvRate.h"

class CIecCfgSmvRates : public CExBaseList
{
public:
	CIecCfgSmvRates();
	virtual ~CIecCfgSmvRates();


//重载函数
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

//私有成员变量
private:
	void InitDefault();
	CIecCfgSmvRate* AddSmvRate(const CString &strName, float fRate);
	CString GetCfgDefaultConfigFile();

//私有成员变量访问方法
public:
	virtual BOOL OpenCfgDefaultConfigFile();
	virtual BOOL SaveCfgDefaultConfigFile();
	
	float GetSmvRate(const CString &strSmvRatrID);
	float GetSmvRate(UINT nSmvRatrID);

	void TransSmvRateID();//zhouhj20210320 转换对应的ID,为与单机软件保存一致将Ip、Up等统一改为I2、U2

private:
	void TransSmvRateID(const CString &strOldID,const CString &strNewID,float fDefautValue);
};

CString iecfg_GetSmvRateID(UINT nSmvRatrID);
