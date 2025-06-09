#include "StdAfx.h"
#include "EpByteBlockControl_101.h"
#include "EpGlobalDefine_101.h"

CEpByteBlockControl_101::CEpByteBlockControl_101(BYTE byteControl)
		: CEpByteBlockControl(byteControl)
{
	Ep101_CalControl(m_byteControl, &m_byteDIR, &m_bytePRM, &m_byteFCB_ACD, &m_byteFCV_DFC, &m_byteFuncCode);
}


CEpByteBlockControl_101::~CEpByteBlockControl_101(void)
{
	
}
