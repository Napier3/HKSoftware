#pragma once

#include "EpByteBlock.h"


class CEpByteBlockData :	public CEpByteBlock
{
public:
	CEpByteBlockData(long nItemIndex);
	virtual ~CEpByteBlockData(void);

//����
public:
	long m_nItemIndex;

protected:
	
public:
	//��������
	virtual UINT GetClassID(){return EPCLASSID_DATA;};

};
