#include "StdAfx.h"
#include "ComtradeDealTool.h"

CComtradeDealTool::CComtradeDealTool(void)
{
}

CComtradeDealTool::~CComtradeDealTool(void)
{
}

CComtradeAnalogData* CComtradeDealTool::AddAnalogChannelI0(CRcdComtradeFile *pComtradeFile,long nChannelIndexIa,long nChannelIndexIb,long nChannelIndexIc)
{
	CExBaseList* pAnalogList = pComtradeFile->GetAnalogs();
	CComtradeAnalogData *pIa = (CComtradeAnalogData*)pAnalogList->GetAt(nChannelIndexIa);
	CComtradeAnalogData *pIb = (CComtradeAnalogData*)pAnalogList->GetAt(nChannelIndexIb);
	CComtradeAnalogData *pIc = (CComtradeAnalogData*)pAnalogList->GetAt(nChannelIndexIc);

	if ((pIa == NULL)||(pIb == NULL)||(pIc == NULL))
	{
		return NULL;
	}

	CComtradeAnalogData *pI0 = new CComtradeAnalogData();
	pIa->CopyOwn(pI0);
	pI0->AllocBuffer(pComtradeFile->m_nTotalPoints);
	pComtradeFile->AddNewChild(pI0);
	pComtradeFile->m_nAllChs++;
	pComtradeFile->m_nAnalogs++;
	pAnalogList->AddTail(pI0);
	pI0->m_nChannelIndex = pAnalogList->GetCount();
	pI0->m_strPhaseID = _T("N");
	pI0->m_strName = _T("New_I0");
	SetZeroValue(pI0,pIa,pIb,pIc,pComtradeFile->m_nTotalPoints);
	return pI0;
}

CComtradeAnalogData* CComtradeDealTool::AddAnalogChannelU0(CRcdComtradeFile *pComtradeFile,long nChannelIndexUa,long nChannelIndexUb,long nChannelIndexUc)
{
	CExBaseList* pAnalogList = pComtradeFile->GetAnalogs();
	CComtradeAnalogData *pUa = (CComtradeAnalogData*)pAnalogList->GetAt(nChannelIndexUa);
	CComtradeAnalogData *pUb = (CComtradeAnalogData*)pAnalogList->GetAt(nChannelIndexUb);
	CComtradeAnalogData *pUc = (CComtradeAnalogData*)pAnalogList->GetAt(nChannelIndexUc);

	if ((pUa == NULL)||(pUb == NULL)||(pUc == NULL))
	{
		return NULL;
	}

	CComtradeAnalogData *pU0 = new CComtradeAnalogData();
	pUa->CopyOwn(pU0);
	pU0->AllocBuffer(pComtradeFile->m_nTotalPoints);
	pComtradeFile->AddNewChild(pU0);
	pComtradeFile->m_nAllChs++;
	pComtradeFile->m_nAnalogs++;
	pAnalogList->AddTail(pU0);
	pU0->m_nChannelIndex = pAnalogList->GetCount();
	pU0->m_strPhaseID = _T("N");
	pU0->m_strName = _T("New_U0");
	SetZeroValue(pU0,pUa,pUb,pUc,pComtradeFile->m_nTotalPoints);
	return pU0;
}

void CComtradeDealTool::SetZeroValue(CComtradeAnalogData *pPhaseN,CComtradeAnalogData *pPhaseA,CComtradeAnalogData *pPhaseB,CComtradeAnalogData *pPhaseC ,long nTotalPoints)
{
	double dCurValue = 0;
	long nLongValue = 0;
	double dTmpValue = 0;
	short* pCurr = (short*)pPhaseN->m_pnAttachBuffer;

	for (int nPointIndex = 0;nPointIndex<nTotalPoints;nPointIndex++)
	{
		dCurValue = pPhaseA->GetUShortPointValueDouble(nPointIndex) + pPhaseB->GetUShortPointValueDouble(nPointIndex) + pPhaseC->GetUShortPointValueDouble(nPointIndex);
		dTmpValue = (dCurValue - pPhaseN->m_dZeroValue)/pPhaseN->m_dCoefValue;

		if ((dTmpValue>32767)||(dTmpValue<-32767))
		{
			pPhaseN->AdjustCoefValue(nPointIndex,pPhaseN->m_dCoefValue*2);//如果当前值超出范围，将系数乘以2，并调整之前的值
			dTmpValue = dTmpValue/2;
			pCurr[nPointIndex] = dTmpValue;
		}
		else
		{
			pCurr[nPointIndex] = dTmpValue;
		}

		if (dTmpValue - pCurr[nPointIndex] > 0.5)  //zhouhj 20201216 考虑精度开放
		{
			pCurr[nPointIndex] += 1;
		}
		else if (dTmpValue - pCurr[nPointIndex] < -0.5)
		{
			pCurr[nPointIndex] -= 1;
		}
	}
}

