#pragma once
#include "tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"
#include "tmt_test_paras_head.h"

//��������:0�޴�����1�ֶ�������2GPS������3����������
#define DIG_REPLAY_TRIGGRE_TYPE_No	     	0
#define DIG_REPLAY_TRIGGRE_TYPE_Manual	    1
#define DIG_REPLAY_TRIGGRE_TYPE_GPS		    2
#define DIG_REPLAY_TRIGGRE_TYPE_Binary   	3

#define DIG_REPLAY_MODE_PkgTime     	    0//������ʱ��ط�
#define DIG_REPLAY_MODE_EqualInterval     	1//���ȼ���ط�
#define DIG_REPLAY_MODE_Custom          	2//���Զ���ط�

#define DIG_REPLAY_INTERVAL_TYPE_ALL  	    0//�ط���������(ȫ��)
#define DIG_REPLAY_INTERVAL_TYPE_Custom     1//�ط���������(����)

#define DIG_REPLAY_FIBER_MAX_NUM                   48//����������
#define DIG_REPLAY_CB_MAX_NUM                      48//���ƿ��������


typedef struct tmt_dig_replay_cb
{
	long m_nSelCB;//ѡ����ƿ�
    long m_nFiberNum;//�������
    long m_oFiberIndex[DIG_REPLAY_FIBER_MAX_NUM];//��ں�,��0��ʼ���
    long m_nAppID;
	long m_nTotalFrames;//��֡��
	long m_nBeginFrameIndex;//��ʼ֡��,��ӦֵС�ڵ���0����ǰ����,δѡ����
	long m_nEndFrameIndex;//����֡��
	float m_fOffsetTime;//��ʱ����(��λ:us)


    void init()
    {
		m_nFiberNum = 0;
		m_nSelCB = 1;
        for (int nIndex = 0;nIndex<DIG_REPLAY_FIBER_MAX_NUM;nIndex++)
        {
            m_oFiberIndex[nIndex] = 0;
        }

		m_nAppID = 0x4001;
		m_nTotalFrames = 0;
		m_nBeginFrameIndex = 0;
		m_nEndFrameIndex = 0;
		m_fOffsetTime = 0.0f;
    }

	BOOL HasSendDatas()//�жϸÿ��ƿ��Ƿ��з�������(1:���ƿ��Ƿ�ѡ��;2:���ƿ��Ƿ����������)
	{
		if (m_nSelCB == 0)
		{
			return FALSE;
		}

		if (m_nFiberNum <= 0)
		{
			return FALSE;
		}

		return HasValidPkg();
	}

	BOOL HasSelCurrFiberIndex(long nFiberIndex)
	{
		for (int nIndex = 0;nIndex<m_nFiberNum;nIndex++)
		{
			if (nFiberIndex == m_oFiberIndex[nIndex])
			{
				return TRUE;
			}
		}

		return FALSE;
	}

	BOOL HasValidPkg()
	{
		if (m_nBeginFrameIndex <= 0)
		{
			return FALSE;
		}

		if (m_nBeginFrameIndex>m_nEndFrameIndex)
		{
			return FALSE;
		}

		return TRUE;
	}
}TMT_DIG_REPLAY_CB;

