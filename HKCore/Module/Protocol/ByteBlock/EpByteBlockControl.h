#pragma once

#include "EpByteBlock.h"


class CEpByteBlockControl : public CEpByteBlock
{
public:
	CEpByteBlockControl(BYTE byteControl);
	virtual ~CEpByteBlockControl(void);

//属性
public:
	BYTE m_byteControl;
	
protected:
	
public:
	//基本方法
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};

};
