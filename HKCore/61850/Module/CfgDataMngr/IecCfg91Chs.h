//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgChs91.h  CIecCfgChs91

#pragma once

#include "IecCfgDataMngrGlobal.h"


#include "IecCfg91Ch.h"
#include "IecCfgChsBase.h"

class CIecCfg91Chs : public CIecCfgChsBase
{
public:
	CIecCfg91Chs();
	virtual ~CIecCfg91Chs();


//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGCHS91;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgChs91Key();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual CIecCfgDataChBase* CreateChannel();
	virtual void InitAfterRead();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

