#pragma once

#include "EpByteBlock.h"


class CEpByteBlockFloat : public CEpByteBlock
{
public:
	CEpByteBlockFloat(float Float, BOOL bAddDetail);
	virtual ~CEpByteBlockFloat(void);

//����
public:
	float m_fValue;
	
protected:
	
public:
	//��������
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};

};
