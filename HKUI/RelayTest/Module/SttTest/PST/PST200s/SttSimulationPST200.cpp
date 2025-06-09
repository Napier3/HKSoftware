#include "stdafx.h"
#include "SttSimulationPST200.h"

CSttSimulationPST200::CSttSimulationPST200()
{
    Init();
    m_oHdChRcdDataMapsMngr.init();
}

void CSttSimulationPST200::Init()
{
    CSttSimulationBase::Init();
}

CSttSimulationPST200::~CSttSimulationPST200(void)
{

}

void CSttSimulationPST200::Stop()
{
    CSttSimulationBase::Stop();
}

void CSttSimulationPST200::StartTest(long nStateIdx)
{
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->SetTestStart(nStateIdx);
#endif
}

void CSttSimulationPST200::ReStart(long nStateIdx)
{
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->Load_RcdData();
#endif
}

void CSttSimulationPST200::OnRecordFinished()
{
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->Load_RcdData();
#endif
}

void CSttSimulationPST200::InitModuleCoef()
{
    for(int i = 0;i < 48;i++)
    {
        m_fCoefWeek[i] = 1;
        m_fCoefSmv[i] = 1;
    }
    m_nReplayChCntWeek = 0;
    m_nReplayChCntSwitch = 0;
    m_nReplayChCntSmv = 0;
    memset(m_pszRtdsMapType,0,128*4);
    long nRtdsMapTotal = m_pOutputMap->GetCount();
    long nChIdx;
    QString strMapId;

    for(int i = 0;i < nRtdsMapTotal;i++)
    {
        CPstRtdsFiberChMap* pFibCh = (CPstRtdsFiberChMap*)m_pOutputMap->GetAt(i);
        strMapId = pFibCh->m_strMap_Ch_Id;

        if(i == 0)
        {
			if(pFibCh->m_strMap_Ch_Id.contains("Uw")
					|| pFibCh->m_strMap_Ch_Id.contains("B"))
            {
                m_nOutputType = OutputType_WeekSwitch;
            }
            else if(pFibCh->m_strMap_Ch_Id.contains("Ud")
                    ||pFibCh->m_strMap_Ch_Id.contains("Id"))
            {
                m_nOutputType = OutputType_SmvGoose;
            }
            else
            {
                m_nOutputType = OutputType_Ft3;
            }
        }

        switch(m_nOutputType)
        {
        case OutputType_WeekSwitch:
        {
            m_fCoefWeek[i] = pFibCh->m_fCoef;
            if(pFibCh->m_strMap_Ch_Id.contains("Uw"))
            {
                m_pszRtdsMapType[i] = 1<<24;
                m_pszRtdsMapType[i] |= 1<<16;

                if(pFibCh->m_strMap_Ch_Id.contains("_"))
                {
                    strMapId = strMapId.split("_")[1];
                    nChIdx = strMapId.toInt();
                    m_pszRtdsMapType[i] |= nChIdx&0xFF;
                    m_nReplayChCntWeek++;
                }
            }
            else if(pFibCh->m_strMap_Ch_Id.contains("B"))
            {
                m_pszRtdsMapType[i] = 2<<24;
                m_pszRtdsMapType[i] |= 3<<16;
                strMapId = strMapId.replace("B","");
                nChIdx = strMapId.toInt();
                m_pszRtdsMapType[i] |= nChIdx&0xFF;
                m_nReplayChCntSwitch++;
            }
        }
            break;
        case OutputType_SmvGoose:
        {
            m_fCoefSmv[i] = pFibCh->m_fCoef;
            if(pFibCh->m_strMap_Ch_Id.contains("Ud"))
            {
                m_pszRtdsMapType[i] = 3<<24;
                m_pszRtdsMapType[i] |= 1<<16;
                if(pFibCh->m_strMap_Ch_Id.contains("_"))
                {
                    strMapId = strMapId.split("_")[1];
                    nChIdx = strMapId.toInt();
                    if(nChIdx < 13)
                    {
                        m_pszRtdsMapType[i] |= nChIdx&0xFF;
                        m_nReplayChCntSmv++;
                    }
                }
            }
            else if(pFibCh->m_strMap_Ch_Id.contains("Id"))
            {
                m_pszRtdsMapType[i] = 3<<24;
                m_pszRtdsMapType[i] |= 2<<16;
                if(pFibCh->m_strMap_Ch_Id.contains("_"))
                {
                    strMapId = strMapId.split("_")[1];
                    nChIdx = strMapId.toInt();
                    if(nChIdx < 13)
                    {
                        m_pszRtdsMapType[i] |= nChIdx&0xFF;
                        m_nReplayChCntSmv++;
                    }
                }
            }
            else if(pFibCh->m_strMap_Ch_Id.contains("B"))
            {
                m_pszRtdsMapType[i] = 3<<24;
                m_pszRtdsMapType[i] |= 3<<16;
            }
        }
            break;
        case OutputType_Ft3:
        {

        }
        }
    }
}
