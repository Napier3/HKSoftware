//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg92ChsIn.h  CIecCfg92ChsIn

#pragma once

#include "IecCfg92Chs.h"
#include "IecCfg92ChIn.h"

class CIecCfg92ChsIn : public CIecCfg92Chs
{
public:
	CIecCfg92ChsIn();
	virtual ~CIecCfg92ChsIn();


//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGCHS92IN;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgChs92InKey();     }
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

//私有成员变量访问方法
public:
#ifdef _USE_IN_AT02D_MODE_
	virtual void SetAT02D_ChannelID(CExBaseList *pSVList,long &nCBIndex);//周宏军 20200616  增加AT02配置
#endif
};

