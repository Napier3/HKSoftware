#pragma once

#include "../../../../Module/OSInterface/OSInterface.h"

#define MAX_HARM_COUNT        32
#define MAX_BINARYIN_COUNT	20
#define MAX_BINARYOUT_COUNT	20
#define MAX_VOLTAGE_COUNT	32
#define MAX_CURRENT_COUNT	32
#define MAX_PARACOUNT_BINARY 	8
#define MAX_MODULE_COUNT		12		//���ģ����

#ifndef EPSINON
#define EPSINON 0.000001
#endif

typedef struct tmt_step_UI
{
public:
    void init()
    {
        for (int i=0;i<MAX_VOLTAGE_COUNT;i++)
        {
            fU[i][0] = fU[i][1] = fU[i][2] =  fI[i][0] = fI[i][1] = fI[i][2] = 0;
        }
    }

    tmt_step_UI()	{	init();	}
    virtual ~tmt_step_UI(){}

    float fU[MAX_VOLTAGE_COUNT][3];	//12*(��ֵ+��λ+fre)
    float fI[MAX_CURRENT_COUNT][3];
}tmt_StepUI;

typedef struct tmt_binary_in
{
public:
    int		nSelect;
    int		nTrigMode;	//0-�����ش��� 1-�½��ش���

public:
    void init()
    {
        nSelect = 1;
        nTrigMode = 0;
    }

    tmt_binary_in()	{	init();	}
    virtual ~tmt_binary_in(){}
}tmt_BinaryIn;

typedef struct tmt_binary_out
{
public:
    int		nState;		//0-�Ͽ� 1-�պ� >1-��ƽ
	//zhouhj 20210616 ���� 2-ͬ��һ��״̬,���ھ���ȸ߼����鿪����ת����
    int		nMode;		//��ת������ʽ 0-ʱ�䴥�� 1-����������  2-ͬ��һ��״̬
    float	fTimeTrig;	//��תʱ�䣬0Ϊ����ת,����Ϊ���̶�ʱ�䷭ת
    float	fHoldTime;	//��ת����ʱ��

public:
    void init()
    {
        nState = 0;
        nMode = 0;
        fTimeTrig = 0;
        fHoldTime = 0;
    }

    tmt_binary_out()	{	init();	}
    virtual ~tmt_binary_out(){}
}tmt_BinaryOut;

typedef struct tmt_channel_harm
{
public:
	bool	m_bSelect;//�Ƿ�ʹ��
    int		nIndex;
    float	fContent;//������
    float	fAmp;
    float	fAngle;
    float	fFreq;
    bool	bDC;

public:
    void init()
    {
		m_bSelect = false;
        nIndex = 0;
        fContent= 0;
        fAmp = fAngle = fFreq = 0;
        bDC = 0;
    }

    tmt_channel_harm()	{	init();	}
    virtual ~tmt_channel_harm(){}
}tmt_ChannelHarm;

typedef struct tmt_channel_ramp
{
public:
    int		nIndex;	//�ݱ�г����� -1-�޵ݱ� 0-�ݱ�ֱ�� 1-�ݱ���� 2~n-�ݱ�2~n��г��
    int		nType;	//�ݱ����ͣ�0-��ֵ 1-��λ 2-Ƶ��
    int		nMode;	//�ݱ�ģʽ��0-���ݵݱ�	1-����
    float	fBegin;
    float	fEnd;
    float	fStep;
    float	fStepTime;

public:
    void init()
    {
        fBegin = fEnd = fStep = fStepTime = 0;
        nMode = nType = 0;
        nIndex = -1;
    }

    tmt_channel_ramp()	{	init();	}
    virtual ~tmt_channel_ramp(){}
}tmt_ChannelRamp;

typedef struct tmt_channel
{
public:
    tmt_ChannelHarm Harm[MAX_HARM_COUNT];
    tmt_ChannelRamp Ramp;

public:
    void init()
	{
		for (int j=0;j<MAX_HARM_COUNT;j++)
		{
			Harm[j].fAmp = 0;
			Harm[j].fFreq = 0;
			Harm[j].nIndex = 0;
		}
	}

	void setSel(bool bSel)
	{
		for (int i=2; i<MAX_HARM_COUNT; i++)
		{
			Harm[i].m_bSelect = bSel;
		}
	}

	void init(bool bSel, float fAmp,float fAngle)
	{
		Harm[0].fAmp = 0;

		Harm[1].m_bSelect = true;
		Harm[1].nIndex = 1;
		Harm[1].fAngle = fAngle;
		Harm[1].fAmp = fAmp;
		Harm[1].fContent = 100;	

		for (int i=2; i<MAX_HARM_COUNT; i++)
		{
			Harm[i].m_bSelect = bSel;
			Harm[i].nIndex = i;
			Harm[i].fAngle = fAngle;
			Harm[i].fAmp = 0;
			Harm[i].fContent = 0;
		}
	}

	void setContent(int nHarmIndex,float fVal)
	{
		if ((fVal >= 0) && (fVal <= 100))
		{
			Harm[nHarmIndex].fContent = fVal;
			Harm[nHarmIndex].fAmp = Harm[1].fAmp * 0.01 * fVal;
		}
	}

	void setAmp(int nHarmIndex,float fVal)
	{
		float fBaseAmp = Harm[1].fAmp;
		if ((fBaseAmp > EPSINON) && (fVal <= fBaseAmp))
		{
			if (fVal > EPSINON)
			{
				Harm[nHarmIndex].fAmp = fVal;
			}
			else
			{
				Harm[nHarmIndex].fAmp = 0;
			}
			Harm[nHarmIndex].fContent = fVal * 100 / fBaseAmp;
		}
	}

	float getTotalVal()
	{
		float fTotal = 0;
		for (int i=0; i<MAX_HARM_COUNT; i++)
		{
			if (Harm[i].m_bSelect)
			{
				fTotal += Harm[i].fAmp;
			}
		}
		return fTotal;
	}

	float getCurHarmAmp(int nHarmIndex)
	{
		float fVal = 0;
		if (Harm[nHarmIndex].m_bSelect)
		{
			fVal = Harm[nHarmIndex].fAmp;
		}
		return fVal;
	}

    tmt_channel()	{	init();	}
	virtual ~tmt_channel(){}
}tmt_Channel;

typedef struct tmt_time
{
public:
    int		nYear;
    int		nMonth;
    int		nDay;
    int		nHour;
    int		nMinutes;
    int		nSeconds;
    int		nMilliSeconds;

public:
    void init()
	{
        nYear = 0;
        nMonth = 0;
        nDay = 0;
        nHour = 0;
        nMinutes = 0;
        nSeconds = 0;
        nMilliSeconds = 0;
	}

    tmt_time()	{	init();	}
	virtual ~tmt_time(){}
}tmt_Time;

typedef struct
{
public:
    BOOL    m_bUChange[MAX_VOLTAGE_COUNT][3];//mag   ph   fre
    BOOL    m_bIChange[MAX_CURRENT_COUNT][3];
    tmt_StepUI m_uiStepData[3000];	//�ݱ�����
    int        m_nStepCount;
}tmt_GradientProcess;

typedef struct tmt_gradient_common
{
public:
    tmt_GradientProcess m_oGradientProcess;
public:
    tmt_gradient_common(){m_oGradientProcess.m_nStepCount = 0;}
    virtual ~tmt_gradient_common(){}
}tmt_GradientCommon;
