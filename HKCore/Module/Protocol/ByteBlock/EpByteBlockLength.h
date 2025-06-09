#pragma once

#include "EpByteBlock.h"


class CEpByteBlockLength : public CEpByteBlock
{
public:
	CEpByteBlockLength(BYTE byteVSQ);
	virtual ~CEpByteBlockLength(void);

//属性
public:
	BYTE m_byteVSQ;     //可变结构限定词
	
	long m_nSQ;         //	SQ=1：表明此帧中的信息体是按信息体地址顺序排列的。SQ=0：表明此帧中的信息体不是按信息体地址顺序排列的
	long m_nCount;      //信息体的个数,小于128

	
protected:
	
public:
	//基本方法
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};

};
