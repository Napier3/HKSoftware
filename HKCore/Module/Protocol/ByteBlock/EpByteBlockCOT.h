#pragma once

#include "EpByteBlock.h"


class CEpByteBlockCOT : public CEpByteBlock
{
public:
	CEpByteBlockCOT(BYTE byteCOT);
	virtual ~CEpByteBlockCOT(void);

//属性
public:
	BYTE m_byteCOT; 
	BYTE m_byteAsdu;

protected:
	
public:
	//基本方法
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};

};
