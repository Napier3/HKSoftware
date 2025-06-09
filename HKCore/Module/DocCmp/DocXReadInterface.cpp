//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DocXReadInterface.cpp  CDocXReadInterface


#include "stdafx.h"
#include "DocXReadInterface.h"

CDocXReadInterface::CDocXReadInterface()
{
	m_pProgress = NULL;
}

CDocXReadInterface::~CDocXReadInterface()
{
}

void CDocXReadInterface::MessageTickCount(const CString &strTitle)
{
	CString strMsg;
	strMsg.Format(_T("%s : %d"), strTitle.GetString(), m_oTickCount.GetTickCountLong(TRUE));
	if (m_pProgress != NULL)
	{
		m_pProgress->ShowMsg(strMsg);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, strMsg);
	}
}

