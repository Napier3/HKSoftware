#include "StdAfx.h"
#include "CfgSclCmpData.h"

CCfgSclCmpData::CCfgSclCmpData(void)
{
	m_pDataParas = new CCfgSclCmpParaObjects();
}

CCfgSclCmpData::~CCfgSclCmpData(void)
{
	delete m_pDataParas;
	DeleteAll();
}

CCfgSclCmpParaObjects* CCfgSclCmpData::CreateNewChParaObjects(const CString &strName)
{
	CCfgSclCmpParaObjects *pParas = new CCfgSclCmpParaObjects();

	if (strName.GetLength() > 1)
	{
		pParas->m_strName = strName;
	}
	else
	{
		pParas->m_strName.Format(_T("Í¨µÀ%d"), GetCount()+1);
	}

	pParas->m_strID = pParas->m_strName;
	AddNewChild(pParas);

	return pParas;
}

void CCfgSclCmpData::Compare(CCfgSclCmpData *pCmp)
{
	m_pDataParas->Compare(pCmp->m_pDataParas);

	TPOS posSrc = GetHeadPosition();
	TPOS posDest = pCmp->GetHeadPosition();
	CCfgSclCmpParaObjects *pChSrc = NULL;
	CCfgSclCmpParaObjects *pChDest = NULL;

	while (posSrc != NULL && posDest != NULL)
	{
		pChSrc = (CCfgSclCmpParaObjects *)GetNext(posSrc);
		pChDest = (CCfgSclCmpParaObjects *)pCmp->GetNext(posDest);
		pChSrc->Compare(pChDest);
	}
}

