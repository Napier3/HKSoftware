// RtVariable.cpp: implementation of the CRtVariable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtVariable.h"
#include "RtVariables.h"
#include "../../API/GloblaDrawFunctions.h"
#include "../MR1200BaseApp.h"
#include "../../API/MathApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// const char *CRtVariable::g_pszKeyColor		= "color";
// const char *CRtVariable::g_pszKeyType		= "type";
// const char *CRtVariable::g_pszKeyVariable	= "variable";
// 
// const char *CRtVariable::g_pszKeyType_U      = "U";
// const char *CRtVariable::g_pszKeyType_I      = "I";
// const char *CRtVariable::g_pszKeyType_NONE   = "NONE";
// 
// const char *CRtVariable::g_pszKeyRecordBufferID  = "record-buf-id";
// const char *CRtVariable::g_pszKeyRecordBufferUse = "record-buf-use";
// const char *CRtVariable::g_pszKeySpyBufferID     = "spy-buf-id";
// const char *CRtVariable::g_pszKeySpyBufferUse    = "spy-buf-use";
// const char *CRtVariable::g_pszKeyHdChIndex       = "hd-ch-index";
// const char *CRtVariable::g_pszKeyTranModel       = "tranmodel";
// const char *CRtVariable::g_pszKeyVariableUse	 = "variable-use";

CRtVariable::CRtVariable()
{
	m_dAngleOffset = 0;
	m_nFrequencyCalBeginPos = 0xFFFFFFFF;                         //频率计算的起始位置 ,0
	m_nAttrCalBeginPos      = 0xFFFFFFFF;                 //属性计算的起始位置
	m_nRefBufLen = 0;
	m_nRefBufFillBeginPos = 0;
	m_nRefBufDataLen = 0;
	memset(m_dwAttrCalPosition, 0, MAX_FREQ_ZERO_POS_BUFFER * sizeof(DWORD));

	m_pRefRecordData = NULL;
	m_pChannels = NULL;
	m_pDataAttrs = NULL;

	//外部关联的数据缓冲区
	m_pChannelBuffer = NULL;
	m_pAttachRecordBuffer = NULL;
	
	//为自身保存的数据而开辟的缓冲区
	m_pAllocBuffer = NULL;

	//录波缓存、监视缓存设置
	m_nRecordBufferUse = 0;
	m_nSpyBufferUse    = 0;
	
	memset(&m_oCurrValue, 0, sizeof(RTCHANNELATTRVALUE));
	memset(&m_oPrevValue, 0, sizeof(RTCHANNELATTRVALUE));
	memset(&m_oMutationValue, 0, sizeof(RTCHANNELATTRVALUE));
	m_nSpyState = 0;
	m_bReadSets = FALSE;

	m_nVariableUse = 0;

	m_pClone = NULL;
	m_pRefRtVariable = NULL;
	m_bChannelBufferCreatedByClone = FALSE;
	m_n64AttrReadBeginPos = 0;
}

CRtVariable::~CRtVariable()
{
	m_pClone = NULL;

	if (m_bChannelBufferCreatedByClone)
	{
		m_bChannelBufferCreatedByClone = FALSE;

		m_pChannelBuffer->AttachSpyMemBuffer(NULL);
		m_pChannelBuffer->AttachRecordMemBuffer(NULL);

		delete m_pChannelBuffer;
	}

	m_pChannelBuffer = NULL;
}

void CRtVariable::CalValues(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCalUseRecordBuffer)
{	
	if(m_nVariableUse == 0)
	{
		return;
	}

	m_pDataAttrs->CalValues(pRtAttrCalBufPos, (m_oCurrValue.dFrequency > 10), bCalUseRecordBuffer);//zhouhj 2024.6.20 增加备注说明,当频率大于10Hz时,进行谐波计算

	double *pDest = &m_oMutationValue.dFrequency;
	double *pSrc1 = &m_oCurrValue.dFrequency;
	double *pSrc2 = &m_oPrevValue.dFrequency;
	
	double *pEnd = pDest + MAX_CHANNEL_ATTRID_KEYS;
	
	while (pDest < pEnd)
	{
		*pDest = fabs(*pSrc1 - *pSrc2);//
		pDest++;
		pSrc1++;
		pSrc2++;
	}

	CalThd();
}

void CRtVariable::CalStaticValues(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer)
{
	if(m_nVariableUse == 0)
	{
		return;
	}

	m_pDataAttrs->CalStaticValues(pRtAttrCalBufPos, bAddFrequency, bCalUseRecordBuffer);	
}

void CRtVariable::CalStaticValues_Quick(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer)
{
	if(m_nVariableUse == 0)
	{
		return;
	}

	m_pDataAttrs->CalStaticValues_Quick(pRtAttrCalBufPos, bAddFrequency, bCalUseRecordBuffer);	
}

void CRtVariable::CalValues_PeakVellay(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer)
{
	if(m_nVariableUse == 0)
	{
		return;
	}

	m_pDataAttrs->CalValues_PeakVellay(pRtAttrCalBufPos, bAddFrequency, bCalUseRecordBuffer);	
}

void CRtVariable::InitCalFuncPara()
{
	m_pDataAttrs->InitCalFuncPara();	
}

