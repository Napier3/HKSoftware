#pragma once

#include "EpByteBlock.h"


class CEpByteBlockQOS : public CEpByteBlock
{
public:
	CEpByteBlockQOS(BYTE byteQOS, BOOL bAddDetail);
	virtual ~CEpByteBlockQOS(void);

//����
public:
	BYTE m_byteSE;     //ִ��/ѡ��
	BYTE m_byteQL;     //����

protected:
	
public:
	//��������
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};

};
