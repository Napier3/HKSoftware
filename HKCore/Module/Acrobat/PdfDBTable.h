//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PdfDBTable.h  CPdfDBTable

#pragma once

#include "PdfHLParseGlobal.h"


#include "PdfDBHead.h"

class CPdfDBTable : public CExBaseList
{
public:
	CPdfDBTable();
	virtual ~CPdfDBTable();


//重载函数
public:
	virtual UINT GetClassID() {    return PDF_CLASSID_CPDFDBTABLE;   }
	virtual BSTR GetXmlElementKey()  {      return CPdfHLParseXmlRWKeys::CPdfDBTableKey();     }
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

