#pragma once

#include "EpByteBlock.h"


class CEpByteBlockVSQ : public CEpByteBlock
{
public:
	CEpByteBlockVSQ(BYTE byteVSQ);
	virtual ~CEpByteBlockVSQ(void);

//����
public:
	BYTE m_byteVSQ;     //�ɱ�ṹ�޶���
	
	long m_nSQ;         //	SQ=1��������֡�е���Ϣ���ǰ���Ϣ���ַ˳�����еġ�SQ=0��������֡�е���Ϣ�岻�ǰ���Ϣ���ַ˳�����е�
	long m_nCount;      //��Ϣ��ĸ���,С��128

	
protected:
	
public:
	//��������
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};

};
