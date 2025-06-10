#include "StdAfx.h"
#include "SttTestBase.h"

#include "../../../Module/System/TickCount32.h"

#include "../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../SttDevice/SttDeviceBase.h"
#endif

long g_nRtDataVoltCnt = MAX_VOLTAGE_COUNT;
long g_nRtDataCurrCnt = MAX_CURRENT_COUNT;
BOOL g_bUpdateFPGA = FALSE;
BOOL g_bNeedReadDeviceStatatus = TRUE;
tmt_AsyncManualTest *g_pAsyncManualTest = NULL;
tmt_AsyncStateTest *g_pAsyncStateTest = NULL;
//////////////////////////////////////////////////////////////////////////
//CSttTestBase
CSttTestBase::CSttTestBase(void)
{
    m_bIsTestChanged = FALSE;

    m_bIsSearchMode = 0;
    m_bIsTestChanged = 0;
    m_fAbsError = 0;
    m_fRelError = 0;
    m_nRsltJdg = 1;
    m_nRsltDsc = 1;

    SetTestStarting(FALSE);
}

CSttTestBase::~CSttTestBase(void)
{
}

void CSttTestBase::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{

}

void CSttTestBase::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{

}

void CSttTestBase::SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{

}

void CSttTestBase::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
}

void CSttTestBase::Report_XmlSerialize_WithPara(CSttXmlSerializeBase *pXmlSerialize)
{
    ASSERT(stt_xml_serialize_is_write(pXmlSerialize));
    Para_XmlSerialize(pXmlSerialize);
    Report_XmlSerialize(pXmlSerialize);
}

//2020-04-9  扩展测试功能对应的底层测试功能
void CSttTestBase::Para_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize)
{
    //缺省：为自身对象，例如状态序列、手动测试、递变等
    Para_XmlSerialize(pXmlSerialize);
}

void CSttTestBase::Report_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize)
{
    //缺省：为自身对象，例如状态序列、手动测试、递变等
    Report_XmlSerialize(pXmlSerialize);
}

void CSttTestBase::Report_XmlSerialize_WithPara_Basic(CSttXmlSerializeBase *pXmlSerialize)
{
    //缺省：为自身对象，例如状态序列、手动测试、递变等
    Para_XmlSerialize_Basic(pXmlSerialize);
    Report_XmlSerialize_Basic(pXmlSerialize);
}

//2020-10-26  lijunqing 底层驱动结构体的XML串行化
void CSttTestBase::Para_XmlSerialize_Drv(CSttXmlSerializeBase *pXmlSerialize)
{

}

void CSttTestBase::Report_XmlSerialize_Drv(CSttXmlSerializeBase *pXmlSerialize)
{

}

void CSttTestBase::Report_XmlSerialize_WithPara_Drv(CSttXmlSerializeBase *pXmlSerialize)
{
    Para_XmlSerialize_Drv(pXmlSerialize);
    Report_XmlSerialize_Drv(pXmlSerialize);
}


BOOL CSttTestBase::EventProcess()
{
    return FALSE;
}

BOOL CSttTestBase::EventProcessEx()
{
	return FALSE;
}

void CSttTestBase::Init()
{	
    m_pDrvResults=stt_test_get_drvresult_buff();
    m_nCurStateLoopIndex = 0;
    m_nCurStateIndex = -1;
    m_nCurStepIndex = -1;
    m_bBinStopTest = FALSE;
	g_bUpdateFPGA = FALSE;
	g_bNeedReadDeviceStatatus = TRUE;
    for(int i = 0;i < 100;i++)
    {
        m_nStateNum[i] = -1;
    }
}

long CSttTestBase::GetStateNum(long nStateIndex)
{
    if(nStateIndex < 0 || nStateIndex >= 100)
    {
        return -1;
    }
    else
    {
        return m_nStateNum[nStateIndex];
    }
}

void CSttTestBase::StartTest()
{
    m_dwHasPostFinishMsg = 0;		//MODIFY
#ifdef _PSX_QT_LINUX_
    m_dwBeginTickCount = 0;
    m_dwCurTickCount = 0;
#else
    m_dwBeginTickCount = ::GetTickCount();
#endif
}

void CSttTestBase::UpdateParameter()
{

}

long CSttTestBase::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttTestBase::Stop()
{
#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
#endif
#endif
    SetTestStarting(FALSE);
}

/*
void CSttTestBase::RegisterRsltJdg(CSttParaObjects *pParas)
{
    pParas->RegisterPara("结果判断", "RsltJdg", "", "number", "0",  &m_nRsltJdg);
    pParas->RegisterPara("结果描述", "RsltDsc", "", "number", "0",  &m_nRsltDsc);
}

void CSttTestBase::RegisterResultsCommon(CSttParaObjects *pParas)
{
    pParas->RegisterPara("绝对误差", "AbsError", "", "number", "0",  &m_fAbsError);
    pParas->RegisterPara("相对误差", "RelError", "", "number", "0",  &m_fRelError);
    pParas->RegisterPara("扩展结果1", "RsltEx1", "", "number", "0",  &m_nResult01);
    pParas->RegisterPara("扩展结果2", "RsltEx2", "", "number", "0",  &m_nResult02);
    pParas->RegisterPara("扩展结果3", "RsltEx3", "", "number", "0",  &m_nResult03);
    pParas->RegisterPara("扩展结果4", "RsltEx4", "", "number", "0",  &m_nResult04);
}
*/

//获取测试从开始到现在的时间长度
DWORD CSttTestBase::CalTestUseTimeLong()
{
#ifdef _PSX_QT_LINUX_
    DWORD dwCurr = m_dwCurTickCount;
#else
    DWORD dwCurr = ::GetTickCount()/1000;
#endif
    DWORD dwLong = 0;

    if (m_dwBeginTickCount > dwCurr)
    {
        dwLong = (~m_dwBeginTickCount);
        dwLong += dwCurr;
    }
    else
    {
        dwLong = dwCurr - m_dwBeginTickCount;
    }

    return dwLong;
}


BOOL CSttTestBase::IsTestTimeFinished(long nS)
{
    return (CalTestUseTimeLong() > (DWORD)nS);
}

