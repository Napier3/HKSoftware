#pragma once

#include "EpByteBlock.h"


class CEpByteBlockQOI : public CEpByteBlock
{
public:
	CEpByteBlockQOI(BYTE byteQOI, BOOL bAddDetail);
	virtual ~CEpByteBlockQOI(void);

//����
public:
	BYTE m_byteQOI;     //

protected:
	
public:
	//��������
	//virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};
	virtual void GetBbInfor(CString &strInfor);

};
