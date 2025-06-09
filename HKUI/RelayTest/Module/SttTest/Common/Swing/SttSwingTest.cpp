#include "stdafx.h"
#include"SttSwingTest.h"
#include "../SttSystemConfig.h"
#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttSwingTest::m_strMacroName = "振荡测试";
CString CSttSwingTest::m_strMacroID = STT_MACRO_ID_PsuSwing;
CString CSttSwingTest::m_strFilePostFix = "pswt";
CString CSttSwingTest::m_strMacroVer ="1.0";

#define SWING_FAULT_TYPE_AN                                                    0
#define SWING_FAULT_TYPE_BN                                                    1
#define SWING_FAULT_TYPE_CN                                                    2
#define SWING_FAULT_TYPE_AB                                                    3
#define SWING_FAULT_TYPE_BC                                                    4
#define SWING_FAULT_TYPE_CA                                                    5
#define SWING_FAULT_TYPE_ABC                                                   9

CSttSwingTest::CSttSwingTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	SetTestStarting(FALSE);
	m_dTestStartTime=0;

	m_pszDrvPara=stt_test_get_drvparas_buff();
}

void CSttSwingTest::Init()
{
	tmt_SwingParas::init();
	CSttTestBase::Init();
	m_oSwingResults.init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
}

float TranAng(float fPh)
{
    while((fPh >= 360)||(fPh < 0))
    {
        if(fPh >= 360)
        {
            fPh -= 360;
        }
        else
        {
            fPh += 360;
        }
    }

    return fPh;
}

void CSttSwingTest::ReCalVoltCurr(STT_RTDATA_EVENT &oRTDATA)
{
#ifdef _PSX_QT_LINUX_
    int nCommfd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	int nSize = 0;
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	nSize = read(nCommfd,(char*)&m_oSwingRst,0x251);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

    if(nSize != sizeof(Drv_SwingRst))
        return;
#endif

    float fAmpI,fPhI,fFreI;
    float fAmpU,fPhU,fFreU;
    unsigned int nStep = m_oSwingRst.nStep;//状态内步数
    unsigned int nType = m_oSwingRst.nType;//实验状态

    if(nStep > 720 || nType > 2)
    {
        return;
    }

    //3U3I
    for(int i = 0;i < 3;i++)
    {
        switch(nType)
        {
        case 0:
            //振荡前
            fAmpU = m_oUI0.fU[i][0];
            fPhU = m_oUI0.fU[i][1];
            fFreU = m_oUI0.fU[i][2];

            fAmpI = m_oUI0.fI[i][0];
            fPhI = m_oUI0.fI[i][1];
            fFreI = m_oUI0.fI[i][2];
            break;
        case 1:
            //每步振荡
            fAmpU = m_oUI1.m_uiStepData[nStep].fU[i][0];
            fPhU = m_oUI1.m_uiStepData[nStep].fU[i][1];
            fFreU = m_oUI1.m_uiStepData[nStep].fU[i][2];

            fAmpI = m_oUI1.m_uiStepData[nStep].fI[i][0];
            fPhI = m_oUI1.m_uiStepData[nStep].fI[i][1];
            fFreI = m_oUI1.m_uiStepData[nStep].fI[i][2];
            break;
        case 2:
            //每步故障
            fAmpU = m_oUI1.m_uiStepData[nStep].fU[i][0];
            fPhU = m_oUI1.m_uiStepData[nStep].fU[i][1];
            fFreU = m_oUI1.m_uiStepData[nStep].fU[i][2];

            fAmpI = m_oUI1.m_uiStepData[nStep].fI[i][0];
            fPhI = m_oUI1.m_uiStepData[nStep].fI[i][1];
            fFreI = m_oUI1.m_uiStepData[nStep].fI[i][2];
            break;
        }

        oRTDATA.m_oVolCh[i].m_nIndex = i;
		oRTDATA.m_oVolCh[i].m_fMag = fAmpU;
		oRTDATA.m_oVolCh[i].m_fAng = fPhU;
		oRTDATA.m_oVolCh[i].m_fFreq = fFreU;

        oRTDATA.m_oCurCh[i].m_nIndex = i;
		oRTDATA.m_oCurCh[i].m_fMag = fAmpI;
		oRTDATA.m_oCurCh[i].m_fAng = fPhI;
		oRTDATA.m_oCurCh[i].m_fFreq = fFreI;
    }

	float fRefAng = oRTDATA.m_oVolCh[0].m_fAng;
    float fRstAng;
    for(int i = 0;i < 3;i++)
    {
		fRstAng = oRTDATA.m_oVolCh[i].m_fAng;
        fRstAng -= fRefAng;
        fRstAng = TranAng(fRstAng);
		oRTDATA.m_oVolCh[i].m_fAng = fRstAng;

		fRstAng = oRTDATA.m_oCurCh[i].m_fAng;
        fRstAng -= fRefAng;
        fRstAng = TranAng(fRstAng);
		oRTDATA.m_oCurCh[i].m_fAng = fRstAng;
    }
}

long CSttSwingTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
    m_dwCurTickCount++;
    if(GetTestStarting())
    {
#ifdef _PSX_QT_LINUX_
        STT_RTDATA_EVENT oRtdata;
        oRtdata.oTime.dTime = m_dTestStartTime + m_dwCurTickCount;
        oRtdata.oTime.dRealTime = m_dwCurTickCount;
        oRtdata.m_nVolChCount = 3;
        oRtdata.m_nCurChCount = 3;
		oRtdata.m_nHasFaultVolCur=0;

        ReCalVoltCurr(oRtdata);
        stt_add_rtdatas(oRtdata);
#endif
    }

    return 0;
}

CSttSwingTest::~CSttSwingTest(void)
{
}

void CSttSwingTest::AfterSetParameter()
{
	while(m_fPowerAngleBegin<0)
	{
		m_fPowerAngleBegin+=360;
	}

	while(m_fPowerAngleBegin>=360.0f)
	{
		m_fPowerAngleBegin-=360.0f;
	}

	while(m_fPowerAngleEnd<0)
	{
		m_fPowerAngleEnd+=360;
	}

	while(m_fPowerAngleEnd>=360.0f)
	{
		m_fPowerAngleEnd-=360.0f;
	}
}

double CSttSwingTest::GetTestTimeLong()
{
	float fTime = 0.0f;

	// 	fTime = m_oHarmParas.m_fOutPutTime;
	// 	fTime += TIME_ONLINE_DELAY;

	return fTime;
}

long CSttSwingTest::CalReport(UINT nState)
{

	return 0;
}


long CSttSwingTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttSwingTest::StartTest()
{
	CSttTestBase::StartTest();

	if(!GetTestStarting())
	{
		TtmToDrv();
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
		SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->SetTestStart(ShakeTest);
#endif
	}

	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttSwingTest::StartTest >>>>>>");
}

void CSttSwingTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(this,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

BOOL CSttSwingTest::EventProcess()
{
	if(!GetTestStarting())
		return FALSE;

	BOOL bTestFinished=FALSE;
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->ProSwingDrvResult(bTestFinished,m_oTestFinishedTime);
#endif
	return bTestFinished;
}

void CSttSwingTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
	GradientResult_Com &oRampRestCom=CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
#endif

	stt_xml_serialize(&m_oSwingResults,  pXmlSerialize);
}

