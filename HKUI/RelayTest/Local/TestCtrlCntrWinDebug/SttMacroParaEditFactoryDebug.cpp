#include "SttMacroParaEditFactoryDebug.h"

#include "../../Module/UI/Manual/SttMacroParaEditViewManual.h"

#if 0
#include "../../Module/UI//SequenceManu/SttMacroParaEditViewSequenceManu.h"
#include "../../Module/UI/State/SttMacroParaEditViewState.h"
#include "../../Module/UI/Harm/SttMacroParaEditViewHarm.h"
#include "../../Module/UI/Gradient/SttMacroParaEditViewGradient.h"
#include "../../Module/UI/TransPlay/SttMacroParaEditViewTransPlay.h"
#include "../../Module/UI/Webkit/SttMacroParaEditViewHtml.h"
#include "../../Module/UI/State/GooseAbnormal/SttMacroParaEditViewGooseAbnormal.h"
#include "../../Module/UI/SOE/SttMacroParaEditViewSoe.h"
#include "../../Module/UI/SequenceGradient/SttMacroParaEditViewSequenceGradient.h"
#include "../../Module/UI/LineVolGradient/SttMacroParaEditViewLineVolGradient.h"
#include "../../Module/UI/LineVoltManu/SttMacroParaEditViewLineVoltManu.h"
#include "../../Module/UI/MUAutoTest/SttMacroParaEditViewMuAutoTest.h"
#include "../../Module/UI/RemoteMeas/SttMacroParaEditViewRemoteMeas.h"
#include "../../Module/UI/RemoteCtrl/SttMacroParaEditViewRemoteCtrl.h"
#include "../../Module/UI/TerminalAutoTest/SttMacroParaEditViewTerminalAutoTest.h"
#include "../../Module/UI/IntelligentTerminal/SttMacroParaEditViewIntelligentTerminal.h"
#include "../../Module/UI/SttTestCntrCmdDefine.h"
#include "../../Module/UI/ShortTimeOver/QttMacroParaEditViewShortTimOver.h"
#include "../../Module/UI/VoltageTimeTypeSectorMode/QSttMacroParaEditViewVolTimeTypeSec.h"
#include "../../Module/UI/FaultGradient/SttMacroParaEditViewFaultGradient.h"
#include "../../Module/UI/AntiShakeTime/QSttMacroParaEditViewAntiShakeTime.h"
#include "../../Module/UI/ADMUAccurAutoTest/SttMacroParaEditViewADMUAccurAutoTest.h"
#include "../../Module/UI/PowerManu/SttMacroParaEditViewPowerManu.h"
#include "../../Module/UI/ImpedanceManu/SttMacroParaEditViewImpedanceManu.h"
#include "../../Module/UI/CBOperate/QSttMacroParaEditViewCBOperate.h"
#include "../../Module/TestUI/Distance/SttMultiMacroParaEditViewDistance.h"
#include "../../Module/TestUI/LowFreq/SttMultiMacroParaEditViewLowFreq.h"
#include "../../Module/TestUI/LowVol/SttMultiMacroParaEditViewLowVol.h"
#include "../../Module/UI/Swing/SttMacroParaEditViewSwing.h"
#include "../../Module/TestUI/ActTime/SttMultiMacroParaEditViewActionTime.h"
#include "../../Module/TestUI/CurrInverseTime/SttMultiMacroParaEditViewCurrInverseTime.h"
#include "../../Module/TestUI/DistanceSearch/SttMultiMacroParaEditViewDistanceSearch.h"
#include "../../Module/TestUI/RecloseAcc/SttMultiMacroParaEditViewRecloseAcc.h"
#include "../../Module/TestUI/PowerDirection/SttMultiMacroParaEditViewPowerDir.h"
#include "../../Module/TestUI/VolInverseTime/SttMultiMacroParaEditViewVolInverseTime.h"
#endif

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewManual(const CString &strGridFile)
{
	return new QSttMacroParaEditViewManual();
}

