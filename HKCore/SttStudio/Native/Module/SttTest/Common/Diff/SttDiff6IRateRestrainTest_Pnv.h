#ifndef STTDIFF6IRATERESTRAINPNVTEST_H
#define STTDIFF6IRATERESTRAINPNVTEST_H

#include "SttDiff6IRateTest_Pnv.h"


class CSttDiff6IRateRestrainTest : public CSttDiff6IRatePnvTest
{
public:
    CSttDiff6IRateRestrainTest();
    virtual ~CSttDiff6IRateRestrainTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CSttDiff6IRateRestrainTest();
    }
};

#endif // STTDIFF6IRATERESTRAINPNVTEST_H
