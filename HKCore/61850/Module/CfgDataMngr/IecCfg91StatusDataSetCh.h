//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg91StatusDataSetCh.h  CIecCfg91StatusDataSetCh

#pragma once

#include "IecCfgDataMngrGlobal.h"
#include "../GlobalDataMngr/IecGlobalDataMngr.h"



class CIecCfg91StatusDataSetCh : public CExBaseObject
{
public:
	CIecCfg91StatusDataSetCh();
	virtual ~CIecCfg91StatusDataSetCh();


	long  m_nSValue;
	long  m_nIndex;
	long  m_nQValue;
	CString m_strIndex;
//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG91STATUSDATASETCH;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfg91StatusDataSetChKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
	WORD Get_hbo();

};

