#pragma once

#include "EpByteBlock.h"


class CEpByteBlockControl : public CEpByteBlock
{
public:
	CEpByteBlockControl(BYTE byteControl);
	virtual ~CEpByteBlockControl(void);

//����
public:
	BYTE m_byteControl;
	
protected:
	
public:
	//��������
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};

};
