//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Stt_RemoteRegHiss.cpp  CStt_RemoteRegHiss


#include "stdafx.h"
#include "Stt_RemoteRegHiss.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CStt_RemoteRegHiss::CStt_RemoteRegHiss()
{
	//初始化属性

	//初始化成员变量
}

CStt_RemoteRegHiss::~CStt_RemoteRegHiss()
{
}

long CStt_RemoteRegHiss::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CStt_RemoteRegHiss::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CStt_RemoteRegHiss::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CStt_RemoteRegHiss::InitAfterRead()
{
}

BOOL CStt_RemoteRegHiss::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CStt_RemoteRegHiss *p = (CStt_RemoteRegHiss*)pObj;

	return TRUE;
}

BOOL CStt_RemoteRegHiss::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CStt_RemoteRegHiss *p = (CStt_RemoteRegHiss*)pDest;

	return TRUE;
}

CBaseObject* CStt_RemoteRegHiss::Clone()
{
	CStt_RemoteRegHiss *p = new CStt_RemoteRegHiss();
	Copy(p);
	return p;
}

CBaseObject* CStt_RemoteRegHiss::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CStt_RemoteRegHiss *p = new CStt_RemoteRegHiss();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CStt_RemoteRegHiss::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTT_REMOTEREGHIS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CStt_RemoteRegHiss::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCStt_RemoteRegHisKey)
	{
		pNew = new CStt_RemoteRegHis();
	}

	return pNew;
}

CExBaseObject* CStt_RemoteRegHiss::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTT_REMOTEREGHIS)
	{
		pNew = new CStt_RemoteRegHis();
	}

	return pNew;
}
CExBaseObject* CStt_RemoteRegHiss::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CStt_RemoteRegHis();

	return pNew;
}
