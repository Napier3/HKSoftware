#ifndef CSTTDEVICE_H
#define CSTTDEVICE_H

#include <QObject>
#include "QtCore"
#include "QMap"
#include "QList"
#include "../../SttTest/PTU/define.h"
#include "stdafx.h"
#include "../SttDeviceBase.h"
#include "SttDriverOper.h"
#include "../../SttTest/PTU/protobuf/DeviceInnerPara.pb.h"
#include "../../SttTest/PTU/protobuf/hqyBinaryInSetting.pb.h"
#include<fstream>
#include "../../SttTest/PTU/tmt_set_parameter.h"


#define MAXCHANELNUM 6
#define TEMPCOUNT 20
#define HARMCOUNT  63
#define MaxNum 65536

//DAPara Send to Driver
typedef struct{
	unsigned long nvolt;
	unsigned long ncurrent;
}DeviceDAPara;

union ConverStruct {
	unsigned char b[4];
	unsigned long l;
	float f;
};//4涓瓧鑺傦紝鍒╃敤鍏辩敤浣擄紝杩涜杞崲

class CSttDevice : public QObject,public CSttDeviceBase
{
	Q_OBJECT

private:
	explicit CSttDevice(QObject *parent = 0);
	static long g_nSttDeviceRef;

public:
	static void Create();
	static void Release();

	static CSttDevice *g_pSttDevice;	

public:
	unsigned long getAnalogUMaxNum(){return 6;}
	unsigned long getAnalogIMaxNum(){return 6;}
	float getUdcMaxNum(){return 300;}
	float getAnalogVoltMax(){return 300;}
	float getAnalogCurrentMax(){return 20;}

	virtual void CloseDevice();
	virtual BOOL SetParameter(CSttXmlSerializeBase *pXmlSierialize);
	virtual BOOL IsStartTest_UserParameter();
	virtual void StartTest_UserParameter();
	void setTap();
	BOOL m_bStartTest_UserParameter;
	tmt_Paras otmt_Paras;
	Drv_ManuPara m_oDrvManuPara;
public:
	float m_fIDa;
	bool m_bAuto;
	float m_fVamp[4][4][31]; //交流电压幅值 //通道 档位 频率
	float m_fVphe[4][4]; //交流电压相位
	float m_fVzero[4][4];//交流电压零漂
	float m_fIamp[5][2][31];//交流电流幅值
	float m_fIphe[5][2];//交流电流相位
	float m_fIzero[5][2];//交流电流零漂

	float m_fIamp1[5][2][31];//交流电流幅值
	float m_fIphe1[5][2];//交流电流相位
	float m_fIzero1[5][2];//交流电流零漂

	float m_fVampMeas[4][5];
	float m_fVpheMeas[4][5]; //交流电压相位 通道 档位
	float m_fVzeroMeas[4][5];//交流电压零漂 通道 档位
	float m_fIampMeas[5][5];//交流电流幅值 通道 档位
	float m_fIpheMeas[5][5];//交流电流相位 通道 档位
	float m_fIzeroMeas[5][5];//交流电流零漂
	float m_fVDcoutput[4];//直流电压输出
	float m_fVDcoutputzero[4];
	float m_fIDcinput[8];//直流测量电流
	float m_fIDcinputzero[8];
	float m_fVDcinput[4];//直流测量电压,零漂
	float m_fILarge[5];
	float m_fILarge1[5];
	float m_fIDcoutput[2];
	float m_fIDcoutputzero[2];

	float m_fSmallOut[8][3][31];//小信号输出 通道 档位 频率
	float m_fSmallOutphe[8];
	float m_fSmallOutzero[8];

	void InitDevice();
	void InitDApara();
	void UpdateDApara(double params[]);
	void ReadCompensation();	

	void setCurrentDa(float fValue){m_fIDa = fValue;}
	float getCurrentDa(){return m_fIDa;}
	void setAuto(bool bAuto){m_bAuto = bAuto;}
	bool getAuto(){return m_bAuto;}
	hqyBinaryInPackage::BinaryInFD getBinaryInFD(float fThreadHold);
	void SetbinarySetting(hqyBinaryInPackage::BinaryinSetting* pSetting);
	hqyBinaryInPackage::BinaryinSetting* m_pBianryInSetting;
	QMap<hqyBinaryInPackage::BinaryInFD,int> m_vBinarySetting;
	void InitBinaryInSetting();
	int getBinaryFDCode(hqyBinaryInPackage::BinaryInFD nFD);
	void SetDeviceInnerParaSet(float *fValue);
	void TranslateACVoltBuffer(float fAmp,float fPh,float fFre,int nChanIndex, long* pBuff,int nHarmIndex=0);
	void TranslateACVoltBufferDC(float fAmp,int nChanIndex,long* pBuff);
	void TranslateACCurrentBuffer(float fAmp,float fPh,float fFre,int nChanIndex, long* pBuff,int nHarmIndex=0);
	void TranslateACCurrentBufferDC(float fAmp,int nChanIndex,long* pBuff);
	long TRanslateDcVolt(float fVDc);
	void TranslateDCCurrent(float fCurrent,long* pBuff);
};

#endif // CSTTDEVICE_H