BOOL CSttTestBase::IsTestOverTime(long nMsEx)
{
    double dtime = GetTestTimeLong();
    long nTestTimeLong = (long)(dtime * 1000.0f + nMsEx);
    long nUseTimeLong = CalTestUseTimeLong();

    if (nUseTimeLong > nTestTimeLong)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("IsTestOverTime超时(%d>(%d*1000+%d)),%s=%x"),nUseTimeLong , dtime, nMsEx,this->m_strName.GetString(),this);
    }

    return (nUseTimeLong > nTestTimeLong);
}

float CSttTestBase::GetTimeFromLong(UINT nS,UINT nnS)
{
    return nS+nnS/1000000000.0f;
}

void CSttTestBase::ReturnTestStateEvent(long nEventType, double dTime, double dRealTime, bool bWithEvent)
{
    STT_TIME oTime;
    oTime.dRealTime = dRealTime;
    oTime.dTime = dTime;
    oTime.dBinActTime = -1;

    CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
    pTestServer->ReturnTestStateEvent(nEventType, &oTime, bWithEvent);
}

void CSttTestBase::ReturnTestStateEvent_SearchPoint(double dTime, double dRealTime, bool bWithEvent)
{
	STT_TIME oTime;
	oTime.dRealTime = dRealTime;
	oTime.dTime = dTime;
	oTime.dBinActTime = -1;

	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
	pTestServer->ReturnTestStateEvent(SttResult_Type_SearchPointReport, &oTime, bWithEvent);
}

void CSttTestBase::ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
{
    STT_TIME oTime;
    oTime.dRealTime = dRealTime;
    oTime.dTime = dTime;
    oTime.dBinActTime = -1;

    CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
    pTestServer->ReturnTestStateEvent(SttResult_Type_TestStart, &oTime, bWithEvent);
}

void CSttTestBase::ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
{
    STT_TIME oTime;
    oTime.dRealTime = dRealTime;
    oTime.dTime = dTime;
    oTime.dBinActTime = -1;

    CalReport();//zhouhj 20210613在返回测试结束消息时,计算报告结果值

    CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
    pTestServer->ReturnTestStateEvent(SttResult_Type_TestFinish, &oTime, bWithEvent);
	SetTestStarting(FALSE);//20231121 zhoulei
}

void CSttTestBase::ReturnRealTimeEvent()
{
    CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();

    //2020-10-23  lijunqing
    //锁定，锁定状态下才能定时上报，在一定程度上避免重复上报
#ifndef _STT_NOT_IN_TEST_SERVER_
    stt_test_event_set_lock(1);
    pTestServer->ReturnTestEvents();
    stt_test_event_set_lock(0);
#endif
}

void CSttTestBase::InitParaBeforeGradient(tmt_GradientParas *pTmt_GradientParas,long nGradientChCount)
{
    InitParaBeforeGradient_Chs(pTmt_GradientParas,nGradientChCount,nGradientChCount);
#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
    memset(CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess.m_bUChange,0,sizeof(bool)*3*GRADIENT_CHAN_COUNT);
    memset(CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess.m_bIChange,0,sizeof(bool)*3*GRADIENT_CHAN_COUNT);
#endif
#endif
}