typedef struct tmt_dig_replay_para
{
	long m_nCBNum_SV92;//9-2����ֵ���ƿ�����
    long m_nCBNum_GOOSE;//GOOSE���ƿ�����
	TMT_DIG_REPLAY_CB m_oCB_SV92[DIG_REPLAY_CB_MAX_NUM];
    TMT_DIG_REPLAY_CB m_oCB_GOOSE[DIG_REPLAY_CB_MAX_NUM];

    long m_nTripType;       //������ʽ	0�޴�����1�ֶ�������2GPS������3����������
	long m_nReplayMode_SV;//SV�ط�ģʽ
	long m_nReplayMode_GOOSE;//GOOSE�ط�ģʽ
	float m_fEqualIntervalTimeSV;//SV�ȼ���ļ��ʱ��(us)
	float m_fEqualIntervalTimeGOOSE;//GOOSE�ȼ���ļ��ʱ��(us)
	float m_fShakeValue;//����ֵ(us)
	long  m_nIsLoop;//�Ƿ�ѭ��(0��ѭ��,1ѭ��)
	long  m_nLoopNum;//ѭ������,ѭ��1��ʵ�����2��
	long  m_nReplayIntervalType;//�ط�������������(0:ȫ���ط�,1:���ֻط�)
	long m_nTotalFrameBeginIndex;//��ʼ֡��
	long m_nTotalFrameEndIndex;//����֡��
	tmt_time	    m_tGps;
	float       m_fOutPutTime;	// ����ʱ��,�����������,���ݸ��ײ�,���ڿ������ֹͣ

    long  m_nBinLogic;
    tmt_BinaryIn m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn m_binInEx[MAX_ExBINARY_COUNT];//ϵͳ��չ������

    tmt_dig_replay_para()
    {
        init();
    }
    void init()
    {
        int nIndex = 0;
		m_nCBNum_SV92 = 0;
        m_nCBNum_GOOSE = 0;
        m_nTripType = DIG_REPLAY_TRIGGRE_TYPE_No;
		m_nReplayMode_SV = DIG_REPLAY_MODE_PkgTime;
		m_nReplayMode_GOOSE = DIG_REPLAY_MODE_PkgTime;
		m_fEqualIntervalTimeSV = 250.0f;
		m_fEqualIntervalTimeGOOSE = 5000000.0f;
		m_fShakeValue = 0.0f;
		m_fOutPutTime = 5.0f;
		m_nIsLoop = 0;
		m_nLoopNum = 0;
		m_nReplayIntervalType = DIG_REPLAY_INTERVAL_TYPE_ALL;
		m_nTotalFrameBeginIndex = 0;
		m_nTotalFrameEndIndex = 0;
		m_tGps.init();
		memset(m_oCB_SV92,0,sizeof(TMT_DIG_REPLAY_CB)*DIG_REPLAY_CB_MAX_NUM);
        memset(m_oCB_GOOSE,0,sizeof(TMT_DIG_REPLAY_CB)*DIG_REPLAY_CB_MAX_NUM);

        for (nIndex = 0;nIndex<DIG_REPLAY_CB_MAX_NUM;nIndex++)
        {
			m_oCB_SV92[nIndex].init();
            m_oCB_GOOSE[nIndex].init();
        }

        for (nIndex=0; nIndex<MAX_BINARYIN_COUNT; nIndex++)
        {
#ifdef _STT_NOT_IN_TEST_SERVER_
            if(nIndex<g_nBinCount)
            {
                m_binIn[nIndex].nSelect = 1;
            }
            else
            {
                m_binIn[nIndex].nSelect = 0;
            }
#else
			m_binIn[nIndex].nSelect = 0;
#endif
            m_binIn[nIndex].nTrigMode = 0;
        }

        for(nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
		{
			m_binInEx[nIndex].nSelect = 0;
			m_binInEx[nIndex].nTrigMode = 0;
		}

        m_nBinLogic = 0;
    }

	long GetUseFiberNum();//��ȡ��ǰʹ�õĹ��������SV+GOOSE
	long GetTotalPkgNum(long nFiberIndex);//��ȡ��ǰ���,SV+GOOSE���ĵ���֡��
	BOOL HasPcapSendDatas();//�жϵ�ǰ�Ƿ������������
	long GetCurSelCtrlNum_SVGOOSE();//��ȡ��ǰѡ��Ŀ��ƿ�����
	void InitAllCB_TotalFrames();//20230824 suyang ��ʼ�����п��ƿ����ʼ֡�ͽ���֡

	TMT_DIG_REPLAY_CB* FindTotalPkgCtrl_SV(long nAppID);//��ȡ����ǰSV���ƿ�
	TMT_DIG_REPLAY_CB* FindTotalPkgCtrl_GOOSE(long nAppID);//��ȡ����ǰGOOSE���ƿ�

}tmt_DigReplayParas;

typedef struct tmt_dig_replay_test : public TMT_PARAS_HEAD
{
    tmt_DigReplayParas m_oReplayParas;

    tmt_dig_replay_test()
    {
        init();
    }
    void init()
    {
        init_head(); //20210918 zhouhj
        strcpy(m_pszMacroID, STT_MACRO_ID_DigReplayTest);
        m_nVersion = 0x00010001;
        m_nSelected = 1;
        m_nTestState = 0;
        m_oReplayParas.init();
    }
}tmt_DigReplayTest;



void stt_xml_serialize(tmt_DigReplayParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_write_DigReplayTest();
CSttXmlSerializeBase* stt_xml_serialize(tmt_DigReplayTest *pTests, CSttXmlSerializeBase *pXmlSerialize);

