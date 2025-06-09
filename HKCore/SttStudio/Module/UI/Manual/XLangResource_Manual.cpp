#include "stdafx.h"
#include "XLangResource_Manual.h"

const CString QXLangResource_Manual::g_strXLangRs_Test = _T("Lang_ManualTest");

QXLangResource_Manual::QXLangResource_Manual()
{
    m_pXLangRsExe = &m_oXLangRs_Test;
    m_oXLangRs_Test.m_strID = g_strXLangRs_Test;
    m_oXLangRs_Test.m_strName = g_strXLangRs_Test;
}

QXLangResource_Manual::~QXLangResource_Manual()
{
    m_oXLangRs_Test.RemoveAll();
}


CXLangItem* QXLangResource_Manual::rs_AddString(const CString &strID, CString *pstrString)
{
    CXLangItem *p = CXLanguage::AddString(strID, pstrString);

    m_oXLangRs_Test.AddTail(p);

    return p;
}


void QXLangResource_Manual::InitLangRsByFile()
{
    CXLanguageResourceBase::InitLangRsByFile();

    InitLangRsByFileEx(&m_oXLangRs_Test, g_strXLangRs_Test);
}


void QXLangResource_Manual::RegisterLanguageResource()
{
    CXLanguageResourceBase::RegisterLanguageResource();

    rs_AddString(g_sLangID_Manual_IV, &g_sLangTxt_Manual_IV);
    rs_AddString(g_sLangID_Manual_OtherParam, &g_sLangTxt_Manual_OtherParam);
    rs_AddString(g_sLangID_Manual_Changing, &g_sLangTxt_Manual_Changing);
    rs_AddString(g_sLangID_Manual_InitVal, &g_sLangTxt_Manual_InitVal);
    rs_AddString(g_sLangID_Manual_ChangeType, &g_sLangTxt_Manual_ChangeType);
    rs_AddString(g_sLangID_Manual_Channel, &g_sLangTxt_Manual_Channel);
    rs_AddString(g_sLangID_Manual_FinishVal, &g_sLangTxt_Manual_FinishVal);
    rs_AddString(g_sLangID_Manual_Step, &g_sLangTxt_Manual_Step);
    rs_AddString(g_sLangID_Manual_Timer, &g_sLangTxt_Manual_Timer);
    rs_AddString(g_sLangID_Manual_Old, &g_sLangTxt_Manual_Old);
    rs_AddString(g_sLangID_Manual_Auto, &g_sLangTxt_Manual_Auto);
    rs_AddString(g_sLangID_Manual_Direct, &g_sLangTxt_Manual_Direct);
    rs_AddString(g_sLangID_Manual_Delayed, &g_sLangTxt_Manual_Delayed);
    rs_AddString(g_sLangID_Manual_OutSetting, &g_sLangTxt_Manual_OutSetting);
    rs_AddString(g_sLangID_Manual_Out1, &g_sLangTxt_Manual_Out1);
    rs_AddString(g_sLangID_Manual_Out2, &g_sLangTxt_Manual_Out2);
    rs_AddString(g_sLangID_Manual_Out3, &g_sLangTxt_Manual_Out3);
    rs_AddString(g_sLangID_Manual_Out4, &g_sLangTxt_Manual_Out4);
    rs_AddString(g_sLangID_Manual_Out5, &g_sLangTxt_Manual_Out5);
    rs_AddString(g_sLangID_Manual_Out6, &g_sLangTxt_Manual_Out6);
    rs_AddString(g_sLangID_Manual_Out7, &g_sLangTxt_Manual_Out7);
    rs_AddString(g_sLangID_Manual_Out8, &g_sLangTxt_Manual_Out8);
    rs_AddString(g_sLangID_Manual_Lock, &g_sLangTxt_Manual_Lock);
    rs_AddString(g_sLangID_Manual_Action, &g_sLangTxt_Manual_Action);
    rs_AddString(g_sLangID_Manual_ActionTime, &g_sLangTxt_Manual_ActionTime);
    rs_AddString(g_sLangID_Manual_ReturnVal, &g_sLangTxt_Manual_ReturnVal);
    rs_AddString(g_sLangID_Manual_ReturnTime, &g_sLangTxt_Manual_ReturnTime);
}

