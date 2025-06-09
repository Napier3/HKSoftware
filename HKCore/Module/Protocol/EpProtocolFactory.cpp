#include "StdAfx.h"
#include "EpProtocolFactory.h"

#include "101\EpProtocol101.h"
#include "101\EpProtocol104.h"

long CEpProtocolFactory::g_nProtocolFactoryRef = 0;
CEpProtocolFactory* CEpProtocolFactory::g_pEpFactory = NULL;

CEpProtocolFactory* CEpProtocolFactory::Create()
{
	g_nProtocolFactoryRef++;

	if (g_nProtocolFactoryRef == 1)
	{
		g_pEpFactory = new CEpProtocolFactory();
		g_pEpFactory->RegisterProtocols();
	}

	return g_pEpFactory;
}

void CEpProtocolFactory::Release()
{
	g_nProtocolFactoryRef--;

	if (g_nProtocolFactoryRef == 0)
	{
		delete g_pEpFactory;
		g_pEpFactory = NULL;
	}
}

CEpProtocolFactory::CEpProtocolFactory()
{
	
}

CEpProtocolFactory::~CEpProtocolFactory()
{
	
}


void CEpProtocolFactory::RegisterProtocol(const CString &strName, const CString &strID, DWORD dwProtocolID, EPPCREATE* pFunCreate)
{
	CEpProtocolCreator* pEpProtocolCreator = NULL;
	pEpProtocolCreator = new CEpProtocolCreator(strName, strID, dwProtocolID, pFunCreate);
	AddTail(pEpProtocolCreator);
	pEpProtocolCreator->SetParent(this);
}

CProtocolBase* CEpProtocolFactory::CreateProtocolByID(const CString &strID)
{
	ASSERT (g_pEpFactory != NULL);
	CEpProtocolCreator* pEpProtocolCreator = (CEpProtocolCreator*)g_pEpFactory->FindByID(strID);

	if (pEpProtocolCreator != NULL)
	{
		return pEpProtocolCreator->Create();
	}

	return NULL;
}


CProtocolBase* CEpProtocolFactory::CreateProtocolByIndex(long nIndex)
{
	CEpProtocolCreator* pEpProtocolCreator;
	long nCount = g_pEpFactory->GetCount();
	
	if(nIndex < nCount)
	{
		pEpProtocolCreator = (CEpProtocolCreator*)g_pEpFactory->GetAt(nIndex);
		return pEpProtocolCreator->Create();
	}
	
	return NULL;
}

CProtocolBase* CEpProtocolFactory::CreateProtocolByID(DWORD dwProtocolID)
{
	CEpProtocolCreator* pEpProtocolCreator = NULL;
	CProtocolBase* pProtocol = NULL;
	POS pos = g_pEpFactory->GetHeadPosition();

	while (pos != NULL)
	{
		pEpProtocolCreator = (CEpProtocolCreator*)g_pEpFactory->GetNext(pos);

		if (pEpProtocolCreator->IsProtocol(dwProtocolID) )
		{
			pProtocol = pEpProtocolCreator->Create();
			break;
		}
	}

	return pProtocol;
}

void CEpProtocolFactory::RegisterProtocols()
{
	RegisterProtocol(_T("标准101"), _T("101"), EPPROTOCOL_101, CEpProtocol101::CreateProtocol);
	RegisterProtocol(_T("标准104"), _T("104"), EPPROTOCOL_104, CEpProtocol104::CreateProtocol);
}

