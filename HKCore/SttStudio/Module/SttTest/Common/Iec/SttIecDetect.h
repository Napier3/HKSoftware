#ifndef STTIECDETECT_H
#define STTIECDETECT_H

#include"../../../SttTestBase/SttTestBase.h"

class CSttIecDetect:public CSttTestBase
{
public:
    CSttIecDetect(void);
    virtual ~CSttIecDetect(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;
	static CSttTestBase* CreateTest()
	{
        return new CSttIecDetect();
	}
public:
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};

#endif // STTRECORD_H
