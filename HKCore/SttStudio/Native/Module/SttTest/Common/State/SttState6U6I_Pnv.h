#pragma once

#include "../SttStateTest.h"

class CSttState6U6I_Pnv : public CSttStateTest//, public tmt_StateTest
{
public:
    CSttState6U6I_Pnv();
    virtual ~CSttState6U6I_Pnv(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttState6U6I_Pnv();
	}

public:
//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Para_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize);
	virtual void ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType){}
};





