#pragma once

#include <math.h>
#include <winsock.h>
#include "../../../../Module/Serial/Serial.h"
#include "../../../../Module/Serial/SerialConfig/SerialConfig.h"
#include "../../../../Module/DataMngr/DataGroup.h"

#define Comm_Text_ReceiveLens 22
#define Comm_Text_SendLens 14

#define DTVP_TIMER_NUMBER_JUDGERSLT 	100     //��λ��100ms�ж���ȷ���Ƿ���Խ���
#define DTVP_TIMER_NUMBER_READMEAS  	2000    //�ϱ�ʵʱ����

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

//ָ������
#define DTVP_SET_ORDER_NOSET      0   //δ����
#define DTVP_SET_ORDER_SETENABLE  1   //����ʹ��
#define DTVP_SET_ORDER_SETANGLE   2   //����ת��

class CDtvp200Test
{
public:
	CDtvp200Test();
	virtual ~CDtvp200Test(void);

	CSerial m_Serial;

	//���õĲ���
	int m_nEnable[2];		//ʹ�� 0-���� 1-��λ
	int m_nWrokModel[2];	//���ƹ���ģʽ��0������λ�ã�1�����λ�ã�0-���� 1-��λ
	int m_nAngleControl[2];//���ƽǶ�  0-���� 1-��λ(����0.001)Ҳ����˵������1000 ʵ������1	 ��Ҫ����ת,�����óɸ���
	int m_nSpeedControl[2];//�����ٶ�  0-���� 1-��λ(����0.001)Ҳ����˵������1000 ʵ������1

	//��ȡ��ʵ��ֵ
	int m_nPitchRtAngle;//�ڿ�Ƕ�   ����0.001
	float m_fPitchRtAngle;//�ڿ�ʵ�ʽǶ�
	int m_nPitchRtSpeed;//�ڿ��ٶ�
	int m_nPitchRtEnable;//�ڿ�״̬ 0-������� 1-���ʹ��
	int m_nPitchRtArrive;//�ڿ򵽴� 0-δ����ָ��λ�� 1-����ָ��λ��

	int m_nPositionRtAngle;//���Ƕ�   ����0.001
	float m_fPositionRtAngle;//���ʵ�ʽǶ�
	int m_nPositionRtSpeed;//����ٶ�
	int m_nPositionRtEnable;//���״̬ 0-������� 1-���ʹ��
	int m_nPositionRtArrive;//��򵽴� 0-δ����ָ��λ�� 1-����ָ��λ��

	//��ʱ��
	BOOL m_bIsXTimerRunning;
	//ָ������
	int m_nOrderSetting;//0-δ���� 1-����ʹ�� 2-����ת��
	long m_nRunTime;
	long m_nJudgeCount;  //Ϊ�˷�ֹ���������ڿ����ת���ٶȵ�Ӱ�죬����

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
	ULONG m_nIsConnectSuccess;//����״̬
	CString m_strError;  //������

	void SetEnable(BYTE *cmd,int nOrder);
	void AngleSet(BYTE *cmd,int nOrder);
	BYTE CRC16(BYTE *cmd,int nLength);
	int Cal4ByteToInt(BYTE *byteContext,int nIndex);//С��
	int GetHeigthByte(BYTE byteValue);
	int GetLowByte(BYTE byteValue);

	int send_command(BYTE *cmd);
	void InitParas();
};