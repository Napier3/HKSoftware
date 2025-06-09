#include "StdAfx.h"
#include "RDReadCtrl.h"
#include "RdReadConfig.h"
#include "../../../Module/System/TickCount32.h"
#include "math.h"

BOOL CRDReadCtrl::g_bConnected = FALSE;
BOOL g_bDebugMode = FALSE;

CRDReadCtrl::CRDReadCtrl(void)
{
	m_pCurDataSet = NULL;
	m_hMsgWnd = 0;
	m_nMsg = 0;
	m_hSysMsgWnd = 0;
	m_nSysMsg = 0;
}

CRDReadCtrl::~CRDReadCtrl(void)
{
}

BOOL CRDReadCtrl::ConnectRDDevice()
{
	if (g_bDebugMode)
	{
		g_bConnected = TRUE;
	}
	else
	{
		if (g_bConnected)
		{
			DisConnectRDDevice();
		}

		ERRORCODE error = RadRDAssignDevice(CRdReadConfig::GetSerialPort(),m_oDeviceId);

		if (error==0)
		{
			g_bConnected = TRUE;
		}
	}
	
	if (m_hSysMsgWnd != 0)
	{
		if (g_bConnected)
		{
			mms_PostDeviceSysMessage(this,0,engineConnectDeviceSuccessful);
		} 
		else
		{
			mms_PostDeviceSysMessage(this,0,engineCommError);
		}
	}

	return g_bConnected;
}

BOOL CRDReadCtrl::DisConnectRDDevice()
{

	RadRDClosePort(CRdReadConfig::GetSerialPort());
	g_bConnected = FALSE;
	return TRUE;
}

void CRDReadCtrl::StatusError()
{
	//Get last error and display a message to the user
	char rdmessage [RAD_SIZE_MESSAGE];
	long status = 0;

	//get last error
	RadRDStatus(m_oDeviceId, &status);
	CLogPrint::LogString(XLOGLEVEL_ERROR,_T("StatusError."));

	if (status != 0)
	{
		RadRDMessage(status, rdmessage);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("StatusError(status = %ld;rdmessage = %s)."),status,rdmessage);
	}
}

BOOL CRDReadCtrl::Read_AllChannels()
{
	if (g_bDebugMode)
	{
		m_oRd_Datas.m_fIaAmp[0] = 1;
		m_oRd_Datas.m_fIbAmp[0] = 2;
		m_oRd_Datas.m_fIcAmp[0] = 3;
		m_oRd_Datas.m_fUaAmp[0] = 10;
		m_oRd_Datas.m_fUbAmp[0] = 20;
		m_oRd_Datas.m_fUcAmp[0] = 30;
		Update_DatasetValus();
		return TRUE;
	}

	if (!ReadRD_UA(TRUE))
	{
		return FALSE;
	}

	if (!ReadRD_UB(TRUE))
	{
		return FALSE;
	}

	if (!ReadRD_UC(TRUE))
	{
		return FALSE;
	}

	if (!ReadRD_IA(TRUE))
	{
		return FALSE;
	}

	if (!ReadRD_IB(TRUE))
	{
		return FALSE;
	}

	if (!ReadRD_IC(TRUE))
	{
		return FALSE;
	}

// 	if (!ReadAllPhases(RAD_INST_PHASE))
// 	{
// 		return FALSE;
// 	}
// 
// 	if (!ReadAllPhases(RAD_INST_DPHASE))
// 	{
// 		return FALSE;
// 	}

// 	if (!ReadRD_THD())
// 	{
// 		return FALSE;
// 	}

	Update_DatasetValus();

	return TRUE;
}

