//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgSmvRate.h  CIecCfgSmvRate

#pragma once

#include "IecCfgDataMngrGlobal.h"



class CIecCfgSmvRate : public CExBaseObject
{
public:
	CIecCfgSmvRate();
	virtual ~CIecCfgSmvRate();


	float  m_fRate;

	//2023/10/12 wjs 新增参数
	long m_nCodeValue;//码值
	long m_nMeasCurrCodeValue;//测量电流码值
	float m_fPrimValue;//一次额定值
	CString m_strAliasName;//数据类型（别名） 

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGSMVRATE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgSmvRateKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
	BOOL IsVolChsGroup();
	BOOL IsDcFT3VolChsGroup();
	BOOL IsDcFT3CurChsGroup();
	BOOL IsAcFT3VolChsGroup();
	BOOL IsAcFT3CurChsGroup();

	//2023/10-20 wjs
	void InitDefaultAliasName();
};

CString st_GetSmvRateID(const CString& strAppCh,BOOL bDCFT3 = FALSE);

