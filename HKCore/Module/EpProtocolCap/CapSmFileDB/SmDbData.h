//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmDbData.h  CSmDbData

#pragma once

#include "SmDbBaseList.h"
#include "SmFileDBGlobal.h"
#include "..\ShareMem\ShareMemServerEx.h"
#include "..\ShareMem\ShareMemClientEx.h"


class CSmDbData : public CSmDbBaseObject
{
public:
	CSmDbData();
	virtual ~CSmDbData();


//重载函数
public:
	virtual UINT GetClassID() {    return SMDBCLASSID_CSMDBDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CSmFileDBXmlRWKeys::CSmDbDataKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	virtual long SmReadOwn(CShareMemClientEx &oSm)	{	return 0;	}

	virtual long SmWriteOwn(CShareMemClientEx &oSm)	{	return 0;	}

	virtual long GetLength()	{	return 0;	}

//私有成员变量
private:

//私有成员变量访问方法
public:
};