CString QXLangResource_Manual::g_sLangID_Manual_IV                 = _T("Manual_IV");
CString QXLangResource_Manual::g_sLangTxt_Manual_IV                 = _T("电流电压");
CString QXLangResource_Manual::g_sLangID_Manual_OtherParam                 = _T("Manual_OtherParam");
CString QXLangResource_Manual::g_sLangTxt_Manual_OtherParam                 = _T("其它参数设置");
CString QXLangResource_Manual::g_sLangID_Manual_Changing                 = _T("Manual_Changing");
CString QXLangResource_Manual::g_sLangTxt_Manual_Changing                 = _T("递变");
CString QXLangResource_Manual::g_sLangID_Manual_InitVal                 = _T("Manual_InitVal");
CString QXLangResource_Manual::g_sLangTxt_Manual_InitVal                 = _T("始值(V):");
CString QXLangResource_Manual::g_sLangID_Manual_ChangeType                 = _T("Manual_ChangeType");
CString QXLangResource_Manual::g_sLangTxt_Manual_ChangeType                 = _T("变化方式:");
CString QXLangResource_Manual::g_sLangID_Manual_Channel                 = _T("Manual_Channel");
CString QXLangResource_Manual::g_sLangTxt_Manual_Channel                 = _T("通道选择:");
CString QXLangResource_Manual::g_sLangID_Manual_FinishVal                 = _T("Manual_FinishVal");
CString QXLangResource_Manual::g_sLangTxt_Manual_FinishVal                 = _T("终值(V):");
CString QXLangResource_Manual::g_sLangID_Manual_Step                 = _T("Manual_Step");
CString QXLangResource_Manual::g_sLangTxt_Manual_Step                 = _T("步长(V):");
CString QXLangResource_Manual::g_sLangID_Manual_Timer                 = _T("Manual_Timer");
CString QXLangResource_Manual::g_sLangTxt_Manual_Timer                 = _T("时间(s):");
CString QXLangResource_Manual::g_sLangID_Manual_Old                 = _T("Manual_Old");
CString QXLangResource_Manual::g_sLangTxt_Manual_Old                 = _T("老化");
CString QXLangResource_Manual::g_sLangID_Manual_Auto                 = _T("Manual_Auto");
CString QXLangResource_Manual::g_sLangTxt_Manual_Auto                 = _T("自动");
CString QXLangResource_Manual::g_sLangID_Manual_Direct                 = _T("Manual_Direct");
CString QXLangResource_Manual::g_sLangTxt_Manual_Direct                 = _T("直流");
CString QXLangResource_Manual::g_sLangID_Manual_Delayed                 = _T("Manual_Delayed");
CString QXLangResource_Manual::g_sLangTxt_Manual_Delayed                 = _T("触发后延时(s):");
CString QXLangResource_Manual::g_sLangID_Manual_OutSetting                 = _T("Manual_OutSetting");
CString QXLangResource_Manual::g_sLangTxt_Manual_OutSetting                 = _T("开出设置");
CString QXLangResource_Manual::g_sLangID_Manual_Out1                 = _T("Manual_Out1");
CString QXLangResource_Manual::g_sLangTxt_Manual_Out1                 = _T("开出1");
CString QXLangResource_Manual::g_sLangID_Manual_Out2                 = _T("Manual_Out2");
CString QXLangResource_Manual::g_sLangTxt_Manual_Out2                 = _T("开出2");
CString QXLangResource_Manual::g_sLangID_Manual_Out3                 = _T("Manual_Out3");
CString QXLangResource_Manual::g_sLangTxt_Manual_Out3                 = _T("开出3");
CString QXLangResource_Manual::g_sLangID_Manual_Out4                 = _T("Manual_Out4");
CString QXLangResource_Manual::g_sLangTxt_Manual_Out4                 = _T("开出4");
CString QXLangResource_Manual::g_sLangID_Manual_Out5                 = _T("Manual_Out5");
CString QXLangResource_Manual::g_sLangTxt_Manual_Out5                 = _T("开出5");
CString QXLangResource_Manual::g_sLangID_Manual_Out6                 = _T("Manual_Out6");
CString QXLangResource_Manual::g_sLangTxt_Manual_Out6                 = _T("开出6");
CString QXLangResource_Manual::g_sLangID_Manual_Out7                 = _T("Manual_Out7");
CString QXLangResource_Manual::g_sLangTxt_Manual_Out7                 = _T("开出7");
CString QXLangResource_Manual::g_sLangID_Manual_Out8                 = _T("Manual_Out8");
CString QXLangResource_Manual::g_sLangTxt_Manual_Out8                 = _T("开出8");
CString QXLangResource_Manual::g_sLangID_Manual_Lock                 = _T("Manual_Lock");
CString QXLangResource_Manual::g_sLangTxt_Manual_Lock                 = _T("锁");
CString QXLangResource_Manual::g_sLangID_Manual_Action                 = _T("Manual_Action");
CString QXLangResource_Manual::g_sLangTxt_Manual_Action                 = _T("动作值(V):");
CString QXLangResource_Manual::g_sLangID_Manual_ActionTime                 = _T("Manual_ActionTime");
CString QXLangResource_Manual::g_sLangTxt_Manual_ActionTime                 = _T("动作时间(s):");
CString QXLangResource_Manual::g_sLangID_Manual_ReturnVal                 = _T("Manual_ReturnVal");
CString QXLangResource_Manual::g_sLangTxt_Manual_ReturnVal                 = _T("返回值(V):");
CString QXLangResource_Manual::g_sLangID_Manual_ReturnTime                 = _T("Manual_ReturnTime");
CString QXLangResource_Manual::g_sLangTxt_Manual_ReturnTime                 = _T("返回时间(s):");
