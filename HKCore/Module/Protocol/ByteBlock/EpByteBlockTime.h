#pragma once

#include "EpByteBlock.h"


class CEpByteBlockTime : public CEpByteBlock
{
public:
	CEpByteBlockTime(EPTIME64 &tm, BOOL bAddDetail);
	virtual ~CEpByteBlockTime(void);

//����
public:
	 EPTIME64 m_tm;

protected:
	
public:
	
};
