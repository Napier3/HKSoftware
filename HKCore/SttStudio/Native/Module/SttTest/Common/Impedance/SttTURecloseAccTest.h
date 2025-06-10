#pragma once
#include "SttRecloseAccTest.h"

class CSttTURecloseAccTest : public CSttRecloseAccTest
{
public:
    CSttTURecloseAccTest();
    virtual ~CSttTURecloseAccTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttTURecloseAccTest();
	}
public:
	virtual void Init();
	virtual void AfterSetParameter();
	virtual void StartTest();

protected:
	virtual void TranslateToStateParas();//�ڴ˺�����ʵ�ֽ��غ�բ����ٲ���ת��Ϊ״̬���в���
};