void CSttTestBase::InitParaBeforeGradient_Chs(tmt_GradientParas *pTmt_GradientParas,long nCurrentChCount,long nVoltageChCount)
{
	float fAngleVoltage[6] = {0, -120.0, 120.0, 0, -120.0, 120.0};//20220719 zhouhj 增加电压电流相序设置功能
	float fAngleCurrent[6] = {0, -120.0, 120.0, 0, -120.0, 120.0};

	if (pTmt_GradientParas->m_nPhaseSet[0] == 1)//电压相序负序
	{
		fAngleVoltage[1] = 120.0f;
		fAngleVoltage[2] = -120.0f;
		fAngleVoltage[4] = 120.0f;
		fAngleVoltage[5] = -120.0f;
	}
	else if (pTmt_GradientParas->m_nPhaseSet[0] == 2)//电压相序零序
	{
		fAngleVoltage[1] = 0.0f;
		fAngleVoltage[2] = 0.0f;
		fAngleVoltage[4] = 0.0f;
		fAngleVoltage[5] = 0.0f;
	}

	if (pTmt_GradientParas->m_nPhaseSet[1] == 1)//电流相序负序
	{
		fAngleCurrent[1] = 120.0f;
		fAngleCurrent[2] = -120.0f;
		fAngleCurrent[4] = 120.0f;
		fAngleCurrent[5] = -120.0f;
	}
	else if (pTmt_GradientParas->m_nPhaseSet[1] == 2)//电流相序零序
	{
		fAngleCurrent[1] = 0.0f;
		fAngleCurrent[2] = 0.0f;
		fAngleCurrent[4] = 0.0f;
		fAngleCurrent[5] = 0.0f;
	}

	if (nCurrentChCount == 6)
	{
		for(int i=3;i<6;i++)//6I电流差动使用
		{
			fAngleVoltage[i]=fAngleVoltage[i]-pTmt_GradientParas->m_fDiffIAngle;
			fAngleCurrent[i]=fAngleCurrent[i]-pTmt_GradientParas->m_fDiffIAngle;
		}
		//6U6I软件资源
	}

	//变化前,额定
	for(int i=0;i<GRADIENT_CHAN_COUNT;i++)
	{
		if(i<nVoltageChCount)
		{
			pTmt_GradientParas->m_uiVOL[0][i].Harm[0].fAmp=0;
			pTmt_GradientParas->m_uiVOL[0][i].Harm[1].fAmp=pTmt_GradientParas->m_fEDU;
			pTmt_GradientParas->m_uiVOL[0][i].Harm[1].fFreq=pTmt_GradientParas->m_fEDFreq;
			pTmt_GradientParas->m_uiVOL[0][i].Harm[1].fAngle=fAngleVoltage[i];
		}
		else
		{
			pTmt_GradientParas->m_uiVOL[0][i].Harm[0].fAmp=0;
			pTmt_GradientParas->m_uiVOL[0][i].Harm[1].fAmp=0;
		}
	}

	for(int i=0;i<GRADIENT_CHAN_COUNT;i++)
	{
		if(i<nCurrentChCount)
		{
			pTmt_GradientParas->m_uiCUR[0][i].Harm[0].fAmp=0;
			pTmt_GradientParas->m_uiCUR[0][i].Harm[1].fAmp=pTmt_GradientParas->m_fEDI;
			pTmt_GradientParas->m_uiCUR[0][i].Harm[1].fFreq=pTmt_GradientParas->m_fEDFreq;
			pTmt_GradientParas->m_uiCUR[0][i].Harm[1].fAngle=fAngleCurrent[i]-pTmt_GradientParas->m_fEDUaIaAngle;
		}
		else
		{
			pTmt_GradientParas->m_uiCUR[0][i].Harm[0].fAmp=0;
			pTmt_GradientParas->m_uiCUR[0][i].Harm[1].fAmp=0;
		}
	}
	//故障前
	for(int i=0;i<GRADIENT_CHAN_COUNT;i++)
	{
		if(i<nVoltageChCount)
		{
			pTmt_GradientParas->m_uiVOL[1][i].Harm[0].fAmp=0;
			pTmt_GradientParas->m_uiVOL[1][i].Harm[1].fAmp=(i<3)?pTmt_GradientParas->m_fG1Volt:pTmt_GradientParas->m_fG2Volt;
			pTmt_GradientParas->m_uiVOL[1][i].Harm[1].fFreq=pTmt_GradientParas->m_fHz;
			pTmt_GradientParas->m_uiVOL[1][i].Harm[1].fAngle=fAngleVoltage[i];
		}
		else
		{
			pTmt_GradientParas->m_uiVOL[1][i].Harm[0].fAmp=0;
			pTmt_GradientParas->m_uiVOL[1][i].Harm[1].fAmp=0;
		}
	}
	for(int i=0;i<GRADIENT_CHAN_COUNT;i++)
	{
		if(i<nCurrentChCount)
		{
			pTmt_GradientParas->m_uiCUR[1][i].Harm[0].fAmp=0;
			pTmt_GradientParas->m_uiCUR[1][i].Harm[1].fAmp=(i<3)?pTmt_GradientParas->m_fG1Current:pTmt_GradientParas->m_fG2Current;
			pTmt_GradientParas->m_uiCUR[1][i].Harm[1].fFreq=pTmt_GradientParas->m_fHz;
			pTmt_GradientParas->m_uiCUR[1][i].Harm[1].fAngle=fAngleCurrent[i]-pTmt_GradientParas->m_fEDUaIaAngle;
		}
		else
		{
			pTmt_GradientParas->m_uiCUR[1][i].Harm[0].fAmp=0;
			pTmt_GradientParas->m_uiCUR[1][i].Harm[1].fAmp=0;
		}
	}

	//故障态参数
	for(int i=0;i<GRADIENT_CHAN_COUNT;i++)
	{
		if(i<nVoltageChCount)
		{
			pTmt_GradientParas->m_uiVOL[2][i].Harm[0].fAmp=pTmt_GradientParas->m_uiVOL[1][i].Harm[0].fAmp;
			pTmt_GradientParas->m_uiVOL[2][i].Harm[1].fAmp=pTmt_GradientParas->m_uiVOL[1][i].Harm[1].fAmp;
			pTmt_GradientParas->m_uiVOL[2][i].Harm[1].fFreq=pTmt_GradientParas->m_uiVOL[1][i].Harm[1].fFreq;
			pTmt_GradientParas->m_uiVOL[2][i].Harm[1].fAngle=pTmt_GradientParas->m_uiVOL[1][i].Harm[1].fAngle;
		}
		else
		{
			pTmt_GradientParas->m_uiVOL[2][i].Harm[0].fAmp=0;
			pTmt_GradientParas->m_uiVOL[2][i].Harm[1].fAmp=0;
		}
	}

	for(int i=0;i<GRADIENT_CHAN_COUNT;i++)
	{
		if(i<nCurrentChCount)
		{
			pTmt_GradientParas->m_uiCUR[2][i].Harm[0].fAmp=pTmt_GradientParas->m_uiCUR[1][i].Harm[0].fAmp;
			pTmt_GradientParas->m_uiCUR[2][i].Harm[1].fAmp=pTmt_GradientParas->m_uiCUR[1][i].Harm[1].fAmp;
			pTmt_GradientParas->m_uiCUR[2][i].Harm[1].fFreq=pTmt_GradientParas->m_uiCUR[1][i].Harm[1].fFreq;
			pTmt_GradientParas->m_uiCUR[2][i].Harm[1].fAngle=pTmt_GradientParas->m_uiCUR[1][i].Harm[1].fAngle;
		}
		else
		{
			pTmt_GradientParas->m_uiCUR[2][i].Harm[0].fAmp=0;
			pTmt_GradientParas->m_uiCUR[2][i].Harm[1].fAmp=0;
		}
	}
}

void CSttTestBase::CalStepValue_Gradient(tmt_GradientParas *pTmt_GradientParas,int nHarmIndex,long nGradientChCount)
{
#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
    tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;
    float fStart=pTmt_GradientParas->m_fStart;
    float fEnd=pTmt_GradientParas->m_fStop;
    float fStep=pTmt_GradientParas->m_fStep;

    tmt_channel *uData=&(pTmt_GradientParas->m_uiVOL[2][0]);
    tmt_channel *iData=&(pTmt_GradientParas->m_uiCUR[2][0]);

	pTmtGradientProcess->m_nStepCount = (int)ceil(fabs((fEnd-fStart)/fStep));//初值不计算在步长内 20240117 zhoulei
    float fCurValue;
	int nStepCount = pTmtGradientProcess->m_nStepCount + 1;//20240117 zhoulei

    if(nStepCount > GRADIENT_MAX_COUNT)
    {
        //qDebug()<<"递变步数（%d）比测试仪支持的最大步数（%d）多，可能导致无法得到正确的测试结果！"<<nStepCount<<GRADIENT_MAX_COUNT;
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("递变步数（%d）比测试仪支持的最大步数（%d）多，可能导致无法得到正确的测试结果！")
                                   , nStepCount, GRADIENT_MAX_COUNT);
    }

    float fSign = 1.0f;

    if(fEnd<fStart)
    {
        fSign=-1.0;
    }

    tmt_StepUI * pUIStepData=&pTmtGradientProcess->m_uiStepData[0];
    // 角度递变时，当总点数多于最大点数且为动作边界测试时，必须将有效点数分布在两条边界附近	Modified by ZM 180608
    if (nStepCount>GRADIENT_MAX_COUNT)
    {
        int nEnd,nGap,nIndex;
        nEnd = GRADIENT_MAX_COUNT/2;
        nGap = nStepCount-GRADIENT_MAX_COUNT;

        for(int i=0;i<=GRADIENT_MAX_COUNT;i++)
        {
            if (i>nEnd)
                nIndex = i+nGap;
            else
                nIndex = i;

            fCurValue = fStart + fStep*fSign*nIndex;
            CalStepValue(pTmt_GradientParas,fCurValue,nHarmIndex);
            SetUIParaToStepUI(uData, iData, pUIStepData, nHarmIndex);
            pUIStepData++;
        }
    }
    else
    {
        for(int i=0;i<nStepCount;i++)
        {
            fCurValue = fStart + fStep*fSign*i;
            if((fCurValue>fEnd&&fSign>0.0)||(fCurValue<fEnd&&fSign<0.0))
            {
                fCurValue = fEnd;
            }
            CalStepValue(pTmt_GradientParas,fCurValue,nHarmIndex);
            SetUIParaToStepUI(uData, iData, pUIStepData, nHarmIndex);
            pUIStepData++;
        }
    }