void CSttSwingTest::TtmToDrv()
{
	Complex pITemp[720];
	Complex p1,p2,pt,pK0,pa,pb;
	Complex pVg,pVs,pSWingCurrent[720],pV[720];
	Complex pVaf[720],pVbf[720],pVcf[720],pIaf[720],pIbf[720],pIcf[720];
	Complex fXs,fXt,fXd;
	float fVnom = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V;//额定相电压
	pVs=p1.polar(fVnom,0.0);//额定相电压-矢量值
	fXs = p1.polar(m_fImpSys,m_fImpSysPh);//系统侧阻抗-矢量
	fXt = p1.polar(m_fImpTf,m_fImpTfPh);//变压器侧阻抗-矢量
	fXd = p1.polar(m_fImpTs,90);//暂态电抗值-矢量
	float fIf = m_fSCurrent;//短路电流
	float fZf = m_fImpedance;//短路阻抗值

	float fAngleStart = 0;
	float fAngleStep = 360.0;
	int nStep = 360;

	if(m_bReciprocating)//是往复振荡
	{
		fAngleStart = m_fPowerAngleBegin;//角度变化开始值

		if(m_fPowerAngleEnd-m_fPowerAngleBegin >0)//功角终值大于始值
		{
			fAngleStep = m_fPowerAngleEnd-m_fPowerAngleBegin;//功角终值与始值之间的角差
			nStep = fAngleStep*2;//单个周期内总共变化的角度数
		}
		else
		{
			fAngleStep = m_fPowerAngleBegin-m_fPowerAngleEnd;
			nStep = fAngleStep*2;
			fAngleStep = -fAngleStep;
		}
	}
	else
	{
		fAngleStart=m_fPowerAngleBegin;
		fAngleStep = 360.0;
		nStep = 720;

		if(m_nAccelerate == 0)//减速振荡
		{
			fAngleStep = -360.0;
		}
	}

#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_SwingTestPara(this,nStep,m_pszDrvPara);
#endif

	int nStepCal = nStep-1;

	for(int i=0;i<nStep;i++)//每一步对应一度,对全部递变步数进行计算
	{
		pt=p2.polar(fVnom*m_fRate/*|Em|/|En|*/,fAngleStart+i*fAngleStep/nStepCal);
		pSWingCurrent[i]=(pt-pVs)/(fXs+fXd+fXt);//单相电流矢量值
		pV[i]=pSWingCurrent[i]*(fXs+fXt)+pVs;//单相电压矢量值
	}

	if(m_bTransFault) //振荡中再故障
	{
// 		float fFaultAngleDiff = (m_fFaultTime)/(m_fCycle/nStep);//故障发生时的角度偏差,(时间偏差/(变化1度的时间))
// 
// 		while(fFaultAngleDiff>=360)
// 		{
// 			fFaultAngleDiff -= 360;
// 		}
// 
// 		fAngleStart += fFaultAngleDiff;//zhouhj 20211112 此处增加用于保证故障时的角度与故障发生前连续,算法可能有问题,待确认???????

		int nK0CalMode = m_nK0CalMode;
		float fKr = m_fK0Amp;
		float fKx = m_fK0Angle;
		pa=m_oFaultCalculatTool.GroundFactor(nK0CalMode,fKr,fKx,pb.arg(fXd));//m_fZPhi);
		float fK0l=pb.norm(pa);
		float fK0lPh=pb.arg(pa);
		pK0=pa.polar(fK0l+1.0,fK0lPh);
		float fVs;
		fVs=fIf*(p1.norm(fXd)+fZf);//powertest m_fIf 文件读取，文件确定是5A  m_fZf 1.0

		switch(m_nFaultType)//根据故障类型计算
		{
		case SWING_FAULT_TYPE_AN:
		{
			pVs=p1.polar(fVs,0.0);

			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIaf[i]=pITemp[i]+p1.polar(fIf,-78.0);
				pVaf[i]=pt-fXd*pK0*pIaf[i];
			}

			pVs=p1.polar(fVnom,-120.0);

			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVbf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}

			pVs=p1.polar(fVnom,120.0);

			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVcf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}

			pVs=p1.polar(fVs,0.0);

			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIaf[i]=pITemp[i]+p1.polar(fIf,-78.0);
			}

			pVs=p1.polar(fVnom,-120.0);

			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pIbf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}

			pVs=p1.polar(fVnom,120.0);

			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pIcf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}

			break;
		}
		case SWING_FAULT_TYPE_BN:
		{
			pVs=p1.polar(fVnom,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVaf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}
			pVs=p1.polar(fVs,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIbf[i]=pITemp[i]+p1.polar(fIf,-78.0);//p2.arg(pSWingCurrent[i]));
				pVbf[i]=pt-fXd*pK0*pIbf[i];
			}
			pVs=p1.polar(fVnom,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVcf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}
			pVs=p1.polar(fVnom,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal);
				pIaf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}
			pVs=p1.polar(fVs,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIbf[i]=pITemp[i]+p1.polar(fIf,-78.0);//p2.arg(pSWingCurrent[i]));
			}
			pVs=p1.polar(fVnom,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pIcf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}
			break;
		}
		case SWING_FAULT_TYPE_CN:
		{
			pVs=p1.polar(fVnom,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVaf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}
			pVs=p1.polar(fVnom,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVbf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}
			pVs=p1.polar(fVs,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIcf[i]=pITemp[i]+p1.polar(fIf,-78.0);//p2.arg(pSWingCurrent[i]));
				pVcf[i]=pt-fXd*pK0*pIcf[i];
			}
			pVs=p1.polar(fVnom,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal);
				pIaf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}
			pVs=p1.polar(fVnom,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pIbf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}
			pVs=p1.polar(fVs,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIcf[i]=pITemp[i]+p1.polar(fIf,-78.0);//p2.arg(pSWingCurrent[i]));
			}
			break;
		}
		case SWING_FAULT_TYPE_AB:
		{
			pVs=p1.polar(fVs,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIaf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0+120.0);
				pVaf[i]=pt-fXd*pIaf[i];
			}
			pVs=p1.polar(fVs,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIbf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0-60.0);
				pVbf[i]=pt-fXd*pIbf[i];
			}
			pVs=p1.polar(fVnom,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVcf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}
			pVs=p1.polar(fVs,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIaf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0+120.0);
			}
			pVs=p1.polar(fVs,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIbf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0-60.0);
			}
			pVs=p1.polar(fVnom,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pIcf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}
			break;
		}
		case SWING_FAULT_TYPE_BC:
		{
			pVs=p1.polar(fVnom,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVaf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}
			pVs=p1.polar(fVs,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIbf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0-120.0);
				pVbf[i]=pt-fXd*pIbf[i];
			}
			pVs=p1.polar(fVs,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIcf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0+60.0);
				pVcf[i]=pt-fXd*pIcf[i];
			}
			pVs=p1.polar(fVnom,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal);
				pIaf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}
			pVs=p1.polar(fVs,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIbf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0-120.0);
			}
			pVs=p1.polar(fVs,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIcf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0+60.0);
			}
			break;
		}
		case SWING_FAULT_TYPE_CA:
		{
			pVs=p1.polar(fVs,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIaf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0-120.0+180.0);
				pVaf[i]=pt-fXd*pIaf[i];
			}
			pVs=p1.polar(fVnom,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVbf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}
			pVs=p1.polar(fVs,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIcf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0-120.0);
				pVcf[i]=pt-fXd*pIcf[i];
			}
			pVs=p1.polar(fVs,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIaf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0-120.0+180.0);
			}
			pVs=p1.polar(fVnom,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*m_fRate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pIbf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}
			pVs=p1.polar(fVs,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIcf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0-120.0);
			}
			break;
		}
		case SWING_FAULT_TYPE_ABC:
		{
			pVs=p1.polar(fVs,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIaf[i]=pITemp[i]+p1.polar(fIf,-78.0);
				pVaf[i]=pt-fXd*pIaf[i];
			}
			pVs=p1.polar(fVs,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIbf[i]=pITemp[i]+p1.polar(fIf,-78.0-120.0);
				pVbf[i]=pt-fXd*pIbf[i];
			}
			pVs=p1.polar(fVs,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*m_fRate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIcf[i]=pITemp[i]+p1.polar(fIf,-78.0+120.0);
				pVcf[i]=pt-fXd*pIcf[i];
			}
			break;
		}
		default:
			break;
		}
	}

	tmt_StepUI oStepUI;

	float fPhe[3]= {0,-120,120};

	for(int nChIndex=0;nChIndex<3;nChIndex++)//计算振荡开始前,第一步的系统电压、电流值；作为故障前电压电流值
	{
		oStepUI.fU[nChIndex][0] = pV[0].norm();
		oStepUI.fU[nChIndex][1] = fPhe[nChIndex]+pV[0].arg();
		oStepUI.fU[nChIndex][2] = g_theSystemConfig->m_fFNom;

		oStepUI.fI[nChIndex][0] = pSWingCurrent[0].norm();
		oStepUI.fI[nChIndex][1] = fPhe[nChIndex]+pSWingCurrent[0].arg();
		oStepUI.fI[nChIndex][2] = g_theSystemConfig->m_fFNom;

		if (m_nCTPoint == 0)//如果CT极性指向母线,则反向
		{
			oStepUI.fI[nChIndex][1] += 180;
		}
	}

