//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CCapFrameDbFileQueryTool.cpp  CCapFrameDbFileQueryTool

#include "stdafx.h"
#include "CapFrameDbFileQueryTool.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CCapFrameDbFileQueryTool::CCapFrameDbFileQueryTool()
{
	m_nBeginPos = 0;
	m_nEndPos = 0;

	m_pCapFrameDbArea = NULL;
	m_pCapFrameIndexDbArea = NULL;

	m_nQueryCapFrameMaxPage = 0;
	m_nQueryCapFrameCurrPage = 0;
	m_strQueryInfo = _T("");

	m_bShowGrid=FALSE;
}

CCapFrameDbFileQueryTool::~CCapFrameDbFileQueryTool()
{
	m_oSttRcdMemBufferMngr.DeleteAll();
	m_oSttFrameMemBufferMngr.DeleteAll();
	delete m_pCapFrameIndexDbArea;
}

CCapFrameIndexDbArea* CCapFrameDbFileQueryTool::CreateCapFrameIndexDbArea()
{
	if (m_pCapFrameIndexDbArea != NULL)
	{
		return m_pCapFrameIndexDbArea;
	}

	m_pCapFrameIndexDbArea = CCapDbSttIndexSmDbFile::CreateCapFrameIndexDbArea();
	
	return m_pCapFrameIndexDbArea;
}

void CCapFrameDbFileQueryTool::SetBeginEndPos(__int64 nBeginPos, __int64 nEndPos, BOOL bShowGrid)
{
	m_nBeginPos = nBeginPos;
	m_nEndPos = nEndPos;

	m_bShowGrid = bShowGrid;

	m_nQueryCapFrameMaxPage = (m_nEndPos - m_nBeginPos)/PERPAGE_MAX_LEN + 1;
	m_nQueryCapFrameCurrPage = 1;

	if(m_pCapFrameDbArea == NULL)
	{
		m_pCapFrameDbArea = CCapFrameDbFile::CreateCapFrameArea();
	}

	m_oSttFrameMemBufferMngr.InitXSmMemBufferMngr();
	m_oSttRcdMemBufferMngr.AttachPkgTransDest(&m_oSttFrameMemBufferMngr);
}

void CCapFrameDbFileQueryTool::GetPageBeginEndPos(long nPage, __int64 &nBeginPos, __int64 &nEndPos)
{
	nBeginPos = m_nBeginPos + (nPage - 1)*PERPAGE_MAX_LEN;
	
	if(nBeginPos + PERPAGE_MAX_LEN < m_nEndPos)
	{
		nEndPos = nBeginPos + PERPAGE_MAX_LEN;
	}
	else
	{
		nEndPos = m_nEndPos;
	}
}

__int64 CCapFrameDbFileQueryTool::GetPageLength(long nPage)
{
	__int64 nBeginPos = 0;
	__int64 nEndPos = 0;

	GetPageBeginEndPos(nPage, nBeginPos, nEndPos);

	return nEndPos-nBeginPos;
}

void CCapFrameDbFileQueryTool::QueryPageCapFrame(long nPage)
{
	__int64 nBeginPos = 0;
	__int64 nEndPos = 0;

	GetPageBeginEndPos(nPage, nBeginPos, nEndPos); 

	__int64 dwLength = nEndPos-nBeginPos;
	__int64 dwTempLength = dwLength;
	dwTempLength = dwTempLength/1024;

	m_strQueryInfo.Format(_T("检索报文范围：[%lld, %lld]，大小：%lldKB"), nBeginPos, nEndPos, dwTempLength);

	m_pCapFrameDbArea->LocateAreaPos(nBeginPos);
	BYTE *pQueryResult = (BYTE *)m_pCapFrameDbArea->Read(nBeginPos, dwLength);

	m_oSttRcdMemBufferMngr.AddFrameBuffer(pQueryResult, dwLength);
	m_oSttRcdMemBufferMngr.ParseSttRcdBuffer(); //分帧
	m_oSttRcdMemBufferMngr.ParseSttFrameBufferMngr(); //解析帧
}

void CCapFrameDbFileQueryTool::ExportAllPagePcap(const CString &strFile)
{
	CFile_Pcap oFile_Pcap;

	FILE *pfile = oFile_Pcap.PcapOpenFile(strFile);

	if (pfile == NULL)
	{
		return;
	}

	m_oSttFrameMemBufferMngr.DeleteAll(TRUE);
	m_oSttRcdMemBufferMngr.ResetMngr();
	m_oSttRcdMemBufferMngr.ClearLeftBuffer();

	for(long nPage = 1; nPage <= m_nQueryCapFrameMaxPage; nPage++)
	{
		QueryPageCapFrame(nPage);
		oFile_Pcap.PcapWriteFile(&m_oSttFrameMemBufferMngr);
	}

	oFile_Pcap.PcapCloseFile();

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("导出PACP文件%s成功"), strFile);
}

BOOL CCapFrameDbFileQueryTool::PopSaveAsPcapFileDlg(CString &strExportFile)
{
	return PopupSaveAsFileDialog(NULL, strExportFile, _T("导出pcap文件(*.pcap)|*.pcap||"), _T("导出pcap保存文件"));
}

void CCapFrameDbFileQueryTool::ExportAllPagePcap()
{
	CString strExportFile = _T("");

	if (!PopSaveAsPcapFileDlg(strExportFile))
	{
		return;
	}

	ExportAllPagePcap(strExportFile);
}

