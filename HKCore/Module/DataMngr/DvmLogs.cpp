//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmLogs.cpp  CDvmLogs


#include "stdafx.h"
#include "DvmLogs.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguage/XLanguageResource.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CDvmLogs::CDvmLogs()
{
	m_strName = _T("Logs");
	m_strID = m_strName;
}

CDvmLogs::~CDvmLogs()
{

}

long CDvmLogs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDvmLogs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

long CDvmLogs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

BOOL CDvmLogs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDvmLogs *p = (CDvmLogs*)pObj;

	return TRUE;
}

BOOL CDvmLogs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDvmLogs *p = (CDvmLogs*)pDest;

	return TRUE;
}

CBaseObject* CDvmLogs::Clone()
{
	CDvmLogs *p = new CDvmLogs();
	Copy(p);
	return p;
}

CExBaseObject* CDvmLogs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDvmLogKey)
	{
		pNew = new CDvmLog();
	}

	return pNew;
}

CExBaseObject* CDvmLogs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DVMCLASSID_CDVMLOG)
	{
		pNew = new CDvmLog();
	}

	return pNew;
}

BOOL CDvmLogs::CanPaste(UINT nClassID)
{
	if (nClassID == DVMCLASSID_CDVMLOG)
	{
		return TRUE;
	}

	return FALSE;
}

void CDvmLogs::InitAfterRead()
{

}

long CDvmLogs::ClearByReserved(DWORD dwReserved)
{
	POS pos = GetHeadPosition();
	CDvmLog *pLog = NULL;

	while (pos != NULL)
	{
		pLog = (CDvmLog *)GetNext(pos);
		pLog->ClearByReserved(dwReserved);
	}

	return 0;
}

