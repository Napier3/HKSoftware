#pragma once

#include "..\ByteBlock\EpByteBlockData.h"


class CEpByteBlockData_101_Yx :	public CEpByteBlockData
{
public:
	CEpByteBlockData_101_Yx(long nItemIndex);
	virtual ~CEpByteBlockData_101_Yx(void);

//����
public:
	long m_nItemIndex;
	long m_nValue;

protected:
	
public:
	//��������
	virtual UINT GetClassID(){return EPCLASSID_DATA;};

};