void CRtVariable::CalFrequncy(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCalUseRecordBuffer)
{
	if(m_nVariableUse == 0)
	{
		return;
	}

	if (IsRtMultiVariable())
	{
		return;
	}

	m_oPrevValue = m_oCurrValue;
	m_pDataAttrs->CalFrequncy(pRtAttrCalBufPos, bCalUseRecordBuffer);	
}

void CRtVariable::AddAttrValue()
{
	CRtDataAttribute *pDataAttr = NULL;
	POS pos  = NULL;
	pos = m_pDataAttrs->GetHeadPosition();
	
	while (pos != NULL)
	{
		pDataAttr = (CRtDataAttribute*)m_pDataAttrs->GetNext(pos);
		pDataAttr->AddValueToAttrBuffer();
	}
}

BOOL CRtVariable::JudgeStartup(long &nStartup)
{
	if(m_nVariableUse == 0)
	{
		return FALSE;
	}

	if (m_pDataAttrs == NULL)
	{
		return FALSE;
	}

	if (!(m_pDataAttrs->JudgeStartup(nStartup))) 
	{
		debug_trace("CRtVariable Judge Startup failed!");
	}

	return TRUE;
}


void CRtVariable::CalFaultValues(long nBeginPos, long nLen, long nCyclePoints)
{
	m_pDataAttrs->CalFaultValues(nBeginPos, nLen, nCyclePoints);
}

void CRtVariable::CalThd()
{
	int nIndex = 0;
	double dThd = 0;

	if (m_oCurrValue.dFundValue <= 0.0001)
	{
		m_oCurrValue.dTHD = 0;
		return;
	}

	for (nIndex=0; nIndex<24; nIndex++)
	{
		dThd +=  (m_oCurrValue.dHarmValue[nIndex] * m_oCurrValue.dHarmValue[nIndex]) / (m_oCurrValue.dFundValue * m_oCurrValue.dFundValue);
	}

	m_oCurrValue.dTHD = sqrt(dThd);
}

BOOL CRtVariable::GetCalFuncByAttrIDByChannel(const CString &strAttrID, double **ppdValue, double **ppdMutationValue, UINT &nAttrID, CALFUNC **ppCalFunc, RTCALFUNCPARA &oRtCalFuncPara)
{	
	long nCount = MAX_CHANNEL_ATTRID_KEYS;
	nAttrID =GetVariableAttributeID(strAttrID.GetString());
	
	//计算参数值的地址
	if (nAttrID != VariableAttrID_NULL)
	{
		*ppdValue = ( &(m_oCurrValue.dFrequency) + nAttrID);
		*ppdMutationValue = ( &(m_oMutationValue.dFrequency) + nAttrID);

		if (IsRtSingleVariable())
		{
			CRtSingleVariable* pSingle = (CRtSingleVariable*)this;
			
			if (nAttrID == SingleVariableAttrID_EffecValue)
			{
				if (pSingle->IsDCVariable())
				{
					*ppdValue = ( &(m_oCurrValue.dFrequency) + SingleVariableAttrID_AverageValue);
					*ppdMutationValue = ( &(m_oMutationValue.dFrequency) + SingleVariableAttrID_AverageValue);
				}
				else
				{
				}
			}
		}
	}
	else
	{
		*ppdValue = NULL;
		*ppdMutationValue = NULL;
	}

	memset(&oRtCalFuncPara, 0, sizeof(RTCALFUNCPARA));
	oRtCalFuncPara.pRtChAttrVal = &m_oCurrValue;

	if (m_pChannelBuffer == NULL)
	{//不分配spy、record缓冲区
		return TRUE;
	}
	else
	{
	}
	
	CMemBufferInterface *pBuffer = NULL;
	CMemBuffer_Float *pfBuffer = NULL;

	//参考通道的过零点
	CRtVariable *pRefVariable = ((CRtVariables*)GetParent())->GetRefVariable();
	
	if (g_wBufferState == 0) //示波状态
	{
#ifdef _USE_RECORD_BUFFER_TO_CAL
		pBuffer = pRefVariable->m_pChannelBuffer->GetRecordMemBuffer();
#else
		pBuffer = pRefVariable->m_pChannelBuffer->GetSpyMemBuffer();
#endif
	} 
	else if (g_wBufferState == 1) // 分析状态
	{
		pBuffer = pRefVariable->m_pChannelBuffer->GetRecordMemBuffer();
	}
	else
	{
	}

	oRtCalFuncPara.pdwRefFreqZeroPosition = pBuffer->m_dwFreqZeroPosition;
	oRtCalFuncPara.pnRefFreqZeroPosCount   = &pBuffer->m_nFreqZeroPosCount;
	oRtCalFuncPara.pRefFrequency = &pRefVariable->m_oCurrValue.dFrequency;
	oRtCalFuncPara.pRefRtChAttrVal = &pRefVariable->m_oCurrValue;

	if (m_pChannelBuffer != NULL)
	{
		if (g_wBufferState == 0)
		{
#ifdef _USE_RECORD_BUFFER_TO_CAL
			pBuffer = m_pChannelBuffer->GetRecordMemBuffer();
#else
			pBuffer = m_pChannelBuffer->GetSpyMemBuffer();
#endif
		} 
		else if (g_wBufferState == 1)
		{
			pBuffer = m_pChannelBuffer->GetRecordMemBuffer();
		}
		else
		{
		}

		if (pBuffer != NULL)
		{
			CRecordTest *pRecordTest = (CRecordTest*)GetAncestor(RTCLASSID_RECORDTEST);
			oRtCalFuncPara.nChIndex = pBuffer->m_nChIndex;			
			oRtCalFuncPara.dCeofValue = pRecordTest->g_pCoefValue[oRtCalFuncPara.nChIndex];
			oRtCalFuncPara.dZeroValue = pRecordTest->g_pZeroValue[oRtCalFuncPara.nChIndex];
			oRtCalFuncPara.dwSampleRate = pRecordTest->g_nSampleRate;
		}
	}

	if (m_pChannelBuffer->IsRtChTypeComplex())
	{
		if (g_wBufferState == 0)
		{
#ifdef _USE_RECORD_BUFFER_TO_CAL
			pfBuffer = m_pChannelBuffer->GetLRecordMemBuffer();
#else
			pfBuffer = m_pChannelBuffer->GetLSpyMemBuffer();
#endif
		} 
		else if (g_wBufferState == 1)
		{
			pfBuffer = m_pChannelBuffer->GetLRecordMemBuffer();
		}
		else
		{
		}

//		pfBuffer = m_pChannelBuffer->GetLSpyMemBuffer();
		oRtCalFuncPara.pfBuffer = pfBuffer->GetBuffer_float();
		oRtCalFuncPara.pdwFreqZeroPosition = pfBuffer->m_dwFreqZeroPosition;
		oRtCalFuncPara.pnFreqZeroPosCount   = &pfBuffer->m_nFreqZeroPosCount;
	}
	else
	{
		if (g_wBufferState == 0)
		{
#ifdef _USE_RECORD_BUFFER_TO_CAL
			pBuffer = m_pChannelBuffer->GetRecordMemBuffer();
#else
			pBuffer = m_pChannelBuffer->GetSpyMemBuffer();
#endif
		} 
		else if (g_wBufferState == 1)
		{
			pBuffer = m_pChannelBuffer->GetRecordMemBuffer();
		}
		else
		{
		}

		oRtCalFuncPara.pnBuffer = pBuffer->GetBuffer();
		oRtCalFuncPara.pnBuffer_long = pBuffer->GetBuffer_long();
		oRtCalFuncPara.pdwFreqZeroPosition = pBuffer->m_dwFreqZeroPosition;
		oRtCalFuncPara.pnFreqZeroPosCount   = &pBuffer->m_nFreqZeroPosCount;
	}

	return TRUE;
}

