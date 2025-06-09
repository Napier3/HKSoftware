﻿//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XMatchConfig.h  CXMatchConfig

#pragma once

#include "KeyDbGlobal.h"


#include "XMatchDatarefs.h"
#include "XMatchDatasetRefs.h"

class CXMatchConfig : public CExBaseList
{
public:
	CXMatchConfig();
	virtual ~CXMatchConfig();


	CString  m_strSrcDatasetPath;
//重载函数
public:
	virtual UINT GetClassID() {    return XMCFGCLASSID_CXMATCHCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CKeyDbXmlRWKeys::CXMatchConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:
	CXMatchDatarefs *m_pXMatchDatarefs;
	CXMatchDatasetRefs *m_pXMatchDatasetRefs;

	virtual void InitAfterRead();
 
};

