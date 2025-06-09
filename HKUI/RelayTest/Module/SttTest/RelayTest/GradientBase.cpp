#include "stdafx.h"
#include "GradientBase.h"
//#include<QtDebug>

CGradientBase::CGradientBase()
{	
}

CGradientBase::~CGradientBase()
{	
}

void CGradientBase::Stop()
{

}

void CGradientBase::SetChannelSelect(int nRampChannel,int nRampType)
{
#ifdef _PSX_IDE_QT_
	memset(m_oGradientProcess.m_bUChange,0,sizeof(bool)*3*MAX_VOLTAGE_COUNT);
	memset(m_oGradientProcess.m_bIChange,0,sizeof(bool)*3*MAX_CURRENT_COUNT);

	CSttDevice::GetTMTChannels(nRampChannel,ChannelVolts,ChannelCurrs);
	int chan=0;
	for(int i=0;i<ChannelVolts.size();i++)
	{
		chan=ChannelVolts.at(i);
		m_oGradientProcess.m_bUChange[chan][nRampType] = TRUE;
	}
	for(int i=0;i<ChannelCurrs.size();i++)
	{
		chan=ChannelCurrs.at(i);
		m_oGradientProcess.m_bIChange[chan][nRampType] = TRUE;
	}
#endif
}

void CGradientBase::CalStepValue_Gradient(float fStart, float fEnd, float fStep, tmt_channel *uData, tmt_channel *iData, int nHarmIndex)
{
    m_oGradientProcess.m_nStepCount = (int)ceil(fabs((fEnd-fStart)/fStep))+1;	//TEMP 因角度搜索时StepSize可能是负值，故将fabs放到外面
	float fCurValue;
    int nStepCount = m_oGradientProcess.m_nStepCount;
	if(nStepCount > GRADIENT_MAX_COUNT)
    {
		//qDebug()<<"递变步数（%d）比测试仪支持的最大步数（%d）多，可能导致无法得到正确的测试结果！"<<nStepCount<<GRADIENT_MAX_COUNT;
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("递变步数（%d）比测试仪支持的最大步数（%d）多，可能导致无法得到正确的测试结果！")
			, nStepCount, GRADIENT_MAX_COUNT);
    }

    float fSign = 1.0f;
    if(fEnd<fStart)
    {
        fSign=-1.0;
    }

	tmt_StepUI * pUIStepData=&m_oGradientProcess.m_uiStepData[0];
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
            CalStepValue(fCurValue);
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
            CalStepValue(fCurValue);
            SetUIParaToStepUI(uData, iData, pUIStepData, nHarmIndex);
			pUIStepData++;
        }
    }
}

void CGradientBase::SetUIParaToStepUI(tmt_channel *uData, tmt_channel *iData, tmt_StepUI *pUIStepData, int nHarmIndex)
{
    for (int i=0;i<MAX_VOLTAGE_COUNT;i++)
    {
        pUIStepData->fU[i][0] = uData[i].Harm[nHarmIndex].fAmp;
        pUIStepData->fU[i][1] = uData[i].Harm[nHarmIndex].fAngle;
        pUIStepData->fU[i][2] = uData[i].Harm[nHarmIndex].fFreq;
        pUIStepData->fI[i][0] = iData[i].Harm[nHarmIndex].fAmp;
        pUIStepData->fI[i][1] = iData[i].Harm[nHarmIndex].fAngle;
        pUIStepData->fI[i][2] = iData[i].Harm[nHarmIndex].fFreq;
    }
}
