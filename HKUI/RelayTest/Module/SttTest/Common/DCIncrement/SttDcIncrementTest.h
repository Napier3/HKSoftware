#pragma once

#include "../SttStateTest.h"
#include "tmt_dc_increment_test.h"


class CSttDcIncrementTest : public CSttStateTest ,public tmt_DcIncrementParas
{
public:
    CSttDcIncrementTest();
    virtual ~CSttDcIncrementTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttDcIncrementTest();
	}
public:

	virtual void Init();
	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

	virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent);
	virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent);
	virtual void SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void SyncSingleStateTmtResult();
//	virtual BOOL IsGradientFinished();

protected:
//	BOOL CalNext();
	virtual void TranslateToStateParas();//�ڴ˺�����ʵ�ֽ��غ�բ����ٲ���ת��Ϊ״̬���в���
	long GetDcIncActTime(float &fAcgtTime);

// 	long m_nRunSearchCount;//��ǰ���������Ĵ���,��ʼֵΪ1
// 	long m_nGradientCount;//�ݱ��ܴ���,��ʼ��Ϊ0 ,�ڲ������ú��趨��ֵ
	tmt_DcIncrementResults m_oResults;
};
