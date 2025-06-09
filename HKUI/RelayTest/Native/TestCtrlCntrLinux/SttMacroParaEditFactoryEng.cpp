#include "SttMacroParaEditFactoryEng.h"

#include "../../Module/UI/Manual/SttMacroParaEditViewManual.h"
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
#include "../../Module/UI/FaultGradient/SttMacroParaEditViewFaultGradient.h"
#include "../../Module/UI/AntiShakeTime/QSttMacroParaEditViewAntiShakeTime.h"
#include "../../Module/UI/ADMUAccurAutoTest/SttMacroParaEditViewADMUAccurAutoTest.h"
#include "../../Module/UI/PowerManu/SttMacroParaEditViewPowerManu.h"
#include "../../Module/UI/ImpedanceManu/SttMacroParaEditViewImpedanceManu.h"
#include "../../Module/UI/CBOperate/QSttMacroParaEditViewCBOperate.h"
#include "../../Module/TestUI/Distance/SttMultiMacroParaEditViewDistance.h"
#include "../../Module/TestUI/LowFreq/SttMultiMacroParaEditViewLowFreq.h"
#include "../../Module/TestUI/LowVol/SttMultiMacroParaEditViewLowVol.h"
#include "../../Module/TestUI/Diff/SttMultiMacroParaEditViewDiff.h"
#include "../../Module/UI/Swing/SttMacroParaEditViewSwing.h"
#include "../../Module/TestUI/ActTime/SttMultiMacroParaEditViewActionTime.h"
#include "../../Module/TestUI/CurrInverseTime/SttMultiMacroParaEditViewCurrInverseTime.h"
#include "../../Module/TestUI/DistanceSearch/SttMultiMacroParaEditViewDistanceSearch.h"
#include "../../Module/TestUI/RecloseAcc/SttMultiMacroParaEditViewRecloseAcc.h"
#include "../../Module/TestUI/PowerDirection/SttMultiMacroParaEditViewPowerDir.h"
#include "../../Module/TestUI/VolInverseTime/SttMultiMacroParaEditViewVolInverseTime.h"
#include "../../Module/TestUI/Syn/SttMultiMacroParaEditViewSyn.h"
#include "../../Module/TestUI/DiffCBOp/SttMultiMacroParaEditViewDiffCBOp.h"

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewManual(const CString &strGridFile)
{    return new QSttMacroParaEditViewManual();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewSequenceManu(const CString &strGridFile)
{    return new QSttMacroParaEditViewSequenceManu();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewState(const CString &strGridFile)
{
    QSttMacroParaEditViewState *pSttMacroParaEditViewState = new QSttMacroParaEditViewState(false);

#ifndef SttTestCntrThread_H
        pSttMacroParaEditViewState->initUI_Paras(false);
#else
        g_theSttTestCntrThread->PostThreadMessage(2, (unsigned long)pNew, (unsigned long)pNew);
#endif
    return pSttMacroParaEditViewState;
}

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewState_SmvAbnTest(const CString &strGridFile)
{
    QSttMacroParaEditViewState *pSttMacroParaEditViewState = new QSttMacroParaEditViewState(false);

#ifndef SttTestCntrThread_H
        pSttMacroParaEditViewState->initUI_Paras(true);
#else
        g_theSttTestCntrThread->PostThreadMessage(3, (unsigned long)pNew, (unsigned long)pNew);
#endif
    return pSttMacroParaEditViewState;
}

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewHarm(const CString &strGridFile)
{    return new QSttMacroParaEditViewHarm();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewGradient(const CString &strGridFile)
{    return new QSttMacroParaEditViewGradient();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewTransPlay(const CString &strGridFile)
{    return new QSttMacroParaEditViewTransPlay();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewHtml(const CString &strGridFile)
{    return new QSttMacroParaEditViewHtml();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewGooseAbnormal(const CString &strGridFile)
{
    QSttMacroParaEditViewGooseAbnormal *pSttMacroParaEditViewGooseAbnormal = new QSttMacroParaEditViewGooseAbnormal(false,false);
    pSttMacroParaEditViewGooseAbnormal = pSttMacroParaEditViewGooseAbnormal;
#ifndef SttTestCntrThread_H
    pSttMacroParaEditViewGooseAbnormal->initUI_Paras(false,false);
#else
    g_theSttTestCntrThread->PostThreadMessage(4, (unsigned long)pNew, (unsigned long)pNew);
#endif
    return pSttMacroParaEditViewGooseAbnormal;
}

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewSequenceGradient(const CString &strGridFile)
{    return new QSttMacroParaEditViewSequenceGradient();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewLineVolGradient(const CString &strGridFile)
{    return new QSttMacroParaEditViewLineVolGradient();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewLineVoltManu(const CString &strGridFile)
{    return new QSttMacroParaEditViewLineVoltManu();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewRemoteCtrl(const CString &strGridFile)
{    return new QSttMacroParaEditViewRemoteCtrl();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewIntelligentTerminal(const CString &strGridFile)
{    return new QSttMacroParaEditViewIntelligentTerminal();  }

//static CSttMacroParaEditInterface* new_QSttMacroParaEditViewIntelligentTerminal(const CString &strGridFile)
//{    return new QSttMacroParaEditViewIntelligentTerminal();  }

static CSttMacroParaEditInterface* new_QttMacroParaEditViewShortTimOver(const CString &strGridFile)
{    return new QttMacroParaEditViewShortTimOver();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewFaultGradient(const CString &strGridFile)
{    return new QSttMacroParaEditViewFaultGradient();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewAntiShakeTime(const CString &strGridFile)
{    return new QSttMacroParaEditViewAntiShakeTime();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewPowerManu(const CString &strGridFile)
{    return new QSttMacroParaEditViewPowerManu();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewImpedanceManu(const CString &strGridFile)
{    return new QSttMacroParaEditViewImpedanceManu();  }

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewCBOperate(const CString &strGridFile)
{    return new QSttMacroParaEditViewCBOperate();  }

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewDistance(const CString &strGridFile)
{
    QSttMultiMacroParaEditViewDistance *pNew = new QSttMultiMacroParaEditViewDistance(strGridFile);
    pNew->InitUI_OneMacro();
    return pNew;
}

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewLowFreq(const CString &strGridFile)
{
    QSttMultiMacroParaEditViewLowFreq *pNew = new QSttMultiMacroParaEditViewLowFreq(strGridFile);
    pNew->InitUI_MultiMacro();
    return pNew;
}


static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewDiffCBOp(const CString &strGridFile)
{
    QSttMultiMacroParaEditViewDiffCBOp *pNew = new QSttMultiMacroParaEditViewDiffCBOp(strGridFile);
    pNew->InitUI_OneMacro();
    return pNew;
}

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewLowVol(const CString &strGridFile)
{
    QSttMultiMacroParaEditViewLowVol *pNew = new QSttMultiMacroParaEditViewLowVol(strGridFile);
    pNew->InitUI_MultiMacro();
    return pNew;
 //   return new QSttMultiMacroParaEditViewLowVol(strGridFile);
}

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewDiff(const CString &strGridFile)
{
    QSttMultiMacroParaEditViewDiff *pNew = new QSttMultiMacroParaEditViewDiff(strGridFile);
    pNew->InitUI_MultiMacro();
    return pNew;
 //   return new QSttMultiMacroParaEditViewLowVol(strGridFile);
}

static CSttMacroParaEditInterface* new_QSttMacroParaEditViewSwing(const CString &strGridFile)
{    return new QSttMacroParaEditViewSwing();  }

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewActionTime(const CString &strGridFile)
{
    QSttMultiMacroParaEditViewActionTime *pNew = new QSttMultiMacroParaEditViewActionTime(strGridFile);
    pNew->InitUI_OneMacro();
    return pNew;
//    return new QSttMultiMacroParaEditViewActionTime(strGridFile);
}

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewCurrInverseTime(const CString &strGridFile)
{
    QSttMultiMacroParaEditViewCurrInverseTime *pNew = new QSttMultiMacroParaEditViewCurrInverseTime(strGridFile);
    pNew->InitUI_OneMacro();
    return pNew;
 //   return new QSttMultiMacroParaEditViewCurrInverseTime(strGridFile);
}

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewDistanceSearch(const CString &strGridFile)
{
    QSttMultiMacroParaEditViewDistanceSearch *pNew = new QSttMultiMacroParaEditViewDistanceSearch(strGridFile);
    pNew->InitUI_OneMacro();
    return pNew;
//    return new QSttMultiMacroParaEditViewDistanceSearch(strGridFile);
}

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewRecloseAcc(const CString &strGridFile)
{
    QSttMultiMacroParaEditViewRecloseAcc *pNew = new QSttMultiMacroParaEditViewRecloseAcc(strGridFile);
    pNew->InitUI_OneMacro();
    return pNew;
 //   return new QSttMultiMacroParaEditViewRecloseAcc(strGridFile);
}

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewPowerDir(const CString &strGridFile)
{
    QSttMultiMacroParaEditViewPowerDir *pNew = new QSttMultiMacroParaEditViewPowerDir(strGridFile);
    pNew->InitUI_OneMacro();
    return pNew;
 //   return new QSttMultiMacroParaEditViewPowerDir(strGridFile);
}

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewVolInverseTime(const CString &strGridFile)
{
    QSttMultiMacroParaEditViewVolInverseTime *pNew = new QSttMultiMacroParaEditViewVolInverseTime(strGridFile);
    pNew->InitUI_OneMacro();
    return pNew;
//    return new QSttMultiMacroParaEditViewVolInverseTime(strGridFile);
}

static CSttMacroParaEditInterface* new_QSttMultiMacroParaEditViewSyn(const CString &strGridFile)
{
	QSttMultiMacroParaEditViewSyn *pNew = new QSttMultiMacroParaEditViewSyn(strGridFile);
	pNew->InitUI_MultiMacro();
	return pNew;
}

extern CSttMacroParaEditFactory *g_theMacroParaEditFactory;

CSttMacroParaEditFactoryEng::CSttMacroParaEditFactoryEng()
{
    g_theMacroParaEditFactory = this;

    Register(STT_ORG_MACRO_ManualTest, new_QSttMacroParaEditViewManual);
    Register(STT_ORG_MACRO_MUAccuracyTest, new_QSttMacroParaEditViewManual);
    Register(STT_ORG_MACRO_MUFirstCycleTest, new_QSttMacroParaEditViewManual);
    Register(STT_ORG_MACRO_MUTimingAccurTest, new_QSttMacroParaEditViewManual);
    Register(STT_ORG_MACRO_MUPunctAccurTest, new_QSttMacroParaEditViewManual);
    Register(STT_ORG_MACRO_StateTest, new_QSttMacroParaEditViewState);
    Register(STT_ORG_MACRO_SmvAbnTest, new_QSttMacroParaEditViewState_SmvAbnTest);
    Register(STT_ORG_MACRO_GseAbnTest, new_QSttMacroParaEditViewGooseAbnormal);
    Register(STT_ORG_MACRO_GradientTest, new_QSttMacroParaEditViewGradient);
    Register(STT_ORG_MACRO_HarmTest, new_QSttMacroParaEditViewHarm);
    Register(STT_ORG_MACRO_ReplayTest, new_QSttMacroParaEditViewTransPlay);
    Register(STT_ORG_MACRO_SequenceManuTest, new_QSttMacroParaEditViewSequenceManu);
    Register(STT_ORG_MACRO_LineVolManuTest, new_QSttMacroParaEditViewLineVoltManu);
    Register(STT_ORG_MACRO_SequenceGradientTest, new_QSttMacroParaEditViewSequenceGradient);
    Register(STT_MACRO_ID_FaultGradientTest, new_QSttMacroParaEditViewFaultGradient);
    Register(STT_ORG_MACRO_LineVolGradientTest, new_QSttMacroParaEditViewLineVolGradient);
    Register(STT_ORG_MACRO_IntelligentTest, new_QSttMacroParaEditViewIntelligentTerminal);//增加用于智能终端测试  20231107 gongyiping
    Register(STT_ORG_MACRO_ShortTimeOverTest, new_QttMacroParaEditViewShortTimOver);//2023/11/30 wangjunsheng 短时过量输入模块
    Register(STT_ORG_MACRO_AntiShakeTimeTest, new_QSttMacroParaEditViewAntiShakeTime);//20240305 xueyangfan 防抖时间测试
    Register(STT_ORG_MACRO_PowerManuTest, new_QSttMacroParaEditViewPowerManu);//20240611 wangtao 通用试验（功率）
    Register(STT_ORG_MACRO_ImpedManualTest, new_QSttMacroParaEditViewImpedanceManu);//20240611 zhangyq 通用试验（阻抗）
    Register(STT_ORG_MACRO_CBOperateTest, new_QSttMacroParaEditViewCBOperate);//20240612 xueyangfan 整组传动
    Register(STT_ORG_MACRO_DistanceTest_I, new_QSttMultiMacroParaEditViewDistance);//20240620 zhouhj 国际-距离保护
    Register(STT_ORG_MACRO_LowFreqTest_I, new_QSttMultiMacroParaEditViewLowFreq);//20240703 wangtao 国际-低周减载
    Register(STT_ORG_MACRO_LowVolTest_I, new_QSttMultiMacroParaEditViewLowVol);//20240703 wangtao 国际-低压减载
    Register(STT_ORG_MACRO_SwingTest, new_QSttMacroParaEditViewSwing);
    Register(STT_ORG_MACRO_DiffCBOpTest_I, new_QSttMultiMacroParaEditViewDiffCBOp);//20240709 xueyangfan 国际-整组差动
    Register(STT_ORG_MACRO_CurrInverseTimeTest_I, new_QSttMultiMacroParaEditViewCurrInverseTime);
    Register(STT_ORG_MACRO_VolInverseTimeTest_I, new_QSttMultiMacroParaEditViewVolInverseTime);// 国际-电压反时
    Register(STT_ORG_MACRO_ActionTimeTest_I, new_QSttMultiMacroParaEditViewActionTime);//20240626 wanmj 国际-动作时间
    Register(STT_ORG_MACRO_DistanceSearchTest_I, new_QSttMultiMacroParaEditViewDistanceSearch);
    Register(STT_ORG_MACRO_RecloseAccTest_I, new_QSttMultiMacroParaEditViewRecloseAcc);//20240705 wanmj 国际-重合闸及后加
    Register(STT_ORG_MACRO_PowerDirectionTest_I, new_QSttMultiMacroParaEditViewPowerDir);//20240708 wanmj 国际-功率方向
	Register(STT_ORG_MACRO_SynTest_I, new_QSttMultiMacroParaEditViewSyn);//20240704 zhangyq 国际-自动准同期
    Register(STT_ORG_MACRO_DiffTest_I, new_QSttMultiMacroParaEditViewDiff);//20240722 wangtao 国际-差动
}

CSttMacroParaEditFactoryEng::~CSttMacroParaEditFactoryEng()
{

}