void CRDReadCtrl::Update_DatasetValus()
{
	ASSERT(m_pCurDataSet);
	CLogPrint::LogString(XLOGLEVEL_ERROR,_T("开始执行CRDReadCtrl::Update_DatasetValus函数."));

	POS pos_data = m_pCurDataSet->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	CDvmValue *pDvmVaue = NULL;
	float *pfValue = NULL;

	while(pos_data)
	{
		pDvmData = (CDvmData *)m_pCurDataSet->GetNext(pos_data);

		if (pDvmData->m_dwReserved != 0x0FFFFFFF)
		{
			pfValue = (float*)pDvmData->m_dwReserved;
			pDvmData->m_strValue.Format(_T("%f"),*pfValue);
			pDvmVaue = (CDvmValue *)pDvmData->GetHead();
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("更新当前数据值(%s)(%s)(%s),%f,%lf"),pDvmData->m_strID,pDvmData->m_strValue,pDvmVaue->m_strID,*pfValue);

			if (pDvmVaue != NULL)
			{
				pDvmVaue->m_strValue = pDvmData->m_strValue;
			}
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前数据(%s)m_dwReserved == 0x0FFFFFFF."),pDvmData->m_strID);
		}
	}
}

BOOL CRDReadCtrl::ReadRD_UA(BOOL bReadPhase)
{
	if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_A,RAD_INST_V,(m_oRd_Datas.m_fUaAmp))!=0)
	{
		return FALSE;
	}

	if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_A,RAD_INST_DPHASE,(m_oRd_Datas.m_fUaPhase))!=0)
	{
		return FALSE;
	}

	if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_A,RAD_INST_FREQ,(m_oRd_Datas.m_fUaFre))!=0)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRDReadCtrl::ReadRD_UB(BOOL bReadPhase)
{
	if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_B,RAD_INST_V,(m_oRd_Datas.m_fUbAmp))!=0)
	{
		return FALSE;
	}

	if (bReadPhase)
	{
		if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_B,RAD_INST_DPHASE,(m_oRd_Datas.m_fUbPhase))!=0)
		{
			return FALSE;
		}
	}

	if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_B,RAD_INST_FREQ,(m_oRd_Datas.m_fUbFre))!=0)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRDReadCtrl::ReadRD_UC(BOOL bReadPhase)
{
	if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_C,RAD_INST_V,(m_oRd_Datas.m_fUcAmp))!=0)
	{
		return FALSE;
	}

	if (bReadPhase)
	{
		if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_C,RAD_INST_DPHASE,(m_oRd_Datas.m_fUcPhase))!=0)
		{
			return FALSE;
		}	
	}

	if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_C,RAD_INST_FREQ,(m_oRd_Datas.m_fUcFre))!=0)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRDReadCtrl::ReadRD_IA(BOOL bReadPhase)
{
	if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_A,RAD_INST_A,(m_oRd_Datas.m_fIaAmp))!=0)
	{
		return FALSE;
	}

	if (bReadPhase)
	{
		if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_A,RAD_INST_PHASE,(m_oRd_Datas.m_fIaPhase))!=0)
		{
			return FALSE;
		}
	}

	if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_A,RAD_INST_FREQ,(m_oRd_Datas.m_fIaFre))!=0)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRDReadCtrl::ReadRD_IB(BOOL bReadPhase)
{
	if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_B,RAD_INST_A,(m_oRd_Datas.m_fIbAmp))!=0)
	{
		return FALSE;
	}

	if (bReadPhase)
	{
		float fTmp1 = 0,fTMp2 = 0;

		if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_B,RAD_INST_PHASE,&(fTmp1))!=0)
		{
			return FALSE;
		}

		if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_B,RAD_INST_DPHASE,&(fTMp2))!=0)
		{
			return FALSE;
		}

		m_oRd_Datas.m_fIbPhase[0] = fTmp1 + fTMp2;
	}

	if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_B,RAD_INST_FREQ,(m_oRd_Datas.m_fIbFre))!=0)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRDReadCtrl::ReadRD_IC(BOOL bReadPhase)
{
	if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_C,RAD_INST_A,(m_oRd_Datas.m_fIcAmp))!=0)
	{
		return FALSE;
	}

	if (bReadPhase)
	{
		float fTmp1 = 0,fTMp2 = 0;

		if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_C,RAD_INST_PHASE,&(fTmp1))!=0)
		{
			return FALSE;
		}

		if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_C,RAD_INST_DPHASE,&(fTMp2))!=0)
		{
			return FALSE;
		}

		m_oRd_Datas.m_fIcPhase[0] = fTmp1 + fTMp2;
	}

	if( RadRDInstMetric(m_oDeviceId,RAD_PHASE_C,RAD_INST_FREQ,(m_oRd_Datas.m_fIcFre))!=0)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRDReadCtrl::ReadAllPhases(uint16 nCurrOrVolt)
{
	float fPaseN = 0,fPhaseNet = 0;

	if (nCurrOrVolt == RAD_INST_PHASE)
	{
		if( RadRDInstMetricAll(m_oDeviceId,nCurrOrVolt,&(m_oRd_Datas.m_fUaPhase[0]),&(m_oRd_Datas.m_fUbPhase[0]),&(m_oRd_Datas.m_fUcPhase[0]),
			&(fPaseN),&(fPhaseNet))!=0)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,_T("读取三相电压相位失败."));
			return FALSE;
		}
	} 
	else
	{
		if( RadRDInstMetricAll(m_oDeviceId,nCurrOrVolt,&(m_oRd_Datas.m_fIaPhase[0]),&(m_oRd_Datas.m_fIbPhase[0]),&(m_oRd_Datas.m_fIcPhase[0]),
			&(fPaseN),&(fPhaseNet))!=0)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,_T("读取三相电流相位失败."));
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CRDReadCtrl::ReadRD_THD()
{
// 	if (g_bDebugMode)
// 	{
// 		m_oRd_Datas.m_fUaTHD = 0.1;
// 		m_oRd_Datas.m_fUbTHD = 0.2;
// 		m_oRd_Datas.m_fUcTHD = 0.3;
// 		m_oRd_Datas.m_fIaTHD = 0.4;
// 		m_oRd_Datas.m_fIbTHD = 0.5;
// 		m_oRd_Datas.m_fIcTHD = 0.6;
// 		return TRUE;
// 	}

	long nReadCount = 0;

	if (!ReadRD_THD(RAD_PHASE_A,RAD_INST_V,&m_oRd_Datas.m_fUaTHD,m_oRd_Datas.m_fUaAmp,m_oRd_Datas.m_fUaPhase,m_oRd_Datas.m_fUaFre ,nReadCount))
	{
		return FALSE;
	}

	nReadCount = 0;

	if (!ReadRD_THD(RAD_PHASE_B,RAD_INST_V,&m_oRd_Datas.m_fUbTHD,m_oRd_Datas.m_fUbAmp,m_oRd_Datas.m_fUbPhase,m_oRd_Datas.m_fUbFre,nReadCount))
	{
		return FALSE;
	}

	nReadCount = 0;

	if (!ReadRD_THD(RAD_PHASE_C,RAD_INST_V,&m_oRd_Datas.m_fUcTHD,m_oRd_Datas.m_fUcAmp,m_oRd_Datas.m_fUcPhase,m_oRd_Datas.m_fUcFre,nReadCount))
	{
		return FALSE;
	}

	nReadCount = 0;

	if (!ReadRD_THD(RAD_PHASE_A,RAD_INST_A,&m_oRd_Datas.m_fIaTHD,m_oRd_Datas.m_fIaAmp,m_oRd_Datas.m_fIaPhase,m_oRd_Datas.m_fIaFre,nReadCount))
	{
		return FALSE;
	}

	nReadCount = 0;

	if (!ReadRD_THD(RAD_PHASE_B,RAD_INST_A,&m_oRd_Datas.m_fIbTHD,m_oRd_Datas.m_fIbAmp,m_oRd_Datas.m_fIbPhase,m_oRd_Datas.m_fIbFre,nReadCount))
	{
		return FALSE;
	}

	nReadCount = 0;

	if (!ReadRD_THD(RAD_PHASE_C,RAD_INST_A,&m_oRd_Datas.m_fIcTHD,m_oRd_Datas.m_fIcAmp,m_oRd_Datas.m_fIcPhase,m_oRd_Datas.m_fIcFre,nReadCount))
	{
		return FALSE;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("谐波畸变率(Ua_THD=%f;Ub_THD=%f;Uc_THD=%f;Ia_THD=%f;Ib_THD=%f;Ic_THD=%f;)"),m_oRd_Datas.m_fUaTHD,
		m_oRd_Datas.m_fUbTHD,m_oRd_Datas.m_fUcTHD,m_oRd_Datas.m_fIaTHD,m_oRd_Datas.m_fIbTHD,m_oRd_Datas.m_fIcTHD);
	return TRUE;
}

