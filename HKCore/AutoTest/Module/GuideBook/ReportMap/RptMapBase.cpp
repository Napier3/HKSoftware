#include "StdAfx.h"
#include "RptMapBase.h"
#include "RptBkmk.h"
#include "RptData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CRptMapBase::CRptMapBase(void)
{

}

CRptMapBase::~CRptMapBase(void)
{
	//DeleteAll();
}


CExBaseObject* CRptMapBase::FindBkmk(const CString  &strBkmk)
{
	return FindBkmkInList(strBkmk ,(CExBaseList*)this);
}

void CRptMapBase::InsertBkmk(const CString  &strBkmk)//在什么位置插入书签
{

}

CExBaseObject* CRptMapBase::FindItemByID(const CString  &strID)//可以查找的有Items，Item，Datas，Data
{
	//return _FindTheItemByID(this, strID);
	return NULL;
}

CRptData* CRptMapBase::AddNewRptData(const CString  &strName, const CString  &strID, const CString &strPrecision)
{
	CRptData *pRptData = new CRptData(strName, strID, strPrecision);
	AddTail(pRptData);
	pRptData->SetParent(this);

	if (strName.GetLength() == 0)
	{
		pRptData->m_strName = strID;
	}

	return pRptData;
}

BOOL CRptMapBase::HasBkmk()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	BOOL bHas = FALSE;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == RPTCLASSID_RPTDATA)
		{
			CRptData *pData = (CRptData*)p;
			bHas |= (pData->GetCount() > 0);
		}
	}

	return bHas;
}

CExBaseObject* CRptMapBase::FindBkmkInList(const CString&  strBkmk, CExBaseList* pList)
{
	ASSERT(pList != NULL);
	LONG nCount = pList->GetCount();
	CExBaseObject* pRObj = NULL;
	CExBaseObject* pObj = NULL;

	for (int i=0; i<nCount; i++)
	{
		pObj = pList->GetAt(i);

		if (pObj->IsBaseList())
		{
			pRObj = FindBkmkInList(strBkmk,(CExBaseList*)pObj);
			if (pRObj != NULL)
			{
				break;
			}
		}
		else
		{
			if (strBkmk == pObj->m_strID)
			{
				pRObj = pObj;
				break;
			}
		}
	}

	return pRObj;
}

void CRptMapBase::ClearDWData()
{
	POS pos = GetHeadPosition();
	CExBaseObject* p = NULL;
	UINT nClassID = 0;
	m_dwItemData = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();
		
		if (nClassID == RPTCLASSID_RPTDATA)
		{
			((CRptData*)p)->ClearDWData();
		}
	}
}

