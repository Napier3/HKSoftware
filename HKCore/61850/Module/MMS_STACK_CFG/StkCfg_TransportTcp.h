//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StkCfg_TransportTcp.h  CStkCfg_TransportTcp

#pragma once

#include "MMS_STACK_CFGGlobal.h"



class CStkCfg_TransportTcp : public CExBaseObject
{
public:
	CStkCfg_TransportTcp();
	virtual ~CStkCfg_TransportTcp();


	CString  m_strRfc1006_Max_Tpdu_Len;
	CString  m_strRfc1006_Max_Num_Conns;
	CString  m_strRfc1006_Max_Spdu_Outstanding;
//重载函数
public:
	virtual UINT GetClassID() {    return MMSCLASSID_CSTKCFG_TRANSPORTTCP;   }
	virtual BSTR GetXmlElementKey()  {      return CMMS_STACK_CFGXmlRWKeys::CStkCfg_TransportTcpKey();     }
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

