//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StkCfg_MMS.h  CStkCfg_MMS

#pragma once

#include "MMS_STACK_CFGGlobal.h"


#include "StkCfg_Transport.h"

class CStkCfg_MMS : public CExBaseObject
{
public:
	CStkCfg_MMS();
	virtual ~CStkCfg_MMS();


	CString  m_strMax_Mms_Pdu_Length;
	CString  m_strMax_Calling_Connections;
	CString  m_strMax_Called_Connections;
//重载函数
public:
	virtual UINT GetClassID() {    return MMSCLASSID_CSTKCFG_MMS;   }
	virtual BSTR GetXmlElementKey()  {      return CMMS_STACK_CFGXmlRWKeys::CStkCfg_MMSKey();     }
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

