// ComtradeBinaryData.cpp: implementation of the CComtradeBinaryData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComtradeBinaryData.h"
#include "ComtradeMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComtradeBinaryData::CComtradeBinaryData()
{
	m_nNormalState = 0;
	m_nDataIndex   = 0;
}

CComtradeBinaryData::~CComtradeBinaryData()
{
	
}

void CComtradeBinaryData::SaveChanInfo(CString& strInfor)
{
#ifdef _PSX_IDE_QT_
	strInfor = QString("%1,%2,%3,%4,%5")
		.arg(m_nChannelIndex)
		.arg(m_strName)
		.arg(m_strPhaseID)
		.arg(m_strCcbm)
		.arg(m_nNormalState);
#else
    //Edit by lipenghui 2020-04-15
	strInfor.Format(_T("%d,%s,%s,%s,%d"),
        m_nChannelIndex,m_strName.GetString(),m_strPhaseID.GetString(),m_strCcbm.GetString(),m_nNormalState);
#endif
}

//��Comtrade�ļ�ʱ���,nOffSet��ʾ�����ģ��ͨ���ĸ���,ģ��Ϳ���ͨ����ͨ������,��ģ��󿪹�
void CComtradeBinaryData::GetChanInfor(CString* pstrParse,long nOffSet)
{
	long nChannelIndex = CString_To_long(pstrParse[0]);

	m_nChannelIndex		= nChannelIndex - nOffSet;
	
	m_strName			= pstrParse[1];
	m_strPhaseID		= pstrParse[2];
	m_strCcbm			= pstrParse[3];
	m_nNormalState      = CString_To_long(pstrParse[4]);
	m_nDataIndex        = m_nChannelIndex % 16 - 1;
	m_strID = m_strName;
}

long CComtradeBinaryData::XmlReadOwn( CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys )
{
	CComtradeDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CComtradeFileXmlRWKeys *pXmlKeys = (CComtradeFileXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strYKey, oNode, m_nNormalState);
//	xml_GetCDATA(oNode, m_pnAttachBuffer);
	return 0;
}

long CComtradeBinaryData::XmlWriteOwn( CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys )
{
	CComtradeDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CComtradeFileXmlRWKeys *pXmlKeys = (CComtradeFileXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strYKey, oElement, m_nNormalState);
 //	xml_SetCDATA(oXMLDoc, oElement, (char *)m_pnAttachBuffer, m_nTotalPt);
	return 0;
}

