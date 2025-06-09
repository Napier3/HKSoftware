//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDatasAnalog.h  CIecCfgDatasAnalog

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDatasBase.h"

#include "IecCfgDataAnalog.h"

class CIecCfgDatasAnalog : public CIecCfgDatasBase
{
public:
	CIecCfgDatasAnalog();
	virtual ~CIecCfgDatasAnalog();


//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGDATASANALOG;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDatasAnalogKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CExBaseObject* pObj);
	virtual BOOL CopyOwn(CExBaseObject* pDest);
	virtual CExBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	virtual CIecCfgDataBase* CreateIecCfgData();
	virtual BOOL IsCfgData(UINT nClassID)	{	return (nClassID == CFGCLASSID_CIECCFGANALOGDATA);	}
	virtual long GetMaxCfgDataCount()	{	return 1;	}

//私有成员变量
private:

//私有成员变量访问方法
public:
	
};

