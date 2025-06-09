#include "stdafx.h"
#include "IotEdgeEngineMngr.h"


CIotEdgeEngineMngr::CIotEdgeEngineMngr()
{

}

CIotEdgeEngineMngr::~CIotEdgeEngineMngr()
{

}

CIotEdgeEngineData *CIotEdgeEngineMngr::Create(const CString &strPpTemplateFile, const CString &strDeviceFile, const CString &strDeviceID)
{
	CIotEdgeEngineData *pNew = new CIotEdgeEngineData(strPpTemplateFile, strDeviceFile,strDeviceID);

	AddNewChild(pNew);

	return pNew;
}