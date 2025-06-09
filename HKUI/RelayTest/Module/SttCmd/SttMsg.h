﻿//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMsg.h  CSttMsg

#pragma once

#include "SttCmdDefineGlobal.h"



class CSttMsg : public CExBaseObject
{
public:
	CSttMsg();
	virtual ~CSttMsg();

	CString  m_strMsg;
	CString m_strTime;
	long m_nLevel;
	long m_nType;
//重载函数
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTMSG;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttMsgKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	CString GetMsg()	{	return m_strMsg;	}
	void SetMsg(CString strMsg)	{	m_strMsg = strMsg;	}
};

