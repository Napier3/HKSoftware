#pragma once

#include "EpByteBlock.h"


class CEpByteBlockCOT : public CEpByteBlock
{
public:
	CEpByteBlockCOT(BYTE byteCOT);
	virtual ~CEpByteBlockCOT(void);

//����
public:
	BYTE m_byteCOT; 
	BYTE m_byteAsdu;

protected:
	
public:
	//��������
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};

};
