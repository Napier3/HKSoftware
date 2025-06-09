//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PdfDBInfo.h  CPdfDBInfo

#pragma once

#include "PdfHLParseGlobal.h"


#include "PdfDBTable.h"

class CPdfDBInfo : public CExBaseList
{
public:
	CPdfDBInfo();
	virtual ~CPdfDBInfo();


//重载函数
public:
	virtual UINT GetClassID() {    return PDF_CLASSID_CPDFDBINFO;   }
	virtual BSTR GetXmlElementKey()  {      return CPdfHLParseXmlRWKeys::CPdfDBInfoKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

