//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_ConStatusResp_ContStatus .cpp  CPkg_ConStatusResp_ContStatus 


#include "stdafx.h"
#include "Pkg_ConStatusResp_ContStatus.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPkg_ConStatusResp_ContStatus ::CPkg_ConStatusResp_ContStatus ()
{
	//初始化属性

	//初始化成员变量
}

CPkg_ConStatusResp_ContStatus ::~CPkg_ConStatusResp_ContStatus ()
{
}

long CPkg_ConStatusResp_ContStatus ::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_ConStatusResp_ContStatus ::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_ConStatusResp_ContStatus ::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_ConStatusResp_ContStatus ::InitAfterRead()
{
}

BOOL CPkg_ConStatusResp_ContStatus ::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_ConStatusResp_ContStatus  *p = (CPkg_ConStatusResp_ContStatus *)pObj;

	return TRUE;
}

BOOL CPkg_ConStatusResp_ContStatus ::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_ConStatusResp_ContStatus  *p = (CPkg_ConStatusResp_ContStatus *)pDest;

	return TRUE;
}

CBaseObject* CPkg_ConStatusResp_ContStatus ::Clone()
{
	CPkg_ConStatusResp_ContStatus  *p = new CPkg_ConStatusResp_ContStatus ();
	Copy(p);
	return p;
}

CBaseObject* CPkg_ConStatusResp_ContStatus ::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPkg_ConStatusResp_ContStatus  *p = new CPkg_ConStatusResp_ContStatus ();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPkg_ConStatusResp_ContStatus ::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_ConStatusResp_ContStatus ::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_ConStatusResp_ContStatus ::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
