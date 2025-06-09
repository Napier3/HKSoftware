#include "stdafx.h"
#include "EpDevWndFactory.h"

CEpDevWndFactory* CEpDevWndFactory::g_pEpDevWndFactory = NULL;
long CEpDevWndFactory::m_nEpDevWndFactoryRef = 0;

CEpDevWndFactory::CEpDevWndFactory()
{
}

CEpDevWndFactory::~CEpDevWndFactory()
{

}

CEpDevBase* CEpDevWndFactory::CreateDevWnd(CExBaseObject* pData,CWnd* pParentWnd)
{
	UINT ClassID = pData->GetClassID();
	CEpDevBase* pObj = g_pEpDevWndFactory->CreateDevWnd(ClassID, pParentWnd, pData);

	return pObj;
}

CEpDevBase* CEpDevWndFactory::CreateDevWnd(UINT nDataClassID,CWnd* pParentWnd,CExBaseObject* pData)
{
	CEpDevBase* pDevBase = g_pEpDevWndFactory->Create(nDataClassID);
	
	ASSERT(pDevBase != NULL);

	if (pDevBase == NULL)
	{
		return NULL;
	}

	pDevBase->m_pData = pData;
	pDevBase->m_nDataClassID = nDataClassID;
	pDevBase->UICreate(pParentWnd);

	return pDevBase;
}

CEpDevBase* CEpDevWndFactory::CreateDevWnd(CExBaseObject* pData, CWnd* pParentWnd, CEpDevBaseList* pDevParent)
{
	CEpDevBase* pDevBase = g_pEpDevWndFactory->CreateDevWnd(pData,pParentWnd);
	ASSERT(pDevBase != NULL);

	pDevParent->AddTail(pDevBase);
	pDevBase->SetParent(pDevParent);

	return pDevBase;
}

