#pragma once

#include "SttLowFreqActTest.h"


class CSttLowFreqDfDtTest : public CSttLowFreqActTest
{
public:
    CSttLowFreqDfDtTest();
    virtual ~CSttLowFreqDfDtTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttLowFreqDfDtTest();
	}
public:

	virtual void Init();
	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual BOOL IsGradientFinished();

protected:
	virtual void TranslateToStateParas();//�ڴ˺�����ʵ�ֽ��غ�բ����ٲ���ת��Ϊ״̬���в���
};
