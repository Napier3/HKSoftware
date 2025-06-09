#pragma once


#include <math.h>
#include <winsock.h>
#include "../../../../Module/Serial/Serial.h"
#include "../../../../Module/Serial/SerialConfig/SerialConfig.h"
#include "../../../../Module/DataMngr/DataGroup.h"
// #include "FileWriteApi.h"


#define GUBEI_PARA_ID_Temperature  _T("Temperature")
#define GUBEI_PARA_ID_Humidity        _T("Humidity")

#define GUBEI_PARA_ID_JdgType	_T("JdgType")
#define GUBEI_PARA_ID_AbsErr	_T("AbsErr")
#define GUBEI_PARA_ID_RunTime	_T("RunTime")
#define GUBEI_PARA_ID_LogicOr	_T("LogicOr")

#define GUBEI_PARA_IDX_RunTime	_T("0")
#define GUBEI_PARA_IDX_AbsErr	_T("1")
#define GUBEI_PARA_IDX_LogicOr	_T("2")

//yzj 2021-10-7 ��ʱ�������finishʱÿ�μ�ʱ�����ٵ�ʱ��
#define GUBEI_TIMER_NUMBER	10000

#define GUBEI_MACRO_ID_Config        _T("Config")
#define GUBEI_MACRO_ID_ReadMeas        _T("TempRead")
#define GUBEI_MACRO_ID_ManualTest        _T("TempSet")
#define GUBEI_MACRO_ID_StopTest        _T("StopTest")
#define GUBEI_MACRO_ID_StopManualTest        _T("StopManualTest")

//���ܶ�Ӧ�ļĴ�����ַ
enum ADDR_REG 
{ 
    ADDR_SET_TEMP = 0x0000,//�趨�¶�
    ADDR_SET_TIME = 0x0001,//�趨ʱ��
    ADDR_MOD_TEMP  = 0x0002,//�¶�����
    ADDR_ALARM_TEMP_H = 0x0003,//���±���
    ADDR_YSJ_DELAY = 0x0012, //��Դ����
    ADDR_ZL = 0x0013,//���俪��
    ADDR_SB= 0x0014,//ˮ�ÿ���
    ADDR_ZL_MODE = 0x0018,//����ģʽ
   ADDR_GET_TEMP = 0x2100, //�����¶�
   ADDR_GET_TIME  = 0x2101//ʣ��ʱ��

}; 


class CGuBeiTest
{
public:
	CGuBeiTest();
	virtual ~CGuBeiTest(void);

	CSerial m_Serial;

	CString m_strIP;
	unsigned short m_nPort;
	CString  m_strAddress;

	//��������
	float m_fTemperature;
	float m_fHumidity;//2023.3.6
	long m_nProgramNumber;
	//yzj 2021-10-7 ���ý����ж�����
	CString m_strJdgType;
	float m_fRunTime;
	float m_fAbsErr;
	

	//��ʱ��
	BOOL m_bIsXTimerRunning;

	//��ȡ��ʵʱֵ
	float m_fTemperature_Read;
	float m_fHumidity_Read;//2023.3.6

public:
	BOOL IsConnectSuccess()	{	return m_nIsConnectSuccess;}
	CString GetLastError()	{	return m_strError;	}
	BOOL Connect();
	BOOL DisConnect();
	LONG Test( const CString &strMacroID);
	void StopTest(); 

	//�Ƿ�ִ�в��Խ��������������¶ȡ�ʪ�ȴﵽĿ���趨ֵ
	BOOL IsAbsErrFinished();
	BOOL IsRunTimeFinished();
	virtual BOOL IsTestFinished();

	BOOL IsReadMeasTesting() { return m_bReadMeas; }

private:
	SOCKET m_hSocket;
	WSADATA m_wsaData;

	CString m_strResult;
	CString m_strRespond;

	BOOL m_bReadMeas;//��ʾ���͵������Ƕ�ȡ����ֵ
	
public:
	ULONG m_nIsConnectSuccess;//����״̬
	CString m_strError;  //������

	int send_command(BYTE *cmd, int len);
	int receive_answer();
	unsigned int crc_chk(BYTE *data,unsigned char length);
	int SendASCII_OneCommand();
	int SendASCII_TwoCommand();
	

	CString Cmd_ReadMeas();     //��ȡʵ��ֵ
	CString Cmd_Run();
	CString Cmd_Stop();

	CString StartingProgram();
	CString ReadingError();
	CString AcknowledgeError();
	CString DescriptionRate();

	CString float_format(float fVal);

    int setTemperature();

    int getOneValue( ADDR_REG addr,   int& value);
    int getTwoValue(ADDR_REG addr,   int& value1,  int& value2);
    //int getValue(ADDR_REG addr,  int* value,  int len);
    int setOneValue( ADDR_REG addr,   int value);
    int setTwoValue(ADDR_REG addr,   int value1,  int value2);
    int Cal4ByteToInt( BYTE *byteContext, int nIndex);
    //int setValue(ADDR_REG addr,  int* value,  int len);
};