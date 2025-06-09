//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StkCfg_LocalAddress.h  CStkCfg_LocalAddress

#pragma once

#include "MMS_STACK_CFGGlobal.h"



class CStkCfg_LocalAddress : public CExBaseObject
{
public:
	CStkCfg_LocalAddress();
	virtual ~CStkCfg_LocalAddress();


	CString  m_strAR_Name;
	CString  m_strAP_Title;
	CString  m_strPsel;
	CString  m_strAE_Qualifier;
	CString  m_strSsel;
	CString  m_strTsel;
	CString  m_strTransportType;
//重载函数
public:
	virtual UINT GetClassID() {    return MMSCLASSID_CSTKCFG_LOCALADDRESS;   }
	virtual BSTR GetXmlElementKey()  {      return CMMS_STACK_CFGXmlRWKeys::CStkCfg_LocalAddressKey();     }
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

