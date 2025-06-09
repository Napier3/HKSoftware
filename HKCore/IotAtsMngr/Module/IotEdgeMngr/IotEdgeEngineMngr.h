#pragma once

#include "IotEdgeEngineData.h"

class CIotEdgeEngineMngr:public CExBaseList
{//子对象为CIotEdgeEngineData
public:
	CIotEdgeEngineMngr();
	virtual ~CIotEdgeEngineMngr();

	CIotEdgeEngineData *Create(const CString &strPpTemplateFile, const CString &strDeviceFile, const CString &strDeviceID);


};