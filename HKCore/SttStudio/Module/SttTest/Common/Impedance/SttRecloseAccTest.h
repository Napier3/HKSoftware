#pragma once

#include "../SttStateTest.h"
#include "tmt_reclose_acc_test.h"

class CSttRecloseAccTest : public CSttStateTest ,public tmt_RecloseAccParas
{
public:
    CSttRecloseAccTest();
    virtual ~CSttRecloseAccTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttRecloseAccTest();
	}
public:

	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);
	virtual void StartTest();

protected:
	virtual void TranslateToStateParas();//�ڴ˺�����ʵ�ֽ��غ�բ����ٲ���ת��Ϊ״̬���в���
	tmt_RecloseAccResults m_oResults;
};
//202406251Xuzt ���ó�ȡ��ѹƵ��
void Cal_SetVzFreq(tmt_StatePara *pStatePara, int nVzDefine, float fVzFreq);
