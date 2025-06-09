#ifndef _XLangResource_Native_h__
#define _XLangResource_Native_h__

#include "../../Module/XLanguage/XLanguageMngr.h"
#include "../../AutoTest/Module/XLanguageResourceAts.h"

class CXLangResource_Native : public CXLanguageResourceAtsBase
{
public:
	CXLangResource_Native();
	virtual ~CXLangResource_Native();

private:
	CXLanguage m_oXLangRs_Test;

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);
	virtual void InitLangRsByFile();

	virtual void RegisterLanguageResource();
	virtual void InitLangTxt();

public:



};

extern CString  g_strXLangRs_Test;
extern CString g_sLangID_Native_Amplitude;
extern CString g_sLangTxt_Native_Amplitude;
extern CString g_sLangID_Native_Phase;
extern CString g_sLangTxt_Native_Phase;
extern CString g_sLangID_Native_Freq;
extern CString g_sLangTxt_Native_Freq;
extern CString g_sLangID_Native_Channel;
extern CString g_sLangTxt_Native_Channel;
extern CString g_sLangID_Native_DC;
extern CString g_sLangTxt_Native_DC;
extern CString g_sLangID_Native_Fundamental;
extern CString g_sLangTxt_Native_Fundamental;
extern CString g_sLangID_Native_Validity;
extern CString g_sLangTxt_Native_Validity;
extern CString g_sLangID_Native_Overhaul;
extern CString g_sLangTxt_Native_Overhaul;
extern CString g_sLangID_Native_SelectTestFunction;
extern CString g_sLangTxt_Native_SelectTestFunction;
extern CString g_sLangID_Native_ReportHeadSet;//报告头设置
extern CString g_sLangTxt_Native_ReportHeadSet;

extern CString g_sLangID_Native_ConnectingTester;
extern CString g_sLangTxt_Native_ConnectingTester;
extern CString g_sLangID_Native_TesterConnectSucc;
extern CString g_sLangTxt_Native_TesterConnectSucc;
extern CString g_sLangID_Native_TesterConnectfail;
extern CString g_sLangTxt_Native_TesterConnectfail;
extern CString g_sLangID_Native_LCSTSendportSTGigabit;
extern CString g_sLangTxt_Native_LCSTSendportSTGigabit;


extern CString g_sLangID_Harm_Set;
extern CString g_sLangTxt_Harm_Set;
extern CString g_sLangID_Harm_Content;
extern CString g_sLangTxt_Harm_Content;
extern CString g_sLangID_Harm_Enable;
extern CString g_sLangTxt_Harm_Enable;
extern CString g_sLangID_Harm_UChannel;
extern CString g_sLangTxt_Harm_UChannel;
extern CString g_sLangID_Harm_IChannel;
extern CString g_sLangTxt_Harm_IChannel;

extern CString g_sLangID_Harm_UAllSelect;
extern CString g_sLangTxt_Harm_UAllSelect;
extern CString g_sLangID_Harm_IAllSelect;
extern CString g_sLangTxt_Harm_IAllSelect;
extern CString g_sLangID_Harm_UClear;	
extern CString g_sLangTxt_Harm_UClear;	   
extern CString g_sLangID_Harm_IClear;	   
extern CString g_sLangTxt_Harm_IClear;




extern CString g_sLangID_Harm_Reset;
extern CString g_sLangTxt_Harm_Reset;
extern CString g_sLangID_Harm_FundFreq;
extern CString g_sLangTxt_Harm_FundFreq;
extern CString g_sLangID_Harm_Times;
extern CString g_sLangTxt_Harm_Times;
extern CString g_sLangID_Harm_InterHarm;//间谐波
extern CString g_sLangTxt_Harm_InterHarm;

extern CString g_sLangID_Native_LangSetting;
extern CString g_sLangTxt_Native_LangSetting;
extern CString g_sLangID_Native_CustomSetup;
extern CString g_sLangTxt_Native_CustomSetup;
extern CString g_sLangID_Native_LangTipContext;
extern CString g_sLangTxt_Native_LangTipContext;
extern CString g_sLangID_Native_GndA;
extern CString g_sLangTxt_Native_GndA;
extern CString g_sLangID_Native_GndB;
extern CString g_sLangTxt_Native_GndB;
extern CString g_sLangID_Native_GndC;
extern CString g_sLangTxt_Native_GndC;
extern CString g_sLangID_Native_ShortAB;
extern CString g_sLangTxt_Native_ShortAB;
extern CString g_sLangID_Native_ShortBC;
extern CString g_sLangTxt_Native_ShortBC;
extern CString g_sLangID_Native_ShortCA;
extern CString g_sLangTxt_Native_ShortCA;
extern CString g_sLangID_Native_GndShortAB;
extern CString g_sLangTxt_Native_GndShortAB;
extern CString g_sLangID_Native_GndShortBC;
extern CString g_sLangTxt_Native_GndShortBC;
extern CString g_sLangID_Native_GndShortCA;
extern CString g_sLangTxt_Native_GndShortCA;
extern CString g_sLangID_Native_ShortABC;
extern CString g_sLangTxt_Native_ShortABC;
extern CString g_sLangID_Native_SinglePhase;
extern CString g_sLangTxt_Native_SinglePhase;
extern CString g_sLangID_Native_INotChange;
extern CString g_sLangTxt_Native_INotChange;
extern CString g_sLangID_Native_UNotChange;
extern CString g_sLangTxt_Native_UNotChange;
extern CString g_sLangID_Native_ZNotChange;
extern CString g_sLangTxt_Native_ZNotChange;
extern CString g_sLangID_Native_UZoomOut;
extern CString g_sLangTxt_Native_UZoomOut;
extern CString g_sLangID_Native_UZoomIn;
extern CString g_sLangTxt_Native_UZoomIn;
extern CString g_sLangID_Native_IZoomOut;
extern CString g_sLangTxt_Native_IZoomOut;
extern CString g_sLangID_Native_IZoomIn;
extern CString g_sLangTxt_Native_IZoomIn;
extern CString g_sLangID_Native_PhaseO;
extern CString g_sLangTxt_Native_PhaseO;
extern CString g_sLangID_Native_Relay;
extern CString g_sLangTxt_Native_Relay;
extern CString g_sLangID_Native_Measure;
extern CString g_sLangTxt_Native_Measure;
extern CString g_sLangID_Native_Current;
extern CString g_sLangTxt_Native_Current;
extern CString g_sLangID_Native_Voltage;
extern CString g_sLangTxt_Native_Voltage;
extern CString g_sLangID_Native_EDPhaseV;
extern CString g_sLangTxt_Native_EDPhaseV;
extern CString g_sLangID_Native_EDCurrent;
extern CString g_sLangTxt_Native_EDCurrent;
extern CString g_sLangID_Native_EqualAmp;
extern CString g_sLangTxt_Native_EqualAmp;
extern CString g_sLangID_Native_EqualFreq;
extern CString g_sLangTxt_Native_EqualFreq;
extern CString g_sLangID_Native_PositiveSeq;
extern CString g_sLangTxt_Native_PositiveSeq;
extern CString g_sLangID_Native_NegativeSeq;
extern CString g_sLangTxt_Native_NegativeSeq;
extern CString g_sLangID_Native_ZeroSeq;
extern CString g_sLangTxt_Native_ZeroSeq;
extern CString g_sLangID_Native_Zero;
extern CString g_sLangTxt_Native_Zero;
extern CString g_sLangID_Native_AllGroup;
extern CString g_sLangTxt_Native_AllGroup;
extern CString g_sLangID_Native_CurGroup;
extern CString g_sLangTxt_Native_CurGroup;
extern CString g_sLangID_Native_LastGroup;
extern CString g_sLangTxt_Natve_LastGroup;
extern CString g_sLangID_Native_NextGroup;
extern CString g_sLangTxt_Natve_NextGroup;
extern CString g_sLangID_Native_ExBinSet;
extern CString g_sLangTxt_Native_ExBinSet;
extern CString g_sLangID_Native_ExBoutSet;
extern CString g_sLangTxt_Native_ExBoutSet;
extern CString g_sLangID_Native_GooseDataSet;
extern CString g_sLangTxt_Native_GooseDataSet;
extern CString g_sLangID_Native_GooseOutSet;
extern CString g_sLangTxt_Native_GooseOutSet;
extern CString g_sLangID_Native_GooseInSet;
extern CString g_sLangTxt_Native_GooseInSet;
extern CString g_sLangID_Native_Bin;
extern CString g_sLangTxt_Native_Bin;
extern CString g_sLangID_Native_Bout;
extern CString g_sLangTxt_Native_Bout;
extern CString g_sLangID_Native_BinX;
extern CString g_sLangTxt_Native_BinX;
extern CString g_sLangID_Native_BoutX;
extern CString g_sLangTxt_Native_BoutX;
extern CString g_sLangID_Native_BinEx;
extern CString g_sLangTxt_Native_BinEx;
extern CString g_sLangID_Native_BoutEx;
extern CString g_sLangTxt_Native_BoutEx;
extern CString g_sLangID_Native_ActType;
extern CString g_sLangTxt_Native_ActType;
extern CString g_sLangID_Native_ActionTime;
extern CString g_sLangTxt_Native_ActionTime;
extern CString g_sLangID_Native_CurTypeIdx;
extern CString g_sLangTxt_Native_CurTypeIdx;
extern CString g_sLangID_Native_Group;
extern CString g_sLangTxt_Native_Group;
extern CString g_sLangID_Native_Reverse;
extern CString g_sLangTxt_Native_Reverse;
extern CString g_sLangID_Native_Repair;
extern CString g_sLangTxt_Native_Repair;
extern CString g_sLangID_Native_Revert;
extern CString g_sLangTxt_Native_Revert;
extern CString g_sLangID_Native_IEDName;
extern CString g_sLangTxt_Native_IEDName;
extern CString g_sLangID_Native_APPID;
extern CString g_sLangTxt_Native_APPID;
extern CString g_sLangID_Native_Type;
extern CString g_sLangTxt_Native_Type;
extern CString g_sLangID_Native_Action;
extern CString g_sLangTxt_Native_Action;
extern CString g_sLangID_Native_ReturnVal;
extern CString g_sLangTxt_Native_ReturnVal;
extern CString g_sLangID_Native_ReturnCoeff;
extern CString g_sLangTxt_Native_ReturnCoeff;
extern CString g_sLangID_Native_LogicOr;
extern CString g_sLangTxt_Native_LogicOr;
extern CString g_sLangID_Native_LogicAnd;
extern CString g_sLangTxt_Native_LogicAnd;
extern CString g_sLangID_Native_Enter;
extern CString g_sLangTxt_Native_Enter;
extern CString g_sLangID_Native_Caps;
extern CString g_sLangTxt_Native_Caps;
extern CString g_sLangID_Native_Space;
extern CString g_sLangTxt_Native_Space;
extern CString g_sLangID_Native_Esc;
extern CString g_sLangID_Native_Maps;
extern CString g_sLangTxt_Native_Maps;
extern CString g_sLangID_Native_Chs;
extern CString g_sLangTxt_Native_Chs;
extern CString g_sLangID_Native_Eng;
extern CString g_sLangTxt_Native_Eng;

extern CString g_sLangID_Native_FileFolder;
extern CString g_sLangTxt_Native_FileFolder;
extern CString g_sLangID_Native_NoTimeSync;
extern CString g_sLangTxt_Native_NoTimeSync;
extern CString g_sLangID_Native_Switch;
extern CString g_sLangTxt_Native_Switch;
extern CString g_sLangID_Native_AllFreq;
extern CString g_sLangTxt_Native_AllFreq;
extern CString g_sLangID_Native_FileType;
extern CString g_sLangTxt_Native_FileType;

extern CString g_sLangID_Native_SCLPath;
extern CString g_sLangTxt_Native_SCLPath;
extern CString g_sLangID_Native_SCLFilter;
extern CString g_sLangTxt_Native_SCLFilter;
extern CString g_sLangID_Native_ResultJudge;
extern CString g_sLangTxt_Native_ResultJudge;
extern CString g_sLangID_Native_ResultDescript;
extern CString g_sLangTxt_Native_ResultDescript;
extern CString g_sLangID_Native_ResultTime;
extern CString g_sLangTxt_Native_ResultTime;
extern CString g_sLangID_Native_ResultAbsRsltCal1;
extern CString g_sLangTxt_Native_ResultAbsRsltCal1;
extern CString g_sLangID_Native_ResultAbsRsltCal2;
extern CString g_sLangTxt_Native_ResultAbsRsltCal2;
extern CString g_sLangID_Native_ResultRelRsltCal1;
extern CString g_sLangTxt_Native_ResultRelRsltCal1;
extern CString g_sLangID_Native_ResultRelRsltCal2;
extern CString g_sLangTxt_Native_ResultRelRsltCal2;
extern CString g_sLangID_Native_TimeSettingCoef;
extern CString g_sLangTxt_Native_TimeSettingCoef;


extern CString g_sLangID_Manual_IV;
extern CString g_sLangTxt_Manual_IV;
extern CString g_sLangID_Manual_OtherParam;
extern CString g_sLangTxt_Manual_OtherParam;
extern CString g_sLangID_Manual_GlobalParam;
extern CString g_sLangTxt_Manual_GlobalParam;
extern CString g_sLangID_Manual_Oscillogram;
extern CString g_sLangTxt_Manual_Oscillogram;
extern CString g_sLangID_Manual_Changing;
extern CString g_sLangTxt_Manual_Changing;
extern CString g_sLangID_Manual_InitVal;
extern CString g_sLangTxt_Manual_InitVal;
extern CString g_sLangID_Manual_ChangeType;
extern CString g_sLangTxt_Manual_ChangeType;
extern CString g_sLangID_Manual_Channel;
extern CString g_sLangTxt_Manual_Channel;
extern CString g_sLangID_Manual_FinishVal;
extern CString g_sLangTxt_Manual_FinishVal;
extern CString g_sLangID_Manual_Step;
extern CString g_sLangTxt_Manual_Step;
extern CString g_sLangID_Manual_Timer;
extern CString g_sLangTxt_Manual_Timer;
extern CString g_sLangID_Manual_Old;
extern CString g_sLangTxt_Manual_Old;
extern CString g_sLangID_Manual_Auto;
extern CString g_sLangTxt_Manual_Auto;
extern CString g_sLangID_Manual_Delayed;
extern CString g_sLangTxt_Manual_Delayed;
extern CString g_sLangID_Manual_OutSetting;
extern CString g_sLangTxt_Manual_OutSetting;
extern CString g_sLangID_Manual_Out1;
extern CString g_sLangTxt_Manual_Out1;
extern CString g_sLangID_Manual_Out2;
extern CString g_sLangTxt_Manual_Out2;
extern CString g_sLangID_Manual_Out3;
extern CString g_sLangTxt_Manual_Out3;
extern CString g_sLangID_Manual_Out4;
extern CString g_sLangTxt_Manual_Out4;
extern CString g_sLangID_Manual_Out5;
extern CString g_sLangTxt_Manual_Out5;
extern CString g_sLangID_Manual_Out6;
extern CString g_sLangTxt_Manual_Out6;
extern CString g_sLangID_Manual_Out7;
extern CString g_sLangTxt_Manual_Out7;
extern CString g_sLangID_Manual_Out8;
extern CString g_sLangTxt_Manual_Out8;
extern CString g_sLangID_Manual_InSetting;
extern CString g_sLangTxt_Manual_InSetting;
extern CString g_sLangID_Manual_InA;
extern CString g_sLangTxt_Manual_InA;
extern CString g_sLangID_Manual_InB;
extern CString g_sLangTxt_Manual_InB;
extern CString g_sLangID_Manual_InC;
extern CString g_sLangTxt_Manual_InC;
extern CString g_sLangID_Manual_InD;
extern CString g_sLangTxt_Manual_InD;
extern CString g_sLangID_Manual_InE;
extern CString g_sLangTxt_Manual_InE;
extern CString g_sLangID_Manual_InF;
extern CString g_sLangTxt_Manual_InF;
extern CString g_sLangID_Manual_InG;
extern CString g_sLangTxt_Manual_InG;
extern CString g_sLangID_Manual_InH;
extern CString g_sLangTxt_Manual_InH;
extern CString g_sLangID_Manual_Lock;
extern CString g_sLangTxt_Manual_Lock;
extern CString g_sLangID_Manual_UnLock;
extern CString g_sLangTxt_Manual_UnLock;
extern CString g_sLangID_Manual_ActionTime;
extern CString g_sLangTxt_Manual_ActionTime;
extern CString g_sLangID_Manual_ReturnTime;
extern CString g_sLangTxt_Manual_ReturnTime;
extern CString g_sLangID_Manual_S_E;
extern CString g_sLangTxt_Manual_S_E;
extern CString g_sLangID_Manual_S_E_S;
extern CString g_sLangTxt_Manual_S_E_S;

extern CString g_sLangID_Manual_Harm;
extern CString g_sLangTxt_Manual_Harm;
extern CString g_sLangID_Manual_TestMethod;
extern CString g_sLangTxt_Manual_TestMethod;
extern CString g_sLangID_Manual_MeasType;
extern CString g_sLangTxt_Manual_MeasType;
extern CString g_sLangID_Manual_BCode;
extern CString g_sLangTxt_Manual_BCode;
extern CString g_sLangID_Manual_TestReport;
extern CString g_sLangTxt_Manual_TestReport;
extern CString g_sLangID_Manual_TestTime;
extern CString g_sLangTxt_Manual_TestTime;
extern CString g_sLangID_Manual_PositiveLogic;
extern CString g_sLangTxt_Manual_PositiveLogic;
extern CString g_sLangID_Manual_NegativeLogic;
extern CString g_sLangTxt_Manual_NegativeLogic;

extern CString g_sLangID_Manual_SyncSet;
extern CString g_sLangTxt_Manual_SyncSet;
extern CString g_sLangID_Manual_SecSyncStatus;
extern CString g_sLangTxt_Manual_SecSyncStatus;
extern CString g_sLangID_Manual_OpenSecSync;
extern CString g_sLangTxt_Manual_OpenSecSync;
extern CString g_sLangID_Manual_CloseSecSync;
extern CString g_sLangTxt_Manual_CloseSecSync;
extern CString g_sLangID_Manual_IEC1588Sync;
extern CString g_sLangTxt_Manual_IEC1588Sync;
extern CString g_sLangID_Manual_PeerDelay;
extern CString g_sLangTxt_Manual_PeerDelay;
extern CString g_sLangID_Manual_DelayRequestReply;
extern CString g_sLangTxt_Manual_DelayRequestReply;

extern CString g_sLangID_Manual_Refresh;
extern CString g_sLangTxt_Manual_Refresh;

extern CString g_sLangID_IEC_IEC_WeakSet;
extern CString g_sLangTxt_IEC_IEC_WeakSet;
extern CString g_sLangID_ErrorSet;
extern CString g_sLangTxt_ErrorSet;
extern CString g_sLangID_CurAbsError;
extern CString g_sLangTxt_CurAbsError;
extern CString g_sLangID_CurRelError;
extern CString g_sLangTxt_CurRelError;
extern CString g_sLangID_VolAbsError;
extern CString g_sLangTxt_VolAbsError;
extern CString g_sLangID_VolRelError;
extern CString g_sLangTxt_VolRelError;
extern CString g_sLangID_ImpAbsError;
extern CString g_sLangTxt_ImpAbsError;
extern CString g_sLangID_ImpRelError;
extern CString g_sLangTxt_ImpRelError;
extern CString g_sLangID_TimeAbsError;
extern CString g_sLangTxt_TimeAbsError;
extern CString g_sLangID_TimeRelError;
extern CString g_sLangTxt_TimeRelError;
extern CString g_sLangID_AngError;
extern CString g_sLangTxt_AngError;
extern CString g_sLangID_FreqError;
extern CString g_sLangTxt_FreqError;
extern CString g_sLangID_DvDtError;
extern CString g_sLangTxt_DvDtError;
extern CString g_sLangID_DfDtError;
extern CString g_sLangTxt_DfDtError;
extern CString g_sLangID_DiffRateCoefAbsError;
extern CString g_sLangTxt_DiffRateCoefAbsError;
extern CString g_sLangID_DiffRateCoefRelError;
extern CString g_sLangTxt_DiffRateCoefRelError;
extern CString g_sLangID_DiffHarmCoefAbsError;
extern CString g_sLangTxt_DiffHarmCoefAbsError;
extern CString g_sLangID_DiffHarmCoefRelError;
extern CString g_sLangTxt_DiffHarmCoefRelError;

extern CString g_sLangID_State_TrigerSetup;
extern CString g_sLangTxt_State_TrigerSetup;
extern CString g_sLangID_State_TrigerCondition;
extern CString g_sLangTxt_State_TrigerCondition;
extern CString g_sLangID_State_OutTime;
extern CString g_sLangTxt_State_OutTime;
extern CString g_sLangID_State_TrigerTime;
extern CString g_sLangTxt_State_TrigerTime;
extern CString g_sLangID_State_Hour;
extern CString g_sLangTxt_State_Hour;
extern CString g_sLangID_State_Minute;
extern CString g_sLangTxt_State_Minute;
extern CString g_sLangID_State_Second;
extern CString g_sLangTxt_State_Second;
extern CString g_sLangID_State_TrigerHoldTime;
extern CString g_sLangTxt_State_TrigerHoldTime;
extern CString g_sLangID_State_HoldTime;
extern CString g_sLangTxt_State_HoldTime;
extern CString g_sLangID_State_ShortCalc;
extern CString g_sLangTxt_State_ShortCalc;
extern CString g_sLangID_State_GradientSet;
extern CString g_sLangTxt_State_GradientSet;
extern CString g_sLangID_State_PasteStateBf;
extern CString g_sLangTxt_State_PasteStateBf;
extern CString g_sLangID_State_InsertStateBf;
extern CString g_sLangTxt_State_InsertStateBf;
extern CString g_sLangID_State_InsertStateAf;
extern CString g_sLangTxt_State_InsertStateAf;
extern CString g_sLangID_State_PasteStateAf;
extern CString g_sLangTxt_State_PasteStateAf;
extern CString g_sLangID_State_CopyCurState;
extern CString g_sLangTxt_State_CopyCurState;
extern CString g_sLangID_State_DeleteCurState;
extern CString g_sLangTxt_State_DeleteCurState;
extern CString g_sLangID_State_UISet;
extern CString g_sLangTxt_State_UISet;
extern CString g_sLangID_State_StateParaSet;
extern CString g_sLangTxt_State_StateParaSet;
extern CString g_sLangID_State_JudgeCondition;
extern CString g_sLangTxt_State_JudgeCondition;
extern CString g_sLangID_State_DCOffSet;
extern CString g_sLangTxt_State_DCOffSet;
extern CString g_sLangID_State_Tou;
extern CString g_sLangTxt_State_Tou;
extern CString g_sLangID_State_StackByState;
extern CString g_sLangTxt_State_StackByState;
extern CString g_sLangID_State_RepeatTimes;
extern CString g_sLangTxt_State_RepeatTimes;
extern CString g_sLangID_State_CommonValue_OK;
extern CString g_sLangTxt_State_CommonValue_OK;
extern CString g_sLangID_State_CommonValue_Cancel;
extern CString g_sLangTxt_State_CommonValue_Cancel;
extern CString g_sLangID_State_ChGroup;
extern CString g_sLangTxt_State_ChGroup;
extern CString g_sLangID_Abnormal_APPID;
extern CString g_sLangTxt_Abnormal_APPID;
extern CString g_sLangID_State_FaultType;
extern CString g_sLangTxt_State_FaultType;
extern CString g_sLangID_State_CalcMode;
extern CString g_sLangTxt_State_CalcMode;
extern CString g_sLangID_State_ShortI;
extern CString g_sLangTxt_State_ShortI;
extern CString g_sLangID_State_ShortU;
extern CString g_sLangTxt_State_ShortU;
extern CString g_sLangID_State_ZeroCoeff;
extern CString g_sLangTxt_State_ZeroCoeff;
extern CString g_sLangID_State_CalcType;
extern CString g_sLangTxt_State_CalcType;
extern CString g_sLangID_State_Amp;
extern CString g_sLangTxt_State_Amp;
extern CString g_sLangID_State_Angle;
extern CString g_sLangTxt_State_Angle;
extern CString g_sLangID_State_DiffCurrentA;
extern CString g_sLangTxt_State_DiffCurrentA;
extern CString g_sLangID_State_BrakCurrentA;
extern CString g_sLangTxt_State_BrakCurrentA;
extern CString g_sLangID_State_Lswindwirtype;
extern CString g_sLangTxt_State_Lswindwirtype;
extern CString g_sLangID_State_HbdiffAngularwind;
extern CString g_sLangTxt_State_HbdiffAngularwind ;
extern CString g_sLangID_LoadI;
extern CString g_sLangTxt_LoadI;
extern CString g_sLangID_State_LoadAngle;
extern CString g_sLangTxt_State_LoadAngle;
extern CString g_sLangID_State_ShortCalc_OK;
extern CString g_sLangTxt_State_ShortCalc_OK;
extern CString g_sLangID_State_ShortCalc_Cancel;
extern CString g_sLangTxt_State_ShortCalc_Cancel;
extern CString g_sLangID_State_Trigger_Time;
extern CString g_sLangTxt_State_Trigger_Time;
extern CString g_sLangID_State_Trigger_TimeAndBin;
extern CString g_sLangTxt_State_Trigger_TimeAndBin;
extern CString g_sLangID_State_Trigger_Bin;
extern CString g_sLangTxt_State_Trigger_Bin;
extern CString g_sLangID_State_Trigger_Manu;
extern CString g_sLangTxt_State_Trigger_Manu;
extern CString g_sLangID_State_Trigger_GPSB;
extern CString g_sLangTxt_State_Trigger_GPSB;
extern CString g_sLangID_State_LinearChange;
extern CString g_sLangTxt_State_LinearChange;
extern CString g_sLangID_State_StepChange;
extern CString g_sLangTxt_State_StepChange;
extern CString g_sLangID_State_StepTime;
extern CString g_sLangTxt_State_StepTime;
extern CString g_sLangID_State_BeginVal;
extern CString g_sLangTxt_State_BeginVal;
extern CString g_sLangID_State_EndVal;
extern CString g_sLangTxt_State_EndVal;
extern CString g_sLangID_State_AmpGradient;
extern CString g_sLangTxt_State_AmpGradient;
extern CString g_sLangID_State_FreqGradient;
extern CString g_sLangTxt_State_FreqGradient;
extern CString g_sLangID_State_LastState;
extern CString g_sLangTxt_State_LastState;
extern CString g_sLangID_State_FirstState;
extern CString g_sLangTxt_State_FirstState;
extern CString g_sLangID_State_Lsbalancefactor;
extern CString g_sLangTxt_State_Lsbalancefactor;
extern CString g_sLangID_State_No;
extern CString g_sLangTxt_State_No;
extern CString g_sLangID_State_Yes;
extern CString g_sLangTxt_State_Yes;
extern CString g_sLangID_State_HarmCount;
extern CString g_sLangTxt_State_HarmCount;
extern CString g_sLangID_State_Trans1;
extern CString g_sLangTxt_State_Trans1;
extern CString g_sLangID_State_Trans2;
extern CString g_sLangTxt_State_Trans2;
extern CString g_sLangID_State_Winding;
extern CString g_sLangTxt_State_Winding;
extern CString g_sLangID_State_NoAdjust;
extern CString g_sLangTxt_State_NoAdjust;
extern CString g_sLangID_State_YAdjust;
extern CString g_sLangTxt_State_YAdjust;


extern CString g_sLangID_State_SettingValue;//整定值
extern CString g_sLangTxt_State_SettingValue;

extern CString g_sLangID_State_Estimate;//整定及结果评估
extern CString g_sLangTxt_State_Estimate;
extern CString g_sLangID_State_InState ;//进入状态
extern CString g_sLangTxt_State_InState ;

//整定及结果评估 表格

extern CString g_sLangID_StateEstimate_Start ;//计时起点
extern CString g_sLangTxt_StateEstimate_State ;
extern CString g_sLangID_StateEstimate_End ;//计时终点
extern CString g_sLangTxt_StateEstimate_End ;
extern CString g_sLangID_StateEstimate_ErrorType ;//误差类型
extern CString g_sLangTxt_StateEstimate_ErrorType ;
extern CString g_sLangID_StateEstimate_RelError ;//相对误差
extern CString g_sLangTxt_StateEstimate_RelError ;
extern CString g_sLangID_StateEstimate_RelError_Percent ;//相对误差(％)
extern CString g_sLangTxt_StateEstimate_RelError_Percent ;
extern CString g_sLangID_StateEstimate_AbsError ;//绝对误差
extern CString g_sLangTxt_StateEstimate_AbsError ;
extern CString g_sLangID_StateEstimate_AbsError_Neg ;//绝对误差(-)
extern CString g_sLangTxt_StateEstimate_AbsError_Neg ;
extern CString g_sLangID_StateEstimate_SettingValue ;//整定值(s)
extern CString g_sLangTxt_StateEstimate_SettingValue ;
extern CString g_sLangID_StateEstimate_BinTrigger ;//开入触发
extern CString g_sLangTxt_StateEstimate_BinTrigger ;

extern CString g_sLangID_StateEstimate_CombinationError ;//组合误差
extern CString g_sLangTxt_StateEstimate_CombinationError ;

extern CString g_sLangID_StateEstimate_ResultEstimate;//结果评估
extern CString g_sLangTxt_StateEstimate_ResultEstimate;

/////

extern CString g_sLangID_State_Difflowcalculation;
extern CString g_sLangTxt_State_Difflowcalculation;
extern CString g_sLangID_State_Bequation;
extern CString g_sLangTxt_State_Bequation;
extern CString g_sLangID_State_CTpolarity;
extern CString g_sLangTxt_State_CTpolarity;
extern CString g_sLangID_State_Hsbalancefactor;
extern CString g_sLangTxt_State_Hsbalancefactor;
extern CString g_sLangID_State_Hswindwirtype;
extern CString g_sLangTxt_State_Hswindwirtype;
extern CString g_sLangID_State_Bfactorcalculation;
extern CString g_sLangTxt_State_Bfactorcalculation;
extern CString g_sLangID_State_Oclock;
extern CString g_sLangTxt_State_Oclock;
extern CString g_sLangID_State_Correctionselection;
extern CString g_sLangTxt_State_Correctionselection;
extern CString g_sLangID_State_Testphase;
extern CString g_sLangTxt_State_Testphase;
extern CString g_sLangID_State_FirHVoltageSide;
extern CString g_sLangTxt_State_FirHVoltageSide;
extern CString g_sLangID_State_SecHVoltageSide;
extern CString g_sLangTxt_State_SecHVoltageSide;
extern CString g_sLangID_State_BFtransformer;
extern CString g_sLangTxt_State_BFtransformer;
extern CString g_sLangID_State_OFtransformer;
extern CString g_sLangTxt_State_OFtransformer;
extern CString g_sLangID_State_NotconWindconnection;
extern CString g_sLangTxt_State_NotconWindconnection;
extern CString g_sLangID_State_ConWindconnection;
extern CString g_sLangTxt_State_ConWindconnection;
extern CString g_sLangID_State_Triangulationcorrection;
extern CString g_sLangTxt_State_Triangulationcorrection;
extern CString g_sLangID_Native_GroundDisSetV;
extern CString g_sLangTxt_Native_GroundDisSetV;//接地距离定值（1-5段）GroundDisSet

//未动作 LCQ 
extern  CString g_sLangID_State_NoActioned;
extern  CString g_sLangTxt_State_NoActioned;
//动作值 LCQ 
extern  CString g_sLangID_State_ActionValue;
extern  CString g_sLangTxt_State_ActionValue;
//误差 LCQ 
extern  CString g_sLangID_State_Error;
extern  CString g_sLangTxt_State_Error;
//谐波含量 LCQ
extern  CString g_sLangID_State_HarContent;
extern  CString g_sLangTxt_State_HarContent;
//差动电流
extern  CString g_sLangID_State_DifferentCur;
extern  CString g_sLangTxt_State_DifferentCur;
//制动电流
extern  CString g_sLangID_State_BrakingCur;
extern  CString g_sLangTxt_State_BrakingCur;
//电压比值
extern  CString g_sLangID_State_VoltageRat;
extern  CString g_sLangTxt_State_VoltageRat;

//阻抗值(Z)
extern  CString g_sLangID_State_ZImpValue;
extern  CString g_sLangTxt_State_ZImpValue;
//角度(°)
extern  CString g_sLangID_State_DAngle;
extern  CString g_sLangTxt_State_DAngle;
//电流比值
extern  CString g_sLangID_State_CurrentRat;
extern  CString g_sLangTxt_State_CurrentRat;


//系统生成  LCQ                                         
extern  CString g_sLangID_State_Sysgenerated;
extern  CString g_sLangTxt_State_Sysgenerated;
//特性曲线查找失败(strCharaID=%s;strIndex=%s),无法更新项目列表.LCQ
extern  CString g_sLangID_State_CurlfailedItems;
extern  CString g_sLangTxt_State_CurlfailedItems;

//差流计算    LCQ                                                
extern  CString g_sLangID_State_Difflowcalculation;
extern  CString g_sLangTxt_State_Difflowcalculation;
//状态编CString辑    LCQ
extern CString g_sLangID_State_StatusEdition;
extern CString g_sLangTxt_State_StatusEdition;											
//谐波按幅值递变   LCQ
extern  CString g_sLangID_State_HarmonicAmpInc;
extern  CString g_sLangTxt_State_HarmonicAmpInc;
//谐波按百分比递变   LCQ
extern  CString g_sLangID_State_HarmonicAmpPer;
extern  CString g_sLangTxt_State_HarmonicAmpPer;
//上一状态   lCQ
extern  CString g_sLangID_State_PreviosState;
extern  CString g_sLangTxt_State_PreviosState;
//下一状态  lCQ
extern  CString g_sLangID_State_NextState;
extern  CString g_sLangTxt_State_NextState;
//非递变通道分组设置  LCQ
extern  CString g_sLangID_Gradient_Npchannelgroupset;
extern  CString g_sLangTxt_Gradient_Npchannelgroupset;
//分组设置  LCQ
extern  CString g_sLangID_Gradient_Groupset;
extern  CString g_sLangTxt_Gradient_Groupset;

//十二点
extern  CString g_sLangID_State_12Oclock;  
extern  CString g_sLangTxt_State_12Oclock;

//工具栏
extern  CString g_sLangID_Native_Toolbar;  
extern  CString g_sLangTxt_Native_Toolbar;

//第一组LCQ
extern  CString g_sLangID_Manual_FirGroup;  
extern  CString g_sLangTxt_Manual_FirGroup;
//测试
extern  CString g_sLangID_State_Test;   
extern  CString g_sLangTxt_State_Test;
//描述
extern  CString g_sLangID_State_Description;  
extern  CString g_sLangTxt_State_Description;
//状态名
extern  CString g_sLangID_State_Statusname;  
extern  CString g_sLangTxt_State_Statusname;
//4G、蓝牙、网卡使能
extern  CString g_sLangID_State_FGBlueNetworkcar;  
extern  CString g_sLangTxt_State_FGBlueNetworkcar;
//蓝牙
extern  CString g_sLangID_State_Bluetooth;  
extern  CString g_sLangTxt_State_Bluetooth;
//无线网卡
extern  CString g_sLangID_State_Wirelesscard;  
extern  CString g_sLangTxt_State_Wirelesscard;
//本机网卡
extern  CString g_sLangID_State_NativeNetworkcard;  
extern  CString g_sLangTxt_State_NativeNetworkcard;
//屏幕亮度
extern  CString g_sLangID_State_MinScreenBright;  
extern  CString g_sLangTxt_State_MinScreenBright;
//(备注:5代表最亮)
extern  CString g_sLangID_State_NoteFivemeansBrightest;  
extern  CString g_sLangTxt_State_NoteFivemeansBrightest;
//背光时间(分钟)
extern  CString g_sLangID_State_MinBacklighttime;  
extern  CString g_sLangTxt_State_MinBacklighttime;
//(备注:0代表常亮)
extern  CString g_sLangID_State_NoteZeromeansAlwayson;  
extern  CString g_sLangTxt_State_NoteZeromeansAlwayson;
//(机器散热风扇模式)
extern  CString g_sLangID_State_FanMode;  
extern  CString g_sLangTxt_State_FanMode;
//("(正常)")
extern  CString g_sLangID_State_Normal;
extern  CString g_sLangTxt_State_Normal;
//("(静音)")
extern  CString g_sLangID_State_Mute;
extern  CString g_sLangTxt_State_Mute;
//时区设置
extern  CString g_sLangID_State_Timezonesetting;  
extern  CString g_sLangTxt_State_Timezonesetting;
//其它设置
extern  CString g_sLangID_State_Othersettings;  
extern  CString g_sLangTxt_State_Othersettings;
//数据值
extern  CString g_sLangID_State_Datavalue;  
extern  CString g_sLangTxt_State_Datavalue;
//辅助直流设置
extern  CString g_sLangID_State_AuxiliaryDCSettings;  
extern  CString g_sLangTxt_State_AuxiliaryDCSettings;
//其它
extern  CString g_sLangID_State_Others;  
extern  CString g_sLangTxt_State_Others;
//电压值(V):
extern  CString g_sLangID_State_Voltagevalue;  
extern  CString g_sLangTxt_State_Voltagevalue;
//"请稍后,已开始"
extern CString g_sLangID_Gradient_Pleaselaterithasstarted;
extern CString g_sLangTxt_Gradient_Pleaselaterithasstarted;
//扫描线段lcq 3.13
extern  CString g_sLangID_State_Scanlinesegments;  
extern  CString g_sLangTxt_State_Scanlinesegments;
//测试点lcq 3.13
extern  CString g_sLangID_State_Testpoints;  
extern  CString g_sLangTxt_State_Testpoints;
//电流(Ie)lcq 3.13
extern  CString g_sLangID_State_Iecurrent;  
extern  CString g_sLangTxt_State_Iecurrent;
//电流(A)lcq 3.13
extern  CString g_sLangID_State_Acurrent;  
extern  CString g_sLangTxt_State_Acurrent;

//谐波 lcq 3.13
extern  CString g_sLangID_State_Harmonicwave;  
extern  CString g_sLangTxt_State_Harmonicwave;
//插值法 lcq 3.13
extern  CString g_sLangID_State_Interpolation;  
extern  CString g_sLangTxt_State_Interpolation;
//同步法 lcq 3.13
extern  CString g_sLangID_State_Synchronousmethod;  
extern  CString g_sLangTxt_State_Synchronousmethod;
//测试逻辑 lcq 3.13
extern  CString g_sLangID_State_TestLogic;  
extern  CString g_sLangTxt_State_TestLogic;
//上升沿有效 lcq 3.13
extern  CString g_sLangID_State_Risingedgeeffective;  
extern  CString g_sLangTxt_State_Risingedgeeffective;
//下降沿有效 lcq 3.13
extern  CString g_sLangID_State_Downedgeeffective;  
extern  CString g_sLangTxt_State_Downedgeeffective;
//无PPS lcq 3.13
extern  CString g_sLangID_State_NOPPS;  
extern  CString g_sLangTxt_State_NOPPS;
//PPS设置 lcq 3.13
extern  CString g_sLangID_State_PPSsettings;  
extern  CString g_sLangTxt_State_PPSsettings;
//无PPS延时补偿(μs) lcq 3.13
extern  CString g_sLangID_State_UsNoPPSdelaycompensation;  
extern  CString g_sLangTxt_State_UsNoPPSdelaycompensation;
//同步时长(s): lcq 3.13
extern  CString g_sLangID_State_SSyncduration;  
extern  CString g_sLangTxt_State_SSyncduration;
//当前误差(μs): lcq 3.13
extern  CString g_sLangID_State_UsCurrenterror;  
extern  CString g_sLangTxt_State_UsCurrenterror;
//最大误差(μs): lcq 3.13
extern  CString g_sLangID_State_UsMaximumerror;  
extern  CString g_sLangTxt_State_UsMaximumerror;
//最小误差(μs): lcq 3.13
extern  CString g_sLangID_State_UsMinimumerror;  
extern  CString g_sLangTxt_State_UsMinimumerror;
//备注  lcq 3.13
extern  CString g_sLangID_State_Remark;  
extern  CString g_sLangTxt_State_Remark;
//守时时长(s):  lcq 3.13 
extern  CString g_sLangID_State_SPunctuality;  
extern  CString g_sLangTxt_State_SPunctuality;
//通用试验模板文件 lcq 3.14 
extern  CString g_sLangID_State_Genexperfile;
extern  CString g_sLangTxt_State_Genexperfile;
//Goose异常模拟模板文件 lcq 3.14
extern  CString g_sLangID_State_Gooseexfile;
extern  CString g_sLangTxt_State_Gooseexfile;
//GOOSE报文参数  lcq 3.14
extern  CString g_sLangID_State_GOOSEmessageparameters;
extern  CString g_sLangTxt_State_GOOSEmessageparameters;
//输入值含有非法字符. lcq 3.14
extern  CString g_sLangID_State_IlleInputCharac;
extern  CString g_sLangTxt_State_IlleInputCharac;

//丢帧 lcq 3.14
extern  CString g_sLangID_State_Dropframes;
extern  CString g_sLangTxt_State_Dropframes;
//飞点 lcq 3.14
extern  CString g_sLangID_State_Flypoint;
extern  CString g_sLangTxt_State_Flypoint;
//抖动 lcq 3.14
extern  CString g_sLangID_State_Dithering;
extern  CString g_sLangTxt_State_Dithering;
//错序 lcq 3.14
extern  CString g_sLangID_State_OutofOrder;
extern  CString g_sLangTxt_State_OutofOrder;
//电压电流 lcq 3.14
extern  CString g_sLangID_State_VoltageandCurrent;
extern  CString g_sLangTxt_State_VoltageandCurrent;
//状态序列模板文件 lcq 3.14
extern  CString g_sLangID_State_StateSequencefile;
extern  CString g_sLangTxt_State_StateSequencefile;
//SV异常模拟  lcq 3.14
extern  CString g_sLangID_State_SVexceptionSimulation;
extern  CString g_sLangTxt_State_SVexceptionSimulation;
//状态数目不能超过%d  lcq 3.14
extern  CString g_sLangID_State_NumnotExceed;
extern  CString g_sLangTxt_State_NumnotExceed;
//当前循环  lcq 3.14
extern  CString g_sLangID_State_TheCurrentLoop;
extern  CString g_sLangTxt_State_TheCurrentLoop;
//进入    lcq 3.14
extern  CString g_sLangID_State_Enter;
extern  CString g_sLangTxt_State_Enter;
//输入的电压超出范围 lcq 3.14
extern  CString g_sLangID_State_InVolOutofRange;
extern  CString g_sLangTxt_State_InVolOutofRange;
//输入的电流超出范围 lcq 3.14
extern  CString g_sLangID_State_InCurOutofrange;
extern  CString g_sLangTxt_State_InCurOutofrange;
//%1次谐波 lcq 3.14
extern  CString g_sLangID_State_TheOnepercentHarmonic;
extern  CString g_sLangTxt_State_TheOnepercentHarmonic;
//谐波测试模板文件 lcq 3.14
extern  CString g_sLangID_State_HarmonicTestTemplatefile;
extern  CString g_sLangTxt_State_HarmonicTestTemplatefile;
//递变试验模板文件  lcq 3.14
extern  CString g_sLangID_State_IncreExperfile;
extern  CString g_sLangTxt_State_IncreExperfile;
//TestCtrlCntrLinux生成日期 lcq 3.14
extern  CString g_sLangID_State_TBuildDate;
extern  CString g_sLangTxt_State_TBuildDate;
//"IEEE曲线参数设置"  lcq 3.14
extern  CString g_sLangID_State_IEEECurset;
extern  CString g_sLangTxt_State_IEEECurset;
//"IAC曲线参数设置"  lcq 3.14
extern  CString g_sLangID_State_IACCurSet;
extern  CString g_sLangTxt_State_IACCurSet;
//"I2T曲线参数设置"  lcq 3.14
extern  CString g_sLangID_State_I2TCurSet;
extern  CString g_sLangTxt_State_I2TCurSet;
//"IEC曲线参数设置"  lcq 3.14
extern  CString g_sLangID_State_IECCurSet;
extern  CString g_sLangTxt_State_IECCurSet;
//"电压反时限参数设置"  lcq 3.14
extern  CString g_sLangID_State_VolLimitSet;
extern  CString g_sLangTxt_State_VolLimitSet;
//放大 lcq 3.14
extern  CString g_sLangID_State_Magnify;
extern  CString g_sLangTxt_State_Magnify;
//缩小 lcq 3.14
extern  CString g_sLangID_State_Shrink;
extern  CString g_sLangTxt_State_Shrink;
//筛选
extern  CString g_sLangID_IECConfig_Screen;	
extern  CString g_sLangTxt_IECConfig_Screen; 
//复位 lcq 3.14
extern  CString g_sLangID_State_Reposition;
extern  CString g_sLangTxt_State_Reposition;
//柔直(FT3)  lcq 3.14
extern  CString g_sLangID_State_FThreeStraight;
extern  CString g_sLangTxt_State_FThreeStraight;
//单相阻抗 lcq 3.15
extern  CString g_sLangID_State_SinglephaseImpedance;
extern  CString g_sLangTxt_State_SinglephaseImpedance;
//" 重  合 "   lcq 3.15
extern  CString g_sLangID_State_Coincidence;
extern  CString g_sLangTxt_State_Coincidence;
//" 后 加 速 " lcq 3.15
extern  CString g_sLangID_State_RearAcceleration;
extern  CString g_sLangTxt_State_RearAcceleration;
//版本信息   lcq 3.15
extern  CString g_sLangID_State_VersionInformation;
extern  CString g_sLangTxt_State_VersionInformation;
//装置属性   lcq 3.15
extern  CString g_sLangID_State_ApplianceProperties;
extern  CString g_sLangTxt_State_ApplianceProperties;
//"型号:"    lcq 3.15
extern  CString g_sLangID_State_AppModel;
extern  CString g_sLangTxt_State_AppModel;
//"编号:"    lcq 3.15
extern  CString g_sLangID_State_AppNumber;
extern  CString g_sLangTxt_State_AppNumber;
//"模块管理"   lcq 3.15
extern  CString g_sLangID_State_ModuleManagement;
extern  CString g_sLangTxt_State_ModuleManagement;
//请打开COMTRADE波形文件 lcq 3.15
extern  CString g_sLangID_State_POpenCFile;
extern  CString g_sLangTxt_State_POpenCFile;

//特性曲线边元素 lcq 3.15
extern  CString g_sLangID_State_CharCurEdgeElements;
extern  CString g_sLangTxt_State_CharCurEdgeElements;
//"边元素类型" lcq 3.15
extern  CString g_sLangID_State_TheEdgeElementType;
extern  CString g_sLangTxt_State_TheEdgeElementType;
//误差带长度 lcq 3.15
extern  CString g_sLangID_State_ErrorBandLength;
extern  CString g_sLangTxt_State_ErrorBandLength;
//边测试点数 lcq 3.15
extern  CString g_sLangID_State_EdgeTestPoints;
extern  CString g_sLangTxt_State_EdgeTestPoints;
//起始点-R  lcq 3.15
extern  CString g_sLangID_State_startingPointR;
extern  CString g_sLangTxt_State_startingPointR;
//起始点-X  lcq 3.15
extern  CString g_sLangID_State_startingPointX;
extern  CString g_sLangTxt_State_EdgeTestPointX;
//终止点-R  lcq 3.15
extern  CString g_sLangID_State_EndPointR;
extern  CString g_sLangTxt_State_EndPointR;
//终止点-X   lcq 3.15
extern  CString g_sLangID_State_EndPointX;
extern  CString g_sLangTxt_State_EndPointX;
//方向  lcq 3.15
extern  CString g_sLangID_State_Direction;
extern  CString g_sLangTxt_State_Direction;
//正向到达  lcq 3.15
extern  CString g_sLangID_State_PositiveArrival;
extern  CString g_sLangTxt_State_PositiveArrival;
//角度  lcq 3.15
extern  CString g_sLangID_State_ANgle;
extern  CString g_sLangTxt_State_ANgle;
//偏移  lcq 3.15
extern  CString g_sLangID_State_Offset;
extern  CString g_sLangTxt_State_Offset;
//宽度  lcq 3.15
extern  CString g_sLangID_State_Width;
extern  CString g_sLangTxt_State_Width;
//x-圆心  lcq 3.15
extern  CString g_sLangID_State_CenterX;
extern  CString g_sLangTxt_State_CenterX;
//y-圆心  lcq 3.15
extern  CString g_sLangID_State_CenterY;
extern  CString g_sLangTxt_State_CenterY;
//半径  lcq 3.15
extern  CString g_sLangID_State_Radius;
extern  CString g_sLangTxt_State_Radius;
//起始角度  lcq 3.15
extern  CString g_sLangID_State_StartingAngle;
extern  CString g_sLangTxt_State_StartingAngle;
//终止角度 lcq 3.15
extern  CString g_sLangID_State_TerminationAngle;
extern  CString g_sLangTxt_State_TerminationAngle;
//时钟方向  lcq 3.15
extern  CString g_sLangID_State_ClockDirection;
extern  CString g_sLangTxt_State_ClockDirection;
//低压保护 lcq 3.20
extern  CString g_sLangID_State_LowVoltageprotection;
extern  CString g_sLangTxt_State_LowVoltageprotection;
//过压保护 lcq 3.20
extern  CString g_sLangID_State_Overvoltageprotection;
extern  CString g_sLangTxt_State_Overvoltageprotection;
//谐波制动系数 lcq 3.20
extern  CString g_sLangID_State_HarmonicBrakingcoefficient;
extern  CString g_sLangTxt_State_HarmonicBrakingcoefficient;
//谐波制动 lcq 3.20
extern  CString g_sLangID_State_Harmonicbraking;
extern  CString g_sLangTxt_State_Harmonicbraking;
//硬件信息设置 lcq 3.15
extern  CString g_sLangID_State_HardwareInformationSettings;
extern  CString g_sLangTxt_State_HardwareInformationSettings;
//输入值%f超出范围(%d).
extern  CString g_sLangID_State_EnterTheValueoutofRange;     
extern  CString g_sLangTxt_State_EnterTheValueoutofRange;    


//(UTC-12:00)国际日期变更线西 lcq 3.15
extern  CString g_sLangID_State_UTC_TwelveWIntDLine;
extern  CString g_sLangTxt_State_UTC_TwelveWIntDLine;

//UTC-11:00)协调世界时-11; lcq 3.15
extern  CString g_sLangID_State_UTC_ElevenCUTime;
extern  CString g_sLangTxt_State_UTC_ElevenCUTime;

//"(UTC-10:00)阿留申群岛"; lcq 3.15
extern  CString g_sLangID_State_UTC_TenAleutianIslands;
extern  CString g_sLangTxt_State_UTC_TenAleutianIslands;

//(UTC-9:00)阿拉斯加; lcq 3.15
extern  CString g_sLangID_State_UTC_NineAlaska;
extern  CString g_sLangTxt_State_UTC_NineAlaska;

//("(UTC-8:00)太平洋时间(美国和加拿大)")); lcq 3.15
extern  CString g_sLangID_State_UTC_EUCPacificTime;
extern  CString g_sLangTxt_State_UTC_EUCPacificTime;

//("(UTC-7:00)奇瓦瓦,拉巴斯,马萨特兰")); lcq 3.15
extern  CString g_sLangID_State_UTC_SevenCLM;
extern  CString g_sLangTxt_State_UTC_SevenCLM;

//("(UTC-6:00)中美洲")); lcq 3.15
extern  CString g_sLangID_State_UTC_SixCentralAmerica;
extern  CString g_sLangTxt_State_UTC_SixCentralAmerica;

//("(UTC-5:00)东部时间(美国和加拿大)")); lcq 3.15
extern  CString g_sLangID_State_UTC_FiveUCEasternTime;
extern  CString g_sLangTxt_State_UTC_FiveUCEasternTime;

//("(UTC-4:00)大西洋时间(加拿大)")); lcq 3.15
extern  CString g_sLangID_State_UTC_FourCanadaAtlanticTime;
extern  CString g_sLangTxt_State_UTC_FourCanadaAtlanticTime;

//("(UTC-3:00)格陵兰")); lcq 3.15
extern  CString g_sLangID_State_UTC_ThreeGreenland;
extern  CString g_sLangTxt_State_UTC_ThreeGreenland;

//("(UTC-2:00)协调世界时-2")); lcq 3.15
extern  CString g_sLangID_State_UTC_TwoCooUniversalTime;
extern  CString g_sLangTxt_State_UTC_TwoCooUniversalTime;

//("(UTC-1:00)佛得角群岛,亚速尔群岛"));lcq 3.15
extern  CString g_sLangID_State_UTC_OneCapIslandsAzores;
extern  CString g_sLangTxt_State_UTC_OneCapIslandsAzores;

//("(UTC)都柏林,爱丁堡,里斯本,伦敦")); lcq 3.15
extern  CString g_sLangID_State_UTC_DubEdinhLisLon;
extern  CString g_sLangTxt_State_UTC_DubEdinhLisLon;

//("(UTC+1:00)布鲁塞尔,哥本哈根,马德里,巴黎,中非西部")); lcq 3.15
extern  CString g_sLangID_State_UTC_POneBCMPWAfrica;
extern  CString g_sLangTxt_State_UTC_POneBCMPWAfrica;

//("(UTC+2:00)开罗,雅典,耶路撒冷")); lcq 3.15
extern  CString g_sLangID_State_UTC_PTwoCAJerusalem;
extern  CString g_sLangTxt_State_UTC_PTwoCAJerusalem;

//("(UTC+3:00)巴格达,科威特,莫斯科,圣彼得比")); lcq 3.15
extern  CString g_sLangID_State_UTC_PThreeBKMPeterby;
extern  CString g_sLangTxt_State_UTC_PThreeBKMPeterby;

//("(UTC+4:00)阿布扎比,巴库")); lcq 3.15
extern  CString g_sLangID_State_UTC_PFourAbuDhabiBaku;
extern  CString g_sLangTxt_State_UTC_PFourAbuDhabiBaku;

//("(UTC+5:00)伊斯兰堡,卡拉奇")); lcq 3.15
extern  CString g_sLangID_State_UTC_PFiveIslamabadKarachi;
extern  CString g_sLangTxt_State_UTC_PFiveIslamabadKarachi;

//("(UTC+6:00)阿斯塔纳")); lcq 3.15
extern  CString g_sLangID_State_UTC_PSixAstana;
extern  CString g_sLangTxt_State_UTC_PSixAstana;

//("(UTC+7:00)曼谷,河内,雅加达")); lcq 3.15
extern  CString g_sLangID_State_UTC_PSevenBHJakarta;
extern  CString g_sLangTxt_State_UTC_PSevenBHJakarta;

//("(UTC+8:00)北京,重庆,香港,乌鲁木齐")); lcq 3.15
extern  CString g_sLangID_State_UTC_PEightBCHUrumqi;
extern  CString g_sLangTxt_State_UTC_PEightBCHUrumqi;

//("(UTC+9:00)东京,首尔,平壤")); lcq 3.15
extern  CString g_sLangID_State_UTC_PNineTSPyongyang;
extern  CString g_sLangTxt_State_UTC_PNineTSPyongyang;

//("(UTC+10:00)堪培拉,墨尔本,悉尼")); lcq 3.15
extern  CString g_sLangID_State_UTC_PTenCMSydney;
extern  CString g_sLangTxt_State_UTC_PTenCMSydney;

//("(UTC+11:00)所罗门群岛,新喀里多尼亚")); lcq 3.15
extern  CString g_sLangID_State_UTC_PSINCaledonia;
extern  CString g_sLangTxt_State_UTC_PSINCaledonia;

//("(UTC+12:00)斐济")); lcq 3.15
extern  CString g_sLangID_State_UTC_PTwelveFiji;
extern  CString g_sLangTxt_State_UTC_PTwelveFiji;

extern CString g_sLangID_Gradient_VarType;
extern CString g_sLangTxt_Gradient_VarType;
extern CString g_sLangID_Gradient_Phase;
extern CString g_sLangTxt_Gradient_Phase;
extern CString g_sLangID_Gradient_VarSet;
extern CString g_sLangTxt_Gradient_VarSet;
extern CString g_sLangID_Gradient_ChangingSet;
extern CString g_sLangTxt_Gradient_ChangingSet;
extern CString g_sLangID_Gradient_UnChangingSet;
extern CString g_sLangTxt_Gradient_UnChangingSet;
extern CString g_sLangID_Gradient_OtherSet;
extern CString g_sLangTxt_Gradient_OtherSet;
extern CString g_sLangID_Gradient_TestResult;
extern CString g_sLangTxt_Gradient_TestResult;
extern CString g_sLangID_Gradient_Init;
extern CString g_sLangTxt_Gradient_Init;
extern CString g_sLangID_Gradient_Finish;
extern CString g_sLangTxt_Gradient_Finish;
extern CString g_sLangID_Gradient_Step;
extern CString g_sLangTxt_Gradient_Step;
extern CString g_sLangID_Gradient_Time;
extern CString g_sLangTxt_Gradient_Time;
extern CString g_sLangID_Gradient_Direction;
extern CString g_sLangTxt_Gradient_Direction;
extern CString g_sLangID_Gradient_MaxAngle;
extern CString g_sLangTxt_Gradient_MaxAngle;
extern CString g_sLangID_Gradient_Clockwise;
extern CString g_sLangTxt_Gradient_Clockwise;
extern CString g_sLangID_Gradient_Anticlockwise;
extern CString g_sLangTxt_Gradient_Anticlockwise;
extern CString g_sLangID_Gradient_AllFreq;
extern CString g_sLangTxt_Gradient_AllFreq;
extern CString g_sLangID_Gradient_TimeBeforeChange;
extern CString g_sLangTxt_Gradient_TimeBeforeChange;
extern CString g_sLangID_Gradient_TimeBeforeFail;
extern CString g_sLangTxt_Gradient_TimeBeforeFail;
extern CString g_sLangID_Gradient_CurBeforeChange;
extern CString g_sLangTxt_Gradient_CurBeforeChange;
extern CString g_sLangID_Gradient_Normal;
extern CString g_sLangTxt_Gradient_Normal;
extern CString g_sLangID_Gradient_Failure;
extern CString g_sLangTxt_Gradient_Failure;
extern CString g_sLangID_Gradient_ParaSet;
extern CString g_sLangTxt_Gradient_ParaSet;
//总计只能选择%d次谐波，假如想选择当前次谐波，需要取消勾选一行.
extern CString g_sLangID_Gradient_Intotalcheckarow;
extern CString g_sLangTxt_Gradient_Intotalcheckarow;

//当前电流组数为(%ld),至少需要2组电流才能进行差流计算. lcq 3.13
extern CString g_sLangID_Gradient_CurbanksatleastTwo;
extern CString g_sLangTxt_Gradient_CurbanksatleastTwo;

//当前选择的递变通道(Index=%d)未查找到.lcq 3.13
extern CString g_sLangID_Gradient_CurselinNotFound;
extern CString g_sLangTxt_Gradient_CurselinNotFound;

//当前为直流输出模式,不可切换为频率递变.lcq 3.13
extern CString g_sLangID_Gradient_CurinDCincrement;
extern CString g_sLangTxt_Gradient_CurinDCincrement;

//备注:规程要求测试时间1分钟，最大对时误差不大于1μs. lcq 3.13
extern CString g_sLangID_Gradient_NoteThepthanoneus;
extern CString g_sLangTxt_Gradient_NoteThepthanoneus;

//备注:规程要求测试时间10分钟，最大守时误差不大于4μs. lcq 3.13
extern CString g_sLangID_Gradient_NoteThepthanfourus;
extern CString g_sLangTxt_Gradient_NoteThepthanfourus;

//无PPS模式下,需要先进行报文探测,选择对应采样值控制块. lcq 3.14
extern CString g_sLangID_Gradient_InPPSfreemodevaluecontrolblock;
extern CString g_sLangTxt_Gradient_InPPSfreemodevaluecontrolblock;

//当前状态(%d)的GOOSE发布数据为空(出现异常).lcq 3.14
extern CString g_sLangID_Gradient_GOOSEreleaseDataStatusIsempty;
extern CString g_sLangTxt_Gradient_GOOSEreleaseDataStatusIsempty;

//至少保留一个状态.lcq 3.14
extern CString g_sLangID_Gradient_MaintainatLeastOneState;
extern CString g_sLangTxt_Gradient_MaintainatLeastOneState;

//"总计只能选择%d次谐波，假如想选择当前次谐波，需要取消勾选一行."  lcq 3.14
extern CString g_sLangID_Gradient_Intotalharmonicuncheckarow;
extern CString g_sLangTxt_Gradient_Intotalharmonicuncheckarow;

//调试使用的配置文件(%s)不存在. lcq 3.14
extern CString g_sLangID_Gradient_TheUsedfordebuggingNOexist;
extern CString g_sLangTxt_Gradient_TheUsedfordebuggingNOexist;

//解析功能测试参数文件【%s】失败  lcq 3.14
extern CString g_sLangID_Gradient_FailedTestParameterfile;
extern CString g_sLangTxt_Gradient_FailedTestParameterfile;

//创建文件夹 lcq 3.14
extern CString g_sLangID_Gradient_CreateFolder;
extern CString g_sLangTxt_Gradient_CreateFolder;

//文件夹创建失败！ Folder creation failed! lcq 3.14
extern CString g_sLangID_Gradient_FolderCreationFailed;
extern CString g_sLangTxt_Gradient_FolderCreationFailed;

//添加试验 lcq 3.14
extern CString g_sLangID_Gradient_AddExperiment;
extern CString g_sLangTxt_Gradient_AddExperiment;
 
//缺少硬件资源文件,无法创建缺省通道映射.  lcq 3.14
extern CString g_sLangID_Gradient_MissingDefaultMappings;
extern CString g_sLangTxt_Gradient_MissingDefaultMappings;

//"创建通道映射缺省路径失败."  lcq 3.14
extern CString g_sLangID_Gradient_FailDefaultPath;
extern CString g_sLangTxt_Gradient_FailDefaultPath;

//导出通道映射文件[%s]成功.  lcq 3.14
extern CString g_sLangID_Gradient_ExportfileSucceeded;
extern CString g_sLangTxt_Gradient_ExportfileSucceeded;
 
//导出通道映射文件[%s]失败. lcq 3.14
extern CString g_sLangID_Gradient_Failedtofile;
extern CString g_sLangTxt_Gradient_Failedtofile;

//测试仪硬件信息文件加载失败. lcq 3.15
extern CString g_sLangID_Gradient_TheTesterfileFailedtoload;
extern CString g_sLangTxt_Gradient_TheTesterfileFailedtoload;

//未知的网页报告执行命令(%s). lcq 3.20
extern CString g_sLangID_Gradient_UnknownCommand;
extern CString g_sLangTxt_Gradient_UnknownCommand;

//功能测试参数文件【%s】不存在 lcq 3.20 
extern CString g_sLangID_Gradient_Functionalfiledtexist;
extern CString g_sLangTxt_Gradient_Functionalfiledtexist;

//"反选" lcq 7.06
extern CString g_sLangID_Gradient_Inverse;
extern CString g_sLangTxt_Gradient_Inverse;

//"电压动作值(V)" lcq 7.06 
extern CString g_sLangID_Gradient_VActionValue;
extern CString g_sLangTxt_Gradient_VActionValue;
//"电流动作值(A)" lcq 7.06 
extern CString g_sLangID_Gradient_CActionValue;
extern CString g_sLangTxt_Gradient_CActionValue;
//"返回系数" lcq 7.06 
extern CString g_sLangID_Gradient_ReCoefficient;
extern CString g_sLangTxt_Gradient_ReCoefficient;
//"边界角1(°)" lcq 7.06 
extern CString g_sLangID_Gradient_FirBoundAngle ;
extern CString g_sLangTxt_Gradient_FirBoundAngle;
//"边界角2(°)" lcq 7.06
extern CString g_sLangID_Gradient_SecBoundAngle;
extern CString g_sLangTxt_Gradient_SecBoundAngle;
//"最大灵敏角(°)" lcq 7.06 
extern CString g_sLangID_Gradient_MaxSenAngle;
extern CString g_sLangTxt_Gradient_MaxSenAngle;
//"动作频率(Hz)" lcq 7.06  
extern CString g_sLangID_Gradient_FreAction;
extern CString g_sLangTxt_Gradient_FreAction;
//"相位动作值(°)" lcq 7.06 
extern CString g_sLangID_Gradient_PhaseAValue;
extern CString g_sLangTxt_Gradient_PhaseAValue;
//"阻抗动作值(Ω)"
extern CString g_sLangID_Gradient_ImpAValue;
extern CString g_sLangTxt_Gradient_ImpAValue;
//测试教学 lcq
extern CString g_sLangID_Gradient_TestTeach;
extern CString g_sLangTxt_Gradient_TestTeach;
//报告头信息  lcq
extern CString g_sLangID_Gradient_ReportHeader;
extern CString g_sLangTxt_Gradient_ReportHeader;
//"下发保存测试模板(%s%s)命令成功." lcq         
extern CString g_sLangID_Gradient_TestTempSusCom;
extern CString g_sLangTxt_Gradient_TestTempSusCom;
//"下发保存测试模板(%s%s)命令失败." lcq         
extern CString g_sLangID_Gradient_TestTempDefCom;
extern CString g_sLangTxt_Gradient_TestTempDefCom;
//"保存网页模板文件(%s%s)成功."    lcq             
extern CString g_sLangID_Gradient_SavePageSus;
extern CString g_sLangTxt_Gradient_SavePageSus;
//"下发保存测试记录(%s%s)命令成功." lcq          
extern CString g_sLangID_Gradient_TestRecordSus;
extern CString g_sLangTxt_Gradient_TestRecordSus;
//"下发保存测试记录(%s%s)命令失败."  lcq             
extern CString g_sLangID_Gradient_TestRecordFai;
extern CString g_sLangTxt_Gradient_TestRecordFai;
//"保存报告文件(%s%s)成功." lcq                    
extern CString g_sLangID_Gradient_SaveReportSus;
extern CString g_sLangTxt_Gradient_SaveReportSus;
//"路径(%s)下存在同名的文件,请修改文件名."  lcq
extern CString g_sLangID_Gradient_SameeXist; 
extern CString g_sLangTxt_Gradient_SameeXist;

//模块类型 Module type  lcq
extern CString g_sLangID_Gradient_ModuleType;  
extern CString g_sLangTxt_Gradient_ModuleType;
//位置号 Location number  lcq
extern CString g_sLangID_Gradient_LocNumber; 
extern CString g_sLangTxt_Gradient_LocNumber;
//模块版本 Module version  lcq
extern CString g_sLangID_Gradient_ModuleVersion; 
extern CString g_sLangTxt_Gradient_ModuleVersion;
 //生产日期 Date of manufacture lcq
extern CString g_sLangID_Gradient_ManufactDate; 
extern CString g_sLangTxt_Gradient_ManufactDate;

// 仪器名称 lcq
// extern CString g_sLangID_Gradient_InstrumentName; 
// extern CString g_sLangTxt_Gradient_InstrumentName;
// 主板版本 lcq
// extern CString g_sLangID_Gradient_BoardVersion; 
// extern CString g_sLangTxt_Gradient_BoardVersion;
// 驱动版本 lcq
// extern CString g_sLangID_Gradient_DriverVersion; 
// extern CString g_sLangTxt_Gradient_DriverVersion;
// TestServer版本 lcq
// extern CString g_sLangID_Gradient_TestSVersion; 
// extern CString g_sLangTxt_Gradient_TestSVersion;
// Linux生成日期 lcq
// extern CString g_sLangID_Gradient_LinuxBDate; 
// extern CString g_sLangTxt_Gradient_LinuxBDate;
// 主板开入数量（个） lcq
// extern CString g_sLangID_Gradient_MboardsNumIn; 
// extern CString g_sLangTxt_Gradient_MboardsNumIn;
// 主板开出数量（个） lcq
// extern CString g_sLangID_Gradient_MboardsNumOut; 
// extern CString g_sLangTxt_Gradient_MboardsNumOut;
// 模拟量绝对相位补偿(度) lcq
// extern CString g_sLangID_Gradient_AAcompensation;  
// extern CString g_sLangTxt_Gradient_AAcompensation;
// 状态序列容量 lcq
// extern CString g_sLangID_Gradient_SsCapacity; 
// extern CString g_sLangTxt_Gradient_SsCapacity;
// TestServer名称 lcq
// extern CString g_sLangID_Gradient_TestSName; 
// extern CString g_sLangTxt_Gradient_TestSName;
// 驱动名称 lcq
// extern CString g_sLangID_Gradient_DriverName; 
// extern CString g_sLangTxt_Gradient_DriverName;
//"模块位置" lcq
// extern CString g_sLangID_Gradient_ModLocation; 
// extern CString g_sLangTxt_Gradient_ModLocation;
// //"谐波数" lcq
// extern CString g_sLangID_Gradient_HarmonicsNum; 
// extern CString g_sLangTxt_Gradient_HarmonicsNum;
// //"直流电压通道最大值" lcq
// extern CString g_sLangID_Gradient_DCVolChaMax; 
// extern CString g_sLangTxt_Gradient_DCVolChaMax;
// //"直流电流通道最大值" lcq
// extern CString g_sLangID_Gradient_DCCurChaMax; 
// extern CString g_sLangTxt_Gradient_DCCurChaMax;
// //"通道出交流最大值"  lcq
// extern CString g_sLangID_Gradient_ACChanMax; 
// extern CString g_sLangTxt_Gradient_ACChanMax;
// //"通道出直流最大值" lcq
// extern CString g_sLangID_Gradient_DCChanMax; 
// extern CString g_sLangTxt_Gradient_DCChanMax;
// //"频率补偿系数" lcq
// extern CString g_sLangID_Gradient_FreComFactor; 
// extern CString g_sLangTxt_Gradient_FreComFactor;
// //"数字硬件相位延时" lcq
// extern CString g_sLangID_Gradient_DigDeLHardware; 
// extern CString g_sLangTxt_Gradient_DigDeLHardware;
// //"电压电流硬件特性" Voltage and current hardware characteristics
// extern CString g_sLangID_Gradient_VCHardware; 
// extern CString g_sLangTxt_Gradient_VCHardware;
// //"电流通道合并模式" Current channel coalescing mode
// extern CString g_sLangID_Gradient_CCcoalescing; 
// extern CString g_sLangTxt_Gradient_CCcoalescing;
// //"第一组开关量配为开入" The first set of switches is configured for opening
// extern CString g_sLangID_Gradient_FirSwitchoPen; 
// extern CString g_sLangTxt_Gradient_FirSwitchoPen;
// //"第二组开关量配为开入" The second set of switches is configured as an inlet
// extern CString g_sLangID_Gradient_SecSwitchoPen; 
// extern CString g_sLangTxt_Gradient_SecSwitchoPen;
// //"第三组开关量配为开入" The third set of switches is configured for opening
// extern CString g_sLangID_Gradient_ThirSwitchoPen; 
// extern CString g_sLangTxt_Gradient_ThirSwitchoPen;
// //"第四组开关量配为开入" The fourth set of switches is configured for opening
// extern CString g_sLangID_Gradient_FourSwitchoPen; 
// extern CString g_sLangTxt_Gradient_FourSwitchoPen;
// //"模块FPGA版本" Module FPGA version
// extern CString g_sLangID_Gradient_FPGAVersion; 
// extern CString g_sLangTxt_Gradient_FPGAVersion;
// //"模块属性版本" Module property version
// extern CString g_sLangID_Gradient_ModproVersion; 
// extern CString g_sLangTxt_Gradient_ModproVersion;
// //"北京博电新力电气股份有限公司" 
// extern CString g_sLangID_Gradient_BodianEleCor; 
// extern CString g_sLangTxt_Gradient_BodianEleCor;



// SCD文件
// extern CString g_sLangID_Gradient_SCDfile; 
// extern CString g_sLangTxt_Gradient_SCDfile;
// 模板文件 Template file
// extern CString g_sLangID_Gradient_TemplateFile; 
// extern CString g_sLangTxt_Gradient_TemplateFile;
// 截屏文件夹 Screenshots folder
// extern CString g_sLangID_Gradient_ScreenFolder; 
// extern CString g_sLangTxt_Gradient_ScreenFolder;
// "保存截屏图片" Save the screencast
// extern CString g_sLangID_Gradient_SaveCast; 
// extern CString g_sLangTxt_Gradient_SaveCast;
// "其他类型文件"  Other types of files
// extern CString g_sLangID_Gradient_OtherTypeFile; 
// extern CString g_sLangTxt_Gradient_OtherTypeFile;




//"截屏成功."   lcq
extern CString g_sLangID_Gradient_ShotScreenSus; 
extern CString g_sLangTxt_Gradient_ShotScreenSus;
//本地网卡IP lcq
extern CString g_sLangID_Gradient_LocalNICIP;
extern CString g_sLangTxt_Gradient_LocalNICIP;
//主IP地址：  lcq
extern CString g_sLangID_Gradient_PrimaryIP;
extern CString g_sLangTxt_Gradient_PrimaryIP;
//"电流档位设置:"  lcq
extern CString g_sLangID_Gradient_CurGSetting;
extern CString g_sLangTxt_Gradient_CurGSetting;
//"大电流输出端口:"  lcq
extern CString g_sLangID_Gradient_HighCurPort;
extern CString g_sLangTxt_Gradient_HighCurPort;
//"1档(0.2Ω/10A)" lcq
extern CString g_sLangID_Gradient_FirstFile;
extern CString g_sLangTxt_Gradient_FirstFile;
//"2档(0.3Ω/10A)" lcq
extern CString g_sLangID_Gradient_SecondFile;
extern CString g_sLangTxt_Gradient_SecondFile;
//"3档(0.7Ω/10A)" lcq
extern CString g_sLangID_Gradient_ThirdFile;
extern CString g_sLangTxt_Gradient_ThirdFile;
//"IEC配置" lcq
extern CString g_sLangID_Gradient_IECConfiguration;
extern CString g_sLangTxt_Gradient_IECConfiguration;
//"报文类型" lcq
extern CString g_sLangID_Gradient_MessageType;
extern CString g_sLangTxt_Gradient_MessageType;
//SCL解析界面  lcq
extern CString g_sLangID_Gradient_SCLPars;
extern CString g_sLangTxt_Gradient_SCLPars;
//电压设置 lcq
extern CString g_sLangID_Gradient_VoltageSet;
extern CString g_sLangTxt_Gradient_VoltageSet;
//电流设置 lcq
extern CString g_sLangID_Gradient_CurrentSet;
extern CString g_sLangTxt_Gradient_CurrentSet;
//"获取文件路径失败(%s)." 
extern CString g_sLangID_Gradient_FailedGfp;
extern CString g_sLangTxt_Gradient_FailedGfp;
//"打开文件失败(%s).
extern CString g_sLangID_Gradient_FailedTof;
extern CString g_sLangTxt_Gradient_FailedTof;
//"[%s]创建写文件失败." 
extern CString g_sLangID_Gradient_FailedCwf;
extern CString g_sLangTxt_Gradient_FailedCwf;
//"文件[%s]大小为(%ld)." 
extern CString g_sLangID_Gradient_FileIsize;
extern CString g_sLangTxt_Gradient_FileIsize;
//"读取指定长度的大文件内容失败." 
extern CString g_sLangID_Gradient_FailedTRlfile;
extern CString g_sLangTxt_Gradient_FailedTRlfile;
//"文件[%s]大小为(%ld)." 
extern CString g_sLangID_Gradient_FileIsize;
extern CString g_sLangTxt_Gradient_FileIsize;
//"文件不存在(%s)." 
extern CString g_sLangID_Gradient_FileNoexist;
extern CString g_sLangTxt_Gradient_FileNoexist;
//频率动作值(Hz) 
extern CString g_sLangID_Gradient_FreAValue;
extern CString g_sLangTxt_Gradient_FreAValue;
//"FT3发布" 
extern CString g_sLangID_Gradient_ReleasedFTT;
extern CString g_sLangTxt_Gradient_ReleasedFTT;
//"当前SMVFT3通道映射出错(%s).
extern CString g_sLangID_Gradient_CurSmvErr;
extern CString g_sLangTxt_Gradient_CurSmvErr;
//"外部IED描述" 
extern CString g_sLangID_Gradient_ExIEDdescrip;
extern CString g_sLangTxt_Gradient_ExIEDdescrip;
//"解析文件(" 
extern CString g_sLangID_Gradient_ParseLFile;
extern CString g_sLangTxt_Gradient_ParseLFile;
//")不存在,无法进行SCL选择切换.
extern CString g_sLangID_Gradient_SCLNoSel;
extern CString g_sLangTxt_Gradient_SCLNoSel;
//"当前表格数据链表无父对象,删除当前行数据失败,存在内存泄漏风险."
extern CString g_sLangID_Gradient_NoParObjRisk;
extern CString g_sLangTxt_Gradient_NoParObjRisk;
//"故障类型"
extern CString g_sLangID_Gradient_FailType;
extern CString g_sLangTxt_Gradient_FailType;
//"故障方向"
extern CString g_sLangID_Gradient_FailDirect;
extern CString g_sLangTxt_Gradient_FailDirect;
//"故障时间"
extern CString g_sLangID_Gradient_FailTime;
extern CString g_sLangTxt_Gradient_FailTime;
//"斜率"
extern CString g_sLangID_Gradient_Slope;
extern CString g_sLangTxt_Gradient_Slope;
//"启动门槛"  
extern CString g_sLangID_Gradient_StartTs;
extern CString g_sLangTxt_Gradient_StartTs;
//"启动电流"
extern CString g_sLangID_Gradient_StartCur;
extern CString g_sLangTxt_Gradient_StartCur;
//拐点
extern CString g_sLangID_Gradient_Inflectp;
extern CString g_sLangTxt_Gradient_Inflectp;
//"差流极值" 
extern CString g_sLangID_Gradient_DiffFlowEx;
extern CString g_sLangTxt_Gradient_DiffFlowEx;
//"添加自定义点" 
extern CString g_sLangID_Gradient_AddCusp;
extern CString g_sLangTxt_Gradient_AddCusp;
//清空自定义点 
extern CString g_sLangID_Gradient_Emptycusp;
extern CString g_sLangTxt_Gradient_Emptycusp;
//"差流极值设置不能小于拐点电流对应差流值."
extern CString g_sLangID_Gradient_NoLessCor;
extern CString g_sLangTxt_Gradient_NoLessCor;
//比率差动 
extern CString g_sLangID_Gradient_RatioDiff;
extern CString g_sLangTxt_Gradient_RatioDiff;
//"自定义测试点" 
extern CString g_sLangID_Gradient_Custestp;
extern CString g_sLangTxt_Gradient_Custestp;
//阻抗表达方式 
extern CString g_sLangID_Gradient_Impedance;
extern CString g_sLangTxt_Gradient_Impedance;
//请先选择需要删除的特性曲线 
extern CString g_sLangID_Gradient_SelectCur;
extern CString g_sLangTxt_Gradient_SelectCur;
//"曲线编辑" 
extern CString g_sLangID_Gradient_CurveEditing;
extern CString g_sLangTxt_Gradient_CurveEditing;
//"插入元素"
extern CString g_sLangID_Gradient_InsertElement;
extern CString g_sLangTxt_Gradient_InsertElement;
//"修改元素"
extern CString g_sLangID_Gradient_ModifyElement;
extern CString g_sLangTxt_Gradient_ModifyElement;
//"删除元素"
extern CString g_sLangID_Gradient_DeleteElement;
extern CString g_sLangTxt_Gradient_DeleteElement;
//"+:初始"
extern CString g_sLangID_Gradient_PInitial;
extern CString g_sLangTxt_Gradient_PInitial;
//"+:选中"
extern CString g_sLangID_Gradient_PSelected;
extern CString g_sLangTxt_Gradient_PSelected;
//"+:试验结束"
extern CString g_sLangID_Gradient_EndTrial;
extern CString g_sLangTxt_Gradient_EndTrial;
//"特性曲线查找失败(strCharaID=%s;strIndex=%s),无法更新曲线图"
extern CString g_sLangID_Gradient_UnUpdateGraph;
extern CString g_sLangTxt_Gradient_UnUpdateGraph;
//"Y/V接线平衡变压器" 
extern CString g_sLangID_Gradient_YNWirBlancer;
extern CString g_sLangTxt_Gradient_YNWirBlancer;
//"Y/△-11接线(无转角)" 
extern CString g_sLangID_Gradient_YNoCorners;
extern CString g_sLangTxt_Gradient_YNoCorners;
//"单相变压器"
extern CString g_sLangID_Gradient_Sphase;
extern CString g_sLangTxt_Gradient_Sphase;
//"Y/△/△接线"
extern CString g_sLangID_Gradient_YDSCornect;
extern CString g_sLangTxt_Gradient_YDSCornect;
//"Y/A 接线阻抗匹配平衡变压器" 
extern CString g_sLangID_Gradient_ImpedanceMB;
extern CString g_sLangTxt_Gradient_ImpedanceMB;
//"三相V/V接线变压器" 
extern CString g_sLangID_Gradient_ThrVWirceTF;
extern CString g_sLangTxt_Gradient_ThrVWirceTF;
//"三相V/V接线变压器2"
extern CString g_sLangID_Gradient_SecThrVWirceTF;
extern CString g_sLangTxt_Gradient_SecThrVWirceTF;
//"Y/△-11接线(Y侧转角)"
extern CString g_sLangID_Gradient_YSideCorner;
extern CString g_sLangTxt_Gradient_YSideCorner;
//"三相V/V" 
extern CString g_sLangID_Gradient_VThrPhase;
extern CString g_sLangTxt_Gradient_VThrPhase;
//"基准电流(Ie)"
extern CString g_sLangID_Gradient_IRCurrent;
extern CString g_sLangTxt_Gradient_IRCurrent;
//"基准电流(A)"
extern CString g_sLangID_Gradient_ARCurrent;
extern CString g_sLangTxt_Gradient_ARCurrent;
//"动作时间" 
extern CString g_sLangID_Gradient_ActionTime;
extern CString g_sLangTxt_Gradient_ActionTime;
//" 跳  A "
extern CString g_sLangID_Gradient_JumpA;
extern CString g_sLangTxt_Gradient_JumpA;
//" 跳  B "
extern CString g_sLangID_Gradient_JumpB;
extern CString g_sLangTxt_Gradient_JumpB;
//" 跳  C "
extern CString g_sLangID_Gradient_JumpC;
extern CString g_sLangTxt_Gradient_JumpC;
//跳
extern CString g_sLangID_Gradient_Jjump;
extern CString g_sLangTxt_Gradient_Jjump;
//"当前相位值越限出错(%f)." 
extern CString g_sLangID_Gradient_CurPhaseErr;
extern CString g_sLangTxt_Gradient_CurPhaseErr;
//"设置"
extern CString g_sLangID_Gradient_Setting;
extern CString g_sLangTxt_Gradient_Setting;
//"当前FT3通道映射出错(%s)." 
extern CString g_sLangID_Gradient_FT3CurChanErr;
extern CString g_sLangTxt_Gradient_FT3CurChanErr;
//"光功率" 
extern CString g_sLangID_Gradient_OpticalPower;
extern CString g_sLangTxt_Gradient_OpticalPower;
//"光口%d" 
extern CString g_sLangID_Gradient_POpticalPort;
extern CString g_sLangTxt_Gradient_POpticalPort;
//"光功率(-dbm)"
extern CString g_sLangID_Gradient_FOpticalPower;
extern CString g_sLangTxt_Gradient_FOpticalPower;
//"文件名称："
extern CString g_sLangID_Gradient_FmFileName;
extern CString g_sLangTxt_Gradient_FmFileName;
//"文件目录："
extern CString g_sLangID_Gradient_DirectoryFile;
extern CString g_sLangTxt_Gradient_DirectoryFile;
//"辅助IP设置" 
extern CString g_sLangID_Gradient_SecondaryIPSet;
extern CString g_sLangTxt_Gradient_SecondaryIPSet;
//"IP输入不合法" 
extern CString g_sLangID_Gradient_IPInputInvalid;
extern CString g_sLangTxt_Gradient_IPInputInvalid;
//"一次值(V/A)"
extern CString g_sLangID_Gradient_VAOnceValue;
extern CString g_sLangTxt_Gradient_VAOnceValue;
//"二次值(V/A)"
extern CString g_sLangID_Gradient_VATwiceValue;
extern CString g_sLangTxt_Gradient_VATwiceValue;
//"三相相同"
extern CString g_sLangID_Gradient_SameThreep;
extern CString g_sLangTxt_Gradient_SameThreep;
//"全部相同"
extern CString g_sLangID_Gradient_AllSamep;
extern CString g_sLangTxt_Gradient_AllSamep;
//"相位(°)" 
extern CString g_sLangID_Gradient_DPhase;
extern CString g_sLangTxt_Gradient_DPhase;
//"当前状态(%d)的FT3发布数据为空(出现异常)."
extern CString g_sLangID_Gradient_FRelCurempty;
extern CString g_sLangTxt_Gradient_FRelCurempty;
//"当前测试项为空."
extern CString g_sLangID_Gradient_EmptyCurTI;
extern CString g_sLangTxt_Gradient_EmptyCurTI;
//"请先关闭网页界面,才能执行工具栏按钮功能."
extern CString g_sLangID_Gradient_ClosePerTBF;
extern CString g_sLangTxt_Gradient_ClosePerTBF;
//"等待测试服务停止后关闭."
extern CString g_sLangID_Gradient_WaitSASD;
extern CString g_sLangTxt_Gradient_WaitSASD;
//"保存截屏(%s)(isNull)失败."
extern CString g_sLangID_Gradient_INUnSavescreen;
extern CString g_sLangTxt_Gradient_INUnSavescreen;
//"保存截屏(%s)(save)失败."
extern CString g_sLangID_Gradient_UnSavescreen;
extern CString g_sLangTxt_Gradient_UnSavescreen;
//保存截屏(%s)成功.
extern CString g_sLangID_Gradient_Savescreen;
extern CString g_sLangTxt_Gradient_Savescreen;
//"请在测试项目树形控件中选择合法的项目分类"
extern CString g_sLangID_Gradient_Selectleg;
extern CString g_sLangTxt_Gradient_Selectleg;
//"?????????????? OnCmd_NewTest: 关闭打开的测试功能页面，并弹框提示是否保存修改 ???????????"
extern CString g_sLangID_Gradient_CLoseMMChanges;
extern CString g_sLangTxt_Gradient_CLoseMMChanges;
//"模板错误！找不到rootnode节点对应的功能界面【%s】"
extern CString g_sLangID_Gradient_TemplateErr;
extern CString g_sLangTxt_Gradient_TemplateErr;
//"模板另存为"
extern CString g_sLangID_Gradient_SaveTemplateAs;
extern CString g_sLangTxt_Gradient_SaveTemplateAs;


//"打开文件失败"
extern CString g_sLangID_Gradient_OpenfileFail;
extern CString g_sLangTxt_Gradient_OpenfileFail;
//"发送完成"
extern CString g_sLangID_Gradient_SendComplete;
extern CString g_sLangTxt_Gradient_SendComplete;
//"接收通道设置"
extern CString g_sLangID_Gradient_RecvChannel;
extern CString g_sLangTxt_Gradient_RecvChannel;
//"PT/CT变比"
extern CString g_sLangID_Gradient_RatioPCT;
extern CString g_sLangTxt_Gradient_RatioPCT;
//"请选择控制块"
extern CString g_sLangID_Gradient_ControlB;
extern CString g_sLangTxt_Gradient_ControlB;
//"接收通道"
extern CString g_sLangID_Gradient_RecvChannnel;
extern CString g_sLangTxt_Gradient_RecvChannnel;
//"响应时间误差"
extern CString g_sLangID_Gradient_ResTimeErr;
extern CString g_sLangTxt_Gradient_ResTimeErr;
//"报文响应时间"
extern CString g_sLangID_Gradient_MessResTime;
extern CString g_sLangTxt_Gradient_MessResTime;
//通道延时 Channel Delay
extern CString g_sLangID_Gradient_ChaDelay;
extern CString g_sLangTxt_Gradient_ChaDelay;
//"合并单元测试功能ID()在配置文件中未查找到."
extern CString g_sLangID_Gradient_MergeUint;
extern CString g_sLangTxt_Gradient_MergeUint;
//"当前选择测试功能异常(%s),导致m_pSttIecRcdFuncInterface==NULL."
extern CString g_sLangID_Gradient_NAbnormalRes;
extern CString g_sLangTxt_Gradient_NAbnormalRes;
//"测试时长(s):"
extern CString g_sLangID_Gradient_TestDuration;
extern CString g_sLangTxt_Gradient_TestDuration;
//"当前延时数据为空,清空时间精度结果失败."
extern CString g_sLangID_Gradient_TheCurDelay;
extern CString g_sLangTxt_Gradient_TheCurDelay;
//"清空时间精度结果成功."
extern CString g_sLangID_Gradient_EmptyRes;
extern CString g_sLangTxt_Gradient_EmptyRes;
//"比差(%)"
extern CString g_sLangID_Gradient_DiffRatio;
extern CString g_sLangTxt_Gradient_DiffRatio;
//"当前数据集为空,清空误差统计结果失败."
extern CString g_sLangID_Gradient_CurNullFa;
extern CString g_sLangTxt_Gradient_CurNullFa;
//"零漂"
extern CString g_sLangID_Gradient_ZeroDrift;
extern CString g_sLangTxt_Gradient_ZeroDrift;
//"输出值"
extern CString g_sLangID_Gradient_ValueOutP;
extern CString g_sLangTxt_Gradient_ValueOutP;
//"输出相位"
extern CString g_sLangID_Gradient_PhaseOutP;
extern CString g_sLangTxt_Gradient_PhaseOutP;
//"实测幅值"
extern CString g_sLangID_Gradient_MeasurAmp;
extern CString g_sLangTxt_Gradient_MeasurAmp;
//"通道延时"
extern CString g_sLangID_Gradient_ChanDelay;
extern CString g_sLangTxt_Gradient_ChanDelay;
//"复合误差" "Composite error"
extern CString g_sLangID_Gradient_CompError;
extern CString g_sLangTxt_Gradient_CompError;
//"实测相位" Measured phase
extern CString g_sLangID_Gradient_MeaPhase;
extern CString g_sLangTxt_Gradient_MeaPhase;
//"频差" "Frequency difference"
extern CString g_sLangID_Gradient_FrequencyDiff;
extern CString g_sLangTxt_Gradient_FrequencyDiff;
//"报文探测界面" Message Detection Interface
extern CString g_sLangID_Gradient_DetectMessageI;
extern CString g_sLangTxt_Gradient_DetectMessageI;
//"未录波"
extern CString g_sLangID_Gradient_Unrecorded;
extern CString g_sLangTxt_Gradient_Unrecorded;
//"GOOSE控制块(AppID=0X%04X),已添加订阅到光口%ld,无需重复添加."
extern CString g_sLangID_Gradient_Appscribed;
extern CString g_sLangTxt_Gradient_Appscribed;
//"GOOSE控制块(AppID=0X%04X),添加订阅到光口%ld成功."
extern CString g_sLangID_Gradient_SEcontrolSus;
extern CString g_sLangTxt_Gradient_SEcontrolSus;
//"GOOSE控制块(AppID=0X%04X),已添加发布到光口%ld,无需重复添加."
extern CString g_sLangID_Gradient_AppscribedFa;
extern CString g_sLangTxt_Gradient_AppscribedFa;
//"GOOSE控制块(AppID=0X%04X),添加发布到光口%ld成功."
extern CString g_sLangID_Gradient_AppFascribedFa;
extern CString g_sLangTxt_Gradient_AppFascribedFa;


//"修改接线提示" 
extern CString g_sLangID_Gradient_ModifyTip;
extern CString g_sLangTxt_Gradient_ModifyTip;
//接线提示
extern CString g_sLangID_Gradient_WiringTip;
extern CString g_sLangTxt_Gradient_WiringTip;
//新建接线提示
extern CString g_sLangID_Gradient_WirPrompt;
extern CString g_sLangTxt_Gradient_WirPrompt;
//"请在此处输入接线提示信息……" 
extern CString g_sLangID_Gradient_EnterTips;
extern CString g_sLangTxt_Gradient_EnterTips;
//"请按照接线提示信息，完成接线后，点击“完成接线”按钮，继续测试……"
extern CString g_sLangID_Gradient_ClickCTest;
extern CString g_sLangTxt_Gradient_ClickCTest;
//"完成接线"
extern CString g_sLangID_Gradient_CompleteWir;
extern CString g_sLangTxt_Gradient_CompleteWir;
//"存在相同名称的接线提示"
extern CString g_sLangID_Gradient_WirpromptExit;
extern CString g_sLangTxt_Gradient_WirpromptExit;
//"接线提示信息编辑，未检测到内容发生变化……"
extern CString g_sLangID_Gradient_WEditNoChange;
extern CString g_sLangTxt_Gradient_WEditNoChange;
//"错误的运行方式！"
extern CString g_sLangID_Gradient_WrongWayrun;
extern CString g_sLangTxt_Gradient_WrongWayrun;






extern CString g_sLangTxt_Gradient_ManufactDate;
extern CString g_sLangID_Report_TestChoose;
extern CString g_sLangTxt_Report_TestChoose;
extern CString g_sLangID_Report_TestObjInf;
extern CString g_sLangTxt_Report_TestObjInf;
extern CString g_sLangID_Report_SubInformation;
extern CString g_sLangTxt_Report_SubInformation;
extern CString g_sLangID_Report_SubName;
extern CString g_sLangTxt_Report_SubName;
extern CString g_sLangID_Report_SubAddr;
extern CString g_sLangTxt_Report_SubAddr;
extern CString g_sLangID_Report_LoopName;
extern CString g_sLangTxt_Report_LoopName;
extern CString g_sLangID_Report_LoopAddr;
extern CString g_sLangTxt_Report_LoopAddr;
extern CString g_sLangID_Report_Tester;
extern CString g_sLangTxt_Report_Tester;
extern CString g_sLangID_Report_ReportTitle;
extern CString g_sLangTxt_Report_ReportTitle;
extern CString g_sLangID_Report_DeviceInfor;
extern CString g_sLangTxt_Report_DeviceInfor;
extern CString g_sLangID_Report_DeviceName;
extern CString g_sLangTxt_Report_DeviceName;
extern CString g_sLangID_Report_DeviceModel;
extern CString g_sLangTxt_Report_DeviceModel;
extern CString g_sLangID_Report_DeviceAddr;
extern CString g_sLangTxt_Report_DeviceAddr;
extern CString g_sLangID_Report_DeviceFactory;
extern CString g_sLangTxt_Report_DeviceFactory;

extern CString g_sLangID_Report_SettingsNO;
extern CString g_sLangTxt_Report_SettingsNO;
extern CString g_sLangID_Report_AdditionalInf;
extern CString g_sLangTxt_Report_AdditionalInf;
extern CString g_sLangID_Report_RatedValue;
extern CString g_sLangTxt_Report_RatedValue;
extern CString g_sLangID_Report_DUTs;
extern CString g_sLangTxt_Report_DUTs;
extern CString g_sLangID_Report_Title;
extern CString g_sLangTxt_Report_Title;
extern CString g_sLangID_Report_Vnom;
extern CString g_sLangTxt_Report_Vnom;
extern CString g_sLangID_Report_Vdc;
extern CString g_sLangTxt_Report_Vdc;
extern CString g_sLangID_Report_SureTime;
extern CString g_sLangTxt_Report_SureTime;
extern CString g_sLangID_Report_AntiShakeTime;
extern CString g_sLangTxt_Report_AntiShakeTime;
extern CString g_sLangID_Report_Vprim;
extern CString g_sLangTxt_Report_Vprim;
extern CString g_sLangID_Report_Fnom;
extern CString g_sLangTxt_Report_Fnom;
extern CString g_sLangID_Report_Iprim;
extern CString g_sLangTxt_Report_Iprim;
extern CString g_sLangID_Report_TestAppInfor;
extern CString g_sLangTxt_Report_TestAppInfor;
extern CString g_sLangID_Report_AppModel;
extern CString g_sLangTxt_Report_AppModel;
extern CString g_sLangID_Report_Imax;
extern CString g_sLangTxt_Report_Imax;
extern CString g_sLangID_Report_AppSN;
extern CString g_sLangTxt_Report_AppSN;
extern CString g_sLangID_Report_TestStartTime;
extern CString g_sLangTxt_Report_TestStartTime;
extern CString g_sLangID_Report_ComPortType;
extern CString g_sLangTxt_Report_ComPortType;
extern CString g_sLangID_Report_TestEndTime;
extern CString g_sLangTxt_Report_TestEndTime;
extern CString g_sLangID_Report_Vmax;
extern CString g_sLangTxt_Report_Vmax;

extern CString g_sLangID_ChMaps_Analog;
extern CString g_sLangTxt_ChMaps_Analog;
extern CString g_sLangID_ChMaps_Digital;
extern CString g_sLangTxt_ChMaps_Digital;
extern CString g_sLangID_ChMaps_Week;
extern CString g_sLangTxt_ChMaps_Week;
extern CString g_sLangID_ChMaps_Title;
extern CString g_sLangTxt_ChMaps_Title;
extern CString g_sLangID_ChMaps_OutputSel;
extern CString g_sLangTxt_ChMaps_OutputSel;
extern CString g_sLangID_ChMaps_AnalogCh;
extern CString g_sLangTxt_ChMaps_AnalogCh;
extern CString g_sLangID_ChMaps_DigitalCh;
extern CString g_sLangTxt_ChMaps_DigitalCh;
extern CString g_sLangID_ChMaps_WeekCh;
extern CString g_sLangTxt_ChMaps_WeekCh;
extern CString g_sLangID_ChMaps_DigitalType;
extern CString g_sLangTxt_ChMaps_DigitalType;
extern CString g_sLangID_ChMaps_DefautMaps;
extern CString g_sLangTxt_ChMaps_DefautMaps;
extern CString g_sLangID_ChMaps_ImportChMaps;
extern CString g_sLangTxt_ChMaps_ImportChMaps;
extern CString g_sLangID_ChMaps_ExportChMaps;
extern CString g_sLangTxt_ChMaps_ExportChMaps;
extern CString g_sLangID_ChMaps_LockMaps;
extern CString g_sLangTxt_ChMaps_LockMaps;
extern CString g_sLangID_ChMaps_MeasSel;
extern CString g_sLangTxt_ChMaps_MeasSel;
extern CString g_sLangID_ChMaps_DigitalMeasType;
extern CString g_sLangTxt_ChMaps_DigitalMeasType;
extern CString g_sLangID_IEC_SysParasSet;
extern CString g_sLangTxt_IEC_SysParasSet;
extern CString g_sLangID_IEC_SysParasConfig;
extern CString g_sLangTxt_IEC_SysParasConfig;
extern CString g_sLangID_IEC_WeakSet;
extern CString g_sLangTxt_IEC_WeakSet;
extern CString g_sLangID_IEC_Message;
extern CString g_sLangTxt_IEC_Message;
extern CString g_sLangID_IEC_Subscription;
extern CString g_sLangTxt_IEC_Subscription;
extern CString g_sLangID_IEC_Publish;
extern CString g_sLangTxt_IEC_Publish;
extern CString g_sLangID_IEC_OpenConfig;
extern CString g_sLangTxt_IEC_OpenConfig;
extern CString g_sLangID_IEC_OpenConfigFile;
extern CString g_sLangTxt_IEC_OpenConfigFile;
extern CString g_sLangID_IEC_ConfigSaveAs;
extern CString g_sLangTxt_IEC_ConfigSaveAs;
extern CString g_sLangID_IEC_ConfigFileSaveAs;
extern CString g_sLangTxt_IEC_ConfigFileSaveAs;
extern CString g_sLangID_IEC_ImportSCL;
extern CString g_sLangTxt_IEC_ImportSCL;
extern CString g_sLangID_IEC_ImportSCLFile;
extern CString g_sLangTxt_IEC_ImportSCLFile;
extern CString g_sLangID_IEC_SaveDatas;
extern CString g_sLangTxt_IEC_SaveDatas;
extern CString g_sLangID_IEC_DeleteAllButFirst;
extern CString g_sLangTxt_IEC_DeleteAllButFirst;
extern CString g_sLangID_IEC_ChEdit;
extern CString g_sLangTxt_IEC_ChEdit;
extern CString g_sLangID_IEC_T1Times;
extern CString g_sLangTxt_IEC_T1Times;
extern CString g_sLangID_IEC_T0Times;
extern CString g_sLangTxt_IEC_T0Times;
extern CString g_sLangID_IEC_TimeQuality;
extern CString g_sLangTxt_IEC_TimeQuality;
extern CString g_sLangID_IEC_GroupDelay;
extern CString g_sLangTxt_IEC_GroupDelay;
extern CString g_sLangID_IEC_Details;
extern CString g_sLangTxt_IEC_Details;
extern CString g_sLangID_IEC_SamplingRate;
extern CString g_sLangTxt_IEC_SamplingRate;
extern CString g_sLangID_IEC_BaudRate;
extern CString g_sLangTxt_IEC_BaudRate;
extern CString g_sLangID_IEC_SetRecordParas;
extern CString g_sLangTxt_IEC_SetRecordParas;
extern CString g_sLangID_IEC_SmpByteNum;
extern CString g_sLangTxt_IEC_SmpByteNum;
extern CString g_sLangID_IEC_SmpCntType;
extern CString g_sLangTxt_IEC_SmpCntType;
extern CString g_sLangID_IEC_RatedDelay;
extern CString g_sLangTxt_IEC_RatedDelay;
extern CString g_sLangID_IEC_DcVolCodeValue;
extern CString g_sLangTxt_IEC_DcVolCodeValue;
extern CString g_sLangID_IEC_AcVolCodeValue;
extern CString g_sLangTxt_IEC_AcVolCodeValue;
extern CString g_sLangID_IEC_DcCurCodeValue;
extern CString g_sLangTxt_IEC_DcCurCodeValue;
extern CString g_sLangID_IEC_PrimtRatedVol;
extern CString g_sLangTxt_IEC_PrimtRatedVol;
extern CString g_sLangID_IEC_PrimtRatedCur;
extern CString g_sLangTxt_IEC_PrimtRatedCur;
extern CString g_sLangID_IEC_DcNeutralVolCodeValue;
extern CString g_sLangTxt_IEC_DcNeutralVolCodeValue;
extern CString g_sLangID_IEC_AcProtCurCodeValue;
extern CString g_sLangTxt_IEC_AcProtCurCodeValue;
extern CString g_sLangID_IEC_AcMeasCurCodeValue;
extern CString g_sLangTxt_IEC_AcMeasCurCodeValue;

extern CString g_sLangID_IEC_FT3PublishParameterSet;
extern CString g_sLangTxt_IEC_FT3PublishParameterSet;
extern CString g_sLangID_IEC_FT3MapParameterSet;
extern CString g_sLangTxt_IEC_FT3MapParameterSet;
extern CString g_sLangID_IEC_KeepSendAfterStop;
extern CString g_sLangTxt_IEC_KeepSendAfterStop;
extern CString g_sLangID_IEC_StopSending;
extern CString g_sLangTxt_IEC_StopSending;

extern CString g_sLangID_IEC_PacketSendingMode;
extern CString g_sLangTxt_IEC_PacketSendingMode;
extern CString g_sLangID_IEC_PTRatio;
extern CString g_sLangTxt_IEC_PTRatio;
extern CString g_sLangID_IEC_CTRatio;
extern CString g_sLangTxt_IEC_CTRatio;
extern CString g_sLangID_IEC_SMVCh;
extern CString g_sLangTxt_IEC_SMVCh;
extern CString g_sLangID_IEC_ChByteLen; 
extern CString g_sLangTxt_IEC_ChByteLen;
extern CString g_sLangID_IEC_ChDescription;
extern CString g_sLangTxt_IEC_ChDescription;
extern CString g_sLangID_IEC_ChType;
extern CString g_sLangTxt_IEC_ChType;
extern CString g_sLangID_IEC_DIMap;
extern CString g_sLangTxt_IEC_DIMap;
extern CString g_sLangID_IEC_SetRepair;
extern CString g_sLangTxt_IEC_SetRepair;
extern CString g_sLangID_IEC_UnSetRepair;
extern CString g_sLangTxt_IEC_UnSetRepair;
extern CString g_sLangID_IEC_IMap;
extern CString g_sLangTxt_IEC_IMap;
extern CString g_sLangID_IEC_UMap;
extern CString g_sLangTxt_IEC_UMap;
extern CString g_sLangID_IEC_SetInitValue; 
extern CString g_sLangTxt_IEC_SetInitValue;
extern CString g_sLangID_IEC_Choose;
extern CString g_sLangTxt_IEC_Choose;
extern CString g_sLangID_IEC_Target;
extern CString g_sLangTxt_IEC_Target;
extern CString g_sLangID_IEC_Entrance;
extern CString g_sLangTxt_IEC_Entrance;
extern CString g_sLangID_IEC_Sendratio;
extern CString g_sLangTxt_IEC_Sendratio;
extern CString g_sLangID_IEC_Receiveratio;
extern CString g_sLangTxt_IEC_Receiveratio;
extern CString g_sLangID_IEC_ChannelNumber;
extern CString g_sLangTxt_IEC_ChannelNumber;
extern CString g_sLangID_IEC_Version;
extern CString g_sLangTxt_IEC_Version;
extern CString g_sLangID_IEC_Test;
extern CString g_sLangTxt_IEC_Test;
extern CString g_sLangID_IEC_LifeTime;
extern CString g_sLangTxt_IEC_LifeTime;
extern CString g_sLangID_IEC_UnParse;
extern CString g_sLangTxt_IEC_UnParse;
extern CString g_sLangID_IEC_ChMaps;
extern CString g_sLangTxt_IEC_ChMaps;
extern CString g_sLangID_IEC_InitValue;
extern CString g_sLangTxt_IEC_InitValue;
extern CString g_sLangID_IEC_InputMap;
extern CString g_sLangTxt_IEC_InputMap;
extern CString g_sLangID_IEC_Source;
extern CString g_sLangTxt_IEC_Source;
extern CString g_sLangID_IEC_Intrance;
extern CString g_sLangTxt_IEC_Intrance;
extern CString g_sLangID_IEC_Quality;
extern CString g_sLangTxt_IEC_Quality;
extern CString g_sLangID_IEC_Delay;
extern CString g_sLangTxt_IEC_Delay;
extern CString g_sLangID_IEC_StartDelay;
extern CString g_sLangTxt_IEC_StartDelay;
extern CString g_sLangID_IEC_Synchronously;
extern CString g_sLangTxt_IEC_Synchronously;
extern CString g_sLangID_IEC_ScaleFactor;
extern CString g_sLangTxt_IEC_ScaleFactor;
extern CString g_sLangID_IEC_SetScaleFactor;
extern CString g_sLangTxt_IEC_SetScaleFactor;
extern CString g_sLangID_IEC_FMByte;
extern CString g_sLangTxt_IEC_FMByte;
extern CString g_sLangID_IEC_GMByte;
extern CString g_sLangTxt_IEC_GMByte;
extern CString g_sLangID_IEC_LCFI;
extern CString g_sLangTxt_IEC_LCFI;
extern CString g_sLangID_IEC_IRIGB;
extern CString g_sLangTxt_IEC_IRIGB;
extern CString g_sLangID_IEC_STFI;
extern CString g_sLangTxt_IEC_STFI;
extern CString g_sLangID_IEC_FI;
extern CString g_sLangTxt_IEC_FI;
extern CString g_sLangID_IEC_FIChoose;
extern CString g_sLangTxt_IEC_FIChoose;
extern CString g_sLangID_IEC_MACAddr;
extern CString g_sLangTxt_IEC_MACAddr;
extern CString g_sLangID_IEC_DataSetText;
extern CString g_sLangTxt_IEC_DataSetText;
extern CString g_sLangID_IEC_GOOSEIndex;
extern CString g_sLangTxt_IEC_GOOSEIndex;
extern CString g_sLangID_IEC_VlanPri;
extern CString g_sLangTxt_IEC_VlanPri;
extern CString g_sLangID_IEC_ConfigVersion;
extern CString g_sLangTxt_IEC_ConfigVersion;
extern CString g_sLangID_IEC_ChAllNumber;
extern CString g_sLangTxt_IEC_ChAllNumber;
extern CString g_sLangID_IEC_SubChNumber;
extern CString g_sLangTxt_IEC_SubChNumber;
extern CString g_sLangID_IEC_SubIED;
extern CString g_sLangTxt_IEC_SubIED;
extern CString g_sLangID_IEC_ASDU;
extern CString g_sLangTxt_IEC_ASDU;
extern CString g_sLangID_IEC_Find;
extern CString g_sLangTxt_IEC_Find;
extern CString g_sLangID_IEC_SMVPublish;
extern CString g_sLangTxt_IEC_SMVPublish;
extern CString g_sLangID_IEC_SMVSubscription;
extern CString g_sLangTxt_IEC_SMVSubscription;
extern CString g_sLangID_IEC_Configure;
extern CString g_sLangTxt_IEC_Configure;
extern CString g_sLangID_IEC_IEDList;
extern CString g_sLangTxt_IEC_IEDList;
extern CString g_sLangID_IEC_PTOnce;
extern CString g_sLangTxt_IEC_PTOnce;  

extern CString g_sLangID_IEC_FiberInSet;
extern CString g_sLangTxt_IEC_FiberInSet;
extern CString g_sLangID_IEC_FiberOutSet;
extern CString g_sLangTxt_IEC_FiberOutSet;

extern CString g_sLangID_IEC_Opticalport;
extern CString g_sLangTxt_IEC_Opticalport;
extern CString g_sLangID_IEC_QualityParaSet;
extern CString g_sLangTxt_IEC_QualityParaSet;
extern CString g_sLangID_IEC_Validity;
extern CString g_sLangTxt_IEC_Validity;
extern CString g_sLangID_IEC_Overflow;
extern CString g_sLangTxt_IEC_Overflow;
extern CString g_sLangID_IEC_OutOfRange;
extern CString g_sLangTxt_IEC_OutOfRange;
extern CString g_sLangID_IEC_BadReference;
extern CString g_sLangTxt_IEC_BadReference;
extern CString g_sLangID_IEC_Oscillatory;
extern CString g_sLangTxt_IEC_Oscillatory;
extern CString g_sLangID_IEC_Failure;
extern CString g_sLangTxt_IEC_Failure;
extern CString g_sLangID_IEC_OldData;
extern CString g_sLangTxt_IEC_OldData;

extern CString g_sLangID_IEC_IEDselect;
extern CString g_sLangTxt_IEC_IEDselect;
extern CString g_sLangID_IEC_Inconsistent;
extern CString g_sLangTxt_IEC_Inconsistent;
extern CString g_sLangID_IEC_Inaccurate;
extern CString g_sLangTxt_IEC_Inaccurate;
extern CString g_sLangID_Channel_Source;
extern CString g_sLangTxt_Channel_Source;
extern CString g_sLangID_Channel_Test;
extern CString g_sLangTxt_Channel_Test;
extern CString g_sLangID_IEC_Opb;
extern CString g_sLangTxt_IEC_Opb;
extern CString g_sLangID_IEC_ModifyAllChs;
extern CString g_sLangTxt_IEC_ModifyAllChs;
extern CString g_sLangID_IEC_DirectSet;
extern CString g_sLangTxt_IEC_DirectSet;
extern CString g_sLangID_IEC_good;
extern CString g_sLangTxt_IEC_good;
extern CString g_sLangID_IEC_invalid;
extern CString g_sLangTxt_IEC_invalid;
extern CString g_sLangID_IEC_reserved;
extern CString g_sLangTxt_IEC_reserved;
extern CString g_sLangID_IEC_questionable;
extern CString g_sLangTxt_IEC_questionable;
extern CString g_sLangID_IEC_nooverflow;
extern CString g_sLangTxt_IEC_nooverflow;
extern CString g_sLangID_IEC_overflow;
extern CString g_sLangTxt_IEC_overflow;
extern CString g_sLangID_IEC_normal;
extern CString g_sLangTxt_IEC_normal;
extern CString g_sLangID_IEC_outofrange;
extern CString g_sLangTxt_IEC_outofrange;
extern CString g_sLangID_IEC_badreference;
extern CString g_sLangTxt_IEC_badreference;
extern CString g_sLangID_IEC_noOscillatory;
extern CString g_sLangTxt_IEC_noOscillatory;
extern CString g_sLangID_IEC_oscillatory;
extern CString g_sLangTxt_IEC_oscillatory;
extern CString g_sLangID_IEC_nofailure;
extern CString g_sLangTxt_IEC_nofailure;
extern CString g_sLangID_IEC_failure;
extern CString g_sLangTxt_IEC_failure;
extern CString g_sLangID_IEC_noovertime;
extern CString g_sLangTxt_IEC_noovertime;
extern CString g_sLangID_IEC_overtime;
extern CString g_sLangTxt_IEC_overtime;
extern CString g_sLangID_IEC_noinconsistent;
extern CString g_sLangTxt_IEC_noinconsistent;
extern CString g_sLangID_IEC_inconsistent;
extern CString g_sLangTxt_IEC_inconsistent;
extern CString g_sLangID_IEC_accurate;
extern CString g_sLangTxt_IEC_accurate;
extern CString g_sLangID_IEC_inaccurate;
extern CString g_sLangTxt_IEC_inaccurate;
extern CString g_sLangID_IEC_process;
extern CString g_sLangTxt_IEC_process;
extern CString g_sLangID_IEC_substituted;
extern CString g_sLangTxt_IEC_substituted;
extern CString g_sLangID_IEC_run;
extern CString g_sLangTxt_IEC_run;
extern CString g_sLangID_IEC_test;
extern CString g_sLangTxt_IEC_test;
extern CString g_sLangID_IEC_nolock;
extern CString g_sLangTxt_IEC_nolock;
extern CString g_sLangID_IEC_lock;
extern CString g_sLangTxt_IEC_lock;
extern CString g_sLangID_IEC_Msg_OverWriteCtrl;
extern CString g_sLangTxt_IEC_Msg_OverWriteCtrl;
extern CString g_sLangID_IEC_DescExternal; 
extern CString g_sLangTxt_IEC_DescExternal; 

extern CString g_sLangID_IEC_PTSecond;
extern CString g_sLangTxt_IEC_PTSecond;

extern CString g_sLangID_IEC_AccuratyLevel;
extern CString g_sLangTxt_IEC_AccuratyLevel;
extern CString g_sLangID_IEC_ImportIecfg;
extern CString g_sLangTxt_IEC_ImportIecfg;
extern CString g_sLangID_IEC_Detect;
extern CString g_sLangTxt_IEC_Detect;
extern CString g_sLangID_IEC_DetectStop;
extern CString g_sLangTxt_IEC_DetectStop;
extern CString g_sLangID_IEC_Clear;
extern CString g_sLangTxt_IEC_Clear;
extern CString g_sLangID_IEC_BeginRecord;
extern CString g_sLangTxt_IEC_BeginRecord;
extern CString g_sLangID_IEC_UseSmv;
extern CString g_sLangTxt_IEC_UseSmv;
extern CString g_sLangID_IEC_UseGoose;
extern CString g_sLangTxt_IEC_UseGoose;
extern CString g_sLangID_IEC_SmvFirstIsTime;
extern CString g_sLangTxt_IEC_SmvFirstIsTime;
extern CString g_sLangID_IEC_WriteDetectPkg;
extern CString g_sLangTxt_IEC_WriteDetectPkg;
extern CString g_sLangID_IEC_WriteRcvPkg;
extern CString g_sLangTxt_IEC_WriteRcvPkg;
extern CString g_sLangID_IEC_AutoWrite;
extern CString g_sLangTxt_IEC_AutoWrite;
extern CString g_sLangID_IEC_SendLength_2;
extern CString g_sLangTxt_IEC_SendLength_2;
extern CString g_sLangID_IEC_SendLength;
extern CString g_sLangTxt_IEC_SendLength;
extern CString g_sLangID_IEC_Writegen;
extern CString g_sLangTxt_IEC_Writegen;
extern CString g_sLangID_IEC_PacketSending;
extern CString g_sLangTxt_IEC_PacketSending;
extern CString g_sLangID_IEC_OnceValue;
extern CString g_sLangTxt_IEC_OnceValue;
extern CString g_sLangID_IEC_TwiceValue;
extern CString g_sLangTxt_IEC_TwiceValue;
extern CString g_sLangID_IEC_Coeff;
extern CString g_sLangTxt_IEC_Coeff;
extern CString g_sLangID_IEC_FileSaveAs;
extern CString g_sLangTxt_IEC_FileSaveAs;
extern CString g_sLangID_IEC_CTOnce;
extern CString g_sLangTxt_IEC_CTOnce;
extern CString g_sLangID_IEC_CTSecond;
extern CString g_sLangTxt_IEC_CTSecond;
extern CString g_sLangID_IEC_OPDES; 
extern CString g_sLangTxt_IEC_OPDES;
extern CString g_sLangID_IEC_Protectcurrent;
extern CString g_sLangTxt_IEC_Protectcurrent;
extern CString g_sLangTxt_IEC_Measurcurrent;
extern CString g_sLangID_IEC_Measurcurrent;
extern CString g_sLangID_IEC_IEC61850;
extern CString g_sLangTxt_IEC_IEC61850;

extern CString g_sLangID_GOOSE_Single;
extern CString g_sLangTxt_GOOSE_Single;
extern CString g_sLangID_GOOSE_Double;
extern CString g_sLangTxt_GOOSE_Double;
extern CString g_sLangID_GOOSE_Float;
extern CString g_sLangTxt_GOOSE_Float;

extern CString g_sLangID_Goose_SwitchTime;
extern CString g_sLangTxt_Goose_SwitchTime;
extern CString g_sLangID_Goose_Value;
extern CString g_sLangTxt_Goose_Value;
extern CString g_sLangID_Goose_RelativeTime;
extern CString g_sLangTxt_Goose_RelativeTime;

extern CString g_sLangID_CharLib_ZoomIndex;
extern CString g_sLangTxt_CharLib_ZoomIndex;
extern CString g_sLangID_CharLib_FaultPhase;
extern CString g_sLangTxt_CharLib_FaultPhase;
extern CString g_sLangID_CharLib_AddChar;
extern CString g_sLangTxt_CharLib_AddChar;
extern CString g_sLangID_CharLib_StartCurr;
extern CString g_sLangTxt_CharLib_StartCurr;
extern CString g_sLangID_CharLib_Ratiobraking;
extern CString g_sLangTxt_CharLib_Ratiobraking;
extern CString g_sLangID_CharLib_Paragraph;
extern CString g_sLangTxt_CharLib_Paragraph;
extern CString g_sLangID_CharLib_Tripping;
extern CString g_sLangTxt_CharLib_Tripping;
extern CString g_sLangID_CharLib_TestPointsGrid;
extern CString g_sLangTxt_CharLib_TestPointsGrid;

extern CString g_sLangID_Smv_SelCb;
extern CString g_sLangTxt_Smv_SelCb;
extern CString g_sLangID_Smv_SelFunc;
extern CString g_sLangTxt_Smv_SelFunc;

extern CString g_sLangID_Smv_PrevPage;
extern CString g_sLangTxt_Smv_PrevPage;
extern CString g_sLangID_Smv_NextPage;
extern CString g_sLangTxt_Smv_NextPage;
extern CString g_sLangID_Smv_SysSet;
extern CString g_sLangTxt_Smv_SysSet;
extern CString g_sLangID_Smv_ChName;
extern CString g_sLangTxt_Smv_ChName;
extern CString g_sLangID_Smv_Item;
extern CString g_sLangTxt_Smv_Item;
extern CString g_sLangID_Smv_Number;
extern CString g_sLangTxt_Smv_Number;

extern CString g_sLangID_Smv_PkgValue;
extern CString g_sLangTxt_Smv_PkgValue;
extern CString g_sLangID_Smv_Category;
extern CString g_sLangTxt_Smv_Category;
extern CString g_sLangID_Smv_Rates;
extern CString g_sLangTxt_Smv_Rates;
extern CString g_sLangID_Smv_ShowOneValue;
extern CString g_sLangTxt_Smv_ShowOneValue;
extern CString g_sLangID_Smv_ShowTwoValue;
extern CString g_sLangTxt_Smv_ShowTwoValue;


extern CString g_sLangID_Native_EffectiveVol;
extern CString g_sLangTxt_Native_EffectiveVol;
extern CString g_sLangID_Native_EffectiveCurr;
extern CString g_sLangTxt_Native_EffectiveCurr;
extern CString g_sLangID_Native_Power;
extern CString g_sLangTxt_Native_Power;
extern CString g_sLangID_Native_ReactivePow;
extern CString g_sLangTxt_Native_ReactivePow;
extern CString g_sLangID_Native_ApparentPow;
extern CString g_sLangTxt_Native_ApparentPow;
extern CString g_sLangID_Native_PowFactor;
extern CString g_sLangTxt_Native_PowFactor;
extern CString g_sLangID_Native_TotalPow;
extern CString g_sLangTxt_Native_TotalPow;
extern CString g_sLangID_Native_Clear;
extern CString g_sLangTxt_Native_Clear;

extern CString g_sLangID_Samples;
extern CString g_sLangTxt_Samples;
extern CString g_sLangID_Momentaryvalue;
extern CString g_sLangTxt_Momentaryvalue;
extern CString g_sLangID_notrigger;
extern CString g_sLangTxt_notrigger;
extern CString g_sLangID_Cyclicwave;
extern CString g_sLangTxt_Cyclicwave;
extern CString g_sLangID_GPS;
extern CString g_sLangTxt_GPS;
extern CString g_sLangID_Timere;
extern CString g_sLangTxt_Timere;
extern CString g_sLangID_Switchtrigger;
extern CString g_sLangTxt_Switchtrigger;
extern CString g_sLangID_Faultcurve;
extern CString g_sLangTxt_Faultcurve;
extern CString g_sLangID_Display;
extern CString g_sLangTxt_Display;
extern CString g_sLangID_AChannel;
extern CString g_sLangTxt_AChannel;
extern CString g_sLangID_BChannel;
extern CString g_sLangTxt_BChannel;
extern CString g_sLangID_Open_Record;
extern CString g_sLangTxt_Open_Record;
extern CString g_sLangID_Instant;
extern CString g_sLangTxt_Instant;
extern CString g_sLangID_PT;
extern CString g_sLangTxt_PT;
extern CString g_sLangID_CT;
extern CString g_sLangTxt_CT;
extern CString g_sLangID_Module1;
extern CString g_sLangTxt_Module1;
extern CString g_sLangID_Outputpower;
extern CString g_sLangTxt_Outputpower;
extern CString g_sLangID_Currentmodule;
extern CString g_sLangTxt_Currentmodule;
extern CString g_sLangID_CurrModuleSelect;
extern CString g_sLangTxt_CurrModuleSelect;
extern CString g_sLangID_Currentgear;
extern CString g_sLangTxt_Currentgear;
extern CString g_sLangID_Maximumport;
extern CString g_sLangTxt_Maximumport;
extern CString g_sLangID_Combinedcurrent;
extern CString g_sLangTxt_Combinedcurrent;
extern CString g_sLangID_Highcurrent;
extern CString g_sLangTxt_Highcurrent;
extern CString g_sLangID_Onegear;
extern CString g_sLangTxt_Onegear;
extern CString g_sLangID_Twogear;
extern CString g_sLangTxt_Twogear;
extern CString g_sLangID_Threegear;
extern CString g_sLangTxt_Threegear;
extern CString g_sLangID_else;
extern CString g_sLangTxt_else;
extern CString g_sLangID_Gradient_BoutSet; //开出量设置
extern CString g_sLangTxt_Gradient_BoutSet;
extern CString g_sLangID_Gradient_BoutSets; //更多开出量设置
extern CString g_sLangTxt_Gradient_BoutSets;

extern CString g_sLangID_Onlyselect;
extern CString g_sLangTxt_Onlyselect;
extern CString g_sLangID_Clickratio;
extern CString g_sLangTxt_Clickratio;
extern CString g_sLangID_Clickmonitor;
extern CString g_sLangTxt_Clickmonitor;
extern CString g_sLangID_Selecttable;
extern CString g_sLangTxt_Selecttable;
extern CString g_sLangID_Reporttest;
extern CString g_sLangTxt_Reporttest;
extern CString g_sLangID_starttest;
extern CString g_sLangTxt_starttest;
extern CString g_sLangID_General;
extern CString g_sLangTxt_General;
extern CString g_sLangID_TestHelp;
extern CString g_sLangTxt_TestHelp;
extern CString g_sLangID_Currentfailed;
extern CString g_sLangTxt_Currentfailed;
extern CString g_sLangID_Succeeded;
extern CString g_sLangTxt_Succeeded;
extern CString g_sLangID_delay;
extern CString g_sLangTxt_delay;
extern CString g_sLangID_Measured;
extern CString g_sLangTxt_Measured;
extern CString g_sLangID_error;
extern CString g_sLangTxt_error;
extern CString g_sLangID_The;
extern CString g_sLangTxt_The;
extern CString g_sLangID_current;
extern CString g_sLangTxt_current;
extern CString g_sLangID_Node;
extern CString g_sLangTxt_Node;
extern CString g_sLangID_Items;
extern CString g_sLangTxt_Items;
extern CString g_sLangID_exist;
extern CString g_sLangTxt_exist;
extern CString g_sLangID_menu;
extern CString g_sLangTxt_menu;
extern CString g_sLangID_return;
extern CString g_sLangTxt_return;
extern CString g_sLangID_USBFile;
extern CString g_sLangTxt_USBFile;
extern CString g_sLangID_RepalceFile;
extern CString g_sLangTxt_RepalceFile;
extern CString g_sLangID_import;
extern CString g_sLangTxt_import;
extern CString g_sLangID_export;
extern CString g_sLangTxt_export;
extern CString g_sLangID_Importflie;
extern CString g_sLangTxt_Importflie;
extern CString g_sLangID_Win;
extern CString g_sLangTxt_Win;
extern CString g_sLangID_Lose;
extern CString g_sLangTxt_Lose;
extern CString g_sLangID_block;
extern CString g_sLangTxt_block;
extern CString g_sLangID_Controlblock;
extern CString g_sLangTxt_Controlblock;
extern CString g_sLangID_leastone;
extern CString g_sLangTxt_leastone;
extern CString g_sLangID_copyblock;
extern CString g_sLangTxt_copyblock;
extern CString g_sLangID_viewchannel;
extern CString g_sLangTxt_viewchannel;
extern CString g_sLangID_dataobject;
extern CString g_sLangTxt_dataobject;
extern CString g_sLangID_channelType;
extern CString g_sLangTxt_channelType;
extern CString g_sLangID_parameterport;
extern CString g_sLangTxt_parameterport;

extern CString g_sLangID_SMV92map;
extern CString g_sLangTxt_SMV92map;
extern CString g_sLangID_samplepublish;
extern CString g_sLangTxt_samplepublish;
extern CString g_sLangID_USB;
extern CString g_sLangTxt_USB;
extern CString g_sLangID_exportbar;
extern CString g_sLangTxt_exportbar;
extern CString g_sLangID_Fileguid;
extern CString g_sLangTxt_Fileguid;
extern CString g_sLangID_adjustrange;
extern CString g_sLangTxt_adjustrange;
extern CString g_sLangID_devicedesc;
extern CString g_sLangTxt_devicedesc;
extern CString g_sLangID_unittype;
extern CString g_sLangTxt_unittype;
extern CString g_sLangID_componenttest;
extern CString g_sLangTxt_componenttest;
extern CString g_sLangID_componentlinevolttest;
extern CString g_sLangTxt_componentlinevolttest;
extern CString g_sLangID_changelist;
extern CString g_sLangTxt_changelist;
extern CString g_sLangID_overwitten;
extern CString g_sLangTxt_overwitten;
extern CString g_sLangID_sequence;
extern CString g_sLangTxt_sequence;
extern CString g_sLangID_linevolt;
extern CString g_sLangTxt_linevolt;
extern CString g_sLangID_steplength;
extern CString g_sLangTxt_steplength;
//extern CString g_sLangID_Frequency;   //移动到基类CXLanguageResourceBase  2024-1-4 shaolei
extern CString g_sLangTxt_Frequency;
extern CString g_sLangID_selectchannel;
extern CString g_sLangTxt_selectchannel;
extern CString g_sLangID_currenttime;
extern CString g_sLangTxt_currenttime;
extern CString g_sLangID_channelname;
extern CString g_sLangTxt_channelname;
extern CString g_sLangID_errorclass;
extern CString g_sLangTxt_errorclass;
extern CString g_sLangID_numbertest;
extern CString g_sLangTxt_numbertest;
extern CString g_sLangID_realtime;
extern CString g_sLangTxt_realtime;
extern CString g_sLangID_emptydata;
extern CString g_sLangTxt_emptydata;
extern CString g_sLangID_ratioerror;
extern CString g_sLangTxt_ratioerror;
extern CString g_sLangID_ratioerror2;
extern CString g_sLangTxt_ratioerror2;
extern CString g_sLangID_angle;
extern CString g_sLangTxt_angle;
extern CString g_sLangID_Compound;
extern CString g_sLangTxt_Compound;
extern CString g_sLangID_statistic;
extern CString g_sLangTxt_statistic;
extern CString g_sLangID_outputvalue;
extern CString g_sLangTxt_outputvalue;
extern CString g_sLangID_Outputphase;
extern CString g_sLangTxt_Outputphase;
extern CString g_sLangID_Measureampl;
extern CString g_sLangTxt_Measureampl;
extern CString g_sLangID_Measuredphase;
extern CString g_sLangTxt_Measuredphase;
extern CString g_sLangID_zerodrift;
extern CString g_sLangTxt_zerodrift;
extern CString g_sLangID_posttrigger;
extern CString g_sLangTxt_posttrigger;
extern CString g_sLangID_Switchimmed;
extern CString g_sLangTxt_Switchimmed;
extern CString g_sLangID_loopwaveform;
extern CString g_sLangTxt_loopwaveform;
extern CString g_sLangID_faultreplay;
extern CString g_sLangTxt_faultreplay;
extern CString g_sLangID_downloaddata;
extern CString g_sLangTxt_downloaddata;
extern CString g_sLangID_starttest2;
extern CString g_sLangTxt_starttest2;
extern CString g_sLangID_playback;
extern CString g_sLangTxt_playback;
extern CString g_sLangID_outputvoltage;
extern CString g_sLangTxt_outputvoltage;
extern CString g_sLangID_outputcurrent;
extern CString g_sLangTxt_outputcurrent;
extern CString g_sLangID_deliverybar;
extern CString g_sLangTxt_deliverybar;
extern CString g_sLangID_cfgFile;
extern CString g_sLangTxt_cfgFile;
extern CString g_sLangID_parsebar;
extern CString g_sLangTxt_parsebar;
extern CString g_sLangID_recordfile;
extern CString g_sLangTxt_recordfile;
extern CString g_sLangID_hardwarefile;
extern CString g_sLangTxt_hardwarefile;
extern CString g_sLangID_channelphase;
extern CString g_sLangTxt_channelphase;
extern CString g_sLangID_tablechannel;
extern CString g_sLangTxt_tablechannel;
extern CString g_sLangID_faulttype;
extern CString g_sLangTxt_faulttype;
extern CString g_sLangID_rangenumber;
extern CString g_sLangTxt_rangenumber;
extern CString g_sLangID_maxblocks;
extern CString g_sLangTxt_maxblocks;
extern CString g_sLangID_valuesubscrip;
extern CString g_sLangTxt_valuesubscrip;
extern CString g_sLangID_emptyIed;
extern CString g_sLangTxt_emptyIed;
extern CString g_sLangID_emptyIEC;
extern CString g_sLangTxt_emptyIEC;
extern CString g_sLangID_addedblock;
extern CString g_sLangTxt_addedblock;
extern CString g_sLangID_configurationfile;
extern CString g_sLangTxt_configurationfile;
// extern CString g_sLangID_warning;
// extern CString g_sLangTxt_warning;
extern CString g_sLangID_NullIEC;
extern CString g_sLangTxt_NullIEC;
extern CString g_sLangID_IECpath;
extern CString g_sLangTxt_IECpath;
extern CString g_sLangID_IECdocument;
extern CString g_sLangTxt_IECdocument;
extern CString g_sLangID_zero;
extern CString g_sLangTxt_zero;
extern CString g_sLangID_step;
extern CString g_sLangTxt_step;
extern CString g_sLangID_datapath;
extern CString g_sLangTxt_datapath;
extern CString g_sLangID_guide;
extern CString g_sLangTxt_guide;
extern CString g_sLangID_wizard;
extern CString g_sLangTxt_wizard;
extern CString g_sLangID_period;
extern CString g_sLangTxt_period;
extern CString g_sLangID_quality;
extern CString g_sLangTxt_quality;
extern CString g_sLangID_mutate;
extern CString g_sLangTxt_mutate;
extern CString g_sLangID_leadtime;
extern CString g_sLangTxt_leadtime;
extern CString g_sLangID_change;
extern CString g_sLangTxt_change;
extern CString g_sLangID_instrument;
extern CString g_sLangTxt_instrument;
extern CString g_sLangID_instrumentnumber;
extern CString g_sLangTxt_instrumentnumber;
extern CString g_sLangID_testip;
extern CString g_sLangTxt_testip;
extern CString g_sLangID_IPaddress;
extern CString g_sLangTxt_IPaddress;
extern CString g_sLangID_correctlyform;
extern CString g_sLangTxt_correctlyform;
extern CString g_sLangID_assistantIP;
extern CString g_sLangTxt_assistantIP;
extern CString g_sLangID_validentry;
extern CString g_sLangTxt_validentry;
extern CString g_sLangID_listIP;
extern CString g_sLangTxt_listIP;
extern CString g_sLangID_cardIP;
extern CString g_sLangTxt_cardIP;
extern CString g_sLangID_scan;
extern CString g_sLangTxt_scan;
extern CString g_sLangID_query;
extern CString g_sLangTxt_query;
extern CString g_sLangID_running;
extern CString g_sLangTxt_running;
extern CString g_sLangID_nullIP;
extern CString g_sLangTxt_nullIP;
extern CString g_sLangID_automatic;
extern CString g_sLangTxt_automatic;
extern CString g_sLangID_networkcards;
extern CString g_sLangTxt_networkcards;
extern CString g_sLangID_validIP;
extern CString g_sLangTxt_validIP;
extern CString g_sLangID_cardlookup;
extern CString g_sLangTxt_cardlookup;
extern CString g_sLangID_modifyIP;
extern CString g_sLangTxt_modifyIP;
extern CString g_sLangID_stopscan;
extern CString g_sLangTxt_stopscan;

extern CString g_sLangID_FileMngr_FolderName;
extern CString g_sLangTxt_FileMngr_FolderName;
extern CString g_sLangID_FileMngr_FolderIllustrate;
extern CString g_sLangTxt_FileMngr_FolderIllustrate;
extern CString g_sLangID_FileMngr_Date;
extern CString g_sLangTxt_FileMngr_Date;
extern CString g_sLangID_FileMngr_File;
extern CString g_sLangTxt_FileMngr_File;
extern CString g_sLangID_FileMngr_Used;
extern CString g_sLangTxt_FileMngr_Used;
extern CString g_sLangID_FileMngr_Available;
extern CString g_sLangTxt_FileMngr_Available;
//SOE

extern CString g_sLangID_SOE_state; 
extern CString g_sLangTxt_SOE_state;
extern CString g_sLangID_SOE_ChangeBeforTimes; 
extern CString g_sLangTxt_SOE_ChangeBeforTimes;
extern CString g_sLangID_SOE_ShuttingTimes; 
extern CString g_sLangTxt_SOE_ShuttingTimes;
extern CString g_sLangID_SOE_DisconTimes; 
extern CString g_sLangTxt_SOE_DisconTimes;
extern CString g_sLangID_SOE_Count; 
extern CString g_sLangTxt_SOE_Count;
extern CString g_sLangID_SOE_SustainTimes; 
extern CString g_sLangTxt_SOE_SustainTimes;

extern CString g_sLangID_SOE_Break; 
extern CString g_sLangTxt_SOE_Break;

extern CString g_sLangID_SOE_Shutting; 
extern CString g_sLangTxt_SOE_Shutting;

extern CString g_sLangID_SOE_ImmediateExperiment; 
extern CString g_sLangTxt_SOE_ImmediateExperiment;
extern CString g_sLangID_SOE_PulseWidth;
extern CString g_sLangTxt_SOE_PulseWidth;	
extern CString g_sLangID_SOE_Resolution;
extern CString g_sLangTxt_SOE_Resolution;
extern CString g_sLangID_SOE_SelectAll;
extern CString g_sLangTxt_SOE_SelectAll;
extern CString g_sLangID_SOE_CancelAll;
extern CString g_sLangTxt_SOE_CancelAll;
extern CString g_sLangID_SOE_InitialAll;
extern CString g_sLangTxt_SOE_InitialAll;
extern CString g_sLangID_SOE_InitialDivideAll;
extern CString g_sLangTxt_SOE_InitialDivideAll;
extern CString g_sLangID_SOE_TemplateFile;
extern CString g_sLangTxt_SOE_TemplateFile;

//自定义设置
extern  CString g_sLangID_Native_BtnRemove;  
extern  CString g_sLangTxt_Native_BtnRemove;
extern  CString g_sLangID_Native_BtnEndInsert;  
extern  CString g_sLangTxt_Native_BtnEndInsert;
extern  CString g_sLangID_Native_BtnInsertAfter;  
extern  CString g_sLangTxt_Native_BtnInsertAfter;
extern  CString g_sLangID_Native_BtnInsertBefore;  
extern  CString g_sLangTxt_Native_BtnInsertBefore;

//装置通讯
extern  CString g_sLangID_Native_BtnConfigDevice;  
extern  CString g_sLangTxt_Native_BtnConfigDevice;
extern  CString g_sLangID_Native_BtnConnectDevice;  
extern  CString g_sLangTxt_Native_BtnConnectDevice;
extern  CString g_sLangID_Native_BtnEnumDevice;  
extern  CString g_sLangTxt_Native_BtnEnumDevice;
extern  CString g_sLangID_Native_BtnReadDataset;  
extern  CString g_sLangTxt_Native_BtnReadDataset;
extern  CString g_sLangID_Native_BtnWriteDataset;  
extern  CString g_sLangTxt_Native_BtnWriteDataset;
extern  CString g_sLangID_Native_BtnReadZone;  
extern  CString g_sLangTxt_Native_BtnReadZone;
extern  CString g_sLangID_Native_BtnWriteZone;  
extern  CString g_sLangTxt_Native_BtnWriteZone;
extern  CString g_sLangID_Native_BtnReset;  
extern  CString g_sLangTxt_Native_BtnReset;
extern  CString g_sLangID_Native_BtnStartRpt;  
extern  CString g_sLangTxt_Native_BtnStartRpt;
extern  CString g_sLangID_Native_BtnStopReport;  
extern  CString g_sLangTxt_Native_BtnStopReportr;
extern  CString g_sLangID_Native_BtnAddDevice;  
extern  CString g_sLangTxt_Native_BtnAddDevice;
extern  CString g_sLangID_Native_BtnEnumLDevice;  
extern  CString g_sLangTxt_Native_BtnEnumLDevice;
extern  CString g_sLangID_Native_BtnEnumDataset;  
extern  CString g_sLangTxt_Native_BtnEnumDataset;
extern  CString g_sLangID_Native_BtnOpenDvmFile;  
extern  CString g_sLangTxt_Native_BtnOpenDvmFile;
extern  CString g_sLangID_Native_BtnSaveDvmFile;  
extern  CString g_sLangTxt_Native_BtnSaveDvmFile;


extern CString g_sLangID_Native_Upgradation;
extern CString g_sLangTxt_Native_Upgradation;
extern CString g_sLangID_Native_UpdateSoftware;
extern CString g_sLangTxt_Native_UpdateSoftware;
extern CString g_sLangID_Native_OnlineUpgrade;
extern CString g_sLangTxt_Native_OnlineUpgrade;
extern CString g_sLangID_Native_UpgradeProgressBar;
extern CString g_sLangTxt_Native_UpgradeProgressBar;
extern CString g_sLangID_Native_NetworkConnectionFailed;
extern CString g_sLangTxt_Native_NetworkConnectionFailed;
extern CString g_sLangID_Native_VersionUpdateFailed;
extern CString g_sLangTxt_Native_VersionUpdateFailed;
extern CString g_sLangID_Native_CommandFailed;
extern CString g_sLangTxt_Native_CommandFailed;
extern CString g_sLangID_Native_LowBatteryLevel;
extern CString g_sLangTxt_Native_LowBatteryLevel;
extern CString g_sLangID_Native_IecDetection;
extern CString g_sLangTxt_Native_IecDetection;
extern CString g_sLangID_Native_UnrecognizedUSB;
extern CString g_sLangTxt_Native_UnrecognizedUSB;
extern CString g_sLangID_Native_ChargingUpgrade;
extern CString g_sLangTxt_Native_ChargingUpgrade;
extern CString g_sLangID_Native_OfflineUpgrade;
extern CString g_sLangTxt_Native_OfflineUpgrade;
extern CString g_sLangID_Native_PreparationUpgrade;
extern CString g_sLangTxt_Native_PreparationUpgrade;
extern CString g_sLangID_Native_LookupFailed;
extern CString g_sLangTxt_Native_LookupFailed;
extern CString g_sLangID_Native_LiveUpdate;
extern CString g_sLangTxt_Native_LiveUpdate;
extern CString g_sLangID_Native_ExcludingReportData;
extern CString g_sLangTxt_Native_ExcludingReportData;
extern CString g_sLangID_Native_ReportDataEmpty;
extern CString g_sLangTxt_Native_ReportDataEmpty;

extern CString g_sLangID_Native_VolSetTypeLN;
extern CString g_sLangTxt_Native_VolSetTypeLN;
extern CString g_sLangID_Native_VolSetTypeLL;
extern CString g_sLangTxt_Native_VolSetTypeLL;
extern CString g_sLangID_Native_VolSetTypeSE;
extern CString g_sLangTxt_Native_VolSetTypeSE;
extern CString g_sLangID_Native_CurSetTypeLN;
extern CString g_sLangTxt_Native_CurSetTypeLN;
extern CString g_sLangID_Native_CurSetTypeSE;
extern CString g_sLangTxt_Native_CurSetTypeSE;

extern CString g_sLangID_Native_SyStempoints;
extern CString g_sLangTxt_Native_SyStempoints;
extern CString g_sLangID_Native_Custompoints;
extern CString g_sLangTxt_Native_Custompoints;

extern CString g_sLangID_Native_Iecurrent;
extern CString g_sLangTxt_Native_Iecurrent;
extern CString g_sLangID_Native_Acurrent;
extern CString g_sLangTxt_Native_Acurrent;
extern CString g_sLangID_Native_Faultcurrent;
extern CString g_sLangTxt_Native_Faultcurrent;



//第七周许
//xwd 10.16
//设置原始报文
extern CString g_sLangID_Native_SetOrigMsg;
extern CString g_sLangTxt_Native_SetOrigMsg;
//目的Mac地址
extern CString g_sLangID_Native_DestMacAddr;
extern CString g_sLangTxt_Native_DestMacAddr;
//网络标识
extern CString g_sLangID_Native_Netid;
extern CString g_sLangTxt_Native_Netid;
//飞点电压值
extern CString g_sLangID_Native_FlyPntVolt;
extern CString g_sLangTxt_Native_FlyPntVolt;
//飞点电流值
extern CString g_sLangID_Native_FlyPntCurr;
extern CString g_sLangTxt_Native_FlyPntCurr;
//飞点电压Ua使能
extern CString g_sLangID_Native_FlyPntVoltUaEn;
extern CString g_sLangTxt_Native_FlyPntVoltUaEn;
//飞点电压Ub使能
extern CString g_sLangID_Native_FlyPntVoltUbEn;
extern CString g_sLangTxt_Native_FlyPntVoltUbEn;
//飞点电压Uc使能
extern CString g_sLangID_Native_FlyPntVoltUcEn;
extern CString g_sLangTxt_Native_FlyPntVoltUcEn;
//飞点电流Ia使能
extern CString g_sLangID_Native_FlyPntCurrIaEn;
extern CString g_sLangTxt_Native_FlyPntCurrIaEn;
//飞点电流Ib使能
extern CString g_sLangID_Native_FlyPntCurrIbEn;
extern CString g_sLangTxt_Native_FlyPntCurrIbEn;
//飞点电流Ic使能
extern CString g_sLangID_Native_FlyPntCurrIcEn;
extern CString g_sLangTxt_Native_FlyPntCurrIcEn;
//抖动值(单位ns)
extern CString g_sLangID_Native_JitterValns;
extern CString g_sLangTxt_Native_JitterValns;
//有效
extern CString g_sLangID_Native_Valid;
extern CString g_sLangTxt_Native_Valid;
//溢出

extern CString g_sLangID_Native_Overflow;
extern CString g_sLangTxt_Native_Overflow;
//超值域
extern CString g_sLangID_Native_OutOfRanges;
extern CString g_sLangTxt_Native_OutOfRanges;
//坏基准值
extern CString g_sLangID_Native_BadBaseVal;
extern CString g_sLangTxt_Native_BadBaseVal;
//旧数据
extern CString g_sLangID_Native_OldData;
extern CString g_sLangTxt_Native_OldData;
//不一致
extern CString g_sLangID_Native_Inconsistent;
extern CString g_sLangTxt_Native_Inconsistent;
//不精确
extern CString g_sLangID_Native_Inaccurate;
extern CString g_sLangTxt_Native_Inaccurate;
//源
extern CString g_sLangID_Native_Source;
extern CString g_sLangTxt_Native_Source;
//操作员闭锁
extern CString g_sLangID_Native_OpLock;
extern CString g_sLangTxt_Native_OpLock;
//异常点选择
extern CString g_sLangID_Native_AbnPointSel;
extern CString g_sLangTxt_Native_AbnPointSel;
//异常点
extern CString g_sLangID_Native_AbnPoint;
extern CString g_sLangTxt_Native_AbnPoint;
//SMV异常参数
extern CString g_sLangID_Native_SMVAbnParam;
extern CString g_sLangTxt_Native_SMVAbnParam;
//SV异常类型
extern CString g_sLangID_Native_SVAbnType;
extern CString g_sLangTxt_Native_SVAbnType;
//SV报文组号(从0开始编号)
extern CString g_sLangID_Native_SVMsgGrpNum;
extern CString g_sLangTxt_Native_SVMsgGrpNum;
//发送周波数(周波模式)
extern CString g_sLangID_Native_SendFreq;
extern CString g_sLangTxt_Native_SendFreq;
//每秒发送周波数(秒模式)
extern CString g_sLangID_Native_SendFreqPerSec;
extern CString g_sLangTxt_Native_SendFreqPerSec;
//异常数据发送时间模式(0-周波;1-秒)
extern CString g_sLangID_Native_AbnormDataSendTimeMode;
extern CString g_sLangTxt_Native_AbnormDataSendTimeMode;
//SV发送时间(秒模式)
extern CString g_sLangID_Native_SVSendTimeSecMode;
extern CString g_sLangTxt_Native_SVSendTimeSecMode;
//GOOSE异常参数
extern CString g_sLangID_Native_GOOSEAbnormParam;
extern CString g_sLangTxt_Native_GOOSEAbnormParam;
//异常组序号（从0计数）
extern CString g_sLangID_Native_AbnormGroupSeq;
extern CString g_sLangTxt_Native_AbnormGroupSeq;
//源MAC(选择)
extern CString g_sLangID_Native_SrcMACSelect;
extern CString g_sLangTxt_Native_SrcMACSelect;
//目标MAC(选择)
extern CString g_sLangID_Native_DestMACSelect;
extern CString g_sLangTxt_Native_DestMACSelect;
//GocbRef(选择)
extern CString g_sLangID_Native_GocbRefSelect;
extern CString g_sLangTxt_Native_GocbRefSelect;
//GoID(选择)
extern CString g_sLangID_Native_GoIDSelect;
extern CString g_sLangTxt_Native_GoIDSelect;
//DataSet(选择)
extern CString g_sLangID_Native_DataSetSelect;
extern CString g_sLangTxt_Native_DataSetSelect;
//目标MAC
extern CString g_sLangID_Native_DestMACs;
extern CString g_sLangTxt_Native_DestMACs;
//AppID(选择)
extern CString g_sLangID_Native_AppIDSelect;
extern CString g_sLangTxt_Native_AppIDSelect;
//St(选择)
extern CString g_sLangID_Native_StSelect;
extern CString g_sLangTxt_Native_StSelect;
//St值
extern CString g_sLangID_Native_StValue;
extern CString g_sLangTxt_Native_StValue;
//Sq(选择)
extern CString g_sLangID_Native_SqSelect;
extern CString g_sLangTxt_Native_SqSelect;
//Sq值
extern CString g_sLangID_Native_SqValue;
extern CString g_sLangTxt_Native_SqValue;
//允许生存时间(选择)
extern CString g_sLangID_Native_AllowLiveTSelect;
extern CString g_sLangTxt_Native_AllowLiveTSelect;
//允许生存时间
extern CString g_sLangID_Native_AllowLiveT;
extern CString g_sLangTxt_Native_AllowLiveT;
//委托(选择)
extern CString g_sLangID_Native_DelegateSelect;
extern CString g_sLangTxt_Native_DelegateSelect;
//测试标记(选择)
extern CString g_sLangID_Native_TestMarkSelect;
extern CString g_sLangTxt_Native_TestMarkSelect;
//委托
extern CString g_sLangID_Native_Delegate;
extern CString g_sLangTxt_Native_Delegate;
//测试标记
extern CString g_sLangID_Native_TestMark;
extern CString g_sLangTxt_Native_TestMark;
//VlanID(选择)
extern CString g_sLangID_Native_VlanIDSelect;
extern CString g_sLangTxt_Native_VlanIDSelect;
//VlanID值
extern CString g_sLangID_Native_VlanIDValue;
extern CString g_sLangTxt_Native_VlanIDValue;
//网络标识(选择)
extern CString g_sLangID_Native_NetIDSelect;
extern CString g_sLangTxt_Native_NetIDSelect;
//网络标识值
extern CString g_sLangID_Native_NetIDValue;
extern CString g_sLangTxt_Native_NetIDValue;
//配置版本(选择)
extern CString g_sLangID_Native_ConfigVerSelect;
extern CString g_sLangTxt_Native_ConfigVerSelect;
//配置版本值
extern CString g_sLangID_Native_ConfigVerValue;
extern CString g_sLangTxt_Native_ConfigVerValue;
//常态开出1状态
extern CString g_sLangID_Native_NormalOpen1State;
extern CString g_sLangTxt_Native_NormalOpen1State;
//常态开出2状态
extern CString g_sLangID_Native_NormalOpen2State;
extern CString g_sLangTxt_Native_NormalOpen2State;
//常态开出3状态
extern CString g_sLangID_Native_NormalOpen3State;
extern CString g_sLangTxt_Native_NormalOpen3State;
//常态开出4状态
extern CString g_sLangID_Native_NormalOpen4State;
extern CString g_sLangTxt_Native_NormalOpen4State;
//常态开出5状态
extern CString g_sLangID_Native_NormalOpen5State;
extern CString g_sLangTxt_Native_NormalOpen5State;
//常态开出6状态
extern CString g_sLangID_Native_NormalOpen6State;
extern CString g_sLangTxt_Native_NormalOpen6State;
//常态开出7状态
extern CString g_sLangID_Native_NormalOpen7State;
extern CString g_sLangTxt_Native_NormalOpen7State;
//常态开出8状态
extern CString g_sLangID_Native_NormalOpen8State;
extern CString g_sLangTxt_Native_NormalOpen8State;
//故障态开出1状态
extern CString g_sLangID_Native_FaultOpen1State;
extern CString g_sLangTxt_Native_FaultOpen1State;
//故障态开出2状态
extern CString g_sLangID_Native_FaultOpen2State;
extern CString g_sLangTxt_Native_FaultOpen2State;
//故障态开出3状态
extern CString g_sLangID_Native_FaultOpen3State;
extern CString g_sLangTxt_Native_FaultOpen3State;
//故障态开出4状态
extern CString g_sLangID_Native_FaultOpen4State;
extern CString g_sLangTxt_Native_FaultOpen4State;
//故障态开出5状态
extern CString g_sLangID_Native_FaultOpen5State;
extern CString g_sLangTxt_Native_FaultOpen5State;
//故障态开出6状态
extern CString g_sLangID_Native_FaultOpen6State;
extern CString g_sLangTxt_Native_FaultOpen6State;
//故障态开出7状态
extern CString g_sLangID_Native_FaultOpen7State;
extern CString g_sLangTxt_Native_FaultOpen7State;
//故障态开出8状态
extern CString g_sLangID_Native_FaultOpen8State;
extern CString g_sLangTxt_Native_FaultOpen8State;
//热过负荷时间常数
extern CString g_sLangID_Native_HotOverloadTimeConst;
extern CString g_sLangTxt_Native_HotOverloadTimeConst;
//热过负荷基数电流
extern CString g_sLangID_Native_HotOverloadBaseCurrent;
extern CString g_sLangTxt_Native_HotOverloadBaseCurrent;
//热过负荷动作定值
extern CString g_sLangID_Native_HotOverloadActionValue;
extern CString g_sLangTxt_Native_HotOverloadActionValue;
//过负荷电流
extern CString g_sLangID_Native_OverloadCurrent;
extern CString g_sLangTxt_Native_OverloadCurrent;
//故障时间裕度
extern CString g_sLangID_Native_FaultTimeMargin;
extern CString g_sLangTxt_Native_FaultTimeMargin;
//电流变化始值
extern CString g_sLangID_Native_CurrentChangeStartValue;
extern CString g_sLangTxt_Native_CurrentChangeStartValue;
//电流变化终值

extern CString g_sLangID_Native_CurrentChangeEndValue;
extern CString g_sLangTxt_Native_CurrentChangeEndValue;
//电流变化步长
extern CString g_sLangID_Native_CurrentChangeStep;
extern CString g_sLangTxt_Native_CurrentChangeStep;
//热过负荷时间常数(表达式)
extern CString g_sLangID_Native_HotOverloadTime;
extern CString g_sLangTxt_Native_HotOverloadTime;
//热过负荷基数电流(表达式)
extern CString g_sLangID_Native_HotOverloadBaseCurr;
extern CString g_sLangTxt_Native_HotOverloadBaseCurr;
//热过负荷动作定值(表达式)
extern CString g_sLangID_Native_HotOverloadActionValues;
extern CString g_sLangTxt_Native_HotOverloadActionValues;
//动作描述
extern CString g_sLangID_Native_ActionDesc;
extern CString g_sLangTxt_Native_ActionDesc;
//故障前电压幅值
extern CString g_sLangID_Native_FaultPreVoltageAmp;
extern CString g_sLangTxt_Native_FaultPreVoltageAmp;
//故障前电流幅值
extern CString g_sLangID_Native_FaultPreCurrentAmp;
extern CString g_sLangTxt_Native_FaultPreCurrentAmp;
//故障前电压电流相角(U-I)
extern CString g_sLangID_Native_FaultPreVoltageCurrentPhase;
extern CString g_sLangTxt_Native_FaultPreVoltageCurrentPhase;
//故障前电压相序
extern CString g_sLangID_Native_FaultPreVoltageSeq;
extern CString g_sLangTxt_Native_FaultPreVoltageSeq;
//故障前电流相序
extern CString g_sLangID_Native_FaultPreCurrentSeq;
extern CString g_sLangTxt_Native_FaultPreCurrentSeq;
//故障电压
extern CString g_sLangID_Native_FaultVoltage;
extern CString g_sLangTxt_Native_FaultVoltage;
//故障态电压电流相角(U-I)
extern CString g_sLangID_Native_FaultVoltageCurrentPhase;
extern CString g_sLangTxt_Native_FaultVoltageCurrentPhase;
//短路电压类别
extern CString g_sLangID_Native_ShortCircuitVoltageType;
extern CString g_sLangTxt_Native_ShortCircuitVoltageType;
//基准值
extern CString g_sLangID_Native_ReferenceValue;
extern CString g_sLangTxt_Native_ReferenceValue;
//CT正极性
extern CString g_sLangID_Native_CTPolarityPositive;
extern CString g_sLangTxt_Native_CTPolarityPositive;
//故障前电压电流相角(表达式)
extern CString g_sLangID_Native_PreFaultVCPAExpr;
extern CString g_sLangTxt_Native_PreFaultVCPAExpr;
//动作时间定值(表达式)
extern CString g_sLangID_Native_ActionTimeSetValueExpr;
extern CString g_sLangTxt_Native_ActionTimeSetValueExpr;
//故障电压(表达式)
extern CString g_sLangID_Native_FaultVoltageExpr;
extern CString g_sLangTxt_Native_FaultVoltageExpr;
//故障电流(表达式)
extern CString g_sLangID_Native_FaultCurr;
extern CString g_sLangTxt_Native_FaultCurr;
//故障态电压电流相角(表达式)
extern CString g_sLangID_Native_FaultAngExp;
extern CString g_sLangTxt_Native_FaultAngExp;
//特性曲线参数(Vp)
extern CString g_sLangID_Native_CharCurveParam;
extern CString g_sLangTxt_Native_CharCurveParam;
//电压频率比
extern CString g_sLangID_Native_VoltFreqRatio;
extern CString g_sLangTxt_Native_VoltFreqRatio;
//变化方式 0-频率不变,增电压  1-电压不变,降频率
extern CString g_sLangID_Native_ChangeMode;
extern CString g_sLangTxt_Native_ChangeMode;
//采集模块位置
extern CString g_sLangID_Native_CollectModPos;
extern CString g_sLangTxt_Native_CollectModPos;
//采集档位
extern CString g_sLangID_Native_CollectGear;
extern CString g_sLangTxt_Native_CollectGear;
//模块位置
extern CString g_sLangID_Native_ModPos;
extern CString g_sLangTxt_Native_ModPos;
//温区
extern CString g_sLangID_Native_TempZone;
extern CString g_sLangTxt_Native_TempZone;
//表计误差
extern CString g_sLangID_Native_MeterError;
extern CString g_sLangTxt_Native_MeterError;
//参考频率
extern CString g_sLangID_Native_RefFreq;
extern CString g_sLangTxt_Native_RefFreq;
//点1参考幅值
extern CString g_sLangID_Native_Point1RefAmp;
extern CString g_sLangTxt_Native_Point1RefAmp;
//点2参考幅值
extern CString g_sLangID_Native_Point2RefAmp;
extern CString g_sLangTxt_Native_Point2RefAmp;
//点1测量幅值
extern CString g_sLangID_Native_Point1MeasAmp;
extern CString g_sLangTxt_Native_Point1MeasAmp;
//点2测量幅值
extern CString g_sLangID_Native_Point2MeasAmp;
extern CString g_sLangTxt_Native_Point2MeasAmp;
//输出幅值
extern CString g_sLangID_Native_OutputAmp;
extern CString g_sLangTxt_Native_OutputAmp;
//相位测量值
extern CString g_sLangID_Native_PhaseMeasVal;
extern CString g_sLangTxt_Native_PhaseMeasVal;
//测量频率
extern CString g_sLangID_Native_MeasFreq;
extern CString g_sLangTxt_Native_MeasFreq;
//通道硬件档位
extern CString g_sLangID_Native_ChannelHardGear;
extern CString g_sLangTxt_Native_ChannelHardGear;
//零漂测量值
extern CString g_sLangID_Native_ZeroDriftMeas;
extern CString g_sLangTxt_Native_ZeroDriftMeas;
//通道1编号
extern CString g_sLangID_Native_Channel1ID;
extern CString g_sLangTxt_Native_Channel1ID;
//通道1幅值

extern CString g_sLangID_Native_Channel1Amp;
extern CString g_sLangTxt_Native_Channel1Amp;
//通道1相位
extern CString g_sLangID_Native_Channel1Phase;
extern CString g_sLangTxt_Native_Channel1Phase;
//通道1频率
extern CString g_sLangID_Native_Channel1Freq;
extern CString g_sLangTxt_Native_Channel1Freq;
//通道2编号
extern CString g_sLangID_Native_Channel2Num;
extern CString g_sLangTxt_Native_Channel2Num;
//通道2幅值
extern CString g_sLangID_Native_Channel2Amp;
extern CString g_sLangTxt_Native_Channel2Amp;
//通道2相位
extern CString g_sLangID_Native_Channel2Phase;
extern CString g_sLangTxt_Native_Channel2Phase;
//通道2频率
extern CString g_sLangID_Native_Channel2Freq;
extern CString g_sLangTxt_Native_Channel2Freq;
//通道3编号
extern CString g_sLangID_Native_Channel3Num;
extern CString g_sLangTxt_Native_Channel3Num;
//通道3幅值
extern CString g_sLangID_Native_Channel3Amp;
extern CString g_sLangTxt_Native_Channel3Amp;
//通道3相位
extern CString g_sLangID_Native_Channel3Phase;
extern CString g_sLangTxt_Native_Channel3Phase;
//通道3频率
extern CString g_sLangID_Native_Channel3Freq;
extern CString g_sLangTxt_Native_Channel3Freq;
//是否大电流校准
extern CString g_sLangID_Native_IsHighCurrentCalib;
extern CString g_sLangTxt_Native_IsHighCurrentCalib;
//通道1幅值系数
extern CString g_sLangID_Native_Channel1AmpCoeff;
extern CString g_sLangTxt_Native_Channel1AmpCoeff;
//通道1零漂
extern CString g_sLangID_Native_Channel1ZeroOffset;
extern CString g_sLangTxt_Native_Channel1ZeroOffset;
//通道2幅值系数
extern CString g_sLangID_Native_Channel2AmpCoeff;
extern CString g_sLangTxt_Native_Channel2AmpCoeff;
//通道2零漂
extern CString g_sLangID_Native_Channel2ZeroOffset;
extern CString g_sLangTxt_Native_Channel2ZeroOffset;
//通道3幅值系数
extern CString g_sLangID_Native_Channel3AmpCoeff;
extern CString g_sLangTxt_Native_Channel3AmpCoeff;
//通道3零漂
extern CString g_sLangID_Native_Channel3ZeroOffset;
extern CString g_sLangTxt_Native_Channel3ZeroOffset;
//波形选择
extern CString g_sLangID_Native_WaveformSelection;
extern CString g_sLangTxt_Native_WaveformSelection;
//档位
extern CString g_sLangID_Native_Gear;
extern CString g_sLangTxt_Native_Gear;
//模块编号2
extern CString g_sLangID_Native_ModuleNo2;
extern CString g_sLangTxt_Native_ModuleNo2;
//温区2
extern CString g_sLangID_Native_TempZone2;
extern CString g_sLangTxt_Native_TempZone2;
//通道编号2
extern CString g_sLangID_Native_ChannelNo2;
extern CString g_sLangTxt_Native_ChannelNo2;
//档位2
extern CString g_sLangID_Native_Gear2;
extern CString g_sLangTxt_Native_Gear2;
//输出通道
extern CString g_sLangID_Native_OutputChannel;
extern CString g_sLangTxt_Native_OutputChannel;
//硬件档位
extern CString g_sLangID_Native_HardwareGear;
extern CString g_sLangTxt_Native_HardwareGear;
//模块编号
extern CString g_sLangID_Native_ModuleNumber;
extern CString g_sLangTxt_Native_ModuleNumber;
//切换模式
extern CString g_sLangID_Native_SwitchMode;
extern CString g_sLangTxt_Native_SwitchMode;
//开出1导通值
extern CString g_sLangID_Native_Output1ConductValue;
extern CString g_sLangTxt_Native_Output1ConductValue;
//开出2导通值
extern CString g_sLangID_Native_Output2ConductValue;
extern CString g_sLangTxt_Native_Output2ConductValue;
//开出3导通值
extern CString g_sLangID_Native_Output3ConductValue;
extern CString g_sLangTxt_Native_Output3ConductValue;
//开出4导通值
extern CString g_sLangID_Native_Output4ConductValue;
extern CString g_sLangTxt_Native_Output4ConductValue;
//开出5导通值
extern CString g_sLangID_Native_Output5ConductValue;
extern CString g_sLangTxt_Native_Output5ConductValue;
//开出6导通值
extern CString g_sLangID_Native_Output6ConductValue;
extern CString g_sLangTxt_Native_Output6ConductValue;
//开出7导通值
extern CString g_sLangID_Native_Output7ConductValue;
extern CString g_sLangTxt_Native_Output7ConductValue;
//开出8导通值
extern CString g_sLangID_Native_Output8ConductValue;
extern CString g_sLangTxt_Native_Output8ConductValue;
//寄存器地址(16进制)
extern CString g_sLangID_Native_RegAddrHex;
extern CString g_sLangTxt_Native_RegAddrHex;
//寄存器值(16进制)
extern CString g_sLangID_Native_RegValHex;
extern CString g_sLangTxt_Native_RegValHex;
//结果
extern CString g_sLangID_Native_Results;
extern CString g_sLangTxt_Native_Results;
//开出翻转延时
extern CString g_sLangID_Native_FlipDelay;
extern CString g_sLangTxt_Native_FlipDelay;
//开入量翻转判别条件
extern CString g_sLangID_Native_InFlipCond;
extern CString g_sLangTxt_Native_InFlipCond;
//是否为顺序状态序列
extern CString g_sLangID_Native_IsSeqStateSeq;
extern CString g_sLangTxt_Native_IsSeqStateSeq;
//重复次数
extern CString g_sLangID_Native_RepeatCount;
extern CString g_sLangTxt_Native_RepeatCount;
//状态数
extern CString g_sLangID_Native_StateNum;
extern CString g_sLangTxt_Native_StateNum;
//开入扩展
extern CString g_sLangID_Native_InputExpand;
extern CString g_sLangTxt_Native_InputExpand;
//次动作时间
extern CString g_sLangID_Native_NActionTime;
extern CString g_sLangTxt_Native_NActionTime;
//循环序号
extern CString g_sLangID_Native_LoopNum;
extern CString g_sLangTxt_Native_LoopNum;
//状态序号
extern CString g_sLangID_Native_StateNums;
extern CString g_sLangTxt_Native_StateNums;
//过流I段定值
extern CString g_sLangID_Native_OverCurrentI;
extern CString g_sLangTxt_Native_OverCurrentI;
//过流II段定值
extern CString g_sLangID_Native_OverCurrentII;
extern CString g_sLangTxt_Native_OverCurrentII;
//过流III段定值
extern CString g_sLangID_Native_OverCurrentIII;
extern CString g_sLangTxt_Native_OverCurrentIII;
//过流IV段定值
extern CString g_sLangID_Native_OverCurrentIV;
extern CString g_sLangTxt_Native_OverCurrentIV;
//过流I段时间
extern CString g_sLangID_Native_OverCurrentITime;
extern CString g_sLangTxt_Native_OverCurrentITime;
//过流II段时间
extern CString g_sLangID_Native_OverCurrentIITime;
extern CString g_sLangTxt_Native_OverCurrentIITime;
//过流III段时间
extern CString g_sLangID_Native_OverCurrentIIITime;
extern CString g_sLangTxt_Native_OverCurrentIIITime;
//过流IV段时间
extern CString g_sLangID_Native_OverCurrentIVTime;
extern CString g_sLangTxt_Native_OverCurrentIVTime;
//分组
extern CString g_sLangID_Native_Grouping;
extern CString g_sLangTxt_Native_Grouping;
//整定动作电流(表达式)
extern CString g_sLangID_Native_SetActCurExp;
extern CString g_sLangTxt_Native_SetActCurExp;
//过流值
extern CString g_sLangID_Native_OverCurrentValue;
extern CString g_sLangTxt_Native_OverCurrentValue;

//第八周吕
extern CString g_sLangID_Native_volDefinition1;
extern CString g_sLangTxt_Native_volDefinition1;// 电压定义
extern CString g_sLangID_Native_refphase;
extern CString g_sLangTxt_Native_refphase;//参考相
extern CString g_sLangID_Native_transfConnection;
extern CString g_sLangTxt_Native_transfConnection;//变压器接线方式
extern CString g_sLangID_Native_maxSyncTime1;
extern CString g_sLangTxt_Native_maxSyncTime1;//最大同步时间
extern CString g_sLangID_Native_breaker4HoldTime;
extern CString g_sLangTxt_Native_breaker4HoldTime;//开出4保持时间
extern CString g_sLangID_Native_Grid_Vol;
extern CString g_sLangTxt_Native_Grid_Vol;//待并侧电压Grid_Vol
extern CString g_sLangID_Native_Grid_Freq;
extern CString g_sLangTxt_Native_Grid_Freq;//待并侧频率Grid_Freq
extern CString g_sLangID_Native_syncSignal;
extern CString g_sLangTxt_Native_syncSignal;//同期信号
extern CString g_sLangID_Native_boostSignal;
extern CString g_sLangTxt_Native_boostSignal;//增压信号
extern CString g_sLangID_Native_boostFreqSignal;
extern CString g_sLangTxt_Native_boostFreqSignal;//增频信号
extern CString g_sLangID_Native_reducePresSignal;
extern CString g_sLangTxt_Native_reducePresSignal;//减压信号
extern CString g_sLangID_Native_reduceFreqSignal;
extern CString g_sLangTxt_Native_reduceFreqSignal;//减频信号
extern CString g_sLangID_Native_OutPut;
extern CString g_sLangTxt_Native_OutPut;//开出%d
extern CString g_sLangID_Native_GvolChangeStep;
extern CString g_sLangTxt_Native_GvolChangeStep;//待并侧电压变化步长
extern CString g_sLangID_Native_GridVol_Exp;
extern CString g_sLangTxt_Native_GridVol_Exp;//待并侧电压(表达式)
extern CString g_sLangID_Native_GridFreq_Exp;
extern CString g_sLangTxt_Native_GridFreq_Exp;//待并侧频率(表达式)
extern CString g_sLangID_Native_GvolChangeStepExp;
extern CString g_sLangTxt_Native_GvolChangeStepExp;//待并侧电压变化步长(表达式)
extern CString g_sLangID_Native_GfreqChangeStep;
extern CString g_sLangTxt_Native_GfreqChangeStep;//待并侧频率变化步长
extern CString g_sLangID_Native_GfreqChangeStepExp;
extern CString g_sLangTxt_Native_GfreqChangeStepExp;//待并侧频率变化步长(表达式)
extern CString g_sLangID_Native_FreqSlip;
extern CString g_sLangTxt_Native_FreqSlip;//频率滑差
extern CString g_sLangID_Native_VoltSlip_Exp;
extern CString g_sLangTxt_Native_VoltSlip_Exp;//电压滑差(表达式)
extern CString g_sLangID_Native_FreqSlip_Exp;
extern CString g_sLangTxt_Native_FreqSlip_Exp;//频率滑差(表达式)
extern CString g_sLangID_Native_RegulatePulseWidth;
extern CString g_sLangTxt_Native_RegulatePulseWidth;//调压脉宽
extern CString g_sLangID_Native_FrequencyPulseWidth;
extern CString g_sLangTxt_Native_FrequencyPulseWidth;//调频脉宽

//2
extern CString g_sLangID_Native_AngleStartPar1;
extern CString g_sLangTxt_Native_AngleStartPar1;//功角始值
extern CString g_sLangID_Native_AngleEndPar1;
extern CString g_sLangTxt_Native_AngleEndPar1;//功角终值
extern CString g_sLangID_Native_OscilPeriod1;
extern CString g_sLangTxt_Native_OscilPeriod1;//振荡周期
extern CString g_sLangID_Native_TripAccessPoint;
extern CString g_sLangTxt_Native_TripAccessPoint;//跳闸接入点
extern CString g_sLangID_Native_ReOscillat_ornot;
extern CString g_sLangTxt_Native_ReOscillat_ornot;//是否往复振荡
extern CString g_sLangID_Native_SpeedChange;
extern CString g_sLangTxt_Native_SpeedChange; // 速度变化选择
extern CString g_sLangID_Native_ImpedanceChange_ornot;
extern CString g_sLangTxt_Native_ImpedanceChange_ornot; //是否变阻抗
extern CString g_sLangID_Native_ImpedanceRateChange;
extern CString g_sLangTxt_Native_ImpedanceRateChange; // 阻抗变化率

extern CString g_sLangID_Native_zeroseq_comp_calculat1;
extern CString g_sLangTxt_Native_zeroseq_comp_calculat1;//零序补偿系数计算方式
extern CString g_sLangID_Native_ZeroSeqComp1;
extern CString g_sLangTxt_Native_ZeroSeqComp1;//零序补偿系数(|K0|$KR$|Z0/Z1|)
extern CString g_sLangID_Native_ZeroSeqComp2;
extern CString g_sLangTxt_Native_ZeroSeqComp2;//零序补偿系数(Phi(K0)$KX$Phi(Z0/Z1))
extern CString g_sLangID_Native_SysImpedAngle;
extern CString g_sLangTxt_Native_SysImpedAngle; // 系统侧阻抗角
extern CString g_sLangID_Native_TransImpedAngle;
extern CString g_sLangTxt_Native_TransImpedAngle; // 变压器阻抗角
extern CString g_sLangID_Native_GeneTransImped;
extern CString g_sLangTxt_Native_GeneTransImped; // 发电机暂态阻抗

extern CString g_sLangID_Out4_Situation;
extern CString g_sLangTxt_Out4_Situation;//开出4状态
extern CString g_sLangID_Out5_Situation;
extern CString g_sLangTxt_Out5_Situation;//开出5状态
extern CString g_sLangID_Out6_Situation;
extern CString g_sLangTxt_Out6_Situation;//开出6状态
extern CString g_sLangID_Out7_Situation;
extern CString g_sLangTxt_Out7_Situation;//开出7状态
extern CString g_sLangID_Out8_Situation;
extern CString g_sLangTxt_Out8_Situation;//开出8状态
extern CString g_sLangID_Native_ProtRelayTime1;
extern CString g_sLangTxt_Native_ProtRelayTime1;//保护出口时间
extern CString g_sLangID_Native_AccelSigOutTime1;
extern CString g_sLangTxt_Native_AccelSigOutTime1;//加速信号出口时间
extern CString g_sLangID_Native_DecelSigOutTime1;
extern CString g_sLangTxt_Native_DecelSigOutTime1;//减速信号出口时间

//3
extern CString g_sLangID_Native_VariablePhaseChange;
extern CString g_sLangTxt_Native_VariablePhaseChange; // 递变相别
extern CString g_sLangID_Native_PreTestTimeS;
extern CString g_sLangTxt_Native_PreTestTimeS; // 测试前时间(秒)
extern CString g_sLangID_Native_FaultPreTimeS;
extern CString g_sLangTxt_Native_FaultPreTimeS; // 故障前时间(秒)
extern CString g_sLangID_Native_FaultPreUIPhaseAngle;
extern CString g_sLangTxt_Native_FaultPreUIPhaseAngle;//故障前电压电流相角(U-I)
extern CString g_sLangID_Native_VariableMode0123;
extern CString g_sLangTxt_Native_VariableMode0123; //递变模式(0-单机模式1-电压递变 2-电流递变 3-单机分组模式)
extern CString g_sLangID_Native_TestReturnCoefficient;
extern CString g_sLangTxt_Native_TestReturnCoefficient;//测试返回系数
extern CString g_sLangID_Native_TestChannelType;
extern CString g_sLangTxt_Native_TestChannelType;//测试通道类型
extern CString g_sLangID_Native_VariableType;
extern CString g_sLangTxt_Native_VariableType;//递变类型

extern CString g_sLangID_Native_PhaseShiftDir01;
extern CString g_sLangTxt_Native_PhaseShiftDir01; //相位递变方向(0:逆时针 1:顺时针)
extern CString g_sLangID_Native_IBeforeChange;
extern CString g_sLangTxt_Native_IBeforeChange;//变化前电流幅值
extern CString g_sLangID_Native_FaultGroup1VAmp;
extern CString g_sLangTxt_Native_FaultGroup1VAmp; //故障态组1电压幅值
extern CString g_sLangID_Native_FaultGroup1IAmp;
extern CString g_sLangTxt_Native_FaultGroup1IAmp;//故障态组1电流幅值
extern CString g_sLangID_Native_FaultGroupIPhaseDiff;
extern CString g_sLangTxt_Native_FaultGroupIPhaseDiff; //故障态两组电流角差
extern CString g_sLangID_Native_FaultGroupFreq;
extern CString g_sLangTxt_Native_FaultGroupFreq;//故障态频率

extern CString g_sLangID_Native_VActionValueAbsErr;
extern CString g_sLangTxt_Native_VActionValueAbsErr;//电压动作值绝对误差
extern CString g_sLangID_Native_VActionValueRelErr;
extern CString g_sLangTxt_Native_VActionValueRelErr;//电压动作值相对误差
extern CString g_sLangID_Native_VActionValueErrLogic;
extern CString g_sLangTxt_Native_VActionValueErrLogic;//电压动作值误差判断逻辑
extern CString g_sLangID_Native_IActionValueAbsErr;
extern CString g_sLangTxt_Native_IActionValueAbsErr;//电流动作值绝对误差
extern CString g_sLangID_Native_IActionValueRelErr;
extern CString g_sLangTxt_Native_IActionValueRelErr;//电流动作值相对误差
extern CString g_sLangID_Native_IActionValueErrLogic;
extern CString g_sLangTxt_Native_IActionValueErrLogic;//电流动作值误差判断逻辑
extern CString g_sLangID_Native_CoefficientAbsErr;
extern CString g_sLangTxt_Native_CoefficientAbsErr; //返回系数绝对误差
extern CString g_sLangID_Native_CoefficientRelErr;
extern CString g_sLangTxt_Native_CoefficientRelErr;//返回系数相对误差
extern CString g_sLangID_Native_CoefficientErrLogic;
extern CString g_sLangTxt_Native_CoefficientErrLogic;//返回系数误差判断逻辑


extern CString g_sLangID_Native_relativeErr;
extern CString g_sLangTxt_Native_relativeErr;//相对误差有效
extern CString g_sLangID_Native_criteria_logic;
extern CString g_sLangTxt_Native_criteria_logic;//判据逻辑
extern CString g_sLangID_Native_VActionValueErr;
extern CString g_sLangTxt_Native_VActionValueErr;//电压动作值误差
extern CString g_sLangID_Native_IActionValueErr;
extern CString g_sLangTxt_Native_IActionValueErr;//电流动作值误差
extern CString g_sLangID_Native_input1_ActionVal;
extern CString g_sLangTxt_Native_input1_ActionVal;//开入1动作值
extern CString g_sLangID_Native_input2_ActionVal;
extern CString g_sLangTxt_Native_input2_ActionVal;//开入2动作值
extern CString g_sLangID_Native_input3_ActionVal;
extern CString g_sLangTxt_Native_input3_ActionVal;//开入3动作值
extern CString g_sLangID_Native_input4_ActionVal;
extern CString g_sLangTxt_Native_input4_ActionVal;//开入4动作值
extern CString g_sLangID_Native_input5_ActionVal;
extern CString g_sLangTxt_Native_input5_ActionVal;//开入5动作值
extern CString g_sLangID_Native_input6_ActionVal;
extern CString g_sLangTxt_Native_input6_ActionVal;//开入6动作值
extern CString g_sLangID_Native_input7_ActionVal;
extern CString g_sLangTxt_Native_input7_ActionVal;//开入7动作值
extern CString g_sLangID_Native_input8_ActionVal;
extern CString g_sLangTxt_Native_input8_ActionVal;//开入8动作值


//4
extern CString g_sLangID_Native_YNaging_test;
extern CString g_sLangTxt_Native_YNaging_test;//是否老化试验
extern CString g_sLangID_Native_varchannel_select;
extern CString g_sLangTxt_Native_varchannel_select;//递变通道选择
extern CString g_sLangID_Native_vartype_select;
extern CString g_sLangTxt_Native_vartype_select;//递变类型选择
extern CString g_sLangID_Native_change_mode;
extern CString g_sLangTxt_Native_change_mode;//变化模式
extern CString g_sLangID_Native_step_time;
extern CString g_sLangTxt_Native_step_time;//每步时间
extern CString g_sLangID_Native_trigger_delay;
extern CString g_sLangTxt_Native_trigger_delay;//触发延时
extern CString g_sLangID_Native_YN_locked;
extern CString g_sLangTxt_Native_YN_locked;//是否锁定
extern CString g_sLangID_Native_YN_autoevo;
extern CString g_sLangTxt_Native_YN_autoevo;//是否自动递变
extern CString g_sLangID_Native_max_outputtime;
extern CString g_sLangTxt_Native_max_outputtime;//最长输出时间(s)
extern CString g_sLangID_Native_acttuning_time;
extern CString g_sLangTxt_Native_acttuning_time;//动作整定时间
extern CString g_sLangID_Native_ActTimeValueAbsErr;
extern CString g_sLangTxt_Native_ActTimeValueAbsErr;//动作时间值绝对误差
extern CString g_sLangID_Native_ActTimeValueRelErr;
extern CString g_sLangTxt_Native_ActTimeValueRelErr;//动作时间值相对误差
extern CString g_sLangID_Native_ActTimeValueErrLogic;
extern CString g_sLangTxt_Native_ActTimeValueErrLogic;//动作时间误差判断逻辑
extern CString g_sLangID_Native_PhaseActValueAbsErr;
extern CString g_sLangTxt_Native_PhaseActValueAbsErr;//相位动作值绝对误差
extern CString g_sLangID_Native_PhaseActValueRelErr;
extern CString g_sLangTxt_Native_PhaseActValueRelErr;//相位动作值相对误差
extern CString g_sLangID_Native_PhaseActValueErrLogic;
extern CString g_sLangTxt_Native_PhaseActValueErrLogic;//相位动作值误差判断逻辑
extern CString g_sLangID_Native_action_mark;
extern CString g_sLangTxt_Native_action_mark;//动作标记
extern CString g_sLangID_Native_result_status;
extern CString g_sLangTxt_Native_result_status;//结果状态
extern CString g_sLangID_Native_extend;
extern CString g_sLangTxt_Native_extend;//扩展%d

//5
extern CString g_sLangID_Native_KeepTime;
extern CString g_sLangTxt_Native_KeepTime;//保持时间
extern CString g_sLangID_Native_SteadyTime;
extern CString g_sLangTxt_Native_SteadyTime;//稳态时间
extern CString g_sLangID_Native_LowFreActValue;
extern CString g_sLangTxt_Native_LowFreActValue;//低频动作值
extern CString g_sLangID_Native_InputASelect;
extern CString g_sLangTxt_Native_InputASelect;//开入A-J选择
extern CString g_sLangID_Native_InputBSelect;
extern CString g_sLangTxt_Native_InputBSelect;
extern CString g_sLangID_Native_InputCSelect;
extern CString g_sLangTxt_Native_InputCSelect;
extern CString g_sLangID_Native_InputDSelect;
extern CString g_sLangTxt_Native_InputDSelect;
extern CString g_sLangID_Native_InputESelect;
extern CString g_sLangTxt_Native_InputESelect;
extern CString g_sLangID_Native_InputFSelect;
extern CString g_sLangTxt_Native_InputFSelect;
extern CString g_sLangID_Native_InputGSelect;
extern CString g_sLangTxt_Native_InputGSelect;
extern CString g_sLangID_Native_InputHSelect;
extern CString g_sLangTxt_Native_InputHSelect;
extern CString g_sLangID_Native_InputISelect;
extern CString g_sLangTxt_Native_InputISelect;
extern CString g_sLangID_Native_InputJSelect;
extern CString g_sLangTxt_Native_InputJSelect;
extern CString g_sLangID_Native_FreInitialValue;
extern CString g_sLangTxt_Native_FreInitialValue;//频率变化始值
extern CString g_sLangID_Native_FreFinalValue;
extern CString g_sLangTxt_Native_FreFinalValue;//频率变化终值
extern CString g_sLangID_Native_FreChangeStep;
extern CString g_sLangTxt_Native_FreChangeStep;//频率变化步长
extern CString g_sLangID_Native_FreFinal;
extern CString g_sLangTxt_Native_FreFinal;//频率终值
extern CString g_sLangID_Native_IChangePhase;
extern CString g_sLangTxt_Native_IChangePhase;//电流变化相
extern CString g_sLangID_Native_SearchslipVal;
extern CString g_sLangTxt_Native_SearchslipVal;//当前搜索滑差值(dfdt)
extern CString g_sLangID_Native_KeepTimeExp;
extern CString g_sLangTxt_Native_KeepTimeExp;//保持时间(表达式)

extern CString g_sLangID_Native_FreInitialValueExp;
extern CString g_sLangTxt_Native_FreInitialValueExp;//频率变化始值(表达式)
extern CString g_sLangID_Native_FreFinalValueExp;
extern CString g_sLangTxt_Native_FreFinalValueExp;//频率变化终值(表达式)
extern CString g_sLangID_Native_FreChangeStepExp;
extern CString g_sLangTxt_Native_FreChangeStepExp;//频率变化步长(表达式)
extern CString g_sLangID_Native_SlipInitialValueExp;
extern CString g_sLangTxt_Native_SlipInitialValueExp;//滑差变化始值(表达式)
extern CString g_sLangID_Native_SlipFinalValueExp;
extern CString g_sLangTxt_Native_SlipFinalValueExp;//滑差变化终值(表达式)
extern CString g_sLangID_Native_SlipChangeStepExp;
extern CString g_sLangTxt_Native_SlipChangeStepExp;//滑差变化步长(表达式)
extern CString g_sLangID_Native_IInitialValueExp;
extern CString g_sLangTxt_Native_IInitialValueExp;//电流变化始值(表达式)
extern CString g_sLangID_Native_IFinalValueExp;
extern CString g_sLangTxt_Native_IFinalValueExp;//电流变化终值(表达式)
extern CString g_sLangID_Native_IChangeStepExp;
extern CString g_sLangTxt_Native_IChangeStepExp;//电流变化步长(表达式)
extern CString g_sLangID_Native_VInitialValueExp;
extern CString g_sLangTxt_Native_VInitialValueExp;//电压变化始值(表达式)
extern CString g_sLangID_Native_VFinalValueExp;
extern CString g_sLangTxt_Native_VFinalValueExp;//电压变化终值(表达式)
extern CString g_sLangID_Native_VChangeStepExp;
extern CString g_sLangTxt_Native_VChangeStepExp;//电压变化步长(表达式)
extern CString g_sLangID_Native_FreActValue;
extern CString g_sLangTxt_Native_FreActValue;//频率动作值
extern CString g_sLangID_Native_LowCycleActDesc;
extern CString g_sLangTxt_Native_LowCycleActDesc;//低周动作描述
extern CString g_sLangID_Native_SlipActValue;
extern CString g_sLangTxt_Native_SlipActValue;//滑差动作值
extern CString g_sLangID_Native_IBlockValue;
extern CString g_sLangTxt_Native_IBlockValue;//电流闭锁值
extern CString g_sLangID_Native_VBlockValue;
extern CString g_sLangTxt_Native_VBlockValue;//电压闭锁值

//6
extern CString g_sLangID_Native_VChangeRate_blockVal;
extern CString g_sLangTxt_Native_VChangeRate_blockVal;//电压变化率闭锁值
extern CString g_sLangID_Native_SearchslipVal2;
extern CString g_sLangTxt_Native_SearchslipVal2;//当前搜索滑差值(dvdt)
extern CString g_sLangID_Native_LowVActionDesc;
extern CString g_sLangTxt_Native_LowVActionDesc;//低压动作描述

extern CString g_sLangID_Native_Uab1Amp;
extern CString g_sLangTxt_Native_Uab1Amp;//Uab1幅值
extern CString g_sLangID_Native_Uab1Ph;
extern CString g_sLangTxt_Native_Uab1Ph;//Uab1相位
extern CString g_sLangID_Native_Uab1Fre;
extern CString g_sLangTxt_Native_Uab1Fre;//Uab1频率
extern CString g_sLangID_Native_3U0_1Amp;
extern CString g_sLangTxt_Native_3U0_1Amp;//3U0_1幅值
extern CString g_sLangID_Native_3U0_1Ph;
extern CString g_sLangTxt_Native_3U0_1Ph;//3U0_1相位
extern CString g_sLangID_Native_3U0_1Fre;
extern CString g_sLangTxt_Native_3U0_1Fre;//3U0_1频率
extern CString g_sLangID_Native_Uab2Amp;
extern CString g_sLangTxt_Native_Uab2Amp;//Uab2幅值
extern CString g_sLangID_Native_Uab2Ph;
extern CString g_sLangTxt_Native_Uab2Ph;//Uab2相位
extern CString g_sLangID_Native_Uab2Fre;
extern CString g_sLangTxt_Native_Uab2Fre;//Uab2频率
extern CString g_sLangID_Native_3U0_2Amp;
extern CString g_sLangTxt_Native_3U0_2Amp;//3U0_2幅值
extern CString g_sLangID_Native_3U0_2Ph;
extern CString g_sLangTxt_Native_3U0_2Ph;//3U0_2相位
extern CString g_sLangID_Native_3U0_2Fre;
extern CString g_sLangTxt_Native_3U0_2Fre;//3U0_2频率
extern CString g_sLangID_Native_Ia1Fre;
extern CString g_sLangTxt_Native_Ia1Fre;//Ia1频率
extern CString g_sLangID_Native_Ib1Fre;
extern CString g_sLangTxt_Native_Ib1Fre;//Ib1频率
extern CString g_sLangID_Native_Ic1Fre;
extern CString g_sLangTxt_Native_Ic1Fre;//Ic1频率
extern CString g_sLangID_Native_Ia2Fre;
extern CString g_sLangTxt_Native_Ia2Fre;//Ia2频率
extern CString g_sLangID_Native_Ib2Fre;
extern CString g_sLangTxt_Native_Ib2Fre;//Ib2频率
extern CString g_sLangID_Native_Ic2Fre;
extern CString g_sLangTxt_Native_Ic2Fre;//Ic2频率

extern CString g_sLangID_Native_AuxiDCI;
extern CString g_sLangTxt_Native_AuxiDCI;//辅助直流电流
extern CString g_sLangID_Native_AuxiDCV;
extern CString g_sLangTxt_Native_AuxiDCV;//辅助直流电压

//
extern CString g_sLangID_Native_syspowerImp;
extern CString g_sLangTxt_Native_syspowerImp;//系统电源阻抗
extern CString g_sLangID_Native_syspowerImpangle;
extern CString g_sLangTxt_Native_syspowerImpangle;//系统电源阻抗角
extern CString g_sLangID_Native_syscomputModel012;
extern CString g_sLangTxt_Native_syscomputModel012;//系统计算模型(0-电流不变 1-电压不变 2-系统阻抗不变)
extern CString g_sLangID_Native_fault_switchtime;
extern CString g_sLangTxt_Native_fault_switchtime;//故障转换时间
extern CString g_sLangID_Native_switchErrtype;
extern CString g_sLangTxt_Native_switchErrtype;//转换故障类型
extern CString g_sLangID_Native_switchErr_shortImp;
extern CString g_sLangTxt_Native_switchErr_shortImp;//转换故障短路阻抗
extern CString g_sLangID_Native_switchErr_shortImpAng;
extern CString g_sLangTxt_Native_switchErr_shortImpAng;//转换故障短路阻抗角
extern CString g_sLangID_Native_switchErr_shortI;
extern CString g_sLangTxt_Native_switchErr_shortI;//转换故障短路电流
extern CString g_sLangID_Native_switchErr_shortV;
extern CString g_sLangTxt_Native_switchErr_shortV;//转换故障短路电压
extern CString g_sLangID_Native_switchErr_direction;
extern CString g_sLangTxt_Native_switchErr_direction;//转换故障故障方向
extern CString g_sLangID_Native_testprocess;
extern CString g_sLangTxt_Native_testprocess;//试验过程
extern CString g_sLangID_Native_redundancy_mode;
extern CString g_sLangTxt_Native_redundancy_mode;//重合方式
extern CString g_sLangID_Native_redundancy_duration;
extern CString g_sLangTxt_Native_redundancy_duration;//重合持续时间
extern CString g_sLangID_Native_postswitch_duration;
extern CString g_sLangTxt_Native_postswitch_duration;//后加速开关跳开后持续时间


extern CString g_sLangID_Native_change_startangle;
extern CString g_sLangTxt_Native_change_startangle;//变化起始角度
extern CString g_sLangID_Native_change_endangle;
extern CString g_sLangTxt_Native_change_endangle;//变化终止角度
extern CString g_sLangID_Native_impedanceAng_measured;
extern CString g_sLangTxt_Native_impedanceAng_measured;//待测阻抗角度定值
extern CString g_sLangID_Native_search_way;
extern CString g_sLangTxt_Native_search_way;//搜索方式
extern CString g_sLangID_Native_Zsearch_startAng;
extern CString g_sLangTxt_Native_Zsearch_startAng;//Z搜索起点角度
extern CString g_sLangID_Native_Zsearch_startAct;
extern CString g_sLangTxt_Native_Zsearch_startAct;//Z搜索起点动作
extern CString g_sLangID_Native_ZAng_currentVal;
extern CString g_sLangTxt_Native_ZAng_currentVal;//Z当前值角度
extern CString g_sLangID_Native_Zsearch_endAng;
extern CString g_sLangTxt_Native_Zsearch_endAng;//Z搜索终点角度
extern CString g_sLangID_Native_Zsearch_endAct;
extern CString g_sLangTxt_Native_Zsearch_endAct;//Z搜索终点动作
extern CString g_sLangID_Native_action_impedance;
extern CString g_sLangTxt_Native_action_impedance;//动作阻抗
extern CString g_sLangID_Native_action_impedanceAng;
extern CString g_sLangTxt_Native_action_impedanceAng;//动作阻抗角
extern CString g_sLangID_Native_Desc_impedance_Act;
extern CString g_sLangTxt_Native_Desc_impedance_Act;//阻抗动作描述

//
extern CString g_sLangID_Native_impedance_setting;
extern CString g_sLangTxt_Native_impedance_setting;//阻抗定值
extern CString g_sLangID_Native_impedance_setExp;
extern CString g_sLangTxt_Native_impedance_setExp;//阻抗定值(表达式)

extern CString g_sLangID_Native_ZeroSeqCompExp;
extern CString g_sLangTxt_Native_ZeroSeqCompExp;//零序补偿系数表达方式
extern CString g_sLangID_Native_ZeroSeqComp_RERL;
extern CString g_sLangTxt_Native_ZeroSeqComp_RERL;//零序补偿系数RE/RL
extern CString g_sLangID_Native_ZeroSeqComp_XEXL;
extern CString g_sLangTxt_Native_ZeroSeqComp_XEXL;//零序补偿系数XE/XL
extern CString g_sLangID_Native_load_current;
extern CString g_sLangTxt_Native_load_current;//负荷电流
extern CString g_sLangID_Native_loadpowerAng;
extern CString g_sLangTxt_Native_loadpowerAng;//负荷功角
extern CString g_sLangID_Native_PT_installPos;
extern CString g_sLangTxt_Native_PT_installPos;//PT安装位置
extern CString g_sLangID_Native_closeAngmode01;
extern CString g_sLangTxt_Native_closeAngmode01;//合闸角方式( 0-随机 1-定值)
extern CString g_sLangID_Native_closing_angle;
extern CString g_sLangTxt_Native_closing_angle;//合闸角
extern CString g_sLangID_Native_Vz_outputDef;
extern CString g_sLangTxt_Native_Vz_outputDef;//Vz输出定义
extern CString g_sLangID_Native_Vz_referPhase;
extern CString g_sLangTxt_Native_Vz_referPhase;//Vz参考相
extern CString g_sLangID_Native_Vz_phase_angle;
extern CString g_sLangTxt_Native_Vz_phase_angle;//Vz相角
extern CString g_sLangID_Native_reclose_timeset;
extern CString g_sLangTxt_Native_reclose_timeset;//重合闸时间定值
extern CString g_sLangID_Native_PostAccelerat_TimeSet;
extern CString g_sLangTxt_Native_PostAccelerat_TimeSet;//后加速时间定值

extern CString g_sLangID_Native_auxiV_UxoutputMode;
extern CString g_sLangTxt_Native_auxiV_UxoutputMode;//辅助电压Ux输出方式
extern CString g_sLangID_Native_synchronous_VAmp;
extern CString g_sLangTxt_Native_synchronous_VAmp;//同期电压幅值(检同期方式有效)
extern CString g_sLangID_Native_synchronous_VPh;
extern CString g_sLangTxt_Native_synchronous_VPh;//同期电压相位(检同期方式有效)
extern CString g_sLangID_Native_pressTestVal;
extern CString g_sLangTxt_Native_pressTestVal;//有压测试值
extern CString g_sLangID_Native_NOpressTestVal;
extern CString g_sLangTxt_Native_NOpressTestVal;//无压测试值
extern CString g_sLangID_Native_openflip_Control;
extern CString g_sLangTxt_Native_openflip_Control;//开出翻转控制方式
extern CString g_sLangID_Native_openflip_delay;
extern CString g_sLangTxt_Native_openflip_delay;//开出翻转延时
extern CString g_sLangID_Native_input_selection;
extern CString g_sLangTxt_Native_input_selection;//开入量选择
extern CString g_sLangID_Native_superimposed_ornot1;
extern CString g_sLangTxt_Native_superimposed_ornot1;//是否叠加非周期分量
extern CString g_sLangID_Native_jumpctrl;
extern CString g_sLangTxt_Native_jumpctrl;//跳合信号控制
extern CString g_sLangID_Native_timectrl;
extern CString g_sLangTxt_Native_timectrl;//时间控制
extern CString g_sLangID_Native_totalweight;
extern CString g_sLangTxt_Native_totalweight;//综重（单重+三重）
extern CString g_sLangID_Native_tripleweight;
extern CString g_sLangTxt_Native_tripleweight;//三重
extern CString g_sLangID_Native_norepeat;
extern CString g_sLangTxt_Native_norepeat;//不重合
extern CString g_sLangID_Native_Totransformer;
extern CString g_sLangTxt_Native_Totransformer;//指向变压器
extern CString g_sLangID_Native_lagrange;
extern CString g_sLangTxt_Native_lagrange;//拉格朗日插值法
extern CString g_sLangID_Native_linear;
extern CString g_sLangTxt_Native_linear;//线性插值法
extern CString g_sLangID_Native_faultvoltype;
extern CString g_sLangTxt_Native_faultvoltype;//故障电压类型

extern CString g_sLangID_Native_Difsetting;
extern CString g_sLangTxt_Native_Difsetting;//差动定值整定方式
extern CString g_sLangID_Native_DifCurChoose;
extern CString g_sLangTxt_Native_DifCurChoose;//差动基准电流选择
extern CString g_sLangID_Native_harmonicnumber;
extern CString g_sLangTxt_Native_harmonicnumber;//谐波次数选择
extern CString g_sLangID_Native_CuroutputPhase;
extern CString g_sLangTxt_Native_CuroutputPhase;//电流输出相
extern CString g_sLangID_Native_PhaseAshort;
extern CString g_sLangTxt_Native_PhaseAshort;//A相短路
extern CString g_sLangID_Native_PhaseBshort;
extern CString g_sLangTxt_Native_PhaseBshort;//B相短路
extern CString g_sLangID_Native_PhaseCshort;
extern CString g_sLangTxt_Native_PhaseCshort;//C相短路
extern CString g_sLangID_Native_PhaseABCshort;
extern CString g_sLangTxt_Native_PhaseABCshort;//ABC相短路

//第八周许
extern CString g_sLangID_Native_ExceptionMsgSet;
extern CString g_sLangTxt_Native_ExceptionMsgSet;
//特性图
extern CString g_sLangID_Native_CharacteristicGraph;
extern CString g_sLangTxt_Native_CharacteristicGraph;
//过压I段定值
extern CString g_sLangID_Native_OV1SetValue;
extern CString g_sLangTxt_Native_OV1SetValue;
//过压II段定值

extern CString g_sLangID_Native_OV2SetValue;
extern CString g_sLangTxt_Native_OV2SetValue;
//过压III段定值
extern CString g_sLangID_Native_OV3SetValue;
extern CString g_sLangTxt_Native_OV3SetValue;
//过压IV段定值
extern CString g_sLangID_Native_OV4SetValue;
extern CString g_sLangTxt_Native_OV4SetValue;
//过压I段时间
extern CString g_sLangID_Native_OV1Time;
extern CString g_sLangTxt_Native_OV1Time;
//过压II段时间
extern CString g_sLangID_Native_OV2Time;
extern CString g_sLangTxt_Native_OV2Time;
//过压III段时间
extern CString g_sLangID_Native_OV3Time;
extern CString g_sLangTxt_Native_OV3Time;
//过压IV段时间
extern CString g_sLangID_Native_OV4Time;
extern CString g_sLangTxt_Native_OV4Time;
//是否模拟断路器延时
extern CString g_sLangID_Native_SimBrkDel;
extern CString g_sLangTxt_Native_SimBrkDel;
//断路器跳闸延时
extern CString g_sLangID_Native_BrkTripDel;
extern CString g_sLangTxt_Native_BrkTripDel;
//断路器合闸延时
extern CString g_sLangID_Native_BrkClsDel;
extern CString g_sLangTxt_Native_BrkClsDel;
//电压类型
extern CString g_sLangID_Native_VoltType;
extern CString g_sLangTxt_Native_VoltType;
//整定动作电压(表达式)
extern CString g_sLangID_Native_ActionVoltExpr;
extern CString g_sLangTxt_Native_ActionVoltExpr;
//A相动作时间
extern CString g_sLangID_Native_PhaseATime;
extern CString g_sLangTxt_Native_PhaseATime;
//B相动作时间
extern CString g_sLangID_Native_PhaseBTime;
extern CString g_sLangTxt_Native_PhaseBTime;
//C相动作时间
extern CString g_sLangID_Native_PhaseCTime;
extern CString g_sLangTxt_Native_PhaseCTime;
//重合闸动作时间
extern CString g_sLangID_Native_RecloseTime;
extern CString g_sLangTxt_Native_RecloseTime;
//开入E动作时间
extern CString g_sLangID_Native_InputETime;
extern CString g_sLangTxt_Native_InputETime;
//开入F动作时间
extern CString g_sLangID_Native_InputFTime;
extern CString g_sLangTxt_Native_InputFTime;
//开入G动作时间
extern CString g_sLangID_Native_InputGTime;
extern CString g_sLangTxt_Native_InputGTime;
//开入H动作时间
extern CString g_sLangID_Native_InputHTime;
extern CString g_sLangTxt_Native_InputHTime;
//开入A动作描述
extern CString g_sLangID_Native_InputADesc;
extern CString g_sLangTxt_Native_InputADesc;
//开入B动作描述
extern CString g_sLangID_Native_InputBDesc;
extern CString g_sLangTxt_Native_InputBDesc;
//开入C动作描述
extern CString g_sLangID_Native_InputCDesc;
extern CString g_sLangTxt_Native_InputCDesc;
//重合闸动作描述
extern CString g_sLangID_Native_ReclActDesc;
extern CString g_sLangTxt_Native_ReclActDesc;
//后加速动作时间
extern CString g_sLangID_Native_PostAccTime;
extern CString g_sLangTxt_Native_PostAccTime;
//后加速动作描述
extern CString g_sLangID_Native_PostAccDesc;
extern CString g_sLangTxt_Native_PostAccDesc;
//实际短路电流
extern CString g_sLangID_Native_ActShortCur;
extern CString g_sLangTxt_Native_ActShortCur;
//实际短路电压
extern CString g_sLangID_Native_ActShortVol;
extern CString g_sLangTxt_Native_ActShortVol;
//过压值
extern CString g_sLangID_Native_OverVoltVal;
extern CString g_sLangTxt_Native_OverVoltVal;
//Ua初值
extern CString g_sLangID_Native_UaInitVal;
extern CString g_sLangTxt_Native_UaInitVal;
//Ub初值
extern CString g_sLangID_Native_UbInitVal;
extern CString g_sLangTxt_Native_UbInitVal;
//Uc初值
extern CString g_sLangID_Native_UcInitVal;
extern CString g_sLangTxt_Native_UcInitVal;
//Uz初值
extern CString g_sLangID_Native_UzInitVal;
extern CString g_sLangTxt_Native_UzInitVal;
//Ia初值
extern CString g_sLangID_Native_IaInitVal;
extern CString g_sLangTxt_Native_IaInitVal;
//Ib初值
extern CString g_sLangID_Native_IbInitVal;
extern CString g_sLangTxt_Native_IbInitVal;
//Ic初值
extern CString g_sLangID_Native_IcInitVal;
extern CString g_sLangTxt_Native_IcInitVal;
//曲线段数
extern CString g_sLangID_Native_CurveSegments;
extern CString g_sLangTxt_Native_CurveSegments;
//递变通道
extern CString g_sLangID_Native_VarChnl;
extern CString g_sLangTxt_Native_VarChnl;
//计时曲线
extern CString g_sLangID_Native_TimingCurve;
extern CString g_sLangTxt_Native_TimingCurve;
//递变选择
extern CString g_sLangID_Native_VarSel;
extern CString g_sLangTxt_Native_VarSel;
//递变类型(0-斜率1-上升时间2-初值)
extern CString g_sLangID_Native_TransType;
extern CString g_sLangTxt_Native_TransType;
//递变曲线选择
extern CString g_sLangID_Native_CurveSelect;
extern CString g_sLangTxt_Native_CurveSelect;
//递变始值
extern CString g_sLangID_Native_StartValue;
extern CString g_sLangTxt_Native_StartValue;
//递变终值
extern CString g_sLangID_Native_EndValue;
extern CString g_sLangTxt_Native_EndValue;
//递变步长
extern CString g_sLangID_Native_StepSize;
extern CString g_sLangTxt_Native_StepSize;
//曲线
extern CString g_sLangID_Native_Curve;
extern CString g_sLangTxt_Native_Curve;
//斜率(A/ms)
extern CString g_sLangID_Native_Slope;
extern CString g_sLangTxt_Native_Slope;
//输出时间(ms)
extern CString g_sLangID_Native_OutputTimems;
extern CString g_sLangTxt_Native_OutputTimems;
//搜索起点
extern CString g_sLangID_Native_SearchStart;
extern CString g_sLangTxt_Native_SearchStart;
//当前值
extern CString g_sLangID_Native_CurrentValue;
extern CString g_sLangTxt_Native_CurrentValue;
//搜索终点
extern CString g_sLangID_Native_SearchEnd;
extern CString g_sLangTxt_Native_SearchEnd;
//搜索区间长度
extern CString g_sLangID_Native_SearchLen;
extern CString g_sLangTxt_Native_SearchLen;
//是否自动搜索
extern CString g_sLangID_Native_AutoSearch;
extern CString g_sLangTxt_Native_AutoSearch;
//复式制动电流(Ir-Id)
extern CString g_sLangID_Native_ComplexBrakeCurrent;
extern CString g_sLangTxt_Native_ComplexBrakeCurrent;
//差动电流定值
extern CString g_sLangID_Native_DiffCurrentSetVal;
extern CString g_sLangTxt_Native_DiffCurrentSetVal;
//差动类别(0-大差试验 1-小差试验)
extern CString g_sLangID_Native_DiffType;
extern CString g_sLangTxt_Native_DiffType;
//Ua幅值
extern CString g_sLangID_Native_UaAmplitude;
extern CString g_sLangTxt_Native_UaAmplitude;
//Ub幅值
extern CString g_sLangID_Native_UbAmplitude;
extern CString g_sLangTxt_Native_UbAmplitude;
//Uc幅值
extern CString g_sLangID_Native_UcAmplitude;
extern CString g_sLangTxt_Native_UcAmplitude;
//Ua相位
extern CString g_sLangID_Native_UaPhase;
extern CString g_sLangTxt_Native_UaPhase;
//Ub相位
extern CString g_sLangID_Native_UbPhase;
extern CString g_sLangTxt_Native_UbPhase;
//Uc相位
extern CString g_sLangID_Native_UcPhase;
extern CString g_sLangTxt_Native_UcPhase;
//间隔1TA变比
extern CString g_sLangID_Native_Gap1TARatio;
extern CString g_sLangTxt_Native_Gap1TARatio;
//间隔2TA变比
extern CString g_sLangID_Native_Gap2TARatio;
extern CString g_sLangTxt_Native_Gap2TARatio;
//间隔3TA变比
extern CString g_sLangID_Native_Gap3TARatio;
extern CString g_sLangTxt_Native_Gap3TARatio;
//最大TA变比
extern CString g_sLangID_Native_MaxTARatio;
extern CString g_sLangTxt_Native_MaxTARatio;
//差动门槛电流
extern CString g_sLangID_Native_DiffThreshCurrent;
extern CString g_sLangTxt_Native_DiffThreshCurrent;
//复式比率系数高值
extern CString g_sLangID_Native_HighCompRatioCoef;
extern CString g_sLangTxt_Native_HighCompRatioCoef;
//复式比率系数低值
extern CString g_sLangID_Native_LowCompRatioCoef;
extern CString g_sLangTxt_Native_LowCompRatioCoef;
//差动动作值
extern CString g_sLangID_Native_DiffActionVal;
extern CString g_sLangTxt_Native_DiffActionVal;
//当前搜索值
extern CString g_sLangID_Native_CurrSearchVal;
extern CString g_sLangTxt_Native_CurrSearchVal;
//差动动作描述
extern CString g_sLangID_Native_DiffActionDesc;
extern CString g_sLangTxt_Native_DiffActionDesc;
//电压闭锁元件
extern CString g_sLangID_Native_VoltLockElem;
extern CString g_sLangTxt_Native_VoltLockElem;
//闭锁电压值
extern CString g_sLangID_Native_LockVoltValue;
extern CString g_sLangTxt_Native_LockVoltValue;
//比率制动系数类别(0-低值 1-高值)
extern CString g_sLangID_Native_BrkCoeffType;
extern CString g_sLangTxt_Native_BrkCoeffType;
//差动电流Id(表达式)
extern CString g_sLangID_Native_DiffCurrentIds;
extern CString g_sLangTxt_Native_DiffCurrentIds;
//复式制动电流(Ir-Id)(表达式)
extern CString g_sLangID_Native_CompBrakeCurr;
extern CString g_sLangTxt_Native_CompBrakeCurr;
//Ir制动方程
extern CString g_sLangID_Native_IrBrakeEq;
extern CString g_sLangTxt_Native_IrBrakeEq;
//第一组电压常态输出值
extern CString g_sLangID_Native_FirstVoltNormOutput;
extern CString g_sLangTxt_Native_FirstVoltNormOutput;
//第二组电压常态输出值
extern CString g_sLangID_Native_SecondVoltNormOutput;
extern CString g_sLangTxt_Native_SecondVoltNormOutput;
//第一组电压故障态故障相输出值
extern CString g_sLangID_Native_VoltFaultState;
extern CString g_sLangTxt_Native_VoltFaultState;
//第二组电压故障态故障相输出值
extern CString g_sLangID_Native_VoltFaultState2;
extern CString g_sLangTxt_Native_VoltFaultState2;
//平衡系数设置方式
extern CString g_sLangID_Native_BalanceMode;
extern CString g_sLangTxt_Native_BalanceMode;
//高压侧差动平衡系数设置值
extern CString g_sLangID_Native_HVBalanceCoeff;
extern CString g_sLangTxt_Native_HVBalanceCoeff;
//中压侧差动平衡系数设置值
extern CString g_sLangID_Native_MVBalanceCoeff;
extern CString g_sLangTxt_Native_MVBalanceCoeff;
//低压侧差动平衡系数设置值
extern CString g_sLangID_Native_LVBalanceCoeff;
extern CString g_sLangTxt_Native_LVBalanceCoeff;
//高压侧CT变比
extern CString g_sLangID_Native_HVCTRatio;
extern CString g_sLangTxt_Native_HVCTRatio;
//中压侧CT变比
extern CString g_sLangID_Native_MVCTRatio;
extern CString g_sLangTxt_Native_MVCTRatio;
//低压侧CT变比
extern CString g_sLangID_Native_LVCTRatio;
extern CString g_sLangTxt_Native_LVCTRatio;
//参与试验的绕组
extern CString g_sLangID_Native_TestCoil;
extern CString g_sLangTxt_Native_TestCoil;
//保护内部相位校正方式
extern CString g_sLangID_Native_ProtPhaseCorr;
extern CString g_sLangTxt_Native_ProtPhaseCorr;
//基准电流设定值
extern CString g_sLangID_Native_BaseCurrSet;
extern CString g_sLangTxt_Native_BaseCurrSet;
//差动速断电流
extern CString g_sLangID_Native_DiffQuickBreakCurr;
extern CString g_sLangTxt_Native_DiffQuickBreakCurr;
//比率制动拐点数
extern CString g_sLangID_Native_RatioBrakeTurnPts;
extern CString g_sLangTxt_Native_RatioBrakeTurnPts;
//比率制动拐点1电流
extern CString g_sLangID_Native_RatioBrakeTurn1Curr;
extern CString g_sLangTxt_Native_RatioBrakeTurn1Curr;
//比率制动拐点2电流
extern CString g_sLangID_Native_RatioBrakeTurn2Curr;
extern CString g_sLangTxt_Native_RatioBrakeTurn2Curr;
//比率制动拐点3电流
extern CString g_sLangID_Native_RatioBrakeTurn3Curr;
extern CString g_sLangTxt_Native_RatioBrakeTurn3Curr;
//谐波制动系数定值
extern CString g_sLangID_Native_HarmonicBrakeCoeff;
extern CString g_sLangTxt_Native_HarmonicBrakeCoeff;
//谐波制动系数描述
extern CString g_sLangID_Native_HarmonicBrakeDesc;
extern CString g_sLangTxt_Native_HarmonicBrakeDesc;
//A相基波电流
extern CString g_sLangID_Native_PhaseACurrent;
extern CString g_sLangTxt_Native_PhaseACurrent;
//B相基波电流
extern CString g_sLangID_Native_PhaseBCurrent;
extern CString g_sLangTxt_Native_PhaseBCurrent;
//C相基波电流
extern CString g_sLangID_Native_PhaseCCurrent;
extern CString g_sLangTxt_Native_PhaseCCurrent;
//A相谐波电流
extern CString g_sLangID_Native_PhaseAHarmCur;
extern CString g_sLangTxt_Native_PhaseAHarmCur;
//B相谐波电流
extern CString g_sLangID_Native_BHarmonicCurrent;
extern CString g_sLangTxt_Native_BHarmonicCurrent;
//C相谐波电流
extern CString g_sLangID_Native_CHarmonicCurrent;
extern CString g_sLangTxt_Native_CHarmonicCurrent;
//第一组电压输出值
extern CString g_sLangID_Native_FirstGroupVoltageOut;
extern CString g_sLangTxt_Native_FirstGroupVoltageOut;
//第二组电压输出值
extern CString g_sLangID_Native_SecondGroupVoltageOut;
extern CString g_sLangTxt_Native_SecondGroupVoltageOut;
//高压侧CT接线方式
extern CString g_sLangID_Native_HVCTConnectionMode;
extern CString g_sLangTxt_Native_HVCTConnectionMode;
//平衡系数计算方法
extern CString g_sLangID_Native_BalanceCoeffCalcMethod;
extern CString g_sLangTxt_Native_BalanceCoeffCalcMethod;
//待测定值
extern CString g_sLangID_Native_UnderTestValue;
extern CString g_sLangTxt_Native_UnderTestValue;
//故障阻抗角
extern CString g_sLangID_Native_FaultImpedanceAngle;
extern CString g_sLangTxt_Native_FaultImpedanceAngle;
//是否模拟PT断线
extern CString g_sLangID_Native_PTLineSimulate;
extern CString g_sLangTxt_Native_PTLineSimulate;
//模拟PT断线相别
extern CString g_sLangID_Native_PTLineSimPhase;
extern CString g_sLangTxt_Native_PTLineSimPhase;
//变化始值(表达式)
extern CString g_sLangID_Native_VarStartValue;
extern CString g_sLangTxt_Native_VarStartValue;
//变化终值(表达式)
extern CString g_sLangID_Native_VarEndValue;
extern CString g_sLangTxt_Native_VarEndValue;
//步长时间(表达式)
extern CString g_sLangID_Native_StepTime;
extern CString g_sLangTxt_Native_StepTime;
//短路电压(表达式)
extern CString g_sLangID_Native_ShortVolt;
extern CString g_sLangTxt_Native_ShortVolt;
//短路电流(表达式)
extern CString g_sLangID_Native_ShortCurr;
extern CString g_sLangTxt_Native_ShortCurr;
//边界角1(兼容)
extern CString g_sLangID_Native_BoundaryAngle1;
extern CString g_sLangTxt_Native_BoundaryAngle1;
//边界角2(兼容)
extern CString g_sLangID_Native_BoundaryAngle2;
extern CString g_sLangTxt_Native_BoundaryAngle2;
//步长时间
extern CString g_sLangID_Native_StepTimes;
extern CString g_sLangTxt_Native_StepTimes;
//短路电流
extern CString g_sLangID_Native_ShortCircuit;
extern CString g_sLangTxt_Native_ShortCircuit;
//阻抗角
extern CString g_sLangID_Native_ImpedanceAngles;
extern CString g_sLangTxt_Native_ImpedanceAngles;
//是否测试返回值
extern CString g_sLangID_Native_TestReturnValue;
extern CString g_sLangTxt_Native_TestReturnValue;
//低电压(V)
extern CString g_sLangID_Native_LowVoltagev;
extern CString g_sLangTxt_Native_LowVoltagev;
//负序电压(V)
extern CString g_sLangID_Native_NegativeSeqVolt;
extern CString g_sLangTxt_Native_NegativeSeqVolt;
//动作电流(A)
extern CString g_sLangID_Native_ActionCurrent;
extern CString g_sLangTxt_Native_ActionCurrent;
//延时时间(s)
extern CString g_sLangID_Native_DelayTimes;
extern CString g_sLangTxt_Native_DelayTimes;
//动作区大小(°)
extern CString g_sLangID_Native_ActionAreaSize;
extern CString g_sLangTxt_Native_ActionAreaSize;
//阻抗角(表达式)
extern CString g_sLangID_Native_ImpedanceAnglexp;
extern CString g_sLangTxt_Native_ImpedanceAnglexp;
//测试仪输出模式
extern CString g_sLangID_Native_TestOutMode;
extern CString g_sLangTxt_Native_TestOutMode;
//额定电压值
extern CString g_sLangID_Native_RatedVoltVal;
extern CString g_sLangTxt_Native_RatedVoltVal;
//额定电流值
extern CString g_sLangID_Native_RatedCurrVal;
extern CString g_sLangTxt_Native_RatedCurrVal;
//第%d组PT一次值
extern CString g_sLangID_Native_FirstPTVal;
extern CString g_sLangTxt_Native_FirstPTVal;
//第%d组PT二次值
extern CString g_sLangID_Native_SecPTVal;
extern CString g_sLangTxt_Native_SecPTVal;
//第%d组CT一次值
extern CString g_sLangID_Native_FirstCTVal;
extern CString g_sLangTxt_Native_FirstCTVal;
//第%d组CT二次值
extern CString g_sLangID_Native_SecCTVal;
extern CString g_sLangTxt_Native_SecCTVal;
//报文输出格式
extern CString g_sLangID_Native_MsgFormat;
extern CString g_sLangTxt_Native_MsgFormat;
//弱信号输出设置
extern CString g_sLangID_Native_WeakSigOutSet;
extern CString g_sLangTxt_Native_WeakSigOutSet;
//1588接收光口
extern CString g_sLangID_Native_1588RecvOptPort;
extern CString g_sLangTxt_Native_1588RecvOptPort;
//1588同步机制
extern CString g_sLangID_Native_1588SyncMech;
extern CString g_sLangTxt_Native_1588SyncMech;
//参数设置选择(0-一次值,1-二次值)
extern CString g_sLangID_Native_ParamSel;
extern CString g_sLangTxt_Native_ParamSel;
//报文输出选择(0-一次值,1-二次值)
extern CString g_sLangID_Native_MsgOutSel;
extern CString g_sLangTxt_Native_MsgOutSel;
//B码逻辑(0-正逻辑,1-负逻辑)
extern CString g_sLangID_Native_BCodeLogics;
extern CString g_sLangTxt_Native_BCodeLogics;
//光纤连接方式(0-双回,1-单回)
extern CString g_sLangID_Native_FiberConn;
extern CString g_sLangTxt_Native_FiberConn;
//组电流模块
extern CString g_sLangID_Native_GroupCurrMod;
extern CString g_sLangTxt_Native_GroupCurrMod;
//电流模块位置
extern CString g_sLangID_Native_CurrModPos;
extern CString g_sLangTxt_Native_CurrModPos;
//电流模块档位值
extern CString g_sLangID_Native_CurrModGearVal;
extern CString g_sLangTxt_Native_CurrModGearVal;
//电流通道最大端口电压
extern CString g_sLangID_Native_CurrChanMaxVolt;
extern CString g_sLangTxt_Native_CurrChanMaxVolt;
//合并电流端子
extern CString g_sLangID_Native_MergeCurrTerm;
extern CString g_sLangTxt_Native_MergeCurrTerm;
//电流模块数量
extern CString g_sLangID_Native_CurrModCount;
extern CString g_sLangTxt_Native_CurrModCount;
//无线网络
extern CString g_sLangID_Native_WirelessNet;
extern CString g_sLangTxt_Native_WirelessNet;
//有线网络
extern CString g_sLangID_Native_WiredNet;
extern CString g_sLangTxt_Native_WiredNet;
//Lcd背光时长
extern CString g_sLangID_Native_LcdBacklightTime;
extern CString g_sLangTxt_Native_LcdBacklightTime;
//触摸灵敏度(ms)
extern CString g_sLangID_Native_TouchSensitivity;
extern CString g_sLangTxt_Native_TouchSensitivity;
//电流动作值绝对误差(A)
extern CString g_sLangID_Native_CurrentActionError;
extern CString g_sLangTxt_Native_CurrentActionError;
//电流动作值相对误差(%)
extern CString g_sLangID_Native_CurrentActionRelError;
extern CString g_sLangTxt_Native_CurrentActionRelError;
//电压动作值绝对误差(V)
extern CString g_sLangID_Native_VoltageActionError;
extern CString g_sLangTxt_Native_VoltageActionError;
//电压动作值相对误差(%)
extern CString g_sLangID_Native_VoltageActionRelError;
extern CString g_sLangTxt_Native_VoltageActionRelError;
//阻抗动作值绝对误差(Ω)
extern CString g_sLangID_Native_ImpedanceActionError;
extern CString g_sLangTxt_Native_ImpedanceActionError;
//阻抗动作值相对误差(%)
extern CString g_sLangID_Native_ImpedanceActionRelError;
extern CString g_sLangTxt_Native_ImpedanceActionRelError;
//动作时间绝对误差(s)
extern CString g_sLangID_Native_ActionTimeAbsError;
extern CString g_sLangTxt_Native_ActionTimeAbsError;
//动作时间相对误差(%)
extern CString g_sLangID_Native_ActionTimeRelError;
extern CString g_sLangTxt_Native_ActionTimeRelError;
//相位误差值(°)
extern CString g_sLangID_Native_PhaseErrorValue;
extern CString g_sLangTxt_Native_PhaseErrorValue;
//频率误差值(Hz)
extern CString g_sLangID_Native_FreqErrorValue;
extern CString g_sLangTxt_Native_FreqErrorValue;
//电压滑差误差值(V/s)
extern CString g_sLangID_Native_VoltSlipErrorValue;
extern CString g_sLangTxt_Native_VoltSlipErrorValue;
//频率滑差误差值(Hz/s)
extern CString g_sLangID_Native_FreqSlipErrorValue;
extern CString g_sLangTxt_Native_FreqSlipErrorValue;
//差动比率制动系数绝对误差
extern CString g_sLangID_Native_DiffRatioBrakeAbsError;
extern CString g_sLangTxt_Native_DiffRatioBrakeAbsError;
//差动比率制动系数相对误差(%)
extern CString g_sLangID_Native_DiffRatioBrakeRelError;
extern CString g_sLangTxt_Native_DiffRatioBrakeRelError;
//差动谐波制动系数绝对误差
extern CString g_sLangID_Native_DiffHarmonicBrakeAbsError;
extern CString g_sLangTxt_Native_DiffHarmonicBrakeAbsError;
//差动谐波制动系数相对误差(%)
extern CString g_sLangID_Native_DiffHarmonicBrakeRelError;
extern CString g_sLangTxt_Native_DiffHarmonicBrakeRelError;
//辅助直流电压值
extern CString g_sLangID_Native_AuxDcVoltageValue;
extern CString g_sLangTxt_Native_AuxDcVoltageValue;
//辅助直流电流值
extern CString g_sLangID_Native_AuxDcCurrentValue;
extern CString g_sLangTxt_Native_AuxDcCurrentValue;
//电压变比一次值(第1组)
extern CString g_sLangID_Native_VoltageRatioPrimary1;
extern CString g_sLangTxt_Native_VoltageRatioPrimary1;
//电压变比一次值(第2组)
extern CString g_sLangID_Native_VoltageRatioPrimary2;
extern CString g_sLangTxt_Native_VoltageRatioPrimary2;
//电压变比一次值(第3组)
extern CString g_sLangID_Native_VoltageRatioPrimary3;
extern CString g_sLangTxt_Native_VoltageRatioPrimary3;
//电压变比一次值(第4组)
extern CString g_sLangID_Native_VoltageRatioPrimary4;
extern CString g_sLangTxt_Native_VoltageRatioPrimary4;
//电压变比一次值(第5组)
extern CString g_sLangID_Native_VoltageRatioPrimary5;
extern CString g_sLangTxt_Native_VoltageRatioPrimary5;
//电压变比一次值(第6组)
extern CString g_sLangID_Native_VoltageRatioPrimary6;
extern CString g_sLangTxt_Native_VoltageRatioPrimary6;
//电压变比二次值(第1组)
extern CString g_sLangID_Native_VoltageRatioSecondary1;
extern CString g_sLangTxt_Native_VoltageRatioSecondary1;
//电压变比二次值(第2组)
extern CString g_sLangID_Native_VoltageRatioSecondary2;
extern CString g_sLangTxt_Native_VoltageRatioSecondary2;
//电压变比二次值(第3组)
extern CString g_sLangID_Native_VoltageRatioSecondary3;
extern CString g_sLangTxt_Native_VoltageRatioSecondary3;
//电压变比二次值(第4组)
extern CString g_sLangID_Native_VoltageRatioSecondary4;
extern CString g_sLangTxt_Native_VoltageRatioSecondary4;
//电压变比二次值(第5组)
extern CString g_sLangID_Native_VoltageRatioSecondary5;
extern CString g_sLangTxt_Native_VoltageRatioSecondary5;
//电压变比二次值(第6组)
extern CString g_sLangID_Native_VoltageRatioSecondary6;
extern CString g_sLangTxt_Native_VoltageRatioSecondary6;
//电流变比一次值(第1组)
extern CString g_sLangID_Native_CurrentRatioPrimary1;
extern CString g_sLangTxt_Native_CurrentRatioPrimary1;
//电流变比一次值(第2组)
extern CString g_sLangID_Native_CurrentRatioPrimary2;
extern CString g_sLangTxt_Native_CurrentRatioPrimary2;
//电流变比一次值(第3组)
extern CString g_sLangID_Native_CurrentRatioPrimary3;
extern CString g_sLangTxt_Native_CurrentRatioPrimary3;
//电流变比一次值(第4组)
extern CString g_sLangID_Native_CurrentRatioPrimary4;
extern CString g_sLangTxt_Native_CurrentRatioPrimary4;
//电流变比一次值(第5组)
extern CString g_sLangID_Native_CurrentRatioPrimary5;
extern CString g_sLangTxt_Native_CurrentRatioPrimary5;
//电流变比一次值(第6组)
extern CString g_sLangID_Native_CurrentRatioPrimary6;
extern CString g_sLangTxt_Native_CurrentRatioPrimary6;
//电流变比二次值(第1组)
extern CString g_sLangID_Native_CurrentRatioSecondary1;
extern CString g_sLangTxt_Native_CurrentRatioSecondary1;
//电流变比二次值(第2组)
extern CString g_sLangID_Native_CurrentRatioSecondary2;
extern CString g_sLangTxt_Native_CurrentRatioSecondary2;
//电流变比二次值(第3组)
extern CString g_sLangID_Native_CurrentRatioSecondary3;
extern CString g_sLangTxt_Native_CurrentRatioSecondary3;
//电流变比二次值(第4组)
extern CString g_sLangID_Native_CurrentRatioSecondary4;
extern CString g_sLangTxt_Native_CurrentRatioSecondary4;
//电流变比二次值(第5组)
extern CString g_sLangID_Native_CurrentRatioSecondary5;
extern CString g_sLangTxt_Native_CurrentRatioSecondary5;
//电流变比二次值(第6组)
extern CString g_sLangID_Native_CurrentRatioSecondary6;
extern CString g_sLangTxt_Native_CurrentRatioSecondary6;
//输出模拟量
extern CString g_sLangID_Native_OutputAnalog;
extern CString g_sLangTxt_Native_OutputAnalog;
//输出数字量
extern CString g_sLangID_Native_OutputDigital;
extern CString g_sLangTxt_Native_OutputDigital;
//输出弱信号
extern CString g_sLangID_Native_OutputWeakSig;
extern CString g_sLangTxt_Native_OutputWeakSig;
//额定线电压值
extern CString g_sLangID_Native_RatedLineVolt;
extern CString g_sLangTxt_Native_RatedLineVolt;
//额定零序电压
extern CString g_sLangID_Native_RatedZeroVolt;
extern CString g_sLangTxt_Native_RatedZeroVolt;
//额定零序电流
extern CString g_sLangID_Native_RatedZeroCurr;
extern CString g_sLangTxt_Native_RatedZeroCurr;
//开始过载延时(s)
extern CString g_sLangID_Native_StartOverloadDelay;
extern CString g_sLangTxt_Native_StartOverloadDelay;
//检测测试端心跳
extern CString g_sLangID_Native_CheckTestEndHeartbeat;
extern CString g_sLangTxt_Native_CheckTestEndHeartbeat;
//使用模拟量采集
extern CString g_sLangID_Native_UseAnalogCapture;
extern CString g_sLangTxt_Native_UseAnalogCapture;
//使用数字量采集
extern CString g_sLangID_Native_UseDigitalCapture;
extern CString g_sLangTxt_Native_UseDigitalCapture;
//使用小信号采集
extern CString g_sLangID_Native_UseSmallSignalCapture;
extern CString g_sLangTxt_Native_UseSmallSignalCapture;
//数字量采集报文类型
extern CString g_sLangID_Native_DigitalCaptureMsgType;
extern CString g_sLangTxt_Native_DigitalCaptureMsgType;
//B码接收逻辑(0-正逻辑,1-负逻辑)
extern CString g_sLangID_Native_BCodeReceiveLogic;
extern CString g_sLangTxt_Native_BCodeReceiveLogic;
//报告需要的扩展开入数量(0-自动关联开关量扩展模块)
extern CString g_sLangID_Native_ReportExtInQty;
extern CString g_sLangTxt_Native_ReportExtInQty;
//底层上报数据的时区
extern CString g_sLangID_Native_BaseReportTimeZone;
extern CString g_sLangTxt_Native_BaseReportTimeZone;
//GPS转B码时使用用户设置时区
extern CString g_sLangID_Native_GPStoBCodeUserTZ;
extern CString g_sLangTxt_Native_GPStoBCodeUserTZ;
//机器散热风扇模式(0-静音,1-正常)
extern CString g_sLangID_Native_MachineFanMode;
extern CString g_sLangTxt_Native_MachineFanMode;
//幅值递变标识
extern CString g_sLangID_Native_AmplitudeGradual;
extern CString g_sLangTxt_Native_AmplitudeGradual;
//幅值递变终值
extern CString g_sLangID_Native_AmplitudeEndValue;
extern CString g_sLangTxt_Native_AmplitudeEndValue;
//幅值递变步长
extern CString g_sLangID_Native_AmplitudeStep;
extern CString g_sLangTxt_Native_AmplitudeStep;
//相位递变标识
extern CString g_sLangID_Native_PhaseFlag;
extern CString g_sLangTxt_Native_PhaseFlag;
//相位递变终值
extern CString g_sLangID_Native_PhaseEndVal;
extern CString g_sLangTxt_Native_PhaseEndVal;
//相位递变步长
extern CString g_sLangID_Native_PhaseStep;
extern CString g_sLangTxt_Native_PhaseStep;
//频率递变标识
extern CString g_sLangID_Native_FreqFlag;
extern CString g_sLangTxt_Native_FreqFlag;
//频率递变终值
extern CString g_sLangID_Native_FreqEnd;
extern CString g_sLangTxt_Native_FreqEnd;
//频率递变步长
extern CString g_sLangID_Native_FreqStep;
extern CString g_sLangTxt_Native_FreqStep;
//是否选择
extern CString g_sLangID_Native_IsSelected;
extern CString g_sLangTxt_Native_IsSelected;
//开出状态
extern CString g_sLangID_Native_OpenState;
extern CString g_sLangTxt_Native_OpenState;
//是否叠加直流分量
extern CString g_sLangID_Native_DCOverlay;
extern CString g_sLangTxt_Native_DCOverlay;
//直流分量的衰减时间常数
extern CString g_sLangID_Native_DCDampTime;
extern CString g_sLangTxt_Native_DCDampTime;
//使能评估
extern CString g_sLangID_Native_EnableEval;
extern CString g_sLangTxt_Native_EnableEval;
//计时起点_状态
extern CString g_sLangID_Native_TimeStartState;
extern CString g_sLangTxt_Native_TimeStartState;
//计时终点_状态
extern CString g_sLangID_Native_TimeEndState;
extern CString g_sLangTxt_Native_TimeEndState;
//计时起点_开入
extern CString g_sLangID_Native_TimeStartInput;
extern CString g_sLangTxt_Native_TimeStartInput;
//计时终点_开入
extern CString g_sLangID_Native_TimeEndInput;
extern CString g_sLangTxt_Native_TimeEndInput;
//绝对误差限
extern CString g_sLangID_Native_AbsErrorLimit;
extern CString g_sLangTxt_Native_AbsErrorLimit;
//相对误差限
extern CString g_sLangID_Native_RelErrorLimit;
extern CString g_sLangTxt_Native_RelErrorLimit;
//判断逻辑
extern CString g_sLangID_Native_JudgeLogic;
extern CString g_sLangTxt_Native_JudgeLogic;
//递变动作步数标识
extern CString g_sLangID_Native_StepChangeID;
extern CString g_sLangTxt_Native_StepChangeID;
//自定义动作时间
extern CString g_sLangID_Native_CustomActTime;
extern CString g_sLangTxt_Native_CustomActTime;
//自定义动作时间绝对误差
extern CString g_sLangID_Native_AbsError;
extern CString g_sLangTxt_Native_AbsError;
//自定义动作时间相对误差
extern CString g_sLangID_Native_RelError;
extern CString g_sLangTxt_Native_RelError;
//当前循环的序号
extern CString g_sLangID_Native_CurrLoop;
extern CString g_sLangTxt_Native_CurrLoop;
//触发模式(0-立即运行,1-等待GPS)
extern CString g_sLangID_Native_TrigModes;
extern CString g_sLangTxt_Native_TrigModes;
//硬件选择(0-主板8个开出,1-扩展插件)
extern CString g_sLangID_Native_HwSelect;
extern CString g_sLangTxt_Native_HwSelect;
//开入动作(0-不记录,1-记录)
extern CString g_sLangID_Native_InAction;
extern CString g_sLangTxt_Native_InAction;
//实验运行总时长(s)
extern CString g_sLangID_Native_TotalTime;
extern CString g_sLangTxt_Native_TotalTime;
//是否启用
extern CString g_sLangID_Native_IsEnabled;
extern CString g_sLangTxt_Native_IsEnabled;
//实验前状态值
extern CString g_sLangID_Native_PreState;
extern CString g_sLangTxt_Native_PreState;
//实验中初始状态值
extern CString g_sLangID_Native_InitState;
extern CString g_sLangTxt_Native_InitState;
//实验前断开持续时间(ms)
extern CString g_sLangID_Native_PreCutDur;
extern CString g_sLangTxt_Native_PreCutDur;
//实验中闭合持续时间(ms)
extern CString g_sLangID_Native_CloseDur;
extern CString g_sLangTxt_Native_CloseDur;
//实验中断开持续时间(ms)
extern CString g_sLangID_Native_BreakDur;
extern CString g_sLangTxt_Native_BreakDur;
//Uz幅值
extern CString g_sLangID_Native_UzAmp;
extern CString g_sLangTxt_Native_UzAmp;
//Uz相位
extern CString g_sLangID_Native_UzPhase;
extern CString g_sLangTxt_Native_UzPhase;
//Uz频率
extern CString g_sLangID_Native_UzFreq;
extern CString g_sLangTxt_Native_UzFreq;
//I0幅值
extern CString g_sLangID_Native_I0Amplitude;
extern CString g_sLangTxt_Native_I0Amplitude;
//I0相位
extern CString g_sLangID_Native_I0Phase;
extern CString g_sLangTxt_Native_I0Phase;
//I0频率
extern CString g_sLangID_Native_I0Frequency;
extern CString g_sLangTxt_Native_I0Frequency;
//电流启用高功率模式
extern CString g_sLangID_Native_CurrentHighPowerMode;
extern CString g_sLangTxt_Native_CurrentHighPowerMode;
//启用自定义输出
extern CString g_sLangID_Native_EnableCustomOutput;
extern CString g_sLangTxt_Native_EnableCustomOutput;
//绝对时间
extern CString g_sLangID_Native_AbsoluteTime;
extern CString g_sLangTxt_Native_AbsoluteTime;
//相对时间
extern CString g_sLangID_Native_RelativeTime;
extern CString g_sLangTxt_Native_RelativeTime;

extern CString g_sLangID_Native_ErrUaAmp;
extern CString g_sLangTxt_Native_ErrUaAmp;//故障Ua幅值
extern CString g_sLangID_Native_ErrUbAmp;
extern CString g_sLangTxt_Native_ErrUbAmp;//故障Ub幅值
extern CString g_sLangID_Native_ErrUcAmp;
extern CString g_sLangTxt_Native_ErrUcAmp;//故障Uc幅值
extern CString g_sLangID_Native_ErrUzAmp;
extern CString g_sLangTxt_Native_ErrUzAmp;//故障Uz幅值
extern CString g_sLangID_Native_ErrUaPh;
extern CString g_sLangTxt_Native_ErrUaPh;//故障Ua相位
extern CString g_sLangID_Native_ErrUbPh;
extern CString g_sLangTxt_Native_ErrUbPh;//故障Ub相位
extern CString g_sLangID_Native_ErrUcPh;
extern CString g_sLangTxt_Native_ErrUcPh;//故障Uc相位
extern CString g_sLangID_Native_ErrUzPh;
extern CString g_sLangTxt_Native_ErrUzPh;//故障Uz相位
extern CString g_sLangID_Native_OverCurrentV;
extern CString g_sLangTxt_Native_OverCurrentV;//过流V段定值
extern CString g_sLangID_Native_OverCurrentVTime;
extern CString g_sLangTxt_Native_OverCurrentVTime;//过流V段时间
extern CString g_sLangID_Native_ShortZImpAngExp;
extern CString g_sLangTxt_Native_ShortZImpAngExp;//短路阻抗角(表达式)
//

extern CString g_sLangID_Native_first_fault_type;
extern CString g_sLangTxt_Native_first_fault_type;//第一次故障类型
extern CString g_sLangID_Native_first_fault_current;
extern CString g_sLangTxt_Native_first_fault_current;//第一次故障电流
extern CString g_sLangID_Native_first_faultact_time;
extern CString g_sLangTxt_Native_first_faultact_time;//第一次故障动作时间
extern CString g_sLangID_Native_first_fault_impedance;
extern CString g_sLangTxt_Native_first_fault_impedance;//第一次故障短路阻抗
extern CString g_sLangID_Native_first_fault_impedance_angle;
extern CString g_sLangTxt_Native_first_fault_impedance_angle;//第一次故障短路阻抗角
extern CString g_sLangID_Native_second_fault_type;
extern CString g_sLangTxt_Native_second_fault_type;//第二次故障类型
extern CString g_sLangID_Native_second_fault_current;
extern CString g_sLangTxt_Native_second_fault_current;//第二次故障电流
extern CString g_sLangID_Native_second_faultact_time;
extern CString g_sLangTxt_Native_second_faultact_time;//第二次故障动作时间
extern CString g_sLangID_Native_second_fault_impedance;
extern CString g_sLangTxt_Native_second_fault_impedance;//第二次故障短路阻抗
extern CString g_sLangID_Native_second_fault_impedance_angle;
extern CString g_sLangTxt_Native_second_fault_impedance_angle;//第二次故障短路阻抗角
extern CString g_sLangID_Native_first_fault_impAmp;
extern CString g_sLangTxt_Native_first_fault_impAmp;//第一次故障短路阻抗(表达式)
extern CString g_sLangID_Native_first_fault_impAngAmp;
extern CString g_sLangTxt_Native_first_fault_impAngAmp;//第一次故障短路阻抗角(表达式)
extern CString g_sLangID_Native_second_fault_impAmp;
extern CString g_sLangTxt_Native_second_fault_impAmp;//第二次故障短路阻抗(表达式)
extern CString g_sLangID_Native_second_fault_impAngAmp;
extern CString g_sLangTxt_Native_second_fault_impAngAmp;//第二次故障短路阻抗角(表达式)
extern CString g_sLangID_Native_synchronous_VAmpExp;
extern CString g_sLangTxt_Native_synchronous_VAmpExp;//同期电压幅值(表达式)
extern CString g_sLangID_Native_synchronous_VPhExp;
extern CString g_sLangTxt_Native_synchronous_VPhExp;//同期电压相位(表达式)

extern CString g_sLangID_Native_impedance_Set;
extern CString g_sLangTxt_Native_impedance_Set;//阻抗定值(定值)
extern CString g_sLangID_Native_ImpedanceAnglesSet;
extern CString g_sLangTxt_Native_ImpedanceAnglesSet;//阻抗角(定值)
extern CString g_sLangID_Native_Syn_closure_AngSet;
extern CString g_sLangTxt_Native_Syn_closure_AngSet;//检同期合闸角(定值)
extern CString g_sLangID_Native_test_item_name;
extern CString g_sLangTxt_Native_test_item_name;//测试项名称

extern CString g_sLangID_Native_0seqISet;
extern CString g_sLangTxt_Native_0seqISet;//零序电流定值
extern CString g_sLangID_Native_YN_autoTestMode;
extern CString g_sLangTxt_Native_YN_autoTestMode;//是否自动测试模式
extern CString g_sLangID_Native_0SeqISet;
extern CString g_sLangTxt_Native_0SeqISet; //零序I-V段定值
extern CString g_sLangID_Native_0SeqIISet;
extern CString g_sLangTxt_Native_0SeqIISet;
extern CString g_sLangID_Native_0SeqIIISet;
extern CString g_sLangTxt_Native_0SeqIIISet;
extern CString g_sLangID_Native_0SeqIVSet;
extern CString g_sLangTxt_Native_0SeqIVSet;
extern CString g_sLangID_Native_0SeqVSet;
extern CString g_sLangTxt_Native_0SeqVSet;
extern CString g_sLangID_Native_0SeqITime;
extern CString g_sLangTxt_Native_0SeqITime;//零序I-V段时间
extern CString g_sLangID_Native_0SeqIITime;
extern CString g_sLangTxt_Native_0SeqIITime;
extern CString g_sLangID_Native_0SeqIIITime;
extern CString g_sLangTxt_Native_0SeqIIITime;
extern CString g_sLangID_Native_0SeqIVTime;
extern CString g_sLangTxt_Native_0SeqIVTime;
extern CString g_sLangID_Native_0SeqVTime;
extern CString g_sLangTxt_Native_0SeqVTime;


//第八周马
//tmt_adjust_sys_para_trans.cpp
/*_T("交流电压插件")*/
extern CString g_sLangID_Native_ACVoltPlugin;
extern CString g_sLangTxt_Native_ACVoltPlugin;
/*_T("交流电流插件")*/
extern CString g_sLangID_Native_ACCurrPlugin;
extern CString g_sLangTxt_Native_ACCurrPlugin;
/*_T("8个百兆口数字板")*/
extern CString g_sLangID_Native_8x100MbpsDB;
extern CString g_sLangTxt_Native_8x100MbpsDB;
/*_T("6个百兆口,2个千兆口数字板")*/
extern CString g_sLangID_Native_6x100M2x1000MDB;
extern CString g_sLangTxt_Native_6x100M2x1000MDB;
/*_T("4个百兆口,4个千兆口数字板")*/
extern CString g_sLangID_Native_4x100M4x1000MDB;
extern CString g_sLangTxt_Native_4x100M4x1000MDB;
/*_T("直流电流插件")*/
extern CString g_sLangID_Native_DCCurrPlugin;
extern CString g_sLangTxt_Native_DCCurrPlugin;
/*_T("直流电压插件")*/
extern CString g_sLangID_Native_DCVoltPlugin;
extern CString g_sLangTxt_Native_DCVoltPlugin;
/*_T("开关量扩展板")*/
extern CString g_sLangID_Native_DI_O_ExpBoard;
extern CString g_sLangTxt_Native_DI_O_ExpBoard;
/*_T("小信号模块插件")*/
extern CString g_sLangID_Native_LSModPlugin;
extern CString g_sLangTxt_Native_LSModPlugin;
/*_T("主板小信号")*/
extern CString g_sLangID_Native_MBLowSignal;
extern CString g_sLangTxt_Native_MBLowSignal;
/*_T("柔直FT3板")*/
extern CString g_sLangID_Native_FSFT3Board;
extern CString g_sLangTxt_Native_FSFT3Board;
/*_T("U、I混合插件")*/
extern CString g_sLangID_Native_UIHybridPlugin;
extern CString g_sLangTxt_Native_UIHybridPlugin;
/*_T("电压采集插件")*/
extern CString g_sLangID_Native_VoltAcqPlugin;
extern CString g_sLangTxt_Native_VoltAcqPlugin;
/*_T("电流采集插件")*/
extern CString g_sLangID_Native_CurrAcqPlugin;
extern CString g_sLangTxt_Native_CurrAcqPlugin;
/*_T("稳控2M通讯插件")*/
extern CString g_sLangID_Native_Stable2MCommPlugin;
extern CString g_sLangTxt_Native_Stable2MCommPlugin;
/*_T("采集")*/
extern CString g_sLangID_Native_Acquisition;
extern CString g_sLangTxt_Native_Acquisition;
/*_T("未定义")*/
extern CString g_sLangID_Native_Undefined;
extern CString g_sLangTxt_Native_Undefined;
/*_T("130伏电压模块")*/
extern CString g_sLangID_Native_130VVoltageModule;
extern CString g_sLangTxt_Native_130VVoltageModule;
/*_T("248伏电压模块")*/
extern CString g_sLangID_Native_248VVoltageModule;
extern CString g_sLangTxt_Native_248VVoltageModule;
/*_T("270伏电压模块无升压")*/
extern CString g_sLangID_Native_270VVMNoBoost;
extern CString g_sLangTxt_Native_270VVMNoBoost;
/*_T("270伏电压模块有升压")*/
extern CString g_sLangID_Native_270VVModuleWBoost;
extern CString g_sLangTxt_Native_270VVModuleWBoost;
/*_T("300伏电压模块无升压")*/
extern CString g_sLangID_Native_300VVMNoBoost;
extern CString g_sLangTxt_Native_300VVMNoBoost;
/*_T("300伏电压模块有升压")*/
extern CString g_sLangID_Native_300VVModuleWBoost;
extern CString g_sLangTxt_Native_300VVModuleWBoost;
/*_T("12.5安电流模块")*/
extern CString g_sLangID_Native_125ACModule;
extern CString g_sLangTxt_Native_125ACModule;
/*_T("20安电流模块")*/
extern CString g_sLangID_Native_20ACModule;
extern CString g_sLangTxt_Native_20ACModule;
/*_T("32安电流模块")*/
extern CString g_sLangID_Native_32ACModule;
extern CString g_sLangTxt_Native_32ACModule;
/*_T("130伏20安混合模块")*/
extern CString g_sLangID_Native_125V20AHM;
extern CString g_sLangTxt_Native_125V20AHM;
/*_T("310伏60安混合模块")*/
extern CString g_sLangID_Native_310V60AHM;
extern CString g_sLangTxt_Native_310V60AHM;
/*_T("PFC_6A 模块")*/
extern CString g_sLangID_Native_PFC6A;
extern CString g_sLangTxt_Native_PFC6A;
/*_T("PIA12DS 模块")*/
extern CString g_sLangID_Native_P12DSM;
extern CString g_sLangTxt_Native_P12DSM;
/*_T("PIA48S 模块")*/
extern CString g_sLangID_Native_P48SM;
extern CString g_sLangTxt_Native_P48SM;
/*_T("EVTECT 模块")*/
extern CString g_sLangID_Native_EVTM;
extern CString g_sLangTxt_Native_EVTM;
/*_T("直流增量保护模块")*/
extern CString g_sLangID_Native_DCIPM;
extern CString g_sLangTxt_Native_DCIPM;
/*_T("6路10伏直流模块")*/
extern CString g_sLangID_Native_6C10VDCM;
extern CString g_sLangTxt_Native_6C10VDCM;
/*_T("6路20毫安直流模块")*/
extern CString g_sLangID_Native_6C20mADC;
extern CString g_sLangTxt_Native_6C20mADC;
/*_T("PN6U6I直流小信号模块")*/
extern CString g_sLangID_Native_PN6U6IDCSSM;
extern CString g_sLangTxt_Native_PN6U6IDCSSM;
/*_T("不支持输出合并")*/
extern CString g_sLangID_Native_OutputNotSupported;
extern CString g_sLangTxt_Native_OutputNotSupported;
/*_T("6路可以合并为1路")*/
extern CString g_sLangID_Native_6to1MergePossible;
extern CString g_sLangTxt_Native_6to1MergePossible;
/*_T("6路可以合并为3路")*/
extern CString g_sLangID_Native_6to3MergePossible;
extern CString g_sLangTxt_Native_6to3MergePossible;
/*_T("6路固定合并为3路")*/
extern CString g_sLangID_Native_6to3FixedMerge;
extern CString g_sLangTxt_Native_6to3FixedMerge;

//adjust_sys_parameter
/*"幅值系数"*/
extern CString g_sLangID_Native_AmpFactor;
extern CString g_sLangTxt_Native_AmpFactor;
/*"档位数"*/
extern CString g_sLangID_Native_NumGears;
extern CString g_sLangTxt_Native_NumGears;
/*"硬件1档直流零漂"*/
extern CString g_sLangID_Native_HW1DCZeroDrift;
extern CString g_sLangTxt_Native_HW1DCZeroDrift;
/*"硬件2档直流零漂"*/
extern CString g_sLangID_Native_HW2DCZeroDrift;
extern CString g_sLangTxt_Native_HW2DCZeroDrift;
/*"硬件3档直流零漂"*/
extern CString g_sLangID_Native_HW3DCZeroDrift;
extern CString g_sLangTxt_Native_HW3DCZeroDrift;
/*"大电流非线性系数"*/
extern CString g_sLangID_Native_LCNLCoeff;
extern CString g_sLangTxt_Native_LCNLCoeff;
/*"%d次谐波"*/
extern CString g_sLangID_Native_NthHarmonic;
extern CString g_sLangTxt_Native_NthHarmonic;
/*"温度"*/
extern CString g_sLangID_Native_Temp;
extern CString g_sLangTxt_Native_Temp;
/*"通道%d"*/
extern CString g_sLangID_Native_ChnN;
extern CString g_sLangTxt_Native_ChnN;
/*"档位ID"*/
extern CString g_sLangID_Native_GearID;
extern CString g_sLangTxt_Native_GearID;
/*"档位值"*/
extern CString g_sLangID_Native_GearVal;
extern CString g_sLangTxt_Native_GearVal;
/*"硬件档位数"*/
extern CString g_sLangID_Native_HwGearCount;
extern CString g_sLangTxt_Native_HwGearCount;
/*"校准系数"*/
extern CString g_sLangID_Native_CalibCoeff;
extern CString g_sLangTxt_Native_CalibCoeff;
/*"温区数"*/
extern CString g_sLangID_Native_TempZoneCount;
extern CString g_sLangTxt_Native_TempZoneCount;
/*"硬件通道"*/
extern CString g_sLangID_Native_HwChannel;
extern CString g_sLangTxt_Native_HwChannel;
/*"通道ID"*/
extern CString g_sLangID_Native_ChnID;
extern CString g_sLangTxt_Native_ChnID;
/*"通道索引"*/
extern CString g_sLangID_Native_ChnIndex;
extern CString g_sLangTxt_Native_ChnIndex;
/*"关联的软件资源"*/
extern CString g_sLangID_Native_AssocSWRes;
extern CString g_sLangTxt_Native_AssocSWRes;
/*"交流最大值"*/
extern CString g_sLangID_Native_ACMaxValue;
extern CString g_sLangTxt_Native_ACMaxValue;
/*"直流最大值"*/
extern CString g_sLangID_Native_DCMaxValue;
extern CString g_sLangTxt_Native_DCMaxValue;
/*"通道采集映射位置"*/
extern CString g_sLangID_Native_ChAcqMapLoc;
extern CString g_sLangTxt_Native_ChAcqMapLoc;
/*"通道采集映射位置"*/
extern CString g_sLangID_Native_OpMode;
extern CString g_sLangTxt_Native_OpMode;
/*"工作模式"*/
extern CString g_sLangID_Native_OpMode;
extern CString g_sLangTxt_Native_OpMode;
/*"电气类型"*/
extern CString g_sLangID_Native_ElecType;
extern CString g_sLangTxt_Native_ElecType;
/*"硬件通道定义"*/
extern CString g_sLangID_Native_HwChDef;
extern CString g_sLangTxt_Native_HwChDef;
/*"通道驱动位置"*/
extern CString g_sLangID_Native_ChDrivePos;
extern CString g_sLangTxt_Native_ChDrivePos;
/*_T("通道%d位置")*/
extern CString g_sLangID_Native_ChPos;
extern CString g_sLangTxt_Native_ChPos;
/*"通道映射定义"*/
extern CString g_sLangID_Native_ChMapDef;
extern CString g_sLangTxt_Native_ChMapDef;
/*"模块属性"*/
extern CString g_sLangID_Native_ModProps;
extern CString g_sLangTxt_Native_ModProps;
/*"LC光口数"*/
extern CString g_sLangID_Native_LCOptPortCount;
extern CString g_sLangTxt_Native_LCOptPortCount;
/*"ST发送光口数"*/
extern CString g_sLangID_Native_STTxOptPortCount;
extern CString g_sLangTxt_Native_STTxOptPortCount;
/*"ST接收光口数"*/
extern CString g_sLangID_Native_STRxOptPortCount;
extern CString g_sLangTxt_Native_STRxOptPortCount;
/*"谐波数"*/
extern CString g_sLangID_Native_HarmOrder;
extern CString g_sLangTxt_Native_HarmOrder;
/*"直流电压通道最大值"*/
extern CString g_sLangID_Native_DCVoltChMax;
extern CString g_sLangTxt_Native_DCVoltChMax;
/*"直流电流通道最大值"*/
extern CString g_sLangID_Native_DCCurrChMax;
extern CString g_sLangTxt_Native_DCCurrChMax;
/*"通道出交流最大值"*/
extern CString g_sLangID_Native_ChACOutMax;
extern CString g_sLangTxt_Native_ChACOutMax;
/*"通道出直流最大值"*/
extern CString g_sLangID_Native_ChDCOutMax;
extern CString g_sLangTxt_Native_ChDCOutMax;
/*"频率补偿系数"*/
extern CString g_sLangID_Native_FreqCompCoeff;
extern CString g_sLangTxt_Native_FreqCompCoeff;
/*"数字硬件相位延时"*/
extern CString g_sLangID_Native_DigiHWPhaseDelay;
extern CString g_sLangTxt_Native_DigiHWPhaseDelay;
/*"电压电流硬件特性"*/
extern CString g_sLangID_Native_VoltCurrHWChar;
extern CString g_sLangTxt_Native_VoltCurrHWChar;
/*"电流通道合并模式"*/
extern CString g_sLangID_Native_CurrChMergeMode;
extern CString g_sLangTxt_Native_CurrChMergeMode;
/*"第一组开关量配为开入"*/
extern CString g_sLangID_Native_1stSetDigInCfg;
extern CString g_sLangTxt_Native_1stSetDigInCfg;
/*"第二组开关量配为开入"*/
extern CString g_sLangID_Native_2stSetDigInCfg;
extern CString g_sLangTxt_Native_2stSetDigInCfg;
/*"第三组开关量配为开入"*/
extern CString g_sLangID_Native_3stSetDigInCfg;
extern CString g_sLangTxt_Native_3stSetDigInCfg;
/*"第四组开关量配为开入"*/
extern CString g_sLangID_Native_4stSetDigInCfg;
extern CString g_sLangTxt_Native_4stSetDigInCfg;
/*"模块FPGA版本"*/
extern CString g_sLangID_Native_ModFPGAVer;
extern CString g_sLangTxt_Native_ModFPGAVer;
/*"模块属性版本"*/
extern CString g_sLangID_Native_ModAttrVer;
extern CString g_sLangTxt_Native_ModAttrVer;
/*"独立直流电流通道硬件档位"*/
extern CString g_sLangID_Native_IndepDCCurrChHWRange;
extern CString g_sLangTxt_Native_IndepDCCurrChHWRange;
/*"独立直流电压通道硬件档位"*/
extern CString g_sLangID_Native_IndepDCVoltChHWRange;
extern CString g_sLangTxt_Native_IndepDCVoltChHWRange;
/*"模块通道档位"*/
extern CString g_sLangID_Native_ModChRange;
extern CString g_sLangTxt_Native_ModChRange;
/*"开出量导通值定义"*/
extern CString g_sLangID_Native_TripRelayPickupDef;
extern CString g_sLangTxt_Native_TripRelayPickupDef;
/*"开出1导通值"*/
extern CString g_sLangID_Native_TripRelay1Pickup;
extern CString g_sLangTxt_Native_TripRelay1Pickup;
/*"开出2导通值"*/
extern CString g_sLangID_Native_TripRelay2Pickup;
extern CString g_sLangTxt_Native_TripRelay2Pickup;
/*"开出3导通值"*/
extern CString g_sLangID_Native_TripRelay3Pickup;
extern CString g_sLangTxt_Native_TripRelay3Pickup;
/*"开出4导通值"*/
extern CString g_sLangID_Native_TripRelay4Pickup;
extern CString g_sLangTxt_Native_TripRelay4Pickup;
/*"开出5导通值"*/
extern CString g_sLangID_Native_TripRelay5Pickup;
extern CString g_sLangTxt_Native_TripRelay5Pickup;
/*"开出6导通值"*/
extern CString g_sLangID_Native_TripRelay6Pickup;
extern CString g_sLangTxt_Native_TripRelay6Pickup;
/*"开出7导通值"*/
extern CString g_sLangID_Native_TripRelay7Pickup;
extern CString g_sLangTxt_Native_TripRelay7Pickup;
/*"开出8导通值"*/
extern CString g_sLangID_Native_TripRelay8Pickup;
extern CString g_sLangTxt_Native_TripRelay8Pickup;
/*"状态序列容量(个)"*/
extern CString g_sLangID_Native_StateSeqCapacity;
extern CString g_sLangTxt_Native_StateSeqCapacity;
/*"主板开入数量(个)"*/
extern CString g_sLangID_Native_MainBrdDInQty;
extern CString g_sLangTxt_Native_MainBrdDInQty;
/*"主板开出数量(个)"*/
extern CString g_sLangID_Native_MainBrdDOutQty;
extern CString g_sLangTxt_Native_MainBrdDOutQty;
/*"整秒时刻,模拟量绝对相位补偿(度)"*/
extern CString g_sLangID_Native_WSecMomentAnaPhAbsComp;
extern CString g_sLangTxt_Native_WSecMomentAnaPhAbsComp;
/*"启用控制权限判断(0-不启用，1-启用)"*/
extern CString g_sLangID_Native_CtrlAuthCheck;
extern CString g_sLangTxt_Native_CtrlAuthCheck;
/*"TestServer名称"*/
extern CString g_sLangID_Native_TestSrvName;
extern CString g_sLangTxt_Native_TestSrvName;
/*"TestServer版本"*/
extern CString g_sLangID_Native_TestSrvVersion;
extern CString g_sLangTxt_Native_TestSrvVersion;
/*"主板版本"*/
extern CString g_sLangID_Native_MainBrdVersion;
extern CString g_sLangTxt_Native_MainBrdVersion;
/*"驱动版本"*/
extern CString g_sLangID_Native_DrvVersion;
extern CString g_sLangTxt_Native_DrvVersion;
/*"驱动名称"*/
extern CString g_sLangID_Native_DrvName;
extern CString g_sLangTxt_Native_DrvName;
/*"主板ST口模式可设置"*/
extern CString g_sLangID_Native_MainBrdSTPortModeCfg;
extern CString g_sLangTxt_Native_MainBrdSTPortModeCfg;
/*"系统版本号"*/
extern CString g_sLangID_Native_SysVerNumber;
extern CString g_sLangTxt_Native_SysVerNumber;



//tmt_adjust_test
/*"校准项目"*/
extern CString g_sLangID_Native_CalibItem;
extern CString g_sLangTxt_Native_CalibItem;
/*"点1幅值"*/
extern CString g_sLangID_Native_Pt1Amp;
extern CString g_sLangTxt_Native_Pt1Amp;
/*"点2幅值"*/
extern CString g_sLangID_Native_Pt2Amp;
extern CString g_sLangTxt_Native_Pt2Amp;

//tmt_dig_replay_test
/*"发送(选择该控制块)"*/
extern CString g_sLangID_Native_SelCtrlBlock;
extern CString g_sLangTxt_Native_SelCtrlBlock;
/*"控制块输出光口数量"*/
extern CString g_sLangID_Native_CtrlBlkOutOptPortsCnt;
extern CString g_sLangTxt_Native_CtrlBlkOutOptPortsCnt;
/*"控制块AppID"*/
extern CString g_sLangID_Native_CtrlBlkAppID;
extern CString g_sLangTxt_Native_CtrlBlkAppID;
/*"控制块输出总帧数"*/
extern CString g_sLangID_Native_CtrlBlkOutTotalFrames;
extern CString g_sLangTxt_Native_CtrlBlkOutTotalFrames;
/*"控制块输出起始帧号(本控制块内排序)"*/
extern CString g_sLangID_Native_CtrlBlkOutStartFrmNum;
extern CString g_sLangTxt_Native_CtrlBlkOutStartFrmNum;
/*"控制块输出结束帧号(本控制块内排序)"*/
extern CString g_sLangID_Native_CtrlBlkOutEndFrmNum;
extern CString g_sLangTxt_Native_CtrlBlkOutEndFrmNum;
/*"控制块延时补偿值(单位:us)"*/
extern CString g_sLangID_Native_CtrlBlkDelayCompValue;
extern CString g_sLangTxt_Native_CtrlBlkDelayCompValue;
/*"采样值控制块数量"*/
extern CString g_sLangID_Native_NumOfSVCBs;
extern CString g_sLangTxt_Native_NumOfSVCBs;
/*"GOOSE控制块数量"*/
extern CString g_sLangID_Native_NumOfGCBs;
extern CString g_sLangTxt_Native_NumOfGCBs;
/*"SV回放模式(0:按时间间隔,1:等间隔,2:自定义)"*/
extern CString g_sLangID_Native_SVReplayMode;
extern CString g_sLangTxt_Native_SVReplayMode;
/*"GOOSE回放模式(0:按时间间隔,1:等间隔)"*/
extern CString g_sLangID_Native_GOOSEReplayMode;
extern CString g_sLangTxt_Native_GOOSEReplayMode;
/*"SV等间隔回放间隔时间(us)"*/
extern CString g_sLangID_Native_SVEqReplayIntervalTime_us;
extern CString g_sLangTxt_Native_SVEqReplayIntervalTime_us;
/*"GOOSE等间隔回放间隔时间(us)"*/
extern CString g_sLangID_Native_GOOSEEqReplayIntervalTime_us;
extern CString g_sLangTxt_Native_GOOSEEqReplayIntervalTime_us;
/*"自定义回放抖动值(us)"*/
extern CString g_sLangID_Native_CustomReplayJitter_us;
extern CString g_sLangTxt_Native_CustomReplayJitter_us;
/*"是否循环(0不循环,1循环)"*/
extern CString g_sLangID_Native_LoopingFlag;
extern CString g_sLangTxt_Native_LoopingFlag;
/*"回放区间设置类型(0全部回放,1部分回放)"*/
extern CString g_sLangID_Native_ReplayIntervalType;
extern CString g_sLangTxt_Native_ReplayIntervalType;
/*"输出起始帧号(全部控制块排序)"*/
extern CString g_sLangID_Native_StartFrameNum;
extern CString g_sLangTxt_Native_StartFrameNum;
/*"输出结束帧号(全部控制块排序)"*/
extern CString g_sLangID_Native_EndFrameNum;
extern CString g_sLangTxt_Native_EndFrameNum;
/*"GPS触发时刻(时)"*/
extern CString g_sLangID_Native_GPSTriggerTime_hr;
extern CString g_sLangTxt_Native_GPSTriggerTime_hr;
/*"GPS触发时刻(分)"*/
extern CString g_sLangID_Native_GPSTriggerTime_min;
extern CString g_sLangTxt_Native_GPSTriggerTime_min;
/*"GPS触发时刻(秒)"*/
extern CString g_sLangID_Native_GPSTriggerTime_sec;
extern CString g_sLangTxt_Native_GPSTriggerTime_sec;
/*"输出时长(s)"*/
extern CString g_sLangID_Native_OutputDuration_sec;
extern CString g_sLangTxt_Native_OutputDuration_sec;
/*"开入%c选择"*/
extern CString g_sLangID_Native_InputSelection;
extern CString g_sLangTxt_Native_InputSelection;

//tmt_gradient_test
/*"返回系数整定值"*/
extern CString g_sLangID_Native_FeedbackCoefSettingVal;
extern CString g_sLangTxt_Native_FeedbackCoefSettingVal;
/*"边界角1整定值"*/
extern CString g_sLangID_Native_BoundaryAngle1SetVal;
extern CString g_sLangTxt_Native_BoundaryAngle1SetVal;
/*"边界角2整定值"*/
extern CString g_sLangID_Native_BoundaryAngle2SetVal;
extern CString g_sLangTxt_Native_BoundaryAngle2SetVal;
/*"最大灵敏角整定值"*/
extern CString g_sLangID_Native_MaxSensitivityAngleSetVal;
extern CString g_sLangTxt_Native_MaxSensitivityAngleSetVal;
/*"步长时间(秒)"*/
extern CString g_sLangID_Native_StepTimeSec;
extern CString g_sLangTxt_Native_StepTimeSec;
/*"故障态组2电压幅值"*/
extern CString g_sLangID_Native_FSG2VoltageAmplitude;
extern CString g_sLangTxt_Native_FSG2VoltageAmplitude;
/*"故障态组2电流幅值"*/
extern CString g_sLangID_Native_FSG2CurrentAmplitude;
extern CString g_sLangTxt_Native_FSG2CurrentAmplitude;
/*"额定电压幅值"*/
extern CString g_sLangID_Native_RatedVoltageAmplitude;
extern CString g_sLangTxt_Native_RatedVoltageAmplitude;
/*"常态电压相序"*/
extern CString g_sLangID_Native_NomVoltPhaseSeq;
extern CString g_sLangTxt_Native_NomVoltPhaseSeq;
/*"常态电流相序"*/
extern CString g_sLangID_Native_NomCurrPhaseSeq;
extern CString g_sLangTxt_Native_NomCurrPhaseSeq;
/*"常态电压幅值"*/
extern CString g_sLangID_Native_NomVoltAmplitude;
extern CString g_sLangTxt_Native_NomVoltAmplitude;
/*"常态电流幅值"*/
extern CString g_sLangID_Native_NomCurrAmplitude;
extern CString g_sLangTxt_Native_NomCurrAmplitude;

/*"Ua1幅值"*/
extern CString g_sLangID_Native_Ua1Amp;
extern CString g_sLangTxt_Native_Ua1Amp;
/*"Ua1相位"*/
extern CString g_sLangID_Native_Ua1Ph;
extern CString g_sLangTxt_Native_Ua1Ph;
/*"Ua2幅值"*/
extern CString g_sLangID_Native_Ua2Amp;
extern CString g_sLangTxt_Native_Ua2Amp;
/*"Ua2相位"*/
extern CString g_sLangID_Native_Ua2Ph;
extern CString g_sLangTxt_Native_Ua2Ph;

/*"Ub1幅值"*/
extern CString g_sLangID_Native_Ub1Amp;
extern CString g_sLangTxt_Native_Ub1Amp;
/*"Ub1相位"*/
extern CString g_sLangID_Native_Ub1Ph;
extern CString g_sLangTxt_Native_Ub1Ph;
/*"Ub2幅值"*/
extern CString g_sLangID_Native_Ub2Amp;
extern CString g_sLangTxt_Native_Ub2Amp;
/*"Ub2相位"*/
extern CString g_sLangID_Native_Ub2Ph;
extern CString g_sLangTxt_Native_Ub2Ph;

/*"Uc1幅值"*/
extern CString g_sLangID_Native_Uc1Amp;
extern CString g_sLangTxt_Native_Uc1Amp;
/*"Uc1相位"*/
extern CString g_sLangID_Native_Uc1Ph;
extern CString g_sLangTxt_Native_Uc1Ph;
/*"Uc2幅值"*/
extern CString g_sLangID_Native_Uc2Amp;
extern CString g_sLangTxt_Native_Uc2Amp;
/*"Uc2相位"*/
extern CString g_sLangID_Native_Uc2Ph;
extern CString g_sLangTxt_Native_Uc2Ph;

/*"Ia1幅值"*/
extern CString g_sLangID_Native_Ia1Amp;
extern CString g_sLangTxt_Native_Ia1Amp;
/*"Ia1相位"*/
extern CString g_sLangID_Native_Ia1Ph;
extern CString g_sLangTxt_Native_Ia1Ph;
/*"Ia2幅值"*/
extern CString g_sLangID_Native_Ia2Amp;
extern CString g_sLangTxt_Native_Ia2Amp;
/*"Ia2相位"*/
extern CString g_sLangID_Native_Ia2Ph;
extern CString g_sLangTxt_Native_Ia2Ph;

/*"Ib1幅值"*/
extern CString g_sLangID_Native_Ib1Amp;
extern CString g_sLangTxt_Native_Ib1Amp;
/*"Ib1相位"*/
extern CString g_sLangID_Native_Ib1Ph;
extern CString g_sLangTxt_Native_Ib1Ph;
/*"Ib2幅值"*/
extern CString g_sLangID_Native_Ib2Amp;
extern CString g_sLangTxt_Native_Ib2Amp;
/*"Ib2相位"*/
extern CString g_sLangID_Native_Ib2Ph;
extern CString g_sLangTxt_Native_Ib2Ph;

/*"Ic1幅值"*/
extern CString g_sLangID_Native_Ic1Amp;
extern CString g_sLangTxt_Native_Ic1Amp;
/*"Ic1相位"*/
extern CString g_sLangID_Native_Ic1Ph;
extern CString g_sLangTxt_Native_Ic1Ph;
/*"Ic2幅值"*/
extern CString g_sLangID_Native_Ic2Amp;
extern CString g_sLangTxt_Native_Ic2Amp;
/*"Ic2相位"*/
extern CString g_sLangID_Native_Ic2Ph;
extern CString g_sLangTxt_Native_Ic2Ph;

/*"频率动作值绝对误差"*/
extern CString g_sLangID_Native_FreqPickAbsErr;
extern CString g_sLangTxt_Native_FreqPickAbsErr;
/*"频率动作值相对误差"*/
extern CString g_sLangID_Native_FreqPickRelErr;
extern CString g_sLangTxt_Native_FreqPickRelErr;
/*"频率动作值误差判断逻辑"*/
extern CString g_sLangID_Native_FreqPickErrDetectLogic;
extern CString g_sLangTxt_Native_FreqPickErrDetectLogic;
/*"最大灵敏角绝对误差"*/
extern CString g_sLangID_Native_MaxSensAngAbsErr;
extern CString g_sLangTxt_Native_MaxSensAngAbsErr;
/*"最大灵敏角相对误差"*/
extern CString g_sLangID_Native_MaxSensAngRelErr;
extern CString g_sLangTxt_Native_MaxSensAngRelErr;
/*"最大灵敏角误差判断逻辑"*/
extern CString g_sLangID_Native_MaxSensAngErrDetectLogic;
extern CString g_sLangTxt_Native_MaxSensAngErrDetectLogic;
/*"边界角1绝对误差"*/
extern CString g_sLangID_Native_BndryAng1AbsErr;
extern CString g_sLangTxt_Native_BndryAng1AbsErr;
/*"边界角1相对误差"*/
extern CString g_sLangID_Native_BndryAng1RelErr;
extern CString g_sLangTxt_Native_BndryAng1RelErr;
/*"边界角1误差判断逻辑"*/
extern CString g_sLangID_Native_BndryAng1ErrDetectLogic;
extern CString g_sLangTxt_Native_BndryAng1ErrDetectLogic;
/*"边界角2绝对误差"*/
extern CString g_sLangID_Native_BndryAng2AbsErr;
extern CString g_sLangTxt_Native_BndryAng2AbsErr;
/*"边界角2相对误差"*/
extern CString g_sLangID_Native_BndryAng2RelErr;
extern CString g_sLangTxt_Native_BndryAng2RelErr;
/*"边界角2误差判断逻辑"*/
extern CString g_sLangID_Native_BndryAng2ErrDetectLogic;
extern CString g_sLangTxt_Native_BndryAng2ErrDetectLogic;
/*"返回系数有效"*/
extern CString g_sLangID_Native_RetCoeffValid;
extern CString g_sLangTxt_Native_RetCoeffValid;
/*"绝对误差有效"*/
extern CString g_sLangID_Native_AbsErrValid;
extern CString g_sLangTxt_Native_AbsErrValid;
/*"频率动作值误差"*/
extern CString g_sLangID_Native_FreqTripValErr;
extern CString g_sLangTxt_Native_FreqTripValErr;
/*"相位动作值误差"*/
extern CString g_sLangID_Native_PhaseTripValErr;
extern CString g_sLangTxt_Native_PhaseTripValErr;
/*"返回系数误差"*/
extern CString g_sLangID_Native_RetCoeffError;
extern CString g_sLangTxt_Native_RetCoeffError;
/*"最大灵敏角误差"*/
extern CString g_sLangID_Native_MaxSensAngleErr;
extern CString g_sLangTxt_Native_MaxSensAngleErr;
/*"边界角1误差"*/
extern CString g_sLangID_Native_BndryAngle1Err;
extern CString g_sLangTxt_Native_BndryAngle1Err;
/*"边界角2误差"*/
extern CString g_sLangID_Native_BndryAngle2Err;
extern CString g_sLangTxt_Native_BndryAngle2Err;

//tmt_harm_test
/*"%d次谐波相位"*/
extern CString g_sLangID_Native_NthHarmPhase;
extern CString g_sLangTxt_Native_NthHarmPhase;
/*"%d次谐波幅值"*/
extern CString g_sLangID_Native_NthHarmAmpl;
extern CString g_sLangTxt_Native_NthHarmAmpl;
/*"直流分量"*/
extern CString g_sLangID_Native_DCCompVaule;
extern CString g_sLangTxt_Native_DCCompVaule;
/*"自动变化设置"*/
extern CString g_sLangID_Native_AutoVarConfig;
extern CString g_sLangTxt_Native_AutoVarConfig;
/*"是否自动变化"*/
extern CString g_sLangID_Native_AutoVarStatus;
extern CString g_sLangTxt_Native_AutoVarStatus;
/*"变化量选择"*/
extern CString g_sLangID_Native_VarSelect;
extern CString g_sLangTxt_Native_VarSelect;
/*"变化类型选择"*/
extern CString g_sLangID_Native_VarTypeSelect;
extern CString g_sLangTxt_Native_VarTypeSelect;
/*"变化谐波次数"*/
extern CString g_sLangID_Native_VarHarmonicNum;
extern CString g_sLangTxt_Native_VarHarmonicNum;

//tmt_manu_test
/*"是否以直流模式输出"*/
extern CString g_sLangID_Native_DCOutputMode;
extern CString g_sLangTxt_Native_DCOutputMode;
/*"谐波叠加"*/
extern CString g_sLangID_Native_HarmSuperposition;
extern CString g_sLangTxt_Native_HarmSuperposition;
/*"谐波选择"*/
extern CString g_sLangID_Native_HarmSelection;
extern CString g_sLangTxt_Native_HarmSelection;
/*"合并单元"*/
extern CString g_sLangID_Native_MrgUnit;
extern CString g_sLangTxt_Native_MrgUnit;
/*"算法选择(0:插值法  1:同步法)"*/
extern CString g_sLangID_Native_AlgorithmSelection;
extern CString g_sLangTxt_Native_AlgorithmSelection;
/*"PPS设置(0:上升沿有效  1:下降沿有效 2:无PPS)"*/
extern CString g_sLangID_Native_PPSConfiguration;
extern CString g_sLangTxt_Native_PPSConfiguration;
/*"额定相电压(零漂计算)"*/
extern CString g_sLangID_Native_RatedV_Phase_ZeroDriftCalc;
extern CString g_sLangTxt_Native_RatedV_Phase_ZeroDriftCalc;
/*"额定相电流(零漂计算)"*/
extern CString g_sLangID_Native_RatedI_Phase_ZeroDriftCalc;
extern CString g_sLangTxt_Native_RatedI_Phase_ZeroDriftCalc;
/*"守时精度测试时同步时长(单位:s)"*/
extern CString g_sLangID_Native_SyncDur_TAT;
extern CString g_sLangTxt_Native_SyncDur_TAT;
/*"无PPS时延时补偿值(对时守时测试用,单位:μs)"*/
extern CString g_sLangID_Native_DelayComp_NoPPS;
extern CString g_sLangTxt_Native_DelayComp_NoPPS;
/*"是否使用自定义报告次数(合并单元)"*/
extern CString g_sLangID_Native_CustomRepCnt_Use_MU;
extern CString g_sLangTxt_Native_CustomRepCnt_Use_MU;
/*"自定义报告测试次数(合并单元)"*/
extern CString g_sLangID_Native_CustomRepTestCnt_MU;
extern CString g_sLangTxt_Native_CustomRepTestCnt_MU;
/*"每次测试时间(合并单元,单位秒)"*/
extern CString g_sLangID_Native_TestDurPerTest_MU_sec;
extern CString g_sLangTxt_Native_TestDurPerTest_MU_sec;
/*"MU时间测试结果"*/
extern CString g_sLangID_Native_MUTimeTestResults;
extern CString g_sLangTxt_Native_MUTimeTestResults;
/*"已测试时长"*/
extern CString g_sLangID_Native_TestedDur;
extern CString g_sLangTxt_Native_TestedDur;
/*"最大误差时间"*/
extern CString g_sLangID_Native_MaxErrTime;
extern CString g_sLangTxt_Native_MaxErrTime;
/*"最小误差时间"*/
extern CString g_sLangID_Native_MinErrTime;
extern CString g_sLangTxt_Native_MinErrTime;
/*"平均误差时间"*/
extern CString g_sLangID_Native_AvgErrTime;
extern CString g_sLangTxt_Native_AvgErrTime;
/*"时间精度测试结果"*/
extern CString g_sLangID_Native_TimeAccTestResults;
extern CString g_sLangTxt_Native_TimeAccTestResults;

/*"Ua频率"*/
extern CString g_sLangID_Native_UaFreq;
extern CString g_sLangTxt_Native_UaFreq;
/*"Ub频率"*/
extern CString g_sLangID_Native_UbFreq;
extern CString g_sLangTxt_Native_UbFreq;
/*"Uc频率"*/
extern CString g_sLangID_Native_UcFreq;
extern CString g_sLangTxt_Native_UcFreq;

/*"Uap幅值"*/
extern CString g_sLangID_Native_UapAmp;
extern CString g_sLangTxt_Native_UapAmp;
/*"Uap相位"*/
extern CString g_sLangID_Native_UapPhase;
extern CString g_sLangTxt_Native_UapPhase;
/*"Uap频率"*/
extern CString g_sLangID_Native_UapFreq;
extern CString g_sLangTxt_Native_UapFreq;

/*"Ubp幅值"*/
extern CString g_sLangID_Native_UbpAmp;
extern CString g_sLangTxt_Native_UbpAmp;
/*"Ubp相位"*/
extern CString g_sLangID_Native_UbpPhase;
extern CString g_sLangTxt_Native_UbpPhase;
/*"Ubp频率"*/
extern CString g_sLangID_Native_UbpFreq;
extern CString g_sLangTxt_Native_UbpFreq;

/*"Ucp幅值"*/
extern CString g_sLangID_Native_UcpAmp;
extern CString g_sLangTxt_Native_UcpAmp;
/*"Ucp相位"*/
extern CString g_sLangID_Native_UcpPhase;
extern CString g_sLangTxt_Native_UcpPhase;
/*"Ucp频率"*/
extern CString g_sLangID_Native_UcpFreq;
extern CString g_sLangTxt_Native_UcpFreq;

/*"Ia幅值"*/
extern CString g_sLangID_Native_IaAmp;
extern CString g_sLangTxt_Native_IaAmp;
/*"Ia相位"*/
extern CString g_sLangID_Native_IaPhase;
extern CString g_sLangTxt_Native_IaPhase;
/*"Ia频率"*/
extern CString g_sLangID_Native_IaFreq;
extern CString g_sLangTxt_Native_IaFreq;

/*"Ib幅值"*/
extern CString g_sLangID_Native_IbAmp;
extern CString g_sLangTxt_Native_IbAmp;
/*"Ib相位"*/
extern CString g_sLangID_Native_IbPhase;
extern CString g_sLangTxt_Native_IbPhase;
/*"Ib频率"*/
extern CString g_sLangID_Native_IbFreq;
extern CString g_sLangTxt_Native_IbFreq;

/*"Ic幅值"*/
extern CString g_sLangID_Native_IcAmp;
extern CString g_sLangTxt_Native_IcAmp;
/*"Ic相位"*/
extern CString g_sLangID_Native_IcPhase;
extern CString g_sLangTxt_Native_IcPhase;
/*"Ic频率"*/
extern CString g_sLangID_Native_IcFreq;
extern CString g_sLangTxt_Native_IcFreq;

/*"Iap幅值"*/
extern CString g_sLangID_Native_IapAmp;
extern CString g_sLangTxt_Native_IapAmp;
/*"Iap相位"*/
extern CString g_sLangID_Native_IapPhase;
extern CString g_sLangTxt_Native_IapPhase;
/*"Iap频率"*/
extern CString g_sLangID_Native_IapFreq;
extern CString g_sLangTxt_Native_IapFreq;

/*"Ibp幅值"*/
extern CString g_sLangID_Native_IbpAmp;
extern CString g_sLangTxt_Native_IbpAmp;
/*"Ibp相位"*/
extern CString g_sLangID_Native_IbpPhase;
extern CString g_sLangTxt_Native_IbpPhase;
/*"Ibp频率"*/
extern CString g_sLangID_Native_IbpFreq;
extern CString g_sLangTxt_Native_IbpFreq;

/*"Icp幅值"*/
extern CString g_sLangID_Native_IcpAmp;
extern CString g_sLangTxt_Native_IcpAmp;
/*"Icp相位"*/
extern CString g_sLangID_Native_IcpPhase;
extern CString g_sLangTxt_Native_IcpPhase;
/*"Icp频率"*/
extern CString g_sLangID_Native_IcpFreq;
extern CString g_sLangTxt_Native_IcpFreq;

/*"测试功能类别(0:普通手动试验1:MU精度测试2:MU零漂测试)"*/
extern CString g_sLangID_Native_TestFuncCategory;
extern CString g_sLangTxt_Native_TestFuncCategory;

//tmt_pt_test
/*"PT1阻值"*/
extern CString g_sLangID_Native_PT1Impedance;
extern CString g_sLangTxt_Native_PT1Impedance;
/*"PT2阻值"*/
extern CString g_sLangID_Native_PT2Impedance;
extern CString g_sLangTxt_Native_PT2Impedance;

//tmt_record
/*"接收光口"*/
extern CString g_sLangID_Native_RecvOptPort;
extern CString g_sLangTxt_Native_RecvOptPort;
/*"订阅总数"*/
extern CString g_sLangID_Native_TotalSubs;
extern CString g_sLangTxt_Native_TotalSubs;


//tmt_NEW
/*"Uas幅值"*/
extern CString g_sLangID_Native_UasAmp;
extern CString g_sLangTxt_Native_UasAmp;
/*"Uas相位"*/
extern CString g_sLangID_Native_UasPhase;
extern CString g_sLangTxt_Native_UasPhase;
/*"Uas频率"*/
extern CString g_sLangID_Native_UasFreq;
extern CString g_sLangTxt_Native_UasFreq;

/*"Ubs幅值"*/
extern CString g_sLangID_Native_UbsAmp;
extern CString g_sLangTxt_Native_UbsAmp;
/*"Ubs相位"*/
extern CString g_sLangID_Native_UbsPhase;
extern CString g_sLangTxt_Native_UbsPhase;
/*"Ubs频率"*/
extern CString g_sLangID_Native_UbsFreq;
extern CString g_sLangTxt_Native_UbsFreq;

/*"Ucs幅值"*/
extern CString g_sLangID_Native_UcsAmp;
extern CString g_sLangTxt_Native_UcsAmp;
/*"Ucs相位"*/
extern CString g_sLangID_Native_UcsPhase;
extern CString g_sLangTxt_Native_UcsPhase;
/*"Ucs频率"*/
extern CString g_sLangID_Native_UcsFreq;
extern CString g_sLangTxt_Native_UcsFreq;

/*"Uat幅值"*/
extern CString g_sLangID_Native_UatAmp;
extern CString g_sLangTxt_Native_UatAmp;
/*"Uat相位"*/
extern CString g_sLangID_Native_UatPhase;
extern CString g_sLangTxt_Native_UatPhase;
/*"Uat频率"*/
extern CString g_sLangID_Native_UatFreq;
extern CString g_sLangTxt_Native_UatFreq;

/*"Ubt幅值"*/
extern CString g_sLangID_Native_UbtAmp;
extern CString g_sLangTxt_Native_UbtAmp;
/*"Ubt相位"*/
extern CString g_sLangID_Native_UbtPhase;
extern CString g_sLangTxt_Native_UbtPhase;
/*"Ubt频率"*/
extern CString g_sLangID_Native_UbtFreq;
extern CString g_sLangTxt_Native_UbtFreq;

/*"Uct幅值"*/
extern CString g_sLangID_Native_UctAmp;
extern CString g_sLangTxt_Native_UctAmp;
/*"Uct相位"*/
extern CString g_sLangID_Native_UctPhase;
extern CString g_sLangTxt_Native_UctPhase;
/*"Uct频率"*/
extern CString g_sLangID_Native_UctFreq;
extern CString g_sLangTxt_Native_UctFreq;

/*"Ias幅值"*/
extern CString g_sLangID_Native_IasAmp;
extern CString g_sLangTxt_Native_IasAmp;
/*"Ias相位"*/
extern CString g_sLangID_Native_IasPhase;
extern CString g_sLangTxt_Native_IasPhase;
/*"Ias频率"*/
extern CString g_sLangID_Native_IasFreq;
extern CString g_sLangTxt_Native_IasFreq;

/*"Ibs幅值"*/
extern CString g_sLangID_Native_IbsAmp;
extern CString g_sLangTxt_Native_IbsAmp;
/*"Ibs相位"*/
extern CString g_sLangID_Native_IbsPhase;
extern CString g_sLangTxt_Native_IbsPhase;
/*"Ibs频率"*/
extern CString g_sLangID_Native_IbsFreq;
extern CString g_sLangTxt_Native_IbsFreq;

/*"Ics幅值"*/
extern CString g_sLangID_Native_IcsAmp;
extern CString g_sLangTxt_Native_IcsAmp;
/*"Ics相位"*/
extern CString g_sLangID_Native_IcsPhase;
extern CString g_sLangTxt_Native_IcsPhase;
/*"Ics频率"*/
extern CString g_sLangID_Native_IcsFreq;
extern CString g_sLangTxt_Native_IcsFreq;

/*"Iat幅值"*/
extern CString g_sLangID_Native_IatAmp;
extern CString g_sLangTxt_Native_IatAmp;
/*"Iat相位"*/
extern CString g_sLangID_Native_IatPhase;
extern CString g_sLangTxt_Native_IatPhase;
/*"Iat频率"*/
extern CString g_sLangID_Native_IatFreq;
extern CString g_sLangTxt_Native_IatFreq;

/*"Ibt幅值"*/
extern CString g_sLangID_Native_IbtAmp;
extern CString g_sLangTxt_Native_IbtAmp;
/*"Ibt相位"*/
extern CString g_sLangID_Native_IbtPhase;
extern CString g_sLangTxt_Native_IbtPhase;
/*"Ibt频率"*/
extern CString g_sLangID_Native_IbtFreq;
extern CString g_sLangTxt_Native_IbtFreq;

/*"Ict幅值"*/
extern CString g_sLangID_Native_IctAmp;
extern CString g_sLangTxt_Native_IctAmp;
/*"Ict相位"*/
extern CString g_sLangID_Native_IctPhase;
extern CString g_sLangTxt_Native_IctPhase;
/*"Ict频率"*/
extern CString g_sLangID_Native_IctFreq;
extern CString g_sLangTxt_Native_IctFreq;




//tmt_replay_test
/*"模块%d"*/
extern CString g_sLangID_Native_ModReplace;
extern CString g_sLangTxt_Native_ModReplace;
/*"测试仪通道%d_A通道序号"*/
extern CString g_sLangID_Native_TIC_A_Chn_Num;
extern CString g_sLangTxt_Native_TIC_A_Chn_Num;
/*"测试仪通道%d_B通道序号"*/
extern CString g_sLangID_Native_TIC_B_Chn_Num;
extern CString g_sLangTxt_Native_TIC_B_Chn_Num;
/*"测试仪通道%d_变比"*/
extern CString g_sLangID_Native_TIC_TransfRatio;
extern CString g_sLangTxt_Native_TIC_TransfRatio;
/*"采样频率"*/
extern CString g_sLangID_Native_SampFreq;
extern CString g_sLangTxt_Native_SampFreq;
/*"PT变比一次值"*/
extern CString g_sLangID_Native_PT_TxRatio_Primary;
extern CString g_sLangTxt_Native_PT_TxRatio_Primary;
/*"PT变比二次值"*/
extern CString g_sLangID_Native_PT_TxRatio_Secondary;
extern CString g_sLangTxt_Native_PT_TxRatio_Secondary;
/*"CT变比一次值"*/
extern CString g_sLangID_Native_CT_TxRatio_Primary;
extern CString g_sLangTxt_Native_CT_TxRatio_Primary;
/*"CT变比二次值"*/
extern CString g_sLangID_Native_CT_TxRatio_Secondary;
extern CString g_sLangTxt_Native_CT_TxRatio_Secondary;
/*"模块数"*/
extern CString g_sLangID_Native_NumOfModules;
extern CString g_sLangTxt_Native_NumOfModules;
/*"录波文件名称"*/
extern CString g_sLangID_Native_WaveFileName;
extern CString g_sLangTxt_Native_WaveFileName;
/*"周波数"*/
extern CString g_sLangID_Native_NumCycles;
extern CString g_sLangTxt_Native_NumCycles;
/*"触发后模式"*/
extern CString g_sLangID_Native_PostTrigMode;
extern CString g_sLangTxt_Native_PostTrigMode;
/*"实验触发时间"*/
extern CString g_sLangID_Native_ExpTrigTime;
extern CString g_sLangTxt_Native_ExpTrigTime;
/*"全部循环次数"*/
extern CString g_sLangID_Native_CycleIndex;
extern CString g_sLangTxt_Native_CycleIndex;
/*"手动控制"*/
extern CString g_sLangID_Native_ManualControl;
extern CString g_sLangTxt_Native_ManualControl;	 
/*"时间间隔"*/
extern CString g_sLangID_Native_ReplayInterval;
extern CString g_sLangTxt_Native_ReplayInterval;
//阻抗特性编辑框
extern CString g_sLangID_Native_ImpedanceEditBox;
extern CString g_sLangTxt_Native_ImpedanceEditBox;

extern CString g_sLangID_Native_SeqComp;
extern CString g_sLangTxt_Native_SeqComp;


//第九周吕
//extern CString g_sLangID_Native_jumpctrl;
//extern CString g_sLangTxt_Native_jumpctrl;//跳合信号控制
//extern CString g_sLangID_Native_timectrl;
//extern CString g_sLangTxt_Native_timectrl;//时间控制
//extern CString g_sLangID_Native_totalweight;
//extern CString g_sLangTxt_Native_totalweight;//综重（单重+三重）
//extern CString g_sLangID_Native_tripleweight;
//extern CString g_sLangTxt_Native_tripleweight;//三重
//extern CString g_sLangID_Native_norepeat;
//extern CString g_sLangTxt_Native_norepeat;//不重合
//extern CString g_sLangID_Native_Totransformer;
//extern CString g_sLangTxt_Native_Totransformer;//指向变压器
//extern CString g_sLangID_Native_lagrange;
//extern CString g_sLangTxt_Native_lagrange;//拉格朗日插值法
//extern CString g_sLangID_Native_linear;
//extern CString g_sLangTxt_Native_linear;//线性插值法
//extern CString g_sLangID_Native_faultvoltype;
//extern CString g_sLangTxt_Native_faultvoltype;//故障电压类型
//
//extern CString g_sLangID_Native_Difsetting;
//extern CString g_sLangTxt_Native_Difsetting;//差动定值整定方式
//extern CString g_sLangID_Native_DifCurChoose;
//extern CString g_sLangTxt_Native_DifCurChoose;//差动基准电流选择
//extern CString g_sLangID_Native_harmonicnumber;
//extern CString g_sLangTxt_Native_harmonicnumber;//谐波次数选择
//extern CString g_sLangID_Native_CuroutputPhase;
//extern CString g_sLangTxt_Native_CuroutputPhase;//电流输出相
//extern CString g_sLangID_Native_PhaseAshort;
//extern CString g_sLangTxt_Native_PhaseAshort;//A相短路
//extern CString g_sLangID_Native_PhaseBshort;
//extern CString g_sLangTxt_Native_PhaseBshort;//B相短路
//extern CString g_sLangID_Native_PhaseCshort;
//extern CString g_sLangTxt_Native_PhaseCshort;//C相短路
//extern CString g_sLangID_Native_PhaseABCshort;
//extern CString g_sLangTxt_Native_PhaseABCshort;//ABC相短路


//UI
//Harm
extern CString g_sLangID_Native_VolactValue;
extern CString g_sLangTxt_Native_VolactValue;//电压动作值(%)
extern CString g_sLangID_Native_CuractValue;
extern CString g_sLangTxt_Native_CuractValue;//电流动作值(%)
extern CString g_sLangID_Native_harmonicNotChecked;
extern CString g_sLangTxt_Native_harmonicNotChecked;//指定通道的谐波未被勾选!

//IEC61850Config
extern CString g_sLangID_Native_DCVmapping;
extern CString g_sLangTxt_Native_DCVmapping;//直流电压映射
extern CString g_sLangID_Native_DCImapping;
extern CString g_sLangTxt_Native_DCImapping;//直流电流映射
extern CString g_sLangID_Native_ACVmapping;
extern CString g_sLangTxt_Native_ACVmapping;//交流电压映射
extern CString g_sLangID_Native_ACImapping;
extern CString g_sLangTxt_Native_ACImapping;//交流电流映射
extern CString g_sLangID_Native_FailtoGetsclPath;
extern CString g_sLangTxt_Native_FailtoGetsclPath;//获取SCL文件路径失败(%s).
extern CString g_sLangID_Native_codesSetting;
extern CString g_sLangTxt_Native_codesSetting;//码值设置
extern CString g_sLangID_Native_DCPart;
extern CString g_sLangTxt_Native_DCPart;//直流部分
extern CString g_sLangID_Native_ACPart;
extern CString g_sLangTxt_Native_ACPart;//交流部分

extern CString g_sLangID_Native_selected;
extern CString g_sLangTxt_Native_selected;//已选中
extern CString g_sLangID_Native_schematic;
extern CString g_sLangTxt_Native_schematic;//示意图
extern CString g_sLangID_Native_codesValue;
extern CString g_sLangTxt_Native_codesValue;//码值

//ImportDvmFile
extern CString g_sLangID_Native_modifyto;
extern CString g_sLangTxt_Native_modifyto;//修改为
extern CString g_sLangID_Native_function;
extern CString g_sLangTxt_Native_function;//功能
extern CString g_sLangID_Native_completeconfig;
extern CString g_sLangTxt_Native_completeconfig;//完成配置
extern CString g_sLangID_Native_nextitem;
extern CString g_sLangTxt_Native_nextitem;//上一项
extern CString g_sLangID_Native_previtem;
extern CString g_sLangTxt_Native_previtem;//上一项
extern CString g_sLangID_Native_ttybzd;
extern CString g_sLangTxt_Native_ttybzd;//_投退压板整定
extern CString g_sLangID_Native_FixedValueSet;
extern CString g_sLangTxt_Native_FixedValueSet;//_修改定值整定

//KeyBoard
extern CString g_sLangID_Native_PYResnotFound;
extern CString g_sLangTxt_Native_PYResnotFound;//没有找到中文拼音资源文件!

//
extern CString g_sLangID_Native_dataid;
extern CString g_sLangTxt_Native_dataid;//数据ID
extern CString g_sLangID_Native_paramselect;
extern CString g_sLangTxt_Native_paramselect;//参数选择

extern CString g_sLangID_Native_globalparams;
extern CString g_sLangTxt_Native_globalparams;//全局参数
extern CString g_sLangID_Native_reportdata;
extern CString g_sLangTxt_Native_reportdata;//报告数据
extern CString g_sLangID_Native_switchreport;
extern CString g_sLangTxt_Native_switchreport;//切换报告
extern CString g_sLangID_Native_reportdataname;
extern CString g_sLangTxt_Native_reportdataname;//报告数据名称

extern CString g_sLangID_Native_paramone;
extern CString g_sLangTxt_Native_paramone;//参数一
extern CString g_sLangID_Native_paramtwo;
extern CString g_sLangTxt_Native_paramtwo;//参数二
extern CString g_sLangID_Native_baselineparams;
extern CString g_sLangTxt_Native_baselineparams;//基准参数
extern CString g_sLangID_Native_errorresult;
extern CString g_sLangTxt_Native_errorresult;//误差结果
extern CString g_sLangID_Native_errorlimit;
extern CString g_sLangTxt_Native_errorlimit;//误差限
extern CString g_sLangID_Native_notcalculated;
extern CString g_sLangTxt_Native_notcalculated;//未计算
extern CString g_sLangID_Native_baseline_min;
extern CString g_sLangTxt_Native_baseline_min;//基准-最小值
extern CString g_sLangID_Native_baseline_max;
extern CString g_sLangTxt_Native_baseline_max;//基准-最大值
extern CString g_sLangID_Native_operationresult;
extern CString g_sLangTxt_Native_operationresult;//运算结果



//第九周许
//10.30
//请先在左侧选中需要映射的参数，然后再进行映射……
extern CString g_sLangID_Native_SelectParamFirst;
extern CString g_sLangTxt_Native_SelectParamFirst;
//当前配置没找到有效的映射数据，配置无效！
extern CString g_sLangID_Native_NoValidMapData;
extern CString g_sLangTxt_Native_NoValidMapData;
//装置模型：（先在左侧表格，选中需要映射的参数，然后双击映射）
extern CString g_sLangID_Native_DeviceModel;
extern CString g_sLangTxt_Native_DeviceModel;
//数据集：
extern CString g_sLangID_Native_Dataset;
extern CString g_sLangTxt_Native_Dataset;
//新增
extern CString g_sLangID_Native_AddNew;
extern CString g_sLangTxt_Native_AddNew;
//清空所有映射
extern CString g_sLangID_Native_ClearMap;
extern CString g_sLangTxt_Native_ClearMap;
//清除选中映射
extern CString g_sLangID_Native_ClearSel;
extern CString g_sLangTxt_Native_ClearSel;
//自定义名称
extern CString g_sLangID_Native_CustomName;
extern CString g_sLangTxt_Native_CustomName;
//实际装置的数据名称
extern CString g_sLangID_Native_RealDevData;
extern CString g_sLangTxt_Native_RealDevData;
//数据所在数据集
extern CString g_sLangID_Native_DataInSet;
extern CString g_sLangTxt_Native_DataInSet;
//曲线名称:
extern CString g_sLangID_Native_CurveName;
extern CString g_sLangTxt_Native_CurveName;
//1段定时限
extern CString g_sLangID_Native_SingleTimeLimit;
extern CString g_sLangTxt_Native_SingleTimeLimit;
//2段定时限
extern CString g_sLangID_Native_DoubleTimeLimit;
extern CString g_sLangTxt_Native_DoubleTimeLimit;
//3段定时限
extern CString g_sLangID_Native_TripleTimeLimit;
extern CString g_sLangTxt_Native_TripleTimeLimit;
//电流值
extern CString g_sLangID_Native_CurrentValueI;
extern CString g_sLangTxt_Native_CurrentValueI;
//动作门槛
extern CString g_sLangID_Native_ActionThres;
extern CString g_sLangTxt_Native_ActionThres;
//特性曲线元素
extern CString g_sLangID_Native_FeatCurveElem;
extern CString g_sLangTxt_Native_FeatCurveElem;
//IEEE曲线元素设置
extern CString g_sLangID_Native_IEEECurveSet;
extern CString g_sLangTxt_Native_IEEECurveSet;
//IAC曲线元素设置
extern CString g_sLangID_Native_IACCurveSet;
extern CString g_sLangTxt_Native_IACCurveSet;
//I2T曲线元素设置
extern CString g_sLangID_Native_I2TCurveSet;
extern CString g_sLangTxt_Native_I2TCurveSet;
//IEC曲线元素设置
extern CString g_sLangID_Native_IECCurveSet;
extern CString g_sLangTxt_Native_IECCurveSet;
//门槛值
extern CString g_sLangID_Native_Threshold;
extern CString g_sLangTxt_Native_Threshold;
//速断定值
extern CString g_sLangID_Native_QuickBreak;
extern CString g_sLangTxt_Native_QuickBreak;
//第一段
extern CString g_sLangID_Native_FirstPart;
extern CString g_sLangTxt_Native_FirstPart;
//拐点1
extern CString g_sLangID_Native_Inflection1;
extern CString g_sLangTxt_Native_Inflection1;
//第二段
extern CString g_sLangID_Native_SecondPart;
extern CString g_sLangTxt_Native_SecondPart;
//拐点2
extern CString g_sLangID_Native_InflectionPoint2;
extern CString g_sLangTxt_Native_InflectionPoint2;
//当前测试控制程序生成日期(%s).
extern CString g_sLangID_Native_TestCtrlProgDate;
extern CString g_sLangTxt_Native_TestCtrlProgDate;
//输出调试
extern CString g_sLangID_Native_DebugOutput;
extern CString g_sLangTxt_Native_DebugOutput;
//开始输出
//extern CString g_sLangID_Native_StartOutput;
//extern CString g_sLangTxt_Native_StartOutput;
//停止输出
extern CString g_sLangID_Native_StopOutput;
extern CString g_sLangTxt_Native_StopOutput;
//打开文件(%s)失败.
extern CString g_sLangID_Native_OpenFail;
extern CString g_sLangTxt_Native_OpenFail;
//与测试仪断开连接，请检查网络链路是否连通，IP地址及端口配置是否正确；重新连接
extern CString g_sLangID_Native_Disconnect;
extern CString g_sLangTxt_Native_Disconnect;
//状态图
extern CString g_sLangID_Native_StateGraph;
extern CString g_sLangTxt_Native_StateGraph;
//软件资源标识
extern CString g_sLangID_Native_SoftResID;
extern CString g_sLangTxt_Native_SoftResID;
//请输入数值，不能为空！
extern CString g_sLangID_Native_EnterNum;
extern CString g_sLangTxt_Native_EnterNum;
//按周波发送
extern CString g_sLangID_Native_SendByWave;
extern CString g_sLangTxt_Native_SendByWave;
//按秒发送
extern CString g_sLangID_Native_SendBySec;
extern CString g_sLangTxt_Native_SendBySec;
//当前状态%d : 网络标识(0x%s)与原网络标识(0x%s)不一致
extern CString g_sLangID_Native_StateNetID;
extern CString g_sLangTxt_Native_StateNetID;
//导出Word报告
extern CString g_sLangID_Native_ExportWords;
extern CString g_sLangTxt_Native_ExportWords;
//Word报告文件 (*.doc)
extern CString g_sLangID_Native_WordDoc;
extern CString g_sLangTxt_Native_WordDoc;
//导出路径：
extern CString g_sLangID_Native_ExportPath;
extern CString g_sLangTxt_Native_ExportPath;





//第九周马
/*_T("stt_rcd_unzip_file解压缩出错.")*/
extern CString g_sLangID_Native_UnzipError;
extern CString g_sLangTxt_Native_UnzipError;
/*_T("导出Pcap文件界面")*/
extern CString g_sLangID_Native_ExpPcapInterf;
extern CString g_sLangTxt_Native_ExpPcapInterf;
/*_T("原始数据文件:")*/
extern CString g_sLangID_Native_RawDataFile;
extern CString g_sLangTxt_Native_RawDataFile;
/*_T("选择...")*/
extern CString g_sLangID_Native_SelectOmit;
extern CString g_sLangTxt_Native_SelectOmit;
/*_T("Pcap文件名:")*/
extern CString g_sLangID_Native_PcapFileN;
extern CString g_sLangTxt_Native_PcapFileN;
/*_T("开始转换")*/
extern CString g_sLangID_Native_StartConver;
extern CString g_sLangTxt_Native_StartConver;
/*_T("at02d压缩文件(*.at02dz);;at02d文件(*.at02d)")*/
extern CString g_sLangID_Native_at02dCompFiles;
extern CString g_sLangTxt_Native_at02dCompFiles;
/*_T("请先选择原始数据文件.")*/
extern CString g_sLangID_Native_SelectRawFile;
extern CString g_sLangTxt_Native_SelectRawFile;
/*_T("请先设置生成文件名称.")*/
extern CString g_sLangID_Native_SetOutFileName;
extern CString g_sLangTxt_Native_SetOutFileName;
/*_T("当前原始数据文件(%s)不存在.")*/
extern CString g_sLangID_Native_CurRawFileNotEx;
extern CString g_sLangTxt_Native_CurRawFileNotEx;
/*_T("Pcap文件(%s)生成成功.")*/
extern CString g_sLangID_Native_PcapGenSuccess;
extern CString g_sLangTxt_Native_PcapGenSuccess;
/*_T("Pcap文件(%s)生成失败.")*/
extern CString g_sLangID_Native_PcapGenFailed;
extern CString g_sLangTxt_Native_PcapGenFailed;
/*"波特率"*/
extern CString g_sLangID_Native_BaudRate;
extern CString g_sLangTxt_Native_BaudRate;
/*"报文长度"*/
extern CString g_sLangID_Native_MsgLength;
extern CString g_sLangTxt_Native_MsgLength;
/*_T("未知的报文类型(%u).")*/
extern CString g_sLangID_Native_UnkwnMsgType;
extern CString g_sLangTxt_Native_UnkwnMsgType;
/*_T("当前解析的报文帧数为0,需收到报文后,才能关联.")*/
extern CString g_sLangID_Native_CurrPsdM0AssocAftRcvM;
extern CString g_sLangTxt_Native_CurrPsdM0AssocAftRcvM;
/*("录波时间")*/
extern CString g_sLangID_Native_RecTime;
extern CString g_sLangTxt_Native_RecTime;
/*_T("停止录波")*/
extern CString g_sLangID_Native_StopRecrd;
extern CString g_sLangTxt_Native_StopRecrd;
/*_T("有效值")*/
extern CString g_sLangID_Native_ValdValue;
extern CString g_sLangTxt_Native_ValdValue;
/*_T("含有率")*/
extern CString g_sLangID_Native_IncRate;
extern CString g_sLangTxt_Native_IncRate;
/*_T("柱状图")*/
extern CString g_sLangID_Native_BarChar;
extern CString g_sLangTxt_Native_BarChar;
/*_T("录波")*/
extern CString g_sLangID_Native_RecWaveform;
extern CString g_sLangTxt_Native_RecWaveform;
/*_T("当前写文件路径为空.")*/
extern CString g_sLangID_Native_CurrWrtFileEmpty;
extern CString g_sLangTxt_Native_CurrWrtFileEmpty;
/*_T("文件保存为")*/
extern CString g_sLangID_Native_SaveAs;
extern CString g_sLangTxt_Native_SaveAs;
/*_T("文件(%s)保存成功.")*/
extern CString g_sLangID_Native_FileSavedSucc;
extern CString g_sLangTxt_Native_FileSavedSucc;
/*_T("文件(%s)保存失败.")*/
extern CString g_sLangID_Native_FileSaveFailed;
extern CString g_sLangTxt_Native_FileSaveFailed;
/*文件已存在，是否替换？*/
extern CString g_sLangID_Native_FileExist;
extern CString g_sLangTxt_Native_FileExist;
/*文件保存成功*/
extern CString g_sLangID_Native_FileSave;
extern CString g_sLangTxt_Native_FileSave;
/*接收*/
extern CString g_sLangID_Native_Accept;
extern CString g_sLangTxt_Native_Accept;
/*_T("SV报文离散度视图")*/
extern CString g_sLangID_Native_SVMsgDispersView;
extern CString g_sLangTxt_Native_SVMsgDispersView;
/*_T("直流(V/A)")*/
extern CString g_sLangID_Native_DCVoltAmp;
extern CString g_sLangTxt_Native_DCVoltAmp;
/*_T("基波(V/A)")*/
extern CString g_sLangID_Native_FundamentalVA;
extern CString g_sLangTxt_Native_FundamentalVA;
/*_T("底层测试模板生成失败.")*/
extern CString g_sLangID_Native_LowLevelTmplFail;
extern CString g_sLangTxt_Native_LowLevelTmplFail;
/*_T("开始测试命令下发失败.")*/
extern CString g_sLangID_Native_StartTestSendFail;
extern CString g_sLangTxt_Native_StartTestSendFail;
/*_T("停止测试命令下发失败.")*/
extern CString g_sLangID_Native_StopTestSendFail;
extern CString g_sLangTxt_Native_StopTestSendFail;
/*_T("状态%ld动作时间%.4lfs.")*/
extern CString g_sLangID_Native_StatusLDActTime;
extern CString g_sLangTxt_Native_StatusLDActTime;
/*_T("?????????????? OnCmd_NewTest: 关闭打开的测试功能页面，并弹框提示是否保存修改 ???????????")*/
extern CString g_sLangID_Native_CloseFeatPromptSave;
extern CString g_sLangTxt_Native_CloseFeatPromptSave;
//插入数据
extern CString g_sLangID_Native_InsData;
extern CString g_sLangTxt_Native_InsData;
//执行通信
extern CString g_sLangID_Native_ExecComm;
extern CString g_sLangTxt_Native_ExecComm;
//删除选中数据
extern CString g_sLangID_Native_DelSelData;
extern CString g_sLangTxt_Native_DelSelData;
/*"是否变化上送"*/
extern CString g_sLangID_Native_SendChanges;
extern CString g_sLangTxt_Native_SendChanges;
//周期时间
extern CString g_sLangID_Native_CycleTm;
extern CString g_sLangTxt_Native_CycleTm;
//误差名称
extern CString g_sLangID_Native_ErrName;
extern CString g_sLangTxt_Native_ErrName;
//误差值
extern CString g_sLangID_Native_ErrValue;
extern CString g_sLangTxt_Native_ErrValue;
//测试分类
extern CString g_sLangID_Native_TestCat;
extern CString g_sLangTxt_Native_TestCat;
//标题等级
extern CString g_sLangID_Native_TitleLvl;
extern CString g_sLangTxt_Native_TitleLvl;
//项目标识
extern CString g_sLangID_Native_ProjIdent;
extern CString g_sLangTxt_Native_ProjIdent;
//作为Word标题
extern CString g_sLangID_Native_AsWordTitle;
extern CString g_sLangTxt_Native_AsWordTitle;
//修改项目名称
extern CString g_sLangID_Native_ModProjName;
extern CString g_sLangTxt_Native_ModProjName;
//向导
extern CString g_sLangID_Native_Wizard;
extern CString g_sLangTxt_Native_Wizard;
//上一步
extern CString g_sLangID_Native_PrevStep;
extern CString g_sLangTxt_Native_PrevStep;
/*_T("网页文件(%s)不存在.")*/
extern CString g_sLangID_Native_WebPageNotExst;
extern CString g_sLangTxt_Native_WebPageNotExst;
/*_T("未选择IED")*/
extern CString g_sLangID_Native_IEDNotSel;
extern CString g_sLangTxt_Native_IEDNotSel;


//Controls
//设备类型
extern CString g_sLangID_Native_DevType;
extern CString g_sLangTxt_Native_DevType;
//规约引擎
extern CString g_sLangID_Native_ProtoEngin;
extern CString g_sLangTxt_Native_ProtoEngin;
//装置IP
extern CString g_sLangID_Native_DevIP;
extern CString g_sLangTxt_Native_DevIP;
//装置端口
extern CString g_sLangID_Native_DevPort;
extern CString g_sLangTxt_Native_DevPort;
//规约模板
extern CString g_sLangID_Native_ProtoTemp;
extern CString g_sLangTxt_Native_ProtoTemp;
//从SCD文件选择
extern CString g_sLangID_Native_SelSCDFile;
extern CString g_sLangTxt_Native_SelSCDFile;
//高级配置
extern CString g_sLangID_Native_AdvConfig;
extern CString g_sLangTxt_Native_AdvConfig;
//时间定值单位为ms
extern CString g_sLangID_Native_TimeSetUnit;
extern CString g_sLangTxt_Native_TimeSetUnit;
//添加装置复归态
extern CString g_sLangID_Native_AddDevReset;
extern CString g_sLangTxt_Native_AddDevReset;
/*"新分类"*/
extern CString g_sLangID_Native_NewCat;
extern CString g_sLangTxt_Native_NewCat;
/*"存在相同名称的项目"*/
extern CString g_sLangID_Native_ProjSameExists;
extern CString g_sLangTxt_Native_ProjSameExists;
/*"存在相同ID的项目"*/
extern CString g_sLangID_Native_ProjSameIDExists;
extern CString g_sLangTxt_Native_ProjSameIDExists;
//测试次数 >1时，自动更新到项目名称
extern CString g_sLangID_Native_TestCntGt1AutoUpdtProjName;
extern CString g_sLangTxt_Native_TestCntGt1AutoUpdtProjName;
//名称作为word标题
extern CString g_sLangID_Native_NameWordTitle;
extern CString g_sLangTxt_Native_NameWordTitle;
/*_T("请在此处输入接线提示信息……")*/
extern CString g_sLangID_Native_PlsEntWiringInstruc;
extern CString g_sLangTxt_Native_PlsEntWiringInstruc;
/*_T("未找到对应的预置提示信息，请在此处输入接线提示信息……")*/
extern CString g_sLangID_Native_NoMatchPresetInstrucPlsEntWiring;
extern CString g_sLangTxt_Native_NoMatchPresetInstrucPlsEntWiring;
//选择需要的接线提示信息
extern CString g_sLangID_Native_SelDesiredWiringInstruc;
extern CString g_sLangTxt_Native_SelDesiredWiringInstruc;
/*"确实要删除 ["*/
extern CString g_sLangID_Native_DeletestrMsg;
extern CString g_sLangTxt_Native_DeletestrMsg;
/*"] 吗？"*/
extern CString g_sLangID_Native_DeletestrMsg2;
extern CString g_sLangTxt_Native_DeletestrMsg2;
/*_T(" ] 吗？删除后无法恢复！")*/
extern CString g_sLangID_Native_DeletestrMsg3;
extern CString g_sLangTxt_Native_DeletestrMsg3;
/*"测试后恢复"*/
extern CString g_sLangID_Native_RestoreAfterTest;
extern CString g_sLangTxt_Native_RestoreAfterTest;
/*"测试前准备"*/
extern CString g_sLangID_Native_PrepBeforeTest;
extern CString g_sLangTxt_Native_PrepBeforeTest;
/*tr("新建项目分类")*/
extern CString g_sLangID_Native_CreateProjCat;
extern CString g_sLangTxt_Native_CreateProjCat;
/*tr("新建测试前准备")*/
extern CString g_sLangID_Native_CreatePrepBeforeTest;
extern CString g_sLangTxt_Native_CreatePrepBeforeTest;
/*tr("新建测试后恢复")*/
extern CString g_sLangID_Native_CreateReplyAfterTest;
extern CString g_sLangTxt_Native_CreateReplyAfterTest;
/*tr("删除当前选中项目")*/
extern CString g_sLangID_Native_DeleteCurrSelectedProj;
extern CString g_sLangTxt_Native_DeleteCurrSelectedProj;
/*tr("编辑当前选中项目")*/
extern CString g_sLangID_Native_EditCurrSelectedProj;
extern CString g_sLangTxt_Native_EditCurrSelectedProj;
/*tr("保存当前选中项目")*/
extern CString g_sLangID_Native_SaveCurrSelectedProj;
extern CString g_sLangTxt_Native_SaveCurrSelectedProj;
/*tr("添加功能向导")*/
extern CString g_sLangID_Native_AddFuncWizard;
extern CString g_sLangTxt_Native_AddFuncWizard;
/*tr("从当前选中项目开始测试")*/
extern CString g_sLangID_Native_StartTestFromSelProj;
extern CString g_sLangTxt_Native_StartTestFromSelProj;
/*tr("测试当前选中项目")*/
extern CString g_sLangID_Native_TestCurrSelProj;
extern CString g_sLangTxt_Native_TestCurrSelProj;
/*"新建通讯命令"*/
extern CString g_sLangID_Native_CreateCommCommand;
extern CString g_sLangTxt_Native_CreateCommCommand;
/*_T("确认删除项目")*/
extern CString g_sLangID_Native_ConfirmDelProj;
extern CString g_sLangTxt_Native_ConfirmDelProj;
/*_T("重命名当前选中项目")*/
extern CString g_sLangID_Native_RenameCurrSelProj;
extern CString g_sLangTxt_Native_RenameCurrSelProj;
/*_T("删除接线提示")*/
extern CString g_sLangID_Native_DeleteWiringInstr;
extern CString g_sLangTxt_Native_DeleteWiringInstr;
/*_T("添加测试前、后通讯组合")*/
extern CString g_sLangID_Native_AddPrePostCommCombo;
extern CString g_sLangTxt_Native_AddPrePostCommCombo;
/*_T("新建配置项目")*/
extern CString g_sLangID_Native_CreateConfigProj;
extern CString g_sLangTxt_Native_CreateConfigProj;
/*_T("硬件通道映射")*/
extern CString g_sLangID_Native_HWChanMapping;
extern CString g_sLangTxt_Native_HWChanMapping;
/*_T("IEC61850配置")*/
extern CString g_sLangID_Native_IEC61850Config;
extern CString g_sLangTxt_Native_IEC61850Config;
/*_T("确认删除接线提示")*/
extern CString g_sLangID_Native_ConfirmDelWiringInstr;
extern CString g_sLangTxt_Native_ConfirmDelWiringInstr;
/*_T("保存项目指令，创建通讯命令失败！")*/
extern CString g_sLangID_Native_SaveProjInstrFailCommCmd;
extern CString g_sLangTxt_Native_SaveProjInstrFailCommCmd;
/*_T("当前选中的项目，不存在！请重新选择项目后进行测试")*/
extern CString g_sLangID_Native_SelProjNotExistRetryTest;
extern CString g_sLangTxt_Native_SelProjNotExistRetryTest;
/*_T("该功能暂不支持……")*/
extern CString g_sLangID_Native_NotSupportFeature;
extern CString g_sLangTxt_Native_NotSupportFeature;
//添加至:子项
extern CString g_sLangID_Native_AddSubitem;
extern CString g_sLangTxt_Native_AddSubitem;
//添加至:项之前
extern CString g_sLangID_Native_AddBeforeItem;
extern CString g_sLangTxt_Native_AddBeforeItem;
//添加至:项之后
extern CString g_sLangID_Native_AddAfterItem;
extern CString g_sLangTxt_Native_AddAfterItem;
/*_T("项目结果")*/
extern CString g_sLangID_Native_ProjResults;
extern CString g_sLangTxt_Native_ProjResults;
/*_T("全部报告数据")*/
extern CString g_sLangID_Native_AllRptData;
extern CString g_sLangTxt_Native_AllRptData;
/*_T("报告数据-数据集")*/
extern CString g_sLangID_Native_RptDataDataset;
extern CString g_sLangTxt_Native_RptDataDataset;
/*_T("测试结论")*/
extern CString g_sLangID_Native_TestConcl;
extern CString g_sLangTxt_Native_TestConcl;
/*_T("查看报告")*/
extern CString g_sLangID_Native_ViewRpt;
extern CString g_sLangTxt_Native_ViewRpt;
/*_T("次测试")*/
extern CString g_sLangID_Native_TestRun;
extern CString g_sLangTxt_Native_TestRun;
/*_T("次计算结果")*/
extern CString g_sLangID_Native_CalcResult;
extern CString g_sLangTxt_Native_CalcResult;
//异常电流
extern CString g_sLangID_Native_AbnCurr;
extern CString g_sLangTxt_Native_AbnCurr;
extern CString g_sLangID_Adjustment_Time;
extern CString g_sLangTxt_Adjustment_Time;//整定动作时间

extern CString g_sLangID_Native_GroundDisTimeI;
extern CString g_sLangTxt_Native_GroundDisTimeI;
extern CString g_sLangID_Native_GroundDisTimeII;
extern CString g_sLangTxt_Native_GroundDisTimeII;
extern CString g_sLangID_Native_GroundDisTimeIII;
extern CString g_sLangTxt_Native_GroundDisTimeIII;
extern CString g_sLangID_Native_GroundDisTimeIV;
extern CString g_sLangTxt_Native_GroundDisTimeIV;
extern CString g_sLangID_Native_GroundDisTimeV;
extern CString g_sLangTxt_Native_GroundDisTimeV;//接地距离时间（1-5段）
extern CString g_sLangID_Native_harmonicOrder;
extern CString g_sLangTxt_Native_harmonicOrder;  // 谐波次数
extern CString g_sLangID_Native_harmRepresent;
extern CString g_sLangTxt_Native_harmRepresent;// 谐波表示方式
//标识
extern CString g_sLangID_Native_Identifier;
extern CString g_sLangTxt_Native_Identifier;

//开入量设置
extern CString g_sLangID_Native_InputSet;
extern CString g_sLangTxt_Native_InputSet;
//异常数据
extern CString g_sLangID_Native_AbnData;
extern CString g_sLangTxt_Native_AbnData;
//开入逻辑
extern CString g_sLangID_Native_InLogic;
extern CString g_sLangTxt_Native_InLogic;
/*QObject::tr("速断电流")*/
extern CString g_sLangID_Native_InstCurr;
extern CString g_sLangTxt_Native_InstCurr;
//异常点设置
extern CString g_sLangID_Native_AbnPointSet;
extern CString g_sLangTxt_Native_AbnPointSet;
//是否直流
extern CString g_sLangID_Native_IsDC;
extern CString g_sLangTxt_Native_IsDC;
//抖动测试
extern CString g_sLangID_Native_JitterTest;
extern CString g_sLangTxt_Native_JitterTest;
//抖动值  
extern CString g_sLangID_Native_JitterVal;
extern CString g_sLangTxt_Native_JitterVal;
//异常电压
extern CString g_sLangID_Native_AbnVolt;
extern CString g_sLangTxt_Native_AbnVolt;
//跳变值
extern CString g_sLangID_Native_JumpVal;
extern CString g_sLangTxt_Native_JumpVal;
extern CString g_sLangID_Native_actionSetting;
extern CString g_sLangTxt_Native_actionSetting; // 动作定值
//最大故障时间
extern CString g_sLangID_Native_MaxTimeMalf;
extern CString g_sLangTxt_Native_MaxTimeMalf;
//修改全部通道值
extern CString g_sLangID_Native_ModAllChan;
extern CString g_sLangTxt_Native_ModAllChan;
//报文选择
extern CString g_sLangID_Native_MsgSel;
extern CString g_sLangTxt_Native_MsgSel;
//B码逻辑
extern CString g_sLangID_Native_BCodeLogic;
extern CString g_sLangTxt_Native_BCodeLogic;
//报文设置
extern CString g_sLangID_Native_MsgSet;
extern CString g_sLangTxt_Native_MsgSet;
//倍数
extern CString g_sLangID_Native_Multiple;
extern CString g_sLangTxt_Native_Multiple;
/*tr("故障前电压")*/
extern CString g_sLangID_Native_PreFaultVolt;
extern CString g_sLangTxt_Native_PreFaultVolt;
/*tr("故障前电流")*/
extern CString g_sLangID_Native_PreFaultCurr;
extern CString g_sLangTxt_Native_PreFaultCurr;
extern CString g_sLangID_Native_PhSetActValue;
extern CString g_sLangTxt_Native_PhSetActValue;//相位整定动作值
/*tr("边界角1")*/
extern CString g_sLangID_Native_BoundAngle1;
extern CString g_sLangTxt_Native_BoundAngle1;
/*tr("边界角2")*/
extern CString g_sLangID_Native_BoundAngle2;
extern CString g_sLangTxt_Native_BoundAngle2;
//第
extern CString g_sLangID_Native_Number;
extern CString g_sLangTxt_Native_Number;
//通道选择
extern CString g_sLangID_Native_ChannelSelect;
extern CString g_sLangTxt_Native_ChannelSelect;
extern CString g_sLangID_Native_PhaseDisSetI;
extern CString g_sLangTxt_Native_PhaseDisSetI;
extern CString g_sLangID_Native_PhaseDisSetII;
extern CString g_sLangTxt_Native_PhaseDisSetII;
extern CString g_sLangID_Native_PhaseDisSetIII;
extern CString g_sLangTxt_Native_PhaseDisSetIII;
extern CString g_sLangID_Native_PhaseDisSetIV;
extern CString g_sLangTxt_Native_PhaseDisSetIV;
extern CString g_sLangID_Native_PhaseDisSetV;
extern CString g_sLangTxt_Native_PhaseDisSetV;//相间距离定值（1-5段）
extern CString g_sLangID_Native_PhaseDisTimeI;
extern CString g_sLangTxt_Native_PhaseDisTimeI;
extern CString g_sLangID_Native_PhaseDisTimeII;
extern CString g_sLangTxt_Native_PhaseDisTimeII;
extern CString g_sLangID_Native_PhaseDisTimeIII;
extern CString g_sLangTxt_Native_PhaseDisTimeIII;
extern CString g_sLangID_Native_PhaseDisTimeIV;
extern CString g_sLangTxt_Native_PhaseDisTimeIV;
extern CString g_sLangID_Native_PhaseDisTimeV;
extern CString g_sLangTxt_Native_PhaseDisTimeV;//相间距离时间（1-5段）

// 接地距离 电阻定值（1-5段）
extern CString g_sLangID_Native_GroundResetI;
extern CString g_sLangTxt_Native_GroundResetI;
extern CString g_sLangID_Native_GroundResetII;
extern CString g_sLangTxt_Native_GroundResetII;
extern CString g_sLangID_Native_GroundResetIII;
extern CString g_sLangTxt_Native_GroundResetIII;
extern CString g_sLangID_Native_GroundResetIV;
extern CString g_sLangTxt_Native_GroundResetIV;
extern CString g_sLangID_Native_GroundResetV;
extern CString g_sLangTxt_Native_GroundResetV; 

// 接地距离电抗 （1-5段）
extern CString g_sLangID_Native_GroundXesetI;
extern CString g_sLangTxt_Native_GroundXesetI;
extern CString g_sLangID_Native_GroundXesetII;
extern CString g_sLangTxt_Native_GroundXesetII;
extern CString g_sLangID_Native_GroundXesetIII;
extern CString g_sLangTxt_Native_GroundXesetIII;
extern CString g_sLangID_Native_GroundXesetIV;
extern CString g_sLangTxt_Native_GroundXesetIV;
extern CString g_sLangID_Native_GroundXesetV;
extern CString g_sLangTxt_Native_GroundXesetV;

// 相间距离 电阻定值（1-5段）
extern CString g_sLangID_Native_PhaseResetI;
extern CString g_sLangTxt_Native_PhaseResetI;
extern CString g_sLangID_Native_PhaseResetII;
extern CString g_sLangTxt_Native_PhaseResetII;
extern CString g_sLangID_Native_PhaseResetIII;
extern CString g_sLangTxt_Native_PhaseResetIII;
extern CString g_sLangID_Native_PhaseResetIV;
extern CString g_sLangTxt_Native_PhaseResetIV;
extern CString g_sLangID_Native_PhaseResetV;
extern CString g_sLangTxt_Native_PhaseResetV; 

// 相间距离电抗 （1-5段）
extern CString g_sLangID_Native_PhaseXesetI;
extern CString g_sLangTxt_Native_PhaseXesetI;
extern CString g_sLangID_Native_PhaseXesetII;
extern CString g_sLangTxt_Native_PhaseXesetII;
extern CString g_sLangID_Native_PhaseXesetIII;
extern CString g_sLangTxt_Native_PhaseXesetIII;
extern CString g_sLangID_Native_PhaseXesetIV;
extern CString g_sLangTxt_Native_PhaseXesetIV;
extern CString g_sLangID_Native_PhaseXesetV;
extern CString g_sLangTxt_Native_PhaseXesetV;

//确认
extern CString g_sLangID_Native_Confm;
extern CString g_sLangTxt_Native_Confm;
//故障性质
extern CString g_sLangID_Native_NatureMalf;
extern CString g_sLangTxt_Native_NatureMalf;
//输出时间
extern CString g_sLangID_Native_OutTime;
extern CString g_sLangTxt_Native_OutTime;
extern CString g_sLangID_Native_CurSetActValue;
extern CString g_sLangTxt_Native_CurSetActValue;//电流整定动作值
//开出量保持时间
extern CString g_sLangID_Native_OutHoldTime;
extern CString g_sLangTxt_Native_OutHoldTime;
//网络标识   0x
extern CString g_sLangID_Native_NetID;
extern CString g_sLangTxt_Native_NetID;
extern CString g_sLangID_Native_networkId;
extern CString g_sLangTxt_Native_networkId; //网络标识
//延时偏差
extern CString g_sLangID_Native_DelayDev;
extern CString g_sLangTxt_Native_DelayDev;
//常态时间
extern CString g_sLangID_Native_NormTime;
extern CString g_sLangTxt_Native_NormTime;
extern CString g_sLangID_Native_oneToMany;
extern CString g_sLangTxt_Native_oneToMany; //一个控制块对应多个线条
//延时时间
extern CString g_sLangID_Native_DelayTime;
extern CString g_sLangTxt_Native_DelayTime;
//动作时间定值
extern CString g_sLangID_Native_OpTimeSet;
extern CString g_sLangTxt_Native_OpTimeSet;
//原始报文设置
extern CString g_sLangID_Native_OrigMsgSet;
extern CString g_sLangTxt_Native_OrigMsgSet;
//延时变化
extern CString g_sLangID_Native_DelayVar;
extern CString g_sLangTxt_Native_DelayVar;
//开出保持时间
extern CString g_sLangID_Native_OutputHoldTimeS;
extern CString g_sLangTxt_Native_OutputHoldTimeS;
extern CString g_sLangID_Native_outputTimeLimit;
extern CString g_sLangTxt_Native_outputTimeLimit;  // 输出限时(s)
/*"过负荷电流通道"*/
extern CString g_sLangID_Native_OverloadCurrChannel;
extern CString g_sLangTxt_Native_OverloadCurrChannel;
extern CString g_sLangID_Native_delegate;
extern CString g_sLangTxt_Native_delegate; //委托
extern CString g_sLangID_Native_phaseDifference;
extern CString g_sLangTxt_Native_phaseDifference; //相别
extern CString g_sLangID_Native_PreFaultTime;
extern CString g_sLangTxt_Native_PreFaultTime;  // 故障前时间(s)
//目的MAC
extern CString g_sLangID_Native_DestMAC;
extern CString g_sLangTxt_Native_DestMAC;
/*_T("定值整定方式")*/
extern CString g_sLangID_Native_DevSetMethod;
extern CString g_sLangTxt_Native_DevSetMethod;
//偏差时间
extern CString g_sLangID_Native_DevTime;
extern CString g_sLangTxt_Native_DevTime;
//偏差值
extern CString g_sLangID_Native_DevVal;
extern CString g_sLangTxt_Native_DevVal;
/*"差动速断"*/
extern CString g_sLangID_Native_DiffSpdBrk;
extern CString g_sLangTxt_Native_DiffSpdBrk;
//保护动作后持续时间
extern CString g_sLangID_Native_DurProtTrip;
extern CString g_sLangTxt_Native_DurProtTrip;

/*tr("故障时间(S)")*/
extern CString g_sLangID_Native_PreFautTime;
extern CString g_sLangTxt_Native_PreFautTime;
/*"项目名称"*/
extern CString g_sLangID_Native_ProjName;
extern CString g_sLangTxt_Native_ProjName;
//品质异常
extern CString g_sLangID_Native_QltyExcp;
extern CString g_sLangTxt_Native_QltyExcp;
extern CString g_sLangID_Native_quote;
extern CString g_sLangTxt_Native_quote; //引用
extern CString g_sLangID_Native_RatioBrakeCoefficient;
extern CString g_sLangTxt_Native_RatioBrakeCoefficient;  // 比率制动系数
extern CString g_sLangID_Native_receive;
extern CString g_sLangTxt_Native_receive; //接收
//返回时间
extern CString g_sLangID_Native_ReturnTime;
extern CString g_sLangTxt_Native_ReturnTime;
//返回值
extern CString g_sLangID_Native_ReturnValue;
extern CString g_sLangTxt_Native_ReturnValue;
//采样延时
extern CString g_sLangID_Native_SampDelay;
extern CString g_sLangTxt_Native_SampDelay;
//采样率
extern CString g_sLangID_Native_SamplingFrequency;
extern CString g_sLangTxt_Native_SamplingFrequency;
extern CString g_sLangID_Native_saveFailed;
extern CString g_sLangTxt_Native_saveFailed; //保存失败！\n
//序号偏差
extern CString g_sLangID_Native_SeqDev;
extern CString g_sLangTxt_Native_SeqDev;
extern CString g_sLangID_Native_SetActVolt;
extern CString g_sLangTxt_Native_SetActVolt;
//整定动作电流
extern CString g_sLangID_Native_SetPickCurr;
extern CString g_sLangTxt_Native_SetPickCurr;
//变位次数
extern CString g_sLangID_Native_ShiftCount;
extern CString g_sLangTxt_Native_ShiftCount;
//短路电压
extern CString g_sLangID_Native_ShortCircuitV;
extern CString g_sLangTxt_Native_ShortCircuitV;
//短路阻抗角
extern CString g_sLangID_Native_ShortZImpAng;
extern CString g_sLangTxt_Native_ShortZImpAng;
/*短路阻抗*/
extern CString g_sLangID_Native_ShortZImp;
extern CString g_sLangTxt_Native_ShortZImp;
extern CString g_sLangID_Native_smvReceive;
extern CString g_sLangTxt_Native_smvReceive; //SMV 接收
//发送周波数
extern CString g_sLangID_Native_SndFreq;
extern CString g_sLangTxt_Native_SndFreq;
//每秒发送周波数
extern CString g_sLangID_Native_SndFreqPS;
extern CString g_sLangTxt_Native_SndFreqPS;
//发送时间(s)
extern CString g_sLangID_Native_SndTimeS;
extern CString g_sLangTxt_Native_SndTimeS;
//源MAC
extern CString g_sLangID_Native_SrcMAC;
extern CString g_sLangTxt_Native_SrcMAC;
//状态%d
extern CString g_sLangID_Native_StateD;
extern CString g_sLangTxt_Native_StateD;
extern CString g_sLangID_Native_subscriptionDescription;
extern CString g_sLangTxt_Native_subscriptionDescription; //订阅描述
extern CString g_sLangID_Native_subscriptionIndex;
extern CString g_sLangTxt_Native_subscriptionIndex; //订阅索引
extern CString g_sLangID_Native_subscriptionReference;
extern CString g_sLangTxt_Native_subscriptionReference; //订阅引用
extern CString g_sLangID_Native_superimpose_ornot;
extern CString g_sLangTxt_Native_superimpose_ornot;  // 是否叠加非周期分量:
//SV原始报文
extern CString g_sLangID_Native_SVOrigMsg;
extern CString g_sLangTxt_Native_SVOrigMsg;
//开关量
extern CString g_sLangID_Native_SwitchVal;
extern CString g_sLangTxt_Native_SwitchVal;
extern CString g_sLangID_Native_test_process;
extern CString g_sLangTxt_Native_test_process;  // 试验过程:
//测试精度
extern CString g_sLangID_Native_TestPrecision;
extern CString g_sLangTxt_Native_TestPrecision;
//变压器接线形式
extern CString g_sLangID_Native_TransConnForm;
extern CString g_sLangTxt_Native_TransConnForm;
//是否转换性故障
extern CString g_sLangID_Native_TransientFault;
extern CString g_sLangTxt_Native_TransientFault;
//触发后保持时间
extern CString g_sLangID_Native_TrigHoldTime;
extern CString g_sLangTxt_Native_TrigHoldTime;
//触发方式
extern CString g_sLangID_Native_TrigMode;
extern CString g_sLangTxt_Native_TrigMode;
//有效[bit0-1]
extern CString g_sLangID_Native_ValidBit;
extern CString g_sLangTxt_Native_ValidBit;
extern CString g_sLangID_Native_VolSetActValue;
extern CString g_sLangTxt_Native_VolSetActValue;//电压整定动作值
extern CString g_sLangID_Native_vTerminalConnectDia;
extern CString g_sLangTxt_Native_vTerminalConnectDia; //虚端子连接图
extern CString g_sLangID_Native_YNInputStop;
extern CString g_sLangTxt_Native_YNInputStop;  // 是否开入停止
extern CString g_sLangID_Out1_Situation; 
extern CString g_sLangTxt_Out1_Situation;//开出1状态
extern CString g_sLangID_Out2_Situation;
extern CString g_sLangTxt_Out2_Situation;//开出2状态
extern CString g_sLangID_Out3_Situation;
extern CString g_sLangTxt_Out3_Situation;//开出3状态
extern CString g_sLangID_without;
extern CString g_sLangTxt_without;//无
extern CString g_sLangID_Native_error;
extern CString g_sLangTxt_Native_error; //错误
//电压滑差
extern CString g_sLangID_Native_VoltSlip;
extern CString g_sLangTxt_Native_VoltSlip;
//错序测试
extern CString g_sLangID_Native_ErrSeqTest;
extern CString g_sLangTxt_Native_ErrSeqTest;
//故障
extern CString g_sLangID_Native_Fault;
extern CString g_sLangTxt_Native_Fault;
//故障通道
extern CString g_sLangID_Native_FaultChnl;
extern CString g_sLangTxt_Native_FaultChnl;
/*故障电流*/
extern CString g_sLangID_Native_FaultCurrValue;
extern CString g_sLangTxt_Native_FaultCurrValue;
//故障触发方式
extern CString g_sLangID_Native_FaultTrigMethod;
extern CString g_sLangTxt_Native_FaultTrigMethod;
//故障电压定义
extern CString g_sLangID_Native_FaultVoltDef;
extern CString g_sLangTxt_Native_FaultVoltDef;
//文件名称
extern CString g_sLangID_Native_FileName;
extern CString g_sLangTxt_Native_FileName;
//翻转时刻
extern CString g_sLangID_Native_FlipMoment;
extern CString g_sLangTxt_Native_FlipMoment;
//丢帧测试
extern CString g_sLangID_Native_FrameDrop;
extern CString g_sLangTxt_Native_FrameDrop;
//飞点测试
extern CString g_sLangID_Native_FlyDot;
extern CString g_sLangTxt_Native_FlyDot;
extern CString g_sLangID_Native_FreqSetActValue;
extern CString g_sLangTxt_Native_FreqSetActValue;//频率整定动作值
extern CString g_sLangID_Native_fundamentalFreq;
extern CString g_sLangTxt_Native_fundamentalFreq;  // 基波频率
extern CString g_sLangID_Native_fundamentalAmp;
extern CString g_sLangTxt_Native_fundamentalAmp;  // 基波幅值
extern CString g_sLangID_Native_fundamentalPhase;
extern CString g_sLangTxt_Native_fundamentalPhase;  // 基波相位
extern CString g_sLangID_Native_GOOSEOrigMsg;
extern CString g_sLangTxt_Native_GOOSEOrigMsg; //GOOSE原始报文
extern CString g_sLangID_Native_gooseReceive;
extern CString g_sLangTxt_Native_gooseReceive; //GOOSE 接收
//GPS触发时刻（时）
extern CString g_sLangID_Native_GPSTriggerHour;
extern CString g_sLangTxt_Native_GPSTriggerHour;
//GPS触发时刻（分）
extern CString g_sLangID_Native_GPSTriggerMinute;
extern CString g_sLangTxt_Native_GPSTriggerMinute;
//GPS触发时刻（秒）
extern CString g_sLangID_Native_GPSTriggerSecond;
extern CString g_sLangTxt_Native_GPSTriggerSecond;
//递变时间分度(ms)
extern CString g_sLangID_Native_GradualTimeScale;
extern CString g_sLangTxt_Native_GradualTimeScale;
extern CString g_sLangID_Native_GroundDisSetI;
extern CString g_sLangTxt_Native_GroundDisSetI;
extern CString g_sLangID_Native_GroundDisSetII;
extern CString g_sLangTxt_Native_GroundDisSetII;
extern CString g_sLangID_Native_GroundDisSetIII;
extern CString g_sLangTxt_Native_GroundDisSetIII;
extern CString g_sLangID_Native_GroundDisSetIV;
extern CString g_sLangTxt_Native_GroundDisSetIV;
// 短路电压(V)：
extern CString g_sLangID_Native_ShortCircuitVs;
extern CString g_sLangTxt_Native_ShortCircuitVs;

//电压变化终值
extern CString g_sLangID_Native_FinalVoltChange;
extern CString g_sLangTxt_Native_FinalVoltChange;
extern CString g_sLangID_Allow_FreqDifference;
extern CString g_sLangTxt_Allow_FreqDifference;//允许频差
extern CString g_sLangID_LeadingAngle;
extern CString g_sLangTxt_LeadingAngle;//导前角

extern CString g_sLangID_Vol_ReguPeriod;
extern CString g_sLangTxt_Vol_ReguPeriod;//调压周期
extern CString g_sLangID_Freq_ReguPeriod;
extern CString g_sLangTxt_Freq_ReguPeriod;//调频周期
extern CString g_sLangID_LeadingTime;
extern CString g_sLangTxt_LeadingTime;//导前时间
extern CString g_sLangID_Allow_VolDifference;
extern CString g_sLangTxt_Allow_VolDifference;//允许压差

extern CString g_sLangID_System_Rated_Voltage;
extern CString g_sLangTxt_System_Rated_Voltage;//系统侧额定电压
extern CString g_sLangID_System_Rated_Frequency;
extern CString g_sLangTxt_System_Rated_Frequency;//系统侧额定频率
extern CString g_sLangID_Grid_Rated_Voltage;
extern CString g_sLangTxt_Grid_Rated_Voltage;//待并侧额定电压

extern CString g_sLangID_Freq_BoundValue;
extern CString g_sLangTxt_Freq_BoundValue;//频率边界值
extern CString g_sLangID_FreqDif;
extern CString g_sLangTxt_FreqDif;//频差

extern CString g_sLangID_Grid_FreqHZ;
extern CString g_sLangTxt_Grid_FreqHZ;//待并侧频率（HZ）

//电压变化始值
extern CString g_sLangID_Native_InitVoltChange;
extern CString g_sLangTxt_Native_InitVoltChange;
/*_T("低压闭锁值")*/
extern CString g_sLangID_Native_LowVLockVal;
extern CString g_sLangTxt_Native_LowVLockVal;
extern CString g_sLangID_Native_maxSyncTime;
extern CString g_sLangTxt_Native_maxSyncTime;   // 最大同步时间:
//低压减载动作值
extern CString g_sLangID_Native_LowVoltUnderloadTripSet;
extern CString g_sLangTxt_Native_LowVoltUnderloadTripSet;
//电压变化步长
extern CString g_sLangID_Native_VoltChangeStep;
extern CString g_sLangTxt_Native_VoltChangeStep;
extern CString g_sLangID_Out4_Mode;
extern CString g_sLangTxt_Out4_Mode;//开出4输出方式
extern CString g_sLangID_Vol_BoundValue;
extern CString g_sLangTxt_Vol_BoundValue;//电压边界值
/*QString::tr("电压滑差动作值")*/	
extern CString g_sLangID_Native_VoltSlipAct;
extern CString g_sLangTxt_Native_VoltSlipAct;
/*_T("闭锁电压定义")*/	
extern CString g_sLangID_Native_LockVoltDef;
extern CString g_sLangTxt_Native_LockVoltDef;
extern CString g_sLangID_VolDif;
extern CString g_sLangTxt_VolDif;//压差

/*_T("低压变化率闭锁值")*/
extern CString g_sLangID_Native_LowVRateLock;
extern CString g_sLangTxt_Native_LowVRateLock;

/*QString::tr("低压减载动作值")*/
extern CString g_sLangID_Native_LVLRActionVal;
extern CString g_sLangTxt_Native_LVLRActionVal;

//故障性质:
extern CString g_sLangID_Native_FaultProp;
extern CString g_sLangTxt_Native_FaultProp;
/*tr("测试绕组之间角差(钟点数)")*/
extern CString g_sLangID_Native_AngleDiffClockHrsTestWindings;
extern CString g_sLangTxt_Native_AngleDiffClockHrsTestWindings;
//制  动  电  流
extern CString g_sLangID_Native_ControlCurrent;
extern CString g_sLangTxt_Native_ControlCurrent;

/*_T("启动段斜率")*/
extern CString g_sLangID_Native_StartSegSlope;
extern CString g_sLangTxt_Native_StartSegSlope;
/*_T("基波比率制动特性斜率1")*/
extern CString g_sLangID_Native_FundRatioBrkSlope1;
extern CString g_sLangTxt_Native_FundRatioBrkSlope1;
/*_T("基波比率制动特性斜率2")*/
extern CString g_sLangID_Native_FundRatioBrkSlope2;
extern CString g_sLangTxt_Native_FundRatioBrkSlope2;
/*_T("基波比率制动特性斜率3")*/
extern CString g_sLangID_Native_FundRatioBrkSlope3;
extern CString g_sLangTxt_Native_FundRatioBrkSlope3;
/*_T("二次谐波制动系数")*/
extern CString g_sLangID_Native_SecHarBrkCoef;
extern CString g_sLangTxt_Native_SecHarBrkCoef;
/*_T("三次谐波制动系数")*/
extern CString g_sLangID_Native_ThiHarBrkCoef;
extern CString g_sLangTxt_Native_ThiHarBrkCoef;
/*_T("五次谐波制动系数")*/
extern CString g_sLangID_Native_FivHarBrkCoef;
extern CString g_sLangTxt_Native_FivHarBrkCoef;
//搜索方法
extern CString g_sLangID_Native_SearchMeth;
extern CString g_sLangTxt_Native_SearchMeth;

/*tr("高压侧额定电压(kV)")*/
extern CString g_sLangID_Native_HighVoltSideRatedVolt;
extern CString g_sLangTxt_Native_HighVoltSideRatedVolt;
/*tr("中压侧额定电压(kV)")*/
extern CString g_sLangID_Native_MedVoltSideRatedVolt;
extern CString g_sLangTxt_Native_MedVoltSideRatedVolt;

/*tr("中压侧绕组接线型式")*/
extern CString g_sLangID_Native_MedVoltWindingConnType;
extern CString g_sLangTxt_Native_MedVoltWindingConnType;
/*tr("低压侧额定电压(kV)")*/
extern CString g_sLangID_Native_LowVoltSideRatedVolt;
extern CString g_sLangTxt_Native_LowVoltSideRatedVolt;
/*"高压侧CT一次值(A)"*/
extern CString g_sLangID_Native_HVSideCTPrimVal;
extern CString g_sLangTxt_Native_HVSideCTPrimVal;
/*"高压侧CT二次值(A)"*/
extern CString g_sLangID_Native_HVSide2CTPrimVal;
extern CString g_sLangTxt_Native_HVSide2CTPrimVal;
/*"中压侧CT一次值(A)"*/
extern CString g_sLangID_Native_MVSideCTPrimVal;
extern CString g_sLangTxt_Native_MVSideCTPrimVal;
/*"高压侧CT二次值(A)"*/
extern CString g_sLangID_Native_MVSide2CTPrimVal;
extern CString g_sLangTxt_Native_MVSide2CTPrimVal;
/*"低压侧CT一次值(A)"*/
extern CString g_sLangID_Native_LVSideCTPrimVal;
extern CString g_sLangTxt_Native_LVSideCTPrimVal;
/*"低压侧CT二次值(A)"*/
extern CString g_sLangID_Native_LVSide2CTPrimVal;
extern CString g_sLangTxt_Native_LVSide2CTPrimVal;
/*_T("基准电流选择")*/
extern CString g_sLangID_Native_RefCurrentSel;
extern CString g_sLangTxt_Native_RefCurrentSel;
//比例制动系数  
extern CString g_sLangID_Native_ProportionalBrakingFactor;
extern CString g_sLangTxt_Native_ProportionalBrakingFactor;
/*tr("变压器额定容量(MVA)")*/
extern CString g_sLangID_Native_TransfRatedCapacity;
extern CString g_sLangTxt_Native_TransfRatedCapacity;
extern CString g_sLangID_interlock_vol;
extern CString g_sLangTxt_interlock_vol;//闭锁电压
extern CString g_sLangID_interlock_cur;
extern CString g_sLangTxt_interlock_cur;//闭锁电流
extern CString g_sLangID_lowfreqloadre_ActTime;
extern CString g_sLangTxt_lowfreqloadre_ActTime;//低周减载动作时间

//电压变化量
extern CString g_sLangID_Native_VoltChangeAmt;
extern CString g_sLangTxt_Native_VoltChangeAmt;
extern CString g_sLangID_Native_sliptripValue;
extern CString g_sLangTxt_Native_sliptripValue;//滑差闭锁值
//加速信号接点
extern CString g_sLangID_Native_AccelSignalCont;
extern CString g_sLangTxt_Native_AccelSignalCont;
//减速信号接点
extern CString g_sLangID_Native_DecelSignalCont;
extern CString g_sLangTxt_Native_DecelSignalCont;
//振荡前时间
extern CString g_sLangID_Native_PreOscTime;
extern CString g_sLangTxt_Native_PreOscTime;
//系统侧阻抗
extern CString g_sLangID_Native_SysImp;
extern CString g_sLangTxt_Native_SysImp;
//变压器阻抗
extern CString g_sLangID_Native_TransImp;
extern CString g_sLangTxt_Native_TransImp;

/*_T("振荡次数")*/
extern CString g_sLangID_Native_OscilCount;
extern CString g_sLangTxt_Native_OscilCount;
//角度定义
extern CString g_sLangID_Native_AngDef;
extern CString g_sLangTxt_Native_AngDef;
//接线方式
extern CString g_sLangID_Native_ConnMethod;
extern CString g_sLangTxt_Native_ConnMethod;
//动作方向
extern CString g_sLangID_Native_ActDirection;
extern CString g_sLangTxt_Native_ActDirection;

//低电压定义
extern CString g_sLangID_Native_LowVoltageDef;
extern CString g_sLangTxt_Native_LowVoltageDef;
/*_T("超前角度")*/
extern CString g_sLangID_Native_LeadAngle;
extern CString g_sLangTxt_Native_LeadAngle;
/*_T("滞后角度")*/
extern CString g_sLangID_Native_LagAngle;
extern CString g_sLangTxt_Native_LagAngle;
//计算系数
extern CString g_sLangID_Native_CalcCoef;
extern CString g_sLangTxt_Native_CalcCoef;
/*_T("工频变化量阻抗定值")*/
extern CString g_sLangID_Native_FreqChgZSetting;
extern CString g_sLangTxt_Native_FreqChgZSetting;
/*_T("正序灵敏角")*/
extern CString g_sLangID_Native_PosSeqSensAng;
extern CString g_sLangTxt_Native_PosSeqSensAng;
/*_T("接地距离偏移角")*/
extern CString g_sLangID_Native_GndDistOffset;
extern CString g_sLangTxt_Native_GndDistOffset;
/*_T("相间距离偏移角")*/
extern CString g_sLangID_Native_PhaseDistOffset;
extern CString g_sLangTxt_Native_PhaseDistOffset;
//平衡系数
extern CString g_sLangID_Native_BalCoeff;
extern CString g_sLangTxt_Native_BalCoeff;
/*QObject::tr("2次谐波制动系数")*/
extern CString g_sLangID_Native_2HarBrkCoef;
extern CString g_sLangTxt_Native_2HarBrkCoef;
/*QObject::tr("3次谐波制动系数")*/
extern CString g_sLangID_Native_3HarBrkCoef;
extern CString g_sLangTxt_Native_3HarBrkCoef;
/*QObject::tr("5次谐波制动系数")*/
extern CString g_sLangID_Native_5HarBrkCoef;
extern CString g_sLangTxt_Native_5HarBrkCoef;

//与当前测试仪建立连接失败(%s).
extern CString g_sLangID_Native_ConnectFail;
extern CString g_sLangTxt_Native_ConnectFail;

//测试仪连接中断，请先与测试仪建立连接。
extern CString g_sLangID_Native_TestrDisconn;
extern CString g_sLangTxt_Native_TestrDisconn;

// 电池电量信息获取异常.
extern CString g_sLangID_Native_UnBatteryInfor;
extern CString g_sLangTxt_Native_UnBatteryInfor;  

//正在加载测试功能界面，请稍后
extern CString g_sLangID_Native_LoadingMacroTest;
extern CString g_sLangTxt_Native_LoadingMacroTest;
//功能加载进度条
extern CString g_sLangID_Native_LoadingBar;
extern CString g_sLangTxt_Native_LoadingBar;

extern CString g_sLangID_remotemeas;
extern CString g_sLangTxt_remotemeas;
extern CString g_sLangID_Internal;
extern CString g_sLangTxt_Internal;
extern CString g_sLangID_Operation;
extern CString g_sLangTxt_Operation;
extern CString g_sLangID_Record;
extern CString g_sLangTxt_Record;
extern CString g_sLangID_EventType;
extern CString g_sLangTxt_EventType;
extern CString g_sLangID_DeviceTime;
extern CString g_sLangTxt_DeviceTime;
extern CString g_sLangID_PCTime;
extern CString g_sLangTxt_PCTime;
//"1档(0.3Ω/10A)" lcq
extern CString g_sLangID_Currentlevel1;
extern CString g_sLangTxt_Currentlevel1;
//"2档(0.7Ω/10A)" lcq
extern CString g_sLangID_Currentlevel2;
extern CString g_sLangTxt_Currentlevel2;
//"3档(1.5Ω/10A)" lcq
extern CString g_sLangID_Currentlevel3;
extern CString g_sLangTxt_Currentlevel3;

extern CString g_sLangID_Native_TempSaveSucc;
extern CString g_sLangTxt_Native_TempSaveSucc;
extern CString g_sLangID_Native_TempSaveFail;
extern CString g_sLangTxt_Native_TempSaveFail;
extern CString g_sLangID_Native_Success;
extern CString g_sLangTxt_Native_Success;
extern CString g_sLangID_Native_Timeout;
extern CString g_sLangTxt_Native_Timeout;
extern CString g_sLangID_Native_Fail;
extern CString g_sLangTxt_Native_Fail;
extern CString g_sLangID_Native_TempSave;
extern CString g_sLangTxt_Native_TempSave;
extern CString g_sLangID_Native_ExportWordReport;
extern CString g_sLangTxt_Native_ExportWordReport;
extern CString g_sLangID_Native_ReportSave;
extern CString g_sLangTxt_Native_ReportSave;

extern CString g_sLangID_Impedance_CalMode;
extern CString g_sLangTxt_Impedance_CalMode;
extern CString g_sLangID_Impedance_Choose;
extern CString g_sLangTxt_Impedance_Choose;
extern CString g_sLangID_Impedance_ShortCurr;
extern CString g_sLangTxt_Impedance_ShortCurr;
extern CString g_sLangID_Impedance_ShortVol;			 //_T("Impedance_ShortVol"); gongyp 20240719
extern CString g_sLangTxt_Impedance_ShortVol;		         //_T("短路电压（V）"); 
extern CString g_sLangID_Impedance_Delayed;
extern CString g_sLangTxt_Impedance_Delayed;
extern CString g_sLangID_Impedance_VarChoose;
extern CString g_sLangTxt_Impedance_VarChoose;
extern CString g_sLangID_Impedance_Mode;
extern CString g_sLangTxt_Impedance_Mode;
extern CString g_sLangID_Impedance_Time;
extern CString g_sLangTxt_Impedance_Time;
extern CString g_sLangID_Impedance_ChangeType;
extern CString g_sLangTxt_Impedance_ChangeType;
extern CString g_sLangID_Impedance_Auto;
extern CString g_sLangTxt_Impedance_Auto;
extern CString g_sLangID_Impedance_Mutation;
extern CString g_sLangTxt_Impedance_Mutation;

extern CString g_sLangID_Impedance_FunParas;			 //=_T("Impedance_FunParas");
extern CString g_sLangTxt_Impedance_FunParas;			 //=_T("");
extern CString g_sLangID_Impedance_Variable;			 //=_T("Impedance_Variable");
extern CString g_sLangTxt_Impedance_Variable;			 //=_T("");
extern CString g_sLangID_Impedance_ChangeStart;			 //=_T("Impedance_ChangeStart");
extern CString g_sLangTxt_Impedance_ChangeStart;			 //=_T("");
extern CString g_sLangID_Impedance_ChangeEnd;			 //=_T("Impedance_ChangeEnd");
extern CString g_sLangTxt_Impedance_ChangeEnd;			 //=_T(")");
extern CString g_sLangID_Impedance_ChangStep;			 //=_T("Impedance_ChangStep");
extern CString g_sLangTxt_Impedance_ChangStep;			 //=_T("");
extern CString g_sLangID_Impedance_NormalTime;			 //=_T("Impedance_NormalTime");
extern CString g_sLangTxt_Impedance_NormalTime;			 //=_T("");
extern CString g_sLangID_Impedance_FailTime;			 //=_T("Impedance_FailTime");
extern CString g_sLangTxt_Impedance_FailTime;			 //=_T("(s)");


extern CString g_sLangID_Impedance_ConstantCur;			 //=_T("Impedance_ConstantCur");
extern CString g_sLangTxt_Impedance_ConstantCur;			 //=_T("");
extern CString g_sLangID_Impedance_ConstantVol;			 //=_T("Impedance_ConstantVol");
extern CString g_sLangTxt_Impedance_ConstantVol;			 //=_T(");
extern CString g_sLangID_Impedance_FixedSystem;			 //=_T("Impedance_FixedSystem");
extern CString g_sLangTxt_Impedance_FixedSystem;			 //=_T

extern CString g_sLangID_Gradient_FailModes;			 //=_T("Gradient_FailModes");
extern CString g_sLangTxt_Gradient_FailModes;			 //=_T
extern CString g_sLangID_Gradient_Change;			 //=_T("Gradient_Change");
extern CString g_sLangTxt_Gradient_Change;			 //=_T
extern CString g_sLangID_Gradient_ImpAngle;			 //=_T("Gradient_ImpAngle");
extern CString g_sLangTxt_Gradient_ImpAngle;			 //=_T
extern CString g_sLangID_Gradient_ChangeTime;			 //=_T("Gradient_ChangeTime");
extern CString g_sLangTxt_Gradient_ChangeTime;			 //=_T(
extern CString g_sLangID_Gradient_FailBeforeTime;			 //=_T("Gradient_FailBeforeTime");
extern CString g_sLangTxt_Gradient_FailBeforeTime;			 //=_T
extern CString g_sLangID_Gradient_FailVol;			 //=_T("Gradient_FailVol");
extern CString g_sLangTxt_Gradient_FailVol;			 //=_T("
extern CString g_sLangID_Gradient_FailCur;			 //=_T("Gradient_FailCur");
extern CString g_sLangTxt_Gradient_FailCur;			 //=_T
extern CString g_sLangID_Gradient_FailAngle;			 //=_T("Gradient_FailAngle");
extern CString g_sLangTxt_Gradient_FailAngle;			 //=_T
extern CString g_sLangID_Gradient_RampParas;			 //=_T("Gradient_RampParas");
extern CString g_sLangTxt_Gradient_RampParas;			 //=_T
//extern CString g_sLangID_Gradient_VarSet;			 //=_T("Gradient_VarSet");
//extern CString g_sLangTxt_Gradient_VarSet;			 //=_T
extern CString g_sLangID_Gradient_CommonParas;			 //=_T("Gradient_CommonParas");
extern CString g_sLangTxt_Gradient_CommonParas;			 //=
extern CString g_sLangID_Gradient_BinBout;			 //=_T("Gradient_BinBout");
extern CString g_sLangTxt_Gradient_BinBout;			 //=_
extern CString g_sLangID_Gradient_BoutNormal;			 //=_T("Gradient_BoutNormal");
extern CString g_sLangTxt_Gradient_BoutNormal;			 //=_T
extern CString g_sLangID_Gradient_BoutFaultState;			 //=_T("Gradient_BoutFaultState");
extern CString g_sLangTxt_Gradient_BoutFaultState;			 //=_T


extern CString g_sLangID_Gradient_Test1;			 //=_T("Gradient_Test1");
extern CString g_sLangTxt_Gradient_Test1;			 //=_T
extern CString g_sLangID_Gradient_Test2;			 //=_T("Gradient_Test2");
extern CString g_sLangTxt_Gradient_Test2;			 //=_T
extern CString g_sLangID_Gradient_Test3;			 //=_T("Gradient_Test3");
extern CString g_sLangTxt_Gradient_Test3;			 //=_T
extern CString g_sLangID_Native_PhaseABshort;			 //=_T("Native_PhaseABshort");
extern CString g_sLangTxt_Native_PhaseABshort;			 //=_T(
extern CString g_sLangID_Native_PhaseBCshort;			 //=_T("Native_PhaseBCshort");
extern CString g_sLangTxt_Native_PhaseBCshort;			 //=_T("
extern CString g_sLangID_Native_PhaseCAshort;			 //=_T("Native_PhaseCAshort");
extern CString g_sLangTxt_Native_PhaseCAshort;			 //=_T(
extern CString g_sLangID_Native_PhaseABshortCcur;			 //=_T("Native_PhaseABshortCcur");
extern CString g_sLangTxt_Native_PhaseABshortCcur;			 //=_T
extern CString g_sLangID_Native_PhaseBCshortAcur;			 //=_T("Native_PhaseBCshortAcur");
extern CString g_sLangTxt_Native_PhaseBCshortAcur;			 //=_T(
extern CString g_sLangID_Native_PhaseCAshortBcur;			 //=_T("Native_PhaseCAshortBcur");
extern CString g_sLangTxt_Native_PhaseCAshortBcur;			 //=_T("
extern CString g_sLangID_Native_PhaseABshortBcur;			 //=_T("Native_PhaseABshortBcur");
extern CString g_sLangTxt_Native_PhaseABshortBcur;			 //=_T(
extern CString g_sLangID_Native_PhaseBCshortCcur;			 //=_T("Native_PhaseBCshortCcur");
extern CString g_sLangTxt_Native_PhaseBCshortCcur;			 //=_T(
extern CString g_sLangID_Native_PhaseCAshortAcur;			 //=_T("Native_PhaseCAshortAcur");
extern CString g_sLangTxt_Native_PhaseCAshortAcur;			 //=_T
extern CString g_sLangID_Native_PosVol;			 //=_T("Native_PosVol");
extern CString g_sLangTxt_Native_PosVol;			 //=_T
extern CString g_sLangID_Native_NegVol;			 //=_T("Native_NegVol");
extern CString g_sLangTxt_Native_NegVol;			 //=_T("
extern CString g_sLangID_Native_ZeroVol3U0;			 //=_T("Native_ZeroVol3U0");
extern CString g_sLangTxt_Native_ZeroVol3U0;			 //=_T
extern CString g_sLangID_Native_PosVolU1;			 //=_T("Native_PosVolU1");
extern CString g_sLangTxt_Native_PosVolU1;			 //=_T
extern CString g_sLangID_Native_NegVolU2;			 //=_T("Native_NegVolU2");
extern CString g_sLangTxt_Native_NegVolU2;			 //=_
extern CString g_sLangID_Native_Zero3U0;			 //=_T("Native_Zero3U0");
extern CString g_sLangTxt_Native_Zero3U0;			 //=_

extern CString g_sLangID_CBOperate_TimeAfterTrigger;			 //=_T("CBOperate_TimeAfterTrigger");
extern CString g_sLangTxt_CBOperate_TimeAfterTrigger;			 //=_T
extern CString g_sLangID_CBOperate_PTVPos;			 //=_T("CBOperate_PTVPos");
extern CString g_sLangTxt_CBOperate_PTVPos;			 //=
extern CString g_sLangID_CBOperate_CTPos;			 //=_T("CBOperate_CTPos");
extern CString g_sLangTxt_CBOperate_CTPos;			 //=_T
extern CString g_sLangID_CBOperate_AfterOpenTime;			 //=_T("CBOperate_AfterOpenTime");
extern CString g_sLangTxt_CBOperate_AfterOpenTime;			 //=_
extern CString g_sLangID_CBOperate_RecloseTime;			 //=_T("CBOperate_RecloseTime");
extern CString g_sLangTxt_CBOperate_RecloseTime;			 //=_
extern CString g_sLangID_CBOperate_AfterAccTime;			 //=_T("CBOperate_AfterAccTime");
extern CString g_sLangTxt_CBOperate_AfterAccTime;			 //=
extern CString g_sLangID_CBOperate_PTPos;			 //=_T("CBOperate_PTPos");
extern CString g_sLangTxt_CBOperate_PTPos;			 //=_
extern CString g_sLangID_CBOperate_TPos;			 //=_T("CBOperate_TPos");
extern CString g_sLangTxt_CBOperate_TPos;			 //=_T
extern CString g_sLangID_CBOperate_CTPos1;			 //=_T("CBOperate_CTPos1");
extern CString g_sLangTxt_CBOperate_CTPos1;			 //=
extern CString g_sLangID_CBOperate_TPos1;			 //=_T("CBOperate_TPos1");
extern CString g_sLangTxt_CBOperate_TPos1;			 //=_
extern CString g_sLangID_CBOperate_Overall;			 //=_T("CBOperate_Overall");
extern CString g_sLangTxt_CBOperate_Overall;			 //=_
extern CString g_sLangID_CBOperate_Zs;			 //=_T("CBOperate_Zs");
extern CString g_sLangTxt_CBOperate_Zs;			 //=_
extern CString g_sLangID_CBOperate_ZsPh;			 //=_T("CBOperate_ZsPh");
extern CString g_sLangTxt_CBOperate_ZsPh;			 //=_
extern CString g_sLangID_CBOperate_SimulateBreakerDelay;			 //=_T("CBOperate_SimulateBreakerDelay");
extern CString g_sLangTxt_CBOperate_SimulateBreakerDelay;			 //=_T
extern CString g_sLangID_CBOperate_BrkBreakTime;			 //=_T("CBOperate_BrkBreakTime");
extern CString g_sLangTxt_CBOperate_BrkBreakTime;			 //=_T(
extern CString g_sLangID_CBOperate_BrkCloseTime;			 //=_T("CBOperate_BrkCloseTime");
extern CString g_sLangTxt_CBOperate_BrkCloseTime;			 //=_T
extern CString g_sLangID_CBOperate_FaultIncMode;			 //=_T("CBOperate_FaultIncMode");
extern CString g_sLangTxt_CBOperate_FaultIncMode;			 //=_
extern CString g_sLangID_CBOperate_FaultAngle;			 //=_T("CBOperate_FaultAngle");
extern CString g_sLangTxt_CBOperate_FaultAngle;			 //=_T
extern CString g_sLangID_CBOperate_BIPlusDC;			 //=_T("CBOperate_BIPlusDC");
extern CString g_sLangTxt_CBOperate_BIPlusDC;			 //=_T("
extern CString g_sLangID_CBOperate_VzDefine;			 //=_T("CBOperate_VzDefine");
extern CString g_sLangTxt_CBOperate_VzDefine;			 //=_T(
extern CString g_sLangID_CBOperate_PsuVzRefPhase;			 //=_T("CBOperate_PsuVzRefPhase");
extern CString g_sLangTxt_CBOperate_PsuVzRefPhase;			 //=_
extern CString g_sLangID_CBOperate_VzPh;			 //=_T("CBOperate_VzPh");
extern CString g_sLangTxt_CBOperate_VzPh;			 //=_T(
extern CString g_sLangID_CBOperate_NotSimulated;			 //=_T("CBOperate_NotSimulated");
extern CString g_sLangTxt_CBOperate_NotSimulated;			 //=
extern CString g_sLangID_CBOperate_Random;			 //=_T("CBOperate_Random");
extern CString g_sLangTxt_CBOperate_Random;			 //=
extern CString g_sLangID_CBOperate_FixedValue;			 //=_T("CBOperate_FixedValue");
extern CString g_sLangTxt_CBOperate_FixedValue;			 //=
extern CString g_sLangID_CBOperate_UabPhase;			 //=_T("CBOperate_UabPhase");
extern CString g_sLangTxt_CBOperate_UabPhase;			 //=_T
extern CString g_sLangID_CBOperate_UbcPhase;			 //=_T("CBOperate_UbcPhase");
extern CString g_sLangTxt_CBOperate_UbcPhase;			 //=_T
extern CString g_sLangID_CBOperate_UcaPhase;			 //=_T("CBOperate_UcaPhase");
extern CString g_sLangTxt_CBOperate_UcaPhase;			 //=
extern CString g_sLangID_CBOperate_SingleHop;			 //=_T("CBOperate_SingleHop");
extern CString g_sLangTxt_CBOperate_SingleHop;			 //=
extern CString g_sLangID_CBOperate_TripleJump;			 //=_T("CBOperate_TripleJump");
extern CString g_sLangTxt_CBOperate_TripleJump;			 //=_
extern CString g_sLangID_CBOperate_Reclose;			 //=_T("CBOperate_Reclose");
extern CString g_sLangTxt_CBOperate_Reclose;			 //=_T
extern CString g_sLangID_CBOperate_BinBoutSelect;			 //=_T("CBOperate_BinBoutSelect");
extern CString g_sLangTxt_CBOperate_BinBoutSelect;			 //=
extern CString g_sLangID_CBOperate_BinABCD;			 //=_T("CBOperate_BinABCD");
extern CString g_sLangTxt_CBOperate_BinABCD;			 //=_
extern CString g_sLangID_CBOperate_BinEFGH;			 //=_T("CBOperate_BinEFGH");
extern CString g_sLangTxt_CBOperate_BinEFGH;			 //=_T
extern CString g_sLangID_CBOperate_OutputSwitchMode;			 //=_T("CBOperate_OutputSwitchMode");
extern CString g_sLangTxt_CBOperate_OutputSwitchMode;			 //=_
extern CString g_sLangID_CBOperate_OutputDelayTime;			 //=_T("CBOperate_OutputDelayTime");
extern CString g_sLangTxt_CBOperate_OutputDelayTime;			 //=
extern CString g_sLangID_CBOperate_StartTime;			 //=_T("CBOperate_StartTime");
extern CString g_sLangTxt_CBOperate_StartTime;			 //=_
extern CString g_sLangID_CBOperate_BinStart;			 //=_T("CBOperate_BinStart");
extern CString g_sLangTxt_CBOperate_BinStart;			 //=_T
extern CString g_sLangID_CBOperate_AbsOrRelative;			 //=_T("CBOperate_AbsOrRelative");
extern CString g_sLangTxt_CBOperate_AbsOrRelative;			 //=_
extern CString g_sLangID_CBOperate_AbsRelative;			 //=_T("CBOperate_AbsRelative");
extern CString g_sLangTxt_CBOperate_AbsRelative;			 //=
extern CString g_sLangID_CBOperate_CombError;			 //=_T("CBOperate_CombError");
extern CString g_sLangTxt_CBOperate_CombError;			 //=_
extern CString g_sLangID_CBOperate_Instan;			 //=_T("CBOperate_Instan");
extern CString g_sLangTxt_CBOperate_Instan;			 //=_
extern CString g_sLangID_CBOperate_Perpetual;			 //=_T("CBOperate_Perpetual");
extern CString g_sLangTxt_CBOperate_Perpetual;			 //=_
extern CString g_sLangID_CBOperate_MaxFaultTime;			 //=_T("CBOperate_MaxFaultTime");
extern CString g_sLangTxt_CBOperate_MaxFaultTime;			 //=_
extern CString g_sLangID_CBOperate_FaultMoment;			 //=_T("CBOperate_FaultMoment");
extern CString g_sLangTxt_CBOperate_FaultMoment;			 //=_
extern CString g_sLangID_CBOperate_Hour;			 //=_T("CBOperate_Hour");
extern CString g_sLangTxt_CBOperate_Hour;			 //=_T
extern CString g_sLangID_CBOperate_Minute;			 //=_T("CBOperate_Minute");
extern CString g_sLangTxt_CBOperate_Minute;			 //=_
extern CString g_sLangID_CBOperate_Second;			 //=_T("CBOperate_Second");
extern CString g_sLangTxt_CBOperate_Second;			 //=_T
extern CString g_sLangID_CBOperate_ImpRepre;			 //=_T("CBOperate_ImpRepre");
extern CString g_sLangTxt_CBOperate_ImpRepre;			 //=_T
extern CString g_sLangID_CBOperate_AmpPhase;			 //=_T("CBOperate_AmpPhase");
extern CString g_sLangTxt_CBOperate_AmpPhase;			 //=_
extern CString g_sLangID_CBOperate_ConversionTime;			 //=_T("CBOperate_ConversionTime");
extern CString g_sLangTxt_CBOperate_ConversionTime;			 //=_T
extern CString g_sLangID_CBOperate_Reverse;			 //=_T("CBOperate_Reverse");
extern CString g_sLangTxt_CBOperate_Reverse;			 //=_T
extern CString g_sLangID_CBOperate_Positive;			 //=_T("CBOperate_Positive");
extern CString g_sLangTxt_CBOperate_Positive;			 //=_T
extern CString g_sLangID_CBOperate_ConversionFail;			 //=_T("CBOperate_ConversionFail");
extern CString g_sLangTxt_CBOperate_ConversionFail;			 //=_T
extern CString g_sLangID_Swing_PowerAngleBegin;			 //=_T("Swing_PowerAngleBegin");
extern CString g_sLangTxt_Swing_PowerAngleBegin;			 //=_T
extern CString g_sLangID_Swing_PowerAngleEnd;			 //=_T("Swing_PowerAngleEnd");
extern CString g_sLangTxt_Swing_PowerAngleEnd;			 //=_
extern CString g_sLangID_Swing_SwingPeriod;             //= _T("Swing_Period");
extern CString g_sLangTxt_Swing_SwingPeriod;            //= _T;
extern CString g_sLangID_Swing_SwingCount;			 //=_T("Swing_SwingCount");
extern CString g_sLangTxt_Swing_SwingCount;			 //=_
extern CString g_sLangID_Swing_TripPoint;			 //=_T("Swing_TripPoint");
extern CString g_sLangTxt_Swing_TripPoint;			 //=_
extern CString g_sLangID_Swing_TripSpeedUp;            //= _T("Swing_TripSpeedUp");
extern CString g_sLangTxt_Swing_TripSpeedUp;           //= _T;
extern CString g_sLangID_Swing_TripSpeedDown;          //= _T("Swing_TripSpeedDown");
extern CString g_sLangTxt_Swing_TripSpeedDown;         //= _T;
extern CString g_sLangID_Swing_FaultType;              //= _T("Swing_FaultType");
extern CString g_sLangTxt_Swing_FaultType;             //= _T;
extern CString g_sLangID_Swing_Impedance;			 //=_T("Swing_Impedance");
extern CString g_sLangTxt_Swing_Impedance;			 //=_T
extern CString g_sLangID_Swing_SCurrent;			 //=_T("Swing_SCurrent");
extern CString g_sLangTxt_Swing_SCurrent;			 //=_T
extern CString g_sLangID_Swing_FaultTime;			 //=_T("Swing_FaultTime");
extern CString g_sLangTxt_Swing_FaultTime;			 //=_T
extern CString g_sLangID_Swing_K0CalMode;			 //=_T("Swing_K0CalMode");
extern CString g_sLangTxt_Swing_K0CalMode;			 //=_T
extern CString g_sLangID_Swing_Amplitude;            //= _T("Swing_Amplitude");
extern CString g_sLangTxt_Swing_Amplitude;             //= _T
extern CString g_sLangID_Swing_Phase;              //= _T("Swing_Phase");
extern CString g_sLangTxt_Swing_Phase;             //= _T
extern CString g_sLangID_Swing_IncreaseSpeed;			 //=_T("Swing_IncreaseSpeed");
extern CString g_sLangTxt_Swing_IncreaseSpeed;			 //=_
extern CString g_sLangID_Swing_Decelerate;			 //=_T("Swing_Decelerate");
extern CString g_sLangTxt_Swing_Decelerate;			 //=_
extern CString g_sLangID_Swing_FaultSwing;			 //=_T("Swing_FaultSwing");
extern CString g_sLangTxt_Swing_FaultSwing;			 //=_
extern CString g_sLangID_Swing_Reciprocating;			 //=_T("Swing_Reciprocating");
extern CString g_sLangTxt_Swing_Reciprocating;			 //
extern CString g_sLangID_Swing_OscParaSet;			 //=_T("Swing_OscParaSet");
extern CString g_sLangTxt_Swing_OscParaSet;			 //=_
extern CString g_sLangID_Swing_ImpDiagram;			 //=_T("Swing_ImpDiagram");
extern CString g_sLangTxt_Swing_ImpDiagram;			 //=_T
extern CString g_sLangID_Swing_EquCirSystem;			 //=_T("Swing_EquCirSystem");
extern CString g_sLangTxt_Swing_EquCirSystem;			 //=_
extern CString g_sLangID_Gradient_FirstVar;			 //=_T("Gradient_FirstVar");
extern CString g_sLangTxt_Gradient_FirstVar;			 //=_
extern CString g_sLangID_Gradient_SecondVar;			 //=_T("Gradient_SecondVar");
extern CString g_sLangTxt_Gradient_SecondVar;			 //=_T
extern CString g_sLangID_Gradient_FirstStep;			 //=_T("Gradient_FirstStep");
extern CString g_sLangTxt_Gradient_FirstStep;			 //=_T(
extern CString g_sLangID_Gradient_SecondStep;			 //=_T("Gradient_SecondStep");
extern CString g_sLangTxt_Gradient_SecondStep;			 //=_T
extern CString g_sLangID_PowerManu_VolPower;			 //=_T("PowerManu_VolPower");
extern CString g_sLangTxt_PowerManu_VolPower;			 //=_T
extern CString g_sLangID_PowerManu_PowerAct;			 //=_T("PowerManu_PowerAct");
extern CString g_sLangTxt_PowerManu_PowerAct;			 //=_T
extern CString g_sLangID_Swing_MinSwingVol;			 //=_T("Swing_MinSwingVol");
extern CString g_sLangTxt_Swing_MinSwingVol;			 //=_T
extern CString g_sLangID_Swing_MaxSwingCur;			 //=_T("Swing_MaxSwingCur");
extern CString g_sLangTxt_Swing_MaxSwingCur;			 //=_
extern CString g_sLangID_Swing_CenterSwing;			 //=_T("Swing_CenterSwing");
extern CString g_sLangTxt_Swing_CenterSwing;			 //=_
extern CString g_sLangID_Swing_Powerangle;			 //=_T("Swing_Powerangle");
extern CString g_sLangTxt_Swing_Powerangle;			 //=_
extern CString g_sLangID_Swing_Time;			 //=_T("Swing_Time");
extern CString g_sLangTxt_Swing_Time;			 //=_T
extern CString g_sLangID_Swing_CTPos;          //=_T("Swing_CTPos");
extern CString g_sLangTxt_Swing_CTPos;         //=_T("TA正极性：");
extern CString g_sLangID_Swing_Zs;			 //=_T("Swing_Zs");
extern CString g_sLangTxt_Swing_Zs;			 //=_T(
extern CString g_sLangID_Swing_ZsPhi;          //=_T("Swing_ZsPhi");
extern CString g_sLangTxt_Swing_ZsPhi;         //=_T("PhI(Zs)(°)：");
extern CString g_sLangID_Swing_Transformer;			 //=_T("Swing_Transformer");
extern CString g_sLangTxt_Swing_Transformer;			 //=_
extern CString g_sLangID_Swing_Transformer_Phi;        //=_T("Swing_Transformer_Phi");
extern CString g_sLangTxt_Swing_Transformer_Phi;       //=_T("Phi(Zt)(°)：");
extern CString g_sLangID_Swing_Dynamo;			 //=_T("Swing_Dynamo");
extern CString g_sLangTxt_Swing_Dynamo;			 //=_T(
extern CString g_sLangID_Power_Active;			 //=_T("Power_Active");
extern CString g_sLangTxt_Power_Active;			 //=_T
extern CString g_sLangID_Power_Reactive;			 //=_T("Power_Reactive");
extern CString g_sLangTxt_Power_Reactive;			 //=_T("无功(Var)");

extern CString g_sLangID_DistanceSearch_LNFault;			 //=_T("DistanceSearch_LNFault");
extern CString g_sLangTxt_DistanceSearch_LNFault;			 //=_T("接\n地\n故\n障");
extern CString g_sLangID_DistanceSearch_LLFault;			 //=_T("DistanceSearch_LLFault");
extern CString g_sLangTxt_DistanceSearch_LLFault;			 //=_T("相\n间\n故\n障");
extern CString g_sLangID_DistanceSearch_SectionOne;			 //=_T("DistanceSearch_SectionOne");
extern CString g_sLangTxt_DistanceSearch_SectionOne;			 //=_T("Ⅰ");
extern CString g_sLangID_DistanceSearch_SectionTwo;			 //=_T("DistanceSearch_SectionTwo");
extern CString g_sLangTxt_DistanceSearch_SectionTwo;			 //=_T("Ⅱ");
extern CString g_sLangID_DistanceSearch_SectionThree;			 //=_T("DistanceSearch_SectionThree");
extern CString g_sLangTxt_DistanceSearch_SectionThree;			 //=_T("Ⅲ");
extern CString g_sLangID_DistanceSearch_SectionFour;			 //=_T("DistanceSearch_SectionFour");
extern CString g_sLangTxt_DistanceSearch_SectionFour;			 //=_T("Ⅳ");
extern CString g_sLangID_DistanceSearch_SectionFive;			 //=_T("DistanceSearch_SectionFive");
extern CString g_sLangTxt_DistanceSearch_SectionFive;			 //=_T("Ⅴ");

extern CString g_sLangID_DistanceSearch_LNShort;				//_T("DistanceSearch_LNShort")
extern CString g_sLangTxt_DistanceSearch_LNShort;				//_T("单相接地短路")
extern CString g_sLangID_DistanceSearch_LLShort;				//_T("DistanceSearch_LLShort")
extern CString g_sLangTxt_DistanceSearch_LLShort;				//_T("相间短路")
extern CString g_sLangID_DistanceSearch_ThreePhaseShort;       //_T("DistanceSearch_ThreePhaseShort")
extern CString g_sLangTxt_DistanceSearch_ThreePhaseShort;       //_T("三相短路")
extern CString g_sLangID_DistanceSearch_ActionTime;			 //_T("DistanceSearch_ActionTime")
extern CString g_sLangTxt_DistanceSearch_ActionTime;			 //_T("动作时间")
extern CString g_sLangID_DistanceSearch_SensAngle;				//_T("DistanceSearch_SensAngle")
extern CString g_sLangTxt_DistanceSearch_SensAngle;			//_T("灵敏角")
extern CString g_sLangID_DistanceSearch_Z;						//_T("DistanceSearch_Z")
extern CString g_sLangTxt_DistanceSearch_Z;					//_T("|Z|(Ω)")
extern CString g_sLangID_DistanceSearch_Phi;					//_T("DistanceSearch_Phi")
extern CString g_sLangTxt_DistanceSearch_Phi;					 //_T("Phi(°)")
extern CString g_sLangID_DistanceSearch_RepeatTime;			//_T("DistanceSearch_RepeatTime")
extern CString g_sLangTxt_DistanceSearch_RepeatTime;			//_T("重复次数")
extern CString g_sLangID_DistanceSearch_Report;				//_T("DistanceSearch_Report")
extern CString g_sLangTxt_DistanceSearch_Report;				//_T("报告处理")
extern CString g_sLangID_DistanceSearch_AutoClose;				//_T("DistanceSearch_AutoClose")
extern CString g_sLangTxt_DistanceSearch_AutoClose;				//_T("边界自动闭合")
extern CString g_sLangID_DistanceSearch_XAxisName;				//_T("DistanceSearch_XAxisName")
extern CString g_sLangTxt_DistanceSearch_XAxisName;				//_T("R/Ω ")
extern CString g_sLangID_DistanceSearch_YAxisName;				//_T("DistanceSearch_YAxisName")
extern CString g_sLangTxt_DistanceSearch_YAxisName;				//_T("X/Ω ")

//20241024 wanmj
extern CString g_sLangID_DistanceSearch_ZoneType;				//_T("DistanceSearch_ZoneType")
extern CString g_sLangTxt_DistanceSearch_ZoneType;				//_T("区段:")
extern CString g_sLangID_DistanceSearch_BeginZ;				//_T("DistanceSearch_BeginZ")
extern CString g_sLangTxt_DistanceSearch_BeginZ;				//_T("首端阻抗(Ω):")
extern CString g_sLangID_DistanceSearch_BeginZAngle;				//_T("DistanceSearch_BeginZAngle")
extern CString g_sLangTxt_DistanceSearch_BeginZAngle;				//_T("首端阻抗角(°):")
extern CString g_sLangID_DistanceSearch_EndZ;				//_T("DistanceSearch_EndZ")
extern CString g_sLangTxt_DistanceSearch_EndZ;				//_T("末端阻抗(Ω):")
extern CString g_sLangID_DistanceSearch_EndZAngle;				//_T("DistanceSearch_EndZAngle")
extern CString g_sLangTxt_DistanceSearch_EndZAngle;				//_T("末端阻抗角(°):")
extern CString g_sLangID_DistanceSearch_Step;				//_T("DistanceSearch_Step")
extern CString g_sLangTxt_DistanceSearch_Step;				//_T("阻抗步长(Ω):")
extern CString g_sLangID_DistanceSearch_TSetting;				//_T("DistanceSearch_TSetting")
extern CString g_sLangTxt_DistanceSearch_TSetting;				//_T("时间定值(s):")
extern CString g_sLangID_DistanceSearch_AbsErr;				//_T("DistanceSearch_AbsErr")
extern CString g_sLangTxt_DistanceSearch_AbsErr;				//_T("绝对误差(Ω):")
extern CString g_sLangID_DistanceSearch_TimeAfterTrigger;				//_T("DistanceSearch_TimeAfterTrigger")
extern CString g_sLangTxt_DistanceSearch_TimeAfterTrigger;				//_T("保护动作后持续时间(s):")
extern CString g_sLangID_DistanceSearch_MinActionTime;				//_T("DistanceSearch_MinActionTime")
extern CString g_sLangTxt_DistanceSearch_MinActionTime;				//_T("最小动作时间(s):")
extern CString g_sLangID_DistanceSearch_Zl;				//_T("DistanceSearch_Zl")
extern CString g_sLangTxt_DistanceSearch_Zl;				//_T("线路阻抗:")
extern CString g_sLangID_DistanceSearch_K0Mode;				//_T("DistanceSearch_K0Mode")
extern CString g_sLangTxt_DistanceSearch_K0Mode;				//_T("零序补偿系数计算方式:")
extern CString g_sLangID_DistanceSearch_ZsMag;				//_T("DistanceSearch_ZsMag")
extern CString g_sLangTxt_DistanceSearch_ZsMag;				//_T("系统阻抗(Ω):")
extern CString g_sLangID_DistanceSearch_ZsAngle;				//_T("DistanceSearch_ZsAngle")
extern CString g_sLangTxt_DistanceSearch_ZsAngle;				//_T("系统阻抗角(°):")
extern CString g_sLangID_DistanceSearch_PTPos;				//_T("DistanceSearch_PTPos")
extern CString g_sLangTxt_DistanceSearch_PTPos;				//_T("TV安装位置:")
extern CString g_sLangID_DistanceSearch_CTPos;				//_T("DistanceSearch_CTPos")
extern CString g_sLangTxt_DistanceSearch_CTPos;				//_T("TA正极性:")
extern CString g_sLangID_DistanceSearch_SimulateBreakerDelay;				//_T("DistanceSearch_SimulateBreakerDelay")
extern CString g_sLangTxt_DistanceSearch_SimulateBreakerDelay;				//_T("断路器模拟:")
extern CString g_sLangID_DistanceSearch_BrkBreakTime;				//_T("DistanceSearch_BrkBreakTime")
extern CString g_sLangTxt_DistanceSearch_BrkBreakTime;				//_T("分闸时间(ms):")
extern CString g_sLangID_DistanceSearch_BrkCloseTime;				//_T("DistanceSearch_BrkCloseTime")
extern CString g_sLangTxt_DistanceSearch_BrkCloseTime;				//_T("合闸时间(ms):")
extern CString g_sLangID_DistanceSearch_FaultId;				//_T("DistanceSearch_FaultId")
extern CString g_sLangTxt_DistanceSearch_FaultId;				//_T("是否叠加非周期分量:")
extern CString g_sLangID_DistanceSearch_FaultAngMode;				//_T("DistanceSearch_FaultAngMode")
extern CString g_sLangTxt_DistanceSearch_FaultAngMode;				//_T("合闸角方式:")
extern CString g_sLangID_DistanceSearch_FaultAng;				//_T("DistanceSearch_FaultAng")
extern CString g_sLangTxt_DistanceSearch_FaultAng;				//_T("合闸角(°):")
extern CString g_sLangID_DistanceSearch_Header_ZoneType;				//_T("DistanceSearch_Header_ZoneType")
extern CString g_sLangTxt_DistanceSearch_Header_ZoneType;				//_T("区段")
extern CString g_sLangID_DistanceSearch_OrigImp;				//_T("DistanceSearch_OrigImp")
extern CString g_sLangTxt_DistanceSearch_OrigImp;				//_T("中心点阻抗(Ω):")
extern CString g_sLangID_DistanceSearch_OrigAng;				//_T("DistanceSearch_OrigAng")
extern CString g_sLangTxt_DistanceSearch_OrigAng;				//_T("中心点阻抗角(°):")
extern CString g_sLangID_DistanceSearch_SearchAngBeg;				//_T("DistanceSearch_SearchAngBeg")
extern CString g_sLangTxt_DistanceSearch_SearchAngBeg;				//_T("搜索角度始值(°):")
extern CString g_sLangID_DistanceSearch_SearchAngEnd;				//_T("DistanceSearch_SearchAngEnd")
extern CString g_sLangTxt_DistanceSearch_SearchAngEnd;				//_T("搜索角度终值(°):")
extern CString g_sLangID_DistanceSearch_AngStep;				//_T("DistanceSearch_AngStep")
extern CString g_sLangTxt_DistanceSearch_AngStep;				//_T("角度改变步长(°):")
extern CString g_sLangID_DistanceSearch_ZoneTypeSelect;				//_T("DistanceSearch_ZoneTypeSelect")
extern CString g_sLangTxt_DistanceSearch_ZoneTypeSelect;				//_T("区段选择:")
extern CString g_sLangID_DistanceSearch_SearchLen;				//_T("DistanceSearch_OrigImp")
extern CString g_sLangTxt_DistanceSearch_SearchLen;				//_T("搜索半径(Ω):")
extern CString g_sLangID_DistanceSearch_TripZ;				//_T("DistanceSearch_TripZ")
extern CString g_sLangTxt_DistanceSearch_TripZ;				//_T("实测阻抗(Ω)")
extern CString g_sLangID_DistanceSearch_TripZAngle;				//_T("DistanceSearch_TripZAngle")
extern CString g_sLangTxt_DistanceSearch_TripZAngle;				//_T("实测阻抗角(°)")

extern CString g_sLangID_ActionTime_LNShort;            //_T("ActionTime_LNShort")
extern CString g_sLangTxt_ActionTime_LNShort;            //_T("单相接地短路")
extern CString g_sLangID_ActionTime_LLShort;            //_T("ActionTime_LLShort")
extern CString g_sLangTxt_ActionTime_LLShort;            //_T("相间短路")
extern CString g_sLangID_ActionTime_ThreePhaseShort;     //_T("ActionTime_ThreePhaseShort")
extern CString g_sLangTxt_ActionTime_ThreePhaseShort;     //_T("三相短路")
extern CString g_sLangID_ActionTime_ZeroCur;             //_T("ActionTime_ZeroCur")
extern CString g_sLangTxt_ActionTime_ZeroCur;            //_T("零序电流3I0")
extern CString g_sLangID_ActionTime_NegCur;              //_T("ActionTime_NegCur")
extern CString g_sLangTxt_ActionTime_NegCur;             //_T("负序电流I2")
extern CString g_sLangID_ActionTime_ThreeParallel;      //_T("ActionTime_ThreeParallel")
extern CString g_sLangTxt_ActionTime_ThreeParallel;     //_T("三相电流并联")
extern CString g_sLangID_ActionTime_ShortVol;            //_T("ActionTime_ShortVol")
extern CString g_sLangTxt_ActionTime_ShortVol;            //_T("短路电压")
extern CString g_sLangID_ActionTime_ZeroVol;            //_T("ActionTime_ZeroVol")
extern CString g_sLangTxt_ActionTime_ZeroVol;            //_T("零序电压")
extern CString g_sLangID_ActionTime_NegVol;            //_T("ActionTime_NegVol")
extern CString g_sLangTxt_ActionTime_NegVol;            //_T("负序电压")
extern CString g_sLangID_ActionTime_SettingTime;            //_T("ActionTime_SettingTime")
extern CString g_sLangTxt_ActionTime_SettingTime;            //_T("动作时间定值(s):")
extern CString g_sLangID_ActionTime_FaultVolType;            //_T("ActionTime_FaultVolType")
extern CString g_sLangTxt_ActionTime_FaultVolType;            //_T("故障电压:")
extern CString g_sLangID_ActionTime_FaultVol;            //_T("ActionTime_FaultVol")
extern CString g_sLangTxt_ActionTime_FaultVol;            //_T("故障电压(V):")
extern CString g_sLangID_ActionTime_FaultAngle;            //_T("ActionTime_FaultAngle")
extern CString g_sLangTxt_ActionTime_FaultAngle;            //_T("故障态相位差(°):")
extern CString g_sLangID_ActionTime_FaultFre;            //_T("ActionTime_FaultFre")
extern CString g_sLangTxt_ActionTime_FaultFre;            //_T("故障态频率(Hz):")
extern CString g_sLangID_ActionTime_RelErr;            //_T("ActionTime_RelErr")
extern CString g_sLangTxt_ActionTime_RelErr;            //_T("相对误差(％):")
extern CString g_sLangID_ActionTime_AbsErrPos;            //_T("ActionTime_AbsErrPos")
extern CString g_sLangTxt_ActionTime_AbsErrPos;            //_T("绝对误差(s)+:")
extern CString g_sLangID_ActionTime_AbsErrNeg;            //_T("ActionTime_AbsErrNeg")
extern CString g_sLangTxt_ActionTime_AbsErrNeg;            //_T("绝对误差(s)-:")
extern CString g_sLangID_ActionTime_NormalVol;            //_T("ActionTime_NormalVol")
extern CString g_sLangTxt_ActionTime_NormalVol;            //_T("常态电压(V):")
extern CString g_sLangID_ActionTime_NormalCur;            //_T("ActionTime_NormalCur")
extern CString g_sLangTxt_ActionTime_NormalCur;            //_T("常态电流(A):")
extern CString g_sLangID_ActionTime_NormalAngle;            //_T("ActionTime_NormalAngle")
extern CString g_sLangTxt_ActionTime_NormalAngle;            //_T("常态相位差(°):")
extern CString g_sLangID_ActionTime_NormalFre;            //_T("ActionTime_NormalFre")
extern CString g_sLangTxt_ActionTime_NormalFre;            //_T("常态频率(Hz):")
extern CString g_sLangID_ActionTime_FaultTime;            //_T("ActionTime_FaultTime")
extern CString g_sLangTxt_ActionTime_FaultTime;            //_T("故障时间裕度(s):")
extern CString g_sLangID_ActionTime_ErrType;            //_T("ActionTime_ErrType")
extern CString g_sLangTxt_ActionTime_ErrType;            //_T("误差类型:")

extern CString g_sLangID_ActionTime_TestItem;            //_T("ActionTime_TestItem")
extern CString g_sLangTxt_ActionTime_TestItem;            //_T("测试项目")
extern CString g_sLangID_ActionTime_FaultPhase;            //_T("ActionTime_TestPhase")
extern CString g_sLangTxt_ActionTime_FaultPhase;            //_T("故障相别")
extern CString g_sLangID_ActionTime_Select;            //_T("ActionTime_Select")
extern CString g_sLangTxt_ActionTime_Select;            //_T("选择")
extern CString g_sLangID_ActionTime_TestResult;            //_T("ActionTime_TestResult")
extern CString g_sLangTxt_ActionTime_TestResult;            //_T("测试结果(s)")
extern CString g_sLangID_ActionTime_Title_SettingTime;            //_T("ActionTime_Title_SettingTime")
extern CString g_sLangTxt_ActionTime_Title_SettingTime;            //_T("时间定值(s)")

extern CString g_sLangID_Button_AddMultQuick;		    //_T("AddMultQuick")//wanmj 2024.7.14
extern CString g_sLangTxt_Button_AddMultQuick;		    //_T("快速添加")
extern CString g_sLangID_Button_AddMultDlg;			//_T("AddMultDlg")
extern CString g_sLangTxt_Button_AddMultDlg;			//_T("添加系列")
extern CString g_sLangID_Button_AddMultBatch;          //_T("AddMultBatch")
extern CString g_sLangTxt_Button_AddMultBatch;          //_T("批量添加")
extern CString g_sLangID_Button_DeleteSelItem;         //_T("DeleteSelItem")
extern CString g_sLangTxt_Button_DeleteSelItem;         //_T("删除当前")
extern CString g_sLangID_Button_DeleteAllItem;         //_T("DeleteAllItem")
extern CString g_sLangTxt_Button_DeleteAllItem;         //_T("删除全部")
extern CString g_sLangID_Button_ClearSelResult;		//_T("ClearSelResult")
extern CString g_sLangTxt_Button_ClearSelResult;		//_T("清除当前")
extern CString g_sLangID_Button_ClearAllResult;		//_T("_ClearAllResult")
extern CString g_sLangTxt_Button_ClearAllResult;		//_T("清除全部")
extern CString g_sLangID_Button_AddOneItem;            //_T("AddOneItem")
extern CString g_sLangTxt_Button_AddOneItem;            //_T("添加测试项")
extern CString g_sLangID_Button_AddMultiItem;            //_T("AddMultiItem")
extern CString g_sLangTxt_Button_AddMultiItem;            //_T("添加系列")

extern CString g_sLangID_Action_AddOneItem;            //_T("Action_AddOneItem")
extern CString g_sLangTxt_Action_AddOneItem;            //_T("添加测试项")
extern CString g_sLangID_Action_DeleteSelItem;         //_T("Action_DeleteSelItem")
extern CString g_sLangTxt_Action_DeleteSelItem;         //_T("删除当前测试项")
extern CString g_sLangID_Action_DeleteAllItem;         //_T("Action_DeleteAllItem")
extern CString g_sLangTxt_Action_DeleteAllItem;         //_T("删除所有测试项")
extern CString g_sLangID_Action_ClearSelResult;		//_T("Action_ClearSelResult")
extern CString g_sLangTxt_Action_ClearSelResult;		//_T("清除当前结果")
extern CString g_sLangID_Action_ClearAllResult;		//_T("Action_ClearAllResult")
extern CString g_sLangTxt_Action_ClearAllResult;		//_T("清除所有结果")

extern CString g_sLangID_PowerDir_TestPhase_Zero;  // _T("PowerDir_ZeroTest");     //20240717 wanmj 功率方向界面中文多语言处理
extern CString g_sLangTxt_PowerDir_TestPhase_Zero;  // _T("零序测试");
extern CString g_sLangID_PowerDir_TestPhase_Neg;  // _T("PowerDir_NegTest");
extern CString g_sLangTxt_PowerDir_TestPhase_Neg;  // _T("负序测试");
extern CString g_sLangID_PowerDir_FaultPhase_ZeroCur;  // _T("PowerDir_ZeroCurr");
extern CString g_sLangTxt_PowerDir_FaultPhase_ZeroCur;  // _T("零序电流");
extern CString g_sLangID_PowerDir_FaultPhase_NegCur;  // _T("PowerDir_NegCurr");
extern CString g_sLangTxt_PowerDir_FaultPhase_NegCur;  // _T("负序电流");

//20241024 wanmj
extern CString g_sLangID_PowerDir_TestPhase;  // _T("PowerDir_TestPhase");
extern CString g_sLangTxt_PowerDir_TestPhase;  // _T("测试相:");
extern CString g_sLangID_PowerDir_FaultPhase;  // _T("PowerDir_FaultPhase");
extern CString g_sLangTxt_PowerDir_FaultPhase;  // _T("故障相:");
extern CString g_sLangID_PowerDir_FaultTime;  // _T("PowerDir_FaultTime");
extern CString g_sLangTxt_PowerDir_FaultTime;  // _T("故障时间(s):");
extern CString g_sLangID_PowerDir_MaxSenAngle;  // _T("PowerDir_MaxSenAngle");
extern CString g_sLangTxt_PowerDir_MaxSenAngle;  // _T("最大灵敏角(°):");
extern CString g_sLangID_PowerDir_ActionAreaRange;  // _T("PowerDir_ActionAreaRange");
extern CString g_sLangTxt_PowerDir_ActionAreaRange;  // _T("动作区范围(°):");
extern CString g_sLangID_PowerDir_StepValue;  // _T("PowerDir_StepValue");
extern CString g_sLangTxt_PowerDir_StepValue;  // _T("变化步长(°):");
extern CString g_sLangID_PowerDir_AbsErr;  // _T("PowerDir_AbsErr");
extern CString g_sLangTxt_PowerDir_AbsErr;  // _T("绝对误差(°):");
extern CString g_sLangID_PowerDir_NormalBout;  // _T("PowerDir_NormalBout");
extern CString g_sLangTxt_PowerDir_NormalBout;  // _T("常态开出设置");
extern CString g_sLangID_PowerDir_FaultBout;  // _T("PowerDir_FaultBout");
extern CString g_sLangTxt_PowerDir_FaultBout;  // _T("故障态开出设置");
extern CString g_sLangID_PowerDir_UPre;  // _T("PowerDir_UPre");
extern CString g_sLangTxt_PowerDir_UPre;  // _T("常态电压幅值(V):");
extern CString g_sLangID_PowerDir_UPhSet;  // _T("PowerDir_UPhSet");
extern CString g_sLangTxt_PowerDir_UPhSet;  // _T("常态电压相序:");
extern CString g_sLangID_PowerDir_IPre;  // _T("PowerDir_IPre");
extern CString g_sLangTxt_PowerDir_IPre;  // _T("常态电流幅值(A):");
extern CString g_sLangID_PowerDir_IPhSet;  // _T("PowerDir_IPhSet");
extern CString g_sLangTxt_PowerDir_IPhSet;  // _T("常态电流相序:");
extern CString g_sLangID_PowerDir_PreAngle;  // _T("PowerDir_PreAngle");
extern CString g_sLangTxt_PowerDir_PreAngle;  // _T("常态相角(U-I):");
extern CString g_sLangID_PowerDir_AngleMode;  // _T("PowerDir_AngleMode");
extern CString g_sLangTxt_PowerDir_AngleMode;  // _T("角度定义:");
extern CString g_sLangID_PowerDir_ConnectMode;  // _T("PowerDir_ConnectMode");
extern CString g_sLangTxt_PowerDir_ConnectMode;  // _T("接线方式:");
extern CString g_sLangID_PowerDir_AngleMargin;  // _T("PowerDir_AngleMargin");
extern CString g_sLangTxt_PowerDir_AngleMargin;  // _T("角度裕度(°):");
extern CString g_sLangID_PowerDir_FaultParas;  // _T("PowerDir_FaultParas");
extern CString g_sLangTxt_PowerDir_FaultParas;  // _T("故障参数");
extern CString g_sLangID_PowerDir_TestParas;  // _T("PowerDir_TestParas");
extern CString g_sLangTxt_PowerDir_TestParas;  // _T("试验参数");
extern CString g_sLangID_PowerDir_APhaseTest;  // _T("PowerDir_APhaseTest");
extern CString g_sLangTxt_PowerDir_APhaseTest;  // _T("A相测试");
extern CString g_sLangID_PowerDir_BPhaseTest;  // _T("PowerDir_BPhaseTest");
extern CString g_sLangTxt_PowerDir_BPhaseTest;  // _T("B相测试");
extern CString g_sLangID_PowerDir_CPhaseTest;  // _T("PowerDir_CPhaseTest");
extern CString g_sLangTxt_PowerDir_CPhaseTest;  // _T("C相测试");
extern CString g_sLangID_PowerDir_ABPhaseTest;  // _T("PowerDir_ABPhaseTest");
extern CString g_sLangTxt_PowerDir_ABPhaseTest;  // _T("AB相测试");
extern CString g_sLangID_PowerDir_BCPhaseTest;  // _T("PowerDir_BCPhaseTest");
extern CString g_sLangTxt_PowerDir_BCPhaseTest;  // _T("BC相测试");
extern CString g_sLangID_PowerDir_CAPhaseTest;  // _T("PowerDir_CAPhaseTest");
extern CString g_sLangTxt_PowerDir_CAPhaseTest;  // _T("CA相测试");

extern CString g_sLangID_PowerDir_Title_MTA;  // _T("PowerDir_MTA");
extern CString g_sLangTxt_PowerDir_Title_MTA;  // _T("最大灵敏角理论值(°)");
extern CString g_sLangID_PowerDir_Title_ActionAreaRange;  // _T("PowerDir_Title_ActionAreaRange");
extern CString g_sLangTxt_PowerDir_Title_ActionAreaRange;  // _T("动作区范围(°)");
extern CString g_sLangID_PowerDir_Title_StepValue;  // _T("PowerDir_Title_StepValue");
extern CString g_sLangTxt_PowerDir_Title_StepValue;  // _T("变化步长(°)");
extern CString g_sLangID_PowerDir_Title_MaxSenAngle;  // _T("PowerDir_Title_MaxSenAngle");
extern CString g_sLangTxt_PowerDir_Title_MaxSenAngle;  // _T("最大灵敏角实测值(°)");
extern CString g_sLangID_PowerDir_Title_AngleF;  // _T("PowerDir_Title_AngleF");
extern CString g_sLangTxt_PowerDir_Title_AngleF;  // _T("边界1(°)");
extern CString g_sLangID_PowerDir_Title_AngleS;  // _T("PowerDir_Title_AngleS");
extern CString g_sLangTxt_PowerDir_Title_AngleS;  // _T("边界2(°)");

extern CString g_sLangID_CrrInverTime_IAmp;            //_T("CrrInverTime_IAmp")//zhangyq 2024.7.14
extern CString g_sLangTxt_CrrInverTime_IAmp;            //_T("电流幅值")
extern CString g_sLangID_CrrInverTime_IPh;            //_T("CrrInverTime_IPh")
extern CString g_sLangTxt_CrrInverTime_IPh;            //_T("电流相位")
extern CString g_sLangID_CrrInverTime_ChangeStart;            //_T("CrrInverTime_ChangeStart")
extern CString g_sLangTxt_CrrInverTime_ChangeStart;            //_T("变化始值(°)")
extern CString g_sLangID_CrrInverTime_ChangeFinish;            //_T("CrrInverTime_ChangeFinish")
extern CString g_sLangTxt_CrrInverTime_ChangeFinish;            //_T("变化终值(°)")
extern CString g_sLangID_CrrInverTime_ChangeStep;            //_T("CrrInverTime_ChangeStep")
extern CString g_sLangTxt_CrrInverTime_ChangeStep;            //_T("变化步长(°)")

extern CString g_sLangID_Syn_ActVoltageTest;            //_T("Syn_ActVoltageTest")
extern CString g_sLangTxt_Syn_ActVoltageTest;            //_T("电压边界值测试")
extern CString g_sLangID_Syn_ActFreqTest;            //_T("Syn_ActFreqTest")
extern CString g_sLangTxt_Syn_ActFreqTest;            //_T("频率边界值测试")
extern CString g_sLangID_Syn_LeadAngTest;            //_T("Syn_LeadAngTest")
extern CString g_sLangTxt_Syn_LeadAngTest;            //_T("导前角及导前时间")
extern CString g_sLangID_Syn_AutoAdjTest;            //_T("Syn_AutoAdjTest")
extern CString g_sLangTxt_Syn_AutoAdjTest;            //_T("自动调整试验")
extern CString g_sLangID_Syn_AdjVolTest;            //_T("Syn_AdjVolTest")
extern CString g_sLangTxt_Syn_AdjVolTest;            //_T("调压周期测试")
extern CString g_sLangID_Syn_AdjFreqTest;            //_T("Syn_AdjFreqTest")
extern CString g_sLangTxt_Syn_AdjFreqTest;            //_T("调频周期测试")

//20240719 huangliang
extern CString g_sLangID_Setting_NoWord;
extern CString g_sLangTxt_Setting_NoWord; //_T("尚未关联定值")
extern CString g_sLangID_Setting_Link;
extern CString g_sLangTxt_Setting_Link; //_T("关联选择定值")
extern CString g_sLangID_Setting_Cancel;
extern CString g_sLangTxt_Setting_Cancel; //_T("取消关联")
extern CString g_sLangID_Setting_CancelAll;
extern CString g_sLangTxt_Setting_CancelAll; //_T("取消全部")
//20240924 huangliang 
extern CString g_sLangID_Setting_NoFind;		
extern CString g_sLangTxt_Setting_NoFind; //_T("未找到")

//wangtao 20240722
extern CString g_sLangID_LowFreq_ULock;            //_T("LowFreq_ULock")
extern CString g_sLangTxt_LowFreq_ULock;            //_T("低电压闭锁值")
extern CString g_sLangID_LowFreq_ILock;            //_T("LowFreq_ILock")
extern CString g_sLangTxt_LowFreq_ILock;            //_T("低电流闭锁值")
extern CString g_sLangID_LowFreq_LowVol;            //_T("LowFreq_LowVol")
extern CString g_sLangTxt_LowFreq_LowVol;            //_T("低压")
extern CString g_sLangID_Gradient_Norm;            //_T("Gradient_Norm")
extern CString g_sLangTxt_Gradient_Norm;            //_T("常态")
extern CString g_sLangID_Diff_Rate;            //_T("Diff_Rate")
extern CString g_sLangTxt_Diff_Rate;            //_T("差动曲线搜索")
extern CString g_sLangID_Diff_Harm;            //_T("Diff_Harm")
extern CString g_sLangTxt_Diff_Harm;            //_T("谐波制动搜索")
extern CString g_sLangID_Diff_AddSearchLine;            //_T("Diff_AddSearchLine")
extern CString g_sLangTxt_Diff_AddSearchLine;            //_T("添加搜索线")
extern CString g_sLangID_Diff_Autocalculation;            //_T("Diff_Autocalculation")
extern CString g_sLangTxt_Diff_Autocalculation;            //_T("自动计算")
extern CString g_sLangID_Diff_Manualcalculation;            //_T("Diff_Manualcalculation")
extern CString g_sLangTxt_Diff_Manualcalculation;            //_T("手动计算")
extern CString g_sLangID_Diff_Dichotomy;            //_T("Diff_Dichotomy")
extern CString g_sLangTxt_Diff_Dichotomy;            //_T("二分法")
extern CString g_sLangID_Diff_StepwiseApproach;            //_T("Diff_StepwiseApproach")
extern CString g_sLangTxt_Diff_StepwiseApproach;            //_T("单步逼近法")
extern CString g_sLangID_Diff_Bequation1;            //_T("Diff_Bequation1")
extern CString g_sLangTxt_Diff_Bequation1;           //_T("Ir=(|I1-I2|)/K1或Ir=(|I1+I2|)/K1")
extern CString g_sLangID_Diff_Bequation5;            //_T("Diff_Bequation5")
extern CString g_sLangTxt_Diff_Bequation5;           //_T("Ir=√(K1*I1*I2*Cos(δ))")
extern CString g_sLangID_Diff_LineCur;            //_T("Diff_LineCur")
extern CString g_sLangTxt_Diff_LineCur;           //_T("线电流")
extern CString g_sLangID_Diff_Variation;            //_T("Diff_Variation")
extern CString g_sLangTxt_Diff_Variation;           //_T("△")
extern CString g_sLangID_Diff_sideAdjust;            //_T("Diff_Adjust")
extern CString g_sLangTxt_Diff_sideAdjust;           //_T("测校正")
extern CString g_sLangID_Diff_High;            //_T("Diff_High")
extern CString g_sLangTxt_Diff_High;           //_T("高")
extern CString g_sLangID_Diff_Medium;            //_T("Diff_Medium")
extern CString g_sLangTxt_Diff_Medium;           //_T("中")
extern CString g_sLangID_Diff_Low;            //_T("Diff_Low")
extern CString g_sLangTxt_Diff_Low;           //_T("低")
extern CString g_sLangID_MaintainatLeastOneItem;            //_T("MaintainatLeastOneItem")
extern CString g_sLangTxt_MaintainatLeastOneItem;           //_T("请至少勾选一个测试项！")
extern CString g_sLangID_MaintainatLeastOneFault;            //_T("MaintainatLeastOneFault");
extern CString g_sLangTxt_MaintainatLeastOneFault;            //_T("请至少勾选一个故障区段！");
extern CString g_sLangID_MaintainatLeastOneFunc;            //_T("MaintainatLeastOneFunc");
extern CString g_sLangTxt_MaintainatLeastOneFunc;            //_T("请至少勾选一个功能模块！");
extern CString g_sLangID_MaintainatLeastOneErrorType;       //_T("MaintainatLeastOneErrorType");
extern CString g_sLangTxt_MaintainatLeastOneErrorType;      //_T("请至少勾选一个故障类别！");
extern CString g_sLangID_MaintainatLeastOneRate;			 //T("MaintainatLeastOneRate");
extern CString g_sLangTxt_MaintainatLeastOneRate;           //_T("请至少勾选一个倍数！");
extern CString g_sLangID_MaintainatLeastOneDirection;       // = _T("MaintainatLeastOneDirection");
extern CString g_sLangTxt_MaintainatLeastOneDirection;      // = _T("请至少勾选一个故障方向！");

//2024.7.19  lupzibing 
extern CString g_sLangID_Distance_DeleteItem;			// _T("Distance_DeleteItem");
extern CString g_sLangTxt_Distance_DeleteItem;			// _T("删除测试项");
extern CString g_sLangID_Distance_ClearResult;			// _T("Distance_ClearResult");
extern CString g_sLangTxt_Distance_ClearResult;			// _T("清除测试结果");
extern CString g_sLangID_Distance_Zone1;				//_T("Distance_Zone1");
extern CString g_sLangTxt_Distance_Zone1;				//_T("Ⅰ段");
extern CString g_sLangID_Distance_Zone2;				//_T("Distance_Zone2");
extern CString g_sLangTxt_Distance_Zone2;				//_T("Ⅱ段");
extern CString g_sLangID_Distance_Zone3;				//_T("Distance_Zone3");
extern CString g_sLangTxt_Distance_Zone3;				//_T("Ⅲ段");
extern CString g_sLangID_Distance_Zone4;				//_T("Distance_Zone4");
extern CString g_sLangTxt_Distance_Zone4;				//_T("Ⅳ段");
extern CString g_sLangID_Distance_Zone5;				//_T("Distance_Zone5");
extern CString g_sLangTxt_Distance_Zone5;				//_T("Ⅴ段");
extern CString g_sLangID_Distance_ZoneLine;				//_T("Distance_ZoneLine");
extern CString g_sLangTxt_Distance_ZoneLine;			//_T("线路长度");
extern CString g_sLangID_Distance_ZoneAllarea;			//_T("Distance_ZoneAllarea");
extern CString g_sLangTxt_Distance_ZoneAllarea;			//_T("所有区域");
extern CString g_sLangID_Distance_ErrorNot;				//_T("Distance_ErrorNot");
extern CString g_sLangTxt_Distance_ErrorNot;			//_T("不评估");;
extern CString g_sLangID_Distance_ErrorRelAndAbs;		//_T("Distance_ErrorRelAndAbs");
extern CString g_sLangTxt_Distance_ErrorRelAndAbs;		//_T("绝对误差&amp;相对误差");
extern CString g_sLangID_Distance_ErrorRelorAbs;		//_T("Distance_ErrorRelorAbs");
extern CString g_sLangTxt_Distance_ErrorRelorAbs;		//_T("绝对误差or相对误差");
extern CString g_sLangID_Distance_AddOneLN;				//_T("Distance_AddOneLN");
extern CString g_sLangTxt_Distance_AddOneLN;			//_T("添加单个区段-接地故障");
extern CString g_sLangID_Distance_AddOneLL;				//_T("Distance_AddOneLL");
extern CString g_sLangTxt_Distance_AddOneLL;			//_T("添加单个区段-相间故障");
extern CString g_sLangID_Distance_AddMult;				//_T("Distance_AddMult");
extern CString g_sLangTxt_Distance_AddMult;				//_T("添加多个区段");
extern CString g_sLangID_Distance_VzDefine;             //_T("Distance_VzDefine");
extern CString g_sLangTxt_Distance_VzDefine;           	//_T("√3×3U0");
extern CString g_sLangID_Distance_ZTYAxis;		//_T("Distance_ZTYAxis");
extern CString g_sLangTxt_Distance_ZTYAxis;		//_T("Z(Ω)");

extern CString g_sLangID_Distance_Percent;			// = _T("Distance_Percent");
extern CString g_sLangTxt_Distance_Percent;			//= _T("百分比(%):");
extern CString g_sLangID_Distance_ZoneSel;			// = _T("Distance_ZoneSel");
extern CString g_sLangTxt_Distance_ZoneSel;			//= _T("区段选择:");
extern CString g_sLangID_Distance_FaultLN;			// = _T("Distance_FaultLN");
extern CString g_sLangTxt_Distance_FaultLN;			//= _T("接地故障");
extern CString g_sLangID_Distance_FaultLL;			// = _T("Distance_FaultLL");
extern CString g_sLangTxt_Distance_FaultLL;			//= _T("相间故障");
extern CString g_sLangID_Distance_MinTrip;			// = _T("Distance_MinTrip");
extern CString g_sLangTxt_Distance_MinTrip;			//= _T("最小动作时间(s):");
extern CString g_sLangID_Distance_ZLineSet;			// = _T("Distance_ZLineSet");
extern CString g_sLangTxt_Distance_ZLineSet;			//= _T("线路阻抗(Ω):");
extern CString g_sLangID_Distance_AddOneTileLL;			// = _T("Distance_AddOneTileLL");
extern CString g_sLangTxt_Distance_AddOneTileLL;			//= _T("添加相间接地故障");
extern CString g_sLangID_Distance_AddOneTileLN;			// = _T("Distance_AddOneTileLN");
extern CString g_sLangTxt_Distance_AddOneTileLN;			//= _T("添加单相接地故障");
extern CString g_sLangID_Distance_AddMultTile;			// = _T("Distance_AddMultTile");
extern CString g_sLangTxt_Distance_AddMultTile;			//= _T("添加系列");
extern CString g_sLangID_Distance_CommonParas;			// = _T("Distance_CommonParas");
extern CString g_sLangTxt_Distance_CommonParas;			//= _T("通用参数设置");
extern CString g_sLangID_Distance_ZImpValue;			// = _T("Distance_ZImpValue");
extern CString g_sLangTxt_Distance_ZImpValue;			// = _T("阻抗(Ω):");
extern CString g_sLangID_Distance_TSetting;			// = _T("Distance_TSetting");
extern CString g_sLangTxt_Distance_TSetting;			// = _T("时间定值(s):");
extern CString g_sLangID_Distance_SetActionTime;			// = _T("Distance_SetActionTime");
extern CString g_sLangTxt_Distance_SetActionTime;			// = _T("整定动作时间(s):");
extern CString g_sLangID_Distance_AddMultZone;			// = _T("Distance_AddMultZone");
extern CString g_sLangTxt_Distance_AddMultZone;			// = _T("区段:");
extern CString g_sLangID_Distance_FaultTypeSel;			// = _T("Distance_FaultTypeSel");
extern CString g_sLangTxt_Distance_FaultTypeSel;			// = _T("故障类型选择:");
extern CString g_sLangID_Distance_FailDirectSel;			// = _T("Distance_FailDirectSel");
extern CString g_sLangTxt_Distance_FailDirectSel;			// = _T("故障方向选择:");
extern CString g_sLangID_Distance_AddMultZAng;			// = _T("Distance_AddMultZAng");
extern CString g_sLangTxt_Distance_AddMultZAng;			// = _T("角阻抗(°)");
extern CString g_sLangID_Distance_OutputHoldTimeS;			// = _T("Distance_OutputHoldTimeS");
extern CString g_sLangTxt_Distance_OutputHoldTimeS;			// = _T("开出保持时间(s)");
extern CString g_sLangID_Distance_OutputDelayTime;			// = _T("Distance_OutputDelayTime");
extern CString g_sLangTxt_Distance_OutputDelayTime;			// = _T("开出翻转时刻(s)");
extern CString g_sLangID_Distance_VzPh;			// = _T("Distance_VzPh");
extern CString g_sLangTxt_Distance_VzPh;			// = _T("抽取电压相角(相对参考相):");
extern CString g_sLangID_Distance_AddTestItemTips;			// = _T("Distance_AddTestItemTips");
extern CString g_sLangTxt_Distance_AddTestItemTips;			// = _T("请添加测试项！");

extern CString g_sLangID_Distance_ImpActBorder;		// =_T("Distance_ImpActBorder");
extern CString g_sLangTxt_Distance_ImpActBorder;		// =_T("阻抗动作边界");
extern CString g_sLangID_Distance_ImpSetCheck;		// =_T("Distance_ImpSetCheck");
extern CString g_sLangTxt_Distance_ImpSetCheck;		// =_T("阻抗定值校验");
extern CString g_sLangID_Distance_AbsErrPlus;			// =_T("Distance_AbsErrPlus");
extern CString g_sLangTxt_Distance_AbsErrPlus;					// =_T("绝对误差(s)+");
extern CString g_sLangID_Distance_AbsErrMinus;		// =_T("Distance_AbsErrMinus");
extern CString g_sLangTxt_Distance_AbsErrMinus;				// =_T("绝对误差(s)-");
extern CString g_sLangID_Distance_CharacterEng_UseZone;		// =_T("CharacterEng_UseZone");
extern CString g_sLangTxt_CharacterEng_UseZone;				// =_T("使用");
extern CString g_sLangID_Distance_CharacterEng_FaulTips;		// =_T("CharacterEng_FaulTips");
extern CString g_sLangTxt_CharacterEng_FaulTips;				// =_T("带有故障环区域确实已存在!");
extern CString g_sLangID_Distance_CharacterEng_FaulTipTile;	// =_T("CharacterEng_FaulTipTile");
extern CString g_sLangTxt_CharacterEng_FaulTipTile;			// =_T("提示");

extern CString g_sLangTxt_Replay_WaveformEditing;         //_T("波形编辑")//wuxy 2024.7.22
extern CString g_sLangID_Replay_WaveformEditing;          //_T("Replay_WaveformEditing")
extern CString g_sLangTxt_Replay_OriWaveEdit;             //_T("原波形编辑")
extern CString g_sLangID_Replay_OriWaveEdit;              //_T("Replay_OriWaveEdit")
extern CString g_sLangTxt_Replay_InsertNorWave;           //_T("插入常态波形")
extern CString g_sLangID_Replay_InsertNorWave;            //_T("Replay_InsertNorWave")
extern CString g_sLangTxt_Replay_InsertWave;              //_T("插入波形")
extern CString g_sLangID_Replay_InsertWave;               //_T("Replay_InsertWave")
extern CString g_sLangTxt_Replay_InsertWaveParams;        //_T("插入波形参数:")
extern CString g_sLangID_Replay_InsertWaveParams;         //_T("Replay_InsertWaveParams")
extern CString g_sLangTxt_Replay_Time;                    //_T("时间")
extern CString g_sLangID_Replay_Time;                     //_T("Replay_Time")
extern CString g_sLangTxt_Replay_PointNumber;             //_T("点号")
extern CString g_sLangID_Replay_PointNumber;             //_T("Replay_PointNumber")
extern CString g_sLangTxt_Replay_StartPointNumber;       //_T("起始点号:")
extern CString g_sLangID_Replay_StartPointNumber;        //_T("Replay_StartPointNumber")
extern CString g_sLangTxt_Replay_EndPointNumber;         //_T("终止点号:")
extern CString g_sLangID_Replay_EndPointNumber;          //_T("Replay_EndPointNumber")
extern CString g_sLangTxt_Replay_StartTime;               //_T("起始时刻（s）:")
extern CString g_sLangID_Replay_StartTime;                //_T("Replay_StartTime")
extern CString g_sLangTxt_Replay_EndTime;                 //_T("终止时刻（s）:")
extern CString g_sLangID_Replay_EndTime;                  //_T("Replay_EndTime")
extern CString g_sLangTxt_Replay_NumCycles;               //_T("循环次数:")
extern CString g_sLangID_Replay_NumCycles;                //_T("Replay_NumCycles")
extern CString g_sLangTxt_Replay_Voltage;                 //_T("电压（V）:")
extern CString g_sLangID_Replay_Voltage;                  //_T("Replay_Voltage")
extern CString g_sLangTxt_Replay_Current;                 //_T("电流（A）:")
extern CString g_sLangID_Replay_Current;                  //_T("Replay_Current")
extern CString g_sLangTxt_Replay_OutputTime;              //_T("输出时间（s）:")
extern CString g_sLangID_Replay_OutputTime;               //_T("Replay_OutputTime")
extern CString g_sLangTxt_Replay_DeleteWave;              //_T("删除波形")
extern CString g_sLangID_Replay_DeleteWave;               //_T("Replay_DeleteWave")
extern CString g_sLangTxt_Replay_WaveReset;               //_T("波形复归")
extern CString g_sLangID_Replay_WaveReset;                //_T("Replay_WaveReset")
extern CString g_sLangTxt_Replay_Delete;                  //_T("删除")
extern CString g_sLangID_Replay_Delete;                   //_T("Replay_Delete")
extern CString g_sLangTxt_Replay_Insert;                  //_T("插入")
extern CString g_sLangID_Replay_Insert;                   //_T("Replay_Insert")
extern CString g_sLangID_Native_ConnectingAtsTester;
extern CString g_sLangTxt_Native_ConnectingAtsTester;
extern CString g_sLangID_Native_TesterConnectAtsSucc;
extern CString g_sLangTxt_Native_TesterConnectAtsSucc;
extern CString g_sLangID_Native_TesterConnectAtsfail;
extern CString g_sLangTxt_Native_TesterConnectAtsfail;

//zhangyq 2024.7.23 自动准同期通用参数中电压定义
extern CString g_sLangID_Syn_UDefineOne;                   //_T("Syn_UDefineOne")
extern CString g_sLangTxt_Syn_UDefineOne;                  //_T("系统->Ua1,待并->Ub1")
extern CString g_sLangID_Syn_UDefineTwo;                   //_T("Syn_UDefineTwo")
extern CString g_sLangTxt_Syn_UDefineTwo;                  //_T("系统->Ua1,待并->Ubc1")
extern CString g_sLangID_Syn_UDefineThree;                   //_T("Syn_UDefineThree")
extern CString g_sLangTxt_Syn_UDefineThree;                  //_T("系统->Ua2/Uz,待并->Uabc1")
extern CString g_sLangID_Syn_UDefineFour;                   //_T("Syn_UDefineFour")
extern CString g_sLangTxt_Syn_UDefineFour;                  //_T("系统->Uabc1,待并->Uabc2")
//zhangyq 2024.7.24 自动准同期开关量设置中开出量
extern CString g_sLangID_Syn_Pulse;                   //_T("Syn_Pulse")
extern CString g_sLangTxt_Syn_Pulse;                    //_T("脉冲")
extern CString g_sLangID_Syn_Continuous;                   //_T("Syn_Continuous")
extern CString g_sLangTxt_Syn_Continuous;                    //_T("连续")
//gongyiping 2024.9.30 自动准同期开关量设置中开出量名称
extern CString g_sLangID_Syn_State;                   //_T("Syn_State")
extern CString g_sLangTxt_Syn_State;                    //_T("状态")
extern CString g_sLangID_Syn_Mode;                   //_T("Syn_Mode")
extern CString g_sLangTxt_Syn_Mode;                    //_T("输出方式")
//gongyiping 2024.10.24 自动准同期参数
extern CString g_sLangID_Syn_ProOutSignals;			// _T("Syn_ProOutSignals");
extern CString g_sLangTxt_Syn_ProOutSignals;			//_T("保护出口信号");
extern CString g_sLangID_Syn_IncFSignals;			// _T("Syn_IncFSignals");
extern CString g_sLangTxt_Syn_IncFSignals;			// _T("增速信号");
extern CString g_sLangID_Syn_DecFSignals;			// _T("Syn_DecFSignals");
extern CString g_sLangTxt_Syn_DecFSignals;			// _T("减速信号");
extern CString g_sLangID_Sys_PointNum;			// _T("Sys_PointNum");
extern CString g_sLangTxt_Sys_PointNum;			// _T("钟点数:");
extern CString g_sLangID_Sys_PhaseDiff;			// _T("Sys_PhaseDiff");
extern CString g_sLangTxt_Sys_PhaseDiff;			// _T("两侧相位差(°):");
//gongyiping 2024.10.24 电压反时限
extern CString g_sLangID_Vol_TestPointsAdd;					// _T("Vol_TestPointsAdd");
extern CString g_sLangTxt_Vol_TestPointsAdd;					//  _T("测试点添加");
extern CString g_sLangID_Vol_FaultTypeSelect;					// _T("Vol_FaultTypeSelect");
extern CString g_sLangTxt_Vol_FaultTypeSelect;					//  _T("故障类别选择");
extern CString g_sLangID_Vol_FaultOutput;					// _T("Vol_FaultOutput");
extern CString g_sLangTxt_Vol_FaultOutput;					//  _T("故障态输出");
//20241024 gongyiping 电流反时限
extern CString g_sLangID_Curr_FaultBeforeOutput;				// _T("Vol_FaultBeforeOutput");
extern CString g_sLangTxt_Curr_FaultBeforeOutput;				// _T("故障前输出");
//zhangyq 2024.7.25 保存模版
extern CString g_sLangID_Native_LangTip                 ;//= _T("Native_LangTip");
extern CString g_sLangTxt_Native_LangTip                ;//= _T("提示");
extern CString g_sLangID_Native_FileSaveSuccess             ;//= _T("Native_FileSaveSuccess");
extern CString g_sLangTxt_Native_FileSaveSuccess            ;//= _T("文件保存成功！");
extern CString g_sLangID_Native_ExportWordDoc             ;//= _T("Native_ExportWordDoc");
extern CString g_sLangTxt_Native_ExportWordDoc            ;//= _T("导出word文件");
extern CString g_sLangID_Native_DocType             ;//= _T("Native_DocType");
extern CString g_sLangTxt_Native_DocType            ;//= _T("Word97-2003报告(*.doc);;Word报告(*.docx);;HTML报告(*.html);;PDF报告(*.pdf)");
extern CString g_sLangID_Iec_StartRcd;                   //_T("Iec_StartRcd")
extern CString g_sLangTxt_Iec_StartRcd;                    //_T("进入监视后，开始录波")
//20241023 wangsen 移入XLanguageResourceAts.h
////wangsen 2024.8.1 Xrio定值关联修改
//extern CString g_sLangID_Xrio_EnterNumbers;                 //=_T("Xrio_EnterNumbers");
//extern CString g_sLangTxt_Xrio_EnterNumbers;                //=_T("请输入一个数字。");

extern CString g_sLangID_Xrio_XrioError;                    //=_T("Xrio_XrioError");
extern CString g_sLangTxt_Xrio_XrioError;                   //=_T("XRIO错误");

//extern CString g_sLangID_Xrio_ValueLessThanOREqual;         //=_T("Xrio_ValueLessThanOREqual");
//extern CString g_sLangTxt_Xrio_ValueLessThanOREqual;        //=_T("值必须 <= ");

//extern CString g_sLangID_Xrio_ValueGreaterThanOREqual;      //=_T("Xrio_ValueGreaterThanOREqual");
//extern CString g_sLangTxt_Xrio_ValueGreaterThanOREqual;     //=_T("值必须 >= ");
//wangsen 2024.8.7 Xrio装置定值
extern CString g_sLangID_Xrio_DeviceSetting;                //=_T("Xrio_DeviceSetting");
extern CString g_sLangTxt_Xrio_DeviceSetting;               //=_T("装置定值")

//zhangyq 2024.8.20 通用阻抗结果评估
extern CString g_sLangTxt_Native_ActTimeValueAbsErrNeg;//动作时间值绝对误差负
extern CString g_sLangID_Native_ActTimeValueAbsErrNeg;

//2024-8-14 wuxinyi
extern CString  g_sLangID_ReplayTest_InsertWaveTip;		//=_T("ReplayTest_InsertWaveTip")
extern CString  g_sLangTxt_ReplayTest_InsertWaveTip;		//=_T("正在生成新的波形,请稍等....")
extern CString  g_sLangID_ReplayTest_RecoverWaveTip;		//=_T("ReplayTest_RecoverWaveTip")
extern CString  g_sLangTxt_ReplayTest_RecoverWaveTip;		//=_T("波形正在复归，请稍等....")
extern CString  g_sLangID_ReplayTest_LeftMove;		//=_T("ReplayTest_LeftMove")
extern CString  g_sLangTxt_ReplayTest_LeftMove;		//=_T("左移")
extern CString  g_sLangID_ReplayTest_RightMove;		//=_T("ReplayTest_RightMove")
extern CString  g_sLangTxt_ReplayTest_RightMove;		//=_T("右移")
extern CString  g_sLangID_ReplayTest_Cursor;		//=_T("ReplayTest_Cursor")
extern CString  g_sLangTxt_ReplayTest_Cursor;		//=_T("光标")
extern CString  g_sLangID_ReplayTest_TimeDiffer;		//=_T("ReplayTest_TimeDiffer")
extern CString  g_sLangTxt_ReplayTest_TimeDiffer;		//=_T("时差")
extern CString  g_sLangID_ReplayTest_PointDiffer;		//=_T("ReplayTest_PointDiffer")
extern CString  g_sLangTxt_ReplayTest_PointDiffer;		//=_T("点差")

//wangsen 2024.8.26 Xrio装置界面输入
extern CString g_sLangID_Xrio_InvalidInput;                 //= _T("Xrio_InvalidInput")
extern CString g_sLangTxt_Xrio_InvalidInput;                //= _T("无效输入")

extern CString g_sLangID_Xrio_InputRestrictionTypeOne;      //= _T("Xrio_InputRestrictionTypeOne")
extern CString g_sLangTxt_Xrio_InputRestrictionTypeOne;     //= _T("输入必须是大于或等于0的数字。")

extern CString g_sLangID_Xrio_InputRestrictionTypeTwo;      //= _T("Xrio_InputRestrictionTypeTwo")
extern CString g_sLangTxt_Xrio_InputRestrictionTypeTwo;     //= _T("请输入介于0和800之间的值。")

extern CString g_sLangID_Xrio_InputRestrictionTypeThree;    //= _T("Xrio_InputRestrictionTypeThree")
extern CString g_sLangTxt_Xrio_InputRestrictionTypeThree;   //= _T("请输入介于0.00和0.025之间的值。")


extern CString  g_sLangID_ReplayTest_DeleteTimeError;		//=_T("ReplayTest_DeleteTimeError");
extern CString  g_sLangTxt_ReplayTest_DeleteTimeError;		//_T("删除起点不能小于或等于终点，请重新输入!");
extern CString  g_sLangID_ReplayTest_InsertBeginTimeError;		//=_T("ReplayTest_InsertBeginTimeError");
extern CString  g_sLangTxt_ReplayTest_InsertBeginTimeError;		//_T("插入起点不能小于或等于终止点号，请重新输入!");
extern CString  g_sLangID_ReplayTest_InsertBeginPointError;		//=_T("ReplayTest_InsertBeginTimeError");
extern CString  g_sLangTxt_ReplayTest_InsertBeginPointError;		//_T("插入起始点号不能小于或等于终止点号，请重新输入!");

//20240905 huangliang
extern CString g_sLangID_MappingRelation_Maps_CHName;
extern CString g_sLangTxt_MappingRelation_Maps_CHName; //_T("电压电流")
extern CString g_sLangID_MappingRelation_Maps_BinName;
extern CString g_sLangTxt_MappingRelation_Maps_BinName; //_T("开关量输入")
extern CString g_sLangID_MappingRelation_Maps_BoutName;
extern CString g_sLangTxt_MappingRelation_Maps_BoutName; //_T("开关量输出")

extern CString g_sLangID_MappingRelation_Maps_TitleID;
extern CString g_sLangTxt_MappingRelation_Maps_TitleID; //_T("开关量通道")
extern CString g_sLangID_MappingRelation_Maps_TitleName;
extern CString g_sLangTxt_MappingRelation_Maps_TitleName; //_T("显示名称")


//20240919 wangsen
extern CString g_sLangID_Xrio_SettingFile;                  //= _T("Xrio_SettingFile")
extern CString g_sLangTxt_Xrio_SettingFile;                 //= _T("定值文件")

extern CString g_sLangID_Xrio_ImportRefs;                   //= _T("Xrio_ImportRefs")
extern CString g_sLangTxt_Xrio_ImportRefs;                  //= _T("参数值已导入。")

//xueyf 2024.9.26
extern CString g_sLangID_RecloseAcc_InspectLineNoStrain;       //= _T("RecloseAcc_InspectLineNoStrain")
extern CString g_sLangTxt_RecloseAcc_InspectLineNoStrain;      //= _T("检线无压母有压")
extern CString  g_sLangID_RecloseAcc_InspectLineStrain;		//=_T("RecloseAcc_InspectLineStrain");
extern CString  g_sLangTxt_RecloseAcc_InspectLineStrain;		//_T("检线有压母无压");
extern CString  g_sLangID_RecloseAcc_InspectLineNoPressure;	//=_T("RecloseAcc_InspectLineNoPressure");
extern CString  g_sLangTxt_RecloseAcc_InspectLineNoPressure;	//_T("检线无压母无压");
extern CString  g_sLangID_RecloseAcc_InspectLinePressure;		//=_T("RecloseAcc_InspectLinePressure");
extern CString  g_sLangTxt_RecloseAcc_InspectLinePressure;		//_T("检线有压母有压");
extern CString  g_sLangID_RecloseAcc_InspectNoOutput;			//=_T("RecloseAcc_InspectNoOutput");
extern CString  g_sLangTxt_RecloseAcc_InspectNoOutput;			//_T("无输出");
extern CString g_sLangID_RecloseAcc_NoAct;       //= _T("RecloseAcc_NoAct")
extern CString g_sLangTxt_RecloseAcc_NoAct;      //= _T("不动作")

//20241024 wanmj
extern CString g_sLangID_RecloseAcc_Z;       //= _T("RecloseAcc_Z")
extern CString g_sLangTxt_RecloseAcc_Z;      //= _T("阻抗(Ω):")
extern CString g_sLangID_RecloseAcc_R;       //= _T("RecloseAcc_R")
extern CString g_sLangTxt_RecloseAcc_R;      //= _T("R(Ω):")
extern CString g_sLangID_RecloseAcc_X;       //= _T("RecloseAcc_X")
extern CString g_sLangTxt_RecloseAcc_X;      //= _T("X(°):")
extern CString g_sLangID_RecloseAcc_Fre;       //= _T("RecloseAcc_Fre")
extern CString g_sLangTxt_RecloseAcc_Fre;      //= _T("频率(Hz):")
extern CString g_sLangID_RecloseAcc_RecloseTime;       //= _T("RecloseAcc_RecloseTime")
extern CString g_sLangTxt_RecloseAcc_RecloseTime;      //= _T("重合时间(s):")
extern CString g_sLangID_RecloseAcc_UxMode;       //= _T("RecloseAcc_UxMode")
extern CString g_sLangTxt_RecloseAcc_UxMode;      //= _T("抽取电压选择:")
extern CString g_sLangID_RecloseAcc_UxInputFre;       //= _T("RecloseAcc_UxInputFre")
extern CString g_sLangTxt_RecloseAcc_UxInputFre;      //= _T("抽取电压频率(Hz):")
extern CString g_sLangID_RecloseAcc_UxInputMag;       //= _T("RecloseAcc_UxInputMag")
extern CString g_sLangTxt_RecloseAcc_UxInputMag;      //= _T("跳闸后抽取电压(V):")
extern CString g_sLangID_RecloseAcc_UxInputAng;       //= _T("RecloseAcc_UxInputAng")
extern CString g_sLangTxt_RecloseAcc_UxInputAng;      //= _T("跳闸后抽取电压相位(°):")
extern CString g_sLangID_RecloseAcc_Input;       //= _T("RecloseAcc_Input")
extern CString g_sLangTxt_RecloseAcc_Input;      //= _T("开入操作")
extern CString g_sLangID_RecloseAcc_Output;       //= _T("RecloseAcc_Output")
extern CString g_sLangTxt_RecloseAcc_Output;      //= _T("开出操作")
extern CString g_sLangID_RecloseAcc_BinSelect;       //= _T("RecloseAcc_BinSelect")
extern CString g_sLangTxt_RecloseAcc_BinSelect;      //= _T("开入选择:")
extern CString g_sLangID_RecloseAcc_OutputSwitchMode;       //= _T("RecloseAcc_OutputSwitchMode")
extern CString g_sLangTxt_RecloseAcc_OutputSwitchMode;      //= _T("开出翻转启动方式:")
extern CString g_sLangID_RecloseAcc_OutputKeepTime;       //= _T("RecloseAcc_OutputKeepTime")
extern CString g_sLangTxt_RecloseAcc_OutputKeepTime;      //= _T("开出保持时间(s):")
extern CString g_sLangID_RecloseAcc_OutputDelayTime;       //= _T("RecloseAcc_OutputDelayTime")
extern CString g_sLangTxt_RecloseAcc_OutputDelayTime;      //= _T("开出翻转时刻(s):")
extern CString g_sLangID_RecloseAcc_FaultTrigMode;       //= _T("RecloseAcc_FaultTrigMode")
extern CString g_sLangTxt_RecloseAcc_FaultTrigMode;      //= _T("故障触发方式:")

extern CString g_sLangID_RecloseAcc_NoPre;       //= _T("RecloseAcc_NoPre")
extern CString g_sLangTxt_RecloseAcc_NoPre;      //= _T("检无压测试:")
extern CString g_sLangID_RecloseAcc_SamPer;       //= _T("RecloseAcc_SamPer")
extern CString g_sLangTxt_RecloseAcc_SamPer;      //= _T("检同期测试")
extern CString g_sLangID_RecloseAcc_Frequency;       //= _T("RecloseAcc_Frequency")
extern CString g_sLangTxt_RecloseAcc_Frequency;      //= _T("检频率测试")
extern CString g_sLangID_RecloseAcc_AutoReclose;       //= _T("RecloseAcc_AutoReclose")
extern CString g_sLangTxt_RecloseAcc_AutoReclose;      //= _T("自动重合闸")
extern CString g_sLangID_RecloseAcc_AftAcc;       //= _T("RecloseAcc_AftAcc")
extern CString g_sLangTxt_RecloseAcc_AftAcc;      //= _T("后加速测试:")
extern CString g_sLangID_RecloseAcc_NoPreSet;       //= _T("RecloseAcc_NoPreSet")
extern CString g_sLangTxt_RecloseAcc_NoPreSet;      //= _T("无压定值(V):")
extern CString g_sLangID_RecloseAcc_SynAngle;       //= _T("RecloseAcc_SynAngle")
extern CString g_sLangTxt_RecloseAcc_SynAngle;      //= _T("合闸角度(°):")
extern CString g_sLangID_RecloseAcc_K0Mode;       //= _T("RecloseAcc_K0Mode")
extern CString g_sLangTxt_RecloseAcc_K0Mode;      //= _T("表达方式:")

extern CString g_sLangID_RecloseAcc_TripTime;       //= _T("RecloseAcc_TripTime")
extern CString g_sLangTxt_RecloseAcc_TripTime;      //= _T("跳闸时间(s)")
extern CString g_sLangID_RecloseAcc_TtripD;       //= _T("RecloseAcc_TtripD")
extern CString g_sLangTxt_RecloseAcc_TtripD;      //= _T("重合时间(s)")
extern CString g_sLangID_RecloseAcc_TtripAcc;       //= _T("RecloseAcc_TtripAcc")
extern CString g_sLangTxt_RecloseAcc_TtripAcc;      //= _T("后加速时间(s)")
extern CString g_sLangID_RecloseAcc_Title_UxInputMag;       //= _T("RecloseAcc_Title_UxInputMag")
extern CString g_sLangTxt_RecloseAcc_Title_UxInputMag;      //= _T("抽取电压(V)")
extern CString g_sLangID_RecloseAcc_Title_UxInputAng;       //= _T("RecloseAcc_Title_UxInputAng")
extern CString g_sLangTxt_RecloseAcc_Title_UxInputAng;      //= _T("抽取电压相位(°)")
extern CString g_sLangID_RecloseAcc_Title_VZFreq;       //= _T("RecloseAcc_Title_VZFreq")
extern CString g_sLangTxt_RecloseAcc_Title_VZFreq;      //= _T("抽取电压频率(Hz)")

//xueyf 2024.9.29
extern CString  g_sLangID_BinRecord_Channel;			//=_T("BinRecord_Channel");
extern CString  g_sLangTxt_BinRecord_Channel;			//_T("录波通道");
extern CString  g_sLangID_BinRecord_RecordType;			//=_T("BinRecord_RecordType");
extern CString  g_sLangTxt_BinRecord_RecordType;			//_T("记录类型");
extern CString  g_sLangID_BinRecord_ClampRate;			//=_T("BinRecord_ClampRate");
extern CString  g_sLangTxt_BinRecord_ClampRate;			//_T("夹钳比率");
extern CString  g_sLangID_BinRecord_Invalid;			//=_T("BinRecord_Invalid");
extern CString  g_sLangTxt_BinRecord_Invalid;			//_T("无效");
extern CString  g_sLangID_BinRecord_BinPassive;			//=_T("BinRecord_BinPassive");
extern CString  g_sLangTxt_BinRecord_BinPassive;			//_T("开关量(无源)");
extern CString  g_sLangID_BinRecord_BinActive;			//=_T("BinRecord_BinActive");
extern CString  g_sLangTxt_BinRecord_BinActive;			//_T("开关量(有源)");
extern CString  g_sLangID_BinRecord_PlugName;			//=_T("BinRecord_PlugName");
extern CString  g_sLangTxt_BinRecord_PlugName;			//_T("插件名称");
extern CString  g_sLangID_BinRecord_PlugPOS;			//=_T("BinRecord_PlugPOS");
extern CString  g_sLangTxt_BinRecord_PlugPOS;			//_T("插件位置");
extern CString  g_sLangID_BinRecord_ChannelNum;			//=_T("BinRecord_ChannelNum");
extern CString  g_sLangTxt_BinRecord_ChannelNum;			//_T("通道数量");
extern CString  g_sLangID_BinRecord_PrimValue;			//=_T("BinRecord_PrimValue");
extern CString  g_sLangTxt_BinRecord_PrimValue;			//_T("一次侧");
extern CString  g_sLangID_BinRecord_SecondValue;			//=_T("BinRecord_SecondValue");
extern CString  g_sLangTxt_BinRecord_SecondValue;			//_T("二次侧");
extern CString  g_sLangID_BinRecord_StartRecord;			//=_T("BinRecord_StartRecord");
extern CString  g_sLangTxt_BinRecord_StartRecord;			//_T("启动录波");
extern CString  g_sLangID_BinRecord_StopRecord;			//=_T("BinRecord_StopRecord");
extern CString  g_sLangTxt_BinRecord_StopRecord;			//_T("停止录波");
extern CString  g_sLangID_BinRecord_Module;			//=_T("BinRecord_Module");
extern CString  g_sLangTxt_BinRecord_Module;			//_T("主板");
extern CString  g_sLangID_BinRecord_SaveDefaultCfg;			//=_T("BinRecord_SaveDefaultCfg");
extern CString  g_sLangTxt_BinRecord_SaveDefaultCfg;			//_T("是否保存为默认配置");
extern CString  g_sLangID_BinRecord_SelFile;			//=_T("BinRecord_SelFile");
extern CString  g_sLangTxt_BinRecord_SelFile;			//_T("选择文件");
extern CString  g_sLangID_BinRecord_ArrangeTop;			//=_T("BinRecord_ArrangeTop");
extern CString  g_sLangTxt_BinRecord_ArrangeTop;			//_T("排列在最前");
extern CString  g_sLangID_BinRecord_ArrangeLast;			//=_T("BinRecord_ArrangeLast");
extern CString  g_sLangTxt_BinRecord_ArrangeLast;			//_T("排列在最后");

//20240927 wangsen
extern CString g_sLangID_Xrio_InvalidName;                  //= _T("Xrio_InvalidName")
extern CString g_sLangTxt_Xrio_InvalidName;                 //= _T("无效名！不能为空！")

//20241023 wangsen 移入XLanguageResourceAts.h
////20241010 wangsen
//extern CString g_sLangID_Xrio_InvalidDoublePrecisionValue;  //= _T("Xrio_InvalidDoublePrecisionValue")
//extern CString g_sLangTxt_Xrio_InvalidDoublePrecisionValue; //= _T("无效的双精度值！")

//extern CString g_sLangID_Xrio_InvalidIntValue;              //= _T("Xrio_InvalidIntValue")
//extern CString g_sLangTxt_Xrio_InvalidIntValue;             //= _T("无效的整形值！")

//20241020 wangsen
extern CString g_sLangID_Xrio_TestObject;                   //= _T("Xrio_TestObject")
extern CString g_sLangTxt_Xrio_TestObject;                  //= _T("测试对象")
extern CString g_sLangID_Xrio_Update;                       //= _T("Xrio_Update")
extern CString g_sLangTxt_Xrio_Update;                      //= _T("更新")

extern CString g_sLangID_Xrio_Foreignid;                    //= _T("Xrio_Foreignid")
extern CString g_sLangTxt_Xrio_Foreignid;                   //= _T("不相关")
extern CString g_sLangID_Xrio_RefValue;                     //= _T("Xrio_RefValue")
extern CString g_sLangTxt_Xrio_RefValue;                    //= _T("参考值")
extern CString g_sLangID_Xrio_ValueFormula;                 //= _T("Xrio_ValueFormula")
extern CString g_sLangTxt_Xrio_ValueFormula;                //= _T("公式")

extern CString g_sLangID_Xrio_DeviceAttr_Name_Description;  //= _T("Xrio_DeviceAttr_Name_Description")
extern CString g_sLangTxt_Xrio_DeviceAttr_Name_Description; //= _T("名称/说明")
extern CString g_sLangID_Xrio_DeviceAttr_Manufacturer;      //= _T("Xrio_DeviceAttr_Manufacturer")
extern CString g_sLangTxt_Xrio_DeviceAttr_Manufacturer;     //= _T("制造厂商")
extern CString g_sLangID_Xrio_DeviceAttr_DeviceType;        //= _T("Xrio_DeviceAttr_DeviceType")
extern CString g_sLangTxt_Xrio_DeviceAttr_DeviceType;       //= _T("装置类型")
extern CString g_sLangID_Xrio_DeviceAttr_SerialNumber;      //= _T("Xrio_DeviceAttr_SerialNumber")
extern CString g_sLangTxt_Xrio_DeviceAttr_SerialNumber;     //= _T("序列号/型号")
extern CString g_sLangID_Xrio_DeviceAttr_AdditionalInformationOne;   //= _T("Xrio_DeviceAttr_AdditionalInformationOne")
extern CString g_sLangTxt_Xrio_DeviceAttr_AdditionalInformationOne;  //= _T("附加信息1")
extern CString g_sLangID_Xrio_DeviceAttr_AdditionalInformationTwo;   //= _T("Xrio_DeviceAttr_AdditionalInformationTwo")
extern CString g_sLangTxt_Xrio_DeviceAttr_AdditionalInformationTwo;  //= _T("附加信息2")

extern CString g_sLangID_Xrio_DeviceAttr_TransformerSubstation;      //= _T("Xrio_DeviceAttr_TransformerSubstation")
extern CString g_sLangTxt_Xrio_DeviceAttr_TransformerSubstation;     //= _T("变电站")
extern CString g_sLangID_Xrio_DeviceAttr_NumberOfPhases;    //= _T("Xrio_DeviceAttr_NumberOfPhases")
extern CString g_sLangTxt_Xrio_DeviceAttr_NumberOfPhases;   //= _T("相数")

extern CString g_sLangID_Xrio_DeviceAttr_ZSVAndZSC;         //= _T("Xrio_DeviceAttr_ZSVAndZSC")
extern CString g_sLangTxt_Xrio_DeviceAttr_ZSVAndZSC;        //= _T("零序电压和电流")
extern CString g_sLangID_Xrio_DeviceAttr_ZSVDirection;      //= _T("Xrio_DeviceAttr_ZSVDirection")
extern CString g_sLangTxt_Xrio_DeviceAttr_ZSVDirection;     //= _T("零序电压的方向")
extern CString g_sLangID_Xrio_DeviceAttr_ZSCDirection;      //= _T("Xrio_DeviceAttr_ZSCDirection")
extern CString g_sLangTxt_Xrio_DeviceAttr_ZSCDirection;     //= _T("零序电流的方向")
extern CString g_sLangID_Xrio_DeviceAttr_UseOfMutualInductor;       //= _T("Xrio_DeviceAttr_UseOfMutualInductor")
extern CString g_sLangTxt_Xrio_DeviceAttr_UseOfMutualInductor;      //= _T("使用互感仪")

extern CString g_sLangID_Xrio_DeviceAttr_OtherDeviceProperties;     //= _T("Xrio_DeviceAttr_OtherDeviceProperties")
extern CString g_sLangTxt_Xrio_DeviceAttr_OtherDeviceProperties;    //= _T("其他装置属性")

extern CString g_sLangID_Xrio_DeviceAttr_MaxValueSetting;   //= _T("Xrio_DeviceAttr_MaxValueSetting")
extern CString g_sLangTxt_Xrio_DeviceAttr_MaxValueSetting;  //= _T("最大值设置")

extern CString g_sLangID_Xrio_DeviceAttr_OvDetSens;         //= _T("Xrio_DeviceAttr_OvDetSens")
extern CString g_sLangTxt_Xrio_DeviceAttr_OvDetSens;        //= _T("过载检测灵敏度")

extern CString g_sLangID_Xrio_DeviceAttr_Damping;           //= _T("Xrio_DeviceAttr_Damping")
extern CString g_sLangTxt_Xrio_DeviceAttr_Damping;          //= _T("防抖/削峰过滤")
extern CString g_sLangID_Xrio_DeviceAttr_BroadeningTime;    //= _T("Xrio_DeviceAttr_BroadeningTime")
extern CString g_sLangTxt_Xrio_DeviceAttr_BroadeningTime;   //= _T("展宽时间")

//20241022 wangsen
extern CString g_sLangID_Xrio_LogInfo_UpdateFile;           //= _T("Xrio_LogInfo_UpdateFile")
extern CString g_sLangTxt_Xrio_LogInfo_UpdateFile;          //= _T("更新文件")
//20241023 wangsen 移入XLanguageResourceAts.h
//extern CString g_sLangID_Xrio_LogInfo_ParamDataType;        //= _T("Xrio_LogInfo_ParamDataType")
//extern CString g_sLangTxt_Xrio_LogInfo_ParamDataType;       //= _T("参数数据类型")
//extern CString g_sLangID_Xrio_LogInfo_NamePath;             //= _T("Xrio_LogInfo_NamePath")
//extern CString g_sLangTxt_Xrio_LogInfo_NamePath;            //= _T("名称路径")
//extern CString g_sLangID_Xrio_LogInfo_IDPath;               //= _T("Xrio_LogInfo_IDPath")
//extern CString g_sLangTxt_Xrio_LogInfo_IDPath;              //= _T("ID路径")
//extern CString g_sLangID_Xrio_LogInfo_InvalidParamDataType; //= _T("Xrio_LogInfo_InvalidParamDataType")
//extern CString g_sLangTxt_Xrio_LogInfo_InvalidParamDataType;//= _T("参数含无效数据类型！数据类型改为字符串型！")
//extern CString g_sLangID_Xrio_LogInfo_MinGreaterThanMax;    //= _T("Xrio_LogInfo_MinGreaterThanMax")
//extern CString g_sLangTxt_Xrio_LogInfo_MinGreaterThanMax;   //= _T("最小值大于最大值！")
//extern CString g_sLangID_Xrio_InvalidEnumValue;             //= _T("Xrio_InvalidEnumValue")
//extern CString g_sLangTxt_Xrio_InvalidEnumValue;            //= _T("无效的枚举值！")
//extern CString g_sLangID_Xrio_InvalidBinaryValue;           //= _T("Xrio_InvalidBinaryValue")
//extern CString g_sLangTxt_Xrio_InvalidBinaryValue;          //= _T("无效的二进制值！")

//2024-10-23 xueyangfan
extern CString g_sLangID_Native_Protection_CodeValue;		//= _T("Native_Protection_CodeValue")
extern CString g_sLangTxt_Native_Protection_CodeValue;		 //= _T("保护码值")
extern CString g_sLangID_Native_Measure_CodeValue;			 //= _T("Native_Measure_CodeValue")
extern CString g_sLangTxt_Native_Measure_CodeValue;		//= _T("测量码值")
extern CString g_sLangID_Native_SecondaryCur;		//= _T("Native_SecondaryCur")
extern CString g_sLangTxt_Native_SecondaryCur;		//= _T("二次额定电流")
extern CString g_sLangID_Native_CodeValue_Corrspondence;    //= _T("Native_CodeValue_Corrspondence")
extern CString g_sLangTxt_Native_CodeValue_Corrspondence;   //= _T("码值对应关系")

extern CString g_sLangID_Native_OpticalPort_Occupation;    //= _T("OpticalPort_Occupation")
extern CString g_sLangTxt_Native_OpticalPort_Occupation;   //= _T("光口已全部占用，当前无可选择的光口！")

extern CString g_sLangID_DiffCBOp_AddOneItme;				//= _T("DiffCBOp_AddOneItme")
extern CString g_sLangTxt_DiffCBOp_AddOneItme;				//= _T("添加单项")
extern CString g_sLangID_DiffCBOp_FaultLocation;				//= _T("DiffCBOp_FaultLocation")
extern CString g_sLangTxt_DiffCBOp_FaultLocation;				//= _T("故障点位置");
extern CString g_sLangID_DiffCBOp_ComBineFeature;				//= _T("DiffCBOp_ComBineFeature")
extern CString g_sLangTxt_DiffCBOp_ComBineFeature;				//= _T("复合特性")
extern CString g_sLangID_DiffCBOp_ZeroSeqElimiType;				//= _T("DiffCBOp_ZeroSeqElimiType")
extern CString g_sLangTxt_DiffCBOp_ZeroSeqElimiType;				//= _T("零序消除方式")
extern CString g_sLangID_DiffCBOp_Earthing;				//= _T("DiffCBOp_Earthing")
extern CString g_sLangTxt_DiffCBOp_Earthing;				//= _T("中性点接地")
extern CString g_sLangID_DiffCBOp_Coordinate;				//= _T("DiffCBOp_Coordinate")
extern CString g_sLangTxt_DiffCBOp_Coordinate;				//= _T("坐标")
extern CString g_sLangID_DiffCBOp_TransfHvKph;				//= _T("DiffCBOp_TransfHvKph")
extern CString g_sLangTxt_DiffCBOp_TransfHvKph;				//= _T("变压器高压侧")
extern CString g_sLangID_DiffCBOp_TransfHvKpm;				//= _T("DiffCBOp_TransfHvKpm")
extern CString g_sLangTxt_DiffCBOp_TransfHvKpm;				//= _T("变压器中压侧")
extern CString g_sLangID_DiffCBOp_TransfHvKpl;				//= _T("DiffCBOp_TransfHvKpl")
extern CString g_sLangTxt_DiffCBOp_TransfHvKpl;				//= _T("变压器低压侧")
extern CString g_sLangID_DiffCBOp_TransfRatedCapacity;				//= _T("DiffCBOp_TransfRatedCapacity")
extern CString g_sLangTxt_DiffCBOp_TransfRatedCapacity;				//= _T("额定容量")
extern CString g_sLangID_DiffCBOp_SetKph;				//= _T("DiffCBOp_SetKph")
extern CString g_sLangTxt_DiffCBOp_SetKph;				//= _T("设置平衡系数")

extern CString g_sLangID_DiffCBOp_BoutSet;				//= _T("DiffCBOp_BoutSet")
extern CString g_sLangTxt_DiffCBOp_BoutSet;				//= _T("常态开出设置")
extern CString g_sLangID_DiffCBOp_FaultBoutSet;				//= _T("DiffCBOp_FaultBoutSet")
extern CString g_sLangTxt_DiffCBOp_FaultBoutSet;				//= _T("故障态开出设置")
extern CString g_sLangID_DiffCBOp_HSecondCur;				//= _T("DiffCBOp_HSecondCur")
extern CString g_sLangTxt_DiffCBOp_HSecondCur;				//= _T("高侧二次额定电流")
extern CString g_sLangID_DiffCBOp_SetValue;				//= _T("DiffCBOp_SetValue")
extern CString g_sLangTxt_DiffCBOp_SetValue;				//= _T("设定值")
extern CString g_sLangID_DiffCBOp_AllSecondCur;				//= _T("DiffCBOp_AllSecondCur")
extern CString g_sLangTxt_DiffCBOp_AllSecondCur;				//= _T("各侧二次额定电流")
extern CString g_sLangID_DiffCBOp_FamousValue;				//= _T("DiffCBOp_FamousValue")
extern CString g_sLangTxt_DiffCBOp_FamousValue;				//= _T("有名值")
extern CString g_sLangID_DiffCBOp_StandardValue;				//= _T("DiffCBOp_StandardValue")
extern CString g_sLangTxt_DiffCBOp_StandardValue;				//= _T("标幺值")
extern CString g_sLangID_DiffCBOp_Auxiliary;				//= _T("DiffCBOp_Auxiliary")
extern CString g_sLangTxt_DiffCBOp_Auxiliary;				//= _T("辅助");

extern CString g_sLangID_DiffCBOp_FauleInH;				//= _T("DiffCBOp_FauleInH")
extern CString g_sLangTxt_DiffCBOp_FauleInH;				//= _T("高压侧(区内)")
extern CString g_sLangID_DiffCBOp_FauleOutH;				//= _T("DiffCBOp_FauleOutH")
extern CString g_sLangTxt_DiffCBOp_FauleOutH;				//= _T("高压侧(区外)")
extern CString g_sLangID_DiffCBOp_FauleInL;				//= _T("DiffCBOp_FauleInL")
extern CString g_sLangTxt_DiffCBOp_FauleInL;				//= _T("低压侧(区内)")
extern CString g_sLangID_DiffCBOp_FauleOutL;				//= _T("DiffCBOp_FauleOutL")
extern CString g_sLangTxt_DiffCBOp_FauleOutL;				//= _T("低压侧(区外)")
extern CString g_sLangID_DiffCBOp_FauleInM;				//= _T("DiffCBOp_FauleInM")
extern CString g_sLangTxt_DiffCBOp_FauleInM;				//= _T("中压侧(区内)")
extern CString g_sLangID_DiffCBOp_FauleOutM;				//= _T("DiffCBOp_FauleOutM")
extern CString g_sLangTxt_DiffCBOp_FauleOutM;				//= _T("中压侧(区外)")


//add wangtao 20241023
extern CString g_sLangID_Diff_RateSearch;            //_T("Diff_RateSearch")
extern CString g_sLangTxt_Diff_RateSearch;            //_T("差动搜索")
extern CString g_sLangID_Diff_FaultTime;            //_T("Diff_FaultTime")
extern CString g_sLangTxt_Diff_FaultTime;            //_T("最大故障时间(s)")
extern CString g_sLangID_Diff_Start;            //_T("Diff_Start")
extern CString g_sLangTxt_Diff_Start;            //_T("启动")
extern CString g_sLangID_Diff_IQuick;            //_T("Diff_IQuick")
extern CString g_sLangTxt_Diff_IQuick;            //_T("速段")
extern CString g_sLangID_Diff_SearchBand;            //_T("Diff_SearchBand")
extern CString g_sLangTxt_Diff_SearchBand;            //_T("搜索带")
extern CString g_sLangID_Diff_RateBeginVal;            //_T("Diff_RateBeginVal")
extern CString g_sLangTxt_Diff_RateBeginVal;            //_T("制动电流始值")
extern CString g_sLangID_Diff_RateEndVal;            //_T("Diff_RateEndVal")
extern CString g_sLangTxt_Diff_RateEndVal;            //_T("制动电流终值")
extern CString g_sLangID_Diff_Step;            //_T("Diff_Step")
extern CString g_sLangTxt_Diff_Step;            //_T("变化步长")
extern CString g_sLangID_Diff_Points;            //_T("Diff_Points")
extern CString g_sLangTxt_Diff_Points;            //_T("测试点数")
extern CString g_sLangID_Diff_ActAbsErr;            //_T("Diff_ActAbsErr")
extern CString g_sLangTxt_Diff_ActAbsErr;            //_T("动作值绝对误差")
extern CString g_sLangID_Diff_ActRelErr;            //_T("Diff_ActRelErr")
extern CString g_sLangTxt_Diff_ActRelErr;            //_T("动作值相对误差(%)")
extern CString g_sLangID_Diff_PrepareTime;            //_T("Diff_PrepareTime")
extern CString g_sLangTxt_Diff_PrepareTime;            //_T("准备时间(s)")
extern CString g_sLangID_Diff_TimeAfter;            //_T("Diff_TimeAfter")
extern CString g_sLangTxt_Diff_TimeAfter;            //_T("动作后保持时间(s)")
extern CString g_sLangID_Diff_KPSetMode;            //_T("Diff_KPSetMode")
extern CString g_sLangTxt_Diff_KPSetMode;            //_T("各侧平衡系数")
extern CString g_sLangID_Diff_KphSet;            //_T("Diff_KphSet")
extern CString g_sLangTxt_Diff_KphSet;            //_T("高压侧差动平衡系数")
extern CString g_sLangID_Diff_KpmSet;            //_T("Diff_KpmSet")
extern CString g_sLangTxt_Diff_KpmSet;            //_T("中压侧差动平衡系数")
extern CString g_sLangID_Diff_KplSet;            //_T("Diff_KplSet")
extern CString g_sLangTxt_Diff_KplSet;            //_T("低压侧差动平衡系数")
extern CString g_sLangID_Native_HighVoltWindingConnType;			 //_T("Native_HighVoltWindingConnType")
extern CString g_sLangTxt_Native_HighVoltWindingConnType;		 //_T("高压侧绕组接线型式")
extern CString g_sLangID_Native_LowVoltWindingConnType;			 //_T("Native_LowVoltWindingConnType")
extern CString g_sLangTxt_Native_LowVoltWindingConnType;		 //_T("低压侧绕组接线型式")
extern CString g_sLangID_Diff_PhCorrectMode;            //_T("Diff_PhCorrectMode")
extern CString g_sLangTxt_Diff_PhCorrectMode;            //_T("校正选择")
extern CString g_sLangID_Diff_AdoptWind;            //_T("Diff_AdoptWind")
extern CString g_sLangTxt_Diff_AdoptWind;            //_T("测试绕组")
extern CString g_sLangID_Diff_TransGroupModeHM;            //_T("Diff_TransGroupModeHM")
extern CString g_sLangTxt_Diff_TransGroupModeHM;            //_T("高-中绕组钟点数")
extern CString g_sLangID_Diff_TransGroupModeHL;            //_T("Diff_TransGroupModeHL")
extern CString g_sLangTxt_Diff_TransGroupModeHL;            //_T("高-低绕组钟点数")
extern CString g_sLangID_Diff_JXFactor;            //_T("Diff_JXFactor")
extern CString g_sLangTxt_Diff_JXFactor;            //_T("平衡系数计算")
extern CString g_sLangID_Diff_Earthing;            //_T("Diff_Earthing")
extern CString g_sLangTxt_Diff_Earthing;            //_T("接地")
extern CString g_sLangID_Diff_FaultType;            //_T("Diff_FaultType")
extern CString g_sLangTxt_Diff_FaultType;            //_T("故障相别")
extern CString g_sLangID_Diff_CustomHarmIndex;            //_T("Diff_CustomHarmIndex")
extern CString g_sLangTxt_Diff_CustomHarmIndex;            //_T("自定义谐波次数")
extern CString g_sLangID_Diff_BeginVal;            //_T("Diff_BeginVal")
extern CString g_sLangTxt_Diff_BeginVal;            //_T("搜索始值")
extern CString g_sLangID_Diff_EndVal;            //_T("Diff_EndVal")
extern CString g_sLangTxt_Diff_EndVal;            //_T("搜索终值")
extern CString g_sLangID_Diff_HarmOutSide;            //_T("Diff_HarmOutSide")
extern CString g_sLangTxt_Diff_HarmOutSide;            //_T("谐波输出侧")
extern CString g_sLangID_Diff_UpperLimit;            //_T("Diff_UpperLimit")
extern CString g_sLangTxt_Diff_UpperLimit;            //_T("搜索上限")
extern CString g_sLangID_Diff_LowLimit;            //_T("Diff_LowLimit")
extern CString g_sLangTxt_Diff_LowLimit;            //_T("搜索下限")
extern CString g_sLangID_Diff_IdSetting;            //_T("Diff_IdSetting")
extern CString g_sLangTxt_Diff_IdSetting;            //_T("差动理论值")
extern CString g_sLangID_Diff_SglSideBalCoeff;            //_T("Diff_SglSideBalCoeff")
extern CString g_sLangTxt_Diff_SglSideBalCoeff;            //_T("Ⅰ侧平衡系数")
extern CString g_sLangID_Diff_TwoSideBalCoeff;            //_T("Diff_TwoSideBalCoeff")
extern CString g_sLangTxt_Diff_TwoSideBalCoeff;            //_T("Ⅱ侧平衡系数")
extern CString g_sLangID_Diff_ThreeSideBalCoeff;            //_T("Diff_ThreeSideBalCoeff")
extern CString g_sLangTxt_Diff_ThreeSideBalCoeff;            //_T("Ⅲ侧平衡系数")
extern CString g_sLangID_Diff_PerUnitVal;            //_T("Diff_PerUnitVal")
extern CString g_sLangTxt_Diff_PerUnitVal;            //_T("标幺值")
extern CString g_sLangID_Diff_WiringCoeff;            //_T("Diff_WiringCoeff")
extern CString g_sLangTxt_Diff_WiringCoeff;            //_T("接线系数")
extern CString g_sLangID_Diff_RefCurrentSel;            //_T("Diff_RefCurrentSel")
extern CString g_sLangTxt_Diff_RefCurrentSel;            //_T("基准电流")
extern CString g_sLangID_Diff_HighVoltSide;            //_T("Diff_HighVoltSide")
extern CString g_sLangTxt_Diff_HighVoltSide;            //_T("高压侧")
extern CString g_sLangID_Diff_MedVoltSide;            //_T("Diff_MedVoltSide")
extern CString g_sLangTxt_Diff_MedVoltSide;            //_T("中压侧")
extern CString g_sLangID_Diff_LowVoltSide;            //_T("Diff_LowVoltSide")
extern CString g_sLangTxt_Diff_LowVoltSide;            //_T("低压侧")
extern CString g_sLangID_Diff_DiffProtCurrTerm;            //_T("Diff_DiffProtCurrTerm")
extern CString g_sLangTxt_Diff_DiffProtCurrTerm;            //_T("差动保护电流端子")
extern CString g_sLangID_Diff_RelayTest;            //_T("Diff_RelayTest")
extern CString g_sLangTxt_Diff_RelayTest;            //_T("继电保护测试仪")
extern CString g_sLangID_Diff_FuncParas;            //_T("Diff_FuncParas")
extern CString g_sLangTxt_Diff_FuncParas;            //_T("功能参数")
extern CString g_sLangID_Diff_AddOneItem;            //_T("Diff_AddOneItem")
extern CString g_sLangTxt_Diff_AddOneItem;            //_T("添加单项")
extern CString g_sLangID_Diff_ClearResult;            //_T("Diff_ClearResult")
extern CString g_sLangTxt_Diff_ClearResult;            //_T("清除结果")
extern CString g_sLangID_Diff_CommonPara;            //_T("Diff_CommonPara")
extern CString g_sLangTxt_Diff_CommonPara;            //_T("通用参数")
extern CString g_sLangID_LowFreq_FreqRangeRate;            //_T("LowFreq_FreqRangeRate")
extern CString g_sLangTxt_LowFreq_FreqRangeRate;            //_T("频率变化范围及其变化率")
extern CString g_sLangID_LowFreq_FreqBegin;            //_T("LowFreq_FreqBegin")
extern CString g_sLangTxt_LowFreq_FreqBegin;            //_T("频率起始值(Hz)")
extern CString g_sLangID_LowFreq_FreqEnd;            //_T("LowFreq_FreqEnd")
extern CString g_sLangTxt_LowFreq_FreqEnd;            //_T("频率结束值(Hz)")
extern CString g_sLangID_LowFreq_FreqFaultTrig;            //_T("LowFreq_FaultTrig")
extern CString g_sLangTxt_LowFreq_FreqFaultTrig;            //_T("闭锁电压选择")
extern CString g_sLangID_LowFreq_PhaseV;            //_T("LowFreq_PhaseV")
extern CString g_sLangTxt_LowFreq_PhaseV;            //_T("相电压")
extern CString g_sLangID_LowFreq_SettingBegin;            //_T("LowFreq_SettingBegin")
extern CString g_sLangTxt_LowFreq_SettingBegin;            //_T("整定值作为计时起点")
extern CString g_sLangID_LowFreq_FreqChangeBegin;            //_T("LowFreq_FreqChangeBegin")
extern CString g_sLangTxt_LowFreq_FreqChangeBegin;            //_T("频率变化作为计时起点")
extern CString g_sLangID_LowFreq_CommonParaSet;            //_T("LowFreq_CommonParaSet")
extern CString g_sLangTxt_LowFreq_CommonParaSet;            //_T("通用参数设置")
extern CString g_sLangID_LowFreq_dfdtSetting;            //_T("LowFreq_dfdtSetting")
extern CString g_sLangTxt_LowFreq_dfdtSetting;            //_T("滑差定值")
extern CString g_sLangID_LowFreq_GradientPara;            //_T("LowFreq_GradientPara")
extern CString g_sLangTxt_LowFreq_GradientPara;            //_T("递变参数")
extern CString g_sLangID_LowFreq_dfdtBegin;            //_T("LowFreq_dfdtBegin")
extern CString g_sLangTxt_LowFreq_dfdtBegin;            //_T("滑差变化始值")
extern CString g_sLangID_LowFreq_dfdtEnd;            //_T("LowFreq_dfdtEnd")
extern CString g_sLangTxt_LowFreq_dfdtEnd;            //_T("滑差变化终值")
extern CString g_sLangID_LowFreq_dfdtStep;            //_T("LowFreq_dfdtStep")
extern CString g_sLangTxt_LowFreq_dfdtStep;            //_T("滑差变化步长")
extern CString g_sLangID_LowFreq_LowVoltage;            //_T("LowFreq_LowVoltage")
extern CString g_sLangTxt_LowFreq_LowVoltage;            //_T("低电压")
extern CString g_sLangID_LowFreq_BeginVal;            //_T("LowFreq_BeginVal")
extern CString g_sLangTxt_LowFreq_BeginVal;            //_T("变化始值")
extern CString g_sLangID_LowFreq_EndVal;            //_T("LowFreq_EndVal")
extern CString g_sLangTxt_LowFreq_EndVal;            //_T("变化终值")
extern CString g_sLangID_LowFreq_TestItem;            //_T("LowFreq_TestItem")
extern CString g_sLangTxt_LowFreq_TestItem;            //_T("测试项目")
extern CString g_sLangID_LowFreq_dvdtRate;            //_T("LowFreq_dvdtRate")
extern CString g_sLangTxt_LowFreq_dvdtRate;            //_T("频率滑差倍数")
extern CString g_sLangID_LowFreq_TimePara;            //_T("LowFreq_TimePara")
extern CString g_sLangTxt_LowFreq_TimePara;            //_T("时间参数")
extern CString g_sLangID_LowFreq_ULockPara;            //_T("LowFreq_ULockPara")
extern CString g_sLangTxt_LowFreq_ULockPara;            //_T("电压闭锁参数")
extern CString g_sLangID_LowFreq_dvdtSetting;            //_T("LowFreq_dvdtSetting")
extern CString g_sLangTxt_LowFreq_dvdtSetting;            //_T("频率滑差动作值(Hz/s)")
extern CString g_sLangID_LowVol_BeginVal;            //_T("LowVol_BeginVal")
extern CString g_sLangTxt_LowVol_BeginVal;            //_T("变化起始值")
extern CString g_sLangID_LowVol_EndVal;            //_T("LowVol_EndVal")
extern CString g_sLangTxt_LowVol_EndVal;            //_T("变化结束值")
extern CString g_sLangID_LowVol_Var;            //_T("LowVol_Var")
extern CString g_sLangTxt_LowVol_Var;            //_T("变化量")
extern CString g_sLangID_LowVol_FreqRangeRate;            //_T("LowVol_FreqRangeRate")
extern CString g_sLangTxt_LowVol_FreqRangeRate;            //_T("电压变化范围及其变化率")
extern CString g_sLangID_LowVol_dVdt;            //_T("LowVol_dVdt")
extern CString g_sLangTxt_LowVol_dVdt;            //_T("滑差")
extern CString g_sLangID_LowVol_dVdtRate;            //_T("LowVol_dVdtRate")
extern CString g_sLangTxt_LowVol_dVdtRate;            //_T("电压滑差倍数")
extern CString g_sLangID_LowVol_VolEnd;            //_T("LowVol_VolEnd")
extern CString g_sLangTxt_LowVol_VolEnd;            //_T("电压结束值(V)")
extern CString g_sLangID_LowVol_OtherPara;            //_T("LowVol_OtherPara")
extern CString g_sLangTxt_LowVol_OtherPara;            //_T("其他参数")
extern CString g_sLangID_LowVol_SteadyCur;            //_T("LowVol_SteadyCur")
extern CString g_sLangTxt_LowVol_SteadyCur;            //_T("稳态电流(A)")
extern CString g_sLangID_LowVol_Exegesis;            //_T("LowVol_Exegesis")
extern CString g_sLangTxt_LowVol_Exegesis;            //_T("注:" 低压减载动作值"测试项使用")
extern CString g_sLangID_Diff_BorderSearch;            //_T("Diff_BorderSearch")
extern CString g_sLangTxt_Diff_BorderSearch;            //_T("比例制动边界搜索")
extern CString g_sLangID_Diff_Section;            //_T("Diff_Section")
extern CString g_sLangTxt_Diff_Section;            //_T("区段")
extern CString g_sLangID_Diff_Expression;            //_T("Diff_Expression")
extern CString g_sLangTxt_Diff_Expression;            //_T("公式")
extern CString g_sLangID_Diff_StraightLine;            //_T("Diff_StraightLine")
extern CString g_sLangTxt_Diff_StraightLine;            //_T("直线")
extern CString g_sLangID_Diff_InSet;            //_T("Diff_InSet")
extern CString g_sLangTxt_Diff_InSet;            //_T("基准电流(其它)")
extern CString g_sLangID_Diff_CombinedFeature;            //_T("Diff_CombinedFeature")
extern CString g_sLangTxt_Diff_CombinedFeature;            //_T("复合特性")
extern CString g_sLangID_Diff_ZeroSeqElimiType;            //_T("Diff_ZeroSeqElimiType")
extern CString g_sLangTxt_Diff_ZeroSeqElimiType;            //_T("零序消除方式")
extern CString g_sLangID_Diff_Setting;            //_T("Diff_Setting")
extern CString g_sLangTxt_Diff_Setting;            //_T("整定定值")
extern CString g_sLangID_Diff_Custom;            //_T("Diff_Custom")
extern CString g_sLangTxt_Diff_Custom;            //_T("自定义")
extern CString g_sLangID_Diff_TypeSel;            //_T("Diff_TypeSel")
extern CString g_sLangTxt_Diff_TypeSel;            //_T("选择类型")
extern CString g_sLangID_Native_ThirdPart;		//=_T("Native_ThirdPart");
extern CString g_sLangTxt_Native_ThirdPart;		//=_T("第三段");
extern CString g_sLangID_Diff_QuickBreak;            //_T("Diff_QuickBreak")
extern CString g_sLangTxt_Diff_QuickBreak;            //_T("速断")
extern CString g_sLangID_Native_InflectionPoint3;	// = _T("Native_InflectionPoint3")
extern CString g_sLangTxt_Native_InflectionPoint3; // = _T("拐点3")
extern CString g_sLangID_Diff_QuickBreakVal;            //_T("Diff_QuickBreakVal")
extern CString g_sLangTxt_Diff_QuickBreakVal;            //_T("速断")
extern CString g_sLangID_Diff_CurrChar;            //_T("Diff_CurrChar")
extern CString g_sLangTxt_Diff_CurrChar;            //_T("当前曲线")
extern CString g_sLangID_Diff_ZAdjust;            //_T("Diff_ZAdjust")
extern CString g_sLangTxt_Diff_ZAdjust;            //_T("Z侧校正")
extern CString g_sLangID_Diff_Result;            //_T("Diff_Result")
extern CString g_sLangTxt_Diff_Result;            //_T("测试结果")
extern CString g_sLangID_Diff_IdTheory;            //_T("Diff_IdTheory")
extern CString g_sLangTxt_Diff_IdTheory;            //_T("理论值Id")
extern CString g_sLangID_Diff_FaultType2;            //_T("Diff_FaultType2")
extern CString g_sLangTxt_Diff_FaultType2;            //_T("故障相")
extern CString g_sLangID_Diff_Select;            //_T("Diff_Select")
extern CString g_sLangTxt_Diff_Select;            //_T("选择")
extern CString g_sLangID_Diff_ActualVal;            //_T("Diff_ActualVal")
extern CString g_sLangTxt_Diff_ActualVal;            //_T("有名值")
extern CString g_sLangID_Diff_HSecondaryCur;            //_T("Diff_HSecondaryCur")
extern CString g_sLangTxt_Diff_HSecondaryCur;            //_T("高侧额定二次电流")
extern CString g_sLangID_Diff_CurrSet;            //_T("Diff_CurrSet")
extern CString g_sLangTxt_Diff_CurrSet;            //_T("设定值")
extern CString g_sLangID_Diff_EverySecondaryCur;            //_T("Diff_EverySecondaryCur")
extern CString g_sLangTxt_Diff_EverySecondaryCur;            //_T("各侧二次额定电流")

#endif // _XLangResource_Native_h__
