//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecSmvChDataType.h  CIecSmvChDataType

#pragma once

#include "IecGlobalDataMngrGlobal.h"



class CIecSmvChDataType : public CDataType
{
public:
	CIecSmvChDataType();
	virtual ~CIecSmvChDataType();


//重载函数
public:
	virtual UINT GetClassID() {    return STGCLASSID_CIecSmvCHDATATYPE;   }
	virtual BSTR GetXmlElementKey()  {      return CIecGlobalDataMngrXmlRWKeys::CIecSmvChDataTypeKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