#ifdef _PSX_QT_LINUX_
    for(int nChIndex=0;nChIndex<3;nChIndex++)
    {
        m_oUI0.fU[nChIndex][0] = oStepUI.fU[nChIndex][0];
        m_oUI0.fU[nChIndex][1] = oStepUI.fU[nChIndex][1];
        m_oUI0.fU[nChIndex][2] = oStepUI.fU[nChIndex][2];

        m_oUI0.fI[nChIndex][0] = oStepUI.fI[nChIndex][0];
        m_oUI0.fI[nChIndex][1] = oStepUI.fI[nChIndex][1];
        m_oUI0.fI[nChIndex][2] = oStepUI.fI[nChIndex][2];
    }
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_SwingAcPara(&oStepUI,m_pszDrvPara,0,0);//振荡前
#endif

	for(int nStepIndex=0;nStepIndex<nStep;nStepIndex++)
	{
		for(int nChIndex=0;nChIndex<3;nChIndex++)
		{
			oStepUI.fU[nChIndex][0] = pV[nStepIndex].norm();
			oStepUI.fU[nChIndex][1] = fPhe[nChIndex]+pV[nStepIndex].arg();
			oStepUI.fU[nChIndex][2] = g_theSystemConfig->m_fFNom;

			oStepUI.fI[nChIndex][0] = pSWingCurrent[nStepIndex].norm();
			oStepUI.fI[nChIndex][1] = fPhe[nChIndex]+pSWingCurrent[nStepIndex].arg();
			oStepUI.fI[nChIndex][2] = g_theSystemConfig->m_fFNom;

			if (m_nCTPoint == 0)//如果CT极性指向母线,则反向
			{
				oStepUI.fI[nChIndex][1] += 180;
			}
		}

#ifdef _PSX_QT_LINUX_
        for(int nChIndex=0;nChIndex<3;nChIndex++)
        {
            m_oUI1.m_uiStepData[nStepIndex].fU[nChIndex][0] = oStepUI.fU[nChIndex][0];
            m_oUI1.m_uiStepData[nStepIndex].fU[nChIndex][1] = oStepUI.fU[nChIndex][1];
            m_oUI1.m_uiStepData[nStepIndex].fU[nChIndex][2] = oStepUI.fU[nChIndex][2];

            m_oUI1.m_uiStepData[nStepIndex].fI[nChIndex][0] = oStepUI.fI[nChIndex][0];
            m_oUI1.m_uiStepData[nStepIndex].fI[nChIndex][1] = oStepUI.fI[nChIndex][1];
            m_oUI1.m_uiStepData[nStepIndex].fI[nChIndex][2] = oStepUI.fI[nChIndex][2];
        }
		CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_SwingAcPara(&oStepUI,m_pszDrvPara,nStepIndex,1);//每步振荡
#endif
	}

	if(m_bTransFault)
	{
		for(int nStepIndex=0;nStepIndex<nStep;nStepIndex++)
		{
			oStepUI.fU[0][0] = pVaf[nStepIndex].norm();
			oStepUI.fU[0][1] = pVaf[nStepIndex].arg();
			oStepUI.fU[0][2] = g_theSystemConfig->m_fFNom;
			oStepUI.fU[1][0] = pVbf[nStepIndex].norm();
			oStepUI.fU[1][1] = pVbf[nStepIndex].arg();
			oStepUI.fU[1][2] = g_theSystemConfig->m_fFNom;
			oStepUI.fU[2][0] = pVcf[nStepIndex].norm();
			oStepUI.fU[2][1] = pVcf[nStepIndex].arg();
			oStepUI.fU[2][2] = g_theSystemConfig->m_fFNom;
			oStepUI.fI[0][0] = pIaf[nStepIndex].norm();
			oStepUI.fI[0][1] = pIaf[nStepIndex].arg();
			oStepUI.fI[0][2] = g_theSystemConfig->m_fFNom;
			oStepUI.fI[1][0] = pIbf[nStepIndex].norm();
			oStepUI.fI[1][1] = pIbf[nStepIndex].arg();
			oStepUI.fI[1][2] = g_theSystemConfig->m_fFNom;
			oStepUI.fI[2][0] = pIcf[nStepIndex].norm();
			oStepUI.fI[2][1] = pIcf[nStepIndex].arg();
			oStepUI.fI[2][2] = g_theSystemConfig->m_fFNom;

			if (m_nCTPoint == 0)//如果CT极性指向母线,则反向
			{
				oStepUI.fI[0][1] += 180;
				oStepUI.fI[1][1] += 180;
				oStepUI.fI[2][1] += 180;
			}

#ifdef _PSX_QT_LINUX_
            for(int nChIndex=0;nChIndex<3;nChIndex++)
            {
                m_oUI2.m_uiStepData[nStepIndex].fU[nChIndex][0] = oStepUI.fU[nChIndex][0];
                m_oUI2.m_uiStepData[nStepIndex].fU[nChIndex][1] = oStepUI.fU[nChIndex][1];
                m_oUI2.m_uiStepData[nStepIndex].fU[nChIndex][2] = oStepUI.fU[nChIndex][2];

                m_oUI2.m_uiStepData[nStepIndex].fI[nChIndex][0] = oStepUI.fI[nChIndex][0];
                m_oUI2.m_uiStepData[nStepIndex].fI[nChIndex][1] = oStepUI.fI[nChIndex][1];
                m_oUI2.m_uiStepData[nStepIndex].fI[nChIndex][2] = oStepUI.fI[nChIndex][2];
            }
			CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_SwingAcPara(&oStepUI,m_pszDrvPara,nStepIndex,2);//每步故障
#endif
		}
	}


