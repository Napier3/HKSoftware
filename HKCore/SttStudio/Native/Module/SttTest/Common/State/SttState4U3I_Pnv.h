#pragma once

#include "SttState6U6I_Pnv.h"

class CSttState4U3I_Pnv : public CSttState6U6I_Pnv//, public tmt_StateTest
{
public:
    CSttState4U3I_Pnv();
    virtual ~CSttState4U3I_Pnv(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttState4U3I_Pnv();
	}

public:
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Para_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize);
};





