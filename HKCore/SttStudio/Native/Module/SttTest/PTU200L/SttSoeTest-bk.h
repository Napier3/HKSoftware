#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"tmt_soe_test.h"

typedef struct{
	unsigned int init_time[8]; //��ʼʱ��
	unsigned int firstfliptime[8]; // ��һ�η�תʱ��
	unsigned int secondfliptime[8]; // �ڶ��η�תʱ��
	unsigned int flipcnt[8]; //��ת����
	unsigned int init_val[8]; //��ʼֵ
}Drv_SoeState;

typedef struct{
	unsigned int triptype; //0: �������� 1: GPS ����
	unsigned int sec;           //GPS s
	unsigned int nsec;          //GPS ns
	unsigned int holdtime;      //����ʱ�����ֵ
	Drv_SoeState soe;
}Drv_SOETest;

//ʱ�䵥λ�� 100us
//��ʼֵ��0 ��  1 ��

class CSttSoeTest : public CSttTestBase, public tmt_SoeTest
{
public:
	CSttSoeTest();
	virtual ~CSttSoeTest(void);

	Drv_SOETest     m_oDrv_SOETest;

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

	static CSttTestBase* CreateTest()
	{
		return new CSttSoeTest();
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
	//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
	virtual void AfterSetParameter();

	virtual long CalReport(UINT nState=0);

public:
	virtual void Init();
	virtual long SetParameter(DWORD dwState=0);
	virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
	virtual void StartTest();
	virtual void EventProcess();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Stop();
	virtual BOOL NeedReadDeviceStatatus() {return FALSE;}

};
