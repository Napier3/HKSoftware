#ifndef CSTTDRIVEROPER_H
#define CSTTDRIVEROPER_H

#include <QObject>
#define DAPARAADDR 0

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

public:
	static void setAnalogMeas(char* pBuff,int nLen);
	static void setOutPutTap(int nTap);
	static int setDeviceDaPara(char* pbuff,int nLen);
	static void setMeasTap(int nTap);
	static void setDelayOverload(int nDelay);
	static void setOutPutStatue(int nValue);
	static void setManualAcAnalogPara(char* pBuff,int nLen);
	static void setInputShake(int nDelay);
	static void readMeasdata(char* pBuff,int nState);
	static void Stop();
	static void setDCoutput(long nDCValue);
	static void Start(int nValue);
	//数字量数据下发
	static void WriteFPGAData(unsigned long nAddr,unsigned long data);
	//Ioctrl
	static void IoCtrl(unsigned long ncmd,unsigned long nValue);
	static void Init();
	static int readManualResult(char* buff,int nSize);
	static void setStatePara(char* pBuff,int nLen);
	static void setSearchAcAnalogPara(char* pBuff,int nLen,int Statue);
public:
    //2019-102  lijq 全局唯一对象，定义静态函数用于外部调用
    static void InitDriver(int nfd);

	long getTemprature();
	long getStartTime();


	void keepStop();
	void setStartTime(unsigned long nSecond,unsigned long nNaSecond);

	//模拟量数据下发
	void WriteRegister(unsigned long nAddr,unsigned long data);



	//模拟量下发
	void WriteFPGAAnalog(char* buff,unsigned long nLen);
	void WriteAnalogSync();


	//Manual Interface
	//ReadManualResult

	int readStateResult(char* buff);
	int readDiffResult(char* buff);
	int readDisResult(char* buff);
	int readSearchResult(char* buff);
	int readDisBinStatePara();
	//
	void SetisStopIfBiChanged(int nValue);
	void SetStopDelayTime(int nTime);
	void SetBinaryOut(int nState);
	void SetBinaryInLogic(int nLogic);
 // is use




	//state oper

	void setStateTrigerManual();

	void setDiffAcAnalogPara(char* pBuff,int nLen,int Statue);
	void setDisAcAnalogPara(char* pBuff, int nLen, int State);



	int setRelayConfData(char* pbuff,int nLen);
	int setRelayData(char* pbuff,int nLen);
	int readRelayIrp();

	int setRampPara(char* pbuff,int nLen);

	//read DeviceInnerPara
	int readDeviceInnerPara(char* pbuff);

	int SaveDevicePara(char* pbuff,int nLen);


	//setFlash
	int setFlashData(char* pbuff,int nLen,int nAddr=0,int nMode=1);
	int readFlashData(char* pbuff,int nLen,int nAddr=0,int nMode=1);

	int setKeepSendData(char* pBuff,int nLen);

	int updateFpga(char* pbuff,int nLen,int nModule);
	int sendUpdateFpgaOver();
	int ReadupdateFpga(char* pbuff,int nType);
	int ReadupdateFpgaState();
	int SetSmallTap(int nTap);

private:


signals:

public slots:
};

#endif // CSTTDRIVEROPER_H
