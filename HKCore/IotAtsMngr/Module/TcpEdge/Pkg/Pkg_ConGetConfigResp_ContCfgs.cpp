//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_ConGetConfigResp_ContCfgs.cpp  CPkg_ConGetConfigResp_ContCfgs


#include "stdafx.h"
#include "Pkg_ConGetConfigResp_ContCfgs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPkg_ConGetConfigResp_ContCfgs::CPkg_ConGetConfigResp_ContCfgs()
{
	//初始化属性

	//初始化成员变量
}

CPkg_ConGetConfigResp_ContCfgs::~CPkg_ConGetConfigResp_ContCfgs()
{
}

long CPkg_ConGetConfigResp_ContCfgs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_ConGetConfigResp_ContCfgs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_ConGetConfigResp_ContCfgs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_ConGetConfigResp_ContCfgs::InitAfterRead()
{
}

BOOL CPkg_ConGetConfigResp_ContCfgs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_ConGetConfigResp_ContCfgs *p = (CPkg_ConGetConfigResp_ContCfgs*)pObj;

	return TRUE;
}

BOOL CPkg_ConGetConfigResp_ContCfgs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_ConGetConfigResp_ContCfgs *p = (CPkg_ConGetConfigResp_ContCfgs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_ConGetConfigResp_ContCfgs::Clone()
{
	CPkg_ConGetConfigResp_ContCfgs *p = new CPkg_ConGetConfigResp_ContCfgs();
	Copy(p);
	return p;
}

CBaseObject* CPkg_ConGetConfigResp_ContCfgs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPkg_ConGetConfigResp_ContCfgs *p = new CPkg_ConGetConfigResp_ContCfgs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPkg_ConGetConfigResp_ContCfgs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_ConGetConfigResp_ContCfgs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_ConGetConfigResp_ContCfgs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
