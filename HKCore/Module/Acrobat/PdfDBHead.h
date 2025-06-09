//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PdfDBHead.h  CPdfDBHead

#pragma once

#include "PdfHLParseGlobal.h"



class CPdfDBHead : public CExBaseObject
{
public:
	CPdfDBHead();
	virtual ~CPdfDBHead();


	long  m_nNameHead;
	long  m_nDWHead;
	long  m_nValueHead;
	long  m_nExistHead;
//重载函数
public:
	virtual UINT GetClassID() {    return PDF_CLASSID_CPDFDBHEAD;   }
	virtual BSTR GetXmlElementKey()  {      return CPdfHLParseXmlRWKeys::CPdfDBHeadKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

