//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_DeviceStatusReq.cpp  CTcpEdgePkgData_DeviceStatusReq


#include "stdafx.h"
#include "TcpEdgePkgData_DeviceStatusReq.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_DeviceStatusReq::CTcpEdgePkgData_DeviceStatusReq()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_DeviceStatusReq::~CTcpEdgePkgData_DeviceStatusReq()
{
}

long CTcpEdgePkgData_DeviceStatusReq::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTcpEdgePkgData_DeviceStatusReq::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTcpEdgePkgData_DeviceStatusReq::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CTcpEdgePkgData_DeviceStatusReq::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_DeviceStatusReq::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_DeviceStatusReq *p = (CTcpEdgePkgData_DeviceStatusReq*)pObj;

	return TRUE;
}

BOOL CTcpEdgePkgData_DeviceStatusReq::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_DeviceStatusReq *p = (CTcpEdgePkgData_DeviceStatusReq*)pDest;

	return TRUE;
}

CBaseObject* CTcpEdgePkgData_DeviceStatusReq::Clone()
{
	CTcpEdgePkgData_DeviceStatusReq *p = new CTcpEdgePkgData_DeviceStatusReq();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_DeviceStatusReq::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_DeviceStatusReq *p = new CTcpEdgePkgData_DeviceStatusReq();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_DeviceStatusReq::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_DeviceStatusReq::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_DeviceStatusReq::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
