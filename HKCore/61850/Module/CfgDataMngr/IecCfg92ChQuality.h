//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfg92ChQuality.h  CIecCfg92ChQuality

#pragma once

#include "IecCfgDataMngrGlobal.h"



class CIecCfg92ChQuality : public CExBaseObject
{
public:
	CIecCfg92ChQuality();
	virtual ~CIecCfg92ChQuality();


	long  m_nValidity;  //Validity(��Ч)[bit0-bit1]
	long  m_nOverflow;  //Overflow(���)[bit2]
	long  m_nOutOfRange;  //OutOfrange(��ֵ��)[bit3]
	long  m_nBadReference;  //BadReference(����׼ֵ)[bit4]
	long  m_nOscillation;  //Oscillatory(����)[bit5]
	long  m_nFailure;  //Failure(����)[bit6]
	long  m_nOldData;  //OldData(������)[bit7]
	long  m_nInconsistent;  //Inconsistent(��һ��)[bit8]
	long  m_nInaccurate;  //Inaccurate(����ȷ)[bit9]
	long  m_nSource;  //Source(Դ)[bit10]
	long  m_nTest;  //Test(����)[bit11]
	long  m_nOPB; //Opb(����Ա����)[bit12]

	DWORD *m_pdwRefQuality;
//˽�г�Ա�������ʷ���
public:
	DWORD GetQuality();
	void SetQuality(DWORD dwQuality);

	DWORD GetQualityRef();
	void SetQualityRef(DWORD *pdwQuality);
};

