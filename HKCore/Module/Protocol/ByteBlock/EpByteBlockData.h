#pragma once

#include "EpByteBlock.h"


class CEpByteBlockData :	public CEpByteBlock
{
public:
	CEpByteBlockData(long nItemIndex);
	virtual ~CEpByteBlockData(void);

//属性
public:
	long m_nItemIndex;

protected:
	
public:
	//基本方法
	virtual UINT GetClassID(){return EPCLASSID_DATA;};

};
