#pragma once

#include "IotEdgeEngineMngr.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"

class CIotEdgeEngineBaseApp
{
public:
	CIotEdgeEngineBaseApp();
	virtual ~CIotEdgeEngineBaseApp();

	CIotEdgeEngineMngr m_oIotEdgeEngineMngr;
	CAutoCriticSection m_oEngineDataCriticSection;

public:
	void InitIotEdgeEngineBaseApp();
	void ExitIotEdgeEngineBaseApp();

	CIotEdgeEngineData* FindEngineData(const CString &strID);
	CIotEdgeEngineData* Create(const CString &strPpTemplateFile, const CString &strDeviceFile, const CString &strDeviceID);  //新建设备
};