#pragma once

#include "IotEdgeEngineData.h"

class CIotEdgeEngineMngr:public CExBaseList
{//�Ӷ���ΪCIotEdgeEngineData
public:
	CIotEdgeEngineMngr();
	virtual ~CIotEdgeEngineMngr();

	CIotEdgeEngineData *Create(const CString &strPpTemplateFile, const CString &strDeviceFile, const CString &strDeviceID);


};