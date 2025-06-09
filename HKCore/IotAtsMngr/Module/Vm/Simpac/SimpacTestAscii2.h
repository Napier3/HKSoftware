#pragma once


#include <math.h>
//#include "..\Module\ParaObjects.h"
#include <winsock.h>

#define STX 2
#define ETX 3
#define DLIM 182

#define eps 1e-15

#define SIMPAC_PARA_ID_Temperature  _T("Temperature")
#define SIMPAC_PARA_ID_Humidity        _T("Humidity")

#define SIMPAC_PARA_ID_JdgType	_T("JdgType")
#define SIMPAC_PARA_ID_AbsErr	_T("AbsErr")
#define SIMPAC_PARA_ID_RunTime	_T("RunTime")
#define SIMPAC_PARA_ID_LogicOr	_T("LogicOr")

#define SIMPAC_PARA_IDX_RunTime	_T("0")
#define SIMPAC_PARA_IDX_AbsErr	_T("1")
#define SIMPAC_PARA_IDX_LogicOr	_T("2")

//yzj 2021-10-7 ��ʱ�������finishʱÿ�μ�ʱ�����ٵ�ʱ��
#define SIMPAC_TIMER_NUMBER	10000

#define SIMPAC_MACRO_ID_Config        _T("Config")
#define SIMPAC_MACRO_ID_ReadMeas        _T("ReadMeas")
#define SIMPAC_MACRO_ID_ManualTest        _T("ManualTest")
#define SIMPAC_MACRO_ID_StopTest        _T("StopTest")
#define SIMPAC_MACRO_ID_StopManualTest        _T("StopManualTest")


class CSimpacTestAscii2
{
public:
	CSimpacTestAscii2();
	virtual ~CSimpacTestAscii2(void);

	CString m_strIP;
	unsigned short m_nPort;
	CString  m_strAddress;

	//��������
	float m_fHumidity;
	float m_fTemperature;
	long m_nProgramNumber;
	//yzj 2021-10-7 ���ý����ж�����
	CString m_strJdgType;
	float m_fRunTime;
	float m_fAbsErr;

	//��ʱ��
	BOOL m_bIsXTimerRunning;

	//��ȡ��ʵʱֵ
	float m_fHumidity_Read;
	float m_fTemperature_Read;

public:
	BOOL IsConnectSuccess()	{	return m_nIsConnectSuccess;		}
	BOOL Connect();
	BOOL DisConnect();
	LONG Test( const CString &strMacroID);
	void StopTest(); 

	//�Ƿ�ִ�в��Խ��������������¶ȡ�ʪ�ȴﵽĿ���趨ֵ
	BOOL IsAbsErrFinished();
	BOOL IsRunTimeFinished();
	BOOL IsTestFinished();

	BOOL IsReadMeasTesting() { return m_bReadMeas; }

private:
	SOCKET m_hSocket;
	WSADATA m_wsaData;

	CString m_strResult;
	CString m_strRespond;

	BOOL m_bReadMeas;//��ʾ���͵������Ƕ�ȡ����ֵ
	
protected:
	ULONG m_nIsConnectSuccess;//����״̬

	int open_socket(char *ipaddr, unsigned short port, SOCKET *sock);
	int send_command(SOCKET so, char *cmd);
	int receive_answer(SOCKET so);
	char *CheckSum(char *buffer);
	int SendASCII_OneCommand(CString strCommand);
	int SendASCII_TwoCommand(CString strCommand);
	

	CString Cmd_ReadMeas();     //��ȡʵ��ֵ
	CString Cmd_Run();
	CString Cmd_Stop();

	CString StartingProgram();
	CString ReadingError();
	CString AcknowledgeError();
	CString DescriptionRate();

	CString float_format(float fVal);
};