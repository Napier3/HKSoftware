//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMsgs.cpp  CSttMsgs


#include "stdafx.h"
#include "SttMsgs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttMsgs::CSttMsgs()
{
	//初始化属性

	//初始化成员变量
}

CSttMsgs::~CSttMsgs()
{
}

long CSttMsgs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttMsgs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttMsgs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CSttMsgs::InitAfterRead()
{
}

BOOL CSttMsgs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttMsgs *p = (CSttMsgs*)pObj;

	return TRUE;
}

BOOL CSttMsgs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttMsgs *p = (CSttMsgs*)pDest;

	return TRUE;
}

CBaseObject* CSttMsgs::Clone()
{
	CSttMsgs *p = new CSttMsgs();
	Copy(p);
	return p;
}

CBaseObject* CSttMsgs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttMsgs *p = new CSttMsgs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttMsgs::CanPaste(UINT nClassID)
{
	if (nClassID == STTCMDCLASSID_CSTTMSG)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttMsgs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttMsgKey)
	{
		pNew = new CSttMsg();
	}

	return pNew;
}

CExBaseObject* CSttMsgs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTCMDCLASSID_CSTTMSG)
	{
		pNew = new CSttMsg();
	}

	return pNew;
}

void CSttMsgs::AddMsg(const CString &strID, const CString &strMsg)
{
    CSttMsg *pMsg = new CSttMsg();
    pMsg->m_strID = strID;
    pMsg->m_strMsg = strMsg;
    AddNewChild(pMsg);
}

