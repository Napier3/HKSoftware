//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_AppStatusResp_AppStaProcs.cpp  CPkg_AppStatusResp_AppStaProcs


#include "stdafx.h"
#include "Pkg_AppStatusResp_AppStaProcs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPkg_AppStatusResp_AppStaProcs::CPkg_AppStatusResp_AppStaProcs()
{
	//初始化属性

	//初始化成员变量
}

CPkg_AppStatusResp_AppStaProcs::~CPkg_AppStatusResp_AppStaProcs()
{
}

long CPkg_AppStatusResp_AppStaProcs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_AppStatusResp_AppStaProcs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_AppStatusResp_AppStaProcs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_AppStatusResp_AppStaProcs::InitAfterRead()
{
}

BOOL CPkg_AppStatusResp_AppStaProcs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_AppStatusResp_AppStaProcs *p = (CPkg_AppStatusResp_AppStaProcs*)pObj;

	return TRUE;
}

BOOL CPkg_AppStatusResp_AppStaProcs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_AppStatusResp_AppStaProcs *p = (CPkg_AppStatusResp_AppStaProcs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_AppStatusResp_AppStaProcs::Clone()
{
	CPkg_AppStatusResp_AppStaProcs *p = new CPkg_AppStatusResp_AppStaProcs();
	Copy(p);
	return p;
}

CBaseObject* CPkg_AppStatusResp_AppStaProcs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPkg_AppStatusResp_AppStaProcs *p = new CPkg_AppStatusResp_AppStaProcs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPkg_AppStatusResp_AppStaProcs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_AppStatusResp_AppStaProcs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_AppStatusResp_AppStaProcs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
