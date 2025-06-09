//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpTimers.cpp  CIotPpTimers


#include "stdafx.h"
#include "IotPpTimers.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotPpTimers::CIotPpTimers()
{
	//初始化属性

	//初始化成员变量
}

CIotPpTimers::~CIotPpTimers()
{
}

long CIotPpTimers::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpTimers::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpTimers::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIotPpTimers::InitAfterRead()
{
}

BOOL CIotPpTimers::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIotPpTimers *p = (CIotPpTimers*)pObj;

	return TRUE;
}

BOOL CIotPpTimers::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIotPpTimers *p = (CIotPpTimers*)pDest;

	return TRUE;
}

CBaseObject* CIotPpTimers::Clone()
{
	CIotPpTimers *p = new CIotPpTimers();
	Copy(p);
	return p;
}

CBaseObject* CIotPpTimers::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotPpTimers *p = new CIotPpTimers();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotPpTimers::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOTPPTIMER)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIotPpTimers::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIotPpTimerKey)
	{
		pNew = new CIotPpTimer();
	}

	return pNew;
}

CExBaseObject* CIotPpTimers::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOTPPTIMER)
	{
		pNew = new CIotPpTimer();
	}

	return pNew;
}

void CIotPpTimers::UpdateTimers(CDvmDataset *pAttrDataset,CExBaseList *pInterface)
{
	POS pos = GetHeadPosition();
	CIotPpTimer *pTimer = NULL;

	while(pos != NULL)
	{
		pTimer = (CIotPpTimer *)GetNext(pos);

		pTimer->UpdateTimers(pAttrDataset,pInterface);
	}
}