BOOL CRtVariable::GetCalFuncByAttrIDByAttach(const CString &strAttrID, double **ppdValue, double **ppdMutationValue, UINT &nAttrID, CALFUNC **ppCalFunc, RTCALFUNCPARA &oRtCalFuncPara)
{
	long nCount = MAX_CHANNEL_ATTRID_KEYS;
	nAttrID =GetVariableAttributeID(strAttrID.GetString());
	
	//计算参数值的地址
	if (nAttrID != VariableAttrID_NULL)
	{
		*ppdValue = ( &(m_oCurrValue.dFrequency) + nAttrID);
		*ppdMutationValue = ( &(m_oMutationValue.dFrequency) + nAttrID);

		if (IsRtSingleVariable())
		{
			CRtSingleVariable* pSingle = (CRtSingleVariable*)this;
			
			if (nAttrID == SingleVariableAttrID_EffecValue)
			{
				if (pSingle->IsDCVariable())
				{
					*ppdValue = ( &(m_oCurrValue.dFrequency) + SingleVariableAttrID_AverageValue);
					*ppdMutationValue = ( &(m_oMutationValue.dFrequency) + SingleVariableAttrID_AverageValue);
				}
				else
				{
				}
			}
		}
	}
	else
	{
		*ppdValue = NULL;
		*ppdMutationValue = NULL;
	}

	memset(&oRtCalFuncPara, 0, sizeof(RTCALFUNCPARA));
	oRtCalFuncPara.pRtChAttrVal = &m_oCurrValue;

	CMemBufferInterface *pBuffer = NULL;
	CMemBufferInterface *pRefBuffer = NULL;
	CMemBuffer_Float *pfBuffer = NULL;

	//参考通道的过零点
	CRtVariable *pRefVariable = ((CRtVariables*)GetParent())->GetRefVariable();
	
	pBuffer = m_pAttachRecordBuffer;

	if (pRefVariable != NULL)
	{
		pRefBuffer = pRefVariable->m_pAttachRecordBuffer;
	}

	if (pBuffer == NULL && pRefBuffer == NULL)
	{
		return TRUE;
	}

	if (pRefBuffer != NULL)
	{
		oRtCalFuncPara.pdwRefFreqZeroPosition = pRefBuffer->m_dwFreqZeroPosition;
		oRtCalFuncPara.pnRefFreqZeroPosCount   = &pRefBuffer->m_nFreqZeroPosCount;
	}
	else
	{
		oRtCalFuncPara.pdwRefFreqZeroPosition = pBuffer->m_dwFreqZeroPosition;
		oRtCalFuncPara.pnRefFreqZeroPosCount   = &pBuffer->m_nFreqZeroPosCount;
	}

	if (pRefVariable != NULL)
	{
		oRtCalFuncPara.pRefFrequency = &pRefVariable->m_oCurrValue.dFrequency;
		oRtCalFuncPara.pRefRtChAttrVal = &pRefVariable->m_oCurrValue;
	}
	else
	{
		oRtCalFuncPara.pRefFrequency = &m_oCurrValue.dFrequency;
		oRtCalFuncPara.pRefRtChAttrVal = &m_oCurrValue;
	}

	CRecordTest *pRecordTest = (CRecordTest*)GetAncestor(RTCLASSID_RECORDTEST);
	oRtCalFuncPara.nChIndex = pBuffer->m_nChIndex;			
	oRtCalFuncPara.dCeofValue = pRecordTest->g_pCoefValue[oRtCalFuncPara.nChIndex];
	oRtCalFuncPara.dZeroValue = pRecordTest->g_pZeroValue[oRtCalFuncPara.nChIndex];
	oRtCalFuncPara.dwSampleRate = pRecordTest->g_nSampleRate;

	oRtCalFuncPara.pnBuffer = pBuffer->GetBuffer();
	oRtCalFuncPara.pnBuffer_long = pBuffer->GetBuffer_long();
	oRtCalFuncPara.pdwFreqZeroPosition = pBuffer->m_dwFreqZeroPosition;
	oRtCalFuncPara.pnFreqZeroPosCount   = &pBuffer->m_nFreqZeroPosCount;

	return TRUE;
}