BOOL CRDReadCtrl::ReadRD_THD(uint16 nDefType,uint16 nCurrOrVolt,float *pfValue,float *pfAmpValue,float *pfPhaseValue,float *pfDistValue,long &nReadCount)
{
	//read harmonic data from all phases
	uint16 phase = nDefType;
	LPSAFEARRAY FAR harmonicdata;
	SAFEARRAYBOUND rgsabound[1];
	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = 151;	//Expect 150 entries per phase
	char buffer[50];
	float *temp;
	HARMONIC_STRUC HarmonicTrigger[10];//zhouhj 20210129  DLL中对该结构体访问越界，导致出错，故将该结构体创建的足够大
	memset(HarmonicTrigger,0,10*sizeof(HARMONIC_STRUC));
	harmonicdata = SafeArrayCreate(VT_R4, 1, rgsabound);

	if (nCurrOrVolt == RAD_INST_V)
	{
		HarmonicTrigger[0].status = (byte)RAD_HARMONIC_VOLTAGE;
	} 
	else
	{
		HarmonicTrigger[0].status = (byte)RAD_HARMONIC_CURRENT;
	}

	HarmonicTrigger[0].base = 1;
	HarmonicTrigger[0].zoom = 1;
	HarmonicTrigger[0].harmonic = 1;
	HarmonicTrigger[0].magnitude = 0;
	HarmonicTrigger[0].phase = 0;
	HarmonicTrigger[0].distortion = 0;

// 	CString strLogString;
// 	strLogString.Format(_T("%d;%d;%d;%d;%f;%f;%f;"),HarmonicTrigger[0].harmonic,HarmonicTrigger[0].status,HarmonicTrigger[0].zoom,
// 		HarmonicTrigger[0].base,HarmonicTrigger[0].magnitude,HarmonicTrigger[0].phase,HarmonicTrigger[0].distortion);
// 	CLogPrint::LogString(XLOGLEVEL_INFOR,strLogString);
// 
// 	strLogString.Format(_T("[1]%d;%d;%d;%d;%f;%f;%f;"),HarmonicTrigger[1].harmonic,HarmonicTrigger[1].status,HarmonicTrigger[1].zoom,
// 		HarmonicTrigger[1].base,HarmonicTrigger[1].magnitude,HarmonicTrigger[1].phase,HarmonicTrigger[1].distortion);
// 	CLogPrint::LogString(XLOGLEVEL_INFOR,strLogString);

	do
	{
		if (HarmonicTrigger[0].status == RAD_HARMONIC_INPROGRESS) 
			HarmonicTrigger[0].status = RAD_HARMONIC_STATUS;

		if (RadRDHarmonicAnalysis(m_oDeviceId, phase, HarmonicTrigger) != 0) 
			StatusError();

		Sleep(100);

// 		strLogString.Format(_T("%d;%d;%d;%d;%f;%f;%f;"),HarmonicTrigger[0].harmonic,HarmonicTrigger[0].status,HarmonicTrigger[0].zoom,
// 			HarmonicTrigger[0].base,HarmonicTrigger[0].magnitude,HarmonicTrigger[0].phase,HarmonicTrigger[0].distortion);
// 		CLogPrint::LogString(XLOGLEVEL_INFOR,strLogString);
// 
// 		strLogString.Format(_T("[1]%d;%d;%d;%d;%f;%f;%f;"),HarmonicTrigger[1].harmonic,HarmonicTrigger[1].status,HarmonicTrigger[1].zoom,
// 			HarmonicTrigger[1].base,HarmonicTrigger[1].magnitude,HarmonicTrigger[1].phase,HarmonicTrigger[1].distortion);
// 		CLogPrint::LogString(XLOGLEVEL_INFOR,strLogString);

		HarmonicTrigger[0].magnitude = 0;
		HarmonicTrigger[0].phase = 0;
		HarmonicTrigger[0].distortion = 0;
	}
	while (HarmonicTrigger[0].status == RAD_HARMONIC_INPROGRESS); //Wait for it to be ready

	if (RadRDHarmonicData(m_oDeviceId, phase, &harmonicdata) != 0) 
		StatusError();
	temp = (float*)((harmonicdata)->pvData);	//Get the proper pointer to the array of data

	float fValues[150];
	memset(fValues,0,150*sizeof(float));
	memcpy(fValues,harmonicdata->pvData,150*sizeof(float));
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;"),fValues[0],fValues[1],fValues[2],fValues[3],fValues[4],
		fValues[5],fValues[6],fValues[7],fValues[8],fValues[9]
	,fValues[10],fValues[11],fValues[12],fValues[13],fValues[14],fValues[15],fValues[16],fValues[17]);

	if (fabs(temp[2]) >= RAD_INVALID_DATA)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("不支持谐波畸变度读取(%ld)."),nDefType);
	}
	else
	{
		*pfValue = temp[2];
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前相(%ld)谐波畸变度(%f)."),nDefType,*pfValue);
	}

	for (int nIndex = 0;nIndex<50;nIndex++)
	{
		pfAmpValue[nIndex] = fValues[nIndex*3];
		pfPhaseValue[nIndex] = fValues[nIndex*3+1];

		if (nIndex != 1)
		{
			pfDistValue[nIndex] = fValues[nIndex*3+2];
		}
	}

