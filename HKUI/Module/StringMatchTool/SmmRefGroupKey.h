﻿//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmmRefGroupKey.h  CSmmRefGroupKey

#pragma once

#include "StringMatchMapGlobal.h"



class CSmmRefGroupKey : public CExBaseObject
{
public:
	CSmmRefGroupKey();
	virtual ~CSmmRefGroupKey();


	long  m_nIndex;
//重载函数
public:
	virtual UINT GetClassID() {    return SMMCLASSID_CSMMREFGROUPKEY;   }
	virtual BSTR GetXmlElementKey()  {      return CStringMatchMapXmlRWKeys::CSmmRefGroupKeyKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