#endif
#endif
}

void CSttTestBase::CalStepValue(tmt_GradientParas *pTmt_GradientParas,float fCurValue,int nHarmIndex)
{
#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
    for(int i=0;i<CSttDeviceBase::g_pSttDeviceBase->ChannelVolts.size();i++)
    {
        int chan=CSttDeviceBase::g_pSttDeviceBase->ChannelVolts.at(i);
        switch(pTmt_GradientParas->m_nType)
        {
        case GRADIENT_AMP:
            pTmt_GradientParas->m_uiVOL[2][chan].Harm[nHarmIndex].fAmp = fCurValue;
            break;
        case GRADIENT_ANG:
            pTmt_GradientParas->m_uiVOL[2][chan].Harm[nHarmIndex].fAngle = fCurValue;
            break;
        case GRADIENT_FRE:
            pTmt_GradientParas->m_uiVOL[2][chan].Harm[nHarmIndex].fFreq = fCurValue;
            break;
        }
    }

    for(int i=0;i<CSttDeviceBase::g_pSttDeviceBase->ChannelCurrs.size();i++)
    {
        int chan=CSttDeviceBase::g_pSttDeviceBase->ChannelCurrs.at(i);
        switch(pTmt_GradientParas->m_nType)
        {
        case GRADIENT_AMP:
            pTmt_GradientParas->m_uiCUR[2][chan].Harm[nHarmIndex].fAmp = fCurValue;
            break;
        case GRADIENT_ANG:
            pTmt_GradientParas->m_uiCUR[2][chan].Harm[nHarmIndex].fAngle = fCurValue;
            break;
        case GRADIENT_FRE:
            pTmt_GradientParas->m_uiCUR[2][chan].Harm[nHarmIndex].fFreq = fCurValue;
            break;
        }
    }
#endif
#endif
}

void CSttTestBase::SetUIParaToStepUI(tmt_channel *uData, tmt_channel *iData, tmt_StepUI *pUIStepData, int nHarmIndex)
{
    for (int i=0;i<GRADIENT_CHAN_COUNT;i++)
    {
        pUIStepData->fU[i][0] = uData[i].Harm[nHarmIndex].fAmp;
        pUIStepData->fU[i][1] = uData[i].Harm[nHarmIndex].fAngle;
        pUIStepData->fU[i][2] = uData[i].Harm[nHarmIndex].fFreq;
    }

    for (int i=0;i<GRADIENT_CHAN_COUNT;i++)
    {
        pUIStepData->fI[i][0] = iData[i].Harm[nHarmIndex].fAmp;
        pUIStepData->fI[i][1] = iData[i].Harm[nHarmIndex].fAngle;
        pUIStepData->fI[i][2] = iData[i].Harm[nHarmIndex].fFreq;
    }
}

float CSttTestBase::GetMaxValue(float fValue1,float fValue2)
{
    if (fValue1<fValue2)
    {
        return fValue2;
    }
    else
    {
        return fValue1;
    }
}

void CSttTestBase::GradientAllChAndAllType(int nChNum)
{
#ifdef _PSX_QT_LINUX_
#ifndef _STT_NOT_IN_TEST_SERVER_
	tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;

	for (int nChIndex = 0;nChIndex<3;nChIndex++)
	{
		for (int nTypeIndex = 0;nTypeIndex<3;nTypeIndex++)
		{
			pTmtGradientProcess->m_bUChange[nChIndex][nTypeIndex] = 1;
			pTmtGradientProcess->m_bIChange[nChIndex][nTypeIndex] = 1;
		}
	}
#endif
#endif
}

