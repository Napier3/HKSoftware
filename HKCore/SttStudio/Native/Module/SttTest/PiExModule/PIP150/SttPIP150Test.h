#pragma once

#include"../../../SttTestBase/SttTestBase.h"

class CSttPIP150Test : public CSttTestBase
{
public:
	CSttPIP150Test();
	virtual ~CSttPIP150Test(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
	static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
		return new CSttPIP150Test;
    }
public:
    UINT m_uStartTimeS;
    UINT m_uStartTimeMS;
    UINT m_uChangeTime;
    UINT m_uChangeTimeMS;
    UINT m_uStartTimeNS;
    bool m_bIsReturn;
    UINT m_uReturnTimeMS;
    UINT m_uReturnTime;

public:
    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
