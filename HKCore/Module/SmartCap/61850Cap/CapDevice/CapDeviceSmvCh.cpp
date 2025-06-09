//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceSmvCh.cpp  CCapDeviceSmvCh


#include "stdafx.h"
#include "CapDeviceSmvCh.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfg92ChIn.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfg6044CommonChIn.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"
#include "CapAnalysisConfig.h"
#include "../CapDevice/CapDevice6044.h"
//#include "../CapGlobalDef.h"

CCapDeviceSmvCh::CCapDeviceSmvCh()
{
	//初始化属性
	//2022-4-17  初始化为位置通道类型
	m_nChType = CAPDEVICE_CHTYPE_I; //CAPDEVICE_CHTYPE_U;// 电压=0；电流=1；时间=2
	m_nChRateIndex = 0;
    m_fChRate = 1.0f;
	m_nAccurLevel = 0;
	m_nChAngType = 0;
	InitAfterSetChType();

	m_dwQuality = 0x0;
	//初始化成员变量
	m_wValue = 0xFFFFFFFF;
	m_dwValue = 0xFFFFFFFF;
	m_fValue = 0;
}

CCapDeviceSmvCh::~CCapDeviceSmvCh()
{
	
}

void CCapDeviceSmvCh::SetChRateString(const CString &strRate)
{
	m_nChRateIndex = st_GetCapDeviceChRateIndex(strRate);
	m_fChRate = st_GetCapDeviceChRate(m_nChRateIndex);
	m_fChRate = 1 / m_fChRate;
}

void CCapDeviceSmvCh::SetChRateIndex(long nIndex)
{
	m_nChRateIndex = nIndex;
	m_fChRate = st_GetCapDeviceChRate(m_nChRateIndex);
	m_fChRate = 1 / m_fChRate;
}

void CCapDeviceSmvCh::UpdateChDescByChTypeChAng()
{
	if (m_nChType == CAPDEVICE_CHTYPE_T)
	{
		m_strName = _T("额定延时");
		return;
	}

	if (m_strName.Find(_T("保护")) != -1)
	{
		m_strName = _T("保护");
	}
	else if (m_strName.Find(_T("测量")) != -1)
	{
		m_strName = _T("测量");
	}
	else
	{
		m_strName = _T("");
	}

	if(m_nChType == CAPDEVICE_CHTYPE_I)
	{
		m_strName += _T("电流");
	}
	else if (m_nChType == CAPDEVICE_CHTYPE_U)
	{
		m_strName += _T("电压");
	} 
	else
	{
		return;
	}

	long nChAngType = m_nChAngType%4,nChAngGroupIndex = m_nChAngType/4;

	switch(nChAngType)
	{
	case 0:
		m_strName += _T("A相");
		break;
	case 1:
		m_strName += _T("B相");
		break;
	case 2:
		m_strName += _T("C相");
		break;
	case 3:
		m_strName += _T("零序");
		break;
	default:
		break;
	}

	m_strName.AppendFormat(_T("%ld"),nChAngGroupIndex+1);
}

void CCapDeviceSmvCh::InitChannel(CIecCfgDataChBase *pIecCfgDataCh)
{
	ASSERT(pIecCfgDataCh != NULL);

	if(pIecCfgDataCh == NULL)
	{
		return;
	}

	CIecCfgDataSmvChBase* pSmvCh = (CIecCfgDataSmvChBase*)pIecCfgDataCh;

	if (pSmvCh->GetClassID() == CFGCLASSID_CIECCFG92CHIN)
	{
		CIecCfg92ChIn *pCfg92ChIn = (CIecCfg92ChIn*)pSmvCh;
		m_nAccurLevel = pCfg92ChIn->m_nAccuratyLevel;
		m_nChAngType = pCfg92ChIn->GetChAngType();
		m_nSelect = pCfg92ChIn->m_nUseFlag;
	}
	else if (pSmvCh->GetClassID() == CFGCLASSID_CIECCFG6044COMMONCHIN)
	{
		CIecCfg6044CommonChIn *pCfg6044CommonChIn = (CIecCfg6044CommonChIn*)pSmvCh;
		m_nAccurLevel = pCfg6044CommonChIn->m_nAccuratyLevel;
		m_nChAngType = pCfg6044CommonChIn->GetChAngType();
		m_nSelect = pCfg6044CommonChIn->m_nUseFlag;
	}

	SetChType(pSmvCh->m_strChType);

	if (pSmvCh->GetClassID() == CFGCLASSID_CIECCFG92CH)
	{	
		m_nLength = 4;
	}
	else
	{
		m_nLength = 2;
	}

	BOOL bDCFT3 = FALSE;
	CExBaseObject *pParent = (CExBaseObject*)GetParent();

	if (pParent != NULL)
	{
		if (pParent->GetClassID() == CPDCLASSID_DEVICE6044)
		{
			CCapDevice6044 *pCapDevice6044 = (CCapDevice6044*)pParent;
			bDCFT3 = pCapDevice6044->m_bDC_FT3;
		}
	}

	m_fChRate = st_GetCapDeviceSVRate(pSmvCh,bDCFT3);

	CCapDeviceChBase::InitChannel(pIecCfgDataCh);
}

