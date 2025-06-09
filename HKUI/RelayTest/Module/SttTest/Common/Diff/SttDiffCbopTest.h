#pragma once

#include "../SttStateTest.h"
#include "tmt_diff_cbop_test.h"
#include "../../../SttTestBase/SttDiffCurrCalculatTool.h"


class CSttDiffCbopTest : public CSttStateTest ,public tmt_DiffCBOpParas
{
public:
    CSttDiffCbopTest();
    virtual ~CSttDiffCbopTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttDiffCbopTest();
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
	virtual void TranslateToStateParas();
    virtual void SetStatePreFault_6U6I();//�ڴ˺��������ù���ǰ��ѹ���������뿪����,�����ù���̬��ѹֵ
    tmt_DiffCBOpResults m_oResults;
	CSttDiffCurrCalculatTool m_oDiffCalTool;
};