BOOL CRtVariable::GetCalFuncByAttrID(const CString &strAttrID, double **ppdValue, double **ppdMutationValue, UINT &nAttrID, CALFUNC **ppCalFunc, RTCALFUNCPARA &oRtCalFuncPara, BOOL bCalUseRecordBuffer)
{
	if (bCalUseRecordBuffer)
	{
		GetCalFuncByAttrIDByChannel(strAttrID, ppdValue, ppdMutationValue, nAttrID, ppCalFunc, oRtCalFuncPara);
	}
	else
	{
		GetCalFuncByAttrIDByAttach(strAttrID, ppdValue, ppdMutationValue, nAttrID, ppCalFunc, oRtCalFuncPara);
	}

	/* ##############################################################
	 *	此处存在的隐患：
	 *  很多的属性定义是配对的，例如二次谐波幅值和相位
	 *  但是这些参数的计算可能放在一个函数中去计算，因此需要考虑如何去实现
	 *///############################################################
	switch(nAttrID)
	{
	case SingleVariableAttrID_Frequancy:             //0
		*ppCalFunc = RT_CalFrequency;//计算频率的函数
		break;
	case SingleVariableAttrID_EffecValue:             //1
		{
			if (IsRtSingleVariable())
			{
				CRtSingleVariable* pSingle = (CRtSingleVariable*)this;
				
				if (pSingle->IsDCVariable())
				{
					*ppCalFunc = RT_CalAverageValue;
				}
				else
				{
		*ppCalFunc = RT_CalEffecValue;
				}
			}
			else
			{
				
			}
		}
		break;
	case SingleVariableAttrID_EffecPhase:             //1
		*ppCalFunc = NULL;//RT_CalEffecValue;
		break;
	case SingleVariableAttrID_FundValue:             //2
		*ppCalFunc = RT_CalFundValue;
		break;
	case SingleVariableAttrID_FundPhase:            //3
		*ppCalFunc = NULL;//RT_CalFundPhase;
		break;
	case SingleVariableAttrID_PeakValue:             //4
		*ppCalFunc = RT_CalPeakValue;
		break;
	case SingleVariableAttrID_VellayValue:           //5
		*ppCalFunc = RT_CalVellayValue;
		break;
	case SingleVariableAttrID_InstValue:              //6
		*ppCalFunc = RT_CalInstValue;
		break;
	case SingleVariableAttrID_AverageValue:        //7
		*ppCalFunc = RT_CalAverageValue;
		break;
	case SingleVariableAttrID_Harm02Value:        //8
		*ppCalFunc = RT_CalHarm02Value;
		break;
	case SingleVariableAttrID_Harm03Value:        //9
		*ppCalFunc = RT_CalHarm03Value;
		break;
	case SingleVariableAttrID_Harm04Value:        //10
		*ppCalFunc = RT_CalHarm04Value;
		break;
	case SingleVariableAttrID_Harm05Value:        //11
		*ppCalFunc = RT_CalHarm05Value;
		break;
	case SingleVariableAttrID_Harm06Value:        //12
		*ppCalFunc = RT_CalHarm06Value;
		break;
	case SingleVariableAttrID_Harm07Value:        //13
		*ppCalFunc = RT_CalHarm07Value;
		break;
	case SingleVariableAttrID_Harm08Value:        //14
		*ppCalFunc = RT_CalHarm08Value;
		break;
	case SingleVariableAttrID_Harm09Value:        //15
		*ppCalFunc = RT_CalHarm09Value;
		break;
	case SingleVariableAttrID_Harm10Value:        //16
		*ppCalFunc = RT_CalHarm10Value;
		break;
	case SingleVariableAttrID_Harm11Value:        //17
		*ppCalFunc = RT_CalHarm11Value;
		break;
	case SingleVariableAttrID_Harm12Value:        //18
		*ppCalFunc = RT_CalHarm12Value;
		break;
	case SingleVariableAttrID_Harm13Value:        //19
		*ppCalFunc = RT_CalHarm13Value;
		break;
	case SingleVariableAttrID_Harm14Value:        //20
		*ppCalFunc = RT_CalHarm14Value;
		break;
	case SingleVariableAttrID_Harm15Value:        //21
		*ppCalFunc = RT_CalHarm15Value;
		break;
	case SingleVariableAttrID_Harm16Value:        //22
		*ppCalFunc = RT_CalHarm16Value;
		break;
	case SingleVariableAttrID_Harm17Value:        //23
		*ppCalFunc = RT_CalHarm17Value;
		break;
	case SingleVariableAttrID_Harm18Value:        //24
		*ppCalFunc = RT_CalHarm18Value;
		break;
	case SingleVariableAttrID_Harm19Value:        //25
		*ppCalFunc = RT_CalHarm19Value;
		break;
	case SingleVariableAttrID_Harm20Value:        //26
		*ppCalFunc = RT_CalHarm20Value;
		break;
	case SingleVariableAttrID_Harm21Value:        //27
		*ppCalFunc = RT_CalHarm21Value;
		break;
	case SingleVariableAttrID_Harm22Value:        //28
		*ppCalFunc = RT_CalHarm22Value;
		break;
	case SingleVariableAttrID_Harm23Value:        //29
		*ppCalFunc = RT_CalHarm23Value;
		break;
	case SingleVariableAttrID_Harm24Value:        //30
		*ppCalFunc = RT_CalHarm24Value;
		break;
	case SingleVariableAttrID_Harm25Value:        //31
		*ppCalFunc = RT_CalHarm25Value;
		break;
	case SingleVariableAttrID_Harm02Phase:        //32
		*ppCalFunc = RT_CalHarm02Phase;
		break;
	case SingleVariableAttrID_Harm03Phase:        //33
		*ppCalFunc = RT_CalHarm03Phase;
		break;
	case SingleVariableAttrID_Harm04Phase:        //34
		*ppCalFunc = RT_CalHarm04Phase;
		break;
	case SingleVariableAttrID_Harm05Phase:        //35
		*ppCalFunc = RT_CalHarm05Phase;
		break;
	case SingleVariableAttrID_Harm06Phase:        //36
		*ppCalFunc = RT_CalHarm06Phase;
		break;
	case SingleVariableAttrID_Harm07Phase:        //37
		*ppCalFunc = RT_CalHarm07Phase;
		break;
	case SingleVariableAttrID_Harm08Phase:        //38
		*ppCalFunc = RT_CalHarm08Phase;
		break;
	case SingleVariableAttrID_Harm09Phase:        //39
		*ppCalFunc = RT_CalHarm09Phase;
		break;
	case SingleVariableAttrID_Harm10Phase:        //40
		*ppCalFunc = RT_CalHarm10Phase;
		break;
	case SingleVariableAttrID_Harm11Phase:        //41
		*ppCalFunc = RT_CalHarm11Phase;
		break;
	case SingleVariableAttrID_Harm12Phase:        //42
		*ppCalFunc = RT_CalHarm12Phase;
		break;
	case SingleVariableAttrID_Harm13Phase:        //43
		*ppCalFunc = RT_CalHarm13Phase;
		break;
	case SingleVariableAttrID_Harm14Phase:        //44
		*ppCalFunc = RT_CalHarm14Phase;
		break;
	case SingleVariableAttrID_Harm15Phase:        //45
		*ppCalFunc = RT_CalHarm15Phase;
		break;
	case SingleVariableAttrID_Harm16Phase:        //46
		*ppCalFunc = RT_CalHarm16Phase;
		break;
	case SingleVariableAttrID_Harm17Phase:        //47
		*ppCalFunc = RT_CalHarm17Phase;
		break;
	case SingleVariableAttrID_Harm18Phase:        //48
		*ppCalFunc = RT_CalHarm18Phase;
		break;
	case SingleVariableAttrID_Harm19Phase:        //49
		*ppCalFunc = RT_CalHarm19Phase;
		break;
	case SingleVariableAttrID_Harm20Phase:        //50
		*ppCalFunc = RT_CalHarm20Phase;
		break;
	case SingleVariableAttrID_Harm21Phase:        //51
		*ppCalFunc = RT_CalHarm21Phase;
		break;
	case SingleVariableAttrID_Harm22Phase:        //52
		*ppCalFunc = RT_CalHarm22Phase;
		break;
	case SingleVariableAttrID_Harm23Phase:        //53
		*ppCalFunc = RT_CalHarm23Phase;
		break;
	case SingleVariableAttrID_Harm24Phase:        //54
		*ppCalFunc = RT_CalHarm24Phase;
		break;
	case SingleVariableAttrID_Harm25Phase:        //55	
		*ppCalFunc = RT_CalHarm25Phase;
		break;
	case MultiVariableAttrID_Impedance :             //0
		*ppCalFunc = RT_CalImpedance    ;//计算阻抗的函数
		break;
	case MultiVariableAttrID_PositiveSequence:       //1
		*ppCalFunc = RT_CalPositiveSequence;
		break;
	case MultiVariableAttrID_NegativeSequence:       //2
		*ppCalFunc = RT_CalNegativeSequence;
		break;
	case MultiVariableAttrID_ZeroSequence:           //3
		*ppCalFunc = RT_CalZeroSequence;
		break;
	case MultiVariableAttrID_ActivePower:            //4
		*ppCalFunc = RT_CalActivePower;
		break;
	case MultiVariableAttrID_ReactivePower:          //5
		*ppCalFunc = RT_CalReactivePower;
		break;
	case MultiVariableAttrID_ApparentPower:          //6
		*ppCalFunc = RT_CalApparentPower;
		break;
	case MultiVariableAttrID_ThreePhaseAverageValue: //7
		*ppCalFunc = RT_CalReserve01Value;
		break;
// 	case MultiVariableAttrID_Reserve02Value:         //8
// 		*ppCalFunc = RT_CalReserve02Value;
// 		break;
// 	case MultiVariableAttrID_Reserve03Value:         //9
// 		*ppCalFunc = RT_CalReserve03Value;
// 		break;
// 	case MultiVariableAttrID_Reserve04Value:         //10
// 		*ppCalFunc = RT_CalReserve04Value;
// 		break;
	case MultiVariableAttrID_Reserve05Value:         //11
		*ppCalFunc = RT_CalReserve05Value;
		break;
	case MultiVariableAttrID_Reserve06Value:         //12
		*ppCalFunc = RT_CalReserve06Value;
		break;
	case MultiVariableAttrID_Reserve07Value:         //13
		*ppCalFunc = RT_CalReserve07Value;
		break;
	case MultiVariableAttrID_Reserve08Value:         //14
		*ppCalFunc = RT_CalReserve08Value;
		break;
// 	case MultiVariableAttrID_Reserve09Value:         //15
// 		*ppCalFunc = RT_CalReserve09Value;
// 		break;
// 	case MultiVariableAttrID_Reserve10Value:         //16
// 		*ppCalFunc = RT_CalReserve10Value;
// 		break;	
	default:
		break;
	}
	
	return TRUE;
}

