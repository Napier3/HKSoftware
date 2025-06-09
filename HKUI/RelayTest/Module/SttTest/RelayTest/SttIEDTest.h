#ifndef STTIEDTEST_H
#define STTIEDTEST_H

#include"../../SttTestBase/SttTestBase.h"
#include "tmt_ied_test.h"
#include "drv_state_test.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#include "../../SttDevice/RelayTest/SttDevice.h"
#include "IEC61850CfgMngr.h"
#endif
#include "QThread"
#include "../../../Module/Socket/Qt/WinTcpSocket.h"
#include "QTime"


typedef struct{
	unsigned int nTmHigh;				//�ߵ�ƽʱ�䳤�Ⱥ���
	unsigned int nTmLow;				//�͵�ƽʱ�䳤�Ⱥ���
	unsigned int nflipCnt;				//��ת����
}structSoeParam;

typedef struct{
	unsigned int nModule;			//ģ����
	unsigned int nBinOut[2];				//������ʼֵ
	unsigned int nType[2];			//ʵ������ 0������1ΪSOEʵ��
	structSoeParam param[64];
	unsigned int nDelayTime;//����ǰʱ��
	unsigned int nBeginTime[64];//���ʱ��
}structSoeItem;

typedef struct{
	unsigned int nModuleCnt;		//ģ����
	unsigned int tm_h;		//����ʱ����ֵ
	unsigned int tm_l;		//����ʱ������ֵ
	structSoeItem item[5];
}structSoe;

typedef struct{
	unsigned int module;			//ģ����
	unsigned int bo[2];				//����ֵ
	unsigned int bi[2];				//����ֵ
}structSoeResultItem;


typedef struct{
	unsigned int nType;			//������� 1����ʼ   2��ֹͣ	3��������λ	4�������λ
	unsigned int nModuleCnt;
	unsigned int tm_h;			//ʱ����
	unsigned int tm_l;			//ʱ������
	structSoeResultItem item[5];
}structSoeResult;




typedef struct{
	unsigned int nModule;
	bool bIsVaild;
	double fChgTime[64];	//����ʱ��
	double fBackTime[64];	//����ʱ��
}SoeItem;

typedef struct{
	double fStartTime;	//����ʱ��
	SoeItem item[5];
}SoeResult;

class CSttIEDTest:public tmt_IEDTest,public CSttTestBase
{
public:
	CSttIEDTest(void);
	virtual ~CSttIEDTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;
	static CSttTestBase* CreateTest()
	{
		return new CSttIEDTest();
	}
public:
	virtual void AfterSetParameter();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void StartTest();
	virtual void Stop();
	virtual void EventProcess();	
	//���ϲ�ṹ��תΪ�ײ�ṹ��
public:
	virtual void TtmToDrv();

private:
	char *m_pszResultBuff;
	int   m_nBoutChang;
	DeviceInfo *m_oDeviceInfo;
	structSoe *stBinOut;
	structSoeResult *soeResult;
	int m_nBoNum[4];
	bool m_Start;
	double m_fDelayBeginTime;
	double m_fDelayEndTime;
	CString m_strPreBiVal;//64bit
	CString m_strCurrBiVal;//64bit
	bool m_bChgChan[64];
	SoeResult m_oSoeResult;
	structGSOutMap *m_ostructGSOutMap;
private:	
	void SetBoVal(structSoe &oSoe,int nExBo,int nState);
	void SetDrvBoVal(SwitchModule &oSwitchModule,structSoeItem &oitem,int nExBo,int nState);
	void TtmToDrv_B2G();
	void TtmToDrv_G2B();
	void GetChgNum(CString strPreBiVal,CString strCurrBiVal,bool *bChgChan);
};

#endif // STTRECORD_H