void CSttTestBase::ProGradientRtDatasEvent(STT_RTDATA_EVENT &oRtdata,int nStep,int nType)
{
#ifndef _STT_NOT_IN_TEST_SERVER_
    int nRtIndex;
    float fVal,fValBase;
#ifdef _PSX_QT_LINUX_
    tmt_GradientParas &oGradientParas=CSttDeviceBase::g_pSttDeviceBase->m_oGradientParas;

    for(int nIndex=0;nIndex<g_nRtDataVoltCnt;nIndex++)
    {
        nRtIndex=oRtdata.m_nVolChCount;
        oRtdata.m_oVolCh[nRtIndex].m_nIndex=nIndex;

        if(nType == 2)
        {
            if(oGradientParas.m_uiVOL[2][nIndex].Ramp[0].nIndex==0)
            {
                if(oGradientParas.m_nType==GRADIENT_AMP)
                {
                    //直流递变幅值
                    fVal = oGradientParas.m_uiVOL[2][nIndex].Harm[0].fAmp;
                    fVal += oGradientParas.m_nStepDirection*oGradientParas.m_fStep*nStep;

                    if(oGradientParas.m_fStart > oGradientParas.m_fStop)
                    {
                        if(fVal < oGradientParas.m_fStop)
                            fVal = oGradientParas.m_fStop;
                    }
                    else
                    {
                        if(fVal > oGradientParas.m_fStop)
                            fVal = oGradientParas.m_fStop;
                    }
					oRtdata.m_oVolCh[nRtIndex].m_fMag=fVal;
					oRtdata.m_oVolCh[nRtIndex].m_fAng=0;
					oRtdata.m_oVolCh[nRtIndex].m_fFreq=0;
                    oRtdata.m_nVolChCount++;
                }
            }
            else if(oGradientParas.m_uiVOL[2][nIndex].Ramp[0].nIndex>0
                    ||oGradientParas.m_uiVOL[2][nIndex].Ramp[1].nIndex==1
                    ||oGradientParas.m_uiVOL[2][nIndex].Ramp[2].nIndex==1)
            {
                switch(oGradientParas.m_nType)
                {
                case GRADIENT_AMP:
                {
                    fValBase=fabs(oGradientParas.m_uiVOL[2][nIndex].Harm[1].fAmp);
                    if(oGradientParas.m_nStepHarm==1)
                    {
                        fValBase+=oGradientParas.m_nStepDirection*oGradientParas.m_fStep*nStep;
                        if(oGradientParas.m_fStart > oGradientParas.m_fStop)
                        {
                            if(fValBase < oGradientParas.m_fStop)
                                fValBase = oGradientParas.m_fStop;
                        }
                        else
                        {
                            if(fValBase > oGradientParas.m_fStop)
                                fValBase = oGradientParas.m_fStop;
                        }
                    }
                    float fTotal=fValBase*fValBase;

                    for(int i=2;i<MAX_HARM_COUNT;i++)
                    {
                        if(oGradientParas.m_nStepHarm==i)
                        {
                            fVal=oGradientParas.m_uiVOL[2][nIndex].Harm[oGradientParas.m_nStepHarm].fAmp;
                            fVal+=oGradientParas.m_nStepDirection*oGradientParas.m_fStep*nStep;
                            if(oGradientParas.m_fStart > oGradientParas.m_fStop)
                            {
                                if(fVal < oGradientParas.m_fStop)
                                    fVal = oGradientParas.m_fStop;
                            }
                            else
                            {
                                if(fVal > oGradientParas.m_fStop)
                                    fVal = oGradientParas.m_fStop;
                            }
                            fTotal+=fVal*fVal;
                            break;
                        }
                    }

                    fTotal=sqrt(fTotal);

                    if(!g_theSystemConfig->m_nHasDigital)
                        fTotal+=oGradientParas.m_uiVOL[2][nIndex].Harm[0].fAmp;


					oRtdata.m_oVolCh[nRtIndex].m_fMag=fTotal;
					oRtdata.m_oVolCh[nRtIndex].m_fAng=
							oGradientParas.m_uiVOL[2][nIndex].Harm[1].fAngle;
					oRtdata.m_oVolCh[nRtIndex].m_fFreq=
							oGradientParas.m_uiVOL[2][nIndex].Harm[1].fFreq;
                }
                    break;
                case GRADIENT_ANG:
                {
                    fVal=oGradientParas.m_uiVOL[2][nIndex].Harm[1].fAngle;
                    fVal+=oGradientParas.m_nStepDirection*oGradientParas.m_fStep*nStep;
                    if(oGradientParas.m_fStart > oGradientParas.m_fStop)
                    {
                        if(fVal < oGradientParas.m_fStop)
                            fVal = oGradientParas.m_fStop;
                    }
                    else
                    {
                        if(fVal > oGradientParas.m_fStop)
                            fVal = oGradientParas.m_fStop;
                    }
					oRtdata.m_oVolCh[nRtIndex].m_fMag=
							oGradientParas.m_uiVOL[2][nIndex].Harm[1].fAmp;
					oRtdata.m_oVolCh[nRtIndex].m_fAng=fVal;
					oRtdata.m_oVolCh[nRtIndex].m_fFreq=
							oGradientParas.m_uiVOL[2][nIndex].Harm[1].fFreq;
                }
                    break;
                case GRADIENT_FRE:
                {
                    fVal=oGradientParas.m_uiVOL[2][nIndex].Harm[1].fFreq;
                    fVal+=oGradientParas.m_nStepDirection*oGradientParas.m_fStep*nStep;
                    if(oGradientParas.m_fStart > oGradientParas.m_fStop)
                    {
                        if(fVal < oGradientParas.m_fStop)
                            fVal = oGradientParas.m_fStop;
                    }
                    else
                    {
                        if(fVal > oGradientParas.m_fStop)
                            fVal = oGradientParas.m_fStop;
                    }
					oRtdata.m_oVolCh[nRtIndex].m_fMag=
							oGradientParas.m_uiVOL[2][nIndex].Harm[1].fAmp;
					oRtdata.m_oVolCh[nRtIndex].m_fAng=
							oGradientParas.m_uiVOL[2][nIndex].Harm[1].fAngle;
					oRtdata.m_oVolCh[nRtIndex].m_fFreq=fVal;
                }
                    break;
                }
                oRtdata.m_nVolChCount++;
            }
            else
            {
                //无递变时需输出故障态
				oRtdata.m_oVolCh[nRtIndex].m_fMag=
						oGradientParas.m_uiVOL[2][nIndex].Harm[1].fAmp;
				oRtdata.m_oVolCh[nRtIndex].m_fAng=
						oGradientParas.m_uiVOL[2][nIndex].Harm[1].fAngle;
				oRtdata.m_oVolCh[nRtIndex].m_fFreq=
						oGradientParas.m_uiVOL[2][nIndex].Harm[1].fFreq;
                oRtdata.m_nVolChCount++;
            }
        }
        else if(nType == 1)
        {
            //故障前
            fVal=oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAmp;
			oRtdata.m_oVolCh[nRtIndex].m_fMag=fVal;
			oRtdata.m_oVolCh[nRtIndex].m_fAng=
					oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAngle;
			oRtdata.m_oVolCh[nRtIndex].m_fFreq=
					oGradientParas.m_uiVOL[1][nIndex].Harm[1].fFreq;
            oRtdata.m_nVolChCount++;
        }
        else
        {
            //实验开始
            if(oGradientParas.m_fPrepareTime > 0.0001)
            {
                //变化前
                fVal=oGradientParas.m_uiVOL[0][nIndex].Harm[1].fAmp;
				oRtdata.m_oVolCh[nRtIndex].m_fMag=fVal;
				oRtdata.m_oVolCh[nRtIndex].m_fAng=
						oGradientParas.m_uiVOL[0][nIndex].Harm[1].fAngle;
				oRtdata.m_oVolCh[nRtIndex].m_fFreq=
						oGradientParas.m_uiVOL[0][nIndex].Harm[1].fFreq;
            }
            else if(oGradientParas.m_fPreFaultTime > 0.0001)
            {
                //故障前
                fVal=oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAmp;
				oRtdata.m_oVolCh[nRtIndex].m_fMag=fVal;
				oRtdata.m_oVolCh[nRtIndex].m_fAng=
						oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAngle;
				oRtdata.m_oVolCh[nRtIndex].m_fFreq=
						oGradientParas.m_uiVOL[1][nIndex].Harm[1].fFreq;
            }
            else
            {
                //递变始值
                fVal=oGradientParas.m_fStart;
                if(oGradientParas.m_uiVOL[2][nIndex].Ramp[0].nIndex >= 0)
                {
					oRtdata.m_oVolCh[nRtIndex].m_fMag=fVal;
					oRtdata.m_oVolCh[nRtIndex].m_fAng=
							oGradientParas.m_uiVOL[2][nIndex].Harm[1].fAngle;
					oRtdata.m_oVolCh[nRtIndex].m_fFreq=
							oGradientParas.m_uiVOL[2][nIndex].Harm[1].fFreq;
                }
                else if(oGradientParas.m_uiVOL[2][nIndex].Ramp[1].nIndex==1)
                {
					oRtdata.m_oVolCh[nRtIndex].m_fMag=
							oGradientParas.m_uiVOL[2][nIndex].Harm[1].fAmp;
					oRtdata.m_oVolCh[nRtIndex].m_fAng=fVal;
					oRtdata.m_oVolCh[nRtIndex].m_fFreq=
							oGradientParas.m_uiVOL[2][nIndex].Harm[1].fFreq;
                }
                else if(oGradientParas.m_uiVOL[2][nIndex].Ramp[2].nIndex==1)
                {
					oRtdata.m_oVolCh[nRtIndex].m_fMag=
							oGradientParas.m_uiVOL[2][nIndex].Harm[1].fAmp;
					oRtdata.m_oVolCh[nRtIndex].m_fAng=
							oGradientParas.m_uiVOL[2][nIndex].Harm[1].fAngle;
					oRtdata.m_oVolCh[nRtIndex].m_fFreq=fVal;
                }
                else
                {
					oRtdata.m_oVolCh[nRtIndex].m_fMag=
							oGradientParas.m_uiVOL[2][nIndex].Harm[1].fAmp;
					oRtdata.m_oVolCh[nRtIndex].m_fAng=
							oGradientParas.m_uiVOL[2][nIndex].Harm[1].fAngle;
					oRtdata.m_oVolCh[nRtIndex].m_fFreq=
							oGradientParas.m_uiVOL[2][nIndex].Harm[1].fFreq;
                }
            }

            oRtdata.m_nVolChCount++;
        }
    }

    for(int nIndex=0;nIndex<g_nRtDataCurrCnt;nIndex++)
    {
        nRtIndex=oRtdata.m_nCurChCount;
        oRtdata.m_oCurCh[nRtIndex].m_nIndex=nIndex;

        if(nType == 2)
        {
            if(oGradientParas.m_uiCUR[2][nIndex].Ramp[0].nIndex==0)
            {
                if(oGradientParas.m_nType==GRADIENT_AMP)
                {
                    //直流递变幅值
                    fVal=oGradientParas.m_uiCUR[2][nIndex].Harm[0].fAmp;
                    fVal+=oGradientParas.m_nStepDirection*oGradientParas.m_fStep*nStep;
                    if(oGradientParas.m_fStart > oGradientParas.m_fStop)
                    {
                        if(fVal < oGradientParas.m_fStop)
                            fVal = oGradientParas.m_fStop;
                    }
                    else
                    {
                        if(fVal > oGradientParas.m_fStop)
                            fVal = oGradientParas.m_fStop;
                    }
					oRtdata.m_oCurCh[nRtIndex].m_fMag=fVal;
					oRtdata.m_oCurCh[nRtIndex].m_fAng=0;
					oRtdata.m_oCurCh[nRtIndex].m_fFreq=0;
                    oRtdata.m_nCurChCount++;
                }

            }
            else if(oGradientParas.m_uiCUR[2][nIndex].Ramp[0].nIndex>0
                    ||oGradientParas.m_uiCUR[2][nIndex].Ramp[1].nIndex==1
                    ||oGradientParas.m_uiCUR[2][nIndex].Ramp[2].nIndex==1)
            {
				oRtdata.m_oCurCh[nRtIndex].m_fMag = 0;

                switch(oGradientParas.m_nType)
                {
                case GRADIENT_AMP:
                {
                    fValBase=fabs(oGradientParas.m_uiCUR[2][nIndex].Harm[1].fAmp);
                    if(oGradientParas.m_nStepHarm==1)
                    {
                        fValBase+=oGradientParas.m_nStepDirection*oGradientParas.m_fStep*nStep;
                        if(oGradientParas.m_fStart > oGradientParas.m_fStop)
                        {
                            if(fValBase < oGradientParas.m_fStop)
                                fValBase = oGradientParas.m_fStop;
                        }
                        else
                        {
                            if(fValBase > oGradientParas.m_fStop)
                                fValBase = oGradientParas.m_fStop;
                        }
                    }
                    float fTotal=fValBase*fValBase;

                    for(int i=2;i<MAX_HARM_COUNT;i++)
                    {
                        if(oGradientParas.m_nStepHarm==i)
                        {
                            fVal=oGradientParas.m_uiCUR[2][nIndex].Harm[oGradientParas.m_nStepHarm].fAmp;
                            fVal+=oGradientParas.m_nStepDirection*oGradientParas.m_fStep*nStep;
                            if(oGradientParas.m_fStart > oGradientParas.m_fStop)
                            {
                                if(fVal < oGradientParas.m_fStop)
                                    fVal = oGradientParas.m_fStop;
                            }
                            else
                            {
                                if(fVal > oGradientParas.m_fStop)
                                    fVal = oGradientParas.m_fStop;
                            }
                            fTotal+=fVal*fVal;
                            break;
                        }
                    }

                    fTotal=sqrt(fTotal);

                    if(!g_theSystemConfig->m_nHasDigital)
                        fTotal+=oGradientParas.m_uiCUR[2][nIndex].Harm[0].fAmp;

					oRtdata.m_oCurCh[nRtIndex].m_fMag=fTotal;
					oRtdata.m_oCurCh[nRtIndex].m_fAng=
							oGradientParas.m_uiCUR[2][nIndex].Harm[1].fAngle;
					oRtdata.m_oCurCh[nRtIndex].m_fFreq=
							oGradientParas.m_uiCUR[2][nIndex].Harm[1].fFreq;
                }
                    break;
                case GRADIENT_ANG:
                {
                    fVal=oGradientParas.m_uiCUR[2][nIndex].Harm[1].fAngle;
                    fVal+=oGradientParas.m_nStepDirection*oGradientParas.m_fStep*nStep;
                    if(oGradientParas.m_fStart > oGradientParas.m_fStop)
                    {
                        if(fVal < oGradientParas.m_fStop)
                            fVal = oGradientParas.m_fStop;
                    }
                    else
                    {
                        if(fVal > oGradientParas.m_fStop)
                            fVal = oGradientParas.m_fStop;
                    }
					oRtdata.m_oCurCh[nRtIndex].m_fMag=
							oGradientParas.m_uiCUR[2][nIndex].Harm[1].fAmp;
					oRtdata.m_oCurCh[nRtIndex].m_fAng=fVal;
					oRtdata.m_oCurCh[nRtIndex].m_fFreq=
							oGradientParas.m_uiCUR[2][nIndex].Harm[1].fFreq;
                }
                    break;
                case GRADIENT_FRE:
                {
                    fVal=oGradientParas.m_uiCUR[2][nIndex].Harm[1].fFreq;
                    fVal+=oGradientParas.m_nStepDirection*oGradientParas.m_fStep*nStep;
                    if(oGradientParas.m_fStart > oGradientParas.m_fStop)
                    {
                        if(fVal < oGradientParas.m_fStop)
                            fVal = oGradientParas.m_fStop;
                    }
                    else
                    {
                        if(fVal > oGradientParas.m_fStop)
                            fVal = oGradientParas.m_fStop;
                    }
					oRtdata.m_oCurCh[nRtIndex].m_fMag=
							oGradientParas.m_uiCUR[2][nIndex].Harm[1].fAmp;
					oRtdata.m_oCurCh[nRtIndex].m_fAng=
							oGradientParas.m_uiCUR[2][nIndex].Harm[1].fAngle;
					oRtdata.m_oCurCh[nRtIndex].m_fFreq=fVal;
                }
                    break;
                }
                oRtdata.m_nCurChCount++;

            }
            else
            {
                //无递变时需输出故障态
				oRtdata.m_oCurCh[nRtIndex].m_fMag=
						oGradientParas.m_uiCUR[2][nIndex].Harm[1].fAmp;
				oRtdata.m_oCurCh[nRtIndex].m_fAng=
						oGradientParas.m_uiCUR[2][nIndex].Harm[1].fAngle;
				oRtdata.m_oCurCh[nRtIndex].m_fFreq=
						oGradientParas.m_uiCUR[2][nIndex].Harm[1].fFreq;
                oRtdata.m_nCurChCount++;
            }
        }
        else if(nType == 1)
        {
            //故障前
            fVal=oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAmp;
			oRtdata.m_oCurCh[nRtIndex].m_fMag=fVal;
			oRtdata.m_oCurCh[nRtIndex].m_fAng=
					oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAngle;
			oRtdata.m_oCurCh[nRtIndex].m_fFreq=
					oGradientParas.m_uiCUR[1][nIndex].Harm[1].fFreq;
            oRtdata.m_nCurChCount++;

        }
        else
        {
            //实验开始
            if(oGradientParas.m_fPrepareTime > 0.0001)
            {
                //变化前
                fVal=oGradientParas.m_uiCUR[0][nIndex].Harm[1].fAmp;
				oRtdata.m_oCurCh[nRtIndex].m_fMag=fVal;
				oRtdata.m_oCurCh[nRtIndex].m_fAng=
						oGradientParas.m_uiCUR[0][nIndex].Harm[1].fAngle;
				oRtdata.m_oCurCh[nRtIndex].m_fFreq=
						oGradientParas.m_uiCUR[0][nIndex].Harm[1].fFreq;
            }
            else if(oGradientParas.m_fPreFaultTime > 0.0001)
            {
                //故障前
                fVal=oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAmp;
				oRtdata.m_oCurCh[nRtIndex].m_fMag=fVal;
				oRtdata.m_oCurCh[nRtIndex].m_fAng=
						oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAngle;
				oRtdata.m_oCurCh[nRtIndex].m_fFreq=
						oGradientParas.m_uiCUR[1][nIndex].Harm[1].fFreq;
            }
            else
            {
                //递变始值
                fVal=oGradientParas.m_fStart;
                if(oGradientParas.m_uiCUR[2][nIndex].Ramp[0].nIndex >= 0)
                {
					oRtdata.m_oCurCh[nRtIndex].m_fMag=fVal;
					oRtdata.m_oCurCh[nRtIndex].m_fAng=
							oGradientParas.m_uiCUR[2][nIndex].Harm[1].fAngle;
					oRtdata.m_oCurCh[nRtIndex].m_fFreq=
							oGradientParas.m_uiCUR[2][nIndex].Harm[1].fFreq;
                }
                else if(oGradientParas.m_uiCUR[2][nIndex].Ramp[1].nIndex==1)
                {
					oRtdata.m_oCurCh[nRtIndex].m_fMag=
							oGradientParas.m_uiCUR[2][nIndex].Harm[1].fAmp;
					oRtdata.m_oCurCh[nRtIndex].m_fAng=fVal;
					oRtdata.m_oCurCh[nRtIndex].m_fFreq=
							oGradientParas.m_uiCUR[2][nIndex].Harm[1].fFreq;
                }
                else if(oGradientParas.m_uiCUR[2][nIndex].Ramp[2].nIndex==1)
                {
					oRtdata.m_oCurCh[nRtIndex].m_fMag=
							oGradientParas.m_uiCUR[2][nIndex].Harm[1].fAmp;
					oRtdata.m_oCurCh[nRtIndex].m_fAng=
							oGradientParas.m_uiCUR[2][nIndex].Harm[1].fAngle;
					oRtdata.m_oCurCh[nRtIndex].m_fFreq=fVal;
                }
                else
                {
					oRtdata.m_oCurCh[nRtIndex].m_fMag=
							oGradientParas.m_uiCUR[2][nIndex].Harm[1].fAmp;
					oRtdata.m_oCurCh[nRtIndex].m_fAng=
							oGradientParas.m_uiCUR[2][nIndex].Harm[1].fAngle;
					oRtdata.m_oCurCh[nRtIndex].m_fFreq=
							oGradientParas.m_uiCUR[2][nIndex].Harm[1].fFreq;
                }
            }

            oRtdata.m_nCurChCount++;
        }
    }
#endif
#endif
}

