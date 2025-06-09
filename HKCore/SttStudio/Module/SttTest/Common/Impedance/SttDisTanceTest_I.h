#pragma once

#include "SttDisTanceTest.h"

class CSttDisTanceTest_I : public CSttDisTanceTest ,public tmt_DistanceParas_I
{
public:
    CSttDisTanceTest_I();
    virtual ~CSttDisTanceTest_I(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;
    static CSttTestBase* CreateTest()
	{
        return new CSttDisTanceTest_I();
	}
public:

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual long CalReport(UINT nState=0);

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);

protected:
	virtual void TranslateToStateParas();//在此函数中实现将重合闸后加速参数转换为状态序列参数

};
