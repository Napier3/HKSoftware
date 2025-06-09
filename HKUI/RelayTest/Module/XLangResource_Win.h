#ifndef _XLangResource_Win_h__
#define _XLangResource_Win_h__

#include "../../Module/XLanguage/XLanguageMngr.h"
#include "../../AutoTest/Module/XLanguageResourceAts.h"
#include "XLangResource_Native.h"

class CXLangResource_Win : public CXLangResource_Native
{
public:
	CXLangResource_Win();
	virtual ~CXLangResource_Win();

private:
	CXLanguage m_oXLangRs_Test;
	static const CString  g_strXLangRs_Test;

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);
	virtual void InitLangRsByFile();

	virtual void RegisterLanguageResource();
	virtual void InitLangTxt();
public:
	
};

extern CString g_sLangID_Win_SysConfig;
extern CString g_sLangTxt_Win_SysConfig;
extern CString g_sLangID_Win_Iec61850Config;
extern CString g_sLangTxt_Win_Iec61850Config;
extern CString g_sLangID_Win_PpxmlPath;
extern CString g_sLangTxt_Win_PpxmlPath;
extern CString g_sLangID_Win_PpxmlFilter;
extern CString g_sLangTxt_Win_PpxmlFilter;
extern CString g_sLangID_Win_CharTabTitle;
extern CString g_sLangTxt_Win_CharTabTitle;
extern CString g_sLangID_Win_CharEditTabTitle;
extern CString g_sLangTxt_Win_CharEditTabTitle;

extern CString g_sLangID_Win_IntelligentTestSystem;
extern CString g_sLangTxt_Win_IntelligentTestSystem;

extern CString g_sLangID_Win_VectorDiagram;
extern CString g_sLangTxt_Win_VectorDiagram;

extern CString g_sLangID_Win_StatusDiagram;
extern CString g_sLangTxt_Win_StatusDiagram;

extern CString g_sLangID_Win_PowerDiagram;
extern CString g_sLangTxt_Win_PowerDiagram;

extern CString g_sLangID_Win_WaveformDiagram;
extern CString g_sLangTxt_Win_WaveformDiagram;

extern CString g_sLangID_Win_InfoDiagram;
extern CString g_sLangTxt_Win_InfoDiagram;

extern CString g_sLangID_Win_ZTView;
extern CString g_sLangTxt_Win_ZTView;

extern CString g_sLangID_Win_LoadingTestInterface;
extern CString g_sLangTxt_Win_LoadingTestInterface;

extern CString g_sLangID_Win_SystemDiagram;
extern CString g_sLangTxt_Win_SystemDiagram;

extern CString g_sLangID_Win_WiringDiagram;
extern CString g_sLangTxt_Win_WiringDiagram;

#endif // _XLangResource_Native_h__
