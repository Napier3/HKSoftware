#pragma once

#include "SttZeroCurrentTest.h"


class CSttStateZeroCurrentTest : public CSttZeroCurrentTest
{
public:
    CSttStateZeroCurrentTest();
    virtual ~CSttStateZeroCurrentTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttStateZeroCurrentTest();
	}
public:

	virtual void AfterSetParameter();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Init();

protected:
	virtual void TranslateToStateParas();//�ڴ˺�����ʵ�ֽ��غ�բ����ٲ���ת��Ϊ״̬���в���
};
