#include "StdAfx.h"
#include "GuideBook\GbScript_Engine.h"

#include "GuideBook\GuideBookInterface.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "luabind.hpp"

extern lua_State* g_pGuideBookLua;


// ��Լ֡¼������
void GBS_RecordPackage(const  char* pszPkgID)
{

}

void GBS_UnRecordPackage(const  char* pszPkgID)
{

}

void GBS_GetPackagePcTime(const  char* pszPkgID, const char *pszPcTimeID, long nUseHeadOrTail)
{
	PPCTIME pTm = tm_CreatePcTime();
	SYSTEMTIME tmSys;
	::GetLocalTime(&tmSys);
	tm_InitPcTime(pTm, tmSys);
	CGuideBook *pGuideBook = GBS_GetGuideBook();
	//pGuideBook->m_oScriptDataVariables.AddScriptDataVariable(SDVT_PCTIME, CString(pszPcTimeID), pTm);
}

// ��ȡ��׼Դװ��GPSʱ����PCʱ���֮���Ӧ��ϵ
void GBS_GetGpsPcTimeMap(const char *pszGpsTime, const char *pszPctime)
{
	CGuideBook *pGuideBook = GBS_GetGuideBook();

	PPCTIME pTm = tm_CreatePcTime();
	SYSTEMTIME tmSys;
	::GetLocalTime(&tmSys);
	tm_InitPcTime(pTm, tmSys);
	//pGuideBook->m_oScriptDataVariables.AddScriptDataVariable(SDVT_PCTIME, CString(pszPctime), pTm);

	PGPSTIME pGpsTime = tm_CreateGpsTime();
	tm_InitGpsTime(pGpsTime, tmSys);
	//pGuideBook->m_oScriptDataVariables.AddScriptDataVariable(SDVT_GPSTIME, CString(pszGpsTime), pGpsTime);
}

//��ȡ�����ʼʱ�̵ı�׼Դװ��GPSʱ��
void GBS_GetOutGpsTime(const char *pszGpsTimeID)
{
	CGuideBook *pGuideBook = GBS_GetGuideBook();

	SYSTEMTIME tmSys;
	::GetLocalTime(&tmSys);

	PGPSTIME pGpsTime = tm_CreateGpsTime();
	tm_InitGpsTime(pGpsTime, tmSys);
	//pGuideBook->m_oScriptDataVariables.AddScriptDataVariable(SDVT_GPSTIME, CString(pszGpsTimeID), pGpsTime);
}

long GBS_ReadMacroTestResult()
{
	return 0;
}


//�������ص�����������Ŀ�Ĳ���
void GBS_DownloadMacroTestPara()
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	UINT nClassID = pItem->GetClassID();

	if (nClassID != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("DownMacroPara��������Ŀ\"%s\"��ʹ��"), pItem->m_strName);
		return;
	}

	CGbItemBase *pMacroTest = (CGbItemBase*)pItem->GetParent();

	if (pMacroTest == NULL)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("DownMacroPara��������Ŀ\"%s\"��ʹ��(��Ŀ�ĸ��������)"), pItem->m_strName);
		return;
	}

	nClassID = pMacroTest->GetClassID();

	if (nClassID != GBCLASSID_MACROTEST)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("DownMacroPara��������Ŀ\"%s\"��ʹ��(��Ŀ�ĸ�����ǵ�������Ŀ)"), pItem->m_strName);
		return;
	}


}


//ͨѶ��Լ����ӿں���
// long GBS_PpCreateDevice(const char *pszPpFile, const char *pszDeviceFile, const char *pszDeviceID)
// {
// 	return 0;
// }
// 
// long GBS_PpGetDeviceAttr(const char *pszDeviceID, const char *pszAttrID)
// {
// 	return 0;
// }
// 
// long GBS_PpGetDevieNodeDatas(const char *pszDeviceID, const char *pszNodePath)
// {
// 	return 0;
// }
// 
// long GBS_PpGetDevieNodeData(const char *pszDeviceID, const char *pszNodeDataPath)
// {
// 	return 0;
// }
// 
// long GBS_PpRun(const char *pszDeviceID, const char *pszProcedureID, const char *pszPara)
// {
// 	return 0;
// }
// 
// long GBS_PpReleaseDevice(const char *pszDeviceID)
// {
// 	return 0;
// }
// 
// long GBS_PpReleaseAllDevice()
// {
// 	return 0;
// }
// 
double GBS_PpGetDeviceAttr(const char *pszAttrID)
{
	return 0;
}

long GBS_PpGetDeviceAttrL(const char *pszAttrID)
{
	return 0;
}

extern char g_pLuaReturnString[MAX_PATH];

const char* GBS_PpGetDeviceAttrStr(const char *pszAttrID)
{
	g_pLuaReturnString[0] = '0';
	g_pLuaReturnString[1] = 0;
	return g_pLuaReturnString;
}



void GBS_PpSetDeviceAttrL(const char *pszAttrID, long nValue)
{
	
}

void GBS_PpSetDeviceAttrStr(const char *pszAttrID, const char *pszValue)
{
	
}


long GBS_PpRptGetDevieNodeDatas(const char *pszNodePath)
{
	return 0;
}

long GBS_PpRptGetDeviceAttrs(void)
{
	return 0;
}

double GBS_PpGetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID)
{
	return 0;
}

long GBS_PpSetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID, double dValue)
{
	return 0;
}

long GBS_PpDeleteAllNodeData(const char *pszNodePath)
{
	return 0;
}


long GBS_PpCreateDevice(const char *pszPpFile, const char *pszDeviceFile, const char *pszDeviceID)
{
	return 0;
}

long GBS_PpReleaseDevice(const char *pszDeviceID)
{
	return 0;
}

long GBS_PpReleaseAllDevice()
{
	return 0;
}

long GBS_GetTestIndex()
{
	return 0;
}

