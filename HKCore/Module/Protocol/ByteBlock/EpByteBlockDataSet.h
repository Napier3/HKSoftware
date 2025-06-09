#pragma once

#include "EpByteBlocks.h"


class CEpByteBlockDataSet :	public CEpByteBlocks
{
public:
	CEpByteBlockDataSet();
	virtual ~CEpByteBlockDataSet(void);

//属性
public:
	DWORD m_dwDataType;
	CEpByteBlockData *m_pCurrData;

protected:
	
public:
	//基本方法
	virtual UINT GetClassID(){return EPCLASSID_DATASET;};
	CEpByteBlockData* AddNewData(long nIndex);
};
