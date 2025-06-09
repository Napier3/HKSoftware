//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrRsAllocParas.h  CAtsSvrRsAllocParas

#pragma once

#include "AtsServiceGlobal.h"



class CAtsSvrRsAllocParas : public CExBaseList
{
public:
	CAtsSvrRsAllocParas();
	virtual ~CAtsSvrRsAllocParas();


	CString  m_strDeviceType;
	CString  m_strDeviceSN;
	CString  m_strMacroID;
//重载函数
public:
	virtual UINT GetClassID() {    return ATSVRCLASSID_CATSSVRRSALLOCPARAS;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsServiceXmlRWKeys::CAtsSvrRsAllocParasKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
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

