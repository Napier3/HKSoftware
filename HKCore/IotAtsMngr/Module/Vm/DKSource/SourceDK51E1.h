#pragma once
#include "..\..\..\..\Module\Serial\Serial.h"
#include "SourceDKDef.h"

class CSourceDK51E1 : public CSerial
{
public:
	long m_nBaudRate;
	long m_nByteSize;
	long m_nParity;
	long m_nStopBits;//ֹͣλ��0,1,2��Ӧ1,1.5,2

	long m_nRxID;//�����ն˵��豸��
	long m_nTxID;//�����ն˵��豸��

	BYTE m_strData[1024];//output
	CString m_strBuffer;//input

	CDataGroup* m_pReport;//����timer�������ϱ�(��ѹ����)

	CString m_strCurProcedure;//��ǰ����
	BOOL m_bIsXTimerRunning;//�Ƿ������˼�ʱ��

private:
	BOOL m_bIsConnected;

public:
	CSourceDK51E1();
	virtual ~CSourceDK51E1();

private:
	float ByteArr_To_Float(const char* pByteArr);//Byte����תfloat
	long CString_htonl(const CString& strNum);//�ߵ�λת��
	float CString_To_Float(const CString& strNum);
	CString CString_To_Float_Str(const CString& strNum);
	CString Float_To_CString(float fNum);
	void Generate(long nProcedureID, const CString& strData, long& nByteLen);//����ͨ������ģ��
	long GetXOR(BYTE* strMsg, long nLen);//�������

private:
	//���Զ����Ե��ú��ʹ�������ĺ���
	CString SetACGear(tagDKSource* pDKSource);//����Դ��λ����
	CString SetACRange(tagDKSource* pDKSource);//����Դ���Ȳ���
	CString SetACPhase(tagDKSource* pDKSource);//����Դ��λ����
	CString SetACRate(tagDKSource* pDKSource);//����ԴƵ��
	CString SetACPrinciple(tagDKSource* pDKSource);//����Դ����ģʽ
	CString SetACEnableLoop(tagDKSource* pDKSource);//�ջ�����ʹ��
	CString SetACVerification(tagDKSource* pDKSource);//���õ���У�鲢����
	CString SetACActivePower(tagDKSource* pDKSource);//�����й�����
	CString SetACReactivePower(tagDKSource* pDKSource);//�����޹�����
	CString SetDCAmp(tagDKSource* pDKSource);//����ֱ��Դ��ֵ
	CString SetSysMode(tagDKSource* pDKSource);//����ϵͳģʽ
	CString SetSysPage(tagDKSource* pDKSource);//�����ն˵�ǰ��ʾ����
	CString SetDCRange(tagDKSource* pDKSource);//����ֱ��Դ��ֵ
	CString SetDCMeasurementType(tagDKSource* pDKSource);////����ֱ�����������
	CString SetDCGear(tagDKSource* pDKSource);//����ֱ��Դ��λ����
	CString SetRemoteOutput(tagDKSource* pDKSource);//��������������ڵ�״̬
	CString SetRemoteControl(tagDKSource* pDKSource);//����ϵͳ��������
	CString SetACHarmonicParam(tagDKSource* pDKSource);//����г������

	void GetACError(CDataGroup* pDataGroup);//���������
	void GetDCParam(CDataGroup* pDataGroup);//��������׼�����
	void GetACParam(CDataGroup* pDataGroup);//��ֱ��Դ����
	void GetRemoteInputState(CDataGroup* pDataGroup);//����������������ڵĵ�ǰ״̬
	void GetDCMeasurementParam(CDataGroup* pDataGroup);//��ֱ�����������

public:
	BOOL IsConnectSuccess()	{	return m_bIsConnected;	}
	BOOL Connect(long nComNumber);
	BOOL Disconnect();
	long CloseDevice();

	BOOL RunProcedure(tagDKSource* pDKSource, long nParamNum = 0);//����д����

	CDataGroup* ParseBuffer();//���ڶ�����
	void GetReport(CString& strDCReport, CString& strACReport);//��ȡRTDATA����
};