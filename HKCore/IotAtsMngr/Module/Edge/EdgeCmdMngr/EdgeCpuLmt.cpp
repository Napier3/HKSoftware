//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EdgeCpuLmt.cpp  CEdgeCpuLmt


#include "stdafx.h"
#include "EdgeCpuLmt.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeCpuLmt::CEdgeCpuLmt()
{
	//��ʼ������

	//��ʼ����Ա����
}

CEdgeCpuLmt::~CEdgeCpuLmt()
{
}

long CEdgeCpuLmt::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeDatas::XmlReadOwn(oNode, pXmlRWKeys);
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEdgeCpuLmt::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeDatas::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEdgeCpuLmt::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CEdgeDatas::SerializeOwn(oBinaryBuffer);
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

void CEdgeCpuLmt::InitAfterRead()
{
}

BOOL CEdgeCpuLmt::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEdgeDatas::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEdgeCpuLmt *p = (CEdgeCpuLmt*)pObj;

	return TRUE;
}

BOOL CEdgeCpuLmt::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeDatas::CopyOwn(pDest);

	CEdgeCpuLmt *p = (CEdgeCpuLmt*)pDest;

	return TRUE;
}

CBaseObject* CEdgeCpuLmt::Clone()
{
	CEdgeCpuLmt *p = new CEdgeCpuLmt();
	Copy(p);
	return p;
}

CBaseObject* CEdgeCpuLmt::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeCpuLmt *p = new CEdgeCpuLmt();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeCpuLmt::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeCpuLmt::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeCpuLmt::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
