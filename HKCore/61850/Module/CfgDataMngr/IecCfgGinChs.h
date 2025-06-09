//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgChsGin.h  CIecCfgChsGin

#pragma once

#include "IecCfgDataMngrGlobal.h"


#include "IecCfgGinCh.h"
#include "IecCfgChsBase.h"

class CIecCfgGinChs : public CIecCfgChsBase
{
public:
	CIecCfgGinChs();
	virtual ~CIecCfgGinChs();


//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGCHSGIN;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgChsGinKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual CIecCfgDataChBase* CreateChannel();

//私有成员变量
private:
#ifdef _USE_IN_AT02D_MODE_
//私有成员变量访问方法
public:
	virtual void SetAT02D_ChannelID(CExBaseList *pGinList,long &nCBIndex);//周宏军 20200616  增加AT02配置
#endif
};

