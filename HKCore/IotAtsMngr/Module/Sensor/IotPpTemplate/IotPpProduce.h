//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpProduce.h  CIotPpProduce

#pragma once

#include "IOTPPGlobal.h"

#include "IotPpParse.h"

#include "IotPpInterface.h"
#include "IotPpPkgHead.h"
#include "IotPpDataList.h"

class CIotPpProduce : public CIotPpParse
{
public:
	CIotPpProduce();
	virtual ~CIotPpProduce();


//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOTPPPRODUCE;   }
	virtual BSTR GetXmlElementKey()  {      return CIOTPPXmlRWKeys::CIotPpProduceKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
protected:
	CIotPpInterface *m_pIotPpInterface;

//私有成员变量访问方法
public:
	CIotPpInterface* GetIotPpInterface()	{	return m_pIotPpInterface;	}

//属性变量访问方法
public:
};

