//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SensorPpPrase.cpp  CSensorPpPrase


#include "stdafx.h"
#include "SensorPpPrase.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSensorPpPrase::CSensorPpPrase()
{
	//��ʼ������

	//��ʼ����Ա����
}

CSensorPpPrase::~CSensorPpPrase()
{
}

BOOL CSensorPpPrase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSensorPpPrase *p = (CSensorPpPrase*)pObj;

	return TRUE;
}

BOOL CSensorPpPrase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSensorPpPrase *p = (CSensorPpPrase*)pDest;

	return TRUE;
}

CBaseObject* CSensorPpPrase::Clone()
{
	CSensorPpPrase *p = new CSensorPpPrase();
	Copy(p);
	return p;
}

CBaseObject* CSensorPpPrase::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSensorPpPrase *p = new CSensorPpPrase();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSensorPpPrase::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CSensorPpPrase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;

	if (strClassID == CDataMngrXmlRWKeys::CDvmDataKey())
	{
		pNew = new CDvmData();
	}

	return pNew;
}

CExBaseObject* CSensorPpPrase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DVMCLASSID_CDVMDATA)
	{
		pNew = new CDvmData();
	}

	return pNew;
}
