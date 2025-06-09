//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpTemplate.h  CIotPpTemplate

#pragma once

#include "IOTPPGlobal.h"


#include "IotPpParses.h"
#include "IotPpProduces.h"
#include "IotPpProcedures.h"

class CIotPpTemplate : public CExBaseList
{
public:
	CIotPpTemplate();
	virtual ~CIotPpTemplate();


	CString  m_strDvm_File;
//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOTPPTEMPLATE;   }
	virtual BSTR GetXmlElementKey()  {      return CIOTPPXmlRWKeys::CIotPpTemplateKey();     }
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
private:
	CIotPpParses *m_pIotPpParses;
	CIotPpProduces *m_pIotPpProduces;
	CIotPpProcedures *m_pIotPpProcedures;

//私有成员变量访问方法
public:
	CIotPpParses* GetIotPpParses()	{	return m_pIotPpParses;	}
	CIotPpProduces* GetIotPpProduces()	{	return m_pIotPpProduces;	}
	CIotPpProcedures* GetIotPpProcedures()	{	return m_pIotPpProcedures;	}

//属性变量访问方法
public:
	CIotPpParse *FindPpParse(const CString &strID);
	CIotPpParse *FindPpParse(int nPkgType,int nCtrlType,int nRequestSetFlag);
	CIotPpProduce *FindPpProduce(const CString &strID);
	CIotPpProcedure *FindPpProcedure(const CString &strID);
};

