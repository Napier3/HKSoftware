#pragma once

#include "../Common/tmt_common_def.h"

#define TMT_RESULT_ID_EventTime	_T("EventTime")

//��¼���Թ����в�����״̬�ṹ��
typedef struct tmt_event_result
{
	long m_nUdc;			//����ֱ�����
	long m_nOverHeat;	//����
	long m_nIOverLoad;	//��������
	long m_nUOverLoad;	//��ѹ����

	long m_nUShort;		//��ѹ��·
	long m_IBreak[MAX_CURRENT_COUNT];		//������·

	long m_BinIn[MAX_BINARYIN_COUNT];		//������״̬:�Ͽ�0���ϲ�1
	long m_BinOut[MAX_BINARYOUT_COUNT];

	long m_nCurrStateIndex;		//��ǰ״̬����

	void init()
	{
		m_nUdc = 0;
		m_nOverHeat = 0;
		m_nIOverLoad = 0;
		m_nUOverLoad = 0;

		m_nUShort = 0;
		memset(m_IBreak,0,sizeof(long)*MAX_CURRENT_COUNT);

		memset(m_BinIn,0,sizeof(long)*MAX_BINARYIN_COUNT);
		memset(m_BinOut,0,sizeof(long)*MAX_BINARYOUT_COUNT);
	}
	void UpdateBinOut(tmt_BinaryOut	*parrBinOut,int nBinOutNum)
	{
		for(int i=0; i<nBinOutNum; i++)
		{
			m_BinOut[i] = parrBinOut[i].nState;
		}
	}
	tmt_event_result(){	init();	}
}tmt_EventResult;