void CComtradeDealTool::SetZeroValue_Short(CComtradeAnalogData *pPhaseN,CComtradeAnalogData *pPhaseA,CComtradeAnalogData *pPhaseB,CComtradeAnalogData *pPhaseC ,long nTotalPoints)
{
	double dCurValue = 0;
	long nLongValue = 0;
	double dTmpValue = 0;
	short* pCurr = (short*)pPhaseN->m_pnAttachBuffer;

	for (int nPointIndex = 0;nPointIndex<nTotalPoints;nPointIndex++)
	{
		dCurValue = pPhaseA->GetUShortPointValueDouble(nPointIndex) + pPhaseB->GetUShortPointValueDouble(nPointIndex) + pPhaseC->GetUShortPointValueDouble(nPointIndex);
		dTmpValue = (dCurValue - pPhaseN->m_dZeroValue)/pPhaseN->m_dCoefValue;

		if ((dTmpValue>32767)||(dTmpValue<-32767))
		{
			pPhaseN->AdjustCoefValue(nPointIndex,pPhaseN->m_dCoefValue*2);//如果当前值超出范围，将系数乘以2，并调整之前的值
			dTmpValue = dTmpValue/2;
			pCurr[nPointIndex] = dTmpValue;
		}
		else
		{
			pCurr[nPointIndex] = dTmpValue;
		}

		if (dTmpValue - pCurr[nPointIndex] > 0.5)  //zhouhj 20201216 考虑精度开放
		{
			pCurr[nPointIndex] += 1;
		}
		else if (dTmpValue - pCurr[nPointIndex] < -0.5)
		{
			pCurr[nPointIndex] -= 1;
		}
	}
}

void CComtradeDealTool::SetZeroValue_Long(CComtradeAnalogData *pPhaseN,CComtradeAnalogData *pPhaseA,CComtradeAnalogData *pPhaseB,CComtradeAnalogData *pPhaseC ,long nTotalPoints)
{
	double dCurValue = 0;
	long nLongValue = 0;
	double dTmpValue = 0;
	long* pCurr = (long*)pPhaseN->m_pnAttachBuffer;

	for (int nPointIndex = 0;nPointIndex<nTotalPoints;nPointIndex++)
	{
		dCurValue = pPhaseA->GetUShortPointValueDouble(nPointIndex) + pPhaseB->GetUShortPointValueDouble(nPointIndex) + pPhaseC->GetUShortPointValueDouble(nPointIndex);
		dTmpValue = (dCurValue - pPhaseN->m_dZeroValue)/pPhaseN->m_dCoefValue;

		if ((dTmpValue>32767)||(dTmpValue<-32767))
		{
			pPhaseN->AdjustCoefValue(nPointIndex,pPhaseN->m_dCoefValue*2);//如果当前值超出范围，将系数乘以2，并调整之前的值
			dTmpValue = dTmpValue/2;
			pCurr[nPointIndex] = dTmpValue;
		}
		else
		{
			pCurr[nPointIndex] = dTmpValue;
		}

		if (dTmpValue - pCurr[nPointIndex] > 0.5)  //zhouhj 20201216 考虑精度开放
		{
			pCurr[nPointIndex] += 1;
		}
		else if (dTmpValue - pCurr[nPointIndex] < -0.5)
		{
			pCurr[nPointIndex] -= 1;
		}
	}
}

void CComtradeDealTool::UpdateAllChannelIndexs(CRcdComtradeFile *pComtradeFile)
{
	long nChannelIndex = 1;
	CExBaseList* pAnalogList = pComtradeFile->GetAnalogs();
	CExBaseList* pBinaryList = pComtradeFile->GetBinarys();
	pComtradeFile->m_nAnalogs = pAnalogList->GetCount();
	pComtradeFile->m_nBinarys = pBinaryList->GetCount();
	pComtradeFile->m_nAllChs = pComtradeFile->m_nAnalogs + pComtradeFile->m_nBinarys;
	POS pos = pAnalogList->GetHeadPosition();
	CComtradeDataBase *pCurDataBase = NULL;

	while(pos)
	{
		pCurDataBase = (CComtradeDataBase*)pAnalogList->GetNext(pos);
		pCurDataBase->m_nChannelIndex = nChannelIndex;
		nChannelIndex++;
	}

	pos = pBinaryList->GetHeadPosition();

	while(pos)
	{
		pCurDataBase = (CComtradeDataBase*)pBinaryList->GetNext(pos);
		pCurDataBase->m_nChannelIndex = nChannelIndex;
		nChannelIndex++;
	}
}

void CComtradeDealTool::DeleteComtradeChannel(CRcdComtradeFile *pSrcRcdFile,CComtradeAnalogData *pComtradeChannel)
{
	if ((pSrcRcdFile == NULL)||(pComtradeChannel == NULL))
	{
		return;
	}

	CExBaseList* pAnalogList = pSrcRcdFile->GetAnalogs();
	pAnalogList->Remove(pComtradeChannel);
	pSrcRcdFile->Delete(pComtradeChannel);
	UpdateAllChannelIndexs(pSrcRcdFile);
}