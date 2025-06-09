#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#include "../../Record/Comtrade/ComtradeMngr.h"
#include "../../GpsPcTime/GpsPcTime.h"
#include "../../SmartCap/61850Cap/CapGlobalDef.h"
#include "../../API/FileApi.h"

extern long g_nXSmartCapDebugMode;
extern long g_n_write_SyncDelt_Rcd_file_Mode;
extern CString g_strSttRcdFilePath;

//波形文件处理
void stt_WriteRcdFile_Comtrade(double *pdLong, long nCount, const CString &strComtradeFile, const CString &strID, float fChRate);

class CSttRcdComtradeFileWrite
{
public:
	CSttRcdComtradeFileWrite();
	virtual ~CSttRcdComtradeFileWrite();

	void InitComtradeFileWrite(long nChCount, long nDataPoints);
	void SetChannelData(long nChIndex, double *pdLong, const CString &strID, float fChRate);

	void WritComtradeFile(const CString &strComtradeFile);

private:
	CRcdComtradeFile m_oRcdComtradeFile;

};

