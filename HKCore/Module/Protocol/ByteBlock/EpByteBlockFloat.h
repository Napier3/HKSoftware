#pragma once

#include "EpByteBlock.h"


class CEpByteBlockFloat : public CEpByteBlock
{
public:
	CEpByteBlockFloat(float Float, BOOL bAddDetail);
	virtual ~CEpByteBlockFloat(void);

//属性
public:
	float m_fValue;
	
protected:
	
public:
	//基本方法
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};

};
