//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDataMap.h  CXDataMap

#pragma once

#include "DataMngrGlobal.h"
#include "../System/VariantDataAddress.h"


class CXDataMap : public CExBaseObject
{
public:
	CXDataMap();
	virtual ~CXDataMap();


	CString  m_strMapID;		//关联定值的绝对路径	
	CVariantDataAddress m_varDataAddr;	//运行过程中变量地址

//重载函数
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CXDATAMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CXDataMapKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

