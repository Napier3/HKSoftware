//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgBase.cpp  CTcpEdgePkgBase


#include "stdafx.h"
#include "TcpEdgePkgBase.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgBase::CTcpEdgePkgBase()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTcpEdgePkgBase::~CTcpEdgePkgBase()
{
}

long CTcpEdgePkgBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTcpEdgePkgBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTcpEdgePkgBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CTcpEdgePkgBase::InitAfterRead()
{
}

BOOL CTcpEdgePkgBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CTcpEdgePkgBase *p = (CTcpEdgePkgBase*)pObj;

	return TRUE;
}

BOOL CTcpEdgePkgBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgBase *p = (CTcpEdgePkgBase*)pDest;

	return TRUE;
}

CBaseObject* CTcpEdgePkgBase::Clone()
{
	CTcpEdgePkgBase *p = new CTcpEdgePkgBase();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgBase::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgBase *p = new CTcpEdgePkgBase();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgBase::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
