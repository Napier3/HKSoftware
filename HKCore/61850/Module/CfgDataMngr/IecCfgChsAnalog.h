//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgChsAnalog.h  CIecCfgChsAnalog

#pragma once

#include "IecCfgDataMngrGlobal.h"


#include "IecCfgAnalogCh.h"
#include "IecCfgChsBase.h"

class CIecCfgChsAnalog : public CIecCfgChsBase
{
public:
	CIecCfgChsAnalog();
	virtual ~CIecCfgChsAnalog();


//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGCHSANALOG;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgChsAnalogKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CExBaseObject* pObj);
	virtual BOOL CopyOwn(CExBaseObject* pDest);
	virtual CExBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual CIecCfgDataChBase* CreateChannel();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

