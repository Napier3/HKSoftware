//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XMatchDatasetRef.h  CXMatchDatasetRef

#pragma once

#include "KeyDbGlobal.h"



class CXMatchDatasetRef : public CExBaseObject
{
public:
	CXMatchDatasetRef();
	virtual ~CXMatchDatasetRef();


//重载函数
public:
	virtual UINT GetClassID() {    return XMCFGCLASSID_CXMATCHDATASETREF;   }
	virtual BSTR GetXmlElementKey()  {      return CKeyDbXmlRWKeys::CXMatchDatasetRefKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

