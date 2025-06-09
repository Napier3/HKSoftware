#pragma once

#include "EpByteBlock.h"


class CEpByteBlockQOS : public CEpByteBlock
{
public:
	CEpByteBlockQOS(BYTE byteQOS, BOOL bAddDetail);
	virtual ~CEpByteBlockQOS(void);

//属性
public:
	BYTE m_byteSE;     //执行/选择
	BYTE m_byteQL;     //备用

protected:
	
public:
	//基本方法
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};

};