#if 0
static CSttMacroParaEditInterface* new_QSttMacroParaEditViewSequenceManu()
{    return new QSttMacroParaEditViewSequenceManu();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewState()
{    return new QSttMacroParaEditViewState();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewHarm()
{    return new QSttMacroParaEditViewHarm();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewGradient()
{    return new QSttMacroParaEditViewGradient();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewTransPlay()
{    return new QSttMacroParaEditViewTransPlay();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewHtml()
{    return new QSttMacroParaEditViewHtml();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewGooseAbnormal()
{    return new QSttMacroParaEditViewGooseAbnormal();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewSoe()
{    return new QSttMacroParaEditViewSoe();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewSequenceGradient()
{    return new QSttMacroParaEditViewSequenceGradient();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewLineVolGradient()
{    return new QSttMacroParaEditViewLineVolGradient();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewLineVoltManu()
{    return new QSttMacroParaEditViewLineVoltManu();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewMuAutoTest()
{    return new QSttMacroParaEditViewMuAutoTest();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewRemoteMeas()
{    return new QSttMacroParaEditViewRemoteMeas();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewRemoteCtrl()
{    return new QSttMacroParaEditViewRemoteCtrl();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewTerminalAutoTest()
{    return new QSttMacroParaEditViewTerminalAutoTest();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewIntelligentTerminal()
{    return new QSttMacroParaEditViewIntelligentTerminal();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewIntelligentTerminal()
{    return new QSttMacroParaEditViewIntelligentTerminal();  }

static CSttMacroParaEditInterface* new_QttMacroParaEditViewShortTimOver()
{    return new QttMacroParaEditViewShortTimOver();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewVolTimeTypeSec()
{    return new QSttMacroParaEditViewVolTimeTypeSec();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewFaultGradientc()
{    return new QSttMacroParaEditViewFaultGradient();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewAntiShakeTimec()
{    return new QSttMacroParaEditViewAntiShakeTime();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewADMUAccurAutoTestc()
{    return new QSttMacroParaEditViewADMUAccurAutoTest();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewPowerManuc()
{    return new QSttMacroParaEditViewPowerManu();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewImpedanceManu()
{    return new QSttMacroParaEditViewImpedanceManu();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewCBOperate()
{    return new QSttMacroParaEditViewCBOperate();  }

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewDistance()
{    return new QSttMultiMacroParaEditViewDistance();  }

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewLowFreq()
{    return new QSttMultiMacroParaEditViewLowFreqe();  }

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewLowVol()
{    return new QSttMultiMacroParaEditViewLowVol();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewSwing()
{    return new QSttMacroParaEditViewSwing();  }

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewActionTime()
{    return new QSttMultiMacroParaEditViewActionTime();  }

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewCurrInverseTime()
{    return new QSttMultiMacroParaEditViewCurrInverseTime();  }

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewDistanceSearch()
{    return new QSttMultiMacroParaEditViewDistanceSearch();  }

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewRecloseAcc()
{    return new QSttMultiMacroParaEditViewRecloseAcc();  }

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewPowerDir()
{    return new QSttMultiMacroParaEditViewPowerDir();  }

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewVolInverseTime()
{    return new QSttMultiMacroParaEditViewVolInverseTime();  }

#endif

extern CSttMacroParaEditFactory *g_theMacroParaEditFactory;

CSttMacroParaEditFactoryDebug::CSttMacroParaEditFactoryDebug()
{
    g_theMacroParaEditFactory = this;
	Register(STT_ORG_MACRO_ManualTest, new_QSttMacroParaEditViewManual);

#if 0
    Register(STT_ORG_MACRO_MUAccuracyTest, new_QSttMacroParaEditViewManual);
    Register(STT_ORG_MACRO_MUFirstCycleTest, new_QSttMacroParaEditViewManual);
    Register(STT_ORG_MACRO_MUTimingAccurTest, new_QSttMacroParaEditViewManual);
    Register(STT_ORG_MACRO_MUPunctAccurTest, new_QSttMacroParaEditViewManual);
    Register(STT_ORG_MACRO_StateTest, new_QSttMacroParaEditViewState);
    Register(STT_ORG_MACRO_SmvAbnTest, new_QSttMacroParaEditViewState);
    Register(STT_ORG_MACRO_GseAbnTest, new_QSttMacroParaEditViewGooseAbnormal);
    Register(STT_ORG_MACRO_GradientTest, new_QSttMacroParaEditViewGradient);
    Register(STT_ORG_MACRO_HarmTest, new_QSttMacroParaEditViewHarm);
    Register(STT_ORG_MACRO_ReplayTest, new_QSttMacroParaEditViewTransPlay);
    Register(STT_ORG_MACRO_SequenceManuTest, new_QSttMacroParaEditViewSequenceManu);
    Register(STT_ORG_MACRO_LineVolManuTest, new_QSttMacroParaEditViewLineVoltManu);
    Register(STT_ORG_MACRO_SoeTest, new_QSttMacroParaEditViewSoe);
    Register(STT_ORG_MACRO_SequenceGradientTest, new_QSttMacroParaEditViewSequenceGradient);
    Register(STT_MACRO_ID_FaultGradientTest, newQSttMacroParaEditViewFaultGradient_);
    Register(STT_ORG_MACRO_LineVolGradientTest, new_QSttMacroParaEditViewLineVolGradient);
    Register(STT_ORG_MACRO_MUAutoTest, new_QSttMacroParaEditViewMuAutoTest);
    Register(STT_ORG_MACRO_RemoteMeasTest, new_QSttMacroParaEditViewRemoteMeas);//遥测 20231120 zhangyq
    Register(STT_ORG_MACRO_TerminalAutoTest, new_QSttMacroParaEditViewTerminalAutoTest);
    Register(STT_ORG_MACRO_IntelligentTest, new_QSttMacroParaEditViewIntelligentTerminal);//增加用于智能终端测试  20231107 gongyiping
    Register(STT_ORG_MACRO_ShortTimeOverTest, new_QttMacroParaEditViewShortTimOver);//2023/11/30 wangjunsheng 短时过量输入模块
    Register(STT_ORG_MACRO_VolTimeTypeSecTest, new_QSttMacroParaEditViewVolTimeTypeSec);//20240112 xueyangfan 电压时间型分段模
    Register(STT_ORG_MACRO_AntiShakeTimeTest, new_QSttMacroParaEditViewAntiShakeTime);//20240305 xueyangfan 防抖时间测试
    Register(STT_ORG_MACRO_MUAccurAutoTest, new_QSttMacroParaEditViewAdmuAccurAutoTest);//2024.5.28 ADMU自动测试
    Register(STT_ORG_MACRO_PowerManuTest, new_QSttMacroParaEditViewPowerManu);//20240611 wangtao 通用试验（功率）
    Register(STT_ORG_MACRO_ImpedManualTest, new_QSttMacroParaEditViewImpedanceManu);//20240611 zhangyq 通用试验（阻抗）
    Register(STT_ORG_MACRO_CBOperateTest, new_QSttMacroParaEditViewCBOperate);//20240612 xueyangfan 整组传动
    Register(STT_ORG_MACRO_DistanceTest_I, new_QSttMultiMacroParaEditViewDistance);//20240620 zhouhj 国际-距离保护
    Register(STT_ORG_MACRO_LowFreqTest_I, new_QSttMultiMacroParaEditViewLowFreq);//20240703 wangtao 国际-低周减载
    Register(STT_ORG_MACRO_LowVolTest_I, new_QSttMultiMacroParaEditViewLowVol);//20240703 wangtao 国际-低压减载
    Register(STT_ORG_MACRO_SwingTest, new_QSttMacroParaEditViewSwing);
    Register(STT_ORG_MACRO_CurrInverseTimeTest_I, new_QSttMultiMacroParaEditViewCurrInverseTime);
    Register(STT_ORG_MACRO_VolInverseTimeTest_I, new_QSttMultiMacroParaEditViewVolInverseTime);// 国际-电压反时
    Register(STT_ORG_MACRO_ActionTimeTest_I, new_QSttMultiMacroParaEditViewActionTime);//20240626 wanmj 国际-动作时间
    Register(STT_ORG_MACRO_DistanceSearchTest_I, new_QSttMultiMacroParaEditViewDistanceSearch);
    Register(STT_ORG_MACRO_RecloseAccTest_I, new_QSttMultiMacroParaEditViewRecloseAcc);//20240705 wanmj 国际-重合闸及后加
    Register(STT_ORG_MACRO_PowerDirectionTest_I, new_QSttMultiMacroParaEditViewPowerDir);//20240708 wanmj 国际-功率方向
#endif
}

CSttMacroParaEditFactoryDebug::~CSttMacroParaEditFactoryDebug()
{

}

