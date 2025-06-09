#ifndef CSTTDEVICEPIC200D_H
#define CSTTDEVICEPIC200D_H

#include "stdafx.h"
#include "../Module/Driver466/SttDeviceComm.h"
#include "../../SttTest/PIC200D/tmt_pic200d_test.h"

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
	/*********CCL**********/
	/*********CCH**********/
	float AuotSetValue;
	float DA1_Direct;//da1输出的直流分量，校准时作为零漂
	float DA1_FZ; //da1幅值
	float DA1_Frequency;//da1频率
	float DA1_Phase;//da1相位
	float DA1_acrisetime;
	float DA1_acholdtime;
	float DA1_acdowntime;
	float DA2_FZ;

	float Qualified_resistance;
	float Leakage_Current;


	float VoltageAlarmMin;
	float VoltageAlarmMax;
	float CurrentAlarmMin;
	float CurrentAlarmMax;

	int PIC200DOUTStateFlag;
	int PIC200DStateFlag; //PIS2K状态 StrModePara.PIS2KStateFlag ，0:READY，1：RUN，2：PASS，3：FAIL,
	//4:Remote,5:RUN-Ready,6:Rise,7:Hold,8:Down,9:guo re,10:overload,11:stop
	int PIS2KScreenFlag;
	int WorkModeFlag;
	int LocalRemoteFlag;
	int ADCurrentState;
	int ADCurrentStateold;
	int ADVoltageState;
	int ADVoltageStateold;
	int RotaryLeftCount;
	int RotaryRightCount;
	int RotaryEnterFlag;
	int AdjCloseLoopMode;
	int ACDCModeFlag;  //1:DCout    0:ACout
	int PIC200DGetStateAutoFlag;
	int  PIC200DStatesendbuffer;
	float temp1;//散热器1温度
	float temp2;//散热器2温度
	float temp3;//片上温度
	std::string EquipmentModel;

}StructModePara;
extern StructModePara StrModePara;
class CSttDevicePIC200D : public CSttDeviceComm,public CSttDeviceBase
{
private:
	explicit CSttDevicePIC200D();
	static long g_nSttDeviceRef;
	 void CalculateDMA();
	 int SENDAtoFPGA(int VALUE,int ADDR);
	 void Refresh_state(int State1Value);
	 void AutoCurrentState();
	 void CloseLoop();

	 int Send_To_Fpga(char* pbuff,int nLen,int nMode);
	 void InitCoef();
	 void tmt_to_drv_pic200d(tmt_Pic200dTest *pTmt,BOOL bUseGear);
	 void SetMeasDefault();
	 void SetVoltMeasGear(long nGear);
	 void SetCurrMeasGear(long nGear);
public:
	static void Create();
	static void Release();

	static CSttDevicePIC200D *g_pSttDevicePIC200D;

	virtual int InitDevice(BOOL bHasAdjFile);

	//pis2k
	virtual void tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt);
	virtual void tmt_to_drv_pic200d(void *pTmt);
	virtual void ProPic200dDrvResult(void *pTmt);
	virtual void close_pic200d();
	virtual BOOL OnTimer(BOOL bExec = FALSE);
    virtual void SetTestStop(BOOL bIsSysDefaultOutput=FALSE);
    void ReturnTestEvents_MEAS();
    void stt_xml_serialize_meas_datas(CSttXmlSerializeBase *pXmlSerialize);

	virtual void SetMeasModuleChanGear(int nModuleType,int nModulePos, int nChannel, int nGearId);
	virtual void EventProcessEx();
};

#endif // CSTTDEVICEPIS2K_H
