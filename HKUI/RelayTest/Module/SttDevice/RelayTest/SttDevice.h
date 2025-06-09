#ifndef CSTTDEVICE_H
#define CSTTDEVICE_H

#include <QObject>
#include "QtCore"
#include "QMap"
#include "QDateTime"
#include "QList"
#include "drv_define.h"
#include "stdafx.h"
#include "../SttDeviceBase.h"
#include "SttDriverOper.h"
#include<fstream>

#include "../../SttTest/Common/tmt_adjust_sys_parameter.h"
#include "../SttDeviceStatus.h"

#define TEMPCOUNT 20
#define HARMCOUNT  63
#define MaxNum 65536
#define ConfigPath "/mnt/sysconfig/developer.set"

typedef struct{
	unsigned int dat[SYS_INFO_COUNT];
}Drv_FeedBack;

typedef struct{
	unsigned int tmFlag;        //bit; 0 GPS   1 BCode
	unsigned int tm_h;          //秒
	unsigned int tm_l;          //纳秒
	Drv_FeedBack stBack[8<<1]/*MODULE_MAX]*/;//module 8 1,2,4,8,16,32,64,128
}Drv_SysInfo;

union ConverStruct {
	unsigned char b[4];
	unsigned long l;
	float f;
};//4个字节，利用共用体，进行转换

typedef struct{
   unsigned int flag;
   unsigned int version[10];
}Drv_BoardVersion;

//DAPara Send to Driver
typedef struct{
	unsigned long nmodule[4];
	unsigned long nvolt[4];
}DeviceDAPara;


class CSttDevice : public QObject,public CSttDeviceBase
{
	Q_OBJECT

private:
	explicit CSttDevice(QObject *parent = 0);
	static long g_nSttDeviceRef;

public:
	static void Create(int fd);
	static void Release();

	static CSttDevice *g_pSttDevice;
	static void GetTMTChannels(int nRampChannel,QVector<int> &ChannelVolts,QVector<int> &ChannelCurrs);
	void setDApara(float fSum,int nModuleIndex,int nModuleType,float fImax=0);
	void setCurrentDCDApara(float fSum,int nModuleIndex);
	void SetCurrentPowerMode(int nMode,float fSetChIMax,int nModuleIndex=0,float fSetVolt=0);

	void AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack,int nModulePos,BOOL IsVolt=FALSE);
	DeviceDAPara oDAPara;
	Drv_BoardVersion m_oBoardinfo;
	Drv_SysInfo *m_pSysInfo;

public:
	virtual void OnTimer();
	virtual void SetTestStart(int nTestType);
	virtual void SetTestStop();
	virtual void SetTestPara(int nTestType,char *pszBuff,int nLen);
	virtual void SetManualBI(char* pszBuff,int nLen);
	virtual void SetStateTriger();
	virtual int GetTestResult(ResultType,char *pszBuff);

	virtual void SetRecordStart();
	virtual void SetRecordStop();
	virtual void SetGooseSub(char* pszBuff,int nLen);

	virtual BOOL TransDigitalVolToDrv(float fAmp,float fAng,float fFre,int nGroupIndex,unsigned int *pnDrvData,int ndigmoduleindex=0);
	virtual BOOL TransDigitalCurToDrv(float fAmp,float fAng,float fFre,int nGroupIndex,unsigned int *pnDrvData,int ndigmoduleindex=0);

	virtual int TransDigitalVolAmp(float fValue,int nGroup,bool bDC);
	virtual int TransDigitalCurAmp(float fValue,int nGroup,bool bDC);
	virtual long TranslateDigitalFre(float fFre);

	virtual int GetDrvChannel_Digital(int Group,int nModuleType,ValueType eType);

	virtual int GetReplayIrp();
private:
	void InitDevice();
	void setBCodeTime(QDateTime tm);
	void InitDApara();
	float getDigitalPhRatio(int nModule);
	CString TransVersion(unsigned int nVal);	
	int m_nCurrentPowerMode;
};

#endif // CSTTDEVICE_H
