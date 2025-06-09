//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttParas.cpp  CSttParas


#include "stdafx.h"
#include "SttComtradeGroup.h"
#include "math.h"
#include "ComtradePlayConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#if 0
CSttComtradeGroup::CSttComtradeGroup()
{
	//初始化属性
	m_pReplayBuf = NULL;
}

CSttComtradeGroup::~CSttComtradeGroup()
{
	if (m_pReplayBuf != NULL)
	{
		delete m_pReplayBuf;
		m_pReplayBuf = NULL;
	}
}

CBaseObject* CSttComtradeGroup::Clone()
{
	CSttComtradeGroup *p = new CSttComtradeGroup();
	Copy(p);
	return p;
}

CBaseObject* CSttComtradeGroup::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttComtradeGroup *p = new CSttComtradeGroup();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttComtradeGroup::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CSttComtradeGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
     CSttCmtrdCfgDefineXmlRWKeys *pXmlKeys = (CSttCmtrdCfgDefineXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCSttMapGroupKey)
	{
		return new CSttComtradeGroup();
	}
	else
	{
		return CDataGroup::CreateNewChild(strClassID, bAddToTail, pXmlKeys);
	}
}

CExBaseObject* CSttComtradeGroup::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
    if (nClassID == MNGRCLASSID_CSTTMAPGROUP)
    {
        return new CSttComtradeGroup();
    }
    else
    {
        return CDataGroup::CreateNewChild(nClassID);
    }
}

double CSttComtradeGroup::CalcChannelMaxValue()
{
	if (m_pReplayBuf == NULL)
	{
		return 0;
	}

	float* pCurr = m_pReplayBuf->GetBuffer_float();
	float* pEnd = pCurr + m_pReplayBuf->GetDataLength();

	double fMax = 0;
	double fVal = 0;

	while (pCurr < pEnd)
	{
		fVal = fabs(*pCurr);

		if (fMax < fVal)
		{
			fMax = fVal;
		}

		pCurr++;
	}

	m_fMaxAbs = fMax;
	return m_fMaxAbs;
}

BOOL CSttComtradeGroup::IsChannelSelected()
{
	return (m_strValue == _T("1"));
}

void CSttComtradeGroup::InitChReplayBuf(long nMaxPoints)
{
	if (m_pReplayBuf == NULL)
	{
		m_pReplayBuf = new CComplexMemBuffer_Float;
	}

	m_pReplayBuf->SetBufferLength(nMaxPoints);
}

void CSttComtradeGroup::ResetChReplayBuf()
{
	if (m_pReplayBuf != NULL)
	{
		m_pReplayBuf->Init();
	}
}

BOOL CSttComtradeGroup::IsModuleSelected()
{
	POS pos = GetHeadPosition();
	CSttComtradeGroup *pCh = NULL;

	while(pos != NULL)
	{
		pCh = (CSttComtradeGroup *)GetNext(pos);

		if (pCh->IsChannelSelected())
		{
			return TRUE;
		}
	}

	return FALSE;
}

double CSttComtradeGroup::CalcChMaxValueByIndex(long nChIndex)
{
	CSttComtradeGroup *pCh = NULL;
	double fMax = 0;
	double fVal = 0;

	if (nChIndex < 0)
	{//所有通道重新计算
		POS pos = GetHeadPosition();

		while(pos != NULL)
		{
			pCh = (CSttComtradeGroup *)GetNext(pos);

			if (pCh->IsChannelSelected())
			{
				fVal = pCh->CalcChannelMaxValue();
				if (fVal > fMax)
				{
					fMax = fVal;
				}
			}
		}
	}
	else
	{
		pCh = (CSttComtradeGroup *)GetAt(nChIndex);
		if (pCh->IsChannelSelected())
		{
			fMax = pCh->CalcChannelMaxValue();
		}
	}

	return fMax;
}

double CSttComtradeGroup::GetModuleMaxValue()
{
	CSttComtradeGroup *pCh = NULL;
	double fMax = 0;
	POS pos = GetHeadPosition();

	while(pos != NULL)
	{
		pCh = (CSttComtradeGroup *)GetNext(pos);

		if (pCh->IsChannelSelected())
		{
			if (pCh->m_fMaxAbs > fMax)
			{
				fMax = pCh->m_fMaxAbs;
			}
		}
	}

	return fMax;
}

