#pragma once

#include "EpByteBlock.h"


class CEpByteBlockType : public CEpByteBlock
{
public:
	CEpByteBlockType(BYTE byte);
	virtual ~CEpByteBlockType(void);

//属性
public:
	BYTE m_byteType; 

protected:
	
public:
	//基本方法
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};

};
