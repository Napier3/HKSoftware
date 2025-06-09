//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgChs6044.h  CIecCfgChs6044

#pragma once

#include "IecCfgDataMngrGlobal.h"


#include "IecCfg6044Ch.h"
#include "IecCfg6044CommonCh.h"
#include "IecCfgChsBase.h"

class CIecCfg6044Chs : public CIecCfgChsBase
{
public:
	CIecCfg6044Chs();
	virtual ~CIecCfg6044Chs();


//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGCHS6044;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgChs6044Key();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual CIecCfgDataChBase* CreateChannel();
	virtual void InitAfterRead();

	CString CreateVolCurrChID_AT02D(CExBaseList *pHasModifiedChListRef,const CString &strPrefix,const CString &strSuffix,
		const CString &strChID,long nChProtMeasType = 0);//最后一个参数标识通道的保护/测量类别  0-不区分,1-保护,2测量

//私有成员变量
private:

//私有成员变量访问方法
public:
#ifdef _USE_IN_AT02D_MODE_
	virtual void SetAT02D_ChannelID(CExBaseList *pSVList,long &nCBIndex);//周宏军 2024.3.2  增加AT02配置
#endif
};