void CSttComtradeGroup::ScalingModuleMaxValue(float fK)
{
	CSttComtradeGroup *pCh = NULL;
	POS pos = GetHeadPosition();

	while(pos != NULL)
	{
		pCh = (CSttComtradeGroup *)GetNext(pos);

		if (pCh->IsChannelSelected())
		{
			pCh->m_fMaxAbs *= fK;
		}
	}
}

void CSttComtradeGroup::InitModuleReplayBuf(long nMaxPoints)
{
	CSttComtradeGroup *pCh = NULL;
	POS pos = GetHeadPosition();

	while(pos != NULL)
	{
		pCh = (CSttComtradeGroup *)GetNext(pos);
		pCh->InitChReplayBuf(nMaxPoints);
	}
}

void CSttComtradeGroup::ResetModuleReplayBuf()
{
	CSttComtradeGroup *pCh = NULL;
	POS pos = GetHeadPosition();

	while(pos != NULL)
	{
		pCh = (CSttComtradeGroup *)GetNext(pos);
		pCh->ResetChReplayBuf();
	}
}

long CSttComtradeGroup::GetMaxPoints()
{
	if (m_pReplayBuf == NULL)
	{
		return 0;
	}

	return m_pReplayBuf->GetBufferLength();
}

long CSttComtradeGroup::GetValue_DataA()
{
	long nValue = 0;
	Stt_GetDataAttr(this,COMTRADE_CONFIG_KEY_A, nValue);
	return nValue;
}

long CSttComtradeGroup::GetValue_DataB()
{
	long nValue = 0;
	Stt_GetDataAttr(this,COMTRADE_CONFIG_KEY_B, nValue);
	return nValue;
}

double CSttComtradeGroup::GetValue_DataK()
{
	CString strValue;
	double dValue = 1;

	if (Stt_GetDataAttr(this,COMTRADE_CONFIG_KEY_K, strValue))
	{
		dValue = CString_To_double(strValue);
	}

	return dValue;
}

/////////////////////////////////////////////

CDvmData* Stt_SetDataAttr(CDataGroup *pGroup,const CString &strID, const CString &strValue)
{
	ASSERT(pGroup != NULL);

	CDvmData *pData = (CDvmData *)pGroup->FindByID(strID);

	if (pData != NULL)
	{
		pData->m_strValue = strValue;
	}
	else
	{
		pData = pGroup->AddNewData(_T(""),strID,_T(""),strValue);
	}

	return pData;
}

CDvmData* Stt_SetDataAttr(CDataGroup *pGroup,const CString &strID, long nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	return Stt_SetDataAttr(pGroup,strID,strValue);
}

CDvmData* Stt_SetDataAttr(CDataGroup *pGroup,const CString &strID, double fValue, long nDecimal)
{
	CString strValue;
	if (nDecimal <= 0)
	{
		strValue.Format(_T("%d"), (int)fValue);
	}
	else
	{
// 		CString strFormat;
// 		strFormat.Format(_T("%%.%df"),nDecimal);
// 		strValue.Format(strFormat,fValue);
		strValue.Format(_T("%.3f"),fValue);
	}

	return Stt_SetDataAttr(pGroup,strID,strValue);
}

BOOL Stt_GetDataAttr(CDataGroup *pGroup,const CString &strID, CString &strValue)
{
	ASSERT(pGroup != NULL);

	CDvmData *pData = (CDvmData *)pGroup->FindByID(strID);

	if (pData != NULL)
	{
		strValue = pData->m_strValue;
		return TRUE;
	}
	else
	{
		strValue = _T("");
		return FALSE;
	}
}

BOOL Stt_GetDataAttr(CDataGroup *pGroup,const CString &strID, long &nValue)
{
	CString strValue = _T("");
	nValue = 0;
	BOOL bRet = Stt_GetDataAttr(pGroup,strID,strValue);

	if (bRet)
	{
		nValue = CString_To_long(strValue);
	}

	return bRet;
}

BOOL Stt_GetDataAttr(CDataGroup *pGroup,const CString &strID, double &fValue,double fDefaultVal)
{
	CString strValue = _T("");
	fValue = fDefaultVal;
	BOOL bRet = Stt_GetDataAttr(pGroup,strID,strValue);

	if (bRet)
	{
		fValue = CString_To_double(strValue);
	}

	return bRet;
}

BOOL Stt_GetDataAttr(CDataGroup *pGroup,const CString &strID, float &fValue,float fDefaultVal)
{
	double fVal = fDefaultVal;
	BOOL bRet = Stt_GetDataAttr(pGroup,strID,fVal);
	fValue = (float)fVal;

	return bRet;
}
#endif
