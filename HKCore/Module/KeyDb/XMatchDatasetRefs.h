//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XMatchDatasetRefs.h  CXMatchDatasetRefs

#pragma once

#include "KeyDbGlobal.h"


#include "XMatchDatasetRef.h"

class CXMatchDatasetRefs : public CExBaseList
{
public:
	CXMatchDatasetRefs();
	virtual ~CXMatchDatasetRefs();


	CString  m_strMmsDvmFile;
//重载函数
public:
	virtual UINT GetClassID() {    return XMCFGCLASSID_CXMATCHDATASETREFS;   }
	virtual BSTR GetXmlElementKey()  {      return CKeyDbXmlRWKeys::CXMatchDatasetRefsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:
	CXMatchDatasetRef* AddNewDataset(const CString &strID);
};

