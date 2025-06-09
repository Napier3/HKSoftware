#include"SttDiff6IRateRestrainTest_Pnv.h"
#include "stdafx.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
    #include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttDiff6IRateRestrainTest::m_strMacroName = "差动(6I)-比例制动(PNV)";
CString CSttDiff6IRateRestrainTest::m_strMacroID = STT_MACRO_ID_Diff6IRateRestrainTest;
CString CSttDiff6IRateRestrainTest::m_strFilePostFix = "pdff6irtst";
CString CSttDiff6IRateRestrainTest::m_strMacroVer = "1.0";

CSttDiff6IRateRestrainTest::CSttDiff6IRateRestrainTest() : CSttDiff6IRatePnvTest()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    SetTestStarting(FALSE);
    m_dTestStartTime = 0;
}

CSttDiff6IRateRestrainTest::~CSttDiff6IRateRestrainTest(void)
{
}
