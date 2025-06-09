//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_DeviceInfoResp_Links.cpp  CTcpEdgePkgData_DeviceInfoResp_Links


#include "stdafx.h"
#include "TcpEdgePkgData_DeviceInfoResp_Links.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_DeviceInfoResp_Links::CTcpEdgePkgData_DeviceInfoResp_Links()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_DeviceInfoResp_Links::~CTcpEdgePkgData_DeviceInfoResp_Links()
{
}

long CTcpEdgePkgData_DeviceInfoResp_Links::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTcpEdgePkgData_DeviceInfoResp_Links::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTcpEdgePkgData_DeviceInfoResp_Links::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CTcpEdgePkgData_DeviceInfoResp_Links::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_DeviceInfoResp_Links::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_DeviceInfoResp_Links *p = (CTcpEdgePkgData_DeviceInfoResp_Links*)pObj;

	return TRUE;
}

BOOL CTcpEdgePkgData_DeviceInfoResp_Links::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CTcpEdgePkgData_DeviceInfoResp_Links *p = (CTcpEdgePkgData_DeviceInfoResp_Links*)pDest;

	return TRUE;
}

CBaseObject* CTcpEdgePkgData_DeviceInfoResp_Links::Clone()
{
	CTcpEdgePkgData_DeviceInfoResp_Links *p = new CTcpEdgePkgData_DeviceInfoResp_Links();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_DeviceInfoResp_Links::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_DeviceInfoResp_Links *p = new CTcpEdgePkgData_DeviceInfoResp_Links();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_DeviceInfoResp_Links::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_DeviceInfoResp_Links::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_DeviceInfoResp_Links::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
