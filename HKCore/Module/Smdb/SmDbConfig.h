//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmDbConfig.h  CSmDbConfig

#pragma once

#include "SmDbConfigGlobal.h"


#include "SmDbFileCfg.h"

class CSmDbConfig : public CExBaseList
{
public:
	CSmDbConfig();
	virtual ~CSmDbConfig();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CEPCAPDBCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CSmDbConfigXmlRWKeys::CSmDbConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:
	CSmDbFileCfg* FindFileCfg(const CString &strFile);
};

