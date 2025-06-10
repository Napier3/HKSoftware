#ifndef CSTTDRIVEROPER_H
#define CSTTDRIVEROPER_H

#include <QObject>
#include <unistd.h>
#include "drv_define.h"

class CSttDriverOper : public QObject
{
	Q_OBJECT

public:
	static void Create(int nfd);
	static void Release();

private:
	explicit CSttDriverOper(QObject *parent = 0);

	static CSttDriverOper *g_pSttDriverOper;
	static long g_nSttDriverOperRef;

//	static int m_nAnalogSync;
//	static unsigned long m_nModuleSet;

public:
	//2019-102  lijq 全局唯一对象，定义静态函数用于外部调�?
	static void InitDriver(int nfd);
	static void Start(int nValue);
	static void StartIecDetect();
	static void StopIecDetect();
	static int readIecDetectResult(char* pBuff);
	static void StartRecord();
	static void Stop();
	static void StopRecord();
	static void set_optical_port(char *pbuff,int nLen,int nFlag);
	static void setConfigIECCoderData(char* pBuff,int nLen);
	static void setGooseChangedCoderData(char* pBuff,int nLen);
	static void setGooseTestMode(char* pBuff,int nLen);//置检�?
	static void setGooseSubData(char* pBuff,int nLen);
	static void setFT3SubData(char* pBuff,int nLen);
	static void setGooseBoMapData(char* pBuff,int nLen);
	static int readRampResult(char* pBuff);
	static int readStateResult(char* pBuff);
	static int readRecordResult(char* pBuff);
	static void setStatePara(char* pBuff,int nLen);
	static void setStatePara(char* pBuff,int nLen,int nType);
	static void SetModuleInfo(char* pBuff,int nLen);
	static long getTemprature();
	static void setPollingsyncsecond(unsigned int nsync);
	static void setSendAtStop(unsigned long nValue);
	static void setfiberports(int nfiberport);
	static int IoCtrl(unsigned long ncmd,unsigned long nValue);
	static int setDeviceDaPara(char* pBuff,int nLen);
	static void startDMA();
	static void setFilter(int nFilter);
	static void stopDMA();
	static  void setStateTrigerManual();
	static void SetBinaryOut(int nState);
	static void SetBinaryOutTurnOnVaule(int nState);
	static void setSwingingPara(char* pBuff,int nLen);
	static void setabnStatePara(char* pBuff,int nLen);
	static void SetCurrent_Multiple(int nType);
	static int readFlashData(char* pbuff,int nMode,int nCmd);
	static void WriteData(char* pBuff,unsigned long nLen);
    static void *getMmapBuffer();
    static bool getLtReplayBufferAFlag();
    static bool getLtReplayBufferBFlag();
    static void setLtReplayBufferAFlag();
    static void setLtReplayBufferBFlag();
     static void setLtReplayBufferLoopFlag();
	static void setRising(int nRising);
	static int ReadPPStime(char* buff);
	static void SetBinaryModule(char *pBuff,int nLen);
	static void setModuleValied(int nModule);
	static int ReadBinaryModule(char* pBuff);
	static int readDeviceInnerPara(char* pBuff);

	void WriteRegister(unsigned long nAddr,unsigned long data);
	void WriteAnalogSync();
	void WriteFPGAData(unsigned long nAddr,unsigned long data);
	void WriteFPGAAnalog(char* buff,unsigned long nLen);


	int readDisBinStatePara();
	int readDisResult(char* pBuff);
	void SetisStopIfBiChanged(int nValue);
	void SetStopDelayTime(int nTime);

	void SetBinaryInLogic(int nLogic);
	static void setManualAcAnalogPara(char* pBuff,int nLen);
	static void setManualBISetting(char* pBuff,int nLen);

	void setDiffAcAnalogPara(char* pBuff,int nLen,int Statue);
	void setSearchAcAnalogPara(char* pBuff,int nLen,int Statue);
	void setDisAcAnalogPara(char* pBuff, int nLen, int State);
	void setDcPowerValue (char *pChar);

	int setFlashData(char* pbuff,int nLen,int nMode);

	int setFlashReadCmd(int module);
	int readFlashDataState(char* pbuff);
	static int setRelayData(char* pBuff,int nLen);
	static int setRelayConfData(char* pBuff,int nLen);
    static int setLtRelayConfData(char* pBuff,int nLen);
	static int readReplayIrp();
	static int setRampPara(char* pBuff,int nLen);
	static int getUpdateFpgaPrecent();

	void setCurrentMerge(unsigned int nMerge);

	int updateFpga(char* pbuff,int nLen,int nModule);
	int ReadupdateFpga(char* pbuff,int nType);
	int ReadupdateFpgaState();
	int sendUpdateFpgaOver();

	int readDMA(char* buffer);

	void setDcModuleTap(int nTap);
	void SetStopDcOutput(char *pBuff,int nLen);

	void SetSyncPara(char *pBuff,int nLen);
	int ReadSyncResult(char* pBuff);

private:


signals:

public slots:
};

#endif // CSTTDRIVEROPER_H
