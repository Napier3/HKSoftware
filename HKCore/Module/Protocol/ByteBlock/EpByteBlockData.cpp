#include "StdAfx.h"
#include "EpByteBlockData.h"


CEpByteBlockData::CEpByteBlockData(long nItemIndex)
{
	m_nItemIndex  = nItemIndex;
	m_strName = _T("����");
	m_strID = _T("data");
}

CEpByteBlockData::~CEpByteBlockData(void)
{
	
}
