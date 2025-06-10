#ifndef CSTTDEVICEPIK100_H
#define CSTTDEVICEPIK100_H

#include "stdafx.h"
#include "../Module/Driver466/SttDeviceComm.h"
#include "../../SttTest/PIK100/tmt_pik100_test.h"
#define BIT0  0x0001
#define BIT1  0x0002
#define BIT2  0x0004
#define BIT3  0x0008
#define BIT4  0x0010
#define BIT5  0X0020
#define BIT6  0X0040
#define BIT7  0X0080
#define BIT8  0X0100
#define BIT9  0X0200
#define BIT10  0X0400
#define BIT11  0X0800
#define BIT12  0x1000
#define BIT13  0x2000
#define BIT14  0x4000
#define BIT15  0x8000
#define BIT16  0x10000
#define BIT17  0X20000
#define BIT18  0X40000
#define BIT19  0X80000
#define BIT20  0X100000
#define BIT21  0X200000
#define BIT22  0X400000
#define BIT23  0X800000
#define BIT24  0x1000000
#define BIT25  0x2000000
#define BIT26  0X4000000
#define BIT27  0X8000000
#define BIT28  0X10000000
#define BIT29  0X20000000
#define BIT30  0X40000000
#define BIT31  0X80000000
//#define BIT32  0X100000000


#define InitXS 0x40000000
typedef struct{
   long DCSendbuffer[10];
}DCpbufferdata;
extern DCpbufferdata DCbuffer;
typedef struct{
   quint32 ACSendbuffer[20];
}ACpbufferdata;
extern ACpbufferdata ACbuffer;
typedef struct{    ///所有的输入量在输入之后全部转换为10mV单位值
	float temp1;//散热器1温度
	float temp2;//散热器2温度
	float temp3;//片上温度
	std::string EquipmentModel;

}StructModePara;
extern StructModePara StrModePara;
class CSttDevicePIK100 : public CSttDeviceComm,public CSttDeviceBase
{
private:
	explicit CSttDevicePIK100();
	static long g_nSttDeviceRef;
	 int SENDAtoFPGA(quint32 VALUE,int ADDR);
	 int Send_To_Fpga(char* pbuff,int nLen,int nMode);
	 void READformHEX(quint32 *VALUE,int ADDR);
	 void Print_Para(tmt_pik100_DA da);
	 void Print_KCKR();
public:
	static void Create();
	static void Release();

	static CSttDevicePIK100 *g_pSttDevicePIK100;

	virtual int InitDevice(BOOL bHasAdjFile);

	//pis2k
	virtual void tmt_to_drv_pik100(void *pTmt);
	virtual void ProPik100DrvResult();
//	virtual void close_pik100();
	virtual BOOL OnTimer(BOOL bExec = FALSE);
	virtual void tmt_to_drv_systemdefaultoutput(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pTmt);
//	virtual void SetTestStart(int nTestType);
	virtual void SetTestStop(BOOL bIsSysDefaultOutput=FALSE);
};

#endif // CSTTDEVICEPIS2K_H
