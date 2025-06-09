//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XMatchDatarefs.h  CXMatchDatarefs

#pragma once

#include "KeyDbGlobal.h"


#include "XMatchDataref.h"

class CXMatchDatarefs : public CExBaseList
{
public:
	CXMatchDatarefs();
	virtual ~CXMatchDatarefs();


//重载函数
public:
	virtual UINT GetClassID() {    return XMCFGCLASSID_CXMATCHDATAREFS;   }
	virtual BSTR GetXmlElementKey()  {      return CKeyDbXmlRWKeys::CXMatchDatarefsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:
	CXMatchDataref* FindBySrcPath(const CString &strPath);
	CXMatchDataref* FindByDestPath(const CString &strPath);

	CXMatchDataref* AddNewDataRef(const CString &strSrcIDPath, const CString &strDestIDPath);
};

