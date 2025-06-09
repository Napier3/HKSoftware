#ifndef STTDIFF6IRATEPNVTEST_H
#define STTDIFF6IRATEPNVTEST_H

#include "tmt_diff_curr_test.h"
#include "../../../SttTestBase/SttDiffCurrCalculatTool.h"
#include "SttDiffCurrRateTest.h"


class CSttDiff6IRatePnvTest : public CSttDiffCurrRateTest
{
public:
    CSttDiff6IRatePnvTest();
    virtual ~CSttDiff6IRatePnvTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CSttDiff6IRatePnvTest();
    }
public:

    virtual void AfterSetParameter();
    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

protected:
};

#endif // STTDIFF6IRATEPNVTEST_H
