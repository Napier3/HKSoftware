#include "StdAfx.h"
#include "PpGlobalDefine.h"

#include "../XLanguageResourcePp.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/GlobalConfigApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class CPpGlobalDefine
{
public:
	CPpGlobalDefine(void)
	{

	}
	virtual ~CPpGlobalDefine(void)
	{

	}
};


// CLogBase* g_pLogTracePrint = NULL;
CLogBase* g_pLogPkgSendPrint = NULL;
CLogBase* g_pLogPkgReceivePrint = NULL;
CPpPkgSpyInterface* g_pLogPkgSpy = NULL;

long g_bLogBindQueryErrorInfor = FALSE;
long g_bLogPackageInfor = FALSE;
long g_bLogEngineDebugInfor = FALSE;

long PpGetLengthFromCurr(PACKAGEBUFFERPOS &oBuffPos)
{
#ifdef _use_CMemBufferList
	return oBuffPos.nBuffer1EndPos - oBuffPos.nBuffer1BeginPos;
#else
	DWORD nResult = 0;
	int iCurrentPos = oBuffPos.nIndex;
	ASSERT (iCurrentPos >= 0);

	//20170622:将解析放在过程执行线程中，会导致解析函数没有数据解析
	//此时就会出现空缓冲区，忽略空缓冲区
	if (iCurrentPos < 0 || oBuffPos.nBuffer1BeginPos < 0)
	{
		return 0;
	}

	if (iCurrentPos >= oBuffPos.nBuffer1BeginPos && iCurrentPos <= oBuffPos.nBuffer1EndPos)
	{// 游标位于第一段缓冲区
		nResult = oBuffPos.nBuffer1EndPos - iCurrentPos;

		if (oBuffPos.nBuffer2EndPos >= 0)
		{
			nResult += oBuffPos.nBuffer2EndPos - oBuffPos.nBuffer2BeginPos;
		}
	}
	else if (iCurrentPos >= oBuffPos.nBuffer2BeginPos && iCurrentPos <= oBuffPos.nBuffer2EndPos)
	{// 游标位于第二段缓冲区
		nResult = oBuffPos.nBuffer2EndPos - iCurrentPos + 1;
	}

	return nResult;
#endif
}

long PpOffsetCurrBuffer(PACKAGEBUFFERPOS &oBuffPos, long nOffsetLen)
{
	oBuffPos.nIndex += nOffsetLen;

	if (oBuffPos.nIndex > oBuffPos.nBuffer1EndPos)
	{
		if (oBuffPos.nBuffer2EndPos >= 0)
		{
			long nTemp = oBuffPos.nIndex - oBuffPos.nBuffer1EndPos;

			if (nTemp > oBuffPos.nBuffer2EndPos)
			{
				oBuffPos.nIndex = oBuffPos.nBuffer2EndPos;
			}
			else
			{
				oBuffPos.nIndex = nTemp;
			}
		}
		else
		{
			oBuffPos.nIndex = oBuffPos.nBuffer1EndPos;
		}
	}

	return oBuffPos.nIndex;
}

//char g_pszPpLogProtocol[102400];

void PpLogProtocol(char *pszPpLogProtocol, CYCLEMEMBUFFERPOS &oBufPos, CString &strMsg)
{
	long nIndex = 0;
	BYTE *pBuffer = oBufPos.pBuffer + oBufPos.nBuf1BeginPos;
	BYTE *pEnd = oBufPos.pBuffer + oBufPos.nBuf1EndPos;

	char *pBegin = pszPpLogProtocol;
	
	while (pBuffer < pEnd)
	{
		ValueToHex(*pBuffer, *pBegin, *(pBegin+1));
		pBegin += 2;
		*pBegin = ' ';
		pBegin++;
		pBuffer++;
	}

	if (oBufPos.nBuf2EndPos >= 0)
	{
		pBuffer = oBufPos.pBuffer + oBufPos.nBuf2BeginPos;
		pEnd = oBufPos.pBuffer + oBufPos.nBuf2EndPos;

		while (pBuffer < pEnd)
		{
			ValueToHex(*pBuffer, *pBegin, *(pBegin+1));
			pBegin += 2;
			*pBegin = ' ';
			pBegin++;

			pBuffer++;
		}
	}

	*pBegin = 0;

	strMsg += pszPpLogProtocol;
}

void LogReceivePackage(char *pszPpLogProtocol, BYTE* buffer, long len)
{
	return;
}

CString pp_GetDeviceModeModeString(UINT nMode)
{
	switch( nMode)
	{
	case PPTEMPLATE_DEVICEMODE_SINGLE://   1
		return g_sLangTxt_SingDev/*_T("单一设备")*/;

	case PPTEMPLATE_DEVICEMODE_MULTI://    2
		return g_sLangTxt_MultDev/*_T("多设备")*/;

	default:
		return g_sLangTxt_NoDevDataModel/*_T("没有指定设备数据模型模式")*/;

	}
}

CString Pp_GetPoProjectPath()
{
	CString strPath;
	strPath = _P_GetLibraryPath();
	strPath += _T("Project");
	CreateAllDirectories(strPath);
	strPath += _P_FOLDER_PATH_SEPARATOR_;

	return strPath;
}
