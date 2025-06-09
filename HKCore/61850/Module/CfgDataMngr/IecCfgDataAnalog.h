//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDataAnalog.h  CIecCfgDataAnalog

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataBase.h"

#include "IecCfgChsAnalog.h"

class CIecCfgDataAnalog : public CIecCfgDataBase
{
public:
	CIecCfgDataAnalog();
	virtual ~CIecCfgDataAnalog();

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGANALOGDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDataAnalogKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CExBaseObject* pObj);
	virtual BOOL CopyOwn(CExBaseObject* pDest);
	virtual CExBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual CString GetCfgDefaultConfigFile()	{	return _T("CfgAnalog.xml");	}

//私有成员变量
private:
	long m_nDataUse;

//私有成员变量访问方法
public:
	virtual CString GetCfgDataName(long nIndex)
	{
		return _T("小信号");
	}
	virtual CString GetCfgDataShortName(long nIndex)
	{
		return GetCfgDataName(nIndex);
	}
	long GetDataUse()
	{
		return m_nDataUse;
	}
	void SetDataUse(long nDataUse)
	{
		m_nDataUse = nDataUse;
	}

// 	virtual void CalArtAmpDigdatas(CArtAmpDigdatas *pArtAmpDigdatas, long &nHdCnIndex);

};