// 	if ((abs(*pfValue)<0.00001)&&(nReadCount<3))
// 	{
// 		SafeArrayDestroy(harmonicdata); 
// 		nReadCount++;
// 		return ReadRD_THD(nDefType,nCurrOrVolt,pfValue,nReadCount);
// 	}

//	SafeArrayDestroy(harmonicdata); 
	return TRUE;
}


// BOOL CRDReadCtrl::ReadRD_THD(long nDefType,long nCurrOrVolt,float *pfValue,long &nReadCount)
// {
// 	//	byte bytCurState = (byte)RAD_HARMONIC_INPROGRESS;
// 	HARMONIC_STRUC oStruHarm;
// 	CTickCount32 oTickCount;
// 
// 	if (nCurrOrVolt == RAD_INST_V)
// 	{
// 		oStruHarm.status = (byte)RAD_HARMONIC_VOLTAGE;
// 	} 
// 	else
// 	{
// 		oStruHarm.status = (byte)RAD_HARMONIC_CURRENT;
// 	}
// 
// 	oStruHarm.harmonic = 1;
// 	oStruHarm.zoom = 1;
// 	oStruHarm.base = 1;
// 	oStruHarm.magnitude = 0;
// 	oStruHarm.phase = 0;
// 	oStruHarm.distortion = 0;
// 	CString strLogString;
// 	strLogString.Format(_T("%d;%d;%d;%d;%f;%f;%f;"),oStruHarm.harmonic,oStruHarm.status,oStruHarm.zoom,oStruHarm.base,oStruHarm.magnitude,oStruHarm.phase,oStruHarm.distortion);
// 	CLogPrint::LogString(XLOGLEVEL_INFOR,strLogString);
// 
// 	if (RadRDHarmonicAnalysis(m_oDeviceId,nDefType,&oStruHarm) != 0)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("谐波畸变分析函数RadRDHarmonicAnalysis调用失败(nDefType=%ld;status=%d;)."),nDefType,oStruHarm.status);
// 		return FALSE;
// 	}
// 
// 	strLogString.Format(_T("%d;%d;%d;%d;%f;%f;%f;"),oStruHarm.harmonic,oStruHarm.status,oStruHarm.zoom,oStruHarm.base,oStruHarm.magnitude,oStruHarm.phase,oStruHarm.distortion);
// 	CLogPrint::LogString(XLOGLEVEL_INFOR,strLogString);
// 	long nAnalysisCount = 0;
// 	//	Sleep(100);
// 
// 	while((oStruHarm.status == (byte)RAD_HARMONIC_INPROGRESS)&&(nAnalysisCount<20))
// 	{
// 		if (oStruHarm.status == (byte)RAD_HARMONIC_INPROGRESS)
// 		{
// 			oStruHarm.status = (byte)RAD_HARMONIC_STATUS;
// 		}
// 
// 		strLogString.Format(_T("%d;%d;%d;%d;%f;%f;%f;"),oStruHarm.harmonic,oStruHarm.status,oStruHarm.zoom,oStruHarm.base,oStruHarm.magnitude,oStruHarm.phase,oStruHarm.distortion);
// 		CLogPrint::LogString(XLOGLEVEL_INFOR,strLogString);
// 
// 		//		Sleep(100);
// 
// 		if (RadRDHarmonicAnalysis(m_oDeviceId,nDefType,&oStruHarm) != 0)
// 		{
// 			strLogString.Format(_T("读取谐波畸变分析结果失败(nDefType=%ld;status=%d)."),nDefType,oStruHarm.status);
// 			CLogPrint::LogString(XLOGLEVEL_TRACE,strLogString);
// 			break;
// 			//			return FALSE;
// 		}
// 
// 		Sleep(100);
// 		//		bytCurState = oStruHarm.status;
// 		strLogString.Format(_T("读取谐波畸变分析结果成功(nDefType=%ld;status=%d)."),nDefType,oStruHarm.status);
// 		CLogPrint::LogString(XLOGLEVEL_TRACE,strLogString);
// 		nAnalysisCount++;
// 	}
// 
// 	strLogString.Format(_T("while后(bytCurState=%d;nAnalysisCount=%ld)."),oStruHarm.status,nAnalysisCount);
// 	CLogPrint::LogString(XLOGLEVEL_TRACE,strLogString);
// 	LPSAFEARRAY FAR metricdata;
// 	SAFEARRAYBOUND rgsabound;
// 	float *temp;
// 	float fValues[150];
// 	memset(fValues,0,150*sizeof(float));
// 	//	char buffer[200];
// 	rgsabound.lLbound = 0;
// 	rgsabound.cElements = 300;
// 
// 	metricdata = SafeArrayCreate(VT_R4, 1, &rgsabound);
// 
// 	if((RadRDHarmonicData(m_oDeviceId,nDefType,&metricdata))!= 0)
// 	{
// 		SafeArrayDestroy(metricdata); 
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("谐波畸变度读取失败(%ld)."),nDefType);
// 		return FALSE;
// 	}
// 
// 	memcpy(fValues,metricdata->pvData,150*sizeof(float));
// 	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;"),fValues[0],fValues[1],fValues[2],fValues[3],fValues[4],
// 		fValues[5],fValues[6],fValues[7],fValues[8],fValues[9]
// 	,fValues[10],fValues[11],fValues[12],fValues[13],fValues[14],fValues[15],fValues[16],fValues[17]);
// 	temp = (float*)(metricdata->pvData);
// 
// 	if (fabs(temp[2]) >= RAD_INVALID_DATA)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("不支持谐波畸变度读取(%ld)."),nDefType);
// 	}
// 	else
// 	{
// 		//		sprintf(buffer,"%f", temp[2]);
// 		*pfValue = temp[2];
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前相(%ld)谐波畸变度(%f)."),nDefType,*pfValue);
// 	}
// 
// 	if ((abs(*pfValue)<0.00001)&&(nReadCount<3))
// 	{
// 		SafeArrayDestroy(metricdata); 
// 		nReadCount++;
// 		return ReadRD_THD(nDefType,nCurrOrVolt,pfValue,nReadCount);
// 	}
// 
// 	SafeArrayDestroy(metricdata); 
// 	return TRUE;
// }