#include "../../XSttRcdInitChDvmData.h"
void CCapDeviceSmvCh::InitChannelAttrs(CDvmData *pChData)
{
	pChData->m_strDataType = GetChType();

	if (m_nChType == CAPDEVICE_CHTYPE_U)
	{
		pChData->m_strUnit = _T("V");
	} 
	else if (m_nChType == CAPDEVICE_CHTYPE_I)
	{
		pChData->m_strUnit = _T("A");
	}

	XSttRcdInitChDvmData(pChData, g_nXSttRcdInitChDvmData_Harm, TRUE);
}

void CCapDeviceSmvCh::UpdateChTypeAndLength(WORD wChType,WORD wLength)
{
	if ((m_nChType<0)||(m_nChType>=3))
	{
		m_nChType = CAPDEVICE_CHTYPE_I;
	}
	if (wLength == 0)
	{
		InitAfterSetChType();
		return;
	}

	if (wChType<3)
	{
		m_nChType = wChType;
	}

	m_nLength = wLength;

	InitAfterSetChType();
}

void CCapDeviceSmvCh::InitAfterSetChType()
{
	double dCT_Rate = 1.0f,dPT_Rate = 1.0f;

	if ((!g_oCapAnalysisConfig.m_nShowPrimaryValue)&&(m_strID.Find("DelayTRtg")== -1))//判断是否为显示二次值、判断是否为延时通道
	{
		long nGroupIndex = m_nChAngType/4;

		if (nGroupIndex>=6)
			{
			nGroupIndex = 0;
		}

		dCT_Rate = g_oCapAnalysisConfig.m_fCT_Rate[nGroupIndex];
		dPT_Rate = g_oCapAnalysisConfig.m_fPT_Rate[nGroupIndex];

// 		if ((m_strID.Find("DV") == -1)&&(!m_strID.IsEmpty()))
// 		{
// 			CString strValue;
// 			strValue = m_strID.Right(1);
// 			long nValue = CString_To_long(strValue);
// 
// 			for (int nIndex = 1;nIndex<=6;nIndex++)
// 			{
// 				if (nValue == nIndex)
// 				{
// 					dCT_Rate = g_oCapAnalysisConfig.m_fCT_Rate[nIndex-1];
// 					dPT_Rate = g_oCapAnalysisConfig.m_fPT_Rate[nIndex-1];
// 					break;
// 				}
// 			}
// 		}
// 		else
// 		{
// 			dCT_Rate = g_oCapAnalysisConfig.m_dCT_PrimaryValue/g_oCapAnalysisConfig.m_dCT_SecondValue;
// 			dPT_Rate = g_oCapAnalysisConfig.m_dPT_PrimaryValue*1000/g_oCapAnalysisConfig.m_dPT_SecondValue;
// 		}
	}

	if (m_nChType == CAPDEVICE_CHTYPE_I)
	{
		m_nChRateIndex = 1;
		m_fChRate = st_GetCapDeviceChRate(m_nChRateIndex);
		m_fChRate = 1 / (m_fChRate*dCT_Rate);
	}
	else if (m_nChType == CAPDEVICE_CHTYPE_U)
	{
		m_nChRateIndex = 2;
		m_fChRate = st_GetCapDeviceChRate(m_nChRateIndex);
		m_fChRate = 1 / (m_fChRate*dPT_Rate);
	}
	else
	{
		m_nChRateIndex = 0;
		m_fChRate = st_GetCapDeviceChRate(m_nChRateIndex);
		m_fChRate = 1 / m_fChRate;
	}
}

//////////////////////////////////////////////////////////////////////////
//
#define CAPDEVICE_CHREATE_MAX  7

