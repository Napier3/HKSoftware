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
	unsigned int nTmHigh;				//高电平时间长度毫秒
	unsigned int nTmLow;				//低电平时间长度毫秒
	unsigned int nflipCnt;				//翻转次数
}structSoeParam;

typedef struct{
	unsigned int nModule;			//模块编号
	unsigned int nBinOut[2];				//开出初始值
	unsigned int nType[2];			//实验类型 0其它，1为SOE实验
	structSoeParam param[64];
	unsigned int nDelayTime;//故障前时间
	unsigned int nBeginTime[64];//间隔时间
}structSoeItem;

typedef struct{
	unsigned int nModuleCnt;		//模块数
	unsigned int tm_h;		//持续时间秒值
	unsigned int tm_l;		//持续时间纳秒值
	structSoeItem item[5];
}structSoe;

typedef struct{
	unsigned int module;			//模块编号
	unsigned int bo[2];				//开出值
	unsigned int bi[2];				//开入值
}structSoeResultItem;


typedef struct{
	unsigned int nType;			//结果类型 1：开始   2：停止	3：开出变位	4：开入变位
	unsigned int nModuleCnt;
	unsigned int tm_h;			//时间秒
	unsigned int tm_l;			//时间纳秒
	structSoeResultItem item[5];
}structSoeResult;




typedef struct{
	unsigned int nModule;
	bool bIsVaild;
	double fChgTime[64];	//绝对时间
	double fBackTime[64];	//绝对时间
}SoeItem;

typedef struct{
	double fStartTime;	//绝对时间
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
	//将上层结构体转为底层结构体
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
