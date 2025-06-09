//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XMatchDataref.h  CXMatchDataref

#pragma once

#include "KeyDbGlobal.h"



class CXMatchDataref : public CExBaseObject
{
public:
	CXMatchDataref();
	virtual ~CXMatchDataref();


	CString  m_strSrcPath;
	CString  m_strDestPath;
//重载函数
public:
	virtual UINT GetClassID() {    return XMCFGCLASSID_CXMATCHDATAREF;   }
	virtual BSTR GetXmlElementKey()  {      return CKeyDbXmlRWKeys::CXMatchDatarefKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

