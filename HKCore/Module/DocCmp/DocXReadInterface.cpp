//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

