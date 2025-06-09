#pragma once

#include "EpByteBlock.h"


class CEpByteBlockTime : public CEpByteBlock
{
public:
	CEpByteBlockTime(EPTIME64 &tm, BOOL bAddDetail);
	virtual ~CEpByteBlockTime(void);

//属性
public:
	 EPTIME64 m_tm;

protected:
	
public:
	
};
