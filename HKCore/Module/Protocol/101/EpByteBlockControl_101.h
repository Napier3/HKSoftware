#pragma once

#include "..\ByteBlock\EpByteBlockControl.h"


class CEpByteBlockControl_101 : public CEpByteBlockControl
{
public:
	CEpByteBlockControl_101(BYTE byteControl);
	virtual ~CEpByteBlockControl_101(void);

//����
public:
	BYTE m_byteControl;

	BYTE m_byteDIR;
	BYTE m_bytePRM;
	BYTE m_byteFCB_ACD;
	BYTE m_byteFCV_DFC;
	BYTE m_byteFuncCode;

protected:
	
public:
	//��������
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};

};
