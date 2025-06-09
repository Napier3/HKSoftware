//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_AppGetConfigResp_AppCfgs .cpp  CPkg_AppGetConfigResp_AppCfgs 


#include "stdafx.h"
#include "Pkg_AppGetConfigResp_AppCfgs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPkg_AppGetConfigResp_AppCfgs ::CPkg_AppGetConfigResp_AppCfgs ()
{
	//初始化属性

	//初始化成员变量
}

CPkg_AppGetConfigResp_AppCfgs ::~CPkg_AppGetConfigResp_AppCfgs ()
{
}

long CPkg_AppGetConfigResp_AppCfgs ::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_AppGetConfigResp_AppCfgs ::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_AppGetConfigResp_AppCfgs ::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_AppGetConfigResp_AppCfgs ::InitAfterRead()
{
}

BOOL CPkg_AppGetConfigResp_AppCfgs ::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_AppGetConfigResp_AppCfgs  *p = (CPkg_AppGetConfigResp_AppCfgs *)pObj;

	return TRUE;
}

BOOL CPkg_AppGetConfigResp_AppCfgs ::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_AppGetConfigResp_AppCfgs  *p = (CPkg_AppGetConfigResp_AppCfgs *)pDest;

	return TRUE;
}

CBaseObject* CPkg_AppGetConfigResp_AppCfgs ::Clone()
{
	CPkg_AppGetConfigResp_AppCfgs  *p = new CPkg_AppGetConfigResp_AppCfgs ();
	Copy(p);
	return p;
}

CBaseObject* CPkg_AppGetConfigResp_AppCfgs ::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPkg_AppGetConfigResp_AppCfgs  *p = new CPkg_AppGetConfigResp_AppCfgs ();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPkg_AppGetConfigResp_AppCfgs ::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_AppGetConfigResp_AppCfgs ::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_AppGetConfigResp_AppCfgs ::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