CDvmDataset *CRDReadCtrl::GetAinDataset()
{
	CDvmLogicDevice *pLogDevice = NULL;
	CDvmDataset *pDvmDataset = NULL;
	CDvmDataset *pFind = NULL;
	POS pos_ldevice = m_oDeviceModel.GetHeadPosition();

	while(pos_ldevice)
	{
		pLogDevice = (CDvmLogicDevice *)m_oDeviceModel.GetNext(pos_ldevice);

		if (pLogDevice->GetClassID() != DVMCLASSID_CDVMLOGICDEVICE)
		{
			continue;
		}

		POS pos_dataset = pLogDevice->GetHeadPosition();

		while(pos_dataset)
		{
			pDvmDataset = (CDvmDataset*)pLogDevice->GetNext(pos_dataset);

			if (pDvmDataset->GetClassID() != DVMCLASSID_CDVMDATASET)
			{
				continue;
			}

			if (pDvmDataset->m_strID.Find(_T("$dsAin")) != -1)
			{
				pFind = pDvmDataset;
				break;
			}
		}

		if (pFind != NULL)
		{
			break;
		}
	}

	if (pFind == NULL)
	{
		pLogDevice = (CDvmLogicDevice *)m_oDeviceModel.FindByID(_T("TEMPLATEPROT"));

		if (pLogDevice == NULL)
		{
			pLogDevice = new CDvmLogicDevice();
			pLogDevice->m_strID = "TEMPLATEPROT";
			pLogDevice->m_strName = pLogDevice->m_strID;
			pLogDevice->m_nIndex = 1;
			m_oDeviceModel.AddNewChild(pLogDevice);
		}
		
		pFind = new CDvmDataset();
		pFind->m_strID = "LLN0$dsAin";
		pFind->m_strName = pFind->m_strID;
		pFind->m_nIndex = 1;
		pLogDevice->AddNewChild(pFind);
	}

	return pFind;
}

