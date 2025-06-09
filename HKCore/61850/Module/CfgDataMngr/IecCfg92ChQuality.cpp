//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfg92ChQuality.cpp  CIecCfg92ChQuality


#include "stdafx.h"
#include "IecCfg92ChQuality.h"

CIecCfg92ChQuality::CIecCfg92ChQuality()
{
	//��ʼ������
	m_nValidity = 0;
	m_nOverflow = 0;
	m_nOutOfRange = 0;
	m_nBadReference = 0;
	m_nOscillation = 0;
	m_nFailure = 0;
	m_nOldData = 0;
	m_nInconsistent = 0;
	m_nInaccurate = 0;
	m_nTest = 0;
	m_nOPB = 0;
	m_nSource = 0;

	//��ʼ����Ա����
	m_pdwRefQuality = NULL;
}

CIecCfg92ChQuality::~CIecCfg92ChQuality()
{
}

DWORD CIecCfg92ChQuality::GetQuality()
{
	DWORD dwQuality = 0;

	dwQuality  = m_nValidity      & 0x03;  //Validity(��Ч)[bit0-bit1]
	dwQuality |= (m_nOverflow     & 0x01) << 2;  //Overflow(���)[bit2]
	dwQuality |= (m_nOutOfRange   & 0x01) << 3;  //OutOfrange(��ֵ��)[bit3]
	dwQuality |= (m_nBadReference & 0x01) << 4;  //BadReference(����׼ֵ)[bit4]
	dwQuality |= (m_nOscillation  & 0x01) << 5;  //Oscillatory(����)[bit5]
	dwQuality |= (m_nFailure      & 0x01) << 6;  //Failure(����)[bit6]
	dwQuality |= (m_nOldData      & 0x01) << 7;  //OldData(������)[bit7]
	dwQuality |= (m_nInconsistent & 0x01) << 8;  //Inconsistent(��һ��)[bit8]
	dwQuality |= (m_nInaccurate   & 0x01) << 9;  //Inaccurate(����ȷ)[bit9]
	dwQuality |= (m_nSource       & 0x01) << 10;  //Source(Դ)[bit10]
	dwQuality |= (m_nTest         & 0x01) << 11;  //Test(����)[bit11]
	dwQuality |= (m_nOPB & 0x01) << 12; //Opb(����Ա����)[bit12]

	return dwQuality;
}

void CIecCfg92ChQuality::SetQuality(DWORD dwQuality)
{
	m_nValidity = dwQuality & 0x03;  //Validity(��Ч)[bit0-bit1]
	m_nOverflow = (dwQuality >> 2) & 0x01;  //Overflow(���)[bit2]
	m_nOutOfRange = (dwQuality >> 3) & 0x01;  //OutOfrange(��ֵ��)[bit3]
	m_nBadReference = (dwQuality >> 4) & 0x01;  //BadReference(����׼ֵ)[bit4]
	m_nOscillation = (dwQuality >>  5) & 0x01;  //Oscillatory(����)[bit5]
	m_nFailure = (dwQuality >>  6) & 0x01;  //Failure(����)[bit6]
	m_nOldData = (dwQuality >> 7) & 0x01;  //OldData(������)[bit7]
	m_nInconsistent = (dwQuality >> 8) & 0x01;  //Inconsistent(��һ��)[bit8]
	m_nInaccurate = (dwQuality >> 9) & 0x01;  //Inaccurate(����ȷ)[bit9]
	m_nSource = (dwQuality >> 10) & 0x01;  //Source(Դ)[bit10]
	m_nTest = (dwQuality >> 11) & 0x01;  //Test(����)[bit11]
	m_nOPB = (dwQuality  >> 12 ) & 0x01; //Opb(����Ա����)[bit12]
}

DWORD CIecCfg92ChQuality::GetQualityRef()
{
	DWORD dwQuality = GetQuality();
	ASSERT (m_pdwRefQuality != NULL);
	*m_pdwRefQuality = dwQuality;
	return dwQuality;
}

void CIecCfg92ChQuality::SetQualityRef(DWORD *pdwQuality)
{
	m_pdwRefQuality = pdwQuality;
	ASSERT(m_pdwRefQuality != NULL);
	SetQuality(*m_pdwRefQuality);
}

