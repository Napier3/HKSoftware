#include "StdAfx.h"
#include "CfgSclCmpParaObjects.h"

CCfgSclCmpParaObjects::CCfgSclCmpParaObjects(void)
{
}

CCfgSclCmpParaObjects::~CCfgSclCmpParaObjects(void)
{
}

CCfgSclCmpParaObject* CCfgSclCmpParaObjects::RegisterPara(const CString &strName,char **value,DWORD dwType, long nLength)
{
	CCfgSclCmpParaObject *pParaObj = NULL;

	pParaObj = new CCfgSclCmpParaObject(strName, value, dwType, nLength);
	AddTail(pParaObj);
	pParaObj->SetParent(this);

	return pParaObj;
}

CCfgSclCmpParaObject* CCfgSclCmpParaObjects::RegisterPara(const CString &strName, int *value,DWORD dwType, long nLength)
{
	CCfgSclCmpParaObject *pParaObj = NULL;

	pParaObj = new CCfgSclCmpParaObject(strName, value, dwType, nLength);
	AddTail(pParaObj);
	pParaObj->SetParent(this);

	return pParaObj;
}

CCfgSclCmpParaObject* CCfgSclCmpParaObjects::RegisterPara(const CString &strName, long *value,DWORD dwType, long nLength)
{
	CCfgSclCmpParaObject *pParaObj = NULL;

	pParaObj = new CCfgSclCmpParaObject(strName, value, dwType, nLength);
	AddTail(pParaObj);
	pParaObj->SetParent(this);

	return pParaObj;
}

CCfgSclCmpParaObject* CCfgSclCmpParaObjects::RegisterPara(const CString &strName, DWORD *value,DWORD dwType, long nLength)
{
	CCfgSclCmpParaObject *pParaObj = NULL;

	pParaObj = new CCfgSclCmpParaObject(strName, value, dwType, nLength);
	AddTail(pParaObj);
	pParaObj->SetParent(this);

	return pParaObj;
}

CCfgSclCmpParaObject* CCfgSclCmpParaObjects::RegisterPara(const CString &strName, float *value,DWORD dwType, long nLength)
{
	CCfgSclCmpParaObject *pParaObj = NULL;

	pParaObj = new CCfgSclCmpParaObject(strName, value, dwType, nLength);
	AddTail(pParaObj);
	pParaObj->SetParent(this);

	return pParaObj;
}

CCfgSclCmpParaObject* CCfgSclCmpParaObjects::RegisterPara(const CString &strName, double *value,DWORD dwType, long nLength)
{
	CCfgSclCmpParaObject *pParaObj = NULL;

	pParaObj = new CCfgSclCmpParaObject(strName, value, dwType, nLength);
	AddTail(pParaObj);
	pParaObj->SetParent(this);

	return pParaObj;
}

CCfgSclCmpParaObject* CCfgSclCmpParaObjects::RegisterPara(const CString &strName, unsigned char *value,DWORD dwType, long nLength)
{
	CCfgSclCmpParaObject *pParaObj = NULL;

	pParaObj = new CCfgSclCmpParaObject(strName, value, dwType, nLength);
	AddTail(pParaObj);
	pParaObj->SetParent(this);

	return pParaObj;
}

CCfgSclCmpParaObject* CCfgSclCmpParaObjects::RegisterPara(const CString &strName, short *value,DWORD dwType, long nLength)
{
	CCfgSclCmpParaObject *pParaObj = NULL;

	pParaObj = new CCfgSclCmpParaObject(strName, value, dwType, nLength);
	AddTail(pParaObj);
	pParaObj->SetParent(this);

	return pParaObj;
}

CCfgSclCmpParaObject* CCfgSclCmpParaObjects::RegisterPara(const CString &strName, CString *value,DWORD dwType, long nLength)
{
	CCfgSclCmpParaObject *pParaObj = NULL;

	pParaObj = new CCfgSclCmpParaObject(strName, value, dwType, nLength);
	AddTail(pParaObj);
	pParaObj->SetParent(this);

	return pParaObj;
}

void CCfgSclCmpParaObjects::FindPara(const CString &strID, CCfgSclCmpParaObject **ppFind, TPOS *pPos)
{
	CCfgSclCmpParaObject* pParaObj = NULL;
	TPOS pos = GetHeadPosition();
	TPOS posPrev = pos;

	while (pos != NULL)
	{
		posPrev = pos;
		pParaObj = (CCfgSclCmpParaObject*)GetNext(pos);

		if( pParaObj->CompareID(strID))
		{
			*ppFind = pParaObj;
			*pPos = posPrev;
			break;
		}
	}
}

void CCfgSclCmpParaObjects::FindPara(LPVOID pValAddr, CCfgSclCmpParaObject **ppFind, TPOS *pPos)
{
	CCfgSclCmpParaObject* pParaObj = NULL;
	TPOS pos = GetHeadPosition();
	TPOS posPrev = pos;

	while (pos != NULL)
	{
		posPrev = pos;
		pParaObj = (CCfgSclCmpParaObject*)GetNext(pos);

		if( pParaObj->CompareValAddr(pValAddr))
		{
			*ppFind = pParaObj;
			*pPos = posPrev;
			break;
		}
	}
}

void CCfgSclCmpParaObjects::UnRegisterPara(const CString &strID)
{
	CCfgSclCmpParaObject* pFind = NULL;
	TPOS pos = NULL;

	FindPara(strID, &pFind, &pos);

	if (pFind != NULL)
	{
		RemoveAt(pos);
		delete pFind;
	}
}

void CCfgSclCmpParaObjects::UnRegisterPara(LPVOID pValAddr)
{
	CCfgSclCmpParaObject* pFind = NULL;
	TPOS pos = NULL;

	FindPara(pValAddr, &pFind, &pos);

	if (pFind != NULL)
	{
		RemoveAt(pos);
		delete pFind;
	}
}

void CCfgSclCmpParaObjects::Compare(CCfgSclCmpParaObjects *pCmp)
{
	TPOS pos = pCmp->GetHeadPosition();
	CCfgSclCmpParaObject *pPara = NULL;

	while (pos != NULL)
	{
		pPara = (CCfgSclCmpParaObject *)pCmp->GetNext(pos);
		Compare(pPara);
	}
}


void CCfgSclCmpParaObjects::Compare(CCfgSclCmpParaObject *pCmp)
{
	CCfgSclCmpParaObject *pFind = (CCfgSclCmpParaObject*)FindByID(pCmp->m_strID);

	if (pFind != NULL)
	{
		pFind->Compare(pCmp);
	}
}


void CCfgSclCmpParaObjects::GetCmpParas(CExList &olistCmp, CExList &oListEmpty)
{
	TPOS pos = GetHeadPosition();
	CCfgSclCmpParaObject *pPara = NULL;

	while (pos != NULL)
	{
		pPara = (CCfgSclCmpParaObject *)GetNext(pos);
		
		if (pPara->m_pRef == NULL)
		{
			oListEmpty.AddTail(pPara);
		}
		else
		{
			olistCmp.AddTail(pPara);
		}
	}
}