double* CRtVariable::GetValueRefByID(const CString &strID)
{
	if (m_pDataAttrs == NULL)
	{
		return NULL;
	}

	double *pdValue = NULL;
	
	pdValue = m_pDataAttrs->GetValueRefByID(strID);
		
	return pdValue;
}

double* CRtVariable::GetAttrValueRefByID(const CString &strID)
{
	if (m_pDataAttrs == NULL)
	{
		return NULL;
	}

	double *pdValue = NULL;
	
	pdValue = m_pDataAttrs->GetAttrValueRefByID(strID);
	
	return pdValue;
}

double* CRtVariable::GetMutationValueRefByID(const CString &strID)
{
	if (m_pDataAttrs == NULL)
	{
		return NULL;
	}

	double *pdValue = NULL;
	
	pdValue = m_pDataAttrs->GetMutationValueRefByID(strID);
	
	return pdValue;
}

void CRtVariable::AdjustStaticAttrs()
{
	UINT nClassID = GetClassID();

	if (nClassID == RTCLASSID_SINGLEVARIABLE || nClassID == RTCLASSID_COMPLEXVARIABLE)
	{
		m_pDataAttrs->AdjustStaticAttrs();
	}
	else if (nClassID == RTCLASSID_MULTIVARIABLE)
	{
		m_pDataAttrs->AdjustMultiVariableAttrs();
	}
	else
	{
	}
}

