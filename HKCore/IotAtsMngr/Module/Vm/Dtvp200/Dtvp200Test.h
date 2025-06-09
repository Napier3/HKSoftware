#pragma once

#include <math.h>
#include <winsock.h>
#include "../../../../Module/Serial/Serial.h"
#include "../../../../Module/Serial/SerialConfig/SerialConfig.h"
#include "../../../../Module/DataMngr/DataGroup.h"

#define Comm_Text_ReceiveLens 22
#define Comm_Text_SendLens 14

#define DTVP_TIMER_NUMBER_JUDGERSLT 	100     //下位机100ms判断误差，确定是否测试结束
#define DTVP_TIMER_NUMBER_READMEAS  	2000    //上报实时数据

#define DTVP_MACRO_ID_SetEnable				_T("SetEnable")
#define DTVP_MACRO_ID_AngleSet				_T("AngleSet")
#define DTVP_MACRO_ID_StopTest				_T("StopTest")

#define DTVP_PARA_ID_PitchEnable			_T("PitchEnable")
#define DTVP_PARA_ID_PositionEnable			_T("PositionEnable")
#define DTVP_PARA_ID_OutputTime				_T("OutputTime")
#define DTVP_PARA_ID_PitchWrokModel			_T("PitchWrokModel")
#define DTVP_PARA_ID_PitchAngleControl		_T("PitchAngleControl")
#define DTVP_PARA_ID_PitchSpeedControl		_T("PitchSpeedControl")
#define DTVP_PARA_ID_PositionWrokModel		_T("PositionWrokModel")
#define DTVP_PARA_ID_PositionAngleControl	_T("PositionAngleControl")
#define DTVP_PARA_ID_PositionSpeedControl	_T("PositionSpeedControl")

#define DTVP_RESULT_ID_PitchAngle			_T("PitchAngle")
#define DTVP_RESULT_ID_PositionAngle		_T("PositionAngle")

//指令设置
#define DTVP_SET_ORDER_NOSET      0   //未设置
#define DTVP_SET_ORDER_SETENABLE  1   //设置使能
#define DTVP_SET_ORDER_SETANGLE   2   //设置转动

class CDtvp200Test
{
public:
	CDtvp200Test();
	virtual ~CDtvp200Test(void);

	CSerial m_Serial;

	//设置的参数
	int m_nEnable[2];		//使能 0-俯仰 1-方位
	int m_nWrokModel[2];	//控制工作模式（0：绝对位置，1：相对位置）0-俯仰 1-方位
	int m_nAngleControl[2];//控制角度  0-俯仰 1-方位(精度0.001)也就是说这里填1000 实际上是1	 想要反着转,得设置成负的
	int m_nSpeedControl[2];//控制速度  0-俯仰 1-方位(精度0.001)也就是说这里填1000 实际上是1

	//读取的实际值
	int m_nPitchRtAngle;//内框角度   精度0.001
	float m_fPitchRtAngle;//内框实际角度
	int m_nPitchRtSpeed;//内框速度
	int m_nPitchRtEnable;//内框状态 0-电机自由 1-电机使能
	int m_nPitchRtArrive;//内框到达 0-未到达指定位置 1-到达指定位置

	int m_nPositionRtAngle;//外框角度   精度0.001
	float m_fPositionRtAngle;//外框实际角度
	int m_nPositionRtSpeed;//外框速度
	int m_nPositionRtEnable;//外框状态 0-电机自由 1-电机使能
	int m_nPositionRtArrive;//外框到达 0-未到达指定位置 1-到达指定位置

	//计时器
	BOOL m_bIsXTimerRunning;
	//指令设置
	int m_nOrderSetting;//0-未设置 1-设置使能 2-设置转动
	long m_nRunTime;
	long m_nJudgeCount;  //为了防止抖动，对内框、外框转动速度的影响，设置

public:
	BOOL IsConnectSuccess()	{	return m_nIsConnectSuccess;		}
	CString GetLastError()	{	return m_strError;	}
	BOOL IsTestFinish();
	BOOL Connect();
	BOOL DisConnect();
	LONG Test( const CString &strMacroID);
	void StopTest();

	int receive_answer();

private:
	
protected:
	ULONG m_nIsConnectSuccess;//连接状态
	CString m_strError;  //错误码

	void SetEnable(BYTE *cmd,int nOrder);
	void AngleSet(BYTE *cmd,int nOrder);
	BYTE CRC16(BYTE *cmd,int nLength);
	int Cal4ByteToInt(BYTE *byteContext,int nIndex);//小端
	int GetHeigthByte(BYTE byteValue);
	int GetLowByte(BYTE byteValue);

	int send_command(BYTE *cmd);
	void InitParas();
};