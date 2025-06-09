//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg92ChQuality.h  CIecCfg92ChQuality

#pragma once

#include "IecCfgDataMngrGlobal.h"



class CIecCfg92ChQuality : public CExBaseObject
{
public:
	CIecCfg92ChQuality();
	virtual ~CIecCfg92ChQuality();


	long  m_nValidity;  //Validity(有效)[bit0-bit1]
	long  m_nOverflow;  //Overflow(溢出)[bit2]
	long  m_nOutOfRange;  //OutOfrange(超值域)[bit3]
	long  m_nBadReference;  //BadReference(坏基准值)[bit4]
	long  m_nOscillation;  //Oscillatory(抖动)[bit5]
	long  m_nFailure;  //Failure(故障)[bit6]
	long  m_nOldData;  //OldData(旧数据)[bit7]
	long  m_nInconsistent;  //Inconsistent(不一致)[bit8]
	long  m_nInaccurate;  //Inaccurate(不精确)[bit9]
	long  m_nSource;  //Source(源)[bit10]
	long  m_nTest;  //Test(测试)[bit11]
	long  m_nOPB; //Opb(操作员闭锁)[bit12]

	DWORD *m_pdwRefQuality;
//私有成员变量访问方法
public:
	DWORD GetQuality();
	void SetQuality(DWORD dwQuality);

	DWORD GetQualityRef();
	void SetQualityRef(DWORD *pdwQuality);
};

