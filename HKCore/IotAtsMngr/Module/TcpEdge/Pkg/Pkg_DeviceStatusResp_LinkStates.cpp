//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DeviceStatusResp_LinkStates.cpp  CPkg_DeviceStatusResp_LinkStates


#include "stdafx.h"
#include "Pkg_DeviceStatusResp_LinkStates.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPkg_DeviceStatusResp_LinkStates::CPkg_DeviceStatusResp_LinkStates()
{
	//初始化属性

	//初始化成员变量
}

CPkg_DeviceStatusResp_LinkStates::~CPkg_DeviceStatusResp_LinkStates()
{
}

long CPkg_DeviceStatusResp_LinkStates::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DeviceStatusResp_LinkStates::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DeviceStatusResp_LinkStates::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_DeviceStatusResp_LinkStates::InitAfterRead()
{
}

BOOL CPkg_DeviceStatusResp_LinkStates::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DeviceStatusResp_LinkStates *p = (CPkg_DeviceStatusResp_LinkStates*)pObj;

	return TRUE;
}

BOOL CPkg_DeviceStatusResp_LinkStates::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DeviceStatusResp_LinkStates *p = (CPkg_DeviceStatusResp_LinkStates*)pDest;

	return TRUE;
}

CBaseObject* CPkg_DeviceStatusResp_LinkStates::Clone()
{
	CPkg_DeviceStatusResp_LinkStates *p = new CPkg_DeviceStatusResp_LinkStates();
	Copy(p);
	return p;
}

CBaseObject* CPkg_DeviceStatusResp_LinkStates::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPkg_DeviceStatusResp_LinkStates *p = new CPkg_DeviceStatusResp_LinkStates();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPkg_DeviceStatusResp_LinkStates::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DeviceStatusResp_LinkStates::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DeviceStatusResp_LinkStates::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
