#include "StdAfx.h"
#include "SttGlobalRtDataMngr.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttGlobalRtDataMngr::CSttGlobalRtDataMngr(void)
{
	m_nMode = STT_RT_DATA_MODE_NONE;
	m_pMacroChannelsMngr = NULL;
	m_pMacroChannels = NULL;
	m_pEventToVector = NULL;
	m_pEventToProgress = NULL;
	m_pEventToPower = NULL;
	m_pEventToLineVolt = NULL;
	m_pEventToSequence = NULL;
	m_nRtDataFlag = 0;
	m_bAutoMode = FALSE;
}

CSttGlobalRtDataMngr::~CSttGlobalRtDataMngr(void)
{
	if (m_pMacroChannelsMngr != NULL)
	{
		delete m_pMacroChannelsMngr;
		m_pMacroChannelsMngr = NULL;
	}

	if (m_pMacroChannels != NULL)
	{
		delete m_pMacroChannels;
		m_pMacroChannels = NULL;
	}
}

void CSttGlobalRtDataMngr::InitSoftResource(CSttTestResourceBase *pTestRerouce, CExBaseList *pChMaps)
{
	ASSERT(pTestRerouce);

	if (pTestRerouce->GetTestRsType() == STT_TEST_RESOURCE_TYPE_ASYNC)
	{
		m_nMode = STT_RT_DATA_MODE_ASYN;
		InitSoftResource_Async(pTestRerouce,pChMaps);
	}
	else
	{
		m_nMode = STT_RT_DATA_MODE_SYN;
		InitSoftResource_Sync(pTestRerouce,pChMaps);
	}

	InitGroup();//在软件资源创建成功后，对其进行分组
}

void CSttGlobalRtDataMngr::InitGroup()
{
	//ASSERT(pTestRerouce);

	if (m_nMode == STT_RT_DATA_MODE_ASYN)
	{
	}
	else
	{
		m_pMacroChannels->InitGroup();
	}
}

void CSttGlobalRtDataMngr::InitSoftResource_Sync(CSttTestResourceBase *pTestRerouce, CExBaseList *pChMaps)
{
	if (m_pMacroChannels == NULL)
	{
		m_pMacroChannels = new CSttMacroChannels;
	}

	m_pMacroChannels->ClearAllChs();

	CSttChResource *pSttChRs = NULL;
	CSttChMap *pChMap = NULL;
	POS pos = pTestRerouce->GetHeadPosition();

	while(pos)
	{
		pSttChRs = (CSttChResource*)pTestRerouce->GetNext(pos);
		pChMap = (CSttChMap*)pChMaps->FindByID(pSttChRs->m_strID);

		if (pChMap != NULL)//原则上软件资源里的通道，在映射文件中都会存在，只有在本地无映射文件对象且无Device文件时，无法自动创建缺省的通道映射文件
		{
			m_pMacroChannels->AddNewCh(pChMap->m_strAlias,pChMap->m_strID,pChMap);
			pSttChRs->m_bHasMapHdRs = pChMap->HasHdCh();
			pSttChRs->m_nHasMapType = pChMap->GetMapChsType();
			pSttChRs->m_nHasMapType = Global_GetCurrChType_Single(pSttChRs->m_nHasMapType,g_oSystemParas.m_nHasAnalog,g_oSystemParas.m_nHasDigital,g_oSystemParas.m_nHasWeek);
		} 
		else
		{
			pSttChRs->m_bHasMapHdRs = FALSE;
			m_pMacroChannels->AddNewCh(pSttChRs->m_strName,pSttChRs->m_strID,NULL);
		}
	}
}

void CSttGlobalRtDataMngr::InitSoftResource_Async(CSttTestResourceBase *pTestRerouce, CExBaseList *pChMaps)
{

}

void CSttGlobalRtDataMngr::AddMacroChValues(CSttParas *pParas)
{

}

void CSttGlobalRtDataMngr::SetMacroChValues(tmt_RtDataCh *pRtVector, long nChannelType, long nCount)
{

}

void CSttGlobalRtDataMngr::SetMacroChValue(tmt_RtDataCh *pRtVector, long nChannelType, long nChIndex)
{

}

void CSttGlobalRtDataMngr::SetMacroChValue(double dMag, double dAng, long nChannelType, long nChIndex)
{

}

void CSttGlobalRtDataMngr::SetMacroChValue(tmt_RtDataCh *pRtVector, const CString &strChID)
{

}

void CSttGlobalRtDataMngr::SetMacroChValue(double dMag, double dAng, const CString &strChID)
{

}

void CSttGlobalRtDataMngr::SetMacroChMagValue(double dMag, const CString &strChID)
{

}

void CSttGlobalRtDataMngr::SetMacroChAngValue(double dAng, const CString &strChID)
{

}

// void CSttGlobalRtDataMngr::RegisterRtDataChangeRcv(CSttRtDataChangeEvent * pEventRcv)
// {
// 
// }

void CSttGlobalRtDataMngr::FireRtDataChangeEvent()
{
	if (m_pEventToVector != NULL)
	{
		m_pEventToVector->OnRtDataChanged();
	}

	if (m_pEventToProgress != NULL)
	{
		m_pEventToProgress->OnRtDataChanged();
	}
	//2021-6-1  yangyijun
	if (m_pEventToPower != NULL)
	{
		m_pEventToPower->OnRtDataChanged();
	}

	if (m_pEventToLineVolt != NULL)
	{
		m_pEventToLineVolt->OnRtDataChanged();
	}
	
	if (m_pEventToSequence != NULL)
	{
		m_pEventToSequence->OnRtDataChanged();
	}
}

void CSttGlobalRtDataMngr::ClearHisDatas()
{
	if (m_nMode == STT_RT_DATA_MODE_ASYN)
	{
		m_pMacroChannels->ClearHisDatas();
	}
	else
	{
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