//////////////////////////////////////////////////////////////////////////
//

BOOL g_bLogTestParaAndReport = FALSE;
BOOL g_bLogTestStateMsg = FALSE;
/////////////////////////////////////////////////////////
char *g_pszSttTestDrvParasBuff = NULL;

char* stt_test_new_drvparas_buff()
{
    if (g_pszSttTestDrvParasBuff != NULL)
    {
        return g_pszSttTestDrvParasBuff;
    }

	g_pszSttTestDrvParasBuff = (char*)malloc(88000000);

    return g_pszSttTestDrvParasBuff;
}

void stt_test_free_drvparas_buff()
{
    if(g_pszSttTestDrvParasBuff != NULL)
    {
        free(g_pszSttTestDrvParasBuff);
        g_pszSttTestDrvParasBuff = NULL;
    }
}

char* stt_test_get_drvparas_buff()
{
    return g_pszSttTestDrvParasBuff;
}

char *g_pszSttTestDrvResultBuff = NULL;

char* stt_test_new_drvresult_buff()
{
    if (g_pszSttTestDrvResultBuff != NULL)
    {
        return g_pszSttTestDrvResultBuff;
    }

    g_pszSttTestDrvResultBuff = (char*)malloc(8*1024*1024);//AT02D每秒采集按1个控制块1MB估算

    return g_pszSttTestDrvResultBuff;
}

