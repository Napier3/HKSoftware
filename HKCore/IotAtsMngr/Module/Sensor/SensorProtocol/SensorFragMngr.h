#pragma once

#include <list>
#include "SttGlobalSensorDef.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"
using namespace std;

/***********************************
��������Ƭ���Ľ��������߼�������ο���������ҵ����Э��淶���ĵ�
SDU:���з�Ƭ���ĺϲ�����������ʱ�����ݲ���
PDU:����ĳ����Ƭ���ĵ����ݲ���
***********************************/

//PDU�ṹ��
//��Ƭͷ�ͷ�Ƭ�������ݣ��ϳ�ΪЭ�����ݵ�Ԫ�����PDU
typedef struct _sensor_frag_pdu_
{
	int m_nPDUSeq; //PDU�����
	int m_nDataLen;
	BYTE *m_pPDUData;

	_sensor_frag_pdu_()
	{
		m_nPDUSeq = 0;
		m_nDataLen = 0;
		m_pPDUData = NULL;
	}
	_sensor_frag_pdu_(int nPDUSeq,int nDataLen,BYTE *pBuf)
	{
		m_nPDUSeq = nPDUSeq;
		m_nDataLen = nDataLen;
		m_pPDUData = pBuf;
	}
	~_sensor_frag_pdu_()
	{
		if (m_pPDUData != NULL)
		{
			delete m_pPDUData;
			m_pPDUData = NULL;
		}
	}
	bool operator== (const _sensor_frag_pdu_ &oPDU)
	{
		return ( this->m_nPDUSeq == oPDU.m_nPDUSeq);
	}
	bool operator< (const _sensor_frag_pdu_ &oPDU)
	{
		return ( this->m_nPDUSeq < oPDU.m_nPDUSeq);
	}
}SensorFragPDU;

//SDU�ṹ��
//���з�Ƭ����������϶��ɵ������������ݳ�Ϊҵ�����ݵ�Ԫ����ƣ�SDU����
typedef struct _sensor_frag_sdu_
{
	__int64 m_n64SensorID;
	int m_nPkgType;
	int m_nParaCnt;
	int m_nSDUSeq;
	int m_nLastPDUSeq;			//�յ����һ��PDUʱ����
	DWORD m_dwTimeStart;		//��ʱ��ʼʱ��
	int m_nTimeOut;				//��ʱ����
	list<SensorFragPDU *> m_listPDU;	//��SDU��PDU����

	_sensor_frag_sdu_()
	{
		m_n64SensorID = 0;
		m_nPkgType = 0;
		m_nParaCnt = 0;
		m_nSDUSeq = 0;
		m_nLastPDUSeq = 0;
		m_nTimeOut = 60000;	//1������δ��ȫ��ص����з�Ƭ���ģ�����
		m_listPDU.clear();
	}
	~_sensor_frag_sdu_()
	{
		for (list<SensorFragPDU *>::iterator it = m_listPDU.begin(); it != m_listPDU.end(); it++)
		{
			if (NULL != *it)
			{
				delete *it;
				*it = NULL;
			}
		}
		m_listPDU.clear();
	}
	BOOL IsTimeOut(DWORD dwCurTime)		{	return (dwCurTime - m_dwTimeStart >= m_nTimeOut);	}
	SensorFragPDU *FindSensorFragPDU(int nPDUSeq)
	{
		SensorFragPDU *pFragPDU = NULL;
		for (list<SensorFragPDU *>::iterator it = m_listPDU.begin(); it != m_listPDU.end(); it++)
		{
			pFragPDU = *it;
			if (pFragPDU->m_nPDUSeq == nPDUSeq)
			{
				return pFragPDU;
			}
		}
		return NULL;
	}
	int GetSDUDataLen()
	{
		int nRet = 0;
		for (list<SensorFragPDU *>::iterator it = m_listPDU.begin(); it != m_listPDU.end(); it++)
		{
			nRet += (*it)->m_nDataLen;
		}
		return nRet;
	}
}SensorFragSDU;


/////////////////////////////

class CSensorFragMngr
{
private:
	CSensorFragMngr();
	virtual ~CSensorFragMngr();

protected:
	CAutoCriticSection m_oSensorFragSDUCriticSection;
	vector<SensorFragSDU *> m_vecSensorFragSDU;		//SDU����

	//���Ҷ�Ӧ��SDU
	SensorFragSDU *FindSensorFragSDU(__int64 n64SensorID,int nSDUSeq);
	//ɾ��ָ����SDU
	void DeleteSensorFragSDU(SensorFragSDU *pFragSDU);

	//���PDU��ƥ���SDU�����У�û�����ȴ���SDU�������򷵻�������SDU
	SensorFragSDU *AddFragPDU(BYTE *pBuf,long nLen,__int64 n64SensorID,int nPkgType,int nParaCnt,int nTimeOut=60000);
	//PDU��Ƭ���������룬�ϲ����������ģ��������ṹ����
	void AnalysisWholeSDU(SensorFragSDU *pFragSDU,SensorPkgInfo &oSensorPkgInfo);

public:
	static CSensorFragMngr *g_pSensorFragMngr;
	static long g_nSensorFragMngrRef;

	static CSensorFragMngr *Create();
	static void Release();

	static BOOL CheckWholeFragSDU(SensorPkgInfo &oSensorPkgInfo,BYTE *pBuf,long nLen,__int64 n64SensorID
		,int nPkgType,int nParaCnt,int nTimeOut=60000);
	static void ProcessTimeOut(DWORD dwCurTime);
};

//��Ƭ���ļ�鳬ʱ�̣߳���ʱ����
void *CheckFragSDUThread(LPVOID lParam);