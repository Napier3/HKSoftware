#include "stdafx.h"
#include "XSmartCapFileWrite.h"
#include "../API/GlobalConfigApi.h"
#include "../API/FileApi.h"
//#include "../../SttStudio/Module/RecordTest/SttRcdSocketBufferZip.h"

CXSmartCapFileWrite* CXSmartCapFileWrite::g_pXSmartCapFileWrite = NULL;
long CXSmartCapFileWrite::g_nXSmartCapFileWriteRef = 0;
long CXSmartCapFileWrite::g_nWriteLength = 0;
long CXSmartCapFileWrite::g_nCanWriteFile = 1;
long CXSmartCapFileWrite::g_nIsFT3PcapFile = 0;
//CString CXSmartCapFileWrite::g_strPcapFilePath = _T("");


CXSmartCapFileWrite::CXSmartCapFileWrite()
{
#ifdef _XSmartCap_use_SttRcdSocket_
	m_bOpenSucc = 0;
#else
	SYSTEMTIME tmSys;
	GetLocalTime(&tmSys);
	m_strWriteFilePath = _P_GetLibraryPath();
	m_strWriteFilePath.AppendFormat(_T("%d_%02d%02d_%02d%02d%02d.at02d"), tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
	m_bOpenSucc = m_oFile.Open(m_strWriteFilePath, CFile::modeCreate | CFile::modeWrite);
#endif
}

CXSmartCapFileWrite::~CXSmartCapFileWrite()
{
	if (m_bOpenSucc)
	{
		m_oFile.Close();
		//SavePcapFile();//dingxy 20240410 不保存直接返回
// #ifdef _PSX_QT_LINUX_  //20220621 已在Close基类处理
// 		system("sync");//20220616 写文件后需要同步  
// #endif
	}
}

void CXSmartCapFileWrite::Create()
{
	g_nXSmartCapFileWriteRef++;

	if (g_nXSmartCapFileWriteRef == 1)
	{
		g_pXSmartCapFileWrite = new CXSmartCapFileWrite();
	}
}


void CXSmartCapFileWrite::Release()
{
	g_nXSmartCapFileWriteRef--;
	g_nWriteLength = 0;//20231017 wxy 每次release时，把g_nWriteLength置为0
	g_nCanWriteFile = 1;

	if (g_nXSmartCapFileWriteRef == 0)
	{
		delete g_pXSmartCapFileWrite;
		g_pXSmartCapFileWrite = NULL;
	}
}

BOOL CXSmartCapFileWrite::HasRelease()
{
	if (g_pXSmartCapFileWrite == NULL)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CXSmartCapFileWrite::WriteBuffer(char *pBuffer, long nLen)
{
	if (g_pXSmartCapFileWrite == NULL)
	{
		return FALSE;
	}

	if (g_nCanWriteFile == 0)
	{
		return FALSE;
	}

	if (! g_pXSmartCapFileWrite->m_bOpenSucc)
	{
		return FALSE;
	}

	g_pXSmartCapFileWrite->m_oFile.Write(pBuffer, nLen);
	g_nWriteLength += nLen;

	return TRUE;
}

long CXSmartCapFileWrite::GetWriteLen()
{
	if (g_pXSmartCapFileWrite == NULL)
	{
		return 0;
	}

	return g_pXSmartCapFileWrite->g_nWriteLength;
}

BOOL CXSmartCapFileWrite::StopWrite(const CString &strPcapFilePath)
{
	if (g_pXSmartCapFileWrite == NULL)
	{
		return FALSE;
	}

	g_nCanWriteFile = 0;
	BOOL bRet = FALSE;

	if (g_pXSmartCapFileWrite->m_bOpenSucc)
	{
		g_pXSmartCapFileWrite->m_oFile.Close();
		bRet = g_pXSmartCapFileWrite->SavePcapFile(strPcapFilePath);
		g_pXSmartCapFileWrite->m_bOpenSucc = FALSE;
// #ifdef _PSX_QT_LINUX_   //20220621 已在Close基类处理
// 		system("sync");//20220616 写文件后需要同步
// #endif
	}

	return bRet;
}

CString CXSmartCapFileWrite::GetWriteFilePath()
{
	if (g_pXSmartCapFileWrite == NULL)
	{
		return _T("");
	}

	return g_pXSmartCapFileWrite->m_strWriteFilePath;
}

BOOL CXSmartCapFileWrite::HasCloseFile()
{
	if (g_pXSmartCapFileWrite == NULL)
	{
		return TRUE;
	}

	return !g_pXSmartCapFileWrite->m_bOpenSucc;
}

BOOL CXSmartCapFileWrite::SavePcapFile(const CString &strPcapFilePath)
{
	if (m_strWriteFilePath.IsEmpty())
	{
		return FALSE;
	}

	if (!IsFileExist(m_strWriteFilePath))
	{
		return FALSE;
	}
	
	CString strNewPcapFilePath;
#ifdef _PSX_QT_LINUX_
	QTextCodec *pOldTextCodec = NULL;
	InitLocalCodec_BeforeReadWrite(strNewPcapFilePath,&pOldTextCodec);//将编码变为utf-8
#endif

	if (strPcapFilePath.IsEmpty())
	{
		strNewPcapFilePath = ChangeFilePostfix(m_strWriteFilePath,_T("pcap"));
	}
	else
	{
		strNewPcapFilePath = strPcapFilePath;
	}

	BOOL bRet = FALSE;

	if (CXSmartCapFileWrite::g_nIsFT3PcapFile)
	{
		bRet = stt_save_pcap_file_ft3(m_strWriteFilePath,strNewPcapFilePath.GetString());
	} 
	else
	{
		bRet = stt_save_pcap_file(m_strWriteFilePath,strNewPcapFilePath.GetString());
	}
#ifdef _PSX_QT_LINUX_
	//dingxy 20240410 转化未utf-8编码后，消息助手中文乱码，恢复编码
	ResetLocalCodec(pOldTextCodec);
#endif

	if (bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("转存Pcap文件(%s)成功."),strPcapFilePath.GetString());
		X_DeleteFile(m_strWriteFilePath);
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("转存Pcap文件(%s)失败."),strPcapFilePath.GetString());
	}

//	g_strPcapFilePath = strPcapFilePath;

#ifdef _PSX_QT_LINUX_   //20220621 已在Close基类处理
	system("sync");//20220616 写文件后需要同步
#endif 	 
	return bRet;
}
// 
// CString CXSmartCapFileWrite::GetPcapFilePath()
// {
// 	return g_strPcapFilePath;
// }

