#pragma once

#include "../SttManuTest.h"

class CSttUITest12U12I_Pnv : public CSttManuTest
{
public:
    CSttUITest12U12I_Pnv();
    virtual ~CSttUITest12U12I_Pnv(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttUITest12U12I_Pnv();
	}

public:
//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};





