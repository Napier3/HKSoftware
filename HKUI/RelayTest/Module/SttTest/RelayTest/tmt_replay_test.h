#pragma once
#include "tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"

//��������:0�޴�����1�ֶ�������2GPS������3����������
#define COMTRADE_TRIGGRE_TYPE_No		0
#define COMTRADE_TRIGGRE_TYPE_Manual	1
#define COMTRADE_TRIGGRE_TYPE_GPS		2
#define COMTRADE_TRIGGRE_TYPE_Binary	3

//����������ģʽ��1ѭ����������л���0�������л�
#define COMTRADE_TRIGGRE_AFTER_TYPE_Immediately	0
#define COMTRADE_TRIGGRE_AFTER_TYPE_Normal		1

typedef struct tmt_replay_test
{
	int m_nSampleFreq;
	int m_nModuleSel[MAX_MODULE_COUNT];		//ģ���Ƿ�ѡ��
	int m_nModuleChNum[MAX_MODULE_COUNT];	//ģ��ͨ����
	int m_nTripType;       //������ʽ	0�޴�����1�ֶ�������2GPS������3����������
	int m_nTrigTimeS;		//GPSʱ�䴥����Ч
	int m_nTrigTimeNS;
	int m_nStartLoopCount;	//��ʼѭ����������������������Ч
	int m_nStartCycleNum;	//��ʼѭ���ܲ������޴�����������������Ч
	int m_nTrigAfterMode;	//����������ģʽ��ѭ����������л����������л�

	int  m_nBinLogic;
	tmt_BinaryIn m_binIn[MAX_BINARYIN_COUNT];

	tmt_replay_test()
	{
		init();
	}
	void init()
	{
		int i=0;
		m_nSampleFreq = 50000;
		m_nTripType = COMTRADE_TRIGGRE_TYPE_No;
		m_nTrigTimeS = 0;
		m_nTrigTimeNS = 0;
		m_nStartLoopCount = 0;
		m_nStartCycleNum = 6;
		m_nTrigAfterMode = COMTRADE_TRIGGRE_AFTER_TYPE_Immediately;

		for (i=0; i<MAX_MODULE_COUNT; i++)
		{
			m_nModuleSel[i] = 0;
			m_nModuleChNum[i] = 0;
		}

		for (i=0; i<MAX_BINARYIN_COUNT; i++)
		{
			if(i<MAX_PARACOUNT_BINARY)
			{
				m_binIn[i].nSelect = 1;
			}
			else
			{
				m_binIn[i].nSelect = 0;
			}
			m_binIn[i].nTrigMode = 0;
		}
		m_nBinLogic = 0; 
	}
	bool IsLoop()
	{
		if ((m_nTripType == COMTRADE_TRIGGRE_TYPE_No) && (m_nStartLoopCount == 0))
		{
			return false;
		}
		return true;
	}
	int SortModuleSelArray(int *pSortArr,int &nModuleCount,int &nChCount)
	{//pSortArr[MAX_MODULE_COUNT]:��ѡ�е�ģ�����������ڿ�ͷ
		int nSortIndex = 0;
		nModuleCount = 0;
		nChCount = 0;

		for (int i=0; i<MAX_MODULE_COUNT; i++)
		{
			if (m_nModuleSel[i] != 0)
			{
				pSortArr[nSortIndex++] = i;
				nModuleCount++;
				nChCount += m_nModuleChNum[i];
			}
		}
		return nModuleCount;
	}
	int GetChSelCount()
	{
		int nChCount = 0;
		for (int i=0; i<MAX_MODULE_COUNT; i++)
		{
			if (m_nModuleSel[i] != 0)
			{
				nChCount += m_nModuleChNum[i];
			}
		}
		return nChCount;
	}
}tmt_ReplayTest;



void stt_xml_serialize(tmt_ReplayTest *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_write_ReplayTest();

