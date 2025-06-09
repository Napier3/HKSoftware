#include "stdafx.h"
#include "ProcedureFactory.h"

#include "../../IotEngineGlobalDef.h"


CProcedureFactory::CProcedureFactory()
{

}

CProcedureFactory::~CProcedureFactory()
{

}

CPxPrcdrBase* CProcedureFactory::CreateProcedure(const CString &strPrcdrID)
{
	CPxPrcdrBase *pProcedure = NULL;

	return pProcedure;
}