CExBaseObject* CComtradeBinaryData::CreateNewChild( const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys )
{
	CExBaseObject *pNew  = NULL;
	CComtradeFileXmlRWKeys *pXmlKeys = (CComtradeFileXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CComtradeBinaryData::CreateNewChild( long nClassID/*, BOOL &bAddToTail*/ )
{
	CExBaseObject *pNew  = NULL;

	return pNew;
}

BOOL CComtradeBinaryData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CComtradeDataBase::CopyOwn(pDest);
	CComtradeBinaryData *p = (CComtradeBinaryData*)pDest;
	p->m_nNormalState = m_nNormalState;
	p->m_nDataIndex = m_nDataIndex;
	return TRUE;
}

BOOL CComtradeBinaryData::InsertBySampleRate(float* pdSrcSamRate,long* pnSrcDataPoints,long nSrcSamAmount,double dDstSmpRate,CComtradeDataBase *pDstData,const double &dDstBeginOffsetTime)
{
	if (pDstData->GetClassID() != CMTRDCLASSID_BINARY)
	{
		return FALSE;
	}

	CComtradeBinaryData *pDstBinaryData = (CComtradeBinaryData*)pDstData;
	CopyOwn(pDstData);

	BOOL bIsFirstSmpRate = TRUE;// ��ֹ��һ��������,��������Ϊ0�����
	long nSrcBeginPoint = 0;
	long nSrcEndPoint = 0;
	long nDstBeginPoint = 0;
	double dSrcBeginPointTime = 0;
	double dSrcGap = 0;
	double dDstGap = 1/dDstSmpRate;

	for (int nRateIndex = 0;nRateIndex<nSrcSamAmount;nRateIndex++)
	{
		if (pnSrcDataPoints[nRateIndex]<=0)//������������,��������Ϊ0�Ĳ�����
		{
			continue;
		}

		dSrcGap = 1/pdSrcSamRate[nRateIndex];

		if (bIsFirstSmpRate)
		{
			nSrcBeginPoint = 0;
			nSrcEndPoint = (pnSrcDataPoints[nRateIndex]-1);//��һ����Ч������,ȥ����һ����
			bIsFirstSmpRate = FALSE;
		} 
		else
		{
			nSrcEndPoint += pnSrcDataPoints[nRateIndex];
		}

		InsertBySampleRate(nSrcBeginPoint,nSrcEndPoint ,nDstBeginPoint,dSrcBeginPointTime,dSrcGap,dDstGap,pDstData,dDstBeginOffsetTime);
		nSrcBeginPoint = nSrcEndPoint;
	}

	long nSrcPointNum = GetMemBuffer_UShortNum(),nDstPointNum = pDstBinaryData->GetMemBuffer_UShortNum();

	if ((nSrcPointNum>0)&&(nDstPointNum>0))
	{
		pDstBinaryData->m_pnAttachBuffer[nDstPointNum-1] = m_pnAttachBuffer[nSrcPointNum-1];//�����һ���������⴦��
	}
	
	return TRUE;
}

BOOL CComtradeBinaryData::InsertBySampleRate(const long &nSrcBeginPoint,const long &nSrcEndPoint ,long &nDstBeginPoint,
												 double &dSrcBeginPointTime,const double &dSrcGap,const double &dDstGap,CComtradeDataBase *pDstData,const double &dDstBeginOffsetTime)
{
	if (pDstData->GetClassID() != CMTRDCLASSID_BINARY)
	{
		return FALSE;
	}

	CComtradeBinaryData *pDstBinaryData = (CComtradeBinaryData*)pDstData;
	long nCurSrcPointIndex = 0;
	long nDstCurPointIndex = nDstBeginPoint;//��ֵ�ز�������λ��
	double dSrcBeginTime = 0;
	double dSrcEndTime = 0;
	double dDstCurTime = 0;
	dDstCurTime = nDstCurPointIndex*dDstGap + dDstBeginOffsetTime;

	for (nCurSrcPointIndex = nSrcBeginPoint;nCurSrcPointIndex<nSrcEndPoint;nCurSrcPointIndex++)
	{
		dSrcBeginTime = dSrcBeginPointTime + (nCurSrcPointIndex-nSrcBeginPoint)*dSrcGap;
		dSrcEndTime = dSrcBeginTime + dSrcGap;

		while(dDstCurTime<dSrcEndTime)
		{
			pDstBinaryData->m_pnAttachBuffer[nDstCurPointIndex] = m_pnAttachBuffer[nCurSrcPointIndex];
			nDstCurPointIndex++;
			dDstCurTime += dDstGap;
		}
	}

	nDstBeginPoint = nDstCurPointIndex;
	dSrcBeginPointTime += (nSrcEndPoint-nSrcBeginPoint)*dSrcGap;
	return TRUE;
}

void CComtradeBinaryData::InsertNormalCyclePoints(long nInsertPoints,long nDataFileType)
{
	CMemBuffer_UShort* pShortBuffer = GetMemBuffer_UShort();

	if(pShortBuffer == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰͨ�����ݻ���Ϊ��,�޷����в�ֵ����"));
		return;
	}

	unsigned short* pBuffer = pShortBuffer->GetBuffer();
	long nBufferSize = pShortBuffer->GetBufferLength();

	if((nBufferSize <= 0)||(pBuffer == NULL))
	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰͨ�����ݻ��泤��Ϊ0,�޷����в�ֵ����"));
		return;
	}

	long nAfterBufferSize = nBufferSize + nInsertPoints;

	// ����unsigned short���͵�����
	unsigned short* pOldBuffer = new unsigned short[nBufferSize];
	memset(pOldBuffer, 0, nBufferSize * sizeof(unsigned short));
	memcpy(pOldBuffer, pBuffer, nBufferSize * sizeof(unsigned short));

	AllocBuffer(nAfterBufferSize);
	pBuffer = pShortBuffer->GetBuffer();

	//���²�������
	//memcpy(pBuffer, pOldBuffer, nInsertPoints * sizeof(unsigned short));
	memcpy(pBuffer + nInsertPoints, pOldBuffer, nBufferSize * sizeof(unsigned short));
	delete[] pOldBuffer;

	m_nTotalPoints = nAfterBufferSize; // ���µ���

	for (int nIndex = 0;nIndex<nInsertPoints;nIndex++)//��������������ǰ��Ҫ��ӵĵ�ֵ
	{
		m_pnAttachBuffer[nIndex] = m_pnAttachBuffer[nInsertPoints];
	}
}

long CComtradeBinaryData::GetChIndex()
{
	long nChIndex = 0;

	CRcdComtradeFile *pComtradeFile = (CRcdComtradeFile*)GetParent();

	if (pComtradeFile == NULL)
	{
		return nChIndex;
	}

	long nFindIndex = 0;
	CComtradeBinaryData *pComtradeBinaryData = NULL;
	CExBaseList* pBinarys = pComtradeFile->GetBinarys();
	POS pos = pBinarys->GetHeadPosition();

	while(pos)
	{
		pComtradeBinaryData = (CComtradeBinaryData*)pBinarys->GetNext(pos);
		nFindIndex++;

		if (pComtradeBinaryData == this)
		{
			nChIndex = nFindIndex;
			break;
		}
	}

	return nChIndex;
}
