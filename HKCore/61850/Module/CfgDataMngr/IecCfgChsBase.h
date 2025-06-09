//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgChsBase.h  CIecCfgChsBase

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataChBase.h"

class CIecCfgChsBase : public CExBaseList
{
public:
	CIecCfgChsBase();
	virtual ~CIecCfgChsBase();


//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGCHSBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgChsBaseKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);

	virtual CIecCfgDataChBase* CreateChannel() = 0;

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual void RemoveTailCh(long nCountRemove, CExBaseList &oListRemove);
	virtual BOOL SetChannelNum(long nChannelNum);
	virtual long GetChannels(CExBaseList &oListCh);
	virtual long GetUsedChsCount();
	virtual void InitChs();
};

