#pragma once

#include "EpByteBlocks.h"


class CEpByteBlockDataSet :	public CEpByteBlocks
{
public:
	CEpByteBlockDataSet();
	virtual ~CEpByteBlockDataSet(void);

//����
public:
	DWORD m_dwDataType;
	CEpByteBlockData *m_pCurrData;

protected:
	
public:
	//��������
	virtual UINT GetClassID(){return EPCLASSID_DATASET;};
	CEpByteBlockData* AddNewData(long nIndex);
};