void stt_test_free_drvresult_buff()
{
    if(g_pszSttTestDrvResultBuff != NULL)
    {
        free(g_pszSttTestDrvResultBuff);
        g_pszSttTestDrvResultBuff = NULL;
    }
}

char* stt_test_get_drvresult_buff()
{
    return g_pszSttTestDrvResultBuff;
}


//统一申请实验结构体空间
tmt_StateTest* g_pszSttTestTmtStateBuff = NULL;
tmt_StateTest* stt_test_new_base_statetest_buff()
{
    if (g_pszSttTestTmtStateBuff != NULL)
    {
        return g_pszSttTestTmtStateBuff;
    }

    g_pszSttTestTmtStateBuff = new tmt_StateTest;

    return g_pszSttTestTmtStateBuff;
}
tmt_StateTest* stt_test_get_base_statetest_buff()
{
    return g_pszSttTestTmtStateBuff;
}
void stt_test_free_base_statetest_buff()
{
    if(g_pszSttTestTmtStateBuff != NULL)
    {
        delete g_pszSttTestTmtStateBuff;
        g_pszSttTestTmtStateBuff=NULL;
    }
}

tmt_ManualTest* g_pszSttTestTmtManualBuff = NULL;
tmt_ManualTest* stt_test_new_base_manualtest_buff()
{
    if (g_pszSttTestTmtManualBuff != NULL)
    {
        return g_pszSttTestTmtManualBuff;
    }

    g_pszSttTestTmtManualBuff = new tmt_ManualTest;

    return g_pszSttTestTmtManualBuff;
}
tmt_ManualTest* stt_test_get_base_manualtest_buff()
{
    return g_pszSttTestTmtManualBuff;
}
void stt_test_free_base_manualtest_buff()
{
    if(g_pszSttTestTmtManualBuff != NULL)
    {
        delete g_pszSttTestTmtManualBuff;
        g_pszSttTestTmtManualBuff=NULL;
    }
}

