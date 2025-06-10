#include "SttDevicePN466.h"

CSttDevicePN466 *CSttDevicePN466::g_pSttDevicePN466=NULL;
long CSttDevicePN466::g_nSttDeviceRef = 0;

CSttDevicePN466::CSttDevicePN466()
{

}

CSttDevicePN466::~CSttDevicePN466()
{

}

void CSttDevicePN466::Create()
{
    g_nSttDeviceRef++;

    if (g_nSttDeviceRef == 1)
    {
        g_pSttDevicePN466=new CSttDevicePN466;
        g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDevicePN466;
    }
}

void CSttDevicePN466::Release()
{
    g_nSttDeviceRef--;

    if (g_nSttDeviceRef == 0)
    {
        delete g_pSttDevicePN466;
        g_pSttDevicePN466 = NULL;
    }
}

int CSttDevicePN466::InitDevice(BOOL bHasAdjFile)
{
    m_nCommfd=open("/dev/SttDriver_PN466",O_RDWR);
	g_nStateCount = read(m_nCommfd,NULL,0x201);
	g_theDeviceSystemParameter->m_oDeviceAttrs.m_nStateCount = g_nStateCount;
	InitBuff();
    m_pDegressMsg = (Drv_DegressMsg *)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, m_nCommfd, 0);
#ifdef _PSX_QT_LINUX_
    qDebug()<<"Driver Mmap = "<<m_pDegressMsg;
#endif
    InitDApara(m_nCommfd,bHasAdjFile);

    //VOLT
    for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
    {
        PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_U[nIndex];
        if(pModule==NULL)
            continue;

        CSttPowerCtrlBase *pCSttPowerCtrlBase=pModule->m_oModuleAttr.m_pPowerCtrlBase;
        if(pCSttPowerCtrlBase==NULL)
        {
            pModule->m_oModuleAttr.m_pPowerCtrlBase=(CSttPowerCtrlBase*)(new CSttPowerCtrlV130_PN);
        }
    }

    //CURRENT
    for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
    {
        PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nIndex];
        if(pModule==NULL)
            continue;

        CSttPowerCtrlBase *pCSttPowerCtrlBase=pModule->m_oModuleAttr.m_pPowerCtrlBase;
        if(pCSttPowerCtrlBase==NULL)
            pModule->m_oModuleAttr.m_pPowerCtrlBase=(CSttPowerCtrlBase*)(new CSttPowerCtrlC20);
    }

    return m_nCommfd;
}

void CSttDevicePN466::GetVoltCurRtData()
{
    CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
    if(pSttTestBase == NULL)
        return;

    GetRtData();
}

void CSttDevicePN466::SetOutputTime(tmt_ManualTest *pManualTest, tmt_HarmTest *pHarmTest)
{
	if(!g_theSystemConfig->m_nHasAnalog)
	{
		return;
	}

	tmt_channel *pChannel = NULL;
	BOOL bIsManualTest = FALSE;

	if(pManualTest != NULL)
	{
		pChannel = pManualTest->m_oManuParas.m_uiCUR;
		bIsManualTest = TRUE;
	}

	if(pHarmTest != NULL)
	{
		pChannel = pHarmTest->m_oHarmParas.m_uiCUR;
	}

	if(pChannel == NULL)
	{
		return;
	}

	PSTT_MODULE pModule;
	float fOutPutTimeMin = 100.0;

	for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_I; i++)
	{
		pModule = g_theDeviceSystemParameter->m_oModules_I[i];

		if(pModule == NULL)
		{
			continue;
		}

		float fIMax = 0;
		float fAmp;
		long nChannelNum = pModule->m_oModuleAttr.m_nChannelNum;

		for(int k = 0; k < nChannelNum; k++)
		{
			m_nTmtPos = pModule->m_nChTmtPos[k];

			if(m_nTmtPos < 0)
			{
				continue;
			}

			fAmp = pChannel[m_nTmtPos].Harm[1].fAmp;

			if(!bIsManualTest)
			{
				for(int i = 2; i <= 31; i++)
				{
					fAmp += pChannel[m_nTmtPos].Harm[i].fAmp;
				}
			}

			if(fAmp > fIMax)
			{
				fIMax = fAmp;
			}
		}

		if(bIsManualTest)
		{
			if(pManualTest->m_oManuParas.m_bDC)
			{
				fIMax = fIMax * 2;
			}
		}

		if(fIMax < 10.001)
		{
			continue;//小于10A，不限时
		}

		long nPowerMode = STT_CurrentMODULE_POWER_HIGH;

		for(int nIndex = 0; nIndex < g_theSystemConfig->m_oGearSetCurModules.m_nCurModuleNum; nIndex++)
		{
			tmt_CurModuleGear &oCurModuleGear = g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nIndex];

			if(oCurModuleGear.m_nModulePos == pModule->m_oModuleAttr.m_nModuleIndex)
			{
				nPowerMode = oCurModuleGear.m_nIPowerMode;
				break;
			}
		}

		float fOutPutTime = 0;
		if(nPowerMode == STT_CurrentMODULE_POWER_HIGH)
		{
			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_CURRENT_C20)
			{
				fOutPutTime = 0.4 * 20 * 20.0 / fIMax;
			}
			else
			{
				//32A模块
				fOutPutTime = 0.4 * 20 * 30.0 / fIMax;
			}
		}
		else
		{
			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_CURRENT_C20)
			{
				fOutPutTime = 20 * 20.0 / fIMax;
			}
			else
			{
				//32A模块
				fOutPutTime = 20 * 30.0 / fIMax;
			}
		}

		if(fOutPutTime < fOutPutTimeMin)
		{
			fOutPutTimeMin = fOutPutTime;
		}
	}


	if(fOutPutTimeMin > 99.0)
		fOutPutTimeMin = 0;//不限时

	if(bIsManualTest)
	{
		pManualTest->m_oManuParas.m_fOutPutTime = fOutPutTimeMin;
	}
	else
	{
		pHarmTest->m_oHarmParas.m_fOutPutTime = fOutPutTimeMin;
	}
}
