#pragma once

#include "SttLowFreqActTest.h"


class CSttLowFreqActPnvTest : public CSttLowFreqActTest
{
public:
    CSttLowFreqActPnvTest();
    virtual ~CSttLowFreqActPnvTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttLowFreqActPnvTest();
	}
public:

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

protected:
    virtual void TranslateToStateParas();//�ڴ˺�����ʵ�ֽ��غ�բ����ٲ���ת��Ϊ״̬���в���
};