BOOL CRtVariable::BuildExpression()
{
	if (m_pDataAttrs == NULL)
	{
		return FALSE;
	}

	if (!(m_pDataAttrs->BuildExpression()))
	{
		debug_trace("CRtVariable Build Expression failed!");
	}
	
	return TRUE;
}


void CRtVariable::InitBufferMngr(CRtMemBufferMngr *pRtMemBufferMngr)
{
	UINT nClassID = GetClassID();
	
	if (nClassID == RTCLASSID_COMPLEXVARIABLE)
	{
		ASSERT (m_pChannels != NULL);
		ASSERT (m_pChannels->m_pScript != NULL);
		
		m_pChannelBuffer = pRtMemBufferMngr->AddMR1200ComplexChannel(m_strID, m_nRecordBufferUse, m_strRecordBufferID, m_nSpyBufferUse, m_strSpyBufferID, m_pChannels->m_pScript);
	}
	else
	{
		m_pChannelBuffer = pRtMemBufferMngr->AddMR1200Channel(m_strID, m_nRecordBufferUse, m_strRecordBufferID, m_nSpyBufferUse, m_strSpyBufferID);
	}	

	m_pDataAttrs->InitBufferMngr(pRtMemBufferMngr);
}

void CRtVariable::InitAttrsBuffer(long nPoints)
{
	m_pDataAttrs->InitAttrsBuffer(nPoints);
}

