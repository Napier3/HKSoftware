//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg6044Ch.h  CIecCfg6044Ch

#pragma once

#include "IecCfg6044CommonCh.h"


class CIecCfg6044CommonChIn : public CIecCfg6044CommonCh
{
public:
	CIecCfg6044CommonChIn();
	virtual ~CIecCfg6044CommonChIn();

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG6044COMMONCHIN;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfg6044CommonChInKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
	long m_nAccuratyLevel;//准确度

};

