// XMemBufferBse.cpp: implementation of the CXMemBufferBse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TExpandMemBufferBase.h"

void Test_TExpandMemBufferBse()
{
	typedef struct _can_state_
	{
		unsigned char chData;
		double dTime;
	}CAN_STATE;

	typedef TExpandMemBufferBase<CAN_STATE> CCanStateBuffer;
	CCanStateBuffer oBffer;
	oBffer.SetBufferLength(100);
	oBffer.AddBufferDataLen(20);
}
