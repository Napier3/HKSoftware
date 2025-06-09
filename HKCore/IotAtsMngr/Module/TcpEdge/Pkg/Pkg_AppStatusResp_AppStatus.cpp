//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_AppStatusResp_AppStatus.cpp  CPkg_AppStatusResp_AppStatus


#include "stdafx.h"
#include "Pkg_AppStatusResp_AppStatus.h"


#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPkg_AppStatusResp_AppStatus::CPkg_AppStatusResp_AppStatus()
{
	//初始化属性

	//初始化成员变量
}

CPkg_AppStatusResp_AppStatus::~CPkg_AppStatusResp_AppStatus()
{
}

long CPkg_AppStatusResp_AppStatus::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;


	return 0;
}

long CPkg_AppStatusResp_AppStatus::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_AppStatusResp_AppStatus::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
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

void CPkg_AppStatusResp_AppStatus::InitAfterRead()
{
}

BOOL CPkg_AppStatusResp_AppStatus::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_AppStatusResp_AppStatus *p = (CPkg_AppStatusResp_AppStatus*)pObj;

	return TRUE;
}

BOOL CPkg_AppStatusResp_AppStatus::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_AppStatusResp_AppStatus *p = (CPkg_AppStatusResp_AppStatus*)pDest;

	return TRUE;
}

CBaseObject* CPkg_AppStatusResp_AppStatus::Clone()
{
	CPkg_AppStatusResp_AppStatus *p = new CPkg_AppStatusResp_AppStatus();
	Copy(p);
	return p;
}

CBaseObject* CPkg_AppStatusResp_AppStatus::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPkg_AppStatusResp_AppStatus *p = new CPkg_AppStatusResp_AppStatus();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPkg_AppStatusResp_AppStatus::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_AppStatusResp_AppStatus::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_AppStatusResp_AppStatus::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
