//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ExecResult.cpp  CExecResult


#include "stdafx.h"
#include "ExecResult.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CExecResult::CExecResult()
{
	//��ʼ������

	//��ʼ����Ա����
}

CExecResult::~CExecResult()
{
}

BOOL CExecResult::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDvmDataset::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CExecResult *p = (CExecResult*)pObj;

	return TRUE;
}

BOOL CExecResult::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDvmDataset::CopyOwn(pDest);

	CExecResult *p = (CExecResult*)pDest;

	return TRUE;
}

CBaseObject* CExecResult::Clone()
{
	CExecResult *p = new CExecResult();
	Copy(p);
	return p;
}

CBaseObject* CExecResult::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CExecResult *p = new CExecResult();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CExecResult::CanPaste(UINT nClassID)
{
	if (nClassID == DVMCLASSID_CDVMDATA)
	{
		return TRUE;
	}

	return FALSE;
}