tmt_ImpBaseParas* g_pszSttTestTmtImpBaseBuff = NULL;
tmt_ImpBaseParas *stt_test_new_ex_ImpBase_buff()
{
    if (g_pszSttTestTmtImpBaseBuff != NULL)
    {
        return g_pszSttTestTmtImpBaseBuff;
    }

    g_pszSttTestTmtImpBaseBuff = new tmt_ImpBaseParas;

    return g_pszSttTestTmtImpBaseBuff;
}
tmt_ImpBaseParas* stt_test_get_ex_ImpBase_buff()
{
    return g_pszSttTestTmtImpBaseBuff;
}
void stt_test_free_ex_ImpBase_buff()
{
    if(g_pszSttTestTmtImpBaseBuff != NULL)
    {
        delete g_pszSttTestTmtImpBaseBuff;
        g_pszSttTestTmtImpBaseBuff=NULL;
    }
}

tmt_HarmTest* g_pszSttTestTmtHarmBuff = NULL;
tmt_HarmTest *stt_test_new_base_harmtest_buff()
{
    if (g_pszSttTestTmtHarmBuff != NULL)
    {
        return g_pszSttTestTmtHarmBuff;
    }

    g_pszSttTestTmtHarmBuff = new tmt_HarmTest;

    return g_pszSttTestTmtHarmBuff;
}
tmt_HarmTest* stt_test_get_base_harmtest_buff()
{
    return g_pszSttTestTmtHarmBuff;
}
void stt_test_free_base_harmtest_buff()
{
    if(g_pszSttTestTmtHarmBuff != NULL)
    {
        delete g_pszSttTestTmtHarmBuff;
        g_pszSttTestTmtHarmBuff=NULL;
    }
}

tmt_SynParas* g_pszSttTestTmtSynParasBuff = NULL;
tmt_SynParas *stt_test_new_synparas_buff()
{
    if (g_pszSttTestTmtSynParasBuff != NULL)
    {
        return g_pszSttTestTmtSynParasBuff;
    }

    g_pszSttTestTmtSynParasBuff = new tmt_SynParas;

    return g_pszSttTestTmtSynParasBuff;
}

tmt_SynParas* stt_test_get_synparas_buff()
{
    return g_pszSttTestTmtSynParasBuff;
}

void stt_test_free_synparas_buff()
{
    if(g_pszSttTestTmtSynParasBuff != NULL)
    {
        delete g_pszSttTestTmtSynParasBuff;
        g_pszSttTestTmtSynParasBuff=NULL;
    }
}
