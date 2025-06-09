#pragma once

#include "EpByteBlock.h"


class CEpByteBlockSIQ : public CEpByteBlock
{
public:
	CEpByteBlockSIQ(BYTE byteSIQ);
	virtual ~CEpByteBlockSIQ(void);

//属性
public:
	BYTE m_byteSIQ;
	
	long m_nSPI; 
	long m_nBL;
	long m_nSB;
	long m_nNT;
	long m_nIV;


	
protected:
	
public:
	//基本方法
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};

};
