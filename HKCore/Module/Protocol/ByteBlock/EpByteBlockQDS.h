#pragma once

#include "EpByteBlock.h"


class CEpByteBlockQDS : public CEpByteBlock
{
public:
	CEpByteBlockQDS(BYTE byteQDS, BOOL bAddDetail);
	virtual ~CEpByteBlockQDS(void);

//����
public:
	BYTE m_byteOV;     //���
	BYTE m_byteBL;     //������
	BYTE m_byteSB;     //��ȡ��
	BYTE m_byteNT;     //��ǰֵ
	BYTE m_byteIV;     //��Ч
	
protected:
	
public:
	//��������
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};

};
