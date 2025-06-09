#pragma once
#include "..\..\..\..\Module\Serial\Serial.h"
#include "SourceDKDef.h"

class CSourceDK51E1 : public CSerial
{
public:
	long m_nBaudRate;
	long m_nByteSize;
	long m_nParity;
	long m_nStopBits;//停止位的0,1,2对应1,1.5,2

	long m_nRxID;//接收终端的设备号
	long m_nTxID;//发送终端的设备号

	BYTE m_strData[1024];//output
	CString m_strBuffer;//input

	CDataGroup* m_pReport;//用于timer的数据上报(电压电流)

	CString m_strCurProcedure;//当前命令
	BOOL m_bIsXTimerRunning;//是否启动了计时器

private:
	BOOL m_bIsConnected;

public:
	CSourceDK51E1();
	virtual ~CSourceDK51E1();

private:
	float ByteArr_To_Float(const char* pByteArr);//Byte数组转float
	long CString_htonl(const CString& strNum);//高低位转换
	float CString_To_Float(const CString& strNum);
	CString CString_To_Float_Str(const CString& strNum);
	CString Float_To_CString(float fNum);
	void Generate(long nProcedureID, const CString& strData, long& nByteLen);//生成通用命令模板
	long GetXOR(BYTE* strMsg, long nLen);//计算异或

private:
	//由自动测试调用后发送串口命令的函数
	CString SetACGear(tagDKSource* pDKSource);//设置源档位参数
	CString SetACRange(tagDKSource* pDKSource);//设置源幅度参数
	CString SetACPhase(tagDKSource* pDKSource);//设置源相位参数
	CString SetACRate(tagDKSource* pDKSource);//设置源频率
	CString SetACPrinciple(tagDKSource* pDKSource);//设置源接线模式
	CString SetACEnableLoop(tagDKSource* pDKSource);//闭环控制使能
	CString SetACVerification(tagDKSource* pDKSource);//设置电能校验并启动
	CString SetACActivePower(tagDKSource* pDKSource);//设置有功功率
	CString SetACReactivePower(tagDKSource* pDKSource);//设置无功功率
	CString SetDCAmp(tagDKSource* pDKSource);//设置直流源幅值
	CString SetSysMode(tagDKSource* pDKSource);//设置系统模式
	CString SetSysPage(tagDKSource* pDKSource);//设置终端当前显示界面
	CString SetDCRange(tagDKSource* pDKSource);//设置直流源幅值
	CString SetDCMeasurementType(tagDKSource* pDKSource);////设置直流表测量类型
	CString SetDCGear(tagDKSource* pDKSource);//设置直流源档位参数
	CString SetRemoteOutput(tagDKSource* pDKSource);//设置数字量输出口的状态
	CString SetRemoteControl(tagDKSource* pDKSource);//发送系统控制命令
	CString SetACHarmonicParam(tagDKSource* pDKSource);//设置谐波参数

	void GetACError(CDataGroup* pDataGroup);//读电能误差
	void GetDCParam(CDataGroup* pDataGroup);//读交流标准表参数
	void GetACParam(CDataGroup* pDataGroup);//读直流源参数
	void GetRemoteInputState(CDataGroup* pDataGroup);//读数字量输入输入口的当前状态
	void GetDCMeasurementParam(CDataGroup* pDataGroup);//读直流表测量参数

public:
	BOOL IsConnectSuccess()	{	return m_bIsConnected;	}
	BOOL Connect(long nComNumber);
	BOOL Disconnect();
	long CloseDevice();

	BOOL RunProcedure(tagDKSource* pDKSource, long nParamNum = 0);//串口写命令

	CDataGroup* ParseBuffer();//串口读命令
	void GetReport(CString& strDCReport, CString& strACReport);//获取RTDATA报文
};