static const CString g_strCapDeviceChRate[CAPDEVICE_CHREATE_MAX] = 
{
	_T("1 / 1"),
	_T("1000 / 1"),
	_T("100 / 1"),
	_T("0x01CF / 1"),
	_T("0x01CF / 5"),
	_T("0x2D41 / 10"),
	_T("0x2D41 / 57.735")
};

static const float g_fCapDeviceChRate[CAPDEVICE_CHREATE_MAX] = 
{
	1.0f, //_T("1 / 1"),
	1000.0f, //_T("1000 / 1"),
	100.0f, //_T("100 / 1");
	463.0f,//_T("0x01CF / 1"),
	92.6f,//_T("0x01CF / 5"),
	1158.5f,//_T("0x2D41 / 10"),
	200.6582f//_T("0x2D41 / 57.735")
};

CString st_GetCapDeviceChRateString(long nIndex)
{
	if (0 <= nIndex && nIndex < CAPDEVICE_CHREATE_MAX)
	{
		return g_strCapDeviceChRate[nIndex];
	}
	else
	{
		return g_strCapDeviceChRate[0];
	}
}


float st_GetCapDeviceChRate(long nIndex)
{
	if (0 <= nIndex && nIndex < CAPDEVICE_CHREATE_MAX)
	{
		return g_fCapDeviceChRate[nIndex];
	}
	else
	{
		return g_fCapDeviceChRate[0];
	}
}

long st_GetCapDeviceChRateIndex(const CString &strID)
{
	long nIndex = 0;
	
	for (nIndex=0; nIndex<CAPDEVICE_CHREATE_MAX; nIndex++)
	{
		if (strID == g_strCapDeviceChRate[nIndex])
		{
			return nIndex;
		}
	}

	return 0;
}

#ifndef _PSX_IDE_QT_
void st_AddCapDeviceChRateTo(CComboBox *pComboBox)
{
	long nIndex = 0;
	pComboBox->ResetContent();

	for (nIndex=0; nIndex<CAPDEVICE_CHREATE_MAX; nIndex++)
	{
		long nItem = pComboBox->AddString(g_strCapDeviceChRate[nIndex]);
		pComboBox->SetItemData(nItem, nIndex);
	}
}
#endif

float st_GetCapDeviceSVRate(CExBaseObject* pSmvCh,BOOL bDCFT3)
{
	if (pSmvCh == NULL)
	{
		return 1;
	}

	CIecCfgDataSmvChBase* pDataSmvCh = (CIecCfgDataSmvChBase*)pSmvCh;
	CIecCfgDatasSMV* pDatasSMV = (CIecCfgDatasSMV*)pDataSmvCh->GetAncestor(CFGCLASSID_CIECCFGDATASSMV);

	if (pDatasSMV == NULL)
	{
		pDatasSMV = (CIecCfgDatasSMV*)pDataSmvCh->GetAncestor(CFGCLASSID_CIECCFGDATASSMVINPUT);
	}

//	CIecCfgDatasSMV* pDatasSMV = pIecCfgDatasMngr->GetSmvMngr();
	CIecCfgSmvRates* pSmvRates = pDatasSMV->GetIecCfgSmvRates();

	if (pSmvRates == NULL)
	{
		return 1;
	}

	CIecCfgSmvRate* pSmvRate = (CIecCfgSmvRate*)pSmvRates->FindByID(st_GetSmvRateID(pDataSmvCh->m_strAppChID,bDCFT3));

	if (pSmvRate == NULL)
	{
		return 1;
	}

	if (pDataSmvCh->GetClassID() == CFGCLASSID_CIECCFG6044COMMONCHIN)
	{
		if (pSmvRate->m_strID.Find("U") != -1)//zhouhj 2024.2.27 对于电压通道,一次值需要乘以1000,其单位为kV
		{
			return (pSmvRate->m_fPrimValue*1000/pSmvRate->m_nCodeValue);
		} 
		else
		{
			if (pDataSmvCh->m_strChType == iecfg_SmvChDataType_Val_CurrMeasure)
			{
				return (pSmvRate->m_fPrimValue/pSmvRate->m_nMeasCurrCodeValue);
			}
			else
			{
				return (pSmvRate->m_fPrimValue/pSmvRate->m_nCodeValue);
			}
		}
	} 

	return pSmvRate->m_fRate;
}

#include "../SttRcdComtradeFileWrite.h"

void CCapDeviceSmvCh::WriteRcdFile_Comtrade(double *pdLong, long nCount, const CString &strComtradeFile)
{
	stt_WriteRcdFile_Comtrade(pdLong, nCount, strComtradeFile, m_strID, m_fChRate);
}

