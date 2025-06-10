#include "stdafx.h"
#include "SttRcdComtradeFileWrite.h"
#include "../../API/GlobalConfigApi.h"

void stt_WriteRcdFile_Comtrade(double *pdLong, long nCount, const CString &strComtradeFile, const CString &strID, float fChRate)
{
	CSttRcdComtradeFileWrite oSttRcdWrite;
	oSttRcdWrite.InitComtradeFileWrite(1, nCount);
	oSttRcdWrite.SetChannelData(0, pdLong, strID, fChRate);
	oSttRcdWrite.WritComtradeFile(strComtradeFile);
}

CSttRcdComtradeFileWrite::CSttRcdComtradeFileWrite()
{

}

CSttRcdComtradeFileWrite::~CSttRcdComtradeFileWrite()
{

}

void CSttRcdComtradeFileWrite::InitComtradeFileWrite(long nChCount, long nDataPoints)
{
	m_oRcdComtradeFile.CreateComtradeFile(nChCount, 0, nDataPoints);
	m_oRcdComtradeFile.SetSamAmount(1);
	m_oRcdComtradeFile.SetSamValue(0, nDataPoints, 4000);
	m_oRcdComtradeFile.m_dFreq = 50;
	m_oRcdComtradeFile.m_nTotalPoints = nDataPoints;

	CGpsPcTime tm, tmEnd;
	CGpsPcTimeSpan ts;
	ts.m_wMilliseconds = nDataPoints / 4;
	tmEnd = tm + ts;
	SYSTEMTIME tmSys;

	tm.GetSysTime(tmSys);
	rcd_InitRtTime(m_oRcdComtradeFile.m_oFirstPointTime, tmSys);
	tmEnd.GetSysTime(tmSys);
	rcd_InitRtTime(m_oRcdComtradeFile.m_oTrigPointTime, tmSys);

	CreateAllDirectories(g_strSttRcdFilePath);
}

void CSttRcdComtradeFileWrite::SetChannelData(long nChIndex, double *pdLong, const CString &strID, float fChRate)
{
	CString strPhaseID, strUnit;
	
	stt_GetVariablePhaseID(strID, strPhaseID, strUnit);

	//相别为“C”：绘图颜色为红色
	m_oRcdComtradeFile.SetAnalogData(nChIndex, strID, _T("C"), strUnit, 0, fChRate, 1000, 1, pdLong);
}

void CSttRcdComtradeFileWrite::WritComtradeFile(const CString &strComtradeFile)
{
	CString strPath ;
	CreateAllDirectories(g_strSttRcdFilePath);

	if (g_strSttRcdFilePath.GetLength() == 0)
	{
		strPath = _P_GetLibraryPath();
	}
	else
	{
		strPath = g_strSttRcdFilePath;
	}

	strPath += strComtradeFile;
	m_oRcdComtradeFile.SaveComtradeFile(strPath);
    //CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s"), strPath);
}
