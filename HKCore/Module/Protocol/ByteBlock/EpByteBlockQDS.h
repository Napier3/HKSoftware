#pragma once

#include "EpByteBlock.h"


class CEpByteBlockQDS : public CEpByteBlock
{
public:
	CEpByteBlockQDS(BYTE byteQDS, BOOL bAddDetail);
	virtual ~CEpByteBlockQDS(void);

//属性
public:
	BYTE m_byteOV;     //溢出
	BYTE m_byteBL;     //被闭锁
	BYTE m_byteSB;     //被取代
	BYTE m_byteNT;     //当前值
	BYTE m_byteIV;     //有效
	
protected:
	
public:
	//基本方法
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};

};
