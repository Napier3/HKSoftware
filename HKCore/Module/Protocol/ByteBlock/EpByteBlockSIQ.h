#pragma once

#include "EpByteBlock.h"


class CEpByteBlockSIQ : public CEpByteBlock
{
public:
	CEpByteBlockSIQ(BYTE byteSIQ);
	virtual ~CEpByteBlockSIQ(void);

//����
public:
	BYTE m_byteSIQ;
	
	long m_nSPI; 
	long m_nBL;
	long m_nSB;
	long m_nNT;
	long m_nIV;


	
protected:
	
public:
	//��������
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};

};
