#pragma once

#include "SttImpBaseTest.h"
#include "tmt_over_current_test.h"


class CSttOverCurrentTest : public CSttImpBaseTest ,public tmt_OverCurrentParas
{
public:
    CSttOverCurrentTest();
    virtual ~CSttOverCurrentTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttOverCurrentTest();
	}
public:

	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);

protected:
	 virtual void TranslateToStateParas();//�ڴ˺�����ʵ�ֽ��غ�բ����ٲ���ת��Ϊ״̬���в���

protected:
	tmt_OverCurrentResults m_oResults;
};
