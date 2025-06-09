#ifndef XLANGRESOURCEMANUAL_H
#define XLANGRESOURCEMANUAL_H

#include "../../../../Module/XLanguage/XLanguageMngr.h"
#include "../../../../Module/XLanguage/XLanguageResource.h"

class QXLangResource_Manual : public CXLanguageResourceBase
{
public:
	QXLangResource_Manual();
	virtual ~QXLangResource_Manual();

private:
	CXLanguage m_oXLangRs_Test;
	static const CString  g_strXLangRs_Test;

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);
	virtual void InitLangRsByFile();

	virtual void RegisterLanguageResource();

public:
	static CString g_sLangID_Manual_IV;
	static CString g_sLangTxt_Manual_IV;
	static CString g_sLangID_Manual_OtherParam;
	static CString g_sLangTxt_Manual_OtherParam;
	static CString g_sLangID_Manual_Changing;
	static CString g_sLangTxt_Manual_Changing;
	static CString g_sLangID_Manual_InitVal;
	static CString g_sLangTxt_Manual_InitVal;
	static CString g_sLangID_Manual_ChangeType;
	static CString g_sLangTxt_Manual_ChangeType;
	static CString g_sLangID_Manual_Channel;
	static CString g_sLangTxt_Manual_Channel;
	static CString g_sLangID_Manual_FinishVal;
	static CString g_sLangTxt_Manual_FinishVal;
	static CString g_sLangID_Manual_Step;
	static CString g_sLangTxt_Manual_Step;
	static CString g_sLangID_Manual_Timer;
	static CString g_sLangTxt_Manual_Timer;
	static CString g_sLangID_Manual_Old;
	static CString g_sLangTxt_Manual_Old;
	static CString g_sLangID_Manual_Auto;
	static CString g_sLangTxt_Manual_Auto;
	static CString g_sLangID_Manual_Direct;
	static CString g_sLangTxt_Manual_Direct;
	static CString g_sLangID_Manual_Delayed;
	static CString g_sLangTxt_Manual_Delayed;
	static CString g_sLangID_Manual_OutSetting;
	static CString g_sLangTxt_Manual_OutSetting;
	static CString g_sLangID_Manual_Out1;
	static CString g_sLangTxt_Manual_Out1;
	static CString g_sLangID_Manual_Out2;
	static CString g_sLangTxt_Manual_Out2;
	static CString g_sLangID_Manual_Out3;
	static CString g_sLangTxt_Manual_Out3;
	static CString g_sLangID_Manual_Out4;
	static CString g_sLangTxt_Manual_Out4;
	static CString g_sLangID_Manual_Out5;
	static CString g_sLangTxt_Manual_Out5;
	static CString g_sLangID_Manual_Out6;
	static CString g_sLangTxt_Manual_Out6;
	static CString g_sLangID_Manual_Out7;
	static CString g_sLangTxt_Manual_Out7;
	static CString g_sLangID_Manual_Out8;
	static CString g_sLangTxt_Manual_Out8;
	static CString g_sLangID_Manual_Lock;
	static CString g_sLangTxt_Manual_Lock;
	static CString g_sLangID_Manual_Action;
	static CString g_sLangTxt_Manual_Action;
	static CString g_sLangID_Manual_ActionTime;
	static CString g_sLangTxt_Manual_ActionTime;
	static CString g_sLangID_Manual_ReturnVal;
	static CString g_sLangTxt_Manual_ReturnVal;
	static CString g_sLangID_Manual_ReturnTime;
	static CString g_sLangTxt_Manual_ReturnTime;
};

#endif // XLANGRESOURCEMANUAL_H
