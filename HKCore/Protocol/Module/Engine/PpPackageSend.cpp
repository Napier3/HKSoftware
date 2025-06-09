#include "StdAfx.h"
#include "PpPackageSend.h"
#include "PpTemplate.h"
#include "PpEngineThreadBase.h"
#include "../XLanguageResourcePp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpPackageSend::CPpPackageSend(CExBaseObject *pPpProcedureRun, CCmmChannel *pChannel, long nBufferLen)
{
	m_pEngineThread = NULL;
	m_pPpProcedureRun = pPpProcedureRun;
	m_pChannel = pChannel;
	ASSERT (nBufferLen > 0 && nBufferLen < 65535);  //������Ч�Լ���
	//m_oBuffer.SetBufferLength(nBufferLen);
	m_oBuffer.SetBufferLength(32768);
	m_pPackageDetail = new CPpPackageDetail(pChannel);
	m_bHasSended = FALSE;
	m_bIsLocked = FALSE;
	m_nSendtimes = 0;
	m_pPackageDetail->SetParent(this);
}

CPpPackageSend::~CPpPackageSend(void)
{
	if (m_pPackageDetail != NULL)
	{
		delete m_pPackageDetail;
		m_pPackageDetail = NULL;
	}

	m_oBuffer.FreeBuffer();
}

void CPpPackageSend::GetPackageBufferPos(PACKAGEBUFFERPOS &oPkgBufPos)
{
	oPkgBufPos.pBuffer = m_oBuffer.GetBuffer();
	oPkgBufPos.nIndex = 0;
	oPkgBufPos.nBuffer1BeginPos = 0;
	oPkgBufPos.nBuffer1EndPos = m_oBuffer.GetBufferLength()-1;
	oPkgBufPos.nBuffer2BeginPos = -1;
	oPkgBufPos.nBuffer2EndPos = -1;
}


void CPpPackageSend::Send()
{
	if (m_pChannel != NULL)
	{
		m_pChannel->Send(this);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                , g_sLangTxt_FrameSend.GetString()
                , m_pPackageDetail->m_strID.GetString());
	}
}

long g_nPpPackageSendIndex = 0;
void CPpPackageSend::LogAndRecordProtocol()
{
	CYCLEMEMBUFFERPOS oCycleBufPos;
	m_oBuffer.GetBufferPos(0, -1, oCycleBufPos);
	oCycleBufPos.nBuf1EndPos = m_oBuffer.GetDataLength();

	//2020-03-26
	CExBaseObject *pPpEngineData = (CExBaseObject *)GetAncestor(PPCLASSID_PPENGINEDATA);
	CXPpPkgLogTool::AddPpPkgLog2(oCycleBufPos, FALSE, pPpEngineData, g_nPpPackageSendIndex);
	g_nPpPackageSendIndex++;

    return;
}

CPpPackageDetail* CPpPackageSend::DettachPpPackage()
{
	CPpPackageDetail *p = m_pPackageDetail;
	m_pPackageDetail = NULL;
	return p;
}

void CPpPackageSend::SetSendState(BOOL bSend)
{
	m_bHasSended = bSend;
	m_pPackageDetail->m_nTimeout = 10000;
	m_pPackageDetail->SetBeginTime();
}


BOOL CPpPackageSend::IsChCmmModeBroadCast()
{
	return (m_strChCmmMode == NET_CMM_MODE_BROADCAST);
}

BOOL CPpPackageSend::IsChCmmModeMultiCast()
{
	return (m_strChCmmMode == NET_CMM_MODE_MULTICAST);
}

BOOL CPpPackageSend::IsChCmmModeToPoint()
{
	if (m_strChCmmMode == NET_CMM_MODE_TOPOINT)
	{
		return TRUE;
	}

	if ( (!IsChCmmModeBroadCast()) && (!IsChCmmModeMultiCast()) )
	{
		return TRUE;
	}

	return FALSE;
}

