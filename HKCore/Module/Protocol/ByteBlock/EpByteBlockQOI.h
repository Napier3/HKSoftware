#pragma once

#include "EpByteBlock.h"


class CEpByteBlockQOI : public CEpByteBlock
{
public:
	CEpByteBlockQOI(BYTE byteQOI, BOOL bAddDetail);
	virtual ~CEpByteBlockQOI(void);

//属性
public:
	BYTE m_byteQOI;     //

protected:
	
public:
	//基本方法
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};
	virtual void GetBbInfor(CString &strInfor);

};
