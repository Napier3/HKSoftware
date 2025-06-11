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
extern CString g_sLangID_Native_ReportHeadSet;//����ͷ����
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
extern CString g_sLangID_Harm_InterHarm;//��г��
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
// extern CString g_sLangID_Native_Bin;
//extern CString g_sLangTxt_Native_Bin;
// extern CString g_sLangID_Native_Bout;
//extern CString g_sLangTxt_Native_Bout;
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
//extern CString g_sLangID_Manual_TestReport;
//extern CString g_sLangTxt_Manual_TestReport;
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
extern CString g_sLangID_State_ShortU_kV;
extern CString g_sLangTxt_State_ShortU_kV;
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


//extern CString g_sLangID_State_SettingValue;//����ֵ
//extern CString g_sLangTxt_State_SettingValue;

extern CString g_sLangID_State_Estimate;//�������������
extern CString g_sLangTxt_State_Estimate;
extern CString g_sLangID_State_InState ;//����״̬
extern CString g_sLangTxt_State_InState ;

//������������� ���

extern CString g_sLangID_StateEstimate_Start ;//��ʱ���
extern CString g_sLangTxt_StateEstimate_State ;
extern CString g_sLangID_StateEstimate_End ;//��ʱ�յ�
extern CString g_sLangTxt_StateEstimate_End ;
extern CString g_sLangID_StateEstimate_ErrorType ;//�������
extern CString g_sLangTxt_StateEstimate_ErrorType ;
extern CString g_sLangID_StateEstimate_RelError ;//������
extern CString g_sLangTxt_StateEstimate_RelError ;
extern CString g_sLangID_StateEstimate_RelError_Percent ;//������(��)
extern CString g_sLangTxt_StateEstimate_RelError_Percent ;
extern CString g_sLangID_StateEstimate_AbsError ;//�������
extern CString g_sLangTxt_StateEstimate_AbsError ;
extern CString g_sLangID_StateEstimate_AbsError_Neg ;//�������(-)
extern CString g_sLangTxt_StateEstimate_AbsError_Neg ;
extern CString g_sLangID_StateEstimate_SettingValue ;//����ֵ(s)
extern CString g_sLangTxt_StateEstimate_SettingValue ;
extern CString g_sLangID_StateEstimate_BinTrigger ;//���봥��
extern CString g_sLangTxt_StateEstimate_BinTrigger ;

extern CString g_sLangID_StateEstimate_CombinationError ;//������
extern CString g_sLangTxt_StateEstimate_CombinationError ;

extern CString g_sLangID_StateEstimate_ResultEstimate;//�������
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
extern CString g_sLangTxt_Native_GroundDisSetV;//�ӵؾ��붨ֵ��1-5�Σ�GroundDisSet

//δ���� LCQ 
//extern  CString g_sLangID_State_NoActioned;
//extern  CString g_sLangTxt_State_NoActioned;
//����ֵ LCQ 
extern  CString g_sLangID_State_ActionValue;
extern  CString g_sLangTxt_State_ActionValue;
//��� LCQ 
extern  CString g_sLangID_State_Error;
extern  CString g_sLangTxt_State_Error;
//г������ LCQ
extern  CString g_sLangID_State_HarContent;
extern  CString g_sLangTxt_State_HarContent;
//�����
extern  CString g_sLangID_State_DifferentCur;
extern  CString g_sLangTxt_State_DifferentCur;
//�ƶ�����
extern  CString g_sLangID_State_BrakingCur;
extern  CString g_sLangTxt_State_BrakingCur;
//��ѹ��ֵ
extern  CString g_sLangID_State_VoltageRat;
extern  CString g_sLangTxt_State_VoltageRat;

//�迹ֵ(Z)
extern  CString g_sLangID_State_ZImpValue;
extern  CString g_sLangTxt_State_ZImpValue;
//�Ƕ�(��)
extern  CString g_sLangID_State_DAngle;
extern  CString g_sLangTxt_State_DAngle;
//������ֵ
extern  CString g_sLangID_State_CurrentRat;
extern  CString g_sLangTxt_State_CurrentRat;


//ϵͳ����  LCQ                                         
extern  CString g_sLangID_State_Sysgenerated;
extern  CString g_sLangTxt_State_Sysgenerated;
//�������߲���ʧ��(strCharaID=%s;strIndex=%s),�޷�������Ŀ�б�.LCQ
extern  CString g_sLangID_State_CurlfailedItems;
extern  CString g_sLangTxt_State_CurlfailedItems;

//��������    LCQ                                                
extern  CString g_sLangID_State_Difflowcalculation;
extern  CString g_sLangTxt_State_Difflowcalculation;
//״̬��CString��    LCQ
extern CString g_sLangID_State_StatusEdition;
extern CString g_sLangTxt_State_StatusEdition;											
//г������ֵ�ݱ�   LCQ
extern  CString g_sLangID_State_HarmonicAmpInc;
extern  CString g_sLangTxt_State_HarmonicAmpInc;
//г�����ٷֱȵݱ�   LCQ
extern  CString g_sLangID_State_HarmonicAmpPer;
extern  CString g_sLangTxt_State_HarmonicAmpPer;
//��һ״̬   lCQ
extern  CString g_sLangID_State_PreviosState;
extern  CString g_sLangTxt_State_PreviosState;
//��һ״̬  lCQ
extern  CString g_sLangID_State_NextState;
extern  CString g_sLangTxt_State_NextState;
//�ǵݱ�ͨ����������  LCQ
extern  CString g_sLangID_Gradient_Npchannelgroupset;
extern  CString g_sLangTxt_Gradient_Npchannelgroupset;
//��������  LCQ
extern  CString g_sLangID_Gradient_Groupset;
extern  CString g_sLangTxt_Gradient_Groupset;

//ʮ����
extern  CString g_sLangID_State_12Oclock;  
extern  CString g_sLangTxt_State_12Oclock;

//������
extern  CString g_sLangID_Native_Toolbar;  
extern  CString g_sLangTxt_Native_Toolbar;

//��һ��LCQ
extern  CString g_sLangID_Manual_FirGroup;  
extern  CString g_sLangTxt_Manual_FirGroup;
//����
extern  CString g_sLangID_State_Test;   
extern  CString g_sLangTxt_State_Test;
//����
extern  CString g_sLangID_State_Description;  
extern  CString g_sLangTxt_State_Description;
//״̬��
extern  CString g_sLangID_State_Statusname;  
extern  CString g_sLangTxt_State_Statusname;
//4G������������ʹ��
extern  CString g_sLangID_State_FGBlueNetworkcar;  
extern  CString g_sLangTxt_State_FGBlueNetworkcar;
//����
extern  CString g_sLangID_State_Bluetooth;  
extern  CString g_sLangTxt_State_Bluetooth;
//��������
extern  CString g_sLangID_State_Wirelesscard;  
extern  CString g_sLangTxt_State_Wirelesscard;
//��������
extern  CString g_sLangID_State_NativeNetworkcard;  
extern  CString g_sLangTxt_State_NativeNetworkcard;
//��Ļ����
extern  CString g_sLangID_State_MinScreenBright;  
extern  CString g_sLangTxt_State_MinScreenBright;
//(��ע:5��������)
extern  CString g_sLangID_State_NoteFivemeansBrightest;  
extern  CString g_sLangTxt_State_NoteFivemeansBrightest;
//����ʱ��(����)
extern  CString g_sLangID_State_MinBacklighttime;  
extern  CString g_sLangTxt_State_MinBacklighttime;
//(��ע:0������)
extern  CString g_sLangID_State_NoteZeromeansAlwayson;  
extern  CString g_sLangTxt_State_NoteZeromeansAlwayson;
//(����ɢ�ȷ���ģʽ)
extern  CString g_sLangID_State_FanMode;  
extern  CString g_sLangTxt_State_FanMode;
//("(����)")
extern  CString g_sLangID_State_Normal;
extern  CString g_sLangTxt_State_Normal;
//("(����)")
extern  CString g_sLangID_State_Mute;
extern  CString g_sLangTxt_State_Mute;
//ʱ������
extern  CString g_sLangID_State_Timezonesetting;  
extern  CString g_sLangTxt_State_Timezonesetting;
//��������
extern  CString g_sLangID_State_Othersettings;  
extern  CString g_sLangTxt_State_Othersettings;
//����ֵ
extern  CString g_sLangID_State_Datavalue;  
extern  CString g_sLangTxt_State_Datavalue;
//����ֱ������
extern  CString g_sLangID_State_AuxiliaryDCSettings;  
extern  CString g_sLangTxt_State_AuxiliaryDCSettings;
//����
extern  CString g_sLangID_State_Others;  
extern  CString g_sLangTxt_State_Others;
//��ѹֵ(V):
extern  CString g_sLangID_State_Voltagevalue;  
extern  CString g_sLangTxt_State_Voltagevalue;
//"���Ժ�,�ѿ�ʼ"
extern CString g_sLangID_Gradient_Pleaselaterithasstarted;
extern CString g_sLangTxt_Gradient_Pleaselaterithasstarted;
//ɨ���߶�lcq 3.13
extern  CString g_sLangID_State_Scanlinesegments;  
extern  CString g_sLangTxt_State_Scanlinesegments;
//���Ե�lcq 3.13
extern  CString g_sLangID_State_Testpoints;  
extern  CString g_sLangTxt_State_Testpoints;
//����(Ie)lcq 3.13
extern  CString g_sLangID_State_Iecurrent;  
extern  CString g_sLangTxt_State_Iecurrent;
//����(A)lcq 3.13
extern  CString g_sLangID_State_Acurrent;  
extern  CString g_sLangTxt_State_Acurrent;

//г�� lcq 3.13
extern  CString g_sLangID_State_Harmonicwave;  
extern  CString g_sLangTxt_State_Harmonicwave;
//��ֵ�� lcq 3.13
extern  CString g_sLangID_State_Interpolation;  
extern  CString g_sLangTxt_State_Interpolation;
//ͬ���� lcq 3.13
extern  CString g_sLangID_State_Synchronousmethod;  
extern  CString g_sLangTxt_State_Synchronousmethod;
//�����߼� lcq 3.13
extern  CString g_sLangID_State_TestLogic;  
extern  CString g_sLangTxt_State_TestLogic;
//��������Ч lcq 3.13
extern  CString g_sLangID_State_Risingedgeeffective;  
extern  CString g_sLangTxt_State_Risingedgeeffective;
//�½�����Ч lcq 3.13
extern  CString g_sLangID_State_Downedgeeffective;  
extern  CString g_sLangTxt_State_Downedgeeffective;
//��PPS lcq 3.13
extern  CString g_sLangID_State_NOPPS;  
extern  CString g_sLangTxt_State_NOPPS;
//PPS���� lcq 3.13
extern  CString g_sLangID_State_PPSsettings;  
extern  CString g_sLangTxt_State_PPSsettings;
//��PPS��ʱ����(��s) lcq 3.13
extern  CString g_sLangID_State_UsNoPPSdelaycompensation;  
extern  CString g_sLangTxt_State_UsNoPPSdelaycompensation;
//ͬ��ʱ��(s): lcq 3.13
extern  CString g_sLangID_State_SSyncduration;  
extern  CString g_sLangTxt_State_SSyncduration;
//��ǰ���(��s): lcq 3.13
extern  CString g_sLangID_State_UsCurrenterror;  
extern  CString g_sLangTxt_State_UsCurrenterror;
//������(��s): lcq 3.13
extern  CString g_sLangID_State_UsMaximumerror;  
extern  CString g_sLangTxt_State_UsMaximumerror;
//��С���(��s): lcq 3.13
extern  CString g_sLangID_State_UsMinimumerror;  
extern  CString g_sLangTxt_State_UsMinimumerror;
//��ע  lcq 3.13
extern  CString g_sLangID_State_Remark;  
extern  CString g_sLangTxt_State_Remark;
//��ʱʱ��(s):  lcq 3.13 
extern  CString g_sLangID_State_SPunctuality;  
extern  CString g_sLangTxt_State_SPunctuality;
//ͨ������ģ���ļ� lcq 3.14 
extern  CString g_sLangID_State_Genexperfile;
extern  CString g_sLangTxt_State_Genexperfile;
//Goose�쳣ģ��ģ���ļ� lcq 3.14
extern  CString g_sLangID_State_Gooseexfile;
extern  CString g_sLangTxt_State_Gooseexfile;
//GOOSE���Ĳ���  lcq 3.14
extern  CString g_sLangID_State_GOOSEmessageparameters;
extern  CString g_sLangTxt_State_GOOSEmessageparameters;
//����ֵ���зǷ��ַ�. lcq 3.14
extern  CString g_sLangID_State_IlleInputCharac;
extern  CString g_sLangTxt_State_IlleInputCharac;

//��֡ lcq 3.14
extern  CString g_sLangID_State_Dropframes;
extern  CString g_sLangTxt_State_Dropframes;
//�ɵ� lcq 3.14
extern  CString g_sLangID_State_Flypoint;
extern  CString g_sLangTxt_State_Flypoint;
//���� lcq 3.14
extern  CString g_sLangID_State_Dithering;
extern  CString g_sLangTxt_State_Dithering;
//���� lcq 3.14
extern  CString g_sLangID_State_OutofOrder;
extern  CString g_sLangTxt_State_OutofOrder;
//��ѹ���� lcq 3.14
extern  CString g_sLangID_State_VoltageandCurrent;
extern  CString g_sLangTxt_State_VoltageandCurrent;
//״̬����ģ���ļ� lcq 3.14
extern  CString g_sLangID_State_StateSequencefile;
extern  CString g_sLangTxt_State_StateSequencefile;
//SV�쳣ģ��  lcq 3.14
extern  CString g_sLangID_State_SVexceptionSimulation;
extern  CString g_sLangTxt_State_SVexceptionSimulation;
//״̬��Ŀ���ܳ���%d  lcq 3.14
extern  CString g_sLangID_State_NumnotExceed;
extern  CString g_sLangTxt_State_NumnotExceed;
//��ǰѭ��  lcq 3.14
extern  CString g_sLangID_State_TheCurrentLoop;
extern  CString g_sLangTxt_State_TheCurrentLoop;
//����    lcq 3.14
extern  CString g_sLangID_State_Enter;
extern  CString g_sLangTxt_State_Enter;
//����ĵ�ѹ������Χ lcq 3.14
extern  CString g_sLangID_State_InVolOutofRange;
extern  CString g_sLangTxt_State_InVolOutofRange;
//����ĵ���������Χ lcq 3.14
extern  CString g_sLangID_State_InCurOutofrange;
extern  CString g_sLangTxt_State_InCurOutofrange;
//%1��г�� lcq 3.14
extern  CString g_sLangID_State_TheOnepercentHarmonic;
extern  CString g_sLangTxt_State_TheOnepercentHarmonic;
//г������ģ���ļ� lcq 3.14
extern  CString g_sLangID_State_HarmonicTestTemplatefile;
extern  CString g_sLangTxt_State_HarmonicTestTemplatefile;
//�ݱ�����ģ���ļ�  lcq 3.14
extern  CString g_sLangID_State_IncreExperfile;
extern  CString g_sLangTxt_State_IncreExperfile;
//TestCtrlCntrLinux�������� lcq 3.14
extern  CString g_sLangID_State_TBuildDate;
extern  CString g_sLangTxt_State_TBuildDate;
//"IEEE���߲�������"  lcq 3.14
extern  CString g_sLangID_State_IEEECurset;
extern  CString g_sLangTxt_State_IEEECurset;
//"IAC���߲�������"  lcq 3.14
extern  CString g_sLangID_State_IACCurSet;
extern  CString g_sLangTxt_State_IACCurSet;
//"I2T���߲�������"  lcq 3.14
extern  CString g_sLangID_State_I2TCurSet;
extern  CString g_sLangTxt_State_I2TCurSet;
//"IEC���߲�������"  lcq 3.14
extern  CString g_sLangID_State_IECCurSet;
extern  CString g_sLangTxt_State_IECCurSet;
//"��ѹ��ʱ�޲�������"  lcq 3.14
extern  CString g_sLangID_State_VolLimitSet;
extern  CString g_sLangTxt_State_VolLimitSet;
//�Ŵ� lcq 3.14
extern  CString g_sLangID_State_Magnify;
extern  CString g_sLangTxt_State_Magnify;
//��С lcq 3.14
extern  CString g_sLangID_State_Shrink;
extern  CString g_sLangTxt_State_Shrink;
//ɸѡ
extern  CString g_sLangID_IECConfig_Screen;	
extern  CString g_sLangTxt_IECConfig_Screen; 
//��λ lcq 3.14
extern  CString g_sLangID_State_Reposition;
extern  CString g_sLangTxt_State_Reposition;
//��ֱ(FT3)  lcq 3.14
extern  CString g_sLangID_State_FThreeStraight;
extern  CString g_sLangTxt_State_FThreeStraight;
//�����迹 lcq 3.15
extern  CString g_sLangID_State_SinglephaseImpedance;
extern  CString g_sLangTxt_State_SinglephaseImpedance;
//" ��  �� "   lcq 3.15
extern  CString g_sLangID_State_Coincidence;
extern  CString g_sLangTxt_State_Coincidence;
//" �� �� �� " lcq 3.15
extern  CString g_sLangID_State_RearAcceleration;
extern  CString g_sLangTxt_State_RearAcceleration;
//�汾��Ϣ   lcq 3.15
extern  CString g_sLangID_State_VersionInformation;
extern  CString g_sLangTxt_State_VersionInformation;
//װ������   lcq 3.15
extern  CString g_sLangID_State_ApplianceProperties;
extern  CString g_sLangTxt_State_ApplianceProperties;
//"�ͺ�:"    lcq 3.15
extern  CString g_sLangID_State_AppModel;
extern  CString g_sLangTxt_State_AppModel;
//"���:"    lcq 3.15
extern  CString g_sLangID_State_AppNumber;
extern  CString g_sLangTxt_State_AppNumber;
//"ģ�����"   lcq 3.15
extern  CString g_sLangID_State_ModuleManagement;
extern  CString g_sLangTxt_State_ModuleManagement;
//���COMTRADE�����ļ� lcq 3.15
extern  CString g_sLangID_State_POpenCFile;
extern  CString g_sLangTxt_State_POpenCFile;

//�������߱�Ԫ�� lcq 3.15
extern  CString g_sLangID_State_CharCurEdgeElements;
extern  CString g_sLangTxt_State_CharCurEdgeElements;
//"��Ԫ������" lcq 3.15
extern  CString g_sLangID_State_TheEdgeElementType;
extern  CString g_sLangTxt_State_TheEdgeElementType;
//�������� lcq 3.15
extern  CString g_sLangID_State_ErrorBandLength;
extern  CString g_sLangTxt_State_ErrorBandLength;
//�߲��Ե��� lcq 3.15
extern  CString g_sLangID_State_EdgeTestPoints;
extern  CString g_sLangTxt_State_EdgeTestPoints;
//��ʼ��-R  lcq 3.15
extern  CString g_sLangID_State_startingPointR;
extern  CString g_sLangTxt_State_startingPointR;
//��ʼ��-X  lcq 3.15
extern  CString g_sLangID_State_startingPointX;
extern  CString g_sLangTxt_State_EdgeTestPointX;
//��ֹ��-R  lcq 3.15
extern  CString g_sLangID_State_EndPointR;
extern  CString g_sLangTxt_State_EndPointR;
//��ֹ��-X   lcq 3.15
extern  CString g_sLangID_State_EndPointX;
extern  CString g_sLangTxt_State_EndPointX;
//����  lcq 3.15
extern  CString g_sLangID_State_Direction;
extern  CString g_sLangTxt_State_Direction;
//���򵽴�  lcq 3.15
extern  CString g_sLangID_State_PositiveArrival;
extern  CString g_sLangTxt_State_PositiveArrival;
//�Ƕ�  lcq 3.15
extern  CString g_sLangID_State_ANgle;
extern  CString g_sLangTxt_State_ANgle;
//ƫ��  lcq 3.15
extern  CString g_sLangID_State_Offset;
extern  CString g_sLangTxt_State_Offset;
//���  lcq 3.15
extern  CString g_sLangID_State_Width;
extern  CString g_sLangTxt_State_Width;
//x-Բ��  lcq 3.15
extern  CString g_sLangID_State_CenterX;
extern  CString g_sLangTxt_State_CenterX;
//y-Բ��  lcq 3.15
extern  CString g_sLangID_State_CenterY;
extern  CString g_sLangTxt_State_CenterY;
//�뾶  lcq 3.15
extern  CString g_sLangID_State_Radius;
extern  CString g_sLangTxt_State_Radius;
//��ʼ�Ƕ�  lcq 3.15
extern  CString g_sLangID_State_StartingAngle;
extern  CString g_sLangTxt_State_StartingAngle;
//��ֹ�Ƕ� lcq 3.15
extern  CString g_sLangID_State_TerminationAngle;
extern  CString g_sLangTxt_State_TerminationAngle;
//ʱ�ӷ���  lcq 3.15
extern  CString g_sLangID_State_ClockDirection;
extern  CString g_sLangTxt_State_ClockDirection;
//��ѹ���� lcq 3.20
extern  CString g_sLangID_State_LowVoltageprotection;
extern  CString g_sLangTxt_State_LowVoltageprotection;
//��ѹ���� lcq 3.20
extern  CString g_sLangID_State_Overvoltageprotection;
extern  CString g_sLangTxt_State_Overvoltageprotection;
//г���ƶ�ϵ�� lcq 3.20
extern  CString g_sLangID_State_HarmonicBrakingcoefficient;
extern  CString g_sLangTxt_State_HarmonicBrakingcoefficient;
//г���ƶ� lcq 3.20
extern  CString g_sLangID_State_Harmonicbraking;
extern  CString g_sLangTxt_State_Harmonicbraking;
//Ӳ����Ϣ���� lcq 3.15
extern  CString g_sLangID_State_HardwareInformationSettings;
extern  CString g_sLangTxt_State_HardwareInformationSettings;
//����ֵ%f������Χ(%d).
extern  CString g_sLangID_State_EnterTheValueoutofRange;     
extern  CString g_sLangTxt_State_EnterTheValueoutofRange;    


//(UTC-12:00)�������ڱ������ lcq 3.15
extern  CString g_sLangID_State_UTC_TwelveWIntDLine;
extern  CString g_sLangTxt_State_UTC_TwelveWIntDLine;

//UTC-11:00)Э������ʱ-11; lcq 3.15
extern  CString g_sLangID_State_UTC_ElevenCUTime;
extern  CString g_sLangTxt_State_UTC_ElevenCUTime;

//"(UTC-10:00)������Ⱥ��"; lcq 3.15
extern  CString g_sLangID_State_UTC_TenAleutianIslands;
extern  CString g_sLangTxt_State_UTC_TenAleutianIslands;

//(UTC-9:00)����˹��; lcq 3.15
extern  CString g_sLangID_State_UTC_NineAlaska;
extern  CString g_sLangTxt_State_UTC_NineAlaska;

//("(UTC-8:00)̫ƽ��ʱ��(�����ͼ��ô�)")); lcq 3.15
extern  CString g_sLangID_State_UTC_EUCPacificTime;
extern  CString g_sLangTxt_State_UTC_EUCPacificTime;

//("(UTC-7:00)������,����˹,��������")); lcq 3.15
extern  CString g_sLangID_State_UTC_SevenCLM;
extern  CString g_sLangTxt_State_UTC_SevenCLM;

//("(UTC-6:00)������")); lcq 3.15
extern  CString g_sLangID_State_UTC_SixCentralAmerica;
extern  CString g_sLangTxt_State_UTC_SixCentralAmerica;

//("(UTC-5:00)����ʱ��(�����ͼ��ô�)")); lcq 3.15
extern  CString g_sLangID_State_UTC_FiveUCEasternTime;
extern  CString g_sLangTxt_State_UTC_FiveUCEasternTime;

//("(UTC-4:00)������ʱ��(���ô�)")); lcq 3.15
extern  CString g_sLangID_State_UTC_FourCanadaAtlanticTime;
extern  CString g_sLangTxt_State_UTC_FourCanadaAtlanticTime;

//("(UTC-3:00)������")); lcq 3.15
extern  CString g_sLangID_State_UTC_ThreeGreenland;
extern  CString g_sLangTxt_State_UTC_ThreeGreenland;

//("(UTC-2:00)Э������ʱ-2")); lcq 3.15
extern  CString g_sLangID_State_UTC_TwoCooUniversalTime;
extern  CString g_sLangTxt_State_UTC_TwoCooUniversalTime;

//("(UTC-1:00)��ý�Ⱥ��,���ٶ�Ⱥ��"));lcq 3.15
extern  CString g_sLangID_State_UTC_OneCapIslandsAzores;
extern  CString g_sLangTxt_State_UTC_OneCapIslandsAzores;

//("(UTC)������,������,��˹��,�׶�")); lcq 3.15
extern  CString g_sLangID_State_UTC_DubEdinhLisLon;
extern  CString g_sLangTxt_State_UTC_DubEdinhLisLon;

//("(UTC+1:00)��³����,�籾����,�����,����,�з�����")); lcq 3.15
extern  CString g_sLangID_State_UTC_POneBCMPWAfrica;
extern  CString g_sLangTxt_State_UTC_POneBCMPWAfrica;

//("(UTC+2:00)����,�ŵ�,Ү·����")); lcq 3.15
extern  CString g_sLangID_State_UTC_PTwoCAJerusalem;
extern  CString g_sLangTxt_State_UTC_PTwoCAJerusalem;

//("(UTC+3:00)�͸��,������,Ī˹��,ʥ�˵ñ�")); lcq 3.15
extern  CString g_sLangID_State_UTC_PThreeBKMPeterby;
extern  CString g_sLangTxt_State_UTC_PThreeBKMPeterby;

//("(UTC+4:00)��������,�Ϳ�")); lcq 3.15
extern  CString g_sLangID_State_UTC_PFourAbuDhabiBaku;
extern  CString g_sLangTxt_State_UTC_PFourAbuDhabiBaku;

//("(UTC+5:00)��˹����,������")); lcq 3.15
extern  CString g_sLangID_State_UTC_PFiveIslamabadKarachi;
extern  CString g_sLangTxt_State_UTC_PFiveIslamabadKarachi;

//("(UTC+6:00)��˹����")); lcq 3.15
extern  CString g_sLangID_State_UTC_PSixAstana;
extern  CString g_sLangTxt_State_UTC_PSixAstana;

//("(UTC+7:00)����,����,�żӴ�")); lcq 3.15
extern  CString g_sLangID_State_UTC_PSevenBHJakarta;
extern  CString g_sLangTxt_State_UTC_PSevenBHJakarta;

//("(UTC+8:00)����,����,���,��³ľ��")); lcq 3.15
extern  CString g_sLangID_State_UTC_PEightBCHUrumqi;
extern  CString g_sLangTxt_State_UTC_PEightBCHUrumqi;

//("(UTC+9:00)����,�׶�,ƽ��")); lcq 3.15
extern  CString g_sLangID_State_UTC_PNineTSPyongyang;
extern  CString g_sLangTxt_State_UTC_PNineTSPyongyang;

//("(UTC+10:00)������,ī����,Ϥ��")); lcq 3.15
extern  CString g_sLangID_State_UTC_PTenCMSydney;
extern  CString g_sLangTxt_State_UTC_PTenCMSydney;

//("(UTC+11:00)������Ⱥ��,�¿��������")); lcq 3.15
extern  CString g_sLangID_State_UTC_PSINCaledonia;
extern  CString g_sLangTxt_State_UTC_PSINCaledonia;

//("(UTC+12:00)쳼�")); lcq 3.15
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
//�ܼ�ֻ��ѡ��%d��г����������ѡ��ǰ��г������Ҫȡ����ѡһ��.
extern CString g_sLangID_Gradient_Intotalcheckarow;
extern CString g_sLangTxt_Gradient_Intotalcheckarow;

//��ǰ��������Ϊ(%ld),������Ҫ2��������ܽ��в�������. lcq 3.13
extern CString g_sLangID_Gradient_CurbanksatleastTwo;
extern CString g_sLangTxt_Gradient_CurbanksatleastTwo;

//��ǰѡ��ĵݱ�ͨ��(Index=%d)δ���ҵ�.lcq 3.13
extern CString g_sLangID_Gradient_CurselinNotFound;
extern CString g_sLangTxt_Gradient_CurselinNotFound;

//��ǰΪֱ�����ģʽ,�����л�ΪƵ�ʵݱ�.lcq 3.13
extern CString g_sLangID_Gradient_CurinDCincrement;
extern CString g_sLangTxt_Gradient_CurinDCincrement;

//��ע:���Ҫ�����ʱ��1���ӣ�����ʱ������1��s. lcq 3.13
extern CString g_sLangID_Gradient_NoteThepthanoneus;
extern CString g_sLangTxt_Gradient_NoteThepthanoneus;

//��ע:���Ҫ�����ʱ��10���ӣ������ʱ������4��s. lcq 3.13
extern CString g_sLangID_Gradient_NoteThepthanfourus;
extern CString g_sLangTxt_Gradient_NoteThepthanfourus;

//��PPSģʽ��,��Ҫ�Ƚ��б���̽��,ѡ���Ӧ����ֵ���ƿ�. lcq 3.14
extern CString g_sLangID_Gradient_InPPSfreemodevaluecontrolblock;
extern CString g_sLangTxt_Gradient_InPPSfreemodevaluecontrolblock;

//��ǰ״̬(%d)��GOOSE��������Ϊ��(�����쳣).lcq 3.14
extern CString g_sLangID_Gradient_GOOSEreleaseDataStatusIsempty;
extern CString g_sLangTxt_Gradient_GOOSEreleaseDataStatusIsempty;

//���ٱ���һ��״̬.lcq 3.14
extern CString g_sLangID_Gradient_MaintainatLeastOneState;
extern CString g_sLangTxt_Gradient_MaintainatLeastOneState;

//"�ܼ�ֻ��ѡ��%d��г����������ѡ��ǰ��г������Ҫȡ����ѡһ��."  lcq 3.14
extern CString g_sLangID_Gradient_Intotalharmonicuncheckarow;
extern CString g_sLangTxt_Gradient_Intotalharmonicuncheckarow;

//����ʹ�õ������ļ�(%s)������. lcq 3.14
extern CString g_sLangID_Gradient_TheUsedfordebuggingNOexist;
extern CString g_sLangTxt_Gradient_TheUsedfordebuggingNOexist;

//�������ܲ��Բ����ļ���%s��ʧ��  lcq 3.14
extern CString g_sLangID_Gradient_FailedTestParameterfile;
extern CString g_sLangTxt_Gradient_FailedTestParameterfile;

//�����ļ��� lcq 3.14
extern CString g_sLangID_Gradient_CreateFolder;
extern CString g_sLangTxt_Gradient_CreateFolder;

//�ļ��д���ʧ�ܣ� Folder creation failed! lcq 3.14
extern CString g_sLangID_Gradient_FolderCreationFailed;
extern CString g_sLangTxt_Gradient_FolderCreationFailed;

//������� lcq 3.14
extern CString g_sLangID_Gradient_AddExperiment;
extern CString g_sLangTxt_Gradient_AddExperiment;
 
//ȱ��Ӳ����Դ�ļ�,�޷�����ȱʡͨ��ӳ��.  lcq 3.14
extern CString g_sLangID_Gradient_MissingDefaultMappings;
extern CString g_sLangTxt_Gradient_MissingDefaultMappings;

//"����ͨ��ӳ��ȱʡ·��ʧ��."  lcq 3.14
extern CString g_sLangID_Gradient_FailDefaultPath;
extern CString g_sLangTxt_Gradient_FailDefaultPath;

//����ͨ��ӳ���ļ�[%s]�ɹ�.  lcq 3.14
extern CString g_sLangID_Gradient_ExportfileSucceeded;
extern CString g_sLangTxt_Gradient_ExportfileSucceeded;
 
//����ͨ��ӳ���ļ�[%s]ʧ��. lcq 3.14
extern CString g_sLangID_Gradient_Failedtofile;
extern CString g_sLangTxt_Gradient_Failedtofile;

//������Ӳ����Ϣ�ļ�����ʧ��. lcq 3.15
extern CString g_sLangID_Gradient_TheTesterfileFailedtoload;
extern CString g_sLangTxt_Gradient_TheTesterfileFailedtoload;

//δ֪����ҳ����ִ������(%s). lcq 3.20
extern CString g_sLangID_Gradient_UnknownCommand;
extern CString g_sLangTxt_Gradient_UnknownCommand;

//���ܲ��Բ����ļ���%s�������� lcq 3.20 
extern CString g_sLangID_Gradient_Functionalfiledtexist;
extern CString g_sLangTxt_Gradient_Functionalfiledtexist;

//"��ѡ" lcq 7.06
extern CString g_sLangID_Gradient_Inverse;
extern CString g_sLangTxt_Gradient_Inverse;

//"��ѹ����ֵ(V)" lcq 7.06 
extern CString g_sLangID_Gradient_VActionValue;
extern CString g_sLangTxt_Gradient_VActionValue;
//"��������ֵ(A)" lcq 7.06 
extern CString g_sLangID_Gradient_CActionValue;
extern CString g_sLangTxt_Gradient_CActionValue;
//"����ϵ��" lcq 7.06 
extern CString g_sLangID_Gradient_ReCoefficient;
extern CString g_sLangTxt_Gradient_ReCoefficient;
//"�߽��1(��)" lcq 7.06 
extern CString g_sLangID_Gradient_FirBoundAngle ;
extern CString g_sLangTxt_Gradient_FirBoundAngle;
//"�߽��2(��)" lcq 7.06
extern CString g_sLangID_Gradient_SecBoundAngle;
extern CString g_sLangTxt_Gradient_SecBoundAngle;
//"���������(��)" lcq 7.06 
extern CString g_sLangID_Gradient_MaxSenAngle;
extern CString g_sLangTxt_Gradient_MaxSenAngle;
//"����Ƶ��(Hz)" lcq 7.06  
extern CString g_sLangID_Gradient_FreAction;
extern CString g_sLangTxt_Gradient_FreAction;
//"��λ����ֵ(��)" lcq 7.06 
extern CString g_sLangID_Gradient_PhaseAValue;
extern CString g_sLangTxt_Gradient_PhaseAValue;
//"�迹����ֵ(��)"
extern CString g_sLangID_Gradient_ImpAValue;
extern CString g_sLangTxt_Gradient_ImpAValue;
//���Խ�ѧ lcq
extern CString g_sLangID_Gradient_TestTeach;
extern CString g_sLangTxt_Gradient_TestTeach;
//����ͷ��Ϣ  lcq
extern CString g_sLangID_Gradient_ReportHeader;
extern CString g_sLangTxt_Gradient_ReportHeader;
//"�·��������ģ��(%s%s)����ɹ�." lcq         
extern CString g_sLangID_Gradient_TestTempSusCom;
extern CString g_sLangTxt_Gradient_TestTempSusCom;
//"�·��������ģ��(%s%s)����ʧ��." lcq         
extern CString g_sLangID_Gradient_TestTempDefCom;
extern CString g_sLangTxt_Gradient_TestTempDefCom;
//"������ҳģ���ļ�(%s%s)�ɹ�."    lcq             
extern CString g_sLangID_Gradient_SavePageSus;
extern CString g_sLangTxt_Gradient_SavePageSus;
//"�·�������Լ�¼(%s%s)����ɹ�." lcq          
extern CString g_sLangID_Gradient_TestRecordSus;
extern CString g_sLangTxt_Gradient_TestRecordSus;
//"�·�������Լ�¼(%s%s)����ʧ��."  lcq             
extern CString g_sLangID_Gradient_TestRecordFai;
extern CString g_sLangTxt_Gradient_TestRecordFai;
//"���汨���ļ�(%s%s)�ɹ�." lcq                    
extern CString g_sLangID_Gradient_SaveReportSus;
extern CString g_sLangTxt_Gradient_SaveReportSus;
//"·��(%s)�´���ͬ�����ļ�,���޸��ļ���."  lcq
extern CString g_sLangID_Gradient_SameeXist; 
extern CString g_sLangTxt_Gradient_SameeXist;

//ģ������ Module type  lcq
extern CString g_sLangID_Gradient_ModuleType;  
extern CString g_sLangTxt_Gradient_ModuleType;
//λ�ú� Location number  lcq
extern CString g_sLangID_Gradient_LocNumber; 
extern CString g_sLangTxt_Gradient_LocNumber;
//ģ��汾 Module version  lcq
extern CString g_sLangID_Gradient_ModuleVersion; 
extern CString g_sLangTxt_Gradient_ModuleVersion;
 //�������� Date of manufacture lcq
extern CString g_sLangID_Gradient_ManufactDate; 
extern CString g_sLangTxt_Gradient_ManufactDate;

// �������� lcq
// extern CString g_sLangID_Gradient_InstrumentName; 
// extern CString g_sLangTxt_Gradient_InstrumentName;
// ����汾 lcq
// extern CString g_sLangID_Gradient_BoardVersion; 
// extern CString g_sLangTxt_Gradient_BoardVersion;
// �����汾 lcq
// extern CString g_sLangID_Gradient_DriverVersion; 
// extern CString g_sLangTxt_Gradient_DriverVersion;
// TestServer�汾 lcq
// extern CString g_sLangID_Gradient_TestSVersion; 
// extern CString g_sLangTxt_Gradient_TestSVersion;
// Linux�������� lcq
// extern CString g_sLangID_Gradient_LinuxBDate; 
// extern CString g_sLangTxt_Gradient_LinuxBDate;
// ���忪������������ lcq
// extern CString g_sLangID_Gradient_MboardsNumIn; 
// extern CString g_sLangTxt_Gradient_MboardsNumIn;
// ���忪������������ lcq
// extern CString g_sLangID_Gradient_MboardsNumOut; 
// extern CString g_sLangTxt_Gradient_MboardsNumOut;
// ģ����������λ����(��) lcq
// extern CString g_sLangID_Gradient_AAcompensation;  
// extern CString g_sLangTxt_Gradient_AAcompensation;
// ״̬�������� lcq
// extern CString g_sLangID_Gradient_SsCapacity; 
// extern CString g_sLangTxt_Gradient_SsCapacity;
// TestServer���� lcq
// extern CString g_sLangID_Gradient_TestSName; 
// extern CString g_sLangTxt_Gradient_TestSName;
// �������� lcq
// extern CString g_sLangID_Gradient_DriverName; 
// extern CString g_sLangTxt_Gradient_DriverName;
//"ģ��λ��" lcq
// extern CString g_sLangID_Gradient_ModLocation; 
// extern CString g_sLangTxt_Gradient_ModLocation;
// //"г����" lcq
// extern CString g_sLangID_Gradient_HarmonicsNum; 
// extern CString g_sLangTxt_Gradient_HarmonicsNum;
// //"ֱ����ѹͨ�����ֵ" lcq
// extern CString g_sLangID_Gradient_DCVolChaMax; 
// extern CString g_sLangTxt_Gradient_DCVolChaMax;
// //"ֱ������ͨ�����ֵ" lcq
// extern CString g_sLangID_Gradient_DCCurChaMax; 
// extern CString g_sLangTxt_Gradient_DCCurChaMax;
// //"ͨ�����������ֵ"  lcq
// extern CString g_sLangID_Gradient_ACChanMax; 
// extern CString g_sLangTxt_Gradient_ACChanMax;
// //"ͨ����ֱ�����ֵ" lcq
// extern CString g_sLangID_Gradient_DCChanMax; 
// extern CString g_sLangTxt_Gradient_DCChanMax;
// //"Ƶ�ʲ���ϵ��" lcq
// extern CString g_sLangID_Gradient_FreComFactor; 
// extern CString g_sLangTxt_Gradient_FreComFactor;
// //"����Ӳ����λ��ʱ" lcq
// extern CString g_sLangID_Gradient_DigDeLHardware; 
// extern CString g_sLangTxt_Gradient_DigDeLHardware;
// //"��ѹ����Ӳ������" Voltage and current hardware characteristics
// extern CString g_sLangID_Gradient_VCHardware; 
// extern CString g_sLangTxt_Gradient_VCHardware;
// //"����ͨ���ϲ�ģʽ" Current channel coalescing mode
// extern CString g_sLangID_Gradient_CCcoalescing; 
// extern CString g_sLangTxt_Gradient_CCcoalescing;
// //"��һ�鿪������Ϊ����" The first set of switches is configured for opening
// extern CString g_sLangID_Gradient_FirSwitchoPen; 
// extern CString g_sLangTxt_Gradient_FirSwitchoPen;
// //"�ڶ��鿪������Ϊ����" The second set of switches is configured as an inlet
// extern CString g_sLangID_Gradient_SecSwitchoPen; 
// extern CString g_sLangTxt_Gradient_SecSwitchoPen;
// //"�����鿪������Ϊ����" The third set of switches is configured for opening
// extern CString g_sLangID_Gradient_ThirSwitchoPen; 
// extern CString g_sLangTxt_Gradient_ThirSwitchoPen;
// //"�����鿪������Ϊ����" The fourth set of switches is configured for opening
// extern CString g_sLangID_Gradient_FourSwitchoPen; 
// extern CString g_sLangTxt_Gradient_FourSwitchoPen;
// //"ģ��FPGA�汾" Module FPGA version
// extern CString g_sLangID_Gradient_FPGAVersion; 
// extern CString g_sLangTxt_Gradient_FPGAVersion;
// //"ģ�����԰汾" Module property version
// extern CString g_sLangID_Gradient_ModproVersion; 
// extern CString g_sLangTxt_Gradient_ModproVersion;
// //"�����������������ɷ����޹�˾" 
// extern CString g_sLangID_Gradient_BodianEleCor; 
// extern CString g_sLangTxt_Gradient_BodianEleCor;



// SCD�ļ�
// extern CString g_sLangID_Gradient_SCDfile; 
// extern CString g_sLangTxt_Gradient_SCDfile;
// ģ���ļ� Template file
// extern CString g_sLangID_Gradient_TemplateFile; 
// extern CString g_sLangTxt_Gradient_TemplateFile;
// �����ļ��� Screenshots folder
// extern CString g_sLangID_Gradient_ScreenFolder; 
// extern CString g_sLangTxt_Gradient_ScreenFolder;
// "�������ͼƬ" Save the screencast
// extern CString g_sLangID_Gradient_SaveCast; 
// extern CString g_sLangTxt_Gradient_SaveCast;
// "���������ļ�"  Other types of files
// extern CString g_sLangID_Gradient_OtherTypeFile; 
// extern CString g_sLangTxt_Gradient_OtherTypeFile;




//"�����ɹ�."   lcq
extern CString g_sLangID_Gradient_ShotScreenSus; 
extern CString g_sLangTxt_Gradient_ShotScreenSus;
//��������IP lcq
extern CString g_sLangID_Gradient_LocalNICIP;
extern CString g_sLangTxt_Gradient_LocalNICIP;
//��IP��ַ��  lcq
extern CString g_sLangID_Gradient_PrimaryIP;
extern CString g_sLangTxt_Gradient_PrimaryIP;
//"������λ����:"  lcq
extern CString g_sLangID_Gradient_CurGSetting;
extern CString g_sLangTxt_Gradient_CurGSetting;
//"���������˿�:"  lcq
extern CString g_sLangID_Gradient_HighCurPort;
extern CString g_sLangTxt_Gradient_HighCurPort;
//"1��(0.2��/10A)" lcq
extern CString g_sLangID_Gradient_FirstFile;
extern CString g_sLangTxt_Gradient_FirstFile;
//"2��(0.3��/10A)" lcq
extern CString g_sLangID_Gradient_SecondFile;
extern CString g_sLangTxt_Gradient_SecondFile;
//"3��(0.7��/10A)" lcq
extern CString g_sLangID_Gradient_ThirdFile;
extern CString g_sLangTxt_Gradient_ThirdFile;
//"IEC����" lcq
extern CString g_sLangID_Gradient_IECConfiguration;
extern CString g_sLangTxt_Gradient_IECConfiguration;
//"��������" lcq
extern CString g_sLangID_Gradient_MessageType;
extern CString g_sLangTxt_Gradient_MessageType;
//"CRC����ѡ��"
extern CString g_sLangID_Gradient_CRCCheck;
extern CString g_sLangTxt_Gradient_CRCCheck;
//SCL��������  lcq
extern CString g_sLangID_Gradient_SCLPars;
extern CString g_sLangTxt_Gradient_SCLPars;
//��ѹ���� lcq
extern CString g_sLangID_Gradient_VoltageSet;
extern CString g_sLangTxt_Gradient_VoltageSet;
//�������� lcq
extern CString g_sLangID_Gradient_CurrentSet;
extern CString g_sLangTxt_Gradient_CurrentSet;
//"��ȡ�ļ�·��ʧ��(%s)." 
extern CString g_sLangID_Gradient_FailedGfp;
extern CString g_sLangTxt_Gradient_FailedGfp;
//"���ļ�ʧ��(%s).
extern CString g_sLangID_Gradient_FailedTof;
extern CString g_sLangTxt_Gradient_FailedTof;
//"[%s]����д�ļ�ʧ��." 
extern CString g_sLangID_Gradient_FailedCwf;
extern CString g_sLangTxt_Gradient_FailedCwf;
//"�ļ�[%s]��СΪ(%ld)." 
extern CString g_sLangID_Gradient_FileIsize;
extern CString g_sLangTxt_Gradient_FileIsize;
//"��ȡָ�����ȵĴ��ļ�����ʧ��." 
extern CString g_sLangID_Gradient_FailedTRlfile;
extern CString g_sLangTxt_Gradient_FailedTRlfile;
//"�ļ�[%s]��СΪ(%ld)." 
extern CString g_sLangID_Gradient_FileIsize;
extern CString g_sLangTxt_Gradient_FileIsize;
//"�ļ�������(%s)." 
extern CString g_sLangID_Gradient_FileNoexist;
extern CString g_sLangTxt_Gradient_FileNoexist;
//Ƶ�ʶ���ֵ(Hz) 
extern CString g_sLangID_Gradient_FreAValue;
extern CString g_sLangTxt_Gradient_FreAValue;
//"FT3����" 
extern CString g_sLangID_Gradient_ReleasedFTT;
extern CString g_sLangTxt_Gradient_ReleasedFTT;
//"��ǰSMVFT3ͨ��ӳ�����(%s).
extern CString g_sLangID_Gradient_CurSmvErr;
extern CString g_sLangTxt_Gradient_CurSmvErr;
//"�ⲿIED����" 
extern CString g_sLangID_Gradient_ExIEDdescrip;
extern CString g_sLangTxt_Gradient_ExIEDdescrip;
//"�����ļ�(" 
extern CString g_sLangID_Gradient_ParseLFile;
extern CString g_sLangTxt_Gradient_ParseLFile;
//")������,�޷�����SCLѡ���л�.
extern CString g_sLangID_Gradient_SCLNoSel;
extern CString g_sLangTxt_Gradient_SCLNoSel;
//"��ǰ������������޸�����,ɾ����ǰ������ʧ��,�����ڴ�й©����."
extern CString g_sLangID_Gradient_NoParObjRisk;
extern CString g_sLangTxt_Gradient_NoParObjRisk;
//"��������"
extern CString g_sLangID_Gradient_FailType;
extern CString g_sLangTxt_Gradient_FailType;
//"���Ϸ���"
extern CString g_sLangID_Gradient_FailDirect;
extern CString g_sLangTxt_Gradient_FailDirect;
//"����ʱ��"
extern CString g_sLangID_Gradient_FailTime;
extern CString g_sLangTxt_Gradient_FailTime;
//"б��"
extern CString g_sLangID_Gradient_Slope;
extern CString g_sLangTxt_Gradient_Slope;
//"�����ż�"  
extern CString g_sLangID_Gradient_StartTs;
extern CString g_sLangTxt_Gradient_StartTs;
//"��������"
extern CString g_sLangID_Gradient_StartCur;
extern CString g_sLangTxt_Gradient_StartCur;
//�յ�
extern CString g_sLangID_Gradient_Inflectp;
extern CString g_sLangTxt_Gradient_Inflectp;
//"������ֵ" 
extern CString g_sLangID_Gradient_DiffFlowEx;
extern CString g_sLangTxt_Gradient_DiffFlowEx;
//"����Զ����" 
extern CString g_sLangID_Gradient_AddCusp;
extern CString g_sLangTxt_Gradient_AddCusp;
//����Զ���� 
extern CString g_sLangID_Gradient_Emptycusp;
extern CString g_sLangTxt_Gradient_Emptycusp;
//"������ֵ���ò���С�ڹյ������Ӧ����ֵ."
extern CString g_sLangID_Gradient_NoLessCor;
extern CString g_sLangTxt_Gradient_NoLessCor;
//���ʲ 
extern CString g_sLangID_Gradient_RatioDiff;
extern CString g_sLangTxt_Gradient_RatioDiff;
//"�Զ�����Ե�" 
extern CString g_sLangID_Gradient_Custestp;
extern CString g_sLangTxt_Gradient_Custestp;
//�迹��﷽ʽ 
extern CString g_sLangID_Gradient_Impedance;
extern CString g_sLangTxt_Gradient_Impedance;
//����ѡ����Ҫɾ������������ 
extern CString g_sLangID_Gradient_SelectCur;
extern CString g_sLangTxt_Gradient_SelectCur;
//"���߱༭" 
extern CString g_sLangID_Gradient_CurveEditing;
extern CString g_sLangTxt_Gradient_CurveEditing;
//"����Ԫ��"
extern CString g_sLangID_Gradient_InsertElement;
extern CString g_sLangTxt_Gradient_InsertElement;
//"�޸�Ԫ��"
extern CString g_sLangID_Gradient_ModifyElement;
extern CString g_sLangTxt_Gradient_ModifyElement;
//"ɾ��Ԫ��"
extern CString g_sLangID_Gradient_DeleteElement;
extern CString g_sLangTxt_Gradient_DeleteElement;
//"+:��ʼ"
extern CString g_sLangID_Gradient_PInitial;
extern CString g_sLangTxt_Gradient_PInitial;
//"+:ѡ��"
extern CString g_sLangID_Gradient_PSelected;
extern CString g_sLangTxt_Gradient_PSelected;
//"+:�������"
extern CString g_sLangID_Gradient_EndTrial;
extern CString g_sLangTxt_Gradient_EndTrial;
//"�������߲���ʧ��(strCharaID=%s;strIndex=%s),�޷���������ͼ"
extern CString g_sLangID_Gradient_UnUpdateGraph;
extern CString g_sLangTxt_Gradient_UnUpdateGraph;
//"Y/V����ƽ���ѹ��" 
extern CString g_sLangID_Gradient_YNWirBlancer;
extern CString g_sLangTxt_Gradient_YNWirBlancer;
//"Y/��-11����(��ת��)" 
extern CString g_sLangID_Gradient_YNoCorners;
extern CString g_sLangTxt_Gradient_YNoCorners;
//"�����ѹ��"
extern CString g_sLangID_Gradient_Sphase;
extern CString g_sLangTxt_Gradient_Sphase;
//"Y/��/������"
extern CString g_sLangID_Gradient_YDSCornect;
extern CString g_sLangTxt_Gradient_YDSCornect;
//"Y/A �����迹ƥ��ƽ���ѹ��" 
extern CString g_sLangID_Gradient_ImpedanceMB;
extern CString g_sLangTxt_Gradient_ImpedanceMB;
//"����V/V���߱�ѹ��" 
extern CString g_sLangID_Gradient_ThrVWirceTF;
extern CString g_sLangTxt_Gradient_ThrVWirceTF;
//"����V/V���߱�ѹ��2"
extern CString g_sLangID_Gradient_SecThrVWirceTF;
extern CString g_sLangTxt_Gradient_SecThrVWirceTF;
//"Y/��-11����(Y��ת��)"
extern CString g_sLangID_Gradient_YSideCorner;
extern CString g_sLangTxt_Gradient_YSideCorner;
//"����V/V" 
extern CString g_sLangID_Gradient_VThrPhase;
extern CString g_sLangTxt_Gradient_VThrPhase;
//"��׼����(Ie)"
extern CString g_sLangID_Gradient_IRCurrent;
extern CString g_sLangTxt_Gradient_IRCurrent;
//"��׼����(A)"
extern CString g_sLangID_Gradient_ARCurrent;
extern CString g_sLangTxt_Gradient_ARCurrent;
//"����ʱ��" 
extern CString g_sLangID_Gradient_ActionTime;
extern CString g_sLangTxt_Gradient_ActionTime;
//" ��  A "
extern CString g_sLangID_Gradient_JumpA;
extern CString g_sLangTxt_Gradient_JumpA;
//" ��  B "
extern CString g_sLangID_Gradient_JumpB;
extern CString g_sLangTxt_Gradient_JumpB;
//" ��  C "
extern CString g_sLangID_Gradient_JumpC;
extern CString g_sLangTxt_Gradient_JumpC;
//��
extern CString g_sLangID_Gradient_Jjump;
extern CString g_sLangTxt_Gradient_Jjump;
//"��ǰ��λֵԽ�޳���(%f)." 
extern CString g_sLangID_Gradient_CurPhaseErr;
extern CString g_sLangTxt_Gradient_CurPhaseErr;
//"����"
extern CString g_sLangID_Gradient_Setting;
extern CString g_sLangTxt_Gradient_Setting;
//"��ǰFT3ͨ��ӳ�����(%s)." 
extern CString g_sLangID_Gradient_FT3CurChanErr;
extern CString g_sLangTxt_Gradient_FT3CurChanErr;
//"�⹦��" 
extern CString g_sLangID_Gradient_OpticalPower;
extern CString g_sLangTxt_Gradient_OpticalPower;
//"���%d" 
extern CString g_sLangID_Gradient_POpticalPort;
extern CString g_sLangTxt_Gradient_POpticalPort;
//"�⹦��(-dbm)"
extern CString g_sLangID_Gradient_FOpticalPower;
extern CString g_sLangTxt_Gradient_FOpticalPower;
//"�ļ����ƣ�"
//extern CString g_sLangID_Gradient_FmFileName;
//extern CString g_sLangTxt_Gradient_FmFileName;
//"�ļ�Ŀ¼��"
extern CString g_sLangID_Gradient_DirectoryFile;
extern CString g_sLangTxt_Gradient_DirectoryFile;
//"����IP����" 
extern CString g_sLangID_Gradient_SecondaryIPSet;
extern CString g_sLangTxt_Gradient_SecondaryIPSet;
//"IP���벻�Ϸ�" 
extern CString g_sLangID_Gradient_IPInputInvalid;
extern CString g_sLangTxt_Gradient_IPInputInvalid;
//"һ��ֵ(V/A)"
extern CString g_sLangID_Gradient_VAOnceValue;
extern CString g_sLangTxt_Gradient_VAOnceValue;
//"����ֵ(V/A)"
extern CString g_sLangID_Gradient_VATwiceValue;
extern CString g_sLangTxt_Gradient_VATwiceValue;
//"������ͬ"
extern CString g_sLangID_Gradient_SameThreep;
extern CString g_sLangTxt_Gradient_SameThreep;
//"ȫ����ͬ"
extern CString g_sLangID_Gradient_AllSamep;
extern CString g_sLangTxt_Gradient_AllSamep;
//"��λ(��)" 
extern CString g_sLangID_Gradient_DPhase;
extern CString g_sLangTxt_Gradient_DPhase;
//"��ǰ״̬(%d)��FT3��������Ϊ��(�����쳣)."
extern CString g_sLangID_Gradient_FRelCurempty;
extern CString g_sLangTxt_Gradient_FRelCurempty;
//"��ǰ������Ϊ��."
extern CString g_sLangID_Gradient_EmptyCurTI;
extern CString g_sLangTxt_Gradient_EmptyCurTI;
//"���ȹر���ҳ����,����ִ�й�������ť����."
extern CString g_sLangID_Gradient_ClosePerTBF;
extern CString g_sLangTxt_Gradient_ClosePerTBF;
//"�ȴ����Է���ֹͣ��ر�."
extern CString g_sLangID_Gradient_WaitSASD;
extern CString g_sLangTxt_Gradient_WaitSASD;
//"�������(%s)(isNull)ʧ��."
extern CString g_sLangID_Gradient_INUnSavescreen;
extern CString g_sLangTxt_Gradient_INUnSavescreen;
//"�������(%s)(save)ʧ��."
extern CString g_sLangID_Gradient_UnSavescreen;
extern CString g_sLangTxt_Gradient_UnSavescreen;
//�������(%s)�ɹ�.
extern CString g_sLangID_Gradient_Savescreen;
extern CString g_sLangTxt_Gradient_Savescreen;
//"���ڲ�����Ŀ���οؼ���ѡ��Ϸ�����Ŀ����"
extern CString g_sLangID_Gradient_Selectleg;
extern CString g_sLangTxt_Gradient_Selectleg;
//"?????????????? OnCmd_NewTest: �رմ򿪵Ĳ��Թ���ҳ�棬��������ʾ�Ƿ񱣴��޸� ???????????"
extern CString g_sLangID_Gradient_CLoseMMChanges;
extern CString g_sLangTxt_Gradient_CLoseMMChanges;
//"ģ������Ҳ���rootnode�ڵ��Ӧ�Ĺ��ܽ��桾%s��"
extern CString g_sLangID_Gradient_TemplateErr;
extern CString g_sLangTxt_Gradient_TemplateErr;
//"ģ�����Ϊ"
extern CString g_sLangID_Gradient_SaveTemplateAs;
extern CString g_sLangTxt_Gradient_SaveTemplateAs;


//"���ļ�ʧ��"
extern CString g_sLangID_Gradient_OpenfileFail;
extern CString g_sLangTxt_Gradient_OpenfileFail;
//"�������"
extern CString g_sLangID_Gradient_SendComplete;
extern CString g_sLangTxt_Gradient_SendComplete;
//"����ͨ������"
extern CString g_sLangID_Gradient_RecvChannel;
extern CString g_sLangTxt_Gradient_RecvChannel;
//"PT/CT���"
extern CString g_sLangID_Gradient_RatioPCT;
extern CString g_sLangTxt_Gradient_RatioPCT;
//"��ѡ����ƿ�"
extern CString g_sLangID_Gradient_ControlB;
extern CString g_sLangTxt_Gradient_ControlB;
//"����ͨ��"
extern CString g_sLangID_Gradient_RecvChannnel;
extern CString g_sLangTxt_Gradient_RecvChannnel;
//"��Ӧʱ�����"
extern CString g_sLangID_Gradient_ResTimeErr;
extern CString g_sLangTxt_Gradient_ResTimeErr;
//"������Ӧʱ��"
extern CString g_sLangID_Gradient_MessResTime;
extern CString g_sLangTxt_Gradient_MessResTime;
//ͨ����ʱ Channel Delay
// extern CString g_sLangID_Gradient_ChaDelay;
// extern CString g_sLangTxt_Gradient_ChaDelay;
//"�ϲ���Ԫ���Թ���ID()�������ļ���δ���ҵ�."
extern CString g_sLangID_Gradient_MergeUint;
extern CString g_sLangTxt_Gradient_MergeUint;
//"��ǰѡ����Թ����쳣(%s),����m_pSttIecRcdFuncInterface==NULL."
extern CString g_sLangID_Gradient_NAbnormalRes;
extern CString g_sLangTxt_Gradient_NAbnormalRes;
//"����ʱ��(s):"
extern CString g_sLangID_Gradient_TestDuration;
extern CString g_sLangTxt_Gradient_TestDuration;
//"��ǰ��ʱ����Ϊ��,���ʱ�侫�Ƚ��ʧ��."
extern CString g_sLangID_Gradient_TheCurDelay;
extern CString g_sLangTxt_Gradient_TheCurDelay;
//"���ʱ�侫�Ƚ���ɹ�."
extern CString g_sLangID_Gradient_EmptyRes;
extern CString g_sLangTxt_Gradient_EmptyRes;
//"�Ȳ�(%)"
extern CString g_sLangID_Gradient_DiffRatio;
extern CString g_sLangTxt_Gradient_DiffRatio;
//"��ǰ���ݼ�Ϊ��,������ͳ�ƽ��ʧ��."
extern CString g_sLangID_Gradient_CurNullFa;
extern CString g_sLangTxt_Gradient_CurNullFa;
//"��Ư"
extern CString g_sLangID_Gradient_ZeroDrift;
extern CString g_sLangTxt_Gradient_ZeroDrift;
//"���ֵ"
extern CString g_sLangID_Gradient_ValueOutP;
extern CString g_sLangTxt_Gradient_ValueOutP;
//"�����λ"
extern CString g_sLangID_Gradient_PhaseOutP;
extern CString g_sLangTxt_Gradient_PhaseOutP;
//"ʵ���ֵ"
extern CString g_sLangID_Gradient_MeasurAmp;
extern CString g_sLangTxt_Gradient_MeasurAmp;
//"ͨ����ʱ"
extern CString g_sLangID_Gradient_ChanDelay;
extern CString g_sLangTxt_Gradient_ChanDelay;
//"�������" "Composite error"
extern CString g_sLangID_Gradient_CompError;
extern CString g_sLangTxt_Gradient_CompError;
//"ʵ����λ" Measured phase
extern CString g_sLangID_Gradient_MeaPhase;
extern CString g_sLangTxt_Gradient_MeaPhase;
//"Ƶ��" "Frequency difference"
extern CString g_sLangID_Gradient_FrequencyDiff;
extern CString g_sLangTxt_Gradient_FrequencyDiff;
//"����̽�����" Message Detection Interface
extern CString g_sLangID_Gradient_DetectMessageI;
extern CString g_sLangTxt_Gradient_DetectMessageI;
//"δ¼��"
extern CString g_sLangID_Gradient_Unrecorded;
extern CString g_sLangTxt_Gradient_Unrecorded;
//"GOOSE���ƿ�(AppID=0X%04X),����Ӷ��ĵ����%ld,�����ظ����."
extern CString g_sLangID_Gradient_Appscribed;
extern CString g_sLangTxt_Gradient_Appscribed;
//"GOOSE���ƿ�(AppID=0X%04X),��Ӷ��ĵ����%ld�ɹ�."
extern CString g_sLangID_Gradient_SEcontrolSus;
extern CString g_sLangTxt_Gradient_SEcontrolSus;
//"GOOSE���ƿ�(AppID=0X%04X),����ӷ��������%ld,�����ظ����."
extern CString g_sLangID_Gradient_AppscribedFa;
extern CString g_sLangTxt_Gradient_AppscribedFa;
//"GOOSE���ƿ�(AppID=0X%04X),��ӷ��������%ld�ɹ�."
extern CString g_sLangID_Gradient_AppFascribedFa;
extern CString g_sLangTxt_Gradient_AppFascribedFa;


//"�޸Ľ�����ʾ" 
extern CString g_sLangID_Gradient_ModifyTip;
extern CString g_sLangTxt_Gradient_ModifyTip;
//������ʾ
extern CString g_sLangID_Gradient_WiringTip;
extern CString g_sLangTxt_Gradient_WiringTip;
//�½�������ʾ
extern CString g_sLangID_Gradient_WirPrompt;
extern CString g_sLangTxt_Gradient_WirPrompt;
//"���ڴ˴����������ʾ��Ϣ����" 
extern CString g_sLangID_Gradient_EnterTips;
extern CString g_sLangTxt_Gradient_EnterTips;
//"�밴�ս�����ʾ��Ϣ����ɽ��ߺ󣬵������ɽ��ߡ���ť���������ԡ���"
extern CString g_sLangID_Gradient_ClickCTest;
extern CString g_sLangTxt_Gradient_ClickCTest;
//"��ɽ���"
extern CString g_sLangID_Gradient_CompleteWir;
extern CString g_sLangTxt_Gradient_CompleteWir;
//"������ͬ���ƵĽ�����ʾ"
extern CString g_sLangID_Gradient_WirpromptExit;
extern CString g_sLangTxt_Gradient_WirpromptExit;
//"������ʾ��Ϣ�༭��δ��⵽���ݷ����仯����"
extern CString g_sLangID_Gradient_WEditNoChange;
extern CString g_sLangTxt_Gradient_WEditNoChange;
//"��������з�ʽ��"
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
extern CString g_sLangID_IEC_CancelConfigure;
extern CString g_sLangTxt_IEC_CancelConfigure;
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
extern CString g_sLangID_Gradient_BoutSet; //����������
extern CString g_sLangTxt_Gradient_BoutSet;
extern CString g_sLangID_Gradient_BoutSets; //���࿪��������
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
//extern CString g_sLangID_Frequency;   //�ƶ�������CXLanguageResourceBase  2024-1-4 shaolei
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
extern CString g_sLangID_MUoutputvalue;
extern CString g_sLangTxt_MUoutputvalue;
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

//�Զ�������
extern  CString g_sLangID_Native_BtnRemove;  
extern  CString g_sLangTxt_Native_BtnRemove;
extern  CString g_sLangID_Native_BtnEndInsert;  
extern  CString g_sLangTxt_Native_BtnEndInsert;
extern  CString g_sLangID_Native_BtnInsertAfter;  
extern  CString g_sLangTxt_Native_BtnInsertAfter;
extern  CString g_sLangID_Native_BtnInsertBefore;  
extern  CString g_sLangTxt_Native_BtnInsertBefore;

//װ��ͨѶ
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



//��������
//xwd 10.16
//����ԭʼ����
extern CString g_sLangID_Native_SetOrigMsg;
extern CString g_sLangTxt_Native_SetOrigMsg;
//Ŀ��Mac��ַ
extern CString g_sLangID_Native_DestMacAddr;
extern CString g_sLangTxt_Native_DestMacAddr;
//�����ʶ
extern CString g_sLangID_Native_Netid;
extern CString g_sLangTxt_Native_Netid;
//�ɵ��ѹֵ
extern CString g_sLangID_Native_FlyPntVolt;
extern CString g_sLangTxt_Native_FlyPntVolt;
//�ɵ����ֵ
extern CString g_sLangID_Native_FlyPntCurr;
extern CString g_sLangTxt_Native_FlyPntCurr;
//�ɵ��ѹUaʹ��
extern CString g_sLangID_Native_FlyPntVoltUaEn;
extern CString g_sLangTxt_Native_FlyPntVoltUaEn;
//�ɵ��ѹUbʹ��
extern CString g_sLangID_Native_FlyPntVoltUbEn;
extern CString g_sLangTxt_Native_FlyPntVoltUbEn;
//�ɵ��ѹUcʹ��
extern CString g_sLangID_Native_FlyPntVoltUcEn;
extern CString g_sLangTxt_Native_FlyPntVoltUcEn;
//�ɵ����Iaʹ��
extern CString g_sLangID_Native_FlyPntCurrIaEn;
extern CString g_sLangTxt_Native_FlyPntCurrIaEn;
//�ɵ����Ibʹ��
extern CString g_sLangID_Native_FlyPntCurrIbEn;
extern CString g_sLangTxt_Native_FlyPntCurrIbEn;
//�ɵ����Icʹ��
extern CString g_sLangID_Native_FlyPntCurrIcEn;
extern CString g_sLangTxt_Native_FlyPntCurrIcEn;
//����ֵ(��λns)
extern CString g_sLangID_Native_JitterValns;
extern CString g_sLangTxt_Native_JitterValns;
//��Ч
extern CString g_sLangID_Native_Valid;
extern CString g_sLangTxt_Native_Valid;
//���

extern CString g_sLangID_Native_Overflow;
extern CString g_sLangTxt_Native_Overflow;
//��ֵ��
extern CString g_sLangID_Native_OutOfRanges;
extern CString g_sLangTxt_Native_OutOfRanges;
//����׼ֵ
extern CString g_sLangID_Native_BadBaseVal;
extern CString g_sLangTxt_Native_BadBaseVal;
//������
extern CString g_sLangID_Native_OldData;
extern CString g_sLangTxt_Native_OldData;
//��һ��
extern CString g_sLangID_Native_Inconsistent;
extern CString g_sLangTxt_Native_Inconsistent;
//����ȷ
extern CString g_sLangID_Native_Inaccurate;
extern CString g_sLangTxt_Native_Inaccurate;
//Դ
extern CString g_sLangID_Native_Source;
extern CString g_sLangTxt_Native_Source;
//����Ա����
extern CString g_sLangID_Native_OpLock;
extern CString g_sLangTxt_Native_OpLock;
//�쳣��ѡ��
extern CString g_sLangID_Native_AbnPointSel;
extern CString g_sLangTxt_Native_AbnPointSel;
//�쳣��
extern CString g_sLangID_Native_AbnPoint;
extern CString g_sLangTxt_Native_AbnPoint;
//SMV�쳣����
extern CString g_sLangID_Native_SMVAbnParam;
extern CString g_sLangTxt_Native_SMVAbnParam;
//SV�쳣����
extern CString g_sLangID_Native_SVAbnType;
extern CString g_sLangTxt_Native_SVAbnType;
//SV�������(��0��ʼ���)
extern CString g_sLangID_Native_SVMsgGrpNum;
extern CString g_sLangTxt_Native_SVMsgGrpNum;
//�����ܲ���(�ܲ�ģʽ)
extern CString g_sLangID_Native_SendFreq;
extern CString g_sLangTxt_Native_SendFreq;
//ÿ�뷢���ܲ���(��ģʽ)
extern CString g_sLangID_Native_SendFreqPerSec;
extern CString g_sLangTxt_Native_SendFreqPerSec;
//�쳣���ݷ���ʱ��ģʽ(0-�ܲ�;1-��)
extern CString g_sLangID_Native_AbnormDataSendTimeMode;
extern CString g_sLangTxt_Native_AbnormDataSendTimeMode;
//SV����ʱ��(��ģʽ)
extern CString g_sLangID_Native_SVSendTimeSecMode;
extern CString g_sLangTxt_Native_SVSendTimeSecMode;
//GOOSE�쳣����
extern CString g_sLangID_Native_GOOSEAbnormParam;
extern CString g_sLangTxt_Native_GOOSEAbnormParam;
//�쳣����ţ���0������
extern CString g_sLangID_Native_AbnormGroupSeq;
extern CString g_sLangTxt_Native_AbnormGroupSeq;
//ԴMAC(ѡ��)
extern CString g_sLangID_Native_SrcMACSelect;
extern CString g_sLangTxt_Native_SrcMACSelect;
//Ŀ��MAC(ѡ��)
extern CString g_sLangID_Native_DestMACSelect;
extern CString g_sLangTxt_Native_DestMACSelect;
//GocbRef(ѡ��)
extern CString g_sLangID_Native_GocbRefSelect;
extern CString g_sLangTxt_Native_GocbRefSelect;
//GoID(ѡ��)
extern CString g_sLangID_Native_GoIDSelect;
extern CString g_sLangTxt_Native_GoIDSelect;
//DataSet(ѡ��)
extern CString g_sLangID_Native_DataSetSelect;
extern CString g_sLangTxt_Native_DataSetSelect;
//Ŀ��MAC
extern CString g_sLangID_Native_DestMACs;
extern CString g_sLangTxt_Native_DestMACs;
//AppID(ѡ��)
extern CString g_sLangID_Native_AppIDSelect;
extern CString g_sLangTxt_Native_AppIDSelect;
//St(ѡ��)
extern CString g_sLangID_Native_StSelect;
extern CString g_sLangTxt_Native_StSelect;
//Stֵ
extern CString g_sLangID_Native_StValue;
extern CString g_sLangTxt_Native_StValue;
//Sq(ѡ��)
extern CString g_sLangID_Native_SqSelect;
extern CString g_sLangTxt_Native_SqSelect;
//Sqֵ
extern CString g_sLangID_Native_SqValue;
extern CString g_sLangTxt_Native_SqValue;
//��������ʱ��(ѡ��)
extern CString g_sLangID_Native_AllowLiveTSelect;
extern CString g_sLangTxt_Native_AllowLiveTSelect;
//��������ʱ��
extern CString g_sLangID_Native_AllowLiveT;
extern CString g_sLangTxt_Native_AllowLiveT;
//ί��(ѡ��)
extern CString g_sLangID_Native_DelegateSelect;
extern CString g_sLangTxt_Native_DelegateSelect;
//���Ա��(ѡ��)
extern CString g_sLangID_Native_TestMarkSelect;
extern CString g_sLangTxt_Native_TestMarkSelect;
//ί��
extern CString g_sLangID_Native_Delegate;
extern CString g_sLangTxt_Native_Delegate;
//���Ա��
extern CString g_sLangID_Native_TestMark;
extern CString g_sLangTxt_Native_TestMark;
//VlanID(ѡ��)
extern CString g_sLangID_Native_VlanIDSelect;
extern CString g_sLangTxt_Native_VlanIDSelect;
//VlanIDֵ
extern CString g_sLangID_Native_VlanIDValue;
extern CString g_sLangTxt_Native_VlanIDValue;
//�����ʶ(ѡ��)
extern CString g_sLangID_Native_NetIDSelect;
extern CString g_sLangTxt_Native_NetIDSelect;
//�����ʶֵ
extern CString g_sLangID_Native_NetIDValue;
extern CString g_sLangTxt_Native_NetIDValue;
//���ð汾(ѡ��)
extern CString g_sLangID_Native_ConfigVerSelect;
extern CString g_sLangTxt_Native_ConfigVerSelect;
//���ð汾ֵ
extern CString g_sLangID_Native_ConfigVerValue;
extern CString g_sLangTxt_Native_ConfigVerValue;
//��̬����1״̬
extern CString g_sLangID_Native_NormalOpen1State;
extern CString g_sLangTxt_Native_NormalOpen1State;
//��̬����2״̬
extern CString g_sLangID_Native_NormalOpen2State;
extern CString g_sLangTxt_Native_NormalOpen2State;
//��̬����3״̬
extern CString g_sLangID_Native_NormalOpen3State;
extern CString g_sLangTxt_Native_NormalOpen3State;
//��̬����4״̬
extern CString g_sLangID_Native_NormalOpen4State;
extern CString g_sLangTxt_Native_NormalOpen4State;
//��̬����5״̬
extern CString g_sLangID_Native_NormalOpen5State;
extern CString g_sLangTxt_Native_NormalOpen5State;
//��̬����6״̬
extern CString g_sLangID_Native_NormalOpen6State;
extern CString g_sLangTxt_Native_NormalOpen6State;
//��̬����7״̬
extern CString g_sLangID_Native_NormalOpen7State;
extern CString g_sLangTxt_Native_NormalOpen7State;
//��̬����8״̬
extern CString g_sLangID_Native_NormalOpen8State;
extern CString g_sLangTxt_Native_NormalOpen8State;
//����̬����1״̬
extern CString g_sLangID_Native_FaultOpen1State;
extern CString g_sLangTxt_Native_FaultOpen1State;
//����̬����2״̬
extern CString g_sLangID_Native_FaultOpen2State;
extern CString g_sLangTxt_Native_FaultOpen2State;
//����̬����3״̬
extern CString g_sLangID_Native_FaultOpen3State;
extern CString g_sLangTxt_Native_FaultOpen3State;
//����̬����4״̬
extern CString g_sLangID_Native_FaultOpen4State;
extern CString g_sLangTxt_Native_FaultOpen4State;
//����̬����5״̬
extern CString g_sLangID_Native_FaultOpen5State;
extern CString g_sLangTxt_Native_FaultOpen5State;
//����̬����6״̬
extern CString g_sLangID_Native_FaultOpen6State;
extern CString g_sLangTxt_Native_FaultOpen6State;
//����̬����7״̬
extern CString g_sLangID_Native_FaultOpen7State;
extern CString g_sLangTxt_Native_FaultOpen7State;
//����̬����8״̬
extern CString g_sLangID_Native_FaultOpen8State;
extern CString g_sLangTxt_Native_FaultOpen8State;
//�ȹ�����ʱ�䳣��
extern CString g_sLangID_Native_HotOverloadTimeConst;
extern CString g_sLangTxt_Native_HotOverloadTimeConst;
//�ȹ����ɻ�������
extern CString g_sLangID_Native_HotOverloadBaseCurrent;
extern CString g_sLangTxt_Native_HotOverloadBaseCurrent;
//�ȹ����ɶ�����ֵ
extern CString g_sLangID_Native_HotOverloadActionValue;
extern CString g_sLangTxt_Native_HotOverloadActionValue;
//�����ɵ���
extern CString g_sLangID_Native_OverloadCurrent;
extern CString g_sLangTxt_Native_OverloadCurrent;
//����ʱ��ԣ��
extern CString g_sLangID_Native_FaultTimeMargin;
extern CString g_sLangTxt_Native_FaultTimeMargin;
//�����仯ʼֵ
extern CString g_sLangID_Native_CurrentChangeStartValue;
extern CString g_sLangTxt_Native_CurrentChangeStartValue;
//�����仯��ֵ

extern CString g_sLangID_Native_CurrentChangeEndValue;
extern CString g_sLangTxt_Native_CurrentChangeEndValue;
//�����仯����
extern CString g_sLangID_Native_CurrentChangeStep;
extern CString g_sLangTxt_Native_CurrentChangeStep;
//�ȹ�����ʱ�䳣��(���ʽ)
extern CString g_sLangID_Native_HotOverloadTime;
extern CString g_sLangTxt_Native_HotOverloadTime;
//�ȹ����ɻ�������(���ʽ)
extern CString g_sLangID_Native_HotOverloadBaseCurr;
extern CString g_sLangTxt_Native_HotOverloadBaseCurr;
//�ȹ����ɶ�����ֵ(���ʽ)
extern CString g_sLangID_Native_HotOverloadActionValues;
extern CString g_sLangTxt_Native_HotOverloadActionValues;
//��������
extern CString g_sLangID_Native_ActionDesc;
extern CString g_sLangTxt_Native_ActionDesc;
//����ǰ��ѹ��ֵ
extern CString g_sLangID_Native_FaultPreVoltageAmp;
extern CString g_sLangTxt_Native_FaultPreVoltageAmp;
//����ǰ������ֵ
extern CString g_sLangID_Native_FaultPreCurrentAmp;
extern CString g_sLangTxt_Native_FaultPreCurrentAmp;
//����ǰ��ѹ�������(U-I)
extern CString g_sLangID_Native_FaultPreVoltageCurrentPhase;
extern CString g_sLangTxt_Native_FaultPreVoltageCurrentPhase;
//����ǰ��ѹ����
extern CString g_sLangID_Native_FaultPreVoltageSeq;
extern CString g_sLangTxt_Native_FaultPreVoltageSeq;
//����ǰ��������
extern CString g_sLangID_Native_FaultPreCurrentSeq;
extern CString g_sLangTxt_Native_FaultPreCurrentSeq;
//���ϵ�ѹ
extern CString g_sLangID_Native_FaultVoltage;
extern CString g_sLangTxt_Native_FaultVoltage;
//����̬��ѹ�������(U-I)
extern CString g_sLangID_Native_FaultVoltageCurrentPhase;
extern CString g_sLangTxt_Native_FaultVoltageCurrentPhase;
//��·��ѹ���
extern CString g_sLangID_Native_ShortCircuitVoltageType;
extern CString g_sLangTxt_Native_ShortCircuitVoltageType;
//��׼ֵ
extern CString g_sLangID_Native_ReferenceValue;
extern CString g_sLangTxt_Native_ReferenceValue;
//CT������
extern CString g_sLangID_Native_CTPolarityPositive;
extern CString g_sLangTxt_Native_CTPolarityPositive;
//����ǰ��ѹ�������(���ʽ)
extern CString g_sLangID_Native_PreFaultVCPAExpr;
extern CString g_sLangTxt_Native_PreFaultVCPAExpr;
//����ʱ�䶨ֵ(���ʽ)
extern CString g_sLangID_Native_ActionTimeSetValueExpr;
extern CString g_sLangTxt_Native_ActionTimeSetValueExpr;
//���ϵ�ѹ(���ʽ)
extern CString g_sLangID_Native_FaultVoltageExpr;
extern CString g_sLangTxt_Native_FaultVoltageExpr;
//���ϵ���(���ʽ)
extern CString g_sLangID_Native_FaultCurr;
extern CString g_sLangTxt_Native_FaultCurr;
//����̬��ѹ�������(���ʽ)
extern CString g_sLangID_Native_FaultAngExp;
extern CString g_sLangTxt_Native_FaultAngExp;
//�������߲���(Vp)
extern CString g_sLangID_Native_CharCurveParam;
extern CString g_sLangTxt_Native_CharCurveParam;
//��ѹƵ�ʱ�
extern CString g_sLangID_Native_VoltFreqRatio;
extern CString g_sLangTxt_Native_VoltFreqRatio;
//�仯��ʽ 0-Ƶ�ʲ���,����ѹ  1-��ѹ����,��Ƶ��
extern CString g_sLangID_Native_ChangeMode;
extern CString g_sLangTxt_Native_ChangeMode;
//�ɼ�ģ��λ��
extern CString g_sLangID_Native_CollectModPos;
extern CString g_sLangTxt_Native_CollectModPos;
//�ɼ���λ
extern CString g_sLangID_Native_CollectGear;
extern CString g_sLangTxt_Native_CollectGear;
//ģ��λ��
extern CString g_sLangID_Native_ModPos;
extern CString g_sLangTxt_Native_ModPos;
//����
extern CString g_sLangID_Native_TempZone;
extern CString g_sLangTxt_Native_TempZone;
//������
extern CString g_sLangID_Native_MeterError;
extern CString g_sLangTxt_Native_MeterError;
//�ο�Ƶ��
extern CString g_sLangID_Native_RefFreq;
extern CString g_sLangTxt_Native_RefFreq;
//��1�ο���ֵ
extern CString g_sLangID_Native_Point1RefAmp;
extern CString g_sLangTxt_Native_Point1RefAmp;
//��2�ο���ֵ
extern CString g_sLangID_Native_Point2RefAmp;
extern CString g_sLangTxt_Native_Point2RefAmp;
//��1������ֵ
extern CString g_sLangID_Native_Point1MeasAmp;
extern CString g_sLangTxt_Native_Point1MeasAmp;
//��2������ֵ
extern CString g_sLangID_Native_Point2MeasAmp;
extern CString g_sLangTxt_Native_Point2MeasAmp;
//�����ֵ
extern CString g_sLangID_Native_OutputAmp;
extern CString g_sLangTxt_Native_OutputAmp;
//��λ����ֵ
extern CString g_sLangID_Native_PhaseMeasVal;
extern CString g_sLangTxt_Native_PhaseMeasVal;
//����Ƶ��
extern CString g_sLangID_Native_MeasFreq;
extern CString g_sLangTxt_Native_MeasFreq;
//ͨ��Ӳ����λ
extern CString g_sLangID_Native_ChannelHardGear;
extern CString g_sLangTxt_Native_ChannelHardGear;
//��Ư����ֵ
extern CString g_sLangID_Native_ZeroDriftMeas;
extern CString g_sLangTxt_Native_ZeroDriftMeas;
//ͨ��1���
extern CString g_sLangID_Native_Channel1ID;
extern CString g_sLangTxt_Native_Channel1ID;
//ͨ��1��ֵ

extern CString g_sLangID_Native_Channel1Amp;
extern CString g_sLangTxt_Native_Channel1Amp;
//ͨ��1��λ
extern CString g_sLangID_Native_Channel1Phase;
extern CString g_sLangTxt_Native_Channel1Phase;
//ͨ��1Ƶ��
extern CString g_sLangID_Native_Channel1Freq;
extern CString g_sLangTxt_Native_Channel1Freq;
//ͨ��2���
extern CString g_sLangID_Native_Channel2Num;
extern CString g_sLangTxt_Native_Channel2Num;
//ͨ��2��ֵ
extern CString g_sLangID_Native_Channel2Amp;
extern CString g_sLangTxt_Native_Channel2Amp;
//ͨ��2��λ
extern CString g_sLangID_Native_Channel2Phase;
extern CString g_sLangTxt_Native_Channel2Phase;
//ͨ��2Ƶ��
extern CString g_sLangID_Native_Channel2Freq;
extern CString g_sLangTxt_Native_Channel2Freq;
//ͨ��3���
extern CString g_sLangID_Native_Channel3Num;
extern CString g_sLangTxt_Native_Channel3Num;
//ͨ��3��ֵ
extern CString g_sLangID_Native_Channel3Amp;
extern CString g_sLangTxt_Native_Channel3Amp;
//ͨ��3��λ
extern CString g_sLangID_Native_Channel3Phase;
extern CString g_sLangTxt_Native_Channel3Phase;
//ͨ��3Ƶ��
extern CString g_sLangID_Native_Channel3Freq;
extern CString g_sLangTxt_Native_Channel3Freq;
//�Ƿ�����У׼
extern CString g_sLangID_Native_IsHighCurrentCalib;
extern CString g_sLangTxt_Native_IsHighCurrentCalib;
//ͨ��1��ֵϵ��
extern CString g_sLangID_Native_Channel1AmpCoeff;
extern CString g_sLangTxt_Native_Channel1AmpCoeff;
//ͨ��1��Ư
extern CString g_sLangID_Native_Channel1ZeroOffset;
extern CString g_sLangTxt_Native_Channel1ZeroOffset;
//ͨ��2��ֵϵ��
extern CString g_sLangID_Native_Channel2AmpCoeff;
extern CString g_sLangTxt_Native_Channel2AmpCoeff;
//ͨ��2��Ư
extern CString g_sLangID_Native_Channel2ZeroOffset;
extern CString g_sLangTxt_Native_Channel2ZeroOffset;
//ͨ��3��ֵϵ��
extern CString g_sLangID_Native_Channel3AmpCoeff;
extern CString g_sLangTxt_Native_Channel3AmpCoeff;
//ͨ��3��Ư
extern CString g_sLangID_Native_Channel3ZeroOffset;
extern CString g_sLangTxt_Native_Channel3ZeroOffset;
//����ѡ��
extern CString g_sLangID_Native_WaveformSelection;
extern CString g_sLangTxt_Native_WaveformSelection;
//��λ
extern CString g_sLangID_Native_Gear;
extern CString g_sLangTxt_Native_Gear;
//ģ����2
extern CString g_sLangID_Native_ModuleNo2;
extern CString g_sLangTxt_Native_ModuleNo2;
//����2
extern CString g_sLangID_Native_TempZone2;
extern CString g_sLangTxt_Native_TempZone2;
//ͨ�����2
extern CString g_sLangID_Native_ChannelNo2;
extern CString g_sLangTxt_Native_ChannelNo2;
//��λ2
extern CString g_sLangID_Native_Gear2;
extern CString g_sLangTxt_Native_Gear2;
//���ͨ��
extern CString g_sLangID_Native_OutputChannel;
extern CString g_sLangTxt_Native_OutputChannel;
//Ӳ����λ
extern CString g_sLangID_Native_HardwareGear;
extern CString g_sLangTxt_Native_HardwareGear;
//ģ����
extern CString g_sLangID_Native_ModuleNumber;
extern CString g_sLangTxt_Native_ModuleNumber;
//�л�ģʽ
extern CString g_sLangID_Native_SwitchMode;
extern CString g_sLangTxt_Native_SwitchMode;
//����1��ֵͨ
extern CString g_sLangID_Native_Output1ConductValue;
extern CString g_sLangTxt_Native_Output1ConductValue;
//����2��ֵͨ
extern CString g_sLangID_Native_Output2ConductValue;
extern CString g_sLangTxt_Native_Output2ConductValue;
//����3��ֵͨ
extern CString g_sLangID_Native_Output3ConductValue;
extern CString g_sLangTxt_Native_Output3ConductValue;
//����4��ֵͨ
extern CString g_sLangID_Native_Output4ConductValue;
extern CString g_sLangTxt_Native_Output4ConductValue;
//����5��ֵͨ
extern CString g_sLangID_Native_Output5ConductValue;
extern CString g_sLangTxt_Native_Output5ConductValue;
//����6��ֵͨ
extern CString g_sLangID_Native_Output6ConductValue;
extern CString g_sLangTxt_Native_Output6ConductValue;
//����7��ֵͨ
extern CString g_sLangID_Native_Output7ConductValue;
extern CString g_sLangTxt_Native_Output7ConductValue;
//����8��ֵͨ
extern CString g_sLangID_Native_Output8ConductValue;
extern CString g_sLangTxt_Native_Output8ConductValue;
//�Ĵ�����ַ(16����)
extern CString g_sLangID_Native_RegAddrHex;
extern CString g_sLangTxt_Native_RegAddrHex;
//�Ĵ���ֵ(16����)
extern CString g_sLangID_Native_RegValHex;
extern CString g_sLangTxt_Native_RegValHex;
//���
extern CString g_sLangID_Native_Results;
extern CString g_sLangTxt_Native_Results;
//������ת��ʱ
extern CString g_sLangID_Native_FlipDelay;
extern CString g_sLangTxt_Native_FlipDelay;
//��������ת�б�����
extern CString g_sLangID_Native_InFlipCond;
extern CString g_sLangTxt_Native_InFlipCond;
//�Ƿ�Ϊ˳��״̬����
extern CString g_sLangID_Native_IsSeqStateSeq;
extern CString g_sLangTxt_Native_IsSeqStateSeq;
//�ظ�����
extern CString g_sLangID_Native_RepeatCount;
extern CString g_sLangTxt_Native_RepeatCount;
//״̬��
extern CString g_sLangID_Native_StateNum;
extern CString g_sLangTxt_Native_StateNum;
//������չ
extern CString g_sLangID_Native_InputExpand;
extern CString g_sLangTxt_Native_InputExpand;
//�ζ���ʱ��
extern CString g_sLangID_Native_NActionTime;
extern CString g_sLangTxt_Native_NActionTime;
//ѭ�����
extern CString g_sLangID_Native_LoopNum;
extern CString g_sLangTxt_Native_LoopNum;
//״̬���
extern CString g_sLangID_Native_StateNums;
extern CString g_sLangTxt_Native_StateNums;
//����I�ζ�ֵ
extern CString g_sLangID_Native_OverCurrentI;
extern CString g_sLangTxt_Native_OverCurrentI;
//����II�ζ�ֵ
extern CString g_sLangID_Native_OverCurrentII;
extern CString g_sLangTxt_Native_OverCurrentII;
//����III�ζ�ֵ
extern CString g_sLangID_Native_OverCurrentIII;
extern CString g_sLangTxt_Native_OverCurrentIII;
//����IV�ζ�ֵ
extern CString g_sLangID_Native_OverCurrentIV;
extern CString g_sLangTxt_Native_OverCurrentIV;
//����I��ʱ��
extern CString g_sLangID_Native_OverCurrentITime;
extern CString g_sLangTxt_Native_OverCurrentITime;
//����II��ʱ��
extern CString g_sLangID_Native_OverCurrentIITime;
extern CString g_sLangTxt_Native_OverCurrentIITime;
//����III��ʱ��
extern CString g_sLangID_Native_OverCurrentIIITime;
extern CString g_sLangTxt_Native_OverCurrentIIITime;
//����IV��ʱ��
extern CString g_sLangID_Native_OverCurrentIVTime;
extern CString g_sLangTxt_Native_OverCurrentIVTime;
//����
extern CString g_sLangID_Native_Grouping;
extern CString g_sLangTxt_Native_Grouping;
//������������(���ʽ)
extern CString g_sLangID_Native_SetActCurExp;
extern CString g_sLangTxt_Native_SetActCurExp;
//����ֵ
extern CString g_sLangID_Native_OverCurrentValue;
extern CString g_sLangTxt_Native_OverCurrentValue;

//�ڰ�����
extern CString g_sLangID_Native_volDefinition1;
extern CString g_sLangTxt_Native_volDefinition1;// ��ѹ����
extern CString g_sLangID_Native_refphase;
extern CString g_sLangTxt_Native_refphase;//�ο���
extern CString g_sLangID_Native_transfConnection;
extern CString g_sLangTxt_Native_transfConnection;//��ѹ�����߷�ʽ
extern CString g_sLangID_Native_maxSyncTime1;
extern CString g_sLangTxt_Native_maxSyncTime1;//���ͬ��ʱ��
extern CString g_sLangID_Native_breaker4HoldTime;
extern CString g_sLangTxt_Native_breaker4HoldTime;//����4����ʱ��
extern CString g_sLangID_Native_Grid_Vol;
extern CString g_sLangTxt_Native_Grid_Vol;//�������ѹGrid_Vol
extern CString g_sLangID_Native_Grid_Freq;
extern CString g_sLangTxt_Native_Grid_Freq;//������Ƶ��Grid_Freq
extern CString g_sLangID_Native_syncSignal;
extern CString g_sLangTxt_Native_syncSignal;//ͬ���ź�
extern CString g_sLangID_Native_boostSignal;
extern CString g_sLangTxt_Native_boostSignal;//��ѹ�ź�
extern CString g_sLangID_Native_boostFreqSignal;
extern CString g_sLangTxt_Native_boostFreqSignal;//��Ƶ�ź�
extern CString g_sLangID_Native_reducePresSignal;
extern CString g_sLangTxt_Native_reducePresSignal;//��ѹ�ź�
extern CString g_sLangID_Native_reduceFreqSignal;
extern CString g_sLangTxt_Native_reduceFreqSignal;//��Ƶ�ź�
extern CString g_sLangID_Native_OutPut;
extern CString g_sLangTxt_Native_OutPut;//����%d
extern CString g_sLangID_Native_GvolChangeStep;
extern CString g_sLangTxt_Native_GvolChangeStep;//�������ѹ�仯����
extern CString g_sLangID_Native_GridVol_Exp;
extern CString g_sLangTxt_Native_GridVol_Exp;//�������ѹ(���ʽ)
extern CString g_sLangID_Native_GridFreq_Exp;
extern CString g_sLangTxt_Native_GridFreq_Exp;//������Ƶ��(���ʽ)
extern CString g_sLangID_Native_GvolChangeStepExp;
extern CString g_sLangTxt_Native_GvolChangeStepExp;//�������ѹ�仯����(���ʽ)
extern CString g_sLangID_Native_GfreqChangeStep;
extern CString g_sLangTxt_Native_GfreqChangeStep;//������Ƶ�ʱ仯����
extern CString g_sLangID_Native_GfreqChangeStepExp;
extern CString g_sLangTxt_Native_GfreqChangeStepExp;//������Ƶ�ʱ仯����(���ʽ)
extern CString g_sLangID_Native_FreqSlip;
extern CString g_sLangTxt_Native_FreqSlip;//Ƶ�ʻ���
extern CString g_sLangID_Native_VoltSlip_Exp;
extern CString g_sLangTxt_Native_VoltSlip_Exp;//��ѹ����(���ʽ)
extern CString g_sLangID_Native_FreqSlip_Exp;
extern CString g_sLangTxt_Native_FreqSlip_Exp;//Ƶ�ʻ���(���ʽ)
extern CString g_sLangID_Native_RegulatePulseWidth;
extern CString g_sLangTxt_Native_RegulatePulseWidth;//��ѹ����
extern CString g_sLangID_Native_FrequencyPulseWidth;
extern CString g_sLangTxt_Native_FrequencyPulseWidth;//��Ƶ����

//2
extern CString g_sLangID_Native_AngleStartPar1;
extern CString g_sLangTxt_Native_AngleStartPar1;//����ʼֵ
extern CString g_sLangID_Native_AngleEndPar1;
extern CString g_sLangTxt_Native_AngleEndPar1;//������ֵ
extern CString g_sLangID_Native_OscilPeriod1;
extern CString g_sLangTxt_Native_OscilPeriod1;//������
extern CString g_sLangID_Native_TripAccessPoint;
extern CString g_sLangTxt_Native_TripAccessPoint;//��բ�����
extern CString g_sLangID_Native_ReOscillat_ornot;
extern CString g_sLangTxt_Native_ReOscillat_ornot;//�Ƿ�������
extern CString g_sLangID_Native_SpeedChange;
extern CString g_sLangTxt_Native_SpeedChange; // �ٶȱ仯ѡ��
extern CString g_sLangID_Native_ImpedanceChange_ornot;
extern CString g_sLangTxt_Native_ImpedanceChange_ornot; //�Ƿ���迹
extern CString g_sLangID_Native_ImpedanceRateChange;
extern CString g_sLangTxt_Native_ImpedanceRateChange; // �迹�仯��

extern CString g_sLangID_Native_zeroseq_comp_calculat1;
extern CString g_sLangTxt_Native_zeroseq_comp_calculat1;//���򲹳�ϵ�����㷽ʽ
extern CString g_sLangID_Native_ZeroSeqComp1;
extern CString g_sLangTxt_Native_ZeroSeqComp1;//���򲹳�ϵ��(|K0|$KR$|Z0/Z1|)
extern CString g_sLangID_Native_ZeroSeqComp2;
extern CString g_sLangTxt_Native_ZeroSeqComp2;//���򲹳�ϵ��(Phi(K0)$KX$Phi(Z0/Z1))
extern CString g_sLangID_Native_SysImpedAngle;
extern CString g_sLangTxt_Native_SysImpedAngle; // ϵͳ���迹��
extern CString g_sLangID_Native_TransImpedAngle;
extern CString g_sLangTxt_Native_TransImpedAngle; // ��ѹ���迹��
extern CString g_sLangID_Native_GeneTransImped;
extern CString g_sLangTxt_Native_GeneTransImped; // �������̬�迹

extern CString g_sLangID_Out4_Situation;
extern CString g_sLangTxt_Out4_Situation;//����4״̬
extern CString g_sLangID_Out5_Situation;
extern CString g_sLangTxt_Out5_Situation;//����5״̬
extern CString g_sLangID_Out6_Situation;
extern CString g_sLangTxt_Out6_Situation;//����6״̬
extern CString g_sLangID_Out7_Situation;
extern CString g_sLangTxt_Out7_Situation;//����7״̬
extern CString g_sLangID_Out8_Situation;
extern CString g_sLangTxt_Out8_Situation;//����8״̬
extern CString g_sLangID_Native_ProtRelayTime1;
extern CString g_sLangTxt_Native_ProtRelayTime1;//��������ʱ��
extern CString g_sLangID_Native_AccelSigOutTime1;
extern CString g_sLangTxt_Native_AccelSigOutTime1;//�����źų���ʱ��
extern CString g_sLangID_Native_DecelSigOutTime1;
extern CString g_sLangTxt_Native_DecelSigOutTime1;//�����źų���ʱ��

//3
extern CString g_sLangID_Native_VariablePhaseChange;
extern CString g_sLangTxt_Native_VariablePhaseChange; // �ݱ����
extern CString g_sLangID_Native_PreTestTimeS;
extern CString g_sLangTxt_Native_PreTestTimeS; // ����ǰʱ��(��)
extern CString g_sLangID_Native_FaultPreTimeS;
extern CString g_sLangTxt_Native_FaultPreTimeS; // ����ǰʱ��(��)
extern CString g_sLangID_Native_FaultPreUIPhaseAngle;
extern CString g_sLangTxt_Native_FaultPreUIPhaseAngle;//����ǰ��ѹ�������(U-I)
extern CString g_sLangID_Native_VariableMode0123;
extern CString g_sLangTxt_Native_VariableMode0123; //�ݱ�ģʽ(0-����ģʽ1-��ѹ�ݱ� 2-�����ݱ� 3-��������ģʽ)
extern CString g_sLangID_Native_TestReturnCoefficient;
extern CString g_sLangTxt_Native_TestReturnCoefficient;//���Է���ϵ��
extern CString g_sLangID_Native_TestChannelType;
extern CString g_sLangTxt_Native_TestChannelType;//����ͨ������
extern CString g_sLangID_Native_VariableType;
extern CString g_sLangTxt_Native_VariableType;//�ݱ�����

extern CString g_sLangID_Native_PhaseShiftDir01;
extern CString g_sLangTxt_Native_PhaseShiftDir01; //��λ�ݱ䷽��(0:��ʱ�� 1:˳ʱ��)
extern CString g_sLangID_Native_IBeforeChange;
extern CString g_sLangTxt_Native_IBeforeChange;//�仯ǰ������ֵ
extern CString g_sLangID_Native_FaultGroup1VAmp;
extern CString g_sLangTxt_Native_FaultGroup1VAmp; //����̬��1��ѹ��ֵ
extern CString g_sLangID_Native_FaultGroup1IAmp;
extern CString g_sLangTxt_Native_FaultGroup1IAmp;//����̬��1������ֵ
extern CString g_sLangID_Native_FaultGroupIPhaseDiff;
extern CString g_sLangTxt_Native_FaultGroupIPhaseDiff; //����̬��������ǲ�
extern CString g_sLangID_Native_FaultGroupFreq;
extern CString g_sLangTxt_Native_FaultGroupFreq;//����̬Ƶ��

extern CString g_sLangID_Native_VActionValueAbsErr;
extern CString g_sLangTxt_Native_VActionValueAbsErr;//��ѹ����ֵ�������
extern CString g_sLangID_Native_VActionValueRelErr;
extern CString g_sLangTxt_Native_VActionValueRelErr;//��ѹ����ֵ������
extern CString g_sLangID_Native_VActionValueErrLogic;
extern CString g_sLangTxt_Native_VActionValueErrLogic;//��ѹ����ֵ����ж��߼�
extern CString g_sLangID_Native_IActionValueAbsErr;
extern CString g_sLangTxt_Native_IActionValueAbsErr;//��������ֵ�������
extern CString g_sLangID_Native_IActionValueRelErr;
extern CString g_sLangTxt_Native_IActionValueRelErr;//��������ֵ������
extern CString g_sLangID_Native_IActionValueErrLogic;
extern CString g_sLangTxt_Native_IActionValueErrLogic;//��������ֵ����ж��߼�
extern CString g_sLangID_Native_CoefficientAbsErr;
extern CString g_sLangTxt_Native_CoefficientAbsErr; //����ϵ���������
extern CString g_sLangID_Native_CoefficientRelErr;
extern CString g_sLangTxt_Native_CoefficientRelErr;//����ϵ��������
extern CString g_sLangID_Native_CoefficientErrLogic;
extern CString g_sLangTxt_Native_CoefficientErrLogic;//����ϵ������ж��߼�


extern CString g_sLangID_Native_relativeErr;
extern CString g_sLangTxt_Native_relativeErr;//��������Ч
extern CString g_sLangID_Native_criteria_logic;
extern CString g_sLangTxt_Native_criteria_logic;//�о��߼�
extern CString g_sLangID_Native_VActionValueErr;
extern CString g_sLangTxt_Native_VActionValueErr;//��ѹ����ֵ���
extern CString g_sLangID_Native_IActionValueErr;
extern CString g_sLangTxt_Native_IActionValueErr;//��������ֵ���
extern CString g_sLangID_Native_input1_ActionVal;
extern CString g_sLangTxt_Native_input1_ActionVal;//����1����ֵ
extern CString g_sLangID_Native_input2_ActionVal;
extern CString g_sLangTxt_Native_input2_ActionVal;//����2����ֵ
extern CString g_sLangID_Native_input3_ActionVal;
extern CString g_sLangTxt_Native_input3_ActionVal;//����3����ֵ
extern CString g_sLangID_Native_input4_ActionVal;
extern CString g_sLangTxt_Native_input4_ActionVal;//����4����ֵ
extern CString g_sLangID_Native_input5_ActionVal;
extern CString g_sLangTxt_Native_input5_ActionVal;//����5����ֵ
extern CString g_sLangID_Native_input6_ActionVal;
extern CString g_sLangTxt_Native_input6_ActionVal;//����6����ֵ
extern CString g_sLangID_Native_input7_ActionVal;
extern CString g_sLangTxt_Native_input7_ActionVal;//����7����ֵ
extern CString g_sLangID_Native_input8_ActionVal;
extern CString g_sLangTxt_Native_input8_ActionVal;//����8����ֵ


//4
extern CString g_sLangID_Native_YNaging_test;
extern CString g_sLangTxt_Native_YNaging_test;//�Ƿ��ϻ�����
extern CString g_sLangID_Native_varchannel_select;
extern CString g_sLangTxt_Native_varchannel_select;//�ݱ�ͨ��ѡ��
extern CString g_sLangID_Native_vartype_select;
extern CString g_sLangTxt_Native_vartype_select;//�ݱ�����ѡ��
extern CString g_sLangID_Native_change_mode;
extern CString g_sLangTxt_Native_change_mode;//�仯ģʽ
extern CString g_sLangID_Native_step_time;
extern CString g_sLangTxt_Native_step_time;//ÿ��ʱ��
extern CString g_sLangID_Native_trigger_delay;
extern CString g_sLangTxt_Native_trigger_delay;//������ʱ
extern CString g_sLangID_Native_YN_locked;
extern CString g_sLangTxt_Native_YN_locked;//�Ƿ�����
extern CString g_sLangID_Native_YN_autoevo;
extern CString g_sLangTxt_Native_YN_autoevo;//�Ƿ��Զ��ݱ�
extern CString g_sLangID_Native_max_outputtime;
extern CString g_sLangTxt_Native_max_outputtime;//����ʱ��(s)
extern CString g_sLangID_Native_acttuning_time;
extern CString g_sLangTxt_Native_acttuning_time;//��������ʱ��
extern CString g_sLangID_Native_ActTimeValueAbsErr;
extern CString g_sLangTxt_Native_ActTimeValueAbsErr;//����ʱ��ֵ�������
extern CString g_sLangID_Native_ActTimeValueRelErr;
extern CString g_sLangTxt_Native_ActTimeValueRelErr;//����ʱ��ֵ������
extern CString g_sLangID_Native_ActTimeValueErrLogic;
extern CString g_sLangTxt_Native_ActTimeValueErrLogic;//����ʱ������ж��߼�
extern CString g_sLangID_Native_PhaseActValueAbsErr;
extern CString g_sLangTxt_Native_PhaseActValueAbsErr;//��λ����ֵ�������
extern CString g_sLangID_Native_PhaseActValueRelErr;
extern CString g_sLangTxt_Native_PhaseActValueRelErr;//��λ����ֵ������
extern CString g_sLangID_Native_PhaseActValueErrLogic;
extern CString g_sLangTxt_Native_PhaseActValueErrLogic;//��λ����ֵ����ж��߼�
extern CString g_sLangID_Native_action_mark;
extern CString g_sLangTxt_Native_action_mark;//�������
extern CString g_sLangID_Native_result_status;
extern CString g_sLangTxt_Native_result_status;//���״̬
extern CString g_sLangID_Native_extend;
extern CString g_sLangTxt_Native_extend;//��չ%d

//5
extern CString g_sLangID_Native_KeepTime;
extern CString g_sLangTxt_Native_KeepTime;//����ʱ��
extern CString g_sLangID_Native_SteadyTime;
extern CString g_sLangTxt_Native_SteadyTime;//��̬ʱ��
extern CString g_sLangID_Native_LowFreActValue;
extern CString g_sLangTxt_Native_LowFreActValue;//��Ƶ����ֵ
extern CString g_sLangID_Native_InputASelect;
extern CString g_sLangTxt_Native_InputASelect;//����A-Jѡ��
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
extern CString g_sLangTxt_Native_FreInitialValue;//Ƶ�ʱ仯ʼֵ
extern CString g_sLangID_Native_FreFinalValue;
extern CString g_sLangTxt_Native_FreFinalValue;//Ƶ�ʱ仯��ֵ
extern CString g_sLangID_Native_FreChangeStep;
extern CString g_sLangTxt_Native_FreChangeStep;//Ƶ�ʱ仯����
extern CString g_sLangID_Native_FreFinal;
extern CString g_sLangTxt_Native_FreFinal;//Ƶ����ֵ
extern CString g_sLangID_Native_IChangePhase;
extern CString g_sLangTxt_Native_IChangePhase;//�����仯��
extern CString g_sLangID_Native_SearchslipVal;
extern CString g_sLangTxt_Native_SearchslipVal;//��ǰ��������ֵ(dfdt)
extern CString g_sLangID_Native_KeepTimeExp;
extern CString g_sLangTxt_Native_KeepTimeExp;//����ʱ��(���ʽ)

extern CString g_sLangID_Native_FreInitialValueExp;
extern CString g_sLangTxt_Native_FreInitialValueExp;//Ƶ�ʱ仯ʼֵ(���ʽ)
extern CString g_sLangID_Native_FreFinalValueExp;
extern CString g_sLangTxt_Native_FreFinalValueExp;//Ƶ�ʱ仯��ֵ(���ʽ)
extern CString g_sLangID_Native_FreChangeStepExp;
extern CString g_sLangTxt_Native_FreChangeStepExp;//Ƶ�ʱ仯����(���ʽ)
extern CString g_sLangID_Native_SlipInitialValueExp;
extern CString g_sLangTxt_Native_SlipInitialValueExp;//����仯ʼֵ(���ʽ)
extern CString g_sLangID_Native_SlipFinalValueExp;
extern CString g_sLangTxt_Native_SlipFinalValueExp;//����仯��ֵ(���ʽ)
extern CString g_sLangID_Native_SlipChangeStepExp;
extern CString g_sLangTxt_Native_SlipChangeStepExp;//����仯����(���ʽ)
extern CString g_sLangID_Native_IInitialValueExp;
extern CString g_sLangTxt_Native_IInitialValueExp;//�����仯ʼֵ(���ʽ)
extern CString g_sLangID_Native_IFinalValueExp;
extern CString g_sLangTxt_Native_IFinalValueExp;//�����仯��ֵ(���ʽ)
extern CString g_sLangID_Native_IChangeStepExp;
extern CString g_sLangTxt_Native_IChangeStepExp;//�����仯����(���ʽ)
extern CString g_sLangID_Native_VInitialValueExp;
extern CString g_sLangTxt_Native_VInitialValueExp;//��ѹ�仯ʼֵ(���ʽ)
extern CString g_sLangID_Native_VFinalValueExp;
extern CString g_sLangTxt_Native_VFinalValueExp;//��ѹ�仯��ֵ(���ʽ)
extern CString g_sLangID_Native_VChangeStepExp;
extern CString g_sLangTxt_Native_VChangeStepExp;//��ѹ�仯����(���ʽ)
extern CString g_sLangID_Native_FreActValue;
extern CString g_sLangTxt_Native_FreActValue;//Ƶ�ʶ���ֵ
extern CString g_sLangID_Native_LowCycleActDesc;
extern CString g_sLangTxt_Native_LowCycleActDesc;//���ܶ�������
extern CString g_sLangID_Native_SlipActValue;
extern CString g_sLangTxt_Native_SlipActValue;//�����ֵ
extern CString g_sLangID_Native_IBlockValue;
extern CString g_sLangTxt_Native_IBlockValue;//��������ֵ
extern CString g_sLangID_Native_VBlockValue;
extern CString g_sLangTxt_Native_VBlockValue;//��ѹ����ֵ

//6
extern CString g_sLangID_Native_VChangeRate_blockVal;
extern CString g_sLangTxt_Native_VChangeRate_blockVal;//��ѹ�仯�ʱ���ֵ
extern CString g_sLangID_Native_SearchslipVal2;
extern CString g_sLangTxt_Native_SearchslipVal2;//��ǰ��������ֵ(dvdt)
extern CString g_sLangID_Native_LowVActionDesc;
extern CString g_sLangTxt_Native_LowVActionDesc;//��ѹ��������

extern CString g_sLangID_Native_Uab1Amp;
extern CString g_sLangTxt_Native_Uab1Amp;//Uab1��ֵ
extern CString g_sLangID_Native_Uab1Ph;
extern CString g_sLangTxt_Native_Uab1Ph;//Uab1��λ
extern CString g_sLangID_Native_Uab1Fre;
extern CString g_sLangTxt_Native_Uab1Fre;//Uab1Ƶ��
extern CString g_sLangID_Native_3U0_1Amp;
extern CString g_sLangTxt_Native_3U0_1Amp;//3U0_1��ֵ
extern CString g_sLangID_Native_3U0_1Ph;
extern CString g_sLangTxt_Native_3U0_1Ph;//3U0_1��λ
extern CString g_sLangID_Native_3U0_1Fre;
extern CString g_sLangTxt_Native_3U0_1Fre;//3U0_1Ƶ��
extern CString g_sLangID_Native_Uab2Amp;
extern CString g_sLangTxt_Native_Uab2Amp;//Uab2��ֵ
extern CString g_sLangID_Native_Uab2Ph;
extern CString g_sLangTxt_Native_Uab2Ph;//Uab2��λ
extern CString g_sLangID_Native_Uab2Fre;
extern CString g_sLangTxt_Native_Uab2Fre;//Uab2Ƶ��
extern CString g_sLangID_Native_3U0_2Amp;
extern CString g_sLangTxt_Native_3U0_2Amp;//3U0_2��ֵ
extern CString g_sLangID_Native_3U0_2Ph;
extern CString g_sLangTxt_Native_3U0_2Ph;//3U0_2��λ
extern CString g_sLangID_Native_3U0_2Fre;
extern CString g_sLangTxt_Native_3U0_2Fre;//3U0_2Ƶ��
extern CString g_sLangID_Native_Ia1Fre;
extern CString g_sLangTxt_Native_Ia1Fre;//Ia1Ƶ��
extern CString g_sLangID_Native_Ib1Fre;
extern CString g_sLangTxt_Native_Ib1Fre;//Ib1Ƶ��
extern CString g_sLangID_Native_Ic1Fre;
extern CString g_sLangTxt_Native_Ic1Fre;//Ic1Ƶ��
extern CString g_sLangID_Native_Ia2Fre;
extern CString g_sLangTxt_Native_Ia2Fre;//Ia2Ƶ��
extern CString g_sLangID_Native_Ib2Fre;
extern CString g_sLangTxt_Native_Ib2Fre;//Ib2Ƶ��
extern CString g_sLangID_Native_Ic2Fre;
extern CString g_sLangTxt_Native_Ic2Fre;//Ic2Ƶ��

extern CString g_sLangID_Native_AuxiDCI;
extern CString g_sLangTxt_Native_AuxiDCI;//����ֱ������
extern CString g_sLangID_Native_AuxiDCV;
extern CString g_sLangTxt_Native_AuxiDCV;//����ֱ����ѹ

//
extern CString g_sLangID_Native_syspowerImp;
extern CString g_sLangTxt_Native_syspowerImp;//ϵͳ��Դ�迹
extern CString g_sLangID_Native_syspowerImpangle;
extern CString g_sLangTxt_Native_syspowerImpangle;//ϵͳ��Դ�迹��
extern CString g_sLangID_Native_syscomputModel012;
extern CString g_sLangTxt_Native_syscomputModel012;//ϵͳ����ģ��(0-�������� 1-��ѹ���� 2-ϵͳ�迹����)
extern CString g_sLangID_Native_fault_switchtime;
extern CString g_sLangTxt_Native_fault_switchtime;//����ת��ʱ��
extern CString g_sLangID_Native_switchErrtype;
extern CString g_sLangTxt_Native_switchErrtype;//ת����������
extern CString g_sLangID_Native_switchErr_shortImp;
extern CString g_sLangTxt_Native_switchErr_shortImp;//ת�����϶�·�迹
extern CString g_sLangID_Native_switchErr_shortImpAng;
extern CString g_sLangTxt_Native_switchErr_shortImpAng;//ת�����϶�·�迹��
extern CString g_sLangID_Native_switchErr_shortI;
extern CString g_sLangTxt_Native_switchErr_shortI;//ת�����϶�·����
extern CString g_sLangID_Native_switchErr_shortV;
extern CString g_sLangTxt_Native_switchErr_shortV;//ת�����϶�·��ѹ
extern CString g_sLangID_Native_switchErr_direction;
extern CString g_sLangTxt_Native_switchErr_direction;//ת�����Ϲ��Ϸ���
extern CString g_sLangID_Native_testprocess;
extern CString g_sLangTxt_Native_testprocess;//�������
extern CString g_sLangID_Native_redundancy_mode;
extern CString g_sLangTxt_Native_redundancy_mode;//�غϷ�ʽ
extern CString g_sLangID_Native_redundancy_duration;
extern CString g_sLangTxt_Native_redundancy_duration;//�غϳ���ʱ��
extern CString g_sLangID_Native_postswitch_duration;
extern CString g_sLangTxt_Native_postswitch_duration;//����ٿ������������ʱ��


extern CString g_sLangID_Native_change_startangle;
extern CString g_sLangTxt_Native_change_startangle;//�仯��ʼ�Ƕ�
extern CString g_sLangID_Native_change_endangle;
extern CString g_sLangTxt_Native_change_endangle;//�仯��ֹ�Ƕ�
extern CString g_sLangID_Native_impedanceAng_measured;
extern CString g_sLangTxt_Native_impedanceAng_measured;//�����迹�Ƕȶ�ֵ
extern CString g_sLangID_Native_search_way;
extern CString g_sLangTxt_Native_search_way;//������ʽ
extern CString g_sLangID_Native_Zsearch_startAng;
extern CString g_sLangTxt_Native_Zsearch_startAng;//Z�������Ƕ�
extern CString g_sLangID_Native_Zsearch_startAct;
extern CString g_sLangTxt_Native_Zsearch_startAct;//Z������㶯��
extern CString g_sLangID_Native_ZAng_currentVal;
extern CString g_sLangTxt_Native_ZAng_currentVal;//Z��ǰֵ�Ƕ�
extern CString g_sLangID_Native_Zsearch_endAng;
extern CString g_sLangTxt_Native_Zsearch_endAng;//Z�����յ�Ƕ�
extern CString g_sLangID_Native_Zsearch_endAct;
extern CString g_sLangTxt_Native_Zsearch_endAct;//Z�����յ㶯��
extern CString g_sLangID_Native_action_impedance;
extern CString g_sLangTxt_Native_action_impedance;//�����迹
extern CString g_sLangID_Native_action_impedanceAng;
extern CString g_sLangTxt_Native_action_impedanceAng;//�����迹��
extern CString g_sLangID_Native_Desc_impedance_Act;
extern CString g_sLangTxt_Native_Desc_impedance_Act;//�迹��������

//
extern CString g_sLangID_Native_impedance_setting;
extern CString g_sLangTxt_Native_impedance_setting;//�迹��ֵ
extern CString g_sLangID_Native_impedance_setExp;
extern CString g_sLangTxt_Native_impedance_setExp;//�迹��ֵ(���ʽ)

extern CString g_sLangID_Native_ZeroSeqCompExp;
extern CString g_sLangTxt_Native_ZeroSeqCompExp;//���򲹳�ϵ����﷽ʽ
extern CString g_sLangID_Native_ZeroSeqComp_RERL;
extern CString g_sLangTxt_Native_ZeroSeqComp_RERL;//���򲹳�ϵ��RE/RL
extern CString g_sLangID_Native_ZeroSeqComp_XEXL;
extern CString g_sLangTxt_Native_ZeroSeqComp_XEXL;//���򲹳�ϵ��XE/XL
extern CString g_sLangID_Native_load_current;
extern CString g_sLangTxt_Native_load_current;//���ɵ���
extern CString g_sLangID_Native_loadpowerAng;
extern CString g_sLangTxt_Native_loadpowerAng;//���ɹ���
extern CString g_sLangID_Native_PT_installPos;
extern CString g_sLangTxt_Native_PT_installPos;//PT��װλ��
extern CString g_sLangID_Native_closeAngmode01;
extern CString g_sLangTxt_Native_closeAngmode01;//��բ�Ƿ�ʽ( 0-��� 1-��ֵ)
extern CString g_sLangID_Native_closing_angle;
extern CString g_sLangTxt_Native_closing_angle;//��բ��
extern CString g_sLangID_Native_Vz_outputDef;
extern CString g_sLangTxt_Native_Vz_outputDef;//Vz�������
extern CString g_sLangID_Native_Vz_referPhase;
extern CString g_sLangTxt_Native_Vz_referPhase;//Vz�ο���
extern CString g_sLangID_Native_Vz_phase_angle;
extern CString g_sLangTxt_Native_Vz_phase_angle;//Vz���
extern CString g_sLangID_Native_reclose_timeset;
extern CString g_sLangTxt_Native_reclose_timeset;//�غ�բʱ�䶨ֵ
extern CString g_sLangID_Native_PostAccelerat_TimeSet;
extern CString g_sLangTxt_Native_PostAccelerat_TimeSet;//�����ʱ�䶨ֵ

extern CString g_sLangID_Native_auxiV_UxoutputMode;
extern CString g_sLangTxt_Native_auxiV_UxoutputMode;//������ѹUx�����ʽ
extern CString g_sLangID_Native_synchronous_VAmp;
extern CString g_sLangTxt_Native_synchronous_VAmp;//ͬ�ڵ�ѹ��ֵ(��ͬ�ڷ�ʽ��Ч)
extern CString g_sLangID_Native_synchronous_VPh;
extern CString g_sLangTxt_Native_synchronous_VPh;//ͬ�ڵ�ѹ��λ(��ͬ�ڷ�ʽ��Ч)
extern CString g_sLangID_Native_pressTestVal;
extern CString g_sLangTxt_Native_pressTestVal;//��ѹ����ֵ
extern CString g_sLangID_Native_NOpressTestVal;
extern CString g_sLangTxt_Native_NOpressTestVal;//��ѹ����ֵ
extern CString g_sLangID_Native_openflip_Control;
extern CString g_sLangTxt_Native_openflip_Control;//������ת���Ʒ�ʽ
extern CString g_sLangID_Native_openflip_delay;
extern CString g_sLangTxt_Native_openflip_delay;//������ת��ʱ
extern CString g_sLangID_Native_input_selection;
extern CString g_sLangTxt_Native_input_selection;//������ѡ��
extern CString g_sLangID_Native_superimposed_ornot1;
extern CString g_sLangTxt_Native_superimposed_ornot1;//�Ƿ���ӷ����ڷ���
extern CString g_sLangID_Native_jumpctrl;
extern CString g_sLangTxt_Native_jumpctrl;//�����źſ���
extern CString g_sLangID_Native_timectrl;
extern CString g_sLangTxt_Native_timectrl;//ʱ�����
extern CString g_sLangID_Native_totalweight;
extern CString g_sLangTxt_Native_totalweight;//���أ�����+���أ�
extern CString g_sLangID_Native_tripleweight;
extern CString g_sLangTxt_Native_tripleweight;//����
extern CString g_sLangID_Native_norepeat;
extern CString g_sLangTxt_Native_norepeat;//���غ�
extern CString g_sLangID_Native_Totransformer;
extern CString g_sLangTxt_Native_Totransformer;//ָ���ѹ��
extern CString g_sLangID_Native_lagrange;
extern CString g_sLangTxt_Native_lagrange;//�������ղ�ֵ��
extern CString g_sLangID_Native_linear;
extern CString g_sLangTxt_Native_linear;//���Բ�ֵ��
extern CString g_sLangID_Native_faultvoltype;
extern CString g_sLangTxt_Native_faultvoltype;//���ϵ�ѹ����

extern CString g_sLangID_Native_Difsetting;
extern CString g_sLangTxt_Native_Difsetting;//���ֵ������ʽ
extern CString g_sLangID_Native_DifCurChoose;
extern CString g_sLangTxt_Native_DifCurChoose;//���׼����ѡ��
extern CString g_sLangID_Native_harmonicnumber;
extern CString g_sLangTxt_Native_harmonicnumber;//г������ѡ��
extern CString g_sLangID_Native_CuroutputPhase;
extern CString g_sLangTxt_Native_CuroutputPhase;//���������
extern CString g_sLangID_Native_PhaseAshort;
extern CString g_sLangTxt_Native_PhaseAshort;//A���·
extern CString g_sLangID_Native_PhaseBshort;
extern CString g_sLangTxt_Native_PhaseBshort;//B���·
extern CString g_sLangID_Native_PhaseCshort;
extern CString g_sLangTxt_Native_PhaseCshort;//C���·
extern CString g_sLangID_Native_PhaseABCshort;
extern CString g_sLangTxt_Native_PhaseABCshort;//ABC���·

//�ڰ�����
extern CString g_sLangID_Native_ExceptionMsgSet;
extern CString g_sLangTxt_Native_ExceptionMsgSet;
//����ͼ
extern CString g_sLangID_Native_CharacteristicGraph;
extern CString g_sLangTxt_Native_CharacteristicGraph;
//��ѹI�ζ�ֵ
extern CString g_sLangID_Native_OV1SetValue;
extern CString g_sLangTxt_Native_OV1SetValue;
//��ѹII�ζ�ֵ

extern CString g_sLangID_Native_OV2SetValue;
extern CString g_sLangTxt_Native_OV2SetValue;
//��ѹIII�ζ�ֵ
extern CString g_sLangID_Native_OV3SetValue;
extern CString g_sLangTxt_Native_OV3SetValue;
//��ѹIV�ζ�ֵ
extern CString g_sLangID_Native_OV4SetValue;
extern CString g_sLangTxt_Native_OV4SetValue;
//��ѹI��ʱ��
extern CString g_sLangID_Native_OV1Time;
extern CString g_sLangTxt_Native_OV1Time;
//��ѹII��ʱ��
extern CString g_sLangID_Native_OV2Time;
extern CString g_sLangTxt_Native_OV2Time;
//��ѹIII��ʱ��
extern CString g_sLangID_Native_OV3Time;
extern CString g_sLangTxt_Native_OV3Time;
//��ѹIV��ʱ��
extern CString g_sLangID_Native_OV4Time;
extern CString g_sLangTxt_Native_OV4Time;
//�Ƿ�ģ���·����ʱ
extern CString g_sLangID_Native_SimBrkDel;
extern CString g_sLangTxt_Native_SimBrkDel;
//��·����բ��ʱ
extern CString g_sLangID_Native_BrkTripDel;
extern CString g_sLangTxt_Native_BrkTripDel;
//��·����բ��ʱ
extern CString g_sLangID_Native_BrkClsDel;
extern CString g_sLangTxt_Native_BrkClsDel;
//��ѹ����
extern CString g_sLangID_Native_VoltType;
extern CString g_sLangTxt_Native_VoltType;
//����������ѹ(���ʽ)
extern CString g_sLangID_Native_ActionVoltExpr;
extern CString g_sLangTxt_Native_ActionVoltExpr;
//A�ද��ʱ��
extern CString g_sLangID_Native_PhaseATime;
extern CString g_sLangTxt_Native_PhaseATime;
//B�ද��ʱ��
extern CString g_sLangID_Native_PhaseBTime;
extern CString g_sLangTxt_Native_PhaseBTime;
//C�ද��ʱ��
extern CString g_sLangID_Native_PhaseCTime;
extern CString g_sLangTxt_Native_PhaseCTime;
//�غ�բ����ʱ��
extern CString g_sLangID_Native_RecloseTime;
extern CString g_sLangTxt_Native_RecloseTime;
//����E����ʱ��
extern CString g_sLangID_Native_InputETime;
extern CString g_sLangTxt_Native_InputETime;
//����F����ʱ��
extern CString g_sLangID_Native_InputFTime;
extern CString g_sLangTxt_Native_InputFTime;
//����G����ʱ��
extern CString g_sLangID_Native_InputGTime;
extern CString g_sLangTxt_Native_InputGTime;
//����H����ʱ��
extern CString g_sLangID_Native_InputHTime;
extern CString g_sLangTxt_Native_InputHTime;
//����A��������
extern CString g_sLangID_Native_InputADesc;
extern CString g_sLangTxt_Native_InputADesc;
//����B��������
extern CString g_sLangID_Native_InputBDesc;
extern CString g_sLangTxt_Native_InputBDesc;
//����C��������
extern CString g_sLangID_Native_InputCDesc;
extern CString g_sLangTxt_Native_InputCDesc;
//�غ�բ��������
extern CString g_sLangID_Native_ReclActDesc;
extern CString g_sLangTxt_Native_ReclActDesc;
//����ٶ���ʱ��
extern CString g_sLangID_Native_PostAccTime;
extern CString g_sLangTxt_Native_PostAccTime;
//����ٶ�������
extern CString g_sLangID_Native_PostAccDesc;
extern CString g_sLangTxt_Native_PostAccDesc;
//ʵ�ʶ�·����
extern CString g_sLangID_Native_ActShortCur;
extern CString g_sLangTxt_Native_ActShortCur;
//ʵ�ʶ�·��ѹ
extern CString g_sLangID_Native_ActShortVol;
extern CString g_sLangTxt_Native_ActShortVol;
//��ѹֵ
extern CString g_sLangID_Native_OverVoltVal;
extern CString g_sLangTxt_Native_OverVoltVal;
//Ua��ֵ
extern CString g_sLangID_Native_UaInitVal;
extern CString g_sLangTxt_Native_UaInitVal;
//Ub��ֵ
extern CString g_sLangID_Native_UbInitVal;
extern CString g_sLangTxt_Native_UbInitVal;
//Uc��ֵ
extern CString g_sLangID_Native_UcInitVal;
extern CString g_sLangTxt_Native_UcInitVal;
//Uz��ֵ
extern CString g_sLangID_Native_UzInitVal;
extern CString g_sLangTxt_Native_UzInitVal;
//Ia��ֵ
extern CString g_sLangID_Native_IaInitVal;
extern CString g_sLangTxt_Native_IaInitVal;
//Ib��ֵ
extern CString g_sLangID_Native_IbInitVal;
extern CString g_sLangTxt_Native_IbInitVal;
//Ic��ֵ
extern CString g_sLangID_Native_IcInitVal;
extern CString g_sLangTxt_Native_IcInitVal;
//���߶���
extern CString g_sLangID_Native_CurveSegments;
extern CString g_sLangTxt_Native_CurveSegments;
//�ݱ�ͨ��
extern CString g_sLangID_Native_VarChnl;
extern CString g_sLangTxt_Native_VarChnl;
//��ʱ����
extern CString g_sLangID_Native_TimingCurve;
extern CString g_sLangTxt_Native_TimingCurve;
//�ݱ�ѡ��
extern CString g_sLangID_Native_VarSel;
extern CString g_sLangTxt_Native_VarSel;
//�ݱ�����(0-б��1-����ʱ��2-��ֵ)
extern CString g_sLangID_Native_TransType;
extern CString g_sLangTxt_Native_TransType;
//�ݱ�����ѡ��
extern CString g_sLangID_Native_CurveSelect;
extern CString g_sLangTxt_Native_CurveSelect;
//�ݱ�ʼֵ
extern CString g_sLangID_Native_StartValue;
extern CString g_sLangTxt_Native_StartValue;
//�ݱ���ֵ
extern CString g_sLangID_Native_EndValue;
extern CString g_sLangTxt_Native_EndValue;
//�ݱ䲽��
extern CString g_sLangID_Native_StepSize;
extern CString g_sLangTxt_Native_StepSize;
//����
extern CString g_sLangID_Native_Curve;
extern CString g_sLangTxt_Native_Curve;
//б��(A/ms)
extern CString g_sLangID_Native_Slope;
extern CString g_sLangTxt_Native_Slope;
//���ʱ��(ms)
extern CString g_sLangID_Native_OutputTimems;
extern CString g_sLangTxt_Native_OutputTimems;
//�������
extern CString g_sLangID_Native_SearchStart;
extern CString g_sLangTxt_Native_SearchStart;
//��ǰֵ
extern CString g_sLangID_Native_CurrentValue;
extern CString g_sLangTxt_Native_CurrentValue;
//�����յ�
extern CString g_sLangID_Native_SearchEnd;
extern CString g_sLangTxt_Native_SearchEnd;
//�������䳤��
extern CString g_sLangID_Native_SearchLen;
extern CString g_sLangTxt_Native_SearchLen;
//�Ƿ��Զ�����
extern CString g_sLangID_Native_AutoSearch;
extern CString g_sLangTxt_Native_AutoSearch;
//��ʽ�ƶ�����(Ir-Id)
extern CString g_sLangID_Native_ComplexBrakeCurrent;
extern CString g_sLangTxt_Native_ComplexBrakeCurrent;
//�������ֵ
extern CString g_sLangID_Native_DiffCurrentSetVal;
extern CString g_sLangTxt_Native_DiffCurrentSetVal;
//����(0-������� 1-С������)
extern CString g_sLangID_Native_DiffType;
extern CString g_sLangTxt_Native_DiffType;
//Ua��ֵ
extern CString g_sLangID_Native_UaAmplitude;
extern CString g_sLangTxt_Native_UaAmplitude;
//Ub��ֵ
extern CString g_sLangID_Native_UbAmplitude;
extern CString g_sLangTxt_Native_UbAmplitude;
//Uc��ֵ
extern CString g_sLangID_Native_UcAmplitude;
extern CString g_sLangTxt_Native_UcAmplitude;
//Ua��λ
extern CString g_sLangID_Native_UaPhase;
extern CString g_sLangTxt_Native_UaPhase;
//Ub��λ
extern CString g_sLangID_Native_UbPhase;
extern CString g_sLangTxt_Native_UbPhase;
//Uc��λ
extern CString g_sLangID_Native_UcPhase;
extern CString g_sLangTxt_Native_UcPhase;
//���1TA���
extern CString g_sLangID_Native_Gap1TARatio;
extern CString g_sLangTxt_Native_Gap1TARatio;
//���2TA���
extern CString g_sLangID_Native_Gap2TARatio;
extern CString g_sLangTxt_Native_Gap2TARatio;
//���3TA���
extern CString g_sLangID_Native_Gap3TARatio;
extern CString g_sLangTxt_Native_Gap3TARatio;
//���TA���
extern CString g_sLangID_Native_MaxTARatio;
extern CString g_sLangTxt_Native_MaxTARatio;
//��ż�����
extern CString g_sLangID_Native_DiffThreshCurrent;
extern CString g_sLangTxt_Native_DiffThreshCurrent;
//��ʽ����ϵ����ֵ
extern CString g_sLangID_Native_HighCompRatioCoef;
extern CString g_sLangTxt_Native_HighCompRatioCoef;
//��ʽ����ϵ����ֵ
extern CString g_sLangID_Native_LowCompRatioCoef;
extern CString g_sLangTxt_Native_LowCompRatioCoef;
//�����ֵ
extern CString g_sLangID_Native_DiffActionVal;
extern CString g_sLangTxt_Native_DiffActionVal;
//��ǰ����ֵ
extern CString g_sLangID_Native_CurrSearchVal;
extern CString g_sLangTxt_Native_CurrSearchVal;
//���������
extern CString g_sLangID_Native_DiffActionDesc;
extern CString g_sLangTxt_Native_DiffActionDesc;
//��ѹ����Ԫ��
extern CString g_sLangID_Native_VoltLockElem;
extern CString g_sLangTxt_Native_VoltLockElem;
//������ѹֵ
extern CString g_sLangID_Native_LockVoltValue;
extern CString g_sLangTxt_Native_LockVoltValue;
//�����ƶ�ϵ�����(0-��ֵ 1-��ֵ)
extern CString g_sLangID_Native_BrkCoeffType;
extern CString g_sLangTxt_Native_BrkCoeffType;
//�����Id(���ʽ)
extern CString g_sLangID_Native_DiffCurrentIds;
extern CString g_sLangTxt_Native_DiffCurrentIds;
//��ʽ�ƶ�����(Ir-Id)(���ʽ)
extern CString g_sLangID_Native_CompBrakeCurr;
extern CString g_sLangTxt_Native_CompBrakeCurr;
//Ir�ƶ�����
extern CString g_sLangID_Native_IrBrakeEq;
extern CString g_sLangTxt_Native_IrBrakeEq;
//��һ���ѹ��̬���ֵ
extern CString g_sLangID_Native_FirstVoltNormOutput;
extern CString g_sLangTxt_Native_FirstVoltNormOutput;
//�ڶ����ѹ��̬���ֵ
extern CString g_sLangID_Native_SecondVoltNormOutput;
extern CString g_sLangTxt_Native_SecondVoltNormOutput;
//��һ���ѹ����̬���������ֵ
extern CString g_sLangID_Native_VoltFaultState;
extern CString g_sLangTxt_Native_VoltFaultState;
//�ڶ����ѹ����̬���������ֵ
extern CString g_sLangID_Native_VoltFaultState2;
extern CString g_sLangTxt_Native_VoltFaultState2;
//ƽ��ϵ�����÷�ʽ
extern CString g_sLangID_Native_BalanceMode;
extern CString g_sLangTxt_Native_BalanceMode;
//��ѹ��ƽ��ϵ������ֵ
extern CString g_sLangID_Native_HVBalanceCoeff;
extern CString g_sLangTxt_Native_HVBalanceCoeff;
//��ѹ��ƽ��ϵ������ֵ
extern CString g_sLangID_Native_MVBalanceCoeff;
extern CString g_sLangTxt_Native_MVBalanceCoeff;
//��ѹ��ƽ��ϵ������ֵ
extern CString g_sLangID_Native_LVBalanceCoeff;
extern CString g_sLangTxt_Native_LVBalanceCoeff;
//��ѹ��CT���
extern CString g_sLangID_Native_HVCTRatio;
extern CString g_sLangTxt_Native_HVCTRatio;
//��ѹ��CT���
extern CString g_sLangID_Native_MVCTRatio;
extern CString g_sLangTxt_Native_MVCTRatio;
//��ѹ��CT���
extern CString g_sLangID_Native_LVCTRatio;
extern CString g_sLangTxt_Native_LVCTRatio;
//�������������
extern CString g_sLangID_Native_TestCoil;
extern CString g_sLangTxt_Native_TestCoil;
//�����ڲ���λУ����ʽ
extern CString g_sLangID_Native_ProtPhaseCorr;
extern CString g_sLangTxt_Native_ProtPhaseCorr;
//��׼�����趨ֵ
extern CString g_sLangID_Native_BaseCurrSet;
extern CString g_sLangTxt_Native_BaseCurrSet;
//��ٶϵ���
extern CString g_sLangID_Native_DiffQuickBreakCurr;
extern CString g_sLangTxt_Native_DiffQuickBreakCurr;
//�����ƶ��յ���
extern CString g_sLangID_Native_RatioBrakeTurnPts;
extern CString g_sLangTxt_Native_RatioBrakeTurnPts;
//�����ƶ��յ�1����
extern CString g_sLangID_Native_RatioBrakeTurn1Curr;
extern CString g_sLangTxt_Native_RatioBrakeTurn1Curr;
//�����ƶ��յ�2����
extern CString g_sLangID_Native_RatioBrakeTurn2Curr;
extern CString g_sLangTxt_Native_RatioBrakeTurn2Curr;
//�����ƶ��յ�3����
extern CString g_sLangID_Native_RatioBrakeTurn3Curr;
extern CString g_sLangTxt_Native_RatioBrakeTurn3Curr;
//г���ƶ�ϵ����ֵ
extern CString g_sLangID_Native_HarmonicBrakeCoeff;
extern CString g_sLangTxt_Native_HarmonicBrakeCoeff;
//г���ƶ�ϵ������
extern CString g_sLangID_Native_HarmonicBrakeDesc;
extern CString g_sLangTxt_Native_HarmonicBrakeDesc;
//A���������
extern CString g_sLangID_Native_PhaseACurrent;
extern CString g_sLangTxt_Native_PhaseACurrent;
//B���������
extern CString g_sLangID_Native_PhaseBCurrent;
extern CString g_sLangTxt_Native_PhaseBCurrent;
//C���������
extern CString g_sLangID_Native_PhaseCCurrent;
extern CString g_sLangTxt_Native_PhaseCCurrent;
//A��г������
extern CString g_sLangID_Native_PhaseAHarmCur;
extern CString g_sLangTxt_Native_PhaseAHarmCur;
//B��г������
extern CString g_sLangID_Native_BHarmonicCurrent;
extern CString g_sLangTxt_Native_BHarmonicCurrent;
//C��г������
extern CString g_sLangID_Native_CHarmonicCurrent;
extern CString g_sLangTxt_Native_CHarmonicCurrent;
//��һ���ѹ���ֵ
extern CString g_sLangID_Native_FirstGroupVoltageOut;
extern CString g_sLangTxt_Native_FirstGroupVoltageOut;
//�ڶ����ѹ���ֵ
extern CString g_sLangID_Native_SecondGroupVoltageOut;
extern CString g_sLangTxt_Native_SecondGroupVoltageOut;
//��ѹ��CT���߷�ʽ
extern CString g_sLangID_Native_HVCTConnectionMode;
extern CString g_sLangTxt_Native_HVCTConnectionMode;
//ƽ��ϵ�����㷽��
extern CString g_sLangID_Native_BalanceCoeffCalcMethod;
extern CString g_sLangTxt_Native_BalanceCoeffCalcMethod;
//���ⶨֵ
extern CString g_sLangID_Native_UnderTestValue;
extern CString g_sLangTxt_Native_UnderTestValue;
//�����迹��
extern CString g_sLangID_Native_FaultImpedanceAngle;
extern CString g_sLangTxt_Native_FaultImpedanceAngle;
//�Ƿ�ģ��PT����
extern CString g_sLangID_Native_PTLineSimulate;
extern CString g_sLangTxt_Native_PTLineSimulate;
//ģ��PT�������
extern CString g_sLangID_Native_PTLineSimPhase;
extern CString g_sLangTxt_Native_PTLineSimPhase;
//�仯ʼֵ(���ʽ)
extern CString g_sLangID_Native_VarStartValue;
extern CString g_sLangTxt_Native_VarStartValue;
//�仯��ֵ(���ʽ)
extern CString g_sLangID_Native_VarEndValue;
extern CString g_sLangTxt_Native_VarEndValue;
//����ʱ��(���ʽ)
extern CString g_sLangID_Native_StepTime;
extern CString g_sLangTxt_Native_StepTime;
//��·��ѹ(���ʽ)
extern CString g_sLangID_Native_ShortVolt;
extern CString g_sLangTxt_Native_ShortVolt;
//��·����(���ʽ)
extern CString g_sLangID_Native_ShortCurr;
extern CString g_sLangTxt_Native_ShortCurr;
//�߽��1(����)
extern CString g_sLangID_Native_BoundaryAngle1;
extern CString g_sLangTxt_Native_BoundaryAngle1;
//�߽��2(����)
extern CString g_sLangID_Native_BoundaryAngle2;
extern CString g_sLangTxt_Native_BoundaryAngle2;
//����ʱ��
extern CString g_sLangID_Native_StepTimes;
extern CString g_sLangTxt_Native_StepTimes;
//��·����
extern CString g_sLangID_Native_ShortCircuit;
extern CString g_sLangTxt_Native_ShortCircuit;
//�迹��
extern CString g_sLangID_Native_ImpedanceAngles;
extern CString g_sLangTxt_Native_ImpedanceAngles;
//�Ƿ���Է���ֵ
extern CString g_sLangID_Native_TestReturnValue;
extern CString g_sLangTxt_Native_TestReturnValue;
//�͵�ѹ(V)
extern CString g_sLangID_Native_LowVoltagev;
extern CString g_sLangTxt_Native_LowVoltagev;
//�����ѹ(V)
extern CString g_sLangID_Native_NegativeSeqVolt;
extern CString g_sLangTxt_Native_NegativeSeqVolt;
//��������(A)
extern CString g_sLangID_Native_ActionCurrent;
extern CString g_sLangTxt_Native_ActionCurrent;
//��ʱʱ��(s)
extern CString g_sLangID_Native_DelayTimes;
extern CString g_sLangTxt_Native_DelayTimes;
//��������С(��)
extern CString g_sLangID_Native_ActionAreaSize;
extern CString g_sLangTxt_Native_ActionAreaSize;
//�迹��(���ʽ)
extern CString g_sLangID_Native_ImpedanceAnglexp;
extern CString g_sLangTxt_Native_ImpedanceAnglexp;
//���������ģʽ
extern CString g_sLangID_Native_TestOutMode;
extern CString g_sLangTxt_Native_TestOutMode;
//���ѹֵ
extern CString g_sLangID_Native_RatedVoltVal;
extern CString g_sLangTxt_Native_RatedVoltVal;
//�����ֵ
extern CString g_sLangID_Native_RatedCurrVal;
extern CString g_sLangTxt_Native_RatedCurrVal;
//��%d��PTһ��ֵ
extern CString g_sLangID_Native_FirstPTVal;
extern CString g_sLangTxt_Native_FirstPTVal;
//��%d��PT����ֵ
extern CString g_sLangID_Native_SecPTVal;
extern CString g_sLangTxt_Native_SecPTVal;
//��%d��CTһ��ֵ
extern CString g_sLangID_Native_FirstCTVal;
extern CString g_sLangTxt_Native_FirstCTVal;
//��%d��CT����ֵ
extern CString g_sLangID_Native_SecCTVal;
extern CString g_sLangTxt_Native_SecCTVal;
//���������ʽ
extern CString g_sLangID_Native_MsgFormat;
extern CString g_sLangTxt_Native_MsgFormat;
//���ź��������
extern CString g_sLangID_Native_WeakSigOutSet;
extern CString g_sLangTxt_Native_WeakSigOutSet;
//1588���չ��
extern CString g_sLangID_Native_1588RecvOptPort;
extern CString g_sLangTxt_Native_1588RecvOptPort;
//1588ͬ������
extern CString g_sLangID_Native_1588SyncMech;
extern CString g_sLangTxt_Native_1588SyncMech;
//��������ѡ��(0-һ��ֵ,1-����ֵ)
extern CString g_sLangID_Native_ParamSel;
extern CString g_sLangTxt_Native_ParamSel;
//�������ѡ��(0-һ��ֵ,1-����ֵ)
extern CString g_sLangID_Native_MsgOutSel;
extern CString g_sLangTxt_Native_MsgOutSel;
//B���߼�(0-���߼�,1-���߼�)
extern CString g_sLangID_Native_BCodeLogics;
extern CString g_sLangTxt_Native_BCodeLogics;
//�������ӷ�ʽ(0-˫��,1-����)
extern CString g_sLangID_Native_FiberConn;
extern CString g_sLangTxt_Native_FiberConn;
//�����ģ��
extern CString g_sLangID_Native_GroupCurrMod;
extern CString g_sLangTxt_Native_GroupCurrMod;
//����ģ��λ��
extern CString g_sLangID_Native_CurrModPos;
extern CString g_sLangTxt_Native_CurrModPos;
//����ģ�鵵λֵ
extern CString g_sLangID_Native_CurrModGearVal;
extern CString g_sLangTxt_Native_CurrModGearVal;
//����ͨ�����˿ڵ�ѹ
extern CString g_sLangID_Native_CurrChanMaxVolt;
extern CString g_sLangTxt_Native_CurrChanMaxVolt;
//�ϲ���������
extern CString g_sLangID_Native_MergeCurrTerm;
extern CString g_sLangTxt_Native_MergeCurrTerm;
//����ģ������
extern CString g_sLangID_Native_CurrModCount;
extern CString g_sLangTxt_Native_CurrModCount;
//��������
extern CString g_sLangID_Native_WirelessNet;
extern CString g_sLangTxt_Native_WirelessNet;
//��������
extern CString g_sLangID_Native_WiredNet;
extern CString g_sLangTxt_Native_WiredNet;
//Lcd����ʱ��
extern CString g_sLangID_Native_LcdBacklightTime;
extern CString g_sLangTxt_Native_LcdBacklightTime;
//����������(ms)
extern CString g_sLangID_Native_TouchSensitivity;
extern CString g_sLangTxt_Native_TouchSensitivity;
//��������ֵ�������(A)
extern CString g_sLangID_Native_CurrentActionError;
extern CString g_sLangTxt_Native_CurrentActionError;
//��������ֵ������(%)
extern CString g_sLangID_Native_CurrentActionRelError;
extern CString g_sLangTxt_Native_CurrentActionRelError;
//��ѹ����ֵ�������(V)
extern CString g_sLangID_Native_VoltageActionError;
extern CString g_sLangTxt_Native_VoltageActionError;
//��ѹ����ֵ������(%)
extern CString g_sLangID_Native_VoltageActionRelError;
extern CString g_sLangTxt_Native_VoltageActionRelError;
//�迹����ֵ�������(��)
extern CString g_sLangID_Native_ImpedanceActionError;
extern CString g_sLangTxt_Native_ImpedanceActionError;
//�迹����ֵ������(%)
extern CString g_sLangID_Native_ImpedanceActionRelError;
extern CString g_sLangTxt_Native_ImpedanceActionRelError;
//����ʱ��������(s)
extern CString g_sLangID_Native_ActionTimeAbsError;
extern CString g_sLangTxt_Native_ActionTimeAbsError;
//����ʱ��������(%)
extern CString g_sLangID_Native_ActionTimeRelError;
extern CString g_sLangTxt_Native_ActionTimeRelError;
//��λ���ֵ(��)
extern CString g_sLangID_Native_PhaseErrorValue;
extern CString g_sLangTxt_Native_PhaseErrorValue;
//Ƶ�����ֵ(Hz)
extern CString g_sLangID_Native_FreqErrorValue;
extern CString g_sLangTxt_Native_FreqErrorValue;
//��ѹ�������ֵ(V/s)
extern CString g_sLangID_Native_VoltSlipErrorValue;
extern CString g_sLangTxt_Native_VoltSlipErrorValue;
//Ƶ�ʻ������ֵ(Hz/s)
extern CString g_sLangID_Native_FreqSlipErrorValue;
extern CString g_sLangTxt_Native_FreqSlipErrorValue;
//������ƶ�ϵ���������
extern CString g_sLangID_Native_DiffRatioBrakeAbsError;
extern CString g_sLangTxt_Native_DiffRatioBrakeAbsError;
//������ƶ�ϵ��������(%)
extern CString g_sLangID_Native_DiffRatioBrakeRelError;
extern CString g_sLangTxt_Native_DiffRatioBrakeRelError;
//�г���ƶ�ϵ���������
extern CString g_sLangID_Native_DiffHarmonicBrakeAbsError;
extern CString g_sLangTxt_Native_DiffHarmonicBrakeAbsError;
//�г���ƶ�ϵ��������(%)
extern CString g_sLangID_Native_DiffHarmonicBrakeRelError;
extern CString g_sLangTxt_Native_DiffHarmonicBrakeRelError;
//����ֱ����ѹֵ
extern CString g_sLangID_Native_AuxDcVoltageValue;
extern CString g_sLangTxt_Native_AuxDcVoltageValue;
//����ֱ������ֵ
extern CString g_sLangID_Native_AuxDcCurrentValue;
extern CString g_sLangTxt_Native_AuxDcCurrentValue;
//��ѹ���һ��ֵ(��1��)
extern CString g_sLangID_Native_VoltageRatioPrimary1;
extern CString g_sLangTxt_Native_VoltageRatioPrimary1;
//��ѹ���һ��ֵ(��2��)
extern CString g_sLangID_Native_VoltageRatioPrimary2;
extern CString g_sLangTxt_Native_VoltageRatioPrimary2;
//��ѹ���һ��ֵ(��3��)
extern CString g_sLangID_Native_VoltageRatioPrimary3;
extern CString g_sLangTxt_Native_VoltageRatioPrimary3;
//��ѹ���һ��ֵ(��4��)
extern CString g_sLangID_Native_VoltageRatioPrimary4;
extern CString g_sLangTxt_Native_VoltageRatioPrimary4;
//��ѹ���һ��ֵ(��5��)
extern CString g_sLangID_Native_VoltageRatioPrimary5;
extern CString g_sLangTxt_Native_VoltageRatioPrimary5;
//��ѹ���һ��ֵ(��6��)
extern CString g_sLangID_Native_VoltageRatioPrimary6;
extern CString g_sLangTxt_Native_VoltageRatioPrimary6;
//��ѹ��ȶ���ֵ(��1��)
extern CString g_sLangID_Native_VoltageRatioSecondary1;
extern CString g_sLangTxt_Native_VoltageRatioSecondary1;
//��ѹ��ȶ���ֵ(��2��)
extern CString g_sLangID_Native_VoltageRatioSecondary2;
extern CString g_sLangTxt_Native_VoltageRatioSecondary2;
//��ѹ��ȶ���ֵ(��3��)
extern CString g_sLangID_Native_VoltageRatioSecondary3;
extern CString g_sLangTxt_Native_VoltageRatioSecondary3;
//��ѹ��ȶ���ֵ(��4��)
extern CString g_sLangID_Native_VoltageRatioSecondary4;
extern CString g_sLangTxt_Native_VoltageRatioSecondary4;
//��ѹ��ȶ���ֵ(��5��)
extern CString g_sLangID_Native_VoltageRatioSecondary5;
extern CString g_sLangTxt_Native_VoltageRatioSecondary5;
//��ѹ��ȶ���ֵ(��6��)
extern CString g_sLangID_Native_VoltageRatioSecondary6;
extern CString g_sLangTxt_Native_VoltageRatioSecondary6;
//�������һ��ֵ(��1��)
extern CString g_sLangID_Native_CurrentRatioPrimary1;
extern CString g_sLangTxt_Native_CurrentRatioPrimary1;
//�������һ��ֵ(��2��)
extern CString g_sLangID_Native_CurrentRatioPrimary2;
extern CString g_sLangTxt_Native_CurrentRatioPrimary2;
//�������һ��ֵ(��3��)
extern CString g_sLangID_Native_CurrentRatioPrimary3;
extern CString g_sLangTxt_Native_CurrentRatioPrimary3;
//�������һ��ֵ(��4��)
extern CString g_sLangID_Native_CurrentRatioPrimary4;
extern CString g_sLangTxt_Native_CurrentRatioPrimary4;
//�������һ��ֵ(��5��)
extern CString g_sLangID_Native_CurrentRatioPrimary5;
extern CString g_sLangTxt_Native_CurrentRatioPrimary5;
//�������һ��ֵ(��6��)
extern CString g_sLangID_Native_CurrentRatioPrimary6;
extern CString g_sLangTxt_Native_CurrentRatioPrimary6;
//������ȶ���ֵ(��1��)
extern CString g_sLangID_Native_CurrentRatioSecondary1;
extern CString g_sLangTxt_Native_CurrentRatioSecondary1;
//������ȶ���ֵ(��2��)
extern CString g_sLangID_Native_CurrentRatioSecondary2;
extern CString g_sLangTxt_Native_CurrentRatioSecondary2;
//������ȶ���ֵ(��3��)
extern CString g_sLangID_Native_CurrentRatioSecondary3;
extern CString g_sLangTxt_Native_CurrentRatioSecondary3;
//������ȶ���ֵ(��4��)
extern CString g_sLangID_Native_CurrentRatioSecondary4;
extern CString g_sLangTxt_Native_CurrentRatioSecondary4;
//������ȶ���ֵ(��5��)
extern CString g_sLangID_Native_CurrentRatioSecondary5;
extern CString g_sLangTxt_Native_CurrentRatioSecondary5;
//������ȶ���ֵ(��6��)
extern CString g_sLangID_Native_CurrentRatioSecondary6;
extern CString g_sLangTxt_Native_CurrentRatioSecondary6;
//���ģ����
extern CString g_sLangID_Native_OutputAnalog;
extern CString g_sLangTxt_Native_OutputAnalog;
//���������
extern CString g_sLangID_Native_OutputDigital;
extern CString g_sLangTxt_Native_OutputDigital;
//������ź�
extern CString g_sLangID_Native_OutputWeakSig;
extern CString g_sLangTxt_Native_OutputWeakSig;
//��ߵ�ѹֵ
extern CString g_sLangID_Native_RatedLineVolt;
extern CString g_sLangTxt_Native_RatedLineVolt;
//������ѹ
extern CString g_sLangID_Native_RatedZeroVolt;
extern CString g_sLangTxt_Native_RatedZeroVolt;
//��������
extern CString g_sLangID_Native_RatedZeroCurr;
extern CString g_sLangTxt_Native_RatedZeroCurr;
//��ʼ������ʱ(s)
extern CString g_sLangID_Native_StartOverloadDelay;
extern CString g_sLangTxt_Native_StartOverloadDelay;
//�����Զ�����
extern CString g_sLangID_Native_CheckTestEndHeartbeat;
extern CString g_sLangTxt_Native_CheckTestEndHeartbeat;
//ʹ��ģ�����ɼ�
extern CString g_sLangID_Native_UseAnalogCapture;
extern CString g_sLangTxt_Native_UseAnalogCapture;
//ʹ���������ɼ�
extern CString g_sLangID_Native_UseDigitalCapture;
extern CString g_sLangTxt_Native_UseDigitalCapture;
//ʹ��С�źŲɼ�
extern CString g_sLangID_Native_UseSmallSignalCapture;
extern CString g_sLangTxt_Native_UseSmallSignalCapture;
//�������ɼ���������
extern CString g_sLangID_Native_DigitalCaptureMsgType;
extern CString g_sLangTxt_Native_DigitalCaptureMsgType;
//B������߼�(0-���߼�,1-���߼�)
extern CString g_sLangID_Native_BCodeReceiveLogic;
extern CString g_sLangTxt_Native_BCodeReceiveLogic;
//������Ҫ����չ��������(0-�Զ�������������չģ��)
extern CString g_sLangID_Native_ReportExtInQty;
extern CString g_sLangTxt_Native_ReportExtInQty;
//�ײ��ϱ����ݵ�ʱ��
extern CString g_sLangID_Native_BaseReportTimeZone;
extern CString g_sLangTxt_Native_BaseReportTimeZone;
//GPSתB��ʱʹ���û�����ʱ��
extern CString g_sLangID_Native_GPStoBCodeUserTZ;
extern CString g_sLangTxt_Native_GPStoBCodeUserTZ;
//����ɢ�ȷ���ģʽ(0-����,1-����)
extern CString g_sLangID_Native_MachineFanMode;
extern CString g_sLangTxt_Native_MachineFanMode;
//��ֵ�ݱ��ʶ
extern CString g_sLangID_Native_AmplitudeGradual;
extern CString g_sLangTxt_Native_AmplitudeGradual;
//��ֵ�ݱ���ֵ
extern CString g_sLangID_Native_AmplitudeEndValue;
extern CString g_sLangTxt_Native_AmplitudeEndValue;
//��ֵ�ݱ䲽��
extern CString g_sLangID_Native_AmplitudeStep;
extern CString g_sLangTxt_Native_AmplitudeStep;
//��λ�ݱ��ʶ
extern CString g_sLangID_Native_PhaseFlag;
extern CString g_sLangTxt_Native_PhaseFlag;
//��λ�ݱ���ֵ
extern CString g_sLangID_Native_PhaseEndVal;
extern CString g_sLangTxt_Native_PhaseEndVal;
//��λ�ݱ䲽��
extern CString g_sLangID_Native_PhaseStep;
extern CString g_sLangTxt_Native_PhaseStep;
//Ƶ�ʵݱ��ʶ
extern CString g_sLangID_Native_FreqFlag;
extern CString g_sLangTxt_Native_FreqFlag;
//Ƶ�ʵݱ���ֵ
extern CString g_sLangID_Native_FreqEnd;
extern CString g_sLangTxt_Native_FreqEnd;
//Ƶ�ʵݱ䲽��
extern CString g_sLangID_Native_FreqStep;
extern CString g_sLangTxt_Native_FreqStep;
//�Ƿ�ѡ��
extern CString g_sLangID_Native_IsSelected;
extern CString g_sLangTxt_Native_IsSelected;
//����״̬
extern CString g_sLangID_Native_OpenState;
extern CString g_sLangTxt_Native_OpenState;
//�Ƿ����ֱ������
extern CString g_sLangID_Native_DCOverlay;
extern CString g_sLangTxt_Native_DCOverlay;
//ֱ��������˥��ʱ�䳣��
extern CString g_sLangID_Native_DCDampTime;
extern CString g_sLangTxt_Native_DCDampTime;
//ʹ������
extern CString g_sLangID_Native_EnableEval;
extern CString g_sLangTxt_Native_EnableEval;
//��ʱ���_״̬
extern CString g_sLangID_Native_TimeStartState;
extern CString g_sLangTxt_Native_TimeStartState;
//��ʱ�յ�_״̬
extern CString g_sLangID_Native_TimeEndState;
extern CString g_sLangTxt_Native_TimeEndState;
//��ʱ���_����
extern CString g_sLangID_Native_TimeStartInput;
extern CString g_sLangTxt_Native_TimeStartInput;
//��ʱ�յ�_����
extern CString g_sLangID_Native_TimeEndInput;
extern CString g_sLangTxt_Native_TimeEndInput;
//���������
extern CString g_sLangID_Native_AbsErrorLimit;
extern CString g_sLangTxt_Native_AbsErrorLimit;
//��������
extern CString g_sLangID_Native_RelErrorLimit;
extern CString g_sLangTxt_Native_RelErrorLimit;
//�ж��߼�
extern CString g_sLangID_Native_JudgeLogic;
extern CString g_sLangTxt_Native_JudgeLogic;
//�ݱ䶯��������ʶ
extern CString g_sLangID_Native_StepChangeID;
extern CString g_sLangTxt_Native_StepChangeID;
//�Զ��嶯��ʱ��
extern CString g_sLangID_Native_CustomActTime;
extern CString g_sLangTxt_Native_CustomActTime;
//�Զ��嶯��ʱ��������
extern CString g_sLangID_Native_AbsError;
extern CString g_sLangTxt_Native_AbsError;
//�Զ��嶯��ʱ��������
extern CString g_sLangID_Native_RelError;
extern CString g_sLangTxt_Native_RelError;
//��ǰѭ�������
extern CString g_sLangID_Native_CurrLoop;
extern CString g_sLangTxt_Native_CurrLoop;
//����ģʽ(0-��������,1-�ȴ�GPS)
extern CString g_sLangID_Native_TrigModes;
extern CString g_sLangTxt_Native_TrigModes;
//Ӳ��ѡ��(0-����8������,1-��չ���)
extern CString g_sLangID_Native_HwSelect;
extern CString g_sLangTxt_Native_HwSelect;
//���붯��(0-����¼,1-��¼)
extern CString g_sLangID_Native_InAction;
extern CString g_sLangTxt_Native_InAction;
//ʵ��������ʱ��(s)
extern CString g_sLangID_Native_TotalTime;
extern CString g_sLangTxt_Native_TotalTime;
//�Ƿ�����
extern CString g_sLangID_Native_IsEnabled;
extern CString g_sLangTxt_Native_IsEnabled;
//ʵ��ǰ״ֵ̬
extern CString g_sLangID_Native_PreState;
extern CString g_sLangTxt_Native_PreState;
//ʵ���г�ʼ״ֵ̬
extern CString g_sLangID_Native_InitState;
extern CString g_sLangTxt_Native_InitState;
//ʵ��ǰ�Ͽ�����ʱ��(ms)
extern CString g_sLangID_Native_PreCutDur;
extern CString g_sLangTxt_Native_PreCutDur;
//ʵ���бպϳ���ʱ��(ms)
extern CString g_sLangID_Native_CloseDur;
extern CString g_sLangTxt_Native_CloseDur;
//ʵ���жϿ�����ʱ��(ms)
extern CString g_sLangID_Native_BreakDur;
extern CString g_sLangTxt_Native_BreakDur;
//Uz��ֵ
extern CString g_sLangID_Native_UzAmp;
extern CString g_sLangTxt_Native_UzAmp;
//Uz��λ
extern CString g_sLangID_Native_UzPhase;
extern CString g_sLangTxt_Native_UzPhase;
//UzƵ��
extern CString g_sLangID_Native_UzFreq;
extern CString g_sLangTxt_Native_UzFreq;
//I0��ֵ
extern CString g_sLangID_Native_I0Amplitude;
extern CString g_sLangTxt_Native_I0Amplitude;
//I0��λ
extern CString g_sLangID_Native_I0Phase;
extern CString g_sLangTxt_Native_I0Phase;
//I0Ƶ��
extern CString g_sLangID_Native_I0Frequency;
extern CString g_sLangTxt_Native_I0Frequency;
//�������ø߹���ģʽ
extern CString g_sLangID_Native_CurrentHighPowerMode;
extern CString g_sLangTxt_Native_CurrentHighPowerMode;
//�����Զ������
extern CString g_sLangID_Native_EnableCustomOutput;
extern CString g_sLangTxt_Native_EnableCustomOutput;
//����ʱ��
extern CString g_sLangID_Native_AbsoluteTime;
extern CString g_sLangTxt_Native_AbsoluteTime;
//���ʱ��
extern CString g_sLangID_Native_RelativeTime;
extern CString g_sLangTxt_Native_RelativeTime;

extern CString g_sLangID_Native_ErrUaAmp;
extern CString g_sLangTxt_Native_ErrUaAmp;//����Ua��ֵ
extern CString g_sLangID_Native_ErrUbAmp;
extern CString g_sLangTxt_Native_ErrUbAmp;//����Ub��ֵ
extern CString g_sLangID_Native_ErrUcAmp;
extern CString g_sLangTxt_Native_ErrUcAmp;//����Uc��ֵ
extern CString g_sLangID_Native_ErrUzAmp;
extern CString g_sLangTxt_Native_ErrUzAmp;//����Uz��ֵ
extern CString g_sLangID_Native_ErrUaPh;
extern CString g_sLangTxt_Native_ErrUaPh;//����Ua��λ
extern CString g_sLangID_Native_ErrUbPh;
extern CString g_sLangTxt_Native_ErrUbPh;//����Ub��λ
extern CString g_sLangID_Native_ErrUcPh;
extern CString g_sLangTxt_Native_ErrUcPh;//����Uc��λ
extern CString g_sLangID_Native_ErrUzPh;
extern CString g_sLangTxt_Native_ErrUzPh;//����Uz��λ
extern CString g_sLangID_Native_OverCurrentV;
extern CString g_sLangTxt_Native_OverCurrentV;//����V�ζ�ֵ
extern CString g_sLangID_Native_OverCurrentVTime;
extern CString g_sLangTxt_Native_OverCurrentVTime;//����V��ʱ��
extern CString g_sLangID_Native_ShortZImpAngExp;
extern CString g_sLangTxt_Native_ShortZImpAngExp;//��·�迹��(���ʽ)
//

extern CString g_sLangID_Native_first_fault_type;
extern CString g_sLangTxt_Native_first_fault_type;//��һ�ι�������
extern CString g_sLangID_Native_first_fault_current;
extern CString g_sLangTxt_Native_first_fault_current;//��һ�ι��ϵ���
extern CString g_sLangID_Native_first_faultact_time;
extern CString g_sLangTxt_Native_first_faultact_time;//��һ�ι��϶���ʱ��
extern CString g_sLangID_Native_first_fault_impedance;
extern CString g_sLangTxt_Native_first_fault_impedance;//��һ�ι��϶�·�迹
extern CString g_sLangID_Native_first_fault_impedance_angle;
extern CString g_sLangTxt_Native_first_fault_impedance_angle;//��һ�ι��϶�·�迹��
extern CString g_sLangID_Native_second_fault_type;
extern CString g_sLangTxt_Native_second_fault_type;//�ڶ��ι�������
extern CString g_sLangID_Native_second_fault_current;
extern CString g_sLangTxt_Native_second_fault_current;//�ڶ��ι��ϵ���
extern CString g_sLangID_Native_second_faultact_time;
extern CString g_sLangTxt_Native_second_faultact_time;//�ڶ��ι��϶���ʱ��
extern CString g_sLangID_Native_second_fault_impedance;
extern CString g_sLangTxt_Native_second_fault_impedance;//�ڶ��ι��϶�·�迹
extern CString g_sLangID_Native_second_fault_impedance_angle;
extern CString g_sLangTxt_Native_second_fault_impedance_angle;//�ڶ��ι��϶�·�迹��
extern CString g_sLangID_Native_first_fault_impAmp;
extern CString g_sLangTxt_Native_first_fault_impAmp;//��һ�ι��϶�·�迹(���ʽ)
extern CString g_sLangID_Native_first_fault_impAngAmp;
extern CString g_sLangTxt_Native_first_fault_impAngAmp;//��һ�ι��϶�·�迹��(���ʽ)
extern CString g_sLangID_Native_second_fault_impAmp;
extern CString g_sLangTxt_Native_second_fault_impAmp;//�ڶ��ι��϶�·�迹(���ʽ)
extern CString g_sLangID_Native_second_fault_impAngAmp;
extern CString g_sLangTxt_Native_second_fault_impAngAmp;//�ڶ��ι��϶�·�迹��(���ʽ)
extern CString g_sLangID_Native_synchronous_VAmpExp;
extern CString g_sLangTxt_Native_synchronous_VAmpExp;//ͬ�ڵ�ѹ��ֵ(���ʽ)
extern CString g_sLangID_Native_synchronous_VPhExp;
extern CString g_sLangTxt_Native_synchronous_VPhExp;//ͬ�ڵ�ѹ��λ(���ʽ)

extern CString g_sLangID_Native_impedance_Set;
extern CString g_sLangTxt_Native_impedance_Set;//�迹��ֵ(��ֵ)
extern CString g_sLangID_Native_ImpedanceAnglesSet;
extern CString g_sLangTxt_Native_ImpedanceAnglesSet;//�迹��(��ֵ)
extern CString g_sLangID_Native_Syn_closure_AngSet;
extern CString g_sLangTxt_Native_Syn_closure_AngSet;//��ͬ�ں�բ��(��ֵ)
extern CString g_sLangID_Native_test_item_name;
extern CString g_sLangTxt_Native_test_item_name;//����������

extern CString g_sLangID_Native_0seqISet;
extern CString g_sLangTxt_Native_0seqISet;//���������ֵ
extern CString g_sLangID_Native_YN_autoTestMode;
extern CString g_sLangTxt_Native_YN_autoTestMode;//�Ƿ��Զ�����ģʽ
extern CString g_sLangID_Native_0SeqISet;
extern CString g_sLangTxt_Native_0SeqISet; //����I-V�ζ�ֵ
extern CString g_sLangID_Native_0SeqIISet;
extern CString g_sLangTxt_Native_0SeqIISet;
extern CString g_sLangID_Native_0SeqIIISet;
extern CString g_sLangTxt_Native_0SeqIIISet;
extern CString g_sLangID_Native_0SeqIVSet;
extern CString g_sLangTxt_Native_0SeqIVSet;
extern CString g_sLangID_Native_0SeqVSet;
extern CString g_sLangTxt_Native_0SeqVSet;
extern CString g_sLangID_Native_0SeqITime;
extern CString g_sLangTxt_Native_0SeqITime;//����I-V��ʱ��
extern CString g_sLangID_Native_0SeqIITime;
extern CString g_sLangTxt_Native_0SeqIITime;
extern CString g_sLangID_Native_0SeqIIITime;
extern CString g_sLangTxt_Native_0SeqIIITime;
extern CString g_sLangID_Native_0SeqIVTime;
extern CString g_sLangTxt_Native_0SeqIVTime;
extern CString g_sLangID_Native_0SeqVTime;
extern CString g_sLangTxt_Native_0SeqVTime;


//�ڰ�����
//tmt_adjust_sys_para_trans.cpp
/*_T("������ѹ���")*/
extern CString g_sLangID_Native_ACVoltPlugin;
extern CString g_sLangTxt_Native_ACVoltPlugin;
/*_T("�����������")*/
extern CString g_sLangID_Native_ACCurrPlugin;
extern CString g_sLangTxt_Native_ACCurrPlugin;
/*_T("8�����׿����ְ�")*/
extern CString g_sLangID_Native_8x100MbpsDB;
extern CString g_sLangTxt_Native_8x100MbpsDB;
/*_T("6�����׿�,2��ǧ�׿����ְ�")*/
extern CString g_sLangID_Native_6x100M2x1000MDB;
extern CString g_sLangTxt_Native_6x100M2x1000MDB;
/*_T("4�����׿�,4��ǧ�׿����ְ�")*/
extern CString g_sLangID_Native_4x100M4x1000MDB;
extern CString g_sLangTxt_Native_4x100M4x1000MDB;
/*_T("ֱ���������")*/
extern CString g_sLangID_Native_DCCurrPlugin;
extern CString g_sLangTxt_Native_DCCurrPlugin;
/*_T("ֱ����ѹ���")*/
extern CString g_sLangID_Native_DCVoltPlugin;
extern CString g_sLangTxt_Native_DCVoltPlugin;
/*_T("��������չ��")*/
extern CString g_sLangID_Native_DI_O_ExpBoard;
extern CString g_sLangTxt_Native_DI_O_ExpBoard;
/*_T("С�ź�ģ����")*/
extern CString g_sLangID_Native_LSModPlugin;
extern CString g_sLangTxt_Native_LSModPlugin;
/*_T("����С�ź�")*/
extern CString g_sLangID_Native_MBLowSignal;
extern CString g_sLangTxt_Native_MBLowSignal;
/*_T("��ֱFT3��")*/
extern CString g_sLangID_Native_FSFT3Board;
extern CString g_sLangTxt_Native_FSFT3Board;
/*_T("U��I��ϲ��")*/
extern CString g_sLangID_Native_UIHybridPlugin;
extern CString g_sLangTxt_Native_UIHybridPlugin;
/*_T("��ѹ�ɼ����")*/
extern CString g_sLangID_Native_VoltAcqPlugin;
extern CString g_sLangTxt_Native_VoltAcqPlugin;
/*_T("�����ɼ����")*/
extern CString g_sLangID_Native_CurrAcqPlugin;
extern CString g_sLangTxt_Native_CurrAcqPlugin;
/*_T("�ȿ�2MͨѶ���")*/
extern CString g_sLangID_Native_Stable2MCommPlugin;
extern CString g_sLangTxt_Native_Stable2MCommPlugin;
/*_T("�ɼ�")*/
extern CString g_sLangID_Native_Acquisition;
extern CString g_sLangTxt_Native_Acquisition;
/*_T("δ����")*/
extern CString g_sLangID_Native_Undefined;
extern CString g_sLangTxt_Native_Undefined;
/*_T("130����ѹģ��")*/
extern CString g_sLangID_Native_130VVoltageModule;
extern CString g_sLangTxt_Native_130VVoltageModule;
/*_T("248����ѹģ��")*/
extern CString g_sLangID_Native_248VVoltageModule;
extern CString g_sLangTxt_Native_248VVoltageModule;
/*_T("270����ѹģ������ѹ")*/
extern CString g_sLangID_Native_270VVMNoBoost;
extern CString g_sLangTxt_Native_270VVMNoBoost;
/*_T("270����ѹģ������ѹ")*/
extern CString g_sLangID_Native_270VVModuleWBoost;
extern CString g_sLangTxt_Native_270VVModuleWBoost;
/*_T("300����ѹģ������ѹ")*/
extern CString g_sLangID_Native_300VVMNoBoost;
extern CString g_sLangTxt_Native_300VVMNoBoost;
/*_T("300����ѹģ������ѹ")*/
extern CString g_sLangID_Native_300VVModuleWBoost;
extern CString g_sLangTxt_Native_300VVModuleWBoost;
/*_T("12.5������ģ��")*/
extern CString g_sLangID_Native_125ACModule;
extern CString g_sLangTxt_Native_125ACModule;
/*_T("20������ģ��")*/
extern CString g_sLangID_Native_20ACModule;
extern CString g_sLangTxt_Native_20ACModule;
/*_T("32������ģ��")*/
extern CString g_sLangID_Native_32ACModule;
extern CString g_sLangTxt_Native_32ACModule;
/*_T("130��20�����ģ��")*/
extern CString g_sLangID_Native_125V20AHM;
extern CString g_sLangTxt_Native_125V20AHM;
/*_T("310��60�����ģ��")*/
extern CString g_sLangID_Native_310V60AHM;
extern CString g_sLangTxt_Native_310V60AHM;
/*_T("PFC_6A ģ��")*/
extern CString g_sLangID_Native_PFC6A;
extern CString g_sLangTxt_Native_PFC6A;
/*_T("PIA12DS ģ��")*/
extern CString g_sLangID_Native_P12DSM;
extern CString g_sLangTxt_Native_P12DSM;
/*_T("PIA48S ģ��")*/
extern CString g_sLangID_Native_P48SM;
extern CString g_sLangTxt_Native_P48SM;
/*_T("EVTECT ģ��")*/
extern CString g_sLangID_Native_EVTM;
extern CString g_sLangTxt_Native_EVTM;
/*_T("ֱ����������ģ��")*/
extern CString g_sLangID_Native_DCIPM;
extern CString g_sLangTxt_Native_DCIPM;
/*_T("6·10��ֱ��ģ��")*/
extern CString g_sLangID_Native_6C10VDCM;
extern CString g_sLangTxt_Native_6C10VDCM;
/*_T("6·20����ֱ��ģ��")*/
extern CString g_sLangID_Native_6C20mADC;
extern CString g_sLangTxt_Native_6C20mADC;
/*_T("PN6U6Iֱ��С�ź�ģ��")*/
extern CString g_sLangID_Native_PN6U6IDCSSM;
extern CString g_sLangTxt_Native_PN6U6IDCSSM;
/*_T("��֧������ϲ�")*/
extern CString g_sLangID_Native_OutputNotSupported;
extern CString g_sLangTxt_Native_OutputNotSupported;
/*_T("6·���Ժϲ�Ϊ1·")*/
extern CString g_sLangID_Native_6to1MergePossible;
extern CString g_sLangTxt_Native_6to1MergePossible;
/*_T("6·���Ժϲ�Ϊ3·")*/
extern CString g_sLangID_Native_6to3MergePossible;
extern CString g_sLangTxt_Native_6to3MergePossible;
/*_T("6·�̶��ϲ�Ϊ3·")*/
extern CString g_sLangID_Native_6to3FixedMerge;
extern CString g_sLangTxt_Native_6to3FixedMerge;

//adjust_sys_parameter
/*"��ֵϵ��"*/
extern CString g_sLangID_Native_AmpFactor;
extern CString g_sLangTxt_Native_AmpFactor;
/*"��λ��"*/
extern CString g_sLangID_Native_NumGears;
extern CString g_sLangTxt_Native_NumGears;
/*"Ӳ��1��ֱ����Ư"*/
extern CString g_sLangID_Native_HW1DCZeroDrift;
extern CString g_sLangTxt_Native_HW1DCZeroDrift;
/*"Ӳ��2��ֱ����Ư"*/
extern CString g_sLangID_Native_HW2DCZeroDrift;
extern CString g_sLangTxt_Native_HW2DCZeroDrift;
/*"Ӳ��3��ֱ����Ư"*/
extern CString g_sLangID_Native_HW3DCZeroDrift;
extern CString g_sLangTxt_Native_HW3DCZeroDrift;
/*"�����������ϵ��"*/
extern CString g_sLangID_Native_LCNLCoeff;
extern CString g_sLangTxt_Native_LCNLCoeff;
/*"%d��г��"*/
extern CString g_sLangID_Native_NthHarmonic;
extern CString g_sLangTxt_Native_NthHarmonic;
/*"�¶�"*/
extern CString g_sLangID_Native_Temp;
extern CString g_sLangTxt_Native_Temp;
/*"ͨ��%d"*/
extern CString g_sLangID_Native_ChnN;
extern CString g_sLangTxt_Native_ChnN;
/*"��λID"*/
extern CString g_sLangID_Native_GearID;
extern CString g_sLangTxt_Native_GearID;
/*"��λֵ"*/
extern CString g_sLangID_Native_GearVal;
extern CString g_sLangTxt_Native_GearVal;
/*"Ӳ����λ��"*/
extern CString g_sLangID_Native_HwGearCount;
extern CString g_sLangTxt_Native_HwGearCount;
/*"У׼ϵ��"*/
extern CString g_sLangID_Native_CalibCoeff;
extern CString g_sLangTxt_Native_CalibCoeff;
/*"������"*/
extern CString g_sLangID_Native_TempZoneCount;
extern CString g_sLangTxt_Native_TempZoneCount;
/*"Ӳ��ͨ��"*/
extern CString g_sLangID_Native_HwChannel;
extern CString g_sLangTxt_Native_HwChannel;
/*"ͨ��ID"*/
extern CString g_sLangID_Native_ChnID;
extern CString g_sLangTxt_Native_ChnID;
/*"ͨ������"*/
extern CString g_sLangID_Native_ChnIndex;
extern CString g_sLangTxt_Native_ChnIndex;
/*"�����������Դ"*/
extern CString g_sLangID_Native_AssocSWRes;
extern CString g_sLangTxt_Native_AssocSWRes;
/*"�������ֵ"*/
extern CString g_sLangID_Native_ACMaxValue;
extern CString g_sLangTxt_Native_ACMaxValue;
/*"ֱ�����ֵ"*/
extern CString g_sLangID_Native_DCMaxValue;
extern CString g_sLangTxt_Native_DCMaxValue;
/*"ͨ���ɼ�ӳ��λ��"*/
extern CString g_sLangID_Native_ChAcqMapLoc;
extern CString g_sLangTxt_Native_ChAcqMapLoc;
/*"ͨ���ɼ�ӳ��λ��"*/
extern CString g_sLangID_Native_OpMode;
extern CString g_sLangTxt_Native_OpMode;
/*"����ģʽ"*/
extern CString g_sLangID_Native_OpMode;
extern CString g_sLangTxt_Native_OpMode;
/*"��������"*/
extern CString g_sLangID_Native_ElecType;
extern CString g_sLangTxt_Native_ElecType;
/*"Ӳ��ͨ������"*/
extern CString g_sLangID_Native_HwChDef;
extern CString g_sLangTxt_Native_HwChDef;
/*"ͨ������λ��"*/
extern CString g_sLangID_Native_ChDrivePos;
extern CString g_sLangTxt_Native_ChDrivePos;
/*_T("ͨ��%dλ��")*/
extern CString g_sLangID_Native_ChPos;
extern CString g_sLangTxt_Native_ChPos;
/*"ͨ��ӳ�䶨��"*/
extern CString g_sLangID_Native_ChMapDef;
extern CString g_sLangTxt_Native_ChMapDef;
/*"ģ������"*/
extern CString g_sLangID_Native_ModProps;
extern CString g_sLangTxt_Native_ModProps;
/*"LC�����"*/
extern CString g_sLangID_Native_LCOptPortCount;
extern CString g_sLangTxt_Native_LCOptPortCount;
/*"ST���͹����"*/
extern CString g_sLangID_Native_STTxOptPortCount;
extern CString g_sLangTxt_Native_STTxOptPortCount;
/*"ST���չ����"*/
extern CString g_sLangID_Native_STRxOptPortCount;
extern CString g_sLangTxt_Native_STRxOptPortCount;
/*"г����"*/
extern CString g_sLangID_Native_HarmOrder;
extern CString g_sLangTxt_Native_HarmOrder;
/*"ֱ����ѹͨ�����ֵ"*/
extern CString g_sLangID_Native_DCVoltChMax;
extern CString g_sLangTxt_Native_DCVoltChMax;
/*"ֱ������ͨ�����ֵ"*/
extern CString g_sLangID_Native_DCCurrChMax;
extern CString g_sLangTxt_Native_DCCurrChMax;
/*"ͨ�����������ֵ"*/
extern CString g_sLangID_Native_ChACOutMax;
extern CString g_sLangTxt_Native_ChACOutMax;
/*"ͨ����ֱ�����ֵ"*/
extern CString g_sLangID_Native_ChDCOutMax;
extern CString g_sLangTxt_Native_ChDCOutMax;
/*"Ƶ�ʲ���ϵ��"*/
extern CString g_sLangID_Native_FreqCompCoeff;
extern CString g_sLangTxt_Native_FreqCompCoeff;
/*"����Ӳ����λ��ʱ"*/
extern CString g_sLangID_Native_DigiHWPhaseDelay;
extern CString g_sLangTxt_Native_DigiHWPhaseDelay;
/*"��ѹ����Ӳ������"*/
extern CString g_sLangID_Native_VoltCurrHWChar;
extern CString g_sLangTxt_Native_VoltCurrHWChar;
/*"����ͨ���ϲ�ģʽ"*/
extern CString g_sLangID_Native_CurrChMergeMode;
extern CString g_sLangTxt_Native_CurrChMergeMode;
/*"��һ�鿪������Ϊ����"*/
extern CString g_sLangID_Native_1stSetDigInCfg;
extern CString g_sLangTxt_Native_1stSetDigInCfg;
/*"�ڶ��鿪������Ϊ����"*/
extern CString g_sLangID_Native_2stSetDigInCfg;
extern CString g_sLangTxt_Native_2stSetDigInCfg;
/*"�����鿪������Ϊ����"*/
extern CString g_sLangID_Native_3stSetDigInCfg;
extern CString g_sLangTxt_Native_3stSetDigInCfg;
/*"�����鿪������Ϊ����"*/
extern CString g_sLangID_Native_4stSetDigInCfg;
extern CString g_sLangTxt_Native_4stSetDigInCfg;
/*"ģ��FPGA�汾"*/
extern CString g_sLangID_Native_ModFPGAVer;
extern CString g_sLangTxt_Native_ModFPGAVer;
/*"ģ�����԰汾"*/
extern CString g_sLangID_Native_ModAttrVer;
extern CString g_sLangTxt_Native_ModAttrVer;
/*"����ֱ������ͨ��Ӳ����λ"*/
extern CString g_sLangID_Native_IndepDCCurrChHWRange;
extern CString g_sLangTxt_Native_IndepDCCurrChHWRange;
/*"����ֱ����ѹͨ��Ӳ����λ"*/
extern CString g_sLangID_Native_IndepDCVoltChHWRange;
extern CString g_sLangTxt_Native_IndepDCVoltChHWRange;
/*"ģ��ͨ����λ"*/
extern CString g_sLangID_Native_ModChRange;
extern CString g_sLangTxt_Native_ModChRange;
/*"��������ֵͨ����"*/
extern CString g_sLangID_Native_TripRelayPickupDef;
extern CString g_sLangTxt_Native_TripRelayPickupDef;
/*"����1��ֵͨ"*/
extern CString g_sLangID_Native_TripRelay1Pickup;
extern CString g_sLangTxt_Native_TripRelay1Pickup;
/*"����2��ֵͨ"*/
extern CString g_sLangID_Native_TripRelay2Pickup;
extern CString g_sLangTxt_Native_TripRelay2Pickup;
/*"����3��ֵͨ"*/
extern CString g_sLangID_Native_TripRelay3Pickup;
extern CString g_sLangTxt_Native_TripRelay3Pickup;
/*"����4��ֵͨ"*/
extern CString g_sLangID_Native_TripRelay4Pickup;
extern CString g_sLangTxt_Native_TripRelay4Pickup;
/*"����5��ֵͨ"*/
extern CString g_sLangID_Native_TripRelay5Pickup;
extern CString g_sLangTxt_Native_TripRelay5Pickup;
/*"����6��ֵͨ"*/
extern CString g_sLangID_Native_TripRelay6Pickup;
extern CString g_sLangTxt_Native_TripRelay6Pickup;
/*"����7��ֵͨ"*/
extern CString g_sLangID_Native_TripRelay7Pickup;
extern CString g_sLangTxt_Native_TripRelay7Pickup;
/*"����8��ֵͨ"*/
extern CString g_sLangID_Native_TripRelay8Pickup;
extern CString g_sLangTxt_Native_TripRelay8Pickup;
/*"״̬��������(��)"*/
extern CString g_sLangID_Native_StateSeqCapacity;
extern CString g_sLangTxt_Native_StateSeqCapacity;
/*"���忪������(��)"*/
extern CString g_sLangID_Native_MainBrdDInQty;
extern CString g_sLangTxt_Native_MainBrdDInQty;
/*"���忪������(��)"*/
extern CString g_sLangID_Native_MainBrdDOutQty;
extern CString g_sLangTxt_Native_MainBrdDOutQty;
/*"����ʱ��,ģ����������λ����(��)"*/
extern CString g_sLangID_Native_WSecMomentAnaPhAbsComp;
extern CString g_sLangTxt_Native_WSecMomentAnaPhAbsComp;
/*"���ÿ���Ȩ���ж�(0-�����ã�1-����)"*/
extern CString g_sLangID_Native_CtrlAuthCheck;
extern CString g_sLangTxt_Native_CtrlAuthCheck;
/*"TestServer����"*/
extern CString g_sLangID_Native_TestSrvName;
extern CString g_sLangTxt_Native_TestSrvName;
/*"TestServer�汾"*/
extern CString g_sLangID_Native_TestSrvVersion;
extern CString g_sLangTxt_Native_TestSrvVersion;
/*"����汾"*/
extern CString g_sLangID_Native_MainBrdVersion;
extern CString g_sLangTxt_Native_MainBrdVersion;
/*"�����汾"*/
extern CString g_sLangID_Native_DrvVersion;
extern CString g_sLangTxt_Native_DrvVersion;
/*"��������"*/
extern CString g_sLangID_Native_DrvName;
extern CString g_sLangTxt_Native_DrvName;
/*"����ST��ģʽ������"*/
extern CString g_sLangID_Native_MainBrdSTPortModeCfg;
extern CString g_sLangTxt_Native_MainBrdSTPortModeCfg;
/*"ϵͳ�汾��"*/
extern CString g_sLangID_Native_SysVerNumber;
extern CString g_sLangTxt_Native_SysVerNumber;



//tmt_adjust_test
/*"У׼��Ŀ"*/
extern CString g_sLangID_Native_CalibItem;
extern CString g_sLangTxt_Native_CalibItem;
/*"��1��ֵ"*/
extern CString g_sLangID_Native_Pt1Amp;
extern CString g_sLangTxt_Native_Pt1Amp;
/*"��2��ֵ"*/
extern CString g_sLangID_Native_Pt2Amp;
extern CString g_sLangTxt_Native_Pt2Amp;

//tmt_dig_replay_test
/*"����(ѡ��ÿ��ƿ�)"*/
extern CString g_sLangID_Native_SelCtrlBlock;
extern CString g_sLangTxt_Native_SelCtrlBlock;
/*"���ƿ�����������"*/
extern CString g_sLangID_Native_CtrlBlkOutOptPortsCnt;
extern CString g_sLangTxt_Native_CtrlBlkOutOptPortsCnt;
/*"���ƿ�AppID"*/
extern CString g_sLangID_Native_CtrlBlkAppID;
extern CString g_sLangTxt_Native_CtrlBlkAppID;
/*"���ƿ������֡��"*/
extern CString g_sLangID_Native_CtrlBlkOutTotalFrames;
extern CString g_sLangTxt_Native_CtrlBlkOutTotalFrames;
/*"���ƿ������ʼ֡��(�����ƿ�������)"*/
extern CString g_sLangID_Native_CtrlBlkOutStartFrmNum;
extern CString g_sLangTxt_Native_CtrlBlkOutStartFrmNum;
/*"���ƿ��������֡��(�����ƿ�������)"*/
extern CString g_sLangID_Native_CtrlBlkOutEndFrmNum;
extern CString g_sLangTxt_Native_CtrlBlkOutEndFrmNum;
/*"���ƿ���ʱ����ֵ(��λ:us)"*/
extern CString g_sLangID_Native_CtrlBlkDelayCompValue;
extern CString g_sLangTxt_Native_CtrlBlkDelayCompValue;
/*"����ֵ���ƿ�����"*/
extern CString g_sLangID_Native_NumOfSVCBs;
extern CString g_sLangTxt_Native_NumOfSVCBs;
/*"GOOSE���ƿ�����"*/
extern CString g_sLangID_Native_NumOfGCBs;
extern CString g_sLangTxt_Native_NumOfGCBs;
/*"SV�ط�ģʽ(0:��ʱ����,1:�ȼ��,2:�Զ���)"*/
extern CString g_sLangID_Native_SVReplayMode;
extern CString g_sLangTxt_Native_SVReplayMode;
/*"GOOSE�ط�ģʽ(0:��ʱ����,1:�ȼ��)"*/
extern CString g_sLangID_Native_GOOSEReplayMode;
extern CString g_sLangTxt_Native_GOOSEReplayMode;
/*"SV�ȼ���طż��ʱ��(us)"*/
extern CString g_sLangID_Native_SVEqReplayIntervalTime_us;
extern CString g_sLangTxt_Native_SVEqReplayIntervalTime_us;
/*"GOOSE�ȼ���طż��ʱ��(us)"*/
extern CString g_sLangID_Native_GOOSEEqReplayIntervalTime_us;
extern CString g_sLangTxt_Native_GOOSEEqReplayIntervalTime_us;
/*"�Զ���طŶ���ֵ(us)"*/
extern CString g_sLangID_Native_CustomReplayJitter_us;
extern CString g_sLangTxt_Native_CustomReplayJitter_us;
/*"�Ƿ�ѭ��(0��ѭ��,1ѭ��)"*/
extern CString g_sLangID_Native_LoopingFlag;
extern CString g_sLangTxt_Native_LoopingFlag;
/*"�ط�������������(0ȫ���ط�,1���ֻط�)"*/
extern CString g_sLangID_Native_ReplayIntervalType;
extern CString g_sLangTxt_Native_ReplayIntervalType;
/*"�����ʼ֡��(ȫ�����ƿ�����)"*/
extern CString g_sLangID_Native_StartFrameNum;
extern CString g_sLangTxt_Native_StartFrameNum;
/*"�������֡��(ȫ�����ƿ�����)"*/
extern CString g_sLangID_Native_EndFrameNum;
extern CString g_sLangTxt_Native_EndFrameNum;
/*"GPS����ʱ��(ʱ)"*/
extern CString g_sLangID_Native_GPSTriggerTime_hr;
extern CString g_sLangTxt_Native_GPSTriggerTime_hr;
/*"GPS����ʱ��(��)"*/
extern CString g_sLangID_Native_GPSTriggerTime_min;
extern CString g_sLangTxt_Native_GPSTriggerTime_min;
/*"GPS����ʱ��(��)"*/
extern CString g_sLangID_Native_GPSTriggerTime_sec;
extern CString g_sLangTxt_Native_GPSTriggerTime_sec;
/*"���ʱ��(s)"*/
extern CString g_sLangID_Native_OutputDuration_sec;
extern CString g_sLangTxt_Native_OutputDuration_sec;
/*"����%cѡ��"*/
extern CString g_sLangID_Native_InputSelection;
extern CString g_sLangTxt_Native_InputSelection;

//tmt_gradient_test
/*"����ϵ������ֵ"*/
extern CString g_sLangID_Native_FeedbackCoefSettingVal;
extern CString g_sLangTxt_Native_FeedbackCoefSettingVal;
/*"�߽��1����ֵ"*/
extern CString g_sLangID_Native_BoundaryAngle1SetVal;
extern CString g_sLangTxt_Native_BoundaryAngle1SetVal;
/*"�߽��2����ֵ"*/
extern CString g_sLangID_Native_BoundaryAngle2SetVal;
extern CString g_sLangTxt_Native_BoundaryAngle2SetVal;
/*"�������������ֵ"*/
extern CString g_sLangID_Native_MaxSensitivityAngleSetVal;
extern CString g_sLangTxt_Native_MaxSensitivityAngleSetVal;
/*"����ʱ��(��)"*/
extern CString g_sLangID_Native_StepTimeSec;
extern CString g_sLangTxt_Native_StepTimeSec;
/*"����̬��2��ѹ��ֵ"*/
extern CString g_sLangID_Native_FSG2VoltageAmplitude;
extern CString g_sLangTxt_Native_FSG2VoltageAmplitude;
/*"����̬��2������ֵ"*/
extern CString g_sLangID_Native_FSG2CurrentAmplitude;
extern CString g_sLangTxt_Native_FSG2CurrentAmplitude;
/*"���ѹ��ֵ"*/
extern CString g_sLangID_Native_RatedVoltageAmplitude;
extern CString g_sLangTxt_Native_RatedVoltageAmplitude;
/*"��̬��ѹ����"*/
extern CString g_sLangID_Native_NomVoltPhaseSeq;
extern CString g_sLangTxt_Native_NomVoltPhaseSeq;
/*"��̬��������"*/
extern CString g_sLangID_Native_NomCurrPhaseSeq;
extern CString g_sLangTxt_Native_NomCurrPhaseSeq;
/*"��̬��ѹ��ֵ"*/
extern CString g_sLangID_Native_NomVoltAmplitude;
extern CString g_sLangTxt_Native_NomVoltAmplitude;
/*"��̬������ֵ"*/
extern CString g_sLangID_Native_NomCurrAmplitude;
extern CString g_sLangTxt_Native_NomCurrAmplitude;

/*"Ua1��ֵ"*/
extern CString g_sLangID_Native_Ua1Amp;
extern CString g_sLangTxt_Native_Ua1Amp;
/*"Ua1��λ"*/
extern CString g_sLangID_Native_Ua1Ph;
extern CString g_sLangTxt_Native_Ua1Ph;
/*"Ua2��ֵ"*/
extern CString g_sLangID_Native_Ua2Amp;
extern CString g_sLangTxt_Native_Ua2Amp;
/*"Ua2��λ"*/
extern CString g_sLangID_Native_Ua2Ph;
extern CString g_sLangTxt_Native_Ua2Ph;

/*"Ub1��ֵ"*/
extern CString g_sLangID_Native_Ub1Amp;
extern CString g_sLangTxt_Native_Ub1Amp;
/*"Ub1��λ"*/
extern CString g_sLangID_Native_Ub1Ph;
extern CString g_sLangTxt_Native_Ub1Ph;
/*"Ub2��ֵ"*/
extern CString g_sLangID_Native_Ub2Amp;
extern CString g_sLangTxt_Native_Ub2Amp;
/*"Ub2��λ"*/
extern CString g_sLangID_Native_Ub2Ph;
extern CString g_sLangTxt_Native_Ub2Ph;

/*"Uc1��ֵ"*/
extern CString g_sLangID_Native_Uc1Amp;
extern CString g_sLangTxt_Native_Uc1Amp;
/*"Uc1��λ"*/
extern CString g_sLangID_Native_Uc1Ph;
extern CString g_sLangTxt_Native_Uc1Ph;
/*"Uc2��ֵ"*/
extern CString g_sLangID_Native_Uc2Amp;
extern CString g_sLangTxt_Native_Uc2Amp;
/*"Uc2��λ"*/
extern CString g_sLangID_Native_Uc2Ph;
extern CString g_sLangTxt_Native_Uc2Ph;

/*"Ia1��ֵ"*/
extern CString g_sLangID_Native_Ia1Amp;
extern CString g_sLangTxt_Native_Ia1Amp;
/*"Ia1��λ"*/
extern CString g_sLangID_Native_Ia1Ph;
extern CString g_sLangTxt_Native_Ia1Ph;
/*"Ia2��ֵ"*/
extern CString g_sLangID_Native_Ia2Amp;
extern CString g_sLangTxt_Native_Ia2Amp;
/*"Ia2��λ"*/
extern CString g_sLangID_Native_Ia2Ph;
extern CString g_sLangTxt_Native_Ia2Ph;

/*"Ib1��ֵ"*/
extern CString g_sLangID_Native_Ib1Amp;
extern CString g_sLangTxt_Native_Ib1Amp;
/*"Ib1��λ"*/
extern CString g_sLangID_Native_Ib1Ph;
extern CString g_sLangTxt_Native_Ib1Ph;
/*"Ib2��ֵ"*/
extern CString g_sLangID_Native_Ib2Amp;
extern CString g_sLangTxt_Native_Ib2Amp;
/*"Ib2��λ"*/
extern CString g_sLangID_Native_Ib2Ph;
extern CString g_sLangTxt_Native_Ib2Ph;

/*"Ic1��ֵ"*/
extern CString g_sLangID_Native_Ic1Amp;
extern CString g_sLangTxt_Native_Ic1Amp;
/*"Ic1��λ"*/
extern CString g_sLangID_Native_Ic1Ph;
extern CString g_sLangTxt_Native_Ic1Ph;
/*"Ic2��ֵ"*/
extern CString g_sLangID_Native_Ic2Amp;
extern CString g_sLangTxt_Native_Ic2Amp;
/*"Ic2��λ"*/
extern CString g_sLangID_Native_Ic2Ph;
extern CString g_sLangTxt_Native_Ic2Ph;

/*"Ƶ�ʶ���ֵ�������"*/
extern CString g_sLangID_Native_FreqPickAbsErr;
extern CString g_sLangTxt_Native_FreqPickAbsErr;
/*"Ƶ�ʶ���ֵ������"*/
extern CString g_sLangID_Native_FreqPickRelErr;
extern CString g_sLangTxt_Native_FreqPickRelErr;
/*"Ƶ�ʶ���ֵ����ж��߼�"*/
extern CString g_sLangID_Native_FreqPickErrDetectLogic;
extern CString g_sLangTxt_Native_FreqPickErrDetectLogic;
/*"��������Ǿ������"*/
extern CString g_sLangID_Native_MaxSensAngAbsErr;
extern CString g_sLangTxt_Native_MaxSensAngAbsErr;
/*"���������������"*/
extern CString g_sLangID_Native_MaxSensAngRelErr;
extern CString g_sLangTxt_Native_MaxSensAngRelErr;
/*"�������������ж��߼�"*/
extern CString g_sLangID_Native_MaxSensAngErrDetectLogic;
extern CString g_sLangTxt_Native_MaxSensAngErrDetectLogic;
/*"�߽��1�������"*/
extern CString g_sLangID_Native_BndryAng1AbsErr;
extern CString g_sLangTxt_Native_BndryAng1AbsErr;
/*"�߽��1������"*/
extern CString g_sLangID_Native_BndryAng1RelErr;
extern CString g_sLangTxt_Native_BndryAng1RelErr;
/*"�߽��1����ж��߼�"*/
extern CString g_sLangID_Native_BndryAng1ErrDetectLogic;
extern CString g_sLangTxt_Native_BndryAng1ErrDetectLogic;
/*"�߽��2�������"*/
extern CString g_sLangID_Native_BndryAng2AbsErr;
extern CString g_sLangTxt_Native_BndryAng2AbsErr;
/*"�߽��2������"*/
extern CString g_sLangID_Native_BndryAng2RelErr;
extern CString g_sLangTxt_Native_BndryAng2RelErr;
/*"�߽��2����ж��߼�"*/
extern CString g_sLangID_Native_BndryAng2ErrDetectLogic;
extern CString g_sLangTxt_Native_BndryAng2ErrDetectLogic;
/*"����ϵ����Ч"*/
extern CString g_sLangID_Native_RetCoeffValid;
extern CString g_sLangTxt_Native_RetCoeffValid;
/*"���������Ч"*/
extern CString g_sLangID_Native_AbsErrValid;
extern CString g_sLangTxt_Native_AbsErrValid;
/*"Ƶ�ʶ���ֵ���"*/
extern CString g_sLangID_Native_FreqTripValErr;
extern CString g_sLangTxt_Native_FreqTripValErr;
/*"��λ����ֵ���"*/
extern CString g_sLangID_Native_PhaseTripValErr;
extern CString g_sLangTxt_Native_PhaseTripValErr;
/*"����ϵ�����"*/
extern CString g_sLangID_Native_RetCoeffError;
extern CString g_sLangTxt_Native_RetCoeffError;
/*"������������"*/
extern CString g_sLangID_Native_MaxSensAngleErr;
extern CString g_sLangTxt_Native_MaxSensAngleErr;
/*"�߽��1���"*/
extern CString g_sLangID_Native_BndryAngle1Err;
extern CString g_sLangTxt_Native_BndryAngle1Err;
/*"�߽��2���"*/
extern CString g_sLangID_Native_BndryAngle2Err;
extern CString g_sLangTxt_Native_BndryAngle2Err;

//tmt_harm_test
/*"%d��г����λ"*/
extern CString g_sLangID_Native_NthHarmPhase;
extern CString g_sLangTxt_Native_NthHarmPhase;
/*"%d��г����ֵ"*/
extern CString g_sLangID_Native_NthHarmAmpl;
extern CString g_sLangTxt_Native_NthHarmAmpl;
/*"ֱ������"*/
extern CString g_sLangID_Native_DCCompVaule;
extern CString g_sLangTxt_Native_DCCompVaule;
/*"�Զ��仯����"*/
extern CString g_sLangID_Native_AutoVarConfig;
extern CString g_sLangTxt_Native_AutoVarConfig;
/*"�Ƿ��Զ��仯"*/
extern CString g_sLangID_Native_AutoVarStatus;
extern CString g_sLangTxt_Native_AutoVarStatus;
/*"�仯��ѡ��"*/
extern CString g_sLangID_Native_VarSelect;
extern CString g_sLangTxt_Native_VarSelect;
/*"�仯����ѡ��"*/
extern CString g_sLangID_Native_VarTypeSelect;
extern CString g_sLangTxt_Native_VarTypeSelect;
/*"�仯г������"*/
extern CString g_sLangID_Native_VarHarmonicNum;
extern CString g_sLangTxt_Native_VarHarmonicNum;

//tmt_manu_test
/*"�Ƿ���ֱ��ģʽ���"*/
extern CString g_sLangID_Native_DCOutputMode;
extern CString g_sLangTxt_Native_DCOutputMode;
/*"г������"*/
extern CString g_sLangID_Native_HarmSuperposition;
extern CString g_sLangTxt_Native_HarmSuperposition;
/*"г��ѡ��"*/
extern CString g_sLangID_Native_HarmSelection;
extern CString g_sLangTxt_Native_HarmSelection;
/*"�ϲ���Ԫ"*/
extern CString g_sLangID_Native_MrgUnit;
extern CString g_sLangTxt_Native_MrgUnit;
/*"�㷨ѡ��(0:��ֵ��  1:ͬ����)"*/
extern CString g_sLangID_Native_AlgorithmSelection;
extern CString g_sLangTxt_Native_AlgorithmSelection;
/*"PPS����(0:��������Ч  1:�½�����Ч 2:��PPS)"*/
extern CString g_sLangID_Native_PPSConfiguration;
extern CString g_sLangTxt_Native_PPSConfiguration;
/*"����ѹ(��Ư����)"*/
extern CString g_sLangID_Native_RatedV_Phase_ZeroDriftCalc;
extern CString g_sLangTxt_Native_RatedV_Phase_ZeroDriftCalc;
/*"������(��Ư����)"*/
extern CString g_sLangID_Native_RatedI_Phase_ZeroDriftCalc;
extern CString g_sLangTxt_Native_RatedI_Phase_ZeroDriftCalc;
/*"��ʱ���Ȳ���ʱͬ��ʱ��(��λ:s)"*/
extern CString g_sLangID_Native_SyncDur_TAT;
extern CString g_sLangTxt_Native_SyncDur_TAT;
/*"��PPSʱ��ʱ����ֵ(��ʱ��ʱ������,��λ:��s)"*/
extern CString g_sLangID_Native_DelayComp_NoPPS;
extern CString g_sLangTxt_Native_DelayComp_NoPPS;
/*"�Ƿ�ʹ���Զ��屨�����(�ϲ���Ԫ)"*/
extern CString g_sLangID_Native_CustomRepCnt_Use_MU;
extern CString g_sLangTxt_Native_CustomRepCnt_Use_MU;
/*"�Զ��屨����Դ���(�ϲ���Ԫ)"*/
extern CString g_sLangID_Native_CustomRepTestCnt_MU;
extern CString g_sLangTxt_Native_CustomRepTestCnt_MU;
/*"ÿ�β���ʱ��(�ϲ���Ԫ,��λ��)"*/
extern CString g_sLangID_Native_TestDurPerTest_MU_sec;
extern CString g_sLangTxt_Native_TestDurPerTest_MU_sec;
/*"MUʱ����Խ��"*/
extern CString g_sLangID_Native_MUTimeTestResults;
extern CString g_sLangTxt_Native_MUTimeTestResults;
/*"�Ѳ���ʱ��"*/
extern CString g_sLangID_Native_TestedDur;
extern CString g_sLangTxt_Native_TestedDur;
/*"������ʱ��"*/
extern CString g_sLangID_Native_MaxErrTime;
extern CString g_sLangTxt_Native_MaxErrTime;
/*"��С���ʱ��"*/
extern CString g_sLangID_Native_MinErrTime;
extern CString g_sLangTxt_Native_MinErrTime;
/*"ƽ�����ʱ��"*/
extern CString g_sLangID_Native_AvgErrTime;
extern CString g_sLangTxt_Native_AvgErrTime;
/*"ʱ�侫�Ȳ��Խ��"*/
extern CString g_sLangID_Native_TimeAccTestResults;
extern CString g_sLangTxt_Native_TimeAccTestResults;

/*"UaƵ��"*/
extern CString g_sLangID_Native_UaFreq;
extern CString g_sLangTxt_Native_UaFreq;
/*"UbƵ��"*/
extern CString g_sLangID_Native_UbFreq;
extern CString g_sLangTxt_Native_UbFreq;
/*"UcƵ��"*/
extern CString g_sLangID_Native_UcFreq;
extern CString g_sLangTxt_Native_UcFreq;

/*"Uap��ֵ"*/
extern CString g_sLangID_Native_UapAmp;
extern CString g_sLangTxt_Native_UapAmp;
/*"Uap��λ"*/
extern CString g_sLangID_Native_UapPhase;
extern CString g_sLangTxt_Native_UapPhase;
/*"UapƵ��"*/
extern CString g_sLangID_Native_UapFreq;
extern CString g_sLangTxt_Native_UapFreq;

/*"Ubp��ֵ"*/
extern CString g_sLangID_Native_UbpAmp;
extern CString g_sLangTxt_Native_UbpAmp;
/*"Ubp��λ"*/
extern CString g_sLangID_Native_UbpPhase;
extern CString g_sLangTxt_Native_UbpPhase;
/*"UbpƵ��"*/
extern CString g_sLangID_Native_UbpFreq;
extern CString g_sLangTxt_Native_UbpFreq;

/*"Ucp��ֵ"*/
extern CString g_sLangID_Native_UcpAmp;
extern CString g_sLangTxt_Native_UcpAmp;
/*"Ucp��λ"*/
extern CString g_sLangID_Native_UcpPhase;
extern CString g_sLangTxt_Native_UcpPhase;
/*"UcpƵ��"*/
extern CString g_sLangID_Native_UcpFreq;
extern CString g_sLangTxt_Native_UcpFreq;

/*"Ia��ֵ"*/
extern CString g_sLangID_Native_IaAmp;
extern CString g_sLangTxt_Native_IaAmp;
/*"Ia��λ"*/
extern CString g_sLangID_Native_IaPhase;
extern CString g_sLangTxt_Native_IaPhase;
/*"IaƵ��"*/
extern CString g_sLangID_Native_IaFreq;
extern CString g_sLangTxt_Native_IaFreq;

/*"Ib��ֵ"*/
extern CString g_sLangID_Native_IbAmp;
extern CString g_sLangTxt_Native_IbAmp;
/*"Ib��λ"*/
extern CString g_sLangID_Native_IbPhase;
extern CString g_sLangTxt_Native_IbPhase;
/*"IbƵ��"*/
extern CString g_sLangID_Native_IbFreq;
extern CString g_sLangTxt_Native_IbFreq;

/*"Ic��ֵ"*/
extern CString g_sLangID_Native_IcAmp;
extern CString g_sLangTxt_Native_IcAmp;
/*"Ic��λ"*/
extern CString g_sLangID_Native_IcPhase;
extern CString g_sLangTxt_Native_IcPhase;
/*"IcƵ��"*/
extern CString g_sLangID_Native_IcFreq;
extern CString g_sLangTxt_Native_IcFreq;

/*"Iap��ֵ"*/
extern CString g_sLangID_Native_IapAmp;
extern CString g_sLangTxt_Native_IapAmp;
/*"Iap��λ"*/
extern CString g_sLangID_Native_IapPhase;
extern CString g_sLangTxt_Native_IapPhase;
/*"IapƵ��"*/
extern CString g_sLangID_Native_IapFreq;
extern CString g_sLangTxt_Native_IapFreq;

/*"Ibp��ֵ"*/
extern CString g_sLangID_Native_IbpAmp;
extern CString g_sLangTxt_Native_IbpAmp;
/*"Ibp��λ"*/
extern CString g_sLangID_Native_IbpPhase;
extern CString g_sLangTxt_Native_IbpPhase;
/*"IbpƵ��"*/
extern CString g_sLangID_Native_IbpFreq;
extern CString g_sLangTxt_Native_IbpFreq;

/*"Icp��ֵ"*/
extern CString g_sLangID_Native_IcpAmp;
extern CString g_sLangTxt_Native_IcpAmp;
/*"Icp��λ"*/
extern CString g_sLangID_Native_IcpPhase;
extern CString g_sLangTxt_Native_IcpPhase;
/*"IcpƵ��"*/
extern CString g_sLangID_Native_IcpFreq;
extern CString g_sLangTxt_Native_IcpFreq;

/*"���Թ������(0:��ͨ�ֶ�����1:MU���Ȳ���2:MU��Ư����)"*/
extern CString g_sLangID_Native_TestFuncCategory;
extern CString g_sLangTxt_Native_TestFuncCategory;

//tmt_pt_test
/*"PT1��ֵ"*/
extern CString g_sLangID_Native_PT1Impedance;
extern CString g_sLangTxt_Native_PT1Impedance;
/*"PT2��ֵ"*/
extern CString g_sLangID_Native_PT2Impedance;
extern CString g_sLangTxt_Native_PT2Impedance;

//tmt_record
/*"���չ��"*/
extern CString g_sLangID_Native_RecvOptPort;
extern CString g_sLangTxt_Native_RecvOptPort;
/*"��������"*/
extern CString g_sLangID_Native_TotalSubs;
extern CString g_sLangTxt_Native_TotalSubs;


//tmt_NEW
/*"Uas��ֵ"*/
extern CString g_sLangID_Native_UasAmp;
extern CString g_sLangTxt_Native_UasAmp;
/*"Uas��λ"*/
extern CString g_sLangID_Native_UasPhase;
extern CString g_sLangTxt_Native_UasPhase;
/*"UasƵ��"*/
extern CString g_sLangID_Native_UasFreq;
extern CString g_sLangTxt_Native_UasFreq;

/*"Ubs��ֵ"*/
extern CString g_sLangID_Native_UbsAmp;
extern CString g_sLangTxt_Native_UbsAmp;
/*"Ubs��λ"*/
extern CString g_sLangID_Native_UbsPhase;
extern CString g_sLangTxt_Native_UbsPhase;
/*"UbsƵ��"*/
extern CString g_sLangID_Native_UbsFreq;
extern CString g_sLangTxt_Native_UbsFreq;

/*"Ucs��ֵ"*/
extern CString g_sLangID_Native_UcsAmp;
extern CString g_sLangTxt_Native_UcsAmp;
/*"Ucs��λ"*/
extern CString g_sLangID_Native_UcsPhase;
extern CString g_sLangTxt_Native_UcsPhase;
/*"UcsƵ��"*/
extern CString g_sLangID_Native_UcsFreq;
extern CString g_sLangTxt_Native_UcsFreq;

/*"Uat��ֵ"*/
extern CString g_sLangID_Native_UatAmp;
extern CString g_sLangTxt_Native_UatAmp;
/*"Uat��λ"*/
extern CString g_sLangID_Native_UatPhase;
extern CString g_sLangTxt_Native_UatPhase;
/*"UatƵ��"*/
extern CString g_sLangID_Native_UatFreq;
extern CString g_sLangTxt_Native_UatFreq;

/*"Ubt��ֵ"*/
extern CString g_sLangID_Native_UbtAmp;
extern CString g_sLangTxt_Native_UbtAmp;
/*"Ubt��λ"*/
extern CString g_sLangID_Native_UbtPhase;
extern CString g_sLangTxt_Native_UbtPhase;
/*"UbtƵ��"*/
extern CString g_sLangID_Native_UbtFreq;
extern CString g_sLangTxt_Native_UbtFreq;

/*"Uct��ֵ"*/
extern CString g_sLangID_Native_UctAmp;
extern CString g_sLangTxt_Native_UctAmp;
/*"Uct��λ"*/
extern CString g_sLangID_Native_UctPhase;
extern CString g_sLangTxt_Native_UctPhase;
/*"UctƵ��"*/
extern CString g_sLangID_Native_UctFreq;
extern CString g_sLangTxt_Native_UctFreq;

/*"Ias��ֵ"*/
extern CString g_sLangID_Native_IasAmp;
extern CString g_sLangTxt_Native_IasAmp;
/*"Ias��λ"*/
extern CString g_sLangID_Native_IasPhase;
extern CString g_sLangTxt_Native_IasPhase;
/*"IasƵ��"*/
extern CString g_sLangID_Native_IasFreq;
extern CString g_sLangTxt_Native_IasFreq;

/*"Ibs��ֵ"*/
extern CString g_sLangID_Native_IbsAmp;
extern CString g_sLangTxt_Native_IbsAmp;
/*"Ibs��λ"*/
extern CString g_sLangID_Native_IbsPhase;
extern CString g_sLangTxt_Native_IbsPhase;
/*"IbsƵ��"*/
extern CString g_sLangID_Native_IbsFreq;
extern CString g_sLangTxt_Native_IbsFreq;

/*"Ics��ֵ"*/
extern CString g_sLangID_Native_IcsAmp;
extern CString g_sLangTxt_Native_IcsAmp;
/*"Ics��λ"*/
extern CString g_sLangID_Native_IcsPhase;
extern CString g_sLangTxt_Native_IcsPhase;
/*"IcsƵ��"*/
extern CString g_sLangID_Native_IcsFreq;
extern CString g_sLangTxt_Native_IcsFreq;

/*"Iat��ֵ"*/
extern CString g_sLangID_Native_IatAmp;
extern CString g_sLangTxt_Native_IatAmp;
/*"Iat��λ"*/
extern CString g_sLangID_Native_IatPhase;
extern CString g_sLangTxt_Native_IatPhase;
/*"IatƵ��"*/
extern CString g_sLangID_Native_IatFreq;
extern CString g_sLangTxt_Native_IatFreq;

/*"Ibt��ֵ"*/
extern CString g_sLangID_Native_IbtAmp;
extern CString g_sLangTxt_Native_IbtAmp;
/*"Ibt��λ"*/
extern CString g_sLangID_Native_IbtPhase;
extern CString g_sLangTxt_Native_IbtPhase;
/*"IbtƵ��"*/
extern CString g_sLangID_Native_IbtFreq;
extern CString g_sLangTxt_Native_IbtFreq;

/*"Ict��ֵ"*/
extern CString g_sLangID_Native_IctAmp;
extern CString g_sLangTxt_Native_IctAmp;
/*"Ict��λ"*/
extern CString g_sLangID_Native_IctPhase;
extern CString g_sLangTxt_Native_IctPhase;
/*"IctƵ��"*/
extern CString g_sLangID_Native_IctFreq;
extern CString g_sLangTxt_Native_IctFreq;




//tmt_replay_test
/*"ģ��%d"*/
extern CString g_sLangID_Native_ModReplace;
extern CString g_sLangTxt_Native_ModReplace;
/*"������ͨ��%d_Aͨ�����"*/
extern CString g_sLangID_Native_TIC_A_Chn_Num;
extern CString g_sLangTxt_Native_TIC_A_Chn_Num;
/*"������ͨ��%d_Bͨ�����"*/
extern CString g_sLangID_Native_TIC_B_Chn_Num;
extern CString g_sLangTxt_Native_TIC_B_Chn_Num;
/*"������ͨ��%d_���"*/
extern CString g_sLangID_Native_TIC_TransfRatio;
extern CString g_sLangTxt_Native_TIC_TransfRatio;
/*"����Ƶ��"*/
extern CString g_sLangID_Native_SampFreq;
extern CString g_sLangTxt_Native_SampFreq;
//"�������"
extern CString g_sLangID_Native_OutputRate;
extern CString g_sLangTxt_Native_OutputRate;
/*"PT���һ��ֵ"*/
extern CString g_sLangID_Native_PT_TxRatio_Primary;
extern CString g_sLangTxt_Native_PT_TxRatio_Primary;
/*"PT��ȶ���ֵ"*/
extern CString g_sLangID_Native_PT_TxRatio_Secondary;
extern CString g_sLangTxt_Native_PT_TxRatio_Secondary;
/*"CT���һ��ֵ"*/
extern CString g_sLangID_Native_CT_TxRatio_Primary;
extern CString g_sLangTxt_Native_CT_TxRatio_Primary;
/*"CT��ȶ���ֵ"*/
extern CString g_sLangID_Native_CT_TxRatio_Secondary;
extern CString g_sLangTxt_Native_CT_TxRatio_Secondary;
/*"ģ����"*/
extern CString g_sLangID_Native_NumOfModules;
extern CString g_sLangTxt_Native_NumOfModules;
/*"¼���ļ�����"*/
extern CString g_sLangID_Native_WaveFileName;
extern CString g_sLangTxt_Native_WaveFileName;
/*"�ܲ���"*/
extern CString g_sLangID_Native_NumCycles;
extern CString g_sLangTxt_Native_NumCycles;
/*"������ģʽ"*/
extern CString g_sLangID_Native_PostTrigMode;
extern CString g_sLangTxt_Native_PostTrigMode;
/*"ʵ�鴥��ʱ��"*/
extern CString g_sLangID_Native_ExpTrigTime;
extern CString g_sLangTxt_Native_ExpTrigTime;
/*"ȫ��ѭ������"*/
extern CString g_sLangID_Native_CycleIndex;
extern CString g_sLangTxt_Native_CycleIndex;
/*"�ֶ�����"*/
extern CString g_sLangID_Native_ManualControl;
extern CString g_sLangTxt_Native_ManualControl;	 
/*"ʱ����"*/
extern CString g_sLangID_Native_ReplayInterval;
extern CString g_sLangTxt_Native_ReplayInterval;
//�迹���Ա༭��
extern CString g_sLangID_Native_ImpedanceEditBox;
extern CString g_sLangTxt_Native_ImpedanceEditBox;

extern CString g_sLangID_Native_SeqComp;
extern CString g_sLangTxt_Native_SeqComp;


//�ھ�����
//extern CString g_sLangID_Native_jumpctrl;
//extern CString g_sLangTxt_Native_jumpctrl;//�����źſ���
//extern CString g_sLangID_Native_timectrl;
//extern CString g_sLangTxt_Native_timectrl;//ʱ�����
//extern CString g_sLangID_Native_totalweight;
//extern CString g_sLangTxt_Native_totalweight;//���أ�����+���أ�
//extern CString g_sLangID_Native_tripleweight;
//extern CString g_sLangTxt_Native_tripleweight;//����
//extern CString g_sLangID_Native_norepeat;
//extern CString g_sLangTxt_Native_norepeat;//���غ�
//extern CString g_sLangID_Native_Totransformer;
//extern CString g_sLangTxt_Native_Totransformer;//ָ���ѹ��
//extern CString g_sLangID_Native_lagrange;
//extern CString g_sLangTxt_Native_lagrange;//�������ղ�ֵ��
//extern CString g_sLangID_Native_linear;
//extern CString g_sLangTxt_Native_linear;//���Բ�ֵ��
//extern CString g_sLangID_Native_faultvoltype;
//extern CString g_sLangTxt_Native_faultvoltype;//���ϵ�ѹ����
//
//extern CString g_sLangID_Native_Difsetting;
//extern CString g_sLangTxt_Native_Difsetting;//���ֵ������ʽ
//extern CString g_sLangID_Native_DifCurChoose;
//extern CString g_sLangTxt_Native_DifCurChoose;//���׼����ѡ��
//extern CString g_sLangID_Native_harmonicnumber;
//extern CString g_sLangTxt_Native_harmonicnumber;//г������ѡ��
//extern CString g_sLangID_Native_CuroutputPhase;
//extern CString g_sLangTxt_Native_CuroutputPhase;//���������
//extern CString g_sLangID_Native_PhaseAshort;
//extern CString g_sLangTxt_Native_PhaseAshort;//A���·
//extern CString g_sLangID_Native_PhaseBshort;
//extern CString g_sLangTxt_Native_PhaseBshort;//B���·
//extern CString g_sLangID_Native_PhaseCshort;
//extern CString g_sLangTxt_Native_PhaseCshort;//C���·
//extern CString g_sLangID_Native_PhaseABCshort;
//extern CString g_sLangTxt_Native_PhaseABCshort;//ABC���·


//UI
//Harm
extern CString g_sLangID_Native_VolactValue;
extern CString g_sLangTxt_Native_VolactValue;//��ѹ����ֵ(%)
extern CString g_sLangID_Native_CuractValue;
extern CString g_sLangTxt_Native_CuractValue;//��������ֵ(%)
extern CString g_sLangID_Native_harmonicNotChecked;
extern CString g_sLangTxt_Native_harmonicNotChecked;//ָ��ͨ����г��δ����ѡ!

//IEC61850Config
extern CString g_sLangID_Native_DCVmapping;
extern CString g_sLangTxt_Native_DCVmapping;//ֱ����ѹӳ��
extern CString g_sLangID_Native_DCImapping;
extern CString g_sLangTxt_Native_DCImapping;//ֱ������ӳ��
extern CString g_sLangID_Native_ACVmapping;
extern CString g_sLangTxt_Native_ACVmapping;//������ѹӳ��
extern CString g_sLangID_Native_ACImapping;
extern CString g_sLangTxt_Native_ACImapping;//��������ӳ��
extern CString g_sLangID_Native_FailtoGetsclPath;
extern CString g_sLangTxt_Native_FailtoGetsclPath;//��ȡSCL�ļ�·��ʧ��(%s).
extern CString g_sLangID_Native_codesSetting;
extern CString g_sLangTxt_Native_codesSetting;//��ֵ����
extern CString g_sLangID_Native_DCPart;
extern CString g_sLangTxt_Native_DCPart;//ֱ������
extern CString g_sLangID_Native_ACPart;
extern CString g_sLangTxt_Native_ACPart;//��������

extern CString g_sLangID_Native_selected;
extern CString g_sLangTxt_Native_selected;//��ѡ��
extern CString g_sLangID_Native_schematic;
extern CString g_sLangTxt_Native_schematic;//ʾ��ͼ
extern CString g_sLangID_Native_codesValue;
extern CString g_sLangTxt_Native_codesValue;//��ֵ

//ImportDvmFile
extern CString g_sLangID_Native_modifyto;
extern CString g_sLangTxt_Native_modifyto;//�޸�Ϊ
extern CString g_sLangID_Native_function;
extern CString g_sLangTxt_Native_function;//����
extern CString g_sLangID_Native_completeconfig;
extern CString g_sLangTxt_Native_completeconfig;//�������
extern CString g_sLangID_Native_nextitem;
extern CString g_sLangTxt_Native_nextitem;//��һ��
extern CString g_sLangID_Native_previtem;
extern CString g_sLangTxt_Native_previtem;//��һ��
extern CString g_sLangID_Native_ttybzd;
extern CString g_sLangTxt_Native_ttybzd;//_Ͷ��ѹ������
extern CString g_sLangID_Native_FixedValueSet;
extern CString g_sLangTxt_Native_FixedValueSet;//_�޸Ķ�ֵ����

//KeyBoard
extern CString g_sLangID_Native_PYResnotFound;
extern CString g_sLangTxt_Native_PYResnotFound;//û���ҵ�����ƴ����Դ�ļ�!

//
extern CString g_sLangID_Native_dataid;
extern CString g_sLangTxt_Native_dataid;//����ID
extern CString g_sLangID_Native_paramselect;
extern CString g_sLangTxt_Native_paramselect;//����ѡ��

extern CString g_sLangID_Native_globalparams;
extern CString g_sLangTxt_Native_globalparams;//ȫ�ֲ���
extern CString g_sLangID_Native_reportdata;
extern CString g_sLangTxt_Native_reportdata;//��������
extern CString g_sLangID_Native_switchreport;
extern CString g_sLangTxt_Native_switchreport;//�л�����
extern CString g_sLangID_Native_reportdataname;
extern CString g_sLangTxt_Native_reportdataname;//������������

extern CString g_sLangID_Native_paramone;
extern CString g_sLangTxt_Native_paramone;//����һ
extern CString g_sLangID_Native_paramtwo;
extern CString g_sLangTxt_Native_paramtwo;//������
extern CString g_sLangID_Native_baselineparams;
extern CString g_sLangTxt_Native_baselineparams;//��׼����
extern CString g_sLangID_Native_errorresult;
extern CString g_sLangTxt_Native_errorresult;//�����
extern CString g_sLangID_Native_errorlimit;
extern CString g_sLangTxt_Native_errorlimit;//�����
extern CString g_sLangID_Native_notcalculated;
extern CString g_sLangTxt_Native_notcalculated;//δ����
extern CString g_sLangID_Native_baseline_min;
extern CString g_sLangTxt_Native_baseline_min;//��׼-��Сֵ
extern CString g_sLangID_Native_baseline_max;
extern CString g_sLangTxt_Native_baseline_max;//��׼-���ֵ
extern CString g_sLangID_Native_operationresult;
extern CString g_sLangTxt_Native_operationresult;//������



//�ھ�����
//10.30
//���������ѡ����Ҫӳ��Ĳ�����Ȼ���ٽ���ӳ�䡭��
extern CString g_sLangID_Native_SelectParamFirst;
extern CString g_sLangTxt_Native_SelectParamFirst;
//��ǰ����û�ҵ���Ч��ӳ�����ݣ�������Ч��
extern CString g_sLangID_Native_NoValidMapData;
extern CString g_sLangTxt_Native_NoValidMapData;
//װ��ģ�ͣ������������ѡ����Ҫӳ��Ĳ�����Ȼ��˫��ӳ�䣩
extern CString g_sLangID_Native_DeviceModel;
extern CString g_sLangTxt_Native_DeviceModel;
//���ݼ���
extern CString g_sLangID_Native_Dataset;
extern CString g_sLangTxt_Native_Dataset;
//����
extern CString g_sLangID_Native_AddNew;
extern CString g_sLangTxt_Native_AddNew;
//�������ӳ��
extern CString g_sLangID_Native_ClearMap;
extern CString g_sLangTxt_Native_ClearMap;
//���ѡ��ӳ��
extern CString g_sLangID_Native_ClearSel;
extern CString g_sLangTxt_Native_ClearSel;
//�Զ�������
extern CString g_sLangID_Native_CustomName;
extern CString g_sLangTxt_Native_CustomName;
//ʵ��װ�õ���������
extern CString g_sLangID_Native_RealDevData;
extern CString g_sLangTxt_Native_RealDevData;
//�����������ݼ�
extern CString g_sLangID_Native_DataInSet;
extern CString g_sLangTxt_Native_DataInSet;
//��������:
extern CString g_sLangID_Native_CurveName;
extern CString g_sLangTxt_Native_CurveName;
//1�ζ�ʱ��
extern CString g_sLangID_Native_SingleTimeLimit;
extern CString g_sLangTxt_Native_SingleTimeLimit;
//2�ζ�ʱ��
extern CString g_sLangID_Native_DoubleTimeLimit;
extern CString g_sLangTxt_Native_DoubleTimeLimit;
//3�ζ�ʱ��
extern CString g_sLangID_Native_TripleTimeLimit;
extern CString g_sLangTxt_Native_TripleTimeLimit;
//����ֵ
extern CString g_sLangID_Native_CurrentValueI;
extern CString g_sLangTxt_Native_CurrentValueI;
//�����ż�
extern CString g_sLangID_Native_ActionThres;
extern CString g_sLangTxt_Native_ActionThres;
//��������Ԫ��
extern CString g_sLangID_Native_FeatCurveElem;
extern CString g_sLangTxt_Native_FeatCurveElem;
//IEEE����Ԫ������
extern CString g_sLangID_Native_IEEECurveSet;
extern CString g_sLangTxt_Native_IEEECurveSet;
//IAC����Ԫ������
extern CString g_sLangID_Native_IACCurveSet;
extern CString g_sLangTxt_Native_IACCurveSet;
//I2T����Ԫ������
extern CString g_sLangID_Native_I2TCurveSet;
extern CString g_sLangTxt_Native_I2TCurveSet;
//IEC����Ԫ������
extern CString g_sLangID_Native_IECCurveSet;
extern CString g_sLangTxt_Native_IECCurveSet;
//�ż�ֵ
extern CString g_sLangID_Native_Threshold;
extern CString g_sLangTxt_Native_Threshold;
//�ٶ϶�ֵ
extern CString g_sLangID_Native_QuickBreak;
extern CString g_sLangTxt_Native_QuickBreak;
//��һ��
extern CString g_sLangID_Native_FirstPart;
extern CString g_sLangTxt_Native_FirstPart;
//�յ�1
extern CString g_sLangID_Native_Inflection1;
extern CString g_sLangTxt_Native_Inflection1;
//�ڶ���
extern CString g_sLangID_Native_SecondPart;
extern CString g_sLangTxt_Native_SecondPart;
//�յ�2
extern CString g_sLangID_Native_InflectionPoint2;
extern CString g_sLangTxt_Native_InflectionPoint2;
//��ǰ���Կ��Ƴ�����������(%s).
extern CString g_sLangID_Native_TestCtrlProgDate;
extern CString g_sLangTxt_Native_TestCtrlProgDate;
//�������
extern CString g_sLangID_Native_DebugOutput;
extern CString g_sLangTxt_Native_DebugOutput;
//��ʼ���
//extern CString g_sLangID_Native_StartOutput;
//extern CString g_sLangTxt_Native_StartOutput;
//ֹͣ���
extern CString g_sLangID_Native_StopOutput;
extern CString g_sLangTxt_Native_StopOutput;
//���ļ�(%s)ʧ��.
extern CString g_sLangID_Native_OpenFail;
extern CString g_sLangTxt_Native_OpenFail;
//������ǶϿ����ӣ�����������·�Ƿ���ͨ��IP��ַ���˿������Ƿ���ȷ����������
extern CString g_sLangID_Native_Disconnect;
extern CString g_sLangTxt_Native_Disconnect;
//״̬ͼ
extern CString g_sLangID_Native_StateGraph;
extern CString g_sLangTxt_Native_StateGraph;
//�����Դ��ʶ
extern CString g_sLangID_Native_SoftResID;
extern CString g_sLangTxt_Native_SoftResID;
//��������ֵ������Ϊ�գ�
extern CString g_sLangID_Native_EnterNum;
extern CString g_sLangTxt_Native_EnterNum;
//���ܲ�����
extern CString g_sLangID_Native_SendByWave;
extern CString g_sLangTxt_Native_SendByWave;
//���뷢��
extern CString g_sLangID_Native_SendBySec;
extern CString g_sLangTxt_Native_SendBySec;
//��ǰ״̬%d : �����ʶ(0x%s)��ԭ�����ʶ(0x%s)��һ��
extern CString g_sLangID_Native_StateNetID;
extern CString g_sLangTxt_Native_StateNetID;
//����Word����
extern CString g_sLangID_Native_ExportWords;
extern CString g_sLangTxt_Native_ExportWords;
//Word�����ļ� (*.doc)
extern CString g_sLangID_Native_WordDoc;
extern CString g_sLangTxt_Native_WordDoc;
//����·����
extern CString g_sLangID_Native_ExportPath;
extern CString g_sLangTxt_Native_ExportPath;
//_T("PDF����(*.pdf)")
extern CString g_sLangID_Native_Pdfpdf;
extern CString g_sLangTxt_Native_Pdfpdf;




//�ھ�����
/*_T("stt_rcd_unzip_file��ѹ������.")*/
extern CString g_sLangID_Native_UnzipError;
extern CString g_sLangTxt_Native_UnzipError;
/*_T("����Pcap�ļ�����")*/
extern CString g_sLangID_Native_ExpPcapInterf;
extern CString g_sLangTxt_Native_ExpPcapInterf;
/*_T("ԭʼ�����ļ�:")*/
extern CString g_sLangID_Native_RawDataFile;
extern CString g_sLangTxt_Native_RawDataFile;
/*_T("ѡ��...")*/
extern CString g_sLangID_Native_SelectOmit;
extern CString g_sLangTxt_Native_SelectOmit;
/*_T("Pcap�ļ���:")*/
extern CString g_sLangID_Native_PcapFileN;
extern CString g_sLangTxt_Native_PcapFileN;
/*_T("��ʼת��")*/
extern CString g_sLangID_Native_StartConver;
extern CString g_sLangTxt_Native_StartConver;
/*_T("at02dѹ���ļ�(*.at02dz);;at02d�ļ�(*.at02d)")*/
extern CString g_sLangID_Native_at02dCompFiles;
extern CString g_sLangTxt_Native_at02dCompFiles;
/*_T("����ѡ��ԭʼ�����ļ�.")*/
extern CString g_sLangID_Native_SelectRawFile;
extern CString g_sLangTxt_Native_SelectRawFile;
/*_T("�������������ļ�����.")*/
extern CString g_sLangID_Native_SetOutFileName;
extern CString g_sLangTxt_Native_SetOutFileName;
/*_T("��ǰԭʼ�����ļ�(%s)������.")*/
extern CString g_sLangID_Native_CurRawFileNotEx;
extern CString g_sLangTxt_Native_CurRawFileNotEx;
/*_T("Pcap�ļ�(%s)���ɳɹ�.")*/
extern CString g_sLangID_Native_PcapGenSuccess;
extern CString g_sLangTxt_Native_PcapGenSuccess;
/*_T("Pcap�ļ�(%s)����ʧ��.")*/
extern CString g_sLangID_Native_PcapGenFailed;
extern CString g_sLangTxt_Native_PcapGenFailed;
/*"������"*/
extern CString g_sLangID_Native_BaudRate;
extern CString g_sLangTxt_Native_BaudRate;
/*"���ĳ���"*/
extern CString g_sLangID_Native_MsgLength;
extern CString g_sLangTxt_Native_MsgLength;
/*_T("δ֪�ı�������(%u).")*/
extern CString g_sLangID_Native_UnkwnMsgType;
extern CString g_sLangTxt_Native_UnkwnMsgType;
/*_T("��ǰ�����ı���֡��Ϊ0,���յ����ĺ�,���ܹ���.")*/
extern CString g_sLangID_Native_CurrPsdM0AssocAftRcvM;
extern CString g_sLangTxt_Native_CurrPsdM0AssocAftRcvM;
/*("¼��ʱ��")*/
extern CString g_sLangID_Native_RecTime;
extern CString g_sLangTxt_Native_RecTime;
/*_T("ֹͣ¼��")*/
extern CString g_sLangID_Native_StopRecrd;
extern CString g_sLangTxt_Native_StopRecrd;
/*_T("��Чֵ")*/
extern CString g_sLangID_Native_ValdValue;
extern CString g_sLangTxt_Native_ValdValue;
/*_T("������")*/
extern CString g_sLangID_Native_IncRate;
extern CString g_sLangTxt_Native_IncRate;
/*_T("��״ͼ")*/
extern CString g_sLangID_Native_BarChar;
extern CString g_sLangTxt_Native_BarChar;
/*_T("¼��")*/
extern CString g_sLangID_Native_RecWaveform;
extern CString g_sLangTxt_Native_RecWaveform;
/*_T("��ǰд�ļ�·��Ϊ��.")*/
extern CString g_sLangID_Native_CurrWrtFileEmpty;
extern CString g_sLangTxt_Native_CurrWrtFileEmpty;
/*_T("�ļ�����Ϊ")*/
extern CString g_sLangID_Native_SaveAs;
extern CString g_sLangTxt_Native_SaveAs;
/*_T("�ļ�(%s)����ɹ�.")*/
extern CString g_sLangID_Native_FileSavedSucc;
extern CString g_sLangTxt_Native_FileSavedSucc;
/*_T("�ļ�(%s)����ʧ��.")*/
extern CString g_sLangID_Native_FileSaveFailed;
extern CString g_sLangTxt_Native_FileSaveFailed;
/*�ļ��Ѵ��ڣ��Ƿ��滻��*/
extern CString g_sLangID_Native_FileExist;
extern CString g_sLangTxt_Native_FileExist;
/*�ļ�����ɹ�*/
extern CString g_sLangID_Native_FileSave;
extern CString g_sLangTxt_Native_FileSave;
/*����*/
extern CString g_sLangID_Native_Accept;
extern CString g_sLangTxt_Native_Accept;
/*_T("SV������ɢ����ͼ")*/
extern CString g_sLangID_Native_SVMsgDispersView;
extern CString g_sLangTxt_Native_SVMsgDispersView;
/*_T("ֱ��(V/A)")*/
extern CString g_sLangID_Native_DCVoltAmp;
extern CString g_sLangTxt_Native_DCVoltAmp;
/*_T("����(V/A)")*/
extern CString g_sLangID_Native_FundamentalVA;
extern CString g_sLangTxt_Native_FundamentalVA;
/*_T("�ײ����ģ������ʧ��.")*/
extern CString g_sLangID_Native_LowLevelTmplFail;
extern CString g_sLangTxt_Native_LowLevelTmplFail;
/*_T("��ʼ���������·�ʧ��.")*/
extern CString g_sLangID_Native_StartTestSendFail;
extern CString g_sLangTxt_Native_StartTestSendFail;
/*_T("ֹͣ���������·�ʧ��.")*/
extern CString g_sLangID_Native_StopTestSendFail;
extern CString g_sLangTxt_Native_StopTestSendFail;
/*_T("״̬%ld����ʱ��%.4lfs.")*/
extern CString g_sLangID_Native_StatusLDActTime;
extern CString g_sLangTxt_Native_StatusLDActTime;
/*_T("?????????????? OnCmd_NewTest: �رմ򿪵Ĳ��Թ���ҳ�棬��������ʾ�Ƿ񱣴��޸� ???????????")*/
extern CString g_sLangID_Native_CloseFeatPromptSave;
extern CString g_sLangTxt_Native_CloseFeatPromptSave;
//��������
extern CString g_sLangID_Native_InsData;
extern CString g_sLangTxt_Native_InsData;
//ִ��ͨ��
extern CString g_sLangID_Native_ExecComm;
extern CString g_sLangTxt_Native_ExecComm;
//ɾ��ѡ������
extern CString g_sLangID_Native_DelSelData;
extern CString g_sLangTxt_Native_DelSelData;
/*"�Ƿ�仯����"*/
extern CString g_sLangID_Native_SendChanges;
extern CString g_sLangTxt_Native_SendChanges;
//����ʱ��
extern CString g_sLangID_Native_CycleTm;
extern CString g_sLangTxt_Native_CycleTm;
//�������
extern CString g_sLangID_Native_ErrName;
extern CString g_sLangTxt_Native_ErrName;
//���ֵ
extern CString g_sLangID_Native_ErrValue;
extern CString g_sLangTxt_Native_ErrValue;
//���Է���
extern CString g_sLangID_Native_TestCat;
extern CString g_sLangTxt_Native_TestCat;
//����ȼ�
extern CString g_sLangID_Native_TitleLvl;
extern CString g_sLangTxt_Native_TitleLvl;
//��Ŀ��ʶ
extern CString g_sLangID_Native_ProjIdent;
extern CString g_sLangTxt_Native_ProjIdent;
//��ΪWord����
extern CString g_sLangID_Native_AsWordTitle;
extern CString g_sLangTxt_Native_AsWordTitle;
//�޸���Ŀ����
extern CString g_sLangID_Native_ModProjName;
extern CString g_sLangTxt_Native_ModProjName;
//��
extern CString g_sLangID_Native_Wizard;
extern CString g_sLangTxt_Native_Wizard;
//��һ��
extern CString g_sLangID_Native_PrevStep;
extern CString g_sLangTxt_Native_PrevStep;
/*_T("��ҳ�ļ�(%s)������.")*/
extern CString g_sLangID_Native_WebPageNotExst;
extern CString g_sLangTxt_Native_WebPageNotExst;
/*_T("δѡ��IED")*/
extern CString g_sLangID_Native_IEDNotSel;
extern CString g_sLangTxt_Native_IEDNotSel;


//Controls
//�豸����
extern CString g_sLangID_Native_DevType;
extern CString g_sLangTxt_Native_DevType;
//��Լ����
extern CString g_sLangID_Native_ProtoEngin;
extern CString g_sLangTxt_Native_ProtoEngin;
//װ��IP
extern CString g_sLangID_Native_DevIP;
extern CString g_sLangTxt_Native_DevIP;
//װ�ö˿�
extern CString g_sLangID_Native_DevPort;
extern CString g_sLangTxt_Native_DevPort;
//��Լģ��
extern CString g_sLangID_Native_ProtoTemp;
extern CString g_sLangTxt_Native_ProtoTemp;
//��SCD�ļ�ѡ��
extern CString g_sLangID_Native_SelSCDFile;
extern CString g_sLangTxt_Native_SelSCDFile;
//�߼�����
extern CString g_sLangID_Native_AdvConfig;
extern CString g_sLangTxt_Native_AdvConfig;
//ʱ�䶨ֵ��λΪms
extern CString g_sLangID_Native_TimeSetUnit;
extern CString g_sLangTxt_Native_TimeSetUnit;
//���װ�ø���̬
extern CString g_sLangID_Native_AddDevReset;
extern CString g_sLangTxt_Native_AddDevReset;
/*"�·���"*/
extern CString g_sLangID_Native_NewCat;
extern CString g_sLangTxt_Native_NewCat;
/*"������ͬ���Ƶ���Ŀ"*/
extern CString g_sLangID_Native_ProjSameExists;
extern CString g_sLangTxt_Native_ProjSameExists;
/*"������ͬID����Ŀ"*/
extern CString g_sLangID_Native_ProjSameIDExists;
extern CString g_sLangTxt_Native_ProjSameIDExists;
//���Դ��� >1ʱ���Զ����µ���Ŀ����
extern CString g_sLangID_Native_TestCntGt1AutoUpdtProjName;
extern CString g_sLangTxt_Native_TestCntGt1AutoUpdtProjName;
//������Ϊword����
extern CString g_sLangID_Native_NameWordTitle;
extern CString g_sLangTxt_Native_NameWordTitle;
/*_T("���ڴ˴����������ʾ��Ϣ����")*/
extern CString g_sLangID_Native_PlsEntWiringInstruc;
extern CString g_sLangTxt_Native_PlsEntWiringInstruc;
/*_T("δ�ҵ���Ӧ��Ԥ����ʾ��Ϣ�����ڴ˴����������ʾ��Ϣ����")*/
extern CString g_sLangID_Native_NoMatchPresetInstrucPlsEntWiring;
extern CString g_sLangTxt_Native_NoMatchPresetInstrucPlsEntWiring;
//ѡ����Ҫ�Ľ�����ʾ��Ϣ
extern CString g_sLangID_Native_SelDesiredWiringInstruc;
extern CString g_sLangTxt_Native_SelDesiredWiringInstruc;
/*"ȷʵҪɾ�� ["*/
extern CString g_sLangID_Native_DeletestrMsg;
extern CString g_sLangTxt_Native_DeletestrMsg;
/*"] ��"*/
extern CString g_sLangID_Native_DeletestrMsg2;
extern CString g_sLangTxt_Native_DeletestrMsg2;
/*_T(" ] ��ɾ�����޷��ָ���")*/
extern CString g_sLangID_Native_DeletestrMsg3;
extern CString g_sLangTxt_Native_DeletestrMsg3;
/*"���Ժ�ָ�"*/
extern CString g_sLangID_Native_RestoreAfterTest;
extern CString g_sLangTxt_Native_RestoreAfterTest;
/*"����ǰ׼��"*/
extern CString g_sLangID_Native_PrepBeforeTest;
extern CString g_sLangTxt_Native_PrepBeforeTest;
/*tr("�½���Ŀ����")*/
extern CString g_sLangID_Native_CreateProjCat;
extern CString g_sLangTxt_Native_CreateProjCat;
/*tr("�½�����ǰ׼��")*/
extern CString g_sLangID_Native_CreatePrepBeforeTest;
extern CString g_sLangTxt_Native_CreatePrepBeforeTest;
/*tr("�½����Ժ�ָ�")*/
extern CString g_sLangID_Native_CreateReplyAfterTest;
extern CString g_sLangTxt_Native_CreateReplyAfterTest;
/*tr("ɾ����ǰѡ����Ŀ")*/
extern CString g_sLangID_Native_DeleteCurrSelectedProj;
extern CString g_sLangTxt_Native_DeleteCurrSelectedProj;
/*tr("�༭��ǰѡ����Ŀ")*/
extern CString g_sLangID_Native_EditCurrSelectedProj;
extern CString g_sLangTxt_Native_EditCurrSelectedProj;
/*tr("���浱ǰѡ����Ŀ")*/
extern CString g_sLangID_Native_SaveCurrSelectedProj;
extern CString g_sLangTxt_Native_SaveCurrSelectedProj;
/*tr("��ӹ�����")*/
extern CString g_sLangID_Native_AddFuncWizard;
extern CString g_sLangTxt_Native_AddFuncWizard;
/*tr("�ӵ�ǰѡ����Ŀ��ʼ����")*/
extern CString g_sLangID_Native_StartTestFromSelProj;
extern CString g_sLangTxt_Native_StartTestFromSelProj;
/*tr("���Ե�ǰѡ����Ŀ")*/
extern CString g_sLangID_Native_TestCurrSelProj;
extern CString g_sLangTxt_Native_TestCurrSelProj;
/*"�½�ͨѶ����"*/
extern CString g_sLangID_Native_CreateCommCommand;
extern CString g_sLangTxt_Native_CreateCommCommand;
/*_T("ȷ��ɾ����Ŀ")*/
extern CString g_sLangID_Native_ConfirmDelProj;
extern CString g_sLangTxt_Native_ConfirmDelProj;
/*_T("��������ǰѡ����Ŀ")*/
extern CString g_sLangID_Native_RenameCurrSelProj;
extern CString g_sLangTxt_Native_RenameCurrSelProj;
/*_T("ɾ��������ʾ")*/
extern CString g_sLangID_Native_DeleteWiringInstr;
extern CString g_sLangTxt_Native_DeleteWiringInstr;
/*_T("��Ӳ���ǰ����ͨѶ���")*/
extern CString g_sLangID_Native_AddPrePostCommCombo;
extern CString g_sLangTxt_Native_AddPrePostCommCombo;
/*_T("�½�������Ŀ")*/
extern CString g_sLangID_Native_CreateConfigProj;
extern CString g_sLangTxt_Native_CreateConfigProj;
/*_T("Ӳ��ͨ��ӳ��")*/
extern CString g_sLangID_Native_HWChanMapping;
extern CString g_sLangTxt_Native_HWChanMapping;
/*_T("IEC61850����")*/
extern CString g_sLangID_Native_IEC61850Config;
extern CString g_sLangTxt_Native_IEC61850Config;
/*_T("ȷ��ɾ��������ʾ")*/
extern CString g_sLangID_Native_ConfirmDelWiringInstr;
extern CString g_sLangTxt_Native_ConfirmDelWiringInstr;
/*_T("������Ŀָ�����ͨѶ����ʧ�ܣ�")*/
extern CString g_sLangID_Native_SaveProjInstrFailCommCmd;
extern CString g_sLangTxt_Native_SaveProjInstrFailCommCmd;
/*_T("��ǰѡ�е���Ŀ�������ڣ�������ѡ����Ŀ����в���")*/
extern CString g_sLangID_Native_SelProjNotExistRetryTest;
extern CString g_sLangTxt_Native_SelProjNotExistRetryTest;
/*_T("�ù����ݲ�֧�֡���")*/
extern CString g_sLangID_Native_NotSupportFeature;
extern CString g_sLangTxt_Native_NotSupportFeature;
//�����:����
extern CString g_sLangID_Native_AddSubitem;
extern CString g_sLangTxt_Native_AddSubitem;
//�����:��֮ǰ
extern CString g_sLangID_Native_AddBeforeItem;
extern CString g_sLangTxt_Native_AddBeforeItem;
//�����:��֮��
extern CString g_sLangID_Native_AddAfterItem;
extern CString g_sLangTxt_Native_AddAfterItem;
/*_T("��Ŀ���")*/
extern CString g_sLangID_Native_ProjResults;
extern CString g_sLangTxt_Native_ProjResults;
/*_T("ȫ����������")*/
extern CString g_sLangID_Native_AllRptData;
extern CString g_sLangTxt_Native_AllRptData;
/*_T("��������-���ݼ�")*/
extern CString g_sLangID_Native_RptDataDataset;
extern CString g_sLangTxt_Native_RptDataDataset;
/*_T("���Խ���")*/
extern CString g_sLangID_Native_TestConcl;
extern CString g_sLangTxt_Native_TestConcl;
/*_T("�鿴����")*/
extern CString g_sLangID_Native_ViewRpt;
extern CString g_sLangTxt_Native_ViewRpt;
/*_T("�β���")*/
extern CString g_sLangID_Native_TestRun;
extern CString g_sLangTxt_Native_TestRun;
/*_T("�μ�����")*/
extern CString g_sLangID_Native_CalcResult;
extern CString g_sLangTxt_Native_CalcResult;
//�쳣����
extern CString g_sLangID_Native_AbnCurr;
extern CString g_sLangTxt_Native_AbnCurr;
extern CString g_sLangID_Adjustment_Time;
extern CString g_sLangTxt_Adjustment_Time;//��������ʱ��

extern CString g_sLangID_Native_GroundDisTimeI;
extern CString g_sLangTxt_Native_GroundDisTimeI;
extern CString g_sLangID_Native_GroundDisTimeII;
extern CString g_sLangTxt_Native_GroundDisTimeII;
extern CString g_sLangID_Native_GroundDisTimeIII;
extern CString g_sLangTxt_Native_GroundDisTimeIII;
extern CString g_sLangID_Native_GroundDisTimeIV;
extern CString g_sLangTxt_Native_GroundDisTimeIV;
extern CString g_sLangID_Native_GroundDisTimeV;
extern CString g_sLangTxt_Native_GroundDisTimeV;//�ӵؾ���ʱ�䣨1-5�Σ�
extern CString g_sLangID_Native_harmonicOrder;
extern CString g_sLangTxt_Native_harmonicOrder;  // г������
extern CString g_sLangID_Native_harmRepresent;
extern CString g_sLangTxt_Native_harmRepresent;// г����ʾ��ʽ
//��ʶ
extern CString g_sLangID_Native_Identifier;
extern CString g_sLangTxt_Native_Identifier;

//����������
extern CString g_sLangID_Native_InputSet;
extern CString g_sLangTxt_Native_InputSet;
//�쳣����
extern CString g_sLangID_Native_AbnData;
extern CString g_sLangTxt_Native_AbnData;
//�����߼�
extern CString g_sLangID_Native_InLogic;
extern CString g_sLangTxt_Native_InLogic;
/*QObject::tr("�ٶϵ���")*/
extern CString g_sLangID_Native_InstCurr;
extern CString g_sLangTxt_Native_InstCurr;
//�쳣������
extern CString g_sLangID_Native_AbnPointSet;
extern CString g_sLangTxt_Native_AbnPointSet;
//�Ƿ�ֱ��
extern CString g_sLangID_Native_IsDC;
extern CString g_sLangTxt_Native_IsDC;
//��������
extern CString g_sLangID_Native_JitterTest;
extern CString g_sLangTxt_Native_JitterTest;
//����ֵ  
extern CString g_sLangID_Native_JitterVal;
extern CString g_sLangTxt_Native_JitterVal;
//�쳣��ѹ
extern CString g_sLangID_Native_AbnVolt;
extern CString g_sLangTxt_Native_AbnVolt;
//����ֵ
extern CString g_sLangID_Native_JumpVal;
extern CString g_sLangTxt_Native_JumpVal;
extern CString g_sLangID_Native_actionSetting;
extern CString g_sLangTxt_Native_actionSetting; // ������ֵ
//������ʱ��
extern CString g_sLangID_Native_MaxTimeMalf;
extern CString g_sLangTxt_Native_MaxTimeMalf;
//�޸�ȫ��ͨ��ֵ
extern CString g_sLangID_Native_ModAllChan;
extern CString g_sLangTxt_Native_ModAllChan;
//����ѡ��
extern CString g_sLangID_Native_MsgSel;
extern CString g_sLangTxt_Native_MsgSel;
//B���߼�
extern CString g_sLangID_Native_BCodeLogic;
extern CString g_sLangTxt_Native_BCodeLogic;
//��������
extern CString g_sLangID_Native_MsgSet;
extern CString g_sLangTxt_Native_MsgSet;
//����
extern CString g_sLangID_Native_Multiple;
extern CString g_sLangTxt_Native_Multiple;
/*tr("����ǰ��ѹ")*/
extern CString g_sLangID_Native_PreFaultVolt;
extern CString g_sLangTxt_Native_PreFaultVolt;
/*tr("����ǰ����")*/
extern CString g_sLangID_Native_PreFaultCurr;
extern CString g_sLangTxt_Native_PreFaultCurr;
extern CString g_sLangID_Native_PhSetActValue;
extern CString g_sLangTxt_Native_PhSetActValue;//��λ��������ֵ
/*tr("�߽��1")*/
extern CString g_sLangID_Native_BoundAngle1;
extern CString g_sLangTxt_Native_BoundAngle1;
/*tr("�߽��2")*/
extern CString g_sLangID_Native_BoundAngle2;
extern CString g_sLangTxt_Native_BoundAngle2;
//��
extern CString g_sLangID_Native_Number;
extern CString g_sLangTxt_Native_Number;
//ͨ��ѡ��
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
extern CString g_sLangTxt_Native_PhaseDisSetV;//�����붨ֵ��1-5�Σ�
extern CString g_sLangID_Native_PhaseDisTimeI;
extern CString g_sLangTxt_Native_PhaseDisTimeI;
extern CString g_sLangID_Native_PhaseDisTimeII;
extern CString g_sLangTxt_Native_PhaseDisTimeII;
extern CString g_sLangID_Native_PhaseDisTimeIII;
extern CString g_sLangTxt_Native_PhaseDisTimeIII;
extern CString g_sLangID_Native_PhaseDisTimeIV;
extern CString g_sLangTxt_Native_PhaseDisTimeIV;
extern CString g_sLangID_Native_PhaseDisTimeV;
extern CString g_sLangTxt_Native_PhaseDisTimeV;//������ʱ�䣨1-5�Σ�

// �ӵؾ��� ���趨ֵ��1-5�Σ�
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

// �ӵؾ���翹 ��1-5�Σ�
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

// ������ ���趨ֵ��1-5�Σ�
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

// ������翹 ��1-5�Σ�
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

//ȷ��
extern CString g_sLangID_Native_Confm;
extern CString g_sLangTxt_Native_Confm;
//��������
extern CString g_sLangID_Native_NatureMalf;
extern CString g_sLangTxt_Native_NatureMalf;
//���ʱ��
extern CString g_sLangID_Native_OutTime;
extern CString g_sLangTxt_Native_OutTime;
extern CString g_sLangID_Native_CurSetActValue;
extern CString g_sLangTxt_Native_CurSetActValue;//������������ֵ
//����������ʱ��
extern CString g_sLangID_Native_OutHoldTime;
extern CString g_sLangTxt_Native_OutHoldTime;
//�����ʶ   0x
extern CString g_sLangID_Native_NetID;
extern CString g_sLangTxt_Native_NetID;
extern CString g_sLangID_Native_networkId;
extern CString g_sLangTxt_Native_networkId; //�����ʶ
//��ʱƫ��
extern CString g_sLangID_Native_DelayDev;
extern CString g_sLangTxt_Native_DelayDev;
//��̬ʱ��
extern CString g_sLangID_Native_NormTime;
extern CString g_sLangTxt_Native_NormTime;
extern CString g_sLangID_Native_oneToMany;
extern CString g_sLangTxt_Native_oneToMany; //һ�����ƿ��Ӧ�������
//��ʱʱ��
extern CString g_sLangID_Native_DelayTime;
extern CString g_sLangTxt_Native_DelayTime;
//����ʱ�䶨ֵ
extern CString g_sLangID_Native_OpTimeSet;
extern CString g_sLangTxt_Native_OpTimeSet;
//ԭʼ��������
extern CString g_sLangID_Native_OrigMsgSet;
extern CString g_sLangTxt_Native_OrigMsgSet;
//��ʱ�仯
extern CString g_sLangID_Native_DelayVar;
extern CString g_sLangTxt_Native_DelayVar;
//��������ʱ��
extern CString g_sLangID_Native_OutputHoldTimeS;
extern CString g_sLangTxt_Native_OutputHoldTimeS;
extern CString g_sLangID_Native_outputTimeLimit;
extern CString g_sLangTxt_Native_outputTimeLimit;  // �����ʱ(s)
/*"�����ɵ���ͨ��"*/
extern CString g_sLangID_Native_OverloadCurrChannel;
extern CString g_sLangTxt_Native_OverloadCurrChannel;
extern CString g_sLangID_Native_delegate;
extern CString g_sLangTxt_Native_delegate; //ί��
extern CString g_sLangID_Native_phaseDifference;
extern CString g_sLangTxt_Native_phaseDifference; //���
extern CString g_sLangID_Native_PreFaultTime;
extern CString g_sLangTxt_Native_PreFaultTime;  // ����ǰʱ��(s)
//Ŀ��MAC
extern CString g_sLangID_Native_DestMAC;
extern CString g_sLangTxt_Native_DestMAC;
/*_T("��ֵ������ʽ")*/
extern CString g_sLangID_Native_DevSetMethod;
extern CString g_sLangTxt_Native_DevSetMethod;
//ƫ��ʱ��
extern CString g_sLangID_Native_DevTime;
extern CString g_sLangTxt_Native_DevTime;
//ƫ��ֵ
extern CString g_sLangID_Native_DevVal;
extern CString g_sLangTxt_Native_DevVal;
/*"��ٶ�"*/
extern CString g_sLangID_Native_DiffSpdBrk;
extern CString g_sLangTxt_Native_DiffSpdBrk;
//�������������ʱ��
extern CString g_sLangID_Native_DurProtTrip;
extern CString g_sLangTxt_Native_DurProtTrip;

/*tr("����ʱ��(S)")*/
extern CString g_sLangID_Native_PreFautTime;
extern CString g_sLangTxt_Native_PreFautTime;
/*"��Ŀ����"*/
extern CString g_sLangID_Native_ProjName;
extern CString g_sLangTxt_Native_ProjName;
//Ʒ���쳣
extern CString g_sLangID_Native_QltyExcp;
extern CString g_sLangTxt_Native_QltyExcp;
extern CString g_sLangID_Native_quote;
extern CString g_sLangTxt_Native_quote; //����
extern CString g_sLangID_Native_RatioBrakeCoefficient;
extern CString g_sLangTxt_Native_RatioBrakeCoefficient;  // �����ƶ�ϵ��
extern CString g_sLangID_Native_receive;
extern CString g_sLangTxt_Native_receive; //����
//����ʱ��
extern CString g_sLangID_Native_ReturnTime;
extern CString g_sLangTxt_Native_ReturnTime;
//����ֵ
extern CString g_sLangID_Native_ReturnValue;
extern CString g_sLangTxt_Native_ReturnValue;
//������ʱ
extern CString g_sLangID_Native_SampDelay;
extern CString g_sLangTxt_Native_SampDelay;
//������
extern CString g_sLangID_Native_SamplingFrequency;
extern CString g_sLangTxt_Native_SamplingFrequency;
extern CString g_sLangID_Native_saveFailed;
extern CString g_sLangTxt_Native_saveFailed; //����ʧ�ܣ�\n
//���ƫ��
extern CString g_sLangID_Native_SeqDev;
extern CString g_sLangTxt_Native_SeqDev;
extern CString g_sLangID_Native_SetActVolt;
extern CString g_sLangTxt_Native_SetActVolt;
//������������
extern CString g_sLangID_Native_SetPickCurr;
extern CString g_sLangTxt_Native_SetPickCurr;
//��λ����
extern CString g_sLangID_Native_ShiftCount;
extern CString g_sLangTxt_Native_ShiftCount;
//��·��ѹ
extern CString g_sLangID_Native_ShortCircuitV;
extern CString g_sLangTxt_Native_ShortCircuitV;
//��·�迹��
extern CString g_sLangID_Native_ShortZImpAng;
extern CString g_sLangTxt_Native_ShortZImpAng;
/*��·�迹*/
extern CString g_sLangID_Native_ShortZImp;
extern CString g_sLangTxt_Native_ShortZImp;
extern CString g_sLangID_Native_smvReceive;
extern CString g_sLangTxt_Native_smvReceive; //SMV ����
//�����ܲ���
extern CString g_sLangID_Native_SndFreq;
extern CString g_sLangTxt_Native_SndFreq;
//ÿ�뷢���ܲ���
extern CString g_sLangID_Native_SndFreqPS;
extern CString g_sLangTxt_Native_SndFreqPS;
//����ʱ��(s)
extern CString g_sLangID_Native_SndTimeS;
extern CString g_sLangTxt_Native_SndTimeS;
//ԴMAC
extern CString g_sLangID_Native_SrcMAC;
extern CString g_sLangTxt_Native_SrcMAC;
//״̬%d
extern CString g_sLangID_Native_StateD;
extern CString g_sLangTxt_Native_StateD;
extern CString g_sLangID_Native_subscriptionDescription;
extern CString g_sLangTxt_Native_subscriptionDescription; //��������
extern CString g_sLangID_Native_subscriptionIndex;
extern CString g_sLangTxt_Native_subscriptionIndex; //��������
extern CString g_sLangID_Native_subscriptionReference;
extern CString g_sLangTxt_Native_subscriptionReference; //��������
extern CString g_sLangID_Native_superimpose_ornot;
extern CString g_sLangTxt_Native_superimpose_ornot;  // �Ƿ���ӷ����ڷ���:
//SVԭʼ����
extern CString g_sLangID_Native_SVOrigMsg;
extern CString g_sLangTxt_Native_SVOrigMsg;
//������
extern CString g_sLangID_Native_SwitchVal;
extern CString g_sLangTxt_Native_SwitchVal;
extern CString g_sLangID_Native_test_process;
extern CString g_sLangTxt_Native_test_process;  // �������:
//���Ծ���
extern CString g_sLangID_Native_TestPrecision;
extern CString g_sLangTxt_Native_TestPrecision;
//��ѹ��������ʽ
extern CString g_sLangID_Native_TransConnForm;
extern CString g_sLangTxt_Native_TransConnForm;
//�Ƿ�ת���Թ���
extern CString g_sLangID_Native_TransientFault;
extern CString g_sLangTxt_Native_TransientFault;
//�����󱣳�ʱ��
extern CString g_sLangID_Native_TrigHoldTime;
extern CString g_sLangTxt_Native_TrigHoldTime;
//������ʽ
extern CString g_sLangID_Native_TrigMode;
extern CString g_sLangTxt_Native_TrigMode;
//��Ч[bit0-1]
extern CString g_sLangID_Native_ValidBit;
extern CString g_sLangTxt_Native_ValidBit;
extern CString g_sLangID_Native_VolSetActValue;
extern CString g_sLangTxt_Native_VolSetActValue;//��ѹ��������ֵ
extern CString g_sLangID_Native_vTerminalConnectDia;
extern CString g_sLangTxt_Native_vTerminalConnectDia; //���������ͼ
extern CString g_sLangID_Native_YNInputStop;
extern CString g_sLangTxt_Native_YNInputStop;  // �Ƿ���ֹͣ
extern CString g_sLangID_Out1_Situation; 
extern CString g_sLangTxt_Out1_Situation;//����1״̬
extern CString g_sLangID_Out2_Situation;
extern CString g_sLangTxt_Out2_Situation;//����2״̬
extern CString g_sLangID_Out3_Situation;
extern CString g_sLangTxt_Out3_Situation;//����3״̬
extern CString g_sLangID_without;
extern CString g_sLangTxt_without;//��
extern CString g_sLangID_Native_error;
extern CString g_sLangTxt_Native_error; //����
//��ѹ����
extern CString g_sLangID_Native_VoltSlip;
extern CString g_sLangTxt_Native_VoltSlip;
//�������
extern CString g_sLangID_Native_ErrSeqTest;
extern CString g_sLangTxt_Native_ErrSeqTest;
//����
extern CString g_sLangID_Native_Fault;
extern CString g_sLangTxt_Native_Fault;
//����ͨ��
extern CString g_sLangID_Native_FaultChnl;
extern CString g_sLangTxt_Native_FaultChnl;
/*���ϵ���*/
extern CString g_sLangID_Native_FaultCurrValue;
extern CString g_sLangTxt_Native_FaultCurrValue;
//���ϴ�����ʽ
extern CString g_sLangID_Native_FaultTrigMethod;
extern CString g_sLangTxt_Native_FaultTrigMethod;
//���ϵ�ѹ����
extern CString g_sLangID_Native_FaultVoltDef;
extern CString g_sLangTxt_Native_FaultVoltDef;
//�ļ�����
//extern CString g_sLangID_Native_FileName;
//extern CString g_sLangTxt_Native_FileName;
//��תʱ��
extern CString g_sLangID_Native_FlipMoment;
extern CString g_sLangTxt_Native_FlipMoment;
//��֡����
extern CString g_sLangID_Native_FrameDrop;
extern CString g_sLangTxt_Native_FrameDrop;
//�ɵ����
extern CString g_sLangID_Native_FlyDot;
extern CString g_sLangTxt_Native_FlyDot;
extern CString g_sLangID_Native_FreqSetActValue;
extern CString g_sLangTxt_Native_FreqSetActValue;//Ƶ����������ֵ
extern CString g_sLangID_Native_fundamentalFreq;
extern CString g_sLangTxt_Native_fundamentalFreq;  // ����Ƶ��
extern CString g_sLangID_Native_fundamentalAmp;
extern CString g_sLangTxt_Native_fundamentalAmp;  // ������ֵ
extern CString g_sLangID_Native_fundamentalPhase;
extern CString g_sLangTxt_Native_fundamentalPhase;  // ������λ
extern CString g_sLangID_Native_GOOSEOrigMsg;
extern CString g_sLangTxt_Native_GOOSEOrigMsg; //GOOSEԭʼ����
extern CString g_sLangID_Native_gooseReceive;
extern CString g_sLangTxt_Native_gooseReceive; //GOOSE ����
//GPS����ʱ�̣�ʱ��
extern CString g_sLangID_Native_GPSTriggerHour;
extern CString g_sLangTxt_Native_GPSTriggerHour;
//GPS����ʱ�̣��֣�
extern CString g_sLangID_Native_GPSTriggerMinute;
extern CString g_sLangTxt_Native_GPSTriggerMinute;
//GPS����ʱ�̣��룩
extern CString g_sLangID_Native_GPSTriggerSecond;
extern CString g_sLangTxt_Native_GPSTriggerSecond;
//�ݱ�ʱ��ֶ�(ms)
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
// ��·��ѹ(V)��
extern CString g_sLangID_Native_ShortCircuitVs;
extern CString g_sLangTxt_Native_ShortCircuitVs;

//��ѹ�仯��ֵ
extern CString g_sLangID_Native_FinalVoltChange;
extern CString g_sLangTxt_Native_FinalVoltChange;
extern CString g_sLangID_Allow_FreqDifference;
extern CString g_sLangTxt_Allow_FreqDifference;//����Ƶ��
extern CString g_sLangID_LeadingAngle;
extern CString g_sLangTxt_LeadingAngle;//��ǰ��

extern CString g_sLangID_Vol_ReguPeriod;
extern CString g_sLangTxt_Vol_ReguPeriod;//��ѹ����
extern CString g_sLangID_Freq_ReguPeriod;
extern CString g_sLangTxt_Freq_ReguPeriod;//��Ƶ����
extern CString g_sLangID_LeadingTime;
extern CString g_sLangTxt_LeadingTime;//��ǰʱ��
extern CString g_sLangID_Allow_VolDifference;
extern CString g_sLangTxt_Allow_VolDifference;//����ѹ��

extern CString g_sLangID_System_Rated_Voltage;
extern CString g_sLangTxt_System_Rated_Voltage;//ϵͳ����ѹ
extern CString g_sLangID_System_Rated_Frequency;
extern CString g_sLangTxt_System_Rated_Frequency;//ϵͳ��Ƶ��
extern CString g_sLangID_Grid_Rated_Voltage;
extern CString g_sLangTxt_Grid_Rated_Voltage;//��������ѹ

extern CString g_sLangID_Freq_BoundValue;
extern CString g_sLangTxt_Freq_BoundValue;//Ƶ�ʱ߽�ֵ
extern CString g_sLangID_FreqDif;
extern CString g_sLangTxt_FreqDif;//Ƶ��

extern CString g_sLangID_Grid_FreqHZ;
extern CString g_sLangTxt_Grid_FreqHZ;//������Ƶ�ʣ�HZ��

//��ѹ�仯ʼֵ
extern CString g_sLangID_Native_InitVoltChange;
extern CString g_sLangTxt_Native_InitVoltChange;
/*_T("��ѹ����ֵ")*/
extern CString g_sLangID_Native_LowVLockVal;
extern CString g_sLangTxt_Native_LowVLockVal;
extern CString g_sLangID_Native_maxSyncTime;
extern CString g_sLangTxt_Native_maxSyncTime;   // ���ͬ��ʱ��:
//��ѹ���ض���ֵ
extern CString g_sLangID_Native_LowVoltUnderloadTripSet;
extern CString g_sLangTxt_Native_LowVoltUnderloadTripSet;
//��ѹ�仯����
extern CString g_sLangID_Native_VoltChangeStep;
extern CString g_sLangTxt_Native_VoltChangeStep;
extern CString g_sLangID_Out4_Mode;
extern CString g_sLangTxt_Out4_Mode;//����4�����ʽ
extern CString g_sLangID_Vol_BoundValue;
extern CString g_sLangTxt_Vol_BoundValue;//��ѹ�߽�ֵ
/*QString::tr("��ѹ�����ֵ")*/	
extern CString g_sLangID_Native_VoltSlipAct;
extern CString g_sLangTxt_Native_VoltSlipAct;
/*_T("������ѹ����")*/	
extern CString g_sLangID_Native_LockVoltDef;
extern CString g_sLangTxt_Native_LockVoltDef;
extern CString g_sLangID_VolDif;
extern CString g_sLangTxt_VolDif;//ѹ��

/*_T("��ѹ�仯�ʱ���ֵ")*/
extern CString g_sLangID_Native_LowVRateLock;
extern CString g_sLangTxt_Native_LowVRateLock;

/*QString::tr("��ѹ���ض���ֵ")*/
extern CString g_sLangID_Native_LVLRActionVal;
extern CString g_sLangTxt_Native_LVLRActionVal;

//��������:
extern CString g_sLangID_Native_FaultProp;
extern CString g_sLangTxt_Native_FaultProp;
/*tr("��������֮��ǲ�(�ӵ���)")*/
extern CString g_sLangID_Native_AngleDiffClockHrsTestWindings;
extern CString g_sLangTxt_Native_AngleDiffClockHrsTestWindings;
//��  ��  ��  ��
extern CString g_sLangID_Native_ControlCurrent;
extern CString g_sLangTxt_Native_ControlCurrent;

/*_T("������б��")*/
extern CString g_sLangID_Native_StartSegSlope;
extern CString g_sLangTxt_Native_StartSegSlope;
/*_T("���������ƶ�����б��1")*/
extern CString g_sLangID_Native_FundRatioBrkSlope1;
extern CString g_sLangTxt_Native_FundRatioBrkSlope1;
/*_T("���������ƶ�����б��2")*/
extern CString g_sLangID_Native_FundRatioBrkSlope2;
extern CString g_sLangTxt_Native_FundRatioBrkSlope2;
/*_T("���������ƶ�����б��3")*/
extern CString g_sLangID_Native_FundRatioBrkSlope3;
extern CString g_sLangTxt_Native_FundRatioBrkSlope3;
/*_T("����г���ƶ�ϵ��")*/
extern CString g_sLangID_Native_SecHarBrkCoef;
extern CString g_sLangTxt_Native_SecHarBrkCoef;
/*_T("����г���ƶ�ϵ��")*/
extern CString g_sLangID_Native_ThiHarBrkCoef;
extern CString g_sLangTxt_Native_ThiHarBrkCoef;
/*_T("���г���ƶ�ϵ��")*/
extern CString g_sLangID_Native_FivHarBrkCoef;
extern CString g_sLangTxt_Native_FivHarBrkCoef;
//��������
extern CString g_sLangID_Native_SearchMeth;
extern CString g_sLangTxt_Native_SearchMeth;

/*tr("��ѹ����ѹ(kV)")*/
extern CString g_sLangID_Native_HighVoltSideRatedVolt;
extern CString g_sLangTxt_Native_HighVoltSideRatedVolt;
/*tr("��ѹ����ѹ(kV)")*/
extern CString g_sLangID_Native_MedVoltSideRatedVolt;
extern CString g_sLangTxt_Native_MedVoltSideRatedVolt;

/*tr("��ѹ�����������ʽ")*/
extern CString g_sLangID_Native_MedVoltWindingConnType;
extern CString g_sLangTxt_Native_MedVoltWindingConnType;
/*tr("��ѹ����ѹ(kV)")*/
extern CString g_sLangID_Native_LowVoltSideRatedVolt;
extern CString g_sLangTxt_Native_LowVoltSideRatedVolt;
/*"��ѹ��CTһ��ֵ(A)"*/
extern CString g_sLangID_Native_HVSideCTPrimVal;
extern CString g_sLangTxt_Native_HVSideCTPrimVal;
/*"��ѹ��CT����ֵ(A)"*/
extern CString g_sLangID_Native_HVSide2CTPrimVal;
extern CString g_sLangTxt_Native_HVSide2CTPrimVal;
/*"��ѹ��CTһ��ֵ(A)"*/
extern CString g_sLangID_Native_MVSideCTPrimVal;
extern CString g_sLangTxt_Native_MVSideCTPrimVal;
/*"��ѹ��CT����ֵ(A)"*/
extern CString g_sLangID_Native_MVSide2CTPrimVal;
extern CString g_sLangTxt_Native_MVSide2CTPrimVal;
/*"��ѹ��CTһ��ֵ(A)"*/
extern CString g_sLangID_Native_LVSideCTPrimVal;
extern CString g_sLangTxt_Native_LVSideCTPrimVal;
/*"��ѹ��CT����ֵ(A)"*/
extern CString g_sLangID_Native_LVSide2CTPrimVal;
extern CString g_sLangTxt_Native_LVSide2CTPrimVal;
/*_T("��׼����ѡ��")*/
extern CString g_sLangID_Native_RefCurrentSel;
extern CString g_sLangTxt_Native_RefCurrentSel;
//�����ƶ�ϵ��  
extern CString g_sLangID_Native_ProportionalBrakingFactor;
extern CString g_sLangTxt_Native_ProportionalBrakingFactor;
/*tr("��ѹ�������(MVA)")*/
extern CString g_sLangID_Native_TransfRatedCapacity;
extern CString g_sLangTxt_Native_TransfRatedCapacity;
extern CString g_sLangID_interlock_vol;
extern CString g_sLangTxt_interlock_vol;//������ѹ
extern CString g_sLangID_interlock_cur;
extern CString g_sLangTxt_interlock_cur;//��������
extern CString g_sLangID_lowfreqloadre_ActTime;
extern CString g_sLangTxt_lowfreqloadre_ActTime;//���ܼ��ض���ʱ��

//��ѹ�仯��
extern CString g_sLangID_Native_VoltChangeAmt;
extern CString g_sLangTxt_Native_VoltChangeAmt;
extern CString g_sLangID_Native_sliptripValue;
extern CString g_sLangTxt_Native_sliptripValue;//�������ֵ
//�����źŽӵ�
extern CString g_sLangID_Native_AccelSignalCont;
extern CString g_sLangTxt_Native_AccelSignalCont;
//�����źŽӵ�
extern CString g_sLangID_Native_DecelSignalCont;
extern CString g_sLangTxt_Native_DecelSignalCont;
//��ǰʱ��
extern CString g_sLangID_Native_PreOscTime;
extern CString g_sLangTxt_Native_PreOscTime;
//ϵͳ���迹
extern CString g_sLangID_Native_SysImp;
extern CString g_sLangTxt_Native_SysImp;
//��ѹ���迹
extern CString g_sLangID_Native_TransImp;
extern CString g_sLangTxt_Native_TransImp;

/*_T("�񵴴���")*/
extern CString g_sLangID_Native_OscilCount;
extern CString g_sLangTxt_Native_OscilCount;
//�Ƕȶ���
extern CString g_sLangID_Native_AngDef;
extern CString g_sLangTxt_Native_AngDef;
//���߷�ʽ
extern CString g_sLangID_Native_ConnMethod;
extern CString g_sLangTxt_Native_ConnMethod;
//��������
extern CString g_sLangID_Native_ActDirection;
extern CString g_sLangTxt_Native_ActDirection;

//�͵�ѹ����
extern CString g_sLangID_Native_LowVoltageDef;
extern CString g_sLangTxt_Native_LowVoltageDef;
/*_T("��ǰ�Ƕ�")*/
extern CString g_sLangID_Native_LeadAngle;
extern CString g_sLangTxt_Native_LeadAngle;
/*_T("�ͺ�Ƕ�")*/
extern CString g_sLangID_Native_LagAngle;
extern CString g_sLangTxt_Native_LagAngle;
//����ϵ��
extern CString g_sLangID_Native_CalcCoef;
extern CString g_sLangTxt_Native_CalcCoef;
/*_T("��Ƶ�仯���迹��ֵ")*/
extern CString g_sLangID_Native_FreqChgZSetting;
extern CString g_sLangTxt_Native_FreqChgZSetting;
/*_T("����������")*/
extern CString g_sLangID_Native_PosSeqSensAng;
extern CString g_sLangTxt_Native_PosSeqSensAng;
/*_T("�ӵؾ���ƫ�ƽ�")*/
extern CString g_sLangID_Native_GndDistOffset;
extern CString g_sLangTxt_Native_GndDistOffset;
/*_T("������ƫ�ƽ�")*/
extern CString g_sLangID_Native_PhaseDistOffset;
extern CString g_sLangTxt_Native_PhaseDistOffset;
//ƽ��ϵ��
extern CString g_sLangID_Native_BalCoeff;
extern CString g_sLangTxt_Native_BalCoeff;
/*QObject::tr("2��г���ƶ�ϵ��")*/
extern CString g_sLangID_Native_2HarBrkCoef;
extern CString g_sLangTxt_Native_2HarBrkCoef;
/*QObject::tr("3��г���ƶ�ϵ��")*/
extern CString g_sLangID_Native_3HarBrkCoef;
extern CString g_sLangTxt_Native_3HarBrkCoef;
/*QObject::tr("5��г���ƶ�ϵ��")*/
extern CString g_sLangID_Native_5HarBrkCoef;
extern CString g_sLangTxt_Native_5HarBrkCoef;

//�뵱ǰ�����ǽ�������ʧ��(%s).
extern CString g_sLangID_Native_ConnectFail;
extern CString g_sLangTxt_Native_ConnectFail;

//�����������жϣ�����������ǽ������ӡ�
extern CString g_sLangID_Native_TestrDisconn;
extern CString g_sLangTxt_Native_TestrDisconn;

// ��ص�����Ϣ��ȡ�쳣.
extern CString g_sLangID_Native_UnBatteryInfor;
extern CString g_sLangTxt_Native_UnBatteryInfor;  

//���ڼ��ز��Թ��ܽ��棬���Ժ�
extern CString g_sLangID_Native_LoadingMacroTest;
extern CString g_sLangTxt_Native_LoadingMacroTest;
//���ܼ��ؽ�����
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
//"1��(0.3��/10A)" lcq
extern CString g_sLangID_Currentlevel1;
extern CString g_sLangTxt_Currentlevel1;
//"2��(0.7��/10A)" lcq
extern CString g_sLangID_Currentlevel2;
extern CString g_sLangTxt_Currentlevel2;
//"3��(1.5��/10A)" lcq
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
extern CString g_sLangTxt_Impedance_ShortVol;		         //_T("��·��ѹ��V��"); 
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
extern CString g_sLangTxt_Impedance_FunParas;			 //=_T("���ܲ���");
extern CString g_sLangID_Impedance_Variable;			 //=_T("Impedance_Variable");
extern CString g_sLangTxt_Impedance_Variable;			 //=_T("�ݱ�");
extern CString g_sLangID_Impedance_ChangeStart;			 //=_T("Impedance_ChangeStart");
extern CString g_sLangTxt_Impedance_ChangeStart;			 //=_T("�仯ʼֵ(��)");
extern CString g_sLangID_Impedance_ChangeEnd;			 //=_T("Impedance_ChangeEnd");
extern CString g_sLangTxt_Impedance_ChangeEnd;			 //=_T("�仯��ֵ(��)");
extern CString g_sLangID_Impedance_ChangStep;			 //=_T("Impedance_ChangStep");
extern CString g_sLangTxt_Impedance_ChangStep;			 //=_T("�仯����(��)");
extern CString g_sLangID_Impedance_NormalTime;			 //=_T("Impedance_NormalTime");
extern CString g_sLangTxt_Impedance_NormalTime;			 //=_T("��̬ʱ��(s)");
extern CString g_sLangID_Impedance_FailTime;			 //=_T("Impedance_FailTime");
extern CString g_sLangTxt_Impedance_FailTime;			 //=_T("����ǰʱ��(s)");


extern CString g_sLangID_Impedance_ConstantCur;			 //=_T("Impedance_ConstantCur");
extern CString g_sLangTxt_Impedance_ConstantCur;			 //=_T("������");
extern CString g_sLangID_Impedance_ConstantVol;			 //=_T("Impedance_ConstantVol");
extern CString g_sLangTxt_Impedance_ConstantVol;			 //=_T("����ѹ");
extern CString g_sLangID_Impedance_FixedSystem;			 //=_T("Impedance_FixedSystem");
extern CString g_sLangTxt_Impedance_FixedSystem;			 //=_T("�̶�ϵͳ���迹");

extern CString g_sLangID_Gradient_FailModes;			 //=_T("Gradient_FailModes");
extern CString g_sLangTxt_Gradient_FailModes;			 //=_T("����ģʽ");
extern CString g_sLangID_Gradient_Change;			 //=_T("Gradient_Change");
extern CString g_sLangTxt_Gradient_Change;			 //=_T("�仯��");
extern CString g_sLangID_Gradient_ImpAngle;			 //=_T("Gradient_ImpAngle");
extern CString g_sLangTxt_Gradient_ImpAngle;			 //=_T("�迹��(��):");
extern CString g_sLangID_Gradient_ChangeTime;			 //=_T("Gradient_ChangeTime");
extern CString g_sLangTxt_Gradient_ChangeTime;			 //=_T("�仯ǰʱ��(s):");
extern CString g_sLangID_Gradient_FailBeforeTime;			 //=_T("Gradient_FailBeforeTime");
extern CString g_sLangTxt_Gradient_FailBeforeTime;			 //=_T("����ǰʱ��(s):");
extern CString g_sLangID_Gradient_FailVol;			 //=_T("Gradient_FailVol");
extern CString g_sLangTxt_Gradient_FailVol;			 //=_T("����ǰ��ѹ(V):");
extern CString g_sLangID_Gradient_FailCur;			 //=_T("Gradient_FailCur");
extern CString g_sLangTxt_Gradient_FailCur;			 //=_T("����ǰ����(A):");
extern CString g_sLangID_Gradient_FailAngle;			 //=_T("Gradient_FailAngle");
extern CString g_sLangTxt_Gradient_FailAngle;			 //=_T("����ǰ���(��):");
extern CString g_sLangID_Gradient_RampParas;			 //=_T("Gradient_RampParas");
extern CString g_sLangTxt_Gradient_RampParas;			 //=_T("�ݱ��������");
//extern CString g_sLangID_Gradient_VarSet;			 //=_T("Gradient_VarSet");
//extern CString g_sLangTxt_Gradient_VarSet;			 //=_T("��������");
extern CString g_sLangID_Gradient_CommonParas;			 //=_T("Gradient_CommonParas");
extern CString g_sLangTxt_Gradient_CommonParas;			 //=_T("ͨ�ò���");
//extern CString g_sLangID_Gradient_BinBout;			 //=_T("Gradient_BinBout");
//extern CString g_sLangTxt_Gradient_BinBout;			 //=_T("������");
extern CString g_sLangID_Gradient_BoutNormal;			 //=_T("Gradient_BoutNormal");
extern CString g_sLangTxt_Gradient_BoutNormal;			 //=_T("����������̬");
extern CString g_sLangID_Gradient_BoutFaultState;			 //=_T("Gradient_BoutFaultState");
extern CString g_sLangTxt_Gradient_BoutFaultState;			 //=_T("����������̬");


extern CString g_sLangID_Gradient_Test1;			 //=_T("Gradient_Test1");
extern CString g_sLangTxt_Gradient_Test1;			 //=_T("����1");
extern CString g_sLangID_Gradient_Test2;			 //=_T("Gradient_Test2");
extern CString g_sLangTxt_Gradient_Test2;			 //=_T("����2");
extern CString g_sLangID_Gradient_Test3;			 //=_T("Gradient_Test3");
extern CString g_sLangTxt_Gradient_Test3;			 //=_T("����3");
extern CString g_sLangID_Native_PhaseABshort;			 //=_T("Native_PhaseABshort");
extern CString g_sLangTxt_Native_PhaseABshort;			 //=_T("AB���·");
extern CString g_sLangID_Native_PhaseBCshort;			 //=_T("Native_PhaseBCshort");
extern CString g_sLangTxt_Native_PhaseBCshort;			 //=_T("BC���·");
extern CString g_sLangID_Native_PhaseCAshort;			 //=_T("Native_PhaseCAshort");
extern CString g_sLangTxt_Native_PhaseCAshort;			 //=_T("CA���·");
extern CString g_sLangID_Native_PhaseABshortCcur;			 //=_T("Native_PhaseABshortCcur");
extern CString g_sLangTxt_Native_PhaseABshortCcur;			 //=_T("AB���·��C�����");
extern CString g_sLangID_Native_PhaseBCshortAcur;			 //=_T("Native_PhaseBCshortAcur");
extern CString g_sLangTxt_Native_PhaseBCshortAcur;			 //=_T("BC���·��A�����");
extern CString g_sLangID_Native_PhaseCAshortBcur;			 //=_T("Native_PhaseCAshortBcur");
extern CString g_sLangTxt_Native_PhaseCAshortBcur;			 //=_T("CA���·��B�����");
extern CString g_sLangID_Native_PhaseABshortBcur;			 //=_T("Native_PhaseABshortBcur");
extern CString g_sLangTxt_Native_PhaseABshortBcur;			 //=_T("AB���·��B�����");
extern CString g_sLangID_Native_PhaseBCshortCcur;			 //=_T("Native_PhaseBCshortCcur");
extern CString g_sLangTxt_Native_PhaseBCshortCcur;			 //=_T("BC���·��C�����");
extern CString g_sLangID_Native_PhaseCAshortAcur;			 //=_T("Native_PhaseCAshortAcur");
extern CString g_sLangTxt_Native_PhaseCAshortAcur;			 //=_T("CA���·��A�����");
extern CString g_sLangID_Native_PosVol;			 //=_T("Native_PosVol");
extern CString g_sLangTxt_Native_PosVol;			 //=_T("�����ѹ");
extern CString g_sLangID_Native_NegVol;			 //=_T("Native_NegVol");
extern CString g_sLangTxt_Native_NegVol;			 //=_T("�����ѹ");
extern CString g_sLangID_Native_ZeroVol3U0;			 //=_T("Native_ZeroVol3U0");
extern CString g_sLangTxt_Native_ZeroVol3U0;			 //=_T("�����ѹ��3U0��");
extern CString g_sLangID_Native_PosVolU1;			 //=_T("Native_PosVolU1");
extern CString g_sLangTxt_Native_PosVolU1;			 //=_T("����(U1)");
extern CString g_sLangID_Native_NegVolU2;			 //=_T("Native_NegVolU2");
extern CString g_sLangTxt_Native_NegVolU2;			 //=_T("����(U2)");
extern CString g_sLangID_Native_Zero3U0;			 //=_T("Native_Zero3U0");
extern CString g_sLangTxt_Native_Zero3U0;			 //=_T("����(3U0)");

extern CString g_sLangID_CBOperate_TimeAfterTrigger;			 //=_T("CBOperate_TimeAfterTrigger");
extern CString g_sLangTxt_CBOperate_TimeAfterTrigger;			 //=_T("�������������ʱ��(s)");
extern CString g_sLangID_CBOperate_PTVPos;			 //=_T("CBOperate_PTVPos");
extern CString g_sLangTxt_CBOperate_PTVPos;			 //=_T("TV��װλ��");
extern CString g_sLangID_CBOperate_CTPos;			 //=_T("CBOperate_CTPos");
extern CString g_sLangTxt_CBOperate_CTPos;			 //=_T("TA������");
extern CString g_sLangID_CBOperate_AfterOpenTime;			 //=_T("CBOperate_AfterOpenTime");
extern CString g_sLangTxt_CBOperate_AfterOpenTime;			 //=_T("�������������ʱ��(s)");
extern CString g_sLangID_CBOperate_RecloseTime;			 //=_T("CBOperate_RecloseTime");
extern CString g_sLangTxt_CBOperate_RecloseTime;			 //=_T("�غϳ���ʱ��(s)");
extern CString g_sLangID_CBOperate_AfterAccTime;			 //=_T("CBOperate_AfterAccTime");
extern CString g_sLangTxt_CBOperate_AfterAccTime;			 //=_T("����ٿ������������ʱ��(s)");
extern CString g_sLangID_CBOperate_PTPos;			 //=_T("CBOperate_PTPos");
extern CString g_sLangTxt_CBOperate_PTPos;			 //=_T("ĸ�߲�");
extern CString g_sLangID_CBOperate_TPos;			 //=_T("CBOperate_TPos");
extern CString g_sLangTxt_CBOperate_TPos;			 //=_T("��·��");
extern CString g_sLangID_CBOperate_CTPos1;			 //=_T("CBOperate_CTPos1");
extern CString g_sLangTxt_CBOperate_CTPos1;			 //=_T("ָ��ĸ��");
extern CString g_sLangID_CBOperate_TPos1;			 //=_T("CBOperate_TPos1");
extern CString g_sLangTxt_CBOperate_TPos1;			 //=_T("ָ����·");
extern CString g_sLangID_CBOperate_Overall;			 //=_T("CBOperate_Overall");
extern CString g_sLangTxt_CBOperate_Overall;			 //=_T("����");
extern CString g_sLangID_CBOperate_Zs;			 //=_T("CBOperate_Zs");
extern CString g_sLangTxt_CBOperate_Zs;			 //=_T("ϵͳ�迹(��)");
extern CString g_sLangID_CBOperate_ZsPh;			 //=_T("CBOperate_ZsPh");
extern CString g_sLangTxt_CBOperate_ZsPh;			 //=_T("ϵͳ�迹��(��)");
extern CString g_sLangID_CBOperate_SimulateBreakerDelay;			 //=_T("CBOperate_SimulateBreakerDelay");
extern CString g_sLangTxt_CBOperate_SimulateBreakerDelay;			 //=_T("��·��ģ��");
extern CString g_sLangID_CBOperate_BrkBreakTime;			 //=_T("CBOperate_BrkBreakTime");
extern CString g_sLangTxt_CBOperate_BrkBreakTime;			 //=_T("��բʱ��(ms)");
extern CString g_sLangID_CBOperate_BrkCloseTime;			 //=_T("CBOperate_BrkCloseTime");
extern CString g_sLangTxt_CBOperate_BrkCloseTime;			 //=_T("��բʱ��(ms)");
extern CString g_sLangID_CBOperate_FaultIncMode;			 //=_T("CBOperate_FaultIncMode");
extern CString g_sLangTxt_CBOperate_FaultIncMode;			 //=_T("��բ��ѡ��");
extern CString g_sLangID_CBOperate_FaultAngle;			 //=_T("CBOperate_FaultAngle");
extern CString g_sLangTxt_CBOperate_FaultAngle;			 //=_T("��բ��(��)");
extern CString g_sLangID_CBOperate_BIPlusDC;			 //=_T("CBOperate_BIPlusDC");
extern CString g_sLangTxt_CBOperate_BIPlusDC;			 //=_T("���ӷ����ڷ���");
extern CString g_sLangID_CBOperate_VzDefine;			 //=_T("CBOperate_VzDefine");
extern CString g_sLangTxt_CBOperate_VzDefine;			 //=_T("��ȡ��ѹ�������");
extern CString g_sLangID_CBOperate_PsuVzRefPhase;			 //=_T("CBOperate_PsuVzRefPhase");
extern CString g_sLangTxt_CBOperate_PsuVzRefPhase;			 //=_T("��ȡ��ѹ�ο��ඨ��");
extern CString g_sLangID_CBOperate_VzPh;			 //=_T("CBOperate_VzPh");
extern CString g_sLangTxt_CBOperate_VzPh;			 //=_T("��ȡ��ѹ���");
extern CString g_sLangID_CBOperate_NotSimulated;			 //=_T("CBOperate_NotSimulated");
extern CString g_sLangTxt_CBOperate_NotSimulated;			 //=_T("��ģ��");
extern CString g_sLangID_CBOperate_Random;			 //=_T("CBOperate_Random");
extern CString g_sLangTxt_CBOperate_Random;			 //=_T("���");
extern CString g_sLangID_CBOperate_FixedValue;			 //=_T("CBOperate_FixedValue");
extern CString g_sLangTxt_CBOperate_FixedValue;			 //=_T("��ֵ");
extern CString g_sLangID_CBOperate_UabPhase;			 //=_T("CBOperate_UabPhase");
extern CString g_sLangTxt_CBOperate_UabPhase;			 //=_T("Uab��λ");
extern CString g_sLangID_CBOperate_UbcPhase;			 //=_T("CBOperate_UbcPhase");
extern CString g_sLangTxt_CBOperate_UbcPhase;			 //=_T("Ubc��λ");
extern CString g_sLangID_CBOperate_UcaPhase;			 //=_T("CBOperate_UcaPhase");
extern CString g_sLangTxt_CBOperate_UcaPhase;			 //=_T("Uca��λ");
extern CString g_sLangID_CBOperate_SingleHop;			 //=_T("CBOperate_SingleHop");
extern CString g_sLangTxt_CBOperate_SingleHop;			 //=_T("����");
extern CString g_sLangID_CBOperate_TripleJump;			 //=_T("CBOperate_TripleJump");
extern CString g_sLangTxt_CBOperate_TripleJump;			 //=_T("����");
extern CString g_sLangID_CBOperate_Reclose;			 //=_T("CBOperate_Reclose");
extern CString g_sLangTxt_CBOperate_Reclose;			 //=_T("�غ�");
extern CString g_sLangID_CBOperate_BinBoutSelect;			 //=_T("CBOperate_BinBoutSelect");
extern CString g_sLangTxt_CBOperate_BinBoutSelect;			 //=_T("����ѡ��");
extern CString g_sLangID_CBOperate_BinABCD;			 //=_T("CBOperate_BinABCD");
extern CString g_sLangTxt_CBOperate_BinABCD;			 //=_T("����A-B-C-D");
extern CString g_sLangID_CBOperate_BinEFGH;			 //=_T("CBOperate_BinEFGH");
extern CString g_sLangTxt_CBOperate_BinEFGH;			 //=_T("����E-F-G-H");
extern CString g_sLangID_CBOperate_OutputSwitchMode;			 //=_T("CBOperate_OutputSwitchMode");
extern CString g_sLangTxt_CBOperate_OutputSwitchMode;			 //=_T("������ת������ʽ");
extern CString g_sLangID_CBOperate_OutputDelayTime;			 //=_T("CBOperate_OutputDelayTime");
extern CString g_sLangTxt_CBOperate_OutputDelayTime;			 //=_T("������תʱ��");
extern CString g_sLangID_CBOperate_StartTime;			 //=_T("CBOperate_StartTime");
extern CString g_sLangTxt_CBOperate_StartTime;			 //=_T("ʱ������");
extern CString g_sLangID_CBOperate_BinStart;			 //=_T("CBOperate_BinStart");
extern CString g_sLangTxt_CBOperate_BinStart;			 //=_T("����������");
extern CString g_sLangID_CBOperate_AbsOrRelative;			 //=_T("CBOperate_AbsOrRelative");
extern CString g_sLangTxt_CBOperate_AbsOrRelative;			 //=_T("����or���");
extern CString g_sLangID_CBOperate_AbsRelative;			 //=_T("CBOperate_AbsRelative");
extern CString g_sLangTxt_CBOperate_AbsRelative;			 //=_T("����&���");
extern CString g_sLangID_CBOperate_CombError;			 //=_T("CBOperate_CombError");
extern CString g_sLangTxt_CBOperate_CombError;			 //=_T("������");
extern CString g_sLangID_CBOperate_Instan;			 //=_T("CBOperate_Instan");
extern CString g_sLangTxt_CBOperate_Instan;			 //=_T("˲ʱ");
extern CString g_sLangID_CBOperate_Perpetual;			 //=_T("CBOperate_Perpetual");
extern CString g_sLangTxt_CBOperate_Perpetual;			 //=_T("����");
extern CString g_sLangID_CBOperate_MaxFaultTime;			 //=_T("CBOperate_MaxFaultTime");
extern CString g_sLangTxt_CBOperate_MaxFaultTime;			 //=_T("������ʱ��(S)");
extern CString g_sLangID_CBOperate_FaultMoment;			 //=_T("CBOperate_FaultMoment");
extern CString g_sLangTxt_CBOperate_FaultMoment;			 //=_T("���ϴ���ʱ��");
extern CString g_sLangID_CBOperate_Hour;			 //=_T("CBOperate_Hour");
extern CString g_sLangTxt_CBOperate_Hour;			 //=_T("ʱ");
extern CString g_sLangID_CBOperate_Minute;			 //=_T("CBOperate_Minute");
extern CString g_sLangTxt_CBOperate_Minute;			 //=_T("��");
extern CString g_sLangID_CBOperate_Second;			 //=_T("CBOperate_Second");
extern CString g_sLangTxt_CBOperate_Second;			 //=_T("��");
extern CString g_sLangID_CBOperate_ImpRepre;			 //=_T("CBOperate_ImpRepre");
extern CString g_sLangTxt_CBOperate_ImpRepre;			 //=_T("�迹��ʾ��ʽ��");
extern CString g_sLangID_CBOperate_AmpPhase;			 //=_T("CBOperate_AmpPhase");
extern CString g_sLangTxt_CBOperate_AmpPhase;			 //=_T("��ֵ��λ");
extern CString g_sLangID_CBOperate_ConversionTime;			 //=_T("CBOperate_ConversionTime");
extern CString g_sLangTxt_CBOperate_ConversionTime;			 //=_T("ת��ʱ��(S)");
extern CString g_sLangID_CBOperate_Reverse;			 //=_T("CBOperate_Reverse");
extern CString g_sLangTxt_CBOperate_Reverse;			 //=_T("����");
extern CString g_sLangID_CBOperate_Positive;			 //=_T("CBOperate_Positive");
extern CString g_sLangTxt_CBOperate_Positive;			 //=_T("����");
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
extern CString g_sLangTxt_Swing_CTPos;         //=_T("TA�����ԣ�");
extern CString g_sLangID_Swing_Zs;			 //=_T("Swing_Zs");
extern CString g_sLangTxt_Swing_Zs;			 //=_T(
extern CString g_sLangID_Swing_ZsPhi;          //=_T("Swing_ZsPhi");
extern CString g_sLangTxt_Swing_ZsPhi;         //=_T("PhI(Zs)(��)��");
extern CString g_sLangID_Swing_Transformer;			 //=_T("Swing_Transformer");
extern CString g_sLangTxt_Swing_Transformer;			 //=_
extern CString g_sLangID_Swing_Transformer_Phi;        //=_T("Swing_Transformer_Phi");
extern CString g_sLangTxt_Swing_Transformer_Phi;       //=_T("Phi(Zt)(��)��");
extern CString g_sLangID_Swing_Dynamo;			 //=_T("Swing_Dynamo");
extern CString g_sLangTxt_Swing_Dynamo;			 //=_T(
extern CString g_sLangID_Power_Active;			 //=_T("Power_Active");
extern CString g_sLangTxt_Power_Active;			 //=_T
extern CString g_sLangID_Power_Reactive;			 //=_T("Power_Reactive");
extern CString g_sLangTxt_Power_Reactive;			 //=_T("�޹�(Var)");

extern CString g_sLangID_DistanceSearch_LNFault;			 //=_T("DistanceSearch_LNFault");
extern CString g_sLangTxt_DistanceSearch_LNFault;			 //=_T("��\n��\n��\n��");
extern CString g_sLangID_DistanceSearch_LLFault;			 //=_T("DistanceSearch_LLFault");
extern CString g_sLangTxt_DistanceSearch_LLFault;			 //=_T("��\n��\n��\n��");
extern CString g_sLangID_DistanceSearch_SectionOne;			 //=_T("DistanceSearch_SectionOne");
extern CString g_sLangTxt_DistanceSearch_SectionOne;			 //=_T("��");
extern CString g_sLangID_DistanceSearch_SectionTwo;			 //=_T("DistanceSearch_SectionTwo");
extern CString g_sLangTxt_DistanceSearch_SectionTwo;			 //=_T("��");
extern CString g_sLangID_DistanceSearch_SectionThree;			 //=_T("DistanceSearch_SectionThree");
extern CString g_sLangTxt_DistanceSearch_SectionThree;			 //=_T("��");
extern CString g_sLangID_DistanceSearch_SectionFour;			 //=_T("DistanceSearch_SectionFour");
extern CString g_sLangTxt_DistanceSearch_SectionFour;			 //=_T("��");
extern CString g_sLangID_DistanceSearch_SectionFive;			 //=_T("DistanceSearch_SectionFive");
extern CString g_sLangTxt_DistanceSearch_SectionFive;			 //=_T("��");

extern CString g_sLangID_DistanceSearch_LNShort;				//_T("DistanceSearch_LNShort")
extern CString g_sLangTxt_DistanceSearch_LNShort;				//_T("����ӵض�·")
extern CString g_sLangID_DistanceSearch_LLShort;				//_T("DistanceSearch_LLShort")
extern CString g_sLangTxt_DistanceSearch_LLShort;				//_T("����·")
extern CString g_sLangID_DistanceSearch_ThreePhaseShort;       //_T("DistanceSearch_ThreePhaseShort")
extern CString g_sLangTxt_DistanceSearch_ThreePhaseShort;       //_T("�����·")
extern CString g_sLangID_DistanceSearch_ActionTime;			 //_T("DistanceSearch_ActionTime")
extern CString g_sLangTxt_DistanceSearch_ActionTime;			 //_T("����ʱ��")
extern CString g_sLangID_DistanceSearch_SensAngle;				//_T("DistanceSearch_SensAngle")
extern CString g_sLangTxt_DistanceSearch_SensAngle;			//_T("������")
extern CString g_sLangID_DistanceSearch_Z;						//_T("DistanceSearch_Z")
extern CString g_sLangTxt_DistanceSearch_Z;					//_T("|Z|(��)")
extern CString g_sLangID_DistanceSearch_Phi;					//_T("DistanceSearch_Phi")
extern CString g_sLangTxt_DistanceSearch_Phi;					 //_T("Phi(��)")
extern CString g_sLangID_DistanceSearch_RepeatTime;			//_T("DistanceSearch_RepeatTime")
extern CString g_sLangTxt_DistanceSearch_RepeatTime;			//_T("�ظ�����")
extern CString g_sLangID_DistanceSearch_Report;				//_T("DistanceSearch_Report")
extern CString g_sLangTxt_DistanceSearch_Report;				//_T("���洦��")
extern CString g_sLangID_DistanceSearch_AutoClose;				//_T("DistanceSearch_AutoClose")
extern CString g_sLangTxt_DistanceSearch_AutoClose;				//_T("�߽��Զ��պ�")
extern CString g_sLangID_DistanceSearch_XAxisName;				//_T("DistanceSearch_XAxisName")
extern CString g_sLangTxt_DistanceSearch_XAxisName;				//_T("R/�� ")
extern CString g_sLangID_DistanceSearch_YAxisName;				//_T("DistanceSearch_YAxisName")
extern CString g_sLangTxt_DistanceSearch_YAxisName;				//_T("X/�� ")

//20241024 wanmj
extern CString g_sLangID_DistanceSearch_ZoneType;				//_T("DistanceSearch_ZoneType")
extern CString g_sLangTxt_DistanceSearch_ZoneType;				//_T("����:")
extern CString g_sLangID_DistanceSearch_BeginZ;				//_T("DistanceSearch_BeginZ")
extern CString g_sLangTxt_DistanceSearch_BeginZ;				//_T("�׶��迹(��):")
extern CString g_sLangID_DistanceSearch_BeginZAngle;				//_T("DistanceSearch_BeginZAngle")
extern CString g_sLangTxt_DistanceSearch_BeginZAngle;				//_T("�׶��迹��(��):")
extern CString g_sLangID_DistanceSearch_EndZ;				//_T("DistanceSearch_EndZ")
extern CString g_sLangTxt_DistanceSearch_EndZ;				//_T("ĩ���迹(��):")
extern CString g_sLangID_DistanceSearch_EndZAngle;				//_T("DistanceSearch_EndZAngle")
extern CString g_sLangTxt_DistanceSearch_EndZAngle;				//_T("ĩ���迹��(��):")
extern CString g_sLangID_DistanceSearch_Step;				//_T("DistanceSearch_Step")
extern CString g_sLangTxt_DistanceSearch_Step;				//_T("�迹����(��):")
extern CString g_sLangID_DistanceSearch_TSetting;				//_T("DistanceSearch_TSetting")
extern CString g_sLangTxt_DistanceSearch_TSetting;				//_T("ʱ�䶨ֵ(s):")
extern CString g_sLangID_DistanceSearch_AbsErr;				//_T("DistanceSearch_AbsErr")
extern CString g_sLangTxt_DistanceSearch_AbsErr;				//_T("�������(��):")
extern CString g_sLangID_DistanceSearch_TimeAfterTrigger;				//_T("DistanceSearch_TimeAfterTrigger")
extern CString g_sLangTxt_DistanceSearch_TimeAfterTrigger;				//_T("�������������ʱ��(s):")
extern CString g_sLangID_DistanceSearch_MinActionTime;				//_T("DistanceSearch_MinActionTime")
extern CString g_sLangTxt_DistanceSearch_MinActionTime;				//_T("��С����ʱ��(s):")
extern CString g_sLangID_DistanceSearch_Zl;				//_T("DistanceSearch_Zl")
extern CString g_sLangTxt_DistanceSearch_Zl;				//_T("��·�迹(��):")
extern CString g_sLangID_DistanceSearch_SearchWay;				//_T("DistanceSearch_SearchWay")
extern CString g_sLangTxt_DistanceSearch_SearchWay;				//_T("������ʽ:")
extern CString g_sLangID_DistanceSearch_K0Mode;				//_T("DistanceSearch_K0Mode")
extern CString g_sLangTxt_DistanceSearch_K0Mode;				//_T("���򲹳�ϵ�����㷽ʽ:")
extern CString g_sLangID_DistanceSearch_ZsMag;				//_T("DistanceSearch_ZsMag")
extern CString g_sLangTxt_DistanceSearch_ZsMag;				//_T("ϵͳ�迹(��):")
extern CString g_sLangID_DistanceSearch_ZsAngle;				//_T("DistanceSearch_ZsAngle")
extern CString g_sLangTxt_DistanceSearch_ZsAngle;				//_T("ϵͳ�迹��(��):")
extern CString g_sLangID_DistanceSearch_PTPos;				//_T("DistanceSearch_PTPos")
extern CString g_sLangTxt_DistanceSearch_PTPos;				//_T("TV��װλ��:")
extern CString g_sLangID_DistanceSearch_CTPos;				//_T("DistanceSearch_CTPos")
extern CString g_sLangTxt_DistanceSearch_CTPos;				//_T("TA������:")
extern CString g_sLangID_DistanceSearch_SimulateBreakerDelay;				//_T("DistanceSearch_SimulateBreakerDelay")
extern CString g_sLangTxt_DistanceSearch_SimulateBreakerDelay;				//_T("��·��ģ��:")
extern CString g_sLangID_DistanceSearch_BrkBreakTime;				//_T("DistanceSearch_BrkBreakTime")
extern CString g_sLangTxt_DistanceSearch_BrkBreakTime;				//_T("��բʱ��(ms):")
extern CString g_sLangID_DistanceSearch_BrkCloseTime;				//_T("DistanceSearch_BrkCloseTime")
extern CString g_sLangTxt_DistanceSearch_BrkCloseTime;				//_T("��բʱ��(ms):")
extern CString g_sLangID_DistanceSearch_FaultId;				//_T("DistanceSearch_FaultId")
extern CString g_sLangTxt_DistanceSearch_FaultId;				//_T("�Ƿ���ӷ����ڷ���:")
extern CString g_sLangID_DistanceSearch_FaultAngMode;				//_T("DistanceSearch_FaultAngMode")
extern CString g_sLangTxt_DistanceSearch_FaultAngMode;				//_T("��բ�Ƿ�ʽ:")
extern CString g_sLangID_DistanceSearch_FaultAng;				//_T("DistanceSearch_FaultAng")
extern CString g_sLangTxt_DistanceSearch_FaultAng;				//_T("��բ��(��):")
extern CString g_sLangID_DistanceSearch_Header_ZoneType;				//_T("DistanceSearch_Header_ZoneType")
extern CString g_sLangTxt_DistanceSearch_Header_ZoneType;				//_T("����")
extern CString g_sLangID_DistanceSearch_OrigImp;				//_T("DistanceSearch_OrigImp")
extern CString g_sLangTxt_DistanceSearch_OrigImp;				//_T("���ĵ��迹(��):")
extern CString g_sLangID_DistanceSearch_OrigAng;				//_T("DistanceSearch_OrigAng")
extern CString g_sLangTxt_DistanceSearch_OrigAng;				//_T("���ĵ��迹��(��):")
extern CString g_sLangID_DistanceSearch_SearchAngBeg;				//_T("DistanceSearch_SearchAngBeg")
extern CString g_sLangTxt_DistanceSearch_SearchAngBeg;				//_T("�����Ƕ�ʼֵ(��):")
extern CString g_sLangID_DistanceSearch_SearchAngEnd;				//_T("DistanceSearch_SearchAngEnd")
extern CString g_sLangTxt_DistanceSearch_SearchAngEnd;				//_T("�����Ƕ���ֵ(��):")
extern CString g_sLangID_DistanceSearch_AngStep;				//_T("DistanceSearch_AngStep")
extern CString g_sLangTxt_DistanceSearch_AngStep;				//_T("�Ƕȸı䲽��(��):")
extern CString g_sLangID_DistanceSearch_ZoneTypeSelect;				//_T("DistanceSearch_ZoneTypeSelect")
extern CString g_sLangTxt_DistanceSearch_ZoneTypeSelect;				//_T("����ѡ��:")
extern CString g_sLangID_DistanceSearch_SearchLen;				//_T("DistanceSearch_SearchLen")
extern CString g_sLangTxt_DistanceSearch_SearchLen;				//_T("�����뾶(��):")
extern CString g_sLangID_DistanceSearch_TripZ;				//_T("DistanceSearch_TripZ")
extern CString g_sLangTxt_DistanceSearch_TripZ;				//_T("ʵ���迹(��)")
extern CString g_sLangID_DistanceSearch_TripZAngle;				//_T("DistanceSearch_TripZAngle")
extern CString g_sLangTxt_DistanceSearch_TripZAngle;				//_T("ʵ���迹��(��)")
extern CString g_sLangID_DistanceSearch_AddItemFailed;				//_T("DistanceSearch_AddItemFailed")
extern CString g_sLangTxt_DistanceSearch_AddItemFailed;				//_T("����������û�н��㣬�����ɲ����")

extern CString g_sLangID_ActionTime_LNShort;            //_T("ActionTime_LNShort")
extern CString g_sLangTxt_ActionTime_LNShort;            //_T("����ӵض�·")
extern CString g_sLangID_ActionTime_LLShort;            //_T("ActionTime_LLShort")
extern CString g_sLangTxt_ActionTime_LLShort;            //_T("����·")
extern CString g_sLangID_ActionTime_ThreePhaseShort;     //_T("ActionTime_ThreePhaseShort")
extern CString g_sLangTxt_ActionTime_ThreePhaseShort;     //_T("�����·")
extern CString g_sLangID_ActionTime_ZeroCur;             //_T("ActionTime_ZeroCur")
extern CString g_sLangTxt_ActionTime_ZeroCur;            //_T("�������3I0")
extern CString g_sLangID_ActionTime_NegCur;              //_T("ActionTime_NegCur")
extern CString g_sLangTxt_ActionTime_NegCur;             //_T("�������I2")
extern CString g_sLangID_ActionTime_ThreeParallel;      //_T("ActionTime_ThreeParallel")
extern CString g_sLangTxt_ActionTime_ThreeParallel;     //_T("�����������")
extern CString g_sLangID_ActionTime_ShortVol;            //_T("ActionTime_ShortVol")
extern CString g_sLangTxt_ActionTime_ShortVol;            //_T("��·��ѹ")
extern CString g_sLangID_ActionTime_ZeroVol;            //_T("ActionTime_ZeroVol")
extern CString g_sLangTxt_ActionTime_ZeroVol;            //_T("�����ѹ")
extern CString g_sLangID_ActionTime_NegVol;            //_T("ActionTime_NegVol")
extern CString g_sLangTxt_ActionTime_NegVol;            //_T("�����ѹ")
extern CString g_sLangID_ActionTime_SettingTime;            //_T("ActionTime_SettingTime")
extern CString g_sLangTxt_ActionTime_SettingTime;            //_T("����ʱ�䶨ֵ(s):")
extern CString g_sLangID_ActionTime_FaultVolType;            //_T("ActionTime_FaultVolType")
extern CString g_sLangTxt_ActionTime_FaultVolType;            //_T("���ϵ�ѹ:")
extern CString g_sLangID_ActionTime_FaultVol;            //_T("ActionTime_FaultVol")
extern CString g_sLangTxt_ActionTime_FaultVol;            //_T("���ϵ�ѹ(V):")
extern CString g_sLangID_ActionTime_FaultAngle;            //_T("ActionTime_FaultAngle")
extern CString g_sLangTxt_ActionTime_FaultAngle;            //_T("����̬��λ��(��):")
extern CString g_sLangID_ActionTime_FaultFre;            //_T("ActionTime_FaultFre")
extern CString g_sLangTxt_ActionTime_FaultFre;            //_T("����̬Ƶ��(Hz):")
extern CString g_sLangID_ActionTime_RelErr;            //_T("ActionTime_RelErr")
extern CString g_sLangTxt_ActionTime_RelErr;            //_T("������(��):")
extern CString g_sLangID_ActionTime_AbsErrPos;            //_T("ActionTime_AbsErrPos")
extern CString g_sLangTxt_ActionTime_AbsErrPos;            //_T("�������(s)+:")
extern CString g_sLangID_ActionTime_AbsErrNeg;            //_T("ActionTime_AbsErrNeg")
extern CString g_sLangTxt_ActionTime_AbsErrNeg;            //_T("�������(s)-:")
extern CString g_sLangID_ActionTime_NormalVol;            //_T("ActionTime_NormalVol")
extern CString g_sLangTxt_ActionTime_NormalVol;            //_T("��̬��ѹ(V):")
extern CString g_sLangID_ActionTime_NormalCur;            //_T("ActionTime_NormalCur")
extern CString g_sLangTxt_ActionTime_NormalCur;            //_T("��̬����(A):")
extern CString g_sLangID_ActionTime_NormalAngle;            //_T("ActionTime_NormalAngle")
extern CString g_sLangTxt_ActionTime_NormalAngle;            //_T("��̬��λ��(��):")
extern CString g_sLangID_ActionTime_NormalFre;            //_T("ActionTime_NormalFre")
extern CString g_sLangTxt_ActionTime_NormalFre;            //_T("��̬Ƶ��(Hz):")
extern CString g_sLangID_ActionTime_FaultTime;            //_T("ActionTime_FaultTime")
extern CString g_sLangTxt_ActionTime_FaultTime;            //_T("����ʱ��ԣ��(s):")
extern CString g_sLangID_ActionTime_ErrType;            //_T("ActionTime_ErrType")
extern CString g_sLangTxt_ActionTime_ErrType;            //_T("�������:")

extern CString g_sLangID_ActionTime_TestItem;            //_T("ActionTime_TestItem")
extern CString g_sLangTxt_ActionTime_TestItem;            //_T("������Ŀ")
extern CString g_sLangID_ActionTime_FaultPhase;            //_T("ActionTime_TestPhase")
extern CString g_sLangTxt_ActionTime_FaultPhase;            //_T("�������")
extern CString g_sLangID_ActionTime_Select;            //_T("ActionTime_Select")
extern CString g_sLangTxt_ActionTime_Select;            //_T("ѡ��")
extern CString g_sLangID_ActionTime_TestResult;            //_T("ActionTime_TestResult")
extern CString g_sLangTxt_ActionTime_TestResult;            //_T("���Խ��(s)")
extern CString g_sLangID_ActionTime_Title_SettingTime;            //_T("ActionTime_Title_SettingTime")
extern CString g_sLangTxt_ActionTime_Title_SettingTime;            //_T("ʱ�䶨ֵ(s)")
extern CString g_sLangID_CurrentHigh330;//�߹��ʵ���
extern CString g_sLangTxt_CurrentHigh330;
extern CString g_sLangID_Native_CommandTimeout;
extern CString g_sLangTxt_Native_CommandTimeout;

extern CString g_sLangID_Button_AddMultQuick;		    //_T("AddMultQuick")//wanmj 2024.7.14
extern CString g_sLangTxt_Button_AddMultQuick;		    //_T("�������")
extern CString g_sLangID_Button_AddMultDlg;			//_T("AddMultDlg")
extern CString g_sLangTxt_Button_AddMultDlg;			//_T("���ϵ��")
extern CString g_sLangID_Button_AddMultBatch;          //_T("AddMultBatch")
extern CString g_sLangTxt_Button_AddMultBatch;          //_T("�������")
extern CString g_sLangID_Button_AddCustomizedPara;			//_T("AddCustomizedPara")
extern CString g_sLangTxt_Button_AddCustomizedPara;			//_T("�Զ���������")
extern CString g_sLangID_Button_AddDefaultPara;          //_T("AddDefaultPara")
extern CString g_sLangTxt_Button_AddDefaultPara;          //_T("Ĭ�ϲ������")

extern CString g_sLangID_Button_DeleteSelItem;         //_T("DeleteSelItem")
extern CString g_sLangTxt_Button_DeleteSelItem;         //_T("ɾ����ǰ")
extern CString g_sLangID_Button_DeleteAllItem;         //_T("DeleteAllItem")
extern CString g_sLangTxt_Button_DeleteAllItem;         //_T("ɾ��ȫ��")
extern CString g_sLangID_Button_ClearSelResult;		//_T("ClearSelResult")
extern CString g_sLangTxt_Button_ClearSelResult;		//_T("�����ǰ")
extern CString g_sLangID_Button_ClearAllResult;		//_T("_ClearAllResult")
extern CString g_sLangTxt_Button_ClearAllResult;		//_T("���ȫ��")
extern CString g_sLangID_Button_AddOneItem;            //_T("AddOneItem")
extern CString g_sLangTxt_Button_AddOneItem;            //_T("��Ӳ�����")
// extern CString g_sLangID_Button_AddMultiItem;            //_T("AddMultiItem")
// extern CString g_sLangTxt_Button_AddMultiItem;            //_T("���ϵ��")

extern CString g_sLangID_Action_AddOneItem;            //_T("Action_AddOneItem")
extern CString g_sLangTxt_Action_AddOneItem;            //_T("��Ӳ�����")
extern CString g_sLangID_Action_DeleteSelItem;         //_T("Action_DeleteSelItem")
extern CString g_sLangTxt_Action_DeleteSelItem;         //_T("ɾ����ǰ������")
extern CString g_sLangID_Action_DeleteAllItem;         //_T("Action_DeleteAllItem")
extern CString g_sLangTxt_Action_DeleteAllItem;         //_T("ɾ�����в�����")
extern CString g_sLangID_Action_ClearSelResult;		//_T("Action_ClearSelResult")
extern CString g_sLangTxt_Action_ClearSelResult;		//_T("�����ǰ���")
extern CString g_sLangID_Action_ClearAllResult;		//_T("Action_ClearAllResult")
extern CString g_sLangTxt_Action_ClearAllResult;		//_T("������н��")

extern CString g_sLangID_PowerDir_TestPhase_Zero;  // _T("PowerDir_ZeroTest");     //20240717 wanmj ���ʷ���������Ķ����Դ���
extern CString g_sLangTxt_PowerDir_TestPhase_Zero;  // _T("�������");
extern CString g_sLangID_PowerDir_TestPhase_Neg;  // _T("PowerDir_NegTest");
extern CString g_sLangTxt_PowerDir_TestPhase_Neg;  // _T("�������");
extern CString g_sLangID_PowerDir_FaultPhase_ZeroCur;  // _T("PowerDir_ZeroCurr");
extern CString g_sLangTxt_PowerDir_FaultPhase_ZeroCur;  // _T("�������");
extern CString g_sLangID_PowerDir_FaultPhase_NegCur;  // _T("PowerDir_NegCurr");
extern CString g_sLangTxt_PowerDir_FaultPhase_NegCur;  // _T("�������");

//20241024 wanmj
extern CString g_sLangID_PowerDir_TestPhase;  // _T("PowerDir_TestPhase");
extern CString g_sLangTxt_PowerDir_TestPhase;  // _T("������:");
extern CString g_sLangID_PowerDir_FaultPhase;  // _T("PowerDir_FaultPhase");
extern CString g_sLangTxt_PowerDir_FaultPhase;  // _T("������:");
extern CString g_sLangID_PowerDir_FaultTime;  // _T("PowerDir_FaultTime");
extern CString g_sLangTxt_PowerDir_FaultTime;  // _T("����ʱ��(s):");
extern CString g_sLangID_PowerDir_MaxSenAngle;  // _T("PowerDir_MaxSenAngle");
extern CString g_sLangTxt_PowerDir_MaxSenAngle;  // _T("���������(��):");
extern CString g_sLangID_PowerDir_ActionAreaRange;  // _T("PowerDir_ActionAreaRange");
extern CString g_sLangTxt_PowerDir_ActionAreaRange;  // _T("��������Χ(��):");
extern CString g_sLangID_PowerDir_StepValue;  // _T("PowerDir_StepValue");
extern CString g_sLangTxt_PowerDir_StepValue;  // _T("�仯����(��):");
extern CString g_sLangID_PowerDir_AbsErr;  // _T("PowerDir_AbsErr");
extern CString g_sLangTxt_PowerDir_AbsErr;  // _T("�������(��):");
extern CString g_sLangID_PowerDir_NormalBout;  // _T("PowerDir_NormalBout");
extern CString g_sLangTxt_PowerDir_NormalBout;  // _T("��̬��������");
extern CString g_sLangID_PowerDir_FaultBout;  // _T("PowerDir_FaultBout");
extern CString g_sLangTxt_PowerDir_FaultBout;  // _T("����̬��������");
extern CString g_sLangID_PowerDir_UPre;  // _T("PowerDir_UPre");
extern CString g_sLangTxt_PowerDir_UPre;  // _T("��̬��ѹ��ֵ(V):");
extern CString g_sLangID_PowerDir_UPhSet;  // _T("PowerDir_UPhSet");
extern CString g_sLangTxt_PowerDir_UPhSet;  // _T("��̬��ѹ����:");
extern CString g_sLangID_PowerDir_IPre;  // _T("PowerDir_IPre");
extern CString g_sLangTxt_PowerDir_IPre;  // _T("��̬������ֵ(A):");
extern CString g_sLangID_PowerDir_IPhSet;  // _T("PowerDir_IPhSet");
extern CString g_sLangTxt_PowerDir_IPhSet;  // _T("��̬��������:");
extern CString g_sLangID_PowerDir_PreAngle;  // _T("PowerDir_PreAngle");
extern CString g_sLangTxt_PowerDir_PreAngle;  // _T("��̬���(U-I):");
extern CString g_sLangID_PowerDir_AngleMode;  // _T("PowerDir_AngleMode");
extern CString g_sLangTxt_PowerDir_AngleMode;  // _T("�Ƕȶ���:");
extern CString g_sLangID_PowerDir_ConnectMode;  // _T("PowerDir_ConnectMode");
extern CString g_sLangTxt_PowerDir_ConnectMode;  // _T("���߷�ʽ:");
extern CString g_sLangID_PowerDir_AngleMargin;  // _T("PowerDir_AngleMargin");
extern CString g_sLangTxt_PowerDir_AngleMargin;  // _T("�Ƕ�ԣ��(��):");
extern CString g_sLangID_PowerDir_FaultParas;  // _T("PowerDir_FaultParas");
extern CString g_sLangTxt_PowerDir_FaultParas;  // _T("���ϲ���");
// extern CString g_sLangID_PowerDir_TestParas;  // _T("PowerDir_TestParas");
// extern CString g_sLangTxt_PowerDir_TestParas;  // _T("�������");
extern CString g_sLangID_PowerDir_APhaseTest;  // _T("PowerDir_APhaseTest");
extern CString g_sLangTxt_PowerDir_APhaseTest;  // _T("A�����");
extern CString g_sLangID_PowerDir_BPhaseTest;  // _T("PowerDir_BPhaseTest");
extern CString g_sLangTxt_PowerDir_BPhaseTest;  // _T("B�����");
extern CString g_sLangID_PowerDir_CPhaseTest;  // _T("PowerDir_CPhaseTest");
extern CString g_sLangTxt_PowerDir_CPhaseTest;  // _T("C�����");
extern CString g_sLangID_PowerDir_ABPhaseTest;  // _T("PowerDir_ABPhaseTest");
extern CString g_sLangTxt_PowerDir_ABPhaseTest;  // _T("AB�����");
extern CString g_sLangID_PowerDir_BCPhaseTest;  // _T("PowerDir_BCPhaseTest");
extern CString g_sLangTxt_PowerDir_BCPhaseTest;  // _T("BC�����");
extern CString g_sLangID_PowerDir_CAPhaseTest;  // _T("PowerDir_CAPhaseTest");
extern CString g_sLangTxt_PowerDir_CAPhaseTest;  // _T("CA�����");

extern CString g_sLangID_PowerDir_Title_MTA;  // _T("PowerDir_MTA");
extern CString g_sLangTxt_PowerDir_Title_MTA;  // _T("�������������ֵ(��)");
extern CString g_sLangID_PowerDir_Title_ActionAreaRange;  // _T("PowerDir_Title_ActionAreaRange");
extern CString g_sLangTxt_PowerDir_Title_ActionAreaRange;  // _T("��������Χ(��)");
extern CString g_sLangID_PowerDir_Title_StepValue;  // _T("PowerDir_Title_StepValue");
extern CString g_sLangTxt_PowerDir_Title_StepValue;  // _T("�仯����(��)");
extern CString g_sLangID_PowerDir_Title_MaxSenAngle;  // _T("PowerDir_Title_MaxSenAngle");
extern CString g_sLangTxt_PowerDir_Title_MaxSenAngle;  // _T("���������ʵ��ֵ(��)");
extern CString g_sLangID_PowerDir_Title_AngleF;  // _T("PowerDir_Title_AngleF");
extern CString g_sLangTxt_PowerDir_Title_AngleF;  // _T("�߽�1(��)");
extern CString g_sLangID_PowerDir_Title_AngleS;  // _T("PowerDir_Title_AngleS");
extern CString g_sLangTxt_PowerDir_Title_AngleS;  // _T("�߽�2(��)");

extern CString g_sLangID_CrrInverTime_IAmp;            //_T("CrrInverTime_IAmp")//zhangyq 2024.7.14
extern CString g_sLangTxt_CrrInverTime_IAmp;            //_T("������ֵ")
extern CString g_sLangID_CrrInverTime_IPh;            //_T("CrrInverTime_IPh")
extern CString g_sLangTxt_CrrInverTime_IPh;            //_T("������λ")
extern CString g_sLangID_CrrInverTime_ChangeStart;            //_T("CrrInverTime_ChangeStart")
extern CString g_sLangTxt_CrrInverTime_ChangeStart;            //_T("�仯ʼֵ(��)")
extern CString g_sLangID_CrrInverTime_ChangeFinish;            //_T("CrrInverTime_ChangeFinish")
extern CString g_sLangTxt_CrrInverTime_ChangeFinish;            //_T("�仯��ֵ(��)")
extern CString g_sLangID_CrrInverTime_ChangeStep;            //_T("CrrInverTime_ChangeStep")
extern CString g_sLangTxt_CrrInverTime_ChangeStep;            //_T("�仯����(��)")

extern CString g_sLangID_Syn_ActVoltageTest;            //_T("Syn_ActVoltageTest")
extern CString g_sLangTxt_Syn_ActVoltageTest;            //_T("��ѹ�߽�ֵ����")
extern CString g_sLangID_Syn_ActFreqTest;            //_T("Syn_ActFreqTest")
extern CString g_sLangTxt_Syn_ActFreqTest;            //_T("Ƶ�ʱ߽�ֵ����")
extern CString g_sLangID_Syn_LeadAngTest;            //_T("Syn_LeadAngTest")
extern CString g_sLangTxt_Syn_LeadAngTest;            //_T("��ǰ�Ǽ���ǰʱ��")
extern CString g_sLangID_Syn_AutoAdjTest;            //_T("Syn_AutoAdjTest")
extern CString g_sLangTxt_Syn_AutoAdjTest;            //_T("�Զ���������")
extern CString g_sLangID_Syn_AdjVolTest;            //_T("Syn_AdjVolTest")
extern CString g_sLangTxt_Syn_AdjVolTest;            //_T("��ѹ���ڲ���")
extern CString g_sLangID_Syn_AdjFreqTest;            //_T("Syn_AdjFreqTest")
extern CString g_sLangTxt_Syn_AdjFreqTest;            //_T("��Ƶ���ڲ���")

//20240719 huangliang
extern CString g_sLangID_Setting_NoWord;
extern CString g_sLangTxt_Setting_NoWord; //_T("��δ������ֵ")
extern CString g_sLangID_Setting_Link;
extern CString g_sLangTxt_Setting_Link; //_T("����ѡ��ֵ")
extern CString g_sLangID_Setting_Cancel;
extern CString g_sLangTxt_Setting_Cancel; //_T("ȡ������")
extern CString g_sLangID_Setting_CancelAll;
extern CString g_sLangTxt_Setting_CancelAll; //_T("ȡ��ȫ��")
//20240924 huangliang 
extern CString g_sLangID_Setting_NoFind;		
extern CString g_sLangTxt_Setting_NoFind; //_T("δ�ҵ�")
//20241127 huangliang 
extern CString g_sLangID_Setting_ModelName;
extern CString g_sLangTxt_Setting_ModelName;

//wangtao 20240722
extern CString g_sLangID_LowFreq_ULock;            //_T("LowFreq_ULock")
extern CString g_sLangTxt_LowFreq_ULock;            //_T("�͵�ѹ����ֵ")
extern CString g_sLangID_LowFreq_ILock;            //_T("LowFreq_ILock")
extern CString g_sLangTxt_LowFreq_ILock;            //_T("�͵�������ֵ")
extern CString g_sLangID_LowFreq_LowVol;            //_T("LowFreq_LowVol")
extern CString g_sLangTxt_LowFreq_LowVol;            //_T("��ѹ")
extern CString g_sLangID_Gradient_Norm;            //_T("Gradient_Norm")
extern CString g_sLangTxt_Gradient_Norm;            //_T("��̬")
extern CString g_sLangID_Diff_Rate;            //_T("Diff_Rate")
extern CString g_sLangTxt_Diff_Rate;            //_T("���������")
extern CString g_sLangID_Diff_Harm;            //_T("Diff_Harm")
extern CString g_sLangTxt_Diff_Harm;            //_T("г���ƶ�����")
extern CString g_sLangID_Diff_AddSearchLine;            //_T("Diff_AddSearchLine")
extern CString g_sLangTxt_Diff_AddSearchLine;            //_T("���������")
extern CString g_sLangID_Diff_Autocalculation;            //_T("Diff_Autocalculation")
extern CString g_sLangTxt_Diff_Autocalculation;            //_T("�Զ�����")
extern CString g_sLangID_Diff_Manualcalculation;            //_T("Diff_Manualcalculation")
extern CString g_sLangTxt_Diff_Manualcalculation;            //_T("�ֶ�����")
extern CString g_sLangID_Diff_Dichotomy;            //_T("Diff_Dichotomy")
extern CString g_sLangTxt_Diff_Dichotomy;            //_T("���ַ�")
extern CString g_sLangID_Diff_StepwiseApproach;            //_T("Diff_StepwiseApproach")
extern CString g_sLangTxt_Diff_StepwiseApproach;            //_T("�����ƽ���")
extern CString g_sLangID_Diff_Bequation1;            //_T("Diff_Bequation1")
extern CString g_sLangTxt_Diff_Bequation1;           //_T("Ir=(|I1-I2|)/K1��Ir=(|I1+I2|)/K1")
extern CString g_sLangID_Diff_Bequation5;            //_T("Diff_Bequation5")
extern CString g_sLangTxt_Diff_Bequation5;           //_T("Ir=��(K1*I1*I2*Cos(��))")
extern CString g_sLangID_Diff_LineCur;            //_T("Diff_LineCur")
extern CString g_sLangTxt_Diff_LineCur;           //_T("�ߵ���")
extern CString g_sLangID_Diff_Variation;            //_T("Diff_Variation")
extern CString g_sLangTxt_Diff_Variation;           //_T("��")
extern CString g_sLangID_Diff_sideAdjust;            //_T("Diff_Adjust")
extern CString g_sLangTxt_Diff_sideAdjust;           //_T("��У��")
extern CString g_sLangID_Diff_High;            //_T("Diff_High")
extern CString g_sLangTxt_Diff_High;           //_T("��")
extern CString g_sLangID_Diff_Medium;            //_T("Diff_Medium")
extern CString g_sLangTxt_Diff_Medium;           //_T("��")
extern CString g_sLangID_Diff_Low;            //_T("Diff_Low")
extern CString g_sLangTxt_Diff_Low;           //_T("��")
extern CString g_sLangID_MaintainatLeastOneItem;            //_T("MaintainatLeastOneItem")
extern CString g_sLangTxt_MaintainatLeastOneItem;           //_T("�����ٹ�ѡһ�������")
extern CString g_sLangID_MaintainatLeastOneFault;            //_T("MaintainatLeastOneFault");
extern CString g_sLangTxt_MaintainatLeastOneFault;            //_T("�����ٹ�ѡһ���������Σ�");
extern CString g_sLangID_MaintainatLeastOneFunc;            //_T("MaintainatLeastOneFunc");
extern CString g_sLangTxt_MaintainatLeastOneFunc;            //_T("�����ٹ�ѡһ������ģ�飡");
extern CString g_sLangID_MaintainatLeastOneErrorType;       //_T("MaintainatLeastOneErrorType");
extern CString g_sLangTxt_MaintainatLeastOneErrorType;      //_T("�����ٹ�ѡһ���������");
extern CString g_sLangID_MaintainatLeastOneRate;			 //T("MaintainatLeastOneRate");
extern CString g_sLangTxt_MaintainatLeastOneRate;           //_T("�����ٹ�ѡһ��������");
extern CString g_sLangID_MaintainatLeastOneDirection;       // = _T("MaintainatLeastOneDirection");
extern CString g_sLangTxt_MaintainatLeastOneDirection;      // = _T("�����ٹ�ѡһ�����Ϸ���");

//2024.7.19  lupzibing 
extern CString g_sLangID_Distance_DeleteItem;			// _T("Distance_DeleteItem");
extern CString g_sLangTxt_Distance_DeleteItem;			// _T("ɾ��������");
extern CString g_sLangID_Distance_ClearResult;			// _T("Distance_ClearResult");
extern CString g_sLangTxt_Distance_ClearResult;			// _T("������Խ��");
extern CString g_sLangID_Distance_Zone1;				//_T("Distance_Zone1");
extern CString g_sLangTxt_Distance_Zone1;				//_T("���");
extern CString g_sLangID_Distance_Zone2;				//_T("Distance_Zone2");
extern CString g_sLangTxt_Distance_Zone2;				//_T("���");
extern CString g_sLangID_Distance_Zone3;				//_T("Distance_Zone3");
extern CString g_sLangTxt_Distance_Zone3;				//_T("���");
extern CString g_sLangID_Distance_Zone4;				//_T("Distance_Zone4");
extern CString g_sLangTxt_Distance_Zone4;				//_T("����");
extern CString g_sLangID_Distance_Zone5;				//_T("Distance_Zone5");
extern CString g_sLangTxt_Distance_Zone5;				//_T("����");
extern CString g_sLangID_Distance_ZoneLine;				//_T("Distance_ZoneLine");
extern CString g_sLangTxt_Distance_ZoneLine;			//_T("��·����");
extern CString g_sLangID_Distance_ZoneAllarea;			//_T("Distance_ZoneAllarea");
extern CString g_sLangTxt_Distance_ZoneAllarea;			//_T("��������");
extern CString g_sLangID_Distance_ErrorNot;				//_T("Distance_ErrorNot");
extern CString g_sLangTxt_Distance_ErrorNot;			//_T("������");;
extern CString g_sLangID_Distance_ErrorRelAndAbs;		//_T("Distance_ErrorRelAndAbs");
extern CString g_sLangTxt_Distance_ErrorRelAndAbs;		//_T("�������&amp;������");
extern CString g_sLangID_Distance_ErrorRelorAbs;		//_T("Distance_ErrorRelorAbs");
extern CString g_sLangTxt_Distance_ErrorRelorAbs;		//_T("�������or������");
extern CString g_sLangID_Distance_AddOneLN;				//_T("Distance_AddOneLN");
extern CString g_sLangTxt_Distance_AddOneLN;			//_T("��ӵ�������-�ӵع���");
extern CString g_sLangID_Distance_AddOneLL;				//_T("Distance_AddOneLL");
extern CString g_sLangTxt_Distance_AddOneLL;			//_T("��ӵ�������-������");
extern CString g_sLangID_Distance_AddMult;				//_T("Distance_AddMult");
extern CString g_sLangTxt_Distance_AddMult;				//_T("��Ӷ������");
extern CString g_sLangID_Distance_VzDefine;             //_T("Distance_VzDefine");
extern CString g_sLangTxt_Distance_VzDefine;           	//_T("��3��3U0");
extern CString g_sLangID_Distance_ZTYAxis;		//_T("Distance_ZTYAxis");
extern CString g_sLangTxt_Distance_ZTYAxis;		//_T("Z(��)");


extern CString g_sLangID_Distance_Percent;			// = _T("Distance_Percent");
extern CString g_sLangTxt_Distance_Percent;			//= _T("�ٷֱ�(%):");
extern CString g_sLangID_Distance_ZoneSel;			// = _T("Distance_ZoneSel");
extern CString g_sLangTxt_Distance_ZoneSel;			//= _T("����ѡ��:");
extern CString g_sLangID_Distance_FaultLN;			// = _T("Distance_FaultLN");
extern CString g_sLangTxt_Distance_FaultLN;			//= _T("��\n��\n��\n��");
extern CString g_sLangID_Distance_FaultLL;			// = _T("Distance_FaultLL");
extern CString g_sLangTxt_Distance_FaultLL;			//= _T("��\n��\n��\n��");
extern CString g_sLangID_Distance_MinTrip;			// = _T("Distance_MinTrip");
extern CString g_sLangTxt_Distance_MinTrip;			//= _T("��С����ʱ��(s):");
extern CString g_sLangID_Distance_ZLineSet;			// = _T("Distance_ZLineSet");
extern CString g_sLangTxt_Distance_ZLineSet;			//= _T("��·�迹(��):");
extern CString g_sLangID_Distance_AddOneTileLL;			// = _T("Distance_AddOneTileLL");
extern CString g_sLangTxt_Distance_AddOneTileLL;			//= _T("���������");
extern CString g_sLangID_Distance_AddOneTileLN;			// = _T("Distance_AddOneTileLN");
extern CString g_sLangTxt_Distance_AddOneTileLN;			//= _T("��ӵ���ӵع���");
// extern CString g_sLangID_Distance_AddMultTile;			// = _T("Distance_AddMultTile");
// extern CString g_sLangTxt_Distance_AddMultTile;			//= _T("���ϵ��");
extern CString g_sLangID_Distance_CommonParas;			// = _T("Distance_CommonParas");
extern CString g_sLangTxt_Distance_CommonParas;			//= _T("ͨ�ò�������");
extern CString g_sLangID_Distance_ZImpValue;			// = _T("Distance_ZImpValue");
extern CString g_sLangTxt_Distance_ZImpValue;			// = _T("�迹(��):");
extern CString g_sLangID_Distance_TSetting;			// = _T("Distance_TSetting");
extern CString g_sLangTxt_Distance_TSetting;			// = _T("ʱ�䶨ֵ(s):");
extern CString g_sLangID_Distance_SetActionTime;			// = _T("Distance_SetActionTime");
extern CString g_sLangTxt_Distance_SetActionTime;			// = _T("��������ʱ��(s):");
extern CString g_sLangID_Distance_AddMultZone;			// = _T("Distance_AddMultZone");
extern CString g_sLangTxt_Distance_AddMultZone;			// = _T("����:");
extern CString g_sLangID_Distance_FaultTypeSel;			// = _T("Distance_FaultTypeSel");
extern CString g_sLangTxt_Distance_FaultTypeSel;			// = _T("��������ѡ��:");
extern CString g_sLangID_Distance_FailDirectSel;			// = _T("Distance_FailDirectSel");
extern CString g_sLangTxt_Distance_FailDirectSel;			// = _T("���Ϸ���ѡ��:");
extern CString g_sLangID_Distance_AddMultZAng;			// = _T("Distance_AddMultZAng");
extern CString g_sLangTxt_Distance_AddMultZAng;			// = _T("�迹��(��)");
extern CString g_sLangID_Distance_OutputHoldTimeS;			// = _T("Distance_OutputHoldTimeS");
extern CString g_sLangTxt_Distance_OutputHoldTimeS;			// = _T("��������ʱ��(s)");
extern CString g_sLangID_Distance_OutputDelayTime;			// = _T("Distance_OutputDelayTime");
extern CString g_sLangTxt_Distance_OutputDelayTime;			// = _T("������תʱ��(s)");
extern CString g_sLangID_Distance_VzPh;			// = _T("Distance_VzPh");
extern CString g_sLangTxt_Distance_VzPh;			// = _T("��ȡ��ѹ���(��Բο���):");
extern CString g_sLangID_Distance_AddTestItemTips;			// = _T("Distance_AddTestItemTips");
extern CString g_sLangTxt_Distance_AddTestItemTips;			// = _T("����Ӳ����");
extern CString g_sLangID_Distance_BreakTime_sec;			// = _T("Distance_BreakTime_sec");
extern CString g_sLangTxt_Distance_BreakTime_sec;			// = _T("��բʱ��(ms)");
extern CString g_sLangID_Distance_BrkCloseTime_sec;			// = _T("Distance_BrkCloseTime_sec");
extern CString g_sLangTxt_Distance_BrkCloseTime_sec;			// = _T("��բʱ��(ms)");
extern CString g_sLangID_Distance_FaultPreTimeS;
extern CString g_sLangTxt_Distance_FaultPreTimeS; // ����ǰʱ��(s)
extern CString g_sLangID_Distance_FaultTimeMargin;			   // = _T("Distance_FaultTimeMargin")
extern CString g_sLangTxt_Distance_FaultTimeMargin;			   // = _T("����ʱ��ԣ��(s)")

extern CString g_sLangID_CharElement_StartPointAmp;			// = _T("CharElement_StartPointAmp");
extern CString g_sLangTxt_CharElement_StartPointAmp;			// = _T("��ʼ��-��ֵ");
extern CString g_sLangID_CharElement_StartPointAngle;			// = _T("CharElement_StartPointAngle");
extern CString g_sLangTxt_CharElement_StartPointAngle;			// = _T("��ʼ��-��λ");
extern CString g_sLangID_CharElement_EndPointAmp;			// = _T("CharElement_EndPointAmp");
extern CString g_sLangTxt_CharElement_EndPointAmp;			// = _T("��ֹ��-��ֵ");
extern CString g_sLangID_CharElement_EndPointAngle;			// = _T("CharElement_EndPointAngle");
extern CString g_sLangTxt_CharElement_EndPointAngle;			// = _T("��ֹ��-��λ");
extern CString g_sLangID_CharElement_ARCAmp;			// = _T("CharElement_ARCAmp");
extern CString g_sLangTxt_CharElement_ARCAmp;			// = _T("��ֵ-Բ��");
extern CString g_sLangID_CharElement_ARCAngle;			// = _T("CharElement_ARCAngle");
extern CString g_sLangTxt_CharElement_ARCAngle;			// = _T("��λ-Բ��");

extern CString g_sLangID_Distance_ImpActBorder;		// =_T("Distance_ImpActBorder");
extern CString g_sLangID_Distance_ImpActBorder;		// =_T("Distance_ImpActBorder");
extern CString g_sLangTxt_Distance_ImpActBorder;		// =_T("�迹�����߽�");
extern CString g_sLangID_Distance_ImpSetCheck;		// =_T("Distance_ImpSetCheck");
extern CString g_sLangTxt_Distance_ImpSetCheck;		// =_T("�迹��ֵУ��");
extern CString g_sLangID_Distance_AbsErrPlus;			// =_T("Distance_AbsErrPlus");
extern CString g_sLangTxt_Distance_AbsErrPlus;					// =_T("�������(+)");
extern CString g_sLangID_Distance_AbsErrMinus;		// =_T("Distance_AbsErrMinus");
extern CString g_sLangTxt_Distance_AbsErrMinus;				// =_T("�������(-)");
extern CString g_sLangID_Distance_CharacterEng_UseZone;		// =_T("CharacterEng_UseZone");
extern CString g_sLangTxt_CharacterEng_UseZone;				// =_T("ʹ��");
extern CString g_sLangID_Distance_CharacterEng_FaulTips;		// =_T("CharacterEng_FaulTips");
extern CString g_sLangTxt_CharacterEng_FaulTips;				// =_T("���й��ϻ�����ȷʵ�Ѵ���!");
extern CString g_sLangID_Distance_CharacterEng_FaulTipTile;	// =_T("CharacterEng_FaulTipTile");
extern CString g_sLangTxt_CharacterEng_FaulTipTile;			// =_T("��ʾ");

extern CString g_sLangTxt_Replay_WaveformEditing;         //_T("���α༭")//wuxy 2024.7.22
extern CString g_sLangID_Replay_WaveformEditing;          //_T("Replay_WaveformEditing")
extern CString g_sLangTxt_Replay_OriWaveEdit;             //_T("ԭ���α༭")
extern CString g_sLangID_Replay_OriWaveEdit;              //_T("Replay_OriWaveEdit")
extern CString g_sLangTxt_Replay_InsertNorWave;           //_T("���볣̬����")
extern CString g_sLangID_Replay_InsertNorWave;            //_T("Replay_InsertNorWave")
extern CString g_sLangTxt_Replay_InsertWave;              //_T("���벨��")
extern CString g_sLangID_Replay_InsertWave;               //_T("Replay_InsertWave")
extern CString g_sLangTxt_Replay_InsertWaveParams;        //_T("���벨�β���:")
extern CString g_sLangID_Replay_InsertWaveParams;         //_T("Replay_InsertWaveParams")
extern CString g_sLangTxt_Replay_Time;                    //_T("ʱ��")
extern CString g_sLangID_Replay_Time;                     //_T("Replay_Time")
extern CString g_sLangTxt_Replay_PointNumber;             //_T("���")
extern CString g_sLangID_Replay_PointNumber;             //_T("Replay_PointNumber")
extern CString g_sLangTxt_Replay_StartPointNumber;       //_T("��ʼ���:")
extern CString g_sLangID_Replay_StartPointNumber;        //_T("Replay_StartPointNumber")
extern CString g_sLangTxt_Replay_EndPointNumber;         //_T("��ֹ���:")
extern CString g_sLangID_Replay_EndPointNumber;          //_T("Replay_EndPointNumber")
extern CString g_sLangTxt_Replay_StartTime;               //_T("��ʼʱ�̣�s��:")
extern CString g_sLangID_Replay_StartTime;                //_T("Replay_StartTime")
extern CString g_sLangTxt_Replay_EndTime;                 //_T("��ֹʱ�̣�s��:")
extern CString g_sLangID_Replay_EndTime;                  //_T("Replay_EndTime")
extern CString g_sLangTxt_Replay_NumCycles;               //_T("ѭ������:")
extern CString g_sLangID_Replay_NumCycles;                //_T("Replay_NumCycles")
extern CString g_sLangTxt_Replay_Voltage;                 //_T("��ѹ��V��:")
extern CString g_sLangID_Replay_Voltage;                  //_T("Replay_Voltage")
extern CString g_sLangTxt_Replay_Current;                 //_T("������A��:")
extern CString g_sLangID_Replay_Current;                  //_T("Replay_Current")
extern CString g_sLangTxt_Replay_OutputTime;              //_T("���ʱ�䣨s��:")
extern CString g_sLangID_Replay_OutputTime;               //_T("Replay_OutputTime")
extern CString g_sLangTxt_Replay_DeleteWave;              //_T("ɾ������")
extern CString g_sLangID_Replay_DeleteWave;               //_T("Replay_DeleteWave")
extern CString g_sLangTxt_Replay_WaveReset;               //_T("���θ���")
extern CString g_sLangID_Replay_WaveReset;                //_T("Replay_WaveReset")
extern CString g_sLangTxt_Replay_Delete;                  //_T("ɾ��")
extern CString g_sLangID_Replay_Delete;                   //_T("Replay_Delete")
extern CString g_sLangTxt_Replay_Insert;                  //_T("����")
extern CString g_sLangID_Replay_Insert;                   //_T("Replay_Insert")
extern CString g_sLangTxt_Replay_Model;						//_T("ģ")
extern CString g_sLangID_Replay_Model;						//_T("Replay_Model")
extern CString g_sLangTxt_Replay_Weak;						//_T("��")
extern CString g_sLangID_Replay_Weak;						//_T("Replay_Weak")

extern CString g_sLangID_Native_ConnectingAtsTester;
extern CString g_sLangTxt_Native_ConnectingAtsTester;
extern CString g_sLangID_Native_TesterConnectAtsSucc;
extern CString g_sLangTxt_Native_TesterConnectAtsSucc;
extern CString g_sLangID_Native_TesterConnectAtsfail;
extern CString g_sLangTxt_Native_TesterConnectAtsfail;

//zhangyq 2024.7.23 �Զ�׼ͬ��ͨ�ò����е�ѹ����
extern CString g_sLangID_Syn_UDefineOne;                   //_T("Syn_UDefineOne")
extern CString g_sLangTxt_Syn_UDefineOne;                  //_T("ϵͳ->Ua1,����->Ub1")
extern CString g_sLangID_Syn_UDefineTwo;                   //_T("Syn_UDefineTwo")
extern CString g_sLangTxt_Syn_UDefineTwo;                  //_T("ϵͳ->Ua1,����->Ubc1")
extern CString g_sLangID_Syn_UDefineThree;                   //_T("Syn_UDefineThree")
extern CString g_sLangTxt_Syn_UDefineThree;                  //_T("ϵͳ->Ua2/Uz,����->Uabc1")
extern CString g_sLangID_Syn_UDefineFour;                   //_T("Syn_UDefineFour")
extern CString g_sLangTxt_Syn_UDefineFour;                  //_T("ϵͳ->Uabc1,����->Uabc2")
//zhangyq 2024.7.24 �Զ�׼ͬ�ڿ����������п�����
extern CString g_sLangID_Syn_Pulse;                   //_T("Syn_Pulse")
extern CString g_sLangTxt_Syn_Pulse;                    //_T("����")
extern CString g_sLangID_Syn_Continuous;                   //_T("Syn_Continuous")
extern CString g_sLangTxt_Syn_Continuous;                    //_T("����")
//gongyiping 2024.9.30 �Զ�׼ͬ�ڿ����������п���������
//extern CString g_sLangID_Syn_State;                   //_T("Syn_State")
//extern CString g_sLangTxt_Syn_State;                    //_T("״̬")
extern CString g_sLangID_Syn_Mode;                   //_T("Syn_Mode")
extern CString g_sLangTxt_Syn_Mode;                    //_T("�����ʽ")
//gongyiping 2024.10.24 �Զ�׼ͬ�ڲ���
extern CString g_sLangID_Syn_ProOutSignals;			// _T("Syn_ProOutSignals");
extern CString g_sLangTxt_Syn_ProOutSignals;			//_T("���������ź�");
extern CString g_sLangID_Syn_IncFSignals;			// _T("Syn_IncFSignals");
extern CString g_sLangTxt_Syn_IncFSignals;			// _T("�����ź�");
extern CString g_sLangID_Syn_DecFSignals;			// _T("Syn_DecFSignals");
extern CString g_sLangTxt_Syn_DecFSignals;			// _T("�����ź�");
extern CString g_sLangID_Sys_PointNum;			// _T("Sys_PointNum");
extern CString g_sLangTxt_Sys_PointNum;			// _T("�ӵ���:");
extern CString g_sLangID_Sys_PhaseDiff;			// _T("Sys_PhaseDiff");
extern CString g_sLangTxt_Sys_PhaseDiff;			// _T("������λ��(��):");
//gongyiping 2024.10.24 ��ѹ��ʱ��
extern CString g_sLangID_Vol_TestPointsAdd;					// _T("Vol_TestPointsAdd");
extern CString g_sLangTxt_Vol_TestPointsAdd;					//  _T("���Ե����");
extern CString g_sLangID_Vol_FaultTypeSelect;					// _T("Vol_FaultTypeSelect");
extern CString g_sLangTxt_Vol_FaultTypeSelect;					//  _T("�������ѡ��");
extern CString g_sLangID_Vol_FaultOutput;					// _T("Vol_FaultOutput");
extern CString g_sLangTxt_Vol_FaultOutput;					//  _T("����̬���");
//20241024 gongyiping ������ʱ��
extern CString g_sLangID_Curr_FaultBeforeOutput;				// _T("Vol_FaultBeforeOutput");
extern CString g_sLangTxt_Curr_FaultBeforeOutput;				// _T("����ǰ���");
//zhangyq 2024.7.25 ����ģ��
extern CString g_sLangID_Native_LangTip                 ;//= _T("Native_LangTip");
extern CString g_sLangTxt_Native_LangTip                ;//= _T("��ʾ");
extern CString g_sLangID_Native_FileSaveSuccess             ;//= _T("Native_FileSaveSuccess");
extern CString g_sLangTxt_Native_FileSaveSuccess;//= _T("�ļ�����ɹ���");
extern CString g_sLangID_Native_AckFileSave;//= _T("Native_AckFileSave");
extern CString g_sLangTxt_Native_AckFileSave;//= _T("��ȷ�ϵ�ǰ�����Ƿ񱣴棡");
extern CString g_sLangID_Native_ExportWordDoc             ;//= _T("Native_ExportWordDoc");
extern CString g_sLangTxt_Native_ExportWordDoc            ;//= _T("����word�ļ�");
extern CString g_sLangID_Native_DocType             ;//= _T("Native_DocType");
extern CString g_sLangTxt_Native_DocType            ;//= _T("Word97-2003����(*.doc);;Word����(*.docx);;HTML����(*.html);;PDF����(*.pdf)");
extern CString g_sLangID_Iec_StartRcd;                   //_T("Iec_StartRcd")
extern CString g_sLangTxt_Iec_StartRcd;                    //_T("������Ӻ󣬿�ʼ¼��")
//wangsen 2024.8.1 Xrio��ֵ�����޸�
//����ʰ汣��һ�� �Ƶ�XLanguageResourceAts��
//extern CString g_sLangID_Xrio_EnterNumbers;                 //=_T("Xrio_EnterNumbers");
//extern CString g_sLangTxt_Xrio_EnterNumbers;                //=_T("������һ�����֡�");

extern CString g_sLangID_Xrio_XrioError;                    //=_T("Xrio_XrioError");
extern CString g_sLangTxt_Xrio_XrioError;                   //=_T("XRIO����");

//extern CString g_sLangID_Xrio_ValueLessThanOREqual;         //=_T("Xrio_ValueLessThanOREqual");
//extern CString g_sLangTxt_Xrio_ValueLessThanOREqual;        //=_T("ֵ���� <= ");

//extern CString g_sLangID_Xrio_ValueGreaterThanOREqual;      //=_T("Xrio_ValueGreaterThanOREqual");
//extern CString g_sLangTxt_Xrio_ValueGreaterThanOREqual;     //=_T("ֵ���� >= ");
//wangsen 2024.8.7 Xrioװ�ö�ֵ
extern CString g_sLangID_Xrio_DeviceSetting;                //=_T("Xrio_DeviceSetting");
extern CString g_sLangTxt_Xrio_DeviceSetting;               //=_T("װ�ö�ֵ")

//zhangyq 2024.8.20 ͨ���迹�������
extern CString g_sLangTxt_Native_ActTimeValueAbsErrNeg;//����ʱ��ֵ������
extern CString g_sLangID_Native_ActTimeValueAbsErrNeg;

//2024-8-14 wuxinyi
extern CString  g_sLangID_ReplayTest_InsertWaveTip;		//=_T("ReplayTest_InsertWaveTip")
extern CString  g_sLangTxt_ReplayTest_InsertWaveTip;		//=_T("���������µĲ���,���Ե�....")
extern CString  g_sLangID_ReplayTest_RecoverWaveTip;		//=_T("ReplayTest_RecoverWaveTip")
extern CString  g_sLangTxt_ReplayTest_RecoverWaveTip;		//=_T("�������ڸ��飬���Ե�....")
extern CString  g_sLangID_ReplayTest_LeftMove;		//=_T("ReplayTest_LeftMove")
extern CString  g_sLangTxt_ReplayTest_LeftMove;		//=_T("����")
extern CString  g_sLangID_ReplayTest_RightMove;		//=_T("ReplayTest_RightMove")
extern CString  g_sLangTxt_ReplayTest_RightMove;		//=_T("����")
extern CString  g_sLangID_ReplayTest_Cursor;		//=_T("ReplayTest_Cursor")
extern CString  g_sLangTxt_ReplayTest_Cursor;		//=_T("���")
extern CString  g_sLangID_ReplayTest_TimeDiffer;		//=_T("ReplayTest_TimeDiffer")
extern CString  g_sLangTxt_ReplayTest_TimeDiffer;		//=_T("ʱ��")
extern CString  g_sLangID_ReplayTest_PointDiffer;		//=_T("ReplayTest_PointDiffer")
extern CString  g_sLangTxt_ReplayTest_PointDiffer;		//=_T("���")

//wangsen 2024.8.26 Xrioװ�ý�������
extern CString g_sLangID_Xrio_InvalidInput;                 //= _T("Xrio_InvalidInput")
extern CString g_sLangTxt_Xrio_InvalidInput;                //= _T("��Ч����")

extern CString g_sLangID_Xrio_InputRestrictionTypeOne;      //= _T("Xrio_InputRestrictionTypeOne")
extern CString g_sLangTxt_Xrio_InputRestrictionTypeOne;     //= _T("��������Ǵ��ڻ����0�����֡�")

extern CString g_sLangID_Xrio_InputRestrictionTypeTwo;      //= _T("Xrio_InputRestrictionTypeTwo")
extern CString g_sLangTxt_Xrio_InputRestrictionTypeTwo;     //= _T("���������0��800֮���ֵ��")

extern CString g_sLangID_Xrio_InputRestrictionTypeThree;    //= _T("Xrio_InputRestrictionTypeThree")
extern CString g_sLangTxt_Xrio_InputRestrictionTypeThree;   //= _T("���������0.00��0.025֮���ֵ��")


extern CString  g_sLangID_ReplayTest_DeleteTimeError;		//=_T("ReplayTest_DeleteTimeError");
extern CString  g_sLangTxt_ReplayTest_DeleteTimeError;		//_T("ɾ����㲻��С�ڻ�����յ㣬����������!");
extern CString  g_sLangID_ReplayTest_InsertBeginTimeError;		//=_T("ReplayTest_InsertBeginTimeError");
extern CString  g_sLangTxt_ReplayTest_InsertBeginTimeError;		//_T("������㲻��С�ڻ������ֹ��ţ�����������!");
extern CString  g_sLangID_ReplayTest_InsertBeginPointError;		//=_T("ReplayTest_InsertBeginTimeError");
extern CString  g_sLangTxt_ReplayTest_InsertBeginPointError;		//_T("������ʼ��Ų���С�ڻ������ֹ��ţ�����������!");

//20240905 huangliang
extern CString g_sLangID_MappingRelation_Maps_CHName;
extern CString g_sLangTxt_MappingRelation_Maps_CHName; //_T("��ѹ����")
extern CString g_sLangID_MappingRelation_Maps_BinName;
extern CString g_sLangTxt_MappingRelation_Maps_BinName; //_T("����������")
extern CString g_sLangID_MappingRelation_Maps_BoutName;
extern CString g_sLangTxt_MappingRelation_Maps_BoutName; //_T("���������")

extern CString g_sLangID_MappingRelation_Maps_TitleID;
extern CString g_sLangTxt_MappingRelation_Maps_TitleID; //_T("������ͨ��")
extern CString g_sLangID_MappingRelation_Maps_TitleName;
extern CString g_sLangTxt_MappingRelation_Maps_TitleName; //_T("��ʾ����")


//20240919 wangsen
extern CString g_sLangID_Xrio_SettingFile;                  //= _T("Xrio_SettingFile")
extern CString g_sLangTxt_Xrio_SettingFile;                 //= _T("��ֵ�ļ�")

extern CString g_sLangID_Xrio_ImportRefs;                   //= _T("Xrio_ImportRefs")
extern CString g_sLangTxt_Xrio_ImportRefs;                  //= _T("����ֵ�ѵ��롣")

//xueyf 2024.9.26
extern CString g_sLangID_RecloseAcc_InspectLineNoStrain;       //= _T("RecloseAcc_InspectLineNoStrain")
extern CString g_sLangTxt_RecloseAcc_InspectLineNoStrain;      //= _T("������ѹĸ��ѹ")
extern CString  g_sLangID_RecloseAcc_InspectLineStrain;		//=_T("RecloseAcc_InspectLineStrain");
extern CString  g_sLangTxt_RecloseAcc_InspectLineStrain;		//_T("������ѹĸ��ѹ");
extern CString  g_sLangID_RecloseAcc_InspectLineNoPressure;	//=_T("RecloseAcc_InspectLineNoPressure");
extern CString  g_sLangTxt_RecloseAcc_InspectLineNoPressure;	//_T("������ѹĸ��ѹ");
extern CString  g_sLangID_RecloseAcc_InspectLinePressure;		//=_T("RecloseAcc_InspectLinePressure");
extern CString  g_sLangTxt_RecloseAcc_InspectLinePressure;		//_T("������ѹĸ��ѹ");
extern CString  g_sLangID_RecloseAcc_InspectNoOutput;			//=_T("RecloseAcc_InspectNoOutput");
extern CString  g_sLangTxt_RecloseAcc_InspectNoOutput;			//_T("�����");
extern CString g_sLangID_RecloseAcc_NoAct;       //= _T("RecloseAcc_NoAct")
extern CString g_sLangTxt_RecloseAcc_NoAct;      //= _T("������")

//20241024 wanmj
extern CString g_sLangID_RecloseAcc_Z;       //= _T("RecloseAcc_Z")
extern CString g_sLangTxt_RecloseAcc_Z;      //= _T("�迹(��):")
extern CString g_sLangID_RecloseAcc_R;       //= _T("RecloseAcc_R")
extern CString g_sLangTxt_RecloseAcc_R;      //= _T("R(��):")
extern CString g_sLangID_RecloseAcc_X;       //= _T("RecloseAcc_X")
extern CString g_sLangTxt_RecloseAcc_X;      //= _T("X(��):")
extern CString g_sLangID_RecloseAcc_Fre;       //= _T("RecloseAcc_Fre")
extern CString g_sLangTxt_RecloseAcc_Fre;      //= _T("Ƶ��(Hz):")
extern CString g_sLangID_RecloseAcc_RecloseTime;       //= _T("RecloseAcc_RecloseTime")
extern CString g_sLangTxt_RecloseAcc_RecloseTime;      //= _T("�غ�ʱ��(s):")
extern CString g_sLangID_RecloseAcc_RecloseMode;       //= _T("RecloseAcc_RecloseMode")
extern CString g_sLangTxt_RecloseAcc_RecloseMode;      //= _T("��������:")
extern CString g_sLangID_RecloseAcc_UxMode;       //= _T("RecloseAcc_UxMode")
extern CString g_sLangTxt_RecloseAcc_UxMode;      //= _T("��ȡ��ѹѡ��:")
extern CString g_sLangID_RecloseAcc_UxInputFre;       //= _T("RecloseAcc_UxInputFre")
extern CString g_sLangTxt_RecloseAcc_UxInputFre;      //= _T("��ȡ��ѹƵ��(Hz):")
extern CString g_sLangID_RecloseAcc_UxInputMag;       //= _T("RecloseAcc_UxInputMag")
extern CString g_sLangTxt_RecloseAcc_UxInputMag;      //= _T("��բ���ȡ��ѹ(V):")
extern CString g_sLangID_RecloseAcc_UxInputAng;       //= _T("RecloseAcc_UxInputAng")
extern CString g_sLangTxt_RecloseAcc_UxInputAng;      //= _T("��բ���ȡ��ѹ��λ(��):")
extern CString g_sLangID_RecloseAcc_Input;       //= _T("RecloseAcc_Input")
extern CString g_sLangTxt_RecloseAcc_Input;      //= _T("�������")
extern CString g_sLangID_RecloseAcc_Output;       //= _T("RecloseAcc_Output")
extern CString g_sLangTxt_RecloseAcc_Output;      //= _T("��������")
extern CString g_sLangID_RecloseAcc_BinSelect;       //= _T("RecloseAcc_BinSelect")
extern CString g_sLangTxt_RecloseAcc_BinSelect;      //= _T("����ѡ��:")
extern CString g_sLangID_RecloseAcc_OutputSwitchMode;       //= _T("RecloseAcc_OutputSwitchMode")
extern CString g_sLangTxt_RecloseAcc_OutputSwitchMode;      //= _T("������ת������ʽ:")
extern CString g_sLangID_RecloseAcc_OutputKeepTime;       //= _T("RecloseAcc_OutputKeepTime")
extern CString g_sLangTxt_RecloseAcc_OutputKeepTime;      //= _T("��������ʱ��(s):")
extern CString g_sLangID_RecloseAcc_OutputDelayTime;       //= _T("RecloseAcc_OutputDelayTime")
extern CString g_sLangTxt_RecloseAcc_OutputDelayTime;      //= _T("������תʱ��(s):")
extern CString g_sLangID_RecloseAcc_FaultTrigMode;       //= _T("RecloseAcc_FaultTrigMode")
extern CString g_sLangTxt_RecloseAcc_FaultTrigMode;      //= _T("���ϴ�����ʽ:")

extern CString g_sLangID_RecloseAcc_NoPre;       //= _T("RecloseAcc_NoPre")
extern CString g_sLangTxt_RecloseAcc_NoPre;      //= _T("����ѹ����:")
extern CString g_sLangID_RecloseAcc_SamPer;       //= _T("RecloseAcc_SamPer")
extern CString g_sLangTxt_RecloseAcc_SamPer;      //= _T("��ͬ�ڲ���")
extern CString g_sLangID_RecloseAcc_Frequency;       //= _T("RecloseAcc_Frequency")
extern CString g_sLangTxt_RecloseAcc_Frequency;      //= _T("��Ƶ�ʲ���")
extern CString g_sLangID_RecloseAcc_AutoReclose;       //= _T("RecloseAcc_AutoReclose")
extern CString g_sLangTxt_RecloseAcc_AutoReclose;      //= _T("�Զ��غ�բ")
extern CString g_sLangID_RecloseAcc_AftAcc;       //= _T("RecloseAcc_AftAcc")
extern CString g_sLangTxt_RecloseAcc_AftAcc;      //= _T("����ٲ���:")
extern CString g_sLangID_RecloseAcc_NoPreSet;       //= _T("RecloseAcc_NoPreSet")
extern CString g_sLangTxt_RecloseAcc_NoPreSet;      //= _T("��ѹ��ֵ(V):")
extern CString g_sLangID_RecloseAcc_SynAngle;       //= _T("RecloseAcc_SynAngle")
extern CString g_sLangTxt_RecloseAcc_SynAngle;      //= _T("��բ�Ƕ�(��):")
extern CString g_sLangID_RecloseAcc_K0Mode;       //= _T("RecloseAcc_K0Mode")
extern CString g_sLangTxt_RecloseAcc_K0Mode;      //= _T("��﷽ʽ:")

extern CString g_sLangID_RecloseAcc_TripTime;       //= _T("RecloseAcc_TripTime")
extern CString g_sLangTxt_RecloseAcc_TripTime;      //= _T("��բʱ��(s)")
extern CString g_sLangID_RecloseAcc_TtripD;       //= _T("RecloseAcc_TtripD")
extern CString g_sLangTxt_RecloseAcc_TtripD;      //= _T("�غ�ʱ��(s)")
extern CString g_sLangID_RecloseAcc_TtripAcc;       //= _T("RecloseAcc_TtripAcc")
extern CString g_sLangTxt_RecloseAcc_TtripAcc;      //= _T("�����ʱ��(s)")
extern CString g_sLangID_RecloseAcc_Title_UxInputMag;       //= _T("RecloseAcc_Title_UxInputMag")
extern CString g_sLangTxt_RecloseAcc_Title_UxInputMag;      //= _T("��ȡ��ѹ(V)")
extern CString g_sLangID_RecloseAcc_Title_UxInputAng;       //= _T("RecloseAcc_Title_UxInputAng")
extern CString g_sLangTxt_RecloseAcc_Title_UxInputAng;      //= _T("��ȡ��ѹ��λ(��)")
extern CString g_sLangID_RecloseAcc_Title_VZFreq;       //= _T("RecloseAcc_Title_VZFreq")
extern CString g_sLangTxt_RecloseAcc_Title_VZFreq;      //= _T("��ȡ��ѹƵ��(Hz)")

//xueyf 2024.9.29
extern CString  g_sLangID_BinRecord_Channel;			//=_T("BinRecord_Channel");
extern CString  g_sLangTxt_BinRecord_Channel;			//_T("¼��ͨ��");
extern CString  g_sLangID_BinRecord_RecordType;			//=_T("BinRecord_RecordType");
extern CString  g_sLangTxt_BinRecord_RecordType;			//_T("��¼����");
extern CString  g_sLangID_BinRecord_ClampRate;			//=_T("BinRecord_ClampRate");
extern CString  g_sLangTxt_BinRecord_ClampRate;			//_T("��ǯ����");
extern CString  g_sLangID_BinRecord_Invalid;			//=_T("BinRecord_Invalid");
extern CString  g_sLangTxt_BinRecord_Invalid;			//_T("��Ч");
extern CString  g_sLangID_BinRecord_BinPassive;			//=_T("BinRecord_BinPassive");
extern CString  g_sLangTxt_BinRecord_BinPassive;			//_T("������(��Դ)");
extern CString  g_sLangID_BinRecord_BinActive;			//=_T("BinRecord_BinActive");
extern CString  g_sLangTxt_BinRecord_BinActive;			//_T("������(��Դ)");
extern CString  g_sLangID_BinRecord_PlugName;			//=_T("BinRecord_PlugName");
extern CString  g_sLangTxt_BinRecord_PlugName;			//_T("�������");
extern CString  g_sLangID_BinRecord_PlugPOS;			//=_T("BinRecord_PlugPOS");
extern CString  g_sLangTxt_BinRecord_PlugPOS;			//_T("���λ��");
extern CString  g_sLangID_BinRecord_ChannelNum;			//=_T("BinRecord_ChannelNum");
extern CString  g_sLangTxt_BinRecord_ChannelNum;			//_T("ͨ������");
extern CString  g_sLangID_BinRecord_PrimValue;			//=_T("BinRecord_PrimValue");
extern CString  g_sLangTxt_BinRecord_PrimValue;			//_T("һ�β�");
extern CString  g_sLangID_BinRecord_SecondValue;			//=_T("BinRecord_SecondValue");
extern CString  g_sLangTxt_BinRecord_SecondValue;			//_T("���β�");
extern CString  g_sLangID_BinRecord_StartRecord;			//=_T("BinRecord_StartRecord");
extern CString  g_sLangTxt_BinRecord_StartRecord;			//_T("����¼��");
extern CString  g_sLangID_BinRecord_StopRecord;			//=_T("BinRecord_StopRecord");
extern CString  g_sLangTxt_BinRecord_StopRecord;			//_T("ֹͣ¼��");
extern CString  g_sLangID_BinRecord_Module;			//=_T("BinRecord_Module");
extern CString  g_sLangTxt_BinRecord_Module;			//_T("����");
extern CString  g_sLangID_BinRecord_SaveDefaultCfg;			//=_T("BinRecord_SaveDefaultCfg");
extern CString  g_sLangTxt_BinRecord_SaveDefaultCfg;			//_T("�Ƿ񱣴�ΪĬ������");
extern CString  g_sLangID_BinRecord_SelFile;			//=_T("BinRecord_SelFile");
extern CString  g_sLangTxt_BinRecord_SelFile;			//_T("ѡ���ļ�");
extern CString  g_sLangID_BinRecord_ArrangeTop;			//=_T("BinRecord_ArrangeTop");
extern CString  g_sLangTxt_BinRecord_ArrangeTop;			//_T("��������ǰ");
extern CString  g_sLangID_BinRecord_ArrangeLast;			//=_T("BinRecord_ArrangeLast");
extern CString  g_sLangTxt_BinRecord_ArrangeLast;			//_T("���������");

//20240927 wangsen
extern CString g_sLangID_Xrio_InvalidName;                  //= _T("Xrio_InvalidName")
extern CString g_sLangTxt_Xrio_InvalidName;                 //= _T("��Ч��������Ϊ�գ�")

//20241010 wangsen
//extern CString g_sLangID_Xrio_InvalidDoublePrecisionValue;  //= _T("Xrio_InvalidDoublePrecisionValue")
//extern CString g_sLangTxt_Xrio_InvalidDoublePrecisionValue; //= _T("��Ч��˫����ֵ��")

//extern CString g_sLangID_Xrio_InvalidIntValue;              //= _T("Xrio_InvalidIntValue")
//extern CString g_sLangTxt_Xrio_InvalidIntValue;             //= _T("��Ч������ֵ��")

//20241020 wangsen
extern CString g_sLangID_Xrio_TestObject;                   //= _T("Xrio_TestObject")
extern CString g_sLangTxt_Xrio_TestObject;                  //= _T("���Զ���")
extern CString g_sLangID_Xrio_Update;                       //= _T("Xrio_Update")
extern CString g_sLangTxt_Xrio_Update;                      //= _T("����")

extern CString g_sLangID_Xrio_Foreignid;                    //= _T("Xrio_Foreignid")
extern CString g_sLangTxt_Xrio_Foreignid;                   //= _T("�����")
extern CString g_sLangID_Xrio_RefValue;                     //= _T("Xrio_RefValue")
extern CString g_sLangTxt_Xrio_RefValue;                    //= _T("�ο�ֵ")
extern CString g_sLangID_Xrio_ValueFormula;                 //= _T("Xrio_ValueFormula")
extern CString g_sLangTxt_Xrio_ValueFormula;                //= _T("��ʽ")

extern CString g_sLangID_Xrio_DeviceAttr_Name_Description;  //= _T("Xrio_DeviceAttr_Name_Description")
extern CString g_sLangTxt_Xrio_DeviceAttr_Name_Description; //= _T("����/˵��")
extern CString g_sLangID_Xrio_DeviceAttr_Manufacturer;      //= _T("Xrio_DeviceAttr_Manufacturer")
extern CString g_sLangTxt_Xrio_DeviceAttr_Manufacturer;     //= _T("���쳧��")
extern CString g_sLangID_Xrio_DeviceAttr_DeviceType;        //= _T("Xrio_DeviceAttr_DeviceType")
extern CString g_sLangTxt_Xrio_DeviceAttr_DeviceType;       //= _T("װ������")
extern CString g_sLangID_Xrio_DeviceAttr_SerialNumber;      //= _T("Xrio_DeviceAttr_SerialNumber")
extern CString g_sLangTxt_Xrio_DeviceAttr_SerialNumber;     //= _T("���к�/�ͺ�")
extern CString g_sLangID_Xrio_DeviceAttr_AdditionalInformationOne;   //= _T("Xrio_DeviceAttr_AdditionalInformationOne")
extern CString g_sLangTxt_Xrio_DeviceAttr_AdditionalInformationOne;  //= _T("������Ϣ1")
extern CString g_sLangID_Xrio_DeviceAttr_AdditionalInformationTwo;   //= _T("Xrio_DeviceAttr_AdditionalInformationTwo")
extern CString g_sLangTxt_Xrio_DeviceAttr_AdditionalInformationTwo;  //= _T("������Ϣ2")

extern CString g_sLangID_Xrio_DeviceAttr_TransformerSubstation;      //= _T("Xrio_DeviceAttr_TransformerSubstation")
extern CString g_sLangTxt_Xrio_DeviceAttr_TransformerSubstation;     //= _T("���վ")
extern CString g_sLangID_Xrio_DeviceAttr_NumberOfPhases;    //= _T("Xrio_DeviceAttr_NumberOfPhases")
extern CString g_sLangTxt_Xrio_DeviceAttr_NumberOfPhases;   //= _T("����")

extern CString g_sLangID_Xrio_DeviceAttr_ZSVAndZSC;         //= _T("Xrio_DeviceAttr_ZSVAndZSC")
extern CString g_sLangTxt_Xrio_DeviceAttr_ZSVAndZSC;        //= _T("�����ѹ�͵���")
extern CString g_sLangID_Xrio_DeviceAttr_ZSVDirection;      //= _T("Xrio_DeviceAttr_ZSVDirection")
extern CString g_sLangTxt_Xrio_DeviceAttr_ZSVDirection;     //= _T("�����ѹ�ķ���")
extern CString g_sLangID_Xrio_DeviceAttr_ZSCDirection;      //= _T("Xrio_DeviceAttr_ZSCDirection")
extern CString g_sLangTxt_Xrio_DeviceAttr_ZSCDirection;     //= _T("��������ķ���")
extern CString g_sLangID_Xrio_DeviceAttr_UseOfMutualInductor;       //= _T("Xrio_DeviceAttr_UseOfMutualInductor")
extern CString g_sLangTxt_Xrio_DeviceAttr_UseOfMutualInductor;      //= _T("ʹ�û�����")

extern CString g_sLangID_Xrio_DeviceAttr_OtherDeviceProperties;     //= _T("Xrio_DeviceAttr_OtherDeviceProperties")
extern CString g_sLangTxt_Xrio_DeviceAttr_OtherDeviceProperties;    //= _T("����װ������")

extern CString g_sLangID_Xrio_DeviceAttr_MaxValueSetting;   //= _T("Xrio_DeviceAttr_MaxValueSetting")
extern CString g_sLangTxt_Xrio_DeviceAttr_MaxValueSetting;  //= _T("���ֵ����")

extern CString g_sLangID_Xrio_DeviceAttr_OvDetSens;         //= _T("Xrio_DeviceAttr_OvDetSens")
extern CString g_sLangTxt_Xrio_DeviceAttr_OvDetSens;        //= _T("���ؼ��������")

extern CString g_sLangID_Xrio_DeviceAttr_Damping;           //= _T("Xrio_DeviceAttr_Damping")
extern CString g_sLangTxt_Xrio_DeviceAttr_Damping;          //= _T("����/�������")
extern CString g_sLangID_Xrio_DeviceAttr_BroadeningTime;    //= _T("Xrio_DeviceAttr_BroadeningTime")
extern CString g_sLangTxt_Xrio_DeviceAttr_BroadeningTime;   //= _T("չ��ʱ��")

//20241022 wangsen
extern CString g_sLangID_Xrio_LogInfo_UpdateFile;           //= _T("Xrio_LogInfo_UpdateFile")
extern CString g_sLangTxt_Xrio_LogInfo_UpdateFile;          //= _T("�����ļ�")
extern CString g_sLangID_Gradient_kVActionValue;
extern CString g_sLangTxt_Gradient_kVActionValue;
//��Сֱ������Ϊ48V��ǿ������Ϊ48V
extern  CString g_sLangID_State_MsgText48V;  
extern  CString g_sLangTxt_State_MsgText48V;
//���ֱ������Ϊ264V��ǿ������Ϊ264V
extern  CString g_sLangID_State_MsgText264V;  
extern  CString g_sLangTxt_State_MsgText264V;

//2024-10-23 xueyangfan
extern CString g_sLangID_Native_Protection_CodeValue;		//= _T("Native_Protection_CodeValue")
extern CString g_sLangTxt_Native_Protection_CodeValue;		 //= _T("������ֵ")
extern CString g_sLangID_Native_Measure_CodeValue;			 //= _T("Native_Measure_CodeValue")
extern CString g_sLangTxt_Native_Measure_CodeValue;		//= _T("������ֵ")
extern CString g_sLangID_Native_SecondaryCur;		//= _T("Native_SecondaryCur")
extern CString g_sLangTxt_Native_SecondaryCur;		//= _T("���ζ����")
extern CString g_sLangID_Native_CodeValue_Corrspondence;    //= _T("Native_CodeValue_Corrspondence")
extern CString g_sLangTxt_Native_CodeValue_Corrspondence;   //= _T("��ֵ��Ӧ��ϵ")

extern CString g_sLangID_Native_OpticalPort_Occupation;    //= _T("OpticalPort_Occupation")
extern CString g_sLangTxt_Native_OpticalPort_Occupation;   //= _T("�����ȫ��ռ�ã���ǰ�޿�ѡ��Ĺ�ڣ�")

// extern CString g_sLangID_Native_ZeroDriftTest;
// extern CString g_sLangTxt_Native_ZeroDriftTest;
// extern CString g_sLangID_Native_TimeTest;
// extern CString g_sLangTxt_Native_TimeTest;
// extern CString g_sLangID_Native_TimingAccuracy;
// extern CString g_sLangTxt_Native_TimingAccuracy;
// extern CString g_sLangID_Native_TimeKeepingAccuracy;
// extern CString g_sLangTxt_Native_TimeKeepingAccuracy;
extern CString g_sLangID_Native_330ReplayAnalogError;
extern CString g_sLangTxt_Native_330ReplayAnalogError;

//�Ѻϲ��������,���ֶ�������������.
extern  CString g_sLangID_MergeOutPutI;  
extern  CString g_sLangTxt_MergeOutPutI;
//���ζ����(A)
extern  CString g_sLangID_IEC_SecondRatedType;  
extern  CString g_sLangTxt_IEC_SecondRatedType;
//������ֵ
// extern  CString g_sLangID_IEC_ProtCodeValue;  
// extern  CString g_sLangTxt_IEC_ProtCodeValue;
// //������ֵ
// extern  CString g_sLangID_IEC_MeasCodeValue;  
// extern  CString g_sLangTxt_IEC_MeasCodeValue;
//���ζ��ѹ(V)
extern  CString g_sLangID_IEC_SecondRatedCur;  
extern  CString g_sLangTxt_IEC_SecondRatedCur;


extern CString g_sLangID_DiffCBOp_AddOneItme;				//= _T("DiffCBOp_AddOneItme")
extern CString g_sLangTxt_DiffCBOp_AddOneItme;				//= _T("��ӵ���")
extern CString g_sLangID_DiffCBOp_FaultLocation;				//= _T("DiffCBOp_FaultLocation")
extern CString g_sLangTxt_DiffCBOp_FaultLocation;				//= _T("���ϵ�λ��");
extern CString g_sLangID_DiffCBOp_ComBineFeature;				//= _T("DiffCBOp_ComBineFeature")
extern CString g_sLangTxt_DiffCBOp_ComBineFeature;				//= _T("��������")
extern CString g_sLangID_DiffCBOp_ZeroSeqElimiType;				//= _T("DiffCBOp_ZeroSeqElimiType")
extern CString g_sLangTxt_DiffCBOp_ZeroSeqElimiType;				//= _T("����������ʽ")
extern CString g_sLangID_DiffCBOp_Earthing;				//= _T("DiffCBOp_Earthing")
extern CString g_sLangTxt_DiffCBOp_Earthing;				//= _T("���Ե�ӵ�")
extern CString g_sLangID_DiffCBOp_Coordinate;				//= _T("DiffCBOp_Coordinate")
extern CString g_sLangTxt_DiffCBOp_Coordinate;				//= _T("����")
extern CString g_sLangID_DiffCBOp_TransfHvKph;				//= _T("DiffCBOp_TransfHvKph")
extern CString g_sLangTxt_DiffCBOp_TransfHvKph;				//= _T("��ѹ����ѹ��")
extern CString g_sLangID_DiffCBOp_TransfHvKpm;				//= _T("DiffCBOp_TransfHvKpm")
extern CString g_sLangTxt_DiffCBOp_TransfHvKpm;				//= _T("��ѹ����ѹ��")
extern CString g_sLangID_DiffCBOp_TransfHvKpl;				//= _T("DiffCBOp_TransfHvKpl")
extern CString g_sLangTxt_DiffCBOp_TransfHvKpl;				//= _T("��ѹ����ѹ��")
extern CString g_sLangID_DiffCBOp_TransfRatedCapacity;				//= _T("DiffCBOp_TransfRatedCapacity")
extern CString g_sLangTxt_DiffCBOp_TransfRatedCapacity;				//= _T("�����")
extern CString g_sLangID_DiffCBOp_SetKph;				//= _T("DiffCBOp_SetKph")
extern CString g_sLangTxt_DiffCBOp_SetKph;				//= _T("����ƽ��ϵ��")

extern CString g_sLangID_DiffCBOp_BoutSet;				//= _T("DiffCBOp_BoutSet")
extern CString g_sLangTxt_DiffCBOp_BoutSet;				//= _T("��̬��������")
extern CString g_sLangID_DiffCBOp_FaultBoutSet;				//= _T("DiffCBOp_FaultBoutSet")
extern CString g_sLangTxt_DiffCBOp_FaultBoutSet;				//= _T("����̬��������")
extern CString g_sLangID_DiffCBOp_HSecondCur;				//= _T("DiffCBOp_HSecondCur")
extern CString g_sLangTxt_DiffCBOp_HSecondCur;				//= _T("�߲���ζ����")
// extern CString g_sLangID_DiffCBOp_SetValue;				//= _T("DiffCBOp_SetValue")
// extern CString g_sLangTxt_DiffCBOp_SetValue;				//= _T("�趨ֵ")
// extern CString g_sLangID_DiffCBOp_AllSecondCur;				//= _T("DiffCBOp_AllSecondCur")
// extern CString g_sLangTxt_DiffCBOp_AllSecondCur;				//= _T("������ζ����")
// extern CString g_sLangID_DiffCBOp_FamousValue;				//= _T("DiffCBOp_FamousValue")
// extern CString g_sLangTxt_DiffCBOp_FamousValue;				//= _T("����ֵ")
// extern CString g_sLangID_DiffCBOp_StandardValue;				//= _T("DiffCBOp_StandardValue")
// extern CString g_sLangTxt_DiffCBOp_StandardValue;				//= _T("����ֵ")
extern CString g_sLangID_DiffCBOp_Auxiliary;				//= _T("DiffCBOp_Auxiliary")
extern CString g_sLangTxt_DiffCBOp_Auxiliary;				//= _T("����");

extern CString g_sLangID_DiffCBOp_FauleInH;				//= _T("DiffCBOp_FauleInH")
extern CString g_sLangTxt_DiffCBOp_FauleInH;				//= _T("��ѹ��(����)")
extern CString g_sLangID_DiffCBOp_FauleOutH;				//= _T("DiffCBOp_FauleOutH")
extern CString g_sLangTxt_DiffCBOp_FauleOutH;				//= _T("��ѹ��(����)")
extern CString g_sLangID_DiffCBOp_FauleInL;				//= _T("DiffCBOp_FauleInL")
extern CString g_sLangTxt_DiffCBOp_FauleInL;				//= _T("��ѹ��(����)")
extern CString g_sLangID_DiffCBOp_FauleOutL;				//= _T("DiffCBOp_FauleOutL")
extern CString g_sLangTxt_DiffCBOp_FauleOutL;				//= _T("��ѹ��(����)")
extern CString g_sLangID_DiffCBOp_FauleInM;				//= _T("DiffCBOp_FauleInM")
extern CString g_sLangTxt_DiffCBOp_FauleInM;				//= _T("��ѹ��(����)")
extern CString g_sLangID_DiffCBOp_FauleOutM;				//= _T("DiffCBOp_FauleOutM")
extern CString g_sLangTxt_DiffCBOp_FauleOutM;				//= _T("��ѹ��(����)")


//add wangtao 20241023
extern CString g_sLangID_Diff_RateSearch;            //_T("Diff_RateSearch")
extern CString g_sLangTxt_Diff_RateSearch;            //_T("�����")
extern CString g_sLangID_Diff_FaultTime;            //_T("Diff_FaultTime")
extern CString g_sLangTxt_Diff_FaultTime;            //_T("������ʱ��(s)")
extern CString g_sLangID_Diff_Start;            //_T("Diff_Start")
extern CString g_sLangTxt_Diff_Start;            //_T("����")
extern CString g_sLangID_Diff_IQuick;            //_T("Diff_IQuick")
extern CString g_sLangTxt_Diff_IQuick;            //_T("�ٶ�")
extern CString g_sLangID_Diff_SearchBand;            //_T("Diff_SearchBand")
extern CString g_sLangTxt_Diff_SearchBand;            //_T("������")
extern CString g_sLangID_Diff_RateBeginVal;            //_T("Diff_RateBeginVal")
extern CString g_sLangTxt_Diff_RateBeginVal;            //_T("�ƶ�����ʼֵ")
extern CString g_sLangID_Diff_RateEndVal;            //_T("Diff_RateEndVal")
extern CString g_sLangTxt_Diff_RateEndVal;            //_T("�ƶ�������ֵ")
extern CString g_sLangID_Diff_Step;            //_T("Diff_Step")
extern CString g_sLangTxt_Diff_Step;            //_T("�仯����")
extern CString g_sLangID_Diff_Points;            //_T("Diff_Points")
extern CString g_sLangTxt_Diff_Points;            //_T("���Ե���")
extern CString g_sLangID_Diff_ActAbsErr;            //_T("Diff_ActAbsErr")
extern CString g_sLangTxt_Diff_ActAbsErr;            //_T("����ֵ�������")
extern CString g_sLangID_Diff_ActRelErr;            //_T("Diff_ActRelErr")
extern CString g_sLangTxt_Diff_ActRelErr;            //_T("����ֵ������(%)")
extern CString g_sLangID_Diff_PrepareTime;            //_T("Diff_PrepareTime")
extern CString g_sLangTxt_Diff_PrepareTime;            //_T("׼��ʱ��(s)")
extern CString g_sLangID_Diff_TimeAfter;            //_T("Diff_TimeAfter")
extern CString g_sLangTxt_Diff_TimeAfter;            //_T("�����󱣳�ʱ��(s)")
extern CString g_sLangID_Diff_KPSetMode;            //_T("Diff_KPSetMode")
extern CString g_sLangTxt_Diff_KPSetMode;            //_T("����ƽ��ϵ��")
extern CString g_sLangID_Diff_KphSet;            //_T("Diff_KphSet")
extern CString g_sLangTxt_Diff_KphSet;            //_T("��ѹ��ƽ��ϵ��")
extern CString g_sLangID_Diff_KpmSet;            //_T("Diff_KpmSet")
extern CString g_sLangTxt_Diff_KpmSet;            //_T("��ѹ��ƽ��ϵ��")
extern CString g_sLangID_Diff_KplSet;            //_T("Diff_KplSet")
extern CString g_sLangTxt_Diff_KplSet;            //_T("��ѹ��ƽ��ϵ��")
extern CString g_sLangID_Native_HighVoltWindingConnType;			 //_T("Native_HighVoltWindingConnType")
extern CString g_sLangTxt_Native_HighVoltWindingConnType;		 //_T("��ѹ�����������ʽ")
extern CString g_sLangID_Native_LowVoltWindingConnType;			 //_T("Native_LowVoltWindingConnType")
extern CString g_sLangTxt_Native_LowVoltWindingConnType;		 //_T("��ѹ�����������ʽ")
extern CString g_sLangID_Diff_PhCorrectMode;            //_T("Diff_PhCorrectMode")
extern CString g_sLangTxt_Diff_PhCorrectMode;            //_T("У��ѡ��")
extern CString g_sLangID_Diff_AdoptWind;            //_T("Diff_AdoptWind")
extern CString g_sLangTxt_Diff_AdoptWind;            //_T("��������")
extern CString g_sLangID_Diff_TransGroupModeHM;            //_T("Diff_TransGroupModeHM")
extern CString g_sLangTxt_Diff_TransGroupModeHM;            //_T("��-�������ӵ���")
extern CString g_sLangID_Diff_TransGroupModeHL;            //_T("Diff_TransGroupModeHL")
extern CString g_sLangTxt_Diff_TransGroupModeHL;            //_T("��-�������ӵ���")
extern CString g_sLangID_Diff_JXFactor;            //_T("Diff_JXFactor")
extern CString g_sLangTxt_Diff_JXFactor;            //_T("ƽ��ϵ������")
extern CString g_sLangID_Diff_Earthing;            //_T("Diff_Earthing")
extern CString g_sLangTxt_Diff_Earthing;            //_T("�ӵ�")
extern CString g_sLangID_Diff_FaultType;            //_T("Diff_FaultType")
extern CString g_sLangTxt_Diff_FaultType;            //_T("�������")
extern CString g_sLangID_Diff_CustomHarmIndex;            //_T("Diff_CustomHarmIndex")
extern CString g_sLangTxt_Diff_CustomHarmIndex;            //_T("�Զ���г������")
extern CString g_sLangID_Diff_BeginVal;            //_T("Diff_BeginVal")
extern CString g_sLangTxt_Diff_BeginVal;            //_T("����ʼֵ")
extern CString g_sLangID_Diff_EndVal;            //_T("Diff_EndVal")
extern CString g_sLangTxt_Diff_EndVal;            //_T("������ֵ")
extern CString g_sLangID_Diff_HarmOutSide;            //_T("Diff_HarmOutSide")
extern CString g_sLangTxt_Diff_HarmOutSide;            //_T("г�������")
extern CString g_sLangID_Diff_UpperLimit;            //_T("Diff_UpperLimit")
extern CString g_sLangTxt_Diff_UpperLimit;            //_T("��������")
extern CString g_sLangID_Diff_LowLimit;            //_T("Diff_LowLimit")
extern CString g_sLangTxt_Diff_LowLimit;            //_T("��������")
extern CString g_sLangID_Diff_IdSetting;            //_T("Diff_IdSetting")
extern CString g_sLangTxt_Diff_IdSetting;            //_T("�����ֵ")
extern CString g_sLangID_Diff_SglSideBalCoeff;            //_T("Diff_SglSideBalCoeff")
extern CString g_sLangTxt_Diff_SglSideBalCoeff;            //_T("���ƽ��ϵ��")
extern CString g_sLangID_Diff_TwoSideBalCoeff;            //_T("Diff_TwoSideBalCoeff")
extern CString g_sLangTxt_Diff_TwoSideBalCoeff;            //_T("���ƽ��ϵ��")
extern CString g_sLangID_Diff_ThreeSideBalCoeff;            //_T("Diff_ThreeSideBalCoeff")
extern CString g_sLangTxt_Diff_ThreeSideBalCoeff;            //_T("���ƽ��ϵ��")
extern CString g_sLangID_Diff_PerUnitVal;            //_T("Diff_PerUnitVal")
extern CString g_sLangTxt_Diff_PerUnitVal;            //_T("����ֵ")
extern CString g_sLangID_Diff_WiringCoeff;            //_T("Diff_WiringCoeff")
extern CString g_sLangTxt_Diff_WiringCoeff;            //_T("����ϵ��")
extern CString g_sLangID_Diff_RefCurrentSel;            //_T("Diff_RefCurrentSel")
extern CString g_sLangTxt_Diff_RefCurrentSel;            //_T("��׼����")
extern CString g_sLangID_Diff_HighVoltSide;            //_T("Diff_HighVoltSide")
extern CString g_sLangTxt_Diff_HighVoltSide;            //_T("��ѹ��")
extern CString g_sLangID_Diff_MedVoltSide;            //_T("Diff_MedVoltSide")
extern CString g_sLangTxt_Diff_MedVoltSide;            //_T("��ѹ��")
extern CString g_sLangID_Diff_LowVoltSide;            //_T("Diff_LowVoltSide")
extern CString g_sLangTxt_Diff_LowVoltSide;            //_T("��ѹ��")
extern CString g_sLangID_Diff_DiffProtCurrTerm;            //_T("Diff_DiffProtCurrTerm")
extern CString g_sLangTxt_Diff_DiffProtCurrTerm;            //_T("�������������")
extern CString g_sLangID_Diff_RelayTest;            //_T("Diff_RelayTest")
extern CString g_sLangTxt_Diff_RelayTest;            //_T("�̵籣��������")
extern CString g_sLangID_Diff_FuncParas;            //_T("Diff_FuncParas")
extern CString g_sLangTxt_Diff_FuncParas;            //_T("���ܲ���")
extern CString g_sLangID_Diff_AddOneItem;            //_T("Diff_AddOneItem")
extern CString g_sLangTxt_Diff_AddOneItem;            //_T("��ӵ���")
extern CString g_sLangID_Diff_ClearResult;            //_T("Diff_ClearResult")
extern CString g_sLangTxt_Diff_ClearResult;            //_T("������")
extern CString g_sLangID_Diff_CommonPara;            //_T("Diff_CommonPara")
extern CString g_sLangTxt_Diff_CommonPara;            //_T("ͨ�ò���")
extern CString g_sLangID_LowFreq_FreqRangeRate;            //_T("LowFreq_FreqRangeRate")
extern CString g_sLangTxt_LowFreq_FreqRangeRate;            //_T("Ƶ�ʱ仯��Χ����仯��")
extern CString g_sLangID_LowFreq_FreqBegin;            //_T("LowFreq_FreqBegin")
extern CString g_sLangTxt_LowFreq_FreqBegin;            //_T("Ƶ����ʼֵ(Hz)")
extern CString g_sLangID_LowFreq_FreqEnd;            //_T("LowFreq_FreqEnd")
extern CString g_sLangTxt_LowFreq_FreqEnd;            //_T("Ƶ�ʽ���ֵ(Hz)")
extern CString g_sLangID_LowFreq_FreqFaultTrig;            //_T("LowFreq_FaultTrig")
extern CString g_sLangTxt_LowFreq_FreqFaultTrig;            //_T("������ѹѡ��")
extern CString g_sLangID_LowFreq_PhaseV;            //_T("LowFreq_PhaseV")
extern CString g_sLangTxt_LowFreq_PhaseV;            //_T("���ѹ")
extern CString g_sLangID_LowFreq_SettingBegin;            //_T("LowFreq_SettingBegin")
extern CString g_sLangTxt_LowFreq_SettingBegin;            //_T("����ֵ��Ϊ��ʱ���")
extern CString g_sLangID_LowFreq_FreqChangeBegin;            //_T("LowFreq_FreqChangeBegin")
extern CString g_sLangTxt_LowFreq_FreqChangeBegin;            //_T("Ƶ�ʱ仯��Ϊ��ʱ���")
extern CString g_sLangID_LowFreq_CommonParaSet;            //_T("LowFreq_CommonParaSet")
extern CString g_sLangTxt_LowFreq_CommonParaSet;            //_T("ͨ�ò�������")
extern CString g_sLangID_LowFreq_dfdtSetting;            //_T("LowFreq_dfdtSetting")
extern CString g_sLangTxt_LowFreq_dfdtSetting;            //_T("���ֵ")
extern CString g_sLangID_LowFreq_GradientPara;            //_T("LowFreq_GradientPara")
extern CString g_sLangTxt_LowFreq_GradientPara;            //_T("�ݱ����")
extern CString g_sLangID_LowFreq_dfdtBegin;            //_T("LowFreq_dfdtBegin")
extern CString g_sLangTxt_LowFreq_dfdtBegin;            //_T("����仯ʼֵ")
extern CString g_sLangID_LowFreq_dfdtEnd;            //_T("LowFreq_dfdtEnd")
extern CString g_sLangTxt_LowFreq_dfdtEnd;            //_T("����仯��ֵ")
extern CString g_sLangID_LowFreq_dfdtStep;            //_T("LowFreq_dfdtStep")
extern CString g_sLangTxt_LowFreq_dfdtStep;            //_T("����仯����")
extern CString g_sLangID_LowFreq_LowVoltage;            //_T("LowFreq_LowVoltage")
extern CString g_sLangTxt_LowFreq_LowVoltage;            //_T("�͵�ѹ")
extern CString g_sLangID_LowFreq_BeginVal;            //_T("LowFreq_BeginVal")
extern CString g_sLangTxt_LowFreq_BeginVal;            //_T("�仯ʼֵ")
extern CString g_sLangID_LowFreq_EndVal;            //_T("LowFreq_EndVal")
extern CString g_sLangTxt_LowFreq_EndVal;            //_T("�仯��ֵ")
extern CString g_sLangID_LowFreq_TestItem;            //_T("LowFreq_TestItem")
extern CString g_sLangTxt_LowFreq_TestItem;            //_T("������Ŀ")
extern CString g_sLangID_LowFreq_dvdtRate;            //_T("LowFreq_dvdtRate")
extern CString g_sLangTxt_LowFreq_dvdtRate;            //_T("Ƶ�ʻ����")
extern CString g_sLangID_LowFreq_TimePara;            //_T("LowFreq_TimePara")
extern CString g_sLangTxt_LowFreq_TimePara;            //_T("ʱ�����")
extern CString g_sLangID_LowFreq_ULockPara;            //_T("LowFreq_ULockPara")
extern CString g_sLangTxt_LowFreq_ULockPara;            //_T("��ѹ��������")
extern CString g_sLangID_LowFreq_dvdtSetting;            //_T("LowFreq_dvdtSetting")
extern CString g_sLangTxt_LowFreq_dvdtSetting;            //_T("Ƶ�ʻ����ֵ(Hz/s)")
extern CString g_sLangID_LowVol_BeginVal;            //_T("LowVol_BeginVal")
extern CString g_sLangTxt_LowVol_BeginVal;            //_T("�仯��ʼֵ")
extern CString g_sLangID_LowVol_EndVal;            //_T("LowVol_EndVal")
extern CString g_sLangTxt_LowVol_EndVal;            //_T("�仯����ֵ")
extern CString g_sLangID_LowVol_Var;            //_T("LowVol_Var")
extern CString g_sLangTxt_LowVol_Var;            //_T("�仯��")
extern CString g_sLangID_LowVol_FreqRangeRate;            //_T("LowVol_FreqRangeRate")
extern CString g_sLangTxt_LowVol_FreqRangeRate;            //_T("��ѹ�仯��Χ����仯��")
extern CString g_sLangID_LowVol_dVdt;            //_T("LowVol_dVdt")
extern CString g_sLangTxt_LowVol_dVdt;            //_T("����")
extern CString g_sLangID_LowVol_dVdtRate;            //_T("LowVol_dVdtRate")
extern CString g_sLangTxt_LowVol_dVdtRate;            //_T("��ѹ�����")
extern CString g_sLangID_LowVol_VolEnd;            //_T("LowVol_VolEnd")
extern CString g_sLangTxt_LowVol_VolEnd;            //_T("��ѹ����ֵ(V)")
extern CString g_sLangID_LowVol_OtherPara;            //_T("LowVol_OtherPara")
extern CString g_sLangTxt_LowVol_OtherPara;            //_T("��������")
extern CString g_sLangID_LowVol_SteadyCur;            //_T("LowVol_SteadyCur")
extern CString g_sLangTxt_LowVol_SteadyCur;            //_T("��̬����(A)")
extern CString g_sLangID_LowVol_Exegesis;            //_T("LowVol_Exegesis")
extern CString g_sLangTxt_LowVol_Exegesis;            //_T("ע:" ��ѹ���ض���ֵ"������ʹ��")
extern CString g_sLangID_Diff_BorderSearch;            //_T("Diff_BorderSearch")
extern CString g_sLangTxt_Diff_BorderSearch;            //_T("�����ƶ��߽�����")
extern CString g_sLangID_Diff_Section;            //_T("Diff_Section")
extern CString g_sLangTxt_Diff_Section;            //_T("����")
extern CString g_sLangID_Diff_Expression;            //_T("Diff_Expression")
extern CString g_sLangTxt_Diff_Expression;            //_T("��ʽ")
extern CString g_sLangID_Diff_StraightLine;            //_T("Diff_StraightLine")
extern CString g_sLangTxt_Diff_StraightLine;            //_T("ֱ��")
extern CString g_sLangID_Diff_InSet;            //_T("Diff_InSet")
extern CString g_sLangTxt_Diff_InSet;            //_T("��׼����(����)")
extern CString g_sLangID_Diff_CombinedFeature;            //_T("Diff_CombinedFeature")
extern CString g_sLangTxt_Diff_CombinedFeature;            //_T("��������")
extern CString g_sLangID_Diff_ZeroSeqElimiType;            //_T("Diff_ZeroSeqElimiType")
extern CString g_sLangTxt_Diff_ZeroSeqElimiType;            //_T("����������ʽ")
extern CString g_sLangID_Diff_Setting;            //_T("Diff_Setting")
extern CString g_sLangTxt_Diff_Setting;            //_T("������ֵ")
extern CString g_sLangID_Diff_Custom;            //_T("Diff_Custom")
extern CString g_sLangTxt_Diff_Custom;            //_T("�Զ���")
extern CString g_sLangID_Diff_TypeSel;            //_T("Diff_TypeSel")
extern CString g_sLangTxt_Diff_TypeSel;            //_T("ѡ������")
extern CString g_sLangID_Native_ThirdPart;		//=_T("Native_ThirdPart");
extern CString g_sLangTxt_Native_ThirdPart;		//=_T("������");
extern CString g_sLangID_Diff_QuickBreak;            //_T("Diff_QuickBreak")
extern CString g_sLangTxt_Diff_QuickBreak;            //_T("�ٶ�")
extern CString g_sLangID_Native_InflectionPoint3;	// = _T("Native_InflectionPoint3")
extern CString g_sLangTxt_Native_InflectionPoint3; // = _T("�յ�3")
extern CString g_sLangID_Diff_QuickBreakVal;            //_T("Diff_QuickBreakVal")
extern CString g_sLangTxt_Diff_QuickBreakVal;            //_T("�ٶ�")
extern CString g_sLangID_Diff_CurrChar;            //_T("Diff_CurrChar")
extern CString g_sLangTxt_Diff_CurrChar;            //_T("��ǰ����")
extern CString g_sLangID_Diff_ZAdjust;            //_T("Diff_ZAdjust")
extern CString g_sLangTxt_Diff_ZAdjust;            //_T("Z��У��")
extern CString g_sLangID_Diff_Result;            //_T("Diff_Result")
extern CString g_sLangTxt_Diff_Result;            //_T("���Խ��")
extern CString g_sLangID_Diff_IdTheory;            //_T("Diff_IdTheory")
extern CString g_sLangTxt_Diff_IdTheory;            //_T("����ֵId")
extern CString g_sLangID_Diff_FaultType2;            //_T("Diff_FaultType2")
extern CString g_sLangTxt_Diff_FaultType2;            //_T("������")
extern CString g_sLangID_Diff_Select;            //_T("Diff_Select")
extern CString g_sLangTxt_Diff_Select;            //_T("ѡ��")
extern CString g_sLangID_Diff_ActualVal;            //_T("Diff_ActualVal")
extern CString g_sLangTxt_Diff_ActualVal;            //_T("����ֵ")
extern CString g_sLangID_Diff_HSecondaryCur;            //_T("Diff_HSecondaryCur")
extern CString g_sLangTxt_Diff_HSecondaryCur;            //_T("�߲����ε���")
extern CString g_sLangID_Diff_CurrSet;            //_T("Diff_CurrSet")
extern CString g_sLangTxt_Diff_CurrSet;            //_T("�趨ֵ")
extern CString g_sLangID_Diff_EverySecondaryCur;            //_T("Diff_EverySecondaryCur")
extern CString g_sLangTxt_Diff_EverySecondaryCur;            //_T("������ζ����")

//2024-10-30 xueyangfan
extern CString g_sLangID_BinRecord_RecordTimeType;            //_T("BinRecord_RecordTimeType");
extern CString g_sLangTxt_BinRecord_RecordTimeType;            //_T("��¼ʱ��");
extern CString g_sLangID_BinRecord_All;						//_T("BinRecord_All");
extern CString g_sLangTxt_BinRecord_All;						//_T("ȫ��");
extern CString g_sLangID_BinRecord_RecordAll;					//_T("BinRecord_RecordAll");
extern CString g_sLangTxt_BinRecord_RecordAll;					//_T("��ȫ��");
extern CString g_sLangID_BinRecord_RecordPlug;					//_T("BinRecord_RecordPlug");
extern CString g_sLangTxt_BinRecord_RecordPlug;				 //_T("�����");
extern CString g_sLangID_BinRecord_DisplayType;					//_T("BinRecord_DisplayType");
extern CString g_sLangTxt_BinRecord_DisplayType;				 //_T("��ʾ��ʽ");
extern CString g_sLangID_BinRecord_Once;						//_T("BinRecord_Once");
extern CString g_sLangTxt_BinRecord_Once;						//_T("һ��");
extern CString g_sLangID_BinRecord_Quadratic;					 //_T("BinRecord_Quadratic");
extern CString g_sLangTxt_BinRecord_Quadratic;					 //_T("����");
extern CString g_sLangID_BinRecord_RecordTriggerType;            //_T("BinRecord_RecordTriggerType");
extern CString g_sLangTxt_BinRecord_RecordTriggerType;            //_T("¼��������ʽ");
extern CString g_sLangID_BinRecord_Rollover;						//_T("BinRecord_Rollover");
extern CString g_sLangTxt_BinRecord_Rollover;						//_T("��ת");
extern CString g_sLangID_BinRecord_RisingEdge;						//_T("BinRecord_RisingEdge");
extern CString g_sLangTxt_BinRecord_RisingEdge;					//_T("������");
extern CString g_sLangID_BinRecord_FallingEdge;					//_T("BinRecord_FallingEdge");
extern CString g_sLangTxt_BinRecord_FallingEdge;					//_T("�½���");
extern CString g_sLangID_BinRecord_TriggeredTime;            //_T("BinRecord_TriggeredTime");
extern CString g_sLangTxt_BinRecord_TriggeredTime;            //_T("��ʱ������GPS/B�룩");
extern CString g_sLangID_BinRecord_ChannelUp;					 //_T("BinRecord_ChannelUp");
extern CString g_sLangTxt_BinRecord_ChannelUp;					//_T("ͨ������");
extern CString g_sLangID_BinRecord_ChannelDown;			 //_T("BinRecord_ChannelDown");
extern CString g_sLangTxt_BinRecord_ChannelDown;				 //_T("ͨ������");
extern CString g_sLangID_BinRecord_ChannelTop;					//_T("BinRecord_ChannelTop");
extern CString g_sLangTxt_BinRecord_ChannelTop;				//_T("�ö�");
extern CString g_sLangID_BinRecord_ChannelBottom;            //_T("BinRecord_ChannelBottom");
extern CString g_sLangTxt_BinRecord_ChannelBottom;            //_T("�ײ�");
extern CString g_sLangID_BinRecord_Recover;            //_T("BinRecord_Recover");
extern CString g_sLangTxt_BinRecord_Recover;					//_T("�ָ�Ĭ��");
extern CString g_sLangID_BinRecord_DefaultSavePath;					//_T("BinRecord_DefaultSavePath");
extern CString g_sLangTxt_BinRecord_DefaultSavePath;            //_T("Ĭ�ϱ���·��");
extern CString g_sLangID_BinRecord_RecordSet;            //_T("BinRecord_RecordSet");
extern CString g_sLangTxt_BinRecord_RecordSet;            //_T("¼������");
extern CString g_sLangID_BinRecord_ImportCfg;            //_T("BinRecord_ImportCfg");
extern CString g_sLangTxt_BinRecord_ImportCfg;            //_T("��������");
extern CString g_sLangID_BinRecord_SaveCfg;            //_T("BinRecord_SaveCfg");
extern CString g_sLangTxt_BinRecord_SaveCfg;            //_T("��������");
extern CString g_sLangID_BinRecord_BinRecord;            //_T("BinRecord_BinRecord");
extern CString g_sLangTxt_BinRecord_BinRecord;            //_T("������¼��");
extern CString g_sLangID_BinRecord_SavePath;            //_T("BinRecord_SavePath");
extern CString g_sLangTxt_BinRecord_SavePath;            //_T("����·��");
extern CString g_sLangID_BinRecord_AutoSaveRecordFile;            //_T("BinRecord_AutoSaveRecordFile");
extern CString g_sLangTxt_BinRecord_AutoSaveRecordFile;            //_T("�Զ�����¼���ļ�");


extern CString g_sLangID_Native_CRCTypeSelection;
extern CString g_sLangTxt_Native_CRCTypeSelection;
extern CString g_sLangID_Native_MergeUnitAutoTest;
extern CString g_sLangTxt_Native_MergeUnitAutoTest;
extern CString g_sLangID_Native_AccuracyTest;
extern CString g_sLangTxt_Native_AccuracyTest;
extern CString g_sLangID_Native_ZeroDriftTest;
extern CString g_sLangTxt_Native_ZeroDriftTest;
extern CString g_sLangID_Native_TimeTest;
extern CString g_sLangTxt_Native_TimeTest;
extern CString g_sLangID_Native_TimingAccuracy;
extern CString g_sLangTxt_Native_TimingAccuracy;
extern CString g_sLangID_Native_TimeKeepingAccuracy;
extern CString g_sLangTxt_Native_TimeKeepingAccuracy;
extern CString g_sLangID_Native_FirstCycleTest;
extern CString g_sLangTxt_Native_FirstCycleTest;

extern CString g_sLangID_BinRecord_SaveType;           // = _T("BinRecord_SaveType");
extern CString g_sLangTxt_BinRecord_SaveType;            // = _T("��������");
extern CString g_sLangID_BinRecord_SelPlugin;            // = _T("BinRecord_SelPlugin");
extern CString g_sLangTxt_BinRecord_SelPlugin;            // = _T("ѡ����");
extern CString g_sLangID_BinRecord_Wave;            // = _T("BinRecord_Wave");
extern CString g_sLangTxt_BinRecord_Wave;            // = _T("���η���");
extern CString g_sLangID_BinRecord_Power;            // = _T("BinRecord_Power");
extern CString g_sLangTxt_BinRecord_Power;            // = _T("����");
extern CString g_sLangID_BinRecord_Vector;            // = _T("BinRecord_Vector");
extern CString g_sLangTxt_BinRecord_Vector;            // = _T("����");

extern CString g_sLangID_Native_TemplatePath; //  Native_TemplatePath
extern CString g_sLangTxt_Native_TemplatePath; // ģ��·��

extern CString g_sLangID_Native_ModelFilePath; // Native_ModelFilePath
extern CString g_sLangTxt_Native_ModelFilePath; //  ģ���ļ�·��

extern CString g_sLangID_Native_TestRecordFilePath; //  Native_TestRecordFilePath
extern CString g_sLangTxt_Native_TestRecordFilePath; //  ���Լ�¼�ļ�·��

extern CString g_sLangID_Native_EmptyNode; // Native_EmptyNode
extern CString g_sLangTxt_Native_EmptyNode; // �սڵ�

extern CString g_sLangID_Native_FlipThreshold ; //  Native_FlipThreshold
extern CString g_sLangTxt_Native_FlipThreshold; // ��ת�ż�

//2024.11.6 zhangyq ͬ��
extern CString g_sLangID_Syn_LeaderAngle; //  Syn_LeaderAngle
extern CString g_sLangTxt_Syn_LeaderAngle; // ��ǰ��ʵ��ֵ
extern CString g_sLangID_Syn_LeaderTime; //  Syn_LeaderTime
extern CString g_sLangTxt_Syn_LeaderTime; // ��ǰʱ��ʵ��ֵ
extern CString g_sLangID_Syn_LAngle; //  Syn_LAngle
extern CString g_sLangTxt_Syn_LAngle; // ��ǰ������ֵ
extern CString g_sLangID_Syn_LTime; //  Syn_LTime
extern CString g_sLangTxt_Syn_LTime; // ��ǰʱ������ֵ
extern CString g_sLangID_Syn_VolDeltValue; //  Syn_VolDeltValue
extern CString g_sLangTxt_Syn_VolDeltValue; // ʵ��ѹ��
extern CString g_sLangID_Syn_FreqDeltValue; //  Syn_FreqDeltValue
extern CString g_sLangTxt_Syn_FreqDeltValue; // ʵ��Ƶ��
extern CString g_sLangID_Syn_UgStart; //  Syn_UgStart
extern CString g_sLangTxt_Syn_UgStart; // �������ѹ
extern CString g_sLangID_Syn_FgStart; //  Syn_FgStart
extern CString g_sLangTxt_Syn_FgStart; // ������Ƶ��
//2024.11.12 gongyiping ͬ��
extern CString g_sLangID_Syn_TestParas; //  Syn_TestParas
extern CString g_sLangTxt_Syn_TestParas; // �������

//2025-1-2�Զ����Ա��벻��������һ����������Դ
//������Ƶ����£����õ��ĵط����벻��ע����
extern CString g_sLangID_NewTest_Native; //  NewTest
extern CString g_sLangTxt_NewTest_Native; // �½�����

//2024.11.7 zhangyq ������ʱ��
extern CString g_sLangID_CurrInverse_SettingTime; //  CurrInverse_SettingTime
extern CString g_sLangTxt_CurrInverse_SettingTime; // ����ʱ��

//add wangtao 20241106 
extern CString g_sLangID_LowVol_VolChangeBegin;            //_T("LowVol_VolChangeBegin")
extern CString g_sLangTxt_LowVol_VolChangeBegin;            //_T("��ѹ�仯��Ϊ��ʱ���")
extern CString g_sLangID_Diff_EndValWarning;            //_T("Diff_EndValWarning")
extern CString g_sLangTxt_Diff_EndValWarning;            //_T("�������޳������ֵ")
extern CString g_sLangID_Power_OverLimitWarning;            //_T("Power_OverLimitWarning")
extern CString g_sLangTxt_Power_OverLimitWarning;            //_T("����ֵ%f����ֵ��������ʾ���ֵ(%f)���ᵼ�µ�������(%f)")

extern CString g_sLangID_TemplateCreatedSuccessful;    // = _T("TemplateCreatedSuccessful");
extern CString g_sLangTxt_TemplateCreatedSuccessful;   // = _T("���ʰ�ģ���������.")
extern CString g_sLangID_TemplateCreatedFailed;    // = _T("TemplateCreatedFailed");
extern CString g_sLangTxt_TemplateCreatedFailed;   // = _T("���ʰ�ģ������ʧ��.")

extern CString g_sLangID_SCL_Parsing; // ��ӦID: SCL_Parsing
extern CString g_sLangTxt_SCL_Parsing; // ����: SCL����

extern CString g_sLangID_SCL_Loading; // ��ӦID: SCL_Loading
extern CString g_sLangTxt_SCL_Loading; // ����: ���ڼ���SCL�ļ�...

extern CString g_sLangID_SCL_InvalidFile; // ��ӦID: SCL_InvalidFile
extern CString g_sLangTxt_SCL_InvalidFile; // ����: ��ǰ�ļ�(%s)û����չ������SCL�ļ�

extern CString g_sLangID_Native_TemplateGenerationSuccess; // ��ӦID: TemplateGenerationSuccess
extern CString g_sLangTxt_Native_TemplateGenerationSuccess; // ����: ���ʰ�ģ���������.

extern CString g_sLangID_Native_TemplateGenerationFail; // ��ӦID: TemplateGenerationFail
extern CString g_sLangTxt_Native_TemplateGenerationFail; // ����: ���ʰ�ģ������ʧ��.

extern CString g_sLangID_Native_CharacteristicCurveUpdateFail; // ��ӦID: CharacteristicCurveUpdateFail
extern CString g_sLangTxt_Native_CharacteristicCurveUpdateFail; // ����: �������߸���ʧ��.

extern CString g_sLangID_Native_CheckReportSave; //_T("Native_CheckReportSave��");
extern CString g_sLangTxt_Native_CheckReportSave; //_T("��ȷ�ϵ�ǰ�����Ƿ񱣴棡");

extern CString g_sLangID_TransientTime;//��̬��Ӧʱ��
extern CString g_sLangTxt_TransientTime;
extern CString g_sLangID_MUInput;//�ϲ���Ԫ����
extern CString g_sLangTxt_MUInput;
extern CString g_sLangID_MUOutput;//�ϲ���Ԫ���
extern CString g_sLangTxt_MUOutput;
//add wangtao 20241112 �ı��������ݴ�ȷ��
extern CString g_sLangID_Diff_DisjointWarning;            //_T("Diff_DisjointWarning")
extern CString g_sLangTxt_Diff_DisjointWarning;            //_T("��ǰ�����������������ֵ�����������޽���")
extern CString g_sLangID_Diff_MultiDisjointWarning;            //_T("MultiDisjointWarning")
extern CString g_sLangTxt_Diff_MultiDisjointWarning;            //_T("���²����������������޽���:")
extern CString g_sLangID_Diff_InflectionPointWarning;            //_T("Diff_InflectionPointWarning")
extern CString g_sLangTxt_Diff_InflectionPointWarning;            //_T("�յ�������ô���, �������յ�")

extern CString g_sLangID_Diff_YDSupCT;            //_T("Diff_YDSupCT")
extern CString g_sLangTxt_Diff_YDSupCT;            //_T("YD����CT")
extern CString g_sLangID_Diff_ImportChar;            //_T("Diff_ImportChar")
extern CString g_sLangTxt_Diff_ImportChar;            //_T("������������")

//2024-11-15 wuxinyi
extern CString g_sLangID_Native_NULL;            //_T("Native_NULL")
extern CString g_sLangTxt_Native_NULL;            //_T("��")
extern CString g_sLangID_Native_CheckSetDelfChMap;            //_T("Native_CheckSetDelfChMap")
extern CString g_sLangTxt_Native_CheckSetDelfChMap;            //_T("��ǰ%1ӳ��Ϊ�գ��Ƿ�����ȱʡͨ��ӳ��?:")

//2024-11-18 gongyiping  QScanLanTesterDlg_trans
//�޸Ĳ�����IP
extern CString g_sLangID_Native_ModTesterIP;
extern CString g_sLangTxt_Native_ModTesterIP;
//��ȡ����IP��ַʧ��,��ǰֵΪ��.
extern CString g_sLangID_Native_FailToRetrieveNetAddr;
extern CString g_sLangTxt_Native_FailToRetrieveNetAddr;
//ȡ���豸��Ϣʧ��
extern CString g_sLangID_Native_FailToRetDevInfo;
extern CString g_sLangTxt_Native_FailToRetDevInfo;
//������IP��ַ(%1)�뵱ǰ����IP����ͬһ����,�Ƿ��޸�?
extern CString g_sLangID_Native_AddrNotInSameSubnet;
extern CString g_sLangTxt_Native_AddrNotInSameSubnet;
//��ǰѡ�������Ϊ��.
extern CString g_sLangID_Native_CurrSelNetAdptEmpty;
extern CString g_sLangTxt_Native_CurrSelNetAdptEmpty;

extern CString g_sLangID_Native_ClearReportData;            //_T("Native_ClearReportData")
extern CString g_sLangTxt_Native_ClearReportData;            //_T("�����������")
extern CString g_sLangID_Native_IsContinueClearReport;            //_T("Native_IsContinueClearReport")
extern CString g_sLangTxt_Native_IsContinueClearReport;            //_T("����������ݺ󣬽��޷��ָ�����ȷ���Ƿ���Ҫ�����������")
extern CString g_sLangID_Native_CreatIecParaError;            //_T("Native_CreatIecParaError")
extern CString g_sLangTxt_Native_CreatIecParaError;            //_T("����ʧ�ܣ��ýڵ��£��Ѿ����ڡ�IEC61850���á���Ŀ")
extern CString g_sLangID_Native_CreatSysParaError;            //_T("Native_CreatSysParaError")
extern CString g_sLangTxt_Native_CreatSysParaError;            //_T("����ʧ�ܣ��ýڵ��£��Ѿ����ڡ�ϵͳ�������á���Ŀ")
extern CString g_sLangID_Native_CreatChMapParaError;            //_T("Native_CreatChMapParaError")
extern CString g_sLangTxt_Native_CreatChMapParaError;            //_T("����ʧ�ܣ��ýڵ��£��Ѿ����ڡ�Ӳ��ͨ��ӳ�䡿��Ŀ")
extern CString g_sLangID_Native_CreatEngineError;            //_T("Native_CreatEngineError")
extern CString g_sLangTxt_Native_CreatEngineError;            //_T("�½�ͨѶ����ʧ�ܣ�")

//add wangtao 20241121
extern CString g_sLangID_Diff_ImportCharFile; //_T("Diff_ImportCharFile")
extern CString g_sLangTxt_Diff_ImportCharFile; //_T("���������ļ�")
extern CString g_sLangID_Diff_ImportCharFilePath; //_T("Diff_ImportCharFilePath")
extern CString g_sLangTxt_Diff_ImportCharFilePath; //_T("�������������ļ�·��")
extern CString g_sLangID_Diff_ImportCharWarning; //_T("Diff_ImportCharWarning")
extern CString g_sLangTxt_Diff_ImportCharWarning; //_T("�����˷Ƿ����������ļ�")
//add luozibing 20241125
extern CString g_sLangID_DistanceSearch_TileAxisName;				//_T("DistanceSearch_TileAxisName")
extern CString g_sLangTxt_DistanceSearch_TileAxisName;				//_T("R-X(��) ")

//2024-11-27 wuxinyi ͳһʹ��XLanguageResource�е�g_sLangTxt_AxisUnitAng��g_sLangTxt_AxisUnitOmega
// extern CString g_sLangID_DistanceSearch_AxisUnitMag;				//_T("DistanceSearch_AxisUnitMag")
// extern CString g_sLangTxt_DistanceSearch_AxisUnitMag;				//_T("��")
// extern CString g_sLangID_DistanceSearch_AxisUnitAng;				//_T("DistanceSearch_AxisUnitAng")
// extern CString g_sLangTxt_DistanceSearch_AxisUnitAng;				//_T("��")

extern CString g_sLangID_Native_PulseSelection;				//_T("Native_PulseSelection")
extern CString g_sLangTxt_Native_PulseSelection;				//_T("����ѡ�� ")

//2024-11-27 zhouyangyong 
extern CString g_sLangID_PhaseCurr;//_T("CurrPhase_I")
extern CString g_sLangTxt_PhaseCurr;//_T("�����_I")
extern CString g_sLangID_PhaseVolt;//_T("VoltPhase_U")
extern CString g_sLangTxt_PhaseVolt;//_T("���ѹ_U")
extern CString g_sLangID_ActiveBin;//_T("ActiveBin")
extern CString g_sLangTxt_ActiveBin;//_T("��Դ����")
extern CString g_sLangID_PassiveBin;//_T("PassiveBin")
extern CString g_sLangTxt_PassiveBin;//_T("��Դ����")
extern CString g_sLangID_VoidBin;//_T("VoidBin")
extern CString g_sLangTxt_VoidBin;//_T("��Ч����")

extern CString g_sLangID_Native_CurrDeviceNumIsNull;				//_T("Native_CurrDeviceNumIsNull")
extern CString g_sLangTxt_Native_CurrDeviceNumIsNull;				//_T("��ǰ�豸���Ϊ�� ")
extern CString g_sLangID_Native_CurrDeviceFileNonexist;				//_T("Native_CurrDeviceFileNonexist")
extern CString g_sLangTxt_Native_CurrDeviceFileNonexist;				//_T("��ǰ�豸�ļ�(%s)������ ")
extern CString g_sLangID_Native_SysxmlNonexist;				//_T("Native_SysxmlNonexist")
extern CString g_sLangTxt_Native_SysxmlNonexist;				//_T("ϵͳ�����ļ���%s��������. ")
extern CString g_sLangID_Native_AnalyzeSysxmlFail;				//_T("Native_AnalyzeSysxmlFail")
extern CString g_sLangTxt_Native_AnalyzeSysxmlFail;				//_T("����ϵͳ�����ļ�ʧ�ܡ�%s�� ")
extern CString g_sLangID_Native_IECParaFileNonexist;				//_T("Native_IECParaFileNonexist")
extern CString g_sLangTxt_Native_IECParaFileNonexist;				//_T("IEC�����ļ�(%s)������. ")
extern CString g_sLangID_Native_GetModuleTypeFail;				//_T("Native_GetModuleTypeFail")
extern CString g_sLangTxt_Native_GetModuleTypeFail;				//_T("��ȡģ������ʧ��")
extern CString g_sLangID_Native_NotMapModuleType;				//_T("Native_NotMapModuleType")
extern CString g_sLangTxt_Native_NotMapModuleType;				//_T("δӳ���ģ������")

extern CString  g_sLangID_ReplayTest_ReEnterWavePoint;		//=_T("ReplayTest_ReEnterWavePoint");
extern CString  g_sLangTxt_ReplayTest_ReEnterWavePoint;		//_T("������С���Ϊ1�����������룡");
extern CString  g_sLangID_ReplayTest_CheckInputWavePoint;		//=_T("ReplayTest_CheckInputWavePoint");
extern CString  g_sLangTxt_ReplayTest_CheckInputWavePoint;		//_T("�������ʼ���/��ֹ��Ų��ܳ��������ܵ���[%d]�����������룡");
extern CString  g_sLangID_ReplayTest_CheckBeginAndEndPoint;		//=_T("ReplayTest_CheckBeginAndEndPoint");
extern CString  g_sLangTxt_ReplayTest_CheckBeginAndEndPoint;		//_T("�������ֹ��Ų���С���������ʼ���[%d]�����������룡");
extern CString  g_sLangID_ReplayTest_CycleNumCheck;		//=_T("ReplayTest_CycleNumCheck");
extern CString  g_sLangTxt_ReplayTest_CycleNumCheck;		//_T("ѭ��������������1�Σ����������룡");
extern CString  g_sLangID_ReplayTest_CheckInputWaveTime;		//=_T("ReplayTest_CheckInputWaveTime");
extern CString  g_sLangTxt_ReplayTest_CheckInputWaveTime;		//_T("��������/�յ㲻�ܳ����ܲ��γ���[%.3fs]�����������룡");
extern CString  g_sLangID_ReplayTest_CheckBeginAndEndTime;		//=_T("ReplayTest_CheckBeginAndEndTime");
extern CString  g_sLangTxt_ReplayTest_CheckBeginAndEndTime;		//_T("������յ㲻��С����������[%.3fs]�����������룡");
extern CString  g_sLangID_ReplayTest_InsertWaveVolOver;		//=_T("ReplayTest_InsertWaveVolOver");
extern CString  g_sLangTxt_ReplayTest_InsertWaveVolOver;		//_T("��ǰ�����ʵ�ʳ�̬���ε�ѹֵ(%f),���ڲ�������������ѹ(%f).");
extern CString  g_sLangID_ReplayTest_InsertWaveCurOver;		//=_T("ReplayTest_InsertWaveCurOver");
extern CString  g_sLangTxt_ReplayTest_InsertWaveCurOver;		//_T("��ǰ�����ʵ�ʳ�̬���ε���ֵ(%f),���ڲ���������������(%f).");
extern CString  g_sLangID_ReplayTest_InsertWaveTimeOver;		//=_T("ReplayTest_InsertWaveTimeOver");
extern CString  g_sLangTxt_ReplayTest_InsertWaveTimeOver;		//_T("��ǰ���ʱ�䲻�ܳ���[%.3fs]�����������룡");
extern CString  g_sLangID_ReplayTest_CheckOverlapTime;		//=_T("ReplayTest_CheckOverlapTime");
extern CString  g_sLangTxt_ReplayTest_CheckOverlapTime;		//_T("������ɾ��ʱ����ص���������ѡ��ʱ�䣡");


extern CString  g_sLangID_Native_IsSaveChangeParas;		//=_T("Native_IsSaveChangeParas");
extern CString  g_sLangTxt_Native_IsSaveChangeParas;		//_T("�Ƿ񱣴�����޸�?");

//2024-12-25 xueyangfan
extern CString  g_sLangID_Native_DisConnectAll;		//=_T("Native_DisConnectAll");
extern CString  g_sLangTxt_Native_DisConnectAll;		//_T("ȫ���Ͽ�");
extern CString  g_sLangID_Native_AllClosed;		//=_T("Native_AllClosed");
extern CString  g_sLangTxt_Native_AllClosed;		//_T("ȫ���պ�");
extern CString  g_sLangID_Native_BoutChannel;		//=_T("Native_BoutChannel");
extern CString  g_sLangTxt_Native_BoutChannel;		//_T("����ͨ��");
extern CString  g_sLangID_Replay_ClearMap;		//=_T("Replay_ClearMap");
extern CString  g_sLangTxt_Replay_ClearMap;		//_T("���ӳ��");
extern CString  g_sLangID_Native_ToPublish;		//=_T("Native_ToPublish");
extern CString  g_sLangTxt_Native_ToPublish;		//_T("������");
extern CString  g_sLangID_Native_ToSubscriptions;		//=_T("Native_ToSubscriptions");
extern CString  g_sLangTxt_Native_ToSubscriptions;		//_T("������");

//dingxy 20241227
extern CString g_sLangID_Native_TestInstrumentConfig;		// = _T("TestInstrumentConfig");
extern CString g_sLangTxt_Native_TestInstrumentConfig;		// = _T("����������");
extern CString g_sLangID_Native_ScanLANTestInstrument;		// = _T("ScanLANTestInstrument");
extern CString g_sLangTxt_Native_ScanLANTestInstrument;	// = _T("ɨ�������������");
extern CString g_sLangID_Native_DirectConfigRemoteInstrument;	// = _T("DirectConfigRemoteInstrument");
extern CString g_sLangTxt_Native_DirectConfigRemoteInstrument;	// = _T("ֱ������Զ�̲�����");
extern CString g_sLangID_Native_ScanRemoteTestInstrument;		// = _T("ScanRemoteTestInstrument");
extern CString g_sLangTxt_Native_ScanRemoteTestInstrument;		// = _T("ɨ��Զ�̲�����");
extern CString g_sLangID_Native_Setup;							//= _T("Setup");
extern CString g_sLangTxt_Native_Setup;						//   = _T("����");
extern CString g_sLangID_Native_Upgrade;						// = _T("Upgrade");
extern CString g_sLangTxt_Native_Upgrade;						// = _T("������");
extern CString g_sLangID_Native_EnablePUDA;					// = _T("EnablePUDA");
extern CString g_sLangTxt_Native_EnablePUDA;					// = _T("��PUDA");
extern CString g_sLangID_Native_EnableTestSvr;					// = _T("EnableTestSvr");
extern CString g_sLangTxt_Native_EnableTestSvr;				// = _T("��TestSvr");
extern CString g_sLangID_Native_TestInstrumentModel;			// = _T("TestInstrumentModel");
extern CString g_sLangTxt_Native_TestInstrumentModel;			// = _T("�������ͺ�");
extern CString g_sLangID_Native_TestInstrumentID;				// = _T("TestInstrumentID");
extern CString g_sLangTxt_Native_TestInstrumentID;				// = _T("�����Ǳ��");
extern CString g_sLangID_Native_CloudIP;						// = _T("CloudIP");
extern CString g_sLangTxt_Native_CloudIP;						// = _T("�ƶ�IP��");
extern CString g_sLangID_Native_CloudPort;						// = _T("CloudPort");
extern CString g_sLangTxt_Native_CloudPort;					// = _T("�ƶ�Port��");
extern CString g_sLangID_Native_TestInstrumentSerialNumber;    // = _T("TestInstrumentSerialNumber");
extern CString g_sLangTxt_Native_TestInstrumentSerialNumber;	// = _T("���������кţ�");
extern CString g_sLangID_Native_Password;						// = _T("Password");
extern CString g_sLangTxt_Native_Password;						// = _T("���룺");
// extern CString g_sLangID_Unit2;							// = _T("Unit");
// extern CString g_sLangTxt_Unit2;						// = _T("��λ��");
extern CString g_sLangID_Native_Bind;							// = _T("Bind");
extern CString g_sLangTxt_Native_Bind;							// = _T("��");
extern CString g_sLangID_Native_Query;							// = _T("Query");
extern CString g_sLangTxt_Native_Query;						// = _T("��ѯ");
extern CString g_sLangID_Native_TestInstrumentConnectionError; // = _T("TestInstrumentConnectionError");
extern CString g_sLangTxt_Native_TestInstrumentConnectionError;// = _T("�����ǣ�%s �������Ӳ�ͨ��");
extern CString g_sLangID_Native_CloudServerConnectionError;	// = _T("CloudServerConnectionError");
extern CString g_sLangTxt_Native_CloudServerConnectionError;	// = _T("�Ʒ�������%s �������Ӳ�ͨ��");
extern CString g_sLangID_Native_IPIsEmpty;						// = _T("IPIsEmpty");
extern CString g_sLangTxt_Native_IPIsEmpty;					// = _T("IPΪ��");
extern CString g_sLangID_Native_ConnectionTestInstrumentFailed; // = _T("ConnectionTestInstrumentFailed");
extern CString g_sLangTxt_Native_ConnectionTestInstrumentFailed; // = _T("���Ӳ�����ʧ��");
extern CString g_sLangID_Native_MulticastInitSuccess;			// = _T("MulticastInitSuccess");
extern CString g_sLangTxt_Native_MulticastInitSuccess;			// = _T("�鲥��ʼ��[%s][%d]�ɹ�");
extern CString g_sLangID_Native_MulticastInitFailed;			// = _T("MulticastInitFailed");
extern CString g_sLangTxt_Native_MulticastInitFailed;			// = _T("�鲥��ʼ��[%s][%d]ʧ��");
extern CString g_sLangID_Native_MulticastInitBindSuccess;		// = _T("MulticastInitBindSuccess");
extern CString g_sLangTxt_Native_MulticastInitBindSuccess;		// = _T("�鲥��ʼ��[%s][%d]�ɹ����󶨱���IP[%s]");
extern CString g_sLangID_Native_Disconnection;					// = _T("Disconnection");
extern CString g_sLangTxt_Native_Disconnection;				// = _T("����");
extern CString g_sLangID_Native_CloudConnectionFailed;			// = _T("CloudConnectionFailed");
extern CString g_sLangTxt_Native_CloudConnectionFailed;		// = _T("�����ƶ�ʧ��");
extern CString g_sLangID_Native_TestInstrumentUserInfoError;	// = _T("TestInstrumentUserInfoError");
extern CString g_sLangTxt_Native_TestInstrumentUserInfoError;	// = _T("��������Ϣ���û���Ϣ�������");
extern CString g_sLangID_Native_Connect;						// = _T("Connect");
extern CString g_sLangTxt_Native_Connect;						//  = _T("����");
extern CString g_sLangID_Native_StopScanning;					// = _T("StopScanning");
extern CString g_sLangTxt_Native_StopScanning;					// = _T("ֹͣɨ��");
extern CString g_sLangID_Native_Scanning;						// = _T("Scanning");
extern CString g_sLangTxt_Native_Scanning;						// = _T("ɨ��");
extern CString g_sLangID_Native_NanjingEnergyCloud;			// = _T("NanjingEnergyCloud");
extern CString g_sLangTxt_Native_NanjingEnergyCloud;			// = _T("�Ͼ����Ƶ���");
extern CString g_sLangID_Native_TestInstrumentConfigFileNotFound; // = _T("TestInstrumentConfigFileNotFound");
extern CString g_sLangTxt_Native_TestInstrumentConfigFileNotFound;// = _T("�����������ļ���%s �Ҳ�����");
extern CString g_sLangID_Native_OAClientInitFail;				// = _T("OAClientInitFail");
extern CString g_sLangTxt_Native_OAClientInitFail;				// = _T("OA�ͻ���COM�ӿڳ�ʼ��ʧ�ܡ�");
//���
extern CString g_sLangID_Native_Index;                    // = _T("SttAdjMain_Index");
extern CString g_sLangTxt_Native_Index;					  //  = _T("���");
// extern CString g_sLangID_Native_IndepDCCurrChHWRange;					// = _T("SttAdjMain_IndepDCCurrChHWRange");
// extern CString g_sLangTxt_Native_IndepDCCurrChHWRange;					// = _T("����ֱ������ͨ��Ӳ����λ");
extern CString g_sLangID_Native_IndepDCVolChHWRange;					// = _T("SttAdjMain_IndepDCVolChHWRange")	
extern CString g_sLangTxt_Native_IndepDCVolChHWRange;					// = _T("����ֱ����ѹͨ��Ӳ����λ");
extern CString g_sLangID_Native_ModChRange;							// = _T("SttAdjMain_ModChRange");
extern CString g_sLangTxt_Native_ModChRange;							// = _T("ģ��ͨ����λ");

//����ֱ������Idc
extern CString g_sLangID_Native_IndepDCCurrIdc;						// = _T("SttAdjMain_IndepDCCurrIdc");
extern CString g_sLangTxt_Native_IndepDCCurrIdc;					// = _T("����ֱ������Idc");
//����ֱ����ѹUdc
extern CString g_sLangID_Native_IndepDCVolUdc;						// = _T("SttAdjMain_IndepDCVolUdc");
extern CString g_sLangTxt_Native_IndepDCVolUdc;						// = _T("����ֱ����ѹUdc");
//ͨ��1-ͨ��3
extern CString g_sLangID_Native_ChannelOneToThree;					// = _T("SttAdjMain_ChannelOneToThree");
extern CString g_sLangTxt_Native_ChannelOneToThree;					// = _T("ͨ��1-ͨ��3");
//ͨ��4-ͨ��6
extern CString g_sLangID_Native_ChannelFourToSix;					// = _T("SttAdjMain_ChannelFourToSix");
extern CString g_sLangTxt_Native_ChannelFourToSix;					// = _T("ͨ��4-ͨ��6");

//��λ%d
extern CString g_sLangID_Native_GearFormat;							// = _T("SttAdjMain_GearFormat");
extern CString g_sLangTxt_Native_GearFormat;						// = _T("��λ%d");
//����%d
extern CString g_sLangID_Native_TempzoneFormat;						// = _T("SttAdjMain_TempzoneFormat");
extern CString g_sLangTxt_Native_TempzoneFormat;					// = _T("����%d");
//ģ��[%s]ģ���ļ�������
extern CString g_sLangID_Native_TemplateFileNoExit;					// = _T("SttAdjMain_TemplateFileNoExit");
extern CString g_sLangTxt_Native_TemplateFileNoExit;				// = _T("ģ��[%s]ģ���ļ�������");
//ģ�����ݴ���û�ж����ͺ�
extern CString g_sLangID_Native_ModelDataError_NoModel;				// = _T("SttAdjMain_ModelDataError_NoModel");
extern CString g_sLangTxt_Native_ModelDataError_NoModel;			// = _T("ģ�����ݴ���û�ж����ͺ�");
//ģ�����ݴ����ͺ�Ϊ��
extern CString g_sLangID_Native_ModelDataError_EmptyModel;			// = _T("SttAdjMain_ModelDataError_EmptyModel");
extern CString g_sLangTxt_Native_ModelDataError_EmptyModel;			// = _T("ģ�����ݴ����ͺ�Ϊ��");
//������%s��ģ��ϵ��ģ���ļ��ɹ�
extern CString g_sLangID_Native_ExportCoefficientTemplateSuccess;	// = _T("SttAdjMain_ExportCoefficientTemplateSuccess");
extern CString g_sLangTxt_Native_ExportCoefficientTemplateSuccess;	// = _T("������%s��ģ��ϵ��ģ���ļ��ɹ�");
//������%s��ģ��ϵ��ģ���ļ�ʧ��
extern CString g_sLangID_Native_ExportFailure;						// = _T("SttAdjMain_ExportFailure");
extern CString g_sLangTxt_Native_ExportFailure;						// = _T("������%s��ģ��ϵ��ģ���ļ�ʧ��");
//ģ��Ӳ��λ��
extern CString g_sLangID_Native_ModuleHardPos;			// = _T("SttAdjMain_ModuleHardPos");
extern CString g_sLangTxt_Native_ModuleHardPos;			// =  _T("ģ��Ӳ��λ��");
//ͨ�����ֵ
extern CString g_sLangID_Native_ChMaxValue;				// = _T("SttAdjMain_ChMaxValue");
extern CString g_sLangTxt_Native_ChMaxValue;			// = _T("ͨ�����ֵ");
//�½�ģ������
extern CString g_sLangID_Native_NewModuleType;			// = _T("SttAdjMain_NewModuleType");
extern CString g_sLangTxt_Native_NewModuleType;			// = _T("�½�ģ������");

//20250116 suyang

extern CString g_sLangID_Native_MUAccuracyTest;	//׼ȷ�Ȳ���	
extern CString g_sLangTxt_Native_MUAccuracyTest;	
extern CString g_sLangID_Native_DifferentialTest;	//�Ȳ����	
extern CString g_sLangTxt_Native_DifferentialTest;	
extern CString g_sLangID_Native_AngleDifferenceTest;	//�ǲ����
extern CString g_sLangTxt_Native_AngleDifferenceTest;
extern CString g_sLangID_Native_CompositeErrorTest;	//����������
extern CString g_sLangTxt_Native_CompositeErrorTest;
extern CString g_sLangID_Native_ChannelDelayTest;	//ͨ����ʱ����
extern CString g_sLangTxt_Native_ChannelDelayTest;
extern CString g_sLangID_Native_MaximumRatioDifference;	//���Ȳ�
extern CString g_sLangTxt_Native_MaximumRatioDifference;
extern CString g_sLangID_Native_MinimumRatioDifference;	//��С�Ȳ�
extern CString g_sLangTxt_Native_MinimumRatioDifference;
extern CString g_sLangID_Native_AverageRatioDifference;	//ƽ���Ȳ�
extern CString g_sLangTxt_Native_AverageRatioDifference ;
extern CString g_sLangID_Native_OutputAngle;	//����Ƕ�(��)
extern CString g_sLangTxt_Native_OutputAngle;
extern CString g_sLangID_Native_MaximumAngleDifference;	//���ǲ�(��)
extern CString g_sLangTxt_Native_MaximumAngleDifference;
extern CString g_sLangID_Native_MinimumAngleDifference;	//��С�ǲ�(��)
extern CString g_sLangTxt_Native_MinimumAngleDifference;
extern CString g_sLangID_Native_AverageAngleDifference;	//ƽ���ǲ�(��)
extern CString g_sLangTxt_Native_AverageAngleDifference;
extern CString g_sLangID_Native_MaximumError;	//������
extern CString g_sLangTxt_Native_MaximumError;
extern CString g_sLangID_Native_MinimumError;	//��С���
extern CString g_sLangTxt_Native_MinimumError;
extern CString g_sLangID_Native_AverageError;	//ƽ�����
extern CString g_sLangTxt_Native_AverageError;
extern CString g_sLangID_Native_ControlBlockDescription;	//���ƿ�����
extern CString g_sLangTxt_Native_ControlBlockDescription;
extern CString g_sLangID_Native_MaximumDelay;	//�����ʱ
extern CString g_sLangTxt_Native_MaximumDelay;
extern CString g_sLangID_Native_MinimumDelay;	//��С��ʱ
extern CString g_sLangTxt_Native_MinimumDelay;
extern CString g_sLangID_Native_AverageDelay;	//ƽ����ʱ
extern CString g_sLangTxt_Native_AverageDelay;
extern CString g_sLangID_Native_MaximumZeroDrif;	//�����Ư
extern CString g_sLangTxt_Native_MaximumZeroDrif;
extern CString g_sLangID_Native_MinimumZeroDrif;	//��С��Ư
extern CString g_sLangTxt_Native_MinimumZeroDrif;
extern CString g_sLangID_Native_AverageZeroDrif;	//ƽ����Ư
extern CString g_sLangTxt_Native_AverageZeroDrif;
extern CString g_sLangID_Native_MUPunctAccurTest;	//��ʱ������
extern CString g_sLangTxt_Native_MUPunctAccurTest;
extern  CString g_sLangID_Native_MUSPunctuality;  //��ʱʱ��
extern  CString g_sLangTxt_Native_MUSPunctuality;
extern  CString g_sLangID_Native_MUSTiming;  //��ʱʱ��
extern  CString g_sLangTxt_Native_MUSTiming;
extern  CString g_sLangID_Native_MUTimingAccurTest;  //��ʱ������
extern  CString g_sLangTxt_Native_MUTimingAccurTest;


//���ʰ���ֲ 20250207 xueyangfan
extern  CString g_sLangID_Smv_AddToSub;
extern  CString g_sLangTxt_Smv_AddToSub;
extern  CString g_sLangID_Smv_AddToPub;
extern  CString g_sLangTxt_Smv_AddToPub;
extern  CString g_sLangID_DistanceSearch_SectionSix;
extern  CString g_sLangTxt_DistanceSearch_SectionSix;
extern  CString g_sLangID_DistanceSearch_SectionSeven;
extern  CString g_sLangTxt_DistanceSearch_SectionSeven;
extern  CString g_sLangID_DistanceSearch_SectionEight;
extern  CString g_sLangTxt_DistanceSearch_SectionEight;
extern CString g_sLangID_CBOperate_VzDefineParas;	
extern CString g_sLangTxt_CBOperate_VzDefineParas;
extern  CString g_sLangID_Transducer_ParasSet;
extern  CString g_sLangTxt_Transducer_ParasSet;
extern  CString g_sLangID_Transducer_Phase_PhaseSingle;
extern  CString g_sLangTxt_Transducer_Phase_APhaseSingle;
extern  CString g_sLangID_Transducer_Phase_A;
extern  CString g_sLangTxt_Transducer_Phase_A;
extern  CString g_sLangID_Transducer_Phase_B;
extern  CString g_sLangTxt_Transducer_Phase_B;
extern  CString g_sLangID_Transducer_Phase_C;
extern  CString g_sLangTxt_Transducer_Phase_C;
extern  CString g_sLangID_Transducer_Phase_ABC;
extern  CString g_sLangTxt_Transducer_Phase_ABC;
extern  CString g_sLangID_Transducer_UInputLimit;
extern  CString g_sLangTxt_Transducer_UInputLimit;
extern  CString g_sLangID_Transducer_LInputLimit;
extern  CString g_sLangTxt_Transducer_LInputLimit;
extern  CString g_sLangID_Transducer_UOutputLimit;
extern  CString g_sLangTxt_Transducer_UOutputLimit;
extern  CString g_sLangID_Transducer_LOutputLimit;
extern  CString g_sLangTxt_Transducer_LOutputLimit;
extern  CString g_sLangID_Transducer_Input;
extern  CString g_sLangTxt_Transducer_Input;
extern  CString g_sLangID_Transducer_Un;
extern  CString g_sLangTxt_Transducer_Un;
extern  CString g_sLangID_Transducer_UIAngle;
extern  CString g_sLangTxt_Transducer_UIAngle;
extern  CString g_sLangID_Transducer_Imax;
extern  CString g_sLangTxt_Transducer_Imax;
extern  CString g_sLangID_Transducer_StdFreq;
extern  CString g_sLangTxt_Transducer_StdFreq;
extern  CString g_sLangID_Transducer_TestTimes;
extern  CString g_sLangTxt_Transducer_TestTimes;
extern  CString g_sLangID_Transducer_GridInput;
extern  CString g_sLangTxt_Transducer_GridInput;
extern  CString g_sLangID_Transducer_GridOutput;
extern  CString g_sLangTxt_Transducer_GridOutput;
extern  CString g_sLangID_Transducer_GridRealOutput;
extern  CString g_sLangTxt_Transducer_GridRealOutput;
extern  CString g_sLangID_Transducer_TestType;
extern  CString g_sLangTxt_Transducer_TestType;
extern  CString g_sLangID_Transducer_Type;
extern  CString g_sLangTxt_Transducer_Type;
extern  CString g_sLangID_Transducer_Level;
extern  CString g_sLangTxt_Transducer_Level;
extern  CString g_sLangID_Transducer_TestValue;
extern  CString g_sLangTxt_Transducer_TestValue;
extern  CString g_sLangID_Transducer_SettingTime;
extern  CString g_sLangTxt_Transducer_SettingTime;
extern  CString g_sLangID_Transducer_Ratio;
extern  CString g_sLangTxt_Transducer_Ratio;
extern  CString g_sLangID_Transducer_CopySelTest;
extern  CString g_sLangTxt_Transducer_CopySelTest;
extern  CString g_sLangID_Transducer_PasteTest;
extern  CString g_sLangTxt_Transducer_PasteTest;
extern  CString g_sLangID_Diff_MSecondaryCur;
extern  CString g_sLangTxt_Diff_MSecondaryCur;
extern  CString g_sLangID_Diff_LSecondaryCur;
extern  CString g_sLangTxt_Diff_LSecondaryCur;
extern  CString g_sLangID_Native_IsSaveTemp;
extern  CString g_sLangTxt_Native_IsSaveTemp;
extern  CString g_sLangID_Native_isContinueExistSameSCD;
extern  CString g_sLangTxt_Native_isContinueExistSameSCD;
extern  CString g_sLangID_Xrio_EnterValue;
extern  CString g_sLangTxt_Xrio_EnterValue;
extern  CString g_sLangID_Xrio_EnterValidValue;
extern  CString g_sLangTxt_Xrio_EnterValidValue;

//dingxy 20250311 У׼���������
//PN��������С�ź�ģ��
extern  CString g_sLangID_Native_WeekPNMain;        // = _T("Native_WeekPNMain");
extern  CString g_sLangTxt_Native_WeekPNMain;		//= _T("PN��������С�ź�ģ��");;
//L336D_ECTEVT ģ��
extern  CString g_sLangID_Native_WeeKL336DECTEVT;	//= _T("Native_WeeKL336DECTEVT");
extern  CString g_sLangTxt_Native_WeeKL336DECTEVT;	 //= _T("L336D_ECTEVT ģ��");
//PIA0103 ģ��
extern  CString g_sLangID_Native_PIA0103;			//= _T("Native_PIA0103");
extern  CString g_sLangTxt_Native_PIA0103;			 //= _T("PIA0103 ģ��");
//PNS330 ģ��(����ͬ�����10��)
extern  CString g_sLangID_Native_PNS330UMax10;		//= _T("Native_PNS330UMax10");
extern  CString g_sLangTxt_Native_PNS330UMax10;		 //= _T("PNS330 ģ��(����ͬ�����10��)");
//PNS330 ģ��(����ͬ�����20��)
extern  CString g_sLangID_Native_PNS330ABC_20;		 //= _T("Native_PNS330ABC_20");
extern  CString g_sLangTxt_Native_PNS330ABC_20;		 //= _T("PNS330 ģ��(����ͬ�����20��)");
//PNS330_H ģ��(����ͬ�����10��)
extern  CString g_sLangID_Native_PNS330_H;			 //= _T("Native_PNS330_H");
extern  CString g_sLangTxt_Native_PNS330_H;			  //= _T("PNS330_H ģ��(����ͬ�����10��)");
//PNS330_H ģ��(����ͬ�����20��)
extern  CString g_sLangID_Native_H_ABC_20;			  // _T("Native_H_ABC_20");
extern  CString g_sLangTxt_Native_H_ABC_20;			   //= _T("PNS330_H ģ��(����ͬ�����20��)");
//PNS330_6 ģ��
extern  CString g_sLangID_Native_PNS330_6;				//= _T("Native_PNS330_6");
extern  CString g_sLangTxt_Native_PNS330_6;				 //= _T("PNS330_6 ģ��");
//PNS331 ģ��(����ͬ�����10��)
extern  CString g_sLangID_Native_PNS331UMax10;			//= _T("Native_PNS331UMax10");
extern  CString g_sLangTxt_Native_PNS331UMax10;			//= _T("PNS331 ģ��(����ͬ�����10��)");
//PNS331 ģ��(����ͬ�����20��)
extern  CString g_sLangID_Native_PNS331_ABC_20;			//= _T("Native_PNS331_ABC_20");
extern  CString g_sLangTxt_Native_PNS331_ABC_20;		 //= _T("PNS331 ģ��(����ͬ�����20��)");
//PNS330_H ģ��(��Դ����V2)
extern  CString g_sLangID_Native_PNS330_H_EX2;			//= _T("Native_PNS330_H_EX2");
extern  CString g_sLangTxt_Native_PNS330_H_EX2;		 //= _T("PNS330_H ģ��(��Դ����V2)");
//PNS331 ģ��(��Դ����V2)
extern  CString g_sLangID_Native_PNS331_EX2;			//= _T("Native_PNS331_EX2");
extern  CString g_sLangTxt_Native_PNS331_EX2;		 //= _T("PNS331 ģ��(��Դ����V2)");


extern  CString g_sLangID_IEC_EndVerification;
extern  CString g_sLangTxt_IEC_EndVerification;
extern  CString g_sLangID_IEC_16ByteVerification;
extern  CString g_sLangTxt_IEC_16ByteVerification;
#endif // _XLangResource_Native_h__