BOOL CRtVariable::IsRecordBufferNull(BOOL bCalUseRecordBuffer)
{
	if (bCalUseRecordBuffer)
	{
		if (m_pChannelBuffer == NULL)
		{
			return TRUE;
		}

		if (m_pChannelBuffer->GetRecordMemBuffer() == NULL)
		{
			return TRUE;
		}

		if (m_pChannelBuffer->GetRecordMemBuffer()->GetBuffer() == NULL)
		{
			return TRUE;
		}
	}
	else
	{
		if (m_pAttachRecordBuffer == NULL)
		{
			return TRUE;
		}

		if (m_pAttachRecordBuffer->GetBuffer() == NULL)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CRtVariable::InitDataAttributeCalFunc(BOOL bCalUseRecordBuffer)
{
	if (m_pDataAttrs == NULL)
	{
		return FALSE;
	}

	if (!(m_pDataAttrs->InitDataAttributeCalFunc(bCalUseRecordBuffer)))
	{
		debug_trace("CRtVariable Initialize DataAttributeCalFunc failed!");
	}
	
	return TRUE;
}

PRTATTRIBUTECALFUNCPARA CRtVariable::GetAttrCalFuncPara(UINT nAttrID)
{
	POS pos  = m_pDataAttrs->GetHeadPosition();
	CRtDataAttribute *pFind = NULL;
	CRtDataAttribute *pAttr = NULL;
	PRTATTRIBUTECALFUNCPARA pCalFuncPara = NULL;

	while (pos != NULL)
	{
		pAttr = (CRtDataAttribute*)m_pDataAttrs->GetNext(pos);

		if (pAttr->m_nAttributeID == nAttrID)
		{
			pFind = pAttr;
			break;
		}
	}

	if (pFind != NULL)
	{
		return &(pFind->m_oCalFuncPara);
	}
	else
	{
		return NULL;
	}
}

// 
// //树形控件相关的操作
// void CRtVariable::InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand, HTREEITEM hAfter)
// {
// 	CString strItem = m_strName;
// 	CString strTemp;
// 
// 	if (m_nSpyBufferUse == 1)
// 	{
// 		strTemp.Format(" : spy-buf=[%s]", m_strSpyBufferID);
// 		strItem += strTemp;
// 	}
// 
// 	if (m_nRecordBufferUse == 1)
// 	{
// 		strTemp.Format(" : spy-buf=[%s]", m_strRecordBufferID);
// 		strItem += strTemp;
// 	}
// 	
// 	m_hTreeItem = pTreeCtrl->InsertItem(strItem, 0, 0, htiParent, hAfter);
// 	pTreeCtrl->SetItemData(m_hTreeItem,(DWORD)this);
// 	
// 	InsertChildrenTreeCtrl(pTreeCtrl, m_hTreeItem, bParentExpand);
// }

CString CRtVariable::GetAttrBufferIDByAttrID(LPCTSTR pszAttrID)
{
	CString strAttrBufferID;
	CRtDataAttribute *pAttr = NULL;
	POS pos  = m_pDataAttrs->GetHeadPosition();

	while (pos != NULL)
	{
		pAttr = (CRtDataAttribute *)m_pDataAttrs->GetNext(pos);

		if (pAttr != NULL)
		{
			if (pAttr->m_strID == pszAttrID)
			{
				strAttrBufferID = pAttr->m_strBufferID;
				break;
			}
		}
	}

	return strAttrBufferID;
}

void CRtVariable::InitAfterClone()
{
	CExBaseObject *pNew = NULL;
	POS pos  = GetHeadPosition();

	while (pos != NULL)
	{
		pNew = (CExBaseObject*)GetNext(pos);
		long nClassID = pNew->GetClassID();

		switch(nClassID)
		{
		case RTCLASSID_CHANNELS:
			m_pChannels = (CRtChannels*)pNew;
			break;
		case RTCLASSID_DATAATTRIBUTES:
			m_pDataAttrs = (CRtDataAttributes*)pNew;
			break;
		case RTCLASSID_ALLOCBUFFER:
			m_pAllocBuffer = (CRtAllocBuffer*)pNew;
			break;
		default:
			break;
		}
	}
}

double* CRtVariable::GetValueByAttrID(const CString &strID)
{
	ASSERT(m_pDataAttrs != NULL);
	if (m_pDataAttrs == NULL)
	{
		return NULL;
	}
	
	double *pdValue = NULL;
	CRtDataAttribute* pAttr = m_pDataAttrs->FindByAttrID(strID.GetString());
	if (pAttr != NULL)
	{
		pdValue = pAttr->m_pdValue;
	}
	
	return pdValue;
}

double* CRtVariable::GetCloneValueByAttrID(const CString &strID)
{
	ASSERT(m_pDataAttrs != NULL);
	if (m_pDataAttrs == NULL)
	{
		return NULL;
	}
	
	double *pdValue = NULL;
	CRtDataAttribute* pAttr = m_pDataAttrs->FindByAttrID(strID.GetString());

	if (pAttr != NULL)
	{
		if (pAttr->m_pClone != NULL)
		{
			pdValue = pAttr->m_pClone->m_pdValue;
		}
	}
	
	return pdValue;
}

double* CRtVariable::GetCalValueByAttrID(const CString &strID)
{
	double* pdValue = NULL;

	if (g_theRecordApp.IsInRecordHoldState())
	{
		pdValue = GetCloneValueByAttrID(strID);
	}
	else
	{
		pdValue = GetValueByAttrID(strID);
	}

	return pdValue;
}

long CRtVariable::Get_ChIndex()
{
	CMemBufferInterface* pMemBuf = GetChannelBuffer();

	if (pMemBuf == NULL)
	{
		return -1;
	}

	return pMemBuf->m_nChIndex;
}

void CRtVariable::Set_ChIndex(long nIndex)
{
	CMemBufferInterface* pMemBuf = GetChannelBuffer();

	if (pMemBuf == NULL)
	{
		return;
	}

	pMemBuf->m_nChIndex = nIndex;
}

long CRtVariable::Get_HdIndex()
{
	CMemBufferInterface* pMemBuf = GetChannelBuffer();

	if (pMemBuf == NULL)
	{
		return -1;
	}

	return pMemBuf->m_nHdIndex;
}

void CRtVariable::Set_HdIndex(long nIndex)
{
	CMemBufferInterface* pMemBuf = GetChannelBuffer();

	if (pMemBuf == NULL)
	{
		return;
	}

	pMemBuf->m_nHdIndex = nIndex;
}


BOOL CRtVariable::CanCal()
{
// 	if (m_strID.Find(_T("DelayTRtg")) >= 0) //20220609 zhouhj 延时通道需要获取对应的数据值,只是不需要进行有效值计算
// 	{
// 		//时间通道不进行计算
// 		return FALSE;
// 	}

	if (!HasChannelBuffer())
	{
		return FALSE;
	}

	return TRUE;
}



void CRtVariable::CloneVariable(CRtVariable* pSrc,CMemBuffer_UShort* pAttachBuffer)
{
	m_strName = pSrc->m_strName;
	m_strID   = pSrc->m_strID;
	
	//先将本对象缓存对应的
	pSrc->m_pClone = this;	
	m_bChannelBufferCreatedByClone = TRUE;

	//关联缓存,将录波缓存和属性缓存都设置成一样的
	m_pChannelBuffer = new CRtMemBufferChannel();
	m_pChannelBuffer->AttachRecordMemBuffer(pAttachBuffer);
	m_pChannelBuffer->AttachSpyMemBuffer(pAttachBuffer);

	m_nSpyState = pSrc->m_nSpyState;
	m_nVariableUse = pSrc->GetVariableUseState();

	if (pSrc->m_pDataAttrs != NULL)
	{
		//创建子对象
		m_pDataAttrs = new CRtDataAttributes();
		m_pDataAttrs->SetParent(this);
		
		//将子对象放入链表
		AddTail(m_pDataAttrs);

		//子对象Clone
		m_pDataAttrs->CloneRtDataAttributes(pSrc->m_pDataAttrs);
	}
}

void CRtVariable::SetAttrUse(UINT nAttrID, long nUse)
{
	m_pDataAttrs->SetAttrUse(nAttrID, nUse);
}

void CRtVariable::CalInstValue(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos,BOOL bCalUseRecordBuffer)
{
	if(m_nVariableUse == 0)
	{
		return;
	}

	m_pDataAttrs->CalInstValue(pRtAttrCalBufPos,bCalUseRecordBuffer);
}


CString CRtVariable::GetUnitString()
{
	CString strUnit = "";
	return strUnit;
}

void CRtVariable::ZeroCalValues()
{
	m_oPrevValue = m_oCurrValue;
	memset(&m_oCurrValue, 0, sizeof(RTCHANNELATTRVALUE));
}

void CRtVariable::ZeroAllCalValues()
{
	memset(&m_oCurrValue, 0, sizeof(RTCHANNELATTRVALUE));
	memset(&m_oPrevValue, 0, sizeof(RTCHANNELATTRVALUE));
	memset(&m_oMutationValue, 0, sizeof(RTCHANNELATTRVALUE));
}

void CRtVariable::InitCalPos()
{
	CMemBufferInterface *pRefBuffer = NULL;

	if (m_pChannelBuffer != NULL)
	{
#ifdef _USE_RECORD_BUFFER_TO_CAL
		pRefBuffer = m_pChannelBuffer->GetRecordMemBuffer();
#else
		pRefBuffer = m_pChannelBuffer->GetSpyMemBuffer();
#endif
	}
	else
	{
		pRefBuffer = m_pAttachRecordBuffer;
	}

	m_nRefBufLen			= pRefBuffer->GetBufferLength();
	m_nRefBufFillBeginPos	= pRefBuffer->GetDataFillBeginPosition();
	m_nRefBufDataLen		= pRefBuffer->GetDataLength();
}


void CRtVariable::InitCalPos(long nRefBufLen, long nRefBufFillBeginPos, long RefBufDataLen)
{
	m_nRefBufLen			= nRefBufLen;
	m_nRefBufFillBeginPos	= nRefBufFillBeginPos;
	m_nRefBufDataLen		= RefBufDataLen;
}

void CRtVariable::ResetValueCal()
{
	m_nFrequencyCalBeginPos = 0xFFFFFFFF;                         //频率计算的起始位置 ,0
	m_nAttrCalBeginPos      = 0xFFFFFFFF;                 //属性计算的起始位置
	m_nRefBufLen = 0;
	m_nRefBufFillBeginPos = 0;
	m_nRefBufDataLen = 0;

	memset(&m_oCurrValue, 0, sizeof(RTCHANNELATTRVALUE));
	memset(&m_oPrevValue, 0, sizeof(RTCHANNELATTRVALUE));
	memset(&m_oMutationValue, 0, sizeof(RTCHANNELATTRVALUE));

	if (m_pChannelBuffer != NULL)
	{
		
	}

	if (m_pAttachRecordBuffer != NULL)
	{
		m_pAttachRecordBuffer->Init();
	}
}
