#ifndef STTIECRECORD_H
#define STTIECRECORD_H

#include"../../../SttTestBase/SttTestBase.h"

class CSttIecRecord:public CSttTestBase
{
public:
    CSttIecRecord(void);
    virtual ~CSttIecRecord(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;
	static CSttTestBase* CreateTest()
	{
        return new CSttIecRecord();
	}
public:
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Stop(){}
	virtual void StartTest();
};

#endif // STTRECORD_H