void CRDReadCtrl::InitModel(const CString &strModelPath)
{
	if (strModelPath.IsEmpty())
	{
		m_strModelPath = _P_GetConfigPath();
		m_strModelPath += _T("RD33_Model.xml");
	}
	else
	{
		m_strModelPath = strModelPath;
	}

	m_oDeviceModel.DeleteAll();

	if (IsFileExist(m_strModelPath))
	{
		m_oDeviceModel.OpenXmlFile(m_strModelPath,CDataMngrXmlRWKeys::g_pXmlKeys);
	} 
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("缺少配置文件(%s)."),m_strModelPath);
	}

	m_pCurDataSet = GetAinDataset();
	Regist_AllChannels();
}

void CRDReadCtrl::Regist_AllChannels()
{
	ASSERT(m_pCurDataSet);
	for (int nIndex = 0;nIndex<30;nIndex++)
	{
		Regist_channel(CRdReadConfig::GetUaAmpDesc(nIndex),&m_oRd_Datas.m_fUaAmp[nIndex]);
		Regist_channel(CRdReadConfig::GetUaPhaseDesc(nIndex),&m_oRd_Datas.m_fUaPhase[nIndex]);
		Regist_channel(CRdReadConfig::GetUaFreDesc(nIndex),&m_oRd_Datas.m_fUaFre[nIndex]);
		Regist_channel(CRdReadConfig::GetUbAmpDesc(nIndex),&m_oRd_Datas.m_fUbAmp[nIndex]);
		Regist_channel(CRdReadConfig::GetUbPhaseDesc(nIndex),&m_oRd_Datas.m_fUbPhase[nIndex]);
		Regist_channel(CRdReadConfig::GetUbFreDesc(nIndex),&m_oRd_Datas.m_fUbFre[nIndex]);
		Regist_channel(CRdReadConfig::GetUcAmpDesc(nIndex),&m_oRd_Datas.m_fUcAmp[nIndex]);
		Regist_channel(CRdReadConfig::GetUcPhaseDesc(nIndex),&m_oRd_Datas.m_fUcPhase[nIndex]);
		Regist_channel(CRdReadConfig::GetUcFreDesc(nIndex),&m_oRd_Datas.m_fUcFre[nIndex]);

		Regist_channel(CRdReadConfig::GetIaAmpDesc(nIndex),&m_oRd_Datas.m_fIaAmp[nIndex]);
		Regist_channel(CRdReadConfig::GetIaPhaseDesc(nIndex),&m_oRd_Datas.m_fIaPhase[nIndex]);
		Regist_channel(CRdReadConfig::GetIaFreDesc(nIndex),&m_oRd_Datas.m_fIaFre[nIndex]);
		Regist_channel(CRdReadConfig::GetIbAmpDesc(nIndex),&m_oRd_Datas.m_fIbAmp[nIndex]);
		Regist_channel(CRdReadConfig::GetIbPhaseDesc(nIndex),&m_oRd_Datas.m_fIbPhase[nIndex]);
		Regist_channel(CRdReadConfig::GetIbFreDesc(nIndex),&m_oRd_Datas.m_fIbFre[nIndex]);
		Regist_channel(CRdReadConfig::GetIcAmpDesc(nIndex),&m_oRd_Datas.m_fIcAmp[nIndex]);
		Regist_channel(CRdReadConfig::GetIcPhaseDesc(nIndex),&m_oRd_Datas.m_fIcPhase[nIndex]);
		Regist_channel(CRdReadConfig::GetIcFreDesc(nIndex),&m_oRd_Datas.m_fIcFre[nIndex]);

	}

	Regist_channel(CRdReadConfig::GetUaTHDDesc(),&m_oRd_Datas.m_fUaTHD);
	Regist_channel(CRdReadConfig::GetUbTHDDesc(),&m_oRd_Datas.m_fUbTHD);
	Regist_channel(CRdReadConfig::GetUcTHDDesc(),&m_oRd_Datas.m_fUcTHD);
	Regist_channel(CRdReadConfig::GetIaTHDDesc(),&m_oRd_Datas.m_fIaTHD);
	Regist_channel(CRdReadConfig::GetIbTHDDesc(),&m_oRd_Datas.m_fIbTHD);
	Regist_channel(CRdReadConfig::GetIcTHDDesc(),&m_oRd_Datas.m_fIcTHD);
}

void CRDReadCtrl::Regist_channel(const CString &strChannelDesc,float *pfChannelValue)
{
	ASSERT(m_pCurDataSet);
	POS pos_channel = m_pCurDataSet->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	CDvmData *pFind = NULL;
	CDvmValue *pDvmValue = NULL;

	while(pos_channel)
	{
		pDvmData = (CDvmData*)m_pCurDataSet->GetNext(pos_channel);

		if (pDvmData->m_strName.Find(strChannelDesc) != -1)
		{
			pFind = pDvmData;
			break;
		}
	}

	if (pFind != NULL)
	{
		pFind->m_dwReserved = (DWORD)pfChannelValue;
		pDvmValue = (CDvmValue*)pFind->GetHead();

		if (pDvmValue)
		{
			pDvmValue->m_strValue.Format(_T("%f"),*pfChannelValue);
		}
	}
	else
	{
		pFind = new CDvmData();
		pFind->m_strName = strChannelDesc;
		m_pCurDataSet->AddNewChild(pFind);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("通道(%s)未找到."),strChannelDesc);
	}

	pFind->m_strValue.Format(_T("%f"),*pfChannelValue);
}