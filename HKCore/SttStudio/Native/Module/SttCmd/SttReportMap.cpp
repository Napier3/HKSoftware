//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttReportMap.cpp  CSttReportMap


#include "stdafx.h"
#include "SttReportMap.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttReportMap::CSttReportMap()
{
	//��ʼ������

	//��ʼ����Ա����
}

CSttReportMap::~CSttReportMap()
{
}

long CSttReportMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttReportMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttReportMap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttReportMap::InitAfterRead()
{
}

BOOL CSttReportMap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttReportMap *p = (CSttReportMap*)pObj;

	return TRUE;
}

BOOL CSttReportMap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttReportMap *p = (CSttReportMap*)pDest;

	return TRUE;
}

CBaseObject* CSttReportMap::Clone()
{
	CSttReportMap *p = new CSttReportMap();
	Copy(p);
	return p;
}

CBaseObject* CSttReportMap::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttReportMap *p = new CSttReportMap();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttReportMap::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTRPTDATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttReportMap::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttRptDataKey)
	{
		pNew = new CSttRptData();
	}

	return pNew;
}

CExBaseObject* CSttReportMap::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTRPTDATA)
	{
		pNew = new CSttRptData();
	}

	return pNew;
}
