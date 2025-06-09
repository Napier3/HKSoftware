#ifndef STTLOWFREQTIMETEST_PNV_H
#define STTLOWFREQTIMETEST_PNV_H

#include "SttLowFreqTimeTest.h"
//xuzhantao240304

class CSttLowFreqTimePnvTest : public CSttLowFreqTimeTest
{
public:
    CSttLowFreqTimePnvTest();
    virtual ~CSttLowFreqTimePnvTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CSttLowFreqTimePnvTest();
    }
public:

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

protected:
    virtual void TranslateToStateParas();//�ڴ˺�����ʵ�ֽ��غ�բ����ٲ���ת��Ϊ״̬���в���
};

#endif // STTLOWFREQTIMETEST_PNV_H
