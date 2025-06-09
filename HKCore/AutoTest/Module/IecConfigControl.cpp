#include "StdAfx.h"
#include "IecConfigControl.h"

CIecConfigControl::CIecConfigControl(void)
{
	m_oTestEngine = NULL;
}

CIecConfigControl::~CIecConfigControl(void)
{
	ExitTest();
}

BOOL CIecConfigControl::CreateTestEngine()
{
	if (m_oTestEngine != NULL)
	{
		return TRUE;

	}

	CString strProgID;
	strProgID = _T("Iec61850Config.TestEngine");
//	CLogPrint::LogFormatString(LOGLEVEL_INFOR,"开始创建调用COM接口(%s).",strProgID);
	m_oTestEngine.CreateDispatch(strProgID);

	if (m_oTestEngine == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,"COM接口(%s)调用失败.",strProgID);
		return FALSE;
	}

	return TRUE;
}

LONG CIecConfigControl::SetWndMsg(ULONG hMainWnd)
{
	if (m_oTestEngine == NULL)
	{
		return 0;
	}

	return m_oTestEngine.SetWndMsg(hMainWnd,WM_IEC_CONFIG_MSG_ID);
}

BOOL CIecConfigControl::OpenTscdFile(const CString &strTsdFilePath)
{
	if (m_oTestEngine == NULL)
	{
		return 0;
	}

	m_oTestEngine.OpenTscdFile(strTsdFilePath);
	return TRUE;
}

BOOL CIecConfigControl::OpenSCDFile(const CString &strScdFilePath)
{
	if (m_oTestEngine == NULL)
	{
		return 0;
	}

	m_oTestEngine.OpenSCDFile(strScdFilePath);
	return TRUE;
}

BOOL CIecConfigControl::NewIecfgFile(const CString &strIEDName)
{
	if (m_oTestEngine == NULL)
	{
		return 0;
	}

	m_oTestEngine.NewIecfgFile(strIEDName,_T(""));
	return TRUE;
}

BOOL CIecConfigControl::GenerNewIecfgFile(const CString &strIEDName,const CString &strSrcIecfgFile)
{
	if (m_oTestEngine == NULL)
	{
		return 0;
	}

	m_oTestEngine.NewIecfgFile(strIEDName,strSrcIecfgFile);
	return TRUE;
}

BOOL CIecConfigControl::EditIecfgFile(const CString &strIecfgPath)
{
	if (m_oTestEngine == NULL)
	{
		return 0;
	}

	m_oTestEngine.EditIecfgFile(strIecfgPath);
	return TRUE;
}

BOOL CIecConfigControl::SaveIecfgFile(const CString &strIecfgPath)
{
	if (m_oTestEngine == NULL)
	{
		return 0;
	}

	m_oTestEngine.SaveIecfgFile(strIecfgPath);
	return TRUE;
}

BOOL CIecConfigControl::SetDestPath(const CString &strIecfgPath)
{
	if (m_oTestEngine == NULL)
	{
		return 0;
	}

	m_oTestEngine.SetDestPath(strIecfgPath);
	return TRUE;
}

ULONG CIecConfigControl::ExitEngine(void)
{
	if (m_oTestEngine == NULL)
	{
		return 0;
	}

	return m_oTestEngine.ExitEngine();
}

void CIecConfigControl::ExitTest()
{
	if (m_oTestEngine != NULL)
	{
		m_oTestEngine.ReleaseDispatch();
		m_oTestEngine = NULL;
	}
}
