#pragma once

#include <list>
#include "SttGlobalSensorDef.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"
using namespace std;

/***********************************
传感器分片报文解析处理逻辑，具体参考“传感器业务报文协议规范”文档
SDU:所有分片报文合并成完整报文时的数据部分
PDU:具体某个分片报文的数据部分
***********************************/

//PDU结构体
//分片头和分片数据内容，合称为协议数据单元，简称PDU
typedef struct _sensor_frag_pdu_
{
	int m_nPDUSeq; //PDU的序号
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

//SDU结构体
//所有分片数据内容组合而成的整个数据内容称为业务数据单元（简称，SDU）。
typedef struct _sensor_frag_sdu_
{
	__int64 m_n64SensorID;
	int m_nPkgType;
	int m_nParaCnt;
	int m_nSDUSeq;
	int m_nLastPDUSeq;			//收到最后一个PDU时设置
	DWORD m_dwTimeStart;		//计时开始时间
	int m_nTimeOut;				//超时丢弃
	list<SensorFragPDU *> m_listPDU;	//该SDU下PDU链表

	_sensor_frag_sdu_()
	{
		m_n64SensorID = 0;
		m_nPkgType = 0;
		m_nParaCnt = 0;
		m_nSDUSeq = 0;
		m_nLastPDUSeq = 0;
		m_nTimeOut = 60000;	//1分钟内未收全相关的所有分片报文，则丢弃
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
	vector<SensorFragSDU *> m_vecSensorFragSDU;		//SDU链表

	//查找对应的SDU
	SensorFragSDU *FindSensorFragSDU(__int64 n64SensorID,int nSDUSeq);
	//删除指定的SDU
	void DeleteSensorFragSDU(SensorFragSDU *pFragSDU);

	//添加PDU到匹配的SDU链表中，没有则先创建SDU，收齐则返回完整的SDU
	SensorFragSDU *AddFragPDU(BYTE *pBuf,long nLen,__int64 n64SensorID,int nPkgType,int nParaCnt,int nTimeOut=60000);
	//PDU分片报文已收齐，合并成完整报文，解析到结构体中
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

//分片报文检查超时线程，超时则丢弃
void *CheckFragSDUThread(LPVOID lParam);