#pragma once

#include "EpByteBlock.h"


class CEpByteBlockType : public CEpByteBlock
{
public:
	CEpByteBlockType(BYTE byte);
	virtual ~CEpByteBlockType(void);

//����
public:
	BYTE m_byteType; 

protected:
	
public:
	//��������
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};

};