void CCapFrameDbFileQueryTool::ExportOnePagePcap(long nPage, const CString &strExportFile)
{
	CFile_Pcap oFile_Pcap;

	FILE *pfile = oFile_Pcap.PcapOpenFile(strExportFile);

	if (pfile == NULL)
	{
		return;
	}

	m_oSttFrameMemBufferMngr.DeleteAll(TRUE);
	m_oSttRcdMemBufferMngr.ResetMngr();
	m_oSttRcdMemBufferMngr.ClearLeftBuffer();

	QueryPageCapFrame(nPage);
	oFile_Pcap.PcapWriteFile(&m_oSttFrameMemBufferMngr);

	oFile_Pcap.PcapCloseFile();

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("导出PACP文件%s成功"), strExportFile);
}

void CCapFrameDbFileQueryTool::ExportOnePagePcap(long nPage)
{
	CString strExportFile = _T("");

	if (!PopSaveAsPcapFileDlg(strExportFile))
	{
		return;
	}

	ExportOnePagePcap(nPage, strExportFile);
}

void CCapFrameDbFileQueryTool::CapoptrExportAT02D()
{
	BYTE *pAT02DHead = NULL;

	CString strPath = _T("");

	BOOL bRet = PopupSaveAsFileDialog(NULL, strPath, _T("导出AT02D文件(*.at02d)|*.at02d||"), _T("导出at02d保存文件"));

	if (!bRet)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("at02d保存文件创建失败"));
		return;
	}

	CFile oFile;

	if (!oFile.Open(strPath, CFile::modeCreate | CFile::modeWrite))
	{
		return;
	}

	m_oSttFrameMemBufferMngr.DeleteAll(TRUE);
	m_oSttRcdMemBufferMngr.ResetMngr();
	m_oSttRcdMemBufferMngr.ClearLeftBuffer();

	for(long nPage = 1; nPage<=m_nQueryCapFrameMaxPage; nPage++)
	{
		QueryPageCapFrame(nPage);

		CXSmMemBuffer *pCapBuffer = NULL;

		long nBegin1 = -1, nEnd1 = -1, nBegin2 = -1, nEnd2 = -1;
		m_oSttFrameMemBufferMngr.GetLastParseIndexRange(nBegin1, nEnd1, nBegin2, nEnd2);

		if(nEnd1 < 0)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("导出AT02D文件%s失败"), strPath);
			oFile.Close();
			return;
		}

		for (long nIndex=nBegin1; nIndex <= nEnd1; nIndex++)
		{
			pCapBuffer = m_oSttFrameMemBufferMngr.GetFrameBuffer(nIndex); //检索出的每一帧at02报文数据（不包括报文头）
			oFile.Write(pCapBuffer->GetBuffer(), pCapBuffer->GetWriteLength());
		}

		if(nEnd2 < 0)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("导出AT02D文件%s成功"), strPath);
			oFile.Close();
			return;
		}

		for (long nIndex=nBegin2; nIndex <= nEnd2; nIndex++)
		{
			pCapBuffer = m_oSttFrameMemBufferMngr.GetFrameBuffer(nIndex); //检索出的每一帧at02报文数据（不包括报文头）
			oFile.Write(pCapBuffer->GetBuffer(), pCapBuffer->GetWriteLength());
		}
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("导出AT02D文件%s成功"), strPath);
	oFile.Close();
}

BOOL CCapFrameDbFileQueryTool::CanDoQueryOptr()
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	if(pXSttCap_61850 == NULL)
	{
		return FALSE;
	}

	if(pXSttCap_61850->m_bTestStarted == FALSE)
	{
		return TRUE;
	}

	return !g_theXSmartCapMngr->IsInCapture();
}

BOOL CCapFrameDbFileQueryTool::Query(SYSTEMTIME tmBegin, SYSTEMTIME tmEnd)
{
	CreateCapFrameIndexDbArea();

	if(m_pCapFrameIndexDbArea->m_pSST_PKT_SM_INDEX == NULL)
	{
		m_pCapFrameIndexDbArea->InitSttPktSmIndex();
	}

	if (m_pCapFrameIndexDbArea->m_pSST_PKT_SM_INDEX->n64IndexCount == 0)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("没有索引数据"));
		return FALSE;
	}

	__int64 nBeginPos = 0, nEndPos = 0;
	m_pCapFrameIndexDbArea->QueryCapFrameDbPos(tmBegin, tmEnd, nBeginPos, nEndPos); //获取检索报文起止位置

	if(nEndPos <= nBeginPos)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("所选区间未检索出内容"));
		return FALSE;
	}

	SetBeginEndPos(nBeginPos, nEndPos, FALSE);

	return TRUE;
}

BOOL CCapFrameDbFileQueryTool::ExportPcap(SYSTEMTIME tmBegin, SYSTEMTIME tmEnd)
{
	if (! Query(tmBegin, tmEnd))
	{
		return FALSE;
	}

	ExportAllPagePcap(); //导出所有

	return TRUE;
}


BOOL CCapFrameDbFileQueryTool::ExportPcap(SYSTEMTIME tmBegin, SYSTEMTIME tmEnd, const CString &strExportFile)
{
	if (! Query(tmBegin, tmEnd))
	{
		return FALSE;
	}

	ExportAllPagePcap(strExportFile);

	return TRUE;
}

BOOL CCapFrameDbFileQueryTool::ExportPcap(const CString &strTmBegin, const CString &strTmEnd, const CString &strExportFile)
{
	SYSTEMTIME tmBegin, tmEnd;
	CString_To_SystemTime(strTmBegin, tmBegin);
	CString_To_SystemTime(strTmEnd, tmEnd);

	return ExportPcap(tmBegin, tmEnd, strExportFile);
}

