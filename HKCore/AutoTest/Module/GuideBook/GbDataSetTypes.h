//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbDataSetTypes.h  CGbDataSetTypes

#pragma once

#include "GuideBookDefine.h"



class CGbDataSetTypes : public CExBaseList
{
public:
	CGbDataSetTypes();
	virtual ~CGbDataSetTypes();


//重载函数
public:
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbXMLKeys::CGbDataSetTypesKey();     }
	virtual UINT GetClassID() {    return GBCLASSID_GBDATASETTYPE;   }

//私有成员变量
private:

//私有成员变量访问方法
public:
};

