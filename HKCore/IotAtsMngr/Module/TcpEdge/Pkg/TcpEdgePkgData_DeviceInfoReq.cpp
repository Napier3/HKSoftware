//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_DeviceInfoReq.cpp  CTcpEdgePkgData_DeviceInfoReq


#include "stdafx.h"
#include "TcpEdgePkgData_DeviceInfoReq.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_DeviceInfoReq::CTcpEdgePkgData_DeviceInfoReq()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_DeviceInfoReq::~CTcpEdgePkgData_DeviceInfoReq()
{
}

long CTcpEdgePkgData_DeviceInfoReq::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTcpEdgePkgData_DeviceInfoReq::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTcpEdgePkgData_DeviceInfoReq::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
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

void CTcpEdgePkgData_DeviceInfoReq::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_DeviceInfoReq::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_DeviceInfoReq *p = (CTcpEdgePkgData_DeviceInfoReq*)pObj;

	return TRUE;
}

BOOL CTcpEdgePkgData_DeviceInfoReq::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_DeviceInfoReq *p = (CTcpEdgePkgData_DeviceInfoReq*)pDest;

	return TRUE;
}

CBaseObject* CTcpEdgePkgData_DeviceInfoReq::Clone()
{
	CTcpEdgePkgData_DeviceInfoReq *p = new CTcpEdgePkgData_DeviceInfoReq();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_DeviceInfoReq::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_DeviceInfoReq *p = new CTcpEdgePkgData_DeviceInfoReq();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_DeviceInfoReq::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_DeviceInfoReq::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_DeviceInfoReq::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}