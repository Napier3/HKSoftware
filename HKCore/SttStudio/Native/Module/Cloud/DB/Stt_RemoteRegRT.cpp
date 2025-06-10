//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Stt_RemoteRegRT.cpp  CStt_RemoteRegRT


#include "stdafx.h"
#include "Stt_RemoteRegRT.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CStt_RemoteRegRT::CStt_RemoteRegRT()
{
	//��ʼ������

	//��ʼ����Ա����
}

CStt_RemoteRegRT::~CStt_RemoteRegRT()
{
}

void CStt_RemoteRegRT::InitAfterRead()
{
}

BOOL CStt_RemoteRegRT::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CStt_RemoteRegHis::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CStt_RemoteRegRT *p = (CStt_RemoteRegRT*)pObj;

	return TRUE;
}

BOOL CStt_RemoteRegRT::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CStt_RemoteRegHis::CopyOwn(pDest);

	CStt_RemoteRegRT *p = (CStt_RemoteRegRT*)pDest;

	return TRUE;
}

CBaseObject* CStt_RemoteRegRT::Clone()
{
	CStt_RemoteRegRT *p = new CStt_RemoteRegRT();
	Copy(p);
	return p;
}

CBaseObject* CStt_RemoteRegRT::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CStt_RemoteRegRT *p = new CStt_RemoteRegRT();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CStt_RemoteRegRT::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTT_REMOTEUSERRT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CStt_RemoteRegRT::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCStt_RemoteUserRTKey)
	{
		pNew = new CStt_RemoteUserRT();
	}

	return pNew;
}

CExBaseObject* CStt_RemoteRegRT::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTT_REMOTEUSERRT)
	{
		pNew = new CStt_RemoteUserRT();
	}

	return pNew;
}
CExBaseObject* CStt_RemoteRegRT::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CStt_RemoteUserRT();

	return pNew;
}

CStt_RemoteUserRT *CStt_RemoteRegRT::FindMacthUser(CStt_RemoteUserRT *pUser)
{
	POS pos = GetHeadPosition();
	CStt_RemoteUserRT *pFind = NULL;

	while (pos != NULL)
	{
		pFind = (CStt_RemoteUserRT *)GetNext(pos);

		if (pFind->IsEqualOwn(pUser))
		{
			return pFind;
		}
	}

	return NULL;
}

CStt_RemoteUserRT *CStt_RemoteRegRT::FindByIDTest(DWORD nDestID)
{
	POS pos = GetHeadPosition();
	CStt_RemoteUserRT *pFind = NULL;

	while (pos != NULL)
	{
		pFind = (CStt_RemoteUserRT *)GetNext(pos);

		if (pFind->m_nID_Test == nDestID)
		{
			return pFind;
		}
	}

	return NULL;
}

void CStt_RemoteRegRT::ClearOtherAuthoritys(CExBaseList *pParas, CStt_RemoteUserRT *pCurrUser
										,CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CStt_RemoteUserRT *p = NULL;

	while(pos != NULL)
	{
		p = (CStt_RemoteUserRT *)GetNext(pos);

		if (p == pCurrUser)
		{
			continue;
		}

		//ȡ�������û���Ȩ�ޣ�ȡ����Ȩ��Ϊ��ǰ�û���Ȩ��Ȩ��
		p->ClearAuthoritys(pParas,pXDbLib,pXmlRWKeys);
	}
}