#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetSwingPara(m_pszDrvPara);
#endif
}

void CSttSwingTest::SyncSingleStateTmtResult()
{
#ifdef _PSX_QT_LINUX_
	GradientResult_Com &oRampRestCom=CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;

	float fPointTime,fSpeedUpTime,fSpeedDownTime;
	//跳闸接入点
	int nBinSwitchCount=oRampRestCom.m_nrBinSwitchCount[m_nTripPoint];
	if(nBinSwitchCount > 0)
	{
		fPointTime = oRampRestCom.m_frTimeBinAct[m_nTripPoint][0];
	}

	//加速信号接点
	nBinSwitchCount=oRampRestCom.m_nrBinSwitchCount[m_nTripSpeedUp];
	if(nBinSwitchCount > 0)
	{
		fSpeedUpTime = oRampRestCom.m_frTimeBinAct[m_nTripSpeedUp][0];
	}

	//减速信号接点
	nBinSwitchCount=oRampRestCom.m_nrBinSwitchCount[m_nTripSpeedDown];
	if(nBinSwitchCount > 0)
	{
		fSpeedDownTime = oRampRestCom.m_frTimeBinAct[m_nTripSpeedDown][0];
	}

	m_oSwingResults.m_nAct = oRampRestCom.m_nAct;
	m_oSwingResults.m_fTripTime = fPointTime;
	m_oSwingResults.m_fSpeedUp = fSpeedUpTime;
	m_oSwingResults.m_fSpeedDown = fSpeedDownTime;
#endif
}
