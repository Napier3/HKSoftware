#pragma once

#include "EpByteBlockData.h"

class CEpByteBlocks :	public CExBaseList
{
public:
	CEpByteBlocks(void);
	virtual ~CEpByteBlocks(void);

public:
	//��������
	virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCKS;};

};
